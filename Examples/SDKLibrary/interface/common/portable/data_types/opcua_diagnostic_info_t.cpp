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

#include "opcua_diagnostic_info_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DiagnosticInfo_t, BaseDataType_t)

DiagnosticInfo_t::DiagnosticInfo_t()
{
}

bool DiagnosticInfo_t::operator==(DiagnosticInfo_t const & obj) const
{
  BaseDataType_t* idi = innerDiagnosticInfo.get();
  BaseDataType_t* other_idi = obj.innerDiagnosticInfo.get();
  if (!idi || !other_idi)
  {
    return false;
  }

  if (!(*idi == *other_idi))
  {
    return false;
  }

  //TODO
  return (
      Equal(symbolicId, obj.symbolicId)
      && Equal(namespaceUri, obj.namespaceUri)
      && Equal(localizedText, obj.localizedText)
      && Equal(locale, obj.locale)
      && Equal(additionalInfo, obj.additionalInfo)
      && Equal(innerStatusCode, obj.innerStatusCode));
}

bool DiagnosticInfo_t::operator>(DiagnosticInfo_t const & obj) const
{
  //TODO
  BaseDataType_t* idi = innerDiagnosticInfo.get();
  BaseDataType_t* other_idi = obj.innerDiagnosticInfo.get();
  if (!idi || !other_idi)
  {
    return false;
  }

  if (!(*idi > *other_idi))
  {
    return false;
  }

  return (
      GreaterThan(symbolicId, obj.symbolicId)
      && GreaterThan(namespaceUri, obj.namespaceUri)
      && GreaterThan(localizedText, obj.localizedText)
      && GreaterThan(locale, obj.locale)
      && GreaterThan(additionalInfo, obj.additionalInfo)
      && GreaterThan(innerStatusCode, obj.innerStatusCode));
}

Status_t DiagnosticInfo_t::CopyFrom(const DiagnosticInfo_t& source)
{
	Status_t status = OpcUa_Good;
	if (source.symbolicId.is_set())
	{
		symbolicId.reset(new SafeRefCount_t<Int32_t>());
		if (!symbolicId.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		status = symbolicId->CopyFrom(*source.symbolicId);
	}
	else
	{
		symbolicId.reset();
	}
  if (status.IsBad())
  {
    return status;
  }

	if (source.namespaceUri.is_set())
	{
		namespaceUri.reset(new SafeRefCount_t<Int32_t>());
		if (!namespaceUri.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		status = namespaceUri->CopyFrom(*source.namespaceUri);
	}
	else
	{
		namespaceUri.reset();
	}  
  if (status.IsBad())
  {
    return status;
  }

	if (source.localizedText.is_set())
	{
		localizedText.reset(new SafeRefCount_t<Int32_t>());
		if (!localizedText.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		localizedText->CopyFrom(*source.localizedText);
	}
	else
	{
		localizedText.reset();
	}
  if (status.IsBad())
  {
    return status;
  }

	if (source.locale.is_set())
	{
		locale.reset(new SafeRefCount_t<Int32_t>());
		if (!locale.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		locale->CopyFrom(*source.locale);
	}
	else
	{
		locale.reset();
	}
	if (status.IsBad())
	{
		return status;
	}
  
	if (source.additionalInfo.is_set())
	{
		additionalInfo.reset(new SafeRefCount_t<String_t>());
		if (!additionalInfo.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		additionalInfo->CopyFrom(*source.additionalInfo);
	}
	else
	{
		additionalInfo.reset();
	}
	if (status.IsBad())
	{
		return status;
	}
  
	if (source.innerStatusCode.is_set())
	{
		innerStatusCode.reset(new SafeRefCount_t<StatusCode_t>());
		if (!innerStatusCode.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		innerStatusCode->CopyFrom(*source.innerStatusCode);
	}
	else
	{
		innerStatusCode.reset();
	}
	if (status.IsBad())
	{
		return status;
	}
  
  if (source.innerDiagnosticInfo.is_set())
  {
    innerDiagnosticInfo = new SafeRefCount_t<DiagnosticInfo_t>();
    if (!innerDiagnosticInfo.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = innerDiagnosticInfo->CopyFrom(*source.innerDiagnosticInfo);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    innerDiagnosticInfo.reset();
  }

  return status;

}

Status_t DiagnosticInfo_t::CopyFrom(const BaseDataType_t& source)
{
  const DiagnosticInfo_t* ptr = RuntimeCast<const DiagnosticInfo_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DiagnosticInfo_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t DiagnosticInfo_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DiagnosticInfo_t& result)
{
  return decoder.Decode(buffer, result);
}

DiagnosticInfo_t::~DiagnosticInfo_t() 
{}

bool DiagnosticInfo_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DiagnosticInfo_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t DiagnosticInfo_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t DiagnosticInfo_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

IntrusivePtr_t<const Int32_t> DiagnosticInfo_t::SymbolicId(void) const
{
  return symbolicId;
}

IntrusivePtr_t<Int32_t>& DiagnosticInfo_t::SymbolicId(void)
{
  return symbolicId;
}

IntrusivePtr_t<const Int32_t> DiagnosticInfo_t::NamespaceUri(void) const
{
  return namespaceUri;
}

IntrusivePtr_t<Int32_t>& DiagnosticInfo_t::NamespaceUri(void)
{
  return namespaceUri;
}

IntrusivePtr_t<const Int32_t> DiagnosticInfo_t::LocalizedText(void) const
{
  return localizedText;
}

IntrusivePtr_t<Int32_t>& DiagnosticInfo_t::LocalizedText(void)
{
  return localizedText;
}

IntrusivePtr_t<const Int32_t> DiagnosticInfo_t::Locale(void) const
{
  return locale;
}

IntrusivePtr_t<Int32_t>& DiagnosticInfo_t::Locale(void)
{
  return locale;
}

IntrusivePtr_t<const String_t> DiagnosticInfo_t::AdditionalInfo(void) const
{
  return additionalInfo;
}

IntrusivePtr_t<String_t>& DiagnosticInfo_t::AdditionalInfo(void)
{
  return additionalInfo;
}

IntrusivePtr_t<const StatusCode_t> DiagnosticInfo_t::InnerStatusCode(void) const 
{ return innerStatusCode; }

IntrusivePtr_t<StatusCode_t>& DiagnosticInfo_t::InnerStatusCode(void)
{
  return innerStatusCode;
}

IntrusivePtr_t<const DiagnosticInfo_t> DiagnosticInfo_t::InnerDiagnosticInfo(void) const
{
  return innerDiagnosticInfo;
}

IntrusivePtr_t<DiagnosticInfo_t>& DiagnosticInfo_t::InnerDiagnosticInfo(void) 
{
  return innerDiagnosticInfo; 
}



} // namespace uasdk
