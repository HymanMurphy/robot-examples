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
-----------------------------------------------------------------------------------------------------------------*/

/*****************************************************************************/
/** \file ua_security.h
 *  \brief The OPC-UA Embedded Server SDK Security API Definition.
 *
 */

#ifndef _UA_SECURITY_
#define _UA_SECURITY_

/*****************************************************************************/
/* Include Files
 */
#include "uasdk_c_declarations.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup UASecurityAPI Public interface
 */

/** \addtogroup UASecurityAPI
*@{*/

/*****************************************************************************/
/* Defines Macros Types
 */

/*****************************************************************************/
/** \brief Enumeration of asymmetric cipher types
 *
 */
typedef enum
{
  UA_ASYM_CIPHER_INVALID = 0, /**< Invalid */
  UA_ASYM_CIPHER_RSA_PKCS1_v1_5 = 1, /**< RSA-1_5 */
  UA_ASYM_CIPHER_RSA_OAEP = 2 /**< RSA OAEP (SHA1) */
} UA_Asym_Cipher_t;

/*****************************************************************************/
/** \brief Enumeration of symmetric cipher types
 *
 */
typedef enum
{
  UA_SYM_CIPHER_INVALID = 0,  /**< invalid */
  UA_SYM_CIPHER_AES_128_CBC = 1,  /**< AES 128 CBC */
  UA_SYM_CIPHER_AES_256_CBC = 2   /**< AES 256 CBC */
} UA_Sym_Cipher_t;

/*****************************************************************************/
/** \brief Enumeration of message digest types
 *
 */
typedef enum
{
  UA_DIGEST_INVALID = 0,   /**< Invalid */
  UA_DIGEST_SHA1 = 1,   /**< SHA1 */
  UA_DIGEST_SHA256 = 2  /**< SHA256 */
} UA_Digest_t;

/*****************************************************************************/
/** \brief Bit definitions for a bitmap that allows you to modify the behaviour
 * of the Certificate validation.
 *
 */

/** Option Bit - Accept expired certificates */
#define OB_SUPPRESS_CERTIFICATE_EXPIRED       (1<<0)
/** Option Bit - Do not validate the application hostname */
#define OB_SUPPRESS_HOSTNAME_INVALID          (1<<1)
/** Option Bit - If checking certificate CRLs do not reject
 * a certificate if a CRL for the Issuer cannot be found */
#define OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN (1<<2)
/** Option Bit - Look for CRLs online (not currently supported) */
#define OB_CHECK_REVOCATION_STATUS_ONLINE     (1<<3)
/** Option Bit - Look for CRLs locally (typically in the local filesystem */
#define OB_CHECK_REVOCATION_STATUS_OFFLINE    (1<<4)
/** Option Bit - Do not validate the application URI */
#define OB_SUPPRESS_URI_MISMATCH              (1<<5)

/*****************************************************************************/
/** \brief Certificate Generation Configuration Structure
 *
 */
typedef struct
{
  UA_UTF8_string_t pki_path;          /**< Type of certificate path */
  UA_CertificateType_t type;          /**< Type of certificate to generate */
  UA_CertificateGroup_t group;        /**< Certificate group to add the certificate to */
  uint32_t private_key_bit_length;     /**< Bit length of the certificate private key */
  UA_UTF8_string_t private_key_password;
  UA_DateTime_t start_date;            /**< start date for certificate expiry */
  UA_DateTime_t end_date;              /**< end date for certificate expiry */
  UA_UTF8_string_t application_uri;    /**< Application URI */
  UA_UTF8_string_t* hostnames;         /**< Array of host names */
  uint32_t no_of_hostnames;            /**< Number of host names */
  UA_UTF8_string_t* ip_addresses;      /**< Array of IP Addresses */
  uint32_t no_of_ip_addresses;         /**< Number of IP Addresses */
  UA_UTF8_string_t common_name;        /**< Certificate Common Name */
  UA_UTF8_string_t organisation;       /**< Certificate Organisation */
  UA_UTF8_string_t organisation_unit;  /**< Certificate Organisation Unit */
  UA_UTF8_string_t locality;           /**< Certificate Locality */
  UA_UTF8_string_t state;              /**< Certificate State */
  UA_UTF8_string_t country;            /**< Certificate Country */
} UA_Certificate_Generation_Parameters_t;

