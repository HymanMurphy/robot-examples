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

#ifndef _OPCUA_ARRAY_UA_BASE_T_
#define _OPCUA_ARRAY_UA_BASE_T_

#include "scoped_ptr_t.h"
#include "intrusive_list_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

template<typename T> class ArrayUA_t;

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ArrayUA_Base_t
 *
 * This class implements the Array  data type
 *
 */
class ArrayUA_Base_t : public BaseDataType_t
{
public:

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  UA_DECLARE_RUNTIME_TYPE(ArrayUA_Base_t);
  
  virtual ~ArrayUA_Base_t()
  { }

  /*****************************************************************************/
  /** Get the Array dimensions
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * array with Int32_t data type. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ArrayUA_t<Int32_t> > Dimensions(void) const = 0;

  /*****************************************************************************/
  /** Get the Array dimensions
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * array with Int32_t data type. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<ArrayUA_t<Int32_t> >& Dimensions(void) = 0;

  /*****************************************************************************/
  /** Get the size of the array
   *
   * @return
   * The size of the array
   */
  virtual uint32_t Size(void) const = 0;

  /*****************************************************************************/
  /** Get the value rank
   *
   * @return
   * Returns the value rank
   */
  virtual int32_t ValueRank(void) const = 0;

  /*****************************************************************************/
  /** Check if the data type is array
   *
   * @return
   * Returns true if array data type.
   */
  virtual bool IsArray(void) const
  {
    return true;
  }

  virtual Status_t EncodeExtensionObjects(ICodec_t& encoder, IBuffer_t& buffer) const = 0;
};

/** @} */

} // namespace uasdk

#endif // _OPCUA_ARRAY_UA_BASE_T_
