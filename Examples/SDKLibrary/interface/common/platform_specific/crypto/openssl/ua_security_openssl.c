/* ----------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
---------------------------------------------------------------------------------------- */

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

#include "uasdk_default_build_config.h"

#if ((UASDK_INCLUDE_SECURITY > 0) && (UASDK_USE_OPENSSL > 0))

#include "ua_security.h"
#include "ua_system_calls.h"
#include "opcua_status_codes.h"
#include "common_utilities_t.h"

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

#ifdef _MSC_VER
#include <stdarg.h>
#include <direct.h>

#ifndef S_ISDIR
#define S_ISDIR(ST_MODE) (((ST_MODE)& _S_IFMT) == _S_IFDIR)
#endif

#define mode_t int

#define snprintf c99_snprintf

static int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
	int count = -1;

	if (size != 0)
		count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
	if (count == -1)
		count = _vscprintf(format, ap);

	return count;
}

static int c99_snprintf(char* str, size_t size, const char* format, ...)
{
	int count;
	va_list ap;

	va_start(ap, format);
	count = c99_vsnprintf(str, size, format, ap);
	va_end(ap);

	return count;
}

#define MKDIR(a, b) _mkdir(a)
#define fileno _fileno
#define S_IRWXU 0

#elif defined __linux
#include <sys/types.h>
#define MKDIR(a, b) mkdir(a, b)
#else
#error This module is implemented for Windows and Linux only
#endif

#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/rsa.h>
#include <openssl/objects.h>
#include <openssl/obj_mac.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/asn1.h>

#ifndef UA_VALGRIND
#define VALGRIND_MAKE_MEM_DEFINED(a, b)
#else
#include "memcheck.h"
#endif

#define UA_SECURITY_PATH_PKI "pki"
#define UA_SECURITY_PATH_DEFAULT_APPLICATION_GROUP "DefaultApplicationGroup"
//#define UA_SECURITY_PATH_DEFAULT_HTTPS_GROUP "DefaultHttpsGroup"              /* HTTPS is not supported yet! */
#define UA_SECURITY_PATH_DEFAULT_USER_TOKEN_GROUP "DefaultUserTokenGroup"

#define UA_SECURITY_PATH_OWN_STORE "own"
#define UA_SECURITY_PATH_TRUSTED_STORE "trusted"
#define UA_SECURITY_PATH_ISSUER_STORE "issuer"
#define UA_SECURITY_PATH_REJECTED_STORE "rejected"

#define UA_SECURITY_PATH_CERTS "certs"
#define UA_SECURITY_PATH_PRIVATE "private"
#define UA_SECURITY_PATH_CRL "crl"

#define UA_SECURITY_FILENAME_CERT_RSA_MIN "application_rsa_min.der"
#define UA_SECURITY_FILENAME_CERT_RSA_SHA256 "application_rsa_sha256.der"
#define UA_SECURITY_FILENAME_KEY_RSA_MIN "application_rsa_min_key.pem"
#define UA_SECURITY_FILENAME_KEY_RSA_SHA256 "application_rsa_sha256_key.pem"

#define MAX_STRING_LENGTH 256

#define MAX_PATH_LENGTH 200
#define MAX_PASSWORD_LENGTH 20

#define SHA1_HASH_LENGTH 20
#define SHA1_STRING_LENGTH 41
#define SHA1_OID_BYTESTRING_LENGTH 15

#define SHA1_LENGTH  SHA1_HASH_LENGTH
#define SHA256_LENGTH  32
#define MAX_DIGEST_LENGTH  SHA256_LENGTH
#define SUBJECT_ALT_NAME_MAX_LEN 500


const uint8_t SHA1_OID_BYTESTRING[SHA1_OID_BYTESTRING_LENGTH] =
    { 0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2B, 0x0E, 0x03, 0x02, 0x1A, 0x05, 0x00, 0x04, 0x14 };

#define SHA256_OID_BYTESTRING_LENGTH 19

const uint8_t SHA256_OID_BYTESTRING[SHA256_OID_BYTESTRING_LENGTH] =
    { 0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20 };


typedef enum
{
  DIR_CERTS = 0,
  DIR_CRL = 1,
  DIR_PRIVATE = 2
} Directory_t;

typedef enum
{
  DIR_TYPE_OWN = 0,
  DIR_TYPE_TRUSTED = 1,
  DIR_TYPE_ISSUER = 2,
  DIR_TYPE_REJECTED = 3
} DirectoryType_t;

static int32_t ua_strnlen(const char* str, int32_t max_len)
{
  const void* terminator = UASDK_memchr( str, '\0', max_len);
  if (terminator == 0)
  {
    return max_len;
  }
  else
  {
    return (uintptr_t)terminator - (uintptr_t)str;
  }
}

static STACK_OF(X509)* trusted_stack = 0;
static bool_t is_trusted = FALSE;
static uint32_t validation_option = 0;

#if (UASDK_MULTITHREADED > 0)
#include <pthread.h>

static pthread_mutex_t *lock_cs = 0;
static long *lock_count = 0;

void pthreads_locking_callback(int mode, int type, char *file, int line)
{
  if (mode & CRYPTO_LOCK)
  {
    pthread_mutex_lock(&(lock_cs[type]));
    lock_count[type]++;
  }
  else
  {
    pthread_mutex_unlock(&(lock_cs[type]));
  }
}

unsigned long pthreads_thread_id(void)
{
  unsigned long ret;

  ret=(unsigned long)pthread_self();
  return(ret);
}
#endif  //(UASDK_MULTITHREADED > 0)

UA_Status_t CopyUtf8StringToNullTerminatedString(const UA_UTF8_string_t* source, unsigned char* destination, uint32_t maxLength)
{
  if ((source == 0) || (source->length <= 0) || (source->data == 0) || (source->length >= (int32_t)maxLength))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UASDK_memcpy(destination, source->data, source->length);
  destination[source->length] = '\0';
  return OpcUa_Good;
}

static bool_t is_application_cert(UA_CertificateGroup_t group)
{
  return (group == UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP);
}

//static const char* get_validation_errstr(long e)
//{
//  switch ((int) e)
//  {
//    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
//      return "ERR_UNABLE_TO_GET_ISSUER_CERT";
//    case X509_V_ERR_UNABLE_TO_GET_CRL:
//      return "ERR_UNABLE_TO_GET_CRL";
//    case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
//      return "ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE";
//    case X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
//      return "ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE";
//    case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
//      return "ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY";
//    case X509_V_ERR_CERT_SIGNATURE_FAILURE:
//      return "ERR_CERT_SIGNATURE_FAILURE";
//    case X509_V_ERR_CRL_SIGNATURE_FAILURE:
//      return "ERR_CRL_SIGNATURE_FAILURE";
//    case X509_V_ERR_CERT_NOT_YET_VALID:
//      return "ERR_CERT_NOT_YET_VALID";
//    case X509_V_ERR_CERT_HAS_EXPIRED:
//      return "ERR_CERT_HAS_EXPIRED";
//    case X509_V_ERR_CRL_NOT_YET_VALID:
//      return "ERR_CRL_NOT_YET_VALID";
//    case X509_V_ERR_CRL_HAS_EXPIRED:
//      return "ERR_CRL_HAS_EXPIRED";
//    case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
//      return "ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD";
//    case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
//      return "ERR_ERROR_IN_CERT_NOT_AFTER_FIELD";
//    case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
//      return "ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD";
//    case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
//      return "ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD";
//    case X509_V_ERR_OUT_OF_MEM:
//      return "ERR_OUT_OF_MEM";
//    case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
//      return "ERR_DEPTH_ZERO_SELF_SIGNED_CERT";
//    case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
//      return "ERR_SELF_SIGNED_CERT_IN_CHAIN";
//    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
//      return "ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY";
//    case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
//      return "ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE";
//    case X509_V_ERR_CERT_CHAIN_TOO_LONG:
//      return "ERR_CERT_CHAIN_TOO_LONG";
//    case X509_V_ERR_CERT_REVOKED:
//      return "ERR_CERT_REVOKED";
//    case X509_V_ERR_INVALID_CA:
//      return "ERR_INVALID_CA";
//    case X509_V_ERR_PATH_LENGTH_EXCEEDED:
//      return "ERR_PATH_LENGTH_EXCEEDED";
//    case X509_V_ERR_INVALID_PURPOSE:
//      return "ERR_INVALID_PURPOSE";
//    case X509_V_ERR_CERT_UNTRUSTED:
//      return "ERR_CERT_UNTRUSTED";
//    case X509_V_ERR_CERT_REJECTED:
//      return "ERR_CERT_REJECTED";
//    case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
//      return "ERR_SUBJECT_ISSUER_MISMATCH";
//    case X509_V_ERR_AKID_SKID_MISMATCH:
//      return "ERR_AKID_SKID_MISMATCH";
//    case X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH:
//      return "ERR_AKID_ISSUER_SERIAL_MISMATCH";
//    case X509_V_ERR_KEYUSAGE_NO_CERTSIGN:
//      return "ERR_KEYUSAGE_NO_CERTSIGN";
//    case X509_V_ERR_INVALID_EXTENSION:
//      return "ERR_INVALID_EXTENSION";
//    case X509_V_ERR_INVALID_POLICY_EXTENSION:
//      return "ERR_INVALID_POLICY_EXTENSION";
//    case X509_V_ERR_NO_EXPLICIT_POLICY:
//      return "ERR_NO_EXPLICIT_POLICY";
//    case X509_V_ERR_APPLICATION_VERIFICATION:
//      return "ERR_APPLICATION_VERIFICATION";
//    default:
//      return "ERR_UNKNOWN";
//  }
//}

static UA_Status_t get_validation_errcode(long e)
{
  UA_Status_t status = OpcUa_Good;

  switch ((int) e)
  {
  case X509_V_ERR_CERT_HAS_EXPIRED:
  case X509_V_ERR_CERT_NOT_YET_VALID:
  case X509_V_ERR_CRL_NOT_YET_VALID:
  case X509_V_ERR_CRL_HAS_EXPIRED:
  case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
  case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
  case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
  case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
    status = OpcUa_BadCertificateTimeInvalid;
    break;

  case X509_V_ERR_CERT_REVOKED:
    status = OpcUa_BadCertificateRevoked;
    break;

  case X509_V_ERR_UNABLE_TO_GET_CRL:
    status = OpcUa_BadCertificateRevocationUnknown;
    break;

  case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
  case X509_V_ERR_CERT_UNTRUSTED:
  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
  case X509_V_ERR_CERT_SIGNATURE_FAILURE:
  default:
    status = OpcUa_BadSecurityChecksFailed;
    break;
  }
  return status;
}

static bool_t save_to_rejected_folder(long e)
{
  switch ((int) e)
  {
  case X509_V_ERR_CERT_HAS_EXPIRED:
  case X509_V_ERR_CERT_NOT_YET_VALID:
  case X509_V_ERR_CRL_NOT_YET_VALID:
  case X509_V_ERR_CRL_HAS_EXPIRED:
  case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
  case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
  case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
  case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
    return TRUE;

  case X509_V_ERR_UNABLE_TO_GET_CRL:
    return TRUE;

  case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
  case X509_V_ERR_CERT_UNTRUSTED:
  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
  case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
  case X509_V_ERR_CERT_SIGNATURE_FAILURE:
    return TRUE;

  case X509_V_OK:
    return TRUE;

  default:
    return FALSE;
  }
  return FALSE;
}

static bool_t is_self_signed(X509* cert)
{
  if (X509_check_issued(cert, cert) == X509_V_OK)
  {
    return TRUE;
  }
  return FALSE;
}

static bool_t suppress_error(long e)
{
  switch ((int) e)
  {
  case X509_V_ERR_CERT_HAS_EXPIRED:
  case X509_V_ERR_CERT_NOT_YET_VALID:
  case X509_V_ERR_CRL_NOT_YET_VALID:
  case X509_V_ERR_CRL_HAS_EXPIRED:
  case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
  case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
  case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
  case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
  {
    if (validation_option & OB_SUPPRESS_CERTIFICATE_EXPIRED)
    {
      return TRUE;
    }
  }
    break;

  case X509_V_ERR_UNABLE_TO_GET_CRL:
  {
    if (validation_option & OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN)
    {
      return TRUE;
    }
  }
    break;

  default:
    return FALSE;
  }
  return FALSE;
}

