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

#ifndef _OPCUA_STATUS_CHANGE_NOTIFICATION_T_
#define _OPCUA_STATUS_CHANGE_NOTIFICATION_T_


#include "opcua_structure_t.h"
#include "opcua_status_code_t.h"
#include "opcua_diagnostic_info_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief StatusChangeNotification_t
 *
 * This class implements the Status Change Notification data type
 *
 */
class StatusChangeNotification_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(StatusChangeNotification_t);
private:

  /*****************************************************************************/
  /* @var StatusCode_t statusCode
   * Status code
   */
  StatusCode_t      statusCode;

  /*****************************************************************************/
  /* @var DiagnosticInfo_t  diagnosticInfo
   * Diagnostic Information
   */
  DiagnosticInfo_t  diagnosticInfo;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_StatusChangeNotification;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~StatusChangeNotification_t();

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
   * @param[in]  StatusChangeNotification_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the Status Change Notification object assigned
   */
  bool operator==(StatusChangeNotification_t const & obj) const;

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
   * @param[in] StatusChangeNotification_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS StatusChangeNotification_t object is greater than RHS StatusChangeNotification_t object
   */
  bool operator>(StatusChangeNotification_t const & obj) const;

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
   * @param[in] const StatusChangeNotification_t& source
   *  Status Change Notification source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const StatusChangeNotification_t& source);

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
  /** Get the Status code
   *
   * @return
   * Returns the Status code
   */
  const StatusCode_t& StatusCode(void) const;

  /*****************************************************************************/
  /** Get the Status code
   *
   * @return
   * Returns the Status code
   */
  StatusCode_t& StatusCode(void);

  /*****************************************************************************/
  /** Get the Diagnostic Information
   *
   * @return
   * Returns the Diagnostic Information
   */
  const DiagnosticInfo_t& DiagnosticInfo(void) const;

  /*****************************************************************************/
  /** Get the Diagnostic Information
   *
   * @return
   * Returns the Diagnostic Information
   */
  DiagnosticInfo_t& DiagnosticInfo(void);

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
   * @param[out] StatusChangeNotification_t& result
   * Decoded Status Change Notification object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, StatusChangeNotification_t& result);
};

/** @} */

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_STATUS_CHANGE_NOTIFICATION_T_
