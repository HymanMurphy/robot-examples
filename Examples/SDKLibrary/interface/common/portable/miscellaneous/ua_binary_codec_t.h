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

#ifndef _UA_BINARY_CODEC_T_
#define _UA_BINARY_CODEC_T_

#include "icodec_t.h"
#include "allocatable_t.h"
#include "opcua_node_id_t.h"

namespace uasdk
{

class UABinaryCodec_t : public ICodec_t, public Allocatable_t
{
private:
  class StackDepth_t
  {
  private:
    const uint32_t MAX_STACK_DEPTH;
    uint32_t& currentStackDepth;

  public:
    StackDepth_t(uint32_t MAX_STACK_DEPTH_, uint32_t& currentStackDepth_) :
      MAX_STACK_DEPTH(MAX_STACK_DEPTH_), currentStackDepth(currentStackDepth_)
    {
      currentStackDepth++;
    }

    ~StackDepth_t()
    {
      currentStackDepth--;
    }

    bool Exceeded(void)
    {
      return (currentStackDepth > MAX_STACK_DEPTH);
    }

  };

  typedef enum
  {
    VARIANT_ENCODING_MASK_NULL            = 0,
    VARIANT_ENCODING_MASK_BOOLEAN         = 1,
    VARIANT_ENCODING_MASK_SBYTE           = 2,
    VARIANT_ENCODING_MASK_BYTE            = 3,
    VARIANT_ENCODING_MASK_INT16           = 4,
    VARIANT_ENCODING_MASK_UINT16          = 5,
    VARIANT_ENCODING_MASK_INT32           = 6,
    VARIANT_ENCODING_MASK_UINT32          = 7,
    VARIANT_ENCODING_MASK_INT64           = 8,
    VARIANT_ENCODING_MASK_UINT64          = 9,
    VARIANT_ENCODING_MASK_FLOAT           = 10,
    VARIANT_ENCODING_MASK_DOUBLE          = 11,
    VARIANT_ENCODING_MASK_STRING          = 12,
    VARIANT_ENCODING_MASK_DATETIME        = 13,
    VARIANT_ENCODING_MASK_GUID            = 14,
    VARIANT_ENCODING_MASK_BYTESTRING      = 15,
    VARIANT_ENCODING_MASK_XMLELEMENT      = 16,
    VARIANT_ENCODING_MASK_NODEID          = 17,
    VARIANT_ENCODING_MASK_EXPANDEDNODEID  = 18,
    VARIANT_ENCODING_MASK_STATUSCODE      = 19,
    VARIANT_ENCODING_MASK_QUALIFIEDNAME   = 20,
    VARIANT_ENCODING_MASK_LOCALIZEDTEXT   = 21,
    VARIANT_ENCODING_MASK_EXTENSIONOBJECT = 22,
    VARIANT_ENCODING_MASK_DATAVALUE       = 23,
    VARIANT_ENCODING_MASK_VARIANT         = 24,
    VARIANT_ENCODING_MASK_DIAGNOSTICINFO  = 25,

    VARIANT_ENCODING_MASK_ARRAY_DIMS_FIELD = (1<<6),
    VARIANT_ENCODING_MASK_ARRAY_OF_VALUES = (1<<7)
  } Variant_Encoding_Mask_t;

  static const uint8_t VARIANT_TYPE_MASK = 0x3F;

  typedef enum
  {
    EXTENSION_OBJECT_ENCODING_NONE                = 0,
    EXTENSION_OBJECT_ENCODING_BINARY              = 1,
    EXTENSION_OBJECT_ENCODING_XML                 = 2
  } Extension_Object_Encoding_t;

  typedef enum
  {
    LOCALIZED_TEXT_ENCODING_LOCALE_PRESENT  = 0x01,
    LOCALIZED_TEXT_ENCODING_TEXT_PRESENT    = 0x02
  } LocalizedTextEncoding_t;

  typedef enum
  {
    DATAVALUE_ENCODING_MASK_VALUE_PRESENT               = 0x01,
    DATAVALUE_ENCODING_MASK_STATUS_CODE_PRESENT         = 0x02,
    DATAVALUE_ENCODING_MASK_SOURCE_TIMESTAMP_PRESENT    = 0x04,
    DATAVALUE_ENCODING_MASK_SERVER_TIMESTAMP_PRESENT    = 0x08,
    DATAVALUE_ENCODING_MASK_SOURCE_PICOSECONDS_PRESENT  = 0x10,
    DATAVALUE_ENCODING_MASK_SERVER_PICOSECONDS_PRESENT  = 0x20
  } DataValueEncodingMask_t;

  typedef enum
  {
    NODE_ENCODING_TWO_BYTE            = 0x00,
    NODE_ENCODING_FOUR_BYTE           = 0x01,
    NODE_ENCODING_NUMERIC             = 0x02,
    NODE_ENCODING_STRING              = 0x03,
    NODE_ENCODING_GUID                = 0x04,
    NODE_ENCODING_BYTESTRING          = 0x05,
    NODE_ENCODING_NAMESPACE_URI_FLAG  = 0x80,
    NODE_ENCODING_SERVER_INDEX_FLAG   = 0x40,
    NODE_ENCODING_TYPE_MASK           = 0x3F
  } NodeEncoding_t;

