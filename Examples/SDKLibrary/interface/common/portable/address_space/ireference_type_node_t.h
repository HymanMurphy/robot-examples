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

#ifndef _IREFERENCE_TYPE_T_
#define _IREFERENCE_TYPE_T_

#include "uasdk_includes.h"
#include "ilocalizable_text_t.h"
#include "inode_t.h"

namespace uasdk
{

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief ReferenceType Node Interface
 *
 * A class that represents a ReferenceType node in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IReferenceTypeNode_t : public virtual INode_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(IReferenceTypeNode_t);

  virtual ~IReferenceTypeNode_t() {}

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

  /*****************************************************************************/
  /** Get the Symmetric attribute of the node
   *
   * @return
   * The Symmetric of the node.
   */
  virtual bool Symmetric(void) const = 0;

  /*****************************************************************************/
  /** Set the Symmetric attribute of the node
   *
   * @param[in] value
   * The required Symmetric of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Symmetric(bool value) = 0;

  /*****************************************************************************/
  /** Get the InverseName attribute of the node
   *
   * @param[in] locales
   * The locales of interest in priority order. The
   * ILocalizableText_t InverseName member variable of the node uses these
   * locales to determine the appropriate LocalizedText_t to return.
   *
   * @param[out] result
   * The result of the operation. This can be ignored unless the returned
   * pointer is not set.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the InverseName
   * of the node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> InverseName(const ArrayUA_t<String_t>& locales, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Set the InverseName attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the InverseName
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the ILocalizableText_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the ILocalizableText_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the InverseName attribute from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t InverseName(IntrusivePtr_t<const ILocalizableText_t> value) = 0;

};

/** @} */

}

#endif // _IREFERENCE_TYPE_T_
