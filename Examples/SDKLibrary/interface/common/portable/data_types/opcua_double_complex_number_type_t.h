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

#ifndef _OPCUA_DOUBLE_COMPLEX_NUMBER_TYPE_T_H_
#define _OPCUA_DOUBLE_COMPLEX_NUMBER_TYPE_T_H_

#include "opcua_structure_t.h"
#include "opcua_double_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ChannelSecurityToken_t
 *
 * This class implements the double complex number Token data type
 *
 */
class DoubleComplexNumberType_t : public Structure_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(DoubleComplexNumberType_t);
private:

  /*****************************************************************************/
  /* @var Double_t   real
   * Complex number real part
   */
  Double_t  real;

  /*****************************************************************************/
  /* @var Float_t   imaginary
   * Complex number imaginary part
   */
  Double_t  imaginary;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_DoubleComplexNumberType;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~DoubleComplexNumberType_t();

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
   * @param[in] const DoubleComplexNumberType_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the DoubleComplexNumberType_t object assigned
   */
  bool operator==(DoubleComplexNumberType_t const & obj) const;

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
   * @param[in] DoubleComplexNumberType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS DoubleComplexNumberType_t object is
   * greater than RHS DoubleComplexNumberType_t object
   */
  bool operator>(DoubleComplexNumberType_t const & obj) const;

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
   * @param[in] const DoubleComplexNumberType_t& source
   *  Double Complex Number source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const DoubleComplexNumberType_t& source);

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
  /** Get the real
   *
   * @return
   * Returns the real
   */
  const Double_t& Real(void) const;

  /*****************************************************************************/
  /** Get the real part of a complex number
   *
   * @return
   * Returns the real part of a complex number
   */
  Double_t& Real(void);

  /*****************************************************************************/
  /** Get the imaginary part of a complex number
   *
   * @return
   * Returns the imaginary part of a complex number
   */
  const Double_t& Imaginary(void) const;

  /*****************************************************************************/
  /** Get the imaginary part of a complex number
   *
   * @return
   * Returns the imaginary part of a complex number
   */
  Double_t& Imaginary(void);

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
   * @param[out] ComplexNumberType_t& result
   * Decoded Complex Number Type object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DoubleComplexNumberType_t& result);
};

/** @} */

} //namespace uasdk

#endif

#endif /* _OPCUA_DOUBLE_COMPLEX_NUMBER_TYPE_T_H_ */
