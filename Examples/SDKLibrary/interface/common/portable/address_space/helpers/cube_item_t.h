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

#ifndef _CUBE_ITEM_T_H_
#define _CUBE_ITEM_T_H_

#include "array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_axis_information_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief CubeItem_t
*
* A class that represents a CubeItem_t in the addressSpace.
*
*/
class CubeItem_t : public ArrayItem_t
{
public:

  typedef struct
  {
    ArrayItem_t::MandatoryPropertyValues_t  arrayItemProperty;
    AxisInformation_t                       xAxisInformation;
    AxisInformation_t                       yAxisInformation;
    AxisInformation_t                       zAxisInformation;
  } MandatoryPropertyValues_t;

  typedef struct
  {
    ArrayItem_t::MandatoryPropertyNumericIds_t  arrayItemPropertyNumericId;
    uint32_t                                    xAxisInformationNumericId;
    uint32_t                                    yAxisInformationNumericId;
    uint32_t                                    zAxisInformationNumericId;
  } MandatoryPropertyNumericIds_t;

protected:
  CubeItem_t();

private:

  /*****************************************************************************/
  /**This function Creates Cube With Mandatory Property.
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] mandatoryPropertiesId
   * Mandatory Properties Id to create cube.
   *
   * @param[in] propertyValues
   * Mandatory Properties Values to create cube.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * CubeItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<CubeItem_t> CreateCubeWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                    const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                    const MandatoryPropertyValues_t& propertyValues,
                                                                    Status_t& result);

  /*****************************************************************************/
   /**This function used to create property.
    *
    * @param[in] cubeItem
    * CubeItem_t object.
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
  static Status_t CreateProperty(CubeItem_t& cubeItem,
                                 uint32_t propertyIdentifier,
                                 const char* propertyName,
                                 uint32_t propertyType,
                                 const AxisInformation_t& value,
                                 IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
   /**This function Creates Cube Item.
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
   * CubeItem. The caller must test the pointer before dereferencing it.
    */

  static IntrusivePtr_t<CubeItem_t> CreateCubeItem( IntrusivePtr_t<IVariableNode_t>& node_,
                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                    Status_t& result);

  /*****************************************************************************/
  /**This function used to Get Axis Information Value.
   *
   * @param[out] propertyNode
   * IVariableNode_t node used to get  Axis Information Value.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * AxisInformation value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const AxisInformation_t> GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result);

  /*****************************************************************************/
   /**This function used to delete the cube properties.
    *
    * @param[in/out] cubeItem
    * item which to be delete.
    *
    */
  void DeleteProperties(CubeItem_t& cubeItem);

public:
  virtual ~CubeItem_t();

  /*****************************************************************************/
  /**This function used to get X Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> XAxisDefinitionNode(void);

  /*****************************************************************************/
  /**This const function used to get X Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> XAxisDefinitionNode(void) const;

  /*****************************************************************************/
  /**This function used to get Y Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> YAxisDefinitionNode(void);

  /*****************************************************************************/
  /**This const function used to get Y Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> YAxisDefinitionNode(void) const;

  /*****************************************************************************/
  /**This function used to get Z Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> ZAxisDefinitionNode(void);

  /*****************************************************************************/
  /**This const function used to get Z Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> ZAxisDefinitionNode(void) const;

  /*****************************************************************************/
  /**This function used to Get X Axis definition value.
   *
   * @param[out]result
   *  X Axis value to be stored.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * AxisInformation value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const AxisInformation_t> GetXAxisDefinitionValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to Set X Axis definition value.
   *
   * @param[in/out]value
   *  X Axis value to be set.
   *
   * @returns
   * status of the operation.
   */
  Status_t SetXAxisDefinitionValue(const AxisInformation_t& value);

  /*****************************************************************************/
   /**This  function used to Get Y Axis definition value.
    *
    * @param[out]result
    *  Y Axis value to be stored.
    *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * AxisInformation value. The caller must test the pointer before dereferencing it.
    */
  IntrusivePtr_t<const AxisInformation_t> GetYAxisDefinitionValue(Status_t& result);

