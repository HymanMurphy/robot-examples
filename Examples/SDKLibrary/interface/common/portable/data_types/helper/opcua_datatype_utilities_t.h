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

#ifndef _DATATYPE_UTILITIES_T_
#define _DATATYPE_UTILITIES_T_

#include "allocatable_t.h"
#include "iref_count_t.h"

namespace uasdk
{

  class NodeId_t;

/*****************************************************************************/
/** \brief DataTypeUtilities_t
 *
 * Implamanets the Data Type Utilities
 *
 */
class DataTypeUtilities_t : public Allocatable_t, public IRefCount_t
{
private:
  DataTypeUtilities_t& operator=(DataTypeUtilities_t const &);
  DataTypeUtilities_t(DataTypeUtilities_t const &);
  DataTypeUtilities_t();

public:

  /*****************************************************************************/
  /** Check if number or not
   *
   * @param[in] const NodeId_t& typeId
   * Reference to the Node ID
   *
   * @return
   * True - if number
   * False - If not number
   */
  bool static IsANumber(const NodeId_t& typeId);
};


/** @} */

}

#endif /* _DATATYPE_UTILITIES_T_ */
