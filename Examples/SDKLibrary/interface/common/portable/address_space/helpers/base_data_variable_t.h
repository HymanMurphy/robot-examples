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

#ifndef _BASE_DATA_VARIABLE_T_
#define _BASE_DATA_VARIABLE_T_

#include "helper_base_t.h"

#if (UASDK_USE_HELPERS > 0)

//#include "allocatable_t.h"
#include "ivariable_node_t.h"
#include "iaddress_space_t.h"
#include "opcua_data_value_t.h"
#include "opcua_node_id_t.h"
#include "address_space_utilities_t.h"

#include "opcua_node_id_numeric_t.h"
#include "opcua_node_id_string_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_node_id_opaque_t.h"

#include "opcua_datatype_utilities_t.h"

#include "browse_names_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief BaseDataVariable_t
*
* BaseDataVariable_t class.
*
*/
class BaseDataVariable_t : public HelperBase_t
{
  private:
  
    /*****************************************************************************/
    /** This function Create BaseDataVariable
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
    static IntrusivePtr_t<BaseDataVariable_t> CreateBaseDataVariable(IntrusivePtr_t<IVariableNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result);

    /*****************************************************************************/
    /** Function used to get value of base data variable
     *
     * @param[in] BaseDataVariable
     * BaseDataVariable which needs to be be get the value.
     *
     * @param[out] val
     * BaseDataType_t object value.
     *
     * @return
     * status of the operation.
     *
     */
    static Status_t GetValue(BaseDataVariable_t& BaseDataVariable, BaseDataType_t& val);

  protected:

    BaseDataVariable_t();

  /*****************************************************************************/
  /** This function creates base data variable with numeric id.
   *
   * @param[in] namespaceIndex
   * namespace index value.
   *
   * @param[in] nodeIdentifier
   * node identifier.
   *
   * @param[in] dataTypeId
   * data id type.
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
    static IntrusivePtr_t<IVariableNode_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                               uint32_t nodeIdentifier,
                                                               uint32_t dataTypeId,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               uint32_t hasTypeReferenceId,
                                                               int32_t valueRank,
                                                               Status_t& result);

  /*****************************************************************************/
  /** This function creates base data variable with string id.
   *
   * @param[in] namespaceIndex
   * namespace index value.
   *
   * @param[in] nodeIdentifier
   * node identifier.
   *
   * @param[in] dataTypeId
   * data id type.
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
    static IntrusivePtr_t<IVariableNode_t> CreateWithStringId(uint16_t namespaceIndex,
                                                              const String_t& nodeIdentifier,
                                                              uint32_t dataTypeId,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              uint32_t hasTypeReferenceId,
                                                              int32_t valueRank,
                                                              Status_t& result);
  /*****************************************************************************/
  /** This function creates base data variable with GUID.
   *
   * @param[in] namespaceIndex
   * namespace index value.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] dataTypeId
   * data id type.
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
    static IntrusivePtr_t<IVariableNode_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                            const Guid_t& nodeIdentifier,
                                                            uint32_t dataTypeId,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            const String_t& browseName,
                                                            uint32_t hasTypeReferenceId,
                                                            int32_t valueRank,
                                                            Status_t& result);

  /*****************************************************************************/
  /** This function creates base data variable with Opaque id.
   *
   * @param[in] namespaceIndex
   * namespace index value.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] dataTypeId
   * data id type.
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
    static IntrusivePtr_t<IVariableNode_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                              const ByteString_t& nodeIdentifier,
                                                              uint32_t dataTypeId,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              uint32_t hasTypeReferenceId,
                                                              int32_t valueRank,
                                                              Status_t& result);

  public:
    virtual ~BaseDataVariable_t();

    /*****************************************************************************/
    /** This function gets the BaseDataVariable node.
      *
      * @return
      * An intrusive reference counting Boost-style smart pointer to the
      * node. The caller must test the pointer before dereferencing it.
      *
      */
    IntrusivePtr_t<IVariableNode_t> GetVariableNode(void);
    /*****************************************************************************/
    /** This const function used to get the BaseDataVariable node.
     *
     * @return
     * An intrusive reference counting Boost-style smart pointer to the
     * node. The caller must test the pointer before dereferencing it.
     *
     */
    IntrusivePtr_t<const IVariableNode_t> GetVariableNode(void) const;

