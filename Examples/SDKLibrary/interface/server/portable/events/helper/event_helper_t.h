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

#ifndef _EVENT_HELPER_H_
#define _EVENT_HELPER_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iserver_configuration_t.h"
#include "opcua_node_id_numeric_t.h"
#include "event_notifier_t.h"
#include "ievent_id_generator_t.h"
#include "ievent_dispatcher_t.h"
#include "iserver_configuration_t.h"
#include "opcua_event_severity_t.h"
#include "iserver_core_t.h"
#include "localizable_text_stored_t.h"
#include "default_event_properties_t.h"
#include "ua_security.h"
#include "event_type_activation_bits_defs.h"
#include "generated_data_classes.h"

#define MAX_64BIT_STRING_LENGTH 256
#define SHA1_LENGTH  20

namespace uasdk
{

/** \addtogroup grpEventsandAC
	*@{*/


	/*****************************************************************************/
	/** \brief EventHelper_t
	* This class implements utility functions required for creating and firing events
	*/
class EventHelper_t
{
public:

	/*****************************************************************************/
	/** CreateEventAndSetBaseEventProperties() API creates the event object based on the input and sets the BaseEventType properties
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[in] sourceNode
	* sourceNode identifies the Node that the Event originated from
	*
	* @param[in] sourceName
	* sourceName provides a description of the source of the Event
	*
	* @param[in] severity
	* severity is an indication of the urgency of the Event
	*
	* @param[in] localizableText
	* localizableText provides list of human-readable and localizable text description of the Event
	*
	* @param[in] sessionLocaleIds
	* The list of localeIds supported by the UA server
	*
	* @param[out] eventInstance
	* eventInstance is the created event object
	*
	* @param[in] emptySourceNode
	* This flag is to set sourceNode as NULL or empty. Default value is false
	*
	* @return status
	* status of the operation
	*/

	template<typename T>
	static Status_t CreateEventAndSetBaseEventProperties(IntrusivePtr_t<IServerConfiguration_t> configuration_,		
		IntrusivePtr_t<NodeId_t>& sourceNode,
		IntrusivePtr_t<String_t>& sourceName,
		uint16_t severity,
		IntrusivePtr_t<ILocalizableText_t> localizableText,
		IntrusivePtr_t<const ArrayUA_t<String_t> > sessionLocaleIds,
		IntrusivePtr_t<T>& eventInstance,
		bool emptySourceNode = false)
	{
		Status_t status;
		uint16_t namespaceIndex = 0;

		if (!configuration_.is_set() || !sourceName.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
		}
    
    if (!eventInstance.is_set())
    {
      eventInstance = new SafeRefCount_t<T>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(eventInstance);
    }

		status = eventInstance->Initialise();
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    uint32_t typeId = eventInstance->TypeId(namespaceIndex);

		//Severity
    IntrusivePtr_t<UInt16_t> severity_ = new SafeRefCount_t<UInt16_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity_);
    severity_->Value(severity);

		//Message
		if (!localizableText.is_set())
		{
			IntrusivePtr_t<String_t> messageLocale = new SafeRefCount_t<String_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(messageLocale);

			status = messageLocale->CopyFrom(LOCALE_DEFAULT);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

			IntrusivePtr_t<String_t> messageText = GetDefaultMessageText(typeId);
			if (!messageText.is_set())
			{
				UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
			}

			status = AddToLocalizableTextStored(*messageLocale, *messageText, localizableText);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
		}
      
    UASDK_RETURN_UNEXPECTED_IF_NULL(localizableText);

		IntrusivePtr_t<const LocalizedText_t> localizedTextTemp;
		if (!sessionLocaleIds.is_set())
		{
			localizedTextTemp = localizableText->GetLocalizedText(status);
		}
		else
		{
			localizedTextTemp = localizableText->GetLocalizedText(*sessionLocaleIds, status);
		}

    UASDK_RETURN_UNEXPECTED_IF_NULL(localizedTextTemp);

		//SourceNode
		IntrusivePtr_t<NodeId_t> sourceNode_;
		if (!emptySourceNode)
		{
			if (!sourceNode.is_set())
			{
				sourceNode_ = GetServerNodeId();
			}
			else
			{
				sourceNode_ = sourceNode;
			}
		}

		//Event Id
		IntrusivePtr_t<ByteString_t> eventId;
		status = configuration_->EventIdGenerator()->GenerateEventId(eventId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		//Event Type
		IntrusivePtr_t<NodeIdNumeric_t> eventType = new SafeRefCount_t<NodeIdNumeric_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(eventType);

		eventType->Initialise(0, typeId);

		//Time
		IntrusivePtr_t<UtcTime_t> time_ = new SafeRefCount_t<UtcTime_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(time_);

		time_->Value(UASDK_datetime());

		//Receive Time
		IntrusivePtr_t<UtcTime_t> receiveTime = new SafeRefCount_t<UtcTime_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(receiveTime);

		receiveTime->Value(UASDK_datetime());

		//Set Base Event Properties
		eventInstance->EventId() = eventId;
		eventInstance->EventType() = eventType;
		eventInstance->SourceNode() = sourceNode_;
		eventInstance->SourceName() = sourceName;
		eventInstance->Message() = new SafeRefCount_t<LocalizedText_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(eventInstance->Message());
    status = eventInstance->Message()->CopyFrom(*localizedTextTemp);
		eventInstance->Severity() = severity_;
		eventInstance->Time() = time_;
		eventInstance->ReceiveTime() = receiveTime;
		eventInstance->LocalTime() = configuration_->LocalTime();

		return status;
	}

