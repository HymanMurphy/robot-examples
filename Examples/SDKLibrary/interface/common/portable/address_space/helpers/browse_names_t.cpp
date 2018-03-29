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

#include "browse_names_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "utilities.h"

namespace uasdk
{

#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)
  /*
  * DA helpers Browse Names
  */
  const char* BROWSE_NAME_DEFINITION = "Definition";
  const char* BROWSE_NAME_VALUE_PRECISION = "ValuePrecision";
  const char* BROWSE_NAME_ENUM_STRINGS = "EnumStrings";
  const char* BROWSE_NAME_ENUM_VALUES = "EnumValues";
  const char* BROWSE_NAME_VALUE_AS_TEXT = "ValueAsText";

  const char* BROWSE_NAME_EU_RANGE = "EURange";
  const char* BROWSE_NAME_INSTRUMENT_RANGE = "InstrumentRange";
  const char* BROWSE_NAME_ENGINEERING_UNITS = "EngineeringUnits";

  const char* BROWSE_NAME_TITLE = "Title";
  const char* BROWSE_NAME_AXIS_SCALE_TYPE = "AxisScaleType";

  const char* BROWSE_NAME_X_AXIS_DEFINATION = "XAxisDefination";
  const char* BROWSE_NAME_Y_AXIS_DEFINATION = "YAxisDefination";
  const char* BROWSE_NAME_Z_AXIS_DEFINATION = "ZAxisDefination";

  const char* BROWSE_NAME_AXIS_DEFINATION = "AxisDefination";

  const char* BROWSE_NAME_SIZE = "Size";
  const char* BROWSE_NAME_WRITABLE = "Writable";
  const char* BROWSE_NAME_USER_WRITABLE = "UserWritable";
  const char* BROWSE_NAME_OPEN_COUNT = "OpenCount";

#endif  //(UASDK_USE_DATA_ACCESS_HELPERS > 0)

#if ((UASDK_USE_DATA_ACCESS_HELPERS > 0) || (UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES > 0))

  const char* BROWSE_NAME_TRUESTATE = "TrueState";
  const char* BROWSE_NAME_FALSESTATE = "FalseState";

  const char* BROWSE_NAME_INPUT_ARGUMENTS = "InputArguments";
  const char* BROWSE_NAME_OUTPUT_ARGUMENTS = "OutputArguments";

#endif //UASDK_USE_DATA_ACCESS_HELPERS ((UASDK_USE_DATA_ACCESS_HELPERS > 0) || (UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES > 0))

#if (UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES > 0)