static UA_Status_t get_directorypath(UA_CertificateGroup_t group, DirectoryType_t directoryType, Directory_t directory, char* dirpath)
{
  const char* pki = UA_SECURITY_PATH_PKI;
  const char* stores = 0;
  const char* store = 0;
  const char* dir = 0;
  int length = 0;

  switch (group)
  {
    case UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP:
      stores = UA_SECURITY_PATH_DEFAULT_APPLICATION_GROUP;
      break;

      /* HTTPS is not supported yet! */
//    case UA_CERTIFICATE_GROUP_DEFAULT_HTTPS_GROUP:
//      stores = UA_SECURITY_PATH_DEFAULT_HTTPS_GROUP;
//      break;

    case UA_CERTIFICATE_GROUP_DEFAULT_USER_GROUP:
      stores = UA_SECURITY_PATH_DEFAULT_USER_TOKEN_GROUP;
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch(directoryType)
  {
    case DIR_TYPE_OWN:
      store = UA_SECURITY_PATH_OWN_STORE;
      break;

    case DIR_TYPE_TRUSTED:
      store = UA_SECURITY_PATH_TRUSTED_STORE;
      break;

    case DIR_TYPE_ISSUER:
      store = UA_SECURITY_PATH_ISSUER_STORE;
      break;

    case DIR_TYPE_REJECTED:
      store = UA_SECURITY_PATH_REJECTED_STORE;
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch (directory)
  {
    case DIR_CERTS:
      dir = UA_SECURITY_PATH_CERTS;
      break;

    case DIR_CRL:
      dir = UA_SECURITY_PATH_CRL;
      break;

    case DIR_PRIVATE:
      dir = UA_SECURITY_PATH_PRIVATE;
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  length = snprintf(dirpath, MAX_PATH_LENGTH - 1, "%s/%s/%s/%s", pki, stores, store, dir);

  if ((length < 0) || (length >= MAX_PATH_LENGTH))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  return OpcUa_Good;
}

static const char* get_filepath(UA_CertificateGroup_t group, DirectoryType_t directoryType, Directory_t directory, const char* filename)
{
  static char filepath[MAX_PATH_LENGTH];
  char dirpath[MAX_PATH_LENGTH];
  int length = 0;
  UA_Status_t status = OpcUa_Good;

  status = get_directorypath(group, directoryType, directory, dirpath);
  if(status != OpcUa_Good)
  {
    return 0;
  }

  length = snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", dirpath, filename);
  if ((length < 0) || (length >= MAX_PATH_LENGTH))
  {
    return 0;
  }

  return filepath;
}

static UA_Status_t uasdk_add_pki_path(const UA_UTF8_string_t* pki_path, const char* native_path, char* file_path)
{
	char pkipath[MAX_PATH_LENGTH];
  int length = 0;

  if(!pki_path)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  
	if(pki_path->length > MAX_PATH_LENGTH)
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
	}
	UASDK_memcpy(pkipath, pki_path->data, pki_path->length);
	pkipath[pki_path->length] = '\0';

  length = snprintf(file_path, MAX_PATH_LENGTH - 1, "%s/%s", pkipath, native_path);
  if ((length <= 0) || (length >= MAX_PATH_LENGTH))
  {
  	UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  return OpcUa_Good;
}

static const char* filename_own_cert_rsa_min(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_CERTS, UA_SECURITY_FILENAME_CERT_RSA_MIN);
}

static const char* filename_own_cert_rsa_sha256(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_CERTS, UA_SECURITY_FILENAME_CERT_RSA_SHA256);
}

static const char* filename_own_cert(UA_CertificateType_t type, UA_CertificateGroup_t group)
{
  const char* filename = 0;
  switch(type)
  {
    case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
      filename = filename_own_cert_rsa_min(group);
      break;

    case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
      filename = filename_own_cert_rsa_sha256(group);
      break;

    default:
      break;
  }

  return filename;
}

static const char* filename_own_cert_private_key_rsa_min(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_PRIVATE, UA_SECURITY_FILENAME_KEY_RSA_MIN);
}

static const char* filename_own_cert_private_key_rsa_sha256(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_PRIVATE, UA_SECURITY_FILENAME_KEY_RSA_SHA256);
}

static const char* filename_own_cert_private_key(UA_CertificateType_t type, UA_CertificateGroup_t group)
{
  const char* filename = 0;

  switch(type)
  {
    case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
      filename = filename_own_cert_private_key_rsa_min(group);
      break;

    case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
      filename = filename_own_cert_private_key_rsa_sha256(group);
      break;

    default:
      break;
  }

  return filename;
}

static const char* filename_rejected_cert(UA_CertificateGroup_t group, X509* cert)
{
  const char* empty_name = 0;
  static char filepath[MAX_PATH_LENGTH];
  char buf[SHA1_HASH_LENGTH];
  int i = 0;
  const EVP_MD *digest = EVP_sha1();
  unsigned len;

  int rc = X509_digest(cert, digest, (unsigned char*) buf, &len);
  if (rc == 0 || len != SHA1_HASH_LENGTH)
  {
    return empty_name;
  }

  for(i = 0; i < SHA1_HASH_LENGTH; i++)
  {
    char *l = &filepath[2 * i];
    snprintf(l, 3, "%02X", buf[i]);
  }
  snprintf(&filepath[SHA1_HASH_LENGTH * 2], 5, ".der");

  return get_filepath(group, DIR_TYPE_REJECTED, DIR_CERTS, filepath);
}

static UA_Status_t get_cert_from_bytestring(const UA_Byte_string_t* certificate, X509** cert)
{
  UA_Status_t result = OpcUa_BadInternalError;
  const unsigned char* p = 0;

  if ((certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->max_length < certificate->length))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  p = certificate->data;
  *cert = d2i_X509(0, &p, certificate->length);
  if (*cert)
  {
    result = OpcUa_Good;
  }

  return result;
}

static bool_t match_uri_with_SAN(GENERAL_NAMES* san_general_name, const UA_UTF8_string_t* uri, int tagMask )
{
   int32_t count = sk_GENERAL_NAME_num(san_general_name);
   bool_t found_uri = FALSE;
   int i = 0;
   for (i = 0; i < count; i++)
   {
     GENERAL_NAME* general_name = sk_GENERAL_NAME_value(san_general_name, i);
     if (general_name->type == tagMask)
     {
       char* URI = (char*)ASN1_STRING_data(general_name->d.uniformResourceIdentifier);
       int length = ASN1_STRING_length(general_name->d.uniformResourceIdentifier);
       if (length > uri->length)
       {
         length = uri->length;
       }
       if (UASDK_memcmp(URI, uri->data, length) == 0)
       {
         found_uri = TRUE;
         break;
       }
     }
   }

   return found_uri;
}

static bool_t match_dns_with_SAN(GENERAL_NAMES* san_general_name, const UA_UTF8_string_t* dns, int tagMask )
{
   int32_t count = sk_GENERAL_NAME_num(san_general_name);
   bool_t found_dns = FALSE;
   int i = 0;
   for (i = 0; i < count; i++)
   {
     GENERAL_NAME* general_name = sk_GENERAL_NAME_value(san_general_name, i);
     if (general_name->type == tagMask)
     {
       char* DNS = (char*)ASN1_STRING_data(general_name->d.dNSName);
       int length = ASN1_STRING_length(general_name->d.dNSName);
       if (length > dns->length)
       {
         length = dns->length;
       }
       if (UASDK_memcmp(DNS, dns->data, length) == 0)
       {
         found_dns = TRUE;
         break;
       }
     }
   }

   return found_dns;
}

static bool_t match_IpAddress_with_SAN(GENERAL_NAMES* san_general_name, const UA_UTF8_string_t* ipAddress, int tagMask )
{
   int32_t count = sk_GENERAL_NAME_num(san_general_name);
   bool_t found_ip = FALSE;
   unsigned char ipv4octet[4];
   int i = 0;

   if(get_string_ipv4_to_ipv4octet(ipAddress, ipv4octet) < 0)
   {
     return found_ip;
   }

   for (i = 0; i < count; i++)
   {
     GENERAL_NAME* general_name = sk_GENERAL_NAME_value(san_general_name, i);
     if (general_name->type == tagMask)
     {
       char* IP = (char*)ASN1_STRING_data(general_name->d.iPAddress);
       int length = ASN1_STRING_length(general_name->d.iPAddress);
       if (length > 4)
       {
         length = 4;
       }
       // TODO - need to validate
       if (UASDK_memcmp(IP, ipv4octet, length) == 0)
       {
         found_ip = TRUE;
         break;
       }
     }
   }

   return found_ip;
}

static UA_Status_t validate_subject_alternate_name(const X509* cert, const UA_UTF8_string_t* san, int tagMask)
{
  UA_Status_t result = OpcUa_BadInternalError;
  int criticality = -1;
  int extIndex = -1;
  bool_t found_san = FALSE;
  GENERAL_NAMES* subject_alt_name = 0;

  if ( !san || (!san->data) || (san->length <= 0)|| (cert == 0))
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  /* Check for subject alt name */
  extIndex = -1;
  subject_alt_name = (GENERAL_NAMES*) X509_get_ext_d2i((X509*)cert, NID_subject_alt_name, &criticality, &extIndex);
  if (!subject_alt_name)
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  /* Test SAN */
  switch(tagMask)
  {
  case GEN_URI:
    found_san = match_uri_with_SAN(subject_alt_name, san, GEN_URI );
    break;
  case GEN_DNS:
  case GEN_IPADD:
    found_san = match_dns_with_SAN(subject_alt_name, san, GEN_DNS );
    if(found_san)
      break;
    found_san = match_IpAddress_with_SAN(subject_alt_name, san, GEN_IPADD );
    break;
  default:
    break;
  }

  if (!found_san)
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  if (subject_alt_name)
  {
    GENERAL_NAMES_free(subject_alt_name);
  }

  return result;
}

static UA_Status_t validate_SAN(const UA_Byte_string_t* certificate, const UA_UTF8_string_t* san, int tagMask)
{
  UA_Status_t result = OpcUa_BadInternalError;
  X509* cert = 0;

  if ( !san || (!san->data) || (san->length <= 0)
      || (certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->max_length < certificate->length) )
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  result = get_cert_from_bytestring(certificate, &cert);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  result = validate_subject_alternate_name( cert, san, tagMask);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  if (cert)
  {
    X509_free(cert);
  }

  return result;
}

static RSA* get_cert_public_key(X509* cert)
{
  EVP_PKEY * evp_key = 0;
  RSA* key = 0;

  if (cert)
  {
    evp_key = X509_get_pubkey(cert);
    if (evp_key)
    {
      key = EVP_PKEY_get1_RSA(evp_key);
      EVP_PKEY_free(evp_key);
    }
  }

  return key;
}

static UA_Status_t get_public_key_from_bytestring(const UA_Byte_string_t* certificate, RSA** key)
{
  X509* cert = 0;
  UA_Status_t result = OpcUa_BadInternalError;

  result = get_cert_from_bytestring(certificate, &cert);
  if (result)
  {
    goto clean_up;
  }

  *key = get_cert_public_key(cert);
  if (!*key)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  clean_up:

  if (cert)
  {
    X509_free(cert);
  }

  return result;
}

static RSA* get_private_key(const char* filepath, UA_UTF8_string_t* private_key_password)
{
  unsigned char tempString[MAX_STRING_LENGTH];
  UA_Status_t status = OpcUa_Good;

  EVP_PKEY* evp_key = 0;
  RSA* rsa_key = 0;
#ifdef _MSC_VER
  FILE* fp = 0;
  errno_t err = fopen_s(&fp, filepath, "rb");
  if (err != 0)
  {
		goto clean_up;
  }
#else
  FILE* fp = fopen(filepath, "r");
#endif
  if (!fp)
  {
    goto clean_up;
  }

  status = CopyUtf8StringToNullTerminatedString(private_key_password, tempString, MAX_STRING_LENGTH);
  if (status != OpcUa_Good)
  {
    goto clean_up;
  }

  if (!PEM_read_PrivateKey(fp, &evp_key, NULL, tempString))
  {
    goto clean_up;
  }
  if (evp_key)
  {
    rsa_key = EVP_PKEY_get1_RSA(evp_key);
  }

  clean_up:

  if (fp)
  {
    fclose(fp);
  }
  if (evp_key)
  {
    EVP_PKEY_free(evp_key);
  }

  if (rsa_key)
  {
    //Protect private key from timing attacks
    RSA_blinding_on(rsa_key, 0);
  }

  return rsa_key;
}

static UA_Status_t get_der_from_file(const char* filepath, UA_Byte_string_t* der)
{
  UA_Status_t result = OpcUa_BadInvalidArgument;
  int fd = 0;
  struct stat buf;
#ifdef _MSC_VER
  FILE* fp = 0;
  errno_t err = fopen_s(&fp, filepath, "rb");
  if (err != 0)
  {
		result = OpcUa_BadInternalError;
		goto clean_up;
  }
#else
  FILE* fp = fopen(filepath, "r");
#endif
  if (!fp)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  fd = fileno(fp);
  fstat(fd, &buf);

  der->data = 0;
  der->data = (uint8_t*)UASDK_Malloc(buf.st_size);
  if(!der->data)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  if ((int32_t)fread(der->data, sizeof(uint8_t), buf.st_size, fp) != buf.st_size)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  der->max_length = der->length = buf.st_size;
  result = OpcUa_Good;

  return result;

  clean_up:

  if (fp)
  {
    fclose(fp);
  }
  if(der->data)
  {
    UASDK_Free(der->data);
  }

  return result;
}

static UA_Status_t get_own_cert_der(const UA_UTF8_string_t* pki_path, UA_CertificateType_t type, UA_CertificateGroup_t group, UA_Byte_string_t* der)
{
  const char* filename = 0;
  char file_path[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_Good;

  filename = filename_own_cert(type, group);
  if(!filename)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    return result;
  }

  return get_der_from_file(file_path, der);
}

static X509* get_cert(const char* filepath)
{
  X509* cert = 0;
#ifdef _MSC_VER
  FILE* fp = 0;
  errno_t err = fopen_s(&fp, filepath, "rb");
  if (err != 0)
  {
	  goto clean_up;
  }
#else
  FILE* fp = fopen(filepath, "r");
#endif
  if (!fp)
  {
    goto clean_up;
  }
  if (!d2i_X509_fp(fp, &cert))
  {
    if (cert)
    {
      X509_free(cert);
      cert = 0;
    }
    goto clean_up;
  }

  clean_up:

  if (fp)
  {
    fclose(fp);
  }

  return cert;
}

static X509_CRL* get_crl(const char* filepath)
{
  X509_CRL* crl = 0;
#ifdef _MSC_VER
  FILE* fp = 0;
  errno_t err = fopen_s(&fp, filepath, "rb");
  if (err != 0)
  {
		goto clean_up;
  }
#else
  FILE* fp = fopen(filepath, "r");
#endif
  if (!fp)
  {
    goto clean_up;
  }
  if (!d2i_X509_CRL_fp(fp, &crl))
  {
    if(crl)
    {
      X509_CRL_free(crl);
      crl = 0;
    }
    goto clean_up;
  }

  clean_up:

  if (fp)
  {
    fclose(fp);
  }

  return crl;
}

