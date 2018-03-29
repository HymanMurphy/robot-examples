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

#ifndef _OPCUA_MON_ITEM_MODIFY_REQUEST_T_
#define _OPCUA_MON_ITEM_MODIFY_REQUEST_T_

#include "opcua_structure_t.h"
#include "opcua_uint32_t.h"
#include "opcua_mon_parameters_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief MonItemModifyRequest_t
 *
 * This class implements the Monitor Item modify Request data type
 *
 */
class MonItemModifyRequest_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(MonItemModifyRequest_t);
private:

  /*****************************************************************************/
  /* @var IntegerId_t monitoredItemId
   * Monitored item ID
   */
  IntegerId_t     monitoredItemId;

  /*****************************************************************************/
  /* @var MonParameters_t requestedParameters
   * Requested parameter
   */
  MonParameters_t requestedParameters;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_MonitoredItemModifyRequest;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  MonItemModifyRequest_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~MonItemModifyRequest_t();

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
   * @param[in] MonItemModifyRequest_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(MonItemModifyRequest_t const & obj) const;

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
   * @param[in] MonItemModifyRequest_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS MonItemModifyRequest_t object is greater than RHS MonItemModifyRequest_t object
   */
  bool operator>(MonItemModifyRequest_t const & obj) const;

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
   * @param[in] const MonItemModifyRequest_t& source
   *  Monitored Item Create Request source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const MonItemModifyRequest_t& source);

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
  /** Get the monitored item ID
   *
   * @return
   * Returns the monitored item ID
   */
  const IntegerId_t& MonitoredItemId(void) const;

  /*****************************************************************************/
  /** Get the monitored item ID
   *
   * @return
   * Returns the monitored item ID
   */
  IntegerId_t& MonitoredItemId(void);

  /*****************************************************************************/
  /** Get the Requested Parameters
   *
   * @return
   * Returns the Requested Parameters
   */
  const MonParameters_t& RequestedParameters(void) const;

  /*****************************************************************************/
  /** Get the Requested Parameters
   *
   * @return
   * Returns the Requested Parameters
   */
  MonParameters_t& RequestedParameters(void);

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
   * @param[out] MonItemModifyRequest_t& result
   * Decoded Monitored Item Modify Request object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemModifyRequest_t& result);
};

/** @} */

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_MON_ITEM_MODIFY_REQUEST_T_
