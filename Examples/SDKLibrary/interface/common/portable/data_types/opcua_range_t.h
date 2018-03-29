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

#ifndef _OPCUA_RANGE_T_
#define _OPCUA_RANGE_T_


#include "opcua_structure_t.h"
#include "opcua_double_t.h"

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Range_t
 *
 * This class implements the Rage data type
 *
 */
class Range_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(Range_t);
private:

  /*****************************************************************************/
  /* @var Double_t low
   * Low range
   */
  Double_t low;

  /*****************************************************************************/
  /* @var Double_t high
   * High range
   */
  Double_t high;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Range;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Range_t();

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] double low
   * Low rage value to be set
   *
   * @param[in] double high
   * High rage value to be set
   *
   */
  Range_t(double low_, double high_);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Range_t();

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  virtual bool operator==(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] Range_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Range_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If grater than RHS
   * False - If less than RHS
   */
  virtual bool operator>(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] Range_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Range_t object is greater than RHS Range_t object
   */
  bool operator>(Range_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const Range_t& source
   *  Range_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Range_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the Binary Encoding Id
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Binary Encoding Id
   */
  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the low range value
   *
   * @return
   * Returns the low range value
   */
  const Double_t& Low(void) const;

  /*****************************************************************************/
  /** Get the low range value
   *
   * @return
   * Returns the low range value
   */
  Double_t& Low(void);

  /*****************************************************************************/
  /** Get the high range value
   *
   * @return
   * Returns the high range value
   */
  const Double_t& High(void) const;

  /*****************************************************************************/
  /** Get the high range value
   *
   * @return
   * Returns the high range value
   */
  Double_t& High(void);

  /*****************************************************************************/
  /** Encode the buffer
   *
   * @param[in] ICodec_t& encoder
   * Reference to the encoder object
   *
   * @param[out] IBuffer_t& buffer
   * Encode buffer
   *
   * @return
   * Returns status of the operation
   */
  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] Range_t& result
   * Decoded Range object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, Range_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_RANGE_T_
