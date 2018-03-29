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

#ifndef _IATTRIBUTE_ACCESS_T_H_
#define _IATTRIBUTE_ACCESS_T_H_

#include "opcua_base_data_type_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_array_ua_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_string_t.h"
#include "opcua_uint32_t.h"
#include "icodec_t.h"
#include "ibuffer_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Object Node Interface
*
* A class that is used to fetch attribute values of an event 
*
*/
class IAttributeAccess_t : public BaseDataType_t
{
private:

  IntrusivePtr_t<UInt32_t> subscriptionId;
  IntrusivePtr_t<UInt32_t> monitoredItemId;

public:
  UA_DECLARE_RUNTIME_TYPE(IAttributeAccess_t);
	virtual ~IAttributeAccess_t() {};

	/*****************************************************************************/
	/** Get the Type ID
	*
	* @param[in] const uint32_t typeId
	* typeId of the input event instance
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* True - If the given event instance is of type given by input typeId
	* False - If the given event instance is not of type given by input typeId
	*/
	virtual bool IsOfType(const uint32_t typeId, uint16_t namespaceIndex) const = 0;

	/*****************************************************************************/
	/** Get the Attribute value of the event attribute
	*
	* @param[in] const uint32_t typeId
	* typeId is the type of the instance
	*
	* @param[in] const ArrayUA_t<QualifiedName_t>& browsePath
	* The path from the instance to the node which defines the attribute
	*
	* @param[in] const uint32_t& attributeId
	* The attribute to return
	*
	* @param[in] const String_t& indexRange
	* The sub-set of an array value to return
	*
	* @param[out] Status_t& result
	* status of the operation
	*
	* @return IntrusivePtr_t<const BaseDataType_t>
	* The value of the requested attribute. The return value is a const reference.
	*/
	virtual IntrusivePtr_t<const BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& attributeId, const String_t& indexRange, Status_t& result) const;

	/*****************************************************************************/
	/** Get the Attribute value of the event attribute
	*
	* @param[in] const uint32_t typeId
	* typeId is the type of the instance
	*
	* @param[in] const ArrayUA_t<QualifiedName_t>& browsePath
	* The path from the instance to the node which defines the attribute
	*
	* @param[in] const uint32_t& attributeId
	* The attribute to return
	*
	* @param[in] const String_t& indexRange
	* The sub-set of an array value to return
	*
	* @param[out] Status_t& result
	* status of the operation
	*
	* @return IntrusivePtr_t<const BaseDataType_t>
	* The value of the requested attribute. The return value is a non-const reference.
	*/
	virtual IntrusivePtr_t<BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& attributeId, const String_t& indexRange, Status_t& result);

  /*****************************************************************************/
  /** Get the Attribute value of the event attribute
  *
  * @param[in] const uint32_t typeId
  * typeId is the type of the instance
  *
  * @param[in] const ArrayUA_t<QualifiedName_t>& browsePath
  * The path from the instance to the node which defines the attribute
  *
  * @param[in] const uint32_t& attributeId
  * The attribute to return
  *
  * @param[in] const String_t& indexRange
  * The sub-set of an array value to return
  *
  * @param[in] const ArrayUA_t<String_t>& locales
  * The list of locales from the current session
  *
  * @param[out] Status_t& result
  * status of the operation
  *
  * @return IntrusivePtr_t<const BaseDataType_t>
  * The value of the requested attribute. The return value is a const reference.
  */
  virtual IntrusivePtr_t<const BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& attributeId, const String_t& indexRange, const ArrayUA_t<String_t>& locales, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Get the Attribute value of the event attribute
  *
  * @param[in] const uint32_t typeId
  * typeId is the type of the instance
  *
  * @param[in] const ArrayUA_t<QualifiedName_t>& browsePath
  * The path from the instance to the node which defines the attribute
  *
  * @param[in] const uint32_t& attributeId
  * The attribute to return
  *
  * @param[in] const String_t& indexRange
  * The sub-set of an array value to return
  *
  * @param[in] const ArrayUA_t<String_t>& locales
  * The list of locales from the current session
  *
  * @param[out] Status_t& result
  * status of the operation
  *
  * @return IntrusivePtr_t<const BaseDataType_t>
  * The value of the requested attribute. The return value is a non-const reference.
  */
  virtual IntrusivePtr_t<BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& attributeId, const String_t& indexRange, const ArrayUA_t<String_t>& locales, Status_t& result) = 0;

  /*****************************************************************************/
  /** Set the subscription id for the given condition 
  * which is triggered from ConditionRefresh method
  *
  * @return IntrusivePtr_t<UInt32_t>
  * return valid subscription id from the 
  * ConditionRefresh method if the data object is a condition, else return null 
  */
  IntrusivePtr_t<UInt32_t> &SubscriptionId(void);

  /*****************************************************************************/
  /** Get the subscription id for the given condition
  * which is triggered from ConditionRefresh method
  *
  * @return IntrusivePtr_t<UInt32_t>
  * return valid subscription id from the
  * ConditionRefresh method if the data object is a condition, else return null
  */
  IntrusivePtr_t<const UInt32_t> SubscriptionId(void) const;

  /*****************************************************************************/
  /** Set the monitored item id for the given condition
  * which is triggered from ConditionRefresh2 method
  *
  * @return IntrusivePtr_t<UInt32_t>
  * return valid monitored item id from the
  * ConditionRefresh2 method if the data object is a condition, else return null
  */
  IntrusivePtr_t<UInt32_t> &MonitoredItemId(void);

  /*****************************************************************************/
  /** Get the monitored item id for the given condition
  * which is triggered from ConditionRefresh2 method
  *
  * @return IntrusivePtr_t<UInt32_t>
  * return valid monitored item id from the
  * ConditionRefresh2 method if the data object is a condition, else return null
  */
  IntrusivePtr_t<const UInt32_t> MonitoredItemId(void) const;

  //unused pure virtual functions
  virtual bool operator==(BaseDataType_t const & obj) const;

  virtual bool operator>(BaseDataType_t const & obj) const;

  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
};

/** @} */

}

#endif // UASDK_INCLUDE_EVENTS

#endif // _IATTRIBUTE_ACCESS_T_H_
