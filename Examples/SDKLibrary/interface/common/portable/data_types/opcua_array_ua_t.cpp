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

#include "opcua_array_ua_t.h"
#include "utilities.h"
#include "icodec_t.h"
#include "safe_ref_count_t.h"
#include "opcua_anonymous_identity_token_t.h"
#include "opcua_app_description_t.h"
#include "opcua_argument_t.h"
#include "opcua_axis_information_t.h"
#include "opcua_boolean_t.h"
#include "opcua_browse_continuation_point_t.h"
#include "opcua_browse_description_t.h"
#include "opcua_browse_path_result_t.h"
#include "opcua_browse_path_t.h"
#include "opcua_browse_path_target_t.h"
#include "opcua_browse_result_t.h"
#include "opcua_byte_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_call_method_request_t.h"
#include "opcua_call_method_result_t.h"
#include "opcua_data_change_filter_t.h"
#include "opcua_data_value_t.h"
#include "opcua_date_time_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_double_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_enum_value_type_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_extensible_parameter_t.h"
#include "opcua_float_t.h"
#include "opcua_guid_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_mon_item_create_request_t.h"
#include "opcua_mon_item_create_result_t.h"
#include "opcua_mon_item_modify_request_t.h"
#include "opcua_mon_item_modify_result_t.h"
#include "opcua_mon_item_notification_t.h"
#include "opcua_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_read_value_id_t.h"
#include "opcua_reference_description_t.h"
#include "opcua_relative_path_element_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_status_code_t.h"
#include "opcua_subscription_acknowledgement_t.h"
#include "opcua_transfer_result_t.h"
#include "opcua_uint16_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint64_t.h"
#include "opcua_user_token_policy_t.h"
#include "opcua_string_t.h"
#include "opcua_write_value_t.h"
#include "opcua_xml_element_t.h"
#include "opcua_xv_type_t.h"
#include "opcua_complex_number_type_t.h"
#include "opcua_double_complex_number_type_t.h"
#include "opcua_server_on_network_t.h"
#include "opcua_add_nodes_result_t.h"
#include "opcua_parsing_result_t.h"
#include "opcua_querydata_set_t.h"
#include "opcua_add_nodes_item_t.h"
#include "opcua_delete_nodes_item_t.h"
#include "opcua_add_references_item_t.h"
#include "opcua_delete_references_item_t.h"
#include "opcua_nodetype_description_t.h"
#include "opcua_querydata_description_t.h"
#include "opcua_extensible_parameter_t.h"
#include "opcua_discovery_configuration_t.h"
#include "opcua_signed_software_certificate.h"

#if (UASDK_INCLUDE_EVENTS > 0)
#include "filter_operand_t.h"
#include "simple_attribute_operand_t.h"
#include "content_filter_element_t.h"
#include "opcua_event_field_list_t.h"
#include "content_filter_element_result_t.h"
#include "opcua_semantic_change_structure_data_type_t.h"
#include "opcua_model_change_structure_data_type_t.h"
#endif // UASDK_INCLUDE_EVENTS

#if(UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS > 0)
#include "opcua_subscription_diagnostics_data_type_t.h"
#endif  //UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS

#if(UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)
#include "opcua_session_diagnostics_data_type_t.h"
#endif  //(UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ArrayUA_Base_t, BaseDataType_t)

int32_t GetNumOfArrayDimensions(const IntrusivePtr_t<ArrayUA_t<Int32_t> >& dimension)
{
  uint32_t count = 1;

  if(dimension.is_set())
  {
    count = dimension->Size();
    if (count <= 0)
    {
      count = 1;
    }
  }

  return (int32_t)(count);
}

Status_t CalculateDepthOfVector(const Array_t<IndexRange_t>& indexRanges, Array_t<IndexRange_t>& depth)
{
  Status_t status;
  status = depth.Initialise(1);
  if(status.IsBad())
  {
    return status;
  }

  int32_t vectorDepthPosition = indexRanges.Size() - 1;
  depth[0].start = indexRanges[vectorDepthPosition].start;
  depth[0].end = indexRanges[vectorDepthPosition].end;
  return OpcUa_Good;
}

