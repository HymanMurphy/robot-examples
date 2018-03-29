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

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

#include "uasdk_default_build_config.h"

#if ((UASDK_INCLUDE_SECURITY > 0) && (UASDK_USE_MBEDTLS > 0))

#include <stdio.h>
#include <string.h>
#include "ua_security.h"
#include "opcua_status_codes.h"
#include "ua_system_calls.h"
#include "common_utilities_t.h"

/* 
   Check for POSIX. The sensible way to do this is to first check for a system 
   that you reasonably expect to support posix, then include unistd.h, then
   check the _POSIX_VERSION macro. Below, we assume that the simple presence
   of POSIX is sufficient. This may be optimistic.
*/
#if defined(__unix__) || defined(__linux__)
#include <unistd.h>

#if defined(_POSIX_VERSION)
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define OS_DIR DIR
#define OS_FILE FILE
#define OS_DIRENT struct dirent
#define os_mkdir(a,b) mkdir(a,b)
#define os_opendir(a) opendir(a)
#define os_readdir(a) readdir(a)
#define os_closedir(a) closedir(a)
#define os_stat(a, b) stat(a, b)
#define os_S_ISDIR(a) S_ISDIR(a)
#define os_fopen(a, b) fopen(a, b)
#define os_fclose(a) fclose(a)
#define os_fread(a, b, c, d) fread(a, b, c, d)
#define os_fwrite(a, b, c, d) fwrite(a, b, c, d)
#define os_remove(a) remove(a)
#endif /* defined(_POSIX_VERSION) */

#elif defined _WIN32
#include <sys/stat.h>
#include <dirent.h>
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

#define OS_DIR DIR
#define OS_FILE FILE
#define OS_DIRENT struct dirent
#define os_mkdir(a,b) win_mkdir(a)
#define os_opendir(a) opendir(a)
#define os_readdir(a) readdir(a)
#define os_closedir(a) closedir(a)
#define os_stat(a, b) stat(a, b)
#define os_S_ISDIR(a) S_ISDIR(a)
#define os_fclose(a) fclose(a)
#define os_fread(a, b, c, d) fread(a, b, c, d)
#define os_fwrite(a, b, c, d) fwrite(a, b, c, d)
#define os_remove(a) remove(a)
#define fileno _fileno
#define S_IRWXU 0

void win_mkdir(const char* path)
{
  int err = _mkdir(path);
  UASDK_UNUSED(err);
}

FILE* os_fopen(const char* filename, const char* mode)
{
	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, filename, mode);
	if (err != 0)
	{
		return NULL;
	}
	return fp;
}
#else
#include <mbedtlsos.h>
#endif

#include "mbedtls/aes.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/rsa.h"
#include "mbedtls/pk.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#include "mbedtls/platform.h"
#include "mbedtls/oid.h"
#include "mbedtls/asn1write.h"
#include "mbedtls/pkcs5.h"
#include "mbedtls/pem.h"
#include "mbedtls/base64.h"

#define UA_SECURITY_PATH_PKI "pki"
#define UA_SECURITY_PATH_DEFAULT_APPLICATION_GROUP "DefaultApplicationGroup"
#define UA_SECURITY_PATH_DEFAULT_USER_TOKEN_GROUP "DefaultUserTokenGroup"
#define UA_SECURITY_PATH_DEFAULT_HTTPS_GROUP "DefaultHttpsGroup"    /* Https is not supported now */

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

#define SHA1_LENGTH  20
#define SHA256_LENGTH  32
#define MAX_DIGEST_LENGTH  SHA256_LENGTH
#define MAX_PASSWORD_LENGTH 20
#define MAX_PATH_LENGTH 200
#define MAX_STRING_LENGTH 200

#define SHA1_HASH_LENGTH SHA1_LENGTH
#define SHA1_STRING_LENGTH 41

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

typedef struct uasdk_x509_crt
{
  mbedtls_x509_crt crt;
  mbedtls_x509_buf Authority_Key_id;         /* Authority Key Identifier - Added by Matrikon OPC  */
  mbedtls_x509_buf Subject_Key_id;        /* Subject Key Identifier - Added by Matrikon OPC */
} uasdk_x509_crt;

typedef struct CRL
{
  struct CRL* next;
  mbedtls_x509_crl* crl_parsed;
} CRL_t;

typedef struct CRLs
{
  struct CRL* first;
} CRLs_t;

typedef struct Cert
{
  struct Cert* next;
  uasdk_x509_crt* cert;
} Cert_t;

typedef struct Certs
{
  Cert_t* first;
} Certs_t;

const mbedtls_x509_crt_profile uasdk_x509_crt_profile_default =
{
    /* Hashes from SHA-1 and above */
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA1 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_RIPEMD160 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA224 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA256 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA384 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA512 ),
    0xFFFFFFF, /* Any PK alg    */
    0xFFFFFFF, /* Any curve     */
    1024,
};

const mbedtls_x509_crt_profile uasdk_x509_crt_profile_basic256sha256 =
{
    /* Only SHA-256 and above */
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA256 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA384 ) |
    MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA512 ),
    0xFFFFFFF, /* Any PK alg    */
    0xFFFFFFF, /* Any curve     */
    2048,
};

#ifndef MBEDTLS_FS_IO
static int mbedtls_pk_load_file( const char *path, unsigned char **buf, size_t *n )
{
    OS_FILE *f;
    long size = os_get_file_size((const char*)path);

    if( ( f = os_fopen( path, "r" ) ) == NULL )
        return( MBEDTLS_ERR_PK_FILE_IO_ERROR );

    *n = (size_t) size;

    if( *n + 1 == 0 ||
        ( *buf = mbedtls_calloc( 1, *n + 1 ) ) == NULL )
    {
      os_fclose( f );
        return( MBEDTLS_ERR_PK_ALLOC_FAILED );
    }

    if( os_fread( *buf, 1, *n, f ) != *n )
    {
      os_fclose( f );
        mbedtls_free( *buf );
        return( MBEDTLS_ERR_PK_FILE_IO_ERROR );
    }

    os_fclose( f );

    (*buf)[*n] = '\0';

    if( strstr( (const char *) *buf, "-----BEGIN " ) != NULL )
        ++*n;

    return( 0 );
}

#endif /* MBEDTLS_FS_IO */

/*
 * Macro to generate an internal function for oid_XXX_from_asn1() (used by
 * the other functions)
 */
#define FN_OID_TYPED_FROM_ASN1( TYPE_T, NAME, LIST )                        \
static const TYPE_T * oid_ ## NAME ## _from_asn1( const mbedtls_asn1_buf *oid )     \
{                                                                           \
    const TYPE_T *p = LIST;                                                 \
    const mbedtls_oid_descriptor_t *cur = (const mbedtls_oid_descriptor_t *) p;             \
    if( p == NULL || oid == NULL ) return( NULL );                          \
    while( cur->asn1 != NULL ) {                                            \
        if( cur->asn1_len == oid->len &&                                    \
            memcmp( cur->asn1, oid->p, oid->len ) == 0 ) {                  \
            return( p );                                                    \
        }                                                                   \
        p++;                                                                \
        cur = (const mbedtls_oid_descriptor_t *) p;                                 \
    }                                                                       \
    return( NULL );                                                         \
}

/*
 * Macro to generate a function for retrieving a single attribute from an
 * mbedtls_oid_descriptor_t wrapper.
 */
#define FN_OID_GET_ATTR1(FN_NAME, TYPE_T, TYPE_NAME, ATTR1_TYPE, ATTR1) \
int FN_NAME( const mbedtls_asn1_buf *oid, ATTR1_TYPE * ATTR1 )                  \
{                                                                       \
    const TYPE_T *data = oid_ ## TYPE_NAME ## _from_asn1( oid );        \
    if( data == NULL ) return( MBEDTLS_ERR_OID_NOT_FOUND );            \
    *ATTR1 = data->ATTR1;                                               \
    return( 0 );                                                        \
}
/*
 * Macro to automatically add the size of #define'd OIDs
 */
#define ADD_LEN(s)      s, MBEDTLS_OID_SIZE(s)


typedef struct {
    mbedtls_oid_descriptor_t    descriptor;
    int                 ext_type;
} uasdk_oid_x509_ext_t;

static const uasdk_oid_x509_ext_t uasdk_oid_x509_ext[] =
{
    {
        { ADD_LEN( MBEDTLS_OID_BASIC_CONSTRAINTS ),    "id-ce-basicConstraints",   "Basic Constraints" },
        MBEDTLS_X509_EXT_BASIC_CONSTRAINTS,
    },
    {
        { ADD_LEN( MBEDTLS_OID_KEY_USAGE ),            "id-ce-keyUsage",           "Key Usage" },
        MBEDTLS_X509_EXT_KEY_USAGE,
    },
    {
        { ADD_LEN( MBEDTLS_OID_EXTENDED_KEY_USAGE ),   "id-ce-keyUsage",           "Extended Key Usage" },
        MBEDTLS_X509_EXT_EXTENDED_KEY_USAGE,
    },
    {
        { ADD_LEN( MBEDTLS_OID_SUBJECT_ALT_NAME ),     "id-ce-subjectAltName",     "Subject Alt Name" },
        MBEDTLS_X509_EXT_SUBJECT_ALT_NAME,
    },
    {
        { ADD_LEN( MBEDTLS_OID_NS_CERT_TYPE ),         "id-netscape-certtype",     "Netscape Certificate Type" },
        MBEDTLS_X509_EXT_NS_CERT_TYPE,
    },
    /* Authority Key Identifier and Subject Key Identifier are added by Matrikon OPC */
    {
        { ADD_LEN( MBEDTLS_OID_AUTHORITY_KEY_IDENTIFIER ),         "id-ce-authorityKeyIdentifier",     "Authority Key Identifier" },
        MBEDTLS_X509_EXT_AUTHORITY_KEY_IDENTIFIER,
    },
    {
        { ADD_LEN( MBEDTLS_OID_SUBJECT_KEY_IDENTIFIER ),         "id-ce-subjectKeyIdentifier",     "Subject Key Identifier" },
        MBEDTLS_X509_EXT_SUBJECT_KEY_IDENTIFIER,
    },
    {
        { NULL, 0, NULL, NULL },
        0,
    },
};

FN_OID_TYPED_FROM_ASN1(uasdk_oid_x509_ext_t, x509_ext, uasdk_oid_x509_ext)
FN_OID_GET_ATTR1(uasdk_oid_get_x509_ext_type, uasdk_oid_x509_ext_t, x509_ext, int, ext_type)