/*****************************************************************************/
/** \brief Certificate Validation Configuration Structure
 *
 */
typedef struct
{
  uintptr_t trusted_stack_handle;
  uintptr_t trusted_crls_handle;
  uintptr_t issuer_stack_handle;
  uintptr_t issuer_crls_handle;
  UA_CertificateType_t type;
  UA_CertificateGroup_t group;
  SecurityPolicy_t policy;
  UA_Byte_string_t certificate_chain;
  UA_UTF8_string_t hostname;
  UA_UTF8_string_t uri;
  uint32_t validation_option_bits;
  bool_t trust_all_clients_when_the_trust_list_is_empty;
  bool_t do_not_save_rejected_certificates;
  bool_t validateExtensionsServer;
  bool_t validateExtensionsClient;
} UA_Certificate_Validation_Parameters_t;

/*****************************************************************************/
/** Initialize the security library
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * The certificate path
 *
 * @return
 * Status of the operation
 *
 */

UA_Status_t UASecurity_library_initialise(const UA_UTF8_string_t* pki_path);

/*****************************************************************************/
/** Terminate security library
 *
 */
void UASecurity_library_terminate(void);

/*****************************************************************************/
/** Security Random Bytes
 *
 * @param[in] const UA_UTF8_string_t* buf
 * Buffer
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_rand_bytes(UA_Byte_string_t* buf);

/*****************************************************************************/
/** Security Random pseudo Bytes
 *
 * @param[in] const UA_UTF8_string_t* buf
 * Buffer
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_rand_pseudo_bytes(UA_Byte_string_t* buf);

/*****************************************************************************/
/** Perform the Symmetric encryption
 *
 * @param[in] UA_Sym_Cipher_t type
 * Symmetric cipher type
 *
 * @param[in] const UA_UTF8_string_t* iv
 * Initialization vector
 *
 * @param[in] const UA_UTF8_string_t* key
 * Key
 *
 * @param[in] const UA_UTF8_string_t* plaintext
 * Plain text
 *
 * @param[out] UA_UTF8_string_t* ciphertext
 * Cipher text
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_symmetric_encrypt(
    UA_Sym_Cipher_t type,
    const UA_Byte_string_t* iv,
    const UA_Byte_string_t* key,
    const UA_Byte_string_t* plaintext,
    UA_Byte_string_t* ciphertext);

/*****************************************************************************/
/** Perform the Symmetric decryption
 *
 * @param[in] UA_Sym_Cipher_t type
 * Symmetric cipher type
 *
 * @param[in] const UA_UTF8_string_t* iv
 * Initialization vector
 *
 * @param[in] const UA_UTF8_string_t* key
 * Key
 *
 * @param[in] const UA_UTF8_string_t* ciphertext
 * Cipher text
 *
 * @param[out] UA_UTF8_string_t* plaintext
 * Plain text
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_symmetric_decrypt(
    UA_Sym_Cipher_t type,
    const UA_Byte_string_t* iv,
    const UA_Byte_string_t* key,
    const UA_Byte_string_t* ciphertext,
    UA_Byte_string_t* plaintext);

/*****************************************************************************/
/** Perform the Digest access authentication
 *
 * @param[in] UA_Digest_t type
 * Digest type
 *
 * @param[in] const UA_Byte_string_t* data
 * data
 *
 * @param[in] UA_Byte_string_t* hash
 * hash
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_digest(
    UA_Digest_t type,
    const UA_Byte_string_t* data,
    UA_Byte_string_t* hash);

/*****************************************************************************/
/** Hash based message authentication code
 *
 * @param[in] UA_Digest_t type
 * Digest type
 *
 * @param[in] const UA_Byte_string_t* key
 * key
 *
 * @param[in] const UA_Byte_string_t* data
 * data
 *
 * @param[in] UA_Byte_string_t* hash
 * hash
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_hmac(
    UA_Digest_t type,
    const UA_Byte_string_t* key,
    const UA_Byte_string_t* data,
    UA_Byte_string_t* hash);

/*****************************************************************************/
/** Secured Hash algorithm
 *
 * @param[in] UA_Digest_t type
 * Digest type
 *
 * @param[in] const UA_Byte_string_t* secret
 * key
 *
 * @param[in] const UA_Byte_string_t* seed
 * data
 *
 * @param[out] UA_Byte_string_t* output
 * hash
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_p_sha(
    UA_Digest_t type,
    const UA_Byte_string_t* secret,
    const UA_Byte_string_t* seed,
    UA_Byte_string_t* output);

/*****************************************************************************/
/** Asymmetric encrypt
 *
 * @param[in] UA_Asym_Cipher_t type
 * Asymmetric cipher type
 *
 * @param[in] const UA_Byte_string_t* receiver_chain
 * Receiver chain
 *
 * @param[in] const UA_Byte_string_t* plaintext
 * Plain Text
 *
 * @param[out] UA_Byte_string_t* ciphertext
 * Cipher Text
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_asymmetric_encrypt(
    UA_Asym_Cipher_t type,
    const UA_Byte_string_t* receiver_chain,
    const UA_Byte_string_t* plaintext,
    UA_Byte_string_t* ciphertext);

/*****************************************************************************/
/** Perform the Asymmetric decryption
 *
 * @param[in] UA_Sym_Cipher_t type
 * Asymmetric cipher type
 *
 * @param[in] uintptr_t receiver_private_key_handle
 * Receiver private key handle
 *
 * @param[in] const UA_Byte_string_t* ciphertext
 * Cipher text
 *
 * @param[out] UA_Byte_string_t* plaintext
 * Plain text
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_asymmetric_decrypt(
    UA_Asym_Cipher_t type,
    uintptr_t receiver_private_key_handle,
    const UA_Byte_string_t* ciphertext,
    UA_Byte_string_t* plaintext);

/*****************************************************************************/
/** Perform the Symmetric encryption
 *
 * @param[in] UA_Sym_Cipher_t type
 * Asymmetric cipher type
 *
 * @param[in] uintptr_t receiver_private_key_handle
 * Receiver private key handle
 *
 * @param[in] const UA_Byte_string_t* data
 * Data to be signed
 *
 * @param[out] const UA_Byte_string_t* signature
 * The signature
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_asymmetric_sign(
    UA_Digest_t type,
    uintptr_t signee_private_key_handle,
    const UA_Byte_string_t* data,
    UA_Byte_string_t* signature);

/*****************************************************************************/
/** Perform the Asymmetric verify
 *
 * @param[in] UA_Digest_t type
 * Asymmetric cipher type
 *
 * @param[in] const UA_Byte_string_t* sender_chain
 * Receiver private key handle
 *
 * @param[in] const UA_Byte_string_t* data
 * Data to be verified
 *
 * @param[in] const UA_Byte_string_t* signature
 * The signature
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_asymmetric_verify(
    UA_Digest_t type,
    const UA_Byte_string_t* sender_chain,
    const UA_Byte_string_t* data,
    const UA_Byte_string_t* signature);

/*****************************************************************************/
/** validate the certificate
 *
 * @param[in] const UA_Certificate_Validation_Parameters_t* parameters
 * Pointer to the certificate validation parameters
 *
 * @param[in] const UA_Byte_string_t* sender_chain
 * Sender chain
 *
 * @param[in] bool_t validate_trust
 * Validate trust
 *
 * @param[out] int32_t* rejected_certificate_length
 * Rejected certificate length
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_certificate_validate(
    const UA_Certificate_Validation_Parameters_t* parameters,
    bool_t validate_trust,
    int32_t* rejected_certificate_length);

/*****************************************************************************/
/** validate the certificate
 *
 * @param[in] const UA_Certificate_Validation_Parameters_t* parameters
 * Pointer to the certificate validation parameters
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_certificate_validation_parameters_init(
    UA_Certificate_Validation_Parameters_t* parameters);

/*****************************************************************************/
/** Save certificate to rejected folder
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] const UA_Byte_string_t* certificate
 * The Certificate
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_save_cert_to_rejected_folder(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    const UA_Byte_string_t* certificate);

/*****************************************************************************/
/** Validate the URI
 *
 * @param[in] const UA_Byte_string_t* certificate
 * Certificate
 *
 * @param[in] const UA_UTF8_string_t* uri
 * URI
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_validate_uri(
    const UA_Byte_string_t* certificate,
    const UA_UTF8_string_t* uri);

/*****************************************************************************/
/** Validate the Hostname
*
* @param[in] const UA_Byte_string_t* certificate
* Certificate
*
* @param[in] const UA_UTF8_string_t* hostname
* Hostname
*
* @return
* Status of the operation
*/
UA_Status_t UASecurity_validate_hostname(
  const UA_Byte_string_t* certificate,
  const UA_UTF8_string_t* hostname);

