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

#ifndef _OPCUA_VARIABLE_ATTRIBUTES_T_
#define _OPCUA_VARIABLE_ATTRIBUTES_T_

#include "intrusive_ptr_t.h"
#include "opcua_uint32_t.h"
#include "opcua_int32_t.h"
#include "opcua_byte_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_structure_t.h"
#include "opcua_base_data_type_t.h"
#include "opcua_node_id_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_duration_t.h"
#include "opcua_boolean_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

class VariableAttributes_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(VariableAttributes_t);
private:
	UInt32_t specifiedAttributes;
	LocalizedText_t displayName;
	LocalizedText_t description;
	IntrusivePtr_t<BaseDataType_t> value;
	IntrusivePtr_t<NodeId_t> dataType;
	Int32_t valueRank;
	ArrayUA_t<UInt32_t> arrayDimensions;
	Byte_t accessLevel;
	Byte_t userAccessLevel;
	Duration_t minimumSamplingInterval;
	Boolean_t historizing;
	UInt32_t writeMask;
	UInt32_t userWriteMask;

public:
  static const uint32_t TYPE_ID = OpcUaId_VariableAttributes;

  virtual ~VariableAttributes_t();

  virtual bool operator==(BaseDataType_t const & obj) const;

  bool operator==(VariableAttributes_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  bool operator>(VariableAttributes_t const & obj) const;
  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  Status_t CopyFrom(const VariableAttributes_t& source);
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  UInt32_t& SpecifiedAttributes();
  const UInt32_t& SpecifiedAttributes() const;

  LocalizedText_t& DisplayName();
  const LocalizedText_t& DisplayName() const;

  LocalizedText_t& Description();
  const LocalizedText_t& Description() const;

  IntrusivePtr_t<const BaseDataType_t> Value(void) const;
  IntrusivePtr_t<BaseDataType_t>& Value(void);

  IntrusivePtr_t<const NodeId_t> DataType(void) const;
  IntrusivePtr_t<NodeId_t>& DataType(void);

  Int32_t& ValueRank();
  const Int32_t& ValueRank() const;

  ArrayUA_t<UInt32_t>& ArrayDimensions();
  const ArrayUA_t<UInt32_t>& ArrayDimensions() const;

  Byte_t& AccessLevel();
  const Byte_t& AccessLevel() const;

  Byte_t& UserAccessLevel();
  const Byte_t& UserAccessLevel() const;

  Duration_t& MinimumSamplingInterval();
  const Duration_t& MinimumSamplingInterval() const;

  Boolean_t& Historizing();
  const Boolean_t& Historizing() const;

  UInt32_t& WriteMask();
  const UInt32_t& WriteMask() const;

  UInt32_t& UserWriteMask();
  const UInt32_t& UserWriteMask() const;
  
  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, VariableAttributes_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_VARIABLE_ATTRIBUTES_T_
