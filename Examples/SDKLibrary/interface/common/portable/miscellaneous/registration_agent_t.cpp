/* -----------------------------------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
----------------------------------------------------------------------------------------------------------------- */

#include "registration_agent_t.h"

#if (UASDK_INCLUDE_SERVER_REGISTRATION_AGENT > 0)

#include "opcua_build_info_t.h"
#include "certificate_validation_options_t.h"
#include "opcua_get_endpoints_request_t.h"
#include "opcua_get_endpoints_response_t.h"
#include "icertificate_private_key_password_provider_t.h"
#include "timer_provider_t.h"
#include "opcua_register_server_request_t.h"
#include "opcua_register_server_response_t.h"

static const char* PROTOCOL = "opc.tcp://";

namespace uasdk
{
/*
 * TimerCallback_t Functions
 */
Status_t RegistrationAgent_t::TimerCallback_t::Intialise(const IntrusivePtr_t<RegistrationAgent_t>& registrationAgent_)
{
  if (!registrationAgent_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  registrationAgent = registrationAgent_;
  return OpcUa_Good;
}

Status_t RegistrationAgent_t::TimerCallback_t::TimerElapsed(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(registrationAgent);
  return registrationAgent->RegisterServer(true, false, 0);
}

/*
 * Private Functions
 */
Status_t RegistrationAgent_t::CreateClient(const IServerConfiguration_t& serverConfiguration)
{
  Status_t status;

  UASDK_RETURN_UNEXPECTED_IF_NULL(serverConfiguration.BuildInfo());
  UASDK_RETURN_UNEXPECTED_IF_NULL(serverConfiguration.ApplicationURI());

  IntrusivePtr_t<IClientConfiguration_t> clientConfiguration = UAClient_t::CreateConfiguration(status);
  if (!clientConfiguration.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<AppDescription_t> applicationDescription = new SafeRefCount_t<AppDescription_t>();
  if (!applicationDescription.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  status = applicationDescription->ApplicationName().Text().CopyFrom(serverConfiguration.BuildInfo()->ProductName());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = applicationDescription->ApplicationUri().CopyFrom(*serverConfiguration.ApplicationURI());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = applicationDescription->ApplicationType().Value() = ApplicationType_t::OPCUA_APPLICATION_TYPE_CLIENT;
  
  clientConfiguration->ApplicationDescription(applicationDescription);
  clientConfiguration->ClientCyclicRateInMs(serverCyclicRateInMs);
  clientConfiguration->SecurityCertificateDirectoryStoresPath(serverConfiguration.SecurityCertificateDirectoryStoresPath());
  clientConfiguration->CertificatePrivateKeyPasswordProvider(serverConfiguration.CertificatePrivateKeyPasswordProvider());
  
  //Create the client instance
  uaClient = new SafeRefCount_t<UAClient_t>();
  if (!uaClient.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

#if (UASDK_INCLUDE_CLIENT_WINDOWS_LINUX_MT > 0)
  status = uaClient->Initialise(clientConfiguration, 1);
#elif (UASDK_INCLUDE_CLIENT_WINDOWS_LINUX_ST > 0)
  status = uaClient->Initialise(clientConfiguration);
#endif

  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

#if (UASDK_INCLUDE_SECURITY > 0)
  status = uaClient->SecurityRefreshApplicationCertificateDirectoryStores();
  if (status.IsBad())
  {
    ;//Ignore initial error
  }
#endif

  const String_t license;
  return uaClient->Start(license);
}

Status_t RegistrationAgent_t::UpdateDiscoveryServerEndpoint(const String_t& discoveryServerUrl)
{  
  UASDK_RETURN_UNEXPECTED_IF_NULL(uaClient);

  IntrusivePtr_t<GetEndpointsRequest_t> getEndpointsRequest = new SafeRefCount_t<GetEndpointsRequest_t>();
  if (!getEndpointsRequest.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Status_t status = getEndpointsRequest->EndpointUrl().CopyFrom(discoveryServerUrl);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<GetEndpointsResponse_t> getEndpointsResponse;
  status = uaClient->GetEndpoints(getEndpointsRequest, getEndpointsResponse);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (getEndpointsResponse->Endpoints().Size() <= 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  discoveryServerEndpoint = getEndpointsResponse->Endpoints()[0];
  return OpcUa_Good;
}

Status_t RegistrationAgent_t::GetServerUrl(const IServerConfiguration_t& serverConfiguration, String_t& result)
{
  String_t protocol;
  Status_t status = protocol.CopyFrom(PROTOCOL);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  String_t protocolWithHost;

  if (serverConfiguration.Hostnames().is_set() && serverConfiguration.Hostnames()->Count() > 0)
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(serverConfiguration.Hostnames()->GetAtIndex(0));
    status = Utilities_t::ConcatenateInputStrings(protocol, *serverConfiguration.Hostnames()->GetAtIndex(0), false, ':', protocolWithHost);
  }
  else if (serverConfiguration.IpAddresses().is_set() && serverConfiguration.IpAddresses()->Count() > 0)
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(serverConfiguration.IpAddresses()->GetAtIndex(0));
    status = Utilities_t::ConcatenateInputStrings(protocol, *serverConfiguration.IpAddresses()->GetAtIndex(0), false, ':', protocolWithHost);
  }
  else
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
  }

  String_t portNumber;
  status = Utilities_t::UlongToString(static_cast<uint64_t>(serverConfiguration.ServerEndpointTCPPort()), portNumber);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return Utilities_t::ConcatenateInputStrings(protocolWithHost, portNumber, true, ':', result);
}

Status_t RegistrationAgent_t::UpdateServerDetails(const IServerConfiguration_t& serverConfiguration)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(serverConfiguration.BuildInfo());
  UASDK_RETURN_UNEXPECTED_IF_NULL(serverConfiguration.ApplicationURI());

  if (!serverDetails.is_set())
  {
    serverDetails.reset(new SafeRefCount_t<RegisteredServer_t>());
    if (!serverDetails.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
  }

  Status_t status = serverDetails->ServerUri().CopyFrom(*serverConfiguration.ApplicationURI());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = serverDetails->ProductUri().CopyFrom(serverConfiguration.BuildInfo()->ProductUri());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  serverDetails->ServerType().Value() = ApplicationType_t::OPCUA_APPLICATION_TYPE_SERVER;

  IntrusivePtr_t<String_t> discoverUrl = new SafeRefCount_t<String_t>();
  if (!discoverUrl.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = GetServerUrl(serverConfiguration, *discoverUrl);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = serverDetails->DiscoveryUrls().Initialise(1);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  serverDetails->DiscoveryUrls()[0] = discoverUrl;

  IntrusivePtr_t<LocalizedText_t> serverName = new SafeRefCount_t<LocalizedText_t>();
  if (!serverName.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = serverName->Text().CopyFrom(serverConfiguration.BuildInfo()->ProductName());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = serverDetails->ServerNames().Initialise(1);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  serverDetails->ServerNames()[0] = serverName;

  return OpcUa_Good;
}

Status_t RegistrationAgent_t::RegisterToDiscoveryServer(bool isOnline)
{
  if (!uaClient.is_set() || !serverDetails.is_set() || !discoveryServerEndpoint.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  serverDetails->IsOnline().Value(isOnline);

  IntrusivePtr_t<RegisterServerRequest_t> registerServerRequest = new SafeRefCount_t<RegisterServerRequest_t>();
  if (!registerServerRequest.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Status_t status = registerServerRequest->Server().CopyFrom(*serverDetails);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<RegisterServerResponse_t> registerServerResponse;
  status = uaClient->RegisterServer(discoveryServerEndpoint, registerServerRequest, registerServerResponse);
  if (status.IsBad() || !registerServerResponse.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (!isOnline)
  {
    status = CleanUp();
  }

  return status;
}

Status_t RegistrationAgent_t::SetupForPeriodicRegistration(uint32_t periodicRegistrationIntervalInMs)
{
  if (callbackTimerElapsed.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNothingToDo);
  }

  callbackTimerElapsed.reset(new SafeRefCount_t<TimerCallback_t>());
  if (!callbackTimerElapsed.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Status_t status = callbackTimerElapsed->Intialise(this);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

#if (UASDK_INCLUDE_TIMERS_CPP11 > 0)
  
  IntrusivePtr_t<TimerProvider_t> timerProvider_ = new SafeRefCount_t<TimerProvider_t>();
  if (!timerProvider_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = timerProvider_->Initialise(serverCyclicRateInMs);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  timerProvider = timerProvider_;

#elif (UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED > 0)
  
  IntrusivePtr_t<TimerProvider_t> timerProvider_ = new SafeRefCount_t<TimerProvider_t>();
  if (!timerProvider_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = timerProvider_->Initialise();
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  timerProvider = timerProvider_;

#endif
  
  UASDK_RETURN_UNEXPECTED_IF_NULL(timerProvider);

  IntrusivePtr_t<ICallbackTimerElapsed_t> callbackTimerElapsed_ = callbackTimerElapsed;
  status = timerProvider->CreatePeriodicTimer(periodicRegistrationIntervalInMs, callbackTimerElapsed_, timer);
  if (status.IsBad() || !timer.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return OpcUa_Good;
}

Status_t RegistrationAgent_t::CleanUp(void)
{
  if (callbackTimerElapsed.is_set())
  {
    callbackTimerElapsed.reset();
  }
  if (timerProvider.is_set())
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(timer);
    timerProvider->DeleteTimer(*timer);
  }

  UASDK_RETURN_UNEXPECTED_IF_NULL(uaClient);
  uaClient->Stop();
  uaClient->Terminate();

  serverDetails.reset();
  discoveryServerEndpoint.reset();

  return OpcUa_Good;
}

/*
 * Public Functions
 */
RegistrationAgent_t::~RegistrationAgent_t()
{
  Status_t status = CleanUp();
  UASDK_UNUSED(status);
}

Status_t RegistrationAgent_t::Initialise(const IServerConfiguration_t& serverConfiguration, const String_t& discoveryServerUrl)
{
  serverCyclicRateInMs = serverConfiguration.ServerCyclicRateInMs();
  if (!serverCyclicRateInMs)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = CreateClient(serverConfiguration);
  if (status.IsBad() || !uaClient.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  status = UpdateDiscoveryServerEndpoint(discoveryServerUrl);
  if (status.IsBad() || !discoveryServerEndpoint.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  return UpdateServerDetails(serverConfiguration);
}

Status_t RegistrationAgent_t::RegisterServer(bool isOnline, bool periodic, uint32_t periodicRegistrationIntervalInMs)
{
  if (periodic && (0 == periodicRegistrationIntervalInMs))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = RegisterToDiscoveryServer(isOnline);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (periodic)
  {
    status = SetupForPeriodicRegistration(periodicRegistrationIntervalInMs);
  }

  return status;
}

Status_t RegistrationAgent_t::RegisterServer2(bool isOnline, bool periodic, uint32_t periodicRegistrationIntervalInMs)
{
  UASDK_UNUSED(isOnline);
  UASDK_UNUSED(periodic);
  UASDK_UNUSED(periodicRegistrationIntervalInMs);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

#if (UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED > 0)
Status_t RegistrationAgent_t::Poll(void)
{
  if (timerProvider.is_set())
  {
    return timerProvider->Poll();
  }

  return OpcUa_Good;
}
#endif  //(UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED > 0)

} //namespace uasdk

#endif  //UASDK_INCLUDE_SERVER_REGISTRATION_AGENT > 0