  //Subscription Diagnostics
  const char* BROWSE_NAME_SESSION_ID = "SessionId";
  const char* BROWSE_NAME_SUBSCRIPTION_ID = "SubscriptionId";
  const char* BROWSE_NAME_PRIORITY = "Priority";
  const char* BROWSE_NAME_PUBLISHING_INTERVAL = "PublishingInterval";
  const char* BROWSE_NAME_MAX_KEEPALIVE_COUNT = "MaxKeepAliveCount";
  const char* BROWSE_NAME_MAX_LIFETIME_COUNT = "MaxLifetimeCount";
  const char* BROWSE_NAME_MAX_NOTIFICATIONS_PER_PUBLISH = "MaxNotificationsPerPublish";
  const char* BROWSE_NAME_PUBLISHING_ENABLED = "PublishingEnabled";
  const char* BROWSE_NAME_MODIFY_COUNT = "ModifyCount";
  const char* BROWSE_NAME_ENABLE_COUNt = "EnableCount";
  const char* BROWSE_NAME_DISABLECOUNT = "DisableCount";
  const char* BROWSE_NAME_REPUBLISH_REQUEST_COUNT = "RepublishRequestCount";
  const char* BROWSE_NAME_REPUBLISH_MESSAGEREQUEST_COUNT = "RepublishMessageRequestCount";
  const char* BROWSE_NAME_REPUBLISH_MESSAGE_COUNT = "RepublishMessageCount";
  const char* BROWSE_NAME_TRANSFER_REQUEST_COUNT = "TransferRequestCount";
  const char* BROWSE_NAME_TRANSFERRED_TO_ALTCLIENT_COUNT = "TransferredToAltClientCount";
  const char* BROWSE_NAME_TRANSFERRED_TO_SAMECLIENT_COUNT = "TransferredToSameClientCount";
  const char* BROWSE_NAME_PUBLISH_REQUEST_COUNT = "PublishRequestCount";
  const char* BROWSE_NAME_DATACHANGE_NOTIFICATIONS_COUNT = "DataChangeNotificationsCount";
  const char* BROWSE_NAME_EVENT_NOTIFICATIONS_COUNT = "EventNotificationsCount";
  const char* BROWSE_NAME_NOTIFICATIONS_COUNT = "NotificationsCount";
  const char* BROWSE_NAME_LATEPUBLISH_REQUEST_COUNT = "LatePublishRequestCount";
  const char* BROWSE_NAME_CURRENT_KEEPALIVE_COUNT = "CurrentKeepAliveCount";
  const char* BROWSE_NAME_CURRENT_LIFETIME_COUNT = "CurrentLifetimeCount";
  const char* BROWSE_NAME_UNACKNOWLEDGED_MESSAGE_COUNT = "UnacknowledgedMessageCount";
  const char* BROWSE_NAME_DISCARDED_MESSAGE_COUNT = "DiscardedMessageCount";
  const char* BROWSE_NAME_MONITORED_ITEM_COUNT = "MonitoredItemCount";
  const char* BROWSE_NAME_DISABLED_MONITOREDITEM_COUNT = "DisabledMonitoredItemCount";
  const char* BROWSE_NAME_MONITORING_QUEUEOVERFLOW_COUNT = "MonitoringQueueOverflowCount";
  const char* BROWSE_NAME_NEXT_SEQUENCE_NUMBER = "NextSequenceNumber";
  const char* BROWSE_NAME_NEXT_EVENT_QUEUEOVERFLOW_COUNT = "EventQueueOverflowCount";

