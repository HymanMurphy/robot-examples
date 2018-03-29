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

#ifndef _OPCUA_XV_TYPE_T_H_
#define _OPCUA_XV_TYPE_T_H_

#include "opcua_structure_t.h"
#include "opcua_double_t.h"
#include "opcua_float_t.h"
#include "opcua_iruntime_type_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief XVType_t
 *
 * This class implements the XV Type data type
 *
 */
class XVType_t : public Structure_t
{
private:

  /*****************************************************************************/
  /* @var Double_t  x
   * X
   */
  Double_t  x;

  /*****************************************************************************/
  /* @var Float_t   value
   * value
   */
  Float_t   value;

public:
  UA_DECLARE_RUNTIME_TYPE(XVType_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_XVType;

  virtual ~XVType_t();

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
   * @param[in] const XVType_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the XVType_t object assigned
   */
  bool operator==(XVType_t const & obj) const;

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
   * @param[in] XVType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS XVType_t object is greater than RHS XVType_t object
   */
  bool operator>(XVType_t const & obj) const;

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
   * Base Data Type source to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const XVType_t& source
   * XV Type source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const XVType_t& source);

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
  /** Get the X
   *
   * @return
   * Returns X
   */

  const Double_t& X(void) const;

  /*****************************************************************************/
  /** Get the X
   *
   * @return
   * Returns X
   */
  Double_t& X(void);

  /*****************************************************************************/
  /** Get the value
   *
   * @return
   * Returns value
   */

  const Float_t& Value(void) const;

  /*****************************************************************************/
  /** Get the value
   *
   * @return
   * Returns value
   */
  Float_t& Value(void);

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
   * @param[out] XVType_t& result
   * Decoded XVType_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, XVType_t& result);
};

/** @} */

} //namespace uasdk

#endif

#endif /* _OPCUA_XV_TYPE_T_H_ */
