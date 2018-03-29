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

#ifndef _CERTIFICATE_VALIDATION_OPTIONS_T_
#define _CERTIFICATE_VALIDATION_OPTIONS_T_

#include "iref_count_t.h"
#include "ua_security.h"

namespace uasdk
{

/** \addtogroup grpSecurity
 *@{*/

class ClientCertificateValidationOptions_t : public Allocatable_t
{
public:
  bool suppressCertificateExpired;
  bool suppressUriMismatch;
  bool suppressHostnameInvalid;
  bool suppressRevocationStatusUnknown;
  bool checkRevocationStatusOnline;
  bool checkRevocationStatusOffline;
  bool doNotSaveRejectedCertificate;

  /*****************************************************************************/
  /** Default Constructor of the class
  */
  ClientCertificateValidationOptions_t() :
    suppressCertificateExpired(false),
    suppressUriMismatch(false),
    suppressHostnameInvalid(false),
    suppressRevocationStatusUnknown(false),
    checkRevocationStatusOnline(false),
    checkRevocationStatusOffline(true),
    doNotSaveRejectedCertificate(true)
    {}

  /*****************************************************************************/
  /** \brief Get the Certificate validation option settings
  * @return
  * Returns the Certificate validation option BITS
  */
  uint32_t GetOptionBits(void) const
  {
    uint32_t optionBits = 0;
    
    if (suppressCertificateExpired)
    {
      optionBits |= OB_SUPPRESS_CERTIFICATE_EXPIRED;
    }
    if (suppressUriMismatch)
    {
      optionBits |= OB_SUPPRESS_URI_MISMATCH;
    }
    if (suppressHostnameInvalid)
    {
      optionBits |= OB_SUPPRESS_HOSTNAME_INVALID;
    }
    if (suppressRevocationStatusUnknown)
    {
      optionBits |= OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN;
    }
    if (checkRevocationStatusOnline)
    {
      optionBits |= OB_CHECK_REVOCATION_STATUS_ONLINE;
    }
    if (checkRevocationStatusOffline)
    {
      optionBits |= OB_CHECK_REVOCATION_STATUS_OFFLINE;
    }
    return optionBits;
  }
};

/*****************************************************************************/
/** \brief Certificate validation option
 *
 * A class contains the Certificate validation option settings
 *
 */
class ServerCertificateValidationOptions_t : public Allocatable_t
{
public:
  bool suppressCertificateExpired;
  bool suppressUriMismatch;
  bool suppressRevocationStatusUnknown;
  bool checkRevocationStatusOnline;
  bool checkRevocationStatusOffline;
  bool trustAllClientsWhenTrustListIsEmpty;
  bool doNotSaveRejectedCertificates;

  /*****************************************************************************/
   /** Default Constructor of the class
   */
  ServerCertificateValidationOptions_t() :
    suppressCertificateExpired(false),
    suppressUriMismatch(false),
    suppressRevocationStatusUnknown(false),
    checkRevocationStatusOnline(false),
    checkRevocationStatusOffline(true),
    trustAllClientsWhenTrustListIsEmpty(false),
    doNotSaveRejectedCertificates(true)
  {}

  /*****************************************************************************/
  /** \brief Get the Certificate validation option settings
  * @return
  * Returns the Certificate validation option BITS
  */
  uint32_t GetOptionBits(void) const
  {
    uint32_t optionBits = 0;

    if (suppressCertificateExpired)
    {
      optionBits |= OB_SUPPRESS_CERTIFICATE_EXPIRED;
    }

    // Never validate the host name on the server side
    optionBits |= OB_SUPPRESS_HOSTNAME_INVALID;

    if (suppressUriMismatch)
    {
      optionBits |= OB_SUPPRESS_URI_MISMATCH;
    }
    if (suppressRevocationStatusUnknown)
    {
      optionBits |= OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN;
    }
    if (checkRevocationStatusOnline)
    {
      optionBits |= OB_CHECK_REVOCATION_STATUS_ONLINE;
    }
    if (checkRevocationStatusOffline)
    {
      optionBits |= OB_CHECK_REVOCATION_STATUS_OFFLINE;
    }
    return optionBits;
  }
};

/**@}*/

} // namespace uasdk
#endif // _CERTIFICATE_VALIDATION_OPTIONS_T_
