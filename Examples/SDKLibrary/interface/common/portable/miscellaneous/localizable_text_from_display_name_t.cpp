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

#include "localizable_text_from_display_name_t.h"
#include "localizable_text_stored_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{

/*
 * Public functions
 */

Status_t LocalizableTextFromDisplayName_t::Initialise(IntrusivePtr_t<INode_t>& node)
{
  if (!node.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }
  source = node;
  return OpcUa_Good;
}

IntrusivePtr_t<const LocalizedText_t> LocalizableTextFromDisplayName_t::GetLocalizedText(const ArrayUA_t<String_t>& locales, Status_t& result) const
{
  if (!source.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    IntrusivePtr_t<const LocalizedText_t> empty;
    return empty;
  }

  return source->DisplayName(locales, result);
}

IntrusivePtr_t<const LocalizedText_t> LocalizableTextFromDisplayName_t::GetLocalizedText(Status_t& result) const
{
  const ArrayUA_t<String_t> locales;
  return GetLocalizedText(locales, result);
}

Status_t LocalizableTextFromDisplayName_t::CopyTo(IntrusivePtr_t<ILocalizableText_t>& destination) const
{
  Status_t status;
  IntrusivePtr_t<LocalizableTextStored_t> localizableTextStored_ = new SafeRefCount_t<LocalizableTextStored_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(localizableTextStored_);

  status = localizableTextStored_->AddText(GetLocalizedText(status));
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  destination = localizableTextStored_;
  return OpcUa_Good;
}


} // namespace uasdk
