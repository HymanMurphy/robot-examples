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

#ifndef _ITRANSACTION_LISTENER_T_
#define _ITRANSACTION_LISTENER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "status_t.h"

namespace uasdk
{

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Transaction Listener
 *
 * This class provides interfaces to listen the transactions begin/end
 *
 */
class ITransactionListener_t : public IRefCount_t
{
public:
  virtual ~ITransactionListener_t() {};

  /*****************************************************************************/
  /** Transaction Begins listener
   *
   * @param[in] transactionId
   * The Transaction ID to begin
   *
   * @param[in] noOfOperations
   * The number of operations
   */
  virtual void TransactionBegins(uint32_t transactionId,
                                 uint32_t noOfOperations) const = 0;

  /*****************************************************************************/
  /** Transaction Ends listener
   *
   * @param[in] transactionId
   * The Transaction ID to begin
   */
  virtual void TransactionEnds(uint32_t transactionId) const = 0;
};

/** @} */

}

#endif // _ITRANSACTION_LISTENER_T_
