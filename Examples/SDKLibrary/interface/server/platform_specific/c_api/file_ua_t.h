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

#ifndef _FILE_UA_T_H_
#define _FILE_UA_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0) && (UA_INCLUDE_FILE_TRANSFER_METHODS > 0)

#include "ifile_ua_t.h"
#include "iserver_configuration_t.h"

namespace uasdk
{

class FileTransferRouter_t;

struct FileOpenContext_t
{
  UA_Status_t result;
  uint32_t file_handle;

  FileOpenContext_t() : result(OpcUa_BadInternalError), file_handle(0) {}
};

struct FileGenericContext_t
{
  UA_Status_t result;

  FileGenericContext_t() : result(OpcUa_BadInternalError) {}
};

struct FileReadContext_t
{
  UA_Status_t result;
  ByteString_t data;

  FileReadContext_t() : result(OpcUa_BadInternalError) {}
};

struct FileGetPositionContext_t
{
  UA_Status_t result;
  uint64_t position;

  FileGetPositionContext_t() : result(OpcUa_BadInternalError), position(0) {}
};

struct FileSizeContext_t
{
  UA_Status_t result;
  uint64_t size;

  FileSizeContext_t() : result(OpcUa_BadInternalError), size(0) {}
};

class FileUA_t : public IFileUA_t, public Allocatable_t
{
private:
  IntrusivePtr_t<const NodeId_t> fileObjectId;
  uint32_t nodeHandle;
  bool isOpenForWriting;

  struct Handle_t : public Allocatable_t, public IRefCount_t
  {
    IntrusivePtr_t<const NodeId_t> sessionId;
    uint32_t fileHandle;
  };

  IntrusiveList_t<Handle_t> handles;

  /*****************************************************************************/
  /** Is session present
  *
  * @param[in] sessionId
  * session Id
  *
  * @param[in] fileHandle
  * file hanlde
  *
  * true if the session is present
  */
  bool IsSessionIdAndFileHandleValid(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle);

  /*****************************************************************************/
  /** remove handle
  *
  * @param[in] sessionId
  * session Id
  *
  * @param[in] fileHandle
  * file hanlde
  *
  * @return
  * status of the operation
  */
  Status_t RemoveHandle(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle);

  /*****************************************************************************/
  /** NodeHandle
  *
  * @return
  * node hanlde of the file
  */
  uintptr_t NodeHandle(void);

public:
  FileUA_t() : nodeHandle(0), isOpenForWriting(false)
  {}
  /*****************************************************************************/
  /** Session created callback
  *
  * This function will be called by the SDK when the session is created
  */
  void virtual SessionCreated(IntrusivePtr_t<const NodeId_t>& sessionId);

  /*****************************************************************************/
  /** Session Activated callback
  *
  * This function will be called by the SDK when the session is Activated
  */
  void virtual SessionActivated(IntrusivePtr_t<const NodeId_t>& sessionId);

  /*****************************************************************************/
  /** Session closed callback
  *
  * This function will be called by the SDK when the session is closed
  */
  void virtual SessionClosed(IntrusivePtr_t<const NodeId_t>& sessionId);

  /*****************************************************************************/
  /** Initialize the object
  *
  * @param[in] fileObjectId_
  * File object Id
  *
  * @param[in] sharedData_
  * shared data
  *
  * @param[in] fileTransferRouter_
  * Fiel stransfer router
  *
  * @return
  * status of the operatin
  */
  Status_t Initialise(IntrusivePtr_t<const NodeId_t> fileObjectId_, IntrusivePtr_t<IServerConfiguration_t> sharedData_, IntrusivePtr_t<FileTransferRouter_t>& fileTransferRouter_);

  /*****************************************************************************/
  /** File object Id
  *
  * Instrussive pointer to the file object Id
  */
  virtual IntrusivePtr_t<const NodeId_t> FileObjectId(void);

  /*****************************************************************************/
  /** OpenCount of the file
  *
  * This function will return the number of file opened
  *
  * @return
  * number of file opened
  */
  virtual uint16_t OpenCount(void);

  /*****************************************************************************/
  /** Size of the file
  *
  * This function will return the size of the file object.
  * In case of errors 0 will be returned.
  *
  * @return
  * The size of file will be returned.
  */
  virtual uint64_t Size(void);

  /*****************************************************************************/
  /** Open file object
  *
  * This function will open the file for reading/writing/append new data
  *
  * @param[in] sessionId
  * session id
  *
  * @param[in] mode
  * mode of opening file
  *
  * @param[out] fileHandle
  * file handle
  *
  * @return
  * status of operation
  */
  virtual Status_t Open(IntrusivePtr_t<const NodeId_t> sessionId, Byte_t mode, uint32_t& fileHandle);

  /*****************************************************************************/
  /** close file object
  *
  * This function will close the file
  *
  * @param[in] sessionId
  * session id
  *
  * @param[in] fileHandle
  * file handle
  *
  * @return
  * status of operation
  */
  virtual Status_t Close(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle);

  /*****************************************************************************/
  /** Read file object
  *
  * This function will read data from file
  *
  * @param[in] sessionId
  * session id
  *
  * @param[in] fileHandle
  * file handle
  *
  * @param[in] lengthToRead
  * number of bytes to be read
  *
  * @param[out] output
  * the read data in byte string format
  *
  * @return
  * status of operation
  */
  virtual Status_t Read(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, uint32_t lengthToRead, IntrusivePtr_t<ByteString_t>& output);

  /*****************************************************************************/
  /** Write to file object
  *
  * This function will write data to file object
  *
  * @param[in] sessionId
  * session id
  *
  * @param[in] fileHandle
  * file handle
  *
  * @param[in] dataToWrite
  * the data to be written
  *
  * @return
  * status of operation
  */
  virtual Status_t Write(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, IntrusivePtr_t<ByteString_t> dataToWrite);

  /*****************************************************************************/
  /** Get current index int he opened file object
  *
  * @param[in] sessionId
  * session id
  *
  * @param[in] fileHandle
  * file handle
  *
  * @param[out] position
  * position in the file
  *
  * @return
  * status of operation
  */
  virtual Status_t GetPosition(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, IntrusivePtr_t<UInt64_t >& position);

  /*****************************************************************************/
  /** Set new position for the file object
  *
  * @param[in] sessionId
  * session id
  *
  * @param[in] fileHandle
  * file handle
  *
  * @param[in] position
  * new position
  *
  * @return
  * status of operation
  */
  virtual Status_t SetPosition(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, IntrusivePtr_t<UInt64_t> position);
};

}

#endif  //#ifdef 
#endif  //(UASDK_INCLUDE_SERVER)
#endif  //_FILE_UA_T_H_
