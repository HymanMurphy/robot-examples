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

#ifndef _OPCUA_EVENT_SEVERITY_T_
#define _OPCUA_EVENT_SEVERITY_T_

#include "opcua_base_data_type_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_enumeration_t.h"

namespace uasdk
{

/** \addtogroup grpEventsandAC
 *@{*/

/*****************************************************************************/
/** \brief EventSeverity_t
 *
 * This class implements the Event Severity data type
 *
 */
class EventSeverity_t : public Enumeration_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(EventSeverity_t);

  /*****************************************************************************/
  /** \brief Enumeration of Event Severity
   */
  typedef enum 
  {
    OPCUA_EVENT_SEVERITY_MAX  = 1000,
		OPCUA_EVENT_SEVERITY_HIGH  = 900,
		OPCUA_EVENT_SEVERITY_MEDIUM_HIGH = 700,
		OPCUA_EVENT_SEVERITY_MEDIUM = 500,
		OPCUA_EVENT_SEVERITY_MEDIUM_LOW = 300,
		OPCUA_EVENT_SEVERITY_LOW = 100,
		OPCUA_EVENT_SEVERITY_MIN = 1
  } Enum_t;

private:

  /*****************************************************************************/
  /* @var Enum_t value
   *  Event Severity value
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
  static const uint32_t TYPE_ID = OpcUaId_UInt32;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
	EventSeverity_t(void);

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] Enum_t value
   * Event severity to be assigned
   */
	EventSeverity_t(Enum_t value);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~EventSeverity_t();

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
   * @param[in] const EventSeverity_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Event Severity object assigned
   */
  bool operator==(EventSeverity_t const & obj) const;

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
   * @param[in] EventSeverity_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS EventSeverity_t object is greater than RHS EventSeverity_t object
   */
  bool operator>(EventSeverity_t const & obj) const;

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
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const EventSeverity_t& source
   * Event Severity source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const EventSeverity_t& source);

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
  /** Get the Event Severity value
   *
   * @return
   * Returns the Event Severity value
   */
  const EventSeverity_t::Enum_t& Value(void) const;

  /*****************************************************************************/
  /** Get the Event Severity value
   *
   * @return
   * Returns the Event Severity value
   */
	EventSeverity_t::Enum_t& Value(void);

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

};

/** @} */

} // namespace uasdk

#endif //UASDK_INCLUDE_EVENTS

#endif // _OPCUA_EVENT_SEVERITY_T_
