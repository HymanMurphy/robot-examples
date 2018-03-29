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

#ifndef _Y_ARRAY_ITEM_T_H_
#define _Y_ARRAY_ITEM_T_H_

#include "array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_axis_information_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief YArrayItem_t
*
* A class that represents a YArrayItem_t in the address space.
*
*/

class YArrayItem_t : public ArrayItem_t
{
public:

  typedef struct
  {
    ArrayItem_t::MandatoryPropertyValues_t arrayItemProperty;
    AxisInformation_t   axisInformation;
  } MandatoryPropertyValues_t;

  typedef struct
  {
    ArrayItem_t::MandatoryPropertyNumericIds_t arrayItemPropertyNumericId;
    uint32_t axisInformationId;
  } MandatoryPropertyNumericIds_t;

protected:

  YArrayItem_t();

private:

  /*****************************************************************************/
  /**This function Creates y array with mandatory property.
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] mandatoryPropertiesId
   * Mandatory Properties Id to create xy array.
   *
   * @param[in] propertyValues
   * Mandatory Properties Values to createxy array.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<YArrayItem_t> CreateYArrayWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                        const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                        const MandatoryPropertyValues_t& propertyValues,
                                                                        Status_t& result);

  /*****************************************************************************/
  /**This function used to creates y_array property.
   *
   * @param[in] item
   * XYArrayItem_t item.
   *
   * @param[in] propertyIdentifier
   * Property Identifier.
   *
   * @param[in] propertyName
   * property Name.
   *
   * @param[in] PropertyType
   * Property Type.
   *
   * @param[in] value
   * AxisInformation_t value.
   *
   * @param[out] propertyNode
   * IVariableNode_t property Node.
   *
   * @returns
   * returns status of the operation.
   */
  static Status_t CreateProperty(YArrayItem_t& item,
                                 uint32_t propertyIdentifier,
                                 const char* propertyName,
                                 uint32_t propertyType,
                                 const AxisInformation_t& value,
                                 IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
  /**This function used to create YArrayItem
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */

  static IntrusivePtr_t<YArrayItem_t> CreateYArrayItem( IntrusivePtr_t<IVariableNode_t>& node_,
                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                        Status_t& result);

  //*****************************************************************************/
  /**Function used to get the AxisInformation value.
   *
   * @param[in/out] propertyNode
   * IVariableNode_t object.
   *
   * @param[out]result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const AxisInformation_t> GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result);

  void DeleteProperties(YArrayItem_t& yArrayItem);

public:

  virtual ~YArrayItem_t();
  /*
   * Standard Property helpers
   */

  /*****************************************************************************/
  /**This function used to get the XAxisDefintion property node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> XAxisDefinitionNode(void);

  /*****************************************************************************/
  /**This const function used to get the XAxisDefinition node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> XAxisDefinitionNode(void) const;

  /*****************************************************************************/
  /**This function used to get the y array x axis definition value.
   *
   * @param[out] result
   * values which is to be store.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const AxisInformation_t> GetXAxisDefinitionValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to set the XAxisDefinition values.
   *
   * @param[in/out] value
   * values which is to be set.
   *
   * @return
   * returns the status of the operation.
   *
   */
  Status_t SetXAxisDefinitionValue(const AxisInformation_t& value);

  /*
   * Wrapper Functions
   */

  /*****************************************************************************/
  /** Function used to get the node as YArrayItem
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
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<YArrayItem_t> Get(const NodeId_t& nodeId,
                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                          Status_t& result);

  /*****************************************************************************/
  /** Function used to get the node as YArrayItem
   *
   * @param[in] node
   *  The Variable node to retrieve as YArrayItem.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * node value
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<YArrayItem_t> Get(IntrusivePtr_t<IVariableNode_t>& node,
                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                          Status_t& result);

  /*****************************************************************************/
  /** This template function used to create y array item with Numeric Id.
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
   * @param[in] propertyValues
   * MandatoryPropertyValues_t values.
   *
   * @param[in] mandatoryPropertiesId
   * MandatoryPropertyNumericIds_t id.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<YArrayItem_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                          uint32_t nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          const MandatoryPropertyValues_t& propertyValues,
                                                          const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                          Status_t& result);

  /*****************************************************************************/
  /** This template function used to create y array with string Id.
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
   * @param[in] propertyValues
   * MandatoryPropertyValues_t values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
    */
  template<typename T>
  static IntrusivePtr_t<YArrayItem_t> CreateWithStringId(uint16_t namespaceIndex,
                                                         const String_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         const MandatoryPropertyValues_t& propertyValues,
                                                         Status_t& result);

  /*****************************************************************************/
  /** This template function used to create y array with GUID
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
   * @param[in] propertyValues
   * MandatoryPropertyValues_t values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<YArrayItem_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                       const Guid_t& nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       const MandatoryPropertyValues_t& propertyValues,
                                                       Status_t& result);

  /*****************************************************************************/
  /** This template function used to create y array item with opaque Id.
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
   * @param[in] propertyValues
   * MandatoryPropertyValues_t values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * YArrayItem. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<YArrayItem_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                         const ByteString_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         const MandatoryPropertyValues_t& propertyValues,
                                                         Status_t& result);

};

template<typename T>
IntrusivePtr_t<YArrayItem_t> YArrayItem_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                               uint32_t nodeIdentifier,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               const MandatoryPropertyValues_t& propertyValues,
                                                               const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                               Status_t& result)
{

  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<YArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_YArrayItemType, 1, result);

  return YArrayItem_t::CreateYArrayWithMandatoryProperty(node_, addressSpace_, mandatoryPropertiesId, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<YArrayItem_t> YArrayItem_t::CreateWithStringId(uint16_t namespaceIndex,
                                                              const String_t& nodeIdentifier,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              const MandatoryPropertyValues_t& propertyValues,
                                                              Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<YArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_YArrayItemType, 1, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0};
  return YArrayItem_t::CreateYArrayWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<YArrayItem_t> YArrayItem_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                            const Guid_t& nodeIdentifier,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            const String_t& browseName,
                                                            const MandatoryPropertyValues_t& propertyValues,
                                                            Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<YArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_YArrayItemType, 1, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0};
  return YArrayItem_t::CreateYArrayWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<YArrayItem_t> YArrayItem_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                              const ByteString_t& nodeIdentifier,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              const MandatoryPropertyValues_t& propertyValues,
                                                              Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<YArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_YArrayItemType, 1, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0};
  return YArrayItem_t::CreateYArrayWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

/** @} */

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _Y_ARRAY_ITEM_T_H_ */
