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

#ifndef BROWSE_NAMES_T_H_
#define BROWSE_NAMES_T_H_

#include "uasdk_includes.h"
#include "opcua_qualified_name_t.h"

#if (UASDK_USE_HELPERS > 0)

namespace uasdk
{
  extern const char* BROWSE_NAME_DEFINITION;
  extern const char* BROWSE_NAME_VALUE_PRECISION;

  extern const char* BROWSE_NAME_TRUESTATE;
  extern const char* BROWSE_NAME_FALSESTATE;

  extern const char* BROWSE_NAME_ENUM_STRINGS;

  extern const char* BROWSE_NAME_ENUM_VALUES;
  extern const char* BROWSE_NAME_VALUE_AS_TEXT;

  extern const char* BROWSE_NAME_EU_RANGE;
  extern const char* BROWSE_NAME_INSTRUMENT_RANGE;
  extern const char* BROWSE_NAME_ENGINEERING_UNITS;

  extern const char* BROWSE_NAME_TITLE;
  extern const char* BROWSE_NAME_AXIS_SCALE_TYPE;

  extern const char* BROWSE_NAME_X_AXIS_DEFINATION;
  extern const char* BROWSE_NAME_Y_AXIS_DEFINATION;
  extern const char* BROWSE_NAME_Z_AXIS_DEFINATION;

  extern const char* BROWSE_NAME_AXIS_DEFINATION;

  extern const char* BROWSE_NAME_SIZE;
  extern const char* BROWSE_NAME_WRITABLE;
  extern const char* BROWSE_NAME_USER_WRITABLE;
  extern const char* BROWSE_NAME_OPEN_COUNT;
  extern const char* BROWSE_NAME_INPUT_ARGUMENTS;
  extern const char* BROWSE_NAME_OUTPUT_ARGUMENTS;

  extern const char* BROWSE_NAME_ID;
  extern const char* BROWSE_NAME_NAME;
  extern const char* BROWSE_NAME_NUMBER;
  extern const char* BROWSE_NAME_EFFECTIVE_DISPLAY_NAME;

  extern const char* BROWSE_NAME_TRANSITION_TIME;
  extern const char* BROWSE_NAME_EFFECTIVE_TRANSITION_TIME;

  extern const char* BROWSE_NAME_SOURCE_TIMESTAMP;

  extern const char* BROWSE_NAME_CONDITION_CLASS_ID;
  extern const char* BROWSE_NAME_CONDITION_CLASS_NAME;
  extern const char* BROWSE_NAME_CONDITION_NAME;
  extern const char* BROWSE_NAME_BRANCH_ID;
  extern const char* BROWSE_NAME_RETAIN;
  extern const char* BROWSE_NAME_ENABLED_STATE;
  extern const char* BROWSE_NAME_QUALITY;
  extern const char* BROWSE_NAME_LAST_SEVERITY;
  extern const char* BROWSE_NAME_COMMENT;
  extern const char* BROWSE_NAME_CLIENT_USER_ID;
  extern const char* BROWSE_NAME_DISABLE;
  extern const char* BROWSE_NAME_ENABLE;
  extern const char* BROWSE_NAME_ADD_COMMENT;
  extern const char* BROWSE_NAME_CONDITION_REFRESH;
  extern const char* BROWSE_NAME_CONDITION_REFRESH2;

  extern const char* BROWSE_NAME_ACKED_STATE;
  extern const char* BROWSE_NAME_CONFIRMED_STATE;
  extern const char* BROWSE_NAME_ACKNOWLEDGE;
  extern const char* BROWSE_NAME_CONFIRM;

  extern const char* BROWSE_NAME_ACTIVE_STATE;
  extern const char* BROWSE_NAME_INPUT_NODE;
  extern const char* BROWSE_NAME_SUPPRESSED_STATE;
  extern const char* BROWSE_NAME_SUPPRESSED_OR_SHELVED;
  extern const char* BROWSE_NAME_MAX_TIME_SHELVED;
  extern const char* BROWSE_NAME_SHELVING_TIME;
  extern const char* BROWSE_NAME_SHELVING_STATE_UNSHELVE;
  extern const char* BROWSE_NAME_SHELVING_STATE_ONE_SHOT_SHELVE;
  extern const char* BROWSE_NAME_SHELVING_STATE_TIMED_SHELVE;

