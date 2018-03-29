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

#ifndef _OPCUA_QUALIFIED_NAME_T_
#define _OPCUA_QUALIFIED_NAME_T_

#include "opcua_string_t.h"
#include "opcua_uint16_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief QualifiedName_t
 *
 * This class implements the Qualified name data type
 *
 */
class QualifiedName_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(QualifiedName_t);

public:

private:

  /*****************************************************************************/
  /* @var UInt16_t namespaceIndex
   * Name space index
   */
	UInt16_t namespaceIndex;

  /*****************************************************************************/
  /* @var String_t name
   * Name
   */
  String_t name;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_QualifiedName;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  QualifiedName_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~QualifiedName_t();

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
   * @param[in] QualifiedName_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(QualifiedName_t const & obj) const;

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
   * @param[in] QualifiedName_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS QualifiedName_t object is greater than RHS QualifiedName_t object
   */
  bool operator>(QualifiedName_t const & obj) const;

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
   * @param[in] const QualifiedName_t& source
   *  QualifiedName_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const QualifiedName_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the name space index
   *
   * @return
   * Returns the Locale value
   */
  const UInt16_t&  NamespaceIndex(void) const;

  /*****************************************************************************/
  /** Get the name space index
   *
   * @return
   * Returns the name space index
   */
  UInt16_t&  NamespaceIndex(void);

  /*****************************************************************************/
  /** Get the name
   *
   * @return
   * Returns the name
   */
  const String_t& Name(void) const;

  /*****************************************************************************/
  /** Get the name
   *
   * @return
   * Returns the name
   */
  String_t& Name(void);

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
   * @param[out] QualifiedName_t& result
   * Decoded QualifiedName_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, QualifiedName_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_QUALIFIED_NAME_T_