static
int pkcs5_parse_pbkdf2_params( const mbedtls_asn1_buf *params,
                                      mbedtls_asn1_buf *salt, int *iterations,
                                      int *keylen, mbedtls_md_type_t *md_type )
{
    int ret;
    mbedtls_asn1_buf prf_alg_oid;
    unsigned char *p = params->p;
    const unsigned char *end = params->p + params->len;

    if( params->tag != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );
    /*
     *  PBKDF2-params ::= SEQUENCE {
     *    salt              OCTET STRING,
     *    iterationCount    INTEGER,
     *    keyLength         INTEGER OPTIONAL
     *    prf               AlgorithmIdentifier DEFAULT algid-hmacWithSHA1
     *  }
     *
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &salt->len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

    salt->p = p;
    p += salt->len;

    if( ( ret = mbedtls_asn1_get_int( &p, end, iterations ) ) != 0 )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

    if( p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_int( &p, end, keylen ) ) != 0 )
    {
        if( ret != MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );
    }

    if( p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_alg_null( &p, end, &prf_alg_oid ) ) != 0 )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

    if( MBEDTLS_OID_CMP( MBEDTLS_OID_HMAC_SHA1, &prf_alg_oid ) != 0 )
        return( MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE );

    *md_type = MBEDTLS_MD_SHA1;

    if( p != end )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

void uasdk_x509_crt_free(uasdk_x509_crt* uacrt)
{
  mbedtls_x509_crt_free(&(uacrt->crt));
  mbedtls_free(uacrt);
}

/*
 *  Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
 */
static int x509_get_version( unsigned char **p,
                             const unsigned char *end,
                             int *ver )
{
    int ret;
    size_t len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONTEXT_SPECIFIC | MBEDTLS_ASN1_CONSTRUCTED | 0 ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
        {
            *ver = 0;
            return( 0 );
        }

        return( ret );
    }

    end = *p + len;

    if( ( ret = mbedtls_asn1_get_int( p, end, ver ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_VERSION + ret );

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_VERSION +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

/*
 *  Validity ::= SEQUENCE {
 *       notBefore      Time,
 *       notAfter       Time }
 */
static int x509_get_dates( unsigned char **p,
                           const unsigned char *end,
                           mbedtls_x509_time *from,
                           mbedtls_x509_time *to )
{
    int ret;
    size_t len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_DATE + ret );

    end = *p + len;

    if( ( ret = mbedtls_x509_get_time( p, end, from ) ) != 0 )
        return( ret );

    if( ( ret = mbedtls_x509_get_time( p, end, to ) ) != 0 )
        return( ret );

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_DATE +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

/*
 * X.509 v2/v3 unique identifier (not parsed)
 */
static int x509_get_uid( unsigned char **p,
                         const unsigned char *end,
                         mbedtls_x509_buf *uid, int n )
{
    int ret;

    if( *p == end )
        return( 0 );

    uid->tag = **p;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &uid->len,
            MBEDTLS_ASN1_CONTEXT_SPECIFIC | MBEDTLS_ASN1_CONSTRUCTED | n ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( 0 );

        return( ret );
    }

    uid->p = *p;
    *p += uid->len;

    return( 0 );
}

static int x509_get_basic_constraints( unsigned char **p,
                                       const unsigned char *end,
                                       int *ca_istrue,
                                       int *max_pathlen )
{
    int ret;
    size_t len;

    /*
     * BasicConstraints ::= SEQUENCE {
     *      cA                      BOOLEAN DEFAULT FALSE,
     *      pathLenConstraint       INTEGER (0..MAX) OPTIONAL }
     */
    *ca_istrue = 0; /* DEFAULT FALSE */
    *max_pathlen = 0; /* endless */

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( *p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_bool( p, end, ca_istrue ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            ret = mbedtls_asn1_get_int( p, end, ca_istrue );

        if( ret != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        if( *ca_istrue != 0 )
            *ca_istrue = 1;
    }

    if( *p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_int( p, end, max_pathlen ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    (*max_pathlen)++;

    return( 0 );
}

static int x509_get_ns_cert_type( unsigned char **p,
                                       const unsigned char *end,
                                       unsigned char *ns_cert_type)
{
    int ret;
    mbedtls_x509_bitstring bs = { 0, 0, NULL };

    if( ( ret = mbedtls_asn1_get_bitstring( p, end, &bs ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( bs.len != 1 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_INVALID_LENGTH );

    /* Get actual bitstring */
    *ns_cert_type = *bs.p;
    return( 0 );
}

static int x509_get_key_usage( unsigned char **p,
                               const unsigned char *end,
                               unsigned int *key_usage)
{
    int ret;
    size_t i;
    mbedtls_x509_bitstring bs = { 0, 0, NULL };

    if( ( ret = mbedtls_asn1_get_bitstring( p, end, &bs ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( bs.len < 1 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_INVALID_LENGTH );

    /* Get actual bitstring */
    *key_usage = 0;
    for( i = 0; i < bs.len && i < sizeof( unsigned int ); i++ )
    {
        *key_usage |= (unsigned int) bs.p[i] << (8*i);
    }

    return( 0 );
}

/*
 * ExtKeyUsageSyntax ::= SEQUENCE SIZE (1..MAX) OF KeyPurposeId
 *
 * KeyPurposeId ::= OBJECT IDENTIFIER
 */
static int x509_get_ext_key_usage( unsigned char **p,
                               const unsigned char *end,
                               mbedtls_x509_sequence *ext_key_usage)
{
    int ret;

    if( ( ret = mbedtls_asn1_get_sequence_of( p, end, ext_key_usage, MBEDTLS_ASN1_OID ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    /* Sequence length must be >= 1 */
    if( ext_key_usage->buf.p == NULL )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_INVALID_LENGTH );

    return( 0 );
}

/*
 * SubjectAltName ::= GeneralNames
 *
 * GeneralNames ::= SEQUENCE SIZE (1..MAX) OF GeneralName
 *
 * GeneralName ::= CHOICE {
 *      otherName                       [0]     OtherName,
 *      rfc822Name                      [1]     IA5String,
 *      dNSName                         [2]     IA5String,
 *      x400Address                     [3]     ORAddress,
 *      directoryName                   [4]     Name,
 *      ediPartyName                    [5]     EDIPartyName,
 *      uniformResourceIdentifier       [6]     IA5String,
 *      iPAddress                       [7]     OCTET STRING,
 *      registeredID                    [8]     OBJECT IDENTIFIER }
 *
 * OtherName ::= SEQUENCE {
 *      type-id    OBJECT IDENTIFIER,
 *      value      [0] EXPLICIT ANY DEFINED BY type-id }
 *
 * EDIPartyName ::= SEQUENCE {
 *      nameAssigner            [0]     DirectoryString OPTIONAL,
 *      partyName               [1]     DirectoryString }
 *
 * NOTE: we only parse and use dNSName at this point.
 */
static int x509_get_subject_alt_name( unsigned char **p,
                                      const unsigned char *end,
                                      mbedtls_x509_sequence *subject_alt_name )
{
    int ret;
    size_t len, tag_len;
    mbedtls_asn1_buf *buf;
    unsigned char tag;
    mbedtls_asn1_sequence *cur = subject_alt_name;

    /* Get main sequence tag */
    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( *p + len != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    while( *p < end )
    {
        if( ( end - *p ) < 1 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_OUT_OF_DATA );

        tag = **p;
        (*p)++;
        if( ( ret = mbedtls_asn1_get_len( p, end, &tag_len ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        if( ( tag & MBEDTLS_ASN1_CONTEXT_SPECIFIC ) != MBEDTLS_ASN1_CONTEXT_SPECIFIC )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

        /* Allocate and assign next pointer */
        if( cur->buf.p != NULL )
        {
            if( cur->next != NULL )
                return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS );

            cur->next = mbedtls_calloc( 1, sizeof( mbedtls_asn1_sequence ) );

            if( cur->next == NULL )
                return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                        MBEDTLS_ERR_ASN1_ALLOC_FAILED );

            cur = cur->next;
        }

        buf = &(cur->buf);
        buf->tag = tag;
        buf->p = *p;
        buf->len = tag_len;
        *p += buf->len;
    }

    /* Set final sequence entry's next pointer to NULL */
    cur->next = NULL;

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

/*
 *    Added by Matrikon OPC
 *
 *    id-ce-subjectKeyIdentifier OBJECT IDENTIFIER ::=  { id-ce 14 }
 *    SubjectKeyIdentifier ::= KeyIdentifier
 *    KeyIdentifier ::= BIT STRING
 *
 */

static int x509_get_Subject_key_Identifier( unsigned char **p,
                         const unsigned char *end,
                         mbedtls_x509_buf *uid, int n )
{
    int ret;

    if( *p == end )
        return( 0 );

    uid->tag = **p;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &uid->len,  n ) ) != 0 )

    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( 0 );

        return( ret );
    }

    uid->p = *p;
    *p += uid->len;

    return( 0 );
}
/*
 *    Added by Matrikon OPC
 *
 *    AuthorityKeyIdentifier ::= SEQUENCE {
 *    keyIdentifier             [0] KeyIdentifier           OPTIONAL,
 *    authorityCertIssuer       [1] GeneralNames            OPTIONAL,
 *    authorityCertSerialNumber [2] CertificateSerialNumber OPTIONAL  }
 *
 *    KeyIdentifier ::= OCTET STRING
 *
 */

static int x509_get_Authority_key_Identifier( unsigned char **p,
                                      const unsigned char *end,
                                      mbedtls_x509_buf *AuthorityKey, int n )
{
    (void)n;
    int ret;
    size_t len, tag_len;
    unsigned char tag;

    /* Get main sequence tag */
    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( *p + len != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    while( *p < end )
    {
        if( ( end - *p ) < 1 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_OUT_OF_DATA );

        tag = **p;
        (*p)++;
        if( ( ret = mbedtls_asn1_get_len( p, end, &tag_len ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        if( ( tag & MBEDTLS_ASN1_CONTEXT_SPECIFIC ) != MBEDTLS_ASN1_CONTEXT_SPECIFIC )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

        /* Skip everything but KeyIdentifier */
        if( tag != ( MBEDTLS_ASN1_CONTEXT_SPECIFIC | 0 ) )
        {
            *p += tag_len;
            continue;
        }

        AuthorityKey->len = tag_len;
        AuthorityKey->p = *p;
        AuthorityKey->tag = tag;
        *p += tag_len;
    }

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

static int x509_get_crt_ext( unsigned char **p,
                             const unsigned char *end,
                             uasdk_x509_crt *uacrt )
{
    int ret;
    size_t len;
    unsigned char *end_ext_data, *end_ext_octet;
    mbedtls_x509_crt* crt = &(uacrt->crt);

    if( ( ret = mbedtls_x509_get_ext( p, end, &crt->v3_ext, 3 ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( 0 );

        return( ret );
    }

    while( *p < end )
    {
        /*
         * Extension  ::=  SEQUENCE  {
         *      extnID      OBJECT IDENTIFIER,
         *      critical    BOOLEAN DEFAULT FALSE,
         *      extnValue   OCTET STRING  }
         */
        mbedtls_x509_buf extn_oid = {0, 0, NULL};
        int is_critical = 0; /* DEFAULT FALSE */
        int ext_type = 0;

        if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
                MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        end_ext_data = *p + len;

        /* Get extension ID */
        extn_oid.tag = **p;

        if( ( ret = mbedtls_asn1_get_tag( p, end, &extn_oid.len, MBEDTLS_ASN1_OID ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        extn_oid.p = *p;
        *p += extn_oid.len;

        if( ( end - *p ) < 1 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_OUT_OF_DATA );

        /* Get optional critical */
        if( ( ret = mbedtls_asn1_get_bool( p, end_ext_data, &is_critical ) ) != 0 &&
            ( ret != MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ) )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        /* Data should be octet string type */
        if( ( ret = mbedtls_asn1_get_tag( p, end_ext_data, &len,
                MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        end_ext_octet = *p + len;

        if( end_ext_octet != end_ext_data )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

        /*
         * Detect supported extensions
         */
        ret = uasdk_oid_get_x509_ext_type( &extn_oid, &ext_type );

        if( ret != 0 )
        {
            /* No parser found, skip extension */
            *p = end_ext_octet;

#if !defined(MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION)
            if( is_critical )
            {
                /* Data is marked as critical: fail */
                return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                        MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );
            }
#endif
            continue;
        }

        /* Forbid repeated extensions */
        if( ( crt->ext_types & ext_type ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS );

        crt->ext_types |= ext_type;

        switch( ext_type )
        {
        case MBEDTLS_X509_EXT_BASIC_CONSTRAINTS:
            /* Parse basic constraints */
            if( ( ret = x509_get_basic_constraints( p, end_ext_octet,
                    &crt->ca_istrue, &crt->max_pathlen ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_KEY_USAGE:
            /* Parse key usage */
            if( ( ret = x509_get_key_usage( p, end_ext_octet,
                    &crt->key_usage ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_EXTENDED_KEY_USAGE:
            /* Parse extended key usage */
            if( ( ret = x509_get_ext_key_usage( p, end_ext_octet,
                    &crt->ext_key_usage ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_SUBJECT_ALT_NAME:
            /* Parse subject alt name */
            if( ( ret = x509_get_subject_alt_name( p, end_ext_octet,
                    &crt->subject_alt_names ) ) != 0 )
                return( ret );
            break;

        case MBEDTLS_X509_EXT_NS_CERT_TYPE:
            /* Parse netscape certificate type */
            if( ( ret = x509_get_ns_cert_type( p, end_ext_octet,
                    &crt->ns_cert_type ) ) != 0 )
                return( ret );
            break;
        case MBEDTLS_X509_EXT_AUTHORITY_KEY_IDENTIFIER: /* Added by Matrikon OPC */
            /* Parse AUTHORITY_KEY_IDENTIFIER */
            if( ( ret = x509_get_Authority_key_Identifier( p, end_ext_octet, &uacrt->Authority_Key_id,  MBEDTLS_ASN1_OCTET_STRING  ) ) != 0 )
                return( ret );
            break;
        case MBEDTLS_X509_EXT_SUBJECT_KEY_IDENTIFIER: /* Added by Matrikon OPC */
            /* Parse SUBJECT_KEY_IDENTIFIER */
          if( ( ret = x509_get_Subject_key_Identifier( p, end_ext_octet, &uacrt->Subject_Key_id,  MBEDTLS_ASN1_OCTET_STRING  ) ) != 0 )
                return( ret );
            break;

        default:
            return( MBEDTLS_ERR_X509_FEATURE_UNAVAILABLE );
        }
    }

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}

/*
 * Parse and fill a single X.509 certificate in DER format
 */
static int x509_crt_parse_der_core( uasdk_x509_crt *uacrt, const unsigned char *buf,
                                    size_t buflen )
{
    int ret;
    size_t len;
    unsigned char *p, *end, *crt_end;
    mbedtls_x509_buf sig_params1, sig_params2, sig_oid2;
    mbedtls_x509_crt* crt = &(uacrt->crt);

    memset( &sig_params1, 0, sizeof( mbedtls_x509_buf ) );
    memset( &sig_params2, 0, sizeof( mbedtls_x509_buf ) );
    memset( &sig_oid2, 0, sizeof( mbedtls_x509_buf ) );

    /*
     * Check for valid input
     */
    if( crt == NULL || buf == NULL || crt == NULL )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    p = mbedtls_calloc( 1, len = buflen );
    if( p == NULL )
        return( MBEDTLS_ERR_X509_ALLOC_FAILED );

    memcpy( p, buf, buflen );

    crt->raw.p = p;
    crt->raw.len = len;
    end = p + len;

    /*
     * Certificate  ::=  SEQUENCE  {
     *      tbsCertificate       TBSCertificate,
     *      signatureAlgorithm   AlgorithmIdentifier,
     *      signatureValue       BIT STRING  }
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT );
    }

    if( len > (size_t) ( end - p ) )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );
    }
    crt_end = p + len;

    /*
     * TBSCertificate  ::=  SEQUENCE  {
     */
    crt->tbs.p = p;

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT + ret );
    }

    end = p + len;
    crt->tbs.len = end - crt->tbs.p;

    /*
     * Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
     *
     * CertificateSerialNumber  ::=  INTEGER
     *
     * signature            AlgorithmIdentifier
     */
    if( ( ret = x509_get_version(  &p, end, &crt->version  ) ) != 0 ||
        ( ret = mbedtls_x509_get_serial(   &p, end, &crt->serial   ) ) != 0 ||
        ( ret = mbedtls_x509_get_alg(      &p, end, &crt->sig_oid,
                                            &sig_params1 ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    crt->version++;

    if( crt->version > 3 )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_UNKNOWN_VERSION );
    }

    if( ( ret = mbedtls_x509_get_sig_alg( &crt->sig_oid, &sig_params1,
                                  &crt->sig_md, &crt->sig_pk,
                                  &crt->sig_opts ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    /*
     * issuer               Name
     */
    crt->issuer_raw.p = p;

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT + ret );
    }

    if( ( ret = mbedtls_x509_get_name( &p, p + len, &crt->issuer ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    crt->issuer_raw.len = p - crt->issuer_raw.p;

    /*
     * Validity ::= SEQUENCE {
     *      notBefore      Time,
     *      notAfter       Time }
     *
     */
    if( ( ret = x509_get_dates( &p, end, &crt->valid_from,
                                         &crt->valid_to ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    /*
     * subject              Name
     */
    crt->subject_raw.p = p;

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT + ret );
    }

    if( len && ( ret = mbedtls_x509_get_name( &p, p + len, &crt->subject ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    crt->subject_raw.len = p - crt->subject_raw.p;

    /*
     * SubjectPublicKeyInfo
     */
    if( ( ret = mbedtls_pk_parse_subpubkey( &p, end, &crt->pk ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    /*
     *  issuerUniqueID  [1]  IMPLICIT UniqueIdentifier OPTIONAL,
     *                       -- If present, version shall be v2 or v3
     *  subjectUniqueID [2]  IMPLICIT UniqueIdentifier OPTIONAL,
     *                       -- If present, version shall be v2 or v3
     *  extensions      [3]  EXPLICIT Extensions OPTIONAL
     *                       -- If present, version shall be v3
     */
    if( crt->version == 2 || crt->version == 3 )
    {
        ret = x509_get_uid( &p, end, &crt->issuer_id,  1 );
        if( ret != 0 )
        {
            mbedtls_x509_crt_free( crt );
            return( ret );
        }
    }

    if( crt->version == 2 || crt->version == 3 )
    {
        ret = x509_get_uid( &p, end, &crt->subject_id,  2 );
        if( ret != 0 )
        {
            mbedtls_x509_crt_free( crt );
            return( ret );
        }
    }

#if !defined(MBEDTLS_X509_ALLOW_EXTENSIONS_NON_V3)
    if( crt->version == 3 )
#endif
    {
        ret = x509_get_crt_ext( &p, end, uacrt );
        if( ret != 0 )
        {
            mbedtls_x509_crt_free( crt );
            return( ret );
        }
    }

    if( p != end )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );
    }

    end = crt_end;

    /*
     *  }
     *  -- end of TBSCertificate
     *
     *  signatureAlgorithm   AlgorithmIdentifier,
     *  signatureValue       BIT STRING
     */
    if( ( ret = mbedtls_x509_get_alg( &p, end, &sig_oid2, &sig_params2 ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    if( crt->sig_oid.len != sig_oid2.len ||
        memcmp( crt->sig_oid.p, sig_oid2.p, crt->sig_oid.len ) != 0 ||
        sig_params1.len != sig_params2.len ||
        ( sig_params1.len != 0 &&
          memcmp( sig_params1.p, sig_params2.p, sig_params1.len ) != 0 ) )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_SIG_MISMATCH );
    }

    if( ( ret = mbedtls_x509_get_sig( &p, end, &crt->sig ) ) != 0 )
    {
        mbedtls_x509_crt_free( crt );
        return( ret );
    }

    if( p != end )
    {
        mbedtls_x509_crt_free( crt );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );
    }

    return( 0 );
}

static bool_t is_application_cert(UA_CertificateGroup_t group)
{
  return (group == UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP);
}

static UA_Status_t get_directorypath(UA_CertificateGroup_t group, DirectoryType_t directoryType, Directory_t directory, const char* dirpath)
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

  length = snprintf((char*)dirpath, MAX_PATH_LENGTH - 1, "%s/%s/%s/%s", pki, stores, store, dir);

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
  if ((length <= 0) || (length >= MAX_PATH_LENGTH))
  {
    return 0;
  }

  return (const char*)filepath;
}

static UA_Status_t uasdk_add_pki_path(const UA_UTF8_string_t* pki_path, const char* native_path, char* file_path)
{
	char pkipath[MAX_PATH_LENGTH];
  int length = 0;

  if (!pki_path || !native_path)
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

static const char* filename_app_cert_rsa_min(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_CERTS, UA_SECURITY_FILENAME_CERT_RSA_MIN);
}

static const char* filename_app_cert_rsa_sha256(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_CERTS, UA_SECURITY_FILENAME_CERT_RSA_SHA256);
}

static const char* filename_app_private_key_rsa_min(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_PRIVATE, UA_SECURITY_FILENAME_KEY_RSA_MIN);
}

static const char* filename_app_private_key_rsa_sha256(UA_CertificateGroup_t group)
{
  return get_filepath(group, DIR_TYPE_OWN, DIR_PRIVATE, UA_SECURITY_FILENAME_KEY_RSA_SHA256);
}

static UA_Status_t filename_app_cert(const UA_UTF8_string_t* pki_path, UA_CertificateGroup_t group, UA_CertificateType_t type, char* file_path)
{
  const char* filename = 0;
  UA_Status_t result = 0;

  switch(type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_min(group);
    break;

  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_sha256(group);
    break;

  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
  	return result;
  }

  return OpcUa_Good;
}

static UA_Status_t filename_app_cert_private_key(const UA_UTF8_string_t* pki_path, UA_CertificateGroup_t group, UA_CertificateType_t type, char* file_path)
{
  const char* filename = 0;
  UA_Status_t result = 0;
  switch(type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    filename = filename_app_private_key_rsa_min(group);
    break;

  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    filename = filename_app_private_key_rsa_sha256(group);
    break;

  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
  	return result;
  }

  return OpcUa_Good;
}

static UA_Status_t get_thumbprint(const UA_Byte_string_t* der, char* thumbprint, uint32_t thumbprint_max_length)
{
  UA_Status_t result = OpcUa_BadInternalError;

  if (!der || !der->data || (der->length <= 0) || !thumbprint || (thumbprint_max_length < SHA1_STRING_LENGTH))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  {
    uint8_t hash[SHA1_LENGTH];
    int i = 0;
    UA_Byte_string_t hash_ = { 0, SHA1_LENGTH, 0 };
    hash_.data = hash;
    result = UASecurity_digest(UA_DIGEST_SHA1, der, &hash_);
    if (result != OpcUa_Good)
    {
      goto clean_up;
    }

    for(i = 0; i < SHA1_LENGTH; i++)
    {
      char *l = &thumbprint[2 * i];

      if (!l)
      {
        result = OpcUa_BadUnexpectedError;
        goto clean_up;
      }

      snprintf(l, 3, "%02X", hash[i]);
    }

    result = OpcUa_Good;
  }

  clean_up:

  return result;
}

static const char* filename_rejected_cert(UA_CertificateGroup_t group, const UA_Byte_string_t* cert_der)
{
  static char filepath[MAX_PATH_LENGTH];
  UA_Status_t status = get_thumbprint(cert_der, filepath, SHA1_STRING_LENGTH);
  if (status != OpcUa_Good)
  {
    return 0;
  }
  snprintf(&filepath[SHA1_HASH_LENGTH * 2], 5, ".der");

  return get_filepath(group, DIR_TYPE_REJECTED, DIR_CERTS, filepath);
}

static UA_Status_t get_cert_from_bytestring(const UA_Byte_string_t* certificate, uasdk_x509_crt** cert)
{
  UA_Status_t result = OpcUa_BadInternalError;
  uasdk_x509_crt* temp = 0;
  int status = 0;

  if ((certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->length > certificate->max_length))
  {
    result = OpcUa_BadInvalidArgument;
    return result;
  }

  temp = (uasdk_x509_crt*) UASDK_Calloc(sizeof(uasdk_x509_crt));
  if (!temp)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  if((status = x509_crt_parse_der_core( temp, (const unsigned char*) certificate->data, (size_t) certificate->length )) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  *cert = temp;
  temp = 0;
  result = OpcUa_Good;

  clean_up:

  if(temp)
  {
    UASDK_Free(temp);
  }

  return result;
}

static UA_Status_t get_private_key(const char* filepath, UA_UTF8_string_t* private_key_password, mbedtls_pk_context* key)
{
  if (!private_key_password)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UA_Status_t result = OpcUa_Good;
  unsigned char* fileBuffer = 0;
  size_t fileBufferLen = 0;
  int  status = 0;

  if((status = mbedtls_pk_load_file( filepath, &fileBuffer, &fileBufferLen )) != 0 )
  {
    result = OpcUa_BadInternalError;
    fileBuffer = 0;
    fileBufferLen = 0;
    goto clean_up;
  }

  if((status = mbedtls_pk_parse_key( key, (const unsigned char*) fileBuffer,
   (size_t) fileBufferLen, (const unsigned char*) private_key_password->data, private_key_password->length )) != 0)
  {
    result = OpcUa_BadInternalError;
    mbedtls_pk_free( key );
    goto clean_up;
  }

  clean_up:

  if(fileBuffer)
  {
    mbedtls_free( fileBuffer );
  }

  return result;
}

void* mbebtls_UASDK_Calloc( size_t n, size_t size)
{
  return UASDK_Calloc( n * size );
}

static UA_Status_t get_der_from_file(const char* filepath, mbedtls_x509_crl** crl)
{
  UA_Status_t result = OpcUa_BadInvalidArgument;
  unsigned char* fileBuffer = 0;
  size_t fileBufferLen = 0;
  int status = 0;

  if((status = mbedtls_pk_load_file( filepath, &fileBuffer, &fileBufferLen )) != 0 )
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  *crl = mbedtls_calloc( 1, sizeof( mbedtls_x509_crl ) );
  if(*crl == 0)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  mbedtls_x509_crl_init( *crl );

  if(mbedtls_x509_crl_parse_der( *crl, fileBuffer, fileBufferLen ) != 0)
  {
    mbedtls_x509_crl_free( *crl );
    mbedtls_free(*crl);
    result = OpcUa_BadInvalidArgument;
	goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  if (fileBuffer)
  {
    mbedtls_free(fileBuffer);
  }

  return result;
}

static uasdk_x509_crt* get_cert(const char* filepath, bool_t get_der, UA_Byte_string_t* der_out)
{
  uasdk_x509_crt* cert_ = 0;
  size_t file_size = 0;
  uint8_t* fileBuffer = 0;
  uint32_t  status = 0;

  status = mbedtls_pk_load_file( (const char*)filepath, &fileBuffer, &file_size);
  if(status != 0)
  {
    goto clean_up;
  }
  if (der_out)
  {
    der_out->data = 0;
    der_out->length = der_out->max_length = 0;
  }

  {
    UA_Byte_string_t der;
    der.data = fileBuffer;
    fileBuffer = 0;
    der.length = der.max_length = (int32_t)file_size;

    if (get_cert_from_bytestring(&der, &cert_) != OpcUa_Good)
    {
      mbedtls_free(der.data);
      goto clean_up;
    }

    if (get_der && (der_out != 0))
    {
      *der_out = der;
    }
  }

  clean_up:

  if (fileBuffer)
  {
    mbedtls_free(fileBuffer);
  }

  return cert_;
}

static UA_Status_t get_crl(const char* filepath, mbedtls_x509_crl** crl)
{
  UA_Status_t result = OpcUa_BadInternalError;

  if (!crl)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }
  result = get_der_from_file(filepath, crl);
  if (result == OpcUa_Good)
  {
    return result;
  }

  clean_up:
  return result;
}

static uint32_t sk_X509_num(Certs_t* stack)
{
  uint32_t count = 0;

  if (stack)
  {
    Cert_t* current = stack->first;
    while (current)
    {
      count++;
      current = current->next;
    }
  }
  return count;
}

static void break_cert_links(  mbedtls_x509_crt* cert)
{
  mbedtls_x509_crt* current = cert;
  while (current)
  {
    mbedtls_x509_crt* next = current->next;
    current->next = 0;
    current = next;
  }
}

static void break_crl_links(mbedtls_x509_crl *crl)
{
  mbedtls_x509_crl* current = crl;
  while (current)
  {
    mbedtls_x509_crl* next = current->next;
    current->next = 0;
    current = next;
  }
}

static void free_x509_stack(Certs_t* stack, bool_t free_certs)
{
  if (stack)
  {
    Cert_t* current = stack->first;
    while (current)
    {
      Cert_t* next = current->next;
      if (current->cert && (free_certs == TRUE))
      {
        uasdk_x509_crt_free( current->cert );
      }
      UASDK_Free(current);
      current = next;
    }
    stack->first = 0;
  }
}

static void free_crl_stack(CRLs_t* stack, bool_t free_crls)
{
  if (stack)
  {
    CRL_t* current = stack->first;
    while (current)
    {
      CRL_t* next = current->next;
      if (current->crl_parsed  && (free_crls == TRUE))
      {
        mbedtls_x509_crl_free( current->crl_parsed );
        mbedtls_free(current->crl_parsed);
      }
      UASDK_Free(current);
      current = next;
    }
    stack->first = 0;
  }
}

static void initialise_x509_stack(Certs_t* stack)
{
  if (stack)
  {
    stack->first = 0;
  }
}

static void initialise_crl_stack(CRLs_t* stack)
{
  if (stack)
  {
    stack->first = 0;
  }
}

static void initialise_x509_stack_element(Cert_t* element)
{
  if (element)
  {
    element->cert = 0;
    element->next = 0;
  }
}

static void initialise_crl_stack_element(CRL_t* element)
{
  if (element)
  {
    element->crl_parsed = 0;
    element->next = 0;
  }
}

static UA_Status_t sk_X509_push(Certs_t* stack, uasdk_x509_crt* cert)
{
  UA_Status_t result = OpcUa_BadInternalError;
  Cert_t* last = 0;
  Cert_t* new_cert = 0;
  if (!stack || !cert)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  last = stack->first;
  if (last != 0 )
  {
    while (last->next)
    {
      last = last->next;
    }
  }

  new_cert =(Cert_t*) UASDK_Calloc(sizeof(Cert_t));
  if (!new_cert)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }
  if (last)
  {
    last->next = new_cert;
    last = last->next;
  }
  else
  {
    last = stack->first = new_cert;
  }
  initialise_x509_stack_element(last);

  last->cert = cert;
  result = OpcUa_Good;

  clean_up:

  return result;
}

static UA_Status_t sk_X509_push_from_stack(Certs_t* destination, Certs_t* source)
{
  UA_Status_t result = OpcUa_BadInternalError;

  if (!destination || !source)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }
  {
    Cert_t* next = source->first;
    while (next)
    {
      UA_Status_t status = sk_X509_push(destination, next->cert);
      if (status)
      {
        result = status;
        goto clean_up;
      }
      next = next->next;
    }
  }
  result = OpcUa_Good;
  clean_up:

  return result;
}

static UA_Status_t sk_X509_CRL_push(CRLs_t* stack, mbedtls_x509_crl* crl)
{
  UA_Status_t result = OpcUa_BadInternalError;
  CRL_t* last = 0;
  CRL_t* new_crl = 0;
  if (!stack || !crl )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  last = stack->first;
  if (last)
  {
    while (last->next)
    {
      last = last->next;
    }
  }

  new_crl =(CRL_t*) UASDK_Calloc(sizeof(CRL_t));
  if (!new_crl)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }
  if (last)
  {
    last->next = new_crl;
    last = last->next;
  }
  else
  {
    last = stack->first = new_crl;
  }
  initialise_crl_stack_element(last);

  last->crl_parsed = crl;
  result = OpcUa_Good;

  clean_up:

  return result;
}

static UA_Status_t sk_X509_CRL_wrap_push(CRLs_t* stack, CRL_t* add)
{
  UA_Status_t result = OpcUa_BadInternalError;

  if (!stack || !add )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  while (add)
  {
    result = sk_X509_CRL_push(stack, add->crl_parsed);
    if(result != OpcUa_Good)
    {
      break;
    }
    add = add->next;
  }

  return result;
}

/* TODO - update TagMask classification */
static UA_Status_t validate_subject_alternate_name_string(uasdk_x509_crt *cert, const UA_UTF8_string_t* san_string, int tagMask)
{
  UA_Status_t result = OpcUa_BadInternalError;
  mbedtls_x509_sequence *cur = 0;
  unsigned char temp[4];
  UA_UTF8_string_t sanString;

  UASDK_UNUSED(tagMask);

  if (!san_string || (san_string->length <= 0) || (!san_string->data) || (!cert))
  {
    result = OpcUa_BadInvalidArgument; 
    goto clean_up;
  }

  if (get_string_ipv4_to_ipv4octet(san_string, temp) == 0)
  {
    sanString.data = temp;
    sanString.length = 4;
  }
  else
  {
    sanString.data = san_string->data;
    sanString.length = san_string->length;
  }

  if (cert->crt.ext_types & MBEDTLS_X509_EXT_SUBJECT_ALT_NAME)
  {
    cur = &cert->crt.subject_alt_names;

    while (cur != NULL)
    {
      if (cur->buf.len == sanString.length &&
        UASDK_memcmp(sanString.data, cur->buf.p, sanString.length) == 0)
        break;
      cur = cur->next;
    }

    if (cur == 0)
    {
      result = OpcUa_BadCertificateInvalid;
      goto clean_up;
    }
    result = OpcUa_Good;
  }

clean_up:

  return result;
}

static UA_Status_t extract_certs_from_chain(const UA_Byte_string_t* certificate_chain, Certs_t* chain_stack)
{
  if (!certificate_chain)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UA_Status_t result = OpcUa_BadInternalError;
  uint32_t  status = 0;

  unsigned char* p = certificate_chain->data;
  const unsigned char* end = certificate_chain->data + certificate_chain->length;

  if ((certificate_chain == 0) || (certificate_chain->data == 0) || (certificate_chain->length <= 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  do
  {
    size_t len = 0;
    unsigned char *crt_end = 0, *crt_start = 0;
    crt_start = p;
    if( ( status = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
    }

    if( len > (size_t) ( end - p ) )
    {
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
    }
    crt_end = p + len;
    {
      size_t certlen = 0;
      uasdk_x509_crt *cert = 0;
      certlen = (size_t) (crt_end - crt_start);
      cert = mbedtls_calloc( 1, sizeof( uasdk_x509_crt ) );
      if( !cert )
      {
        free_x509_stack(chain_stack, TRUE);
        result = OpcUa_BadOutOfMemory;
        goto clean_up;
      }

      if ((status = x509_crt_parse_der_core( cert, crt_start, certlen )) != 0)
      {
        free_x509_stack(chain_stack, TRUE);
        uasdk_x509_crt_free( cert );
        result = OpcUa_BadInvalidArgument;
        goto clean_up;
      }

      sk_X509_push(chain_stack, cert);
    }
    p = crt_end;

  } while (p < end);

  result = OpcUa_Good;

  clean_up:

   return result;
}

static bool_t save_to_rejected_folder(UA_Status_t result)
{
  switch (result)
  {
   case OpcUa_BadCertificateTimeInvalid:
   case OpcUa_BadCertificateIssuerTimeInvalid:
   case OpcUa_BadCertificateIssuerRevocationUnknown:
   case OpcUa_BadCertificateUntrusted:
   case OpcUa_Good:
    return TRUE;

   default:
    return FALSE;
  }
  return FALSE; /* Not reachable */
}

static bool_t is_self_signed(uasdk_x509_crt* cert)
{
  if (cert)
  {
    if (cert->Subject_Key_id.len == cert->Authority_Key_id.len)
    {
      if (cert->Subject_Key_id.p && cert->Authority_Key_id.p)
      {
        return ( memcmp(cert->Subject_Key_id.p, cert->Authority_Key_id.p, cert->Subject_Key_id.len) == 0 );
      }
    }
  }
  return FALSE;
}

static UA_Status_t validate_extensions(uasdk_x509_crt* cert, const UA_Certificate_Validation_Parameters_t* parameters)
{
  UA_Status_t result = OpcUa_BadInternalError;
  uint32_t status = 0;
  uint32_t usage;
  char *ext_oid ;
  size_t ext_len = 0;

  /* Test key usage */
  usage = MBEDTLS_X509_KU_DIGITAL_SIGNATURE
      |MBEDTLS_X509_KU_NON_REPUDIATION
      |MBEDTLS_X509_KU_KEY_ENCIPHERMENT
      |MBEDTLS_X509_KU_DATA_ENCIPHERMENT;

  if( ( cert->crt.ext_types & MBEDTLS_X509_EXT_KEY_USAGE ) == 0 )
  {
    result = OpcUa_BadCertificateUseNotAllowed;
    goto clean_up;
  }

  if((status = mbedtls_x509_crt_check_key_usage( &cert->crt, usage )) != 0)
  {
    result = OpcUa_BadCertificateUseNotAllowed;
    goto clean_up;
  }

  if( ( cert->crt.ext_types & MBEDTLS_X509_EXT_EXTENDED_KEY_USAGE ) == 0 )
  {
    result = OpcUa_BadCertificateUseNotAllowed;
    goto clean_up;
  }

  if (parameters->validateExtensionsClient != FALSE)
  {
    ext_oid = MBEDTLS_OID_CLIENT_AUTH;
    ext_len = MBEDTLS_OID_SIZE(MBEDTLS_OID_CLIENT_AUTH);

    if ((mbedtls_x509_crt_check_extended_key_usage(&cert->crt, (const char*)ext_oid, ext_len)) != 0)
    {
      result = OpcUa_BadCertificateUseNotAllowed;
      goto clean_up;
    }
  }

  if (parameters->validateExtensionsServer != FALSE)
  {
    ext_oid = MBEDTLS_OID_SERVER_AUTH;
    ext_len = MBEDTLS_OID_SIZE(MBEDTLS_OID_SERVER_AUTH);

    if ((mbedtls_x509_crt_check_extended_key_usage(&cert->crt, (const char*)ext_oid, ext_len)) != 0)
    {
      result = OpcUa_BadCertificateUseNotAllowed;
      goto clean_up;
    }
  }

  /* Check for authority key identifier */
  if (!cert->Authority_Key_id.len && !is_self_signed(cert))
  {
    result = OpcUa_BadCertificateUseNotAllowed;
    goto clean_up;
  }

  if ((cert->crt.ext_types & MBEDTLS_X509_EXT_SUBJECT_ALT_NAME) == 0)
  {
    result = OpcUa_BadCertificateUseNotAllowed;
    goto clean_up;
  }

  bool_t supressHostName = (parameters->validation_option_bits & OB_SUPPRESS_HOSTNAME_INVALID);
  if (supressHostName == 0)
  {
    result = validate_subject_alternate_name_string(cert, &parameters->hostname, 0);
    if (result != OpcUa_Good)
    {
      result = OpcUa_BadCertificateHostNameInvalid;
      goto clean_up;
    }
  }

 result = OpcUa_Good;

 clean_up:

 return result;
}

static UA_Status_t extract_cert_from_chain(const UA_Byte_string_t* certificate_chain, UA_Byte_string_t* certificate)
{
  if (!certificate_chain)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UA_Status_t result = OpcUa_BadInternalError;
  int status = 0;
  size_t certlen = 0;
  unsigned char* p = certificate_chain->data;
  const unsigned char* end = certificate_chain->data + certificate_chain->length;

  if ((certificate_chain == 0) || (certificate_chain->data == 0) || (certificate_chain->length <= 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }
  {
    size_t len = 0;
    unsigned char *crt_end = 0, *crt_start = 0;
    crt_start = p;
    if( ( status = mbedtls_asn1_get_tag( &p, end, &len,
        MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
    }

    if( len > (size_t) ( end - p ) )
    {
      result = OpcUa_BadInvalidArgument;
      goto clean_up;
    }
    crt_end = p + len;
    certlen = (size_t) (crt_end - crt_start);
  }
  certificate->data = certificate_chain->data;
  certificate->length = certificate->max_length = (int32_t) certlen;
  result = OpcUa_Good;

  clean_up:

  return result;
}

static mbedtls_x509_crl* find_issuer_crl(mbedtls_x509_crt* cert, CRLs_t* crls)
{
  CRL_t* next = 0;

  if (!cert || !crls || !crls->first)
  {
    return 0;
  }

  next = crls->first;
  while (next)
  {
    mbedtls_x509_crl*  tempcrl = next->crl_parsed;
    unsigned char hash[MBEDTLS_MD_MAX_SIZE];

    if(( mbedtls_md( mbedtls_md_info_from_type( tempcrl->sig_md ), tempcrl->tbs.p, tempcrl->tbs.len, hash )) != 0 )
    {
      next = next->next;
      continue;
    }

    if( mbedtls_pk_verify_ext( tempcrl->sig_pk, tempcrl->sig_opts, &cert->pk,
       tempcrl->sig_md, hash, mbedtls_md_get_size( mbedtls_md_info_from_type( tempcrl->sig_md ) ),
       tempcrl->sig.p, tempcrl->sig.len ) == 0 )
    {
      return tempcrl;
    }
    next = next->next;
  }

  return 0;
}

static bool_t is_certificate_trusted(uasdk_x509_crt* cert, Certs_t* trusted_stack)
{
  Cert_t* next = 0;

  if (!cert || !trusted_stack)
  {
    return FALSE;
  }
  next = trusted_stack->first;

  while (next)
  {
  if(cert->crt.sig.len == next->cert->crt.sig.len)
  {
    if (cert->crt.sig.p && next->cert->crt.sig.p)
    {
      if (memcmp(cert->crt.sig.p, next->cert->crt.sig.p, cert->crt.sig.len) == 0)
      {
      return TRUE;
      }
    }
  }
  next = next->next;
  }

  return FALSE;
}

static Cert_t* find_issuer(uasdk_x509_crt* cert, Certs_t* combined_stack)
{
  Cert_t* next = 0;

  if (!cert || !combined_stack)
  {
    return FALSE;
  }
  next = combined_stack->first;
  while (next)
  {
    if (cert->Authority_Key_id.len == next->cert->Subject_Key_id.len)
    {
      if (cert->Authority_Key_id.p && next->cert->Subject_Key_id.p)
      {
        if (memcmp(cert->Authority_Key_id.p, next->cert->Subject_Key_id.p, cert->Authority_Key_id.len) == 0)
        {
          return next;
        }
      }
    }
    next = next->next;
  }
  return 0;
}

static UA_Status_t build_ordered_chain(uint32_t validation_option_bits,
								bool_t validate_trust,
                                Certs_t* trusted_stack,
                                Certs_t* issuer_stack,
                                Certs_t* chain_stack,
                                mbedtls_x509_crt** ca_cert,
                                CRLs_t* trusted_crls,
                                CRLs_t* issuer_crls,
                                mbedtls_x509_crl** cacrl)
{
  /* Build ordered chain, validate trust */

  UA_Status_t result = OpcUa_Good;
  UA_Status_t status = 0;
  Certs_t combined_stack;
  CRLs_t combined_crls;
  bool_t checkCrlOffLine = 0;
  bool_t supressRevocationUnknown = 0;
  bool_t is_trusted = !validate_trust;

  *cacrl = 0;
  initialise_x509_stack(&combined_stack);
  initialise_crl_stack(&combined_crls);

  checkCrlOffLine = (validation_option_bits & OB_CHECK_REVOCATION_STATUS_OFFLINE);
  supressRevocationUnknown = (validation_option_bits & OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN);

  if (
      ( (trusted_stack == 0)
      || (issuer_stack == 0))
      || (chain_stack == 0)
      || (chain_stack->first == 0)
      || (ca_cert == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }
  /* Copy all certs to combined stack */
  status = sk_X509_push_from_stack(&combined_stack, trusted_stack);
  if (status)
  {
    result = status;
    goto clean_up;
  }
  status = sk_X509_push_from_stack(&combined_stack, issuer_stack);
  if (status)
  {
    result = status;
    goto clean_up;
  }
  status = sk_X509_push_from_stack(&combined_stack, chain_stack);
  if (status)
  {
    result = status;
    goto clean_up;
  }

  if((trusted_crls != 0) && (trusted_crls->first != 0))
  {
    status = sk_X509_CRL_wrap_push(&combined_crls, trusted_crls->first);
    if (status)
    {
      result = status;
      goto clean_up;
    }
  }
  if((issuer_crls != 0) && (issuer_crls->first != 0))
  {
    status = sk_X509_CRL_wrap_push(&combined_crls, issuer_crls->first);
    if (status)
    {
      result = status;
      goto clean_up;
    }
  }

  {
  /* For each certificate, validate trust and find issuer. If self signed we have the complete
   * chain. Checking revocation status and updating missing CRL if required.
   */
   uasdk_x509_crt* next = 0;
   mbedtls_x509_crl* nextcrl = 0;
   next = chain_stack->first->cert;
   while (next)
   {
    /* Check trust */
    if (is_trusted == FALSE)
    {
      is_trusted = is_certificate_trusted( next, trusted_stack );
    }
    if (is_self_signed(next) == TRUE)
    {
      *ca_cert = &next->crt;
      next->crt.next = 0;
      break;
    }
    else
    {
      Cert_t* issuer = find_issuer( next , &combined_stack);
      if (issuer)
      {
        /* Check CRL */
        if (checkCrlOffLine != 0)
        {
          mbedtls_x509_crl* issuer_crl = 0;
          if (((issuer_crl = find_issuer_crl(&issuer->cert->crt, &combined_crls)) == 0) && (supressRevocationUnknown == FALSE))
          {
            result = OpcUa_BadCertificateRevocationUnknown;
            /*Keep checking trust for compliant error reporting*/
          }

          if(issuer_crl)
          {
            if(*cacrl == 0)
            {
              *cacrl = nextcrl = issuer_crl;
            }
            else
            {
              nextcrl->next = issuer_crl;
              nextcrl = nextcrl->next;
            }
          }
        }
        /* Repeat for issuer */
        next->crt.next = &issuer->cert->crt;
        next = issuer->cert;
      }
      else
      {
        result = OpcUa_BadSecurityChecksFailed;
        goto clean_up;
      }
    }
   }
  }

  if (!is_trusted)
  {
    result = OpcUa_BadCertificateUntrusted;
  }

  clean_up:

  free_x509_stack(&combined_stack, FALSE);
  free_crl_stack(&combined_crls, FALSE);

  return result;
}

static UA_Status_t validate_certificate(const UA_Certificate_Validation_Parameters_t* parameters, bool_t validate_trust, int32_t* rejected_certificate_length)
{
  UA_Status_t result = OpcUa_BadInternalError;
  UA_Status_t build_chain_result = OpcUa_BadInternalError;
  Certs_t* trusted_stack = 0;
  Certs_t* issuer_stack = 0;
  Certs_t chain_stack;
  mbedtls_x509_crt *cacert = 0;
  mbedtls_x509_crl *cacrl = 0;
  CRLs_t* trusted_crls = 0;
  CRLs_t* issuer_crls = 0;
  UA_Status_t verify_status = 0;
  bool_t is_trusted = FALSE;
  const mbedtls_x509_crt_profile* prolife = 0;

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
  initialise_x509_stack(&chain_stack);

  result = extract_certs_from_chain(&(parameters->certificate_chain), &chain_stack);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  trusted_stack = (Certs_t*) parameters->trusted_stack_handle;
  issuer_stack = (Certs_t*) parameters->issuer_stack_handle;
  trusted_crls = (CRLs_t*)parameters->trusted_crls_handle;
  issuer_crls = (CRLs_t*)parameters->issuer_crls_handle;

  {
    mbedtls_rsa_context *key = 0;
    key = mbedtls_pk_rsa( chain_stack.first->cert->crt.pk );

    if (!key)
    {
      result = OpcUa_BadSecurityChecksFailed;
      goto clean_up;
    }
    switch (parameters->policy)
    {
      case SECURITY_POLICY_BASIC128RSA15:
      case SECURITY_POLICY_BASIC256:
        prolife = &uasdk_x509_crt_profile_default;
        if ((key->len < 128) || (key->len > 256))
        {
          result = OpcUa_BadSecurityChecksFailed;
          goto clean_up;
        }
      break;
      case SECURITY_POLICY_BASIC256SHA256:
        prolife = &uasdk_x509_crt_profile_basic256sha256;
        if ((key->len < 256) || (key->len > 512))
        {
          result = OpcUa_BadSecurityChecksFailed;
          goto clean_up;
        }
      break;

     default:
       result = OpcUa_BadInvalidArgument;
       goto clean_up;

      break;
    }
  }
 
  build_chain_result = build_ordered_chain(parameters->validation_option_bits, validate_trust, trusted_stack, issuer_stack, &chain_stack, &cacert, trusted_crls, issuer_crls, &cacrl);
  if (build_chain_result != OpcUa_Good)
  {
    if (build_chain_result == OpcUa_BadCertificateUntrusted)
    {
      is_trusted = FALSE;
    }
    else
    {
      is_trusted = TRUE;
    }
  }
  else
  {
    is_trusted = TRUE;
  }

  {
    uint32_t flags = 0;
    char *cn = 0;
    bool_t supressUriMisMatch = (parameters->validation_option_bits & OB_SUPPRESS_URI_MISMATCH);
    if (supressUriMisMatch == 0)
    {
      if (parameters->uri.data != 0)
      {
        cn = UASDK_Malloc(parameters->uri.length + 1);
        if (!cn)
        {
          result = OpcUa_BadOutOfMemory;
          goto clean_up;
        }
        UASDK_memcpy(cn, parameters->uri.data, parameters->uri.length);
        cn[parameters->uri.length] = '\0';
      }
      else
      {
        result = OpcUa_BadCertificateInvalid;
        goto clean_up;
      }
    }

    verify_status = mbedtls_x509_crt_verify_with_profile(  &chain_stack.first->cert->crt, cacert, cacrl, prolife, cn, &flags, 0, 0 );

    if(cn)
    {
      UASDK_Free(cn);
    }

    if(flags)
    {
      bool_t supressExpiredError = (parameters->validation_option_bits & OB_SUPPRESS_CERTIFICATE_EXPIRED);

      uint32_t timeErrors = MBEDTLS_X509_BADCERT_EXPIRED | MBEDTLS_X509_BADCRL_EXPIRED | MBEDTLS_X509_BADCERT_FUTURE | MBEDTLS_X509_BADCRL_FUTURE;
      UA_Status_t veri_status = OpcUa_Good;
      if(flags & timeErrors)
      {
        if(supressExpiredError != 0)
        {
          flags &= ~timeErrors;
        }
        else
        {
          veri_status = OpcUa_BadCertificateTimeInvalid;
        }
      }

      if(flags & MBEDTLS_X509_BADCERT_REVOKED)
      {
        veri_status = OpcUa_BadCertificateRevoked;
      }

      if(!veri_status && flags)
      {
        veri_status = OpcUa_BadSecurityChecksFailed;
      }
      verify_status = veri_status;
    }
  }

  if (verify_status == OpcUa_Good)
  {
    if (is_application_cert(parameters->group)
          && (is_trusted == FALSE)
          && (parameters->trust_all_clients_when_the_trust_list_is_empty)
          && (sk_X509_num(trusted_stack) == 0))
      {
        is_trusted = TRUE;
        if (build_chain_result == OpcUa_BadCertificateUntrusted)
        {
          build_chain_result = OpcUa_Good;
        }
      }
      /* Check trust*/
    if (is_trusted)
    {
      if (is_application_cert(parameters->group))
      {
        /* Validate extensions */
        result = validate_extensions(chain_stack.first->cert, parameters);
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
    switch (build_chain_result)
    {
     case OpcUa_BadCertificateRevocationUnknown:
    result = OpcUa_BadCertificateRevocationUnknown;
    break;

   case OpcUa_BadCertificateIssuerRevocationUnknown:
    result = OpcUa_BadCertificateIssuerRevocationUnknown;
    break;
   case OpcUa_BadCertificateUntrusted:
    result = OpcUa_BadCertificateUntrusted;
    break;
   default:
    result = verify_status;
    break;
    }
  }

  if ((build_chain_result != OpcUa_Good) && (result == OpcUa_Good))
  {
    result = build_chain_result;
  }

  if (result != OpcUa_Good)
  {
    if (!parameters->do_not_save_rejected_certificates)
    {
      if (save_to_rejected_folder(result))
      {
        UA_Byte_string_t certificate = { 0, 0, 0 };
        UA_Status_t rslt = extract_cert_from_chain(&(parameters->certificate_chain), &certificate);
        if (rslt == OpcUa_Good)
        {
          *rejected_certificate_length = certificate.length;
        }
      }
    }
  }

  clean_up:

  break_cert_links(&chain_stack.first->cert->crt);
  free_x509_stack(&chain_stack, TRUE);
  if(cacrl)
  {
  break_crl_links(cacrl);
  }

  return result;
}

static UA_Status_t read_files_from_directory(const char* directory,
                                      const char* file_extension,
                                      uint32_t no_of_files_to_read,
                                      UA_Byte_string_t* der_out,
                                      uint32_t* no_of_files_read)
{
  OS_DIR* dir = 0;
  OS_DIRENT* de = 0;

  if((directory == 0) || (file_extension == 0) || (no_of_files_to_read > 0) || (der_out == 0) || (no_of_files_read == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *no_of_files_read = 0;

  dir = os_opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = os_readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, file_extension))
      {
        char temp_buf[MAX_PATH_LENGTH];
        int length = snprintf(temp_buf, MAX_PATH_LENGTH - 1, "%s/%s", directory, de->d_name);
        if ((length < 0) || (length >= MAX_PATH_LENGTH))
        {
          if (*no_of_files_read > 0)
          {
            UASecurity_free_bytestrings(der_out, *no_of_files_read);
          }
          UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
        }
        {
          size_t file_size = 0;
          unsigned char* fileBuffer = 0;
          uint32_t  status = 0;

          status = mbedtls_pk_load_file( (const char*)temp_buf, &fileBuffer, &file_size);
          if (status != 0)
          {
            if (*no_of_files_read > 0)
            {
              UASecurity_free_bytestrings(der_out, *no_of_files_read);
            }
            UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);

          }
          der_out[*no_of_files_read].data = fileBuffer;
          der_out[*no_of_files_read].length = der_out[*no_of_files_read].max_length = (int32_t)file_size;
        }

        (*no_of_files_read)++;

        if(no_of_files_to_read <= *no_of_files_read)
        {
          break;
        }
      }
    }

  } while (de != 0);

  os_closedir(dir);

  return OpcUa_Good;
}

static UA_Status_t no_of_files_in_directory(const char* directory, const char* file_extension, uint32_t* no_of_files)
{
  OS_DIR* dir = 0;
  OS_DIRENT* de = 0;

  if((directory == 0) || (file_extension == 0) || (no_of_files == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *no_of_files = 0;

  dir = os_opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = os_readdir(dir);
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

  os_closedir(dir);

  return OpcUa_Good;
}

static UA_Status_t add_certs_to_stack(const char* directory, Certs_t* stack)
{
  OS_DIR* dir = 0;
  OS_DIRENT* de = 0;

  dir = os_opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = os_readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, ".der"))
      {
        char temp_buf[MAX_PATH_LENGTH];
        uasdk_x509_crt* cert = 0;
        int length = snprintf(temp_buf, MAX_PATH_LENGTH - 1, "%s/%s", directory, de->d_name);
        if ((length < 0) || (length >= MAX_PATH_LENGTH))
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
        }

        cert = get_cert(temp_buf, FALSE, 0);
        if (cert)
        {
          sk_X509_push(stack, cert);
        }
      }
    }

  } while (de != 0);

  os_closedir(dir);

  return OpcUa_Good;
}

static UA_Status_t add_crls_to_stack(const char* directory, CRLs_t* stack)
{
  OS_DIR* dir = 0;
  OS_DIRENT* de = 0;
  UA_Status_t result = OpcUa_Good;
  dir = os_opendir(directory);
  if (!dir)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
  }

  do
  {
    de = os_readdir(dir);
    if (de)
    {
      if (!strncmp (de->d_name, ".", 1))
          continue;
      if (!strncmp (de->d_name, "..", 2))
          continue;

      if (strstr(de->d_name, ".crl"))
      {
        char temp_buf[MAX_PATH_LENGTH];
        mbedtls_x509_crl *crl = 0;
        int length = snprintf(temp_buf, MAX_PATH_LENGTH - 1, "%s/%s", directory, de->d_name);
        if ((length < 0) || (length >= MAX_PATH_LENGTH))
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
        }
        result = get_crl(temp_buf, &crl);
        if (result == OpcUa_Good)
        {
          result = sk_X509_CRL_push(stack, crl);
          if (result)
          {
            break;
          }
        }
        else
        {
          break;
        }
      }
    }

  } while (de != 0);

  os_closedir(dir);

  return OpcUa_Good;
}

UA_Status_t UASecurity_library_initialise(const UA_UTF8_string_t* pki_path )
{
  UASDK_UNUSED(pki_path);
  UA_Status_t status = OpcUa_Good;

#if !((defined _POSIX_VERSION) || (defined _WIN32 ))
  if (osdepTimeOpen() != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
#ifdef MBEDTLS_ENTROPY_HARDWARE_ALT
  if (osdepEntropyOpen() != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }
#endif
#endif

  if (mbedtls_platform_set_calloc_free(mbebtls_UASDK_Calloc, UASDK_Free) != 0)
  {
    status = OpcUa_BadInternalError;
  }

  return status;
}

void UASecurity_library_terminate(void)
{
#if !((defined _POSIX_VERSION) || (defined _WIN32 ))
  osdepTimeClose();
#ifdef MBEDTLS_ENTROPY_HARDWARE_ALT
  osdepEntropyClose();
#endif
#endif
}

UA_Status_t UASecurity_rand_bytes(UA_Byte_string_t* buf)
{
  UA_Status_t result = OpcUa_BadInternalError;
  int status = 0;
  if ((buf == 0) || (buf->data == 0) || (buf->max_length <= 0))
  {
    result = OpcUa_BadInvalidArgument;
  }
  else
  {
    mbedtls_entropy_context entropy;
    mbedtls_entropy_init( &entropy );

    buf->length = 0;
    status = mbedtls_entropy_func(&entropy , (unsigned char*)buf->data, (size_t)buf->max_length);
    if(status == 0)
    {
      buf->length = buf->max_length;
      result = OpcUa_Good;
    }
  }

  return result;
}

UA_Status_t UASecurity_rand_pseudo_bytes(UA_Byte_string_t* buf)
{
  return UASecurity_rand_bytes(buf);
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
  UASDK_UNUSED(type);
  const int BLOCK_SIZE = 16;
  unsigned char iv_temp[16];
  unsigned char* buff = 0;
  int status = 0;
  UA_Status_t result = OpcUa_BadInternalError;
  mbedtls_aes_context aes_ctx;

  mbedtls_aes_init( &aes_ctx );

  if ((iv == 0) || (iv->data == 0) || (iv->length != BLOCK_SIZE) || (iv->length > iv->max_length)
      || (key == 0) || (key->data == 0) || (key->length <= 0) || (key->length > key->max_length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->length <= 0) || (plaintext->length > plaintext->max_length)
      || (ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->max_length < plaintext->length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if ( (status = mbedtls_aes_setkey_enc( &aes_ctx, key->data,  8 * (key->length))) != 0 )
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  if ((plaintext->length % BLOCK_SIZE) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  UASDK_memcpy(iv_temp, iv->data, BLOCK_SIZE);

  if(!(buff = (unsigned char*) UASDK_Calloc( plaintext->length )))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  UASDK_memcpy( buff, plaintext->data, plaintext->length );

  if ((status = mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_ENCRYPT, plaintext->length, iv_temp, buff, ciphertext->data )) == 0)
  {
    ciphertext->length = plaintext->length;
    result = OpcUa_Good;
  }

  clean_up:

  if (buff)
  {
    UASDK_Free(buff);
    buff = 0;
  }
  return result;
}

UA_Status_t UASecurity_symmetric_decrypt(
    UA_Sym_Cipher_t type, const UA_Byte_string_t* iv, const UA_Byte_string_t* key,
    const UA_Byte_string_t* ciphertext, UA_Byte_string_t* plaintext)
{

  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */  
  const int BLOCK_SIZE = 16;

  UA_Status_t result = OpcUa_BadInternalError;
  unsigned char iv_temp[16];
  unsigned char* buff = 0;
  int status = 0;
  mbedtls_aes_context aes_ctx;

  UASDK_UNUSED(type);
 
  mbedtls_aes_init( &aes_ctx );

  if ((iv == 0) || (iv->data == 0) || (iv->length != BLOCK_SIZE) || (iv->length > iv->max_length)
      || (key == 0) || (key->data == 0) || (key->length <= 0) || (key->length > key->max_length)
      || (ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->length <= 0) || (ciphertext->length > ciphertext->max_length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->max_length < ciphertext->length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if ( (status = mbedtls_aes_setkey_dec( &aes_ctx, key->data,  8*(key->length))) != 0 )
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  if ((ciphertext->length % BLOCK_SIZE) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  UASDK_memcpy( iv_temp, iv->data, BLOCK_SIZE );

  if( !(buff = (unsigned char*)UASDK_Calloc(ciphertext->length)))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  UASDK_memcpy( buff, ciphertext->data, ciphertext->length );

  if ((status = mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_DECRYPT, ciphertext->length, iv_temp, buff, plaintext->data )) == 0)
  {
    plaintext->length = ciphertext->length;
    result =  OpcUa_Good;
  }

  clean_up:

  if (buff)
  {
    UASDK_Free(buff);
    buff = 0;
  }
  return result;
}

UA_Status_t UASecurity_digest(UA_Digest_t type, const UA_Byte_string_t* data, UA_Byte_string_t* hash)
{
  if ((data == 0) || (data->data == 0) || (data->length <= 0) || (data->length > data->max_length)
      || (hash == 0) || (hash->data == 0) || (hash->max_length < ((type == UA_DIGEST_SHA1) ? SHA1_LENGTH : SHA256_LENGTH)))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch (type)
  {
  case UA_DIGEST_SHA1:
    mbedtls_sha1( (const unsigned char*) data->data, (size_t) data->length, (unsigned char*) hash->data );
    hash->length = SHA1_LENGTH;
    break;

  case UA_DIGEST_SHA256:
    mbedtls_sha256( (const unsigned char*) data->data, (size_t) data->length, (unsigned char*) hash->data, 0 );
    hash->length = SHA256_LENGTH;
    break;
  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return OpcUa_Good;
}

static UA_Status_t ua_hmac(const unsigned char* key,
                           size_t key_length,
                           mbedtls_md_type_t md_type,
                           const unsigned char* data,
                           size_t data_length,
                           unsigned char* hash)
{
  UA_Status_t result = OpcUa_Good;
  mbedtls_md_context_t md_ctx;
  uint32_t status = 0;

  mbedtls_md_init( &md_ctx );

  if((status = mbedtls_md_setup( &md_ctx, mbedtls_md_info_from_type( md_type ) , 1 )) != 0)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  if((status = mbedtls_md_hmac_starts( &md_ctx, key, key_length )) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if((status = mbedtls_md_hmac_update( &md_ctx, data, data_length )) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if((status = mbedtls_md_hmac_finish( &md_ctx, hash )) != 0)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  clean_up:

  mbedtls_md_free( &md_ctx );

  return result;
}

UA_Status_t UASecurity_hmac(UA_Digest_t type, const UA_Byte_string_t* key, const UA_Byte_string_t* data, UA_Byte_string_t* hash)
{

  UA_Status_t  status = 0;
  mbedtls_md_type_t md_type = MBEDTLS_MD_NONE;
  size_t hashlen = 0;

  if ((key == 0) || (key->data == 0) || (key->length <= 0) || (key->length > key->max_length)
      || (data == 0) || (data->data == 0) || (data->length <= 0) || (data->length > data->max_length)
      || (hash == 0) || (hash->data == 0) || (hash->max_length < ((type == UA_DIGEST_SHA1) ? SHA1_LENGTH : SHA256_LENGTH)))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch (type)
  {
   case UA_DIGEST_SHA1:
    md_type = MBEDTLS_MD_SHA1;
    hashlen = SHA1_LENGTH;
    break;

   case UA_DIGEST_SHA256:
    md_type = MBEDTLS_MD_SHA256;
    hashlen = SHA256_LENGTH;
    break;

   default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (0 == (status = ua_hmac( (const unsigned char*) key->data, key->length, md_type, (const unsigned char*) data->data, data->length, hash->data)))
  {
    hash->length = (int32_t)hashlen;
    return OpcUa_Good;
  }

  UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
}

UA_Status_t UASecurity_p_sha(UA_Digest_t type,
                             const UA_Byte_string_t* secret,
                             const UA_Byte_string_t* seed,
                             UA_Byte_string_t* output)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  uint8_t A[MAX_DIGEST_LENGTH];
  size_t hash_length = 0;
  uint8_t* seed_buffer = 0;
  uint8_t* hash_buffer = 0;
  uint32_t i = 0;
  uint32_t no_of_bytes_required = 0;
  uint32_t no_of_iterations = 0;
  mbedtls_md_type_t md_type = MBEDTLS_MD_NONE;
  UA_Status_t  status = OpcUa_Good;

  if ((seed == 0) || (seed->data == 0) || (seed->length <= 0) || (seed->length > seed->max_length)
      || (secret == 0) || (secret->data == 0) || (secret->length <= 0) || (secret->length > secret->max_length)
      || (output == 0) || (output->data == 0) || (output->max_length <= 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch (type)
  {
  case UA_DIGEST_SHA1:
    hash_length = SHA1_LENGTH;
    md_type = MBEDTLS_MD_SHA1;
    break;

  case UA_DIGEST_SHA256:
    hash_length = SHA256_LENGTH;
    md_type = MBEDTLS_MD_SHA256;
    break;

  default:
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  /* A(0) = seed */
  /* A(n) = HMAC_SHAx(secret, A(n-1)) */

  no_of_bytes_required = output->max_length;
  no_of_iterations = (no_of_bytes_required / (uint32_t)hash_length);
  if (no_of_bytes_required % hash_length)
  {
    no_of_iterations++;
  }

  if(!(seed_buffer = (uint8_t*) UASDK_Calloc(hash_length + seed->length)))
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  /* Calculate A(1) */
  if (OpcUa_Good != (status = ua_hmac((const unsigned char*)secret->data, secret->length, md_type, (const unsigned char*)seed->data, seed->length, A)))
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  UASDK_memcpy(seed_buffer, A, hash_length);
  UASDK_memcpy(seed_buffer + hash_length, seed->data, seed->length);
  hash_buffer = (uint8_t*) UASDK_Calloc( no_of_iterations * hash_length );

  if (!hash_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  for (i = 0; i < no_of_iterations; i++)
  {
    /* Calculate P_SHAx(n) = HMAC_SHAx(secret, A(n-1) + seed) */
    if (OpcUa_Good != (status = ua_hmac((const unsigned char*) secret->data, secret->length, md_type, (const unsigned char*) seed_buffer, hash_length + seed->length, &hash_buffer[ i * hash_length ] )))
    {
      result = OpcUa_BadInternalError;
      goto clean_up;
    }

    /* Calculate A(n) = HMAC_SHAx(secret, A(n-1)) */
    if (OpcUa_Good != (status = ua_hmac((const unsigned char*)secret->data, secret->length, md_type, (const unsigned char*)seed_buffer, hash_length, seed_buffer )))
    {
      result = OpcUa_BadInternalError;
      goto clean_up;
    }
  }

  UASDK_memcpy(output->data, hash_buffer, output->max_length);
  output->length = output->max_length;

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

UA_Status_t UASecurity_asymmetric_encrypt(UA_Asym_Cipher_t type, const UA_Byte_string_t* receiver_chain,
    const UA_Byte_string_t* plaintext, UA_Byte_string_t* ciphertext)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  UA_Status_t result = OpcUa_BadInternalError;
  UA_Byte_string_t output = {0, 0, 0};
  mbedtls_rsa_context *rsakey = 0;
  mbedtls_entropy_context entropy;
  mbedtls_ctr_drbg_context ctr_drbg;
  uasdk_x509_crt* chain = 0;
  int status = 0;
  mbedtls_entropy_init( &entropy );

  if ((receiver_chain == 0) || (receiver_chain->data == 0) || (receiver_chain->length <= 0) || (receiver_chain->length > receiver_chain->max_length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->length <= 0) || (plaintext->length > plaintext->max_length)
      || (ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->max_length < plaintext->length))
  {
    result =  OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  chain = mbedtls_calloc(1, sizeof(uasdk_x509_crt));
  if(!chain)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if((status = x509_crt_parse_der_core( chain, (const unsigned char*) receiver_chain->data, (size_t) receiver_chain->length )) != 0)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  rsakey = mbedtls_pk_rsa( chain->crt.pk );

  if(!rsakey)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  switch(type)
  {
  case UA_ASYM_CIPHER_RSA_PKCS1_v1_5:
    mbedtls_rsa_set_padding( rsakey, MBEDTLS_RSA_PKCS_V15, MBEDTLS_MD_NONE );
    break;

  case UA_ASYM_CIPHER_RSA_OAEP:
    mbedtls_rsa_set_padding( rsakey, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA1 );
    break;

  default:
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if (ciphertext->max_length < (int32_t) rsakey->len)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  output.length = rsakey->len;
  output.max_length = ciphertext->max_length;
  output.data = (uint8_t*) UASDK_Calloc(ciphertext->max_length);
  if (!output.data )
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  if( (status = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy, 0, 0 )) != 0 )
  {
    goto clean_up;
  }

  if((status = mbedtls_rsa_pkcs1_encrypt( rsakey,  mbedtls_ctr_drbg_random, &ctr_drbg,
                         MBEDTLS_RSA_PUBLIC, (size_t)  plaintext->length,
                         (const unsigned char*) plaintext->data,
                         (unsigned char*) output.data )) == 0)
  {
    ciphertext->length = output.length;
    UASDK_memcpy(ciphertext->data, output.data, ciphertext->length);
    result = OpcUa_Good;
  }
  else
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  clean_up:

  if (output.data)
  {
    UASDK_Free(output.data);
  }

  uasdk_x509_crt_free( chain);

  return result;
}

UA_Status_t UASecurity_asymmetric_decrypt(
    UA_Asym_Cipher_t type,
    uintptr_t receiver_private_key_handle,
    const UA_Byte_string_t* ciphertext,
    UA_Byte_string_t* plaintext)
{
  UA_Status_t result = OpcUa_BadInternalError;
  UA_Byte_string_t output = { 0, 0, 0 };
  mbedtls_rsa_context rsakey;
  mbedtls_entropy_context entropy;
  mbedtls_ctr_drbg_context ctr_drbg;
  size_t plainTextLen = 0;
  uint32_t status = 0;

  mbedtls_entropy_init( &entropy );
  mbedtls_ctr_drbg_init( &ctr_drbg );
  mbedtls_rsa_init( &rsakey, MBEDTLS_RSA_PKCS_V15, MBEDTLS_MD_NONE );

  if ((ciphertext == 0) || (ciphertext->data == 0) || (ciphertext->length <= 0) || (ciphertext->length > ciphertext->max_length)
      || (plaintext == 0) || (plaintext->data == 0) || (plaintext->max_length <= 0) || (receiver_private_key_handle == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if(mbedtls_rsa_copy( &rsakey, (const mbedtls_rsa_context*) receiver_private_key_handle ) != 0)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch(type)
  {
  case UA_ASYM_CIPHER_RSA_PKCS1_v1_5:
    mbedtls_rsa_set_padding( &rsakey, MBEDTLS_RSA_PKCS_V15, MBEDTLS_MD_NONE );
    break;

  case UA_ASYM_CIPHER_RSA_OAEP:
    mbedtls_rsa_set_padding( &rsakey, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA1 );
    break;

  default:
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if (plaintext->max_length < (int32_t)rsakey.len)
  {
   result = OpcUa_BadInvalidArgument;
   goto clean_up;
  }

  output.length = 0;
  output.max_length = plaintext->max_length;
  output.data = (uint8_t*) UASDK_Calloc( plaintext->max_length );
  if (!output.data)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  if( ( status = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy, 0, 0 ) ) != 0 )
  {
    goto clean_up;
  }

  status = mbedtls_rsa_pkcs1_decrypt( &rsakey, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PRIVATE, &plainTextLen,
                         (const unsigned char*) ciphertext->data, (unsigned char*) output.data, output.max_length);
  if (status == 0)
  {
     plaintext->length = (int32_t)plainTextLen;
     UASDK_memcpy(plaintext->data, output.data, plaintext->length);
     result = OpcUa_Good;
  }
  else
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  clean_up:
  if (output.data)
  {
    UASDK_Free(output.data);
  }

  mbedtls_rsa_free( &rsakey );

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
  uint32_t hashLength = 20;
  UA_Status_t result = OpcUa_BadInternalError;
  uint8_t* computed_hash_buffer = 0;
  mbedtls_rsa_context *rsakey = 0;
  mbedtls_entropy_context entropy;
  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_md_type_t md_alg = MBEDTLS_MD_SHA1;
  uint32_t status = 0;

  mbedtls_entropy_init( &entropy );
  mbedtls_ctr_drbg_init( &ctr_drbg );

  if ((data == 0) || (data->data == 0) || (data->length <= 0) || (data->length > data->max_length)
      || (signature == 0) || (signature->data == 0) || (signature->max_length <= 0) ||(signee_private_key_handle == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  rsakey = (mbedtls_rsa_context*)signee_private_key_handle;

  switch (type)
  {
  case UA_DIGEST_SHA1:
    md_alg = MBEDTLS_MD_SHA1;
    hashLength = SHA1_LENGTH;
    break;

  case UA_DIGEST_SHA256:
    md_alg = MBEDTLS_MD_SHA256;
    hashLength = SHA256_LENGTH;
    break;

  default:
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if ((uint32_t)(signature->max_length) < rsakey->len)
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if( ( status = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy, 0, 0 ) ) != 0 )
  {
    goto clean_up;
  }

  computed_hash_buffer = (uint8_t*) UASDK_Calloc(hashLength);
  if(!computed_hash_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  {
    /* Compute hash */
    UA_Byte_string_t computed_hash = { 0, 0, 0 };
    computed_hash.max_length = hashLength;
    computed_hash.data = computed_hash_buffer;
    status = UASecurity_digest(type, data, &computed_hash);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }
  }
  {
    if((status = mbedtls_rsa_pkcs1_sign( rsakey, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PRIVATE, md_alg, 0,
            computed_hash_buffer, (unsigned char*) signature->data )) == 0)
    {
      signature->length = (int32_t)rsakey->len;
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

UA_Status_t UASecurity_asymmetric_verify(UA_Digest_t type, const UA_Byte_string_t* sender_chain,
    const UA_Byte_string_t* data, const UA_Byte_string_t* signature)
{
  /* While goto in general is an undesirable keyword goto is used in this function for resource clean up purposes
   * to avoid large nested if statements.
   */
  uint32_t hashLength = 20;
  UA_Status_t result = OpcUa_BadInternalError;
  uint8_t* computed_hash_buffer = 0;
  uasdk_x509_crt* chain = 0;
  mbedtls_rsa_context *rsakey = 0;
  mbedtls_md_type_t md_alg = MBEDTLS_MD_SHA1;
  uint32_t status = 0;

  if ((data == 0) || (data->data == 0) || (data->length <= 0)  || (data->length > data->max_length)
      || (signature == 0) || (signature->data == 0) || (signature->length <= 0) || (signature->length > signature->max_length)
      || (sender_chain == 0) || (sender_chain->data == 0) || (sender_chain->length <= 0) || (sender_chain->length > sender_chain->max_length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch (type)
  {
   case UA_DIGEST_SHA1:
    md_alg = MBEDTLS_MD_SHA1;
    hashLength = SHA1_LENGTH;
    break;

   case UA_DIGEST_SHA256:
    md_alg = MBEDTLS_MD_SHA256;
    hashLength = SHA256_LENGTH;
    break;

   default:
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  chain = mbedtls_calloc(1, sizeof(uasdk_x509_crt));
  if(!chain)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if((status = x509_crt_parse_der_core( chain, (const unsigned char*) sender_chain->data, (size_t) sender_chain->length )) != 0)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  rsakey = mbedtls_pk_rsa( chain->crt.pk );
  if(!rsakey)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }

  computed_hash_buffer = (uint8_t*) UASDK_Calloc(hashLength);
  if(!computed_hash_buffer)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }
  {
    /* Compute hash */
    UA_Byte_string_t computed_data = { 0, 0, 0 };
    computed_data.max_length = hashLength;
    computed_data.data = computed_hash_buffer;
    status = UASecurity_digest(type, data, &computed_data);
    if (status != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }
  }

  {
    if((status = mbedtls_rsa_pkcs1_verify( rsakey, 0, 0, MBEDTLS_RSA_PUBLIC, md_alg, 0,
            computed_hash_buffer, (unsigned char*) signature->data )) == 0)
    {
      result = OpcUa_Good;
    }
    else
    {
      result = OpcUa_BadUnexpectedError;
      goto clean_up;
    }
  }

  clean_up:

  if(computed_hash_buffer)
  {
    UASDK_Free(computed_hash_buffer);
    computed_hash_buffer = 0;
  }

  uasdk_x509_crt_free( chain);

  return result;
}

UA_Status_t UASecurity_certificate_validate(
    const UA_Certificate_Validation_Parameters_t* parameters,
		bool_t validate_trust,
    int32_t* rejected_certificate_length)
{
  return validate_certificate( parameters, validate_trust, rejected_certificate_length);
}

UA_Status_t UASecurity_certificate_validation_parameters_init(UA_Certificate_Validation_Parameters_t* parameters)
{
  if(parameters == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  parameters->trusted_stack_handle = 0;
  parameters->issuer_stack_handle = 0;
  parameters->trusted_crls_handle = 0;
  parameters->issuer_crls_handle = 0;

  parameters->group = UA_CERTIFICATE_GROUP_INVALID;
  parameters->policy = SECURITY_POLICY_INVALID;
  parameters->type = UA_CERTIFICATE_TYPE_INVALID;

  parameters->certificate_chain.data = 0;
  parameters->certificate_chain.length = 0;
  parameters->certificate_chain.max_length = 0;

  parameters->hostname.data = 0;
  parameters->hostname.length = 0;

  parameters->uri.data = 0;
  parameters->uri.length = 0;

  parameters->do_not_save_rejected_certificates = TRUE;
  parameters->trust_all_clients_when_the_trust_list_is_empty = FALSE;

  parameters->validateExtensionsServer = FALSE;
  parameters->validateExtensionsClient = FALSE;

  return OpcUa_Good;
}

UA_Status_t UASecurity_save_cert_to_rejected_folder(
	  const UA_UTF8_string_t* pki_path,
    UA_CertificateGroup_t group,
    const UA_Byte_string_t* certificate)
{
  OS_FILE *f;
  UA_Status_t result = OpcUa_Good;
  const char* filename = 0;
  char file_path[MAX_PATH_LENGTH];

  if((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0)
  		|| (certificate == 0) || (certificate->data == 0)
      || (certificate->length > certificate->max_length) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  filename = filename_rejected_cert(group, certificate);
  if(!filename)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  os_remove(file_path);
  f = os_fopen(file_path, "wb");
  if (!f)
  {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  if( os_fwrite( certificate->data, 1, certificate->length, f ) != certificate->length )
  {
    result = OpcUa_BadInternalError;
  }
  os_fclose( f );

  return result;
}

UA_Status_t validate_san(const UA_Byte_string_t* certificate, const UA_UTF8_string_t* san, int tagMask)
{
  UA_Status_t result = OpcUa_BadInternalError;
  uasdk_x509_crt *cert = 0;

  if (!san || (san->length <= 0) || (!san->data)
    || (certificate == 0) || (certificate->data == 0) || (certificate->length <= 0) || (certificate->length > certificate->max_length))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if ((get_cert_from_bytestring(certificate, &cert)) != OpcUa_Good)
  {
    result = OpcUa_BadCertificateInvalid;
    goto clean_up;
  }

  result = validate_subject_alternate_name_string(cert, san, tagMask);

clean_up:

  if (cert)
  {
    uasdk_x509_crt_free(cert);
    cert = 0;
  }

  return result;
}

UA_Status_t UASecurity_validate_uri(const UA_Byte_string_t* certificate, const UA_UTF8_string_t* uri)
{
  int tagMask = 0;
  UA_Status_t status = validate_san(certificate, uri, tagMask);
  if ((status != OpcUa_Good) && (status != OpcUa_BadOutOfMemory))
  {
    return OpcUa_BadCertificateUriInvalid;
  }

  return status;
}

UA_Status_t UASecurity_validate_hostname(const UA_Byte_string_t* certificate, const UA_UTF8_string_t* hostname)
{
  int tagMask = 0;
  UA_Status_t status = validate_san(certificate, hostname, tagMask);
  if ((status != OpcUa_Good) && (status != OpcUa_BadOutOfMemory))
  {
    return OpcUa_BadCertificateHostNameInvalid;
  }

  return status;
}

UA_Status_t UASecurity_get_certificate_key_size(
    uintptr_t certificate_handle,
    uint32_t* key_size_in_bytes)
{

  uasdk_x509_crt* cert = 0;
  mbedtls_rsa_context *key = 0;

  if ((certificate_handle == 0) || (key_size_in_bytes == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  cert = (uasdk_x509_crt*)certificate_handle;

  key = mbedtls_pk_rsa( cert->crt.pk );

  if (!key)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *key_size_in_bytes = (int32_t)key->len;

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_der_certificate_key_size(
    const UA_Byte_string_t* certificate,
    uint32_t* key_size_in_bytes)
{
  uasdk_x509_crt* cert = 0;
  mbedtls_rsa_context* key = 0;
  UA_Status_t result = OpcUa_BadUnexpectedError;
  UA_Status_t status = OpcUa_Good;

  if ((certificate == 0) || (certificate->data == 0) || (certificate->length <= 0)
      || (certificate->length > certificate->max_length) || (key_size_in_bytes == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  status = get_cert_from_bytestring(certificate, &cert);
  if (status || (cert == 0))
  {
    result = status;
    goto clean_up;
  }

  key = mbedtls_pk_rsa(cert->crt.pk );
  if (!key)
  {
    result = OpcUa_BadUnexpectedError;
    goto clean_up;
  }

  *key_size_in_bytes = (int32_t)key->len;
  result = OpcUa_Good;

  clean_up:
  if (cert)
  {
    uasdk_x509_crt_free(cert);
  }

  return result;
}

UA_Status_t UASecurity_get_certificate_max_plaintext_size(
    UA_Asym_Cipher_t type,
    uintptr_t certificate_handle,
    uint32_t* max_plaintext_size)
{
  uasdk_x509_crt* cert = 0;
  mbedtls_rsa_context* key = 0;
  uint32_t key_size_in_bytes = 0;

  if ((certificate_handle == 0) || (max_plaintext_size == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = (uasdk_x509_crt*) certificate_handle;

  key = mbedtls_pk_rsa(cert->crt.pk );

  if (!key)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  key_size_in_bytes = (int32_t)key->len;

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
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_der_certificate_max_plaintext_size(
    UA_Asym_Cipher_t type,
    const UA_Byte_string_t* certificate,
    uint32_t* max_plaintext_size)
{
  uasdk_x509_crt* cert = 0;
  UA_Status_t result = OpcUa_BadUnexpectedError;

  if((certificate == 0) || (certificate->data == 0) || (certificate->length <= 0)
      || (certificate->length > certificate->max_length) || (max_plaintext_size == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  result = get_cert_from_bytestring(certificate, &cert);
  if (result || (cert == 0))
  {
    goto clean_up;
  }

  result = UASecurity_get_certificate_max_plaintext_size(type, (uintptr_t) cert, max_plaintext_size);

  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  result = OpcUa_Good;

  clean_up:

  if (cert)
  {
    uasdk_x509_crt_free(cert);
  }

  return result;
}

UA_Status_t UASecurity_certificate_to_der(
    uintptr_t certificate_handle,
    UA_Byte_string_t** certificate_der)
{
	uasdk_x509_crt* cert = 0;
  UA_Byte_string_t* der = 0;
  uint8_t* der_ = 0;

  if((certificate_handle == 0) || (certificate_der == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  cert = (uasdk_x509_crt*) certificate_handle;

  der = (UA_Byte_string_t*) UASDK_Malloc(sizeof(UA_Byte_string_t));
  if(!der)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  der->length = der->max_length = (int32_t)cert->crt.raw.len;

  der_ = (uint8_t*) UASDK_Malloc(der->length + 1);
  if(!der)
  {
    UASDK_Free(der);
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  UASDK_memcpy(der_, cert->crt.raw.p, der->length );

  der->data = der_;

  *certificate_der = der;

  return OpcUa_Good;
}

UA_Status_t UASecurity_der_to_certificate(
    UA_Byte_string_t* certificate_der,
    uintptr_t* certificate_handle)
{
	uasdk_x509_crt *cert = 0;
  UA_Status_t result = OpcUa_Good;
  uint32_t  status = 0;

  if ((certificate_der == 0) || (certificate_der->data == 0) || (certificate_der->length <= 0)
      || (certificate_der->length > certificate_der->max_length) || (certificate_handle == 0))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  uint8_t* p = certificate_der->data;

   cert = mbedtls_calloc( 1, sizeof( uasdk_x509_crt ) );
   if( !cert )
   {
     result = OpcUa_BadOutOfMemory;
     goto clean_up;
   }

   if ((status = x509_crt_parse_der_core( cert, p, certificate_der->length )) != 0)
   {
     uasdk_x509_crt_free( cert );
     result = OpcUa_BadInvalidArgument;
     goto clean_up;
   }

   *certificate_handle = (uintptr_t)cert;
   cert = 0;

   clean_up:
   if(cert)
   {
     uasdk_x509_crt_free( cert );
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
  const char* filename = 0;
  char file_path[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_Good;

  if((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0)
  		|| (own_certificate_handle == 0) || (own_certificate_der == 0) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch(type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_min(group);
    break;

  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_sha256(group);
    break;

  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    break;
  }

  if(!filename)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    return result;
  }

  *own_certificate_der = (UA_Byte_string_t*) UASDK_Malloc(sizeof(UA_Byte_string_t));
  if(!(*own_certificate_der))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  *own_certificate_handle = (uintptr_t) get_cert(file_path, TRUE, *own_certificate_der);

  if(*own_certificate_handle == 0)
  {
    UASDK_Free(*own_certificate_der);
    *own_certificate_der = 0;
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_own_certificate_handle(
		const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    uintptr_t* own_certificate_handle)
{
  const char* filename = 0;
  char file_path[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_Good;

  if ((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0)
  		|| (own_certificate_handle == 0) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch(type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_min(group);
    break;
  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_sha256(group);
    break;
  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    break;
  }
  if(!filename)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    return result;
  }

  *own_certificate_handle = (uintptr_t) get_cert(file_path, FALSE, 0);

  if(*own_certificate_handle == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_own_certificate_der(
		const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    UA_Byte_string_t** own_certificate_der)
{
  const char* filename;
  char file_path[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_Good;

  if ((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0)
  		|| (own_certificate_der == 0) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch(type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_min(group);
    break;
  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    filename = filename_app_cert_rsa_sha256(group);
    break;
  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    break;
  }

  if(!filename)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    return result;
  }

  *own_certificate_der = (UA_Byte_string_t*) UASDK_Malloc(sizeof(UA_Byte_string_t));
  if(!(*own_certificate_der))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  uasdk_x509_crt* cert_ = get_cert(file_path, TRUE, *own_certificate_der);

  if(cert_ == 0)
  {
    UASDK_Free(*own_certificate_der);
    *own_certificate_der = 0;
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  uasdk_x509_crt_free( cert_ );

  return OpcUa_Good;
}

UA_Status_t UASecurity_get_own_certificate_private_key_handle(
		const UA_UTF8_string_t* pki_path,
    UA_CertificateType_t type,
    UA_CertificateGroup_t group,
    UA_UTF8_string_t* private_key_password,
    uintptr_t* private_key_handle)
{
  const char* filename;
  char file_path[MAX_PATH_LENGTH];
  UA_Status_t result = OpcUa_Good;
  mbedtls_rsa_context *dst = 0;
  mbedtls_pk_context pk;

  mbedtls_pk_init( &pk );

  if((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0)
  		|| (private_key_handle == 0) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  switch(type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    filename = filename_app_private_key_rsa_min(group);
    break;
  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    filename = filename_app_private_key_rsa_sha256(group);
    break;
  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    break;
  }
  if(!filename)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  result = uasdk_add_pki_path(pki_path, filename, file_path);
  if(result != OpcUa_Good)
  {
    return result;
  }

  result = get_private_key(file_path, private_key_password, &pk);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }

  dst = (mbedtls_rsa_context*) UASDK_Calloc(sizeof(mbedtls_rsa_context));
  if(!dst)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  if(mbedtls_rsa_copy( dst, mbedtls_pk_rsa( pk ) ) != 0)
  {
    mbedtls_rsa_free( dst );
    UASDK_Free(dst);
    dst = 0;
    result = OpcUa_BadUnexpectedError;
  }

   *private_key_handle = (uintptr_t) dst;

   clean_up:
   mbedtls_pk_free( &pk );

   return result;
}

UA_Status_t UASecurity_get_private_key_handle(
  const UA_Byte_string_t* pkcs8_pem_private_key,
  UA_UTF8_string_t* private_key_password,
  uintptr_t* private_key_handle)
{
  mbedtls_rsa_context *dst = 0;
  mbedtls_pk_context pk;
  UA_Status_t result = OpcUa_Good;
  int  status = 0;

  mbedtls_pk_init(&pk);

  if ( (!private_key_password) || (!pkcs8_pem_private_key) || (!pkcs8_pem_private_key->data) || (pkcs8_pem_private_key->length <= 0) || (pkcs8_pem_private_key->max_length < pkcs8_pem_private_key->length) || !(private_key_handle))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if ((status = mbedtls_pk_parse_key(&pk, (const unsigned char*)pkcs8_pem_private_key->data,
    (size_t)pkcs8_pem_private_key->length, (const unsigned char*)private_key_password->data, private_key_password->length)) != 0)
  {
    result = OpcUa_BadInternalError;
    mbedtls_pk_free(&pk);
    goto clean_up;
  }

  dst = (mbedtls_rsa_context*)UASDK_Calloc(sizeof(mbedtls_rsa_context));
  if (!dst)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }

  if (mbedtls_rsa_copy(dst, mbedtls_pk_rsa(pk)) != 0)
  {
    mbedtls_rsa_free(dst);
    UASDK_Free(dst);
    dst = 0;
    result = OpcUa_BadUnexpectedError;
  }

  *private_key_handle = (uintptr_t)dst;

clean_up:
  mbedtls_pk_free(&pk);

  return result;
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
  Certs_t* app_stack = 0;
  CRLs_t* app_crls = 0;
  UA_Status_t result = OpcUa_BadInternalError;
  char certs_directory_name[MAX_PATH_LENGTH];
  char crls_directory_name[MAX_PATH_LENGTH];

  if ((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0) || (stack_handle == 0) || (crls_handle == 0) || (group == UA_CERTIFICATE_GROUP_INVALID))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  result = get_stack_path(pki_path, group, is_trusted_stack, certs_directory_name, crls_directory_name);
  if(result != OpcUa_Good)
  {
  	return result;
  }

  app_stack = (Certs_t*) UASDK_Malloc(sizeof(Certs_t));
  if(!app_stack)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }
  initialise_x509_stack(app_stack);

  app_crls = (CRLs_t*) UASDK_Malloc(sizeof(CRLs_t));
  if(!app_crls)
  {
    result = OpcUa_BadOutOfMemory;
    goto clean_up;
  }
  initialise_crl_stack(app_crls);

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
  app_stack = 0;
  app_crls = 0;
  result = OpcUa_Good;

  clean_up:

  if(app_stack)
  {
    free_x509_stack( app_stack, TRUE);
    UASDK_Free(app_stack);
  }
  if(app_crls)
  {
    free_crl_stack(app_crls, TRUE);
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

  if ((pki_path == 0) || (pki_path->length <= 0) || (pki_path->data == 0)
  		|| (certificates_der == 0) || (crls_der == 0) || (no_of_certificates == 0)
			|| (no_of_crls == 0) || (group == UA_CERTIFICATE_GROUP_INVALID))
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

UA_Status_t UASecurity_free_certificate_handle(
    uintptr_t certificate_handle)
{
  uasdk_x509_crt* cert = 0;
  if(certificate_handle == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  cert = (uasdk_x509_crt*) certificate_handle;

  uasdk_x509_crt_free( cert );

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_certificate_der(
    UA_Byte_string_t* certificate_der)
{
  if((!certificate_der) || (!certificate_der->data))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UASDK_Free(certificate_der->data);
  UASDK_Free(certificate_der);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_private_key_handle(
    uintptr_t private_key_handle)
{
  mbedtls_rsa_context* ctx = 0;
  if(private_key_handle == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  ctx = (mbedtls_rsa_context*) private_key_handle;

  mbedtls_rsa_free( ctx );
  UASDK_Free(ctx);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_stacks(
    uintptr_t stack_handle,
    uintptr_t crls_handle)
{
  if((stack_handle == 0) || (crls_handle == 0) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  free_x509_stack((Certs_t*) stack_handle, TRUE);
  UASDK_Free((Certs_t*) stack_handle);

  free_crl_stack((CRLs_t*) crls_handle, TRUE);
  UASDK_Free((CRLs_t*) crls_handle);

  return OpcUa_Good;
}

UA_Status_t UASecurity_free_bytestrings(
    UA_Byte_string_t* bytestrings,
    uint32_t no_of_elements)
{
  if((bytestrings == 0) ||(no_of_elements <= 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  while(no_of_elements > 0)
  {
    UASDK_Free( bytestrings[no_of_elements - 1].data );
    no_of_elements--;
  }

  UASDK_Free( bytestrings);

  return OpcUa_Good;
}

static uint32_t get_parameter_length(UA_UTF8_string_t* name, uint32_t no_of_names )
{
  uint32_t length = 0;
  uint8_t i = 0;
  for(; i < no_of_names; i++)
  {
    length += name[i].length + 2;
  }
  return length;
}

static void get_utf8_to_char(const UA_UTF8_string_t* utf8_str, char* name)
{
  UASDK_memcpy(name, utf8_str->data, utf8_str->length);
  name[utf8_str->length] = '\0';
}

static UA_Status_t get_concatination(const char* first_str, const char* name_type, const UA_UTF8_string_t* utf8_str, char* buf, uint32_t bufLen, uint32_t* outLen  )
{
  if (!utf8_str)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  char name[MAX_STRING_LENGTH];

  if(utf8_str->length < MAX_STRING_LENGTH)
  {
    get_utf8_to_char(utf8_str, name);
  }
  else
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  int length = 0;

  if(first_str)
  {
    length = snprintf (buf, bufLen - 1 , "%s, %s=%s", first_str, name_type, name);
  }
  else
  {
    length = snprintf (buf, bufLen - 1 , "%s=%s", name_type, name);
  }

  if(length > (int)bufLen)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  *outLen =(uint32_t) (length + 1);

  return OpcUa_Good;
}

static int create_subject_buf(const UA_Certificate_Generation_Parameters_t* parameters, char* buf, uint32_t bufLen)
{
  if (!parameters)
  {
    return -1;
  }

	char* temp = (char*) UASDK_Calloc(bufLen);
	if(!temp)
	{
		return -1;
	}

  if(parameters->common_name.length > 0)
  {
    uint32_t length = 0;
    UA_Status_t status = get_concatination((const char*) 0 , "CN", &parameters->common_name, buf, bufLen, &length );
    if(status != OpcUa_Good)
    {
      UASDK_Free(temp);
      return -1;
    }

    UASDK_memcpy(temp, buf, length );
  }
  if(parameters->organisation.length > 0)
  {
    uint32_t length = 0;
    UA_Status_t status = get_concatination(temp , "O", &parameters->organisation, buf, bufLen, &length );
    if(status != OpcUa_Good)
    {
      UASDK_Free(temp);
      return -1;
    }
    UASDK_memcpy(temp, buf, length );
  }
  if(parameters->organisation_unit.length > 0)
  {
    uint32_t length = 0;
    UA_Status_t status = get_concatination(temp , "OU", &parameters->organisation_unit, buf, bufLen, &length );
    if(status != OpcUa_Good)
    {
      UASDK_Free(temp);
      return -1;
    }
    UASDK_memcpy(temp, buf, length );
  }
  if(parameters->locality.length > 0)
  {
    uint32_t length = 0;
    UA_Status_t status = get_concatination(temp , "L", &parameters->locality, buf, bufLen, &length );
    if(status != OpcUa_Good)
    {
      UASDK_Free(temp);
      return -1;
    }
    UASDK_memcpy(temp, buf, length );
  }
  if(parameters->state.length > 0)
  {
    uint32_t length = 0;
    UA_Status_t status = get_concatination(temp , "ST", &parameters->state, buf, bufLen, &length );
    if(status != OpcUa_Good)
    {
      UASDK_Free(temp);
      return -1;
    }
    UASDK_memcpy(temp, buf, length );
  }
  if(parameters->country.length > 0)
  {
    uint32_t length = 0;
    UA_Status_t status = get_concatination(temp , "C", &parameters->country, buf, bufLen, &length );
    if(status != OpcUa_Good)
    {
      UASDK_Free(temp);
      return -1;
    }
  }

  UASDK_Free(temp);
  return 0;
}

static UA_Status_t create_cert(
    mbedtls_x509write_cert *crt, mbedtls_pk_context *pk,
    const UA_Certificate_Generation_Parameters_t* parameters)
{
  UA_Status_t result = OpcUa_Good;
  uint32_t status = 0;
  mbedtls_x509write_crt_set_subject_key( crt, pk );
  mbedtls_x509write_crt_set_issuer_key( crt, pk );

  {
  	int length = 0;
    char* buf = 0;
    uint32_t bufLen = parameters->common_name.length
        + parameters->organisation.length
        + parameters->organisation_unit.length
        + parameters->locality.length
        + parameters->state.length
        + parameters->country.length + 6*6;

		buf = (char*) UASDK_Calloc(bufLen);
		if(!buf)
		{
			result = OpcUa_BadOutOfMemory;
			goto clean_up;
		}

		length = create_subject_buf(parameters, buf, bufLen);
		if(length < 0)
		{
			result = OpcUa_BadInternalError;
				goto clean_up;
		}

		if( ( status = mbedtls_x509write_crt_set_subject_name( crt, buf ) ) != 0 )
		{
			result = OpcUa_BadInternalError;
				goto clean_up;
		}
		if( ( status = mbedtls_x509write_crt_set_issuer_name( crt, buf ) ) != 0 )
		{
			result = OpcUa_BadInternalError;
			goto clean_up;
		}
    UASDK_Free(buf);
	}
  { /* Write Serial No */
    int ret;
    uint8_t* buf = 0;
    uint8_t* c = 0;
    size_t len = 0;
    mbedtls_mpi serial;
    uint32_t bufsize = (parameters->private_key_bit_length / 8) + 16;

    mbedtls_mpi_init( &serial );

    buf = (uint8_t* ) UASDK_Calloc(bufsize);
    if(!buf)
    {
      result = OpcUa_BadOutOfMemory;
      goto clean_up;
    }
    c = buf + bufsize;

    len = mbedtls_pk_write_pubkey( &c, buf, crt->subject_key );

    mbedtls_sha1( buf + bufsize - len, len, buf + bufsize - 20 );
    c = buf + bufsize - 20;
    len = 20;

    if( ( ret = mbedtls_mpi_read_binary( &serial, c, len ) ) != 0 )
    {
      result = OpcUa_BadInternalError;
      UASDK_Free(buf);
      goto clean_up;
    }

    if((ret = mbedtls_x509write_crt_set_serial( crt, &serial )) != 0)
    {
      mbedtls_mpi_free( &serial );
      UASDK_Free(buf);
      result = OpcUa_BadInternalError;
      goto clean_up;
    }
    mbedtls_mpi_free( &serial );
    UASDK_Free(buf);
  }
  {
    /* Set validity */
    char notBefore[20];
    char notAfter[20];
    UASDK_GetStringFromFileTime(parameters->start_date, 0, 20, notBefore);
    UASDK_GetStringFromFileTime(parameters->end_date, 0, 20, notAfter);

    if((status = mbedtls_x509write_crt_set_validity( crt, (const char *)notBefore, (const char *)notAfter )) != 0)
    {
      result = OpcUa_BadInternalError;
      goto clean_up;
    }
  }
/* Set Basic constrain */
  if((status = mbedtls_x509write_crt_set_basic_constraints( crt, TRUE, -1)) != 0)
  {
     result = OpcUa_BadInternalError;
     goto clean_up;
  }

/* Set Subject key Identifier */
  if((status = mbedtls_x509write_crt_set_subject_key_identifier( crt )) != 0)
  {
     result = OpcUa_BadInternalError;
     goto clean_up;
  }
/* Set Authority Key Identifier */
  if((status = mbedtls_x509write_crt_set_authority_key_identifier( crt )) != 0)
  {
     result = OpcUa_BadInternalError;
     goto clean_up;
  }

  {  /* Set Key Uses */
    unsigned int key_uses = 0;

    key_uses |= MBEDTLS_X509_KU_DIGITAL_SIGNATURE
      | MBEDTLS_X509_KU_NON_REPUDIATION
      | MBEDTLS_X509_KU_KEY_ENCIPHERMENT
      | MBEDTLS_X509_KU_DATA_ENCIPHERMENT
      | MBEDTLS_X509_KU_KEY_CERT_SIGN;

    if((status = mbedtls_x509write_crt_set_key_usage( crt, key_uses )) != 0)
    {
       result = OpcUa_BadInternalError;
       goto clean_up;
    }
  }
  { /* Extended Key Uses */
    uint32_t ret;
    uint8_t* buf = 0;
    uint32_t bufsize = 32;
    uint8_t* c = 0;
    size_t len = 0;

    buf = (uint8_t*) UASDK_Calloc(bufsize);
    if(!buf)
    {
      result = OpcUa_BadOutOfMemory;
      goto clean_up;
    }

    c = buf + bufsize;

    len = mbedtls_asn1_write_oid( &c, buf, MBEDTLS_OID_SERVER_AUTH, sizeof(MBEDTLS_OID_SERVER_AUTH) - 1);
    len += mbedtls_asn1_write_oid( &c, buf, MBEDTLS_OID_CLIENT_AUTH, sizeof(MBEDTLS_OID_CLIENT_AUTH) - 1);
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED |
                        MBEDTLS_ASN1_SEQUENCE ) );

    if((ret = mbedtls_x509write_crt_set_extension( crt, MBEDTLS_OID_EXTENDED_KEY_USAGE,
                   MBEDTLS_OID_SIZE( MBEDTLS_OID_EXTENDED_KEY_USAGE ),
                   TRUE, buf + bufsize - len, len )) != 0)
    {
      UASDK_Free(buf);
      result = OpcUa_BadInternalError;
      goto clean_up;
    }

    UASDK_Free(buf);
  }
  { /* Subject Alternate Name */
    uint8_t* buf = 0;
    uint8_t* c = 0;
    uint32_t bufsize = 0;
    size_t len1 = 0;

    bufsize = 4 + get_parameter_length( parameters->hostnames, parameters->no_of_hostnames )
        + get_parameter_length( parameters->ip_addresses, parameters->no_of_ip_addresses )
        + (parameters->application_uri.length + 2);

    buf = (uint8_t*) UASDK_Calloc(bufsize);
    if(!buf)
    {
      result = OpcUa_BadOutOfMemory;
      goto clean_up;
    }

    c = buf + bufsize;

    if(parameters->no_of_hostnames > 0)
    {
      uint32_t i;
      for(i = 0; i < parameters->no_of_hostnames; i++ )
      {
        int ret;
        size_t len = 0;

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_raw_buffer( &c, buf, parameters->hostnames[i].data, parameters->hostnames[i].length  ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONTEXT_SPECIFIC | 0x02) );
        len1 += len;
      }
    }

    if(parameters->no_of_ip_addresses > 0)
    {
      uint32_t i;
      for(i = 0 ; i < parameters->no_of_ip_addresses; i++ )
      {
        int ret;
        size_t len = 0;
        size_t IpAddressLength = 4;
        unsigned char temp[4];

        if (ret = get_string_ipv4_to_ipv4octet(&parameters->ip_addresses[i], temp) < 0)
        {
          result = OpcUa_BadInvalidArgument;
          UASDK_Free(buf);
          goto clean_up;
        }

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_raw_buffer( &c, buf, temp, IpAddressLength  ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONTEXT_SPECIFIC | 0x07 ) );
        len1 += len;
      }
    }

    if(parameters->application_uri.length > 0)
    {
      int ret;
      size_t len = 0;

      MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_raw_buffer( &c, buf, parameters->application_uri.data, parameters->application_uri.length  ) );
      MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
      MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONTEXT_SPECIFIC | 0x06 ) );
      len1 += len;
    }
    {
      int ret;
      MBEDTLS_ASN1_CHK_ADD( len1, mbedtls_asn1_write_len( &c, buf, len1 ) );
      MBEDTLS_ASN1_CHK_ADD( len1, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED |
                        MBEDTLS_ASN1_SEQUENCE ) );
    }
    if(( status = mbedtls_x509write_crt_set_extension( crt, MBEDTLS_OID_SUBJECT_ALT_NAME,
                     MBEDTLS_OID_SIZE( MBEDTLS_OID_SUBJECT_ALT_NAME ),
                     0, buf + bufsize - len1, len1 )) != 0)
    {
      UASDK_Free(buf);
      result = OpcUa_BadInternalError;
      goto clean_up;
    }
    UASDK_Free(buf);
  }

  clean_up:

  return result;
}

static int32_t write_buffer_to_file(const char* filename, const uint8_t* buf,size_t buf_len)
{
  int32_t ret = 0;
    OS_FILE *f;
    os_remove(filename);

    if( ( f = os_fopen( filename, "wb" ) ) == NULL )
        return -1;

    if( os_fwrite( buf, 1, buf_len, f ) != buf_len)
    {
      ret = -1;
    }
    os_fclose( f );

    return ret;
}

static int32_t write_pkcs8_unencrypted_der(unsigned char* buf, size_t bufsize, int len)
{
  int ret;
  unsigned char *c = buf + bufsize - len;
  const char *oid;
  size_t olen = 0;

  MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
  MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_OCTET_STRING ) );

  mbedtls_oid_get_oid_by_pk_alg( MBEDTLS_PK_RSA, &oid, &olen );
  len += mbedtls_asn1_write_algorithm_identifier( &c, buf, oid, olen, 0);
  len += mbedtls_asn1_write_int( &c, buf, 0 );
  MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
  MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) );

  return len;
}

static int32_t opc_asn1_write_int( unsigned char **p, unsigned char *start, int32_t val )
{
  int32_t ret;
  size_t len = 0;

  if( *p - start < 1 )
    return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

  while( val > 0 )
  {
    if( *p - start < 1 )
      return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    *--(*p) = val;
    val = (val >> 8);
    len += 1;
  }

  MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
  MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_INTEGER ) );

  return( (int32_t) len );
}

static UA_Status_t write_pkcs5_params( mbedtls_asn1_buf *pbe_params, unsigned char *param, size_t paramlen, uint32_t rsaKeyLen )
{
  int32_t ret = 0;
  int32_t len1 = 0, len = 0;
  unsigned char random[8] ;
  size_t randomsize = 8;
  unsigned char *c = param + paramlen;
  mbedtls_entropy_context entropy;

  mbedtls_entropy_init( &entropy );
  if((ret = mbedtls_entropy_func( &entropy, random, randomsize )) != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  /* Encryption scheme */
  if((len = mbedtls_asn1_write_octet_string( &c, param, random, randomsize )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  if((len += mbedtls_asn1_write_oid( &c, param, MBEDTLS_OID_DES_EDE3_CBC, sizeof(MBEDTLS_OID_DES_EDE3_CBC) - 1 )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len += mbedtls_asn1_write_len( &c, param, len )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len += mbedtls_asn1_write_tag( &c, param, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  /* KDF Alg Parameter */
  if((len1 += opc_asn1_write_int( &c, param, rsaKeyLen )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((ret = mbedtls_entropy_func( &entropy, random, randomsize )) != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  if((len1 += mbedtls_asn1_write_octet_string( &c, param, random, randomsize)) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len1 += mbedtls_asn1_write_len( &c, param, len1 )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len1 += mbedtls_asn1_write_tag( &c, param, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  /* KDF Alg OID */
  if((len += mbedtls_asn1_write_algorithm_identifier( &c, param, MBEDTLS_OID_PKCS5_PBKDF2, sizeof(MBEDTLS_OID_PKCS5_PBKDF2) - 1, len1 )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  pbe_params->len = len;
  pbe_params->tag = MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE;
  pbe_params->p = c;

  return OpcUa_Good;
}

static int32_t opc_pkcs5_pbes2( const mbedtls_asn1_buf *pbe_params, int mode,
                 const unsigned char *pwd,  size_t pwdlen,
                 const unsigned char *data, size_t datalen,
                 unsigned char *output, size_t *olen )
{
  int32_t ret;
  int iterations = 0, keylen = 0;
  unsigned char *p, *end;
  mbedtls_asn1_buf kdf_alg_oid, enc_scheme_oid, kdf_alg_params, enc_scheme_params;
  mbedtls_asn1_buf salt;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA1;
  unsigned char key[32], iv[32];
  const mbedtls_md_info_t *md_info;
  const mbedtls_cipher_info_t *cipher_info;
  mbedtls_md_context_t md_ctx;
  mbedtls_cipher_type_t cipher_alg;
  mbedtls_cipher_context_t cipher_ctx;

  p = pbe_params->p;
  end = p + pbe_params->len;

  /*
   *  PBES2-params ::= SEQUENCE {
   *    keyDerivationFunc AlgorithmIdentifier {{PBES2-KDFs}},
   *    encryptionScheme AlgorithmIdentifier {{PBES2-Encs}}
   *  }
   */
  if( pbe_params->tag != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) )
    return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT +
              MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

  if( ( ret = mbedtls_asn1_get_alg( &p, end, &kdf_alg_oid, &kdf_alg_params ) ) != 0 )
    return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

  // Only PBKDF2 supported at the moment
  //
  if( MBEDTLS_OID_CMP( MBEDTLS_OID_PKCS5_PBKDF2, &kdf_alg_oid ) != 0 )
    return( MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE );

  if( ( ret = pkcs5_parse_pbkdf2_params( &kdf_alg_params,
                                         &salt, &iterations, &keylen,
                                         &md_type ) ) != 0 )
  {
    return( ret );
  }

  md_info = mbedtls_md_info_from_type( md_type );
  if( md_info == NULL )
    return( MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE );

  if( ( ret = mbedtls_asn1_get_alg( &p, end, &enc_scheme_oid,
                            &enc_scheme_params ) ) != 0 )
  {
    return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );
  }

  if( mbedtls_oid_get_cipher_alg( &enc_scheme_oid, &cipher_alg ) != 0 )
    return( MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE );

  cipher_info = mbedtls_cipher_info_from_type( cipher_alg );
  if( cipher_info == NULL )
    return( MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE );

  /*
   * The value of keylen from pkcs5_parse_pbkdf2_params() is ignored
   * since it is optional and we don't know if it was set or not
   */
  keylen = cipher_info->key_bitlen / 8;

  if( enc_scheme_params.tag != MBEDTLS_ASN1_OCTET_STRING ||
      enc_scheme_params.len != cipher_info->iv_size )
  {
    return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT );
  }

  mbedtls_md_init( &md_ctx );
  mbedtls_cipher_init( &cipher_ctx );

  memcpy( iv, enc_scheme_params.p, enc_scheme_params.len );

  if( ( ret = mbedtls_md_setup( &md_ctx, md_info, 1 ) ) != 0 )
    goto clean_up;

  if( ( ret = mbedtls_pkcs5_pbkdf2_hmac( &md_ctx, pwd, pwdlen, salt.p, salt.len,
                                 iterations, keylen, key ) ) != 0 )
  {
    goto clean_up;
  }

  if( ( ret = mbedtls_cipher_setup( &cipher_ctx, cipher_info ) ) != 0 )
    goto clean_up;

  if( ( ret = mbedtls_cipher_setkey( &cipher_ctx, key, 8 * keylen, (mbedtls_operation_t) mode ) ) != 0 )
    goto clean_up;

  if( ( ret = mbedtls_cipher_crypt( &cipher_ctx, iv, enc_scheme_params.len,
                            data, datalen, output, olen ) ) != 0 )
    ret = MBEDTLS_ERR_PKCS5_PASSWORD_MISMATCH;

  clean_up:

  mbedtls_md_free( &md_ctx );
  mbedtls_cipher_free( &cipher_ctx );

  return( ret );
}

static UA_Status_t opc_write_pkcs8_encrypted_der(unsigned char* buf, size_t size, int len, const UA_UTF8_string_t* private_key_password, size_t *olen, uint32_t rsaKeyLen)
{
  uint32_t ret = 0;
  UA_Status_t status = OpcUa_Good;
  mbedtls_asn1_buf pbe_params;
  uint8_t param[100];
  uint8_t* c = 0;
  uint32_t len1 = 0;

  UASDK_memset(param, 0, 100);

  if((status = write_pkcs5_params( &pbe_params, param , 100, rsaKeyLen)) != OpcUa_Good)
  {
    return status;
  }
  {
    unsigned char* output = 0;
    uint32_t outBufSize = 2048;
    size_t keylen = 0;
    output = (unsigned char*) UASDK_Calloc(outBufSize);
    if(!output)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    if( ( ret = opc_pkcs5_pbes2( &pbe_params, MBEDTLS_PKCS5_ENCRYPT, private_key_password->data, private_key_password->length,
                            buf + size - len , len, output, &keylen ) ) != 0 )
    {
      UASDK_Free(output);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }
    c = buf + size;
    if((len = mbedtls_asn1_write_octet_string( &c, buf, output, keylen )) < 0)
    {
      UASDK_Free(output);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
    }
    UASDK_Free(output);
  }
  if((len1 = mbedtls_asn1_write_raw_buffer( &c, buf, pbe_params.p, pbe_params.len )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len1 += mbedtls_asn1_write_len( &c, buf, pbe_params.len )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len1 += mbedtls_asn1_write_tag( &c, buf, pbe_params.tag )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len += mbedtls_asn1_write_algorithm_identifier( &c, buf, MBEDTLS_OID_PKCS5_PBES2, sizeof(MBEDTLS_OID_PKCS5_PBES2) - 1, len1 )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  if((len += mbedtls_asn1_write_len( &c, buf, len )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }
  if((len += mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE )) < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  *olen = len;

  return OpcUa_Good;
}

static UA_Status_t opc_write_pkcs8_des3_pem(mbedtls_pk_context* pk, const UA_UTF8_string_t* private_key_password, uint8_t** outbuf, size_t *olen, uint32_t rsaKeyLen)
{
  UA_Status_t status = OpcUa_Good;
  uint8_t* keybuf = 0;
  size_t keybufsize = 2048;
  int32_t ret = 0;
  int32_t ilen = 0;
  size_t olender = 0;

  keybuf = (uint8_t*) UASDK_Calloc(keybufsize);
  if(!keybuf)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if((ilen = mbedtls_pk_write_key_der( pk, keybuf, keybufsize )) < 0)
  {
    UASDK_Free(keybuf);
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  if((ilen = write_pkcs8_unencrypted_der(keybuf, keybufsize, ilen)) < 0)
  {
    UASDK_Free(keybuf);
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  if((status = opc_write_pkcs8_encrypted_der(keybuf, keybufsize, ilen, private_key_password, &olender, rsaKeyLen)) != OpcUa_Good)
  {
    UASDK_Free(keybuf);
    return status;
  }
  if((ret = mbedtls_pem_write_buffer( "-----BEGIN ENCRYPTED PRIVATE KEY-----\n", "-----END ENCRYPTED PRIVATE KEY-----\n",
      keybuf + keybufsize - olender, olender, 0, 0, olen )) != MBEDTLS_ERR_BASE64_BUFFER_TOO_SMALL)
  {
    UASDK_Free(keybuf);
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  if( ( *outbuf = mbedtls_calloc( 1, *olen + 1) ) == NULL )
  {
    UASDK_Free(keybuf);
    return  OpcUa_BadOutOfMemory ;
  }
  if((ret = mbedtls_pem_write_buffer( "-----BEGIN ENCRYPTED PRIVATE KEY-----\n", "-----END ENCRYPTED PRIVATE KEY-----\n",
      keybuf + keybufsize - olender, olender,
      *outbuf, *olen, olen )) != 0)
  {
    UASDK_Free(keybuf);
    mbedtls_free(*outbuf);
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  UASDK_Free(keybuf);

  return OpcUa_Good;
}

static UA_Status_t check_input_parameters(const UA_Certificate_Generation_Parameters_t* parameters)
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
       && ((parameters->country.length > 0) ? (uintptr_t) parameters->country.data : TRUE)) == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_create_self_signed_certificate(
    const UA_Certificate_Generation_Parameters_t* parameters)
{
  UA_Status_t status = OpcUa_Good, result = OpcUa_Good;
  mbedtls_entropy_context entropy;
  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_rsa_context rsakey;
  mbedtls_pk_context pk;
  mbedtls_x509write_cert crt;
  mbedtls_md_type_t md_alg = MBEDTLS_MD_SHA1;
  int ret = 0;
  int len = 0;
  mbedtls_rsa_init( &rsakey, MBEDTLS_RSA_PKCS_V15, 0 );
  mbedtls_pk_init( &pk );
  mbedtls_ctr_drbg_init( &ctr_drbg );
  mbedtls_entropy_init( &entropy );

  if(check_input_parameters(parameters) != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  switch(parameters->type)
  {
  case UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE:
    md_alg = MBEDTLS_MD_SHA1;
    break;

  case UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE:
    md_alg = MBEDTLS_MD_SHA256;
    break;

  default:
    result = OpcUa_BadInvalidArgument;
    goto clean_up;
  }

  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy, 0, 0 ) ) != 0 )
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  if( ( ret = mbedtls_pk_setup( &pk, mbedtls_pk_info_from_type( MBEDTLS_PK_RSA ) ) ) != 0 )
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  ret = mbedtls_rsa_gen_key( mbedtls_pk_rsa( pk ), mbedtls_ctr_drbg_random, &ctr_drbg, parameters->private_key_bit_length , 65537 );
  if( ret != 0 )
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  mbedtls_x509write_crt_init( &crt );

  mbedtls_x509write_crt_set_md_alg( &crt, md_alg );

  if((status = create_cert(&crt, &pk, parameters)) != OpcUa_Good)
  {
    result = OpcUa_BadInternalError;
    goto clean_up;
  }
  {
    char file_path[MAX_PATH_LENGTH];
  	uint8_t* buf = 0;
    uint32_t buf_len = 2048;

    buf = (uint8_t*) UASDK_Calloc(buf_len);
    if(!buf)
    {
      result = OpcUa_BadOutOfMemory;
      goto clean_up;
    }

    if( 0 > (len =  mbedtls_x509write_crt_der( &crt, buf, buf_len, mbedtls_ctr_drbg_random, &ctr_drbg )))
    {
      UASDK_Free(buf);
      result = OpcUa_BadInternalError;
      goto clean_up;
    }

    status = filename_app_cert(&parameters->pki_path, parameters->group, parameters->type, file_path);
    if(status != OpcUa_Good)
    {
    	result = status;
    	goto clean_up;
    }

    if (0 >  write_buffer_to_file((const char *)file_path, buf + buf_len - len , len))
    {
      UASDK_Free(buf);
      result = OpcUa_BadInternalError;
      goto clean_up;
    }

    UASDK_Free(buf);
  }
  {
    char file_path[MAX_PATH_LENGTH];
    uint8_t *pembuf = 0;
    size_t olen = 0;
    if((status = opc_write_pkcs8_des3_pem( &pk, &(parameters->private_key_password) ,&pembuf, &olen, parameters->private_key_bit_length)) != OpcUa_Good)
    {
      result = status;
      goto clean_up;
    }

    status = filename_app_cert_private_key(&parameters->pki_path, parameters->group, parameters->type, file_path);
    if(status != OpcUa_Good)
    {
     	result = status;
     	goto clean_up;
    }

    if (0 >  write_buffer_to_file((const char *)file_path, (const uint8_t*) pembuf , olen - 1))
    {
      result = OpcUa_BadInternalError;
    }
    mbedtls_free(pembuf);
  }

  clean_up:

  mbedtls_x509write_crt_free( &crt );
  mbedtls_pk_free( &pk );

  return result;
}

UA_Status_t UASecurity_certificate_generation_parameters_init(UA_Certificate_Generation_Parameters_t* parameters)
{
  if(parameters == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  parameters->group = UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP;
  parameters->type = UA_CERTIFICATE_TYPE_APPLICATION_TYPE;

  parameters->private_key_bit_length = 0;
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

static void create_store(const char* path, DirectoryType_t type)
{
  mode_t mode = S_IRWXU;
  char filepath[MAX_PATH_LENGTH];

  os_mkdir(path, mode);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_CERTS);
  os_mkdir(filepath, mode);

  switch(type)
  {
    case DIR_TYPE_OWN:
      snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_PRIVATE);
      os_mkdir(filepath, mode);
      break;

    case DIR_TYPE_TRUSTED:
    case DIR_TYPE_ISSUER:
      snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", path, UA_SECURITY_PATH_CRL);
      os_mkdir(filepath, mode);
      break;

    default:
      break;
  }
}

static void create_store_type(const char* path)
{
  mode_t mode = S_IRWXU;
  char filepath[MAX_PATH_LENGTH];

  os_mkdir(path, mode);

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

  if(os_stat(pkipath, &s) != 0)
  {
  	UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  else
  {
  	if(!os_S_ISDIR(s.st_mode))
  	{
  		UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
   	}
  }

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s", pkipath, UA_SECURITY_PATH_PKI);
  os_mkdir(filepath, mode);
  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s/%s", pkipath, UA_SECURITY_PATH_PKI, UA_SECURITY_PATH_DEFAULT_APPLICATION_GROUP);
  create_store_type(filepath);

  snprintf(filepath, MAX_PATH_LENGTH - 1, "%s/%s/%s", pkipath, UA_SECURITY_PATH_PKI, UA_SECURITY_PATH_DEFAULT_USER_TOKEN_GROUP);
  create_store_type(filepath);

  return OpcUa_Good;
}

int64_t UASecurity_get_certificate_expiry_date(const UA_Byte_string_t* certDer)
{
  Certs_t chain_stack;
  int64_t expiry_time = 0;

  if ((certDer == 0) || (certDer->data == 0) || (certDer->length <= 0) || (certDer->length > certDer->max_length))
  {
    return expiry_time;
  }

  initialise_x509_stack(&chain_stack);

  UA_Status_t result = extract_certs_from_chain(certDer, &chain_stack);
  if (result != OpcUa_Good)
  {
    goto clean_up;
  }
  mbedtls_x509_time time = chain_stack.first->cert->crt.valid_to;
  UASDK_DatetimeFormat_t dateTimeFormt;
  dateTimeFormt.year = time.year;
  dateTimeFormt.month = time.mon;
  dateTimeFormt.day = time.day;
  dateTimeFormt.hour = time.hour;
  dateTimeFormt.minute = time.min;
  dateTimeFormt.second = time.sec;

  expiry_time = UASDK_GetFileTimeFromDateTimeFormat(dateTimeFormt);

clean_up:

  free_x509_stack(&chain_stack, TRUE);
 
  return expiry_time;

}

#else

/*
 * This line is just to avoid the pedantic warning
 * If security is disabled
 */
typedef int dummy;

#endif /* ((UA_INCLUDE_SECURITY > 0) && (UA_USE_NANOSSL > 0)) */
