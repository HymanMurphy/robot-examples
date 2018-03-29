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

#ifndef _ADDRESS_SPACE_MODELER_T_
#define _ADDRESS_SPACE_MODELER_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_SERVER > 0) && (UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "iserver_configuration_t.h"
#include "inode_value_attribute_reader_writer_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_localized_text_t.h"
#include "base_object_t.h"
#include "inode_t.h"
#include "opcua_node_id_t.h"
#include "method_t.h"
#include "utilities.h"
#include "base_data_variable_t.h"

namespace uasdk
{

class NodeStandardIdMap_t : public IRefCount_t, public Allocatable_t
{
public:
  uint32_t standardId;
  IntrusivePtr_t<HelperBase_t> node;
};

/*****************************************************************************/
/** \brief AddressSpaceModeler_t
*
* This class is used for modeling a given condition in the address space
*
*/
class AddressSpaceModeler_t : public Allocatable_t, public IRefCount_t
{

private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> rootNodeId
  * rootNodeId is the root node which is to be modelled in the address space
  */
  IntrusivePtr_t<NodeId_t> rootNodeId;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IAddressSpace_t> addressSpace
  * addressSpace instance
  */
  IntrusivePtr_t<IAddressSpace_t> addressSpace;

  /*****************************************************************************/
  /* @var  IntrusiveList_t<NodeStandardIdMap_t> variablesMap
  * variablesMap will contain the list of variables under rootNodeId
  */
  IntrusiveList_t<NodeStandardIdMap_t> variablesMap;

  /*****************************************************************************/
  /* @var  IntrusiveList_t<NodeStandardIdMap_t> methodsMap
  * methodsMap will contain the list of methods under rootNodeId
  */
  IntrusiveList_t<NodeStandardIdMap_t> methodsMap;

  /*****************************************************************************/
  /* @var  IntrusiveList_t<BaseObject_t> objects
  * objects will contain the list of objects under rootNodeId
  */
  IntrusiveList_t<BaseObject_t> objects;

  /*****************************************************************************/
  /** CreateMap()
  *
  * @param[in] node
  * node to be mapped to the standard type Id
  *
  * @param[in] typeNode
  * type node
  *
  * @param[in] list
  * list of NodeStandardIdMap_t
  *
  * @return
  * status of the operation
  */
  Status_t CreateMap(IntrusivePtr_t<HelperBase_t> node, const INode_t& typeNode, IntrusiveList_t<NodeStandardIdMap_t>& list);

  /*****************************************************************************/
  /** GetStandardNodeId()
  *
  * @param[in] node
  * node to be mapped to the standard type Id
  *
  * @param[in] list
  * list of NodeStandardIdMap_t
  *
  * @return
  * type Id
  */
  uint32_t GetStandardNodeId(const INode_t& node, IntrusiveList_t<NodeStandardIdMap_t>& list);

  /*****************************************************************************/
  /** AssignValue()
  *
  * @param[in] value
  * actual value which needs to be updated to the variable node
  *
  * @param[out] node
  * node which has to be updated with the value.
  *
  * @return
  * status of operation.
  */
  Status_t AssignValue(const BaseDataType_t& value, IVariableNode_t& node);

  /*****************************************************************************/
  /** AddArugmentsToMethod()
  *
  * @param[in] methodNode
  * Node which determines what Input and/or Output arguments needs to be added to Method
  *
  * @param[out] method
  * method node to which Input and/or Output arguments to be added
  *
  * @return
  * status of operation.
  */
  Status_t AddArugmentsToMethod(const IMethodNode_t& methodNode, Method_t& method);

  /*****************************************************************************/
  /** CreateVariable()
  *
  * @param[in] parentNode
  * parent node under which node has to be created
  *
  * @param[in] browseName
  * browse name of the variable
  *
  * @param[in] dataType
  * data type of the variable node
  *
  * @param[in] hasTypeDefinitionId
  * has type definition reference id of the variable node
  *
  * @param[in] referenceType
  * reference type with which variable node is referencesd with the condition
  *
  * @param[in] assignReaderWriter
  * boolean flag to identify whether the reader writer has to be set
  *
  * @param[in] readerWriter
  * reader writer object
  *
  * @param[out] result
  * result of the operation
  *
  * @return
  * Intrusive pointer to variable node
  */
  IntrusivePtr_t<IVariableNode_t> CreateVariable(IntrusivePtr_t<INode_t>& parentNode,
    const IVariableNode_t& typeNode,
    uint32_t dataType,
    uint32_t hasTypeDefinitionId,
    uint32_t referenceType,
    bool assignReaderWriter,
    IntrusivePtr_t<INodeValueAttributeReaderWriter_t> readerWriter,
    Status_t& result);

  /*****************************************************************************/
  /** CreateMethod()
  *
  * @param[in] conditionNode
  * Condition node inder which method needs to be created
  *
  * @param[in] addressSpace
  * address space variable
  *
  * @param[in] typeNode
  * type of the method
  *
  * @param[in] referenceType
  * reference type with which variable node is referencesd with the condition
  *
  * @param[in] result
  * status of the operation
  *
  * @return
  * Intrusive pointer to Method node
  */
  IntrusivePtr_t<Method_t> CreateMethod(IntrusivePtr_t<INode_t>& conditionNode,
    IntrusivePtr_t<IAddressSpace_t>& addressSpace,
    const IMethodNode_t& typeNode,
    uint32_t referenceType,
    IntrusivePtr_t<INodeMethodHandler_t>& methodHandler,
    Status_t& result);
	