  /*****************************************************************************/
  /**This  function used to Set Y Axis definition value.
   *
   * @param[in/out]value
   *  Y Axis value to be set.
   *
   * @returns
   * status of the operation.
   */
  Status_t SetYAxisDefinitionValue(const AxisInformation_t& value);

  /*****************************************************************************/
 /**This function used to Get Z Axis definition value.
  *
  * @param[out]result
  *  Z Axis value to be stored.
  *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * AxisInformation value. The caller must test the pointer before dereferencing it.
  */
  IntrusivePtr_t<const AxisInformation_t> GetZAxisDefinitionValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to Get Z Axis definition value.
   *
   * @param[in/out]value
   *  Z Axis value to be stored.
   *
   * @returns
   * returns status of the operation.
   */
  Status_t SetZAxisDefinitionValue(const AxisInformation_t& value);

  /*
   * Wrapper Functions
   */
  /*****************************************************************************/
  /** Function finds get the variable node as cube item.
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
   * Cube. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<CubeItem_t> Get(const NodeId_t& nodeId,
                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                        Status_t& result);

  /*****************************************************************************/
  /** Function used to get the variable node as cube item.
   *
   * @param[in] nodeId
   *  Variable node id which needs to find in the address space.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * node value
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * CubeItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<CubeItem_t> Get(IntrusivePtr_t<IVariableNode_t>& node,
                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                        Status_t& result);

  /*****************************************************************************/
  /** This template Function used to create CubeItem  With Numeric Id.
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
   * property values.
   *
   * @param[in] mandatoryPropertiesId
   * mandatory properties id.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * CubeItem. The caller must test the pointer before dereferencing it.
   */

  template<typename T>
  static IntrusivePtr_t<CubeItem_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                        uint32_t nodeIdentifier,
                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                        const String_t& browseName,
                                                        const MandatoryPropertyValues_t& propertyValues,
                                                        const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                        Status_t& result);

  /*****************************************************************************/
  /** This template Function used to create CubeItem  with string Id.
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
   * property values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * CubeItem. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<CubeItem_t> CreateWithStringId(uint16_t namespaceIndex,
                                                       const String_t& nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       const MandatoryPropertyValues_t& propertyValues,
                                                       Status_t& result);


  /*****************************************************************************/
  /** This template Function used to create CubeItem  with Gui Id.
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
   * property values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * CubeItem. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<CubeItem_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                     const Guid_t& nodeIdentifier,
                                                     IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                     const String_t& browseName,
                                                     const MandatoryPropertyValues_t& propertyValues,
                                                     Status_t& result);


  /*****************************************************************************/
  /** This template function used to create CubeItem with opaque id.
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
   * property values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * CubeItem. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<CubeItem_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                       const ByteString_t& nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       const MandatoryPropertyValues_t& propertyValues,
                                                       Status_t& result);


};

template<typename T>
IntrusivePtr_t<CubeItem_t> CubeItem_t::CreateWithNumericId(uint16_t namespaceIndex,
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
    IntrusivePtr_t<CubeItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_CubeItemType, 3, result);

  return CubeItem_t::CreateCubeWithMandatoryProperty(node_, addressSpace_, mandatoryPropertiesId, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<CubeItem_t> CubeItem_t::CreateWithStringId(uint16_t namespaceIndex,
                                                          const String_t& nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          const MandatoryPropertyValues_t& propertyValues,
                                                          Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<CubeItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_CubeItemType, 3, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0, 0, 0};
  return CubeItem_t::CreateCubeWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<CubeItem_t> CubeItem_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                        const Guid_t& nodeIdentifier,
                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                        const String_t& browseName,
                                                        const MandatoryPropertyValues_t& propertyValues,
                                                        Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<CubeItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_CubeItemType, 3, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0, 0, 0};
  return CubeItem_t::CreateCubeWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<CubeItem_t> CubeItem_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                          const ByteString_t& nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          const MandatoryPropertyValues_t& propertyValues,
                                                          Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<CubeItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_CubeItemType, 3, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0, 0, 0};
  return CubeItem_t::CreateCubeWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

/** @} */

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _CUBE_ITEM_T_H_ */
