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

#ifndef _OPCUA_BROWSE_PATH_RESULT_T_
#define _OPCUA_BROWSE_PATH_RESULT_T_

#include "opcua_node_id_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_string_t.h"
#include "opcua_browse_direction_t.h"
#include "opcua_browse_path_target_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_status_code_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief BrowsePathResult_t
 *
 * This class implements the Browse path result data type
 *
 */
class BrowsePathResult_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(BrowsePathResult_t);

private:

  /*****************************************************************************/
  /* @var StatusCode_t statusCode
   * Browse path result status code
   */
  StatusCode_t                    statusCode;

  /*****************************************************************************/
  /* @var ArrayUA_t<BrowsePathTarget_t> targets
   * Array of browse path targets
   */
  ArrayUA_t<BrowsePathTarget_t>   targets;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_BrowsePathResult;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BrowsePathResult_t();

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
  bool operator==(BrowsePathResult_t const & obj) const;

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
   * @param[in] BrowsePathResult_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS BrowsePathResult_t object is greater than RHS BrowsePathResult_t object
   */
  bool operator>(BrowsePathResult_t const & obj) const;

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
   * @param[in] const BrowsePathResult_t& source
   *  Browse Path Result source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const BrowsePathResult_t& source);

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
  /** Get the array of Browse path targets
   *
   * @return
   * Returns the array of Browse path targets
   */
  const ArrayUA_t<BrowsePathTarget_t>& Targets(void) const;

  /*****************************************************************************/
  /** Get the array of Browse path targets
   *
   * @return
   * Returns the array of Browse path targets
   */
  ArrayUA_t<BrowsePathTarget_t>& Targets(void);

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
   * @param[out] BrowsePathResult_t& result
   * Decoded Browse Path Result object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowsePathResult_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BROWSE_PATH_RESULT_T_
