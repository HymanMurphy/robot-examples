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

#include "localizable_text_stored_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{

Status_t LocalizableTextStored_t::GetPreferredText(const ArrayUA_t<String_t>& sessionLocales, IntrusivePtr_t<const LocalizedText_t>& result) const
{
  uint32_t storedTextCount = storedText.Count();
  uint32_t localesCount = sessionLocales.Count();

  for(uint32_t i = 0; i < localesCount; i++)
  {
    IntrusivePtr_t<String_t> locale = sessionLocales[i];
    if(!locale.is_set())
    {
      result = 0;
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }

    for(uint32_t j = 0; j < storedTextCount; j++)
    {
      result = storedText.GetAtIndex(j);
      if(!result.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      if(*locale == result->Locale())
      {
        return OpcUa_Good;
      }
    }
  }

  result = storedText.GetFirst();
  return OpcUa_Good;
}

/*
 * Public functions
 */
Status_t LocalizableTextStored_t::AddText(IntrusivePtr_t<const LocalizedText_t> text)
{
  if (!text.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  IntrusivePtr_t<String_t> locale = new SafeRefCount_t<String_t>();
  if (!locale.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  Status_t status = locale->CopyFrom(text->Locale());
  if (status.IsBad())
  {
    return status;
  }

  IntrusivePtr_t<const LocalizedText_t> defaultText = GetLocalizedText(status);
  if (status.IsBad())
  {
    if ((status.Value() == OpcUa_BadNoData) && !defaultText.is_set())
    {
      return storedText.AddToTail(text);
    }

    return status;
  }
  if (defaultText.is_set() && (*locale == defaultText->Locale()))
  {
    storedText.DeleteCurrent();
    return storedText.AddToHead(text);
  }

  ArrayUA_t<String_t> locales;
  status = locales.Initialise(1);
  if (status.IsBad())
  {
    return status;
  }
  locales[0] = locale;

  IntrusivePtr_t<const LocalizedText_t> temp = GetLocalizedText(locales, status);
  if (status.IsBad())
  {
    return status;
  }
  if (temp.is_set() && (*locale == temp->Locale()))
  {
    storedText.DeleteCurrent();
  }

  return storedText.AddToTail(text);
}

IntrusivePtr_t<const LocalizedText_t> LocalizableTextStored_t::GetLocalizedText(const ArrayUA_t<String_t>& sessionLocales,
                                                                               Status_t& result) const
{
  IntrusivePtr_t<const LocalizedText_t> localizedText;

  if(storedText.Count() <= 0)
  {
    result = OpcUa_BadNoData;
    return localizedText;
  }
  else if( (storedText.Count() == 1) || (sessionLocales.Count() <= 0) )
  {
    localizedText = storedText.GetFirst();
    if (!localizedText.is_set())
    {
      result = OpcUa_BadNoData;
      return localizedText;
    }
    result = OpcUa_Good;
  }
  else
  {
    result = GetPreferredText(sessionLocales, localizedText);
  }

  return localizedText;
}

IntrusivePtr_t<const LocalizedText_t> LocalizableTextStored_t::GetLocalizedText(Status_t& result) const
{
  ArrayUA_t<String_t> locales;
  return GetLocalizedText(locales, result);
}

Status_t LocalizableTextStored_t::CopyTo(IntrusivePtr_t<ILocalizableText_t>& destination) const
{
  Status_t status;
  IntrusivePtr_t<LocalizableTextStored_t> localizableTextStored_ = new SafeRefCount_t<LocalizableTextStored_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(localizableTextStored_);

  for (uint32_t i = 0; i < storedText.Count(); i++)
  {
    status = localizableTextStored_->AddText(storedText.GetAtIndex(i));
    if (status.IsBad())
    {
      localizableTextStored_->storedText.DeleteAll();
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }
  destination = localizableTextStored_;
  return OpcUa_Good;
}

} // namespace uasdk
