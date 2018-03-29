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

#ifndef _OPCUA_APPLICATION_TYPE_T_
#define _OPCUA_APPLICATION_TYPE_T_

#include "opcua_enumeration_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ApplicationType_t
 *
 * This class implements the Application Type data type
 *
 */
class ApplicationType_t : public Enumeration_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration of Application Type
   *
   */
  UA_DECLARE_RUNTIME_TYPE(ApplicationType_t);

  typedef enum
  {
    OPCUA_APPLICATION_TYPE_SERVER = 0,
    OPCUA_APPLICATION_TYPE_CLIENT = 1,
    OPCUA_APPLICATION_TYPE_CLIENT_AND_SERVER = 2,
    OPCUA_APPLICATION_TYPE_DISCOVERY_SERVER = 3,
    OPCUA_APPLICATION_TYPE_END
  } Enum_t;

private:

  /*****************************************************************************/
  /* @var Enum_t value
   * Application Type is stored in value
   */
  Enum_t value;

  /*****************************************************************************/
  /* This function used to write the integer value to Enum type
   *
   * Integer value for the enumeration
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteIntToValue(int32_t newValue);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ApplicationType;

  /*****************************************************************************/
  /** default constructor for the class.
   *
   */
  ApplicationType_t(void);

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] Enum_t value
   * Application type to set
   *
   */
  ApplicationType_t(Enum_t value);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ApplicationType_t(void);

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
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the application IDs are same
   * False - If the both the application IDs are not same
   */
  bool operator==(ApplicationType_t const & obj) const;

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
   * @param[in] ApplicationType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the LHS application ID is greater
   * False - If the both the RHS application ID is greater
   */
  bool operator>(ApplicationType_t const & obj) const;

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
   * @param[in] const ApplicationType_t& source
   * Application Type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const ApplicationType_t& source);

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
  /** Get the Application Type
   *
   * @return
   * Returns the Application Type
   */
  const ApplicationType_t::Enum_t& Value(void) const;

  /*****************************************************************************/
  /** Get the Application Type
   *
   * @return
   * Returns the Application Type
   */
  ApplicationType_t::Enum_t& Value(void);

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
  // static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ApplicationType_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_APPLICATION_TYPE_T_
