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

#ifndef _IFILE_UA_T_
#define _IFILE_UA_T_

#include "uasdk_includes.h"
#include "isession_listener_t.h"
#include "iref_count_t.h"
#include "opcua_byte_t.h"
#include "opcua_uint64_t.h"

namespace uasdk
{
class IFileUA_t : public ISessionListener_t
{
public:
  virtual ~IFileUA_t() {};

  /*****************************************************************************/
  /** Session created callback
  *
  * This function will be called by the SDK when the session is created
  */
  virtual void SessionCreated(IntrusivePtr_t<const NodeId_t>& sessionId) = 0;

  /*****************************************************************************/
  /** Session Activated callback
  *
  * This function will be called by the SDK when the session is Activated
  */
  virtual void SessionActivated(IntrusivePtr_t<const NodeId_t>& sessionId) = 0;

  /*****************************************************************************/
  /** Session closed callback
  *
  * This function will be called by the SDK when the session is closed
  */
  virtual void SessionClosed(IntrusivePtr_t<const NodeId_t>& sessionId) = 0;

  /*****************************************************************************/
  /** OpenCount of the file
  *
  * This function will return the number of file opened
  *
  * @return
  * number of file opened
  */
  virtual uint16_t OpenCount(void) = 0;

  /*****************************************************************************/
  /** Size of the file
  *
  * This function will return the size of the file object.
  * In case of errors 0 will be returned.
  *
  * @return
  * The size of file will be returned.
  */
  virtual uint64_t Size(void) = 0;

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
  virtual Status_t Open(IntrusivePtr_t<const NodeId_t> sessionId, Byte_t mode, uint32_t& fileHandle) = 0;

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
  virtual Status_t Close(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle) = 0;

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
  virtual Status_t Read(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, uint32_t lengthToRead, IntrusivePtr_t<ByteString_t>& output) = 0;

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
  virtual Status_t Write(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, IntrusivePtr_t<ByteString_t> dataToWrite) = 0;

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
  virtual Status_t GetPosition(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, IntrusivePtr_t<UInt64_t >& position) = 0;

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
  virtual Status_t SetPosition(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle, IntrusivePtr_t<UInt64_t> position) = 0;
};
}

#endif  //_IFILE_UA_T_