  //Session Diagnostics
  const char* BROWSE_NAME_SESSION_NAME = "SessionName";
  const char* BROWSE_NAME_CLIENT_DESRIPTION = "ClientDesription";
  const char* BROWSE_NAME_SERVER_URI = "ServerUri";
  const char* BROWSE_NAME_ENDPOINT_URL = "EndpointUrl";
  const char* BROWSE_NAME_LOCALE_IDS = "LocaleIds";
  const char* BROWSE_NAME_ACTUAL_SESSION_TIMEOUT = "ActualSessionTimeout";
  const char* BROWSE_NAME_MAX_RESPONSE_MESSAGE_SIZE = "MaxResponseMessageSize";
  const char* BROWSE_NAME_CLIENT_CONNECTION_TIME = "ClientConnectionTime";
  const char* BROWSE_NAME_CLIENT_LAST_CONTACT_TIME = "ClientLastContactTime";
  const char* BROWSE_NAME_CURRENT_SUBSCRIPTIONS_COUNT = "CurrentSubscriptionsCount";
  const char* BROWSE_NAME_CURRENT_MONITORED_ITEMS_COUNT = "CurrentMonitoredItemsCount";
  const char* BROWSE_NAME_CURRENT_PUBLISH_REQUESTS_IN_QUEUE = "CurrentPublishRequestsInQueue";
  //const char* BROWSE_NAME_CURRENT_PUBLISH_TIME_EXPIRATON            = "CurrentPublishTimerExpirations";//TODO
  const char* BROWSE_NAME_TOTAL_REQUESTS_COUNT = "TotalRequestsCount";
  const char* BROWSE_NAME_UNAUTHORIZED_REQUESTS_COUNT = "UnauthorizedRequestsCount";
  const char* BROWSE_NAME_READ_COUNT = "ReadCount";
  const char* BROWSE_NAME_HISTORY_READ_COUNT = "HistoryReadCount";
  const char* BROWSE_NAME_WRITE_COUNT = "WriteCount";
  const char* BROWSE_NAME_HISTORY_UPDATE_COUNT = "HistoryUpdateCount";
  const char* BROWSE_NAME_CALL_COUNT = "CallCount";
  const char* BROWSE_NAME_CREATE_MONITORED_ITEMS_COUNT = "CreateMonitoredItemsCount";
  const char* BROWSE_NAME_MODIFY_MONITORED_ITEMS_COUNT = "ModifyMonitoredItemsCount";
  const char* BROWSE_NAME_SET_MONITORING_MODE_COUNT = "SetMonitoringModeCount";
  const char* BROWSE_NAME_SET_TRIGGERING_COUNT = "SetTriggeringCount";
  const char* BROWSE_NAME_DELETE_MONITORED_ITEMS_COUNT = "DeleteMonitoredItemsCount";
  const char* BROWSE_NAME_CREATE_SUBSCRIPTION_COUNT = "CreateSubscriptionCount";
  const char* BROWSE_NAME_MODIFY_SUBSCRIPTION_COUNT = "ModifySubscriptionCount";
  const char* BROWSE_NAME_SET_PUBLISHING_MODE_COUNT = "SetPublishingModeCount";
  const char* BROWSE_NAME_PUBLISH_COUNT = "PublishCount";
  const char* BROWSE_NAME_REPUBLISH_COUNT = "RepublishCount";
  const char* BROWSE_NAME_TRANSFER_SUBSCRIPTIONS_COUNT = "TransferSubscriptionsCount";
  const char* BROWSE_NAME_DELETE_SUBSCRIPTIONS_COUNT = "DeleteSubscriptionsCount";
  const char* BROWSE_NAME_ADD_NODES_COUNT = "AddNodesCount";
  const char* BROWSE_NAME_ADD_REFERENCES_COUNT = "AddReferencesCount";
  const char* BROWSE_NAME_DELETE_NODES_COUNT = "DeleteNodesCount";
  const char* BROWSE_NAME_DELETE_REFERENCES_COUNT = "DeleteReferencesCount";
  const char* BROWSE_NAME_BROWSE_COUNT = "BrowseCount";
  const char* BROWSE_NAME_BROWSE_NEXT_COUNT = "BrowseNextCount";
  const char* BROWSE_NAME_TRANSLATE_BROWSE_PATHS_TO_NODE_IDS_COUNT = "TranslateBrowsePathsToNodeIdsCount";
  const char* BROWSE_NAME_QUERY_FIRST_COUNT = "QueryFirstCount";
  const char* BROWSE_NAME_QUERY_NEXT_COUNT = "QueryNextCount";
  const char* BROWSE_NAME_REGISTER_NODES_COUNT = "RegisterNodesCount";
  const char* BROWSE_NAME_UNREGISTER_NODES_COUNT = "UnregisterNodesCount";

  //Session Security Diagnostics
  const char* BROWSE_NAME_CLIENT_USER_ID_OF_SESSION = "ClientUserIdOfSession";
  const char* BROWSE_NAME_CLIENT_USER_ID_HISTORY = "ClientUserIdHistory";
  const char* BROWSE_NAME_AUTHENTICATION_MECHANISM = "AuthenticationMechanism";
  const char* BROWSE_NAME_ENCODING = "Encoding";
  const char* BROWSE_NAME_TRANSPORT_PROTOCOL = "TransportProtocol";
  const char* BROWSE_NAME_SECURITY_MODE = "SecurityMode";
  const char* BROWSE_NAME_SECURITY_POLICY_URI = "SecurityPolicyUri";
  const char* BROWSE_NAME_CLIENT_CERTIFICATE = "ClientCertificate";

  //Events, Alarms and Conditions
  const char* BROWSE_NAME_ID = "Id";
  const char* BROWSE_NAME_NAME = "Name";
  const char* BROWSE_NAME_NUMBER = "Number";
  const char* BROWSE_NAME_EFFECTIVE_DISPLAY_NAME = "EffectiveDisplayName";

  const char* BROWSE_NAME_TRANSITION_TIME = "TransitionTime";
  const char* BROWSE_NAME_EFFECTIVE_TRANSITION_TIME = "EffectiveTransitionTime";

  const char* BROWSE_NAME_SOURCE_TIMESTAMP = "SourceTimestamp";

