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

#ifndef _OPCUA_EVENT_FILTER_RESULT_T_
#define _OPCUA_EVENT_FILTER_RESULT_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "opcua_status_code_t.h"
#include "opcua_diagnostic_info_t.h"
#include "content_filter_result_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief EventFilterResult_t
*
* This class implements EventFilterResult type
*
*/
class EventFilterResult_t : public Structure_t
{
private:

	/*****************************************************************************/
	/* @var ArrayUA_t<StatusCode_t>  selectClauseResults
	* List of status codes for the elements in the select clause. 
	* The size and order of the list matches the size and order of the elements in the selectClauses request parameter. 
	* The Server returns null for unavailable or rejected Event fields.
	*/
  ArrayUA_t<StatusCode_t> selectClauseResults;

	/*****************************************************************************/
	/* @var ArrayUA_t<DiagnosticInfo_t>  selectClauseDiagnosticInfos
	* A list of diagnostic information for individual elements in the select clause. 
	* The size and order of the list matches the size and order of the elements in the selectClauses request parameter. 
	* This list is empty if diagnostics information was not requested in the request header or if no diagnostic information was encountered in processing of the select clauses.
	*/
  ArrayUA_t<DiagnosticInfo_t> selectClauseDiagnosticInfos;

	/*****************************************************************************/
	/* @var ContentFilterResult_t  whereClauseResult
	* results associated with the whereClause request parameter.
	*/
  ContentFilterResult_t whereClauseResult;

public:
  UA_DECLARE_RUNTIME_TYPE(EventFilterResult_t);

	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_EventFilterResult;

	/*****************************************************************************/
	/** constructor for the class.
	*
	*/
  EventFilterResult_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~EventFilterResult_t();

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
	* @param[in] EventFilterResult_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(EventFilterResult_t const & obj) const;

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
	* @param[in] EventFilterResult_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS EventFilterResult_t object is greater than RHS EventFilterResult_t object
	*/
  bool operator>(EventFilterResult_t const & obj) const;

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
	* @param[in] const EventFilterResult_t& source
	*  EventFilterResult source to copy from
	*
	* @return
	* Status of the operation
	*/
	Status_t CopyFrom(const EventFilterResult_t& source);

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
	/** Get the SelectClauseResults
	*
	* @return
	* Returns the SelectClauseResults
	*/
  const ArrayUA_t<StatusCode_t>& SelectClauseResults(void) const;

	/*****************************************************************************/
	/** Set the SelectClauseResults
	*
	* @return
	* Returns the SelectClauseResults
	*/
  ArrayUA_t<StatusCode_t>& SelectClauseResults(void);

	/*****************************************************************************/
	/** Get the SelectClauseDiagnosticInfos
	*
	* @return
	* Returns the SelectClauseDiagnosticInfos
	*/
  const ArrayUA_t<DiagnosticInfo_t>& SelectClauseDiagnosticInfos(void) const;

	/*****************************************************************************/
	/** Set the SelectClauseDiagnosticInfos
	*
	* @return
	* Returns the SelectClauseDiagnosticInfos
	*/
  ArrayUA_t<DiagnosticInfo_t>& SelectClauseDiagnosticInfos(void);

	/*****************************************************************************/
	/** Get the WhereClauseResult
	*
	* @return
	* Returns the WhereClauseResult
	*/
  const ContentFilterResult_t& WhereClauseResult() const;

	/*****************************************************************************/
	/** Set the WhereClauseResult
	*
	* @return
	* Returns the WhereClauseResult
	*/
  ContentFilterResult_t& WhereClauseResult();

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
	* @param[out] EventFilterResult_t& result
	* Decoded EventFilterResult object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, EventFilterResult_t& result);
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _OPCUA_EVENT_FILTER_RESULT_T_
