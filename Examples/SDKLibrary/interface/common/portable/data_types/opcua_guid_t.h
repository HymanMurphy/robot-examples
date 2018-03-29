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

#ifndef _OPCUA_GUID_T_
#define _OPCUA_GUID_T_

#include "iallocator_t.h"
#include "opcua_base_data_type_t.h"
#include "intrusive_ptr_t.h"
#include "scoped_ptr_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Guid_t
 *
 * This class implements the GUID  data type
 *
 */
class Guid_t : public BaseDataType_t
{
public:

  /*****************************************************************************/
  /* @var uint8_t GUID_LENGTH
   * length of the GUID
   */
  UA_DECLARE_RUNTIME_TYPE(Guid_t);

  static const uint8_t GUID_LENGTH = 16;

private:

  #define GUID_DATA_1         1
  #define GUID_DATA_2         2
  #define GUID_DATA_3         3
  #define GUID_DATA_4_PART_1  4
  #define GUID_DATA_4_PART_2  5

  //Number of Hex digits in each data filed
  #define GUID_HYPHENS_COUNT       4
  #define GUID_DATA_1_SIZE         8
  #define GUID_DATA_2_SIZE         4
  #define GUID_DATA_3_SIZE         4
  #define GUID_DATA_4_PART_1_SIZE  4
  #define GUID_DATA_4_PART_2_SIZE  12
  #define GUID_LENGTH_IN_STRING    (GUID_DATA_1_SIZE + GUID_DATA_2_SIZE + GUID_DATA_3_SIZE + \
                                      GUID_DATA_4_PART_1_SIZE + GUID_DATA_4_PART_2_SIZE + GUID_HYPHENS_COUNT)

  /*****************************************************************************/
  /* @var uint8_t data[GUID_LENGTH]
   * GUID
   */
  uint8_t data[GUID_LENGTH];

  /*****************************************************************************/
  /** Set Version for the GUID
   *
   */
  void SetVersion4Guid(void);

  /*****************************************************************************/
  /** swaping the characters with the given positions
  *
  * @param[in] pos1
  * position1 in which value has to be replaced value with position2
  *
  * @param[in] pos2
  * position2 in which value has to be replaced value with position1
  */
  void Swap(uint8_t pos1, uint8_t pos2);

  /*****************************************************************************/
  /** Reverse the characters with the given data field
  *
  * @param[in] dataField
  * data field which has to be reversed
  *
  * @param[in] pos2
  * position2 in which value has to be replaced value with position1
  */
  void Reverse(uint8_t dataField);

  /*****************************************************************************/
  /** Convert the given character to ASCII
  *
  * @param[in] value
  * value which has to be converted to ascii
  */
  void ConvertToAscii(uint8_t& value) const;
  /*****************************************************************************/
  /** Convert Guid to string
  *
  * @param[in] dataField
  * data filed which needs to be copied to result
  *
  * @param[in] position
  * location in the result in which converted guid data to be entered.
  *
  * @param[in] result
  * result where converted guid will be stored.
  */
  void ConvertGuidToString(uint8_t dataField, uint8_t position, uint8_t* result) const;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Guid;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] const uint8_t* data
   * GUID value to be set
   */
  Guid_t(const uint8_t* data);

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Guid_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Guid_t();

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
   * @param[in] Guid_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Guid_t const & obj) const;

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
   * @param[in] Guid_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Guid_t object is greater than RHS Guid_t object
   */
  bool operator>(Guid_t const & obj) const;

  /*****************************************************************************/
  /** Initalize the GUID
   *
   * @return
   * Staus of the operation
   */
  Status_t Initialise(void);

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] uint8_t* destination
   * Destination data to copy to
   *
   * @return
   * Status of the operation
   */
  Status_t CopyTo(uint8_t* destination) const;

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
   * @param[in] const uint8_t* source
   *  Source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const uint8_t* source);

//  Status_t CopyFrom(const uint8_t* source, const String_t& indexRange)
//  {
//    CopyFrom(source);
//
//    return OpcUa_Good;
//  }

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const Guid_t& source
   *  Guid_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Guid_t& source);

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
   * Name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the GUID
   *
   * @return
   * Returns the pointer to the GUID.
   */
  const uint8_t* Value(void) const;

  /*****************************************************************************/
  /** Get the GUID
   *
   * @return
   * Returns the pointer to the GUID.
   */
  uint8_t* Value(void);

  /*****************************************************************************/
  /** Check if the GUID is null or not
   *
   * @return
   * Returns true if the GUID is null.
   */
  bool IsNull(void) const;

  /*****************************************************************************/
  /** Convert to String
  *
  * @param[out] value
  * converted string value
  *
  * @return
  * Status of the operation
  */
  Status_t ToString(ScopedPtr_t< Array_t<uint8_t> >& value) const;

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

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] Guid_t& result
   * Decoded Guid_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, Guid_t& result);

};

/** @} */

} //namespace uasdk
#endif // _OPCUA_GUID_T_
