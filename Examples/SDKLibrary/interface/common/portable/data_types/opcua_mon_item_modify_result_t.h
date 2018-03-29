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

#ifndef _OPCUA_MON_ITEM_MODIFY_RESULT_T_
#define _OPCUA_MON_ITEM_MODIFY_RESULT_T_

#include "opcua_structure_t.h"
#include "opcua_status_code_t.h"
#include "opcua_extensible_parameter_t.h"
#include "opcua_uint32_t.h"
#include "opcua_duration_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief MonItemModifyResult_t
 *
 * This class implements the Monitor Item modify  Result data type
 *
 */
class MonItemModifyResult_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(MonItemModifyResult_t);
private:

  /*****************************************************************************/
  /* @var StatusCode_t statusCode
   * Call method status code
   */
  StatusCode_t           statusCode;

  /*****************************************************************************/
  /* @var Duration_t revisedSamplingInterval
   * Rivised Sampling interval
   */
  Duration_t             revisedSamplingInterval;

  /*****************************************************************************/
  /* @var Counter_t revisedQueueSize
   * Revised Queue size
   */
  Counter_t              revisedQueueSize;

  /*****************************************************************************/
  /* @var ExtensibleParameter_t filterResult
   * Filter result
   */
  ExtensibleParameter_t  filterResult;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_MonitoredItemModifyResult;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  MonItemModifyResult_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~MonItemModifyResult_t();

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
   * @param[in] MonItemModifyResult_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(MonItemModifyResult_t const & obj) const;

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
   * @param[in] MonItemModifyResult_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS MonItemModifyResult_t object is greater than RHS MonItemModifyResult_t object
   */
  bool operator>(MonItemModifyResult_t const & obj) const;

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
  Status_t CopyFrom(const MonItemModifyResult_t& source);

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
  /** Get the Revised Sampling Interval
   *
   * @return
   * Returns the Revised Sampling Interval
   */
  const Duration_t& RevisedSamplingInterval(void) const;

  /*****************************************************************************/
  /** Get the Revised Sampling Interval
   *
   * @return
   * Returns the Revised Sampling Interval
   */
  Duration_t& RevisedSamplingInterval(void);

  /*****************************************************************************/
  /** Get the Revised Queue Size
   *
   * @return
   * Returns the Revised Queue Size
   */
  const Counter_t& RevisedQueueSize(void) const;

  /*****************************************************************************/
  /** Get the Revised Queue Size
   *
   * @return
   * Returns the Revised Queue Size
   */
  Counter_t& RevisedQueueSize(void);

  /*****************************************************************************/
  /** Get the Filter Result
   *
   * @return
   * Returns the Filter Result
   */
  const ExtensibleParameter_t& FilterResult(void) const;

  /*****************************************************************************/
  /** Get the Filter Result
   *
   * @return
   * Returns the Filter Result
   */
  ExtensibleParameter_t& FilterResult(void);

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
   * @param[out] MonItemModifyResult_t& result
   * Decoded Monitor Item Modify Result object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemModifyResult_t& result);
};

/** @} */

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_MON_ITEM_MODIFY_RESULT_T_  
