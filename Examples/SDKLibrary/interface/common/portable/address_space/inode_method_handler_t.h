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

#ifndef _INODE_METHOD_CALLER_T_
#define _INODE_METHOD_CALLER_T_

#include "uasdk_includes.h"
#include "opcua_argument_t.h"

namespace uasdk
{

class DiagnosticInfo_t;
class IUserPermissions_t;
class StatusCode_t;
class CallMethodResult_t;
class CallMethodRequest_t;

/** \addtogroup grpAddressSpace
 *@{*/

class ICallbackCallMethodCompleted_t : public IRefCount_t
{
public:
  virtual ~ICallbackCallMethodCompleted_t() {};

  /*****************************************************************************/
  /** Method Call completed callback
   *
   * @param[in] result
   * result of the method call.
   *
   * @return
   * The result of the operation.
   *
   */
  virtual Status_t CallMethodCompleted(IntrusivePtr_t<CallMethodResult_t>& result) = 0;

  /*****************************************************************************/
  /** Method Call completed callback
  *
  * @param[in] result
  * result of the method call.
  *
  * @param[in] diagnosticInfo
  * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  * required.
  *
  * @return
  * The result of the operation.
  *
  */
  virtual Status_t CallMethodCompleted(
    IntrusivePtr_t<CallMethodResult_t>& result,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo) = 0;
  
};

class INode_t;
class IMethodNode_t;

class INodeMethodHandler_t : public virtual IRefCount_t
{
public:
  virtual ~INodeMethodHandler_t() {};

  /*****************************************************************************/
  /** Begins calling the method of the node
   *
   *  If the method call is successful
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
   * @param[in] requestParameters
   * The parameters of the method call.
   *
   * @param[in] method
   * The method to be called
   *
   * @param[in] result
   * Object to store the result of the method call.
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
  virtual Status_t CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
                                   uint32_t transactionId,
                                   const IUserPermissions_t& userPermissions,
                                   uint32_t timeoutHint,
                                   IntrusivePtr_t<INode_t>& componentOf,
                                   IntrusivePtr_t<IMethodNode_t>& method,
                                   IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
                                   IntrusivePtr_t<CallMethodResult_t>& result,
                                   IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback) = 0;
};

/** @} */

}

#endif // _INODE_METHOD_CALLER_T_
