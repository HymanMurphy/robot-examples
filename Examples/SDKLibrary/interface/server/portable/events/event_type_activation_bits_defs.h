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

#ifndef _EVENT_TYPE_ACTIVATION_BITS_DEFS_T_
#define _EVENT_TYPE_ACTIVATION_BITS_DEFS_T_

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{

/** refer to Figure 27 in UA Spec Part 3 section 9.1 */
typedef enum
{
	/** system event type */
	ENABLE_BIT_DEVICE_FAILURE_EVENT_TYPE = 0,
	ENABLE_BIT_SYSTEM_STATUS_CHANGE_EVENT_TYPE = 1,

	/** progress event type */
	ENABLE_BIT_PROGRESS_EVENT_TYPE = 2,

	/** audit event type */
	ENABLE_BIT_AUDIT_UPDATE_METHOD_EVENT_TYPE = 3,

	/** security certificate of audit event type */
	ENABLE_BIT_AUDIT_CERTIFICATE_DATA_MISMATCH_EVENT_TYPE = 4,
	ENABLE_BIT_AUDIT_CERTIFICATE_EXPIRED_EVENT_TYPE = 5,
	ENABLE_BIT_AUDIT_CERTIFICATE_INVALID_EVENT_TYPE = 6,
	ENABLE_BIT_AUDIT_CERTIFICATE_UNTRUSTED_EVENT_TYPE = 7,
	ENABLE_BIT_AUDIT_CERTIFICATE_REVOKED_EVENT_TYPE = 8,
	ENABLE_BIT_AUDIT_CERTIFICATE_MISMATCH_EVENT_TYPE = 9,

	/** security channel of audit event type */
	ENABLE_BIT_AUDIT_OPEN_SECURE_CHANNEL_EVENT_TYPE = 10,

	/** security session of audit event type */
	ENABLE_BIT_AUDIT_CANCEL_EVENT_TYPE = 11,
	ENABLE_BIT_AUDIT_ACTIVATE_SESSION_EVENT_TYPE = 12,
	ENABLE_BIT_AUDIT_CREATE_SESSION_EVENT_TYPE = 13,
	ENABLE_BIT_AUDIT_URL_MISMATCH_EVENT_TYPE = 14,

	/** node management of audit event type */
	ENABLE_BIT_AUDIT_ADD_NODES_EVENT_TYPE = 15,
	ENABLE_BIT_AUDIT_DELETE_NODES_EVENT_TYPE = 16,
	ENABLE_BIT_AUDIT_ADD_REFERENCES_EVENT_TYPE = 17,
	ENABLE_BIT_AUDIT_DELETE_REFERENCES_EVENT_TYPE = 18,

	/** update of audit event type */
	ENABLE_BIT_AUDIT_WRITE_UPDATE_EVENT_TYPE = 19,
	ENABLE_BIT_AUDIT_HISTORY_UPDATE_EVENT_TYPE = 20,

	/** semantic change event type */
	ENABLE_BIT_SEMANTIC_CHANGE_EVENT_TYPE = 21,

	/** Model change event type */
	ENABLE_BIT_GENERAL_MODEL_CHANGE_EVENT_TYPE = 22,


	/** remaining bits (23-31) reserved for condition event type */

  /** Audit Condition event type */
  ENABLE_BIT_AUDIT_CONDITION_ENABLE_EVENT_TYPE = 23,
  ENABLE_BIT_AUDIT_CONDITION_COMMENT_EVENT_TYPE = 24,
  ENABLE_BIT_AUDIT_CONDITION_RESPOND_EVENT_TYPE = 25,
  ENABLE_BIT_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE = 26,
  ENABLE_BIT_AUDIT_CONDITION_CONFIRM_EVENT_TYPE = 27,
  ENABLE_BIT_AUDIT_CONDITION_SHELVING_EVENT_TYPE = 28,

  /** Condition Refresh related event type */
  ENABLE_BIT_CONDITION_REFRESH_START_EVENT_TYPE = 29,
  ENABLE_BIT_CONDITION_REFRESH_END_EVENT_TYPE = 30,
  ENABLE_BIT_CONDITION_REFRESH_REQUIRED_EVENT_TYPE = 30,

	ENABLE_BIT_END = 32
} Event_Types_Enable_Bits_t;

/** enable individual event type */
#define ENABLE_DEVICE_FAILURE_EVENT_TYPE                   ((1<<ENABLE_BIT_DEVICE_FAILURE_EVENT_TYPE) & 0xffffffff)
#define ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE             ((1<<ENABLE_BIT_SYSTEM_STATUS_CHANGE_EVENT_TYPE) & 0xffffffff)

#define ENABLE_PROGRESS_EVENT_TYPE 				                 ((1<<ENABLE_BIT_PROGRESS_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_UPDATE_METHOD_EVENT_TYPE              ((1<<ENABLE_BIT_AUDIT_UPDATE_METHOD_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_CERTIFICATE_DATA_MISMATCH_EVENT_TYPE  ((1<<ENABLE_BIT_AUDIT_CERTIFICATE_DATA_MISMATCH_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CERTIFICATE_EXPIRED_EVENT_TYPE        ((1<<ENABLE_BIT_AUDIT_CERTIFICATE_EXPIRED_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CERTIFICATE_INVALID_EVENT_TYPE        ((1<<ENABLE_BIT_AUDIT_CERTIFICATE_INVALID_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CERTIFICATE_UNTRUSTED_EVENT_TYPE      ((1<<ENABLE_BIT_AUDIT_CERTIFICATE_UNTRUSTED_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CERTIFICATE_REVOKED_EVENT_TYPE        ((1<<ENABLE_BIT_AUDIT_CERTIFICATE_REVOKED_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CERTIFICATE_MISMATCH_EVENT_TYPE       ((1<<ENABLE_BIT_AUDIT_CERTIFICATE_MISMATCH_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_OPEN_SECURE_CHANNEL_EVENT_TYPE        ((1<<ENABLE_BIT_AUDIT_OPEN_SECURE_CHANNEL_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_CANCEL_EVENT_TYPE                     ((1<<ENABLE_BIT_AUDIT_CANCEL_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_ACTIVATE_SESSION_EVENT_TYPE           ((1<<ENABLE_BIT_AUDIT_ACTIVATE_SESSION_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CREATE_SESSION_EVENT_TYPE             ((1<<ENABLE_BIT_AUDIT_CREATE_SESSION_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_URL_MISMATCH_EVENT_TYPE               ((1<<ENABLE_BIT_AUDIT_URL_MISMATCH_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_ADD_NODES_EVENT_TYPE                  ((1<<ENABLE_BIT_AUDIT_ADD_NODES_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_DELETE_NODES_EVENT_TYPE               ((1<<ENABLE_BIT_AUDIT_DELETE_NODES_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_ADD_REFERENCES_EVENT_TYPE             ((1<<ENABLE_BIT_AUDIT_ADD_REFERENCES_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_DELETE_REFERENCES_EVENT_TYPE          ((1<<ENABLE_BIT_AUDIT_DELETE_REFERENCES_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_WRITE_UPDATE_EVENT_TYPE               ((1<<ENABLE_BIT_AUDIT_WRITE_UPDATE_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_HISTORY_UPDATE_EVENT_TYPE             ((1<<ENABLE_BIT_AUDIT_HISTORY_UPDATE_EVENT_TYPE) & 0xffffffff)

#define ENABLE_SEMANTIC_CHANGE_EVENT_TYPE        		       ((1<<ENABLE_BIT_SEMANTIC_CHANGE_EVENT_TYPE) & 0xffffffff)
#define ENABLE_MODEL_CHANGE_EVENT_TYPE           		       ((1<<ENABLE_BIT_GENERAL_MODEL_CHANGE_EVENT_TYPE) & 0xffffffff)

#define ENABLE_AUDIT_CONDITION_ENABLE_EVENT_TYPE        	 ((1<<ENABLE_BIT_AUDIT_CONDITION_ENABLE_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CONDITION_COMMENT_EVENT_TYPE          ((1<<ENABLE_BIT_AUDIT_CONDITION_COMMENT_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CONDITION_RESPOND_EVENT_TYPE        	 ((1<<ENABLE_BIT_AUDIT_CONDITION_RESPOND_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE      ((1<<ENABLE_BIT_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CONDITION_CONFIRM_EVENT_TYPE        	 ((1<<ENABLE_BIT_AUDIT_CONDITION_CONFIRM_EVENT_TYPE) & 0xffffffff)
#define ENABLE_AUDIT_CONDITION_SHELVING_EVENT_TYPE         ((1<<ENABLE_BIT_AUDIT_CONDITION_SHELVING_EVENT_TYPE) & 0xffffffff)

#define ENABLE_CONDITION_REFRESH_START_EVENT_TYPE        	 ((1<<ENABLE_BIT_CONDITION_REFRESH_START_EVENT_TYPE) & 0xffffffff)
#define ENABLE_CONDITION_REFRESH_END_EVENT_TYPE            ((1<<ENABLE_BIT_CONDITION_REFRESH_END_EVENT_TYPE) & 0xffffffff)
#define ENABLE_CONDITION_REFRESH_REQUIRED_EVENT_TYPE       ((1<<ENABLE_BIT_CONDITION_REFRESH_REQUIRED_EVENT_TYPE) & 0xffffffff)


/** disable individual event type */
#define DISABLE_DEVICE_FAILURE_EVENT_TYPE                  ((~ENABLE_DEVICE_FAILURE_EVENT_TYPE) & 0xffffffff)
#define DISABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE            ((~ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE) & 0xffffffff)

#define DISABLE_PROGRESS_EVENT_TYPE 				               ((~ENABLE_PROGRESS_EVENT_TYPE) & 0xffffffff)

#define DISABLE_AUDIT_UPDATE_METHOD_EVENT_TYPE             ((~ENABLE_AUDIT_UPDATE_METHOD_EVENT_TYPE) & 0xffffffff)

#define DISABLE_AUDIT_CERTIFICATE_DATA_MISMATCH_EVENT_TYPE ((~ENABLE_AUDIT_CERTIFICATE_DATA_MISMATCH_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CERTIFICATE_EXPIRED_EVENT_TYPE       ((~ENABLE_AUDIT_CERTIFICATE_EXPIRED_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CERTIFICATE_INVALID_EVENT_TYPE       ((~ENABLE_AUDIT_CERTIFICATE_INVALID_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CERTIFICATE_UNTRUSTED_EVENT_TYPE     ((~ENABLE_AUDIT_CERTIFICATE_UNTRUSTED_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CERTIFICATE_REVOKED_EVENT_TYPE       ((~ENABLE_AUDIT_CERTIFICATE_REVOKED_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CERTIFICATE_MISMATCH_EVENT_TYPE      ((~ENABLE_AUDIT_CERTIFICATE_MISMATCH_EVENT_TYPE) & 0xffffffff)

#define DISABLE_AUDIT_OPEN_SECURE_CHANNEL_EVENT_TYPE       ((~ENABLE_AUDIT_OPEN_SECURE_CHANNEL_EVENT_TYPE) & 0xffffffff)

#define DISABLE_AUDIT_CANCEL_EVENT_TYPE                    ((~ENABLE_AUDIT_CANCEL_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_ACTIVATE_SESSION_EVENT_TYPE          ((~ENABLE_AUDIT_ACTIVATE_SESSION_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CREATE_SESSION_EVENT_TYPE            ((~ENABLE_AUDIT_CREATE_SESSION_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_URL_MISMATCH_EVENT_TYPE              ((~ENABLE_AUDIT_URL_MISMATCH_EVENT_TYPE) & 0xffffffff)

#define DISABLE_AUDIT_ADD_NODES_EVENT_TYPE                 ((~ENABLE_AUDIT_ADD_NODES_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_DELETE_NODES_EVENT_TYPE              ((~ENABLE_AUDIT_DELETE_NODES_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_ADD_REFERENCES_EVENT_TYPE            ((~ENABLE_AUDIT_ADD_REFERENCES_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_DELETE_REFERENCES_EVENT_TYPE         ((~ENABLE_AUDIT_DELETE_REFERENCES_EVENT_TYPE) & 0xffffffff)

#define DISABLE_AUDIT_WRITE_UPDATE_EVENT_TYPE              ((~ENABLE_AUDIT_WRITE_UPDATE_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_HISTORY_UPDATE_EVENT_TYPE            ((~ENABLE_AUDIT_HISTORY_UPDATE_EVENT_TYPE) & 0xffffffff)

#define DISABLE_SEMANTIC_CHANGE_EVENT_TYPE        		     ((~ENABLE_SEMANTIC_CHANGE_EVENT_TYPE) & 0xffffffff))
#define DISABLE_MODEL_CHANGE_EVENT_TYPE           		     ((~ENABLE_MODEL_CHANGE_EVENT_TYPE) & 0xffffffff))

#define DISABLE_AUDIT_CONDITION_ENABLE_EVENT_TYPE        	 ((~ENABLE_AUDIT_CONDITION_ENABLE_EVENT_TYPE) & 0xffffffff))
#define DISABLE_AUDIT_CONDITION_COMMENT_EVENT_TYPE         ((~ENABLE_AUDIT_CONDITION_COMMENT_EVENT_TYPE) & 0xffffffff))
#define DISABLE_AUDIT_CONDITION_RESPOND_EVENT_TYPE         ((~ENABLE_AUDIT_CONDITION_RESPOND_EVENT_TYPE) & 0xffffffff))
#define DISABLE_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE     ((~ENABLE_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE) & 0xffffffff))
#define DISABLE_AUDIT_CONDITION_CONFIRM_EVENT_TYPE         ((~ENABLE_AUDIT_CONDITION_CONFIRM_EVENT_TYPE) & 0xffffffff))
#define DISABLE_AUDIT_CONDITION_SHELVING_EVENT_TYPE        ((~ENABLE_AUDIT_CONDITION_SHELVING_EVENT_TYPE) & 0xffffffff))

#define DISABLE_CONDITION_REFRESH_START_EVENT_TYPE         ((~ENABLE_CONDITION_REFRESH_START_EVENT_TYPE) & 0xffffffff))
#define DISABLE_CONDITION_REFRESH_END_EVENT_TYPE           ((~ENABLE_CONDITION_REFRESH_END_EVENT_TYPE) & 0xffffffff))
#define DISABLE_CONDITION_REFRESH_REQUIRED_EVENT_TYPE      ((~ENABLE_CONDITION_REFRESH_REQUIRED_EVENT_TYPE) & 0xffffffff))

/** enable a group category of event types */
#define ENABLE_SYSTEM_EVENT_TYPE                           (  ENABLE_DEVICE_FAILURE_EVENT_TYPE \
                                                            | ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE )

