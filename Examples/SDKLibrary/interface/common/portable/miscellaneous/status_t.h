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

#ifndef _STATUS_T_
#define _STATUS_T_

#include "uasdk_includes.h"
#include "opcua_status_codes.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

template<typename T> class IntrusivePtr_t;
class String_t;

/*****************************************************************************/
/** \brief Status_t
 *
 * A Class to implements the Operation status uitility
 *
 */
class Status_t
{
private:
  uint32_t statusCode;

public:
  /*****************************************************************************/
  /** Default Constructor for the class
   *
   */
  Status_t() : statusCode(OpcUa_Good) {}

  /*****************************************************************************/
  /** Constructor for the class
   *
   * @param[in] uint32_t value
   * The status code
   */
  Status_t(uint32_t value) : statusCode(value) {}

  /*****************************************************************************/
  /** Copy Constructor for the class
   *
   * @param[in] rhs
   *  Status object to be copied from
   */
  Status_t(const Status_t& rhs) : statusCode(rhs.statusCode) {}

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] const Status_t& rhs
   *  Status object to be assigned
   */
  Status_t& operator =(const Status_t& rhs)
  {
    statusCode = rhs.statusCode;
    return *this;
  }

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] uint32_t rhs
   *  Status code to be assigned
   */
  Status_t& operator =(const uint32_t& rhs)
  {
    statusCode = rhs;
    return *this;
  }

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] const Status_t& rhs
   *  Status object to be compared with
   */
  bool operator ==(const Status_t& rhs) const
  {
    return (statusCode == rhs.statusCode);
  }

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] const Status_t& rhs
   *  Status object to be compared with
   */
  bool operator !=(const Status_t& rhs) const
  {
    return (!(*this == rhs));
  }

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] int rhs
   *  Status code to be compared with
   */
  bool operator ==(int rhs) const
  {
    return (statusCode == static_cast<uint32_t>(rhs));
  }

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] int rhs
   *  Status code to be compared with
   */
  bool operator !=(int rhs) const
  {
    return (!(statusCode == static_cast<uint32_t>(rhs)));
  }

  /*****************************************************************************/
  /** Check if the status code is bad
   *
   * @return
   *  True - If bad
   *  False - Otherwise
   */
  bool IsBad() const
  {
    return (statusCode & (1<<31)) != 0;
  }

  /*****************************************************************************/
  /** Check if the status code is good
   *
   * @return
   *  True - If good
   *  False - Otherwise
   */
  bool IsGood() const
  {
    return !IsBad();
  }

  /*****************************************************************************/
  /** Check if the status code is bad due to out of memory
   *
   * @return
   *  True - If status code is bad due to out of memory
   *  False - Otherwise
   */
  bool IsOutOfMemory() const
  {
    return (statusCode == OpcUa_BadOutOfMemory);
  }

  /*****************************************************************************/
  /** Check if the status code is bad due to security
  *
  * @return
  *  True - If status code is bad due to security related error
  *  False - Otherwise
  */
  bool IsSecurityError() const
  {
    return ( (statusCode == OpcUa_BadSecurityChecksFailed)
            || (statusCode == OpcUa_BadRequestTypeInvalid)
            || (statusCode == OpcUa_BadSecurityModeRejected)
            || (statusCode == OpcUa_BadSecurityPolicyRejected) 
            || (statusCode == OpcUa_BadCertificateInvalid)
            || (statusCode == OpcUa_BadCertificateTimeInvalid) 
            || (statusCode == OpcUa_BadCertificateIssuerTimeInvalid)
            || (statusCode == OpcUa_BadCertificateHostNameInvalid)
            || (statusCode == OpcUa_BadCertificateUriInvalid)
            || (statusCode == OpcUa_BadCertificateUseNotAllowed)
            || (statusCode == OpcUa_BadCertificateIssuerUseNotAllowed)
            || (statusCode == OpcUa_BadCertificateUntrusted)
            || (statusCode == OpcUa_BadCertificateRevocationUnknown)
            || (statusCode == OpcUa_BadCertificateIssuerRevocationUnknown)
            || (statusCode == OpcUa_BadCertificateRevoked) 
            || (statusCode == OpcUa_BadCertificateIssuerRevoked)
            || (statusCode == OpcUa_BadUserAccessDenied) );
  }

  /*****************************************************************************/
  /** Get the status code
   *
   * @return
   *  Returns the status code
   */
  uint32_t Value(void) const { return statusCode; }
};

/** @} */

}

#endif // _STATUS_T_
