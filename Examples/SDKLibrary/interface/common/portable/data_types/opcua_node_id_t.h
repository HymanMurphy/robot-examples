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

#ifndef _OPCUA_NODE_ID_T_
#define _OPCUA_NODE_ID_T_


#include "ibuffer_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint16_t.h"
#include "opcua_string_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_guid_t.h"

#define LOG_ERROR_UA_NODEID LOG_ERROR_HEADER(UA_NODEID_FILENAME)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief NodeId_t
 *
 * This class implements the Node ID data type
 */
class NodeId_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(NodeId_t);

  /*****************************************************************************/
  /** \brief Enumeration of Node identifier types
   */
  typedef enum
  {
    NODEID_IDENTIFIER_NUMERIC = 0,
    NODEID_IDENTIFIER_STRING  = 1,
    NODEID_IDENTIFIER_GUID    = 2,
    NODEID_IDENTIFIER_OPAQUE  = 3,
    NODEID_IDENTIFIER_INVALID = 4
  } NodeIdIdentifierType_t;

protected:

  /*****************************************************************************/
  /* @var UInt16_t namespaceIndex
   * Namesapce index
   */
  UInt16_t namespaceIndex;

  /*****************************************************************************/
  /** copy Constructor for the class.
   *
   * @param[in] NodeId_t const &
   * Node ID object to copy from
   */
  NodeId_t(NodeId_t const &);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_NodeId;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  NodeId_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~NodeId_t();

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
  /** Copy to the Node ID
   *
   * @param[out] IntrusivePtr_t<NodeId_t>& destination
   * Destination data to copy to
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyToNodeId(IntrusivePtr_t<NodeId_t>& destination) const = 0;

  /*****************************************************************************/
  /** Get the Name space index of the node ID
   *
   * @return
   * Returns the Name space index of the node ID
   */
  const UInt16_t& NamespaceIndex(void) const;

  /*****************************************************************************/
  /** Get the Name space index of the node ID
   *
   * @return
   * Returns the Name space index of the node ID
   */
  UInt16_t& NamespaceIndex(void);

  /*****************************************************************************/
  /** Get the Node ID Identifier Type
   *
   * @return
   * Returns the Node ID Identifier Type
   */
  virtual NodeIdIdentifierType_t NodeIdIdentiferType(void) const = 0;

  /*****************************************************************************/
  /** Get the Identifier Base
   *
   * @return
   * Returns the Identifier Base.
   */
  virtual const BaseDataType_t& IdentiferBase(void) const = 0;

  /*****************************************************************************/
  /** Get the Identifier Base
   *
   * @return
   * Returns the Identifier Base.
   */
  virtual BaseDataType_t& IdentiferBase(void) = 0;

  /*****************************************************************************/
  /** Check if the GUID is null or not
   *
   * @return
   * Returns true if the GUID is null.
   */
  virtual bool IsNull(void) const = 0;

  /*****************************************************************************/
  /** Hash
   *
   * @return
   * Returns hash value
   */
  virtual uint32_t Hash(void) const = 0;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] IntrusivePtr_t<NodeId_t>& result
   * Decoded Node ID
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer,
                         ICodec_t& decoder,
                         IntrusivePtr_t<NodeId_t>& result);

};

/*****************************************************************************/
/** Duplicate the node id
 *
 * @param[in] const T& source
 * Source node ID
 *
 * @param[out] IntrusivePtr_t<NodeId_t>& destination
 * Destination Node ID
 *
 * @return
 * Returns status of the operation
 */
template<typename T>
Status_t DuplicateNodeId(const T& source, IntrusivePtr_t<NodeId_t>& destination)
{
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<T> data(new SafeRefCount_t<T>());
  if(!data.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  status = data->CopyFrom(source);
  if(status.IsBad())
  {
    return status;
  }

  destination = data;

  return OpcUa_Good;
}

/** @} */

} //namespace uasdk

#endif // _OPCUA_NODE_ID_T_
