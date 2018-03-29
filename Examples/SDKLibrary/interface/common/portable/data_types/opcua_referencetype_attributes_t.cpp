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

#include "opcua_referencetype_attributes_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ReferenceTypeAttributes_t, Structure_t)

bool ReferenceTypeAttributes_t::operator==(ReferenceTypeAttributes_t const & obj) const
{
	return (
		(specifiedAttributes == obj.specifiedAttributes)
		&& (displayName == obj.displayName)
		&& (description == obj.description)
		&& (isAbstract == obj.isAbstract)
		&& (symmetric == obj.symmetric)
		&& (inverseName == obj.inverseName)
		&& (writeMask == obj.writeMask)
		&& (userWriteMask == obj.userWriteMask));
}

bool ReferenceTypeAttributes_t::operator>(ReferenceTypeAttributes_t const & obj) const
{
	return (
		(specifiedAttributes > obj.specifiedAttributes)
		&& (displayName > obj.displayName)
		&& (description > obj.description)
		&& (isAbstract > obj.isAbstract)
		&& (symmetric > obj.symmetric)
		&& (inverseName > obj.inverseName)
		&& (writeMask > obj.writeMask)
		&& (userWriteMask > obj.userWriteMask));
}

Status_t ReferenceTypeAttributes_t::CopyFrom(const ReferenceTypeAttributes_t& source)
{
	Status_t status = specifiedAttributes.CopyFrom(source.specifiedAttributes);

	if (status.IsBad())
	{
		return status;
	}

	status = displayName.CopyFrom(source.displayName);
	if (status.IsBad())
	{
		return status;
	}

	status = description.CopyFrom(source.description);
	if (status.IsBad())
	{
		return status;
	}

	status = isAbstract.CopyFrom(source.isAbstract);
	if (status.IsBad())
	{
		return status;
	}

	status = symmetric.CopyFrom(source.symmetric);
	if (status.IsBad())
	{
		return status;
	}

	status = inverseName.CopyFrom(source.inverseName);
	if (status.IsBad())
	{
		return status;
	}

	status = writeMask.CopyFrom(source.writeMask);
	if (status.IsBad())
	{
		return status;
	}

	status = userWriteMask.CopyFrom(source.userWriteMask);
	if (status.IsBad())
	{
		return status;
	}

	return status;
}

Status_t ReferenceTypeAttributes_t::CopyFrom(const BaseDataType_t& source)
{
  const ReferenceTypeAttributes_t* ptr = RuntimeCast<const ReferenceTypeAttributes_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ReferenceTypeAttributes_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
	Status_t status = specifiedAttributes.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = displayName.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = description.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = isAbstract.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = symmetric.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = inverseName.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = writeMask.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = userWriteMask.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	return status;
}

Status_t ReferenceTypeAttributes_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ReferenceTypeAttributes_t& result)
{
	Status_t status = UInt32_t::Decode(buffer, decoder, result.SpecifiedAttributes());
	if (status.IsBad())
	{
		return status;
	}

	status = LocalizedText_t::Decode(buffer, decoder, result.DisplayName());
	if (status.IsBad())
	{
		return status;
	}

	status = LocalizedText_t::Decode(buffer, decoder, result.Description());
	if (status.IsBad())
	{
		return status;
	}

	status = Boolean_t::Decode(buffer, decoder, result.IsAbstract());
	if (status.IsBad())
	{
		return status;
	}

	status = Boolean_t::Decode(buffer, decoder, result.Symmetric());
	if (status.IsBad())
	{
		return status;
	}

	status = LocalizedText_t::Decode(buffer, decoder, result.InverseName());
	if (status.IsBad())
	{
		return status;
	}

	status = UInt32_t::Decode(buffer, decoder, result.WriteMask());
	if (status.IsBad())
	{
		return status;
	}

	status = UInt32_t::Decode(buffer, decoder, result.UserWriteMask());
	if (status.IsBad())
	{
		return status;
	}

	return status;
}

ReferenceTypeAttributes_t::~ReferenceTypeAttributes_t() {}

bool ReferenceTypeAttributes_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ReferenceTypeAttributes_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ReferenceTypeAttributes_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ReferenceTypeAttributes_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ReferenceTypeAttributes_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ReferenceTypeAttributes_Encoding_DefaultBinary;
}

UInt32_t & ReferenceTypeAttributes_t::SpecifiedAttributes()
{
	return specifiedAttributes;
}

const UInt32_t & ReferenceTypeAttributes_t::SpecifiedAttributes() const
{
	return specifiedAttributes;
}

LocalizedText_t & ReferenceTypeAttributes_t::DisplayName()
{
	return displayName;
}

const LocalizedText_t & ReferenceTypeAttributes_t::DisplayName() const
{
	return displayName;
}

LocalizedText_t & ReferenceTypeAttributes_t::Description()
{
	return description;
}

const LocalizedText_t & ReferenceTypeAttributes_t::Description() const
{
	return description;
}

Boolean_t & ReferenceTypeAttributes_t::IsAbstract()
{
	return isAbstract;
}

const Boolean_t & ReferenceTypeAttributes_t::IsAbstract() const
{
	return isAbstract;
}

Boolean_t & ReferenceTypeAttributes_t::Symmetric()
{
	return symmetric;
}

const Boolean_t & ReferenceTypeAttributes_t::Symmetric() const
{
	return symmetric;
}

LocalizedText_t & ReferenceTypeAttributes_t::InverseName()
{
	return inverseName;
}

const LocalizedText_t & ReferenceTypeAttributes_t::InverseName() const
{
	return inverseName;
}

UInt32_t & ReferenceTypeAttributes_t::WriteMask()
{
	return writeMask;
}

const UInt32_t & ReferenceTypeAttributes_t::WriteMask() const
{
	return writeMask;
}

UInt32_t & ReferenceTypeAttributes_t::UserWriteMask()
{
	return userWriteMask;
}

const UInt32_t & ReferenceTypeAttributes_t::UserWriteMask() const
{
	return userWriteMask;
}

} // namespace uasdk

#endif
