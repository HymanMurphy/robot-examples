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

#ifndef _TYPE_CONVERSION_T_
#define _TYPE_CONVERSION_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "intrusive_ptr_t.h"
#include "opcua_base_data_type_t.h"
#include "opcua_expanded_node_id_t.h"

namespace uasdk
{

#define MAX_STR_LEN_FOR_FLOAT                     12
#define MAX_STR_LEN_FOR_DOUBLE                    20
#define MAX_STR_LEN_FOR_64_BIT_INTEGER            21
#define MAX_STR_LEN_FOR_EXP_NODEID_NAMESPACE_URI  800

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief TypeConversion_t
*
* This class implements the type conversion methods
*
*/
class TypeConversion_t
{
private:
  int64_t Ifloor(float x);

	//private methods
	Status_t ConvertGuidToString(IntrusivePtr_t<Guid_t>& guidPtr, IntrusivePtr_t<String_t>& stringPtr);
	Status_t ConvertStringToGuid(IntrusivePtr_t<String_t>& stringPtr, IntrusivePtr_t<Guid_t>& guidPtr);
	Status_t ConvertNodeIdToString(IntrusivePtr_t<NodeId_t>& nodeidPtr, IntrusivePtr_t<String_t>& stringPtr);
	Status_t ConvertStringToNodeId(IntrusivePtr_t<String_t>& stringPtr, IntrusivePtr_t<NodeId_t>& nodeidPtr, bool uriPresent=false);
	Status_t ConvertExpandedNodeidToString(IntrusivePtr_t<ExpandedNodeId_t>& expandednodeidPtr, IntrusivePtr_t<String_t>& stringPtr);
	Status_t ConvertStringToExpandedNodeid(IntrusivePtr_t<String_t>& stringPtr, IntrusivePtr_t<ExpandedNodeId_t>& expandednodeidPtr);
	Status_t ConvertBooleanTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertByteTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertDoubleTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertFloatTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertInt16To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertInt32To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertInt64To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertSByteTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertStringTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertUInt16To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertUInt32To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertUInt64To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertByteStringTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertDateTimeTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
	Status_t ConvertExpandedNodeIdTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
  Status_t ConvertGuidTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
  Status_t ConvertNodeIdTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
  Status_t ConvertStatusCodeTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
  Status_t ConvertLocalizedTextTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
  Status_t ConvertQualifiedNameTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);
  Status_t ConvertXmlElementTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);

  Status_t IsValidPrecedenceType(IntrusivePtr_t<BaseDataType_t> operandValue);
  int32_t  FindFirstSubstr(IntrusivePtr_t<String_t>& strPtr, const char *substrPtr, int32_t startPos = 0);

  Status_t  UseTypePrecedenceConvertToOrFromBoolean(IntrusivePtr_t<BaseDataType_t>& aType,
																										IntrusivePtr_t<BaseDataType_t>& bType,
																										IntrusivePtr_t<BaseDataType_t>& dest,
																										bool &convertedToFirstArgType,
																										bool &firstArgConversionFail,
																										bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromByte(IntrusivePtr_t<BaseDataType_t>& aType,
																								IntrusivePtr_t<BaseDataType_t>& bType,
																								IntrusivePtr_t<BaseDataType_t>& dest,
																								bool &convertedToFirstArgType,
																								bool &firstArgConversionFail,
																								bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromSByte(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromUInt16(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromInt16(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromUInt32(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromInt32(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromUInt64(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromInt64(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromFloat(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromDouble(IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromStatusCode(IntrusivePtr_t<BaseDataType_t>& aType,
																											IntrusivePtr_t<BaseDataType_t>& bType,
																											IntrusivePtr_t<BaseDataType_t>& dest,
																											bool &convertedToFirstArgType,
																											bool &firstArgConversionFail,
																											bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromGuid(IntrusivePtr_t<BaseDataType_t>& bType,
																								IntrusivePtr_t<BaseDataType_t>& dest,
																								bool &convertedToFirstArgType,
																								bool &firstArgConversionFail,
																								bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromString(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromExpandedNodeid(IntrusivePtr_t<BaseDataType_t>& aType,
																													IntrusivePtr_t<BaseDataType_t>& bType,
																													IntrusivePtr_t<BaseDataType_t>& dest,
																													bool &convertedToFirstArgType,
																													bool &firstArgConversionFail,
																													bool &secondArgConversionFail);

  Status_t UseTypePrecedenceConvertToOrFromNodeId(IntrusivePtr_t<BaseDataType_t>& aType,
																									IntrusivePtr_t<BaseDataType_t>& bType,
																									IntrusivePtr_t<BaseDataType_t>& dest,
																									bool &convertedToFirstArgType,
																									bool &firstArgConversionFail,
																									bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromLocalizedText(IntrusivePtr_t<BaseDataType_t>& aType,
																													IntrusivePtr_t<BaseDataType_t>& bType,
																													IntrusivePtr_t<BaseDataType_t>& dest,
																													bool &convertedToFirstArgType,
																													bool &firstArgConversionFail,
																													bool &secondArgConversionFail);

  Status_t  UseTypePrecedenceConvertToOrFromQualifiedName(IntrusivePtr_t<BaseDataType_t>& aType,
																													IntrusivePtr_t<BaseDataType_t>& bType,
																													IntrusivePtr_t<BaseDataType_t>& dest,
																													bool &convertedToFirstArgType,
																													bool &firstArgConversionFail);

protected:

	/**
	 * Implement Table 118 - Conversion Rules
	 * A data with the source type is forced to converted into a data with the target type. The type info
	 * for the data with "targetType" and the data with "sourceType" must be setup before this function
	 * is called. Otherwise an error will be return.
	 * @param sourceType (in)  -- a pointer to the data with source type which needs to be converted into.
	 * @param targetType (out) -- a pointer to the data with target type that the data with source type
	 *                            attempts to convert to.
	 * @return Good if the type conversion successes, bad otherwise.
	 */
	Status_t TypeConversionRule(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType);

	/**
	 * Implement Table 119 - Precedence Rules
	 *
	 * The data with the lower precedence type between "aType" and "bType" is forced to converted to the
	 * data with the higher precedence type. The converted data is saved to the argument "dest".
	 *
	 * The type precedence is given in the following table with the decrement order.
	 * The data type at the top of the table has the highest precedence and the data type at the bottom
	 * of the table has the lowest precedence.
	 *
	 *  Table 119 -- Data Precedence Rule
	 * ==================================
	 *    Rank    |      Data Type
	 * ==================================
	 *     1      |       Double
	 * ----------------------------------
	 *     2      |       Float
	 * ----------------------------------
	 *     3      |       Int64
	 * ----------------------------------
	 *     4      |       UInt64
	 * ----------------------------------
	 *     5      |       Int32
	 * ----------------------------------
	 *     6      |       UInt32
	 * ----------------------------------
	 *     7      |     StatusCode
	 * ----------------------------------
	 *     8      |       Int16
	 * ----------------------------------
	 *     9      |       UInt16
	 * ----------------------------------
	 *    10      |       SByte
	 * ----------------------------------
	 *    11      |       Byte
	 * ----------------------------------
	 *    12      |      Boolean
	 * ----------------------------------
	 *    13      |       Guid
	 * ----------------------------------
	 *    14      |      String
	 * ----------------------------------
	 *    15      |   ExpandedNodeId
	 * ----------------------------------
	 *    16      |      NodeId
	 * ----------------------------------
	 *    17      |    LocalizedText
	 * ----------------------------------
	 *    18      |    QualifiedName
	 * ==================================
	 *
	 * @param aType (in) -- a pointer to the first data with any type.
	 * @param bType (in) -- a pointer to the second data with any type.
	 * @param dest (out) -- a pointer to the converted data if the conversion succeeds according to the
	 *                      precedences of both the data "aType" and the data "bType".
	 * @param convertedToFirstArgType (out)-- true if the "bType" is converted into "dest" with the same
	 *                                        data type as "aType", false if the "aType" is converted into
	 *                                        "dest" with the same data type as "bType".
	 * @param firstArgConversionFail (out) -- true if conversion fails due to the "aType".
	 * @param secondArgConversionFail (out)-- true if conversion fails due to the "bType".
	 * @return Good if the type conversion succeeds, bad otherwise.
	 */
	Status_t TypePrecedenceRule(IntrusivePtr_t<BaseDataType_t>& aType,
								IntrusivePtr_t<BaseDataType_t>& bType,
								IntrusivePtr_t<BaseDataType_t>& dest,
								bool &convertedToFirstArgType,
								bool &firstArgConversionFail,
								bool &secondArgConversionFail);

	//Bitwise Operators Related Conversion Methods
	bool IsIntegerType(uint32_t typeID);
	uint32_t GetIntegerSizePriority(uint32_t typeID);
	bool CanConvertToIntegerType(uint32_t typeID);
	uint32_t GetTargetTypeForNonIntegers(uint32_t typeID);
	Status_t ConvertToIntegerType(IntrusivePtr_t<BaseDataType_t>& source, IntrusivePtr_t<BaseDataType_t>& target, uint32_t targetType);
	Status_t CheckAndConvertInputValuesToIntegerType(IntrusivePtr_t<BaseDataType_t>& value1, IntrusivePtr_t<BaseDataType_t>& value2, bool& isNULL);

public:

	TypeConversion_t();
	virtual ~TypeConversion_t();
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _TYPE_CONVERSION_T_
