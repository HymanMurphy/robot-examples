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

#ifndef _FILTER_OPERATOR_T_
#define _FILTER_OPERATOR_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_enumeration_t.h"
#include "opcua_identifiers.h"
#include "intrusive_ptr_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief FilterOperator_t
*
* This class implements the FilterOperator enum type
*
*/
class FilterOperator_t : public Enumeration_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(FilterOperator_t);

	/*****************************************************************************/
	/** \brief Enumeration of Filter Operators
	*
	*/
  typedef enum
  {
    FILTER_OP_EQUAL              = 0,
    FILTER_OP_ISNULL             = 1,
    FILTER_OP_GREATERTHAN        = 2,
    FILTER_OP_LESSTHAN           = 3,
    FILTER_OP_GREATERTHANOREQUAL = 4,
    FILTER_OP_LESSTHANOREQUAL    = 5,
    FILTER_OP_LIKE               = 6,
    FILTER_OP_NOT                = 7,
    FILTER_OP_BETWEEN            = 8,
    FILTER_OP_INLIST             = 9,
    FILTER_OP_AND                = 10,
    FILTER_OP_OR                 = 11,
    FILTER_OP_CAST               = 12,
    FILTER_OP_INVIEW             = 13,
    FILTER_OP_OFTYPE             = 14,
    FILTER_OP_RELATEDTO          = 15,
    FILTER_OP_BITWISEAND         = 16,
    FILTER_OP_BITWISEOR          = 17,
    FILTER_OP_END                = 18
  }Enum_t;

private:

	/*****************************************************************************/
	/* @var Enum_t value
	* enum value
	*/
  Enum_t  value;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_FilterOperator;
  
	/*****************************************************************************/
	/** Default constructor for the class.
	*
	*/
	FilterOperator_t();

	/*****************************************************************************/
	/** Parameterized constructor for the class.
	*
	*/
  FilterOperator_t(Enum_t value_);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~FilterOperator_t();

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
	* @param[in] FilterOperator_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(FilterOperator_t const & obj) const;

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
	* @param[in] FilterOperator_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS FilterOperator_t object is greater than RHS FilterOperator_t object
	*/
  bool operator>(FilterOperator_t const & obj) const;

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
	* @param[in] const BaseDataType_t& source
	* Source data type
	*
	* @return
	* Status of the operation
	*/
	virtual Status_t CopyFrom(const BaseDataType_t& source);

	/*****************************************************************************/
	/** Copy from the source
	*
	* @param[in] const FilterOperator_t& source
	*  FilterOperator source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const FilterOperator_t& source);

	/*****************************************************************************/
	/** Get the Type ID
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Type ID
	*/
	virtual uint32_t TypeId(uint16_t& namespaceIndex)  const;

	/*****************************************************************************/
	/** Get the Value
	*
	* @return
	* Returns the Value
	*/
	const FilterOperator_t::Enum_t& Value(void) const;

	/*****************************************************************************/
	/** Set the Value
	*
	* @return
	* Returns the Value
	*/
	FilterOperator_t::Enum_t& Value(void);

	/*****************************************************************************/
	/* This function used to write the integer value to Enum type
	*
	* Integer value for the enumeration
	*
	* @return
	* Status of the operation
	*/
	virtual Status_t WriteIntToValue(int32_t newValue);

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
  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

	/*****************************************************************************/
	/** Decode the buffer
	*
	* @param[in] const IBuffer_t& buffer
	* Decode buffer
	*
	* @param[in] ICodec_t& decoder
	* Reference to the decoder object
	*
	* @param[out] FilterOperator_t& result
	* Decoded FilterOperator object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, FilterOperator_t& result);

  //Public interface for testing

	/*****************************************************************************/
	/** Set the Value
	*
	* @param[in] FilterOperator_t::Enum_t value_
	* input Value
	*
	* @return
	* Returns the status of the operation
	*/
  Status_t Value(FilterOperator_t::Enum_t value_);
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _FILTER_OPERATOR_T_
