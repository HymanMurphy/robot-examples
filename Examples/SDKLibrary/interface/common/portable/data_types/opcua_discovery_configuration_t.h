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

#ifndef _OPCUA_DISCOVERY_CONFIGURATION_T_
#define _OPCUA_DISCOVERY_CONFIGURATION_T_


#include "opcua_string_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_application_type_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_structure_t.h"
#include "opcua_boolean_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

class MdnsDiscoveryConfiguration_t : public Structure_t
{
private:
  String_t                mdnsServerName;
  ArrayUA_t<String_t>     serverCapabilities;

public:
  UA_DECLARE_RUNTIME_TYPE(MdnsDiscoveryConfiguration_t);
  
  static const uint32_t TYPE_ID = OpcUaId_MdnsDiscoveryConfiguration;

  virtual ~MdnsDiscoveryConfiguration_t();

  virtual bool operator==(BaseDataType_t const & obj) const;

  bool operator==(MdnsDiscoveryConfiguration_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  bool operator>(MdnsDiscoveryConfiguration_t const & obj) const;

  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  virtual Status_t CopyFrom(const MdnsDiscoveryConfiguration_t& source);
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  const String_t& MdnsServerName(void) const;
  String_t& MdnsServerName(void);

  const ArrayUA_t<String_t>& ServerCapabilities(void) const;
  ArrayUA_t<String_t>& ServerCapabilities(void);

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, MdnsDiscoveryConfiguration_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_DISCOVERY_CONFIGURATION_T_
