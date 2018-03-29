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

#include "data_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

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
#include "node_with_instrument_range_property_value_attribute_reader_writer_t.h"

namespace uasdk
{
/*
 * Private Functions
 */
bool DataItem_t::IsPropertyAllowed(IntrusivePtr_t<const IVariableNode_t> node_)
{
  if (!node_.is_set() || !node_->DataType().is_set())
  {
    return false;
  }

  if(node_.is_set() && node_->DataType().is_set())
  {
    const UInt32_t* dataType = RuntimeCast<const UInt32_t*>(node_->DataType()->IdentiferBase());
    if(dataType)
    {
      uint32_t val = dataType->Value();
      if( (val != OpcUaId_Float) && (val != OpcUaId_Double) && (val != OpcUaId_DateTime) )
      {
        return false;
      }
    }
  }

  return true;
}

IntrusivePtr_t<DataItem_t> DataItem_t::CreateDataItem(IntrusivePtr_t<IVariableNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result)
{
  IntrusivePtr_t<DataItem_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<DataItem_t>());
  if(!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }

  retVal->Initialize(node_, addressSpace_);
  result = OpcUa_Good;
  return retVal;
}

/*
 * Protected Functions
 */

DataItem_t::DataItem_t()
{}

Status_t DataItem_t::CreatePropertyAndAssignValue(DataItem_t& dataItem,
                                                  uint32_t numericId,
                                                  const char* browseName_,
                                                  uint32_t dataTypeId,
                                                  IntrusivePtr_t<BaseDataType_t> destinationValue,
                                                  const BaseDataType_t& sourceValue,
                                                  IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = HelperBase_t::CreateProperty(dataItem, numericId, browseName_, dataTypeId, propertyNode);
  if(status.IsBad())
  {
    return status;
  }

  status = destinationValue->CopyFrom(sourceValue);
  if(status.IsBad())
  {
    return status;
  }

  DateTime_t sourceTime_(UASDK_datetime());
  status = HelperBase_t::CreateAndAssignDataValue(propertyNode, destinationValue, sourceTime_);
  if (status.IsBad())
  {
    return status;
  }

  //To add the Custom reader and Writer for node with Instrument range property

  int32_t length1 = Utilities_t::Strnlen(BROWSE_NAME_INSTRUMENT_RANGE, 100);
  int32_t length2 = Utilities_t::Strnlen(browseName_, 100);

  if ((length1 == length2) && (UASDK_memcmp(browseName_, BROWSE_NAME_INSTRUMENT_RANGE, length1) == 0))
  {
    IntrusivePtr_t<IVariableNode_t> variableNode_ = dataItem.GetVariableNode();
    UASDK_RETURN_UNEXPECTED_IF_NULL(variableNode_);

    //To check if the custom reader and writer already created
    if (!variableNode_->Value().is_set() && variableNode_->ValueAttributeReaderWriter().is_set() )
    {
      return status;
    }

    IntrusivePtr_t<NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t> customReaderWriter(
        new SafeRefCount_t<NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t>());
    if (!customReaderWriter.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = customReaderWriter->Initialize(variableNode_->Value(), propertyNode);
    if(status.IsBad())
    {
      return status;
    }

    if(variableNode_->Value().is_set())
    {
      IntrusivePtr_t<DataValue_t> empty;
      variableNode_->Value(empty);
    }

    status = variableNode_->ValueAttributeReaderWriter(customReaderWriter);
    if (status.IsBad())
    {
      return status;
    }
  }

  return status;
}

void DataItem_t::DeleteProperties(DataItem_t& dataItem)
{
  UASDK_RETURN_IF_NULL(dataItem.addressSpace);

  IntrusivePtr_t<IVariableNode_t> definitionNode = dataItem.DefinitionNode();
  IntrusivePtr_t<IVariableNode_t> valuePrecisionNode = dataItem.ValuePrecisionNode();

  if(definitionNode.is_set() && definitionNode->NodeId().is_set())
  {
    dataItem.addressSpace->RemoveNode( *(definitionNode->NodeId()) );
  }
  if(valuePrecisionNode.is_set() && valuePrecisionNode->NodeId().is_set())
  {
    dataItem.addressSpace->RemoveNode( *(valuePrecisionNode->NodeId()) );
  }
}

/*
 * Public Functions
 */
DataItem_t::~DataItem_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

/*
 * Properties
 */
Status_t DataItem_t::CreateDefinitionProperty(const String_t& value)
{
  IntrusivePtr_t<String_t> val(new SafeRefCount_t<String_t>());
  if(!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = DefinitionNode();
  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_DEFINITION, OpcUaId_String, val, value, propertyNode);
}

Status_t DataItem_t::CreateDefinitionProperty(uint32_t nodeIdentifier, const String_t& value)
{
  IntrusivePtr_t<String_t> val(new SafeRefCount_t<String_t>());
  if(!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = DefinitionNode();
  return DataItem_t::CreatePropertyAndAssignValue(*this, nodeIdentifier, BROWSE_NAME_DEFINITION, OpcUaId_String, val, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> DataItem_t::DefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set() )
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_DEFINITION);
}

IntrusivePtr_t<const IVariableNode_t> DataItem_t::DefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_DEFINITION);
}

