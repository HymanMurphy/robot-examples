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

#ifndef _OPCUA_ADD_NODES_ITEM_T_
#define _OPCUA_ADD_NODES_ITEM_T_

#include "opcua_structure_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_node_class_t.h"
#include "opcua_extensible_parameter_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

class AddNodesItem_t : public Structure_t
{
private:
    ExpandedNodeId_t parentNodeId;
    IntrusivePtr_t<NodeId_t> referenceTypeId;
    ExpandedNodeId_t requestedNewNodeId;
    QualifiedName_t browseName;
    NodeClass_t nodeClass;
    ExtensibleParameter_t nodeAttributes;
    ExpandedNodeId_t typeDefinition;

public:
  UA_DECLARE_RUNTIME_TYPE(AddNodesItem_t);
  
  static const uint32_t TYPE_ID = OpcUaId_AddNodesItem;

  virtual ~AddNodesItem_t();

  virtual bool operator==(BaseDataType_t const & obj) const;

  bool operator==(AddNodesItem_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  bool operator>(AddNodesItem_t const & obj) const;

  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  virtual Status_t CopyFrom(const AddNodesItem_t& source);
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  const ExpandedNodeId_t& ParentNodeId(void) const;
  ExpandedNodeId_t& ParentNodeId(void);

  IntrusivePtr_t<const NodeId_t> ReferenceTypeId(void) const;
  IntrusivePtr_t<NodeId_t>& ReferenceTypeId(void);

  const ExpandedNodeId_t& RequestedNewNodeId(void) const;
  ExpandedNodeId_t& RequestedNewNodeId(void);

  const QualifiedName_t& BrowseName(void) const;
  QualifiedName_t& BrowseName(void);

  const NodeClass_t& NodeClass(void) const;
  NodeClass_t& NodeClass(void);

  // Here the extensible parameter should be NodeAttributes_t
  const ExtensibleParameter_t& NodeAttributes(void) const;
  ExtensibleParameter_t& NodeAttributes(void);

  const ExpandedNodeId_t& TypeDefinition(void) const;
  ExpandedNodeId_t& TypeDefinition(void);

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, AddNodesItem_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_ADD_NODES_ITEM_T_
