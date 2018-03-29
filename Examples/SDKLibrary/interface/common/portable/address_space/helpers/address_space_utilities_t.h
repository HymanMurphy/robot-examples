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

#ifndef _ADDRESS_SPACE_UTILITIES_T_
#define _ADDRESS_SPACE_UTILITIES_T_

#include "uasdk_includes.h"
#include "opcua_message_security_mode_t.h"
#include "inode_t.h"
#include "attribute_id_mask_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{

class IObjectNode_t;
class IObjectTypeNode_t;
class IViewNode_t;
class IMethodNode_t;
class IVariableNode_t;
class IVariableTypeNode_t;
class IDataTypeNode_t;
class IReferenceTypeNode_t;
class INode_t;
class IAddressSpace_t;

class Range_t;
class Guid_t;
class StatusCode_t;

/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief AddressSpaceUtilities_t
*
* AddressSpaceUtilities_t class.
*
*/
class AddressSpaceUtilities_t : public Allocatable_t, public IRefCount_t
{
public:
  typedef enum
  {
    ref_type_null = 0,
    ref_type_References = 31,
    ref_type_NonHierarchicalReferences = 32,
    ref_type_HierarchicalReferences = 33,
    ref_type_HasChild = 34,
    ref_type_Organizes = 35,
    ref_type_HasEventSource = 36,
    ref_type_HasModellingRule = 37,
    ref_type_HasEncoding = 38,
    ref_type_HasDescription = 39,
    ref_type_HasTypeDefinition = 40,
    ref_type_GeneratesEvent = 41,
    ref_type_Aggregates = 44,
    ref_type_HasSubtype = 45,
    ref_type_HasProperty = 46,
    ref_type_HasComponent = 47,
    ref_type_HasNotifier = 48,
    ref_type_HasOrderedComponent = 49,
    ref_type_HasModelParent = 50,
    ref_type_FromState = 51,
    ref_type_ToState = 52,
    ref_type_HasCause = 53,
    ref_type_HasEffect = 54,
    ref_type_HasHistoricalConfiguration = 56,
    ref_type_HasHistoricalEventConfiguration = 57,
    ref_type_HasSubStateMachine = 117,
    ref_type_HasEventHistory = 118,
    ref_type_AlwaysGeneratesEvent = 3065,
    ref_type_HasTrueSubState = 9004,
    ref_type_HasFalseSubState = 9005,
    ref_type_HasCondition = 9006,
    ref_type_end
  } ReferenceType_t;

private:

  /*****************************************************************************/
  /** This function overloads the "=" assignment operator.
   *
   * @param[in] AddressSpaceUtilities_t const &
   * AddressSpaceUtilities_t object which needs to assign.
   *
   * @return
   * returns class object type.
   */

  AddressSpaceUtilities_t& operator=(AddressSpaceUtilities_t const &);

  //*****************************************************************************/
  /** Function used to check whether value to be written is actually in range
  *
  * @param[in] range
  * instrument range of the node.
  *
  * @param[in] value
  * value to be written
  *
  * @param[out] result
  * status of the range check
  *
  * @return
  * true if it is in range. false otherwise
  */
  template<typename T>
  static bool IsInRange(const Range_t& range, const BaseDataType_t& value, Status_t& result);

  /*****************************************************************************/
  /** Copy constructor.
   *
   * @param[in] AddressSpaceUtilities_t const &
   * AddressSpaceUtilities_t object which needs to copy.
   *
   * @return
   * returns class object type.
   */
  AddressSpaceUtilities_t(AddressSpaceUtilities_t const &);
  AddressSpaceUtilities_t();

public:

