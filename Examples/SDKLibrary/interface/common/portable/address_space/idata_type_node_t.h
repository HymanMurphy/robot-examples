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

#ifndef _IDATA_TYPE_NODE_T_
#define _IDATA_TYPE_NODE_T_

#include "uasdk_includes.h"
#include "inode_t.h"

namespace uasdk
{

template<typename T> class ArrayUA_t;
class IVariableNode_t;

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief DataType Node Interface
 *
 * A class that represents a DataType node in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IDataTypeNode_t : public virtual INode_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(IDataTypeNode_t);

  virtual ~IDataTypeNode_t() {}

  /*****************************************************************************/
  /** Get the IsAbstract attribute of the node
   *
   * @return
   * The IsAbstract of the node.
   */
  virtual bool IsAbstract(void) const = 0;

  /*****************************************************************************/
  /** Set the IsAbstract attribute of the node
   *
   * @param[in] value
   * The required IsAbstract of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t IsAbstract(bool value) = 0;
};

/** @} */

}

#endif // _IDATA_TYPE_NODE_T_
