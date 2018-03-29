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

#ifndef _IBUFFER_T_
#define _IBUFFER_T_

#include "iref_count_t.h"
#include "uasdk_includes.h"

namespace uasdk
{
/** \addtogroup grpBuffers
 *@{*/

class IBuffer_t : public IRefCount_t
{
public:
  virtual ~IBuffer_t() {}

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
  virtual Status_t Write(const void* data, uint32_t length) = 0;

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * Reference to the IBuffer object
   *
   * @param[in] length
   * number of bytes to be written
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(const IBuffer_t& data, uint32_t length) = 0;

  /*****************************************************************************/
  /** Write double value to buffer
   *
   * @param[in] val
   * value of type double to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(double val) = 0;

  /*****************************************************************************/
  /** Write float value to buffer
   *
   * @param[in] val
   * value of type float to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(float val) = 0;

  /*****************************************************************************/
  /** Write uint64_t value to buffer
   *
   * @param[in] val
   * value of type uint64_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint64_t val) = 0;

  /*****************************************************************************/
  /** Write int64_t value to buffer
   *
   * @param[in] val
   * value of type int64_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int64_t val) = 0;

  /*****************************************************************************/
  /** Write uint32_t value to buffer
   *
   * @param[in] val
   * value of type uint32_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint32_t val) = 0;

  /*****************************************************************************/
  /** Write int32_t value to buffer
   *
   * @param[in] val
   * value of type int32_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int32_t val) = 0;

  /*****************************************************************************/
  /** Write uint16_t value to buffer
   *
   * @param[in] val
   * value of type uint16_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint16_t val) = 0;

  /*****************************************************************************/
  /** Write int16_t value to buffer
   *
   * @param[in] val
   * value of type int16_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int16_t val) = 0;

  /*****************************************************************************/
  /** Write uint8_t valueto buffer
   *
   * @param[in] val
   * value of type uint8_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint8_t val) = 0;

  /*****************************************************************************/
  /** Write int8_t value to buffer
   *
   * @param[in] val
   * value of type int8_t to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int8_t val) = 0;

  /*****************************************************************************/
  /** Write boolean value to buffer
   *
   * @param[in] val
   * value of type boolean to be written to buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(bool val) = 0;


  /*****************************************************************************/
  /** Read from buffer
   *
   * @param[in] data
   * pointer data where data to be read from the buffer
   *
   * @param[in] length
   * number of bytes to be read
   *
   * @param[in] increment
   * if set to true, the buffer's memory will be incremented by length value
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(void* data, uint32_t length, bool increment = true) const = 0;

  /*****************************************************************************/
  /** Read double from buffer
   *
   * @param[in] val
   * reference to the type double where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(double& val) const = 0;

  /*****************************************************************************/
  /** Read float from buffer
   *
   * @param[in] val
   * reference to the type float where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(float& val) const = 0;

  /*****************************************************************************/
  /** Read uint64_t from buffer
   *
   * @param[in] val
   * reference to the type uint64_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint64_t& val) const = 0;

  /*****************************************************************************/
  /** Read int64_t from buffer
   *
   * @param[in] val
   * reference to the type int64_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int64_t& val) const = 0;

  /*****************************************************************************/
  /** Read uint32_t from buffer
   *
   * @param[in] val
   * reference to the type uint32_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint32_t& val) const = 0;

  /*****************************************************************************/
  /** Read int32_t from buffer
   *
   * @param[in] val
   * reference to the type int32_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int32_t& val) const = 0;

  /*****************************************************************************/
  /** Read uint16_t from buffer
   *
   * @param[in] val
   * reference to the type uint16_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint16_t& val) const = 0;

  /*****************************************************************************/
  /** Read int16_t from buffer
   *
   * @param[in] val
   * reference to the type int16_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int16_t& val) const = 0;

  /*****************************************************************************/
  /** Read uint8_t from buffer
   *
   * @param[in] val
   * reference to the type uint8_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint8_t& val) const = 0;

  /*****************************************************************************/
  /** Read int8_t from buffer
   *
   * @param[in] val
   * reference to the type int8_t where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int8_t& val) const = 0;

  /*****************************************************************************/
  /** Read bool from buffer
   *
   * @param[in] val
   * reference to the type bool where value will be stored from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(bool& val) const = 0;

  /*****************************************************************************/
  /** Copy to Buffer
   *
   * @param[in] source
   * reference buffer object from where data to be copied
   *
   * @param[in] length
   * number of bytes to be copied from the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t CopyFrom(const IBuffer_t& source, uint32_t length) = 0;

  /*****************************************************************************/
  /** Clear the buffer
   *
   */
  virtual void Clear(void) = 0;

