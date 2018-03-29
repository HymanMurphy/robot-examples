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

#ifndef _N_DIMENSION_ARRAY_ITEM_T_H_
#define _N_DIMENSION_ARRAY_ITEM_T_H_

#include "array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_axis_information_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief NDimensionArrayItem_t
*
* A class that represents a NDimensionArrayItem_t in the addressSpace.
*
*/
class NDimensionArrayItem_t : public ArrayItem_t
{
public:

  typedef struct
  {
    ArrayItem_t::MandatoryPropertyValues_t  arrayItemProperty;
    ArrayUA_t<AxisInformation_t>            axisInformation;
  } MandatoryPropertyValues_t;

  typedef struct
  {
    ArrayItem_t::MandatoryPropertyNumericIds_t  arrayItemPropertyNumericId;
    uint32_t                                    axisInformationNumericId;
  } MandatoryPropertyNumericIds_t;

protected:
  NDimensionArrayItem_t();

private:

  /*****************************************************************************/
  /**This function creates N-Dimensional array with mandatory property.
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] mandatoryPropertiesId
   * const MandatoryPropertyNumericIds_t struct variable.
   *
   * @param[in] value
   * const MandatoryPropertyValues_t struct variable.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<NDimensionArrayItem_t> CreateNDimensionArrayWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                          const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                                          const MandatoryPropertyValues_t& propertyValues,
                                                                                          Status_t& result);
  /*****************************************************************************/
  /**This function used to creates N- dimensional array property.
   *
   * @param[in] item
   * NDimensionArrayItem_t object.
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

  static Status_t CreateProperty(NDimensionArrayItem_t& item,
                                 uint32_t propertyIdentifier,
                                 const char* propertyName,
                                 uint32_t propertyType,
                                 const ArrayUA_t<AxisInformation_t>& value,
                                 IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
  /**This function Creates N-dimensional array Item.
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
   * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<NDimensionArrayItem_t> CreateNDimensionArrayItem( IntrusivePtr_t<IVariableNode_t>& node_,
                                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                          Status_t& result);

  /*****************************************************************************/
  /**This function used to Get N-dimensional Axis Information property Value.
   *
   * @param[out] propertyNode
   * IVariableNode_t node used to get Axis Information Value.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * Value. The caller must test the pointer before dereferencing it.
   */

  IntrusivePtr_t<const ArrayUA_t<AxisInformation_t> > GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result);

  /*****************************************************************************/
  /**This function used to delete the N- dimensional properties.
   *
   * @param[in] imageItem
   * item which to be delete.
   *
   */
  void DeleteProperties(NDimensionArrayItem_t& cubeItem);

public:

  virtual ~NDimensionArrayItem_t();
  /*
   * Standard Property helpers
   */
  /*****************************************************************************/
  /**This function used to create Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> AxisDefinitionNode(void);

  /*****************************************************************************/
  /**This function used to create Axis definition node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> AxisDefinitionNode(void) const;

  /*****************************************************************************/
  /**This function used to Get Axis definition value.
   *
   * @param[out]result
   * Axis value to be stored.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const ArrayUA_t<AxisInformation_t> > GetAxisDefinitionValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to Set Axis definition value.
   *
   * @param[in/out]value
   * Axis value to be set.
   *
   * @returns
   * status of the operation.
   */
  Status_t SetAxisDefinitionValue(const ArrayUA_t<AxisInformation_t>& value);

    /*
    * Wrapper Functions
    */
  /*****************************************************************************/
  /** This function used to get the existing node as NDimensionArrayItem
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
   * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
    */
   static IntrusivePtr_t<NDimensionArrayItem_t> Get(const NodeId_t& nodeId,
                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                    Status_t& result);
   
   /*****************************************************************************/
   /** This function used to get the existing node as NDimensionArrayItem
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
    * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
    */
   static IntrusivePtr_t<NDimensionArrayItem_t> Get(IntrusivePtr_t<IVariableNode_t>& node,
                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                    Status_t& result);

   /*****************************************************************************/
   /** This template function to create N -dimensional array item with Numeric Id.
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
   * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
    */
   template<typename T>
   static IntrusivePtr_t<NDimensionArrayItem_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                                    uint32_t nodeIdentifier,
                                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                    const String_t& browseName,
                                                                    const MandatoryPropertyValues_t& propertyValues,
                                                                    const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                    Status_t& result);

   /*****************************************************************************/
   /** This template function to create N-dimensional property  with string Id.
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
   * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
    */
   template<typename T>
   static IntrusivePtr_t<NDimensionArrayItem_t> CreateWithStringId(uint16_t namespaceIndex,
                                                                   const String_t& nodeIdentifier,
                                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                   const String_t& browseName,
                                                                   const MandatoryPropertyValues_t& propertyValues,
                                                                   Status_t& result);

   /*****************************************************************************/
   /** This template function to create N-dimensional property  with GUID.
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
    * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
    */
   template<typename T>
   static IntrusivePtr_t<NDimensionArrayItem_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                                 const Guid_t& nodeIdentifier,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 const String_t& browseName,
                                                                 const MandatoryPropertyValues_t& propertyValues,
                                                                 Status_t& result);

   /*****************************************************************************/
   /** This template function used to create N-dimensional array property with opaque Id.
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
    * NDimentionArrayItem. The caller must test the pointer before dereferencing it.
    */
   template<typename T>
   static IntrusivePtr_t<NDimensionArrayItem_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                   const ByteString_t& nodeIdentifier,
                                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                   const String_t& browseName,
                                                                   const MandatoryPropertyValues_t& propertyValues,
                                                                   Status_t& result);

};


template<typename T>
IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::CreateWithNumericId(uint16_t namespaceIndex,
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
    IntrusivePtr_t<NDimensionArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_NDimensionArrayItemType, 0, result);

  return NDimensionArrayItem_t::CreateNDimensionArrayWithMandatoryProperty(node_, addressSpace_, mandatoryPropertiesId, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::CreateWithStringId(uint16_t namespaceIndex,
                                                                                const String_t& nodeIdentifier,
                                                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                const String_t& browseName,
                                                                                const MandatoryPropertyValues_t& propertyValues,
                                                                                Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<NDimensionArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_NDimensionArrayItemType, 0, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0};
  return NDimensionArrayItem_t::CreateNDimensionArrayWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                                              const Guid_t& nodeIdentifier,
                                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                              const String_t& browseName,
                                                                              const MandatoryPropertyValues_t& propertyValues,
                                                                              Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<NDimensionArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_NDimensionArrayItemType, 0, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0};
  return NDimensionArrayItem_t::CreateNDimensionArrayWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

template<typename T>
IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                                const ByteString_t& nodeIdentifier,
                                                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                const String_t& browseName,
                                                                                const MandatoryPropertyValues_t& propertyValues,
                                                                                Status_t& result)
{
  if( !IsDataTypeValid(T::TYPE_ID))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<NDimensionArrayItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_NDimensionArrayItemType, 0, result);

  MandatoryPropertyNumericIds_t empty = { {0, 0, 0, 0}, 0};
  return NDimensionArrayItem_t::CreateNDimensionArrayWithMandatoryProperty(node_, addressSpace_, empty, propertyValues, result);
}

/** @} */

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _N_DIMENSION_ARRAY_ITEM_T_H_ */
