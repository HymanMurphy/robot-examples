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

#ifndef _ANALOG_ITEM_T_
#define _ANALOG_ITEM_T_

#include "data_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

namespace uasdk
{

class Range_t;
class EUInformation_t;

/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief AnalogItem_t
*
* A class that represents a AnalogItem_t in the addressSpace.
*
*/
class AnalogItem_t : public DataItem_t
{
  private:

 /*****************************************************************************/
 /** This function checks whether the data type is valid or not.for analog item
  *
  * @param[in] datatype
  * datatype, which is to be check for validity
  *
  * @return
  * returns boolean status
  */
    static bool IsDataTypeValid(uint32_t datatype);

  /*****************************************************************************/
  /** This function used to create the property
   *
   * @param[in] analogItem
   * AnalogItem_t object.
   *
   * @param[in] propertyIdentifier
   * property Identifier.
   *
   * @param[in] propertyName
   * Name of the property.
   *
   * @param[in] propertyType
   * Property which needs to create.
   *
   * @param[in] value
   * BaseDataType_t object value.
   *
   * @param[out] propertyNode
   * Node which is to be create the opcUa property.
   *
   * @return
   * returns status of the operation.
   */
    static Status_t CreateProperty(AnalogItem_t& analogItem,
                                   uint32_t propertyIdentifier,
                                   const char* propertyName,
                                   uint32_t propertyType,
                                   const BaseDataType_t& value,
                                   IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
  /** This function used to create the EU Range property
   *
   * @param[in] analogItem
   * analogItem used to get the eu range node..
   *
   * @param[in] euRangeIdentifier
   * EU Range Identifier Identifier.
   *
   * @param[in] euRangeValue
   * EU Range Value.
   *
   * @return
   * returns status of the operation.
   */
    static Status_t CreateEURangeProperty(AnalogItem_t& analogItem,
                                          uint32_t euRangeIdentifier,
                                          const Range_t& euRangeValue);

  /*****************************************************************************/
  /** This function creates the analog item.
   *
   * @param[in] node_
   * IVariableNode_t type node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * returns AnalogItem_t value.
   */
    static IntrusivePtr_t<AnalogItem_t> CreateAnalogItem(IntrusivePtr_t<IVariableNode_t>& node_,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         Status_t& result);

  /*****************************************************************************/
  /** This function creates the analog item with mandatory property.
   *
   * @param[in] node_
   * IVariableNode_t type node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in ] euRangeIdentifier
   * EU Range Identifier.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * returns AnalogItem_t value.
   */
    static IntrusivePtr_t<AnalogItem_t> CreateAnalogItemWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                              uint32_t euRangeIdentifier,
                                                                              const Range_t& euRangeValue,
                                                                              Status_t& result);

   /*****************************************************************************/
   /** This template function used to get the value of the property.
    *
    * @param[in/out] propertyNode
    * propertyNode value.
    *
    * @param[out] result
    * status of the operation.
    *
    * @return
    * returns appropriate const class instance.
    */
    template <typename T>
    static IntrusivePtr_t<const T> GetPropertyValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result);

   /*****************************************************************************/
   /** This function used to delete the properties which all has already created.
    *
    * @param[in/out] analogItem
    * delete the property which is created from analog Item .
    */
    static void DeleteProperties(AnalogItem_t& analogItem);

  protected:
    AnalogItem_t();

  public:
    virtual ~AnalogItem_t();

    /*
     * Properties
     */

  /*****************************************************************************/
  /** Function used to get the EU range property node.
   *
   * @return
   * returns IntrusivePtr_t IVariableNode_t class value.
   */
    IntrusivePtr_t<IVariableNode_t> EURangeNode(void);

  /*****************************************************************************/
  /** const function used to get the EU range property node.
   *
   * @return
   * returns IntrusivePtr_t const IVariableNode_t class value.
   */
    IntrusivePtr_t<const IVariableNode_t> EURangeNode(void) const;

  /*****************************************************************************/
  /** Function used to get the EU range value.
   *
   * @return
   * returns IntrusivePtr_t const Range_t class value.
   */
    IntrusivePtr_t<const Range_t> GetEURangeValue(Status_t& result);

  /*****************************************************************************/
  /** Function used to set the EU range value.
   *
   * @param[in] value
   * value which needs to set for EU range.
   *
   * @return
   * returns status of the operation.
   */
    Status_t SetEURangeValue(const Range_t& value);

  /*****************************************************************************/
  /** Function used to Create Instrument Range Property.
   *
   * @param[in] value
   * value which needs to Create Instrument Range Property.
   *
   * @return
   * returns status of the operation.
   */
    Status_t CreateInstrumentRangeProperty(const Range_t& value);