  extern const char* BROWSE_NAME_EVENT_ID;
  extern const char* BROWSE_NAME_SESSION_ID;
  extern const char* BROWSE_NAME_MONITORED_ITEM_ID;
  extern const char* BROWSE_NAME_SUBSCRIPTION_ID;
  extern const char* BROWSE_NAME_PRIORITY;
  extern const char* BROWSE_NAME_PUBLISHING_INTERVAL;
  extern const char* BROWSE_NAME_MAX_KEEPALIVE_COUNT;
  extern const char* BROWSE_NAME_MAX_LIFETIME_COUNT;
  extern const char* BROWSE_NAME_MAX_NOTIFICATIONS_PER_PUBLISH;
  extern const char* BROWSE_NAME_PUBLISHING_ENABLED;
  extern const char* BROWSE_NAME_MODIFY_COUNT;
  extern const char* BROWSE_NAME_ENABLE_COUNt;
  extern const char* BROWSE_NAME_DISABLECOUNT;
  extern const char* BROWSE_NAME_REPUBLISH_REQUEST_COUNT;
  extern const char* BROWSE_NAME_REPUBLISH_MESSAGEREQUEST_COUNT;
  extern const char* BROWSE_NAME_REPUBLISH_MESSAGE_COUNT;
  extern const char* BROWSE_NAME_TRANSFER_REQUEST_COUNT;
  extern const char* BROWSE_NAME_TRANSFERRED_TO_ALTCLIENT_COUNT;
  extern const char* BROWSE_NAME_TRANSFERRED_TO_SAMECLIENT_COUNT;
  extern const char* BROWSE_NAME_PUBLISH_REQUEST_COUNT;
  extern const char* BROWSE_NAME_DATACHANGE_NOTIFICATIONS_COUNT;
  extern const char* BROWSE_NAME_EVENT_NOTIFICATIONS_COUNT;
  extern const char* BROWSE_NAME_NOTIFICATIONS_COUNT;
  extern const char* BROWSE_NAME_LATEPUBLISH_REQUEST_COUNT;
  extern const char* BROWSE_NAME_CURRENT_KEEPALIVE_COUNT;
  extern const char* BROWSE_NAME_CURRENT_LIFETIME_COUNT;
  extern const char* BROWSE_NAME_UNACKNOWLEDGED_MESSAGE_COUNT;
  extern const char* BROWSE_NAME_DISCARDED_MESSAGE_COUNT;
  extern const char* BROWSE_NAME_MONITORED_ITEM_COUNT;
  extern const char* BROWSE_NAME_DISABLED_MONITOREDITEM_COUNT;
  extern const char* BROWSE_NAME_MONITORING_QUEUEOVERFLOW_COUNT;
  extern const char* BROWSE_NAME_NEXT_SEQUENCE_NUMBER;
  extern const char* BROWSE_NAME_NEXT_EVENT_QUEUEOVERFLOW_COUNT;

