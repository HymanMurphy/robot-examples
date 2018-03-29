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

#include "opcua_base_data_type_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_structure_t.h"
#include "opcua_boolean_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_byte_t.h"
#include "opcua_int16_t.h"
#include "opcua_uint16_t.h"
#include "opcua_int32_t.h"
#include "opcua_uint32_t.h"
#include "opcua_int64_t.h"
#include "opcua_uint64_t.h"
#include "opcua_status_code_t.h"
#include "opcua_float_t.h"
#include "opcua_double_t.h"
#include "opcua_xml_element_t.h"
#include "opcua_date_time_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_localized_text_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE_ROOT(BaseDataType_t)

Status_t BaseDataType_t::Decode(const IBuffer_t& buffer,
                                ICodec_t& decoder,
                                IntrusivePtr_t<BaseDataType_t>& result)
{
  return decoder.Decode(buffer, result);
}

int BaseDataType_t::RefCount(void) const
{
  UASDK_ASSERT(false);
  return 0;
}

BaseDataType_t::BaseDataType_t() 
{}

BaseDataType_t::~BaseDataType_t() 
{}

bool BaseDataType_t::operator!=(BaseDataType_t const & obj) const
{
  return !(*this == obj);
}

Status_t BaseDataType_t::WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const
{
  UASDK_UNUSED(indexRange);
  return CopyTo(destination);
}

Status_t BaseDataType_t::WriteSubsetFrom(const Array_t<IndexRange_t>& indexRange, const BaseDataType_t& source)
{
  UASDK_UNUSED(indexRange);
  return CopyFrom(source);
}

bool BaseDataType_t::IsArray(void) const
{
  return false;
}

bool BaseDataType_t::IsNumber(void) const
{
  return false;
}

void BaseDataType_t::AddReference() const
{
  UASDK_ASSERT(false);
}

void BaseDataType_t::RemoveReference() const
{
  UASDK_ASSERT(false);
}

} // namespace uasdk