    /*****************************************************************************/
    /** This function is used to get the value of BaseDataVariable node for generic types.
     *
     * @return
     * returns the status of the operation.
     *
     */
    template<typename T>
    Status_t GetValue(T& value)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
    }

    /*****************************************************************************/
    /** This is used to set the value for BaseDataVariable type for generic types
     *
     * @return
     * returns the status of the operation.
     *
     */
    template<typename T>
    Status_t SetValue(const T& value)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
    }

    /*****************************************************************************/
    /** This function used to get the value of BaseDataVariable node for OPCUA datatype
     *
     * @param[out] result
     * status of the operation.
     *
     * @return
     * An intrusive reference counting Boost-style smart pointer to the
     * value. The caller must test the pointer before dereferencing it.
     */
    template<typename T>
    IntrusivePtr_t<const T> GetValue(Status_t& result);

    /*****************************************************************************/
    /** This function used to set the value of BaseDataVariable Node for OPCUA datatypes
     *
     * @param[in] value
     * value to be set for the node.
     *
     * @return
     * returns status of the operation.
     *
     */
    Status_t SetValue(IntrusivePtr_t<BaseDataType_t> value);

  /*****************************************************************************/
  /** This function used to set the value for BaseDataVariable node
   *
   * @param[in] value
   * value to be set for the node.
   *
   * @param[in] sourceTimestamp
   * time stamp.
   *
   * @return
   * returns status of the operation.
   *
   */
    Status_t SetValue(IntrusivePtr_t<BaseDataType_t> value, DateTime_t& sourceTimestamp);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
   *  BaseDataVariable node.
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
    static IntrusivePtr_t<BaseDataVariable_t> Get(const NodeId_t& nodeId,
                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                  Status_t& result);

    /*****************************************************************************/
    /** This function is used to get the existing node in the address space as
    *  BaseDataVariable node.
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
    static IntrusivePtr_t<BaseDataVariable_t> Get(IntrusivePtr_t<IVariableNode_t>& node,
                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                  Status_t& result);

  /*****************************************************************************/
  /** This Function used to create BaseDataVariable with Numeric Id.
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
   * BaseDataVariable. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<BaseDataVariable_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                                  uint32_t nodeIdentifier,
                                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                  const String_t& browseName,
                                                                  Status_t& result);

  /*****************************************************************************/
  /** This Function is used to create BaseDataVariable node with sting Id.
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
   * BaseDataVariable. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<BaseDataVariable_t> CreateWithStringId(uint16_t namespaceIndex,
                                                                 const String_t& nodeIdentifier,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 const String_t& browseName,
                                                                 Status_t& result);

  /*****************************************************************************/
  /** This Function used to create BaseDataVariable with GUID
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
   * BaseDataVariable. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<BaseDataVariable_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                               const Guid_t& nodeIdentifier,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               Status_t& result);

  /*****************************************************************************/
  /** This Function is used to BaseDataVariable with Opaque item
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
   * BaseDataVariable. The caller must test the pointer before dereferencing it.
   */
    template<typename T>
    static IntrusivePtr_t<BaseDataVariable_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                 const ByteString_t& nodeIdentifier,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 const String_t& browseName,
                                                                 Status_t& result);

};