IntrusivePtr_t<const String_t> DataItem_t::GetDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const String_t> val;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = DefinitionNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadNoData;
    return val;
  }

  val = RuntimeCast<const String_t *>(*( propertyNode->Value()->Value()) );
  if(!val.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return val;
  }

  result = OpcUa_Good;
  return val;
}

Status_t DataItem_t::SetDefinitionValue(const String_t& value)
{
  return CreateDefinitionProperty(value);
}

Status_t DataItem_t::CreateValuePrecisionProperty(double value)
{
  if( !IsPropertyAllowed(GetVariableNode()) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
  }

  IntrusivePtr_t<Double_t> val(new SafeRefCount_t<Double_t>());
  if(!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Double_t sourceVal(value);
  IntrusivePtr_t<IVariableNode_t> propertyNode = ValuePrecisionNode();
  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_VALUE_PRECISION, OpcUaId_Double, val, sourceVal, propertyNode);
}

Status_t DataItem_t::CreateValuePrecisionProperty(uint32_t nodeIdentifier, double value)
{
  if( !IsPropertyAllowed(GetVariableNode()) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
  }

  IntrusivePtr_t<Double_t> val(new SafeRefCount_t<Double_t>());
  if(!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Double_t sourceVal(value);
  IntrusivePtr_t<IVariableNode_t> propertyNode = ValuePrecisionNode();
  return DataItem_t::CreatePropertyAndAssignValue(*this, nodeIdentifier, BROWSE_NAME_VALUE_PRECISION, OpcUaId_Double, val, sourceVal, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> DataItem_t::ValuePrecisionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_VALUE_PRECISION);
}

IntrusivePtr_t<const IVariableNode_t> DataItem_t::ValuePrecisionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_VALUE_PRECISION);
}

Status_t DataItem_t::GetValuePrecisionValue(double& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = ValuePrecisionNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }

  IntrusivePtr_t<const Double_t> val = RuntimeCast<const Double_t *>(*( propertyNode->Value()->Value()) );
  if(!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  result = val->Value();
  return OpcUa_Good;
}

Status_t DataItem_t::SetValuePrecisionValue(const double value)
{
  return CreateValuePrecisionProperty(value);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<DataItem_t> DataItem_t::Get(const NodeId_t& nodeId,
                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                           Status_t& result)
{
  IntrusivePtr_t<DataItem_t> empty;
  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> dataItemNode = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !dataItemNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(dataItemNode, addressSpace_, result);
}

IntrusivePtr_t<DataItem_t> DataItem_t::Get(IntrusivePtr_t<IVariableNode_t>& node,
                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                           Status_t& result)
{
  IntrusivePtr_t<DataItem_t> empty;
  if(!node.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = HelperBase_t::CheckHasTypeDefinition(*node, *addressSpace_, OpcUaId_DataItemType);
  if(result.IsBad())
  {
    return empty;
  }

  return DataItem_t::CreateDataItem(node, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS
