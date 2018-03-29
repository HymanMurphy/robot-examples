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

#ifndef _WRITE_MASK_T_
#define _WRITE_MASK_T_


#include "opcua_identifiers.h"
#include "opcua_number_t.h"
#include "attribute_id_mask_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief UInt64_t
 *
 * This class implements the WriteMask_t data type
 */
class WriteMask_t : public UInt32_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration of write mask
   */
  typedef enum
  {
    BIT_ACCESS_LEVEL = 0,
    BIT_ARRAY_DIMENSIONS = 1,
    BIT_BROWSE_NAME = 2,
    BIT_CONTAINS_NO_LOOPS = 3,
    BIT_DATA_TYPE = 4,
    BIT_DESCRIPTION = 5,
    BIT_DISPLAY_NAME = 6,
    BIT_EVENT_NOTIFIER = 7,
    BIT_EXECUTABLE = 8,
    BIT_HISTORIZING = 9,
    BIT_INVERSE_NAME = 10,
    BIT_IS_ABSTRACT = 11,
    BIT_MINIMUM_SAMPLING_INTERVAL = 12,
    BIT_NODE_CLASS = 13,
    BIT_NODE_ID = 14,
    BIT_SYMMETRIC = 15,
    BIT_USER_ACCESS_LEVEL = 16,
    BIT_USER_EXECUTABLE = 17,
    BIT_USER_WRITEMASK = 18,
    BIT_VALUE_RANK = 19,
    BIT_WRITE_MASK = 20,
    BIT_VALUE_FOR_VARIABLE_TYPE = 21,
    BIT_RESERVED
  } Bits_t;

private:

  /*****************************************************************************/
  /** Set or clear the write mask bits
   *
   * @param[in] bool val
   * True to set, False to clear the bit
   *
   * @param[in] uint32_t bit
   * Write mask bit clear or set
   */
  void SetOrClear(bool val, uint32_t bit);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_UInt32;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  WriteMask_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] uint32_t val
   * Value to be assigned
   */
  WriteMask_t(uint32_t val);

  /*****************************************************************************/
  /** Copy constructor for the class.
   *
   * @param[in] WriteMask_t const & other
   * Write mask object to be copied
   */
  WriteMask_t(WriteMask_t const & other);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~WriteMask_t();

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] WriteMask_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the WriteMask_t object assigned
   */
  WriteMask_t& operator=(WriteMask_t const & rhs);

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
  /** This function is used to check whether AccessLevel is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool AccessLevel(void) const;

  /*****************************************************************************/
  /** Set the AccessLevel
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void AccessLevel(bool val);

  /*****************************************************************************/
  /** This function is used to check whether ArrayDimension is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool ArrayDimensions(void) const;

  /*****************************************************************************/
  /** Set the ArrayDimensions
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void ArrayDimensions(bool val);

  /*****************************************************************************/
  /** This function is used to check whether BrowseName is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool BrowseName(void) const;

  /*****************************************************************************/
  /** Set the BrowseName
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void BrowseName(bool val);

  /*****************************************************************************/
  /** This function is used to check whether ContainsNoLoops is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool ContainsNoLoops(void) const;

  /*****************************************************************************/
  /** Set the ContainsNoLoops
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void ContainsNoLoops(bool val);

  /*****************************************************************************/
  /** This function is used to check whether DataType is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool DataType(void) const;

  /*****************************************************************************/
  /** Set the DataType
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void DataType(bool val);

  /*****************************************************************************/
  /** This function is used to check whether Description is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool Description(void) const;

  /*****************************************************************************/
  /** Set the Description
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void Description(bool val);

  /*****************************************************************************/
  /** This function is used to check whether DisplayName is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool DisplayName(void) const;


  /*****************************************************************************/
  /** Set the DisplayName
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void DisplayName(bool val);

  /*****************************************************************************/
  /** This function is used to check whether EventNotifier is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool EventNotifier(void) const;

  /*****************************************************************************/
  /** Set the EventNotifier
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void EventNotifier(bool val);

  /*****************************************************************************/
  /** This function is used to check whether Executable is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool Executable(void) const;

  /*****************************************************************************/
  /** Set the Executable
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void Executable(bool val);

  /*****************************************************************************/
  /** This function is used to check whether Historizing is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool Historizing(void) const;

  /*****************************************************************************/
  /** Set the Executable
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void Historizing(bool val);

  /*****************************************************************************/
  /** This function is used to check whether InverseName is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool InverseName(void) const;

  /*****************************************************************************/
  /** Set the InverseName
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void InverseName(bool val);

  /*****************************************************************************/
  /** This function is used to check whether ISAbstract is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool IsAbstract(void) const;

  /*****************************************************************************/
  /** Set the IsAbstract
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void IsAbstract(bool val);

  /*****************************************************************************/
  /** This function is used to check whether MinimumSaplingInterval is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool MinimumSamplingInterval(void) const;

  /*****************************************************************************/
  /** Set the Minimum Sampling Interval
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void MinimumSamplingInterval(bool val);

  /*****************************************************************************/
  /** This function is used to check whether NodeClass is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool NodeClass(void) const;

  /*****************************************************************************/
  /** Set the NodeClass
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void NodeClass(bool val);

  /*****************************************************************************/
  /** This function is used to check whether NodeId is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool NodeId(void) const;

  /*****************************************************************************/
  /** Set the Node Id
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void NodeId(bool val);

  /*****************************************************************************/
  /** This function is used to check whether Symmetric is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool Symmetric(void) const;

  /*****************************************************************************/
  /** Set the Symmetric
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void Symmetric(bool val);

  /*****************************************************************************/
  /** This function is used to check whether UserAccessLevel is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool UserAccessLevel(void) const;

  /*****************************************************************************/
  /** Set the User Access Level
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void UserAccessLevel(bool val);

  /*****************************************************************************/
  /** This function is used to check whether UserExecutable is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool UserExecutable(void) const;

  /*****************************************************************************/
  /** Set the User Executable
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void UserExecutable(bool val);

  /*****************************************************************************/
  /** This function is used to check whether UserWriteMask is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool UserWriteMask(void) const;

  /*****************************************************************************/
  /** Set the User Write Mask
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void UserWriteMask(bool val);

  /*****************************************************************************/
  /** This function is used to check whether ValueRank is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool ValueRank(void) const;

  /*****************************************************************************/
  /** Set the Value Rank
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void ValueRank(bool val);

  /*****************************************************************************/
  /** This function is used to check whether WriteMask is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool WriteMask(void) const;

  /*****************************************************************************/
  /** Set the Write Mask
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void WriteMask(bool val);

  /*****************************************************************************/
  /** This function is used to check whether Value Attribute for VariableType is wriable
   *
   * @return
   * true if this attibute is wribale. false otherwise
   */
  bool ValueForVariableType(void) const;

  /*****************************************************************************/
  /** Set the Value For Variable Type
   *
   * @param[in] bool val
   * Value to set or clear
   */
  void ValueForVariableType(bool val);

  /*****************************************************************************/
  /** Check the attribute is set or clear
   *
   * @param[in] AttributeId_t::Enum_t attributeId
   * Attribute ID to be checked
   *
   * @return
   * Returns True if the attribute is set.
   */
  bool IsSet(AttributeId_t::Enum_t attributeId);
};

/** @} */

} // namespace uasdk

#endif // _WRITE_MASK_T_
