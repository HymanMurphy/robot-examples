/* ----------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
---------------------------------------------------------------------------------------- */

#include "localizable_text_translate_for_c_api_t.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "opcua_array_ua_t.h"
#include "uasdk_c_declarations.h"
#include "ua_server.h"
#include "opcua_localized_text_t.h"

namespace uasdk
{

uint16_t LocalizableTextTranslateForCAPI_t::GetLocaleIndex(const ArrayUA_t<String_t>& sessionLocales, IntrusivePtr_t<String_t>& locale, Status_t& result) const
{
  if (sessionLocales.Count() == 0)
  {
    result = OpcUa_Good;
    return 0;
  }
  else
  {
    if (!localeIdArray.is_set())
    {
      result = OpcUa_BadUnexpectedError;
      return 0;
    }

    uint32_t localeIdArrayCount = localeIdArray->Count();
    uint32_t localesCount = sessionLocales.Count();

    for (uint32_t i = 0; i < localesCount; i++)
    {
      IntrusivePtr_t<String_t> locale_ = sessionLocales[i];
      if (!locale_.is_set())
      {
        result = OpcUa_BadUnexpectedError;
        return 0;
      }

      for (uint32_t j = 0; j < localeIdArrayCount; j++)
      {
        IntrusivePtr_t<String_t> localeId = (*localeIdArray)[j];
        if (!localeId.is_set())
        {
          result = OpcUa_BadUnexpectedError;
          return 0;
        }

        if (*locale_ == *localeId)
        {
          result = OpcUa_Good;
          locale = localeId;
          return j;
        }
      }
    }
    //If locale is not set by now, set to default
    if (!locale.is_set())
    {
      locale = (*localeIdArray)[0];
      result = OpcUa_Good;
      return 0;
    }
  }

  result = OpcUa_BadUnexpectedError;
  return 0;
}

void LocalizableTextTranslateForCAPI_t::AddTextHandle(uintptr_t textHandle_)
{
  textHandle = textHandle_;
}

void LocalizableTextTranslateForCAPI_t::AddLocaleIdArray(IntrusivePtr_t<const ArrayUA_t<String_t> >& localesIdArray_)
{
  localeIdArray = localesIdArray_;
}

IntrusivePtr_t<const LocalizedText_t> LocalizableTextTranslateForCAPI_t::GetLocalizedText(const ArrayUA_t<String_t>& sessionLocales,
  Status_t& result) const
{
  IntrusivePtr_t<LocalizedText_t> retVal;
  IntrusivePtr_t<String_t> locale;
  uint16_t localeHandle = GetLocaleIndex(sessionLocales, locale, result);
  if (result.IsBad() || !locale.is_set())
  {
    return retVal;
  }

  const UA_UTF8_string_t* translatedText = UAServer_Callback_translate(localeHandle, textHandle);
  if (!translatedText || !translatedText->data ||(translatedText->length <= 0))
  {
    result = OpcUa_BadNoData;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<LocalizedText_t>());
  if (!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }

  result = retVal->Locale().CopyFrom(*locale);
  if (result.IsBad())
  {
    IntrusivePtr_t<const LocalizedText_t> empty;
    return empty;
  }

  result = retVal->Text().CopyFrom((const char*)(translatedText->data), (translatedText->length + 1) );
  if (result.IsBad())
  {
    IntrusivePtr_t<const LocalizedText_t> empty;
    return empty;
  }

  result = OpcUa_Good;
  return retVal;
}

IntrusivePtr_t<const LocalizedText_t> LocalizableTextTranslateForCAPI_t::GetLocalizedText(Status_t& result) const
{
  ArrayUA_t<String_t> empty;
  return GetLocalizedText(empty, result);
}

Status_t LocalizableTextTranslateForCAPI_t::CopyTo(IntrusivePtr_t<ILocalizableText_t>& destination) const
{
  return OpcUa_BadNotSupported;
}

} // uasdk

#endif //(UASDK_INCLUDE_SERVER_C_API > 0)
#endif //(UASDK_INCLUDE_SERVER)