static X509* get_own_cert(const UA_UTF8_string_t* pki_path, UA_CertificateType_t type, UA_CertificateGroup_t group)
{
  const char* filename = 0;
  char file_path[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_Good;

  filename = filename_own_cert(type, group);
  if(!filename)
  {
    return 0;
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    return 0;
  }

  return get_cert(file_path);
}

static UA_Status_t extract_certs_from_chain(const UA_Byte_string_t* certificate_chain, X509** cert, STACK_OF(X509)* untrusted_stack)
{
  UA_Status_t result = OpcUa_BadInternalError;
  const unsigned char* p = certificate_chain->data;
  const unsigned char* end = certificate_chain->data + certificate_chain->length;

  if ((certificate_chain == 0) || (certificate_chain->data == 0) || (certificate_chain->length <= 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  do
  {
    X509* temp = d2i_X509(0, &p, end - p);
    if (!temp)
    {
      goto clean_up;
    }
    sk_X509_push(untrusted_stack, temp);
  } while (p < end);

  *cert = sk_X509_shift(untrusted_stack);

  result = OpcUa_Good;

  clean_up:

  return result;
}

int verify_callback(int ok, X509_STORE_CTX *ctx)
{
#if (UASDK_DEBUG > 0)
  char data[256];
#endif

  if (!is_trusted)
  {
    /* Manually check trust */
    X509* cert = X509_STORE_CTX_get_current_cert(ctx);
    if (cert && trusted_stack)
    {
      int count = sk_X509_num(trusted_stack);
      int i = 0;
      for (i = 0; i < count; i++)
      {
        if (X509_cmp(cert, sk_X509_value(trusted_stack, i)) == 0)
        {
          /* At least one cert in the chain is trusted */
          is_trusted = TRUE;
        }
      }
    }
  }

  if(!ok)
  {
    int err = X509_STORE_CTX_get_error(ctx);
#if (UASDK_DEBUG > 0)
    X509* cert = X509_STORE_CTX_get_current_cert(ctx);
    int depth = X509_STORE_CTX_get_error_depth(ctx);
    fprintf(stderr, "-Error with certificate at depth: %i\n", depth);
    X509_NAME_oneline(X509_get_issuer_name(cert), data, 256);
    fprintf(stderr, " issuer = %s\n", data);
    X509_NAME_oneline(X509_get_subject_name(cert), data, 256);
    fprintf(stderr, " subject = %s\n", data);
    fprintf(stderr, " err %i:%s\n", err, X509_verify_cert_error_string(err));
#endif

    if (suppress_error(err))
    {
      return 1;
    }
  }
  return ok;
}

static UA_Status_t set_verification_parameters(X509_STORE_CTX *ctx, uint32_t option_bits, bool_t self_signed)
{
  UA_Status_t result = OpcUa_BadInternalError;
  unsigned long flags = 0;
  X509_VERIFY_PARAM* param = X509_STORE_CTX_get0_param(ctx);
  if (!param)
  {
    goto clean_up;
  }

  flags |= X509_V_FLAG_X509_STRICT;
  flags |= X509_V_FLAG_CHECK_SS_SIGNATURE;

	if (option_bits & OB_SUPPRESS_CERTIFICATE_EXPIRED)
	{
	  /* Handled in verify callback */
	}
	if (option_bits & OB_SUPPRESS_HOSTNAME_INVALID)
	{
	  /* This is Handled in validate_extensions  */
	}
  if (option_bits & OB_SUPPRESS_URI_MISMATCH)
  {
    /* This is Handled in validate_extensions  */
  }
 	if (option_bits & OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN)
	{
	  /* Handled in verify callback */
	}
	if (option_bits & OB_CHECK_REVOCATION_STATUS_ONLINE)
	{
	  /* Ignore as we do not support online CRL checking */
	}
	if (option_bits & OB_CHECK_REVOCATION_STATUS_OFFLINE)
	{
	  if (!self_signed)
	  {
		flags |= X509_V_FLAG_CRL_CHECK;
		flags |= X509_V_FLAG_CRL_CHECK_ALL;
	  }
	}

  X509_VERIFY_PARAM_set_flags(param, flags);

  result = OpcUa_Good;

  clean_up:

  return result;
}

static UA_Status_t validate_extensions(X509* cert, const UA_Certificate_Validation_Parameters_t* parameters)
{
  UA_Status_t result = OpcUa_BadInternalError;
  int i = 0;
  int criticality = -1;
  int extIndex = -1;
  EXTENDED_KEY_USAGE* ext_key_usage = 0;
  ASN1_BIT_STRING* key_usage = 0;
  AUTHORITY_KEYID* auth_key_id = 0;
  GENERAL_NAMES* subject_alt_name = 0;

  /* Check for subject alt name */
  extIndex = -1;
  subject_alt_name = (GENERAL_NAMES*) X509_get_ext_d2i(cert, NID_subject_alt_name, &criticality, &extIndex);
  if (!subject_alt_name)
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  { /* Check HostName */
    bool_t supressHostName = (parameters->validation_option_bits & OB_SUPPRESS_HOSTNAME_INVALID);
    if (supressHostName == 0)
    {
      result = validate_subject_alternate_name(cert, &parameters->hostname, GEN_DNS);
      if (result != OpcUa_Good)
      {
        result = OpcUa_BadCertificateHostNameInvalid;
        goto clean_up;
      }
    }
  }
  { /* Check URI */
    bool_t supressUriMismatch = (parameters->validation_option_bits & OB_SUPPRESS_URI_MISMATCH);
    if (supressUriMismatch == 0)
    {
      result = validate_subject_alternate_name(cert, &parameters->uri, GEN_URI);
      if (result != OpcUa_Good)
      {
        result = OpcUa_BadCertificateInvalid;
        goto clean_up;
      }
    }
  }

  /* Test key usage */
  extIndex = -1;
  key_usage = (ASN1_BIT_STRING *) X509_get_ext_d2i(cert, NID_key_usage, &criticality, &extIndex);
  if (!key_usage)
  {
    goto clean_up;
  }

  if (!ASN1_BIT_STRING_get_bit(key_usage, 0) || !ASN1_BIT_STRING_get_bit(key_usage, 1)
      || !ASN1_BIT_STRING_get_bit(key_usage, 2) || !ASN1_BIT_STRING_get_bit(key_usage, 3))
  {
    result = OpcUa_BadCertificateUseNotAllowed;
    goto clean_up;
  }

  /* Test extended key usage */
  extIndex = -1;
  ext_key_usage = (EXTENDED_KEY_USAGE*) X509_get_ext_d2i(cert, NID_ext_key_usage, &criticality, &extIndex);
  if (!ext_key_usage)
  {
    goto clean_up;
  }

  {
    bool_t client_ext_ok = FALSE;
    bool_t server_ext_ok = FALSE;
    for(i = 0; i < sk_ASN1_OBJECT_num(ext_key_usage); i++)
    {
      switch(OBJ_obj2nid(sk_ASN1_OBJECT_value(ext_key_usage, i)))
      {
        case NID_client_auth:
          client_ext_ok = TRUE;
          break;
        case NID_server_auth:
          server_ext_ok = TRUE;
          break;
      }
    }

    if ( ((client_ext_ok == FALSE) && (parameters->validateExtensionsClient))
        || ((server_ext_ok == FALSE) && (parameters->validateExtensionsServer)) )
    {
      result = OpcUa_BadCertificateUseNotAllowed;
      goto clean_up;
    }
  }
  /* Check for authority key identifier */
  extIndex = -1;
  auth_key_id = (AUTHORITY_KEYID*) X509_get_ext_d2i(cert, NID_authority_key_identifier, &criticality, &extIndex);
  if (!auth_key_id && !is_self_signed(cert))
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  if (key_usage)
  {
    ASN1_BIT_STRING_free(key_usage);
  }
  if (ext_key_usage)
  {
    sk_ASN1_OBJECT_pop_free(ext_key_usage, ASN1_OBJECT_free);
  }
  if (auth_key_id)
  {
    AUTHORITY_KEYID_free(auth_key_id);
  }
  if (subject_alt_name)
  {
    GENERAL_NAMES_free(subject_alt_name);
  }

  return result;
}

//UA_Status_t get_thumbprint(const UA_Byte_string_t* der, char* thumbprint, uint32_t thumbprint_max_length)
//{
//  UA_Status_t result = OpcUa_BadInternalError;
//
//  if (!der || !der->data || (der->length <= 0) || !thumbprint || (thumbprint_max_length < SHA1_STRING_LENGTH))
//  {
//    result = OpcUa_BadInvalidArgument;
//    goto clean_up;
//  }
//
//  {
//      uint8_t hash[SHA1_LENGTH];
//      UA_Byte_string_t hash_ = { 0, SHA1_LENGTH, hash };
//      int i = 0;
//      result = UASecurity_digest(UA_DIGEST_SHA1, der, &hash_);
//      if (result != OpcUa_Good)
//      {
//        goto clean_up;
//      }
//
//      for(i = 0; i < SHA1_LENGTH; i++)
//      {
//        char *l = &thumbprint[2 * i];
//        snprintf(l, 3, "%02X", hash[i]);
//      }
//
//      result = OpcUa_Good;
//  }
//
//  clean_up:
//
//  return result;
//}

static UA_Status_t extract_cert_from_chain(const UA_Byte_string_t* certificate_chain, UA_Byte_string_t* certificate)
{
  UA_Status_t result = OpcUa_BadInternalError;
  X509* cert = 0;
  const unsigned char* p = certificate_chain->data;

  if ((certificate_chain == 0) || (certificate_chain->data == 0) || (certificate_chain->length <= 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  cert = d2i_X509(0, &p, certificate_chain->length);
  if (!cert)
  {
    goto clean_up;
  }

  certificate->data = certificate_chain->data;
  certificate->length = certificate->max_length = p - certificate_chain->data;

  result = OpcUa_Good;

  clean_up:

  if (cert)
  {
    X509_free(cert);
  }

  return result;
}

void set_is_trusted(bool_t validate_trust)
{
	is_trusted = !validate_trust;
}

static UA_Status_t validate_certificate(const UA_Certificate_Validation_Parameters_t* parameters, bool_t validate_trust, int32_t* rejected_certificate_length)
{
  UA_Status_t result = OpcUa_BadInternalError;
  X509* cert = 0;
  RSA* key = 0;

  STACK_OF(X509)* chain_stack = 0;
  STACK_OF(X509)* total_stack = 0;
  STACK_OF(X509_CRL)* total_crls = 0;

  //STACK_OF(X509)* trusted_stack = 0;
  STACK_OF(X509)* issuer_stack = 0;
  STACK_OF(X509_CRL)* trusted_crls = 0;
  STACK_OF(X509_CRL)* issuer_crls = 0;

  X509_STORE* store = 0;
  X509_STORE_CTX* ctx = 0;

  int rc = 0;
  bool_t self_signed = FALSE;

  if ((parameters->trusted_stack_handle == 0) || (parameters->issuer_stack_handle == 0)
      || (parameters->trusted_crls_handle == 0)|| (parameters->issuer_crls_handle == 0)
      || (rejected_certificate_length == 0)
      || (parameters->certificate_chain.data == 0) || (parameters->certificate_chain.length <= 0)
      || (parameters->type == UA_CERTIFICATE_TYPE_INVALID) || (parameters->group == UA_CERTIFICATE_GROUP_INVALID)
      || (parameters->certificate_chain.length > parameters->certificate_chain.max_length))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *rejected_certificate_length = 0;

  total_stack = sk_X509_new_null();
  if (!total_stack)
  {
    goto clean_up;
  }
  chain_stack = sk_X509_new_null();
  if (!chain_stack)
  {
    goto clean_up;
  }
  total_crls = sk_X509_CRL_new_null();
  if(!total_crls)
  {
    goto clean_up;
  }

  result = extract_certs_from_chain(&parameters->certificate_chain, &cert, chain_stack);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  trusted_stack = (STACK_OF(X509)*) parameters->trusted_stack_handle;
  issuer_stack = (STACK_OF(X509)*) parameters->issuer_stack_handle;
  trusted_crls = (STACK_OF(X509_CRL)*) parameters->trusted_crls_handle;
  issuer_crls = (STACK_OF(X509_CRL)*) parameters->issuer_crls_handle;

  /* Validate key length */
  key = get_cert_public_key(cert);
  if (!key)
  {
    result = OpcUa_BadSecurityChecksFailed;
    goto clean_up;
  }

  switch (parameters->policy)
  {
    case SECURITY_POLICY_BASIC128RSA15:
    case SECURITY_POLICY_BASIC256:
    {
    	switch(OBJ_obj2nid(cert->sig_alg->algorithm))
    	{
    	case NID_sha1WithRSAEncryption:
    	case NID_sha256WithRSAEncryption:
    	case NID_sha384WithRSAEncryption:
    	case NID_sha512WithRSAEncryption:
    		break;

    	default:
        result = OpcUa_BadSecurityChecksFailed;
    		break;
    	}

      if ((RSA_size(key) < 128) || (RSA_size(key) > 256))
      {
        result = OpcUa_BadSecurityChecksFailed;
      }
    }
      break;

    case SECURITY_POLICY_BASIC256SHA256:
    {
    	switch(OBJ_obj2nid(cert->sig_alg->algorithm))
    	{
    	case NID_sha256WithRSAEncryption:
    	case NID_sha384WithRSAEncryption:
    	case NID_sha512WithRSAEncryption:
    		break;

    	default:
        result = OpcUa_BadSecurityChecksFailed;
    		break;
    	}

      if ((RSA_size(key) < 256) || (RSA_size(key) > 512))
      {
        result = OpcUa_BadSecurityChecksFailed;
      }
    }
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      break;
  }

  if(result != OpcUa_Good)
  {
    goto clean_up;
  }

  if (is_self_signed(cert))
  {
    /* Add cert to total stack */
    sk_X509_push(total_stack, cert);
    self_signed = TRUE;
  }
  else
  {
    /* Add all certs to total stack */
    int count = sk_X509_num(chain_stack);
    int i = 0;
    for (i = 0; i < count; i++)
    {
      sk_X509_push(total_stack, sk_X509_value(chain_stack, i));
    }

    count = sk_X509_num(trusted_stack);
    for (i = 0; i < count; i++)
    {
      sk_X509_push(total_stack, sk_X509_value(trusted_stack, i));
    }

    count = sk_X509_num(issuer_stack);
    for (i = 0; i < count; i++)
    {
      sk_X509_push(total_stack, sk_X509_value(issuer_stack, i));
    }

    /* Add all crls to total_crls*/
    count = sk_X509_CRL_num(trusted_crls);
    for (i = 0; i < count; i++)
    {
      sk_X509_CRL_push(total_crls, sk_X509_value(trusted_crls, i));
    }

    count = sk_X509_CRL_num(issuer_crls);
    for (i = 0; i < count; i++)
    {
      sk_X509_CRL_push(total_crls, sk_X509_value(issuer_crls, i));
    }
  }

  validation_option = parameters->validation_option_bits;
  store = X509_STORE_new();
  X509_STORE_set_verify_cb(store, verify_callback);
  ctx = X509_STORE_CTX_new();
  X509_STORE_CTX_init(ctx, store, 0, 0);
  X509_STORE_CTX_trusted_stack(ctx, total_stack);
  X509_STORE_CTX_set0_crls(ctx, total_crls);
  X509_STORE_CTX_set_cert(ctx, cert);
  result = set_verification_parameters(ctx, parameters->validation_option_bits, self_signed);

  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  /* Initialise global */
  set_is_trusted(validate_trust);

  rc = X509_verify_cert(ctx);
  if (rc == 1)
  {
    if (is_application_cert(parameters->group)
        && (is_trusted == FALSE)
        && (parameters->trust_all_clients_when_the_trust_list_is_empty)
        && (sk_X509_num(trusted_stack) == 0))
    {
      is_trusted = TRUE;
    }

    /* Check trust*/
    if (is_trusted)
    {
      if (is_application_cert(parameters->group))
      {
        /* Validate extensions */
        result = validate_extensions(cert, parameters);
      }
      else
      {
        result = OpcUa_Good;
      }
    }
    else
    {
      result = OpcUa_BadCertificateUntrusted;
    }
  }
  else
  {
    result = OpcUa_BadSecurityChecksFailed;
  }

  if (result != OpcUa_Good)
  {
    int err = X509_STORE_CTX_get_error(ctx);
    if (err != X509_V_OK)
    {
      result = get_validation_errcode(err);
    }

    if (save_to_rejected_folder(err))
    {
      UA_Byte_string_t cert = { 0, 0, 0};
      extract_cert_from_chain(&parameters->certificate_chain, &cert);
      *rejected_certificate_length = cert.length;
    }
  }

  if (is_trusted == FALSE)
  {
    result = OpcUa_BadCertificateUntrusted;
  }

  clean_up:

  if (ctx)
  {
    X509_STORE_CTX_cleanup(ctx);
    X509_STORE_CTX_free(ctx);
  }
  if (chain_stack)
  {
    sk_X509_pop_free(chain_stack, X509_free);
  }
  if (key)
  {
    RSA_free(key);
  }
  if (total_stack)
  {
    sk_X509_free(total_stack);
    total_stack = 0;
  }
  if (total_crls)
  {
    sk_X509_CRL_free(total_crls);
    total_crls = 0;
  }
  if (store)
  {
    X509_STORE_free(store);
  }
  if (cert)
  {
    X509_free(cert);
  }

  return result;
}

static UA_Status_t add_certs_to_stack(const char* directory, STACK_OF(X509)* stack)
{
  DIR* dir = 0;
  struct dirent* de = 0;

  dir = opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, ".der"))
      {
        char temp_buf[MAX_PATH_LENGTH];
        X509* cert = 0;
        int length = snprintf(temp_buf, MAX_PATH_LENGTH - 1, "%s/%s", directory, de->d_name);
        if ((length < 0) || (length >= MAX_PATH_LENGTH))
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
        }

        cert = get_cert(temp_buf);
        if (cert)
        {
          sk_X509_push(stack, cert);
        }
      }
    }

  } while (de != NULL);

  closedir(dir);

  return OpcUa_Good;
}

