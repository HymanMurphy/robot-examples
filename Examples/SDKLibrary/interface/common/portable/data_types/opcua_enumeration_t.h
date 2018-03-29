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

#ifndef _OPCUA_ENUMERATION_T_
#define _OPCUA_ENUMERATION_T_


#include "opcua_identifiers.h"
#include "opcua_base_data_type_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief CallMethodResult_t
 *
 * This class implements the Enumeration data type
 *
 */
class Enumeration_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(Enumeration_t);
private:

  Enumeration_t & operator=(Enumeration_t const &);
  Enumeration_t(Enumeration_t const &);

  /*****************************************************************************/
  /** This function used to write integer value to the enum
   *
   * @param[in] newValue
   * new value to be written to enumeration type
   *
   * @return
   * Returns status of the operation
   */
  virtual Status_t WriteIntToValue(int32_t newValue) = 0;

protected:

  /*****************************************************************************/
  /** This function used write int32_t value to enum
   *
   * When client tries to write data to enum type, data is encoded as int32_t.
   * So,to write this int32_t value to enum this function is used.
   *
   * @param[in] source
   * Source type with value
   *
   * @return
   * Returns status of the operation
   */
  Status_t TryCopyFromInt32(const BaseDataType_t& source);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Enumeration;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  Enumeration_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Enumeration_t();
  
  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] Enumeration_t& result
   * Decoded Enumeration object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, Enumeration_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_ENUMERATION_T_
