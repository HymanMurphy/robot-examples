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

#ifndef _OPCUA_DELETE_NODES_ITEM_T_
#define _OPCUA_DELETE_NODES_ITEM_T_

#include "opcua_structure_t.h"
#include "opcua_node_id_t.h"
#include "opcua_boolean_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

class DeleteNodesItem_t : public Structure_t
{
private:
	
	IntrusivePtr_t<NodeId_t> nodeId;
	Boolean_t deleteTargetReferences;
	

public:
  UA_DECLARE_RUNTIME_TYPE(DeleteNodesItem_t);
  
  static const uint32_t TYPE_ID = OpcUaId_DeleteNodesItem;

  virtual ~DeleteNodesItem_t();

  virtual bool operator==(BaseDataType_t const & obj) const;

  bool operator==(DeleteNodesItem_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  bool operator>(DeleteNodesItem_t const & obj) const;

  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  virtual Status_t CopyFrom(const DeleteNodesItem_t& source);
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  IntrusivePtr_t<const NodeId_t> NodeId(void) const;
  IntrusivePtr_t<NodeId_t>& NodeId(void);

  const Boolean_t& DeleteTargetReferences(void) const;
  Boolean_t& DeleteTargetReferences(void);

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteNodesItem_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_DELETE_NODES_ITEM_T_