/*****************************************************************************/
/** get Certificate key size
 *
 * @param[in] uintptr_t certificate_handle
 * Certificate handle
 *
 * @param[out] uint32_t* key_size_in_bytes
 * Key size in bytes
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_certificate_key_size(
    uintptr_t certificate_handle,
    uint32_t* key_size_in_bytes);

/*****************************************************************************/
/** Get Der Certificate key size
 *
 * @param[in] const UA_Byte_string_t* certificate
 * Certificate
 *
 * @param[out] uint32_t* key_size_in_bytes
 * Key size in bytes
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_der_certificate_key_size(
    const UA_Byte_string_t* certificate,
    uint32_t* key_size_in_bytes);

/*****************************************************************************/
/** Get certificate maximum plain text size
 *
 * @param[in] UA_Asym_Cipher_t type
 * Asymmetric cipher type
 *
 * @param[in] uintptr_t certificate_handle
 * Certificate handle
 *
 * @param[out] uint32_t* max_plaintext_size
 * Maximum plain text size
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_certificate_max_plaintext_size(
    UA_Asym_Cipher_t type,
    uintptr_t certificate_handle,
    uint32_t* max_plaintext_size);

/*****************************************************************************/
/** Get DER certificate maximum plain text size
 *
 * @param[in] UA_Asym_Cipher_t type
 * Asymmetric cipher type
 *
 * @param[in] const UA_Byte_string_t* certificate
 * Certificate
 *
 * @param[out] uint32_t* max_plaintext_size
 * Maximum plain text size
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_der_certificate_max_plaintext_size(
    UA_Asym_Cipher_t type,
    const UA_Byte_string_t* certificate,
    uint32_t* max_plaintext_size);

/*****************************************************************************/
/** Get Certificate to DER
 *
 * @param[in] uintptr_t certificate_handle
 * Asymmetric cipher type
 *
 * @param[out] UA_Byte_string_t** certificate_der
 * Certificate DER
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_certificate_to_der(
    uintptr_t certificate_handle,
    UA_Byte_string_t** certificate_der);

/*****************************************************************************/
/** Get DER to Certificate
 *
 * @param[in] UA_Byte_string_t* certificate_der
 * Certificate DER
 *
 * @param[out] uintptr_t* certificate_handle
 * Certificate handle
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_der_to_certificate(
    UA_Byte_string_t* certificate_der,
    uintptr_t* certificate_handle);

/*****************************************************************************/
/** Get own certificate
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateType_t type
 * Certificate type
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] uintptr_t* own_certificate_handle
 * Own Certificate handle
 *
 * @param[out] UA_Byte_string_t** own_certificate_der
 * Own Certificate DER
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_own_certificate(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    uintptr_t* own_certificate_handle,
    UA_Byte_string_t** own_certificate_der);

/*****************************************************************************/
/** Get own certificate
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateType_t type
 * Certificate type
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[out] uintptr_t* own_certificate_handle
 * Own Certificate handle
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_own_certificate_handle(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    uintptr_t* own_certificate_handle);

/*****************************************************************************/
/** Get own certificate
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateType_t type
 * Certificate type
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[out] UA_Byte_string_t** own_certificate_der
 * Own Certificate DER
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_own_certificate_der(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    UA_Byte_string_t** own_certificate_der);

/*****************************************************************************/
/** Get own certificate private key handle
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateType_t type
 * Certificate type
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] UA_UTF8_string_t* private_key_password
 * private key password
 *
 * @param[out] uintptr_t* private_key_handle
 * private key handle
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_own_certificate_private_key_handle(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    UA_UTF8_string_t* private_key_password,
    uintptr_t* private_key_handle);

/*****************************************************************************/
/** Get private key handle
*
* @param[in] const UA_Byte_string_t* pkcs8_pem_private_key
* PKCS8 PEM encoded private key
*
*
* @param[in] UA_UTF8_string_t* private_key_password
* private key password
*
* @param[out] uintptr_t* private_key_handle
* private key handle
*
* @return
* Status of the operation
*/
UA_Status_t UASecurity_get_private_key_handle(
  const UA_Byte_string_t* pkcs8_pem_private_key,
  UA_UTF8_string_t* private_key_password,
  uintptr_t* private_key_handle);

