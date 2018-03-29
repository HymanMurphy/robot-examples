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

#ifndef _FOLDER_T_
#define _FOLDER_T_

#include "helper_base_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "opcua_node_id_t.h"
#include "iaddress_space_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief Folder_t
*
* Folder_t class.
*
*/
class Folder_t : public HelperBase_t
{
private:
  static IntrusivePtr_t<Folder_t> CreateFolderObject(IntrusivePtr_t<IObjectNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result);

  static IntrusivePtr_t<Folder_t> CreateFolderObject(IntrusivePtr_t<const NodeId_t>& nodeId,
                                                           const String_t& browseName,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           Status_t& result);

protected:
  Folder_t();

public:
  virtual ~Folder_t();


  /*****************************************************************************/
  /** This function gets the Folder Object node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<IObjectNode_t> GetObjectNode(void);
  /*****************************************************************************/
  /** This const function used to get the Folder Object node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<const IObjectNode_t> GetObjectNode(void) const;

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  FolderObject node.
  *
  * @param[in] nodeId
  * Object node id which needs to find in the address space.
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
  static IntrusivePtr_t<Folder_t> Get(const NodeId_t& nodeId,
                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                      Status_t& result);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  FolderObject node.
  *
  * @param[in] nodeId
  * const Object node id which needs to find in the address space.
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
  static IntrusivePtr_t<Folder_t> Get(IntrusivePtr_t<IObjectNode_t>& node,
                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                      Status_t& result);

  /*****************************************************************************/
  /** This Function used to create FolderObject with Numeric Id.
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
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Folder_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                      uint32_t nodeIdentifier,
                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                      const String_t& browseName,
                                                      Status_t& result);

  /*****************************************************************************/
  /** This Function is used to create FolderObject node with sting Id.
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
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Folder_t> CreateWithStringId(uint16_t namespaceIndex,
                                                     const String_t& nodeIdentifier,
                                                     IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                     const String_t& browseName,
                                                     Status_t& result);

  /*****************************************************************************/
  /** This Function used to create FolderObject with GUID
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
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Folder_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                   const Guid_t& nodeIdentifier,
                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                   const String_t& browseName,
                                                   Status_t& result);

  /*****************************************************************************/
  /** This Function is used to FolderObject with Opaque item
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
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Folder_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                     const ByteString_t& nodeIdentifier,
                                                     IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                     const String_t& browseName,
                                                     Status_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_USE_HELPERS

#endif  //_FOLDER_T_