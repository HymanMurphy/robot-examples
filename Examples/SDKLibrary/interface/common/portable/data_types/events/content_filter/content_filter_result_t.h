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

#ifndef _CONTENT_FILTER_RESULT_T_
#define _CONTENT_FILTER_RESULT_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "opcua_diagnostic_info_t.h"
#include "content_filter_element_result_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ContentFilterResult_t
*
* This class implements the ContentFilterResult type
*
*/
class ContentFilterResult_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ContentFilterResult_t);

private:

	/*****************************************************************************/
	/* @var Status_t statusCode
	* The status code of the operation
	*/
  Status_t statusCode;

	/*****************************************************************************/
	/* @var ArrayUA_t<ContentFilterElementResult_t>  elementResults
	* A list of results for individual elements in the filter. 
	* The size and order of the list matches the size and order of the elements in the ContentFilter parameter.
	*/
  ArrayUA_t<ContentFilterElementResult_t> elementResults;

	/*****************************************************************************/
	/* @var ArrayUA_t<DiagnosticInfo_t>  elementDiagnosticInfos
	* A list of diagnostic information for individual elements in the filter. 
	* The size and order of the list matches the size and order of the elements in the filter request parameter. 
	* This list is empty if diagnostics information was not requested in the request header or if no diagnostic information was encountered in processing of the elements.
	*/
  ArrayUA_t<DiagnosticInfo_t> elementDiagnosticInfos;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_ContentFilterResult;

	/*****************************************************************************/
	/** Constructor for the class.
	*
	*/
  ContentFilterResult_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~ContentFilterResult_t();

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
	* @param[in] ContentFilterResult_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(ContentFilterResult_t const & obj) const;

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
	* @param[in] ContentFilterResult_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS ContentFilterResult_t object is greater than RHS ContentFilterResult_t object
	*/
  bool operator>(ContentFilterResult_t const & obj) const;

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
	* @param[in] const ContentFilterResult_t& source
	*  ContentFilterResult source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const ContentFilterResult_t& source);

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
	/** Get the ElementResults
	*
	* @return
	* Returns the ElementResults
	*/
	const ArrayUA_t<ContentFilterElementResult_t>& ElementResults(void) const;

	/*****************************************************************************/
	/** Set the ElementResults
	*
	* @return
	* Returns the ElementResults
	*/
	ArrayUA_t<ContentFilterElementResult_t>& ElementResults(void);

	/*****************************************************************************/
	/** Get the ElementDiagnosticInfos
	*
	* @return
	* Returns the ElementDiagnosticInfos
	*/
	const ArrayUA_t<DiagnosticInfo_t>& ElementDiagnosticInfos(void) const;

	/*****************************************************************************/
	/** Set the ElementDiagnosticInfos
	*
	* @return
	* Returns the ElementDiagnosticInfos
	*/
	ArrayUA_t<DiagnosticInfo_t>& ElementDiagnosticInfos(void);

	/*****************************************************************************/
	/** Get the StatusCode
	*
	* @return
	* Returns the StatusCode
	*/
	const Status_t& StatusCode() const;

	/*****************************************************************************/
	/** Set the StatusCode
	*
	* @return
	* Returns the StatusCode
	*/
	Status_t& StatusCode();

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
	* @param[out] ContentFilterResult_t& result
	* Decoded ContentFilterResult object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ContentFilterResult_t& result);

};//class ContentFilterResult_t

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _CONTENT_FILTER_RESULT_T_
