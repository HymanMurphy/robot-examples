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

#ifndef _MULTI_STATE_VALUE_DISCRETE_T_H_
#define _MULTI_STATE_VALUE_DISCRETE_T_H_

#include "discrete_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

namespace uasdk
{

class EnumValueType_t;

/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief MultiStateValueDiscrete_t
*
* A class that represents a MultiStateValueDiscrete_t in the addressSpace.
*
*/
class MultiStateValueDiscrete_t : public DiscreteItem_t
{
public:
  typedef struct
  {
    uint32_t enumValues;
    uint32_t valueAsText;
  }MandatoryPropertyNumericIds_t;

private:
  //*****************************************************************************/
  /**Function used to check the valid data type.
   *
   * @param[in]datatype
   * data type which needs to be check for validity .
   *
   * @return
   * returns the boolean status of the operation.
   */
  static bool IsDataTypeValid(uint32_t dataType);

  //*****************************************************************************/
   /**Function used to create value as text property.
    *
    * @param[in/out] multiStateDiscrete
    * MultiStateDiscrete_t object.
    *
    * @param[in]propertyIdentifier
    * property identifier.
    *
    * @return
    * returns the status of the operation.
    */
  static Status_t CreateValueAsTextProperty(IntrusivePtr_t<MultiStateValueDiscrete_t>& multiStateValueDiscrete,
                                            uint32_t propertyIdentifier);

  //*****************************************************************************/
  /**Function used to create enum values property.
   *
   * @param[in]multiStateDiscrete
   * MultiStateDiscrete_t object.
   *
   * @param[in]propertyIdentifier
   * property identifier.
   *
   * @param[out]value
   * LocalizedText_t text.
   *
   * @return
   * returns the status of the operation.
   */
  static Status_t CreateEnumValuesProperty(MultiStateValueDiscrete_t& multiStateValueDiscrete,
                                           uint32_t propertyIdentifier,
                                           const ArrayUA_t<EnumValueType_t>& value);


  //*****************************************************************************/
   /**Function used to create multi state value discrete values.
    *
    * @param[in]node_
    * IVariableNode_t node which needs to create.
    *
    * @param[in]addressSpace_
    * IAddressSpace_t object.
    *
    * @param[out]result
    * status of the operation.
    *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
    */

  static IntrusivePtr_t<MultiStateValueDiscrete_t> CreateMultiStateValueDiscrete(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                 Status_t& result);

  /*****************************************************************************/
  /**This function creates multi state value discretes with mandatory property.
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] ids
   * const struct variable.
   *
   * @param[in] value
   * EnumValueType_t values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<MultiStateValueDiscrete_t> CreateMultiStateValueDiscreteWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                                      const MandatoryPropertyNumericIds_t& ids,
                                                                                                      const ArrayUA_t<EnumValueType_t>& value,
                                                                                                      Status_t& result);

  /*****************************************************************************/
  /**This function used to delete the properties.
   *
   * @param[in] multiStateValueDiscrete
   * Item which to be delete.
   *
   */
  static void DeleteProperties(MultiStateValueDiscrete_t& multiStateValueDiscrete);

protected:
  MultiStateValueDiscrete_t();

public:
  virtual ~MultiStateValueDiscrete_t();

  /*
   * Properties
   */
  /*****************************************************************************/
  /**This function used to get the node property.
   *
   * @return
   * Item IVariableNode_t values.
   *
   */
  IntrusivePtr_t<IVariableNode_t> EnumValuesNode(void);

  /*****************************************************************************/
  /**This const function used to get the node property.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   *
   */
  IntrusivePtr_t<const IVariableNode_t> EnumValuesNode(void) const;

  /*****************************************************************************/
  /**This function used to get EnumValues property value.
   *
   * @param[out] result
   * values which is to be store.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   *
   */
  IntrusivePtr_t<const ArrayUA_t<EnumValueType_t> > GetEnumValuesValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to set the EnumValue property value.
   *
   * @param[in/out] value
   * values which is to be set.
   *
   * @return
   * returns the status of the operation.
   *
   */
  Status_t SetEnumValuesValue(const ArrayUA_t<EnumValueType_t>& value);

  /*****************************************************************************/
  /**This function used to get the ValueAsText property node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   *
   */
  IntrusivePtr_t<IVariableNode_t> ValueAsTextNode(void);

  /*****************************************************************************/
  /**This const function used to get ValueAsText property node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   *
   */
  IntrusivePtr_t<const IVariableNode_t> ValueAsTextNode(void) const;

  /*****************************************************************************/
  /**This const function used to get ValueAsText property value.
   *
   * @param[in] value
   * values which is to be store.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const LocalizedText_t> GetValueAsTextValue(Status_t& result);

  /*
   * Wrapper creation
   */