Status_t CalculateTotalLength(const Array_t<IndexRange_t>& indexRanges, const int32_t& numOfIndexRange,
                              const IntrusivePtr_t<ArrayUA_t<Int32_t> >& dimension, const uint32_t& size,
                              Array_t<uint32_t>& arrayDimensionLength, Array_t<uint32_t>& lengthInEachRange, uint32_t& totalLengthToCopy)
{
  Status_t status;

  status = lengthInEachRange.Initialise(numOfIndexRange);
  if(status.IsBad())
  {
    return status;
  }
  status = arrayDimensionLength.Initialise(numOfIndexRange);
  if(status.IsBad())
  {
    return status;
  }

  totalLengthToCopy = 1;

  for(int32_t i = 0; i < numOfIndexRange; i++)
  {
    if(numOfIndexRange > 1)
    {
      IntrusivePtr_t<Int32_t> dimensionLength = (*dimension)[i];
      if(!dimensionLength.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
      arrayDimensionLength[i] = (uint32_t)dimensionLength->Value();
    }
    else
    {
      arrayDimensionLength[i] = size;
    }

    IndexRange_t indexRange = indexRanges[i];
    if((indexRange.end < indexRange.start) || (indexRange.start >= arrayDimensionLength[i]))
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
    }

    if( indexRange.end < arrayDimensionLength[i] )
    {
      lengthInEachRange[i] = (indexRange.end - indexRange.start + 1);
    }
    else
    {
      lengthInEachRange[i] = (arrayDimensionLength[i] - indexRange.start);
    }

    totalLengthToCopy = totalLengthToCopy * lengthInEachRange[i];
  }

  return OpcUa_Good;
}

Status_t CalculateIndices(const Array_t<IndexRange_t>& indexRanges, const uint32_t& totalLengthToCopy, const int32_t& numOfIndexRange,
                          const Array_t<uint32_t>& arrayDimensionLength, const Array_t<uint32_t>& lengthInEachRange, Array_t<uint32_t>& indices)
{
  Status_t status;
  status = indices.Initialise(totalLengthToCopy);
  if(status.IsBad())
  {
    return status;
  }

  for(int32_t i = (numOfIndexRange - 1); i >= 0; i--)
  {
    //Calculate the source array size till this dimension
    uint32_t arraySizeTillNow = 1;
    if(i == 1)
    {
      arraySizeTillNow = arraySizeTillNow * arrayDimensionLength[i];
    }
    else if(i > 0)
    {
      for(int32_t j = 0; j < i; j++)
      {
        arraySizeTillNow = arraySizeTillNow * arrayDimensionLength[j];
      }
    }

    //Calculate length to be copied till this dimension length
    uint32_t lengthToBeCopiedTillNow = 1;
    if(i == 1)
    {
      lengthToBeCopiedTillNow = lengthToBeCopiedTillNow * lengthInEachRange[i];
    }
    else if(i > 0)
    {
      for(int32_t j = 0; j < i; j++)
      {
        lengthToBeCopiedTillNow = lengthToBeCopiedTillNow * lengthInEachRange[j];
      }
    }

    //Calculate the index to be copied
    {
      uint32_t start = indexRanges[i].start;
      uint32_t end = indexRanges[i].end;
      if(numOfIndexRange > 1)
      {
        if(i == 1)
        {
          start = indexRanges[0].start;
          end = indexRanges[0].end;
        }
        else if(i == 0)
        {
          start = indexRanges[1].start;
          end = indexRanges[1].end;
        }
      }

      uint32_t val = start;
      for(uint32_t m = 0; m < totalLengthToCopy; m++)
      {
        for(uint32_t n = 0; ((n < lengthToBeCopiedTillNow) && val); n++)
        {
          indices[m] += (val * arraySizeTillNow);
          if(n < (lengthToBeCopiedTillNow - 1))
          {
            m++;
          }
        }

        val++;
        if(val > end)
        {
          val = start;
        }
      }
    }
  }

  //To Verify Indices is in the range!
  {
    uint32_t totalArraySize = 1;
    uint32_t lengthOfDimension = arrayDimensionLength.Size();
    for(uint32_t i = 0; i < lengthOfDimension; i++)
    {
      totalArraySize = totalArraySize * arrayDimensionLength[i];
    }

    uint32_t lengthOfIndices = indices.Size();
    for(uint32_t i = 0; i < lengthOfIndices; i++)
    {
      if(indices[i] >= totalArraySize)
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
    }
  }

  return OpcUa_Good;
}

