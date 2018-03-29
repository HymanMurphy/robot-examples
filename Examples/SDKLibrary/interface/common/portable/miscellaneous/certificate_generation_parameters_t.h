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

#ifndef _CERTIFICATE_GENERATION_PARAMETERS_T_
#define _CERTIFICATE_GENERATION_PARAMETERS_T_

#include "allocatable_t.h"
#include "iref_count_t.h"
#include "opcua_date_time_t.h"
#include "opcua_string_t.h"
#include "array_t.h"

namespace uasdk
{

/** \addtogroup grpSecurity
 *@{*/

/*****************************************************************************/
/** \brief Certificate generation parameters
 *
 * A class contains the list of parameters required for certificate generation
 *
 */

class CertificateGenerationParameters_t : public IRefCount_t, public Allocatable_t
{
public:
  UA_CertificateType_t type;            /**< Type of certificate to generate */
  UA_CertificateGroup_t group;          /**< Certificate group to add the certificate to */
  uint32_t privateKeyBitLength;         /**< Bit length of the certificate private key */
  String_t privateKeyPassword;    /**< Private Key File Password */
  DateTime_t start_date;                /**< start date for certificate expiry */
  DateTime_t end_date;                  /**< end date for certificate expiry */
  String_t applicationUri;        /**< Application URI */
  Array_t<String_t> hostnames;    /**< Array of host names */
  Array_t<String_t> ipAddresses;  /**< Array of IP Addresses */
  String_t commonName;            /**< Certificate Common Name */
  String_t organisation;          /**< Certificate Organisation */
  String_t organisationUnit;      /**< Certificate Organisation Unit */
  String_t locality;              /**< Certificate Locality */
  String_t state;                 /**< Certificate State */
  String_t country;               /**< Certificate Country */

  /*****************************************************************************/
   /** Default Constructor of the class
   */
  CertificateGenerationParameters_t() : type(UA_CERTIFICATE_TYPE_INVALID),
      group(UA_CERTIFICATE_GROUP_INVALID), privateKeyBitLength(0)
  {}

};

/**@}*/

} // namespace uasdk
#endif // _CERTIFICATE_GENERATION_PARAMETERS_T_