template<typename T>
IntrusivePtr_t<const T> BaseDataVariable_t::GetValue(Status_t& result)
{
  IntrusivePtr_t<const T> retVal;
  IntrusivePtr_t<const IVariableNode_t> node_ = GetVariableNode();
  if(!node_.is_set())
  {
    result = OpcUa_BadNoData;
    return retVal;
  }

  if(!node_->Value().is_set() && node_->CanReadValueSynchronously())
  {
    uint32_t maxAge = 0;
    TimestampsToReturn_t::Enum_t timestampsToReturn = TimestampsToReturn_t::RETURN_BOTH;
    const ArrayUA_t<String_t> locales;
    const Array_t<IndexRange_t> indexRange;
    uint32_t transactionId = 0;
    uint32_t timeoutHint = 0;
    IntrusivePtr_t<DataValue_t> dataValue;
    IntrusivePtr_t<DiagnosticInfo_t> diagInfo;

    result = node_->ReadValue(maxAge, timestampsToReturn, locales, indexRange, transactionId, timeoutHint, dataValue, diagInfo);
    if(result.IsBad() || !dataValue.is_set())
    {
      result = OpcUa_BadUnexpectedError;
      return retVal;
    }

    retVal = RuntimeCast<const T*>( *(dataValue->Value()) );
  }
  else
  {
    if(!node_->Value().is_set() || !node_->Value()->Value().is_set())
    {
      result = OpcUa_BadNoData;
      return retVal;
    }

    retVal = RuntimeCast<const T*>(*(node_->Value()->Value()) );
  }

  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

template<typename T>
IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                                        uint32_t nodeIdentifier,
                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                        const String_t& browseName,
                                                                        Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_BaseDataVariableType, -2, result);

  return BaseDataVariable_t::CreateBaseDataVariable(node_, addressSpace_, result);
}

template<typename T>
IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::CreateWithStringId(uint16_t namespaceIndex,
                                                                       const String_t& nodeIdentifier,
                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                       const String_t& browseName,
                                                                       Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_BaseDataVariableType, -2, result);

  return BaseDataVariable_t::CreateBaseDataVariable(node_, addressSpace_, result);
}

template<typename T>
IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                                     const Guid_t& nodeIdentifier,
                                                                     IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                     const String_t& browseName,
                                                                     Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_BaseDataVariableType, -2, result);

  return BaseDataVariable_t::CreateBaseDataVariable(node_, addressSpace_, result);
}

template<typename T>
IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                          const ByteString_t& nodeIdentifier,
                                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                          const String_t& browseName,
                                                                          Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_BaseDataVariableType, -2, result);

  return BaseDataVariable_t::CreateBaseDataVariable(node_, addressSpace_, result);
}

template<> Status_t BaseDataVariable_t::GetValue<bool>(bool& value);
template<> Status_t BaseDataVariable_t::GetValue<int8_t>(int8_t& value);
template<> Status_t BaseDataVariable_t::GetValue<int16_t>(int16_t& value);
template<> Status_t BaseDataVariable_t::GetValue<int32_t>(int32_t& value);
template<> Status_t BaseDataVariable_t::GetValue<int64_t>(int64_t& value);
template<> Status_t BaseDataVariable_t::GetValue<uint8_t>(uint8_t& value);
template<> Status_t BaseDataVariable_t::GetValue<uint16_t>(uint16_t& value);
template<> Status_t BaseDataVariable_t::GetValue<uint32_t>(uint32_t& value);
template<> Status_t BaseDataVariable_t::GetValue<uint64_t>(uint64_t& value);
template<> Status_t BaseDataVariable_t::GetValue<float>(float& value);
template<> Status_t BaseDataVariable_t::GetValue<double>(double& value);

template<> Status_t BaseDataVariable_t::SetValue<bool>(const bool& value);
template<> Status_t BaseDataVariable_t::SetValue<int8_t>(const int8_t& value);
template<> Status_t BaseDataVariable_t::SetValue<int16_t>(const int16_t& value);
template<> Status_t BaseDataVariable_t::SetValue<int32_t>(const int32_t& value);
template<> Status_t BaseDataVariable_t::SetValue<int64_t>(const int64_t& value);
template<> Status_t BaseDataVariable_t::SetValue<uint8_t>(const uint8_t& value);
template<> Status_t BaseDataVariable_t::SetValue<uint16_t>(const uint16_t& value);
template<> Status_t BaseDataVariable_t::SetValue<uint32_t>(const uint32_t& value);
template<> Status_t BaseDataVariable_t::SetValue<uint64_t>(const uint64_t& value);
template<> Status_t BaseDataVariable_t::SetValue<float>(const float& value);
template<> Status_t BaseDataVariable_t::SetValue<double>(const double& value);

/** @} */

}

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif // _BASE_DATA_VARIABLE_T_
