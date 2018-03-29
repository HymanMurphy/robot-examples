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

#ifndef _OPCUA_AXIS_SCALE_ENUMERATION_T_H_
#define _OPCUA_AXIS_SCALE_ENUMERATION_T_H_

#include "opcua_enumeration_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief AxisScaleEnumeration_t
 *
 * This class implements the Axis Scale Enumeration data type
 *
 */
class AxisScaleEnumeration_t : public Enumeration_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration for axis scale defenitions
   *
   */
  UA_DECLARE_RUNTIME_TYPE(AxisScaleEnumeration_t);

  typedef enum
  {
    OPCUA_AXIS_SCALE_ENUMERATION_LINEAR_0 = 0,
    OPCUA_AXIS_SCALE_ENUMERATION_LOG_1 = 1,
    OPCUA_AXIS_SCALE_ENUMERATION_LN_2 = 2,
    OPCUA_AXIS_SCALE_ENUMERATION_END
  } Enum_t;

private:

  /*****************************************************************************/
  /* @var Enum_t value
   * Axis Scale value
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
  static const uint32_t TYPE_ID = OpcUaId_AxisScaleEnumeration;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  AxisScaleEnumeration_t(void);

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] uint8_t val
   * Axis Scale Enumeration
   */
  AxisScaleEnumeration_t(Enum_t value);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~AxisScaleEnumeration_t(void);

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
   * @param[in] AxisScaleEnumeration_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the Axis Scales are same
   * False - If the both the Axis Scales are not same
   */
  bool operator==(AxisScaleEnumeration_t const & obj) const;

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
   * @param[in] AnonymousIdentityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the Axis Scale is LHS is greater
   * False - If the both the Axis Scale is LHS is not greater
   */
  bool operator>(AxisScaleEnumeration_t const & obj) const;

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
   * @param[in] const AxisScaleEnumeration_t& source
   * Source Axis Scale Enumeration object to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const AxisScaleEnumeration_t& source);

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
  /** Get the Axis Scale value
   *
   * @return
   * Returns the Axis Scale value
   */
  const AxisScaleEnumeration_t::Enum_t& Value(void) const;

  /*****************************************************************************/
  /** Get the  Axis Scale value
   *
   * @return
   * Returns the Axis Scale value
   */
  AxisScaleEnumeration_t::Enum_t& Value(void);

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

};

/** @} */

} //namespace uasdk

#endif

#endif /* _OPCUA_AXIS_SCALE_ENUMERATION_T_H_ */
