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

#ifndef _OPCUA_DATA_CHANGE_FILTER_T_
#define _OPCUA_DATA_CHANGE_FILTER_T_

#include "opcua_string_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_range_t.h"
#include "opcua_data_value_t.h"
#include "opcua_structure_t.h"
#include "opcua_double_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief CallMethodRequest_t
 *
 * This class implements the Data change filter data type
 *
 */
class DataChangeFilter_t : public Structure_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration of data change trigger
   */

  UA_DECLARE_RUNTIME_TYPE(DataChangeFilter_t);

  typedef enum 
  {
    OPCUA_DATACHANGE_TRIGGER_STATUS                 = 0,
    OPCUA_DATACHANGE_TRIGGER_STATUS_VALUE           = 1,
    OPCUA_DATACHANGE_TRIGGER_STATUS_VALUE_TIMESTAMP = 2,
    OPCUA_DATACHANGE_TRIGGER_END
  } DataChangeTrigger_t;

  /*****************************************************************************/
  /* @var uint32_t DEADBAND_TYPE_NONE
   * Deadband type none
   */
  static const uint32_t DEADBAND_TYPE_NONE;

  /*****************************************************************************/
  /* @var uint32_t DEADBAND_TYPE_ABSOLUTE
   * Absolute Deadband type
   */
  static const uint32_t DEADBAND_TYPE_ABSOLUTE;

  /*****************************************************************************/
  /* @var uint32_t DEADBAND_TYPE_absolute
   * Percent Deadband type
   */
  static const uint32_t DEADBAND_TYPE_PERCENT;

private:

  /*****************************************************************************/
  /* @var DataChangeTrigger_t trigger
   * Data change trigger
   */
  DataChangeTrigger_t trigger;

  /*****************************************************************************/
  /* @var UInt32_t deadbandType
   * Dead band type
   */
  UInt32_t deadbandType;

  /*****************************************************************************/
  /* @var Double_t deadbandValue
   * Dead band value
   */
  Double_t deadbandValue;

  /*****************************************************************************/
  /** CalculateDeadbandScalar
   *
   * @param[in] BaseDataType_t const & newValue
   * New Value
   *
   * @param[in] BaseDataType_t const & previousValue
   * Previous Value
   *
   * @return
   * Deadband scalar
   */
  bool CalculateDeadbandScalar(const BaseDataType_t& newValue, const BaseDataType_t& previousValue,
    Range_t& euRange);

  /*****************************************************************************/
  /** CalculateDeadbandScalar
   *
   * @param[in] BaseDataType_t const & newValue
   * New Value
   *
   * @param[in] BaseDataType_t const & previousValue
   * Previous Value
   *
   * @return
   * Deadband vector
   */
  bool CalculateDeadbandVector(const BaseDataType_t& newValue, const BaseDataType_t& previousValue,
    Range_t& euRange);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_DataChangeFilter;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  DataChangeFilter_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~DataChangeFilter_t();

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] const CallMethodRequest_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the CallMethodRequest_t object assigned
   */
  DataChangeFilter_t& operator=(DataChangeFilter_t const &);

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
   * @param[in] DataChangeFilter_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(DataChangeFilter_t const & obj) const;

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
   * @param[in] DataChangeFilter_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS DataChangeFilter_t object is greater than RHS DataChangeFilter_t object
   */
  bool operator>(DataChangeFilter_t const & obj) const;

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
   * @param[in] const DataChangeFilter_t& source
   *  Data Change Filter source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const DataChangeFilter_t& source);

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
  /** Get the data change trigger.
   *
   * @return
   * Returns the data change trigger.
   */
  const DataChangeFilter_t::DataChangeTrigger_t& Trigger(void) const;

  /*****************************************************************************/
  /** Get the data change trigger.
   *
   * @return
   * Returns the data change trigger.
   */
  DataChangeFilter_t::DataChangeTrigger_t& Trigger(void);

  /*****************************************************************************/
  /** Get the deadband type
   *
   * @return
   * Returns the deadband type
   */
  const UInt32_t& DeadbandType(void) const;

  /*****************************************************************************/
  /** Get the deadband type
   *
   * @return
   * Returns the deadband type
   */
  UInt32_t& DeadbandType(void);

  /*****************************************************************************/
  /** Get the deadband value
   *
   * @return
   * Returns the deadband value
   */
  const Double_t& DeadbandValue(void) const;

  /*****************************************************************************/
  /** Get the deadband value
   *
   * @return
   * Returns the deadband value
   */
  Double_t& DeadbandValue(void);

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
   * @param[out] DataChangeFilter_t& result
   * Decoded Data Change Filter object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DataChangeFilter_t& result);

  /*****************************************************************************/
  /** Does Value Pass Filter
   *
   * @param[in] DataValue_t& newValue
   * New Value
   *
   * @param[in] DataValue_t& previousValue
   * Previous Value
   *
   * @param[in] Range_t& euRange
   *
   *
   * @return
   * True on Value Pass filter
   */
  bool DoesValuePassFilter(DataValue_t& newValue, DataValue_t& previousValue, Range_t& euRange);

  /*****************************************************************************/
  /** Calculate Deadband Scalar
   *
   * @param[in] UASDK_DEADBAND_DATA_TYPE newValue
   * New Value
   *
   * @param[in] UASDK_DEADBAND_DATA_TYPE previousValue
   * Previous Value
   *
   * @param[in] Range_t& euRange
   *
   *
   * @return
   * Deadband scalar
   */
  bool CalculateDeadbandScalar(UASDK_DEADBAND_DATA_TYPE newValue, UASDK_DEADBAND_DATA_TYPE previousValue, Range_t& euRange);
};

/** @} */

} // namespace uasdk

#endif

#endif // _OPCUA_DATA_CHANGE_FILTER_T_
