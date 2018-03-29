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

#ifndef _ATTRIBUTE_ID_MASK_T_
#define _ATTRIBUTE_ID_MASK_T_

#include "uasdk_includes.h"
#include "opcua_uint32_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief AttributeIdMask_t
 *
 * This class contains the attribute id definitions
 *
 */
class AttributeId_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration of attribute id
   *
   */
  typedef enum
  {
    ATTRIBUTE_ID_INVALID = 0,
    ATTRIBUTE_ID_NODEID = 1,
    ATTRIBUTE_ID_NODECLASS = 2,
    ATTRIBUTE_ID_BROWSENAME = 3,
    ATTRIBUTE_ID_DISPLAYNAME = 4,
    ATTRIBUTE_ID_DESCRIPTION = 5,
    ATTRIBUTE_ID_WRITEMASK = 6,
    ATTRIBUTE_ID_USERWRITEMASK = 7,
    ATTRIBUTE_ID_ISABSTRACT = 8,
    ATTRIBUTE_ID_SYMMETRIC = 9,
    ATTRIBUTE_ID_INVERSENAME = 10,
    ATTRIBUTE_ID_CONTAINSNOLOOPS = 11,
    ATTRIBUTE_ID_EVENTNOTIFIER = 12,
    ATTRIBUTE_ID_VALUE = 13,
    ATTRIBUTE_ID_DATATYPE = 14,
    ATTRIBUTE_ID_VALUERANK = 15,
    ATTRIBUTE_ID_ARRAYDIMENSIONS = 16,
    ATTRIBUTE_ID_ACCESSLEVEL = 17,
    ATTRIBUTE_ID_USERACCESSLEVEL = 18,
    ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL = 19,
    ATTRIBUTE_ID_HISTORIZING = 20,
    ATTRIBUTE_ID_EXECUTABLE = 21,
    ATTRIBUTE_ID_USEREXECUTABLE = 22,
    ATTRIBUTE_ID_END = 23
  } Enum_t;
};

/*****************************************************************************/
/** \brief AttributeIdMask_t
 *
 * This class implements the Attribute Id Mask
 *
 */
class AttributeIdMask_t : public UInt32_t
{
private:

  /*****************************************************************************/
  /** Set or Clear
   *
   * @param[in] bool val
   * Set or clear
   *
   * @param[in] uint32_t bit
   * Attribute ID to set or clear
   */
  void SetOrClear(bool val, uint32_t bit)
  {
    if (bit < AttributeId_t::ATTRIBUTE_ID_END)
    {
      if (val)
      {
        value |= (1 << bit);
      }
      else
      {
        value &= ~(1 << bit);
      }
    }
  }

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_UInt32;

