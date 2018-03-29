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

#ifndef _BASE_OBJECT_T_
#define _BASE_OBJECT_T_

#include "helper_base_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "opcua_node_id_t.h"
#include "iaddress_space_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief BaseObject_t
*
* BaseObject_t class.
*
*/
class BaseObject_t : public HelperBase_t
{
private:
  /*****************************************************************************/
  /** This Function used to create Object with GUID
  *
  * @param[in] node_
  * Object Node
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * BaseObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> CreateObject(IntrusivePtr_t<IObjectNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result);

  /*****************************************************************************/
  /** This Function used to create Object with GUID
  *
  * @param[in] node_
  * Object Node
  *
  * @param[in] browseName
  * browse name.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] hasTypeDefinitionId
  * has Type Defintion
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * BaseObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> CreateObject(IntrusivePtr_t<const NodeId_t>& nodeId,
                                                   const String_t& browseName,
                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                   uint32_t hasTypeDefinitionId,
                                                   Status_t& result);

protected:
  BaseObject_t();

public:
  virtual ~BaseObject_t();


  /*****************************************************************************/
  /** This function gets the Object node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<IObjectNode_t> GetObjectNode(void);

  /*****************************************************************************/
  /** This const function used to get the Object node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<const IObjectNode_t> GetObjectNode(void) const;

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  BaseOject_t.
  *
  * @param[in] nodeId
  * Method node id which needs to find in the address space.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] result
  * node value
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> Get(const NodeId_t& nodeId,
    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
    Status_t& result);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  BaseOject_t.
  *
  * @param[in] node
  * object node which needs to find in the address space.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] result
  * node value
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> Get(IntrusivePtr_t<IObjectNode_t>& node,
    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
    Status_t& result);

  /*****************************************************************************/
  /** This Function used to create Object with Numeric Id.
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] nodeIdentifier
  * node Identifier.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[out] hasTypeDefinitionId
  * Has Type Definition.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                          uint32_t nodeIdentifier,
                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                          const String_t& browseName,
                                                          uint32_t hasTypeDefinitionId,
                                                          Status_t& result);

  /*****************************************************************************/
  /** This Function is used to create Object node with sting Id.
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] nodeIdentifier
  * node Identifier.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[out] hasTypeDefinitionId
  * Has Type Definition.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> CreateWithStringId(uint16_t namespaceIndex,
                                                         const String_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         uint32_t hasTypeDefinitionId,
                                                         Status_t& result);

  /*****************************************************************************/
  /** This Function used to create Object with GUID
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] nodeIdentifier
  * node Identifier.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[out] hasTypeDefinitionId
  * Has Type Definition.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                       const Guid_t& nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       uint32_t hasTypeDefinitionId,
                                                       Status_t& result);

  /*****************************************************************************/
  /** This Function is used to Object with Opaque item
  *
  * @param[in] namespaceIndex
  * namespace Index.
  *
  * @param[in] nodeIdentifier
  * node Identifier.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[in] browseName
  * Browse Name.
  *
  * @param[out] hasTypeDefinitionId
  * Has Type Definition.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<BaseObject_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                         const ByteString_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         uint32_t hasTypeDefinitionId,
                                                         Status_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_USE_HELPERS

#endif  //_BASE_OBJECT_T_