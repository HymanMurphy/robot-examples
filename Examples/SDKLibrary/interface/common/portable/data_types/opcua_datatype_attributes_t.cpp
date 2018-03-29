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

#include "opcua_datatype_attributes_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

	UA_DEFINE_RUNTIME_TYPE(DataTypeAttributes_t, Structure_t)

		bool DataTypeAttributes_t::operator==(DataTypeAttributes_t const & obj) const
	{
		return (
			(specifiedAttributes == obj.specifiedAttributes)
			&& (displayName == obj.displayName)
			&& (description == obj.description)
			&& (isAbstract == obj.isAbstract)
			&& (writeMask == obj.writeMask)
			&& (userWriteMask == obj.userWriteMask));
	}

	bool DataTypeAttributes_t::operator>(DataTypeAttributes_t const & obj) const
	{
		return (
			(specifiedAttributes > obj.specifiedAttributes)
			&& (displayName > obj.displayName)
			&& (description > obj.description)
			&& (isAbstract > obj.isAbstract)
			&& (writeMask > obj.writeMask)
			&& (userWriteMask > obj.userWriteMask));
	}

	Status_t DataTypeAttributes_t::CopyFrom(const DataTypeAttributes_t& source)
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

	Status_t DataTypeAttributes_t::CopyFrom(const BaseDataType_t& source)
	{
		const DataTypeAttributes_t* ptr = RuntimeCast<const DataTypeAttributes_t *>(source);
		if (!ptr)
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
		}

		return CopyFrom(*ptr);
	}

	Status_t DataTypeAttributes_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
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

	Status_t DataTypeAttributes_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DataTypeAttributes_t& result)
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

	DataTypeAttributes_t::~DataTypeAttributes_t() {}

	bool DataTypeAttributes_t::operator==(BaseDataType_t const & obj) const
	{
		return OperatorEqualTo(*this, obj);
	}

	bool DataTypeAttributes_t::operator>(BaseDataType_t const & obj) const
	{
		return OperatorGreaterThan(*this, obj);
	}

	Status_t DataTypeAttributes_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}

	uint32_t DataTypeAttributes_t::TypeId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return TYPE_ID;
	}

	uint32_t DataTypeAttributes_t::BinaryEncodingId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return OpcUaId_DataTypeAttributes_Encoding_DefaultBinary;
	}

	UInt32_t & DataTypeAttributes_t::SpecifiedAttributes()
	{
		return specifiedAttributes;
	}

	const UInt32_t & DataTypeAttributes_t::SpecifiedAttributes() const
	{
		return specifiedAttributes;
	}

	LocalizedText_t & DataTypeAttributes_t::DisplayName()
	{
		return displayName;
	}

	const LocalizedText_t & DataTypeAttributes_t::DisplayName() const
	{
		return displayName;
	}

	LocalizedText_t & DataTypeAttributes_t::Description()
	{
		return description;
	}

	const LocalizedText_t & DataTypeAttributes_t::Description() const
	{
		return description;
	}

	Boolean_t & DataTypeAttributes_t::IsAbstract()
	{
		return isAbstract;
	}

	const Boolean_t & DataTypeAttributes_t::IsAbstract() const
	{
		return isAbstract;
	}

	UInt32_t & DataTypeAttributes_t::WriteMask()
	{
		return writeMask;
	}

	const UInt32_t & DataTypeAttributes_t::WriteMask() const
	{
		return writeMask;
	}

	UInt32_t & DataTypeAttributes_t::UserWriteMask()
	{
		return userWriteMask;
	}

	const UInt32_t & DataTypeAttributes_t::UserWriteMask() const
	{
		return userWriteMask;
	}

} // namespace uasdk

#endif
