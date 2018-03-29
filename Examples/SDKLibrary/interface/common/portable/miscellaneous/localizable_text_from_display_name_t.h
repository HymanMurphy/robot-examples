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

#ifndef _LOCALIZABLE_TEXT_FROM_DISPLAY_NAME_T_
#define _LOCALIZABLE_TEXT_FROM_DISPLAY_NAME_T_

#include "opcua_string_t.h"
#include "intrusive_list_t.h"
#include "opcua_localized_text_t.h"
#include "ilocalizable_text_t.h"
#include "inode_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief LocalizableTextFromDisplayName_t
 *  Localized Text from the display name of the node
 *
 */
class LocalizableTextFromDisplayName_t : public Allocatable_t, public ILocalizableText_t
{
private:
  IntrusivePtr_t<INode_t> source;

public:
  /*****************************************************************************/
  /** Initialise the input node
  *
  * @param[in] IntrusivePtr_t<INode_t>& node
  * input node
  *
  * @return
  * status of the operation
  */
  Status_t Initialise(IntrusivePtr_t<INode_t>& node);  

  /*****************************************************************************/
  /** Get Localised Text
   *
   * This function can be used to get the localized value from the array
   * of requested locales. If the none of the locales are matching in the
   * stored localized text a default localized text value will be returned.
   *
   * @param[in] const ArrayUA_t<String_t>& sessionLocales
   * Array of the required locales
   *
   * @param[out] result
   * status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * Localized text. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> GetLocalizedText(const ArrayUA_t<String_t>& sessionLocales,
                                                                Status_t& result) const;

  /*****************************************************************************/
  /** Get default localized text
   *
   * @param[out] Status_t& result
   * status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * Localized text. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> GetLocalizedText(Status_t& result) const;

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<ILocalizableText_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  virtual Status_t CopyTo(IntrusivePtr_t<ILocalizableText_t>& destination) const;
};

/** @} */

} // namespace uasdk

#endif // _LOCALIZABLE_TEXT_FROM_DISPLAY_NAME_T_
