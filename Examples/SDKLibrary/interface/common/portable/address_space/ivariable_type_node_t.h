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

#ifndef _IVARIABLE_TYPE_NODE_T_
#define _IVARIABLE_TYPE_NODE_T_

#include "uasdk_includes.h"
#include "inode_t.h"

namespace uasdk
{

class UInt32_t;
class IVariableNode_t;
template<typename T> class ArrayUA_t;

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief VariableType Node Interface
 *
 * A class that represents a VariableType node in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IVariableTypeNode_t : public virtual INode_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(IVariableTypeNode_t);

  virtual ~IVariableTypeNode_t() {}

  /*****************************************************************************/
  /** Get the Value attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the Value
   * of the node. All variable type nodes do not have a value and the caller must
   * test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const DataValue_t> Value(void) const = 0;

  /*****************************************************************************/
  /** Set the Value attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the Value
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the DataValue_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the DataValue_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the Value attribute from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Value(IntrusivePtr_t<const DataValue_t> value_) = 0;

  /*****************************************************************************/
  /** Get the DataType attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the DataType
   * of the node. All nodes have a DataType however the caller must test the
   * pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const NodeId_t> DataType(void) const = 0;

  /*****************************************************************************/
  /** Set the DataType attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the DataType
   * of the node. The value provided must satisfy a number of rules.
   * 1) No non-const references to the NodeId_t must exist, i.e. it must
   *    be immutable (to ensure thread safety).
   * 2) The NodeId_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value must be set (i.e. pointing to an actual object) as all
   *    variable type nodes require a DataType.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t DataType(IntrusivePtr_t<const NodeId_t> value) = 0;

  /*****************************************************************************/
  /** Get the ValueRank attribute of the node
   *
   * @return
   * The ValueRank of the node.
   */
  virtual int32_t ValueRank(void) const = 0;

  /*****************************************************************************/
  /** Set the ValueRank attribute of the node
   *
   * @param[in] value
   * The required ValueRank of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ValueRank(int32_t value) = 0;

  /*****************************************************************************/
  /** Get the ArrayDimensions attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ArrayDimensions of the node. All variable type nodes do not have
   * ArrayDimensions and the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ArrayUA_t<UInt32_t> > ArrayDimensions(void) const = 0;

  /*****************************************************************************/
  /** Set the ArrayDimensions attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the ArrayDimensions
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the ArrayUA_t<UInt32_t> must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the ArrayUA_t<UInt32_t> must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the ArrayDimensions attribute from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ArrayDimensions(IntrusivePtr_t<const ArrayUA_t<UInt32_t> > value) = 0;

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

#endif // _IVARIABLE_TYPE_NODE_T_
