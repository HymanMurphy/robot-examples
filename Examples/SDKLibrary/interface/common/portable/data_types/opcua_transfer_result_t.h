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

#ifndef _OPCUA_TRANSFER_RESULT_T_
#define _OPCUA_TRANSFER_RESULT_T_

#include "opcua_structure_t.h"
#include "opcua_uint32_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_status_code_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0 && UASDK_INCLUDE_TRANSFER_SUBSCRIPTIONS_SERVICE > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief TransferResult_t
 *
 * This class implements the Transfer Result Result data type
 *
 */
class TransferResult_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(TransferResult_t);

private:

  /*****************************************************************************/
  /* @var StatusCode_t statusCode
   * Call method status code
   */
  StatusCode_t          statusCode;

  /*****************************************************************************/
  /* @var ArrayUA_t<Counter_t>  availableSequenceNumbers
   * Available Sequence Numbers
   */
  ArrayUA_t<Counter_t>  availableSequenceNumbers;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_TransferResult;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~TransferResult_t();


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
  /** = operator overloading
   *
   * @param[in] const TransferResult_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Transfer Result object assigned
   */
  bool operator==(TransferResult_t const & obj) const;

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
   * @param[in] TransferResult_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS TransferResult_t object is greater than RHS TransferResult_t object
   */
  bool operator>(TransferResult_t const & obj) const;

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
   * @param[in] const MonItemModifyResult_t& source
   *  Monitor Item modify Result source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const TransferResult_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
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
  /** Get the call method result status code
   *
   * @return
   * Returns the call method result status code
   */
  const StatusCode_t& StatusCode(void) const;

  /*****************************************************************************/
  /** Get the call method result status code
   *
   * @return
   * Returns the call method result status code
   */
  StatusCode_t& StatusCode(void);

  /*****************************************************************************/
  /** Get the Available Sequence Numbers
   *
   * @return
   * Returns the Available Sequence Numbers
   */
  const ArrayUA_t<Counter_t>& AvailableSequenceNumbers(void) const;

  /*****************************************************************************/
  /** Get the Available Sequence Numbers
   *
   * @return
   * Returns the Available Sequence Numbers
   */
  ArrayUA_t<Counter_t>& AvailableSequenceNumbers(void);

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
   * @param[out] TransferResult_t& result
   * Decoded Transfer Result object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, TransferResult_t& result);
};

/** @} */

} // namespace uasdk

#endif

#endif // _OPCUA_TRANSFER_RESULT_T_
