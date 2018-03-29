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

#include "base_data_variable_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "opcua_qualified_name_t.h"
#include "localizable_text_stored_t.h"
#include "access_level_t.h"
#include "utilities.h"
#include "opcua_boolean_t.h"
#include "opcua_byte_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_float_t.h"
#include "opcua_uint64_t.h"

#include "opcua_duration_t.h"
#include "opcua_diagnostic_info_t.h"
#include "node_with_instrument_range_property_value_attribute_reader_writer_t.h"

namespace uasdk
{

IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::CreateBaseDataVariable(IntrusivePtr_t<IVariableNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result)
{
  IntrusivePtr_t<BaseDataVariable_t> retVal;
  if (!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<BaseDataVariable_t>());
  if (!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }

  retVal->Initialize(node_, addressSpace_);
  result = OpcUa_Good;
  return retVal;
}

Status_t BaseDataVariable_t::GetValue(BaseDataVariable_t& dataItem, BaseDataType_t& val)
{
  IntrusivePtr_t<IVariableNode_t> node_ = dataItem.GetVariableNode();
  UASDK_RETURN_UNEXPECTED_IF_NULL(node_);

  if (!node_->Value().is_set() && node_->CanReadValueSynchronously())
  {
    uint32_t maxAge = 0;
    TimestampsToReturn_t::Enum_t timestampsToReturn = TimestampsToReturn_t::RETURN_BOTH;
    const ArrayUA_t<String_t> locales;
    const Array_t<IndexRange_t> indexRange;
    uint32_t transactionId = 0;
    uint32_t timeoutHint = 0;
    IntrusivePtr_t<DataValue_t> dataValue;
    IntrusivePtr_t<DiagnosticInfo_t> diagInfo;

    Status_t status = node_->ReadValue(maxAge, timestampsToReturn, locales, indexRange, transactionId, timeoutHint, dataValue, diagInfo);
    if (status.IsBad() || !dataValue.is_set())
    {
      return status;
    }

    return val.CopyFrom(*(dataValue->Value()));
  }

  if (!node_->Value().is_set() || !node_->Value()->Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }

  return val.CopyFrom(*(node_->Value()->Value()));
}

/*
* Protected Functions
*/

BaseDataVariable_t::BaseDataVariable_t()
{}

IntrusivePtr_t<IVariableNode_t> BaseDataVariable_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                                        uint32_t nodeIdentifier,
                                                                        uint32_t dataTypeId,
                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                        const String_t& browseName,
                                                                        uint32_t hasTypeReferenceId,
                                                                        int32_t valueRank,
                                                                        Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> retVal;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateNumericNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return retVal;
  }

  return HelperBase_t::Create(nodeId, dataTypeId, addressSpace_, browseName, hasTypeReferenceId, valueRank, result);
}

IntrusivePtr_t<IVariableNode_t> BaseDataVariable_t::CreateWithStringId(uint16_t namespaceIndex,
                                                                       const String_t& nodeIdentifier,
                                                                       uint32_t dataTypeId,
                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                       const String_t& browseName,
                                                                       uint32_t hasTypeReferenceId,
                                                                       int32_t valueRank,
                                                                       Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> retVal;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateStringNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return retVal;
  }

  return HelperBase_t::Create(nodeId, dataTypeId, addressSpace_, browseName, hasTypeReferenceId, valueRank, result);
}

IntrusivePtr_t<IVariableNode_t> BaseDataVariable_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                                     const Guid_t& nodeIdentifier,
                                                                     uint32_t dataTypeId,
                                                                     IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                     const String_t& browseName,
                                                                     uint32_t hasTypeReferenceId,
                                                                     int32_t valueRank,
                                                                     Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> retVal;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateGuidNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return retVal;
  }

  return HelperBase_t::Create(nodeId, dataTypeId, addressSpace_, browseName, hasTypeReferenceId, valueRank, result);
}

IntrusivePtr_t<IVariableNode_t> BaseDataVariable_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                       const ByteString_t& nodeIdentifier,
                                                                       uint32_t dataTypeId,
                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                       const String_t& browseName,
                                                                       uint32_t hasTypeReferenceId,
                                                                       int32_t valueRank,
                                                                       Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> retVal;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateOpaqueNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return retVal;
  }

  return HelperBase_t::Create(nodeId, dataTypeId, addressSpace_, browseName, hasTypeReferenceId, valueRank, result);
}

/*
* Public Functions
*/
BaseDataVariable_t::~BaseDataVariable_t()
{}

/*
* Node
*/
IntrusivePtr_t<IVariableNode_t> BaseDataVariable_t::GetVariableNode(void)
{
  IntrusivePtr_t<IVariableNode_t> node_;
  if (!node.is_set())
  {
    return node_;
  }

  node_ = AddressSpaceUtilities_t::NodeDownCast<IVariableNode_t>(*node);
  if (!node_.is_set())
  {
    return node_;
  }

  return node_;
}

