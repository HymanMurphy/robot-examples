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

#ifndef _IUSER_AUTHENTICATOR_T_
#define _IUSER_AUTHENTICATOR_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "status_t.h"

namespace uasdk
{

class INode_t;
class IMethodNode_t;
class IObjectNode_t;
class IVariableNode_t;
class WriteMask_t;
class AccessLevel_t;

/** \addtogroup grpAddressSpace
 *@{*/

class IUserPermissions_t : public IRefCount_t
{
public:
  virtual ~IUserPermissions_t() {};

  virtual bool operator==(IUserPermissions_t const & obj) const = 0;

  virtual bool operator!=(IUserPermissions_t const & obj) const = 0;

  /*****************************************************************************/
  /** Variable Node user Access Level Getter
   *
   *  @param[in] node
   *  node of which assess level has to be found
   *
   *  @param[out] userAccessLevel
   *  access level information of the node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t GetVariableNodeUserAccessLevel(const IVariableNode_t& node,
                                                  AccessLevel_t& userAccessLevel) const = 0;

  /*****************************************************************************/
  /** Variable Node user Access Level Getter
   *
   *  @param[in] node
   *  node of which assess level has to be found
   *
   *  @param[out] userAccessLevel
   *  access level information of the node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SetVariableNodeUserAccessLevel(IVariableNode_t& node,
                                                  AccessLevel_t userAccessLevel) = 0;

  /*****************************************************************************/
  /** Node user Write Mask Getter
   *
   *  @param[in] node
   *  node of which write mask to get
   *
   *  @param[out] userWriteMask
   *  User Write Mask information of the node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t GetNodeUserWriteMask(const INode_t& node,
                                        WriteMask_t& userWriteMask) const = 0;

  /*****************************************************************************/
  /** Node user Write Mask Getter
   *
   *  @param[in] node
   *  node of which write mask to get
   *
   *  @param[out] userWriteMask
   *  User Write Mask information of the node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SetNodeUserWriteMask(const INode_t& node,
                                        WriteMask_t userWriteMask) = 0;

  /*****************************************************************************/
  /** Node visibility Getter
   *
   *  @param[in] node
   *  node of which visibility has to get
   *
   *  @param[out] visible
   *  Visibility of the node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t GetNodeUserVisibility(const INode_t& node,
                                         bool& visible) const = 0;

  /*****************************************************************************/
  /** Node visibility Getter
   *
   *  @param[in] node
   *  node of which visibility has to get
   *
   *  @param[out] visible
   *  Visibility of the node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SetNodeUserVisibility(INode_t& node,
                                         bool visible) = 0;

  /*****************************************************************************/
  /** User Executable Getter for method node
   *
   *  @param[in] method
   *  method of which user executable has to get
   *
   *  @param[out] userExecutable
   *  user executable information of the method
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t GetMethodNodeUserExecutable(const IMethodNode_t& method,
                                               bool& userExecutable) const = 0;

  /*****************************************************************************/
  /** User Executable Getter for method node
   *
   *  @param[in] method
   *  method of which user executable has to get
   *
   *  @param[out] userExecutable
   *  user executable information of the method
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SetMethodNodeUserExecutable(IMethodNode_t& method,
                                               bool userExecutable) = 0;

};


/** @} */

}

#endif // _IUSER_AUTHENTICATOR_T_