template<typename T>
bool ArrayUA_t<T>::operator==( const ArrayUA_t<T>& obj ) const
{
  uint32_t count = Size();
  if (count != obj.Size())
  {
    return false;
  }

  for (uint32_t i = 0; i < count; i++)
  {
    const IntrusivePtr_t<T> val1 = payload[i];
    const IntrusivePtr_t<T> val2 = obj.payload[i];
    if (!val1.is_set() || !val2.is_set())
    {
      return false;
    }
    if (!(*val1 == *val2))
    {
      return false;
    }
  }
  return true;
}

template<typename T>
bool ArrayUA_t<T>::operator>(ArrayUA_t<T> const & obj) const
{
  uint32_t count = Size();
  if (count != obj.Size())
  {
    return false;
  }

  for (uint32_t i = 0; i < count; i++)
  {
    const IntrusivePtr_t<T> val1 = payload[i];
    const IntrusivePtr_t<T> val2 = obj.payload[i];
    if (!val1.is_set() || !val2.is_set())
    {
      return false;
    }
    if (!(*val1 > *val2))
    {
      return false;
    }
  }
  return true;
}

template<typename T>
const IntrusivePtr_t<T>& ArrayUA_t<T>::operator[](uint32_t i) const
{
  return payload[i];
}

template<typename T>
IntrusivePtr_t<T>& ArrayUA_t<T>::operator[](uint32_t i)
{
  return payload[i];
}

template<typename T>
Status_t ArrayUA_t<T>::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

