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

#ifndef TWO_STATE_DISCRETE_T_H_
#define TWO_STATE_DISCRETE_T_H_

#include "discrete_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "opcua_localized_text_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief TwoStateDiscrete_t
*
* A class that represents a TwoStateDiscrete_t in the address space.
*
*/
class TwoStateDiscrete_t : public DiscreteItem_t
{
public:
  typedef struct
  {
    uint32_t trueState;
    uint32_t falseState;
  }MandatoryPropertyNumericIds_t;

  typedef struct
  {
    LocalizedText_t trueState;
    LocalizedText_t falseState;
  }MandatoryPropertyValues_t;

private:

  /*****************************************************************************/
  /**This function used to creates TwoStateDiscrete property.
   *
   * @param[in] twoStateDiscrete
   * TwoStateDiscrete_t object.
   *
   * @param[in] propertyIdentifier
   * Property Identifier.
   *
   * @param[in] propertyName
   * property Name.
   *
   * @param[in] PropertyType
   * Property Type.
   *
   * @param[in] value
   * AxisInformation_t value.
   *
   * @param[out] propertyNode
   * IVariableNode_t property Node.
   *
   * @returns
   * returns status of the operation.
   */
  static Status_t CreateProperty(TwoStateDiscrete_t& twoStateDiscrete,
                                 uint32_t propertyIdentifier,
                                 const char* propertyName,
                                 uint32_t propertyType,
                                 const LocalizedText_t& value,
                                 IntrusivePtr_t<IVariableNode_t>& propertyNode);

  /*****************************************************************************/
  /**This function used to create TwoStateDiscrete
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> CreateTwoStateDiscrete(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                   Status_t& result);


  /*****************************************************************************/
  /**This function Creates two state discrete with mandatory property.
   *
   * @param[in] node_
   * IVariableNode_t node.
   *
   * @param[in] addressSpace_
   * IAddressSpace_t object.
   *
   * @param[in] ids
   * Mandatory Properties Id to create two state discrete.
   *
   * @param[in] values
   * Mandatory Properties Values to create two state discrete.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> CreateTwoStateDiscreteWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                        const MandatoryPropertyNumericIds_t& ids,
                                                                                        const MandatoryPropertyValues_t& values,
                                                                                        Status_t& result);

  //*****************************************************************************/
  /**Function used to get the TwoStateDiscrete Node's property value.
   *
   * @param[in] propertyNode
   * IVariableNode_t object.
   *
   * @param[out]result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * Value. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<const LocalizedText_t> GetLocalizedTextValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result);

  /*****************************************************************************/
  /**This function used to delete the properties.
   *
   * @param[in/out] twoStateDiscreteItem
   * item which to be delete.
   *
   */
  static void DeleteProperties(TwoStateDiscrete_t& twoStateDiscreteItem);

protected:
  TwoStateDiscrete_t();

public:

  virtual ~TwoStateDiscrete_t();

  /*
   * Properties
   */
  /*****************************************************************************/
  /**This function used to get the TrueState node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   *
   */
  IntrusivePtr_t<IVariableNode_t> TrueStateNode(void);

  /*****************************************************************************/
  /**This function used to get TrueState node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> TrueStateNode(void) const;

  /*****************************************************************************/
  /**This function used to get the TrueState value
   *
   * @param[out] result
   * values which is to be store.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const LocalizedText_t> GetTrueStateValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to set the TrueState value
   *
   * @param[in/out] value
   * values which is to be set.
   *
   * @return
   * returns the status of the operation.
   *
   */
  Status_t SetTrueStateValue(const LocalizedText_t& value);

  /*****************************************************************************/
  /**This function used to get the FalseState node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<IVariableNode_t> FalseStateNode(void);

  /*****************************************************************************/
  /**This const function used to get the FalseState Node.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const IVariableNode_t> FalseStateNode(void) const;

  /*****************************************************************************/
  /**This function used to get FalseState value.
   *
   * @param[in/out] value
   * values which is to be store.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const LocalizedText_t> GetFalseStateValue(Status_t& result);

  /*****************************************************************************/
  /**This function used to set the FalseState value.
   *
   * @param[in/out] value
   * values which is to be store.
   *
   * @return
   * returns status of the operation
   *
   */
  Status_t SetFalseStateValue(const LocalizedText_t& value);

  /*
   * Wrapper creation
   */

  /*****************************************************************************/
  /** Functon used to get the existing node as TwoState Discrete
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
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> Get(const NodeId_t& nodeId,
                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                Status_t& result);

  /*****************************************************************************/
  /** Functon used to get the existing node as TwoState Discrete
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
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */

  static IntrusivePtr_t<TwoStateDiscrete_t> Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                Status_t& result);

  /*****************************************************************************/
  /** This template function used to create two state discrete with Numeric Id.
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
   * @param[in] propertyIdentifier
   * property identifiers.
   *
   * @param[in] propertyValue
   * MandatoryPropertyValues_t values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                                uint32_t nodeIdentifier,
                                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                const String_t& browseName,
                                                                const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                                                const MandatoryPropertyValues_t& propertyValue,
                                                                Status_t& result);


  /*****************************************************************************/
  /** This template function to create two state discrete with string Id.
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
   * @param[in] propertyValue
   * Mandatory property values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> CreateWithStringId(uint16_t namespaceIndex,
                                                               const String_t& nodeIdentifier,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               const MandatoryPropertyValues_t& propertyValue,
                                                               Status_t& result);


  /*****************************************************************************/
  /** This template function to create two state discrete with GUID.
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
   * @param[in] propertyValue
   * Mandatory property values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                             const Guid_t& nodeIdentifier,
                                                             IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                             const String_t& browseName,
                                                             const MandatoryPropertyValues_t& propertyValue,
                                                             Status_t& result);

  /*****************************************************************************/
  /** This template function to create two state discrete with Opaque Id.
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
   * @param[in] propertyValue
   * Mandatory property values.
   *
   * @param[out] result
   * status of the operation.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TwoStateDiscrete. The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<TwoStateDiscrete_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                               const ByteString_t& nodeIdentifier,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               const String_t& browseName,
                                                               const MandatoryPropertyValues_t& propertyValue,
                                                               Status_t& result);
};

/** @} */

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS

#endif /* TWO_STATE_DISCRETE_T_H_ */
