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

#include "opcua_qualified_name_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(QualifiedName_t, BaseDataType_t)

bool QualifiedName_t::operator==(QualifiedName_t const & obj) const
{
  return (
      (namespaceIndex == obj.namespaceIndex)
      && (name == obj.name));
}

bool QualifiedName_t::operator>(QualifiedName_t const & obj) const
{
  return (
      (namespaceIndex > obj.namespaceIndex)
      && (name > obj.name));
}

Status_t QualifiedName_t::CopyFrom(const BaseDataType_t& source)
{
  const QualifiedName_t* ptr = RuntimeCast<const QualifiedName_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t QualifiedName_t::CopyFrom(const QualifiedName_t& source)
{
  Status_t status = namespaceIndex.CopyFrom(source.namespaceIndex);
  if (status.IsBad())
  {
    return status;
  }

  status = name.CopyFrom(source.name);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t QualifiedName_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t QualifiedName_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QualifiedName_t& result)
{
  return decoder.Decode(buffer, result);
}

QualifiedName_t::QualifiedName_t()
{}

QualifiedName_t::~QualifiedName_t()
{}

bool QualifiedName_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool QualifiedName_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t QualifiedName_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t QualifiedName_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const UInt16_t&  QualifiedName_t::NamespaceIndex(void) const
{
  return namespaceIndex;
}

UInt16_t&  QualifiedName_t::NamespaceIndex(void)
{
  return namespaceIndex;
}

const String_t& QualifiedName_t::Name(void) const
{
  return name;
}

String_t& QualifiedName_t::Name(void)
{
  return name;
}

} // namespace uasdk