#define ENABLE_AUDIT_SECURITY_CERTIFICATE_EVENT_TYPE       (  ENABLE_AUDIT_CERTIFICATE_DATA_MISMATCH_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CERTIFICATE_EXPIRED_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CERTIFICATE_INVALID_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CERTIFICATE_UNTRUSTED_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CERTIFICATE_REVOKED_EVENT_TYPE \
                                                            |	ENABLE_AUDIT_CERTIFICATE_MISMATCH_EVENT_TYPE )

#define ENABLE_AUDIT_SESSION_EVENT_TYPE                    (  ENABLE_AUDIT_CANCEL_EVENT_TYPE \
		                                              		      | ENABLE_AUDIT_ACTIVATE_SESSION_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CREATE_SESSION_EVENT_TYPE \
                                                            | ENABLE_AUDIT_URL_MISMATCH_EVENT_TYPE )

#define ENABLE_AUDIT_NODES_MANAGEMENT_EVENT_TYPE           (  ENABLE_AUDIT_ADD_NODES_EVENT_TYPE \
		                                              		      | ENABLE_AUDIT_DELETE_NODES_EVENT_TYPE \
                                                            | ENABLE_AUDIT_ADD_REFERENCES_EVENT_TYPE \
                                                            | ENABLE_AUDIT_DELETE_REFERENCES_EVENT_TYPE )

