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

#include "iattribute_access_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  UA_DEFINE_RUNTIME_TYPE(IAttributeAccess_t, BaseDataType_t);

  //Default implementation of the non-locale version that requests a default locale
  IntrusivePtr_t<const BaseDataType_t> IAttributeAccess_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& attributeId, const String_t& indexRange, Status_t& result) const
  {
    ArrayUA_t<String_t> locales;
    locales.Initialise(1);
    locales[0] = new SafeRefCount_t<String_t>();
    if (locales[0].is_set())
    {
      locales[0]->CopyFrom(""); //Request default locale.
    }
    return AttributeValue(typeId, browsePath, attributeId, indexRange, locales, result);
  }

  IntrusivePtr_t<BaseDataType_t> IAttributeAccess_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& attributeId, const String_t& indexRange, Status_t& result)
  {
    ArrayUA_t<String_t> locales;
    locales.Initialise(1);
    locales[0] = new SafeRefCount_t<String_t>();
    if (locales[0].is_set())
    {
      locales[0]->CopyFrom(""); //Request default locale.
    }
    return AttributeValue(typeId, browsePath, attributeId, indexRange, locales, result);
  }

  IntrusivePtr_t<const UInt32_t> IAttributeAccess_t::SubscriptionId(void) const 
  { 
    return subscriptionId;
  }

  IntrusivePtr_t<UInt32_t>& IAttributeAccess_t::SubscriptionId(void) 
  { 
    return subscriptionId; 
  }

  IntrusivePtr_t<const UInt32_t> IAttributeAccess_t::MonitoredItemId(void) const 
  {
    return monitoredItemId; 
  }

  IntrusivePtr_t<UInt32_t>& IAttributeAccess_t::MonitoredItemId(void) 
  { 
    return monitoredItemId; 
  }

  //unused pure virtual functions
  bool IAttributeAccess_t::operator==(BaseDataType_t const & obj) const
  {
    UASDK_UNUSED(obj);
    return false;
  }

  bool IAttributeAccess_t::operator>(BaseDataType_t const & obj) const
  {
    UASDK_UNUSED(obj);
    return false;
  }

  Status_t IAttributeAccess_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
  {
    UASDK_UNUSED(encoder);
    UASDK_UNUSED(buffer);
    return OpcUa_Good;
  }
}

#endif //UASDK_INCLUDE_EVENTS
