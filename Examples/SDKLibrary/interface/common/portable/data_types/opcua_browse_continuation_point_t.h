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

#ifndef _OPCUA_BROWSE_CONTINUATION_POINT_T_
#define _OPCUA_BROWSE_CONTINUATION_POINT_T_


#include "opcua_identifiers.h"
#include "intrusive_ptr_t.h"
#include "opcua_browse_direction_t.h"
#include "opcua_browse_description_t.h"
#include "opcua_uint16_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief BrowseContinuationPoint_t
 *
 * This class implements the Browse Continuation Point data type
 *
 */
class BrowseContinuationPoint_t : public ByteString_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(BrowseContinuationPoint_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t>  viewId
   * View id
   */
  IntrusivePtr_t<NodeId_t>  viewId;

  /*****************************************************************************/
  /* @var BrowseDescription_t nodeToBrowse
   * Node to browse
   */
  BrowseDescription_t       nodeToBrowse;

  /*****************************************************************************/
  /* @var UInt32_t maxRefsPerNode
   * Maximum Reference Per node
   */
  UInt32_t                  maxRefsPerNode;

  /*****************************************************************************/
  /* @var UInt32_t startingRefIndex
   * Starting reference index
   */
  UInt32_t                  startingRefIndex;

  /*****************************************************************************/
  /* @var bool isValid
   * Is valid
   */
  bool isValid;

  //TODO add references changed listener to continuation point to invalidate it on change

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ContinuationPoint;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  BrowseContinuationPoint_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BrowseContinuationPoint_t();

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
   * @param[in] BrowseContinuationPoint_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(BrowseContinuationPoint_t const & obj) const;

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
   * @param[in] BrowseContinuationPoint_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the first byte that does not match
   * in both the class member variables have a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(BrowseContinuationPoint_t const & obj) const;

  /*****************************************************************************/
  /** Get the View Id
   *
   * @return
   * Returns the View Id
   */
  IntrusivePtr_t<const NodeId_t> ViewId(void) const;

  /*****************************************************************************/
  /** Get the View Id
   *
   * @return
   * Returns the View Id
   */
  IntrusivePtr_t<NodeId_t>& ViewId(void);

  /*****************************************************************************/
  /** Get the Node To Browse
   *
   * @return
   * Returns the Node To Browse
   */
  const BrowseDescription_t& NodeToBrowse(void) const;

  /*****************************************************************************/
  /** Get the Node To Browse
   *
   * @return
   * Returns the Node To Browse
   */
  BrowseDescription_t& NodeToBrowse(void);

  /*****************************************************************************/
  /** Get the Max References Per Node
   *
   * @return
   * Returns the Max References Per Node
   */
  const UInt32_t& MaxRefsPerNode(void) const;

  /*****************************************************************************/
  /** Get the Max References Per Node
   *
   * @return
   * Returns the Max References Per Node
   */
  UInt32_t& MaxRefsPerNode(void);

  /*****************************************************************************/
  /** Get the Starting Reference Index
   *
   * @return
   * Returns the Starting Reference Index
   */
  const UInt32_t& StartingRefIndex(void) const;

  /*****************************************************************************/
  /** Get the Starting Reference Index
   *
   * @return
   * Returns the Starting Reference Index
   */
  UInt32_t& StartingRefIndex(void);

  /*****************************************************************************/
  /** Get the is valid flag
   *
   * @return
   * Returns the is valid flag
   */
  bool IsValid(void) const;

  /*****************************************************************************/
  /** Get the is valid flag
   *
   * @return
   * Returns the is valid flag
   */
  void IsValid(bool value);

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
   * @param[in] const ByteString_t& source
   *  Argument source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ByteString_t& source);

  /*****************************************************************************/
  /** Copy from the source
  *
  * @param[in] const BrowseContinuationPoint_t& source
  *  Argument source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const BrowseContinuationPoint_t& source);

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
  /** Configure the browse continuation point
   *
   * @param[in] IntrusivePtr_t<NodeId_t>& viewId_
   * View id
   *
   * @param[in] BrowseDescription_t& nodeToBrowse_
   * Node to browse
   *
   * @param[in] uint32_t maxRefsPerNode_
   * Maxmimum reference index
   *
   * @param[in] uint32_t startingRefIndex_
   * Starting reference index
   *
   * @return
   * Status of the operation
   */
  Status_t Configure(IntrusivePtr_t<NodeId_t>& viewId_, BrowseDescription_t& nodeToBrowse_,
                     uint32_t maxRefsPerNode_, uint32_t startingRefIndex_);

  /*****************************************************************************/
  /** Decode from the ByteString_t
  *
  * @return
  * Returns status of the operation
  */
  Status_t DecodeAndValidate(void);

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
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BROWSE_CONTINUATION_POINT_T_