  typedef enum
  {
    DIAGNOSTIC_INFO_ENCODING_SYMBOLIC_ID            = 0x01,
    DIAGNOSTIC_INFO_ENCODING_NAMESPACE              = 0x02,
    DIAGNOSTIC_INFO_ENCODING_LOCALIZED_TEXT         = 0x04,
    DIAGNOSTIC_INFO_ENCODING_LOCALE                 = 0x08,
    DIAGNOSTIC_INFO_ENCODING_ADDITIONAL_INFO        = 0x10,
    DIAGNOSTIC_INFO_ENCODING_INNER_STATUS_CODE      = 0x20,
    DIAGNOSTIC_INFO_ENCODING_INNER_DIAGNOSTIC_INFO  = 0x40
  } DiagnosticInfoEncoding_t;

  uint32_t maxStackDepth;
  uint32_t currentStackDepth;

  Status_t EncodeVariant(IBuffer_t& buffer, bool hasArrayDimensions);

  template<typename T>
  Status_t DecodeVariantValue(const IBuffer_t& buffer,
                              IntrusivePtr_t<BaseDataType_t>& result)
  {
    IntrusivePtr_t<T> value = new SafeRefCount_t<T>();
    if (!value.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    Status_t status = T::Decode(buffer, *this, *value);
    if (status.IsBad())
    {
      return status;
    }

    result = value;
    return status;
  }

  template<typename T>
  Status_t EncodeNumber(const T& value, IBuffer_t& buffer);

  template<typename T>
  Status_t DecodeNumber(const IBuffer_t& buffer, T& value);

  template<typename T>
  Status_t Encode(const NodeId_t& value,
                  uint8_t encoding,
                  const T& identifier,
                  IBuffer_t& buffer);

  Status_t DecodeNumericNodeId(const IBuffer_t& buffer,
                  NodeEncoding_t encodingMask,
                  NodeIdNumeric_t& result);

  Status_t DecodeNodeId(const IBuffer_t& buffer,
                       NodeEncoding_t& encodingMask,
                       IntrusivePtr_t<NodeId_t>& result);

  Status_t Decode(const IBuffer_t& buffer, NodeIdString_t& result);

  Status_t Decode(const IBuffer_t& buffer, NodeIdOpaque_t& result);

  Status_t Decode(const IBuffer_t& buffer, NodeIdGuid_t& result);

  Status_t DecodeKnownType(const IBuffer_t& buffer,
                           const NodeId_t& type_id,
                           IntrusivePtr_t<Structure_t>& result);

public:
  UABinaryCodec_t() : maxStackDepth(100), currentStackDepth(0) {}
  virtual ~UABinaryCodec_t() {}

  Status_t Initialise(uint32_t maxStackDepth_)
  {
    maxStackDepth = maxStackDepth_;
    return OpcUa_Good;
  }

  virtual Status_t Encode(const Boolean_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const SByte_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Byte_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Int16_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const UInt16_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Int32_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const UInt32_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Int64_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const UInt64_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Float_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Double_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const String_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const DateTime_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const Guid_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const ByteString_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const XmlElement_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(IntrusivePtr_t<const NodeId_t> value, IBuffer_t& buffer);

  virtual Status_t Encode(const NodeIdString_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const NodeIdOpaque_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const NodeIdGuid_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const NodeIdNumeric_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const ExpandedNodeId_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const StatusCode_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const QualifiedName_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const LocalizedText_t& value, IBuffer_t& buffer);

  virtual Status_t EncodeExtensionObject(IntrusivePtr_t<const Structure_t> value, IBuffer_t& buffer);

  virtual Status_t EncodeExtensionObject(const Structure_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const DataValue_t& value, IBuffer_t& buffer);

  virtual Status_t EncodeVariant(IntrusivePtr_t<const BaseDataType_t> value, IBuffer_t& buffer);

  virtual Status_t EncodeVariant(const BaseDataType_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const DiagnosticInfo_t& value, IBuffer_t& buffer);

  virtual Status_t Encode(const MessageUA_t& value, IBuffer_t& buffer);

  virtual Status_t Decode(const IBuffer_t& buffer, Boolean_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, SByte_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Byte_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Int16_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, UInt16_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Int32_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, UInt32_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Int64_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, UInt64_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Float_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Double_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, String_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, DateTime_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, Guid_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, ByteString_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, XmlElement_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<NodeId_t>& result);

  virtual Status_t Decode(const IBuffer_t& buffer, ExpandedNodeId_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, StatusCode_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, QualifiedName_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, LocalizedText_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<Structure_t>& result);

  virtual Status_t Decode(const IBuffer_t& buffer, DataValue_t& result);

  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<BaseDataType_t>& result);

  virtual Status_t Decode(const IBuffer_t& buffer, DiagnosticInfo_t& result);

//  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<MessageUA_t>& result);

  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<RequestMessage_t>& result);

  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<ResponseMessage_t>& result);

};

} // namespace uasdk

#endif // _UA_BINARY_CODEC_T_
