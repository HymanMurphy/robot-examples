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

#ifndef _HELPER_BASE_T_
#define _HELPER_BASE_T_

#include "uasdk_includes.h"

#if (UASDK_USE_HELPERS > 0)

#include "allocatable_t.h"
#include "iobject_node_t.h"
#include "iaddress_space_t.h"

namespace uasdk
{

class DateTime_t;
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief HelperBase_t
*
* HelperBase_t class.
*
*/
class HelperBase_t : public Allocatable_t, public virtual IRefCount_t
{
private:
  /*****************************************************************************/
  /** This function used to create qualified name from given string
  *
  * @param[in] name
  * name to be copy into the other object .
  *
  * @param[in] namespaceIndex
  * namespace index .
  *
  * @param[in] result
  * stores the copied name.
  *
  * @return
  * returns status of the operation.
  */
  static Status_t CreateQualifiedName(const String_t& name, uint16_t namespaceIndex, IntrusivePtr_t<const QualifiedName_t>& result);

  /*****************************************************************************/
  /** This function used to create localized text.
  *
  * @param[in] text
  * text to be create.
  *
  * @param[out] result
  * stores the copied localized text.
  *
  * @return
  * returns status of the operation.
  */
  static Status_t CreateLocalizableText(const String_t& text, IntrusivePtr_t<const ILocalizableText_t>& result);

  /*****************************************************************************/
  /** This function used to Convert To Node Id Pointer.
  *
  * @param[in] sourceId
  * source id which is to be convert.
  *
  * @param[out] result
  * stores the converted node id..
  *
  * @return
  * returns status of the operation.
  */
  static Status_t ConvertToNodeIdPointer(const NodeId_t& sourceId, IAddressSpace_t& addressSpace_, IntrusivePtr_t<const NodeId_t>& result);


  /*****************************************************************************/
  /** This function used to Update the Attributes.
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] browseName_
  * browse name.
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] dataTypeId
  * data type id.
  *
  * @param[in] valueRank
  * value Rank.
  *
  * @param[out] result
  * IVariableNode_t variable.
  *
  * @return
  * returns status of the operation.
  */
  static Status_t UpdateAttributes(uint16_t namespaceIndex,
                                   const String_t& browseName_,
                                   INode_t& result);

  /*****************************************************************************/
  /** This function used to Update the Attributes.
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] browseName_
  * browse name.
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] dataTypeId
  * data type id.
  *
  * @param[in] valueRank
  * value Rank.
  *
  * @param[out] result
  * IVariableNode_t variable.
  *
  * @return
  * returns status of the operation.
  */
  static Status_t UpdateAttributes(uint16_t namespaceIndex,
                                   IAddressSpace_t& addressSpace_,
                                   const String_t& browseName_,
                                   uint32_t dataTypeId,
                                   int32_t valueRank,
                                   IntrusivePtr_t<IVariableNode_t>& result);

protected:
  IntrusivePtr_t<INode_t>         node;
  IntrusivePtr_t<IAddressSpace_t> addressSpace;
  bool                            deleteNode;

  HelperBase_t();
  /*****************************************************************************/
  /** Function used to initialize helper base object.
  *
  * @param[in] node_
  * INode_t  value.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object
  *
  */
  void Initialize(IntrusivePtr_t<INode_t> node_, IntrusivePtr_t<IAddressSpace_t> addressSpace_);

  /*****************************************************************************/
  /** Function used to check HasTypeDefinition reference
  *
  * @param[in] node_
  * IVariableNode_t  value.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object
  *
  * @param[in] typeId
  * type id.
  *
  * @return
  * returns the status of the operation
  *
  */
  static Status_t CheckHasTypeDefinition(const INode_t& node, const IAddressSpace_t& addressSpace_, uint32_t typeId);

