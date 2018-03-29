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

#ifndef _DEFAULT_EVENT_PROPERTIES_H_
#define _DEFAULT_EVENT_PROPERTIES_H_

#include "opcua_event_severity_t.h"

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Default Event and Alarms Properties
*
* This header file has the list of default values for events, alarms and conditions.
*
*/

#define LOCALE_DEFAULT "en"
#define LOCALE_EN "en"
#define LOCALE_FR "fr"
#define LOCALE_GR "gr"

#define SOURCE_NAME "DefaultSourceName"

#define AUDIT_EVENT_STATUS true
#define AUDIT_EVENT_SERVER_ID "MatrikonOPCUAServer"

//Default messages for events
#define DEFAULT_EVENT_MESSAGE "Default System message. Please update the EventHelper_t for new events."

#define AUDIT_CREATE_SESSION_MESSAGE "Session created"
#define AUDIT_ACTIVATE_SESSION_MESSAGE "Session activated"
#define AUDIT_CANCEL_SESSION_MESSAGE "Session request cancelled"
#define AUDIT_CERTIFICATE_DATA_MISMATCH_MESSAGE "Certificate data mismatch"
#define AUDIT_CERTIFICATE_EXPIRED_MESSAGE "Certificate expired"
#define AUDIT_CERTIFICATE_INVALID_MESSAGE "Certificate invalid"
#define AUDIT_CERTIFICATE_MISMATCH_MESSAGE "Certificate mismatch"
#define AUDIT_CERTIFICATE_REVOKED_MESSAGE "Certificate revoked"
#define AUDIT_CERTIFICATE_UNTRUSTED_MESSAGE "Certificate Untrusted"
#define AUDIT_HISTORY_UPDATE_MESSAGE "History update completed"
#define AUDIT_OPEN_SECURE_CHANNEL_MESSAGE "OpenSecureChannel called"
#define AUDIT_UPDATE_METHOD_MESSAGE "Update method called"
#define AUDIT_URL_MISMATCH_MESSAGE "Session Url mismatch"
#define AUDIT_WRITE_UPDATE_MESSAGE "Write operation completed"
#define AUDIT_EVENT_QUEUE_OVERFLOW_MESSAGE "Events lost due to queue overflow"
#define AUDIT_SYSTEM_STATUS_CHANGE_MESSAGE "System status changed"
#define AUDIT_SYSTEM_EVENT_MESSAGE "System event occured"
#define AUDIT_PROGRESS_EVENT_MESSAGE "Progress event occured"
#define AUDIT_CANCEL_EVENT_MESSAGE "Cancel event occured"

//Default messages for conditions
#define ENABLE_METHOD_MESSAGE "Enable method called"
#define DISABLE_METHOD_MESSAGE "Disable method called"
#define ADD_COMMENT_METHOD_MESSAGE "AddComment method called"
#define ACKNOWLEDGE_METHOD_MESSAGE "Acknowledge method called"
#define CONFIRM_METHOD_MESSAGE "Confirm method called"

#define REFRESH_START_EVENT_TMESSAGE "Refresh start event"
#define REFRESH_END_EVENT_TMESSAGE "Refresh end event"
#define REFRESH_REQUIRED_EVENT_MESSAGE "Refresh is required"

#define ACKNOWLEDGE_CONDITION_EVENT_MESSAGE "Acknowledgeable condition event occurred"
#define ALARM_CONDITION_EVENT_MESSAGE "Alarm condition event occurred"