	/*****************************************************************************/
	/** SetAuditEventProperties() API will set the audit event properties for the input event object.
	* The input object must be a subtype of AuditEvent.
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[in] auditEventInstance
	* The input auditEventObject created using CreateEventAndSetBaseEventProperties
	*
	* @param[in] actionTimeStamp
	* actionTimeStamp identifies the time the user initiated the action that resulted in the AuditEvent being generated
	*
	* @param[in] status
	* status identifies whether the requested action could be performed
	*
	* @param[in] serverId
	* serverId uniquely identifies the Server generating the Event.
	*
	* @param[in] clientAuditEntryId
	* clientAuditEntryId contains the human-readable AuditEntryId
	*
	* @param[in] clientUserId
	* The clientUserId identifies the user of the client requesting an action
	*
	* @return status
	* status of the operation
	*/

	template<typename T>
	static Status_t SetAuditEventProperties(IntrusivePtr_t<IServerConfiguration_t> configuration_,
		IntrusivePtr_t<T>& auditEventInstance,
		IntrusivePtr_t<UtcTime_t> actionTimeStamp,
		IntrusivePtr_t<Boolean_t> status,
		IntrusivePtr_t<String_t> serverId,
		IntrusivePtr_t<String_t> clientAuditEntryId,
		IntrusivePtr_t<String_t> clientUserId)
	{
		Status_t result;
		if (!auditEventInstance.is_set() || !clientAuditEntryId.is_set() || !configuration_.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
		}
    
		uint16_t namespaceIndex = 0;
		switch (auditEventInstance->TypeId(namespaceIndex))
		{
		case OpcUaId_AuditActivateSessionEventType:
		case OpcUaId_AuditCancelEventType:
		case OpcUaId_AuditCertificateDataMismatchEventType:
		case OpcUaId_AuditCertificateExpiredEventType:
		case OpcUaId_AuditCertificateInvalidEventType:
		case OpcUaId_AuditCertificateMismatchEventType:
		case OpcUaId_AuditCertificateRevokedEventType:
		case OpcUaId_AuditCertificateUntrustedEventType:
		case OpcUaId_AuditCreateSessionEventType:		
		case OpcUaId_AuditOpenSecureChannelEventType:

    case OpcUaId_AuditUpdateEventType:
		case OpcUaId_AuditUpdateMethodEventType:
		case OpcUaId_AuditUrlMismatchEventType:
		case OpcUaId_AuditWriteUpdateEventType:

    case OpcUaId_AuditConditionEventType:
    case OpcUaId_AuditConditionEnableEventType:    
    case OpcUaId_AuditConditionCommentEventType:
    case OpcUaId_AuditConditionRespondEventType:
    case OpcUaId_AuditConditionAcknowledgeEventType:
    case OpcUaId_AuditConditionConfirmEventType:
    case OpcUaId_AuditConditionShelvingEventType:

    case OpcUaId_AuditProgramTransitionEventType:
    case OpcUaId_AuditHistoryEventUpdateEventType:
    case OpcUaId_AuditHistoryValueUpdateEventType:
    case OpcUaId_AuditHistoryDeleteEventType:
    case OpcUaId_AuditHistoryRawModifyDeleteEventType:
    case OpcUaId_AuditHistoryAtTimeDeleteEventType:
    case OpcUaId_AuditHistoryEventDeleteEventType:
    case OpcUaId_AuditHistoryUpdateEventType:

    case OpcUaId_AuditNodeManagementEventType:
    case OpcUaId_AuditAddNodesEventType:
    case OpcUaId_AuditDeleteNodesEventType:
    case OpcUaId_AuditAddReferencesEventType:
    case OpcUaId_AuditDeleteReferencesEventType:    

			break;
		default:
			UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
		}

		if (!actionTimeStamp.is_set())
		{
			actionTimeStamp = new SafeRefCount_t<UtcTime_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(actionTimeStamp);

			actionTimeStamp->Value(UASDK_datetime());
		}

		if (!status.is_set())
		{
			status = new SafeRefCount_t<Boolean_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(status);

			status->Value(AUDIT_EVENT_STATUS);
		}
		if (!serverId.is_set())
		{
			serverId = new SafeRefCount_t<String_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(serverId);

			result = serverId->CopyFrom((const char*)AUDIT_EVENT_SERVER_ID);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(result.Value());
		}
		auditEventInstance->ActionTimeStamp() = actionTimeStamp;
		auditEventInstance->Status() = status;
		auditEventInstance->ServerId() = serverId;
		auditEventInstance->ClientAuditEntryId() = clientAuditEntryId;
		auditEventInstance->ClientUserId() = clientUserId;

		return OpcUa_Good;
	}