template<typename T>
Status_t ArrayUA_t<T>::CopyFromByteString(const ByteString_t& source)
{
  UASDK_UNUSED(source);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

template<>
Status_t ArrayUA_t<Byte_t>::CopyFromByteString(const ByteString_t& source)
{
  DeleteAll();

  int32_t length = source.Length();
  if(length <= 0)
  {
    return OpcUa_Good;
  }

  Status_t status = Initialise(length);
  if(status.IsBad())
  {
    return status;
  }
  const uint8_t* sourceData = source.Data();
  for(int32_t i = 0; i < length; i++)
  {
    IntrusivePtr_t<Byte_t> item (new SafeRefCount_t<Byte_t>());
    if (!item.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    item->Value(sourceData[i]);

    payload[i] = item;
  }

  return OpcUa_Good;
}

template<typename T>
Status_t ArrayUA_t<T>::CopyFrom(const BaseDataType_t& source)
{
  uint16_t type = 0;
  if((TypeId(type) == OpcUaId_Byte) && (source.TypeId(type) == OpcUaId_ByteString))
  {
    const ByteString_t* temp = RuntimeCast<const ByteString_t *>(source);
    if(!temp)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
    }
    return CopyFromByteString(*temp);
  }

  const ArrayUA_t<T>*  ptr = RuntimeCast<const ArrayUA_t<T> *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

template<typename T>
Status_t ArrayUA_t<T>::CopyFrom(const ArrayUA_t<T>& source)
{
  uint32_t count = source.Size();
  Status_t status;

  DeleteAll();
  status = Initialise(count);
  if(status.IsBad())
  {
    return status;
  }

  for(uint32_t i = 0; i < count; i++)
  {
    IntrusivePtr_t<T> item = source.payload[i];
    if (!item.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }

    IntrusivePtr_t<BaseDataType_t> val;

    status = item->CopyTo(val);
    if(status.IsBad())
    {
      return status;
    }

    payload[i] = RuntimeCast<T *>(*val);
  }

  if(source.Dimensions().is_set())
  {
    if(source.Dimensions()->Size() > 0)
    {
      IntrusivePtr_t<ArrayUA_t<Int32_t> > dimensions_(new SafeRefCount_t<ArrayUA_t<Int32_t> >());
      if(!dimensions_.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }
      status = dimensions_->CopyFrom(*(source.Dimensions()));
      if(status.IsBad())
      {
        return status;
      }

      dimensions = dimensions_;
    }
  }

  return status;
}

template<typename T>
Status_t ArrayUA_t<T>::WriteSubsetTo(const Array_t<IndexRange_t>& indexRanges, IntrusivePtr_t<BaseDataType_t>& destination) const
{
  Status_t status;
  bool isVector = false;
  Array_t<IndexRange_t> depth;

  if(indexRanges.Count() <= 0)
  {
    return CopyTo(destination);
  }

  int32_t  numOfArrayDimensions = GetNumOfArrayDimensions(dimensions);
  int32_t   numOfIndexRange = indexRanges.Size();

  isVector = IsVector(*this);
  if(!isVector)
  {
    if( numOfArrayDimensions != numOfIndexRange )
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
    }
  }
  else
  {
    if( (numOfArrayDimensions != numOfIndexRange) && ((numOfArrayDimensions + 1) != numOfIndexRange) )
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
    }

    if((numOfArrayDimensions + 1) == numOfIndexRange)
    {
      status = CalculateDepthOfVector(indexRanges, depth);
      if(status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      numOfIndexRange--;
    }
  }

  //Calculate Total Length to copy
  Array_t<uint32_t> arrayDimensionLength;
  Array_t<uint32_t> lengthInEachRange;
  uint32_t totalLengthToCopy = 1;

  status = CalculateTotalLength(indexRanges, numOfIndexRange, dimensions, Size(), arrayDimensionLength, lengthInEachRange, totalLengthToCopy);
  if(status.IsBad())
  {
    return status;
  }

  //Calculate the indices to be copied!
  Array_t<uint32_t> indices;
  status = CalculateIndices(indexRanges, totalLengthToCopy, numOfIndexRange, arrayDimensionLength, lengthInEachRange, indices);
  if(status.IsBad())
  {
    return status;
  }

  //Now Write to Destination
  {
    IntrusivePtr_t< ArrayUA_t<T> > ptr(new SafeRefCount_t< ArrayUA_t<T> >() );
    if(!ptr.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }

    status = ptr->Initialise(totalLengthToCopy);
    if(status.IsBad())
    {
      return status;
    }

    uint32_t index = 0;
    for(uint32_t i = 0; i < totalLengthToCopy; i++)
    {
      IntrusivePtr_t<BaseDataType_t> val;

      index = indices[i];
      IntrusivePtr_t<T> data = payload[index];
      if(!data.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      status = data->WriteSubsetTo(depth, val);
      if(status.IsBad() || !val.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      (*ptr)[i] = RuntimeCast<T *>(*val);
     }

    //Calculate Dimensions
    IntrusivePtr_t<ArrayUA_t<Int32_t> > newDimensions(new SafeRefCount_t<ArrayUA_t<Int32_t> >());
    if(!newDimensions.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    if((numOfIndexRange > 1) && (totalLengthToCopy/numOfIndexRange > 0))
    {
      status = newDimensions->Initialise((uint32_t)numOfIndexRange);
      if(status.IsBad())
      {
        return status;
      }

      for(int32_t i = 0; i < numOfIndexRange; i++)
      {
        IntrusivePtr_t<Int32_t> dimension(new SafeRefCount_t<Int32_t>());
        if(!dimension.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
        }

        dimension->Value((int32_t)lengthInEachRange[i]);

        (*newDimensions)[i] = dimension;
      }

      ptr->Dimensions() = newDimensions;
    }

    destination = ptr;
  }

  return OpcUa_Good;
}

template<typename T>
Status_t ArrayUA_t<T>::WriteSubsetFrom(const Array_t<IndexRange_t>& indexRanges, const BaseDataType_t& source)
{
  /*
   * Example for Index range: for 4x4 array Index Range will be like:
   *
   * "1:2,1:3" or
   * "1:2,1:3,5:8" - for ByteString/String/XmlElement - here 5:8 is optional
   */
  Status_t status = OpcUa_Good;
  bool isVector = false;
  Array_t<IndexRange_t> depth;

  if(indexRanges.Size() <= 0)
  {
    return CopyFrom(source);
  }

  const ArrayUA_t<T>* sourceArray = RuntimeCast<const ArrayUA_t<T> * >(source);
  IntrusivePtr_t<ArrayUA_t<T> > tempArray;
  if(!sourceArray)
  {
    uint16_t type = 0;
    if(TypeId(type) == OpcUaId_Byte)
    {
      const ByteString_t* temp = RuntimeCast<const ByteString_t * >(source);
      if(temp)
      {
        tempArray = new SafeRefCount_t<ArrayUA_t<T> >();
        Status_t status = tempArray->CopyFromByteString(*temp);
        if(status.IsBad())
        {
          return status;
        }
        sourceArray = tempArray.get();
      }
      else
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
      }
    }
    else
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
    }
  }

  int32_t  numOfArrayDimensions = GetNumOfArrayDimensions(dimensions);
  int32_t  numOfSourceDimensions = GetNumOfArrayDimensions(sourceArray->dimensions);
  int32_t   numOfIndexRange = indexRanges.Size();
  isVector = IsVector(*sourceArray);
  if(!isVector)
  {
    if( numOfArrayDimensions != numOfIndexRange )
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
    }
  }
  else
  {
    if( (numOfArrayDimensions != numOfIndexRange) && ((numOfArrayDimensions + 1) != numOfIndexRange) )
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
    }

    //Calculate the depth of bytes to be copied from vector datatypes like ByteString, String and XmlElement.
    //In the example "1:2,1:3,5:8" - extract 5:8
    if((numOfSourceDimensions + 1) == numOfIndexRange)
    {
      status = CalculateDepthOfVector(indexRanges, depth);
      if(status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      numOfIndexRange--;
    }
  }

  //Calculate Total Length to copy
  Array_t<uint32_t> arrayDimensionLength;
  Array_t<uint32_t> lengthInEachRange;
  uint32_t totalLengthToCopy = 1;

  status = CalculateTotalLength(indexRanges, numOfIndexRange, dimensions, Size(), arrayDimensionLength, lengthInEachRange, totalLengthToCopy);
  if(status.IsBad())
  {
    return status;
  }

  //Calculate the indices to be copied!
  Array_t<uint32_t> indices;
  status = CalculateIndices(indexRanges, totalLengthToCopy, numOfIndexRange, arrayDimensionLength, lengthInEachRange, indices);
  if(status.IsBad())
  {
    return status;
  }

  //Now Write source to this array
  for(uint32_t i = 0; i < totalLengthToCopy; i++)
  {
    IntrusivePtr_t<BaseDataType_t> val;
    uint32_t index = indices[i];
    IntrusivePtr_t<T> data = (*sourceArray)[i];
    if(!data.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }

    if(!depth.IsEmpty())
    {
      status = payload[index]->WriteSubsetFrom(depth, *data );
      if(status.IsBad())
      {
        return status;
      }
    }
    else
    {
      IntrusivePtr_t<BaseDataType_t> val;

      status = data->CopyTo(val);
      if(status.IsBad())
      {
        return status;
      }

      payload[index] = RuntimeCast<T *>(*val);
    }
  }

  return OpcUa_Good;
}

template<typename T>
Status_t ArrayUA_t<T>::Initialise(uint32_t size)
{
  return payload.Initialise(size);
}

template <typename A>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<A>& result);

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<BaseDataType_t>& result);

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<Structure_t>& result);

