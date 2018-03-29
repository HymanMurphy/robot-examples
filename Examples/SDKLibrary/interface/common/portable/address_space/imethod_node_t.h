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

#ifndef _IMETHOD_NODE_T_
#define _IMETHOD_NODE_T_

#include "uasdk_includes.h"
#include "inode_t.h"
#include "inode_method_handler_t.h"

namespace uasdk
{

class IVariableNode_t;
class ICallbackCallMethodCompleted_t;
class IObjectNode_t;

template<typename T> class ArrayUA_t;

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief Method Node Interface
 *
 * A class that represents a method node in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IMethodNode_t : public virtual INode_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(IMethodNode_t);

  virtual ~IMethodNode_t() {}

  /*****************************************************************************/
  /** Get the Executable attribute of the node
   *
   * @return
   * The Executable of the node.
   */
  virtual bool Executable(void) const = 0;

  /*****************************************************************************/
  /** Set the Executable attribute of the node
   *
   * @param[in] value
   * The required Executable of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Executable(bool value) = 0;

  /*****************************************************************************/
  /** Get the UserExecutable attribute of the node
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * The UserExecutable of the node.
   */
  virtual bool UserExecutable(const IUserPermissions_t& userPermissions) const = 0;

  /*****************************************************************************/
  /** Set the UserExecutable attribute of the node
   *
   * @param[in] value
   * The required UserExecutable of the node
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t UserExecutable(bool value, IUserPermissions_t& userPermissions) = 0;

  /*****************************************************************************/
  /** Set the method handler of the node
   *
   *  The method handler is used by the node to execute the method. Only a single
   *  method handler can be registered at any given time. Any software component
   *  registering a method handler with the node is responsible for removing the
   *  method handler if required.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the method handler
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, the INodeMethodHandler_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the method handler from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t SetMethodHandler(IntrusivePtr_t<INodeMethodHandler_t> value) = 0;

  /*****************************************************************************/
  /** Begins calling the method of the node
   *
   *  This function internally calls the method handler registered with the node.
   *  If this function returns a good status code
   *  completedCallback.CallMethodCompleted() will be called by the method handler
   *  when the method has completed. If this function returns a bad status code
   *  completedCallback.CallMethodCompleted() will not be called by the method
   *  handler.
   *
   * @param[in] sessionId
   * The ID of the session making the call. Will be null if the call is not being made
   * in the context of a session.
   *
   * @param[in] transationId
   * A non-zero unique identifier for a collection of methods being called as a
   * group (typically by the Call Service). Can be optionally used in conjunction
   * with a transaction listener to optimise processing of method calls by the
   * application. If calling the method outside of the Call Service should be set
   * to zero.
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @param[in] timeoutHint
   * The timeoutHint in milliseconds provided by the Call Service. The method
   * handler can optionally consider this hint when replying to the caller.
   * Should be set to zero where no timeoutHint is provided.
   *
   * @param[in] componentOf
   * The object that defines the context for the method call. Must be referenced by
   * a ComponentOf reference from the Method.
   *
   * @param[in] requestedParameters
   * The parameters of the method call.
   *
   * @param[in] result
   * Object to store the results of the method call.
   *
   * @param[out] completedCallback
   * The CallMethodCompleted() function of this interface will be called by the method
   * handler if this function returns a good status code.
   *
   * @return
   * The result of the operation. If the status code is good then the method handler
   * has been successfully launched and will return the method result in due course. If
   * the status code is bad the method handler was not successfully launched.
   *
   */
  virtual Status_t BeginMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
                                   uint32_t transactionId,
                                   const IUserPermissions_t& userPermissions,
                                   uint32_t timeoutHint,
                                   INode_t& componentOf,
                                   IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
                                   IntrusivePtr_t<CallMethodResult_t>& result,
                                   IntrusivePtr_t<ICallbackCallMethodCompleted_t> completedCallback) = 0;

};

/** @} */

}

#endif // _IMETHOD_NODE_T_