#define ENABLE_AUDIT_UPDATE_EVENT_TYPE                     (  ENABLE_AUDIT_WRITE_UPDATE_EVENT_TYPE \
                                                            | ENABLE_AUDIT_HISTORY_UPDATE_EVENT_TYPE )


#define ENABLE_AUDIT_CONDITION_EVENT_TYPE                  (  ENABLE_AUDIT_CONDITION_ENABLE_EVENT_TYPE \
		                                              		      | ENABLE_AUDIT_CONDITION_COMMENT_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CONDITION_RESPOND_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CONDITION_CONFIRM_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CONDITION_SHELVING_EVENT_TYPE )

#define ENABLE_CONDITION_REFRESH_EVENT_TYPE                (  ENABLE_CONDITION_REFRESH_START_EVENT_TYPE \
		                                              		      | ENABLE_CONDITION_REFRESH_END_EVENT_TYPE \
                                                            | ENABLE_CONDITION_REFRESH_REQUIRED_EVENT_TYPE )

#define ENABLE_AUDIT_EVENT_TYPE                            (  ENABLE_AUDIT_UPDATE_METHOD_EVENT_TYPE \
		                                              		      | ENABLE_AUDIT_SECURITY_CERTIFICATE_EVENT_TYPE \
                                                            | ENABLE_AUDIT_OPEN_SECURE_CHANNEL_EVENT_TYPE \
                                                            | ENABLE_AUDIT_SESSION_EVENT_TYPE \
                                                            | ENABLE_AUDIT_NODES_MANAGEMENT_EVENT_TYPE \
                                                            | ENABLE_AUDIT_CONDITION_EVENT_TYPE \
                                                            | ENABLE_AUDIT_UPDATE_EVENT_TYPE)

