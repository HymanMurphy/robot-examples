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

#ifndef _BASE_CONDITION_T_
#define _BASE_CONDITION_T_

#include "icondition_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "iserver_configuration_t.h"
#include "icondition_state_update_handler_t.h"
#include "inode_value_attribute_reader_writer_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_localized_text_t.h"
#include "base_object_t.h"
#include "icondition_registrar_t.h"
#include "inode_t.h"
#include "method_t.h"
#include "utilities.h"
#include "address_space_utilities_t.h"
#include "opcua_call_method_request_t.h"
#include "opcua_call_method_result_t.h"
#include "browse_names_t.h"
#include "localizable_text_from_display_name_t.h"
#include "event_helper_t.h"
#include "address_space_modeler_t.h"
#include "iuser_permissions_t.h"
#include "condition_type_data_t.h"
#include "two_state_variable_type_t.h"
#include "condition_variable_type_t.h"

namespace uasdk
{

class BaseCondition_t;

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief IBaseConditionMethodListener_t
*
* This class is used to add callback listener for the condition methods.
* The methods of this class should be implemented in the application layer.
*
*/
class IBaseConditionMethodListener_t : public IRefCount_t
{
public:

  virtual void OnEnable(ICondition_t& condition, const IUserPermissions_t& userPermissions, Status_t result) = 0;

  virtual void OnDisable(ICondition_t& condition, const IUserPermissions_t& userPermissions, Status_t result) = 0;

  virtual void OnAddComment(
    ICondition_t& condition,
    const IUserPermissions_t& userPermissions,
    const ByteString_t& eventId,
    const LocalizedText_t& comment,
    Status_t result) = 0;

};

/*****************************************************************************/
/** \brief BaseCondition_t
*
* The BaseCondition defines all general characteristics of a Condition. All other ConditionTypes derive from it.
*
*/
class BaseCondition_t : public ICondition_t, public IConditionStateUpdateHandler_t, public INodeValueAttributeReaderWriter_t, public Allocatable_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(BaseCondition_t);

private: 

  /*****************************************************************************/
  /* @var IntrusivePtr_t<AddressSpaceModeler_t> addressSpaceModeler
  * addressSpaceModeler is used to model the condition in the address space
  */
  IntrusivePtr_t<AddressSpaceModeler_t> addressSpaceModeler;

  /*****************************************************************************/
  /* @var  uint32_t conditionStateCounter
  * conditionStateCounter is used to track the condition state and variable changes.
  */
  uint32_t conditionStateCounter;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ConditionTypeData_t> conditionData
  * conditionData is a structure which holds all the variables of the condition.
  */
  IntrusivePtr_t<ConditionTypeData_t> conditionData;

  /*****************************************************************************/
  /** InitialiseConditionDataAttributes()
  * InitialiseConditionDataAttributes will initialize the data object attributes 
  *
  * @param[in] conditionClassId
  * condition class id
  *
  * @param[in] conditionName
  * ConditionName identifies the Condition instance that the Event originated from
  *
  * @return
  * status of the operation
  */
  Status_t InitialiseConditionDataAttributes(uint32_t conditionClassId, String_t& conditionName);

  /*****************************************************************************/
  /** UpdateEnabledState()
  * This Method is used to change a Condition instance to the input state.
  *
  * @param[in] isEnabled_
  * EnabledState value
  *
  * @return
  * status of the operation
  */
  Status_t UpdateEnabledState(bool isEnabled_);

 

protected:

  /*****************************************************************************/
  /** BeginConditionStateUpdate()
  * Multiple condition state updates can be grouped together in a single notification by calling BeginConditionStateUpdate before
  * calling ConditionStateUpdated().
  * Every call to BeginConditionStateUpdate() must be matched with a call to EndConditionStateUpdate()
  *
  * BeginConditionStateUpdate/EndConditionStateUpdate blocks may be built recursively, and all updates made inside a block
  * will be sent as a single notification at the end.
  *
  */
  virtual void BeginConditionStateUpdate(void);

  /*****************************************************************************/
  /** ConditionStateUpdated()
  * ConditionStateUpdated should be called every time a condition variable member
  * of the class has been changed.  If it is called inside of a BeginConditionStateUpdate/EndConditionStateUpdate pair,
  * the event notification will be sent when all updates are completed and the final EndCOnditionStateUpdate call is made.
  * If this method is called outside of a Begin.../End ... block, then an event notification is sent immediately.
  *
  * @return
  * status of the operation
  */
  virtual void ConditionStateUpdated(void);

