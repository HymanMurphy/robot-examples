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

#ifndef _IFILE_T_
#define _IFILE_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "opcua_bytestring_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

  /*****************************************************************************/
  /** Brief about the File Object.
   *
   * This object will provide all file operations as specified by the OPC UA
   * Specification.
   * If file is opened for reading then file can only be opened again for reading.
   * If file is opened for writing then another instance of file open is not
   * possible either in read or write mode.
   */
 
class IFile_t : public IRefCount_t{
public:
  virtual ~IFile_t() {}

  /*****************************************************************************/
  /** Size of the file
   *
   * This function will return the size of the file object.
   * In case of errors 0 will be returned.
   *
   * @return
   * The size of file will be returned.
   */
  virtual uint64_t Size(void) const = 0;
  
  /*****************************************************************************/
  /** File is writable or read only
   *
   * This function will return whether file object is writable or not
   *
   * @return
   * true if file object is writable. false is not writable.
   */
  virtual bool Writable(void) const = 0;

  /*****************************************************************************/
  /** Open count of file
   *
   * This function will returns the number of instances the file object is opened.
   *
   * @return
   * Number of instance the file object is opened.
   */
  virtual uint16_t OpenCount(void) const = 0;

  /*****************************************************************************/
  /** Open file object for reading
   *
   * This function will open the file for reading only if file object is
   * not already opened for writing
   *
   * @param[out] context
   * pointer to the file object which is successfully opened.
   * 
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t OpenForReading(uintptr_t& context) const = 0;

  /*****************************************************************************/
  /** Open file object
   *
   * This function will open the file for reading/writing/append new data
   *
   * @param[in] allowReading
   * Boolean flag to indicate open for reading 
   *
   * @param[in] allowWriting
   * Boolean flag to indicate open for writing
   *
   * @param[in] eraseExisting
   * Boolean flag to indicate erase the existing file
   *
   * @param[in] append
   * Boolean flag to indicate open in append mode
   *
   * @param[out] context
   * pointer to the file object which is successfully opened.
   * 
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Open(bool allowReading,
                        bool allowWriting,
                        bool eraseExisting,
                        bool append,
                        uintptr_t& context) = 0;

  /*****************************************************************************/
  /** Close file object
   *
   * This function will close the file object
   *
   * @param[in] context
   * pointer to the file object which has to be closed.
   * 
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Close(uintptr_t context) const = 0;

  /*****************************************************************************/
  /** Read the file object
   *
   * This function will read length number of bytes from the file object and
   * copy the file content to output variable.
   *
   * @param[in] context
   * pointer to the file object which has to be read.
   *
   * @param[in] length
   * number of bytes to be read from the file object.
   * 
   * @param[out] data
   * Buffer, where the file content will be stored
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Read(uintptr_t context, int32_t length, ByteString_t& data) const = 0;

  /*****************************************************************************/
  /** Write the file object
   *
   * This function will write the file object with the data passed as input
   * 
   * @param[in] context
   * pointer to the file object to which data has to be written
   *
   * @param[in] data
   * Buffer, from which data has to be written to file
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t Write(uintptr_t context, const ByteString_t& data) = 0;

  /*****************************************************************************/
  /** Get position of the file object
   *
   * This function will gets the current position in the file object.
   *
   * @param[in] context
   * pointer to the file object.
   * 
   * @param[out] position
   * current position of the file object.
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t GetPosition(uintptr_t context, uint64_t& position) const = 0;

  /*****************************************************************************/
  /** Set position to the file object
   *
   * This function which will set the file object with new position.
   *
   * @param[in] context
   * pointer to the file object.
   * 
   * @param[in] position
   * new position to the file object.
   *
   * @return
   * The OPC UA StatusCode representing the result of the operation.
   */
  virtual Status_t SetPosition(uintptr_t context, uint64_t position) const = 0;

};

/** @} */

}

#endif // _IFILE_T_
