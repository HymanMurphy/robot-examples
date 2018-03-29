/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef _VALUE_ATTRIBUTE_READER_WRITER_FOR_C_API_
#define _VALUE_ATTRIBUTE_READER_WRITER_FOR_C_API_

#include "uasdk_default_build_config.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "inode_value_attribute_reader_writer_t.h"
#include "ua_types.h"
#include "iaddress_space_t.h"
#include "ilocalizable_text_t.h"

namespace uasdk
{
/** \addtogroup grpServer_C_API
*@{*/

/*****************************************************************************/
/** \brief ValueAttributeReaderWriterForCAPI_t
*  Value attribute reader and writer for UA Server C API
*
*/
class ValueAttributeReaderWriterForCAPI_t : public INodeValueAttributeReaderWriter_t, public Allocatable_t
{

private:

  Lock_t lock;

  //Inputs At initialization
  uintptr_t nodeHandle;
  uint32_t maxArrayLength;
  uint32_t actualArraySize;
  UA_Value_type_t valueType;
  IntrusivePtr_t<IAddressSpace_t> addressSpace;

  //Actual data from the Appliation layer
  Array_t<IndexRange_t> indexRange_;
  Status_t   statusCode;
  IntrusivePtr_t<DataValue_t> dataValue_;

  //Handling the Deferred Read operation
  uint32_t timeoutHint_;
  uintptr_t deferralHandle;
  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t> readCompletedCallback;

  //*****************************************************************************/
  /**This function is used for updating the UA data from Raw data after to read
  *
  * @param[in] rawValue_
  * pointer to raw data
  *
  * @param[in] value_
  * UA data
  *
  * @return
  * returns the status of the operation.
  */
  template<typename T, typename U>
  Status_t UpdateToBaseDataValue(U* rawValue_, IntrusivePtr_t<BaseDataType_t>& value_);

  //*****************************************************************************/
  /**This function is used for converting the raw data to UA data
  *
  * @param[in] dataValue
  * UA data
  *
  * @return
  * returns the status of the operation.
  */
  Status_t ConvertRawDataToUaData(UA_Value_t& rawData);

  //*****************************************************************************/
  /**This function is used reading the value from the application layer
  *
  * @param[in] rawData_
  * raw data
  *
  * @param[in] statusCode_
  * status code
  *
  * @param[in] sourceTimeStamp_
  * source time stamp
  *
  * @return
  * returns the status of the operation.
  */
  Status_t ReadValue(UA_Value_t& rawData, Status_t& statusCode_, int64_t& sourceTimeStamp);

  //*****************************************************************************/
  /**This function is used for updating the Raw data from the basedata variable after write
  *
  * @param[in] rawValue_
  * pointer to raw data
  *
  * @param[in] newLengthOfArray
  * new lenght of the Array
  *
  * @return
  * returns the status of the operation.
  */
  template<typename T, typename U>
  Status_t UpdateFromBaseDataValue(U* rawValue_, uint32_t& newLengthOfArray);
  
  //*****************************************************************************/
  /**This function is used for converting the UA data to raw data
  *
  * @param[out] rawData_
  * raw data
  *
  * @param[out] sourceTimeStamp_
  * source time stamp
  *
  * @param[out] newLengthOfArray
  * new lenght of array
  *
  * @return
  * returns the status of the operation.
  */
  Status_t WriteValue(UA_Value_t& rawData_, int64_t& sourceTimeStamp_, uint32_t& newLengthOfArray);

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  
  //*****************************************************************************/
  /**This will be used to get the instrument range of the Node
  *
  * @param[out] parentNode
  * parent node from which instrument range has to be taken
  *
  * @param[out] result
  * status of the operation
  *
  * @return
  * Intrusive pointer to the Instrument range node.
  */
  IntrusivePtr_t<IVariableNode_t> GetInstrumentRangePropertyNode(const IVariableNode_t& parentNode, Status_t& result);

  //*****************************************************************************/
  /**This function is used for checking whether the value is in instrument range limits
  *
  * @param[out] instrumentRangeNode
  * instrument range node
  *
  * @param[out] parentNodeValue
  * parent node value
  *
  * @return
  * return OpcUa_Good if the value is the range
  */
  Status_t IsInRange(const IVariableNode_t& instrumentRangeNode, const DataValue_t& parentNodeValue);
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

public:
  ValueAttributeReaderWriterForCAPI_t();
  ~ValueAttributeReaderWriterForCAPI_t();

