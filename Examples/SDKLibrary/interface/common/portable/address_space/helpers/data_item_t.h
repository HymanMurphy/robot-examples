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

#ifndef _DATA_ITEM_T_
#define _DATA_ITEM_T_

#include "base_data_variable_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "browse_names_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief DataItem_t
*
* A class that represents a DataItem_t in the addressSpace.
*
*/
class DataItem_t : public BaseDataVariable_t
{
  private:
    /*****************************************************************************/
    /** This function checks for property allowance for data item.
     *
     * @param[in] node
     * IVariableNode_t node to be check for the property allowance.
     *
     * @return
     * returns boolean status
     */
    static bool IsPropertyAllowed(IntrusivePtr_t<const IVariableNode_t> node);

    /*****************************************************************************/
    /** This function Create DataItem
    *
    * @param[in] node_
    * node to be created as DataItem
    *
    * @param[in] addressSpace_
    * pointer to address space where node has to be created
    *
    * @param[in] result
    * status of the operation
    *
    * An intrusive reference counting Boost-style smart pointer to the
    * DataItem. The caller must test the pointer before dereferencing it.
    */
    static IntrusivePtr_t<DataItem_t> CreateDataItem(IntrusivePtr_t<IVariableNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result);

  protected:

    DataItem_t();

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
    static Status_t CreatePropertyAndAssignValue(DataItem_t& dataItem,
                                                 uint32_t numericId,
                                                 const char* browseName_,
                                                 uint32_t dataTypeId,
                                                 IntrusivePtr_t<BaseDataType_t> destinationValue,
                                                 const BaseDataType_t& sourceValue,
                                                 IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
  /** This function deletes properties.
   *
   * @param[in] dataItem
   * data item which is to be delete.
   *
   */

    static void DeleteProperties(DataItem_t& dataItem);

  public:
    virtual ~DataItem_t();

    /*
     * Properties
     */
  /*****************************************************************************/
  /** This function creates Definition property for data item.
   *
   * @param[in] value
   * value which is to be assign.
   *
   *
   * @return
   * returns status of the operation.
   */
    Status_t CreateDefinitionProperty(const String_t& value);
  /*****************************************************************************/
  /** This function creates Definition property for data item.
   *
   * @param[in] nodeIdentifier
   * node identifier.
   *
   * @return
   * returns status of the operation.
   */
    Status_t CreateDefinitionProperty(uint32_t nodeIdentifier, const String_t& value);

  /*****************************************************************************/
  /** This function used to get definition property node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
    IntrusivePtr_t<IVariableNode_t> DefinitionNode(void);

  /*****************************************************************************/
  /** This function used to get the Definition property node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
    IntrusivePtr_t<const IVariableNode_t> DefinitionNode(void) const;

  /*****************************************************************************/
  /** This function used to get the value of Definition property
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
    IntrusivePtr_t<const String_t> GetDefinitionValue(Status_t& result);

  /*****************************************************************************/
  /** This function used to set the defintion property value
   *
   * @param[in/out] value
   * value which is to be create the node definition.
   *
   * @return
   * returns  status of the operation.
   */
    Status_t SetDefinitionValue(const String_t& value);

  /*****************************************************************************/
  /** This function creates ValuePrecision property
   *
   * @param[in] value
   * value which is to be initialize the source double value.
   *
   * @return
   * returns  status of the operation.
   */
    Status_t CreateValuePrecisionProperty(double value);

  /*****************************************************************************/
  /** This function creates ValuePrecision property 
   *
   * @param[in] nodeIdentifier
   * node identifier.
   *
   * @param[in] value
   * value which is to be initialize the source double value.
   *
   * @return
   * returns  status of the operation.
   */
    Status_t CreateValuePrecisionProperty(uint32_t nodeIdentifier, double value);

  /*****************************************************************************/
  /** This function is used to get ValuePrecision node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */

  IntrusivePtr_t<IVariableNode_t> ValuePrecisionNode(void);

  /*****************************************************************************/
  /** This const function calls the get property node function to get the value.
   *
   * @return
   * returns  const IVariableNode_t value.
   */

  IntrusivePtr_t<const IVariableNode_t> ValuePrecisionNode(void) const;

  /*****************************************************************************/
  /** This function gets ValuePrecision property value.
   *
   * @param[out]result
   * gets the precision value.
   *
   * @return
   * returns  status of the operation.
   */
    Status_t GetValuePrecisionValue(double& result);

  /*****************************************************************************/
  /** This function sets the ValuePrecision value.
   *
   * @param[out]value
   * value which is to be set.
   *
   * @return
   * returns  status of the operation.
   */
    Status_t SetValuePrecisionValue(double value);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
   *  DataItem node.
   *
   * @param[in] nodeId
   * Variable node id which needs to find in the address space.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * node value
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
    static IntrusivePtr_t<DataItem_t> Get(const NodeId_t& nodeId,
                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                          Status_t& result);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
   *  DataItem node.
   *
   * @param[in] nodeId
   * const Variable node id which needs to find in the address space.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * node value
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
    static IntrusivePtr_t<DataItem_t> Get(IntrusivePtr_t<IVariableNode_t>& node,
                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                          Status_t& result);

  /*****************************************************************************/
  /** This Function used to create DataItem with Numeric Id.
   *
   * @param[in] namespaceIndex
   * namespace Index.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] browseName
   * Browse Name.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * DataItem. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<DataItem_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                          uint32_t nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          Status_t& result);

  /*****************************************************************************/
  /** This Function is used to create DataItem node with sting Id.
   *
   * @param[in] namespaceIndex
   * namespace Index.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] browseName
   * Browse Name.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * DataItem. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<DataItem_t> CreateWithStringId(uint16_t namespaceIndex,
                                                         const String_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         Status_t& result);

  /*****************************************************************************/
  /** This Function used to create DataItem with GUID
   *
   * @param[in] namespaceIndex
   * namespace Index.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] browseName
   * Browse Name.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * DataItem. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<DataItem_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                       const Guid_t& nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       Status_t& result);

  /*****************************************************************************/
  /** This Function is used to DataItem with Opaque item
   *
   * @param[in] namespaceIndex
   * namespace Index.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] browseName
   * Browse Name.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * DataItem. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<DataItem_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                         const ByteString_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         Status_t& result);

};

template<typename T>
IntrusivePtr_t<DataItem_t> DataItem_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                           uint32_t nodeIdentifier,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           const String_t& browseName,
                                                           Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_DataItemType, -2, result);
  return DataItem_t::CreateDataItem(node_, addressSpace_, result);
}

template<typename T>
IntrusivePtr_t<DataItem_t> DataItem_t::CreateWithStringId(uint16_t namespaceIndex,
                                                          const String_t& nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_DataItemType, -2, result);
  return DataItem_t::CreateDataItem(node_, addressSpace_, result);
}

template<typename T>
IntrusivePtr_t<DataItem_t> DataItem_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                        const Guid_t& nodeIdentifier,
                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                        const String_t& browseName,
                                                        Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_DataItemType, -2, result);
  return DataItem_t::CreateDataItem(node_, addressSpace_, result);
}

template<typename T>
IntrusivePtr_t<DataItem_t> DataItem_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                          const ByteString_t& nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_DataItemType, -2, result);
  return DataItem_t::CreateDataItem(node_, addressSpace_, result);
}

/** @} */

}

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif // _DATA_ITEM_T_