#define LIMIT_ALARM_CONDITION_EVENT_MESSAGE "Limit alarm condition event occurred"
#define DISCRETE_ALARM_CONDITION_EVENT_MESSAGE "Discrete alarm condition event occurred"
#define OFF_NORMAL_TYPE_ALARM_CONDITION_EVENT_MESSAGE "Off normal type alarm condition event occurred"
#define SYSTEM_OFF_NORMAL_TYPE_ALARM_CONDITION_EVENT_MESSAGE "System Off normal type alarm condition event occurred"
#define DISCRETE_ALARM_CONDITION_EVENT_MESSAGE "Discrete alarm condition event occurred"
#define EXCLUSIVE_LIMIT_ALARM_CONDITION_EVENT_MESSAGE "Exclusive limit alarm condition event occurred"
#define EXCLUSIVE_LEVEL_ALARM_CONDITION_EVENT_MESSAGE "Exclusive level alarm condition event occurred"
#define EXCLUSIVE_MULTI_DEVIATION_ALARM_CONDITION_EVENT_MESSAGE "Exclusive multi deviation alarm condition event occurred"
#define EXCLUSIVE_RATE_OF_CHANGE_ALARM_CONDITION_EVENT_MESSAGE "Exclusive rate of change alarm condition event occurred"
#define NON_EXCLUSIVE_LIMIT_ALARM_CONDITION_EVENT_MESSAGE "Non Exclusive limit alarm condition event occurred"
#define NON_EXCLUSIVE_LEVEL_ALARM_CONDITION_EVENT_MESSAGE "Non Exclusive level alarm condition event occurred"
#define NON_EXCLUSIVE_MULTI_DEVIATION_ALARM_CONDITION_EVENT_MESSAGE "Non Exclusive multi deviation alarm condition event occurred"
#define NON_EXCLUSIVE_RATE_OF_CHANGE_ALARM_CONDITION_EVENT_MESSAGE "Non Exclusive rate of change alarm condition event occurred"

#define CERTIFICATE_EXPIRATION_ALARM_EVENT_MESSAGE "Certificate expiration alarm"


//Default Source Names
#define DEFAULT_EVENT_SOURCE_NAME "Default Source Name.  Please update the EventHelper_t for new events."

#define AUDIT_CREATE_SESSION_SOURCE_NAME "Session/CreateSession"
#define AUDIT_ACTIVATE_SESSION_SOURCE_NAME "Session/ActivateSession"
#define AUDIT_CANCEL_SESSION_SOURCE_NAME "Session/Cancel"
#define AUDIT_CERTIFICATE_EVENTS_SOURCE_NAME "Security/Certificate"
#define AUDIT_ADD_NODES_SOURCE_NAME "NodeManagement/AddNodes"
#define AUDIT_ADD_REFERENCES_SOURCE_NAME "NodeManagement/DeleteNodes"
#define AUDIT_DELETE_NODES_SOURCE_NAME "NodeManagement/AddReferences"
#define AUDIT_DELETE_REFERENCES_SOURCE_NAME "NodeManagement/DeleteReferences"
#define AUDIT_HISTORY_UPDATE_SOURCE_NAME "Attribute/HistoryUpdate"
#define AUDIT_OPEN_SECURE_CHANNEL_SOURCE_NAME "SecureChannel/OpenSecureChannel"
#define AUDIT_UPDATE_METHOD_SOURCE_NAME "Attribute/Call"
#define AUDIT_URL_MISMATCH_SOURCE_NAME "Session/CreateSession"
#define AUDIT_WRITE_UPDATE_SOURCE_NAME "Attribute/Write"
#define AUDIT_EVENT_QUEUE_OVERFLOW_SOURCE_NAME "Internal/EventQueueOverflow"

#define CERTIFICATE_EXPIRATION_ALARM_SOURCE_NAME "Server"

#define CONDITION_REFRESH_SOURCE_NAME "ConditionRefresh"
#define CONDITION_REFRESH2_SOURCE_NAME "ConditionRefresh2"
#define REFRESH_REQUIRED_SOURCE_NAME "RefreshRequired"

//Default ConditionId, ConditionName for CertificateExpirationAlarm
#define CERTIFICATE_EXPIRATION_ALARM_CONDITION_NODE_ID "Server/CertificateExpirationAlarmCondition"
#define CERTIFICATE_EXPIRATION_ALARM_CONDITION_NAME "CertificateExpirationAlarmCondition"

//Default Severity for Events and Conditions
#define SYSTEM_STATUS_CHANGE_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define DEVICE_FAILURE_CHANGE_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define AUDIT_SESSION_TYPE_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define AUDIT_OPEN_SECURE_CHANNEL_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define AUDIT_CERTIFICATE_TYPE_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_MEDIUM_LOW
#define AUDIT_WRITE_UPDATE_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define AUDIT_UPDATE_METHOD_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define EVENT_QUEUE_OVERFLOW_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_HIGH
#define PROGRESS_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW

#define AUDIT_CONDITION_TYPE_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW

#define REFRESH_START_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define REFRESH_END_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW
#define REFRESH_REQUIRED_EVENT_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW

#define CERTIFICATE_EXPIRATION_ALARM_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_HIGH
#define CERTIFICATE_EXPIRATION_ALARM_INACTIVE_SEVERITY EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW

/** @} */

#endif // _DEFAULT_EVENT_PROPERTIES_H_
