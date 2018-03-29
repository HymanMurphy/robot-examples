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

#ifndef _OPCUA_MON_PARAMETERS_T_
#define _OPCUA_MON_PARAMETERS_T_

#include "opcua_structure_t.h"
#include "opcua_uint32_t.h"
#include "opcua_duration_t.h"
#include "opcua_boolean_t.h"
#include "opcua_extensible_parameter_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief MonParameters_t
 *
 * This class implements the Monitor Parameters data type
 *
 */
class MonParameters_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(MonParameters_t);

private:

  /*****************************************************************************/
  /* @var UInt32_t clientHandle
   *  Minitor item client handle
   */
  UInt32_t                 clientHandle;

  /*****************************************************************************/
  /* @var Duration_t samplingInterval
   * Sampling interval
   */
  Duration_t               samplingInterval;

  /*****************************************************************************/
  /* @var ExtensibleParameter_t filter
   * Filter
   */
  ExtensibleParameter_t    filter;

  /*****************************************************************************/
  /* @var Counter_t queueSize
   * Queue size
   */
  Counter_t                queueSize;

  /*****************************************************************************/
  /* @var Boolean_t discardOldest
   * Discard oldest
   */
  Boolean_t                discardOldest;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_MonitoringParameters;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  MonParameters_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~MonParameters_t();

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
   * @param[in] MonParameters_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(MonParameters_t const & obj) const;

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
   * @param[in] MonParameters_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS MonParameters_t object is greater than RHS MonParameters_t object
   */
  bool operator>(MonParameters_t const & obj) const;

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
   *  BaseDataType_t source to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const MonParameters_t& source
   *  MonParameters_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const MonParameters_t& source);

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
  /** Get the Client Handle
   *
   * @return
   * Returns the Client Handle
   */
  const UInt32_t& ClientHandle(void) const;

  /*****************************************************************************/
  /** Get the Client Handle
   *
   * @return
   * Returns the Client Handle
   */
  UInt32_t& ClientHandle(void);

  /*****************************************************************************/
  /** Get the Sampling Interval
   *
   * @return
   * Returns the Sampling Interval
   */
  const Duration_t& SamplingInterval(void) const;

  /*****************************************************************************/
  /** Get the Sampling Interval
   *
   * @return
   * Returns the Sampling Interval
   */
  Duration_t& SamplingInterval(void);

  /*****************************************************************************/
  /** Get the Filter
   *
   * @return
   * Returns the Filter
   */
  const ExtensibleParameter_t& Filter(void) const;

  /*****************************************************************************/
  /** Get the Filter
   *
   * @return
   * Returns the Filter
   */
  ExtensibleParameter_t& Filter(void);

  /*****************************************************************************/
  /** Get the Queue Size
   *
   * @return
   * Returns the Queue Size
   */
  const Counter_t& QueueSize(void) const;

  /*****************************************************************************/
  /** Get the Queue Size
   *
   * @return
   * Returns the Queue Size
   */
  Counter_t& QueueSize(void);

  /*****************************************************************************/
  /** Get the Discard Oldest
   *
   * @return
   * Returns the Discard Oldest
   */
  const Boolean_t& DiscardOldest(void) const;

  /*****************************************************************************/
  /** Get the Discard Oldest
   *
   * @return
   * Returns the Discard Oldest
   */
  Boolean_t& DiscardOldest(void);

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
   * @param[out] MonParameters_t& result
   * Decoded MonParameters_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonParameters_t& result);
};

/** @} */

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_MON_PARAMETERS_T_
