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

#ifndef _OPCUA_AXIS_INFORMATION_T_H_
#define _OPCUA_AXIS_INFORMATION_T_H_

#include "opcua_structure_t.h"
#include "opcua_eu_information_t.h"
#include "opcua_range_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_axis_scale_enumeration_t.h"
#include "opcua_array_ua_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief AxisInformation_t
 *
 * This class implements the Axis information data type
 *
 */
class AxisInformation_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(AxisInformation_t);

private:

  /*****************************************************************************/
  /* @var EUInformation_t engineeringUnits;
   * Engineering units
   */
  EUInformation_t                         engineeringUnits;

  /*****************************************************************************/
  /* @var Range_t eURange;
   * Range
   */
  Range_t                                 eURange;

  /*****************************************************************************/
  /* @var LocalizedText_t title;
   * Title
   */
  LocalizedText_t                         title;

  /*****************************************************************************/
  /* @var AxisScaleEnumeration_t axisScaleType;
   * Axis scale tye
   */
  AxisScaleEnumeration_t                  axisScaleType;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ArrayUA_t<Double_t> > axisSteps;
   * Axis steps
   */
  IntrusivePtr_t<ArrayUA_t<Double_t> >    axisSteps;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_AxisInformation;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~AxisInformation_t();

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
   * @param[in] AxisInformation_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects member variables are same
   * False - If the both the objects member variables are not same
   */
  bool operator==(AxisInformation_t const & obj) const;

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
   * @param[in] AxisInformation_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects member variables are greater in values
   * False - If the both the objects member variables are not greater
   */
  bool operator>(AxisInformation_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[in] IntrusivePtr_t<BaseDataType_t>& destination
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
  /** Copy from the source AxisInformation
   *
   * @param[in] const AxisInformation_t& source
   *  Source Axis Information to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const AxisInformation_t& source);

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
  /** Get the Engineering Units
   *
   * @return
   * Returns the Engineering Units
   */
  const EUInformation_t& EngineeringUnits(void) const;

  /*****************************************************************************/
  /** Get the Engineering Units
   *
   * @return
   * Returns the Engineering Units
   */
  EUInformation_t& EngineeringUnits(void);

  /*****************************************************************************/
  /** Get the Engineering Unit range
   *
   * @return
   * Returns the Engineering Unit range
   */
  const Range_t& EURange(void) const;

  /*****************************************************************************/
  /** Get the Engineering Unit range
   *
   * @return
   * Returns the Engineering Unit range
   */
  Range_t& EURange(void);

  /*****************************************************************************/
  /** Get the Title
   *
   * @return
   * Returns the Title
   */
  const LocalizedText_t& Title(void) const;

  /*****************************************************************************/
  /** Get the Title
   *
   * @return
   * Returns the Title
   */
  LocalizedText_t& Title(void);

  /*****************************************************************************/
  /** Get the Axis Scale Type
   *
   * @return
   * Returns the Axis Scale Type
   */
  const AxisScaleEnumeration_t& AxisScaleType(void) const;

  /*****************************************************************************/
  /** Get the Title
   *
   * @return
   * Returns the Axis Scale Type
   */
  AxisScaleEnumeration_t& AxisScaleType(void);

  /*****************************************************************************/
  /** Get the Axis Steps
   *
   * @return
   * Returns the Axis Steps. An intrusive reference counting Boost-style smart pointer to the
   * array with Double_t data type. The caller must test the pointer before dereferencing it.
   */
  const IntrusivePtr_t<ArrayUA_t<Double_t> >& AxisSteps(void) const;

  /*****************************************************************************/
  /** Get the Axis Steps
   *
   * @return
   * Returns the Axis Steps. An intrusive reference counting Boost-style smart pointer to the
   * array with Double_t data type. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<ArrayUA_t<Double_t> >& AxisSteps(void);

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
   * @param[out] AxisInformation_t& result
   * Decoded Axis Information object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, AxisInformation_t& result);
};

/** @} */

} //namespace uasdk

#endif

#endif /* _OPCUA_AXIS_INFORMATION_T_H_ */
