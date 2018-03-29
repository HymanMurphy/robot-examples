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

#ifndef _BUFFER_T_
#define _BUFFER_T_

#include "ibuffer_t.h"
#include "allocatable_t.h"

namespace uasdk
{

/** \addtogroup grpBuffers
 *@{*/

class Buffer_t : public IBuffer_t, public Allocatable_t
{
private:

protected:

  /*****************************************************************************/
  /** Get the reference count
   *
   * @return
   * Returns the reference count
   */
  virtual int RefCount(void) const
  {
    return 0;
  }

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
  virtual Status_t WriteBytes(const uint8_t* data, uint32_t length) = 0;

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
  virtual Status_t ReadBytes(uint8_t* data, uint32_t length, bool increment = true) const = 0;

public:

  /*****************************************************************************/
  /** Default Constructor of the class
   */
  Buffer_t() {}

  /*****************************************************************************/
  /** Destructor of the class
   */
  virtual ~Buffer_t() {}

  /*****************************************************************************/
  /** Add Reference. Reference counting utility
   */
  virtual void AddReference() const
  {
    /* Allow use of subclasses without bolting on reference counting
     * functionality but catch it if it is used unintentionally
     */
    UASDK_ASSERT(false);
  }

  /*****************************************************************************/
  /** Remove Reference. Reference counting utility
   */
  virtual void RemoveReference() const
  {
    UASDK_ASSERT(false);
  }

  /*****************************************************************************/
  /** Check if the buffer is thread safe or not
   *
   * @return
   * True - Thread safe
   * False - Not thread safe
   */
  virtual bool IsThreadSafe(void) const
  {
    return false;
  }

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
  virtual Status_t Write(const void* data, uint32_t length);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * Data to write
   *
   * @param[in] length
   * number of bytes to be written
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(const IBuffer_t& data, uint32_t length);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * double Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(double val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * Float Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(float val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * uint64_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint64_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * int64_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int64_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * uint32_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint32_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * int32_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int32_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * uint16_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint16_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * int16_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int16_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * uint8_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(uint8_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * int8_t Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(int8_t val);

  /*****************************************************************************/
  /** Write to buffer
   *
   * @param[in] data
   * bool Data to write
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Write(bool val);

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
  virtual Status_t Read(void* data, uint32_t length, bool increment = true) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * double Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(double& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * float Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(float& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * uint64_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint64_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * int64_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int64_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * uint32_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint32_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * int32_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int32_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * uint16_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint16_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * int16_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int16_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * uint8_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(uint8_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * int8_t Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(int8_t& val) const;

  /*****************************************************************************/
  /** Read from the buffer
   *
   * @param[out] data
   * bool Data to read
   *
   * @return
   * The result of the operation
   */
  virtual Status_t Read(bool& val) const;

  /*****************************************************************************/
  /** Copy from the buffer
   *
   * @param[in] const IBuffer_t& source
   * Source data buffer
   *
   * @param[in] uint32_t length
   * length of the data
   *
   * @return
   * The result of the operation
   */
  virtual Status_t CopyFrom(const IBuffer_t& source, uint32_t length);

};

/** @} */

}
#endif // _BUFFER_T_
