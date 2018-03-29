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

#ifndef _OPCUA_EXTENSIBLE_PARAMETER_T_
#define _OPCUA_EXTENSIBLE_PARAMETER_T_

#include "opcua_structure_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ExtensibleParameter_t
 *
 * This class implements Extensible Parameter data type
 *
 */
class ExtensibleParameter_t : public Structure_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(ExtensibleParameter_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<Structure_t> payload
   * An intrusive reference counting Boost-style smart pointer to the payload.
   */
  IntrusivePtr_t<Structure_t> payload;

public:

  /*****************************************************************************/
  /** constructor for the class.
   *
   */
  ExtensibleParameter_t();

  /*****************************************************************************/
  /** Initialiser for the class.
   *
   * @param[in] IntrusivePtr_t<T> const& payload_
   * Payload to be assigned
   *
   */
  template<typename T> void Initialise(IntrusivePtr_t<T> const& payload_)
  {
    payload = payload_;
  }

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ExtensibleParameter_t();

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
   * @param[in] const ExtensibleParameter_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the ExtensibleParameter_t object assigned
   */
  bool operator==(ExtensibleParameter_t const & obj) const;

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
   * @param[in] ExtensibleParameter_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ExtensibleParameter_t object is greater than RHS ExtensibleParameter_t object
   */
  bool operator>(ExtensibleParameter_t const & obj) const;

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
   * @param[in] const ExtensibleParameter_t& source
   *  Extensible Parameter source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ExtensibleParameter_t& source);

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
  /** Get the Binary Encoding Id
   *
   * @return
   * Returns the Binary Encoding Id
   */
  uint32_t BinaryEncodingId(void) const;

  /*****************************************************************************/
  /** Get the Payload
   *
   * @return
   * Returns the Payload. An intrusive reference counting Boost-style
   * smart pointer to the Payload. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const Structure_t> Payload(void) const;

  /*****************************************************************************/
  /** Get the Payload
   *
   * @return
   * Returns the Payload. An intrusive reference counting Boost-style
   * smart pointer to the Payload. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<Structure_t>& Payload(void);

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

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] ExtensibleParameter_t& result
   * Decoded ExtensibleParameter_t object object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer,
                              ICodec_t& decoder,
                              ExtensibleParameter_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_EXTENSIBLE_PARAMETER_T_
