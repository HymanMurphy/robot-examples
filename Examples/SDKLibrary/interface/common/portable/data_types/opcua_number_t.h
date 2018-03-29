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

#ifndef _OPCUA_NUMBER_T_
#define _OPCUA_NUMBER_T_



#include "opcua_base_data_type_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Number_t
 *
 * This class implements the Number data type
 */
template<typename T>
class Number_t : public BaseDataType_t
{
public:
  UA_DEFINE_RUNTIME_TYPE_TMPL(Number_t, BaseDataType_t);
protected:

  /*****************************************************************************/
  /* @var T value
   * Number value
   */
  T value;

private:

  /*****************************************************************************/
  /** Hidden = Operator
   *
   * @param[in] NodeId_t const &
   * Node ID object to copy from
   */
  Number_t& operator=(Number_t const &);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Number;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Number_t() { value = T(); }

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] T value_
   * Number value to be assigned
   *
   */
  Number_t(T value_) { value = value_; }

  /*****************************************************************************/
  /** Copy constructor for the class.
   *
   * @param[in] Number_t const & other
   * Number object to be copied from
   *
   */
  Number_t(Number_t const & other) : BaseDataType_t() { value = other.value; }

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Number_t(void) { }

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
  virtual bool operator==(BaseDataType_t const & obj) const
  {
    return OperatorEqualTo(*this, obj);
  }
  
  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] Number_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Number_t const & obj) const
  {
    return (value == obj.value);
  }

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
  virtual bool operator>(BaseDataType_t const & obj) const
  {
    return OperatorGreaterThan(*this, obj);
  }
  
  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] Number_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Number_t object is greater than RHS Number_t object
   */
  bool operator>(Number_t const & obj) const
  {
    return (value > obj.value);
  }

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const Number_t& source
   *  Number_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Number_t<T>& source)
  {
    value = source.Value();

    return OpcUa_Good;
  }

  /*****************************************************************************/
  /** Check if the data is a number
   *
   * @return
   * Returns true if the data is a number
   */
  virtual bool IsNumber(void) const
  {
    return true;
  }

  /*****************************************************************************/
  /** Get the reference to the value
   *
   * @return
   * Returns the reference to the value
   */
  T& ValueRef(void) { return value; }

  /*****************************************************************************/
  /** Get the value
   *
   * @return
   * Returns the value
   */
  T Value(void) const { return value; }

  /*****************************************************************************/
  /** Set the value
   *
   * @param[in] Value to be set
   *
   */
  void Value(T val) { value = val; }
};

/** @} */

} //  namespace uasdk
#endif // _OPCUA_NUMBER_T_
