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

#ifndef _NODE_WITH_INSTRUMENT_RANGE_PROPERTY_VALUE_ATTRIBUTE_READER_WRITER_T_H_
#define _NODE_WITH_INSTRUMENT_RANGE_PROPERTY_VALUE_ATTRIBUTE_READER_WRITER_T_H_

#include "uasdk_includes.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "lock_t.h"

#include "opcua_range_t.h"
#include "ivariable_node_t.h"
#include "opcua_data_value_t.h"
#include "inode_value_attribute_reader_writer_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t
*
* A class that represents a NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t.
*
*/
class NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t : public INodeValueAttributeReaderWriter_t, public Allocatable_t
{
private:
  Lock_t lock;
  IntrusivePtr_t<DataValue_t>     valueOfNodeWithInstrumentRangeProperty;
  IntrusivePtr_t<IVariableNode_t> instrumentRangeNode;

  //*****************************************************************************/
  /** Function used to read value to the node
  *
  * @param[in] indexRange
  * index range value to be written
  *
  * @param[in] setSourceTimestamp
  * Boolean value indicating whether source time stamp is set or not
  *
  * @param[out] dataValue
  * value to be read
  *
  * @return
  * status of the operation
  */
  Status_t ReadValue(const Array_t<IndexRange_t>& indexRange, bool setSourceTimestamp, IntrusivePtr_t<DataValue_t>& dataValue);

  //*****************************************************************************/
  /** Function used to write value to the node if it is in instrumental range
   *
   * @param[in] indexRange
   * index range value to be written
   *
   * @param[in] dataValue
   * value to be written
   *
   * @return
   * status of the operation
   */
  Status_t WriteValue(const Array_t<IndexRange_t>& indexRange, const DataValue_t& dataValue);

public:
  ~NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t();

  //*****************************************************************************/
  /** Function used to Initialize the custom reader and writer with
   *  with Instrument Range Property Node and data value of node
   *
   * @param[in] valueOfNodeWithInstrumentRangeProperty_
   * Value of Node with InstrumentRange Property
   *
   * @param[in] instrumentRangeNode_
   * Intrusment range property node
   *
   * @return
   * status of the operation
   */
  Status_t Initialize(IntrusivePtr_t<const DataValue_t> valueOfNodeWithInstrumentRangeProperty_, IntrusivePtr_t<IVariableNode_t>& instrumentRangeNode_);

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

  //*****************************************************************************/
  /**Function begins to write value attribute to the node
   *
   * @param[in] node
   * node to which value has to be written
   *
   * @param[in] indexRange
   * IndexRange_t object.
   *
   * @param[in] dataValue
   * value to be written to the node
   *
   * @param[in] transactionId
   * IndexRange_t object.
   *
   * @param[in] timeoutHint
   * timeout Hint.
   *
   * @param[out] completedCallback
   * ICallbackNodeValueAttributeWriteCompleted_t object.
   * This will be called only if the write is successful
   *
   * @return
   * returns the status of the operation.
   *
   * Note: For ComplexNumberType and DoubleComplexNumberType, Server developer
   *       Has to decide on how to change validate for the Instrument Range.
   *       Default implementation will allow writing the value of the node,
   *       without checking against the Instrument Range
   */
  virtual Status_t WriteValueAttributeBegin(
    IntrusivePtr_t<IVariableNode_t>& node,
    IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
    IntrusivePtr_t<const DataValue_t> dataValue,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback);

  //*****************************************************************************/
  /**Function used to Write value to the node if value is within the instrument range
   *
   * @param[in] node
   * node to which value has to be written
   *
   * @param[in] indexRange
   * IndexRange_t object.
   *
   * @param[in] dataValue
   * value to be written to the node
   *
   * @param[in] transactionId
   * IndexRange_t object.
   *
   * @param[in] timeoutHint
   * timeout Hint.
   *
   * @return
   * returns the status of the operation.
   *
   * Note: For ComplexNumberType and DoubleComplexNumberType, Server developer
   *       Has to decide on how to change validate for the Instrument Range.
   *       Default implementation will allow writing the value of the node,
   *       without checking against the Instrument Range
   */
  virtual Status_t WriteValueAttribute(
    IVariableNode_t& node,
    const Array_t<IndexRange_t>& indexRange,
    IntrusivePtr_t<const DataValue_t> dataValue,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo);
};

/** @} */

} // namespace uasdk

#endif  //UASDK_USE_DATA_ACCESS_HELPERS

#endif  //_NODE_WITH_INSTRUMENT_RANGE_PROPERTY_VALUE_ATTRIBUTE_READER_WRITER_T_H_
