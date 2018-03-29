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

#ifndef _OPCUA_VIEW_DESCRIPTION_T_
#define _OPCUA_VIEW_DESCRIPTION_T_

#include "opcua_structure_t.h"
#include "opcua_node_id_t.h"
#include "opcua_date_time_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ArrayUA_t
 *
 * This class implements the ViewDescription_t data type
 *
 */
class ViewDescription_t : public Structure_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> viewId
   * An intrusive reference counting Boost-style smart pointer to the starting view id
   */
  IntrusivePtr_t<NodeId_t>  viewId;

  /*****************************************************************************/
  /* @var UtcTime_t timestamp
   * Time Stamp
   */
  UtcTime_t              timestamp;

  /*****************************************************************************/
  /* @var UInt32_t viewVersion
   * View Version
   */
  UInt32_t                  viewVersion;

public:
  UA_DECLARE_RUNTIME_TYPE(ViewDescription_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ViewDescription;


  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ViewDescription_t();

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
  bool operator==(ViewDescription_t const & obj) const;

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
   * @param[in] ViewDescription_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ViewDescription_t object is greater than RHS ViewDescription_t object
   */
  bool operator>(ViewDescription_t const & obj) const;

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
   * @param[in] const ViewDescription_t& source
   *  View Description source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ViewDescription_t& source);

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
  /** Get the View ID
   *
   * @return
   * Returns the View ID
   */
  IntrusivePtr_t<const NodeId_t> ViewId(void) const;

  /*****************************************************************************/
  /** Get the View ID
   *
   * @return
   * Returns the View ID
   */
  IntrusivePtr_t<NodeId_t>& ViewId(void);

  /*****************************************************************************/
  /** Get the Time Stamp
   *
   * @return
   * Returns the Time Stamp
   */
  const UtcTime_t& Timestamp(void) const;

  /*****************************************************************************/
  /** Get the Time Stamp
   *
   * @return
   * Returns the Time Stamp
   */
  UtcTime_t& Timestamp(void);

  /*****************************************************************************/
  /** Get the View Version
   *
   * @return
   * Returns the View Version
   */
  const UInt32_t&  ViewVersion(void) const;

  /*****************************************************************************/
  /** Get the View Version
   *
   * @return
   * Returns the View Version
   */
  UInt32_t&  ViewVersion(void);

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
   * @param[out] ViewDescription_t& result
   * Decoded View Description Path object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ViewDescription_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_VIEW_DESCRIPTION_T_
