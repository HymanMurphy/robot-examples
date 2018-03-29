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

#ifndef _STD_FILE_T_
#define _STD_FILE_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_FILE_WINDOWS_LINUX > 0)

#include "linked_list_t.h"
#include "allocatable_t.h"
#include "ifile_t.h"
#include "opcua_string_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

  /*****************************************************************************/
  /** Brief about the Std File Object.
   *
   * This object will provide all file operations as specified by the OPC UA
   * Specification.
   * If file is opened for reading then file can only be opened again for reading.
   * If file is opened for writing then another instance of file open is not
   * possible either in read or write mode.
   */
class StdFile_t : public IFile_t, public Allocatable_t
{
private:

  bool                            initialised;
  bool                            writable;
  IntrusivePtr_t<String_t>        filename;
  mutable bool                    openedForWriting;
  mutable LinkedList_t<uintptr_t> contexts;

  /*****************************************************************************/
  /** This function used to open the file.
   *
   * @param[in] mode
   * file type mode.
   *
   * @param[in] append
   * boolean value
   *
   * @param[in] context
   *
   * @return
   * returns result of the operation.
   */

  Status_t OpenFile(const char* mode, bool append, uintptr_t& context) const;

public:
  StdFile_t() : initialised(false), writable(false), openedForWriting(false)  {}
  ~StdFile_t();

  /*****************************************************************************/
  /** This function used to initialize the object with filename and writable information.
    *
    * @param[in] writable_
    *
    * @param[in] filename_
    * Filename to be initialize
    *
    *  @return
    * returns result of the operation.
    */
  Status_t Initialise(bool writable_, IntrusivePtr_t<String_t>& filename_);

  /*****************************************************************************/
  /** This function gets the file size
    *
    *  @return
    * returns size in unsigned integer value.
    */
  virtual uint64_t Size(void) const;

  /*****************************************************************************/
  /** This function used to get the file writable status.
    *
    *  @return
    * returns booleans value.
    */
  virtual bool Writable(void) const;

  /*****************************************************************************/
  /** This function used to get the number of times a file has been opened
   *
   *  @return
   * returns open count.
   */
  virtual uint16_t OpenCount(void) const;

  /*****************************************************************************/
  /** This function used to open a file in read mode
   *
   * @param[in] context
   * context of the file
   *
   * @return
   * returns result of the operation.
   */
  virtual Status_t OpenForReading(uintptr_t& context) const;

  /*****************************************************************************/
  /** This function opens the file in read or write or append mode
   *
   * @param[in] allowReading
   * file reading allowance status
   *
   * @param[in] allowWriting
   * file writing allowance status
   *
   * @param[in] eraseExisting
   * file erase existing status
   *
   * @param[in] append
   * file appending status
   *
   * @param[in] context
   * file context
   *
   * @return
   * returns status  of the operation.
   */
  virtual Status_t Open(bool allowReading,
                        bool allowWriting,
                        bool eraseExisting,
                        bool append,
                        uintptr_t& context);

  /*****************************************************************************/
  /** This function used to close the file context
   *
   * @param[in] context
   * context of the file
   *
   * @return
   * returns status of the operation.
   */
  virtual Status_t Close(uintptr_t context) const;

  /*****************************************************************************/
  /** This function used to read the file.
   *
   * @param[in] context
   * context of the file
   *
   * @param[in] length
   * length of the data.
   *
   * @param[out] data
   * data to be read
   *
   * @return
   * returns status of the operation.
   */
  virtual Status_t Read(uintptr_t context, int32_t length, ByteString_t& data) const;

  /*****************************************************************************/
  /** This function used to write the data into the file.
   *
   * @param[in] context
   * context of the file
   *
   * @param[in] data
   * data to be written to the file
   *
   * @return
   * returns status of the operation.
   */
  virtual Status_t Write(uintptr_t context, const ByteString_t& data);

  /*****************************************************************************/
  /** This function used to get the current position of the file.
   *
   * @param[in] context
   * context of the file
   *
   * @param[out] position
   * position of the file context.,
   *
   * @return
   * returns status of the operation.
   */

  virtual Status_t GetPosition(uintptr_t context, uint64_t& position) const;

  /*****************************************************************************/
  /** This function used to set the new position to file
   *
   * @param[in] context
   * context of the file
   *
   * @param[in] position
   * position to be set for the file context.
   *
   * @return
   * returns status of the operation.
   */
  virtual Status_t SetPosition(uintptr_t context, uint64_t position) const;
};

/** @} */

} //namespace uasdk

#endif //UASDK_INCLUDE_FILE_WINDOWS_LINUX

#endif //_STD_FILE_T_
