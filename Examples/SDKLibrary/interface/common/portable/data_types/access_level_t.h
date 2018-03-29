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

#ifndef _ACCESS_LEVEL_T_
#define _ACCESS_LEVEL_T_


#include "opcua_identifiers.h"
#include "opcua_byte_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief AccessLevel_t
 *
 * This class implements the data access level
 *
 */
class AccessLevel_t : public Byte_t
{
public:

  /*****************************************************************************/
  /** \brief Enumeration of Access level bits
   *
   */
  typedef enum
  {
    BIT_CURRENT_READ = 0,
    BIT_CURRENT_WRITE = 1,
    BIT_HISTORY_READ = 2,
    BIT_HISTORY_WRITE = 3,
    BIT_RESERVED_4 = 4,
    BIT_STATUS_WRITE = 5,
    BIT_TIMESTAMP_WRITE = 6,
    BIT_RESERVED = 7
  } Bits_t;

private:

  /*****************************************************************************/
  /** Update the Access level bits
   *
   * @param[in] bool val
   * Set or clear
   *
   * @param[in] uint32_t bit
   * Access level to set or clear
   */
  void SetOrClear(bool val, uint32_t bit);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Byte;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  AccessLevel_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] uint8_t val
   * Access level
   *
   */
  AccessLevel_t(uint8_t val);

  /*****************************************************************************/
  /** Copy constructor
   *
   * @param[in] AccessLevel_t const & other
   * Object to be copied from
   */
  AccessLevel_t(AccessLevel_t const & other);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~AccessLevel_t();

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
  /** Get the current read access level bit
   *
   * @return
   * Returns the current read access level bit
   */
  bool CurrentRead(void) const;

  /*****************************************************************************/
  /** Set the current read access level bit
   *
   * @param[in] bool val
   * Current Read access level bit to set or clear
   *
   */
  void CurrentRead(bool val);

  /*****************************************************************************/
  /** Get the current write access level bit
   *
   * @return
   * Returns the current write access level bit
   */
  bool CurrentWrite(void) const;

  /*****************************************************************************/
  /** Set the current write access level bit
   *
   * @param[in] bool val
   * Current write access level bit to set or clear
   *
   */
  void CurrentWrite(bool val);

  /*****************************************************************************/
  /** Get the History Read access level bit
   *
   * @return
   * Returns the History Read access level bit
   */
  bool HistoryRead(void) const;

  /*****************************************************************************/
  /** Set the  History Read access level bit
   *
   * @param[in] bool val
   *  History Read access level bit to set or clear
   *
   */
  void HistoryRead(bool val);

  /*****************************************************************************/
  /** Set the  History Write access level bit
   *
   * @param[in] bool val
   *  History Write access level bit to set or clear
   *
   */
  void HistoryWrite(bool val);

  /*****************************************************************************/
  /** Get the History Write access level bit
   *
   * @return
   * Returns the History Write access level bit
   */
  bool HistoryWrite(void) const;

  /*****************************************************************************/
  /** Set the  Status Write access level bit
   *
   * @param[in] bool val
   *  Status Write access level bit to set or clear
   *
   */
  void StatusWrite(bool val);

  /*****************************************************************************/
  /** Get the Status Write access level bit
   *
   * @return
   * Returns the Status Write access level bit
   */
  bool StatusWrite(void) const;

  /*****************************************************************************/
  /** Set the Time stamp Write access level bit
   *
   * @param[in] bool val
   *  Time stamp Write access level bit to set or clear
   *
   */
  void TimestampWrite(bool val);

  /*****************************************************************************/
  /** Get the Time stamp Write access level bit
   *
   * @return
   * Returns the Time stamp Write access level bit
   */
  bool TimestampWrite(void) const;

};

/** @} */

} // namespace uasdk

#endif // _ACCESS_LEVEL_T_