static UA_Status_t add_crls_to_stack(const char* directory, STACK_OF(X509_CRL)* stack)
{
  DIR* dir = 0;
  struct dirent* de = 0;

  dir = opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, ".crl"))
      {
        char temp_buf[MAX_PATH_LENGTH];
        X509_CRL* crl = 0;
        int length = snprintf(temp_buf, MAX_PATH_LENGTH - 1, "%s/%s", directory, de->d_name);
        if ((length < 0) || (length >= MAX_PATH_LENGTH))
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
        }

        crl = get_crl(temp_buf);
        if (crl)
        {
          sk_X509_CRL_push(stack, crl);
        }
      }
    }

  } while (de != NULL);

  closedir(dir);

  return OpcUa_Good;
}

static void initialise_x509_stack(STACK_OF(X509)** stack)
{
  if (*stack)
  {
    sk_X509_pop_free(*stack, X509_free);
  }
  *stack = sk_X509_new_null();
}

static void initialise_crl_stack(STACK_OF(X509_CRL)** stack)
{
  if (*stack)
  {
    sk_X509_CRL_pop_free(*stack, X509_CRL_free);
  }
  *stack = sk_X509_CRL_new_null();
}

static void free_x509_stack(STACK_OF(X509)* stack)
{
  if (stack)
  {
    sk_X509_pop_free(stack, X509_free);
  }
}

static void free_crl_stack(STACK_OF(X509_CRL)* stack)
{
  if (stack)
  {
    sk_X509_CRL_pop_free(stack, X509_CRL_free);
  }
}

static UA_Status_t read_files_from_directory(
          const char* directory,
          const char* file_extension,
          uint32_t no_of_files_to_read,
          UA_Byte_string_t* der_out,
          uint32_t* no_of_files_read)
{
  DIR* dir = 0;
  struct dirent* de = 0;

  if( !((strcmp(file_extension, ".der") == 0) || (strcmp(file_extension, ".crl") == 0))
      && ((directory == 0) || (file_extension == 0) || (no_of_files_to_read > 0) || (der_out == 0) || (no_of_files_read == 0)) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *no_of_files_read = 0;

  dir = opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, file_extension))
      {
        char filepath[MAX_PATH_LENGTH];
        int length = snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", directory, de->d_name);
        if ((length < 0) || (length >= MAX_PATH_LENGTH))
        {
          if (*no_of_files_read > 0)
          {
            UASecurity_free_bytestrings(der_out, *no_of_files_read);
          }
          UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
        }
        {
          uint32_t  status = 0;
          UA_Byte_string_t file_der;

          status = get_der_from_file(filepath, &file_der);

          if (status != 0)
          {
            if (*no_of_files_read > 0)
            {
              UASecurity_free_bytestrings(der_out, *no_of_files_read);
            }
            UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
          }

          der_out[*no_of_files_read].data = file_der.data;
          der_out[*no_of_files_read].length = file_der.length;
          der_out[*no_of_files_read].max_length = file_der.max_length;
        }

        (*no_of_files_read)++;

        if(no_of_files_to_read <= *no_of_files_read)
        {
          break;
        }
      }
    }

  } while (de != 0);

  closedir(dir);

  return OpcUa_Good;
}

static UA_Status_t no_of_files_in_directory(const char* directory, const char* file_extension, uint32_t* no_of_files)
{
  DIR* dir = 0;
  struct dirent* de = 0;

  if( !((strcmp(file_extension, ".der") == 0) || (strcmp(file_extension, ".crl") == 0))
      && ((directory == 0) || (file_extension == 0) || (no_of_files == 0)))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *no_of_files = 0;

  dir = opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, file_extension))
      {
        (*no_of_files)++;
      }
    }

  } while (de != 0);

  closedir(dir);

  return OpcUa_Good;
}

