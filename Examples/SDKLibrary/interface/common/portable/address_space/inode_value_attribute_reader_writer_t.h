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

#ifndef _INODE_VALUE_ATTRIBUTE_READER_WRITER_T_
#define _INODE_VALUE_ATTRIBUTE_READER_WRITER_T_

#include "uasdk_includes.h"
#include "opcua_double_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_data_value_t.h"
#include "opcua_diagnostic_info_t.h"

namespace uasdk
{

class DiagnosticInfo_t;
class DataValue_t;
class IUserPermissions_t;
class ILocales_t;
class Duration_t;
template<typename T> class ArrayUA_t;
template<typename T> class Array_t;
class IndexRange_t;

/** \addtogroup grpAddressSpace
 *@{*/

class ICallbackNodeValueAttributeAccessCompleted_t : public virtual IRefCount_t
{
public:
  virtual ~ICallbackNodeValueAttributeAccessCompleted_t() {};

  /*****************************************************************************/
  /** Value attribute completed callback
   *
   *  @param[in] dataValue
   *  Intrusive pointer of type DataValue_t, which can be used for getting the value
   *
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t ReadValueAttributeCompleted(IntrusivePtr_t<DataValue_t> dataValue) = 0;

  /*****************************************************************************/
  /** Value attribute completed callback
  *
  *  @param[in] dataValue
  *  Intrusive pointer of type DataValue_t, which can be used for getting the value
  *
  *  @param[in] diagnosticInfo
  *  Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  *  required.
  *
  * @return
  * Status of the operation.
  */
  virtual Status_t ReadValueAttributeCompleted(
    IntrusivePtr_t<DataValue_t> dataValue,
    IntrusivePtr_t<DiagnosticInfo_t> diagnosticInfo) = 0;

  /*****************************************************************************/
  /** Value attribute write completed callback
  *
  *  @param[in] statusCode
  *  StatusCode of the operation
  *
  * @return
  * Status of the operation.
  */
  virtual Status_t WriteValueAttributeCompleted(Status_t resultCode) = 0;

    /*****************************************************************************/
    /** Value attribute write completed callback
    *
    *  @param[in] statusCode
    *  StatusCode of the operation
    *
    *  @param[in] diagnosticInfo
    *  Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
    *  required.
    *
    * @return
    * Status of the operation.
    */
    virtual Status_t WriteValueAttributeCompleted(
      Status_t resultCode,
      IntrusivePtr_t<DiagnosticInfo_t> diagnosticInfo) = 0;

};

class IVariableNode_t;

class INodeValueAttributeReaderWriter_t : public virtual IRefCount_t
{
public:
  virtual ~INodeValueAttributeReaderWriter_t() {};

  /*****************************************************************************/
  /** Availability of read value attribute object synchronously or not
   *
   * @param[in] node
   * variable node for query
   *
   * @return
   * TRUE if object can be accessed synchronously. FALSE Otherwise
   */

  virtual bool CanReadValueSynchronously(const IVariableNode_t& node) = 0;

  /*****************************************************************************/
  /** Begins reading the value attribute of the node asynchronously
   *
   *  If reading is successful completedCallback.ReadValueAttributeCompleted()
   *  will be called. If reading is not successful completedCallback.ReadValueAttributeCompleted() 
   *  will not be called.
   *
   * @param[in] node
   * variable node from which data will be read
   *
   * @param[in] maxAge
   * The maxAge of the value in milliseconds provided by the Read Service. The reader
   * can optionally consider this when replying to the caller.
   * Should be set to zero where no maxAge is provided.
   *
   * @param[in] setSourceTimestamp
   * Set the source timestamp in the data value.
   *
   * @param[in] locales
   * A list of locales in order of preference to use when reading LocalizedText.
   *
   * @param[in] indexRange
   * The index range to apply to the value if it is an array.
   *
   * @param[in] transactionId
   * A non-zero unique identifier for a collection of nodes being read as a
   * group (typically by the Read Service). Can be optionally used in conjunction
   * with a transaction listener to optimise processing of read operations by the
   * application. If reading the node outside of the Read Service should be set
   * to zero.
   *
   * @param[in] timeoutHint
   * The timeoutHint in milliseconds provided by the Read Service. The reader
   * can optionally consider this hint when replying to the caller.
   * Should be set to zero where no timeoutHint is provided.
   *
   * @param[out] completedCallback
   * The ReadValueAttributeCompleted() function of this interface will be called by the
   * reader if this function returns a good status code.
   *
   * @return
   * The result of the operation. If the status code is good then the reader
   * has been successfully launched and will return the read result in due course. If
   * the status code is bad the reader was not successfully launched.
   *
   */
  virtual Status_t ReadValueAttributeBegin(
    IntrusivePtr_t<const IVariableNode_t>& node,
    uint32_t maxAge,
    bool setSourceTimestamp,
    IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
    IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback) = 0;


