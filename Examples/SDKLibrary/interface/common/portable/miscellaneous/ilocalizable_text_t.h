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

#ifndef _ILOCALIZABLE_TEXT_T_
#define _ILOCALIZABLE_TEXT_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "ilocalizable_text_t.h"
#include "intrusive_ptr_t.h"
#include "status_t.h"

namespace uasdk
{

template <typename T> class ArrayUA_t;
class String_t;
class LocalizedText_t;

/** \addtogroup grpMiscellaneous
 *@{*/

class ILocalizableText_t : public IRefCount_t
{
public:
  /*****************************************************************************/
  /** Get Localised Text
   *
   * This function can be used to get the localised value from the array
   * of requested locales. If the none of the locales are matching in the
   * stored localised text a default localised text value will be returned.
   *
   * @param[in] locales
   * Array of the required locales
   *
   * @param[out] result
   * status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * localised text. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> GetLocalizedText(const ArrayUA_t<String_t>& locales,
                                                                 Status_t& result) const  = 0;

  /*****************************************************************************/
  /** Get default localized text
   *
   * @param[out] result
   * status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * localised text. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> GetLocalizedText(Status_t& result) const  = 0;

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<ILocalizableText_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  virtual Status_t CopyTo(IntrusivePtr_t<ILocalizableText_t>& destination) const = 0;

};

/** @} */

} // namespace uasdk

#endif // _ILOCALIZABLE_TEXT_T_