  /*****************************************************************************/
  /** Function gets the node property.
  *
  * @param[in] addressSpace
  * IAddressSpace_t addressSpace.
  *
  * @param[out] sourceNode
  * const IVariableNode_t node.
  *
  * @param[in] propertyName
  * Name of the property.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  static IntrusivePtr_t<IVariableNode_t> GetPropertyNode(IAddressSpace_t& addressSpace, const INode_t& sourceNode, const char* propertyName);

  /*****************************************************************************/
  /** Function generates the String NodeId
  *
  * @param[in] sourceId
  * Index value.
  *
  * @param[in] propertyName
  * property name.
  *
  * @param[out] result
  * generated string node id
  *
  * @return
  * returns the status of the operation.
  *
  */
  static Status_t GenerateStringNodeId(const NodeId_t& sourceId, const char* propertyName, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** Function generates the Opaque NodeId
  *
  * @param[in] namespaceIndex
  * namespace Index
  *
  * @param[in] data
  * node Id as uint pointer
  *
  * @param[in] lengthOfData
  * length of data
  *
  * @param[in] propertyName
  * property name.
  *
  * @param[out] result
  * generated string node id
  *
  * @return
  * returns the status of the operation.
  *
  */
  static Status_t GenerateOpaqueNodeId(const uint16_t namespaceIndex, const uint8_t* data, const int32_t lengthOfData, const char* propertyName, IntrusivePtr_t<const NodeId_t>& result);

  /*****************************************************************************/
  /** This function creates Object node.
  *
  * @param[in] nodeId
  * node id which needs to create in the address space.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[in] hasTypeReferenceId
  * Type ReferenceId.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<IObjectNode_t> Create(IntrusivePtr_t<const NodeId_t> nodeId,
                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                              const String_t& browseName,
                                              uint32_t hasTypeReferenceId,
                                              Status_t& result);

  /*****************************************************************************/
  /** This function creates Method node.
  *
  * @param[in] nodeId
  * node id which needs to create in the address space.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[in] executable
  * executable.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<IMethodNode_t> CreateMethod(IntrusivePtr_t<const NodeId_t> nodeId,
                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                    const String_t& browseName,
                                                    bool executable,
                                                    Status_t& result);

  /*****************************************************************************/
  /** This function creates variable node.
  *
  * @param[in] nodeId
  * node id which needs to create in the address space.
  *
  * @param[in] dataTypeId
  * data type id
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[in] hasTypeReferenceId
  * Type ReferenceId.
  *
  * @param[in] valueRank
  * Rank value.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<IVariableNode_t> Create(IntrusivePtr_t<const NodeId_t> nodeId,
                                                uint32_t dataTypeId,
                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                const String_t& browseName,
                                                uint32_t hasTypeReferenceId,
                                                int32_t valueRank,
                                                Status_t& result);

  /*****************************************************************************/
  /** This function creates the property
  *
  * @param[in] dataItem
  * data item value.
  *
  * @param[in] numericId
  * numeric id value.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[in] dataTypeId
  * data id type.
  *
  * @param[out] propertyNode
  * node property.
  *
  * @returns
  * returns status of the operation..
  */
  static Status_t CreateProperty(HelperBase_t& sourceNode,
                                 uint32_t numericId,
                                 const char* browseName_,
                                 uint32_t dataTypeId,
                                 IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
  /** This function Create and assign data value
  *
  * @param[in] node_
  * node to be create
  *
  * @param[in] value
  * IVariableNode_t object value.
  *
  * @param[in] sourceTimeStamp_
  * DateTime_t object.
  *
  * @return
  * returns status of the operation.
  */
  static Status_t CreateAndAssignDataValue(IntrusivePtr_t<IVariableNode_t> node_,
                                           IntrusivePtr_t<BaseDataType_t>& value,
                                           DateTime_t& sourceTimeStamp_);

  /*****************************************************************************/
  /** This function creates and assigns value to the data item.
  *
  * @param[in] dataItem
  * data item value.
  *
  * @param[in] numericId
  * numeric id value.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[in] destinationValue
  * value to be assigned from source value.
  *
  * @param[in] sourceValue
  * value to be copy to destination.
  *
  * @param[out] propertyNode
  * node property.
  *
  * @returns
  * returns status of the operation..
  */
  static Status_t CreatePropertyAndAssignValue(HelperBase_t& sourceNode,
                                               uint32_t numericId,
                                               const char* browseName_,
                                               uint32_t dataTypeId,
                                               IntrusivePtr_t<BaseDataType_t> destinationValue,
                                               const BaseDataType_t& sourceValue,
                                               IntrusivePtr_t<IVariableNode_t>& propertyNode);

public:

  virtual ~HelperBase_t();

  /*****************************************************************************/
  /** This function used to hide/unhide the node in the address sapce.
  *
  * @param[in] value
  * set false to unhide
  *
  * @returns
  * returns boolean status of the operation.
  */
  void Hide(bool value);

  /*****************************************************************************/
  /** This function used to remove the DataItem node in the address space
  *
  * @param[in] value
  * set true to delete.
  *
  */
  void RemoveNodesOnDeletion(bool value);

  /*****************************************************************************/
  /** This function used to get the string node id separator
  *
  * @return
  * returns char string.
  *
  */
  static char StringNodeIdSeparator(void);

  /*****************************************************************************/
  /** This function used to set the string node id separator
  *
  * @param[in] separator
  * character which is needs to be separate from the string.
  *
  */
  static void StringNodeIdSeparator(char separator);

  /*****************************************************************************/
  /** This function gets the node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<INode_t> Node(void);
  /*****************************************************************************/
  /** This const function used to get the node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<const INode_t> Node(void) const;
};

/** @} */

} //namespace uasdk

#endif  //UASDK_USE_HELPERS

#endif  //_HELPER_BASE_T_