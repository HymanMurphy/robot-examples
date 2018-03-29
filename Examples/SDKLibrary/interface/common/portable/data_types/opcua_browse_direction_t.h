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

#ifndef _OPCUA_BROWSE_DIRECTION_T_
#define _OPCUA_BROWSE_DIRECTION_T_

#include "opcua_enumeration_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief BrowseDirection_t
 *
 * This class implements the Browse Direction data type
 *
 */

class BrowseDirection_t : public Enumeration_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration of the Browse Direction
   */
  UA_DECLARE_RUNTIME_TYPE(BrowseDirection_t);

  typedef enum
  {
    DIRECTION_FORWARD = 0,
    DIRECTION_INVERSE = 1,
    DIRECTION_BOTH = 2,
    DIRECTION_INVALID = 3,
    DIRECTION_END
  } Enum_t;

private:

  /*****************************************************************************/
  /* @var Enum_t value
   * Browse direction value
   */
  Enum_t value;

  /*****************************************************************************/
  /* This function used to write the integer value to Enum type
   *
   * Integer value for the enumeration
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteIntToValue(int32_t newValue);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_BrowseDirection;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  BrowseDirection_t(void);

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] Enum_t value
   * Browse direction value to be set
   *
   */
  BrowseDirection_t(Enum_t value);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BrowseDirection_t();

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
   * @param[in] const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(BrowseDirection_t const & obj) const;

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
   * @param[in] BrowseDirection_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS BrowseDirection_t object is greater than RHS BrowseDirection_t object
   */
  bool operator>(BrowseDirection_t const & obj) const;

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
   * @param[in] const BrowseDirection_t& source
   *  BrowseDirection_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const BrowseDirection_t& source);

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
  /** Get the Browse Direction value
   *
   * @return
   * Returns the Browse Direction value
   */
  const BrowseDirection_t::Enum_t& Value(void) const;

  /*****************************************************************************/
  /** Get the Browse Direction value
   *
   * @return
   * Returns the Browse Direction value
   */
  BrowseDirection_t::Enum_t& Value(void);

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

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BROWSE_DIRECTION_T_