  //*****************************************************************************/
  /**Function used to initialize reader with multi state value discrete value.
  *
  * @param[in] nodeHandle_
  * node handle
  *
  * @param[in] maxArrayLength_
  * maxArrayLength
  *
  * @param[in] valueType_
  * value type
  *
  * @return
  * Status of initialisation
  */
  Status_t Initialize(uintptr_t nodeHandle_, uint32_t maxArrayLength_, UA_Value_type_t valueType_, IntrusivePtr_t<IAddressSpace_t>& addressSapce_);

  //*****************************************************************************/
  /**Function used to update raw data for read
  *
  * @param[in] rawData_
  * raw data
  *
  * @param[in] statusCode_
  * status code
  *
  * @param[in] sourceTimeStamp_
  * source time stamp
  */
  void PerformRead(UA_Value_t rawData_, Status_t statusCode_, int64_t sourceTimeStamp_);

  //*****************************************************************************/
  /**Function used to update raw data after write
  *
  * @param[in] rawData_
  * raw data
  *
  * @param[in] sourceTimeStamp_
  * source time stamp
  *
  * @param[in] newLengthOfArray
  * new lenght of array
  */
  void PerformWrite(UA_Value_t& rawData_, int64_t& sourceTimeStamp_, uint32_t& newLengthOfArray);

  //*****************************************************************************/
  /**Function used to set the status of the write operation
  *
  * @param[in] resultCode
  *
  * @return
  * Status of the operation.
  */
  Status_t SetWriteOperationLevelResultCode(Status_t resultCode);

  /*****************************************************************************/
  /** Is the current read operation a repeat of an operation that was previously
  * deferred?
  *
  * @return
  * true if the read operation was previously deferred deferred.
  */
  bool IsReadOperationDeferred(void);

  /*****************************************************************************/
  /** Get Time Out Hint
  *
  *
  * @return
  * time out value of the read operation.
  */
  uint32_t GetReadTimeOutHint(void);
  /*****************************************************************************/
  /** Update Deferral Handle
  *
  * @param[in] deferral_handle
  * pointer to Deferral handle
  *
  * @return
  * Status of the operation.
  */
  Status_t UpdateDeferralHandle(uintptr_t* deferralHandle_);

  /*****************************************************************************/
  /** Read Deferral Complete
  *
  * @return
  * Status of the operation.
  */
  Status_t ReadDeferralComplete(void);

  /*****************************************************************************/
  /** Call Application Layer Read operation
  *
  */
  void CallApplicationLayerRead(void);

  /*****************************************************************************/
  /** Availability of read value attribute object synchronously or not
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */

  virtual bool CanReadValueSynchronously(const IVariableNode_t& node);

  //*****************************************************************************/
  /**Function begins to read the value attribute.
  *
  * @param[in] node
  * IVariableNode_t object.
  *
  * @param[in] maxAge
  * Maximum age.
  *
  * @param[in] setSourceTimestamp
  * status of set Source Time stamp.
  *
  * @param[in/out] locales
  * string values to be read.
  *
  * @param[in] indexRange
  * IndexRange_t object.
  *
  * @param[in] transactionId
  * IndexRange_t object.
  *
  * @param[in] timeoutHint
  * timeout Hint.
  *
  * @param[out] completedCallback
  * ICallbackNodeValueAttributeReadCompleted_t object.
  *
  * @return
  * returns the status of the operation.
  */
  virtual Status_t ReadValueAttributeBegin(
    IntrusivePtr_t<const IVariableNode_t>& node,
    uint32_t maxAge,
    bool setSourceTimestamp,
    IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
    IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback);


  //*****************************************************************************/
  /**Function reads the data value attribute.
  *
  * @param[in] node
  * IVariableNode_t object.
  *
  * @param[in] maxAge
  * Maximum age.
  *
  * @param[in] setSourceTimestamp
  * status of set Source Time stamp.
  *
  * @param[in/out] locales
  * string values to be read.
  *
  * @param[in] indexRange
  * IndexRange_t object.
  *
  * @param[in] transactionId
  * IndexRange_t object.
  *
  * @param[in] timeoutHint
  * timeout Hint.
  *
  * @param[out] dataValue
  * data which is to be store after reading from base data type.
  *
  * @param[out] diagnosticInfo
  * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  * required.
  *
  *
  * @return
  * returns the status of the operation.
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
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo);

  /*****************************************************************************/
  /** Availability of write value attribute object synchronously or not
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */

  virtual bool CanWriteValueSynchronously(const IVariableNode_t& node);

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
    IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback);

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
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo);

};

/*@}*/
} //namespace uasdk

#endif // UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
#endif //_VALUE_ATTRIBUTE_READER_WRITER_FOR_C_API_