/*****************************************************************************/
/** Get certificate stacks
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] bool_t is_trusted_stack
 * Trusted stack indicator
 *
 * @param[out] uintptr_t* stack_handle
 * Stack handle
 *
 * @param[out] uintptr_t* crls_handle
 * Certificate Revocation List
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_stacks(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_stack,
    uintptr_t* stack_handle,
    uintptr_t* crls_handle);

/*****************************************************************************/
/** Get the trust list
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] bool_t is_trusted_list
 * Trusted stack indicator
 *
 * @param[out] UA_Byte_string_t** certificates_der
 * the certificate DER
 *
 * @param[out] uint32_t* no_of_certificates
 * Number of certificate
 *
 * @param[out] UA_Byte_string_t** crls_der
 * Certificate Revocation List DER
 *
 * @param[out] uint32_t* no_of_crls
 * Number of Certificate Revocation List
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_trust_list(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_list,
    UA_Byte_string_t** certificates_der,
    uint32_t* no_of_certificates,
    UA_Byte_string_t** crls_der,
    uint32_t* no_of_crls);

/*****************************************************************************/
/** Get the rejected list
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[out] UA_Byte_string_t** rejected_list_der
 * the certificate DER
 *
 * @param[out] uint32_t* no_of_certificates
 * Number of certificate
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_get_rejected_list(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    UA_Byte_string_t** rejected_list_der,
    uint32_t* no_of_certificates);


/*****************************************************************************/
/** Add certificate to trust list
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] bool_t is_trusted_certificate
 * the certificate DER
 *
 * @param[in] const UA_Byte_string_t* certificate_der
 * certificate DER
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_add_certificate_to_trust_list(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_certificate,
    const UA_Byte_string_t* certificate_der);

/*****************************************************************************/
/** Remove certificate from the trust list
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] bool_t is_trusted_certificate
 * Truster is certificate or not
 *
 * @param[in] const UA_Byte_string_t* certificate_thumbprint
 * certificate thumb print
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_remove_certificate_from_trust_list(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_certificate,
    const UA_Byte_string_t* certificate_thumbprint);

/*****************************************************************************/
/** Update certificate
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @param[in] UA_CertificateType_t type
 * Certificate type
 *
 * @param[in] UA_CertificateGroup_t group
 * Certificate group
 *
 * @param[in] const UA_Byte_string_t* certificate_der
 * Certificate DER
 *
 * @param[in] const UA_Byte_string_t* private_key_pem
 * Private key PEM
 *
 * @param[in] const UA_Byte_string_t* issuer_certificates
 * Issuer Certificate
 *
 * @param[in] uint32_t no_of_issuer_certificates
 * Number of issuer certificates
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_update_certificate(
    const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    const UA_Byte_string_t* certificate_der,
    const UA_Byte_string_t* private_key_pem,
    const UA_Byte_string_t* issuer_certificates,
    uint32_t no_of_issuer_certificates);


/*****************************************************************************/
/** Create certificate signing request
 *
 * @param[in] UA_Certificate_Generation_Parameters_t* parameters
 * Certificate generation parameters
 *
 * @param[in] bool_t regeneratePrivateKey
 * Regenerate private key
 *
 * @param[in] UA_Byte_string_t** certificate_signing_request_der
 *  certificate signing request der
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_create_certificate_signing_request(
    UA_Certificate_Generation_Parameters_t* parameters,
    bool_t regeneratePrivateKey,
    UA_Byte_string_t** certificate_signing_request_der);

/*****************************************************************************/
/** Create certificate signing request
 *
 * @param[in] uintptr_t certificate_handle
 * Certificate handle
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_free_certificate_handle(
    uintptr_t certificate_handle);

/*****************************************************************************/
/** Free the certificate DER
 *
 * @param[in] UA_Byte_string_t* certificate_der
 * Certificate DER
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_free_certificate_der(
    UA_Byte_string_t* certificate_der);

/*****************************************************************************/
/** Free private key handle
 *
 * @param[in] uintptr_t private_key_handle
 * private key handle
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_free_private_key_handle(
    uintptr_t private_key_handle);

/*****************************************************************************/
/** Create certificate signing request
 *
 * @param[in] uintptr_t stack_handle
 * stack handle
 *
 * @param[in] uintptr_t crls_handle
 * CRLS handle
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_free_stacks(
    uintptr_t stack_handle,
    uintptr_t crls_handle);

/*****************************************************************************/
/** Free the byte string
 *
 * @param[in] UA_Byte_string_t* bytestrings
 * pointer to the Byte string to free
 *
 * @param[in] uint32_t no_of_elements
 * Number of element
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_free_bytestrings(
    UA_Byte_string_t* bytestrings,
    uint32_t no_of_elements);

/*****************************************************************************/
/** Create certificate certificate
 *
 * @param[in] const UA_Certificate_Generation_Parameters_t* parameters
 * Certificate generation parameter
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_create_self_signed_certificate(
    const UA_Certificate_Generation_Parameters_t* parameters);

/*****************************************************************************/
/** Initialize certificate generation parameters
 *
 * @param[in] UA_Certificate_Generation_Parameters_t* parameters
 * Pointer to the certificat generation parameters
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_certificate_generation_parameters_init(
    UA_Certificate_Generation_Parameters_t* parameters);

/*****************************************************************************/
/** Create directory stores
 *
 * @param[in] const UA_UTF8_string_t* pki_path
 * Certificate path
 *
 * @return
 * Status of the operation
 */
UA_Status_t UASecurity_create_directory_stores(const UA_UTF8_string_t* pki_path);

/*****************************************************************************/
/** Get certificate expiry date
*
* @param[in] const UA_Byte_string_t* certDer
* Certificate
*
* @return
* expiry date of the input certificate
*/
int64_t UASecurity_get_certificate_expiry_date(const UA_Byte_string_t* certDer);
/*@}*/

#ifdef __cplusplus
}
#endif

/*@}*/

#endif //_UA_SECURITY_
