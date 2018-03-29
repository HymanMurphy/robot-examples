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

#ifndef _IXML_NODESET_IO_T_
#define _IXML_NODESET_IO_T_

#include "uasdk_includes.h"

#include "iref_count_t.h"
#include "status_t.h"

namespace uasdk
{

class IAddressSpace_t;
class IFile_t;

/** \addtogroup grpMiscellaneous
 *@{*/
 
class IXmlNodesetIO_t : public IRefCount_t
{
public:
  virtual ~IXmlNodesetIO_t() {}

  /*****************************************************************************/
  /** Create address space using the input nodeset file.
   *
   * This method does not validate the nodeset file for compliance with a schema.
   *
   * @param[in] nodeset
   * The file containing the node information to import
   *
   * @param[in] addressSpace
   * The address space object where nodes has to be created
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Import(const IFile_t& nodeset, IAddressSpace_t& addressSpace) = 0;

  /*****************************************************************************/
  /** Validate nodeset file against schema and Create address space using the input nodeset file.
   *
   * This method validates the nodeset file for compliance with a schema.
   *
   * @param[in] nodeset
   * The file containing the node information to import
   *
   * @param[in] schema
   * The file containing the schema for nodeset file
   *
   * @param[in] addressSpace
   * The address space object where nodes has to be created

   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Import(const IFile_t& nodeset, const IFile_t& schema, IAddressSpace_t& addressSpace) = 0;

  /*****************************************************************************/
  /** Export nodes from an address space into a nodeset file
   *
   * This method exports all nodes in the address space to a nodeset file.
   *
   * @param[in] addressSpace
   * The address space from where nodes has to be browsed and update in the nodeset file
   *
   * @param[in] nodeset
   * The file where node informatiokn has to be updated
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Export(const IAddressSpace_t& addressSpace, IFile_t& nodeset) = 0;

  /*****************************************************************************/
  /** Update address space from the nodeset file provided as input
   *
   * This method updates the newly added/modified/deleted node or reference in nodeset file to
   * address space. If there is no error during update, output nodeset file will be empty.
   * Otherwise, output nodeset fill contain the result of each update operation.
   *
   * @param[in] nodeset
   * The file which contains the newly added/modified/deleted node information 
   *
   * @param[in] addressSpace
   * The address space where nodes has to be updated according to nodeset file
   *
   * @param[out] updateResultNodeset
   * The result of the update operation will be stored in the file specified by this argument
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Update(const IFile_t& nodeset, IAddressSpace_t& addressSpace, IFile_t& updateResultNodeset) = 0;

  /*****************************************************************************/
  /** Validate nodeset file against schema and Update address space from 
   *  the nodeset file provided as input
   *
   * This method updates the newly added/modified/deleted node or reference in nodeset file to
   * address space. If there is no error during update, output nodeset file will be empty.
   * Otherwise, output nodeset fill contain the result of each update operation.
   *
   * @param[in] nodeset
   * The file which contains the newly added/modified/deleted node information 
   *
   * @param[in] schema
   * The file containing the schema for nodeset file
   *
   * @param[in] addressSpace
   * The address space where nodes has to be updated according to nodeset file
   *
   * @param[out] updateResultNodeset
   * The result of the update operation will be stored in the file specified by this argument
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Update(const IFile_t& nodeset, const IFile_t& schema, IAddressSpace_t& addressSpace, IFile_t& updateResultNodeset) = 0;
};

/** @} */

}
#endif // _IXML_NODESET_IO_T_
