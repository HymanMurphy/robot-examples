/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef _LOCALIZABLE_TEXT_TRANSLATE_T_
#define _LOCALIZABLE_TEXT_TRANSLATE_T_

#include "uasdk_default_build_config.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "opcua_string_t.h"
#include "ilocalizable_text_t.h"

namespace uasdk
{
/** \addtogroup grpServer_C_API
*@{*/

/*****************************************************************************/
/** \brief LocalizableTextStored_t
*  Localized Text Store
*
*/

class LocalizableTextTranslateForCAPI_t : public ILocalizableText_t, public Allocatable_t
{
private:
  uintptr_t textHandle;
  IntrusivePtr_t<const ArrayUA_t<String_t> > localeIdArray;

  /*****************************************************************************/
  /** Get Preferred Text
  *
  * This function can be used to get the preferred text from the array
  * of requested locales.
  *
  * @param[in] const ArrayUA_t<String_t>& sessionLocales
  * Session Locales
  *
  * @param[out] locale
  * locale of matched text
  *
  * @param[out] result
  * result of operation
  *
  * @return
  * index in the locale id array
  */
  uint16_t GetLocaleIndex(const ArrayUA_t<String_t>& sessionLocales, IntrusivePtr_t<String_t>& locale, Status_t& result) const;

public:

  /*****************************************************************************/
  /** Add the text handle
  *
  * @param[in] textHandle_
  * handle to text
  */
  void AddTextHandle(uintptr_t textHandle_);

  /*****************************************************************************/
  /** Add the text handle
  *
  * @param[in] localesIdArray_
  * An intrusive reference counting Boost-style smart pointer to the
  * Array of locale Ids. The caller must test the pointer before dereferencing it.
  */
  void AddLocaleIdArray(IntrusivePtr_t<const ArrayUA_t<String_t> >& localesIdArray_);

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

/*@}*/
} // uasdk

#endif //UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
#endif // _LOCALIZABLE_TEXT_TRANSLATE_T_
