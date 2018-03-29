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

#ifndef _ICERTIFICATE_PRIVATE_KEY_PASSWORD_PROVIDER_T_
#define _ICERTIFICATE_PRIVATE_KEY_PASSWORD_PROVIDER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "status_t.h"

namespace uasdk
{
/** \addtogroup grpSecurity
 *@{*/
class ICertificatePrivateKeyPasswordProvider_t : public IRefCount_t
{
public:
  virtual ~ICertificatePrivateKeyPasswordProvider_t() {};

  /*****************************************************************************/
  /** This function is used to get the password.
   *
   * @param[in] type
   * Type of UA certificate.
   *
   * @param[in] group
   * group type of UA certificate.
   *
   * @param[out] password
   * Password to be returned
   *
   * @return
   * returns the result of the operation.
   */
  virtual Status_t GetPassword(UA_CertificateType_t type, UA_CertificateGroup_t group, String_t& password) const = 0;
};

/**@}*/

}

#endif // _ICERTIFICATE_PRIVATE_KEY_PASSWORD_PROVIDER_T_
