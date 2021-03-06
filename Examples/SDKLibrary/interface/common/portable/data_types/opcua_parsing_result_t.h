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

#ifndef _OPCUA_PARSING_RESULT_T_
#define _OPCUA_PARSING_RESULT_T_

#include "opcua_array_ua_t.h"
#include "opcua_status_code_t.h"
#include "opcua_structure_t.h"
#include "opcua_diagnostic_info_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

class ParsingResult_t: public Structure_t
{
private:
	StatusCode_t statusCode;
	ArrayUA_t<StatusCode_t> dataStatusCodes;
	ArrayUA_t<DiagnosticInfo_t> dataDiagnosticInfos;

public:
  UA_DECLARE_RUNTIME_TYPE(ParsingResult_t);

  static const uint32_t TYPE_ID = OpcUaId_ParsingResult;

  virtual ~ParsingResult_t();

  virtual bool operator==(BaseDataType_t const & obj) const;

  bool operator==(ParsingResult_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  bool operator>(ParsingResult_t const & obj) const;

  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  virtual Status_t CopyFrom(const ParsingResult_t& source);
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  const StatusCode_t& StatusCode() const;
  StatusCode_t& StatusCode();

  const ArrayUA_t<StatusCode_t>& DataStatusCodes() const;
  ArrayUA_t<StatusCode_t>& DataStatusCodes();

  const ArrayUA_t<DiagnosticInfo_t>& DataDiagnosticInfos() const;
  ArrayUA_t<DiagnosticInfo_t>& DataDiagnosticInfos();

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ParsingResult_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_PARSING_RESULT_T_
