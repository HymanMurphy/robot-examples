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

#ifndef _METHOD_T_
#define _METHOD_T_

#include "helper_base_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_INCLUDE_METHOD_SERVICE_SET > 0))

#include "opcua_node_id_t.h"
#include "iaddress_space_t.h"

namespace uasdk
{

/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief Method_t
*
* A class that is a wrapper to create methods
*
*/
class Method_t : public HelperBase_t
{
private:
  /*****************************************************************************/
  /** This Function used to create Method with GUID
  *
  * @param[in] node_
  * Method Node
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * Method. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> CreateMethod(IntrusivePtr_t<IMethodNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result);

  /*****************************************************************************/
  /** This Function used to create Method with GUID
  *
  * @param[in] node_
  * Method Node
  *
  * @param[in] browseName
  * browse name.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] executable
  * executable.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * Method. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> CreateMethod(IntrusivePtr_t<const NodeId_t>& nodeId,
                                               const String_t& browseName,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               bool executable,
                                               Status_t& result);

protected:
  Method_t();

  /*****************************************************************************/
  /** This function deletes properties.
  *
  * @param[in] dataItem
  * data item which is to be delete.
  *
  */

  static void DeleteProperties(Method_t& method);

public:
  virtual ~Method_t();

  /*****************************************************************************/
  /** This function used to get Input Argument Property node
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  IntrusivePtr_t<IVariableNode_t> InputArguments(void);

  /*****************************************************************************/
  /** This function used to get the Output Argument property node
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  IntrusivePtr_t<const IVariableNode_t> InputArguments(void) const;

  /*****************************************************************************/
  /** This function used to get Output Argument Property node
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  IntrusivePtr_t<IVariableNode_t> OutputArguments(void);

  /*****************************************************************************/
  /** This function used to get the Input Argument property node
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  IntrusivePtr_t<const IVariableNode_t> OutputArguments(void) const;

  /*****************************************************************************/
  /** This function gets the Method node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<IMethodNode_t> GetMethodNode(void);

  /*****************************************************************************/
  /** This const function used to get the Method node.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  *
  */
  IntrusivePtr_t<const IMethodNode_t> GetMethodNode(void) const;

  /*****************************************************************************/
  /** This Function used to Add Array Dimension to argument
  *
  * @param[in] arrayDimensions
  * Array Dimension
  *
  * @param[in/out] result
  * argument with added array Dimenstion.
  *
  * @return
  * Status of the operation
  */
  Status_t AddArrayDimensions(ArrayUA_t<UInt32_t>& arrayDimensions, IntrusivePtr_t<Argument_t>& result);

  /*****************************************************************************/
  /** This Function used to Add description to argument
  *
  * @param[in] Description
  * Add Description
  *
  * @param[in/out] result
  * argument with added array Dimenstion.
  *
  * @return
  * Status of the operation
  */
  Status_t AddDescription(LocalizedText_t& description, IntrusivePtr_t<Argument_t>& result);

  /*****************************************************************************/
  /** This Function used to create argument
  *
  * @param[in] name_
  * name of the argument
  *
  * @param[in] dataType_
  * datatype of the argument
  *
  * @param[in] valueRank_
  * value rank of the argument
  *
  * @param[out] result
  * Argument with the updated input argument
  *
  * @return
  * Status of the operation
  */
  Status_t CreateArgument(const char* name_, uint32_t dataType_, int32_t valueRank_, IntrusivePtr_t<Argument_t>& result);

  /*****************************************************************************/
  /** This Function used to create Input Argument Property
  *
  * @param[in] argument
  * array of arguments that needed to be added to Input Argument Property
  *
  * @return
  * Status of the operation
  */
  Status_t CreateInputArguments(ArrayUA_t<Argument_t>& argument);

  /*****************************************************************************/
  /** This Function used to create Input Argument Property
  *
  * @param[in] identifier
  * identifier of the property
  *
  * @param[in] argument
  * array of arguments that needed to be added to Input Argument Property
  *
  * @return
  * Status of the operation
  */
  Status_t CreateInputArguments(uint32_t identifier, ArrayUA_t<Argument_t>& argument);

  /*****************************************************************************/
  /** This Function used to create Output Argument Property
  *
  * @param[in] argument
  * array of arguments that needed to be added to Output Argument Property
  *
  * @return
  * Status of the operation
  */
  Status_t CreateOutputArguments(ArrayUA_t<Argument_t>& argument);

  /*****************************************************************************/
  /** This Function used to create Output Argument Property
  *
  * @param[in] identifier
  * identifier of the property
  *
  * @param[in] argument
  * array of arguments that needed to be added to Output Argument Property
  *
  * @return
  * Status of the operation
  */
  Status_t CreateOutputArguments(uint32_t identifier, ArrayUA_t<Argument_t>& argument);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  Method_t.
  *
  * @param[in] nodeId
  * Method node id which needs to find in the address space.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] result
  * node value
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> Get(const NodeId_t& nodeId,
    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
    Status_t& result);

  /*****************************************************************************/
  /** This function is used to get the existing node in the address space as
  *  Method_t.
  *
  * @param[in] node
  * method node which needs to find in the address space.
  *
  * @param[in] addressSpace_
  * IAddressSpace_t object.
  *
  * @param[out] result
  * node value
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * node. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> Get(IntrusivePtr_t<IMethodNode_t>& node,
    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
    Status_t& result);

  /*****************************************************************************/
  /** This Function used to create Method with Numeric Id.
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
  * @param[out] executable
  * executable.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderMethod. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> CreateWithNumericId(uint16_t namespaceIndex,
                                                      uint32_t nodeIdentifier,
                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                      const String_t& browseName,
                                                      bool executable,
                                                      Status_t& result);

  /*****************************************************************************/
  /** This Function is used to create Method node with sting Id.
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
  * @param[out] executable
  * executable.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderMethod. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> CreateWithStringId(uint16_t namespaceIndex,
                                                         const String_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         bool executable,
                                                         Status_t& result);

  /*****************************************************************************/
  /** This Function used to create Method with GUID
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
  * @param[out] executable
  * executable.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderMethod. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> CreateWithGuidId(uint16_t namespaceIndex,
                                                       const Guid_t& nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       bool executable,
                                                       Status_t& result);

  /*****************************************************************************/
  /** This Function is used to Method with Opaque item
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
  * @param[out] executable
  * executable.
  *
  * @param[out] result
  * status of the operation.
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * FolderMethod. The caller must test the pointer before dereferencing it.
  */
  static IntrusivePtr_t<Method_t> CreateWithOpaqueId(uint16_t namespaceIndex,
                                                         const ByteString_t& nodeIdentifier,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         bool executable,
                                                         Status_t& result);
};

/** @} */

} //namespace uasdk

#endif  //((UASDK_USE_HELPERS > 0) && (UASDK_INCLUDE_METHOD_SERVICE_SET > 0))

#endif  //_METHOD_T_