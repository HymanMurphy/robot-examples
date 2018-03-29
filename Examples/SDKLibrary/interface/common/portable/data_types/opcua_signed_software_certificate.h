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

#ifndef _OPCUA_SIGNED_SOFTWARE_CERTIFICATE_T_
#define _OPCUA_SIGNED_SOFTWARE_CERTIFICATE_T_

#include "opcua_string_t.h"
#include "opcua_app_description_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief SignedSoftwareCertificate_t
 *
 * This class implements the SignedSoftwareCertificate data type
 *
 */
class SignedSoftwareCertificate_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(SignedSoftwareCertificate_t);
private:

  /*****************************************************************************/
  /* @var ByteString_t certificateData
   *  The certificate data serialized as a ByteString.
   */
  ByteString_t	certificateData;

	/*****************************************************************************/
	/* @var ByteString_t signature
	*  The signature for the certificateData.
	*/
	ByteString_t	signature;


public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_SignedSoftwareCertificate;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
	SignedSoftwareCertificate_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~SignedSoftwareCertificate_t();

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
   * @param[in] const SignedSoftwareCertificate_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the SignedSoftwareCertificate  object assigned
   */
  bool operator==(SignedSoftwareCertificate_t const & obj) const;

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
   * @param[in] SignedSoftwareCertificate_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS SignedSoftwareCertificate_t object is greater than RHS SignedSoftwareCertificate_t object
   */
  bool operator>(SignedSoftwareCertificate_t const & obj) const;

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
   * @param[in] const SignedSoftwareCertificate_t& source
   * Signed Software Certificate source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const SignedSoftwareCertificate_t& source);

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
  /** Get the CertificateData
   *
   * @return
   * Returns the CertificateData
   */
  const ByteString_t& CertificateData(void) const;

  /*****************************************************************************/
  /** Get the CertificateData
   *
   * @return
   * Returns the CertificateData
   */
  ByteString_t& CertificateData(void);

	/*****************************************************************************/
	/** Get the Signature
	*
	* @return
	* Returns the Signature
	*/
	const ByteString_t& Signature(void) const;

	/*****************************************************************************/
	/** Get the Signature
	*
	* @return
	* Returns the Signature
	*/
	ByteString_t& Signature(void);

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
   * @param[out] SignedSoftwareCertificate_t& result
   * Decoded Signed Software Certificate  object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SignedSoftwareCertificate_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_SIGNED_SOFTWARE_CERTIFICATE_T_