  /*****************************************************************************/
  /** EndConditionStateUpdate()
  * end of the condition state update
  *
  * @return
  * status of the operation
  */
  virtual void EndConditionStateUpdate(void);

  /*****************************************************************************/
  /* @var IntrusivePtr_t<BaseObject_t> baseObject
  * baseObject is a helper object which represents the condition and other UA objects in the address space
  */
  IntrusivePtr_t<BaseObject_t> baseObject;
  Lock_t lock;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IServerConfiguration_t> configuration
  * configuration is the instance of server configuration
  */
  IntrusivePtr_t<IServerConfiguration_t> configuration;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> conditionId
  * conditionId is the unique identifer for a condition
  */
  IntrusivePtr_t<NodeId_t> conditionId;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IBaseConditionMethodListener_t> conditionMethodListener
  * conditionMethodListener is used to register for callback listeners.
  */
  IntrusivePtr_t<IBaseConditionMethodListener_t> conditionMethodListener;

  /*****************************************************************************/
  /** EvaluteState()
  * EvaluteState will evaluate the current state of the condition
  *
  * @param[in] methodId
  * methodId is the type Id of the method from which the EvaluateState is called.
  *
  * @return
  * return the status of the operation.
  */
  Status_t EvaluteState(uint32_t methodId);

  /*****************************************************************************/
  /** InitialiseConditionData()
  * InitialiseConditionData will initialize the data object
  *
  * @param[in] conditionData_
  * input condition data object
  *
  * @param[in] conditionClassId
  * The ConditionClassId Property of the ConditionType is used to assign a Condition to a ConditionClass.
  *
  * @param[in] conditionName
  * ConditionName identifies the Condition instance that the Event originated from
  *
  * @param[in] isAllocated
  * if this flag is false, conditionData object will be allocated, else it will only assign the input data object to the member variable.
  *
  * @return
  * status of the operation
  */
  virtual Status_t InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated = false);

  /*****************************************************************************/
  /** GetStandardNodeId()
  * GetStandardNodeId method will return the type Id of the input node if
  * condition is mounted in the address space
  *
  * @param[in] node
  * input node
  *
  * @return
  * return the type Id of the node if the condition is mounted to the address space, else returns 0
  */
  uint32_t GetStandardNodeId(const INode_t& node);

  /*****************************************************************************/
  /** GetMethodNodeFromStandardNodeId()
  * GetMethodNodeFromStandardNodeId will return the method node from the input type Id of the method
  *
  * @param[in] standardNodeId
  * typeId of the node
  *
  * @param[out] methodId
  * nodeId of the method
  *
  * @return
  * status of the operation
  */
  Status_t GetMethodNodeIdFromStandardNodeId(uint32_t standardNodeId, IntrusivePtr_t<NodeId_t>& methodId);

  /*****************************************************************************/
  /** OnDisable()
  * OnDisable method to be called from the CallMethodBegin. 
  * Here all other necessary action will be taken care before changing the state to disable
  *
  * @param[in] userPermissions
  * An object used to identify a specific user and authenticate that user's access permissions.
  *
  * @return
  * status of the operation
  */
  virtual Status_t OnDisable(const IUserPermissions_t& userPermissions);

  /*****************************************************************************/
  /** OnEnable()
  * OnEnable method to be called from the CallMethodBegin. 
  * Here all other necessary action will be taken care before changing the state to enable
  *
  * @param[in] userPermissions
  * An object used to identify a specific user and authenticate that user's access permissions.
  *
  * @return
  * status of the operation
  */
  virtual Status_t OnEnable(const IUserPermissions_t& userPermissions);

  /*****************************************************************************/
  /** OnAddComment()
  * OnAddMethod method to be called from the CallMethodBegin. Here all other necessary action will be taken before adding comment
  *
  * @param[in] userPermissions
  * An object used to identify a specific user and authenticate that user's access permissions.
  *  
  * @param[in] requestParameters
  * requested parameter
  *
  * @return
  * status of the operation
  */
  virtual Status_t OnAddComment(const IUserPermissions_t& userPermissions, IntrusivePtr_t<const CallMethodRequest_t>& requestParameters);

 
  /*****************************************************************************/
  /** FireEventNotification()
  * This method is called to take a copy of the current event information and 
  * post it to any subscribed UA clients through monitored items.
  *
  * @return
  * status of the operation
  */
  virtual Status_t FireEventNotification(void);


  /*****************************************************************************/
  /** EvaluateQualityFromEnabledState()
  * EvaluateQualityFromEnabledState method return the quality based on the EnabledState
  *
  * @param[out] quality_
  * quality to be updated
  *
  * @return
  * status of the operation
  */
  Status_t EvaluateQualityFromEnabledState(IntrusivePtr_t<ConditionVariableType_t>& quality_);

  /*****************************************************************************/
  /** UpdateCommentState()
  * Update the comment state
  *
  * @param[in] eventId
  * id of the event to which add comment should be added.
  *
  * @param[in] comment
  * Comment to be added
  *
  * @return
  * status of the operation
  */
  Status_t UpdateCommentState(ByteString_t& eventId, LocalizedText_t& comment);

  /*****************************************************************************/
  /**  MayFireEventNotification();
  * Called by FireEventNotification to check if notifications should be sent.
  * The default implementation provided by BaseCondition_t checks whether or 
  * not the condition is enabled.
  * This may be overriden by subclasses to provide more complex rules. 
  * E.g. the AlarmCondition_t class will override this to support use of the 
  * Suppressed state to block event notifications.
  *
  * Note:  This does not check if there is a reason to fire a notification --
  *  It only checks if it is allowed.  If the event is taged with a AlwaysGenerateEvent
  *  indication in the spec, the value of this should be ignored.
  *
  * @return
  * true if the condition is in a state where event notifications are allowed.
  */
  virtual bool MayFireEventNotification(void);