  /*****************************************************************************/
  /** Reading the value attribute of the node synchronously
   *
   * @param[in] node
   * variable node from which data will be read
   *
   * @param[in] maxAge
   * The maxAge of the value in milliseconds provided by the Read Service. The reader
   * can optionally consider this when replying to the caller.
   * Should be set to zero where no maxAge is provided.
   *
   * @param[in] setSourceTimestamp
   * Set the source timestamp in the data value.
   *
   * @param[in] locales
   * A list of locales in order of preference to use when reading LocalizedText.
   *
   * @param[in] indexRange
   * The index range to apply to the value if it is an array.
   *
   * @param[in] transactionId
   * A non-zero unique identifier for a collection of nodes being read as a
   * group (typically by the Read Service). Can be optionally used in conjunction
   * with a transaction listener to optimise processing of read operations by the
   * application. If reading the node outside of the Read Service should be set
   * to zero.
   *
   * @param[in] timeoutHint
   * The timeoutHint in milliseconds provided by the Read Service. The reader
   * can optionally consider this hint when replying to the caller.
   * Should be set to zero where no timeoutHint is provided.
   *
   * @param[out] dataValue
   * That read from the node will be update to the dataValue
   *
   * @param[out] diagnosticInfo
   * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
   * required.
   *
   * @return
   * The result of the operation.
   *
   */
  virtual Status_t ReadValueAttribute(
    const IVariableNode_t& node,
    uint32_t maxAge,
    bool setSourceTimestamp,
    const ArrayUA_t<String_t>& locales,
    const Array_t<IndexRange_t>& indexRange,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<DataValue_t>& dataValue,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo) = 0;

  /*****************************************************************************/
  /** Availability of write value attribute object synchronously or not
  *
  * @param[in] node
  * variable node for query
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */

  virtual bool CanWriteValueSynchronously(const IVariableNode_t& node) = 0;

  /*****************************************************************************/
  /** Begins writing the value attribute of the node synchronously
  *
  *  If the Writing node is successful completedCallback.WriteValueAttributeCompleted()
  *  will be called. otherwise completedCallback.WriteValueAttributeCompleted()
  *  will not be called.
  *
  * @param[out] node
  * node to write data value
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] dataValue
  * The value to be written.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being written as a
  * group (typically by the Write Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of write operations by the
  * application. If writing the node outside of the WriteService should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Write Service. The writer
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] completedCallback
  * The WriteValueAttributeCompleted() function of this interface will be called by the
  * writer if this function returns a good status code.
  *
  * @return
  * The result of the operation. If the status code is good then the writer
  * has been successfully launched and will return the write result in due course. If
  * the status code is bad the writer was not successfully launched.
  *
  */
  virtual Status_t WriteValueAttributeBegin(
	  IntrusivePtr_t<IVariableNode_t>& node,
	  IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
	  IntrusivePtr_t<const DataValue_t> dataValue,
	  uint32_t transactionId,
	  uint32_t timeoutHint,
	  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback) = 0;

  /*****************************************************************************/
  /** Writing the value attribute of the node Synchronously
  *
  * @param[out] node
  * node to write data value
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] dataValue
  * The value to be written.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being written as a
  * group (typically by the Write Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of write operations by the
  * application. If writing the node outside of the WriteService should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Write Service. The writer
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] diagnosticInfo
  * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  * required.
  *
  * @return
  * The result of the operation.
  *
  */
  virtual Status_t WriteValueAttribute(
	  IVariableNode_t& node,
	  const Array_t<IndexRange_t>& indexRange,
	  IntrusivePtr_t<const DataValue_t> dataValue,
	  uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo) = 0;

};
/** @} */

}

#endif // _INODE_VALUE_ATTRIBUTE_READER_WRITER_T_
