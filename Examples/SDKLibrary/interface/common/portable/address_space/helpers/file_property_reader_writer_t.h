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

#ifndef _FILE_PROPERTY_READER_WRITER_T_
#define _FILE_PROPERTY_READER_WRITER_T_

#include "uasdk_includes.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0))

#include "inode_value_attribute_reader_writer_t.h"
#include "allocatable_t.h"
#include "lock_t.h"
#include "ifile_ua_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief FilePropertyReaderWriter_t
*
* FilePropertyReaderWriter_t class.
*
*/
class FilePropertyReaderWriter_t : public INodeValueAttributeReaderWriter_t, public Allocatable_t
{
private:
  Lock_t lock;
  IntrusivePtr_t<const NodeId_t> sizeNodeId;
  IntrusivePtr_t<const NodeId_t> openCountNodeId;
  IntrusivePtr_t<IFileUA_t> fileUAObject;

  //*****************************************************************************/
  /** Function used to read value to the node
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
  Status_t ReadValue(const IVariableNode_t& node, bool setSourceTimestamp, IntrusivePtr_t<DataValue_t>& dataValue);

public:
  ~FilePropertyReaderWriter_t();

  //*****************************************************************************/
  /** Function used to Initialize the custom reader and writer with
  *  with UA file object
  *
  * @param[in] fileUAObject_
  * UA file object
  *
  * @return
  * status of the operation
  */
  Status_t Initialize(IntrusivePtr_t<IFileUA_t> fileUAObject_);

  //*****************************************************************************/
  /** Function used to Add the custom reader and writer with
  *  with size node id
  *
  * @param[in] sizeNodeId_
  * size node id
  */
  void AddSizeNodeId(IntrusivePtr_t<const NodeId_t> sizeNodeId_);

  //*****************************************************************************/
  /** Function used to Add the custom reader and writer with
  *  with Open count node id
  *
  * @param[in] openCountNodeId_
  * open count node id
  */
  void AddOpenCountNodeId(IntrusivePtr_t<const NodeId_t> openCountNodeId_);

  /*****************************************************************************/
  /** Availability of read value attribute object synchronously or not
  *
  * @param[in] node_
  * node to which value has to be Read
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */

  virtual bool CanReadValueSynchronously(const IVariableNode_t& node_);

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
  * @param[in] node_
  * node to which value has to be written
  *
  * @return
  * TRUE if object can be accessed synchronously. FALSE Otherwise
  */

  virtual bool CanWriteValueSynchronously(const IVariableNode_t& node_);

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

}

#endif  //( (UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0))

#endif  //_FILE_PROPERTY_READER_WRITER_T_