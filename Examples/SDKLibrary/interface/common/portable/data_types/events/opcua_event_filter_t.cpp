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

#include "opcua_event_filter_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(EventFilter_t, Structure_t)

EventFilter_t::EventFilter_t()
{
}

EventFilter_t::~EventFilter_t()
{
}

bool EventFilter_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EventFilter_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EventFilter_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EventFilter_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t EventFilter_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_EventFilter_Encoding_DefaultBinary;
}

const ArrayUA_t<SimpleAttributeOperand_t>& EventFilter_t::SelectClauses(void) const
{
	return selectClauses;
}

ArrayUA_t<SimpleAttributeOperand_t>& EventFilter_t::SelectClauses(void)
{
	return selectClauses;
}

const ContentFilter_t& EventFilter_t::WhereClause(void) const
{
  return whereClause;
}

ContentFilter_t& EventFilter_t::WhereClause(void)
{
  return whereClause;
}

EventFilter_t& EventFilter_t::operator=(EventFilter_t const & other)
{
  if (this != &other)
  {
    selectClauses.CopyFrom(other.selectClauses);
    whereClause.CopyFrom(other.whereClause);
  }
  return *this;
}

bool EventFilter_t::operator==(EventFilter_t const & obj) const
{
  return (
     (selectClauses == obj.selectClauses)
      && (whereClause == obj.whereClause));
}

bool EventFilter_t::operator>(EventFilter_t const & obj) const
{
  return (
      (selectClauses > obj.selectClauses)
      && (whereClause > obj.whereClause));
}

Status_t EventFilter_t::CopyFrom(const EventFilter_t& source)
{
  Status_t status = OpcUa_Good;

  status = selectClauses.CopyFrom(source.selectClauses);
  if (status.IsBad())
  {
    return status;
  }

  status = whereClause.CopyFrom(source.whereClause);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t EventFilter_t::CopyFrom(const BaseDataType_t& source)
{
  const EventFilter_t* ptr = RuntimeCast<const EventFilter_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t EventFilter_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = selectClauses.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = whereClause.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t EventFilter_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, EventFilter_t& result)
{
  Status_t status = ArrayUA_t<SimpleAttributeOperand_t>::Decode(buffer, decoder, result.SelectClauses());
  if (status.IsBad())
  {
    return status;
  }

  status = ContentFilter_t::Decode(buffer, decoder, result.WhereClause());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

bool EventFilter_t::DoesEventPassFilter(const INode_t& targetNode, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration)
{
	IntrusivePtr_t<BaseDataType_t> evaluatedResult;
	IntrusivePtr_t<ContentFilterResult_t> resultStructure;

	Status_t status = whereClause.ApplyFilter(targetNode, eventAttributes, configuration, resultStructure, evaluatedResult);
	if (status.IsBad())
	{
    if (status == OpcUa_BadNothingToDo)
    {
      return true;
    }
		return false;
	}

	return true;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