  /*****************************************************************************/
  /** This function is used to get the exisiting node as MultiStateValueDiscrete
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
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<MultiStateValueDiscrete_t> Get(const NodeId_t& nodeId,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       Status_t& result);

  /*****************************************************************************/
  /** This function is used to get the exisiting node as MultiStateValueDiscrete
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
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<MultiStateValueDiscrete_t> Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       Status_t& result);

  /*****************************************************************************/
  /** This template function used to create multi state value discrete  with Numeric Id.
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
   * @param[in] propertyIdentifier
   * property identifiers.
   *
   * @param[in] value
   * EnumValueType_t values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<MultiStateValueDiscrete_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                                       uint32_t nodeIdentifier,
                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                       const String_t& browseName,
                                                                       const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                                                       const ArrayUA_t<EnumValueType_t>& value,
                                                                       Status_t& result);

  /*****************************************************************************/
   /** This template function to create multi state value discrete  with string Id.
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
    * @param[in] propertyIdentifier
    * property identifiers.
    *
    * @param[in] value
    * EnumValueType_t values.
    *
    * @param[out] result
    * status of the operation.
    *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<MultiStateValueDiscrete_t> CreateWithStringId(uint16_t namespaceIndex,
                                                                      const String_t& nodeIdentifier,
                                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                      const String_t& browseName,
                                                                      const ArrayUA_t<EnumValueType_t>& value,
                                                                      Status_t& result);

  /*****************************************************************************/
   /** This template function to create multi state value discrete  with GUID.
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
    * @param[in] value
    * EnumValueType_t values.
    *
    * @param[out] result
    * status of the operation.
    *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
    */
  template<typename T>
  static IntrusivePtr_t<MultiStateValueDiscrete_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                                    const Guid_t& nodeIdentifier,
                                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                    const String_t& browseName,
                                                                    const ArrayUA_t<EnumValueType_t>& value,
                                                                    Status_t& result);

  /*****************************************************************************/
   /** This template function to create multi state value discrete  with Opaque id.
    *
    * @param[in] namespaceIndex
    * namespace Index
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
    * @param[in] value
    * EnumValueType_t values.
    *
    * @param[out] result
    * status of the operation.
    *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateValueDiscrete. The caller must test the pointer before dereferencing it.
    */
  template<typename T>
  static IntrusivePtr_t<MultiStateValueDiscrete_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                      const ByteString_t& nodeIdentifier,
                                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                      const String_t& browseName,
                                                                      const ArrayUA_t<EnumValueType_t>& value,
                                                                      Status_t& result);
};

template<typename T>
IntrusivePtr_t<MultiStateValueDiscrete_t> MultiStateValueDiscrete_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                                                         uint32_t nodeIdentifier,
                                                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                         const String_t& browseName,
                                                                                         const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                                                                         const ArrayUA_t<EnumValueType_t>& value,
                                                                                         Status_t& result)
{
  if(!(MultiStateValueDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                  browseName, OpcUaId_MultiStateValueDiscreteType, -1, result);

  return MultiStateValueDiscrete_t::CreateMultiStateValueDiscreteWithMandatoryProperty(node_, addressSpace_, propertyIdentifier, value, result);
}

template<typename T>
IntrusivePtr_t<MultiStateValueDiscrete_t> MultiStateValueDiscrete_t::CreateWithStringId(uint16_t namespaceIndex,
                                                                                        const String_t& nodeIdentifier,
                                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                        const String_t& browseName,
                                                                                        const ArrayUA_t<EnumValueType_t>& value,
                                                                                        Status_t& result)
{
  if(!(MultiStateValueDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_MultiStateValueDiscreteType, -1, result);

  MandatoryPropertyNumericIds_t empty = {0, 0};
  return MultiStateValueDiscrete_t::CreateMultiStateValueDiscreteWithMandatoryProperty(node_, addressSpace_, empty, value, result);
}

template<typename T>
IntrusivePtr_t<MultiStateValueDiscrete_t> MultiStateValueDiscrete_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                                                      const Guid_t& nodeIdentifier,
                                                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                      const String_t& browseName,
                                                                                      const ArrayUA_t<EnumValueType_t>& value,
                                                                                      Status_t& result)
{
  if(!(MultiStateValueDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_MultiStateValueDiscreteType, -1, result);

  MandatoryPropertyNumericIds_t empty = {0, 0};
  return MultiStateValueDiscrete_t::CreateMultiStateValueDiscreteWithMandatoryProperty(node_, addressSpace_, empty, value, result);
}

template<typename T>
IntrusivePtr_t<MultiStateValueDiscrete_t> MultiStateValueDiscrete_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                                        const ByteString_t& nodeIdentifier,
                                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                        const String_t& browseName,
                                                                                        const ArrayUA_t<EnumValueType_t>& value,
                                                                                        Status_t& result)
{
  if(!(MultiStateValueDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_MultiStateValueDiscreteType, -1, result);

  MandatoryPropertyNumericIds_t empty = {0, 0};
  return MultiStateValueDiscrete_t::CreateMultiStateValueDiscreteWithMandatoryProperty(node_, addressSpace_, empty, value, result);
}

/** @} */

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _MULTI_STATE_VALUE_DISCRETE_T_H_ */
