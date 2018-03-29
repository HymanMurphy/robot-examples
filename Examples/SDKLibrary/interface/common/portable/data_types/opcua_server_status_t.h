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

#ifndef _OPCUA_SERVER_STATUS_T_
#define _OPCUA_SERVER_STATUS_T_

#include "opcua_structure_t.h"
#include "opcua_date_time_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_build_info_t.h"
#include "opcua_date_time_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ServerStatus_t
 *
 * This class implements the Server status data type
 *
 */
class ServerStatus_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ServerStatus_t);
private:

  /*****************************************************************************/
  /* @var UtcTime_t startTime
   * Start Time
   */
  UtcTime_t            startTime;

  /*****************************************************************************/
  /* @var UtcTime_t currentTime
   * Current time
   */
  UtcTime_t            currentTime;

  /*****************************************************************************/
  /* @var ServerState_t state
   * Server state
   */
  ServerState_t		        state;

  /*****************************************************************************/
  /* @var BuildInfo_t buildInfo
   * Build Information
   */
  BuildInfo_t             buildInfo;

  /*****************************************************************************/
  /* @var UInt32_t secondsTillShutdown
   * Seconds till shutdown
   */
  UInt32_t                secondsTillShutdown;

  /*****************************************************************************/
  /* @var LocalizedText_t shutdownReason
   * Shutdown Reason
   */
  LocalizedText_t         shutdownReason;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ServerStatusDataType;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  ServerStatus_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ServerStatus_t();

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
   * @param[in] const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(ServerStatus_t const & obj) const;

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
   * @param[in] ServerStatus_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ServerStatus_t object is greater than RHS ServerStatus_t object
   */
  bool operator>(ServerStatus_t const & obj) const;

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
   * @param[in] const ServerStatus_t& source
   * Server Status source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ServerStatus_t& source);

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
  /** Get the Start Time
   *
   * @return
   * Returns the Start Time
   */
  const UtcTime_t& StartTime(void) const;

  /*****************************************************************************/
  /** Get the Start Time
   *
   * @return
   * Returns the Start Time
   */
  UtcTime_t& StartTime(void);

  /*****************************************************************************/
  /** Get the Current Time
   *
   * @return
   * Returns the Current Time
   */
  const UtcTime_t&  CurrentTime(void) const;

  /*****************************************************************************/
  /** Get the Current Time
   *
   * @return
   * Returns the Current Time
   */
  UtcTime_t&  CurrentTime(void);

  /*****************************************************************************/
  /** Get the Server State
   *
   * @return
   * Returns the Server State
   */
  const  ServerState_t& State(void) const;

  /*****************************************************************************/
  /** Get the Server State
   *
   * @return
   * Returns the Server State
   */
  ServerState_t& State(void);

  /*****************************************************************************/
  /** Get the Build Information
   *
   * @return
   * Returns the Build Information
   */
  const BuildInfo_t& BuildInfo(void) const;

  /*****************************************************************************/
  /** Get the Build Information
   *
   * @return
   * Returns the Build Information
   */
  BuildInfo_t& BuildInfo(void);

  /*****************************************************************************/
  /** Get the Seconds Till Shutdown
   *
   * @return
   * Returns the Seconds Till Shutdown
   */
  const UInt32_t&  SecondsTillShutdown(void) const;

  /*****************************************************************************/
  /** Get the Seconds Till Shutdown
   *
   * @return
   * Returns the Seconds Till Shutdown
   */
  UInt32_t&  SecondsTillShutdown(void);

  /*****************************************************************************/
  /** Get the Shutdown Reason
   *
   * @return
   * Returns the Shutdown Reason
   */
  const LocalizedText_t& ShutdownReason(void) const;

  /*****************************************************************************/
  /** Get the Shutdown Reason
   *
   * @return
   * Returns the Shutdown Reason
   */
  LocalizedText_t& ShutdownReason(void);

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
  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] ServerStatus_t& result
   * Decoded Server status object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ServerStatus_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_SERVER_STATUS_T_
