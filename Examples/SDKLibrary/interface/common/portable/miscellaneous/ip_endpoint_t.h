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

#ifndef _IP_ENDPOINT_T_
#define _IP_ENDPOINT_T_

namespace uasdk
{
/** \addtogroup grpMiscellaneous
*@{*/

class IPEndpoint_t : public IRefCount_t
{
/*****************************************************************************/
/** This function is used to get port information..
 *
 *
 *  @return
 *  return port value
 */
virtual uint16_t Port(void) const = 0;

/*****************************************************************************/
/** This function is used to get the end point infomraiton in string format
 *
 *
 *  @return
 *  An intrusive reference counting Boost-style smart pointer to end point in String type
 *  result should be checked for null before dereferencing it
 *
 */
  virtual IntrusivePtr_t<String_t> ToString(void) const = 0;
};

/** @} */

} // namespace uasdk

#endif // _IP_ENDPOINT_T_
