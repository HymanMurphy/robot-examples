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

#ifndef _OPCUA_BROWSE_RESULT_T_
#define _OPCUA_BROWSE_RESULT_T_


#include "opcua_browse_continuation_point_t.h"
#include "opcua_status_code_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_uint32_t.h"
#include "opcua_reference_description_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief BrowsePath_t
 *
 * This class implements the Browse Result data type
 *
 */
class BrowseResult_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(BrowseResult_t);
private:

  /*****************************************************************************/
  /* @var StatusCode_t statusCode
   * Browse result status code
   */
  StatusCode_t                        statusCode;

  /*****************************************************************************/
  /* @var ByteString_t continuationPoint
   * Browse continuation point
   */
  IntrusivePtr_t<ByteString_t> continuationPoint;

  /*****************************************************************************/
  /* @var ArrayUA_t<ReferenceDescription_t> references
   * References
   */
  ArrayUA_t<ReferenceDescription_t>   references;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_BrowseResult;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BrowseResult_t();

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
  bool operator==(BrowseResult_t const & obj) const;

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
   * @param[in] BrowseResult_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS BrowseResult_t object is greater than RHS BrowseResult_t object
   */
  bool operator>(BrowseResult_t const & obj) const;

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
   * @param[in] const BrowseResult_t& source
   *  Browse Result source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const BrowseResult_t& source);

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
  /** Get the Browse path result status code
   *
   * @return
   * Returns the Browse path result status code
   */
  const StatusCode_t& StatusCode(void) const;

  /*****************************************************************************/
  /** Get the Browse path result status code
   *
   * @return
   * Returns the Browse path result status code
   */
  StatusCode_t& StatusCode(void);

  /*****************************************************************************/
  /** Get the Browse Continuation Point
   *
   * @return
   * Returns the Browse Continuation Point
   */
  IntrusivePtr_t<const ByteString_t> ContinuationPoint(void) const;

  /*****************************************************************************/
  /** Get the Browse Continuation Point
   *
   * @return
   * Returns the Browse Continuation Point
   */
  IntrusivePtr_t<ByteString_t>& ContinuationPoint(void);

  /*****************************************************************************/
  /** Get the References
   *
   * @return
   * Returns the References
   */
  const ArrayUA_t<ReferenceDescription_t>& References(void) const;

  /*****************************************************************************/
  /** Get the References
   *
   * @return
   * Returns the References
   */
  ArrayUA_t<ReferenceDescription_t>& References(void);

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
   * @param[out] BrowseResult_t& result
   * Decoded Browse Result object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowseResult_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BROWSE_RESULT_T_
