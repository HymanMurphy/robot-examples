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

#ifndef _OPCUA_STRUCTURE_T_
#define _OPCUA_STRUCTURE_T_


#include "opcua_node_id_t.h"
#include "opcua_identifiers.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ServerState_t
 *
 * This class implements the Structure_t data type
 *
 */
class Structure_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(Structure_t);
private:
  Structure_t & operator=(Structure_t const &);
  Structure_t(Structure_t const &);

public:
  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Structure;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  Structure_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Structure_t();

  /*****************************************************************************/
  /** Get the Binary Encoding Id
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Binary Encoding Id
   */
  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const = 0;

  /*****************************************************************************/
  /** Get the Binary Encoding Id
   *
   * @return
   * Returns the Binary Encoding Id
   */
  uint32_t BinaryEncodingId(void) const;

  /*****************************************************************************/
  /** Copy to the Structure
  *
  * @param[out] IntrusivePtr_t<Structure_t>& destination
  * Destination data to copy to
  *
  * @return
  * Status of the operation
  */
  Status_t CopyToStructure(IntrusivePtr_t<Structure_t>& destination) const;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] IntrusivePtr_t<Structure_t>& result
   * Decoded Structure
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<Structure_t>& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_STRUCTURE_T_