	/*****************************************************************************/
	/** CreateAuditSessionTypeEvents() API will create audit session type of events
	*
	* @param[in] typeId
	* The typeId of the event to be created. The list of typeIds are available in opcua_identifiers.h
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[in] auditEntryId
	* clientAuditEntryId contains the human-readable AuditEntryId
	*
	* @param[in] clientUserId
	* The clientUserId identifies the user of the client requesting an action
	*		
	* @param[in] sessionLocaleIds
	* The list of localeIds supported by the UA server
	*
	* @param[out] eventInstance
	* eventInstance is the created event object
	*
	* @return status
	* status of the operation
	*/

	template<typename T>
	static Status_t CreateAuditSessionTypeEvents(uint32_t typeId,
		IntrusivePtr_t<IServerConfiguration_t> configuration,
		String_t& auditEntryId,
		IntrusivePtr_t<String_t> clientUserId,
		IntrusivePtr_t<const ArrayUA_t<String_t> > sessionLocaleIds,
		IntrusivePtr_t<T>& eventInstance)
	{
		Status_t status;

		IntrusivePtr_t<NodeId_t> sourceNode;

		IntrusivePtr_t<ILocalizableText_t> message;
		IntrusivePtr_t<String_t> sourceName = GetDefaultSourceName(typeId);
		status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNode, sourceName, AUDIT_SESSION_TYPE_EVENT_SEVERITY, message, sessionLocaleIds, eventInstance, false);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		IntrusivePtr_t<String_t> clientAuditEntryId = new SafeRefCount_t<String_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(clientAuditEntryId);

		status = clientAuditEntryId->CopyFrom(auditEntryId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		IntrusivePtr_t<String_t> serverId;
		IntrusivePtr_t<Boolean_t> booleanStatus;
		IntrusivePtr_t<UtcTime_t> actionTimestamp;			

		IntrusivePtr_t<String_t> clientUserId_ = clientUserId;
		if (!clientUserId_.is_set())
		{
			clientUserId_ = GetClientUserId(typeId);
		}

		status = EventHelper_t::SetAuditEventProperties(configuration, eventInstance, actionTimestamp, booleanStatus, serverId, clientAuditEntryId, clientUserId_);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		return status;
	}

	/*****************************************************************************/
	/** CreateAuditCertificateTypeEvents() API will create audit certificate type of events
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[in] typeId
	* The typeId of the event to be created. The list of typeIds are available in opcua_identifiers.h
	*
	* @param[in] certificate
	* Input client certificate
	*
	* @param[in] sessionLocaleIds
	* The list of localeIds supported by the UA server
	*
	* @param[out] eventInstance
	* eventInstance is the created event object
	*
	* @return status
	* status of the operation
	*/

	template<typename T>
	static Status_t CreateAuditCertificateTypeEvents(IntrusivePtr_t<IServerConfiguration_t> configuration,
		uint32_t typeId,
		ByteString_t& certificate,
		IntrusivePtr_t<const ArrayUA_t<String_t> > sessionLocaleIds,
		IntrusivePtr_t<T>& eventInstance)
	{
		Status_t status;

		IntrusivePtr_t<NodeId_t> sourceNode;
		IntrusivePtr_t<UInt16_t> severity = new SafeRefCount_t<UInt16_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity);

		severity->Value(AUDIT_CERTIFICATE_TYPE_EVENT_SEVERITY);

		//Message
		IntrusivePtr_t<ILocalizableText_t> message;

		IntrusivePtr_t<String_t> sourceName = GetDefaultSourceName(typeId);
		status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNode, sourceName, severity->Value(), message, sessionLocaleIds, eventInstance, true);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		IntrusivePtr_t<ByteString_t> certificate_ = new SafeRefCount_t<ByteString_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(certificate_);

		status = certificate_->CopyFrom(certificate);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		eventInstance->Certificate() = certificate_;