  /*****************************************************************************/
  /** Function used to Create Instrument Range Property.
   *
   *@param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] value
   * value which needs to Create Instrument Range Property.
   *
   * @return
   * returns status of the operation.
   */
    Status_t CreateInstrumentRangeProperty(uint32_t nodeIdentifier, const Range_t& value);

  /*****************************************************************************/
    /** Function used to get the property node.
     *
     * @return
     * returns IntrusivePtr_t IVariableNode_t class value.
     */
    IntrusivePtr_t<IVariableNode_t> InstrumentRangeNode(void);

   /*****************************************************************************/
   /** Function used to get the property node.
    *
    * @return
    * returns intrusivePtr_t  const IVariableNode_t class value.
    */
    IntrusivePtr_t<const IVariableNode_t> InstrumentRangeNode(void) const;

    /*****************************************************************************/
    /** Function used to Get Instrument Range Value.
     *
     * @param[out] result
     * value which is to be get into the buff.
     *
     * returns intrusivePtr_t  const Range_t class value.
     */
    IntrusivePtr_t<const Range_t> GetInstrumentRangeValue(Status_t& result);

    /*****************************************************************************/
    /** Function used to Set Instrument Range Value.
     *
     * @param[in/out] value
     * value which is to be Set as a instrument range.
     *
     * returns status of the operation..
     */
    Status_t SetInstrumentRangeValue(const Range_t& value);


    /*****************************************************************************/
    /** Function used to Create Engineering Units Property.
     *
     * @param[in/out] value
     * value which is to be Create for Engineering Units.
     *
     * returns status of the operation..
     */
    Status_t CreateEngineeringUnitsProperty(const EUInformation_t& value);

    /*****************************************************************************/
    /** Function used to Create Engineering Units Property.
     *
     *@param[in] nodeIdentifier
     * node Identifier.
     *
     * @param[in/out] value
     * value which is to be Create for Engineering Units.
     *
     * returns status of the operation..
     */
    Status_t CreateEngineeringUnitsProperty(uint32_t nodeIdentifier, const EUInformation_t& value);

   /*****************************************************************************/
   /** Function used to get the Engineering Units Node property.
    *
    *  @returns
    *  returns IntrusivePtr_t IVariableNode_t value
    */
    IntrusivePtr_t<IVariableNode_t> EngineeringUnitsNode(void);

    /*****************************************************************************/
    /** Function used to get the Engineering Units Node property.
     *
     * @returns
     * returns IntrusivePtr_t const IVariableNode_t value
     */
    IntrusivePtr_t<const IVariableNode_t> EngineeringUnitsNode(void) const;

    /*****************************************************************************/
   /** Function used to get the Engineering Units values.
    *
    * @param[in] result
    * value to be store
    *
    * @returns
    * returns IntrusivePtr_t const EUInformation_t value.
    */
    IntrusivePtr_t<const EUInformation_t> GetEngineeringUnitsValue(Status_t& result);

    /*****************************************************************************/
      /** Function used to set the Engineering Units values.
       *
       * @param[in] value
       * value to be set
       *
       * @returns
       * returns status of the operation.
       */
    Status_t SetEngineeringUnitsValue(const EUInformation_t& value);

    /*
     * Wrapper creation
     */
    /*****************************************************************************/
   /** This function is used to get the variable node as Analog item node
    *  get the node.
    *
    * @param[in] nodeId
    * const Variable node id which needs to find in the address space.
    *
    * @param[in] addressSpace_
    * IAddressSpace_t object.
    *
    * @param[out] result
    * node value
    *
    * @returns
    * returnsIntrusivePtr_t AnalogItem_t value.
    */
    static IntrusivePtr_t<AnalogItem_t> Get(const NodeId_t& nodeId,
                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                            Status_t& result);

