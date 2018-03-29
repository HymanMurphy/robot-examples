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

#ifndef _OPCUA_TIME_ZONE_DATA_TYPE_T_
#define _OPCUA_TIME_ZONE_DATA_TYPE_T_

#include "opcua_int16_t.h"
#include "opcua_boolean_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{
/** \addtogroup grpDataType
*@{*/

/*****************************************************************************/
/** \brief EventNotificationList_t
*
* This class implements EventNotificationList type
*
*/
class TimeZoneDataType_t : public Structure_t
{
public:
	UA_DECLARE_RUNTIME_TYPE(TimeZoneDataType_t);

private:
	Int16_t offset;
	Boolean_t daylightSavingInOffset;

public:
	static const uint32_t TYPE_ID = OpcUaId_TimeZoneDataType;

	/*****************************************************************************/
	/** constructor for the class.
	*
	*/
	TimeZoneDataType_t();

	/*****************************************************************************/
	/** constructor for the class.
	*
	* @param[in] int16_t offset_
	* offset_
	*
	* @param[in] bool daylightSavingInOffset_
	* daylightSavingInOffset_
	*/
	TimeZoneDataType_t(int16_t offset_, bool daylightSavingInOffset_);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
	virtual ~TimeZoneDataType_t(void);

	/*****************************************************************************/
	/** = operator overloading
	*
	* @param[in] TimeZoneDataType_t const & obj
	* Object to be assigned
	*
	* @return
	* Reference to the TimeZoneDataType_t object assigned
	*/
	TimeZoneDataType_t& operator=(TimeZoneDataType_t const & obj);

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
	* @param[in] TimeZoneDataType_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
	bool operator==(TimeZoneDataType_t const & obj) const;

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
	* @param[in] TimeZoneDataType_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS TimeZoneDataType_t object is greater than RHS TimeZoneDataType_t object
	*/
	bool operator>(TimeZoneDataType_t const & obj) const;

	/*****************************************************************************/
	/** Copy from the source
	*
	* @param[in] const TimeZoneDataType_t& source
	*  EventNotificationList source to copy from
	*
	* @return
	* Status of the operation
	*/
	Status_t CopyFrom(const TimeZoneDataType_t& source);

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
	/** Get the Binary Encoding Id
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Binary Encoding Id
	*/
	virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

	/*****************************************************************************/
	/** Get the Offset
	*
	* @return
	* Returns the Offset
	*/
	const Int16_t& Offset(void) const;

	/*****************************************************************************/
	/** Set the Offset
	*
	* @return
	* Returns the Offset
	*/
	Int16_t& Offset(void);

	/*****************************************************************************/
	/** Get the DaylightSavingInOffset
	*
	* @return
	* Returns the DaylightSavingInOffset
	*/
	const Boolean_t& DaylightSavingInOffset(void) const;

	/*****************************************************************************/
	/** Set the DaylightSavingInOffset
	*
	* @return
	* Returns the DaylightSavingInOffset
	*/
	Boolean_t& DaylightSavingInOffset(void);

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
	* @param[out] TimeZoneDataType_t& result
	* Decoded TimeZoneDataType_t object
	*
	* @return
	* Returns status of the operation
	*/
	static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, TimeZoneDataType_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_TIME_ZONE_DATA_TYPE_T_