template<typename T>
Status_t ArrayUAEncode(const IntrusivePtr_t<T>& obj, ICodec_t& encoder, IBuffer_t& buffer);

template<>
Status_t ArrayUAEncode(const IntrusivePtr_t<BaseDataType_t>& obj, ICodec_t& encoder, IBuffer_t& buffer);

template<>
Status_t ArrayUAEncode(const IntrusivePtr_t<Structure_t>& obj, ICodec_t& encoder, IBuffer_t& buffer);

template<typename T>
Status_t ArrayUA_t<T>::EncodeExtensionObjects(ICodec_t& encoder, IBuffer_t& buffer) const
{
  UInt32_t no_of_elements(payload.Size());

  Status_t status = no_of_elements.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  for (uint32_t i = 0; i < no_of_elements.Value(); i++)
  {
    const IntrusivePtr_t<T> obj = payload[i];
    if ((!obj.is_set()))
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
    }

    const BaseDataType_t& base = *obj;
    const Structure_t* structure = RuntimeCast<const Structure_t*>(base);
    if (structure == 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
    }

    status = encoder.EncodeExtensionObject(structure, buffer);
    if (status.IsBad())
    {
      return status;
    }
  }

  return OpcUa_Good;
}

template<typename T>
Status_t ArrayUA_t<T>::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  UInt32_t no_of_elements(payload.Size());

  Status_t status = no_of_elements.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  for (uint32_t i = 0; i < no_of_elements.Value(); i++)
  {
    const IntrusivePtr_t<T> obj = payload[i];
    status = ArrayUAEncode(obj, encoder, buffer);
    if (status.IsBad())
    {
      return status;
    }
  }

  return OpcUa_Good;
}