  /*****************************************************************************/
  /** This function is used for Downcast
   *
   * @param[in] node
   * Node which needs to convert to   derived class type.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  template<typename T> static IntrusivePtr_t<T> NodeDownCast(INode_t& node)
  {
    return RuntimeCast<T* >(node);
  }

  /*****************************************************************************/
  /** This const function is used for Downcasting
   *
   * @param[in] node
   * Node which needs to convert to derived class type.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  template<typename T> static IntrusivePtr_t<const T> NodeDownCast(const INode_t& node)
  {
    return RuntimeCast<const T* >(node);
  }

  /*****************************************************************************/
  /** This function used to check the transport security.
   *
   * @param[in] policy
   * Security policy type.
   *
   * @param[in] mode
   * Message security mode.
   *
   * @return
   * returns boolean status.
   */
  static bool IsTransportSecure(SecurityPolicy_t policy, MessageSecurityMode_t::Enum_t mode)
  {
    return ((policy > SECURITY_POLICY_NONE)
        && (mode == MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGNANDENCRYPT));
  }

  /*****************************************************************************/
  /** This function used to check is class A type is  child of class B.
   *
   * @param[in] refTypeA
   * Child class.
   *
   * @param[in] refTypeB
   * Parent class.
   *
   * @param[in] addressSpace
   * IAddressSpace_t type.
   *
   * @return
   * returns boolean status.
   */

  static bool IsAaChildOfB(const NodeId_t& refTypeA, const NodeId_t& refTypeB, const IAddressSpace_t& addressSpace);

  /*****************************************************************************/
  /** Function generates the numeric node id
   *
   * @param[in] namespaceIndex
   * Index value.
   *
   * @param[out] nodeIdentifier
   * node identifier.
   *
   * @param[out] result
   * generated numeric node id
   *
   * @return
   * returns the status of the operation.
   *
   */
  static Status_t GenerateNumericNodeId(const uint16_t namespaceIndex, const uint32_t nodeIdentifier, IntrusivePtr_t<const NodeId_t>& result);

	/*****************************************************************************/
	/** Function generates unique numeric identifier
	*
	* @param[in] namespaceIndex
	* Index value.
	*
	* @param[in] addressSpace
	* addressSpace object.
	*
	* @return
	* returns the numeric identifier
	*
	*/
	static uint32_t GenerateUniqueNumericIdentifier(const uint16_t namespaceIndex, IntrusivePtr_t<IAddressSpace_t>& addressSpace);

  /*****************************************************************************/
  /** Function generates the String NodeId
   *
   * @param[in] namespaceIndex
   * Index value.
   *
   * @param[in] nodeIdentifier
   * node identifier.
   *
   * @param[out] result
   * generated numeric node id
   *
   * @return
   * returns the status of the operation.
   *
   */
  static Status_t GenerateStringNodeId(const uint16_t namespaceIndex, const String_t& nodeIdentifier, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** Function generates the GUID node id
   *
   * @param[in] namespaceIndex
   * Index value.
   *
   * @param[out] result
   * generated Guid node id
   *
   * @return
   * returns the status of the operation.
   *
   */
  static Status_t GenerateGuidNodeId(const uint16_t namespaceIndex, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** Function generates the GUID node id
   *
   * @param[in] namespaceIndex
   * Index value.
   *
   * @param[in] id
   * node id
   *
   * @param[out] result
   * generated Guid node id
   *
   * @return
   * returns the status of the operation.
   *
   */
  static Status_t GenerateGuidNodeId(const uint16_t namespaceIndex, const uint8_t* id_, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** Function generates the GUID node id
  *
  * @param[in] namespaceIndex
  * Index value.
  *
  * @param[in] id
  * node id
  *
  * @param[out] result
  * generated Guid node id
  *
  * @return
  * returns the status of the operation.
  *
  */
  static Status_t GenerateGuidNodeId(const uint16_t namespaceIndex, const Guid_t& guid, IntrusivePtr_t<const NodeId_t>& result);

	/*****************************************************************************/
	/** Function generates unique guid identifier
	*
	* @param[in] namespaceIndex
	* Index value.
	*
	* @param[in] addressSpace
	* addressSpace object.
	*
	* @param[out] guid
	* the guid object
	*
	* @return
	* returns the status of the operation
	*
	*/
	static Status_t GenerateUniqueGuidIdentifier(const uint16_t namespaceIndex, IntrusivePtr_t<IAddressSpace_t>& addressSpace, Guid_t& guid);

  /*****************************************************************************/
  /** Function generates opaque node id.
   *
   * @param[in] namespaceIndex
   * Index value.
   *
   * @param[out] result
   * generated Opa queue node id
   *
   * @return
   * returns the status of the operation.
   *
   */
  static Status_t GenerateOpaqueNodeId(const uint16_t namespaceIndex, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** Function generates opaque node id.
   *
   * @param[in] namespaceIndex
   * Index value.
   *
   * @param[in] id
   * node id
   *
   * @param[out] result
   * generated Opa queue node id
   *
   * @return
   * returns the status of the operation.
   *
   */
  static Status_t GenerateOpaqueNodeId(const uint16_t namespaceIndex, const ByteString_t& id_, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** This function used to Create HasTypeDefinition reference.
   *
   * @param[in] addressSpace
   * IAddressSpace_t object.
   *
   * @param[in] node
   * INode_t object.
   *
   * @param[in] hasTypeDefinitionId
   * Type Definition Id for the node
   *
   * @return
   * returns status of the operation.
   */
  static Status_t CreateHasTypeDefintion(IAddressSpace_t& addressSpace, IntrusivePtr_t<INode_t> node, uint32_t hasTypeDefinitionId);

  /*****************************************************************************/
  /** This function used to Create Reference.
   *
   * @param[in] addressSpace
   * IAddressSpace_t object.
   *
   * @param[in] sourceNode
   * INode_t sourceNode reference.
   *
   * @param[out] targetNode
   * INode_t targetNode reference.
   *
   * @param[in] referenceTypeId
   * reference type id index.
   *
   * @return
   * returns status of the operation.
   */
  static Status_t CreateReference(IAddressSpace_t& addressSpace,
                                  IntrusivePtr_t<INode_t> sourceNode,
                                  IntrusivePtr_t<INode_t> targetNode,
                                  uint32_t referenceTypeId);

  /*****************************************************************************/
  /** This function used to Create Reference.
  *
  * @param[in] addressSpace
  * IAddressSpace_t object.
  *
  * @param[in] sourceNode
  * INode_t sourceNode reference.
  *
  * @param[out] targetNode
  * INode_t targetNode reference.
  *
  * @param[in] referenceTypeId
  * reference type id index.
  *
  * @param[in] viewId
  * view ID
  *
  * @return
  * returns status of the operation.
  */
  static Status_t CreateReference(IAddressSpace_t& addressSpace,
                                  IntrusivePtr_t<INode_t> sourceNode,
                                  IntrusivePtr_t<INode_t> targetNode,
                                  uint32_t referenceTypeId,
                                  IntrusivePtr_t<const NodeId_t>& viewId);

  /*****************************************************************************/
  /** This function used to Create Reference.
  *
  * @param[in] addressSpace
  * IAddressSpace_t object.
  *
  * @param[in] sourceNode
  * INode_t sourceNode reference.
  *
  * @param[out] targetNode
  * INode_t targetNode reference.
  *
  * @param[in] referenceTypeId
  * reference type id index.
  *
  * @return
  * returns status of the operation.
  */
  static Status_t CreateSlowReference(IAddressSpace_t& addressSpace,
    IntrusivePtr_t<const NodeId_t> sourceNodeId,
    IntrusivePtr_t<const NodeId_t> targetNodeId,
    uint32_t referenceTypeId);

  /*****************************************************************************/
  /** This function used to Create Reference.
  *
  * @param[in] addressSpace
  * IAddressSpace_t object.
  *
  * @param[in] sourceNode
  * INode_t sourceNode reference.
  *
  * @param[out] targetNode
  * INode_t targetNode reference.
  *
  * @param[in] referenceTypeId
  * reference type id index.
  *
  * @param[in] viewId
  * view ID
  *
  * @return
  * returns status of the operation.
  */
  static Status_t CreateSlowReference(IAddressSpace_t& addressSpace,
    IntrusivePtr_t<const NodeId_t> sourceNodeId,
    IntrusivePtr_t<const NodeId_t> targetNodeId,
    uint32_t referenceTypeId,
    IntrusivePtr_t<const NodeId_t>& viewId);

  /*****************************************************************************/
    /** This function is used to get the type definition.
     *
     * @param[in] node
     * INode_t object which needs to be copy.
     *
     * @param[in] addressSpace
     * IAddressSpace_t object.
     *
     * @param[out] result
     * the object which hold the type definition.
     *
     * @return
     * returns status of the operation..
     */
  static Status_t GetTypeDefinition(const INode_t& node, const IAddressSpace_t& addressSpace, IntrusivePtr_t<NodeId_t>& result);

  /*****************************************************************************/
  /** This function is used to get the property of the node
   *
   * @param[in] node
   * const INode_t object
   *
   * @param[in] addressSpace
   * const IAddressSpace_t object which contains all nodes.
   *
   * @param[in] browseName
   * const String_t which needs to be compare.
   *
   * @param[out] result
   * Resultant variable which gets the property of otehr node .
   *
   * @return
   * returns status of the operation..
   */
  static Status_t GetProperty(const INode_t& node, const IAddressSpace_t& addressSpace, const String_t& browseName, IntrusivePtr_t<const IVariableNode_t>& result);

  /*****************************************************************************/
  /** This function is used for getting property of a node
   *
   * @param[in] node
   * const INode_t object
   *
   * @param[in] addressSpace
   * IAddressSpace_t object which contains all nodes.
   *
   * @param[in] browseName
   * const String_t which needs to be compare.
   *
   * @param[out] result
   * Resultant variable which gets the property of otehr node .
   *
   * @return
   * returns status of the operation..
   */
  static Status_t GetProperty(const INode_t& node, IAddressSpace_t& addressSpace, const String_t& browseName, IntrusivePtr_t<IVariableNode_t>& result);

	/*****************************************************************************/
	/** This function is used to get the node with given referenceType from the addressSpace
	*
	* @param[in] node
	* const INode_t object
	*
	* @param[in] addressSpace
	* const IAddressSpace_t object which contains all nodes.
	*
	* @param[in] browseName
	* const String_t which needs to be compare.
	*
	* @param[out] result
	* Resultant variable which gets the property of other node .
	*
	* @return
	* returns status of the operation..
	*/
	static Status_t GetNodeWithReferenceType(const INode_t& node, const IAddressSpace_t& addressSpace, const String_t& browseName, uint32_t referenceType, IntrusivePtr_t<const INode_t>& result);

	/*****************************************************************************/
	/** This function is used to get the node with given referenceType from the addressSpace
	*
	* @param[in] node
	* const INode_t object
	*
	* @param[in] addressSpace
	* const IAddressSpace_t object which contains all nodes.
	*
	* @param[in] browseName
	* const String_t which needs to be compare.
	*
	* @param[out] result
	* Resultant variable which gets the property of otehr node .
	*
	* @return
	* returns status of the operation..
	*/
	static Status_t GetNodeWithReferenceType(const INode_t& node, IAddressSpace_t& addressSpace, const String_t& browseName, uint32_t referenceType, IntrusivePtr_t<INode_t>& result);

  /*****************************************************************************/
  /** This function is used to get the reference with given referenceType from the addressSpace
  *
  * @param[in] node
  * const INode_t object
  *
  * @param[in] referenceType
  * type of reference to be found
  *
  * @param[in] forwardReference
  * If forwardReference is false then inverse reference of the given referenceType will be returned, else the forward reference will be returned.
  *
  * @param[out] result
  * const Resultant reference.
  *
  * @return
  * returns status of the operation..
  */
  static Status_t GetReference(const INode_t& node, uint32_t referenceType, bool forwardReference, IntrusivePtr_t<const IReference_t>& result);

  /*****************************************************************************/
  /** This function is used to get the reference with given referenceType from the addressSpace
  *
  * @param[in] node
  * const INode_t object
  *
  * @param[in] referenceType
  * type of reference to be found
  *
  * @param[in] forwardReference
  * If forwardReference is false then inverse reference of the given referenceType will be returned, else the forward reference will be returned.
  *
  * @param[out] result
  * Resultant reference.
  *
  * @return
  * returns status of the operation..
  */
  static Status_t GetReference(const INode_t& node, uint32_t referenceType, bool forwardReference, IntrusivePtr_t<IReference_t>& result);



 /*****************************************************************************/
 /** This function is used to gets target node
  *
  * @param[in] node
  * const INode_t object which gets references status.
  *
  * @param[in] addressSpace
  * IAddressSpace_t object which contains all nodes..
  *
  * @param[in] referenceTypeId
  * uint32_t object which needs to check for reference type.
  *
  * @return
  * returns target node..
  */
  static IntrusivePtr_t<const INode_t> GetTarget(const INode_t& node, const IAddressSpace_t& addressSpace, uint32_t referenceTypeId);

  /*****************************************************************************/
  /** This function is used to get target node
   *
   * @param[in] node
   * const INode_t object
   *
   * @param[in] addressSpace
   * IAddressSpace_t object
   *
   * @param[in] referenceTypeId
   * Reference type id
   *
   * @param[out] isForward
   * is reference forward information
   *
   * @return
   * returns const target node. 
   */
  static IntrusivePtr_t<const INode_t> GetTarget(const INode_t& node, const IAddressSpace_t& addressSpace,
                                           uint32_t referenceTypeId, bool isForward);

  /*****************************************************************************/
  /** This function is used to get target node
  *
  * @param[in] node
  * const INode_t object
  *
  * @param[in] addressSpace
  * IAddressSpace_t object
  *
  * @param[in] referenceTypeId
  * Reference type id
  *
  * @param[out] isForward
  * is reference forward information
  *
  * @return
  * returns non-const target node.
  */
  static IntrusivePtr_t<INode_t> GetTarget(const INode_t& node, IAddressSpace_t& addressSpace,
    uint32_t referenceTypeId, bool isForward);

  /*****************************************************************************/
  /** This function is used to gets target nodes
  *
  * @param[in] node
  * const INode_t object which gets references status.
  *
  * @param[in] addressSpace
  * IAddressSpace_t object which contains all nodes..
  *
  * @param[in] referenceTypeId
  * uint32_t object which needs to check for reference type.
  *
  * @param[in] listOfTargetNodes
  * list of target nodes.
  *
  * @return
  * returns status of the operation
  */
  static Status_t GetTargets(const INode_t& node, const IAddressSpace_t& addressSpace, uint32_t referenceTypeId, IntrusiveList_t<const INode_t>& listOfTargetNodes);

  /*****************************************************************************/
  /** This function is used to get target nodes
  *
  * @param[in] node
  * const INode_t object
  *
  * @param[in] addressSpace
  * IAddressSpace_t object
  *
  * @param[in] referenceTypeId
  * Reference type id
  *
  * @param[out] isForward
  * is reference forward information
  *
  * @param[in] listOfTargetNodes
  * list of target nodes.
  *
  * @return
  * returns status of the operation
  */
  static Status_t GetTargets(const INode_t& node, const IAddressSpace_t& addressSpace,
    uint32_t referenceTypeId, bool isForward, IntrusiveList_t<const INode_t>& listOfTargetNodes);

  //*****************************************************************************/
  /** Function used to check whether value to be written is actually in range
  *
  * @param[in] range
  * instrument range of the node.
  *
  * @param[in] value
  * value to be written
  *
  * @return
  * status of the operation
  * If status is OpcUa_Good, then value is in range and can be written to node
  */
  static Status_t RangeCheck(const Range_t& range, const BaseDataType_t& value);

  /*****************************************************************************/
  /** This function used to check whether the attributes are present or not.
   *
   * @param[in] attributeId
   * Attribute ID to be check in the node class.
   *
   * @param[in] nodeClass
   * NodeClass_t enum object.
   *
   * @return
   * returns boolean status
   */

  static bool IsAttributePresent(AttributeId_t::Enum_t attributeId, NodeClass_t::Enum_t nodeClass);

 /*****************************************************************************/
 /** This function used to read attributes synchronously.
  *
  * @param[in] node
  * node which used to copy to other node.
  *
  * @param[in] attributeId
  * Attribute id which needs to read synchronously.
  *
  * @param[in] userPermissions
  * IUserPermissions_tm is used for user write mask operation.
  *
  * @param[in] locales
  * array of string objects.
  *
  * @param[in] maxAge
  * Maximum age unsigned integer value.
  *
  * @param[in] timeoutHint
  * Timeout hint value in unsigned integer range.
  *
  * @param[in] timestamps
  * Time stamps.
  *
  * @param[in] indexRange
  * Array index range.
  *
  * @param[out] result
  * Output of read attributes will be stored in DataValue_t object.
  *
  * @return
  * returns boolean status
  */
  static Status_t ReadNodeAttributeSynchronously(
    const INode_t& node,
    AttributeId_t::Enum_t attributeId,
    const IUserPermissions_t& userPermissions,
    const ArrayUA_t<String_t>& locales,
    uint32_t maxAge,
    uint32_t timeoutHint,
    TimestampsToReturn_t::Enum_t timestamps,
    const Array_t<IndexRange_t>& indexRange,
    DataValue_t& result);

  /*****************************************************************************/
  /** This function used to remove all node references.
   *
   * @param[in] node
   * Node which needs to remove the references in from the address space.
   *
   * @param[out] addressSpace
   * addressSpace which contains all node references.
   *
   * @return
   * returns boolean status
   */
  static Status_t RemoveAllInverseReferences(IntrusivePtr_t<INode_t> node, IAddressSpace_t& addressSpace);

  /*****************************************************************************/
  /** Checks if a method is a component of a node.
  *
  * @param[in] method
  * The method concerned.
  *
  * @param[in] node
  * The object or object type concerned.
  *
  * @param[in] addressSpace
  * addressSpace which contains all node references.
  *
  * @return
  * returns boolean status
  */
  static bool IsMethodAComponentOfObject(const IMethodNode_t& method, const INode_t& node, const IAddressSpace_t& addressSpace);

  /*****************************************************************************/
  /** Checks if a method is a component of a given node or its parent nodes till the input parentId.
  *
  * @param[in] method
  * The method concerned.
  *
  * @param[in] node
  * The object or object type concerned.
  *
  * @param[in] addressSpace
  * addressSpace which contains all node references.
  *
  * @param[in] loopParent
  * loop the parent if the flag is true.
  *
  * @param[in] parentId
  * parentId is the id till which the loop should be executed.
  *
  * @return
  * returns boolean status
  */
  static bool IsMethodAComponentOfObjectOrParent(const IMethodNode_t& method, const INode_t& object, const IAddressSpace_t& addressSpace, bool loopParent, uint32_t parentId);

  /*****************************************************************************/
  /** Checks if a method is a component of a node.
  *
  * @param[in] inputArguments
  * The inputArguments to validate.
  *
  * @param[in] method
  * The method concerned.
  *
  * @param[in] addressSpace
  * addressSpace which contains all node references.
  *
  * @param[out] inputArgumentResults
  * Results are populated if the return code is bad.
  *
  * @return
  * Result of the operation
  */
  static Status_t ValidateInputArguments(
    const ArrayUA_t<BaseDataType_t>& inputArguments,
    const IMethodNode_t& method,
    const IAddressSpace_t& addressSpace,
    ArrayUA_t<StatusCode_t>& inputArgumentResults);

  template<typename T>
  static Status_t CastInputArgument(
    const BaseDataType_t& base,
    IntrusivePtr_t<T>& concrete);

  template<typename A>
  static Status_t CastInputArguments(
    const ArrayUA_t<BaseDataType_t>& inputArguments,
    IntrusivePtr_t<A>& arg0);

  template<typename A, typename B>
  static Status_t CastInputArguments(
    const ArrayUA_t<BaseDataType_t>& inputArguments,
    IntrusivePtr_t<A>& arg0,
    IntrusivePtr_t<B>& arg1);

  template<typename A, typename B, typename C>
  static Status_t CastInputArguments(
    const ArrayUA_t<BaseDataType_t>& inputArguments,
    IntrusivePtr_t<A>& arg0,
    IntrusivePtr_t<B>& arg1,
    IntrusivePtr_t<C>& arg2);

  template<typename A, typename B, typename C, typename D>
  static Status_t CastInputArguments(
    const ArrayUA_t<BaseDataType_t>& inputArguments,
    IntrusivePtr_t<A>& arg0,
    IntrusivePtr_t<B>& arg1,
    IntrusivePtr_t<C>& arg2,
    IntrusivePtr_t<D>& arg3);


};

template<typename T>
Status_t uasdk::AddressSpaceUtilities_t::CastInputArgument(const BaseDataType_t& base, IntrusivePtr_t<T>& concrete)
{
  concrete = RuntimeCast< T* >(base);
  if(!concrete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  return OpcUa_Good;
}

template<typename A, typename B, typename C, typename D>
Status_t uasdk::AddressSpaceUtilities_t::CastInputArguments(const ArrayUA_t<BaseDataType_t>& inputArguments, IntrusivePtr_t<A>& arg0, IntrusivePtr_t<B>& arg1, IntrusivePtr_t<C>& arg2, IntrusivePtr_t<D>& arg3)
{
  uint32_t size = inputArguments.Size();
  if(size != 4)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  arg0 = RuntimeCast< A* >(*inputArguments[0]);
  if(!arg0.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  arg1 = RuntimeCast< B* >(*inputArguments[1]);
  if(!arg1.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  arg2 = RuntimeCast< C* >(*inputArguments[2]);
  if(!arg2.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  arg3 = RuntimeCast< D* >(*inputArguments[3]);
  if(!arg3.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  return OpcUa_Good;
}

template<typename A, typename B, typename C>
Status_t uasdk::AddressSpaceUtilities_t::CastInputArguments(const ArrayUA_t<BaseDataType_t>& inputArguments, IntrusivePtr_t<A>& arg0, IntrusivePtr_t<B>& arg1, IntrusivePtr_t<C>& arg2)
{
  uint32_t size = inputArguments.Size();
  if(size != 3)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  arg0 = RuntimeCast< A* >(*inputArguments[0]);
  if(!arg0.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  arg1 = RuntimeCast< B* >(*inputArguments[1]);
  if(!arg1.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  arg2 = RuntimeCast< C* >(*inputArguments[2]);
  if(!arg2.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  return OpcUa_Good;
}

template<typename A, typename B>
Status_t uasdk::AddressSpaceUtilities_t::CastInputArguments(const ArrayUA_t<BaseDataType_t>& inputArguments, IntrusivePtr_t<A>& arg0, IntrusivePtr_t<B>& arg1)
{
  uint32_t size = inputArguments.Size();
  if(size != 2)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  arg0 = RuntimeCast< A* >(*inputArguments[0]);
  if(!arg0.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  arg1 = RuntimeCast< B* >(*inputArguments[1]);
  if(!arg1.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  return OpcUa_Good;
}

template<typename A>
Status_t uasdk::AddressSpaceUtilities_t::CastInputArguments(const ArrayUA_t<BaseDataType_t>& inputArguments, IntrusivePtr_t<A>& arg0)
{
  uint32_t size = inputArguments.Size();
  if(size != 1)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  arg0 = RuntimeCast< A* >(*inputArguments[0]);
  if(!arg0.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  return OpcUa_Good;
}

/** @} */

}

#endif // _ADDRESS_SPACE_UTILITIES_T_
