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

#ifndef _OPCUA_QUERY_DATA_SET_T_
#define _OPCUA_QUERY_DATA_SET_T_

#include "opcua_array_ua_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_structure_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

class QueryDataSet_t: public Structure_t
{
private:

    ExpandedNodeId_t nodeId;
    ExpandedNodeId_t typeDefinitionNode;
    ArrayUA_t<BaseDataType_t> values;

public:
  UA_DECLARE_RUNTIME_TYPE(QueryDataSet_t);

  static const uint32_t TYPE_ID = OpcUaId_QueryDataSet;

  virtual ~QueryDataSet_t();

  virtual bool operator==(BaseDataType_t const & obj) const;

  bool operator==(QueryDataSet_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  bool operator>(QueryDataSet_t const & obj) const;

  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  virtual Status_t CopyFrom(const QueryDataSet_t& source);
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  const ExpandedNodeId_t& NodeId() const;
  ExpandedNodeId_t& NodeId();

  const ExpandedNodeId_t& TypeDefinitionNode() const;
  ExpandedNodeId_t& TypeDefinitionNode();

  const ArrayUA_t<BaseDataType_t>& Values() const;
  ArrayUA_t<BaseDataType_t>& Values();

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryDataSet_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_QUERY_DATA_SET_T_