  const char* BROWSE_NAME_CONDITION_CLASS_ID = "ConditionClassId";
  const char* BROWSE_NAME_CONDITION_CLASS_NAME = "ConditionClassName";
  const char* BROWSE_NAME_CONDITION_NAME = "ConditionName";
  const char* BROWSE_NAME_BRANCH_ID = "BranchId";
  const char* BROWSE_NAME_RETAIN = "Retain";
  const char* BROWSE_NAME_ENABLED_STATE = "EnabledState";
  const char* BROWSE_NAME_QUALITY = "Quality";
  const char* BROWSE_NAME_LAST_SEVERITY = "LastSeverity";
  const char* BROWSE_NAME_COMMENT = "Comment";
  const char* BROWSE_NAME_CLIENT_USER_ID = "ClientUserId";
  const char* BROWSE_NAME_DISABLE = "Disable";
  const char* BROWSE_NAME_ENABLE = "Enable";
  const char* BROWSE_NAME_ADD_COMMENT = "AddComment";
  const char* BROWSE_NAME_CONDITION_REFRESH = "ConditionRefresh";
  const char* BROWSE_NAME_CONDITION_REFRESH2 = "ConditionRefresh2";

  const char* BROWSE_NAME_ACKED_STATE = "AckedState";
  const char* BROWSE_NAME_CONFIRMED_STATE = "ConfirmedState";
  const char* BROWSE_NAME_ACKNOWLEDGE = "Acknowledge";
  const char* BROWSE_NAME_CONFIRM = "Confirm";

  const char* BROWSE_NAME_ACTIVE_STATE = "ActiveState";
  const char* BROWSE_NAME_INPUT_NODE = "InputNode";
  const char* BROWSE_NAME_SUPPRESSED_STATE = "SuppressedState";
  const char* BROWSE_NAME_SUPPRESSED_OR_SHELVED = "SuppressedOrShelved";
  const char* BROWSE_NAME_MAX_TIME_SHELVED = "MaxTimeShelved";

  const char* BROWSE_NAME_SHELVING_TIME = "ShelvingTime";
  const char* BROWSE_NAME_SHELVING_STATE_UNSHELVE = "Unshelve";
  const char* BROWSE_NAME_SHELVING_STATE_ONE_SHOT_SHELVE = "OneShotShelve";
  const char* BROWSE_NAME_SHELVING_STATE_TIMED_SHELVE = "TimedShelve";

  const char* BROWSE_NAME_EVENT_ID = "EventId";
  const char* BROWSE_NAME_MONITORED_ITEM_ID = "MonitoredItemId";

#endif  //(UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES > 0)

  Status_t BrowseNames_t::ConvertToCharPtr(IntrusivePtr_t<const QualifiedName_t>& browseName, ScopedPtr_t< Array_t<char> >& result)
  {
    if (!browseName.is_set())
    {
      return 0;
    }

    String_t name;
    Status_t status = name.CopyFrom(browseName->Name());
    if (status.IsBad())
    {
      return 0;
    }

    return name.ToString(result);
  }

  uint32_t BrowseNames_t::GetIndex(BrowseNames_t::Data_t* source, const uint32_t count, const char* data)
  {
    int32_t length = Utilities_t::Strnlen(data, INT32_MAX);
    if (!length)
    {
      return 0;
    }

    for (uint32_t i = 1; i < count; i++)
    {
      int32_t sourceLength = Utilities_t::Strnlen(reinterpret_cast<const char*>(source[i].name), INT32_MAX);
      if (!sourceLength)
      {
        return 0;
      }

      if ((sourceLength == length) && (UASDK_memcmp(source[i].name, data, length) == 0))
      {
        return source[i].index;
      }
    }

    return 0;
  }

  const char* BrowseNames_t::GetName(BrowseNames_t::Data_t* source, const uint32_t count, const uint32_t index)
  {
    uint32_t i = 1;
    for (i = 1; i < count; i++)
    {
      if (source[i].index == index)
      {
        return source[i].name;
      }
    }

    return 0;
  }

} //namespace uasdk

#endif //UASDK_USE_HELPERS