IntrusivePtr_t<const IVariableNode_t> BaseDataVariable_t::GetVariableNode(void) const
{
  IntrusivePtr_t<IVariableNode_t> node_;
  if (!node.is_set())
  {
    return node_;
  }

  node_ = AddressSpaceUtilities_t::NodeDownCast<IVariableNode_t>(*node);
  if (!node_.is_set())
  {
    return node_;
  }

  return node_;
}

Status_t BaseDataVariable_t::SetValue(IntrusivePtr_t<BaseDataType_t> value)
{
  if (!value.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  DateTime_t empty;
  return BaseDataVariable_t::CreateAndAssignDataValue(GetVariableNode(), value, empty);
}

Status_t BaseDataVariable_t::SetValue(IntrusivePtr_t<BaseDataType_t> value, DateTime_t& sourceTimestamp)
{
  if (!value.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return BaseDataVariable_t::CreateAndAssignDataValue(GetVariableNode(), value, sourceTimestamp);
}

/*
* Wrapper creation
*/
IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::Get(const NodeId_t& nodeId,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           Status_t& result)
{
  IntrusivePtr_t<BaseDataVariable_t> empty;
  if (!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> baseDataVariableNode = addressSpace_->FindVariableNode(nodeId, result);
  if (result.IsBad() || !baseDataVariableNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return BaseDataVariable_t::Get(baseDataVariableNode, addressSpace_, result);
}

IntrusivePtr_t<BaseDataVariable_t> BaseDataVariable_t::Get(IntrusivePtr_t<IVariableNode_t>& node,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           Status_t& result)
{
  IntrusivePtr_t<BaseDataVariable_t> empty;
  if (!node.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = HelperBase_t::CheckHasTypeDefinition(*node, *addressSpace_, OpcUaId_BaseDataVariableType);
  if (result.IsBad())
  {
    return empty;
  }

  return BaseDataVariable_t::CreateBaseDataVariable(node, addressSpace_, result);
}

/*
* Get And Set Template Functions
*/
template<> Status_t BaseDataVariable_t::GetValue<bool>(bool& value)
{
  Boolean_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<int8_t>(int8_t& value)
{
  SByte_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<int16_t>(int16_t& value)
{
  Int16_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<int32_t>(int32_t& value)
{
  Int32_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<int64_t>(int64_t& value)
{
  Int64_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<uint8_t>(uint8_t& value)
{
  Byte_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<uint16_t>(uint16_t& value)
{
  UInt16_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<uint32_t>(uint32_t& value)
{
  UInt32_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<uint64_t>(uint64_t& value)
{
  UInt64_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<float>(float& value)
{
  Float_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::GetValue<double>(double& value)
{
  Double_t val;
  Status_t status = BaseDataVariable_t::GetValue(*this, val);
  if (status.IsGood())
  {
    value = val.Value();
  }

  return status;
}

template<> Status_t BaseDataVariable_t::SetValue<bool>(const bool& value)
{
  IntrusivePtr_t<Boolean_t> val(new SafeRefCount_t<Boolean_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return BaseDataVariable_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<int8_t>(const int8_t& value)
{
  IntrusivePtr_t<SByte_t> val(new SafeRefCount_t<SByte_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<int16_t>(const int16_t& value)
{
  IntrusivePtr_t<Int16_t> val(new SafeRefCount_t<Int16_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<int32_t>(const int32_t& value)
{
  IntrusivePtr_t<Int32_t> val(new SafeRefCount_t<Int32_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<int64_t>(const int64_t& value)
{
  IntrusivePtr_t<Int64_t> val(new SafeRefCount_t<Int64_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<uint8_t>(const uint8_t& value)
{
  IntrusivePtr_t<Byte_t> val(new SafeRefCount_t<Byte_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<uint16_t>(const uint16_t& value)
{
  IntrusivePtr_t<UInt16_t> val(new SafeRefCount_t<UInt16_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<uint32_t>(const uint32_t& value)
{
  IntrusivePtr_t<UInt32_t> val(new SafeRefCount_t<UInt32_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<uint64_t>(const uint64_t& value)
{
  IntrusivePtr_t<UInt64_t> val(new SafeRefCount_t<UInt64_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<float>(const float& value)
{
  IntrusivePtr_t<Float_t> val(new SafeRefCount_t<Float_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

template<> Status_t BaseDataVariable_t::SetValue<double>(const double& value)
{
  IntrusivePtr_t<Double_t> val(new SafeRefCount_t<Double_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  val->Value(value);

  DateTime_t sourceTimeStamp(UASDK_datetime());
  IntrusivePtr_t<BaseDataType_t> temp = val;
  return HelperBase_t::CreateAndAssignDataValue(GetVariableNode(), temp, sourceTimeStamp);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS
