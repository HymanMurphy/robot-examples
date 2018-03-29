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

#ifndef _OPCUA_BASE_DATA_TYPE_T_
#define _OPCUA_BASE_DATA_TYPE_T_


#include "allocatable_t.h"
#include "iref_count_t.h"
#include "opcua_iruntime_type_t.h"

#include "opcua_identifiers.h"
#include "intrusive_ptr_t.h"
#include "iref_count_t.h"
#include "allocatable_t.h"
#include "status_t.h"
#include "uasdk_includes.h"
#include "safe_ref_count_t.h"

namespace uasdk
{

class Int32_t;
class ITypeVisitor_t;
class IBuffer_t;
class IndexRange_t;
template<typename T> class Array_t;
class ICodec_t;

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Argument_t
 *
 * This class implements the base data type
 *
 */
class BaseDataType_t
  : public Allocatable_t
  , public IRefCount_t
  , public IRuntimeType_t
{
private:
  BaseDataType_t& operator=(BaseDataType_t const &);
  BaseDataType_t(BaseDataType_t const &);

protected:

  /*****************************************************************************/
  /** Get the Reference count
   *
   * @return
   * Returns the Reference count
   */
  virtual int RefCount(void) const;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  UA_DECLARE_RUNTIME_TYPE(BaseDataType_t);
  
  static const uint32_t TYPE_ID = OpcUaId_BaseDataType;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  BaseDataType_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BaseDataType_t();

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
  virtual bool operator==(BaseDataType_t const & obj) const = 0;

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are not same
   * False - If the both the objects are same
   */
  bool operator!=(BaseDataType_t const & obj) const;

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
  virtual bool operator>(BaseDataType_t const & obj) const = 0;

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const = 0;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const = 0;

  /*****************************************************************************/
  /** Write the subset of array elements to destination array
   *
   * @param[in] const Array_t<IndexRange_t>& indexRanges
   *  Array index range to copy the data from
   *
   * @param[in] IntrusivePtr_t<BaseDataType_t>& destination
   *  Destination array
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source) = 0;

  /*****************************************************************************/
  /** Write the subset of array elements from the source array
   *
   * @param[in] const Array_t<IndexRange_t>& indexRanges
   *  Array index range
   *
   * @param[in] const BaseDataType_t& source
   *  Source array
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteSubsetFrom(const Array_t<IndexRange_t>& indexRange, const BaseDataType_t& source);

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
  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const = 0;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] Argument_t& result
   * Decoded argument object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer,
                         ICodec_t& decoder,
                         IntrusivePtr_t<BaseDataType_t>& result);

  /*****************************************************************************/
  /** Check if the data type is array
   *
   * @return
   * Returns true if array data type.
   */
  virtual bool IsArray(void) const;

  /*****************************************************************************/
  /** Check if the array stores the number element
   *
   * @return
   * True - If the data is a number
   * False - If the data is a not a number
   */
  virtual bool IsNumber(void) const;

  /*****************************************************************************/
  /** Add reference for reference counting utility
   *
   */
  virtual void AddReference() const;

  /*****************************************************************************/
  /** Remove reference for reference counting utility
   *
   */
  virtual void RemoveReference() const;
};

template<typename T> bool OperatorGreaterThan(T& a, BaseDataType_t const & b)
{
  uint16_t namespaceIndexA = 0;
  uint16_t namespaceIndexB = 0;

  if (a.TypeId(namespaceIndexA) != b.TypeId(namespaceIndexB))
  {
    return false;
  }
  if (namespaceIndexA != namespaceIndexB)
  {
    return false;
  }
  return (a > static_cast<T const&>(b));
}

template<typename T> bool OperatorEqualTo(T& a, BaseDataType_t const & b)
{
  uint16_t namespaceIndexA = 0;
  uint16_t namespaceIndexB = 0;

  if (a.TypeId(namespaceIndexA) != b.TypeId(namespaceIndexB))
  {
    return false;
  }
  if (namespaceIndexA != namespaceIndexB)
  {
    return false;
  }
  return (a == static_cast<T const&>(b));
}

/*****************************************************************************/
/** Copy to destination
 *
 * @param[in] T& source
 * Source data
 *
 * @param[in] IntrusivePtr_t<BaseDataType_t>& destination
 * Destination object
 *
 * @return
 * Status of the operation
 */
template<typename T>
Status_t CopyToDestination(const T& source, IntrusivePtr_t<BaseDataType_t>& destination)
{
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<T> ptr( new SafeRefCount_t<T>() );
  if (!ptr.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  status = ptr->CopyFrom(source);
  if(status.IsBad())
  {
    return status;
  }

  destination = ptr;

  return status;
}

/*****************************************************************************/
/** Check the if the data in both the objects are same
 *
 * @param[in] const IntrusivePtr_t<T>& a
 * Object to compare
 *
 * @param[in] const IntrusivePtr_t<T>& b
 * Object to compare
 *
 * @return
 * Return true if equal
 */
template<typename T>
bool Equal(const IntrusivePtr_t<T>& a, const IntrusivePtr_t<T>& b)
{
  if ((!a.is_set() && b.is_set())
      || (a.is_set() && !b.is_set()))
  {
    return false;
  }
  if (a.is_set() && b.is_set() && (*a != *b))
  {
    return false;
  }
  return true;
}

/*****************************************************************************/
/** Greater than Operator overloading helper method
 *
 * @param[in] const IntrusivePtr_t<T>& a
 * LHS object to compare with
 *
 * @param[in] const BaseDataType_t& b
 * RHS object to compare with
 *
 * @return
 * Return true if greater
 */
template<typename T>
bool GreaterThan(const IntrusivePtr_t<T>& a, const IntrusivePtr_t<T>& b)
{
  if ((!a.is_set() && b.is_set())
      || (a.is_set() && !b.is_set()))
  {
    return false;
  }
  if (a.is_set() && b.is_set() && !(*a > *b))
  {
    return false;
  }
  return true;
}

/*****************************************************************************/
/** Greater than Operator overloading helper method
 *
 * @param[in] const T& data
 * Data type to be checked for "is vector?"
 *
 * @return
 * Return true if the data type is vector
 */
template<typename T>
bool IsVector(const T& data)
{
  uint16_t namespaceIndex = 0;
  if( data.TypeId(namespaceIndex) == OpcUaId_ByteString
      || data.TypeId(namespaceIndex) == OpcUaId_String
      || data.TypeId(namespaceIndex) == OpcUaId_XmlElement )
  {
    return true;
  }

  return false;
}

/** @} */

} // namespace uasdk
#endif // _OPCUA_BASE_DATA_TYPE_T_