#define ENABLE_BASE_EVENT_TYPE                             (  ENABLE_SYSTEM_EVENT_TYPE \
		                                              		      | ENABLE_PROGRESS_EVENT_TYPE \
                                                            | ENABLE_AUDIT_EVENT_TYPE \
                                                            | ENABLE_CONDITION_REFRESH_EVENT_TYPE \
                                                            | ENABLE_SEMANTIC_CHANGE_EVENT_TYPE \
                                                            | ENABLE_MODEL_CHANGE_EVENT_TYPE )

/** disable a group category of event types */
#define DISABLE_SYSTEM_EVENT_TYPE                          ((~ENABLE_SYSTEM_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_SECURITY_CERTIFICATE_EVENT_TYPE      ((~ENABLE_AUDIT_SECURITY_CERTIFICATE_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_SESSION_EVENT_TYPE                   ((~ENABLE_AUDIT_SESSION_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_NODES_MANAGEMENT_EVENT_TYPE          ((~ENABLE_AUDIT_NODES_MANAGEMENT_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_UPDATE_EVENT_TYPE                    ((~ENABLE_AUDIT_UPDATE_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_EVENT_TYPE                           ((~ENABLE_AUDIT_EVENT_TYPE) & 0xffffffff)
#define DISABLE_BASE_EVENT_TYPE                            ((~ENABLE_BASE_EVENT_TYPE) & 0xffffffff)
#define DISABLE_AUDIT_CONDITION_EVENT_TYPE                 ((~ENABLE_AUDIT_CONDITION_EVENT_TYPE) & 0xffffffff)
#define DISABLE_CONDITION_REFRESH_EVENT_TYPE               ((~ENABLE_CONDITION_REFRESH_EVENT_TYPE) & 0xffffffff)

}

#endif // UASDK_INCLUDE_EVENTS

#endif // _EVENT_TYPE_ACTIVATION_BITS_DEFS_T_
