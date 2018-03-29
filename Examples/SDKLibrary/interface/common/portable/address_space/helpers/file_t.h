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

#ifndef _FILE_T_
#define _FILE_T_

#include "helper_base_t.h"

#if ((UASDK_USE_HELPERS > 0) &&(UASDK_USE_FILE_OBJECT_HELPERS > 0))

#include "opcua_boolean_t.h"
#include "opcua_node_id_t.h"
#include "iaddress_space_t.h"
#include "allocatable_t.h"
#include "ifile_ua_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief File_t
*
* File_t class.
*
*/
class File_t : public HelperBase_t
{
public:
  typedef struct
  {
    Boolean_t                  writable;
    Boolean_t                  userWritable;
    IntrusivePtr_t<IFileUA_t>  fileHandler;
  } MandatoryPropertyValues_t;

  typedef struct
  {
    uint32_t  sizeId;
    uint32_t  writableId;
    uint32_t  userWritableId;
    uint32_t  openCountId;
  } MandatoryPropertyNumericIds_t;

private:

  static Status_t AddMethodNodeReference(uint32_t methodId, IntrusivePtr_t<INodeMethodHandler_t>& methodHandler, File_t& fileObject);

  static IntrusivePtr_t<File_t> CreateFileObject(IntrusivePtr_t<IObjectNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result);
  
  static Status_t SetReaderWriter(IntrusivePtr_t<IVariableNode_t>& propertyNode, uint32_t propertyType, const IntrusivePtr_t<IFileUA_t>& fileHandler);

  IntrusivePtr_t<IVariableNode_t> SizeNode(void);
  IntrusivePtr_t<const IVariableNode_t> SizeNode(void) const;

  IntrusivePtr_t<IVariableNode_t> WritableNode(void);
  IntrusivePtr_t<const IVariableNode_t> WritableNode(void) const;

  IntrusivePtr_t<IVariableNode_t> UserWritableNode(void);
  IntrusivePtr_t<const IVariableNode_t> UserWritableNode(void) const;

  IntrusivePtr_t<IVariableNode_t> OpenCountNode(void);
  IntrusivePtr_t<const IVariableNode_t> OpenCountNode(void) const;

  static Status_t CreateSizeProperty(File_t& fileObject,
                                     const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                     const MandatoryPropertyValues_t& value);

  static Status_t CreateWritableProperty(File_t& fileObject,
                                         const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                         const MandatoryPropertyValues_t& value);

  static Status_t CreateUserWritableProperty(File_t& fileObject,
                                             const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                             const MandatoryPropertyValues_t& value);

  static Status_t CreateOpenCountProperty(File_t& fileObject,
                                          const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                          const MandatoryPropertyValues_t& value);

  static IntrusivePtr_t<File_t> CreateFileObjectWithMandatoryProperty(IntrusivePtr_t<const NodeId_t>& nodeId_,
                                                                            const String_t& browseName,
                                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                            const MandatoryPropertyNumericIds_t& ids,
                                                                            const MandatoryPropertyValues_t& value,
                                                                            IntrusivePtr_t<INodeMethodHandler_t>& methodHandler,
                                                                            Status_t& result);

protected:
  File_t();

  /*****************************************************************************/
  /** This function deletes properties.
  *
  * @param[in] FileObject
  * data item which is to be delete.
  *
  */
  void DeleteProperties(File_t& fileObject);

public:
  virtual ~File_t();

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  FileObject node.
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
  static IntrusivePtr_t<File_t> Get(const NodeId_t& nodeId,
                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                    Status_t& result);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  FileObject node.
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
  static IntrusivePtr_t<File_t> Get(IntrusivePtr_t<IObjectNode_t>& node,
                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                    Status_t& result);

  /*****************************************************************************/
  /** This Function used to create FileObject with Numeric Id.
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
  * FileObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<File_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                    uint32_t nodeIdentifier,
                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                    const String_t& browseName,
                                                    MandatoryPropertyNumericIds_t& propertyIds,
                                                    MandatoryPropertyValues_t& propertyValues,
                                                    IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                    Status_t& result);

  /*****************************************************************************/
  /** This Function is used to create FileObject node with sting Id.
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
  * FileObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<File_t> CreateWithStringId(uint16_t namespaceIndex,
                                                   const String_t& nodeIdentifier,
                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                   const String_t& browseName,
                                                   MandatoryPropertyValues_t& propertyValues,
                                                   IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                   Status_t& result);

  /*****************************************************************************/
  /** This Function used to create FileObject with GUID
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
  * FileObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<File_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                 const Guid_t& nodeIdentifier,
                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                 const String_t& browseName,
                                                 MandatoryPropertyValues_t& propertyValues,
                                                 IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                 Status_t& result);

  /*****************************************************************************/
  /** This Function is used to FileObject with Opaque item
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
  * FileObject. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<File_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                   const ByteString_t& nodeIdentifier,
                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                   const String_t& browseName,
                                                   MandatoryPropertyValues_t& propertyValues,
                                                   IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                   Status_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_USE_FILE_TRANSFER_HELPERS

#endif  //_FILE_T_