  /*****************************************************************************/
  /** CreateObject()
  *
  * @param[in] conditionNode
  * Condition node inder which method needs to be created
  *
  * @param[in] addressSpace
  * address space variable
  *
  * @param[in] browseName
  * browse name of the method
  *
  * @param[in] referenceType
  * reference type with which variable node is referencesd with the condition
  *
  * @param[in] result
  * status of the operation
  *
  * @return
  * Intrusive pointer to BaseObject
  */
  IntrusivePtr_t<BaseObject_t> CreateObject(IntrusivePtr_t<INode_t>& conditionNode,
    IntrusivePtr_t<IAddressSpace_t>& addressSpace,
    IntrusivePtr_t<const QualifiedName_t> browseName,
    uint32_t referenceType,
    Status_t& result);

public:

  /*****************************************************************************/
  /** AddressSpaceModeler_t()
  * It is the constructor of the class
  */
  AddressSpaceModeler_t();

  /*****************************************************************************/
  /** ~AddressSpaceModeler_t()
  * It is the descturctor of the class
  */
  virtual ~AddressSpaceModeler_t();

  /*****************************************************************************/
  /** Initialise()
  * this function is used to create condition and update in the condition registrar of the condition is created successfully.
  *
  * @return
  * status of the operation
  */
  Status_t Initialise(IntrusivePtr_t<IAddressSpace_t>& addressSpace_, IntrusivePtr_t<NodeId_t> rootNodeId_);

  /*****************************************************************************/
  /** Clear()
  * Clears the inputs list of variables, objects and methods.
  *
  */
  void Clear();

  /*****************************************************************************/
  /** GetStandardNodeId()
  *
  * @param[in] node
  * node to be mapped to the standard type Id
  *
  * @return
  * type Id
  */
  uint32_t GetStandardNodeId(const INode_t& node);

  /*****************************************************************************/
  /** GetMethodNodeIdFromStandardNodeId()
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
  /** InitialiseValue()
  *
  * @param[in] dataType
  * input datatype
  *
  * @param[out] value
  * updated data value.
  *
  * @return
  * status of operation.
  */
  static Status_t InitialiseValue(uint32_t dataType, IntrusivePtr_t<BaseDataType_t>& value);

  /*****************************************************************************/
  /** ReadValue()
  *
  * @param[in] value
  * data which is read and which has to be updated to the data value
  *
  * @param[in] setSourceTimestamp
  * boolena flag to set the source time stamp or not!
  *
  * @param[in] statusCode
  * status code of the read operation, which has to be updated to the dataValue
  *
  * @param[out] dataValue
  * updated data value from all the inputs.
  *
  * @return
  * status of operation.
  */
  static Status_t ReadValue(const BaseDataType_t& value, bool setSourceTimestamp, uint32_t statusCode, IntrusivePtr_t<DataValue_t>& dataValue);

  /*****************************************************************************/
  /** GetParentBrowseName()
  *
  * This method is going to check the root node id with the node which is passed. If the root node id is
  * not same as input node id, then it will create full browsename for parent. which will be used as Node Id.
  *
  * @param[in] rootNodeId_
  * node Id of the root
  *
  * @param[in] node_
  * node information
  *
  * @param[in] addressSpace_
  * address space
  *
  * @param[out] result
  * browse name of the node.
  *
  * @return
  * status of operation.
  */
  static Status_t GetParentBrowseName(NodeId_t& rootNodeId_, INode_t& node_, IAddressSpace_t& addressSpace_, String_t& result);

  /*****************************************************************************/
  /** AddNodesUsingTypeInformation()
  * This method will add all the objects, variables, methods for a given node based on 
  * the type info avaialble in the address space.
  *
  * @param[in] typeId
  * the typeId for which the nodes needs to be created.
  *
  * @param[in] parentNodeId
  * parentNodeId under which the new node needs to be added
  *
  * @param[in] assignReaderWriter
  * whether to assign readerWriter to a given variable node
  *
  * @param[in] readerWriter
  * readerWriter instance
  *
  * @param[in] methodHandler
  * methodHandler for methods
  *
  * @param[in] baseTypeId
  * the typeId of the parent Node from which the nodes creation should start from.
  *
  * @return
  * status of the operation
  */
  Status_t AddNodesUsingTypeInformation(const NodeId_t& typeId, const NodeId_t& parentNodeId, bool assignReaderWriter, IntrusivePtr_t<INodeValueAttributeReaderWriter_t>& readerWriter, IntrusivePtr_t<INodeMethodHandler_t>& methodHandler, NodeId_t& baseTypeId);
    
};


/** @} */

} // namespace uasdk

#endif  //((UASDK_INCLUDE_SERVER > 0) && (UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _ADDRESS_SPACE_MODELER_T_
