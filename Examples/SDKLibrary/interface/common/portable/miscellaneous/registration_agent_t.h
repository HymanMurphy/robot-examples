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

#ifndef _REGISTRATION_AGENT_T_
#define _REGISTRATION_AGENT_T_

#include "uasdk_default_build_config.h"

#if (UASDK_INCLUDE_SERVER_REGISTRATION_AGENT > 0)

#include "allocatable_t.h"
#include "iref_count_t.h"
#include "iserver_configuration_t.h"
#include "uaclient_t.h"
#include "opcua_registered_server_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
*@{*/

/*****************************************************************************/
/** \brief Server Registration Agent
*
* A class used to register the server to Discovery server
*
*/

class RegistrationAgent_t : public Allocatable_t, public IRefCount_t
{
private:
  
  class TimerCallback_t : public ICallbackTimerElapsed_t, public Allocatable_t
  {
  private:
    IntrusivePtr_t<RegistrationAgent_t> registrationAgent;

  public:
    virtual ~TimerCallback_t() {};

    /*****************************************************************************/
    /** Initialise timer callback
    *
    * @param[in] registrationAgent_
    * registration agent
    *
    * @return
    * status of the operation
    */
    Status_t Intialise(const IntrusivePtr_t<RegistrationAgent_t>& registrationAgent_);

    /*****************************************************************************/
    /** Timer elapsed
    * this function will be called once the timer is elapsed
    * If the timer elapsed, Server needs to be registered.
    *
    * @return
    * status of the operation
    */
    virtual Status_t TimerElapsed(void);
  };

  uint32_t serverCyclicRateInMs;
  IntrusivePtr_t<UAClient_t> uaClient;
  IntrusivePtr_t<RegisteredServer_t> serverDetails;
  IntrusivePtr_t<const EndpointDescription_t> discoveryServerEndpoint;

  IntrusivePtr_t<TimerCallback_t> callbackTimerElapsed;
  IntrusivePtr_t<ITimer_t> timer;
  IntrusivePtr_t<ITimerProvider_t> timerProvider;

  /*****************************************************************************/
  /** Create client
  *
  * @param[in] serverConfiguration
  * server configuration
  *
  * @return
  * status of the operation
  */
  Status_t CreateClient(const IServerConfiguration_t& serverConfiguration);

  /*****************************************************************************/
  /** Update Discovery server endpoint
  *
  * @param[in] serverConfiguration
  * server configuration
  *
  * @return
  * status of the operation
  */
  Status_t UpdateDiscoveryServerEndpoint(const String_t& discoveryServerUrl);

  /*****************************************************************************/
  /** Get Server Url
  *
  * @param[in] serverConfiguration
  * server configuration
  *
  * @param[our] result
  * server url information using hostname or ip addresses
  *
  * @return
  * status of the operation
  */
  Status_t GetServerUrl(const IServerConfiguration_t& serverConfiguration, String_t& result);

  /*****************************************************************************/
  /** Update Server Details which is needed for server registration
  *
  * @param[in] serverConfiguration
  * server configuration
  *
  * @return
  * status of the operation
  */
  Status_t UpdateServerDetails(const IServerConfiguration_t& serverConfiguration);

  /*****************************************************************************/
  /** Register server to Discovery Server
  *
  * @param[in] isOnline
  * flag to indicate whether server is online or offline
  *
  * @return
  * status of the operation
  */
  Status_t RegisterToDiscoveryServer(bool isOnline);

  /*****************************************************************************/
  /** Setup for Periodic registration of server to Local discovery server
  *
  * @param[in] periodicRegistrationIntervalInMs
  * rate at which periodically registering server
  *
  * @return
  * status of the operation
  */
  Status_t SetupForPeriodicRegistration(uint32_t periodicRegistrationIntervalInMs);

  /*****************************************************************************/
  /** CleanUp the registration agent
  * When the Registering to discovery server is called, with server offline,
  * the used parameter needs to be deleted.
  *
  * @return
  * status of the operation
  */
  Status_t CleanUp(void);

public:
  RegistrationAgent_t() {}
  ~RegistrationAgent_t();

  /*****************************************************************************/
  /** Initialise the registration agent
  *
  * @param[in] serverConfiguration
  * Server configuration
  *
  * @param[in] discoveryServerUrl
  * discovery server Url
  *
  * @return
  * status of the operation
  */
  Status_t Initialise(const IServerConfiguration_t& serverConfiguration, const String_t& discoveryServerUrl);

  /*****************************************************************************/
  /** RegisterServer implements registering the server to Discovery Server on local network or localhost
  *
  * @param[in] isOnline
  * flag to indicate whether server is online or offline
  * set "true" if the server is online, "false" otherwise
  *
  * @param[in] periodic
  * Set to "true" for periodic registration
  *
  * @param[in] periodicRegistrationIntervalInMs
  * rate at which periodically registering server
  *
  * @return
  * status of the operation
  */
  Status_t RegisterServer(bool isOnline, bool periodic, uint32_t periodicRegistrationIntervalInMs);

  /*****************************************************************************/
  /** RegisterServer2 implements registering the server to Discovery Server on Netowrk
  *
  * @param[in] isOnline
  * flag to indicate whether server is online or offline
  * set "true" if the server is online, "false" otherwise
  *
  * @param[in] periodic
  * Set to "true" for periodic registration
  *
  * @param[in] periodicRegistrationIntervalInMs
  * rate at which periodically registering server
  *
  * @return
  * status of the operation
  */
  Status_t RegisterServer2(bool isOnline, bool periodic, uint32_t periodicRegistrationIntervalInMs);

#if (UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED > 0)
  /*****************************************************************************/
  /** Polling for periodic registration
  *
  * In Single threaded platform, application layer has to poll to check
  * whether timer ha expired re registration.
  *
  * @return
  * status of the operation
  */
  Status_t Poll(void);
#endif  //(UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED > 0)
};

/** @} */

} //namespace uasdk

#endif  //UASDK_INCLUDE_SERVER_REGISTRATION_AGENT

#endif  //_REGISTRATION_AGENT_T_