  extern const char* BROWSE_NAME_SESSION_NAME;
  extern const char* BROWSE_NAME_CLIENT_DESRIPTION;
  extern const char* BROWSE_NAME_SERVER_URI;
  extern const char* BROWSE_NAME_ENDPOINT_URL;
  extern const char* BROWSE_NAME_LOCALE_IDS;
  extern const char* BROWSE_NAME_ACTUAL_SESSION_TIMEOUT;
  extern const char* BROWSE_NAME_MAX_RESPONSE_MESSAGE_SIZE;
  extern const char* BROWSE_NAME_CLIENT_CONNECTION_TIME;
  extern const char* BROWSE_NAME_CLIENT_LAST_CONTACT_TIME;
  extern const char* BROWSE_NAME_CURRENT_SUBSCRIPTIONS_COUNT;
  extern const char* BROWSE_NAME_CURRENT_MONITORED_ITEMS_COUNT;
  extern const char* BROWSE_NAME_CURRENT_PUBLISH_REQUESTS_IN_QUEUE;
  //extern const char* BROWSE_NAME_CURRENT_PUBLISH_TIME_EXPIRATON;
  extern const char* BROWSE_NAME_TOTAL_REQUESTS_COUNT;
  extern const char* BROWSE_NAME_UNAUTHORIZED_REQUESTS_COUNT;
  extern const char* BROWSE_NAME_READ_COUNT;
  extern const char* BROWSE_NAME_HISTORY_READ_COUNT;
  extern const char* BROWSE_NAME_WRITE_COUNT;
  extern const char* BROWSE_NAME_HISTORY_UPDATE_COUNT;
  extern const char* BROWSE_NAME_CALL_COUNT;
  extern const char* BROWSE_NAME_CREATE_MONITORED_ITEMS_COUNT;
  extern const char* BROWSE_NAME_MODIFY_MONITORED_ITEMS_COUNT;
  extern const char* BROWSE_NAME_SET_MONITORING_MODE_COUNT;
  extern const char* BROWSE_NAME_SET_TRIGGERING_COUNT;
  extern const char* BROWSE_NAME_DELETE_MONITORED_ITEMS_COUNT;
  extern const char* BROWSE_NAME_CREATE_SUBSCRIPTION_COUNT;
  extern const char* BROWSE_NAME_MODIFY_SUBSCRIPTION_COUNT;
  extern const char* BROWSE_NAME_SET_PUBLISHING_MODE_COUNT;
  extern const char* BROWSE_NAME_PUBLISH_COUNT;
  extern const char* BROWSE_NAME_REPUBLISH_COUNT;
  extern const char* BROWSE_NAME_TRANSFER_SUBSCRIPTIONS_COUNT;
  extern const char* BROWSE_NAME_DELETE_SUBSCRIPTIONS_COUNT;
  extern const char* BROWSE_NAME_ADD_NODES_COUNT;
  extern const char* BROWSE_NAME_ADD_REFERENCES_COUNT;
  extern const char* BROWSE_NAME_DELETE_NODES_COUNT;
  extern const char* BROWSE_NAME_DELETE_REFERENCES_COUNT;
  extern const char* BROWSE_NAME_BROWSE_COUNT;
  extern const char* BROWSE_NAME_BROWSE_NEXT_COUNT;
  extern const char* BROWSE_NAME_TRANSLATE_BROWSE_PATHS_TO_NODE_IDS_COUNT;
  extern const char* BROWSE_NAME_QUERY_FIRST_COUNT;
  extern const char* BROWSE_NAME_QUERY_NEXT_COUNT;
  extern const char* BROWSE_NAME_REGISTER_NODES_COUNT;
  extern const char* BROWSE_NAME_UNREGISTER_NODES_COUNT;

  extern const char* BROWSE_NAME_CLIENT_USER_ID_OF_SESSION;
  extern const char* BROWSE_NAME_CLIENT_USER_ID_HISTORY;
  extern const char* BROWSE_NAME_AUTHENTICATION_MECHANISM;
  extern const char* BROWSE_NAME_ENCODING;
  extern const char* BROWSE_NAME_TRANSPORT_PROTOCOL;
  extern const char* BROWSE_NAME_SECURITY_MODE;
  extern const char* BROWSE_NAME_SECURITY_POLICY_URI;
  extern const char* BROWSE_NAME_CLIENT_CERTIFICATE;

  class BrowseNames_t
  {
  public:
    typedef struct
    {
      uint32_t    index;
      const char* name;
    } Data_t;

    static Status_t ConvertToCharPtr(IntrusivePtr_t<const QualifiedName_t>& browseName, ScopedPtr_t< Array_t<char> >& result);
    static uint32_t GetIndex(BrowseNames_t::Data_t* source, const uint32_t count, const char* data);
    static const char* GetName(BrowseNames_t::Data_t* source, const uint32_t count, const uint32_t index);
  };
}

#endif //(UASDK_USE_HELPERS > 0)

#endif /* BROWSE_NAMES_T_H_ */
