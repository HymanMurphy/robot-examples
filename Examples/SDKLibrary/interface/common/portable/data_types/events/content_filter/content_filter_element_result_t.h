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

#ifndef _CONTENT_FILTER_ELEMENT_RESULT_T_
#define _CONTENT_FILTER_ELEMENT_RESULT_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_status_code_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ContentFilterElementResult_t
*
* This class implements the ContentFilterElementResult type
*
*/
class ContentFilterElementResult_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ContentFilterElementResult_t);
  
private:

	/*****************************************************************************/
	/* @var StatusCode_t statusCode
	* The status code for a single element.
	*/
  StatusCode_t statusCode;

	/*****************************************************************************/
	/* @var ArrayUA_t<StatusCode_t>  operandStatusCodes
	* A list of status codes for the operands in an element. 
	* The size and order of the list matches the size and order of the operands in the ContentFilterElement. 
	* This list is empty if no operand errors occurred.
	*/
  ArrayUA_t<StatusCode_t> operandStatusCodes;

	/*****************************************************************************/
	/* @var ArrayUA_t<DiagnosticInfo_t>  operandDiagnosticInfos
	* A list of diagnostic information for the operands in an element. 
	* The size and order of the list matches the size and order of the operands in the ContentFilterElement. 
	* This list is empty if diagnostics information was not requested in the request header or if no diagnostic information was encountered in processing of the operands.
	*/
  ArrayUA_t<DiagnosticInfo_t> operandDiagnosticInfos;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_ContentFilterElementResult;

	/*****************************************************************************/
	/** Constructor for the class.
	*
	*/
  ContentFilterElementResult_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~ContentFilterElementResult_t();

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
	* @param[in] ContentFilterElementResult_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(ContentFilterElementResult_t const & obj) const;

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
	* @param[in] ContentFilterElementResult_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS ContentFilterElementResult_t object is greater than RHS ContentFilterElementResult_t object
	*/
  bool operator>(ContentFilterElementResult_t const & obj) const;

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
	* @param[in] const ContentFilterElementResult_t& source
	*  ContentFilterElementResult source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const ContentFilterElementResult_t& source);

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
	/** Get the StatusCode
	*
	* @return
	* Returns the StatusCode
	*/
	const StatusCode_t& StatusCode(void) const;

	/*****************************************************************************/
	/** Set the StatusCode
	*
	* @return
	* Returns the StatusCode
	*/
	StatusCode_t& StatusCode(void);

	/*****************************************************************************/
	/** Get the OperandStatusCodes
	*
	* @return
	* Returns the OperandStatusCodes
	*/
	const ArrayUA_t<StatusCode_t>& OperandStatusCodes(void) const;

	/*****************************************************************************/
	/** Set the OperandStatusCodes
	*
	* @return
	* Returns the OperandStatusCodes
	*/
	ArrayUA_t<StatusCode_t>& OperandStatusCodes(void);

	/*****************************************************************************/
	/** Get the OperandDiagnosticInfos
	*
	* @return
	* Returns the OperandDiagnosticInfos
	*/
	const ArrayUA_t<DiagnosticInfo_t>& OperandDiagnosticInfos(void) const;

	/*****************************************************************************/
	/** Set the OperandDiagnosticInfos
	*
	* @return
	* Returns the OperandDiagnosticInfos
	*/
	ArrayUA_t<DiagnosticInfo_t>& OperandDiagnosticInfos(void);

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
	* @param[out] ContentFilterElementResult_t& result
	* Decoded ContentFilterElementResult object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ContentFilterElementResult_t& result);

};//class ContentFilterElementResult_t

/** @} */

} //namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _CONTENT_FILTER_ELEMENT_RESULT_T_
