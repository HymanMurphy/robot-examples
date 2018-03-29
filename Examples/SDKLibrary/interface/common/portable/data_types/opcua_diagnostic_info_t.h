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

#ifndef _OPCUA_DIAGNOSTIC_INFO_T_
#define _OPCUA_DIAGNOSTIC_INFO_T_

#include "opcua_uint32_t.h"
#include "opcua_int32_t.h"
#include "opcua_string_t.h"
#include "opcua_status_code_t.h"
#include "opcua_localized_text_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief DataValue_t
 *
 * This class implements Diagnostic information data type
 *
 */
class DiagnosticInfo_t : public BaseDataType_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(DiagnosticInfo_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<Int32_t> symbolicId
   * An intrusive reference counting Boost-style smart pointer to the symbolic Id.
   */
  IntrusivePtr_t<Int32_t>          symbolicId;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<Int32_t> namespaceUri
   * An intrusive reference counting Boost-style smart pointer to the namespace URI.
   */
  IntrusivePtr_t<Int32_t>          namespaceUri;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<Int32_t>
   * An intrusive reference counting Boost-style smart pointer to the .
   */
  IntrusivePtr_t<Int32_t>          localizedText;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<Int32_t> localizedText
   * An intrusive reference counting Boost-style smart pointer to the localized Text.
   */
  IntrusivePtr_t<Int32_t>          locale;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<String_t> additionalInfo
   * An intrusive reference counting Boost-style smart pointer to the additional Information.
   */
  IntrusivePtr_t<String_t>         additionalInfo;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<StatusCode_t> innerStatusCode
   * An intrusive reference counting Boost-style smart pointer to the inner Status Code.
   */
  IntrusivePtr_t<StatusCode_t>     innerStatusCode;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<DiagnosticInfo_t> innerDiagnosticInfo
   * An intrusive reference counting Boost-style smart pointer to the inner Diagnostic Information.
   */
  IntrusivePtr_t<DiagnosticInfo_t> innerDiagnosticInfo;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_DiagnosticInfo;

  /*****************************************************************************/
  /** constructor for the class.
   *
   */
  DiagnosticInfo_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~DiagnosticInfo_t();

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  virtual bool operator==(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] const DiagnosticInfo_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the DiagnosticInfo_t object assigned
   */
  bool operator==(DiagnosticInfo_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If grater than RHS
   * False - If less than RHS
   */
  virtual bool operator>(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] DiagnosticInfo_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS DiagnosticInfo_t object is greater than RHS DiagnosticInfo_t object
   */
  bool operator>(DiagnosticInfo_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const DiagnosticInfo_t& source
   *  Diagnostic Information source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const DiagnosticInfo_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the Symbolic Id
   *
   * @return
   * Returns the Symbolic Id. An intrusive reference counting Boost-style
   * smart pointer to the Symbolic Id. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Int32_t> SymbolicId(void) const;

  /*****************************************************************************/
  /** Get the Symbolic Id
   *
   * @return
   * Returns the Symbolic Id. An intrusive reference counting Boost-style
   * smart pointer to the Symbolic Id. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<Int32_t>& SymbolicId(void);

  /*****************************************************************************/
  /** Get the Namespace URI
   *
   * @return
   * Returns the Namespace URI. An intrusive reference counting Boost-style
   * smart pointer to the Namespace URI. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Int32_t> NamespaceUri(void) const;

  /*****************************************************************************/
  /** Get the Namespace URI
   *
   * @return
   * Returns the Namespace URI. An intrusive reference counting Boost-style
   * smart pointer to the Namespace URI. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<Int32_t>& NamespaceUri(void);

  /*****************************************************************************/
  /** Get the Localized Text
   *
   * @return
   * Returns the Localized Text. An intrusive reference counting Boost-style
   * smart pointer to the Localized Text. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Int32_t> LocalizedText(void) const;

  /*****************************************************************************/
  /** Get the Localized Text
   *
   * @return
   * Returns the Localized Text. An intrusive reference counting Boost-style
   * smart pointer to the Localized Text. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<Int32_t>& LocalizedText(void);

  /*****************************************************************************/
  /** Get the Locale
   *
   * @return
   * Returns the Locale. An intrusive reference counting Boost-style
   * smart pointer to the Locale. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Int32_t> Locale(void) const;

  /*****************************************************************************/
  /** Get the Locale
   *
   * @return
   * Returns the Locale. An intrusive reference counting Boost-style
   * smart pointer to the Locale. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<Int32_t>& Locale(void);

  /*****************************************************************************/
  /** Get the Additional Information
   *
   * @return
   * Returns the Additional Information. An intrusive reference counting Boost-style
   * smart pointer to the Additional Information. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const String_t> AdditionalInfo(void) const;

  /*****************************************************************************/
  /** Get the Additional Information
   *
   * @return
   * Returns the Additional Information. An intrusive reference counting Boost-style
   * smart pointer to the Additional Information. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<String_t>& AdditionalInfo(void);

  /*****************************************************************************/
  /** Get the Inner Status Code
   *
   * @return
   * Returns the Inner Status Code. An intrusive reference counting Boost-style
   * smart pointer to the Inner Status Code. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const StatusCode_t> InnerStatusCode(void) const;

  /*****************************************************************************/
  /** Get the Inner Status Code
   *
   * @return
   * Returns the Inner Status Code. An intrusive reference counting Boost-style
   * smart pointer to the Inner Status Code. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<StatusCode_t>& InnerStatusCode(void);

  /*****************************************************************************/
  /** Get the Inner Diagnostic Information
   *
   * @return
   * Returns the Inner Diagnostic Information. An intrusive reference counting Boost-style
   * smart pointer to the Inner Diagnostic Information. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const DiagnosticInfo_t> InnerDiagnosticInfo(void) const;

  /*****************************************************************************/
  /** Get the Inner Diagnostic Information
   *
   * @return
   * Returns the Inner Diagnostic Information. An intrusive reference counting Boost-style
   * smart pointer to the Inner Diagnostic Information. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<DiagnosticInfo_t>& InnerDiagnosticInfo(void);

  /*****************************************************************************/
  /** Encode the buffer
   *
   * @param[in] ICodec_t& encoder
   * Reference to the encoder object
   *
   * @param[out] IBuffer_t& buffer
   * Encode buffer
   *
   * @return
   * Returns status of the operation
   */
  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] DiagnosticInfo_t& result
   * Decoded DiagnosticInfo_t object object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DiagnosticInfo_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_DIAGNOSTIC_INFO_T_
