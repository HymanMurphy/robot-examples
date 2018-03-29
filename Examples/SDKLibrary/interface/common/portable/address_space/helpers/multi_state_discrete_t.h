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

#ifndef _MULTI_STATE_DISCRETE_T_H_
#define _MULTI_STATE_DISCRETE_T_H_

#include "discrete_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief MultiStateDiscrete_t
*
* A class that represents a MultiStateDiscrete_t in the addressSpace.
*
*/
class MultiStateDiscrete_t : public DiscreteItem_t
{
private:

   //*****************************************************************************/
   /**Function used to check the valid data type.
    *
    * @param[in]datatype
    * data type which needs to be check for validity .
    *
    * @return
    * returns the status of the operation.
    */
  static bool IsDataTypeValid(uint32_t datatype);

  //*****************************************************************************/
   /**Function used to create enum string property.
    *
    * @param[in]multiStateDiscrete
    * MultiStateDiscrete_t object.
    *
    * @param[in]propertyIdentifier
    * property identifier.
    *
    * @param[in]value
    * LocalizedText_t text.
    *
    * @param[in]propertyNode
    * node property.
    *
    * @return
    * returns the status of the operation.
    */
  static Status_t CreateEnumStringsProperty(MultiStateDiscrete_t& multiStateDiscrete,
                                            uint32_t propertyIdentifier,
                                            const ArrayUA_t<LocalizedText_t>& value,
                                            IntrusivePtr_t<IVariableNode_t>& propertyNode);

  //*****************************************************************************/
   /**Function used to create multi state discrete node.
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
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
    */

  static IntrusivePtr_t<MultiStateDiscrete_t> CreateMultiStateDiscrete(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                       Status_t& result);

  /*****************************************************************************/
  /**This function creates multi state discrete with mandatory property.
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] enumStringsIdentifier
   * string identifiers.
   *
   * @param[in] enumStringsValue
   * string values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<MultiStateDiscrete_t> CreateMultiStateDiscreteWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                            uint32_t enumStringsIdentifier,
                                                                            const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                            Status_t& result);
  /*****************************************************************************/
   /**This function used to delete the multi state discrete properties.
    *
    * @param[in] multiStateDiscrete
    * item which to be delete.
    *
    */
  static void DeleteProperties(MultiStateDiscrete_t& multiStateDiscrete);

protected:
  MultiStateDiscrete_t();

public:
  virtual ~MultiStateDiscrete_t();

  /*
   * Properties
   */
  IntrusivePtr_t<IVariableNode_t> EnumStringsNode(void);
  IntrusivePtr_t<const IVariableNode_t> EnumStringsNode(void) const;

  IntrusivePtr_t<const ArrayUA_t<LocalizedText_t> > GetEnumStringsValue(Status_t& result);
  Status_t SetEnumStringsValue(const ArrayUA_t<LocalizedText_t>& value);

  /*
   * Wrapper creation
   */
  /*****************************************************************************/
  /** Function used to get the existing node in address space as MultiStateDiscret
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
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<MultiStateDiscrete_t> Get(const NodeId_t& nodeId,
                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                  Status_t& result);

  /*****************************************************************************/
  /** Function used to get the existing node in address space as MultiStateDiscret
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
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
   */

  static IntrusivePtr_t<MultiStateDiscrete_t> Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                  Status_t& result);

  /*****************************************************************************/
  /** This template function to create multi state discrete with Numeric Id.
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
   * @param[in] enumStringsIdentifier
   * string identifiers.
   *
   * @param[in] enumStringsValue
   * string values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
   */

  template<typename T>
  static IntrusivePtr_t<MultiStateDiscrete_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                                  uint32_t nodeIdentifier,
                                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                  const String_t& browseName,
                                                                  uint32_t enumStringsIdentifier,
                                                                  const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                  Status_t& result);

  /*****************************************************************************/
   /** This template function to create multi state discrete  with string Id.
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
    * @param[in] enumStringsValue
    * string values.
    *
    * @param[out] result
    * status of the operation.
    *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
    */
  template<typename T>
  static IntrusivePtr_t<MultiStateDiscrete_t> CreateWithStringId(uint16_t namespaceIndex,
                                                                 const String_t& nodeIdentifier,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 const String_t& browseName,
                                                                 const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                 Status_t& result);

  /*****************************************************************************/
  /** This template function to create multi state discrete  with GUID.
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
   * @param[in] enumStringsValue
   * string values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @returns
   * returns IntrusivePtr_t MultiStateDiscrete_t value.
   */
  template<typename T>
  static IntrusivePtr_t<MultiStateDiscrete_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                               const Guid_t& nodeIdentifier,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                               Status_t& result);

  /*****************************************************************************/
  /** This template function to create multi state discrete  with Opaque Id.
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
   * @param[in] enumStringsValue
   * string values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * MultiStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  template<typename T>
  static IntrusivePtr_t<MultiStateDiscrete_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                 const ByteString_t& nodeIdentifier,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 const String_t& browseName,
                                                                 const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                 Status_t& result);
};

template<typename T>
IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                                               uint32_t nodeIdentifier,
                                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                               const String_t& browseName,
                                                                               uint32_t enumStringsIdentifier,
                                                                               const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                               Status_t& result)
{
  if(!(MultiStateDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_MultiStateDiscreteType, -2, result);

  return MultiStateDiscrete_t::CreateMultiStateDiscreteWithMandatoryProperty(node_, addressSpace_, enumStringsIdentifier, enumStringsValue, result);
}

template<typename T>
IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::CreateWithStringId(uint16_t namespaceIndex,
                                                                              const String_t& nodeIdentifier,
                                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                              const String_t& browseName,
                                                                              const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                              Status_t& result)
{
  if(!(MultiStateDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_MultiStateDiscreteType, -2, result);

  return MultiStateDiscrete_t::CreateMultiStateDiscreteWithMandatoryProperty(node_, addressSpace_, 0, enumStringsValue, result);
}

template<typename T>
IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                                            const Guid_t& nodeIdentifier,
                                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                            const String_t& browseName,
                                                                            const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                            Status_t& result)
{
  if(!(MultiStateDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_MultiStateDiscreteType, -2, result);

  return MultiStateDiscrete_t::CreateMultiStateDiscreteWithMandatoryProperty(node_, addressSpace_, 0, enumStringsValue, result);
}

template<typename T>
IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                              const ByteString_t& nodeIdentifier,
                                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                              const String_t& browseName,
                                                                              const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                              Status_t& result)
{
  if(!(MultiStateDiscrete_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<MultiStateDiscrete_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_MultiStateDiscreteType, -2, result);

  return MultiStateDiscrete_t::CreateMultiStateDiscreteWithMandatoryProperty(node_, addressSpace_, 0, enumStringsValue, result);
}

/** @} */

} //namespace uasdk


#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _MULTI_STATE_DISCRETE_T_H_ */
