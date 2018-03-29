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

#ifndef _ARRAY_ITEM_T_
#define _ARRAY_ITEM_T_

#include "data_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_range_t.h"
#include "opcua_eu_information_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_axis_scale_enumeration_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief ArrayItem_t
*
* A class that represents a ArrayItem_t in the addressSpace.
*
*/
class ArrayItem_t : public DataItem_t
{
public:
  typedef struct
  {
    Range_t                 euRange;
    EUInformation_t         engineeringUnits;
    LocalizedText_t         title;
    AxisScaleEnumeration_t  axisScaleType;
  } MandatoryPropertyValues_t;

  typedef struct
  {
    uint32_t  euRangeIdentifier;
    uint32_t  engineeringUnitsIdentifier;
    uint32_t  titleIdentifier;
    uint32_t  axisScaleTypeIdentifier;
  } MandatoryPropertyNumericIds_t;

protected:

  ArrayItem_t();
  virtual ~ArrayItem_t();

  static bool IsDataTypeValid(uint32_t datatype);

  void DeleteProperties(ArrayItem_t& item);

  /*****************************************************************************/
  /** This  function used to create property mandatory property for ArrayItem.
   *
   * @param[in] item
   *  Node to which mandatory item to be added
   *
   * @param[in] propertyIdentifier
   * Ids for property
   *
   * @param[in/out] value
   * Mandatory Property Values.
   *
   * @returns
   * returns status of the operation.
   */
  static Status_t CreateArrayMandatoryProperty( ArrayItem_t& item,
                                                const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                                const MandatoryPropertyValues_t& value);
public:

  /*****************************************************************************/
  /** This  function used to create Instrument range.property
   *
   * @param[in/out] value
   * Range_t value .
   *
   * @returns
   * returns status of the operation.
   */
  Status_t CreateInstrumentRangeProperty(const Range_t& value);

  /*****************************************************************************/
  /** This  function used to create Instrument range.property with numeric node id
   *
   * @param[in] nodeIdentifier
   * Node Identifier.
   *
   * @param[in/out] value
   * Range_t value .
   *
   * @returns
   * returns status of the operation.
   */
  Status_t CreateInstrumentRangeProperty(uint32_t nodeIdentifier, const Range_t& value);

  /*****************************************************************************/
  /** Function used to get Instrument range node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> InstrumentRangeNode(void);

  /*****************************************************************************/
  /**  This const function used to create Instrument range node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> InstrumentRangeNode(void) const;

  /*****************************************************************************/
  /**  This function used to get Instrument range values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Range_t> GetInstrumentRangeValue(Status_t& result);

  /*****************************************************************************/
  /**  This function used to set Instrument range values.
   *
   * @param[in/out] value
   * Instrument Range Value to be set.
   *
   * @returns
   * returns status of the operation.
   */
  Status_t SetInstrumentRangeValue(const Range_t& value);

  /*****************************************************************************/
  /**  This function used to get EU range node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> EURangeNode(void);

  /*****************************************************************************/
  /**  This const function used to get EU range node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> EURangeNode(void) const;

  /*****************************************************************************/
  /**  This function used to get EU range value.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * Range value The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Range_t> GetEURangeValue(Status_t& result);

  /*****************************************************************************/
  /**  This function used to set EU range value.
   *
   * @param[in/out] value
   * EU Range Value to be set.
   *
   * @returns
   * returns status of the operation.
   */
  Status_t SetEURangeValue(const Range_t& value);

  /*****************************************************************************/
  /**  This  function used to get Engineering Units Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> EngineeringUnitsNode(void);

  /*****************************************************************************/
  /**  This const function used to get Engineering Units Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> EngineeringUnitsNode(void) const;

  /*****************************************************************************/
  /**  This  function used to get Engineering Units values.
   *
   * @param[in/out] result
   *  status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * EUInformaiton Value. The caller must test the pointer before dereferencing it.
   */

  IntrusivePtr_t<const EUInformation_t> GetEngineeringUnitsValue(Status_t& result);

  /*****************************************************************************/
  /**  This  function used to set Engineering Units values.
   *
   * @param[in/out] value
   *  Engineering Units Value to be set.
   *
   * @returns
   * returns IntrusivePtr_t const EUInformation_t value.
   */
  Status_t SetEngineeringUnitsValue(const EUInformation_t& value);

  /*****************************************************************************/
  /**  This  function used to get Title Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> TitleNode(void);

  /*****************************************************************************/
  /**  This const function used to get a Title Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> TitleNode(void) const;

  /*****************************************************************************/
  /** Function used to Get Title Value.
   *
   * @param[in/out] result
   *  status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * localized text. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const LocalizedText_t> GetTitleValue(Status_t& result);

  /*****************************************************************************/
  /** Function used to Set Title Value.
   *
   * @param[in/out] value
   *  Title Value to be set.
   *
   * @returns
   * returns IntrusivePtr_t const LocalizedText_t value.
   */
  Status_t SetTitleValue(const LocalizedText_t& value);

  /*****************************************************************************/
  /**  This  function used to get Axis Scale Type Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> AxisScaleTypeNode(void);

  /*****************************************************************************/
  /**  This const function used to get Axis Scale Type Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> AxisScaleTypeNode(void) const;

  /*****************************************************************************/
  /** Function used to Get Axis Scale Type Value.
   *
   * @param[in/out] result
   *  status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * AxisScaleEnumeration value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const AxisScaleEnumeration_t> GetAxisScaleTypeValue(Status_t& result);

  /*****************************************************************************/
  /** Function used to Set Axis Scale Type Value.
   *
   * @param[in/out] value
   * Axis Scale Type Value to be set.
   *
   * @returns
   * returns status of the operation.
   */
  Status_t SetAxisScaleTypeValue(const AxisScaleEnumeration_t& value);
};

/** @} */

}

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _ARRAY_ITEM_T_ */