template<typename T>
Status_t ArrayUA_t<T>::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ArrayUA_t<T>& result)
{
  Int32_t number_of_elements(0);
  Status_t status = Int32_t::Decode(buffer, decoder, number_of_elements);
  if (status.IsBad())
  {
    return status;
  }

  if (number_of_elements.Value() >= 0)
  {
    status = result.payload.Initialise(number_of_elements.Value());
  }
  else
  {
    status = result.payload.Initialise(0);
  }
  if (status.IsBad())
  {
    return status;
  }

  uint32_t count = result.payload.Size();
  for (uint32_t i = 0; i < count; i++)
  {
    IntrusivePtr_t<T> ptr;
    status = ArrayUADecode(buffer, decoder, ptr);
    if (status.IsBad())
    {
      return status;
    }
    result.payload[i] = ptr;
  }

  return 0;
}

template <typename A>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                       ICodec_t& decoder,
                       IntrusivePtr_t<A>& result)
{
  result = new SafeRefCount_t<A>();
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  return A::Decode(buffer, decoder, *result);
}

#if (UASDK_INCLUDE_EVENTS > 0)
template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
  ICodec_t& decoder,
  IntrusivePtr_t<FilterOperand_t>& result)
{
  return FilterOperand_t::Decode(buffer, decoder, result);
}

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
  ICodec_t& decoder,
  IntrusivePtr_t<SimpleAttributeOperand_t>& result)
{
  return SimpleAttributeOperand_t::Decode(buffer, decoder, result);
}

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
  ICodec_t& decoder,
  IntrusivePtr_t<ContentFilterElement_t>& result)
{
  return ContentFilterElement_t::Decode(buffer, decoder, result);
}

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
  ICodec_t& decoder,
  IntrusivePtr_t<EventFieldList_t>& result)
{
  return EventFieldList_t::Decode(buffer, decoder, result);
}
#endif // UASDK_INCLUDE_EVENTS

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<const NodeId_t>& result)
{
  IntrusivePtr_t<NodeId_t> temp;
  Status_t status = NodeId_t::Decode(buffer, decoder, temp);
  if (status.IsGood())
  {
    result = temp;
  }
  return status;
}

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<NodeId_t>& result)
{
  return NodeId_t::Decode(buffer, decoder, result);
}

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<BaseDataType_t>& result)
{
  return BaseDataType_t::Decode(buffer, decoder, result);
}

