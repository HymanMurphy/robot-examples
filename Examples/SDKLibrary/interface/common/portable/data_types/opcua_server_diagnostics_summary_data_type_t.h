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

#ifndef _OPCUA_SERVER_DIAGNOSTICS_SUMMARY_DATA_TYPE_T_H_
#define _OPCUA_SERVER_DIAGNOSTICS_SUMMARY_DATA_TYPE_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY > 0)

#include "opcua_structure_t.h"
#include "opcua_uint32_t.h"

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ServerDiagnosticsSummaryDataType_t
 *
 * This class implements the Server Diagnostics Summery Data Type
 *
 */
class ServerDiagnosticsSummaryDataType_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ServerDiagnosticsSummaryDataType_t);

private:

  /*****************************************************************************/
  /* @var UInt32_t serverViewCount
   * number view nodes created
   */
  UInt32_t serverViewCount;
  
  /*****************************************************************************/
  /* @var UInt32_t currentSessionCount
   * Current Session Count
   */
  UInt32_t currentSessionCount;
  
  /*****************************************************************************/
  /* @var UInt32_t cumulatedSessionCount
   * Total number of Session count
   */
  UInt32_t cumulatedSessionCount;
  
  /*****************************************************************************/
  /* @var UInt32_t securityRejectedSessionCount
   * Rejected Session Count for Security reasons
   */
  UInt32_t securityRejectedSessionCount;
  
  /*****************************************************************************/
  /* @var UInt32_t rejectedSessionCount
   * Total Rejected Session Count
   */
  UInt32_t rejectedSessionCount;
  
  /*****************************************************************************/
  /* @var UInt32_t sessionTimeoutCount
   * Session Timeout Count
   */
  UInt32_t sessionTimeoutCount;
  
  /*****************************************************************************/
  /* @var UInt32_t sessionAbortCount
   * Session Abort Count
   */
  UInt32_t sessionAbortCount;
  
  /*****************************************************************************/
  /* @var UInt32_t publishingIntervalCount
   * Publishing Interval Count
   */
  UInt32_t publishingIntervalCount;
  
  /*****************************************************************************/
  /* @var UInt32_t currentSubscriptionCount
   * Subscription Count in a Session
   */
  UInt32_t currentSubscriptionCount;
  
  /*****************************************************************************/
  /* @var UInt32_t cumulatedSubscriptionCount
   * Subscription Count in all Sessions
   */
  UInt32_t cumulatedSubscriptionCount;
  
  /*****************************************************************************/
  /* @var UInt32_t securityRejectedRequestsCount
   * Rejected Service Requests Count due to Security reason
   */
  UInt32_t securityRejectedRequestsCount;
  
  /*****************************************************************************/
  /* @var UInt32_t rejectedRequestsCount
   * Rejected Service Requests Count
   */
  UInt32_t rejectedRequestsCount;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID for ServerDiagnosticsSummaryDataType
   */
  static const uint32_t TYPE_ID = OpcUaId_ServerDiagnosticsSummaryDataType;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  ServerDiagnosticsSummaryDataType_t();
  
  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ServerDiagnosticsSummaryDataType_t();

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
   * @param[in] ServerDiagnosticsSummaryDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(ServerDiagnosticsSummaryDataType_t const & obj) const;

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are not same
   * False - If the both the objects are same
   */
  bool operator!=(ServerDiagnosticsSummaryDataType_t const & obj) const;

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
   * @param[in] ServerDiagnosticsSummaryDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ServerDiagnosticsSummaryDataType_t object is greater than RHS ServerDiagnosticsSummaryDataType_t object
   */
  bool operator>(ServerDiagnosticsSummaryDataType_t const & obj) const;

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
   * @param[in] const ServerDiagnosticsSummaryDataType_t& source
   * Server Diagnostics Summery Data Type source object to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const ServerDiagnosticsSummaryDataType_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Data Type ID
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
  /** Get the ServerViewCount
   *
   * @return
   * Returns the ServerViewCount
   */
  const UInt32_t& ServerViewCount() const;
  
  /*****************************************************************************/
  /** Get the ServerViewCount
   *
   * @return
   * Returns the ServerViewCount
   */
  UInt32_t& ServerViewCount();

  /*****************************************************************************/
  /** Get the CurrentSessionCount
   *
   * @return
   * Returns the CurrentSessionCount
   */
  const UInt32_t& CurrentSessionCount() const;
  
  /*****************************************************************************/
  /** Get the CurrentSessionCount
   *
   * @return
   * Returns the CurrentSessionCount
   */
  UInt32_t& CurrentSessionCount();

  /*****************************************************************************/
  /** Get the CumulatedSessionCount
   *
   * @return
   * Returns the CumulatedSessionCount
   */
  const UInt32_t& CumulatedSessionCount() const;
  
  /*****************************************************************************/
  /** Get the CumulatedSessionCount
   *
   * @return
   * Returns the CumulatedSessionCount
   */
  UInt32_t& CumulatedSessionCount();

  /*****************************************************************************/
  /** Get the SecurityRejectedSessionCount
   *
   * @return
   * Returns the SecurityRejectedSessionCount
   */
  const UInt32_t& SecurityRejectedSessionCount() const;
  
  /*****************************************************************************/
  /** Get the SecurityRejectedSessionCount
   *
   * @return
   * Returns the SecurityRejectedSessionCount
   */
  UInt32_t& SecurityRejectedSessionCount();

  /*****************************************************************************/
  /** Get the RejectedSessionCount
   *
   * @return
   * Returns the RejectedSessionCount
   */
  const UInt32_t& RejectedSessionCount() const;
  
  /*****************************************************************************/
  /** Get the RejectedSessionCount
   *
   * @return
   * Returns the RejectedSessionCount
   */
  UInt32_t& RejectedSessionCount();

  /*****************************************************************************/
  /** Get the SessionTimeoutCount
   *
   * @return
   * Returns the SessionTimeoutCount
   */
  const UInt32_t& SessionTimeoutCount() const;
  
  /*****************************************************************************/
  /** Get the SessionTimeoutCount
   *
   * @return
   * Returns the SessionTimeoutCount
   */
  UInt32_t& SessionTimeoutCount();

  /*****************************************************************************/
  /** Get the SessionAbortCount
   *
   * @return
   * Returns the SessionAbortCount
   */
  const UInt32_t& SessionAbortCount() const;
  
  /*****************************************************************************/
  /** Get the SessionAbortCount
   *
   * @return
   * Returns the SessionAbortCount
   */
  UInt32_t& SessionAbortCount();

  /*****************************************************************************/
  /** Get the PublishingIntervalCount
   *
   * @return
   * Returns the PublishingIntervalCount
   */
  const UInt32_t& PublishingIntervalCount() const;
  
  /*****************************************************************************/
  /** Get the PublishingIntervalCount
   *
   * @return
   * Returns the PublishingIntervalCount
   */
  UInt32_t& PublishingIntervalCount();
  
  /*****************************************************************************/
  /** Get the CurrentSubscriptionCount
   *
   * @return
   * Returns the CurrentSubscriptionCount
   */
  const UInt32_t& CurrentSubscriptionCount() const;
  
  /*****************************************************************************/
  /** Get the CurrentSubscriptionCount
   *
   * @return
   * Returns the CurrentSubscriptionCount
   */
  UInt32_t& CurrentSubscriptionCount();

  /***************************************************************************/
  /** Get the CumulatedSubscriptionCount
   *
   * @return
   * Returns the CumulatedSubscriptionCount
   */
  const UInt32_t& CumulatedSubscriptionCount() const;
  
  /*****************************************************************************/
  /** Get the CumulatedSubscriptionCount
   *
   * @return
   * Returns the CumulatedSubscriptionCount
   */
  UInt32_t& CumulatedSubscriptionCount();

  /*****************************************************************************/
  /** Get the SecurityRejectedRequestsCount
   *
   * @return
   * Returns the SecurityRejectedRequestsCount
   */
  const UInt32_t& SecurityRejectedRequestsCount() const;
  
  /*****************************************************************************/
  /** Get the SecurityRejectedRequestsCount
   *
   * @return
   * Returns the SecurityRejectedRequestsCount
   */
  UInt32_t& SecurityRejectedRequestsCount();

  /*****************************************************************************/
  /** Get the RejectedRequestsCount
   *
   * @return
   * Returns the RejectedRequestsCount
   */
  const UInt32_t& RejectedRequestsCount() const;
  
  /*****************************************************************************/
  /** Get the RejectedRequestsCount
   *
   * @return
   * Returns the RejectedRequestsCount
   */
  UInt32_t& RejectedRequestsCount();

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
   * @param[out] ServerDiagnosticsSummaryDataType_t& result
   * Decoded Server Diagnostics Summery Data Type
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ServerDiagnosticsSummaryDataType_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY

#endif /* _OPCUA_SERVER_DIAGNOSTICS_SUMMARY_DATA_TYPE_T_H_ */