		return status;
	}

	/*****************************************************************************/
	/** CreateProgressEvent() API creates the ProgressEvent instance
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[in] sourceNode
	* sourceNode identifies the Node that the Event originated from
	*
	* @param[in] sourceName
	* sourceName provides a description of the source of the Event
	*
	* @param[in] localizableTextStored
	* localizableTextStored provides list of human-readable and localizable text description of the Event
	*
	* @param[in] sessionLocaleIds
	* The list of localeIds supported by the UA server
	*
	* @param[in] context
	* context contains context information about what operation progress is reported
	*
	* @param[in] progress
	* Progress contains the percentage completed of the progress. The value shall be between 0 and 100, where 100 identifies that the operation has been finished
	*
	* @param[out] eventInstance
	* eventInstance is the created event object
	*
	* @return status
	* status of the operation
	*/

	static Status_t CreateProgressEvent(IntrusivePtr_t<IServerConfiguration_t> configuration,
		IntrusivePtr_t<NodeId_t> sourceNode,
		IntrusivePtr_t<String_t> sourceName,
		IntrusivePtr_t<ILocalizableText_t> localizableText,
		IntrusivePtr_t<const ArrayUA_t<String_t> > sessionLocaleIds,
		IntrusivePtr_t<BaseDataType_t> context,
		uint16_t progress,
		IntrusivePtr_t<ProgressEventTypeData_t>& progressEventType)
	{
		Status_t status;

		IntrusivePtr_t<UInt16_t> severity = new SafeRefCount_t<UInt16_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity);

		severity->Value(PROGRESS_EVENT_SEVERITY);

		if (!localizableText.is_set())
		{		
			IntrusivePtr_t<String_t> messageText = GetDefaultMessageText(OpcUaId_ProgressEventType);	

      String_t messageLocale;
      status = messageLocale.CopyFrom(LOCALE_DEFAULT);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = AddToLocalizableTextStored(messageLocale, *messageText, localizableText);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
		}
    
		if (progressEventType.is_set())
		{
			progressEventType.reset();
		}
		status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNode, sourceName, severity->Value(), localizableText, sessionLocaleIds, progressEventType);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		//Set ProgressEventType paramters
		IntrusivePtr_t<UInt16_t> progress_ = new SafeRefCount_t<UInt16_t>();
		if (!progress_.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		progress_->Value(progress);

		progressEventType->Context() = context;
		progressEventType->Progress() = progress_;

		return status;
	}

	/*****************************************************************************/
	/** GetDefaultSourceName() API returns the default source name for an event
	*
	* @param[in] typeId
	* The typeId of the event. The list of typeIds are available in opcua_identifiers.h
	*
	* @return IntrusivePtr_t<String_t>
	* The default source name based on the input typeId
	*/

	static IntrusivePtr_t<String_t> GetDefaultSourceName(uint32_t typeId)
	{
		Status_t status;
		IntrusivePtr_t<String_t> emptyString;
		IntrusivePtr_t<String_t> sourceName = new SafeRefCount_t<String_t>();
		if (!sourceName.is_set())
		{
			return emptyString;
		}

		switch (typeId)
		{
		case  OpcUaId_AuditCreateSessionEventType:
			status = sourceName->CopyFrom(AUDIT_CREATE_SESSION_SOURCE_NAME);
			break;
		case  OpcUaId_AuditActivateSessionEventType:
			status = sourceName->CopyFrom(AUDIT_ACTIVATE_SESSION_SOURCE_NAME);
			break;
		case  OpcUaId_AuditAddNodesEventType:
			status = sourceName->CopyFrom(AUDIT_ADD_NODES_SOURCE_NAME);
			break;
		case  OpcUaId_AuditAddReferencesEventType:
			status = sourceName->CopyFrom(AUDIT_ADD_REFERENCES_SOURCE_NAME);
			break;
		case  OpcUaId_AuditCancelEventType:
			status = sourceName->CopyFrom(AUDIT_CANCEL_SESSION_SOURCE_NAME);
			break;
		case  OpcUaId_AuditCertificateDataMismatchEventType:
		case  OpcUaId_AuditCertificateExpiredEventType:
		case  OpcUaId_AuditCertificateInvalidEventType:
		case  OpcUaId_AuditCertificateMismatchEventType:
		case  OpcUaId_AuditCertificateRevokedEventType:
		case  OpcUaId_AuditCertificateUntrustedEventType:
			status = sourceName->CopyFrom(AUDIT_CERTIFICATE_EVENTS_SOURCE_NAME);
			break;
		case  OpcUaId_AuditDeleteNodesEventType:
			status = sourceName->CopyFrom(AUDIT_DELETE_NODES_SOURCE_NAME);
			break;
		case  OpcUaId_AuditDeleteReferencesEventType:
			status = sourceName->CopyFrom(AUDIT_DELETE_REFERENCES_SOURCE_NAME);
			break;
		case  OpcUaId_AuditHistoryUpdateEventType:
			status = sourceName->CopyFrom(AUDIT_HISTORY_UPDATE_SOURCE_NAME);
			break;
		case  OpcUaId_AuditOpenSecureChannelEventType:
			status = sourceName->CopyFrom(AUDIT_OPEN_SECURE_CHANNEL_SOURCE_NAME);
			break;
		case  OpcUaId_AuditUpdateMethodEventType:
			status = sourceName->CopyFrom(AUDIT_UPDATE_METHOD_SOURCE_NAME);
			break;
		case  OpcUaId_AuditUrlMismatchEventType:
			status = sourceName->CopyFrom(AUDIT_URL_MISMATCH_SOURCE_NAME);
			break;
		case  OpcUaId_AuditWriteUpdateEventType:
			status = sourceName->CopyFrom(AUDIT_WRITE_UPDATE_SOURCE_NAME);
			break;
		case  OpcUaId_EventQueueOverflowEventType:
			status = sourceName->CopyFrom(AUDIT_EVENT_QUEUE_OVERFLOW_SOURCE_NAME);
			break;
    case  OpcUaId_CertificateExpirationAlarmType:
      status = sourceName->CopyFrom(CERTIFICATE_EXPIRATION_ALARM_SOURCE_NAME);
      break;
		default:
			status = sourceName->CopyFrom(DEFAULT_EVENT_SOURCE_NAME);
			break;
		}

		if (status.IsBad())
		{
			return emptyString;
		}

		return sourceName;
	}

	/*****************************************************************************/
	/** GetDefaultMessageText() API returns the default message text for an event
	*
	* @param[in] typeId
	* The typeId of the event. The list of typeIds are available in opcua_identifiers.h
	*
	* @return IntrusivePtr_t<String_t>
	* The default message text based on the input typeId
	*/

	static IntrusivePtr_t<String_t> GetDefaultMessageText(uint32_t typeId)
	{
		Status_t status;
		IntrusivePtr_t<String_t> emptyString;
		IntrusivePtr_t<String_t> messageText = new SafeRefCount_t<String_t>();
		if (!messageText.is_set())
		{
			return emptyString;
		}

		switch (typeId)
		{
		case  OpcUaId_AuditCancelEventType:
			status = messageText->CopyFrom(AUDIT_CANCEL_EVENT_MESSAGE);
			break;
		case  OpcUaId_AuditCreateSessionEventType:
			status = messageText->CopyFrom(AUDIT_CREATE_SESSION_MESSAGE);
			break;
		case  OpcUaId_AuditActivateSessionEventType:
			status = messageText->CopyFrom(AUDIT_ACTIVATE_SESSION_MESSAGE);
			break;
		case  OpcUaId_AuditCertificateDataMismatchEventType:
			status = messageText->CopyFrom(AUDIT_CERTIFICATE_DATA_MISMATCH_MESSAGE);
			break;
		case  OpcUaId_AuditCertificateExpiredEventType:
			status = messageText->CopyFrom(AUDIT_CERTIFICATE_EXPIRED_MESSAGE);
			break;
		case  OpcUaId_AuditCertificateInvalidEventType:
			status = messageText->CopyFrom(AUDIT_CERTIFICATE_INVALID_MESSAGE);
			break;
		case  OpcUaId_AuditCertificateMismatchEventType:
			status = messageText->CopyFrom(AUDIT_CERTIFICATE_MISMATCH_MESSAGE);
			break;
		case  OpcUaId_AuditCertificateRevokedEventType:
			status = messageText->CopyFrom(AUDIT_CERTIFICATE_REVOKED_MESSAGE);
			break;
		case  OpcUaId_AuditCertificateUntrustedEventType:
			status = messageText->CopyFrom(AUDIT_CERTIFICATE_UNTRUSTED_MESSAGE);
			break;
		case  OpcUaId_AuditHistoryUpdateEventType:
			status = messageText->CopyFrom(AUDIT_HISTORY_UPDATE_MESSAGE);
			break;
		case  OpcUaId_AuditOpenSecureChannelEventType:
			status = messageText->CopyFrom(AUDIT_OPEN_SECURE_CHANNEL_MESSAGE);
			break;
		case  OpcUaId_AuditUpdateMethodEventType:
			status = messageText->CopyFrom(AUDIT_UPDATE_METHOD_MESSAGE);
			break;
		case  OpcUaId_AuditUrlMismatchEventType:
			status = messageText->CopyFrom(AUDIT_URL_MISMATCH_MESSAGE);
			break;
		case  OpcUaId_AuditWriteUpdateEventType:
			status = messageText->CopyFrom(AUDIT_WRITE_UPDATE_MESSAGE);
			break;
		case  OpcUaId_EventQueueOverflowEventType:
			status = messageText->CopyFrom(AUDIT_EVENT_QUEUE_OVERFLOW_MESSAGE);
			break;
		case  OpcUaId_SystemEventType:
			status = messageText->CopyFrom(AUDIT_SYSTEM_EVENT_MESSAGE);
			break;
		case  OpcUaId_SystemStatusChangeEventType:
			status = messageText->CopyFrom(AUDIT_SYSTEM_STATUS_CHANGE_MESSAGE);
			break;
		case  OpcUaId_ProgressEventType:
			status = messageText->CopyFrom(AUDIT_PROGRESS_EVENT_MESSAGE);
			break;
    //Condition event related messages
    case  OpcUaId_AcknowledgeableConditionType:
      status = messageText->CopyFrom(ACKNOWLEDGE_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_AlarmConditionType:
      status = messageText->CopyFrom(ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_LimitAlarmType:
      status = messageText->CopyFrom(LIMIT_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_ExclusiveLimitAlarmType:
      status = messageText->CopyFrom(EXCLUSIVE_LIMIT_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_ExclusiveLevelAlarmType:
      status = messageText->CopyFrom(EXCLUSIVE_LEVEL_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_ExclusiveDeviationAlarmType:
      status = messageText->CopyFrom(EXCLUSIVE_MULTI_DEVIATION_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_ExclusiveRateOfChangeAlarmType:
      status = messageText->CopyFrom(EXCLUSIVE_RATE_OF_CHANGE_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_NonExclusiveLimitAlarmType:
      status = messageText->CopyFrom(NON_EXCLUSIVE_LIMIT_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_NonExclusiveLevelAlarmType:
      status = messageText->CopyFrom(NON_EXCLUSIVE_LEVEL_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_NonExclusiveDeviationAlarmType:
      status = messageText->CopyFrom(NON_EXCLUSIVE_MULTI_DEVIATION_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_NonExclusiveRateOfChangeAlarmType:
      status = messageText->CopyFrom(NON_EXCLUSIVE_RATE_OF_CHANGE_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_DiscreteAlarmType:
      status = messageText->CopyFrom(DISCRETE_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_OffNormalAlarmType:
      status = messageText->CopyFrom(OFF_NORMAL_TYPE_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_SystemOffNormalAlarmType:
      status = messageText->CopyFrom(SYSTEM_OFF_NORMAL_TYPE_ALARM_CONDITION_EVENT_MESSAGE);
      break;
    case  OpcUaId_RefreshStartEventType:
      status = messageText->CopyFrom(REFRESH_START_EVENT_TMESSAGE);
      break;
    case  OpcUaId_RefreshEndEventType:
      status = messageText->CopyFrom(REFRESH_END_EVENT_TMESSAGE);
      break;
    case  OpcUaId_RefreshRequiredEventType:
      status = messageText->CopyFrom(REFRESH_REQUIRED_EVENT_MESSAGE);
      break;
    case  OpcUaId_CertificateExpirationAlarmType:
      status = messageText->CopyFrom(CERTIFICATE_EXPIRATION_ALARM_EVENT_MESSAGE);
      break;
		default:
			status = messageText->CopyFrom(DEFAULT_EVENT_MESSAGE);
			break;
		}

		if (status.IsBad())
		{
			return emptyString;
		}

		return messageText;
	}

	/*****************************************************************************/
	/** GetClientUserId() API returns the clientUserId for AuditSession type events
	*
	* @param[in] typeId
	* The typeId of the event. The list of typeIds are available in opcua_identifiers.h
	*
	* @return IntrusivePtr_t<String_t>
	* The clientUserId based on the input typeId
	*/

	static IntrusivePtr_t<String_t> GetClientUserId(uint32_t typeId)
	{
		Status_t status;
		IntrusivePtr_t<String_t> emptyString;
		IntrusivePtr_t<String_t> clientUserId = new SafeRefCount_t<String_t>();
		if (!clientUserId.is_set())
		{
			return emptyString;
		}
		switch (typeId)
		{
		case OpcUaId_AuditUrlMismatchEventType:
			status = clientUserId->CopyFrom("System/CreateSession");
			break;
		case OpcUaId_AuditOpenSecureChannelEventType:
			status = clientUserId->CopyFrom("System/OpenSecureChannel");
			break;
		default:
			return emptyString;
		}
			
		if (status.IsBad())
		{
			return emptyString;
		}
		return clientUserId;
	}

	/*****************************************************************************/
	/** GetServerNodeId() API returns the NodeId of the Server object
	*
	* @return IntrusivePtr_t<NodeId_t>
	* The NodeId of the server object
	*/

	static IntrusivePtr_t<NodeId_t> GetServerNodeId(void)
	{
		IntrusivePtr_t<NodeIdNumeric_t> emptyNode;
		IntrusivePtr_t<NodeIdNumeric_t> serverNodeId = new SafeRefCount_t<NodeIdNumeric_t>();
		if (!serverNodeId.is_set())
		{
			return emptyNode;
		}
		serverNodeId->Initialise(0, OpcUaId_Server);

		return serverNodeId;
	}

	/*****************************************************************************/
	/** GetSecureChannelIdAsString() API returns input secureChannelId as String
	*
	* @param[in] secureChannelId
	* secureChannelId is the uint32_t which needs to be converted to String
	*
	* @return IntrusivePtr_t<String_t>
	* The secureChannelId as string
	*/

	static IntrusivePtr_t<String_t> GetSecureChannelIdAsString(uint32_t secureChannelId)
	{
		Status_t status;
		IntrusivePtr_t<String_t> emptyString;
		IntrusivePtr_t<String_t> secureChannelIdString = new SafeRefCount_t<String_t>();
		if (!secureChannelIdString.is_set())
		{
			return emptyString;
		}

		char buf[MAX_64BIT_STRING_LENGTH];
		int32_t length = UASDK_unsigned_integer_to_string(static_cast<uint64_t>(secureChannelId), 0, buf, MAX_64BIT_STRING_LENGTH);
		if (length < 0)
		{
			return emptyString;
		}

		status = secureChannelIdString->CopyFrom(buf, MAX_64BIT_STRING_LENGTH);
		if (status.IsBad())
		{
			return emptyString;
		}
		return secureChannelIdString;
	}

	/*****************************************************************************/
	/** GetCertificateThumbprint() API returns the thumbprint of the input certificate
	*
	* @param[in] certificate_
	* certificate_ is the input certificate in ByteString
	*
	* @return IntrusivePtr_t<String_t>
	* The thumbprint of the input certificate
	*/

	static IntrusivePtr_t<String_t> GetCertificateThumbprint(IntrusivePtr_t<ByteString_t> certificate_)
	{
		Status_t status;
		IntrusivePtr_t<String_t> emptyString;
		UA_Byte_string_t cert = certificate_->ToLegacy();
		uint8_t data[SHA1_LENGTH];
		UA_Byte_string_t hash = { 0, SHA1_LENGTH, data };
		hash.length = 0;

		status = UASecurity_digest(UA_DIGEST_SHA1, &cert, &hash);
		if (status.IsBad())
		{
			return emptyString;
		}
		IntrusivePtr_t<String_t> thumbPrint = new SafeRefCount_t<String_t>();
		if (!thumbPrint.is_set())
		{
			return emptyString;
		}
		status = thumbPrint->Payload().CopyFrom(hash.data, hash.length);
		if (status.IsBad())
		{
			return emptyString;
		}

		return thumbPrint;
	}

	/*****************************************************************************/
	/** AddToLocalizableTextStored() API adds the input locale and text to the localizableTextStored.
	* localizableTextStored will be used to pass the message parameter of any given event
	*
	* @param[in] locale
	* locale is the localeId of the given input text
	*
	* @param[in] text
	* text is the message text
	*
	* @param[out] localizableText
	* localizableText is the updated object which contains the input localeId and text
	*
	* @return status
	* status of the operation
	*/

  static Status_t AddToLocalizableTextStored(const String_t& locale,
    const String_t& text,
    IntrusivePtr_t<ILocalizableText_t>& localizableText)
  {    
    IntrusivePtr_t<LocalizedText_t> localizedText = new SafeRefCount_t<LocalizedText_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(localizedText);

    Status_t status = localizedText->Locale().CopyFrom(locale);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    status = localizedText->Text().CopyFrom(text);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    IntrusivePtr_t<LocalizableTextStored_t> localizableTextStored;
    localizableTextStored = new SafeRefCount_t<LocalizableTextStored_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(localizableTextStored);

    status = localizableTextStored->AddText(localizedText);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    localizableText.reset();
    localizableText = localizableTextStored;
    return status;
  }

  /*****************************************************************************/
  /** AddToLocalizableTextStored() API adds the input locale and text to the localizableTextStored.
  * localizableTextStored will be used to pass the message parameter of any given event
  *
  * @param[in] localizedText
  * input localized text to be added to the localizableText
  *
  * @param[out] localizableText
  * localizableText is the updated object which contains the input localeId and text
  *
  * @return status
  * status of the operation
  */
  static Status_t AddToLocalizableTextStored(const LocalizedText_t& localizedText,
    IntrusivePtr_t<ILocalizableText_t>& localizableText)
  {
    IntrusivePtr_t<LocalizedText_t> localizedText_ = new SafeRefCount_t<LocalizedText_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(localizedText_);
    Status_t status = localizedText_->CopyFrom(localizedText);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    IntrusivePtr_t<LocalizableTextStored_t> localizableTextStored = new SafeRefCount_t<LocalizableTextStored_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(localizableTextStored);

    status = localizableTextStored->AddText(localizedText_);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    localizableText.reset();
    localizableText = localizableTextStored;
    return status;
  }

#if (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)
  /*****************************************************************************/
  /** FireAuditConditionEvents()
  * A general method to fire the AuditCondition type of events
  *
  * @param[in] configuration
  * configuration is the instance of server configuration
  *
  * @param[in] conditionId
  * unique Id of the condition
  *
  * @param[in] conditionTypeId
  * condition type id
  *
  * @param[in] sourceName
  * Source Name of the event
  *
  * @param[in] messageLocale
  * locale information of the message
  *
  * @param[in] messageText
  * event message text in respective locale
  *
  * @param[in] methodId
  * nodeId of the method
  *
  * @param[in] eventId
  * event id
  *
  * @param[in] comment
  * comment for the event
  *
  * @param[in] selectedResponse
  * response that was selected!
  *
  * @param[in] shelvingTime
  * shelving time
  *
  * @return
  * status of the operation
  */
  static Status_t FireAuditConditionEvents(IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<NodeId_t> conditionId, uint32_t conditionTypeId, String_t& sourceName, LocalizedText_t& messageText,
    IntrusivePtr_t<NodeId_t> methodId, ByteString_t& affectedEventId, LocalizedText_t& comment, uint32_t selectedResponse = 0, double shelvingTime = 0.0)
  {
    if (!configuration.is_set() || !configuration->EventDispatcher().is_set() || !methodId.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }

    Status_t status;

    //SourceNode
    //Note: AuditUpdateMethodEventType - The SourceNode for Events of this type shall be assigned to the NodeId of the Object that the Method resides on.
    IntrusivePtr_t<NodeId_t> sourceNodeId = conditionId;

    //SourceName
    IntrusivePtr_t<String_t> sourceName_ = new SafeRefCount_t<String_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(sourceName_);
    status = sourceName_->CopyFrom(sourceName);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    //Message
    IntrusivePtr_t<ILocalizableText_t> message;
    status = EventHelper_t::AddToLocalizableTextStored(messageText, message);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    String_t clientAuditEntryId;
    status = clientAuditEntryId.CopyFrom(sourceName);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    IntrusivePtr_t<UtcTime_t> actionTimeStamp;
    IntrusivePtr_t<Boolean_t> auditStatus;
    IntrusivePtr_t<String_t> serverId;
    IntrusivePtr_t<String_t> clientUserId = new SafeRefCount_t<String_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(clientUserId);

    IntrusivePtr_t<String_t> clientAuditEntryId_ = new SafeRefCount_t<String_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(clientAuditEntryId_);

    status = clientAuditEntryId_->CopyFrom(clientAuditEntryId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    IntrusivePtr_t<ByteString_t> affectedEventId_ = new SafeRefCount_t<ByteString_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(affectedEventId_);

    status = affectedEventId_->CopyFrom(affectedEventId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    IntrusivePtr_t<LocalizedText_t> comment_ = new SafeRefCount_t<LocalizedText_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(comment_);

    status = comment_->CopyFrom(comment);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    IntrusivePtr_t<UInt32_t> selectedResponse_ = new SafeRefCount_t<UInt32_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(selectedResponse_);

    selectedResponse_->Value(selectedResponse);

    IntrusivePtr_t<Duration_t> shelvingTime_ = new SafeRefCount_t<Duration_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(shelvingTime_);

    shelvingTime_->Value(shelvingTime);

    IntrusivePtr_t<const ArrayUA_t<String_t> > localeIds;//Empty parameter is passed. The below method will take the default values.

    IntrusivePtr_t<IAttributeAccess_t> eventInstance;

    switch (conditionTypeId)
    {
    case OpcUaId_AuditConditionEnableEventType:
    {
      IntrusivePtr_t<AuditConditionEnableEventTypeData_t> auditConditionEvent;

      status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNodeId, sourceName_, AUDIT_CONDITION_TYPE_EVENT_SEVERITY, message, localeIds, auditConditionEvent, false);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = EventHelper_t::SetAuditEventProperties(configuration, auditConditionEvent, actionTimeStamp, auditStatus, serverId, clientAuditEntryId_, clientUserId);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = methodId->CopyToNodeId(auditConditionEvent->MethodId());
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      eventInstance = auditConditionEvent;
    }
    break;

    case OpcUaId_AuditConditionCommentEventType:
    {
      IntrusivePtr_t<AuditConditionCommentEventTypeData_t> auditConditionEvent;

      status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNodeId, sourceName_, AUDIT_CONDITION_TYPE_EVENT_SEVERITY, message, localeIds, auditConditionEvent, false);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = EventHelper_t::SetAuditEventProperties(configuration, auditConditionEvent, actionTimeStamp, auditStatus, serverId, clientAuditEntryId_, clientUserId);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = methodId->CopyToNodeId(auditConditionEvent->MethodId());
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      auditConditionEvent->AffectedEventId() = affectedEventId_;
      auditConditionEvent->Comment() = comment_;

      eventInstance = auditConditionEvent;
    }
    break;

    case OpcUaId_AuditConditionAcknowledgeEventType:
    {
      IntrusivePtr_t<AuditConditionAcknowledgeEventTypeData_t> auditConditionEvent;

      status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNodeId, sourceName_, AUDIT_CONDITION_TYPE_EVENT_SEVERITY, message, localeIds, auditConditionEvent, false);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = EventHelper_t::SetAuditEventProperties(configuration, auditConditionEvent, actionTimeStamp, auditStatus, serverId, clientAuditEntryId_, clientUserId);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = methodId->CopyToNodeId(auditConditionEvent->MethodId());
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      auditConditionEvent->AffectedEventId() = affectedEventId_;
      auditConditionEvent->Comment() = comment_;

      eventInstance = auditConditionEvent;
    }
    break;

    case OpcUaId_AuditConditionConfirmEventType:
    {
      IntrusivePtr_t<AuditConditionConfirmEventTypeData_t> auditConditionEvent;

      status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNodeId, sourceName_, AUDIT_CONDITION_TYPE_EVENT_SEVERITY, message, localeIds, auditConditionEvent, false);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = EventHelper_t::SetAuditEventProperties(configuration, auditConditionEvent, actionTimeStamp, auditStatus, serverId, clientAuditEntryId_, clientUserId);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = methodId->CopyToNodeId(auditConditionEvent->MethodId());
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      auditConditionEvent->AffectedEventId() = affectedEventId_;
      auditConditionEvent->Comment() = comment_;

      eventInstance = auditConditionEvent;
    }
    break;

    case OpcUaId_AuditConditionRespondEventType:
    {
      IntrusivePtr_t<AuditConditionRespondEventTypeData_t> auditConditionEvent;

      status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNodeId, sourceName_, AUDIT_CONDITION_TYPE_EVENT_SEVERITY, message, localeIds, auditConditionEvent, false);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = EventHelper_t::SetAuditEventProperties(configuration, auditConditionEvent, actionTimeStamp, auditStatus, serverId, clientAuditEntryId_, clientUserId);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = methodId->CopyToNodeId(auditConditionEvent->MethodId());
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      auditConditionEvent->SelectedResponse() = selectedResponse_;

      eventInstance = auditConditionEvent;
    }
    break;

    case OpcUaId_AuditConditionShelvingEventType:
    {
      IntrusivePtr_t<AuditConditionShelvingEventTypeData_t> auditConditionEvent;

      status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNodeId, sourceName_, AUDIT_CONDITION_TYPE_EVENT_SEVERITY, message, localeIds, auditConditionEvent, false);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = EventHelper_t::SetAuditEventProperties(configuration, auditConditionEvent, actionTimeStamp, auditStatus, serverId, clientAuditEntryId_, clientUserId);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      status = methodId->CopyToNodeId(auditConditionEvent->MethodId());
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

      auditConditionEvent->ShelvingTime() = shelvingTime_;

      eventInstance = auditConditionEvent;
    }
    break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
      break;
    }

    return configuration->EventDispatcher()->FireEventObject(eventInstance, sourceNodeId);
  }
#endif //(UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _EVENT_HELPER_H_