template <>
Status_t ArrayUADecode(const IBuffer_t& buffer,
                            ICodec_t& decoder,
                            IntrusivePtr_t<Structure_t>& result)
{
  return Structure_t::Decode(buffer, decoder, result);
}

template<typename T>
Status_t ArrayUAEncode(const IntrusivePtr_t<T>& obj, ICodec_t& encoder, IBuffer_t& buffer)
{
  if (!obj.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }
  return obj->Encode(encoder, buffer);
}

template<>
Status_t ArrayUAEncode(const IntrusivePtr_t<BaseDataType_t>& obj, ICodec_t& encoder, IBuffer_t& buffer)
{
  return encoder.EncodeVariant(obj, buffer);
}

template<>
Status_t ArrayUAEncode(const IntrusivePtr_t<Structure_t>& obj, ICodec_t& encoder, IBuffer_t& buffer)
{
  return encoder.EncodeExtensionObject(obj, buffer);
}

template <typename A>
bool ArrayUAIsNumber(void)
{
  A a;
  return a.IsNumber();
}

#if (UASDK_INCLUDE_EVENTS > 0)
template <>
bool ArrayUAIsNumber<ContentFilterElement_t>(void)
{
  return false;
}

template <>
bool ArrayUAIsNumber<FilterOperand_t>(void)
{
  return false;
}

template <>
bool ArrayUAIsNumber<SimpleAttributeOperand_t>(void)
{
  return false;
}

template <>
bool ArrayUAIsNumber<EventFieldList_t>(void)
{
  return false;
}
#endif // UASDK_INCLUDE_EVENTS

template <>
bool ArrayUAIsNumber<const NodeId_t>(void)
{
  return false;
}

template <>
bool ArrayUAIsNumber<NodeId_t>(void)
{
  return false;
}

template <>
bool ArrayUAIsNumber<BaseDataType_t>(void)
{
  return false;
}

template <>
bool ArrayUAIsNumber<Structure_t>(void)
{
  return false;
}

template<typename T>
bool ArrayUA_t<T>::IsNumber(void) const
{
  return ArrayUAIsNumber<T>();
}

template<typename T>
int32_t ArrayUA_t<T>::ValueRank(void) const
{
  if (!dimensions.is_set() || (dimensions->Size() == 0))
  {
    return 1;
  }
  else
  {
    return dimensions->Size();
  }
}

template<typename T>
uint32_t ArrayUA_t<T>::Size(void) const
{
  return payload.Size();
}

template<typename T>
void ArrayUA_t<T>::DeleteAll(void)
{
  payload.Initialise(0);
}

template<typename T>
IntrusivePtr_t<const ArrayUA_t<Int32_t> > ArrayUA_t<T>::Dimensions(void) const
{
  return dimensions;
}

template<typename T>
IntrusivePtr_t<ArrayUA_t<Int32_t> >& ArrayUA_t<T>::Dimensions(void)
{
  return dimensions;
}

template<typename T>
inline uint32_t ArrayUA_t<T>::TypeId(uint16_t & namespaceIndex) const
{
	UASDK_UNUSED(namespaceIndex);
	return T::TYPE_ID;
}

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)
template class ArrayUA_t<ServerOnNetwork_t>;
template class ArrayUA_t<MdnsDiscoveryConfiguration_t>;
#endif

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)
template class ArrayUA_t<CallMethodRequest_t>;
template class ArrayUA_t<CallMethodResult_t>;
template class ArrayUA_t<Argument_t>;
#endif

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)
template class ArrayUA_t<AddNodesResult_t>;
template class ArrayUA_t<AddNodesItem_t>;
template class ArrayUA_t<DeleteNodesItem_t>;
template class ArrayUA_t<AddReferencesItem_t>;
template class ArrayUA_t<DeleteReferencesItem_t>;
#endif

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)
template class ArrayUA_t<ParsingResult_t>;
template class ArrayUA_t<QueryDataSet_t>;
template class ArrayUA_t<NodeTypeDescription_t>;
template class ArrayUA_t<QueryDataDescription_t>;
#endif

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)
template class ArrayUA_t<AxisInformation_t>;
template class ArrayUA_t<XVType_t>;
template class ArrayUA_t<ComplexNumberType_t>;
template class ArrayUA_t<DoubleComplexNumberType_t>;
#endif

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)
template class ArrayUA_t<MonItemCreateRequest_t>;
template class ArrayUA_t<MonItemCreateResult_t>;
template class ArrayUA_t<MonItemModifyRequest_t>;
template class ArrayUA_t<MonItemModifyResult_t>;
template class ArrayUA_t<SubscriptionAcknowledgment_t>;
template class ArrayUA_t<MonItemNotification_t>;
template class ArrayUA_t<DataChangeFilter_t>;
#endif