    /*****************************************************************************/
      /** Function checks the type definition to  get the node value
       *  get the node.
       *
       * @param[in] nodeId
       *  Variable node id which needs to find in the address space.
       *
       * @param[in] addressSpace_
       * IAddressSpace_t object.
       *
       * @param[out] result
       * node value
       *
       * @returns
       * returnsIntrusivePtr_t AnalogItem_t value.
       */
    static IntrusivePtr_t<AnalogItem_t> Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                            Status_t& result);

    /*****************************************************************************/
    /** This template Function to create property  With Numeric Id.
     *
     * @param[in] namespaceIndex
     * namespace Index.
     *
     * @param[in] nodeIdentifier
     * node Identifier.
     *
     * @param[in] addressSpace_
     * IAddressSpace_t object.
     *
     * @param[in] browseName
     * Browse Name.
     *
     * @param[in] euRangeIdentifier
     * EU Range Identifier.
     *
     * @param[in] euRangeValue
     * EU Range Value.
     *
     * @param[out] result
     * status of the operation.
     *
     * @returns
     * returns IntrusivePtr_t AnalogItem_t value.
     */
    template<typename T>
    static IntrusivePtr_t<AnalogItem_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                            uint32_t nodeIdentifier,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            const String_t& browseName,
                                                            uint32_t euRangeIdentifier,
                                                            const Range_t& euRangeValue,
                                                            Status_t& result);


    /*****************************************************************************/
    /** This template Function to create property  with string Id.
     *
     * @param[in] namespaceIndex
     * namespace Index.
     *
     * @param[in] nodeIdentifier
     * node Identifier.
     *
     * @param[in] addressSpace_
     * IAddressSpace_t object.
     *
     * @param[in] browseName
     * Browse Name.
     *
     * @param[in] euRangeValue
     * EU Range Value.
     *
     * @param[out] result
     * status of the operation.
     *
     * @returns
     * returns IntrusivePtr_t AnalogItem_t value.
     */
    template<typename T>
    static IntrusivePtr_t<AnalogItem_t> CreateWithStringId(uint16_t namespaceIndex,
                                                           const String_t& nodeIdentifier,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           const String_t& browseName,
                                                           const Range_t& euRangeValue,
                                                           Status_t& result);

    /*****************************************************************************/
    /** This template Function to create property  with Gui Id.
     *
     * @param[in] namespaceIndex
     * namespace Index.
     *
     * @param[in] nodeIdentifier
     * node Identifier.
     *
     * @param[in] addressSpace_
     * IAddressSpace_t object.
     *
     * @param[in] browseName
     * Browse Name.
     *
     * @param[in] euRangeValue
     * EU Range Value.
     *
     * @param[out] result
     * status of the operation.
     *
     * @returns
     * returns IntrusivePtr_t AnalogItem_t value.
     */
    template<typename T>
    static IntrusivePtr_t<AnalogItem_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                         const Guid_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         const Range_t& euRangeValue,
                                                         Status_t& result);

  /*****************************************************************************/
  /** This template function to create property  with Opc queue Id.
   *
   * @param[in] namespaceIndex
   * namespace Index.
   *
   * @param[in] nodeIdentifier
   * node Identifier.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] browseName
   * Browse Name.
   *
   * @param[in] euRangeValue
   * EU Range Value.
   *
   * @param[out] result
   * status of the operation.
   *
   * @returns
   * returns IntrusivePtr_t AnalogItem_t value.
   */
    template<typename T>
    static IntrusivePtr_t<AnalogItem_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                           const ByteString_t& nodeIdentifier,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           const String_t& browseName,
                                                           const Range_t& euRangeValue,
                                                           Status_t& result);

};

template<typename T>
IntrusivePtr_t<AnalogItem_t> AnalogItem_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                               uint32_t nodeIdentifier,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               uint32_t euRangeIdentifier,
                                                               const Range_t& euRangeValue,
                                                               Status_t& result)
{
  if(!(AnalogItem_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<AnalogItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                  addressSpace_, browseName, OpcUaId_AnalogItemType, -2, result);

  return AnalogItem_t::CreateAnalogItemWithMandatoryProperty(node_, addressSpace_, euRangeIdentifier, euRangeValue, result);
}

template<typename T>
IntrusivePtr_t<AnalogItem_t> AnalogItem_t::CreateWithStringId(uint16_t namespaceIndex,
                                                              const String_t& nodeIdentifier,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              const Range_t& euRangeValue,
                                                              Status_t& result)
{
  if(!(AnalogItem_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<AnalogItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, T::TYPE_ID,
                                                                                 addressSpace_, browseName, OpcUaId_AnalogItemType, -2, result);

  return AnalogItem_t::CreateAnalogItemWithMandatoryProperty(node_, addressSpace_, 0, euRangeValue, result);
}

template<typename T>
IntrusivePtr_t<AnalogItem_t> AnalogItem_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                            const Guid_t& nodeIdentifier,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            const String_t& browseName,
                                                            const Range_t& euRangeValue,
                                                            Status_t& result)
{
  if(!(AnalogItem_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<AnalogItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                               browseName, OpcUaId_AnalogItemType, -2, result);

  return AnalogItem_t::CreateAnalogItemWithMandatoryProperty(node_, addressSpace_, 0, euRangeValue, result);
}

template<typename T>
IntrusivePtr_t<AnalogItem_t> AnalogItem_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                              const ByteString_t& nodeIdentifier,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              const Range_t& euRangeValue,
                                                              Status_t& result)
{
  if(!(AnalogItem_t::IsDataTypeValid(T::TYPE_ID)))
  {
    result = OpcUa_BadNotSupported;
    IntrusivePtr_t<AnalogItem_t> empty;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, T::TYPE_ID, addressSpace_,
                                                                                 browseName, OpcUaId_AnalogItemType, -2, result);

  return AnalogItem_t::CreateAnalogItemWithMandatoryProperty(node_, addressSpace_, 0, euRangeValue, result);
}

/** @} */

}

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* _ANALOG_ITEM_T_ */