public:

  /*****************************************************************************/
  /** BaseCondition_t()
  * Constructor for the class
  */
  BaseCondition_t();

  /*****************************************************************************/
  /** ~BaseCondition_t()
  * Destructor for the class
  */
  virtual ~BaseCondition_t();

  /*****************************************************************************/
  /** Initialise()
  * This method is used to create condition and update in the condition registrar of the condition is created successfully.
  *
  * @param[in] configuration_
  * server configuration
  *
  * @param[in] conditionId_
  * id for the condition
  *
  * @param[in] conditionClassId
  * class id of the condition
  *
  * @param[in] conditionName
  * ConditionName identifies the Condition instance that the Event originated from
  *
  * @return
  * status of the operation
  */
  virtual Status_t Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName) = 0;

  /*****************************************************************************/
  /** InitialiseEnabledStateLocalizationValues()
  * This method is used to set the enabledState localization values
  * Ensure that, condition is initialised before calling this method.
  *
  * @param[in] enabledStateTrueState
  * list of true values for enabledState
  *
  * @param[in] enabledStateFalseState
  * list of false values for enabledState
  *
  * @return
  * status of the operation
  */
  Status_t InitialiseEnabledStateLocalizationValues(IntrusivePtr_t<ILocalizableText_t> enabledStateTrueState, IntrusivePtr_t<ILocalizableText_t> enabledStateFalseState);

  /*****************************************************************************/
  /** ConditionId()
  * Get Condition Id
  *
  * @return
  * intrusive pointer to condition id
  */
  virtual IntrusivePtr_t<const NodeId_t> ConditionId(void);
  
  /*****************************************************************************/
  /** ConditionNode()
  * Get condition node from the address space
  *
  * @param[out] result
  * status of the operation
  *
  * @return
  * intrusive pointer to the object node
  */
  IntrusivePtr_t<const IObjectNode_t> ConditionNode(Status_t& result) const;

  /*****************************************************************************/
  /** IsEnabled()
  * method to check whether the condition is enabled
  *
  * @return
  * true if enabled, else false
  */
  bool IsEnabled(void);

  /*****************************************************************************/
  /** Disable()
  * The Disable Method is used to change a Condition instance to the Disabled state.
  *
  * @return
  * status of the operation
  */
  virtual Status_t Disable(void);

  /*****************************************************************************/
  /** Enable()
  * The Enable Method is used to change a Condition instance to the enabled state.
  *
  * @return
  * status of the operation
  */
  virtual Status_t Enable(void);

  /*****************************************************************************/
  /** AddComment()
  * AddComment Method is used to apply a comment to a specific state of a Condition instance.
  *
  * @param[in] eventId
  * id of the event to which add comment should be added.
  *
  * @param[in] comment
  * Comment to be added
  *
  * @return
  * status of the operation
  */
  virtual Status_t AddComment(ByteString_t& eventId, LocalizedText_t& comment);

  /*****************************************************************************/
  /** MountToAddressSpace()
  * Mount the condition in the address space
  *
  * @param[in] browseName
  * browse name of the condition
  *
  * @param[in] hasTypeDefinitionId
  * type definition reference of the condition
  *
  * @param[in] parentNodeId
  * new parent id
  *
  * @return
  * status of the operation
  */
  virtual Status_t MountToAddressSpace(const String_t& browseName, uint32_t hasTypeDefinitionId, NodeId_t& parentNodeId);

  /*****************************************************************************/
  /** SetMethodListener()
  * Set the method handler for the callback listener
  *
  * @param[in] value
  * callback listener instance
  *
  * @return
  * status of the operation
  */
  virtual Status_t SetMethodListener(IntrusivePtr_t<IBaseConditionMethodListener_t> value);

  /*****************************************************************************/
  /** UnmountFromAddressSpace()
  * Unmount the condition from the address space
  *
  * @param[in] browseName
  * browse name of the condition
  *
  * @param[in] hasTypeDefinitionId
  * type definition reference of the condition
  *
  * @param[in] newParentNodeId
  * new parent id
  *
  * @return
  * status of the operation
  */
  virtual void UnmountFromAddressSpace(void);

  /*****************************************************************************/
  /** RelocateInAddressSpace()
  * Relocate the condition in the address space
  *
  * @param[in] browseName
  * browse name of the condition
  *
  * @param[in] hasTypeDefinitionId
  * type definition reference of the condition
  *
  * @param[in] newParentNodeId
  * new parent id
  *
  * @return
  * status of the operation
  */
  virtual Status_t RelocateInAddressSpace(const String_t& browseName, uint32_t hasTypeDefinitionId, NodeId_t& newParentNodeId);

  /*****************************************************************************/
  /** IsMountedToAddressSpace()
  * IsMountedToAddressSpace is used to find if the condition is
  * mounted in the address space or not
  *
  * @return
  * return true if the condition is mounted in the address space, else return false
  */
  virtual bool IsMountedToAddressSpace(void);


  /*****************************************************************************/
  /** ConditionData()
  *  Get the condition data instance
  *
  * @return
  * condition data instance
  */
  virtual IntrusivePtr_t<ConditionTypeData_t>& ConditionData(void);
  
  /*****************************************************************************/
  /** Begins calling the method of the node
  *
  *  If the method call is successful
  *  completedCallback.CallMethodCompleted() will be called by the method handler
  *  when the method has completed. If this function returns a bad status code
  *  completedCallback.CallMethodCompleted() will not be called by the method
  *  handler.
  *
  * @param[in] sessionId
  * The ID of the session making the call. Will be null if the call is not being made
  * in the context of a session.
  *
  * @param[in] transationId
  * A non-zero unique identifier for a collection of methods being called as a
  * group (typically by the Call Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of method calls by the
  * application. If calling the method outside of the Call Service should be set
  * to zero.
  *
  * @param[in] userPermissions
  * An object used to identify a specific user and authenticate that user's
  * access permissions.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Call Service. The method
  * handler can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[in] componentOf
  * The object that defines the context for the method call. Must be referenced by
  * a ComponentOf reference from the Method.
  *
  * @param[in] requestParameters
  * The parameters of the method call.
  *
  * @param[in] method
  * The method to be called
  *
  * @param[in] result
  * Object to store the result of the method call.
  *
  * @param[out] completedCallback
  * The CallMethodCompleted() function of this interface will be called by the method
  * handler if this function returns a good status code.
  *
  * @return
  * The result of the operation. If the status code is good then the method handler
  * has been successfully launched and will return the method result in due course. If
  * the status code is bad the method handler was not successfully launched.
  *
  */
  virtual Status_t CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
    uint32_t transactionId,
    const IUserPermissions_t& userPermissions,
    uint32_t timeoutHint,
    IntrusivePtr_t<INode_t>& componentOf,
    IntrusivePtr_t<IMethodNode_t>& method,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result,
    IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback);

  /*****************************************************************************/
  /** Availability of read value attribute object synchronously or not
  *
  * @param[in] node
  * variable node for query
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */

  virtual bool CanReadValueSynchronously(const IVariableNode_t& node);

  /*****************************************************************************/
  /** Begins reading the value attribute of the node asynchronously
  *
  *  If reading is successful completedCallback.ReadValueAttributeCompleted()
  *  will be called. If reading is not successful completedCallback.ReadValueAttributeCompleted()
  *  will not be called.
  *
  * @param[in] node
  * variable node from which data will be read
  *
  * @param[in] maxAge
  * The maxAge of the value in milliseconds provided by the Read Service. The reader
  * can optionally consider this when replying to the caller.
  * Should be set to zero where no maxAge is provided.
  *
  * @param[in] setSourceTimestamp
  * Set the source timestamp in the data value.
  *
  * @param[in] locales
  * A list of locales in order of preference to use when reading LocalizedText.
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being read as a
  * group (typically by the Read Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of read operations by the
  * application. If reading the node outside of the Read Service should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Read Service. The reader
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] completedCallback
  * The ReadValueAttributeCompleted() function of this interface will be called by the
  * reader if this function returns a good status code.
  *
  * @return
  * The result of the operation.
  *
  */
  virtual Status_t ReadValueAttributeBegin(
    IntrusivePtr_t<const IVariableNode_t>& node,
    uint32_t maxAge,
    bool setSourceTimestamp,
    IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
    IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback);

  /*****************************************************************************/
  /** Reading the value attribute of the node synchronously
  *
  * @param[in] node
  * variable node from which data will be read
  *
  * @param[in] maxAge
  * The maxAge of the value in milliseconds provided by the Read Service. The reader
  * can optionally consider this when replying to the caller.
  * Should be set to zero where no maxAge is provided.
  *
  * @param[in] setSourceTimestamp
  * Set the source timestamp in the data value.
  *
  * @param[in] locales
  * A list of locales in order of preference to use when reading LocalizedText.
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being read as a
  * group (typically by the Read Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of read operations by the
  * application. If reading the node outside of the Read Service should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Read Service. The reader
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] dataValue
  * That read from the node will be update to the dataValue
  *
  * @param[out] diagnosticInfo
  * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  * required.
  *
  * @return
  * The result of the operation.
  *
  */
  virtual Status_t ReadValueAttribute(
    const IVariableNode_t& node,
    uint32_t maxAge,
    bool setSourceTimestamp,
    const ArrayUA_t<String_t>& locales,
    const Array_t<IndexRange_t>& indexRange,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<DataValue_t>& dataValue,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo);

  /*****************************************************************************/
  /** Availability of write value attribute object synchronously or not
  *
  * @param[in] node
  * variable node for query
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */
  virtual bool CanWriteValueSynchronously(const IVariableNode_t& node);

  /*****************************************************************************/
  /** Begins writing the value attribute of the node synchronously
  *
  *  If the Writing node is successful completedCallback.WriteValueAttributeCompleted()
  *  will be called. otherwise completedCallback.WriteValueAttributeCompleted()
  *  will not be called.
  *
  * @param[out] node
  * node to write data value
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] dataValue
  * The value to be written.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being written as a
  * group (typically by the Write Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of write operations by the
  * application. If writing the node outside of the WriteService should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Write Service. The writer
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] completedCallback
  * The WriteValueAttributeCompleted() function of this interface will be called by the
  * writer if this function returns a good status code.
  *
  * @return
  * The result of the operation. If the status code is good then the writer
  * has been successfully launched and will return the write result in due course. If
  * the status code is bad the writer was not successfully launched.
  *
  */
  virtual Status_t WriteValueAttributeBegin(
    IntrusivePtr_t<IVariableNode_t>& node,
    IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
    IntrusivePtr_t<const DataValue_t> dataValue,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback);

  /*****************************************************************************/
  /** Writing the value attribute of the node Synchronously
  *
  * @param[out] node
  * node to write data value
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] dataValue
  * The value to be written.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being written as a
  * group (typically by the Write Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of write operations by the
  * application. If writing the node outside of the WriteService should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Write Service. The writer
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] diagnosticInfo
  * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  * required.
  *
  * @return
  * The result of the operation.
  *
  */
  virtual Status_t WriteValueAttribute(
    IVariableNode_t& node,
    const Array_t<IndexRange_t>& indexRange,
    IntrusivePtr_t<const DataValue_t> dataValue,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo);

  };

/** @} */

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _BASE_CONDITION_T_