static UA_Status_t check_certificate_generation_parameters(const UA_Certificate_Generation_Parameters_t* parameters)
{
  if( (parameters == 0)
  		|| (parameters->pki_path.length <= 0) || (parameters->pki_path.length >= MAX_PATH_LENGTH)|| (parameters->pki_path.data == 0)
		  || (parameters->type == UA_CERTIFICATE_TYPE_INVALID)
      || (parameters->group == UA_CERTIFICATE_GROUP_INVALID)
      || (parameters->private_key_password.data == 0) || (parameters->private_key_password.length <= 0)
      || (parameters->start_date == 0) || (parameters->end_date == 0)
      || (parameters->application_uri.data == 0) || (parameters->application_uri.length <= 0)
      || (parameters->common_name.data == 0) || (parameters->common_name.length <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch(parameters->type)
  {
    case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
      if((parameters->private_key_bit_length < 1024) || (parameters->private_key_bit_length > 2048))
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
      }
      break;

    case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
      if((parameters->private_key_bit_length < 2048) || (parameters->private_key_bit_length > 4096))
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
      }
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if(parameters->no_of_hostnames > 0)
  {
    if(parameters->hostnames == 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }
  }
  else if(parameters->no_of_ip_addresses > 0)
  {
    if(parameters->ip_addresses == 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }
  }
  else
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if((((parameters->organisation.length > 0) ? (uintptr_t) parameters->organisation.data : TRUE)
       && ((parameters->organisation_unit.length > 0) ? (uintptr_t) parameters->organisation_unit.data : TRUE)
       && ((parameters->locality.length > 0) ? (uintptr_t) parameters->locality.data : TRUE)
       && ((parameters->state.length > 0) ? (uintptr_t) parameters->state.data : TRUE)
       && ((parameters->country.length > 0) ? ((parameters->country.length <= 2) && ((uintptr_t) parameters->country.data)) : TRUE)) == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_library_initialise(const UA_UTF8_string_t* pki_path)
{
  UASDK_UNUSED(pki_path);
  UA_Status_t status = OpcUa_Good;
  const int NO_RANDOM_BYTES = 32;
  CRYPTO_set_mem_functions(UASDK_Malloc, UASDK_Realloc, UASDK_Free);

#if (UASDK_MULTITHREADED > 0)
  int i;

  lock_cs = UASDK_Malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
  if(!lock_cs)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  lock_count = UASDK_Malloc(CRYPTO_num_locks() * sizeof(long));
  if(!lock_count)
  {
    if(lock_cs)
    {
      UASDK_Free(lock_cs);
    }
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  for (i=0; i<CRYPTO_num_locks(); i++)
  {
    lock_count[i]=0;
    pthread_mutex_init(&(lock_cs[i]),NULL);
  }

  CRYPTO_set_id_callback((unsigned long (*)())pthreads_thread_id);
  CRYPTO_set_locking_callback((void (*)())pthreads_locking_callback);
#endif  //UASDK_MULTITHREADED

#ifndef _MSC_VER
  /* "/dev/random" can block on embedded systems due to insufficient entropy.
   * Developers and researchers are divided on whether "/dev/urandom" is
   * a secure alternative to seed the OpenSSL PRNG. Developers are further
   * divided on whether either "/dev/random" or "/dev/urandom" are particularly
   * secure sources of entropy. It is up to the application developer to
   * decide what is the most appropriate source of entropy for their specific
   * needs. This source may include alternatives such as hardware random
   * number generators, etc. and is not solely restricted to the Linux Kernel.
   */
  if (RAND_load_file("/dev/random", NO_RANDOM_BYTES) != NO_RANDOM_BYTES)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }
#endif

  if (RAND_status() == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }

  OpenSSL_add_all_algorithms();

  if (status != OpcUa_Good)
  {
    return status;
  }

  /* validate_server_certificate() must be the last operation */

  return OpcUa_Good;
}

void UASecurity_library_terminate(void)
{

  RAND_cleanup();

  EVP_cleanup();

  ERR_free_strings();

  ERR_remove_thread_state(NULL);

  CRYPTO_cleanup_all_ex_data();

#if (UASDK_MULTITHREADED > 0)
  int i;

  for (i=0; i<CRYPTO_num_locks(); i++)
  {
    pthread_mutex_destroy(&(lock_cs[i]));
  }
  UASDK_Free(lock_count);
  UASDK_Free(lock_cs);
#endif  //UASDK_MULTITHREADED
}

UA_Status_t UASecurity_rand_bytes(UA_Byte_string_t* buf)
{
//#error Verify that the entropy gathering implemented here is suitable for your application before removing this error macro

  if ((buf == 0) || (buf->data == 0) || (buf->max_length <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  buf->length = 0;

  if (RAND_bytes(buf->data, buf->max_length))
  {
    buf->length = buf->max_length;
    VALGRIND_MAKE_MEM_DEFINED(buf->data, buf->length);
    return OpcUa_Good;
  }

  UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
}

UA_Status_t UASecurity_rand_pseudo_bytes(UA_Byte_string_t* buf)
{
  if ((buf == 0) || (buf->data == 0) || (buf->max_length <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  buf->length = 0;

  if (RAND_pseudo_bytes(buf->data, buf->max_length))
  {
    buf->length = buf->max_length;
    VALGRIND_MAKE_MEM_DEFINED(buf->data, buf->length);
    return OpcUa_Good;
  }

  UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
}

UA_Status_t UASecurity_symmetric_encrypt(
    UA_Sym_Cipher_t type,
    const UA_Byte_string_t* iv,
    const UA_Byte_string_t* key,
    const UA_Byte_string_t* plaintext,
    UA_Byte_string_t* ciphertext)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  const EVP_CIPHER* cipher = 0;
  EVP_CIPHER_CTX ctx;
  int outl = 0;

  EVP_CIPHER_CTX_init(&ctx);

  if ((iv == 0) || (iv->data == 0) || (iv->length <= 0) || (iv->max_length < iv->length)
      || (key == 0) || (key->data == 0) || (key->length <= 0) || (key->max_length < key->length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->length <= 0) || (plaintext->max_length < plaintext->length)
      || (ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->max_length < plaintext->length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch (type)
  {
    case UA_SYM_CIPHER_AES_128_CBC:
      cipher = EVP_aes_128_cbc();
      break;

    case UA_SYM_CIPHER_AES_256_CBC:
      cipher = EVP_aes_256_cbc();
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  if ((iv->length != EVP_CIPHER_iv_length(cipher)) || (key->length != EVP_CIPHER_key_length(cipher)))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if (!EVP_EncryptInit(&ctx, cipher, key->data, iv->data))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  EVP_CIPHER_CTX_set_padding(&ctx, 0);

  if ((plaintext->length % EVP_CIPHER_CTX_block_size(&ctx)) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if (EVP_EncryptUpdate(&ctx, ciphertext->data, &outl, plaintext->data, plaintext->length) && (outl == plaintext->length))
  {
    if (EVP_EncryptFinal(&ctx, 0, &outl) && (outl == 0))
    {
      ciphertext->length = plaintext->length;
      VALGRIND_MAKE_MEM_DEFINED(ciphertext->data, ciphertext->length);
      result = OpcUa_Good;
    }
  }

  clean_up:

  EVP_CIPHER_CTX_cleanup(&ctx);

  return result;
}

UA_Status_t UASecurity_symmetric_decrypt(
    UA_Sym_Cipher_t type,
    const UA_Byte_string_t* iv,
    const UA_Byte_string_t* key,
    const UA_Byte_string_t* ciphertext,
    UA_Byte_string_t* plaintext)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  const EVP_CIPHER* cipher = 0;
  EVP_CIPHER_CTX ctx;
  int outl = 0;

  EVP_CIPHER_CTX_init(&ctx);

  if ((iv == 0) || (iv->data == 0) || (iv->length <= 0) || (iv->max_length < iv->length)
      || (key == 0) || (key->data == 0) || (key->length <= 0) || (key->max_length < key->length)
      || (ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->length <= 0) || (ciphertext->max_length < ciphertext->length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->max_length < ciphertext->length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch (type)
  {
    case UA_SYM_CIPHER_AES_128_CBC:
      cipher = EVP_aes_128_cbc();
      break;

    case UA_SYM_CIPHER_AES_256_CBC:
      cipher = EVP_aes_256_cbc();
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  if ((iv->length != EVP_CIPHER_iv_length(cipher)) || (key->length != EVP_CIPHER_key_length(cipher)))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if (!EVP_DecryptInit(&ctx, cipher, key->data, iv->data))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  EVP_CIPHER_CTX_set_padding(&ctx, 0);

  if ((ciphertext->length % EVP_CIPHER_CTX_block_size(&ctx)) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if (EVP_DecryptUpdate(&ctx, plaintext->data, &outl, ciphertext->data, ciphertext->length) && (outl == ciphertext->length))
  {
    if (EVP_DecryptFinal(&ctx, 0, &outl) && (outl == 0))
    {
      plaintext->length = ciphertext->length;
      VALGRIND_MAKE_MEM_DEFINED(plaintext->data, plaintext->length);
      result =  OpcUa_Good;
    }
  }

  clean_up:

  EVP_CIPHER_CTX_cleanup(&ctx);

  return result;
}

UA_Status_t UASecurity_digest(UA_Digest_t type, const UA_Byte_string_t* data, UA_Byte_string_t* hash)
{
  const EVP_MD* digest = 0;
  EVP_MD_CTX ctx;
  UA_Status_t result = OpcUa_BadInternalError;

  if ((data == 0) || (data->data == 0) || (data->length <= 0) || (data->length > data->max_length)
      || (hash == 0) || (hash->data == 0) || (hash->max_length <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch (type)
  {
    case UA_DIGEST_SHA1:
      digest = EVP_sha1();
      break;

    case UA_DIGEST_SHA256:
      digest = EVP_sha256();
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (hash->max_length < EVP_MD_size(digest))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  EVP_MD_CTX_init(&ctx);
  if (EVP_DigestInit(&ctx, digest))
  {
    if (EVP_DigestUpdate(&ctx, data->data, data->length))
    {
      unsigned int len = 0;

      if (EVP_DigestFinal(&ctx, hash->data, &len) && ((int32_t)len == EVP_MD_size(digest)))
      {
        hash->length = len;
        VALGRIND_MAKE_MEM_DEFINED(hash->data, hash->length);
        result = OpcUa_Good;
      }
    }
  }

  EVP_MD_CTX_cleanup(&ctx);

  return result;
}

UA_Status_t UASecurity_hmac(UA_Digest_t type, const UA_Byte_string_t* key, const UA_Byte_string_t* data, UA_Byte_string_t* hash)
{
  const EVP_MD* digest = 0;
  unsigned int hashlen = 0;

  if ((key == 0) || (key->data == 0) || (key->length <= 0) || (key->max_length < key->length)
      || (data == 0) || (data->data == 0) || (data->length <= 0) || (data->max_length < data->length)
      || (hash == 0) || (hash->data == 0) || (hash->max_length <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch (type)
  {
    case UA_DIGEST_SHA1:
      digest = EVP_sha1();
      break;

    case UA_DIGEST_SHA256:
      digest = EVP_sha256();
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (hash->max_length < EVP_MD_size(digest))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (HMAC(digest, key->data, key->length, data->data, data->length, hash->data, &hashlen) && ((int32_t)hashlen == EVP_MD_size(digest)))
  {
    hash->length = hashlen;
    VALGRIND_MAKE_MEM_DEFINED(hash->data, hash->length);
    return OpcUa_Good;
  }
  UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
}

UA_Status_t UASecurity_p_sha(UA_Digest_t type, const UA_Byte_string_t* secret, const UA_Byte_string_t* seed, UA_Byte_string_t* output)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;

  uint8_t A[MAX_DIGEST_LENGTH];
  const EVP_MD* digest = 0;
  uint32_t hash_length = 0;
  uint8_t* seed_buffer = 0;
  uint8_t* hash_buffer = 0;
  uint32_t no_of_bytes_required = 0;
  uint32_t no_of_iterations = 0;
  uint32_t i = 0;

  if ( (seed == 0) || (seed->data == 0) || (seed->length <= 0) || (seed->max_length < seed->length)
      || (secret == 0) || (secret->data == 0) || (secret->length <= 0) || (secret->max_length < secret->length)
      || (output == 0) || (output->data == 0) || (output->max_length <= 0) || (output->length > 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch (type)
  {
    case UA_DIGEST_SHA1:
      digest = EVP_sha1();
      hash_length = SHA1_LENGTH;
      break;

    case UA_DIGEST_SHA256:
      digest = EVP_sha256();
      hash_length = SHA256_LENGTH;
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  /* A(0) = seed */
  /* A(n) = HMAC_SHAx(secret, A(n-1)) */

  no_of_bytes_required = output->max_length;
  no_of_iterations = (no_of_bytes_required / hash_length);
  if (no_of_bytes_required % hash_length)
  {
    no_of_iterations++;
  }

  seed_buffer = (uint8_t*)UASDK_Malloc(hash_length + seed->length);
  if (!seed_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  /* Calculate A(1) */
  if (!HMAC(digest, secret->data, secret->length, seed->data, seed->length, A, 0))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  UASDK_memcpy(seed_buffer, A, hash_length);
  UASDK_memcpy(seed_buffer + hash_length, seed->data, seed->length);

  hash_buffer = (uint8_t*)UASDK_Malloc(no_of_iterations * hash_length);
  if (!hash_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  for (i = 0; i < no_of_iterations; i++)
  {
    /* Calculate P_SHAx(n) = HMAC_SHAx(secret, A(n-1) + seed) */
    if (!HMAC(digest, secret->data, secret->length, seed_buffer, hash_length + seed->length, &hash_buffer[i*hash_length], 0))
    {
      result = OpcUa_BadInternalError;
      goto clean_up;
    }

    /* Calculate A(n) = HMAC_SHAx(secret, A(n-1)) */
    if (!HMAC(digest, secret->data, secret->length, seed_buffer, hash_length, seed_buffer, 0))
    {
      result = OpcUa_BadInternalError;
      goto clean_up;
    }
  }

  UASDK_memcpy(output->data, hash_buffer, output->max_length);
  output->length = output->max_length;
  VALGRIND_MAKE_MEM_DEFINED(output->data, output->length);

  result = OpcUa_Good;

  clean_up:

  if (seed_buffer)
  {
    UASDK_Free(seed_buffer);
  }
  if (hash_buffer)
  {
    UASDK_Free(hash_buffer);
  }

  return result;
}

UA_Status_t UASecurity_asymmetric_encrypt(
    UA_Asym_Cipher_t type,
    const UA_Byte_string_t* receiver_chain,
    const UA_Byte_string_t* plaintext,
    UA_Byte_string_t* ciphertext)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  UA_Status_t status = OpcUa_BadInternalError;
  RSA* rsa = 0;
  int padding = 0;
  int cipherlen = 0;

  if ((receiver_chain == 0) || (receiver_chain->data == 0) || (receiver_chain->length <= 0) || (receiver_chain->max_length < receiver_chain->length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->length <= 0) || (plaintext->max_length < plaintext->length)
      || (ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->max_length <= 0))
  {
    result =  OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  status = get_public_key_from_bytestring(receiver_chain, &rsa);
  if (status || (rsa == 0))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  switch (type)
  {
    case UA_ASYM_CIPHER_RSA_PKCS1_v1_5:
      padding = RSA_PKCS1_PADDING;
      break;

    case UA_ASYM_CIPHER_RSA_OAEP:
      padding = RSA_PKCS1_OAEP_PADDING;
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  if (ciphertext->max_length < RSA_size(rsa))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  cipherlen = RSA_public_encrypt(plaintext->length, plaintext->data, ciphertext->data, rsa, padding);
  if (cipherlen >= 0)
  {
    ciphertext->length = cipherlen;
    VALGRIND_MAKE_MEM_DEFINED(ciphertext->data, ciphertext->length);
    result = OpcUa_Good;
  }

  clean_up:

  if (rsa)
  {
    RSA_free(rsa);
  }

  return result;
}

UA_Status_t UASecurity_asymmetric_decrypt(
    UA_Asym_Cipher_t type,
    uintptr_t receiver_private_key_handle,
    const UA_Byte_string_t* ciphertext,
    UA_Byte_string_t* plaintext)
{
  RSA* rsa = 0;
  int padding = 0;
  UA_Status_t result = OpcUa_BadInvalidArgument;
  int plainlen = 0;

  if ((ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->length <= 0) || (ciphertext->max_length < ciphertext->length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->max_length <= 0)
      || (receiver_private_key_handle == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  rsa = (RSA*) receiver_private_key_handle;

  switch (type)
  {
    case UA_ASYM_CIPHER_RSA_PKCS1_v1_5:
      padding = RSA_PKCS1_PADDING;
      break;

    case UA_ASYM_CIPHER_RSA_OAEP:
      padding = RSA_PKCS1_OAEP_PADDING;
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  if (plaintext->max_length < RSA_size(rsa))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  plainlen = RSA_private_decrypt(ciphertext->length, ciphertext->data, plaintext->data, rsa, padding);
  if (plainlen >= 0)
  {
    plaintext->length = plainlen;
    VALGRIND_MAKE_MEM_DEFINED(plaintext->data, plaintext->length);
    result = OpcUa_Good;
  }
  else
  {
    result = OpcUa_BadInternalError;
  }

  clean_up:

  return result;
}

UA_Status_t UASecurity_asymmetric_sign(
    UA_Digest_t type,
    uintptr_t signee_private_key_handle,
    const UA_Byte_string_t* data,
    UA_Byte_string_t* signature)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  RSA* rsa = 0;
  const EVP_MD* digest = 0;
  uint32_t oid_length = 0;
  uint8_t* computed_hash_buffer = 0;
  const uint8_t* hash_oid = 0;
  uint32_t hash_length = 0;
  uint32_t input_length = 0;

  if ((data == 0) || (data->data == 0) || (data->length <= 0) || (data->max_length < data->length)
      || (signature == 0) || (signature->data == 0) || (signature->max_length <= 0)
      || (signee_private_key_handle == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  rsa = (RSA*) signee_private_key_handle;

  switch (type)
  {
    case UA_DIGEST_SHA1:
      digest = EVP_sha1();
      oid_length = SHA1_OID_BYTESTRING_LENGTH;
      hash_oid = SHA1_OID_BYTESTRING;
      break;

    case UA_DIGEST_SHA256:
      digest = EVP_sha256();
      oid_length = SHA256_OID_BYTESTRING_LENGTH;
      hash_oid = SHA256_OID_BYTESTRING;
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  if (signature->max_length < RSA_size(rsa))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  hash_length = EVP_MD_size(digest);
  input_length = hash_length + oid_length;

  computed_hash_buffer = (uint8_t*)UASDK_Malloc(input_length);
  if(!computed_hash_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  UASDK_memcpy(computed_hash_buffer, hash_oid, oid_length);

  {
    /* Compute hash */
    UA_Byte_string_t computed_hash = { 0, hash_length, computed_hash_buffer + oid_length };
    uint32_t status = UASecurity_digest(type, data, &computed_hash);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }
  }

  {
    int32_t siglen = 0;
    UA_Byte_string_t from = { input_length, input_length, computed_hash_buffer };

    siglen = RSA_private_encrypt(from.length, from.data, signature->data, rsa, RSA_PKCS1_PADDING);
    if (siglen == RSA_size(rsa))
    {
      signature->length = siglen;
      VALGRIND_MAKE_MEM_DEFINED(signature->data, signature->length);
      result = OpcUa_Good;
    }
    else
    {
      result = OpcUa_BadUnexpectedError;
      goto clean_up;
    }
  }

  clean_up:

  if (computed_hash_buffer)
  {
    UASDK_Free(computed_hash_buffer);
  }

  return result;
}

UA_Status_t UASecurity_asymmetric_verify(
    UA_Digest_t type,
    const UA_Byte_string_t* sender_chain,
    const UA_Byte_string_t* data,
    const UA_Byte_string_t* signature)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  UA_Status_t status = OpcUa_BadInternalError;
  RSA* rsa = 0;
  const EVP_MD* digest = 0;
  uint32_t oid_length = 0;
  const uint8_t* hash_oid = 0;
  uint8_t* extracted_data_buffer = 0;
  uint8_t* computed_data_buffer = 0;
  uint32_t hash_length = 0;
  uint32_t output_length = 0;

  if ((data == 0) || (data->data == 0) || (data->length <= 0) || (data->max_length < data->length)
      || (signature == 0) || (signature->data == 0) || (signature->length <= 0) || (signature->max_length < signature->length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  status = get_public_key_from_bytestring(sender_chain, &rsa);
  if (status || (rsa == 0))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  switch (type)
  {
    case UA_DIGEST_SHA1:
      digest = EVP_sha1();
      oid_length = SHA1_OID_BYTESTRING_LENGTH;
      hash_oid = SHA1_OID_BYTESTRING;
      break;

    case UA_DIGEST_SHA256:
      digest = EVP_sha256();
      oid_length = SHA256_OID_BYTESTRING_LENGTH;
      hash_oid = SHA256_OID_BYTESTRING;
      break;

    default:
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
  }

  hash_length = EVP_MD_size(digest);
  output_length = hash_length + oid_length;

  extracted_data_buffer = (uint8_t*)UASDK_Calloc(output_length);
  if(!extracted_data_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  computed_data_buffer = (uint8_t*)UASDK_Calloc(output_length);
  if(!computed_data_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  UASDK_memcpy(computed_data_buffer, hash_oid, oid_length);

  {
    /* Compute hash */
    UA_Byte_string_t computed_data = { 0, hash_length, computed_data_buffer + oid_length };
    status = UASecurity_digest(type, data, &computed_data);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }
  }

  {
    int plainlen = 0;
    UA_Byte_string_t extracted_data = { 0, output_length, extracted_data_buffer };

    plainlen = RSA_public_decrypt(signature->length, signature->data, extracted_data.data, rsa, RSA_PKCS1_PADDING);
    if ((plainlen >= 0) && (plainlen <= extracted_data.max_length))
    {
      extracted_data.length = plainlen;
    }
    else
    {
      result = OpcUa_BadUnexpectedError;
      goto clean_up;
    }
  }

  VALGRIND_MAKE_MEM_DEFINED(extracted_data_buffer, output_length);
  VALGRIND_MAKE_MEM_DEFINED(computed_data_buffer, hash_length);

  if (UASDK_memcmp(extracted_data_buffer, computed_data_buffer, output_length) == 0)
  {
    result = OpcUa_Good;
  }

  clean_up:

  if (rsa)
  {
    RSA_free(rsa);
  }
  if (extracted_data_buffer)
  {
    UASDK_Free(extracted_data_buffer);
  }
  if (computed_data_buffer)
  {
    UASDK_Free(computed_data_buffer);
  }

  return result;
}

UA_Status_t UASecurity_certificate_validation_parameters_init(UA_Certificate_Validation_Parameters_t* parameters)
{
  if(parameters == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  parameters->trusted_stack_handle = 0;
  parameters->trusted_crls_handle = 0;
  parameters->issuer_stack_handle = 0;
  parameters->issuer_crls_handle = 0;

  parameters->type = UA_CERTIFICATE_TYPE_INVALID;
  parameters->group = UA_CERTIFICATE_GROUP_INVALID;
  parameters->policy = SECURITY_POLICY_INVALID;

  parameters->certificate_chain.data = 0;
  parameters->certificate_chain.length = 0;
  parameters->certificate_chain.max_length = 0;

  parameters->hostname.data = 0;
  parameters->hostname.length = 0;

  parameters->uri.data = 0;
  parameters->uri.length = 0;

  parameters->validation_option_bits = 0;

  return OpcUa_Good;
}

UA_Status_t UASecurity_certificate_validate(
    const UA_Certificate_Validation_Parameters_t* parameters,
		bool_t validate_trust,
    int32_t* rejected_certificate_length)
{
  return validate_certificate(parameters, validate_trust, rejected_certificate_length);
}

UA_Status_t UASecurity_save_cert_to_rejected_folder(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    const UA_Byte_string_t* certificate)
{
	char file_path[MAX_PATH_LENGTH];
  X509* cert;
  const char* filename = 0;
  FILE* fp = 0;
  UA_Status_t result = OpcUa_BadInternalError;

  if((certificate == 0) || (certificate->data == 0) || (certificate->length <= 0)
      || (certificate->max_length < certificate->length) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = get_cert_from_bytestring(certificate, &cert);
  if(result > 0)
  {
    goto clean_up;
  }

  filename = filename_rejected_cert(group, cert);
  if(!filename)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
	result = uasdk_add_pki_path(pki_path, filename, file_path);
	if(result != OpcUa_Good)
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
	}
	remove(file_path);
#ifdef _MSC_VER
	{
	  errno_t err = fopen_s(&fp, file_path, "wb");
	  if (err != 0)
	  {
			result = OpcUa_BadInternalError;
			goto clean_up;
	  }
	}
#else
  fp = fopen(file_path, "w");
#endif
  if(!fp)
  {
    result = OpcUa_BadInternalError;
	goto clean_up;
  }

  if(!i2d_X509_fp(fp, cert))
  {
    result = OpcUa_BadInternalError;
  }

  clean_up:

  if(fp)
  {
    fclose(fp);
  }
  if(cert)
  {
    X509_free(cert);
  }

  return result;
}

UA_Status_t UASecurity_validate_uri(const UA_Byte_string_t* certificate, const UA_UTF8_string_t* uri)
{
  UA_Status_t result = OpcUa_BadInternalError;

  if ( !uri || (!uri->data) || (uri->length <= 0)
      || (certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->max_length < certificate->length) )
  {
    result = OpcUa_BadCertificateUriInvalid;
    goto clean_up;
  }

  result = validate_SAN(certificate, uri, GEN_URI);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  return result;
}

UA_Status_t UASecurity_validate_hostname(const UA_Byte_string_t* certificate, const UA_UTF8_string_t* hostname)
{
  UA_Status_t result = OpcUa_BadInternalError;

  if ( !hostname || (!hostname->data) || (hostname->length <= 0)
      || (certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->max_length < certificate->length) )
  {
    result = OpcUa_BadCertificateUriInvalid;
    goto clean_up;
  }

  result = validate_SAN(certificate, hostname, GEN_DNS);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  return result;
}

UA_Status_t UASecurity_get_certificate_key_size(
    uintptr_t certificate_handle,
    uint32_t* key_size_in_bytes)
{
  X509* cert = 0;
  RSA* rsa = 0;

  if((certificate_handle == 0) || (key_size_in_bytes == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = (X509*) certificate_handle;
  rsa = get_cert_public_key(cert);

  if(!rsa)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *key_size_in_bytes = RSA_size(rsa);

  if (rsa)
  {
    RSA_free(rsa);
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_der_certificate_key_size(
    const UA_Byte_string_t* certificate,
    uint32_t* key_size_in_bytes)
{
  X509* cert = 0;
  UA_Status_t result = OpcUa_Good;

  if((key_size_in_bytes == 0)
      || (certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->max_length < certificate->length) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = get_cert_from_bytestring(certificate, &cert);
  if(result > 0)
  {
    goto clean_up;
  }

  result = UASecurity_get_certificate_key_size((uintptr_t)cert, key_size_in_bytes);

  clean_up:

  if(cert)
  {
    X509_free(cert);
  }

  return result;

}

UA_Status_t UASecurity_get_certificate_max_plaintext_size(
    UA_Asym_Cipher_t type,
    uintptr_t certificate_handle,
    uint32_t* max_plaintext_size)
{
  X509* cert = 0;
  RSA* rsa = 0;
  uint32_t key_size_in_bytes = 0;
  UA_Status_t result = OpcUa_Good;

  if ((certificate_handle == 0) || (max_plaintext_size == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = (X509*) certificate_handle;

  rsa = get_cert_public_key(cert);
  if(!rsa)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  key_size_in_bytes = RSA_size(rsa);

  if (type == UA_ASYM_CIPHER_RSA_PKCS1_v1_5)
  {
    *max_plaintext_size = key_size_in_bytes - 11;
  }
  else if (type == UA_ASYM_CIPHER_RSA_OAEP)
  {
    *max_plaintext_size = key_size_in_bytes - 42;
  }
  else
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  clean_up:

  if (rsa)
  {
    RSA_free(rsa);
  }

  return result;
}

UA_Status_t UASecurity_get_der_certificate_max_plaintext_size(
    UA_Asym_Cipher_t type,
    const UA_Byte_string_t* certificate,
    uint32_t* max_plaintext_size)
{
  X509* cert = 0;
  UA_Status_t result = OpcUa_Good;

  if ((max_plaintext_size == 0) || (type == UA_ASYM_CIPHER_INVALID)
      || (certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->max_length < certificate->length))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = get_cert_from_bytestring(certificate, &cert);
  if(result > 0)
  {
    goto clean_up;
  }

  result = UASecurity_get_certificate_max_plaintext_size(type, (uintptr_t)cert, max_plaintext_size);

  clean_up:

  if(cert)
  {
    X509_free(cert);
  }

  return result;
}

UA_Status_t UASecurity_certificate_to_der(
    uintptr_t certificate_handle,
    UA_Byte_string_t** certificate_der)
{
  X509* cert = 0;
  uint8_t* data = 0;
  int32_t len = 0;
  UA_Byte_string_t* derCert = 0;
  UA_Status_t result = OpcUa_BadInternalError;

  if((certificate_handle == 0) || (certificate_der == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = (X509*)certificate_handle;

  derCert = UASDK_Malloc(sizeof(UA_Byte_string_t));
  if(!derCert)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  //OpenSSL version should be 0.9.7 or later
  len = i2d_X509(cert, 0);
  if(len <= 0)
  {
    goto clean_up;
  }

  data = UASDK_Malloc(len);
  if(!data)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  derCert->length = i2d_X509(cert, &data);
  if(derCert->length <= 0)
  {
    goto clean_up;
  }
  derCert->data = data;
  derCert->max_length = derCert->length;

  *certificate_der = derCert;

  result = OpcUa_Good;

  return result;

  clean_up:

  if(derCert)
  {
    UASDK_Free(derCert);
  }
  if(data)
  {
    UASDK_Free(data);
  }

  return result;
}

UA_Status_t UASecurity_der_to_certificate(
    UA_Byte_string_t* certificate_der,
    uintptr_t* certificate_handle)
{
  X509* cert = 0;
  UA_Status_t result = OpcUa_BadInternalError;

  if((certificate_der == 0) || (certificate_handle == 0)
      || (certificate_der->data == 0) || (certificate_der->length <= 0) || (certificate_der->max_length < certificate_der->length))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = get_cert_from_bytestring(certificate_der, &cert);
  if(result > 0)
  {
    goto clean_up;
  }

  *certificate_handle = (uintptr_t) cert;

  return OpcUa_Good;

  clean_up:

  if(cert)
  {
    X509_free(cert);
  }
  return result;
}

UA_Status_t UASecurity_get_own_certificate(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    uintptr_t* own_certificate_handle,
    UA_Byte_string_t** own_certificate_der)
{
  UA_Status_t result = OpcUa_Good;
  if((pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0)
  		|| (type < UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE) || (type > UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE)
      || (group == UA_CERTIFICATE_GROUP_INVALID)
      || (own_certificate_handle == 0)
      || (own_certificate_der == 0) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = UASecurity_get_own_certificate_handle(pki_path, type, group, own_certificate_handle);
  if(result > 0)
  {
    goto clean_up;
  }

  result = UASecurity_get_own_certificate_der(pki_path, type, group, own_certificate_der);
  if(result > 0)
  {
    if(*own_certificate_handle)
    {
      X509_free((X509*)own_certificate_handle);
    }
  }

  clean_up:

  return result;
}

UA_Status_t UASecurity_get_own_certificate_handle(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    uintptr_t* own_certificate_handle)
{
  X509* cert = 0;

  if( (pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0)
  		|| (own_certificate_handle == 0) || (group == UA_CERTIFICATE_GROUP_INVALID)
      || (type < UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE) || (type > UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = get_own_cert(pki_path, type, group);
  if(!cert)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  *own_certificate_handle = (uintptr_t) cert;

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_own_certificate_der(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    UA_Byte_string_t** own_certificate_der)
{
  UA_Byte_string_t* derCert = 0;
  UA_Status_t result = OpcUa_Good;

  if( (pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0)
  		|| (own_certificate_der == 0) || (group == UA_CERTIFICATE_GROUP_INVALID)
      || (type < UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE) || (type > UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  derCert = UASDK_Malloc(sizeof(UA_Byte_string_t));
  if(!derCert)
  {
    result = OpcUa_BadOutOfMemory;
    return result;
  }
  derCert->length = derCert->max_length = 0;
  derCert->data = 0;
  result = get_own_cert_der(pki_path, type, group, derCert);
  if(result > 0)
  {
    if(derCert->data)
    {
      UASDK_Free(derCert->data);
    }
    if(derCert)
    {
      UASDK_Free(derCert);
    }
    return result;
  }

  *own_certificate_der = derCert;

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_own_certificate_private_key_handle(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    UA_UTF8_string_t* private_key_password,
    uintptr_t* private_key_handle)
{
  char file_path[MAX_PATH_LENGTH];
  const char* filename = 0;
  RSA* key = 0;
  UA_Status_t result = OpcUa_Good;

  if( (pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0)
  		|| (private_key_handle == 0) || (group == UA_CERTIFICATE_GROUP_INVALID)
      || (type < UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE) || (type > UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE)
      || (private_key_password == 0) || (private_key_password->data == 0) || (private_key_password->length <= 0) )
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  filename = filename_own_cert_private_key(type, group);
  if(!filename)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
  	goto clean_up;
  }

  key = get_private_key(file_path, private_key_password);
  if(!key)
  {
    result = OpcUa_BadUnexpectedError;
    goto clean_up;
  }

  *private_key_handle = (uintptr_t)key;

  clean_up:

  return result;
}

UA_Status_t UASecurity_get_private_key_handle(
  const UA_Byte_string_t* pkcs8_pem_private_key,
  UA_UTF8_string_t* private_key_password,
  uintptr_t* private_key_handle)
{
  unsigned char tempString[MAX_STRING_LENGTH];
  UA_Status_t status = OpcUa_Good;

  EVP_PKEY* evp_key = 0;
  RSA* rsa_key = 0;

  if ((pkcs8_pem_private_key == 0) || (pkcs8_pem_private_key->data == 0)
    || (private_key_password == 0) || (private_key_password->data == 0)
    || (private_key_handle == 0))
  {
    return OpcUa_BadInvalidArgument;
  }

  status = CopyUtf8StringToNullTerminatedString(private_key_password, tempString, MAX_STRING_LENGTH);
  if (status != OpcUa_Good)
  {
    goto clean_up;
  }

  BIO* bp = BIO_new_mem_buf((void*)pkcs8_pem_private_key->data, pkcs8_pem_private_key->length);
  if (bp == 0)
  {
    status = OpcUa_BadInternalError;
    goto clean_up;
  }

  if (!PEM_read_bio_PrivateKey(bp, &evp_key, NULL, tempString))
  {
    status = OpcUa_BadInternalError;
    goto clean_up;
  }

  if (evp_key)
  {
    rsa_key = EVP_PKEY_get1_RSA(evp_key);
  }

  clean_up:

  if (bp)
  {
    BIO_free(bp);
  }

  if (evp_key)
  {
    EVP_PKEY_free(evp_key);
  }

  if (rsa_key)
  {
    //Protect private key from timing attacks
    RSA_blinding_on(rsa_key, 0);
  }

  *private_key_handle = (uintptr_t)rsa_key;

  return status;
}

UA_Status_t get_stack_path(
		const UA_UTF8_string_t* pki_path,
		UA_CertificateGroup_t group,
		bool_t is_trusted_stack,
		char* certs_directory_name,
		char* crls_directory_name)
{
	char certs_native_directory[MAX_PATH_LENGTH];
	char crl_native_directory[MAX_PATH_LENGTH];
	UA_Status_t result = OpcUa_Good;

	switch(is_trusted_stack)
  {
  case TRUE:
  	result = get_directorypath(group, DIR_TYPE_TRUSTED, DIR_CERTS, certs_native_directory);
  	if(result != OpcUa_Good)
  	{
  		return result;
  	}
  	result = get_directorypath(group, DIR_TYPE_TRUSTED, DIR_CRL, crl_native_directory);
  	if(result != OpcUa_Good)
  	{
  		return result;
  	}
    break;

  case FALSE:
  	result = get_directorypath(group, DIR_TYPE_ISSUER, DIR_CERTS, certs_native_directory);
  	if(result != OpcUa_Good)
  	{
  		return result;
  	}
  	result = get_directorypath(group, DIR_TYPE_ISSUER, DIR_CRL, crl_native_directory);
  	if(result != OpcUa_Good)
  	{
  		return result;
  	}
    break;

  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = uasdk_add_pki_path(pki_path, certs_native_directory, certs_directory_name);
  if(result != OpcUa_Good)
  {
    return result;
  }

  result = uasdk_add_pki_path(pki_path, crl_native_directory, crls_directory_name);
  if(result != OpcUa_Good)
  {
    return result;
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_stacks(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_stack,
    uintptr_t* stack_handle,
    uintptr_t* crls_handle)
{
  STACK_OF(X509)* app_stack = 0;
  STACK_OF(X509_CRL)* app_crls = 0;
  char certs_directory_name[MAX_PATH_LENGTH];
  char crls_directory_name[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_BadInternalError;

  if ( (pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0)
  		|| (group == UA_CERTIFICATE_GROUP_INVALID) || (crls_handle == 0) || (stack_handle == 0) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = get_stack_path(pki_path, group, is_trusted_stack, certs_directory_name, crls_directory_name);
  if(result != OpcUa_Good)
  {
  	return result;
  }

  initialise_x509_stack(&app_stack);

  initialise_crl_stack(&app_crls);

  if(add_certs_to_stack(certs_directory_name, app_stack) != OpcUa_Good)
  {
    goto clean_up;
  }
  if(add_crls_to_stack(crls_directory_name, app_crls) != OpcUa_Good)
  {
    goto clean_up;
  }

  *stack_handle  = (uintptr_t) app_stack;
  *crls_handle = (uintptr_t) app_crls;

  result = OpcUa_Good;

  return result;

  clean_up:
  if(app_stack)
  {
    free_x509_stack(app_stack);
    UASDK_Free(app_stack);
  }
  if(app_crls)
  {
    free_crl_stack(app_crls);
    UASDK_Free(app_crls);
  }

  return result;
}

UA_Status_t UASecurity_get_trust_list(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_list,
    UA_Byte_string_t** certificates_der,
    uint32_t* no_of_certificates,
    UA_Byte_string_t** crls_der,
    uint32_t* no_of_crls)
{
  UA_Byte_string_t* der_ = 0;
  UA_Byte_string_t* crl_ = 0;
  char certs_directory_name[MAX_PATH_LENGTH];
  char crls_directory_name[MAX_PATH_LENGTH];
  uint32_t certs_to_read = 0;
  uint32_t crls_to_read = 0;
  UA_Status_t result = OpcUa_BadInternalError;

  if ( (pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0)
  		|| (group == UA_CERTIFICATE_GROUP_INVALID) || (certificates_der == 0) || (crls_der == 0) || (no_of_certificates == 0) || (no_of_crls == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *no_of_certificates = 0;
  *no_of_crls = 0;

  result = get_stack_path(pki_path, group, is_trusted_list, certs_directory_name, crls_directory_name);
  if(result != OpcUa_Good)
  {
  	return result;
  }

  result = no_of_files_in_directory( certs_directory_name, ".der", &certs_to_read);
  if(result != OpcUa_Good)
  {
    goto clean_up;
  }

  result = no_of_files_in_directory( crls_directory_name, ".crl", &crls_to_read);
  if(result != OpcUa_Good)
  {
    goto clean_up;
  }

  if(certs_to_read > 0)
  {
    der_ = UASDK_Malloc(certs_to_read * sizeof(UA_Byte_string_t));
    if(!der_)
    {
      result = OpcUa_BadOutOfMemory;
      goto clean_up;
    }

    result = read_files_from_directory(certs_directory_name, ".der", certs_to_read, der_, no_of_certificates);
    if(result != OpcUa_Good)
    {
      goto clean_up;
    }
  }

  if(crls_to_read > 0)
  {
    crl_ = UASDK_Malloc(crls_to_read * sizeof(UA_Byte_string_t));
    if(!crl_)
    {
      result = OpcUa_BadOutOfMemory;
      goto clean_up;
    }

    result = read_files_from_directory(crls_directory_name, ".crl", crls_to_read, crl_, no_of_crls);
    if(result != OpcUa_Good)
    {
      goto clean_up;
    }
  }

  *certificates_der = der_;
  *crls_der = crl_;
  der_ = 0;
  crl_ = 0;

  result = OpcUa_Good;

  clean_up:

  if(der_)
  {
    UASecurity_free_bytestrings(der_, *no_of_certificates);
  }
  if(crl_)
  {
    UASecurity_free_bytestrings(crl_, *no_of_crls);
  }

  return result;
}

UA_Status_t UASecurity_get_rejected_list(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    UA_Byte_string_t** rejected_list_der,
    uint32_t* no_of_certificates)
{
  UASDK_UNUSED(pki_path);
  UASDK_UNUSED(group);
  UASDK_UNUSED(rejected_list_der);
  UASDK_UNUSED(no_of_certificates);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

UA_Status_t UASecurity_add_certificate_to_trust_list(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_certificate,
    const UA_Byte_string_t* certificate_der)
{
  UASDK_UNUSED(pki_path);
  UASDK_UNUSED(group);
  UASDK_UNUSED(is_trusted_certificate);
  UASDK_UNUSED(certificate_der);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

UA_Status_t UASecurity_remove_certificate_from_trust_list(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    bool_t is_trusted_certificate,
    const UA_Byte_string_t* certificate_thumbprint)
{
  UASDK_UNUSED(pki_path);
  UASDK_UNUSED(group);
  UASDK_UNUSED(is_trusted_certificate);
  UASDK_UNUSED(certificate_thumbprint);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

UA_Status_t UASecurity_update_certificate(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    const UA_Byte_string_t* certificate_der,
    const UA_Byte_string_t* private_key_pem,
    const UA_Byte_string_t* issuer_certificates,
    uint32_t no_of_issuer_certificates)
{
  UASDK_UNUSED(pki_path);
  UASDK_UNUSED(type);
  UASDK_UNUSED(group);
  UASDK_UNUSED(certificate_der);
  UASDK_UNUSED(private_key_pem);
  UASDK_UNUSED(issuer_certificates);
  UASDK_UNUSED(no_of_issuer_certificates);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

UA_Status_t UASecurity_create_certificate_signing_request(
    UA_Certificate_Generation_Parameters_t* parameters,
    bool_t regeneratePrivateKey,
    UA_Byte_string_t** certificate_signing_request_der)
{
  UASDK_UNUSED(parameters);
  UASDK_UNUSED(regeneratePrivateKey);
  UASDK_UNUSED(certificate_signing_request_der);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
}

UA_Status_t UASecurity_free_certificate_handle(uintptr_t certificate_handle)
{
  X509* cert = 0;
  if(certificate_handle == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = (X509*) certificate_handle;
  X509_free(cert);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_certificate_der(UA_Byte_string_t* certificate_der)
{
  if((certificate_der == 0) || (certificate_der->data == 0) || (certificate_der->length <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UASDK_Free(certificate_der->data);
  UASDK_Free(certificate_der);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_private_key_handle(uintptr_t private_key_handle)
{
  RSA* key = 0;

  if(private_key_handle == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  key = (RSA*) private_key_handle;

  RSA_blinding_off(key);
  RSA_free(key);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_stacks(
    uintptr_t stack_handle,
    uintptr_t crls_handle)
{
  if( (stack_handle == 0) || (crls_handle == 0) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  free_x509_stack((STACK_OF(X509)*)stack_handle);
  free_crl_stack((STACK_OF(X509_CRL)*)crls_handle);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_bytestrings(
    UA_Byte_string_t* bytestrings,
    uint32_t no_of_elements)
{
  uint32_t count = 0;

  if((bytestrings == 0) || (no_of_elements == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  for(count = 0; count < no_of_elements; count++)
  {
    UASDK_Free(bytestrings[count].data);
  }
  UASDK_Free(bytestrings);

  return OpcUa_Good;
}

UA_Status_t UASecurity_certificate_generation_parameters_init(UA_Certificate_Generation_Parameters_t* parameters)
{
  if(parameters == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  parameters->type = UA_CERTIFICATE_TYPE_INVALID;
  parameters->group = UA_CERTIFICATE_GROUP_INVALID;
  parameters->private_key_bit_length = 1024;
  parameters->private_key_password.data = 0;
  parameters->private_key_password.length = 0;
  parameters->start_date = 0;
  parameters->end_date = 0;

  parameters->application_uri.data = 0;
  parameters->application_uri.length = 0;

  parameters->hostnames = 0;
  parameters->no_of_hostnames = 0;
  parameters->ip_addresses = 0;
  parameters->no_of_ip_addresses = 0;

  parameters->common_name.data = 0;
  parameters->common_name.length = 0;

  parameters->organisation.data = 0;
  parameters->organisation.length = 0;

  parameters->organisation_unit.data = 0;
  parameters->organisation_unit.length = 0;

  parameters->locality.data = 0;
  parameters->locality.length = 0;

  parameters->state.data = 0;
  parameters->state.length = 0;

  parameters->country.data = 0;
  parameters->country.length = 0;

  return OpcUa_Good;
}

UA_Status_t UASecurity_create_self_signed_certificate(const UA_Certificate_Generation_Parameters_t* parameters)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
	unsigned char tempString[MAX_STRING_LENGTH];

  const char* filename = 0;
  char* password = 0;
  RSA* rsa_keys = 0;
  X509* cert = 0;
  X509_NAME* subject = 0;
  EVP_PKEY* pkey = 0;
  X509_EXTENSION* subject_key_id = 0;
  X509_EXTENSION* authority_key_id = 0;
  X509_EXTENSION* basic_constraints = 0;
  X509_EXTENSION* key_usage = 0;
  X509_EXTENSION* extended_key_usage = 0;
  X509_EXTENSION* subject_alt_name = 0;
  X509V3_CTX ctx;
  FILE* fp = 0;
  UA_Status_t result = OpcUa_BadInternalError;
  UA_Status_t status = OpcUa_BadInternalError;

  if(check_certificate_generation_parameters(parameters) != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  //Generate keys
  rsa_keys = RSA_generate_key(parameters->private_key_bit_length, RSA_F4, 0, 0);
  if (rsa_keys == 0)
  {
    goto clean_up;
  }

  //Create new certificate
  cert = X509_new();
  if (!cert)
  {
    goto clean_up;
  }

  //Set version number (X509v3)
  if (!X509_set_version(cert, 2L))
  {
    goto clean_up;
  }

  //Set serial number using a long pseudo random number (not strictly compliant with the RFC)
  {
    long serial = 0;
    UA_Byte_string_t sn;
    sn.data = (uint8_t*)&serial;
    sn.max_length = sizeof(long);
    sn.length = 0;
    status = UASecurity_rand_pseudo_bytes(&sn);
    if (status)
    {
      result = status;
      goto clean_up;
    }
    if (serial < 0)
    {
      serial *= -1;
    }
    ASN1_INTEGER_set(X509_get_serialNumber(cert), serial);
  }

  //Set subject name
  subject = X509_NAME_new();
  if (!subject)
  {
    goto clean_up;
  }

  {
    const UA_UTF8_string_t* primary_host = 0;
    if (parameters->no_of_hostnames > 0)
    {
      primary_host = &parameters->hostnames[0];
    }
    else if (parameters->no_of_ip_addresses > 0)
    {
      primary_host = &parameters->ip_addresses[0];
    }
    if (!primary_host)
    {
      goto clean_up;
    }

    status = CopyUtf8StringToNullTerminatedString(primary_host, tempString, MAX_STRING_LENGTH);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }

    if (!X509_NAME_add_entry_by_txt(subject, "DC", MBSTRING_ASC, tempString, -1, -1, 0))
    {
      goto clean_up;
    }
  }

  {
    status = CopyUtf8StringToNullTerminatedString(&parameters->common_name, tempString, MAX_STRING_LENGTH);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }

    if (!X509_NAME_add_entry_by_txt(subject, "CN", MBSTRING_ASC, tempString, -1, -1, 0))
    {
      goto clean_up;
    }
  }

  {
    if(parameters->organisation.data)
    {
      status = CopyUtf8StringToNullTerminatedString(&parameters->organisation, tempString, MAX_STRING_LENGTH);
      if (status != OpcUa_Good)
      {
        result = status;
        goto clean_up;
      }

      if (!X509_NAME_add_entry_by_txt(subject, "O", MBSTRING_ASC, tempString, -1, -1, 0))
			{
				goto clean_up;
			}
		}
  }

  {
    if(parameters->organisation_unit.data)
    {
      status = CopyUtf8StringToNullTerminatedString(&parameters->organisation_unit, tempString, MAX_STRING_LENGTH);
      if (status != OpcUa_Good)
      {
        result = status;
        goto clean_up;
      }

			if (!X509_NAME_add_entry_by_txt(subject, "OU", MBSTRING_ASC, tempString, -1, -1, 0))
			{
				goto clean_up;
			}
    }
  }

  {
    if(parameters->locality.data)
    {
      status = CopyUtf8StringToNullTerminatedString(&parameters->locality, tempString, MAX_STRING_LENGTH);
      if (status != OpcUa_Good)
      {
        result = status;
        goto clean_up;
      }

			if (!X509_NAME_add_entry_by_txt(subject, "L", MBSTRING_ASC, tempString, -1, -1, 0))
			{
				goto clean_up;
			}
    }
  }

  {
    if(parameters->state.data)
    {
      status = CopyUtf8StringToNullTerminatedString(&parameters->state, tempString, MAX_STRING_LENGTH);
      if (status != OpcUa_Good)
      {
        result = status;
        goto clean_up;
      }

			if (!X509_NAME_add_entry_by_txt(subject, "ST", MBSTRING_ASC, tempString, -1, -1, 0))
			{
				goto clean_up;
			}
    }
  }

  {
    if(parameters->country.data)
    {
      status = CopyUtf8StringToNullTerminatedString(&parameters->country, tempString, MAX_STRING_LENGTH);
      if (status != OpcUa_Good)
      {
        result = status;
        goto clean_up;
      }

			if (!X509_NAME_add_entry_by_txt(subject, "C", MBSTRING_ASC, tempString, -1, -1, 0))
			{
				goto clean_up;
			}
    }
  }

  if (!X509_set_subject_name(cert, subject))
  {
    goto clean_up;
  }

  //Self signed cert so set issuer name to be the subject
  if (!X509_set_issuer_name(cert, subject))
  {
    goto clean_up;
  }

  //Set public key
  pkey = EVP_PKEY_new();
  if (!pkey)
  {
    goto clean_up;
  }
  if (!EVP_PKEY_set1_RSA(pkey, rsa_keys) || !pkey)
  {
    goto clean_up;
  }

  if (!X509_set_pubkey(cert, pkey))
  {
    goto clean_up;
  }

  //Set duration
  {
    time_t time;

    time = ((parameters->start_date / 1000000) / 10);
    time -= EPOCH_DIFF;
    if(!(X509_get_notBefore(cert) = ASN1_TIME_set(0, time)))
    {
      goto clean_up;
    }

    time = ((parameters->end_date / 1000000) / 10);
    time -= EPOCH_DIFF;
    if(!(X509_get_notAfter(cert) = ASN1_TIME_set(0, time)))
    {
      goto clean_up;
    }
  }

  //Prepare to add extensions
  X509V3_set_ctx(&ctx, cert, cert, 0, 0, 0);

  //Add extension (subject key identifier)
  subject_key_id = X509V3_EXT_conf_nid(0, &ctx, NID_subject_key_identifier, "hash");
  if (!subject_key_id)
  {
    goto clean_up;
  }
  if (!X509_add_ext(cert, subject_key_id, -1))
  {
    goto clean_up;
  }

  //Add extension (authority key identifier)
  authority_key_id = X509V3_EXT_conf_nid(0, &ctx, NID_authority_key_identifier, "keyid,issuer");
  if (!authority_key_id)
  {
    goto clean_up;
  }
  if (!X509_add_ext(cert, authority_key_id, -1))
  {
    goto clean_up;
  }

  //Add extension (basic constraints)
  basic_constraints = X509V3_EXT_conf_nid(0, &ctx, NID_basic_constraints, "critical, CA:FALSE");
  if (!basic_constraints)
  {
    goto clean_up;
  }
  if (!X509_add_ext(cert, basic_constraints, -1))
  {
    goto clean_up;
  }

  //Add extension (key usage)
  key_usage = X509V3_EXT_conf_nid(0, &ctx, NID_key_usage, "critical, digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment, keyCertSign");
  if (!key_usage)
  {
    goto clean_up;
  }
  if (!X509_add_ext(cert, key_usage, -1))
  {
    goto clean_up;
  }

  //Add extension (extended key usage)
  extended_key_usage = X509V3_EXT_conf_nid(0, &ctx, NID_ext_key_usage, "critical, serverAuth, clientAuth");
  if (!extended_key_usage)
  {
    goto clean_up;
  }
  if (!X509_add_ext(cert, extended_key_usage, -1))
  {
    goto clean_up;
  }

  //Add extension (subject alternative name)
  {
    char alt_name[SUBJECT_ALT_NAME_MAX_LEN] = "\0";

    if (parameters->no_of_hostnames > 0)
    {
      uint32_t i = 0;
      for (i = 0; i < parameters->no_of_hostnames; i++)
      {
        status = CopyUtf8StringToNullTerminatedString(&parameters->hostnames[i], tempString, MAX_STRING_LENGTH);
        if (status != OpcUa_Good)
        {
          result = status;
          goto clean_up;
        }
				UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, "DNS:", ua_strnlen("DNS:", SUBJECT_ALT_NAME_MAX_LEN));
				UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, (const char*) tempString, ua_strnlen( (const char*) tempString, MAX_STRING_LENGTH));
				UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, ", ", ua_strnlen(", ", SUBJECT_ALT_NAME_MAX_LEN));
      }
    }

    if (parameters->no_of_ip_addresses > 0)
    {
      uint32_t i = 0;
      for (i = 0; i < parameters->no_of_ip_addresses; i++)
      {
        status = CopyUtf8StringToNullTerminatedString(&parameters->ip_addresses[i], tempString, MAX_STRING_LENGTH);
        if (status != OpcUa_Good)
        {
          result = status;
          goto clean_up;
        }
				UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, "IP:", ua_strnlen("IP:", SUBJECT_ALT_NAME_MAX_LEN));
				UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, (const char*) tempString, ua_strnlen( (const char*) tempString, MAX_STRING_LENGTH));
				UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, ", ", ua_strnlen(", ", SUBJECT_ALT_NAME_MAX_LEN));
      }
    }
    status = CopyUtf8StringToNullTerminatedString(&parameters->application_uri, tempString, MAX_STRING_LENGTH);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }
		UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, "URI:", ua_strnlen("URI:", SUBJECT_ALT_NAME_MAX_LEN));
		UASDK_strncat(alt_name, SUBJECT_ALT_NAME_MAX_LEN, (const char*) tempString, ua_strnlen( (const char*) tempString, MAX_STRING_LENGTH));
    subject_alt_name = X509V3_EXT_conf_nid(0, &ctx, NID_subject_alt_name, alt_name);
    if (!subject_alt_name)
    {
      goto clean_up;
    }
    if (!X509_add_ext(cert, subject_alt_name, -1))
    {
      goto clean_up;
    }
  }


  //Sign the certificate
  {
    const EVP_MD* digest = 0;

    switch(parameters->type)
    {
      case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
        digest = EVP_sha1();
        break;

      case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
        digest = EVP_sha256();
        break;

      default:
        break;
    }

    if(!digest)
    {
      goto clean_up;
    }

    if(!X509_sign(cert, pkey, digest))
    {
      goto clean_up;
    }
  }
  {
  	char file_path[MAX_PATH_LENGTH];
		//Write the cert to the store
		filename = filename_own_cert(parameters->type, parameters->group);
		if(!filename)
		{
			result = OpcUa_BadInternalError;
			goto clean_up;
		}
		result = uasdk_add_pki_path(&parameters->pki_path, filename, file_path);
		if(result != OpcUa_Good)
		{
			result = OpcUa_BadInternalError;
			goto clean_up;
		}
		remove(file_path);

#ifdef _MSC_VER
		{
		  errno_t err = fopen_s(&fp, file_path, "wb");
		  if (err != 0)
		  {
				result = OpcUa_BadInternalError;
				goto clean_up;
		  }
		}
	#else
		fp = fopen(file_path, "w");
	#endif
		if (!fp)
		{
			goto clean_up;
		}
		if (!i2d_X509_fp(fp, cert))
		{
			goto clean_up;
		}
		fclose(fp);
		fp = 0;

		//Write the private key to the store
		filename = filename_own_cert_private_key(parameters->type, parameters->group);
		if(!filename)
		{
			result = OpcUa_BadInternalError;
			goto clean_up;
		}

		result = uasdk_add_pki_path(&parameters->pki_path, filename, file_path);
		if(result != OpcUa_Good)
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
		}
		remove(file_path);

#ifdef _MSC_VER
		{
		  errno_t err = fopen_s(&fp, file_path, "wb");
		  if (err != 0)
		  {
				goto clean_up;
	  	}
		}
	#else
		fp = fopen(file_path, "w");
	#endif
		if (!fp)
		{
			goto clean_up;
		}

		password = UASDK_Calloc(parameters->private_key_password.length + 1);
		if(!password)
		{
		  goto clean_up;
		}
		UASDK_memcpy(password, parameters->private_key_password.data, parameters->private_key_password.length);
		password[parameters->private_key_password.length] = '\0';

		if (!PEM_write_PKCS8PrivateKey(fp, pkey, EVP_des_ede3_cbc(), NULL, 0, NULL, (void*)password))
		{
			goto clean_up;
		}

  }
  result = OpcUa_Good;

  clean_up:
  if(password)
  {
    UASDK_Free(password);
  }
  if (fp)
  {
    fclose(fp);
  }
  if (pkey)
  {
    EVP_PKEY_free(pkey);
  }
  if (authority_key_id)
  {
    X509_EXTENSION_free(authority_key_id);
  }
  if (basic_constraints)
  {
    X509_EXTENSION_free(basic_constraints);
  }
  if (key_usage)
  {
    X509_EXTENSION_free(key_usage);
  }
  if (extended_key_usage)
  {
    X509_EXTENSION_free(extended_key_usage);
  }
  if (subject_alt_name)
  {
    X509_EXTENSION_free(subject_alt_name);
  }
  if (subject_key_id)
  {
    X509_EXTENSION_free(subject_key_id);
  }
  if (subject)
  {
    X509_NAME_free(subject);
  }
  if (cert)
  {
    X509_free(cert);
  }
  if (rsa_keys)
  {
    RSA_free(rsa_keys);
  }

  return result;
}

void create_store(const char* path, DirectoryType_t type)
{
  mode_t mode = S_IRWXU;
  char filepath[MAX_PATH_LENGTH];

  MKDIR(path, mode);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_CERTS);
  MKDIR(filepath, mode);

  switch(type)
  {
    case DIR_TYPE_OWN:
      snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_PRIVATE);
      MKDIR(filepath, mode);
      break;

    case DIR_TYPE_TRUSTED:
    case DIR_TYPE_ISSUER:
      snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_CRL);
      MKDIR(filepath, mode);
      break;

    default:
      break;
  }
}

void create_store_type(const char* path)
{
  mode_t mode = S_IRWXU;
  char filepath[MAX_PATH_LENGTH];

  MKDIR(path, mode);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_OWN_STORE);
  create_store(filepath, DIR_TYPE_OWN);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_TRUSTED_STORE);
  create_store(filepath, DIR_TYPE_TRUSTED);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_ISSUER_STORE);
  create_store(filepath, DIR_TYPE_ISSUER);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_REJECTED_STORE);
  create_store(filepath, DIR_TYPE_REJECTED);
}

UA_Status_t UASecurity_create_directory_stores(const UA_UTF8_string_t* pki_path)
{
  char filepath[MAX_PATH_LENGTH];
  char pkipath[MAX_PATH_LENGTH];
  struct stat s;
	mode_t mode = S_IRWXU;

  if((pki_path == 0) || (pki_path->length <= 0) || (pki_path->length >= MAX_PATH_LENGTH)|| (pki_path->data == 0))
  {
  	UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UASDK_memcpy(pkipath, pki_path->data, pki_path->length);
  pkipath[pki_path->length] = '\0';

  if(stat(pkipath, &s) != 0)
  {
  	UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  else
  {
  	if(!S_ISDIR(s.st_mode))
  	{
  		UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
   	}
  }

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", pkipath, UA_SECURITY_PATH_PKI);
  MKDIR(filepath, mode);
  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s/%s", pkipath, UA_SECURITY_PATH_PKI, UA_SECURITY_PATH_DEFAULT_APPLICATION_GROUP);
  create_store_type(filepath);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s/%s", pkipath, UA_SECURITY_PATH_PKI, UA_SECURITY_PATH_DEFAULT_USER_TOKEN_GROUP);
  create_store_type(filepath);

  return OpcUa_Good;
}

int64_t UASecurity_get_certificate_expiry_date(const UA_Byte_string_t* certDer)
{
  UA_Status_t result = OpcUa_Good;
  int64_t expiryDate = 0;
  X509* cert = 0;
  STACK_OF(X509)* chain_stack = 0;
  ASN1_TIME* time = 0;
  char buf[128];

  chain_stack = sk_X509_new_null();
  if (!chain_stack)
  {
	goto clean_up;
  }

  result = extract_certs_from_chain(certDer, &cert, chain_stack);
  if (result != OpcUa_Good)
  {
	goto clean_up;
  }

  time = X509_get_notAfter(cert);

  UASDK_memset(buf, 0, 128);
  UASDK_memcpy(buf, time->data, time->length);

  UASDK_TextToFileTime(buf, 2, &expiryDate);

  clean_up:

  if (chain_stack)
  {
    sk_X509_pop_free(chain_stack, X509_free);
  }

  if (cert)
  {
    X509_free(cert);
  }

  return expiryDate;
}

#else

/*
 * This line is just to avoid the pedantic warning
 * If security is disabled
 */
typedef int dummy;

#endif //(UA_INCLUDE_SECURITY > 0)
