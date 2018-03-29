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

#ifndef _USER_AUTHENTICATOR_PROVIDER_T_
#define _USER_AUTHENTICATOR_PROVIDER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "status_t.h"

#if (UASDK_INCLUDE_SERVER > 0)
namespace uasdk
{

class IUserPermissions_t;
class UsernameIdentityToken_t;
class X509IdentityToken_t;
class AnonymousIdentityToken_t;
class NodeId_t;

/** \addtogroup grpSecurity
 *@{*/

/*****************************************************************************/
/** \brief User Permissions Provider
 *  \class IUserPermissionsProvider_t
 *
 * This class provides interfaces to get the User permissions
 *
 */
class IUserPermissionsProvider_t : public IRefCount_t
{
public:
  virtual ~IUserPermissionsProvider_t() {};

  /*****************************************************************************/
  /** Get the User permission for the given session id, user name and password.
   *
   * @param[in] sessionId
   * The session ID
   *
   * @param[in] userName
   * The User Name
   *
   * @param[in] password
   * The Password
   *
   * @param[out] userPermissions
   * The User permission for the given session id, user name and password
   *
   * @return
   * Status of the operation
   */
  virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
                                      const String_t& userName,
                                      const String_t& password,
                                      IntrusivePtr_t<IUserPermissions_t>& userPermissions) const = 0;

  /*****************************************************************************/
  /** Get the User permission for the given session id and certificate for user identity token
   *
   * @param[in] sessionId
   * The session ID
   *
   * @param[in] userIdentityToken
   * X509 User Identity Token
   *
   * @param[out] userPermissions
   * The User permission for the given session id, X509 User Identity Token
   *
   * @return
   * Status of the operation
   */
  virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
                                      const X509IdentityToken_t& userIdentityToken,
                                      IntrusivePtr_t<IUserPermissions_t>& userPermissions) const = 0;

  /*****************************************************************************/
  /** Get the User permission for the given session id and anonymous user identity token
   *
   * @param[in] sessionId
   * The session ID
   *
   * @param[in] userIdentityToken
   * Anonymous User Identity Token
   *
   * @param[out] userPermissions
   * The User permission for the given session id, Anonymous User Identity Token
   *
   * @return
   * Status of the operation
   */
  virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
                                      const AnonymousIdentityToken_t& userIdentityToken,
                                      IntrusivePtr_t<IUserPermissions_t>& userPermissions) const = 0;
};

/**@}*/

}
#endif // #if (UASDK_INCLUDE_SERVER > 0)
#endif // _USER_AUTHENTICATOR_PROVIDER_T_
