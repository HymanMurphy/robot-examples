/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef _FILE_TRANSFER_ROUTER_T_H_
#define _FILE_TRANSFER_ROUTER_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0)

#include "inode_method_handler_t.h"
#include "isession_listener_t.h"
#include "file_ua_t.h"

namespace uasdk
{

class FileTransferRouter_t : public Allocatable_t, public INodeMethodHandler_t
{
private:
  IntrusiveList_t<FileUA_t> allFiles;

  //*****************************************************************************/
  /** Get File from the give object id
  *
  * @param[in] fileObjectId
  * node id of the file object
  *
  * @return
  * Intrusive pointer to the file object.
  */
  IntrusivePtr_t<FileUA_t> getFile(IntrusivePtr_t<const NodeId_t>& fileObjectId);

  //*****************************************************************************/
  /** to handle the Open method
  *
  * @param[in] session id
  * session
  *
  * @param[in] file
  * file object
  *
  * @param[in] requestParameters
  * request parameters for method
  *
  * @param[in] result
  * the result fo the method callback
  *
  * @return
  * status of the operation
  */
  Status_t OpenMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<FileUA_t> file,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result);

  //*****************************************************************************/
  /** to handle the close method
  *
  * @param[in] session id
  * session
  *
  * @param[in] file
  * file object
  *
  * @param[in] requestParameters
  * request parameters for method
  *
  * @param[in] result
  * the result fo the method callback
  *
  * @return
  * status of the operation
  */
  Status_t CloseMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<FileUA_t> file,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result);

  //*****************************************************************************/
  /** to handle the read method
  *
  * @param[in] session id
  * session
  *
  * @param[in] file
  * file object
  *
  * @param[in] requestParameters
  * request parameters for method
  *
  * @param[in] result
  * the result fo the method callback
  *
  * @return
  * status of the operation
  */
  Status_t ReadMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<FileUA_t> file,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result);

  //*****************************************************************************/
  /** to handle the write method
  *
  * @param[in] session id
  * session
  *
  * @param[in] file
  * file object
  *
  * @param[in] requestParameters
  * request parameters for method
  *
  * @param[in] result
  * the result fo the method callback
  *
  * @return
  * status of the operation
  */
  Status_t WriteMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<FileUA_t> file,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result);

  //*****************************************************************************/
  /** to handle the Get position method
  *
  * @param[in] session id
  * session
  *
  * @param[in] file
  * file object
  *
  * @param[in] requestParameters
  * request parameters for method
  *
  * @param[in] result
  * the result fo the method callback
  *
  * @return
  * status of the operation
  */
  Status_t GetPositionMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<FileUA_t> file,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result);

  //*****************************************************************************/
  /** to handle the Set position method
  *
  * @param[in] session id
  * session
  *
  * @param[in] file
  * file object
  *
  * @param[in] requestParameters
  * request parameters for method
  *
  * @param[in] result
  * the result fo the method callback
  *
  * @return
  * status of the operation
  */
  Status_t SetPositionMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<FileUA_t> file,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result);


public:
  FileTransferRouter_t() {}

  //*****************************************************************************/
  /** initialize
  *
  * @return
  * status of the operation
  */
  Status_t Initialise();

  //*****************************************************************************/
  /** Remove the file
  *
  * @param[in] file
  * file object to be added to the list
  *
  * @return
  * status of the operation
  */
  Status_t AddFile(FileUA_t& file);

  //*****************************************************************************/
  /** Remove the file
  *
  * @param[in] file
  * file object to be removed from the list
  *
  * @return
  * status of the operation
  */
  Status_t RemoveFile(FileUA_t& file);

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
  virtual Status_t CallMethodBegin(
    IntrusivePtr_t<const NodeId_t> sessionId,
    uint32_t transactionId,
    const IUserPermissions_t& userPermissions,
    uint32_t timeoutHint,
    IntrusivePtr_t<IObjectNode_t>& componentOf,
    IntrusivePtr_t<IMethodNode_t>& method,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result,
    IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback);

};

}

#endif //(UASDK_INCLUDE_SERVER_C_API > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0)
#endif //(UASDK_INCLUDE_SERVER)
#endif //_FILE_TRANSFER_ROUTER_T_H_
