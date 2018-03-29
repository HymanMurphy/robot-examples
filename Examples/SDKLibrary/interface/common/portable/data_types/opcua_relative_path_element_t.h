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

#ifndef _OPCUA_RELATIVE_PATH_ELEMENT_T_
#define _OPCUA_RELATIVE_PATH_ELEMENT_T_

#include "opcua_structure_t.h"
#include "opcua_node_id_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_boolean_t.h"
#include "opcua_qualified_name_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief RelativePathElement_t
 *
 * This class implements the Relative Path Element data type
 *
 */
class RelativePathElement_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(RelativePathElement_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> referenceTypeId
   * An intrusive reference counting Boost-style smart pointer to the reference type ID.
   */
  IntrusivePtr_t<NodeId_t>      referenceTypeId;

  /*****************************************************************************/
  /* @var Boolean_t isInverse
   * Is inverse
   */
  Boolean_t                     isInverse;

  /*****************************************************************************/
  /* @var Boolean_t includeSubtypes
   * Include subtypes
   */
  Boolean_t                     includeSubtypes;

  /*****************************************************************************/
  /* @var QualifiedName_t target name
   * target name
   */
  QualifiedName_t               targetName;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_RelativePathElement;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~RelativePathElement_t();

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
   * @param[in] const RelativePathElement_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Relative Path Element object assigned
   */
  bool operator==(RelativePathElement_t const & obj) const;

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
   * @param[in] RelativePathElement_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS RelativePathElement_t object is greater than RHS RelativePathElement_t object
   */
  bool operator>(RelativePathElement_t const & obj) const;

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
   * @param[in] const RelativePathElement_t& source
   *  Relative Path Element source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const RelativePathElement_t& source);

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
  /** Get the Reference type ID.
   *
   * @return
   * Returns the Reference type ID. An intrusive reference counting Boost-style
   * smart pointer to the Reference type ID. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const NodeId_t> ReferenceTypeId(void) const;


  /*****************************************************************************/
  /** Get the Reference type ID.
   *
   * @return
   * Returns the Reference type ID. An intrusive reference counting Boost-style
   * smart pointer to the Reference type ID. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<NodeId_t>& ReferenceTypeId(void);

  /*****************************************************************************/
  /** Get the "is inverse"
   *
   * @return
   * Return true if inverse
   */
  const Boolean_t& IsInverse(void) const;
  Boolean_t& IsInverse(void);

  /*****************************************************************************/
  /** Get the Include sub type
   *
   * @return
   * Returns the Include sub type
   */
  const Boolean_t& IncludeSubtypes(void) const;

  /*****************************************************************************/
  /** Get the Include sub type
   *
   * @return
   * Returns the Include sub type
   */
  Boolean_t& IncludeSubtypes(void);

  /*****************************************************************************/
  /** Get the target name
   *
   * @return
   * Returns the target name
   */
  const QualifiedName_t& TargetName(void) const;

  /*****************************************************************************/
  /** Get the target name
   *
   * @return
   * Returns the target name
   */
  QualifiedName_t& TargetName(void);

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
   * @param[out] RelativePathElement_t& result
   * Decoded Relative Path Element object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, RelativePathElement_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_RELATIVE_PATH_ELEMENT_T_