  /*****************************************************************************/
  /** Get the Write index of the buffer
   *
   * @return
   * write index of the buffer
   */
  virtual uint32_t WriteIndex() const = 0;

  /*****************************************************************************/
  /** Set the new Write index to the buffer
   *
   * @param[in] val
   * new write index to the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t WriteIndex(uint32_t val) = 0;

  /*****************************************************************************/
  /** Get the Read index of the buffer
   *
   * @return
   * Read index of the buffer
   */
  virtual uint32_t ReadIndex() const = 0;

  /*****************************************************************************/
  /** Set the new Read index to the buffer
   *
   * @param[in] val
   * new read index to the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t ReadIndex(uint32_t val) const = 0;

  /*****************************************************************************/
  /** Get the Write address of the buffer
   *
   * @return
   * Write address of the buffer
   */
  virtual uint8_t* WriteAddress() const = 0;

  /*****************************************************************************/
  /** Set the new Write address to the buffer
   *
   * @param[in] val
   * new write address to the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t WriteAddress(uint8_t* val) = 0;

  /*****************************************************************************/
  /** Get the Read address of the buffer
   *
   * @return
   * Read address of the buffer
   */
  virtual uint8_t* ReadAddress() const = 0;

  /*****************************************************************************/
  /** Set the new Read address to the buffer
   *
   * @param[in] val
   * new read address to the buffer
   *
   * @return
   * The result of the operation
   */
  virtual Status_t ReadAddress(uint8_t* val) const = 0;

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
  virtual Status_t GetIndexFromAddress(uint8_t* val, uint32_t& index) const = 0;

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
  virtual Status_t GetAddressFromIndex(uint32_t val, uint8_t*& address) const = 0;

  /*****************************************************************************/
  /** Test the address
   *
   * @param[in] val
   * address to be checked
   *
   * @return
   * The result of the operation
   */
  virtual Status_t TestAddress(uint8_t* val) const = 0;

  /*****************************************************************************/
  /** Increment write index
   *
   * @param[in] no_of_bytes
   * number of bytes to be incremented for write index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t IncrementWriteIndex(uint32_t no_of_bytes) = 0;

  /*****************************************************************************/
  /** Decrement write index
   *
   * @param[in] no_of_bytes
   * number of bytes to be decrement for write index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t DecrementWriteIndex(uint32_t no_of_bytes) = 0;

  /*****************************************************************************/
  /** Increment read index
   *
   * @param[in] no_of_bytes
   * number of bytes to be incremented for read index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t IncrementReadIndex(uint32_t no_of_bytes) const = 0;

  /*****************************************************************************/
  /** Decrement read index
   *
   * @param[in] no_of_bytes
   * number of bytes to be decrement for read index
   *
   * @return
   * The result of the operation
   */
  virtual Status_t DecrementReadIndex(uint32_t no_of_bytes) const = 0;

  /*****************************************************************************/
  /** Check for the write address alignment
   *
   * @param[in] alignment
   * the alignment value for the buffer
   *
   * @return
   * Address after the alignment
   */
  virtual uint32_t IsWriteAddressAligned(uint32_t alignment) const = 0;

  /*****************************************************************************/
  /** Total size of the buffer
   *
   * @return
   * size of the buffer or block
   */
  virtual uint32_t TotalSize(void) const = 0;

  /*****************************************************************************/
  /** Space remaining in the buffer
   *
   * @return
   * size remaining in the buffer or block
   */
  virtual uint32_t SpaceRemaining(void) const = 0;

  /*****************************************************************************/
  /** Length of Unread data
   *
   * @return
   * size of the buffer or block which is unread
   */
  virtual uint32_t DataUnread(void) const = 0;

  /*****************************************************************************/
  /** Contiguous space remaining in the buffer
  *
  * @return
  * size remaining in the buffer or block
  */
  virtual uint32_t ContiguousSpaceRemaining(void) const = 0;

  /*****************************************************************************/
  /** Length of Contiguous unread data
  *
  * @return
  * size of the buffer or block which is unread
  */
  virtual uint32_t ContiguousDataUnread(void) const = 0;

  /*****************************************************************************/
  /** Is buffer empty
   *
   * @return
   * True if the buffer is empty. False otherwise.
   */
  virtual bool IsEmpty(void) const = 0;
};

/** @} */
}

#endif // _IBUFFER_T_