  /*****************************************************************************/
  /** default constructor for the class.
   *
   */
  AttributeIdMask_t() {}

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] uint8_t val
   * Attribute id
   *
   */
  AttributeIdMask_t(uint32_t val) : UInt32_t()
  {
    value = (1 << val);
  }

  /*****************************************************************************/
  /** Copy constructor
   *
   * @param[in] AttributeIdMask_t const & other
   * Object to be copied from
   */
  AttributeIdMask_t(AttributeIdMask_t const & other) : UInt32_t() { value = other.value; }

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~AttributeIdMask_t(){}

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  /*****************************************************************************/
  /** Get the access level bit from the Attribute Id
   *
   * @return
   * Returns the access level bit from the Attribute Id
   */
  bool AccessLevel(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_ACCESSLEVEL) != 0;
  }

  /*****************************************************************************/
  /** Set the access level bit from the Attribute Id
   *
   * @param[in] bool val
   * The access level bit from the Attribute Id to set or clear
   */
  void AccessLevel(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_ACCESSLEVEL);
  }

  /*****************************************************************************/
  /** Get the array dimensions bit from the Attribute Id
   *
   * @return
   * Returns the array dimensions bit from the Attribute Id
   */
  bool ArrayDimensions(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_ARRAYDIMENSIONS) != 0;
  }

  /*****************************************************************************/
  /** Set the Array Dimensions bit from the Attribute Id
   *
   * @param[in] bool val
   * The Array Dimensions bit from the Attribute Id to set or clear
   */
  void ArrayDimensions(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_ARRAYDIMENSIONS);
  }

  /*****************************************************************************/
  /** Get the BrowseName bit from the Attribute Id
   *
   * @return
   * Returns the BrowseName bit from the Attribute Id
   */
  bool BrowseName(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_BROWSENAME) != 0;
  }

  /*****************************************************************************/
  /** Set the Browse Name bit from the Attribute Id
   *
   * @param[in] bool val
   * The Browse Name bit from the Attribute Id to set or clear
   */
  void BrowseName(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_BROWSENAME);
  }

  /*****************************************************************************/
  /** Get the Contains No Loops bit from the Attribute Id
   *
   * @return
   * Returns the Contains No Loops bit from the Attribute Id
   */
  bool ContainsNoLoops(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_CONTAINSNOLOOPS) != 0;
  }

  /*****************************************************************************/
  /** Set the Contains No Loops bit from the Attribute Id
   *
   * @param[in] bool val
   * The Contains No Loops bit from the Attribute Id to set or clear
   */
  void ContainsNoLoops(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_CONTAINSNOLOOPS);
  }

  /*****************************************************************************/
  /** Get the DataType bit from the Attribute Id
   *
   * @return
   * Returns the DataType bit from the Attribute Id
   */
  bool DataType(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_DATATYPE) != 0;
  }

  /*****************************************************************************/
  /** Set the DataType bit from the Attribute Id
   *
   * @param[in] bool val
   * The DataType bit from the Attribute Id to set or clear
   */
  void DataType(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_DATATYPE);
  }

  /*****************************************************************************/
  /** Get the Description bit from the Attribute Id
   *
   * @return
   * Returns the Description bit from the Attribute Id
   */
  bool Description(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_DESCRIPTION) != 0;
  }

  /*****************************************************************************/
  /** Set the Description bit from the Attribute Id
   *
   * @param[in] bool val
   * The Description bit from the Attribute Id to set or clear
   */
  void Description(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_DESCRIPTION);
  }

  /*****************************************************************************/
  /** Get the DisplayName bit from the Attribute Id
   *
   * @return
   * Returns the DisplayName bit from the Attribute Id
   */
  bool DisplayName(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME) != 0;
  }

  /*****************************************************************************/
  /** Set the DisplayName bit from the Attribute Id
   *
   * @param[in] bool val
   * The DisplayName bit from the Attribute Id to set or clear
   */
  void DisplayName(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME);
  }

  /*****************************************************************************/
  /** Get the EventNotifier bit from the Attribute Id
   *
   * @return
   * Returns the EventNotifier bit from the Attribute Id
   */
  bool EventNotifier(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_EVENTNOTIFIER) != 0;
  }

  /*****************************************************************************/
  /** Set the EventNotifier bit from the Attribute Id
   *
   * @param[in] bool val
   * The EventNotifier bit from the Attribute Id to set or clear
   */
  void EventNotifier(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_EVENTNOTIFIER);
  }

  /*****************************************************************************/
  /** Get the Executable bit from the Attribute Id
   *
   * @return
   * Returns the Executable bit from the Attribute Id
   */
  bool Executable(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_EXECUTABLE) != 0;
  }

  /*****************************************************************************/
  /** Set the Executable bit from the Attribute Id
   *
   * @param[in] bool val
   * The Executable bit from the Attribute Id to set or clear
   */
  void Executable(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_EXECUTABLE);
  }

  /*****************************************************************************/
  /** Get the Historizing bit from the Attribute Id
   *
   * @return
   * Returns the Historizing bit from the Attribute Id
   */
  bool Historizing(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_HISTORIZING) != 0;
  }

  /*****************************************************************************/
  /** Set the Historizing bit from the Attribute Id
   *
   * @param[in] bool val
   * The Historizing bit from the Attribute Id to set or clear
   */
  void Historizing(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_HISTORIZING);
  }

  /*****************************************************************************/
  /** Get the InverseName bit from the Attribute Id
   *
   * @return
   * Returns the InverseName bit from the Attribute Id
   */
  bool InverseName(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_INVERSENAME) != 0;
  }

  /*****************************************************************************/
  /** Set the InverseName bit from the Attribute Id
   *
   * @param[in] bool val
   * The InverseName bit from the Attribute Id to set or clear
   */
  void InverseName(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_INVERSENAME);
  }

  /*****************************************************************************/
  /** Get the IsAbstract bit from the Attribute Id
   *
   * @return
   * Returns the IsAbstract bit from the Attribute Id
   */
  bool IsAbstract(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_ISABSTRACT) != 0;
  }

  /*****************************************************************************/
  /** Set the IsAbstract bit from the Attribute Id
   *
   * @param[in] bool val
   * The IsAbstract bit from the Attribute Id to set or clear
   */
  void IsAbstract(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_ISABSTRACT);
  }

  /*****************************************************************************/
  /** Get the Minimum Sampling Interval bit from the Attribute Id
   *
   * @return
   * Returns the Minimum Sampling Interval bit from the Attribute Id
   */
  bool MinimumSamplingInterval(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL) != 0;
  }

  /*****************************************************************************/
  /** Set the Minimum Sampling Interval bit from the Attribute Id
   *
   * @param[in] bool val
   * The Minimum Sampling Interval bit from the Attribute Id to set or clear
   */
  void MinimumSamplingInterval(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL);
  }

  /*****************************************************************************/
  /** Get the NodeClass bit from the Attribute Id
   *
   * @return
   * Returns the NodeClass bit from the Attribute Id
   */
  bool NodeClass(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_NODECLASS) != 0;
  }

  /*****************************************************************************/
  /** Set the NodeClass bit from the Attribute Id
   *
   * @param[in] bool val
   * The NodeClass bit from the Attribute Id to set or clear
   */
  void NodeClass(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_NODECLASS);
  }

  /*****************************************************************************/
  /** Get the NodeId bit from the Attribute Id
   *
   * @return
   * Returns the NodeId bit from the Attribute Id
   */
  bool NodeId(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_NODEID) != 0;
  }

  /*****************************************************************************/
  /** Set the NodeId bit from the Attribute Id
   *
   * @param[in] bool val
   * The NodeId bit from the Attribute Id to set or clear
   */
  void NodeId(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_NODEID);
  }

  /*****************************************************************************/
  /** Get the Symmetric bit from the Attribute Id
   *
   * @return
   * Returns the Symmetric bit from the Attribute Id
   */
  bool Symmetric(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_SYMMETRIC) != 0;
  }

  /*****************************************************************************/
  /** Set the Symmetric bit from the Attribute Id
   *
   * @param[in] bool val
   * The Symmetric bit from the Attribute Id to set or clear
   */
  void Symmetric(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_SYMMETRIC);
  }

  /*****************************************************************************/
  /** Get the User Access Level bit from the Attribute Id
   *
   * @return
   * Returns the User Access Level bit from the Attribute Id
   */
  bool UserAccessLevel(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_USERACCESSLEVEL) != 0;
  }

  /*****************************************************************************/
  /** Set the User Access Level bit from the Attribute Id
   *
   * @param[in] bool val
   * The User Access Level bit from the Attribute Id to set or clear
   */
  void UserAccessLevel(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_USERACCESSLEVEL);
  }

  /*****************************************************************************/
  /** Get the User Executable bit from the Attribute Id
   *
   * @return
   * Returns the User Executable bit from the Attribute Id
   */
  bool UserExecutable(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_USEREXECUTABLE) != 0;
  }

  /*****************************************************************************/
  /** Set the User Executable bit from the Attribute Id
   *
   * @param[in] bool val
   * The User Executable bit from the Attribute Id to set or clear
   */
  void UserExecutable(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_USEREXECUTABLE);
  }

  /*****************************************************************************/
  /** Get the User Write Mask bit from the Attribute Id
   *
   * @return
   * Returns the User Write Mask bit from the Attribute Id
   */
  bool UserWriteMask(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_USERWRITEMASK) != 0;
  }

  /*****************************************************************************/
  /** Set the User Write Mask bit from the Attribute Id
   *
   * @param[in] bool val
   * The User Write Mask bit from the Attribute Id to set or clear
   */
  void UserWriteMask(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_USERWRITEMASK);
  }

  /*****************************************************************************/
  /** Get the Value Rank bit from the Attribute Id
   *
   * @return
   * Returns the Value Rank bit from the Attribute Id
   */
  bool ValueRank(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_VALUERANK) != 0;
  }

  /*****************************************************************************/
  /** Set the Value Rank bit from the Attribute Id
   *
   * @param[in] bool val
   * The Value Rank bit from the Attribute Id to set or clear
   */
  void ValueRank(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_VALUERANK);
  }

  /*****************************************************************************/
  /** Get the Write Mask bit from the Attribute Id
   *
   * @return
   * Returns the Write Mask bit from the Attribute Id
   */
  bool WriteMask(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_WRITEMASK) != 0;
  }

  /*****************************************************************************/
  /** Set the Write Mask bit from the Attribute Id
   *
   * @param[in] bool val
   * The Write Mask bit from the Attribute Id to set or clear
   */
  void WriteMask(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_WRITEMASK);
  }

  /*****************************************************************************/
  /** Get the Value bit from the Attribute Id
   *
   * @return
   * Returns the Value bit from the Attribute Id
   */
  bool Value(void) const
  {
    return (value & AttributeId_t::ATTRIBUTE_ID_VALUE) != 0;
  }

  /*****************************************************************************/
  /** Set the Value bit from the Attribute Id
   *
   * @param[in] bool val
   * The Value bit from the Attribute Id to set or clear
   */
  void Value(bool val)
  {
    SetOrClear(val, AttributeId_t::ATTRIBUTE_ID_VALUE);
  }

  /*****************************************************************************/
  /** Check if the Attribute Id bit is set or not
   *
   * @param[in] AttributeId_t::Enum_t attributeId
   * Attribute id bit to check
   *
   * @return
   * True - If the attribute id bit requested is set
   * False -  If the attribute id bit requested is cleared
   *
   */
  bool IsSet(AttributeId_t::Enum_t attributeId)
  {
    return ( value & (1 << attributeId) ) != 0;
  }

};

/** @} */

} // namespace uasdk

#endif // _ATTRIBUTE_ID_MASK_T_