#if ( UASDK_INCLUDE_SUBSCRIPTIONS > 0 && UASDK_INCLUDE_TRANSFER_SUBSCRIPTIONS_SERVICE > 0)
template class ArrayUA_t<TransferResult_t>;
#endif

template class ArrayUA_t<BaseDataType_t>;
template class ArrayUA_t<String_t>;
template class ArrayUA_t<XmlElement_t>;
template class ArrayUA_t<NodeId_t>;
template class ArrayUA_t<DateTime_t>;
template class ArrayUA_t<DataValue_t>;
template class ArrayUA_t<ByteString_t>;
template class ArrayUA_t<Boolean_t>;
template class ArrayUA_t<Byte_t>;
template class ArrayUA_t<SByte_t>;
template class ArrayUA_t<UInt16_t>;
template class ArrayUA_t<Int16_t>;
template class ArrayUA_t<UInt32_t>;
template class ArrayUA_t<Int32_t>;
template class ArrayUA_t<UInt64_t>;
template class ArrayUA_t<Int64_t>;
template class ArrayUA_t<Float_t>;
template class ArrayUA_t<Double_t>;
template class ArrayUA_t<LocalizedText_t>;
template class ArrayUA_t<QualifiedName_t>;
template class ArrayUA_t<DiagnosticInfo_t>;
template class ArrayUA_t<ExpandedNodeId_t>;
template class ArrayUA_t<Guid_t>;
template class ArrayUA_t<EndpointDescription_t>;
template class ArrayUA_t<UserTokenPolicy_t>;
template class ArrayUA_t<ReferenceDescription_t>;
template class ArrayUA_t<BrowseResult_t>;
template class ArrayUA_t<BrowseDescription_t>;
template class ArrayUA_t<ReadValueId_t>;
template class ArrayUA_t<WriteValue_t>;
template class ArrayUA_t<BrowsePath_t>;
template class ArrayUA_t<BrowsePathTarget_t>;
template class ArrayUA_t<BrowsePathResult_t>;
template class ArrayUA_t<RelativePathElement_t>;
template class ArrayUA_t<AppDescription_t>;
template class ArrayUA_t<BrowseContinuationPoint_t>;
template class ArrayUA_t<Structure_t>;
template class ArrayUA_t<StatusCode_t>;
template class ArrayUA_t<EnumValueType_t>;
template class ArrayUA_t<ExtensibleParameter_t>;

#if (UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS > 0)
template class ArrayUA_t<SubscriptionDiagnosticsDataType_t>;
#endif  //UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS

#if(UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)
template class ArrayUA_t<SessionDiagnosticsDataType_t>;
#endif  //(UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)

template class ArrayUA_t<SignedSoftwareCertificate_t>;

#if (UASDK_INCLUDE_EVENTS > 0)
template class ArrayUA_t<SimpleAttributeOperand_t>;
template class ArrayUA_t<EventFieldList_t>;
template class ArrayUA_t<ContentFilterElementResult_t>;
template class ArrayUA_t<ContentFilterElement_t>;
template class ArrayUA_t<FilterOperand_t>;
template class ArrayUA_t<SemanticChangeStructureDataType_t>;
template class ArrayUA_t<ModelChangeStructureDataType_t>;
#endif /* UASDK_INCLUDE_EVENTS */

} // namespace uasdk
