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

#ifndef _OPCUA_BUILD_INFO_T_
#define _OPCUA_BUILD_INFO_T_


#include "opcua_string_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_application_type_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_server_state_t.h"
#include "opcua_date_time_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief BuildInfo_t
 *
 * This class implements the Build Information data type
 *
 */

class BuildInfo_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(BuildInfo_t);
private:

  /*****************************************************************************/
  /* @var String_t productUri
   *  Product URI
   */
  String_t      productUri;

  /*****************************************************************************/
  /* @var String_t manufacturerName
   * Manufacturer name
   */
  String_t      manufacturerName;

  /*****************************************************************************/
  /* @var String_t productName
   * Product Name
   */
  String_t	    productName;

  /*****************************************************************************/
  /* @var String_t softwareVersion
   * Software Version
   */
  String_t      softwareVersion;

  /*****************************************************************************/
  /* @var String_t buildNumber
   * Build Number
   */
  String_t      buildNumber;

  /*****************************************************************************/
  /* @var UtcTime_t  buildDate
   * Build Date
   */
  UtcTime_t  buildDate;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_BuildInfo;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BuildInfo_t();

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
  /** == operator overloading
   *
   * @param[in] const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(BuildInfo_t const & obj) const;

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
   * @param[in] BuildInfo_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS BuildInfo_t object is greater than RHS BuildInfo_t object
   */
  bool operator>(BuildInfo_t const & obj) const;

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
   * @param[in] const BuildInfo_t& source
   *  Build Information source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const BuildInfo_t& source);

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
  /** Get the Binary Encoding Id
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Binary Encoding Id
   */
  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the Product URI
   *
   * @return
   * Returns the Product URI
   */
  const String_t& ProductUri(void) const;

  /*****************************************************************************/
  /** Get the Product URI
   *
   * @return
   * Returns the Product URI
   */
  String_t& ProductUri(void);

  /*****************************************************************************/
  /** Get the manufacturer name
   *
   * @return
   * Returns the manufacturer name
   */
  const String_t& ManufacturerName(void) const;

  /*****************************************************************************/
  /** Get the manufacturer name
   *
   * @return
   * Returns the manufacturer name
   */
  String_t& ManufacturerName(void);

  /*****************************************************************************/
  /** Get the Product name
   *
   * @return
   * Returns the Product name
   */
  const String_t& ProductName(void) const;

  /*****************************************************************************/
  /** Get the Product name
   *
   * @return
   * Returns the Product name
   */
  String_t& ProductName(void);

  /*****************************************************************************/
  /** Get the Software version
   *
   * @return
   * Returns the Software version
   */
  const String_t& SoftwareVersion(void) const;

  /*****************************************************************************/
  /** Get the Software version
   *
   * @return
   * Returns the Software version
   */
  String_t& SoftwareVersion(void);

  /*****************************************************************************/
  /** Get the Build number
   *
   * @return
   * Returns the Build number
   */
  const String_t& BuildNumber(void) const;

  /*****************************************************************************/
  /** Get the Build number
   *
   * @return
   * Returns the Build number
   */
  String_t& BuildNumber(void);

  /*****************************************************************************/
  /** Get the Build Date
   *
   * @return
   * Returns the Build Date
   */
  const UtcTime_t& BuildDate(void) const;

  /*****************************************************************************/
  /** Get the Build Date
   *
   * @return
   * Returns the Build Date
   */
  UtcTime_t& BuildDate(void);

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
  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] BuildInfo_t& result
   * Decoded Build Information object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, BuildInfo_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BUILD_INFO_T_
