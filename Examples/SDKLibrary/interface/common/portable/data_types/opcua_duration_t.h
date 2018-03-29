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

#ifndef _OPCUA_DURATION_T_
#define _OPCUA_DURATION_T_

#include "opcua_double_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Duration_t
 *
 * This class implements the Duration data type
 *
 */
class Duration_t : public Double_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(Duration_t);
public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Duration;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Duration_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] double val
   * Duration
   *
   */
  Duration_t(double val);

  /*****************************************************************************/
  /** Copy constructor for the class.
   *
   * @param[in] Duration_t const & other
   * Object to be copied
   *
   */
  Duration_t(Duration_t const & other);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Duration_t();

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
  /** = operator overloading
   *
   * @param[in] Duration_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the Double object assigned
   */
  Duration_t& operator=(Duration_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] double const & obj
   * Duration value to be assigned
   *
   * @return
   * Reference to the Double object assigned
   */
  Duration_t& operator=(double const & obj);

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
   * @param[in] Duration_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Duration_t const & obj) const;

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
   * @param[in] Duration_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Duration_t object is greater than RHS Duration_t object
   */
  bool operator>(Duration_t const & obj) const;

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
   * @param[in] const Duration_t& source
   *  Duration_t source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Duration_t& source);

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

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_DURATION_T_
