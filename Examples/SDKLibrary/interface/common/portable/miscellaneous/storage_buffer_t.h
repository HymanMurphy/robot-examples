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

#ifndef _STORAGE_BUFFER_T_
#define _STORAGE_BUFFER_T_

#include "array_t.h"
#include "uasdk_includes.h"
#include "wrap_buffer_t.h"
#include "safe_ref_count_t.h"

namespace uasdk
{

/** \addtogroup grpBuffers
 *@{*/

class StorageBuffer_t : public Buffer_t
{
private:

  /*****************************************************************************/
  /** @var Array_t<uint8_t> storage
   * Storage array
   */
  Array_t<uint8_t> storage;

  /*****************************************************************************/
  /** @var Wrap_Buffer_t buffer
   * Wrape buffer
   */
  WrapBuffer_t buffer;

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * pointer to the data to be written
   *
   * @param[in] length
   * number of bytes to be written
   *
   * @return
   * The result of the operation
   */
  virtual Status_t WriteBytes(const uint8_t* data, uint32_t length);

  /*****************************************************************************/
  /** Read from buffer
   *
   * @param[out] data
   * Pointer to the destination array
   *
   * @param[in] length
   * number of bytes to be read
   *
   * @param[in] increment
   * If set to true, read index will be incremented to the bytes read from the buffer ()
   *
   * @return
   * The result of the operation
   */
  virtual Status_t ReadBytes(uint8_t* data, uint32_t length, bool increment = true) const;

public:

  /*****************************************************************************/
  /** Default Constructor of the class
   */
  StorageBuffer_t()  {}

  /*****************************************************************************/
  /** Destructor of the class
   */
  virtual ~StorageBuffer_t() {}

  /*****************************************************************************/
  /** Get the wrap buffer
   *
   * @return
   * Returns the wrap buffer
   */
  const WrapBuffer_t& Buffer(void) const { return buffer; }

  /*****************************************************************************/
  /** Initialize the storage buffer
   *
   * @param[in] uint8_t* storage_
   * Pointer to the storage buffer
   *
   * @return
   * Returns status of the operation
   */
  Status_t Initialise(uint32_t storage_length_);

  /*****************************************************************************/
  /** Checks the object is initialized or not
   *
   * @return
   * Returns true if the buffer is initialized already
   */
  virtual bool Initialised(void) { return storage.Initialised() && buffer.Initialised(); }

  /*****************************************************************************/
  /** Clear the buffer. Reset the buffer read and write index to zero.
   */
  virtual void Clear(void);

  /*****************************************************************************/
  /** Get the write index
   *
   * @return
   * Returns the write index of the buffer.
   */
  virtual uint32_t WriteIndex() const;

  /*****************************************************************************/
  /** Set the write index
   *
   * @param[in] uint32_t val
   * Write index to be set
   */
  virtual Status_t WriteIndex(uint32_t val);

  /*****************************************************************************/
  /** Get the read index
   *
   * @return
   * Returns the read index of the buffer.
   */
  virtual uint32_t ReadIndex() const;

  /*****************************************************************************/
  /** Set the read index
   *
   * @param[in] uint32_t val
   * Read index to be set
   */
  virtual Status_t ReadIndex(uint32_t val) const;

  /*****************************************************************************/
  /** Get the Write address of the buffer
   *
   * @return
   * Write address of the buffer
   */
  virtual uint8_t* WriteAddress() const;

  /*****************************************************************************/
  /** Set the new Write address to the buffer
   *
   * @param[in] val
   * new write address to the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t WriteAddress(uint8_t* val);

  /*****************************************************************************/
  /** Get the Read address of the buffer
   *
   * @return
   * Read address of the buffer
   */
  virtual uint8_t* ReadAddress() const;

  /*****************************************************************************/
  /** Set the new Read address to the buffer
   *
   * @param[in] val
   * new read address to the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t ReadAddress(uint8_t* val) const;

  /*****************************************************************************/
  /** Get the index from the address
   *
   * @param[in] val
   * address whose index to be identified
   *
   * @param[out] index
   * index of the address
   *
   * @return
   * The result of the operation
   */
  virtual Status_t GetIndexFromAddress(uint8_t* val, uint32_t& index) const;

  /*****************************************************************************/
  /** Get the address from the index
   *
   * @param[in] val
   * index whose address to be identified
   *
   * @param[out] address
   * address of the index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t GetAddressFromIndex(uint32_t val, uint8_t*& address) const;

  /*****************************************************************************/
  /** Test the address is valid or not
   *
   * @param[in] val
   * address to be checked
   *
   * @return
   * The result of the operation
   */
  virtual Status_t TestAddress(uint8_t* val) const;

  /*****************************************************************************/
  /** Increment write index
   *
   * @param[in] no_of_bytes
   * number of bytes to be incremented for write index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t IncrementWriteIndex(uint32_t no_of_bytes);

  /*****************************************************************************/
  /** Decrement write index
   *
   * @param[in] no_of_bytes
   * number of bytes to be decrement for write index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t DecrementWriteIndex(uint32_t no_of_bytes);

  /*****************************************************************************/
  /** Increment read index
   *
   * @param[in] no_of_bytes
   * number of bytes to be incremented for read index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t IncrementReadIndex(uint32_t no_of_bytes) const;

  /*****************************************************************************/
  /** Decrement read index
   *
   * @param[in] no_of_bytes
   * number of bytes to be decrement for read index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t DecrementReadIndex(uint32_t no_of_bytes) const;

  /*****************************************************************************/
  /** Check for the write address alignment
   *
   * @param[in] alignment
   * the alignment value for the buffer
   *
   * @return
   * Address after the alignment
   */
  virtual uint32_t IsWriteAddressAligned(uint32_t alignment) const;

  /*****************************************************************************/
  /** Total size of the buffer
   *
   * @return
   * size of the buffer or block
   */
  virtual uint32_t TotalSize(void) const;

  /*****************************************************************************/
  /** Space remaining in the buffer
   *
   * @return
   * size remaining in the buffer or block
   */
  virtual uint32_t SpaceRemaining(void) const;

  /*****************************************************************************/
  /** Length of Unread data
   *
   * @return
   * size of the buffer or block which is unread
   */
  virtual uint32_t DataUnread(void) const;

  /*****************************************************************************/
  /** Contiguous space remaining in the buffer
  *
  * @return
  * size remaining in the buffer or block
  */
  virtual uint32_t ContiguousSpaceRemaining(void) const;

  /*****************************************************************************/
  /** Length of Contiguous unread data
  *
  * @return
  * size of the buffer or block which is unread
  */
  virtual uint32_t ContiguousDataUnread(void) const;

  /*****************************************************************************/
  /** Is buffer empty
   *
   * @return
   * True if the buffer is empty. False otherwise.
   */
  virtual bool IsEmpty(void) const;

  /*****************************************************************************/
  /** Convert the unread data into byte string
   *
   * @return
   * unread data in byte string format
   */
  virtual UA_Byte_string_t Expose_unread_data_as_legacy(void);

  /*****************************************************************************/
  /** Convert the free buffer space into byte string
   *
   * @return
   * Byte string format free buffer space
   */
  virtual UA_Byte_string_t Expose_free_space_as_legacy(void);

};

/** @} */

}
#endif // _STORAGE_BUFFER_T_
