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

#ifndef _ICERTIFICATE_REJECTED_LIST_LISTENER_T_
#define _ICERTIFICATE_REJECTED_LIST_LISTENER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

namespace uasdk
{
/** \addtogroup grpSecurity
 *@{*/

class ICertificateRejectedListListener_t : public IRefCount_t
{
public:
  virtual ~ICertificateRejectedListListener_t() {};

  /*****************************************************************************/
  /** This function used to add UA certificate into rejected list..
   *
   * @param[in] group
   * The group to which rejected certificate to be added.
   */
  virtual void CertificatedAddedToRejectedList(UA_CertificateGroup_t group) const = 0;
};
/** @}*/

}

#endif // _ICERTIFICATE_REJECTED_LIST_LISTENER_T_
