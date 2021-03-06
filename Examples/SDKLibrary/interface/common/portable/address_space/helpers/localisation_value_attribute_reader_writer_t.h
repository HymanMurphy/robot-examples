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

#ifndef _LOCALISATION_VALUE_ATTRIBUTE_READER_WRITER_T_H_
#define _LOCALISATION_VALUE_ATTRIBUTE_READER_WRITER_T_H_

#include "uasdk_includes.h"

#if (UASDK_USE_HELPERS > 0)

#include "lock_t.h"

#include "inode_value_attribute_reader_writer_t.h"
#include "localizable_text_stored_t.h"

namespace uasdk
{
/** \addtogroup grpAddressSpace
*@{*/

/*****************************************************************************/
/** \brief LocalisationValueAttributeReaderWriter_t
*
* A class that is a wrapper to read/write localization values.
*
*/
class LocalisationValueAttributeReaderWriter_t : public INodeValueAttributeReaderWriter_t, public Allocatable_t
{

private:
  Lock_t                                  lock;
  IntrusivePtr_t<LocalizableTextStored_t> localizableTextStored;

 //*****************************************************************************/
 /**Function used to read the data value
  *
  * @param[in] setSourceTimestamp
  * boolean status of time stamp.
  *
  * @param[in] locale
  * locale.
  *
  * @param[out] dataValue
  * data which is to be store after reading from base data type.
  *
  * @return
  * returns the status of the operation.
  */
  Status_t ReadValue(bool setSourceTimestamp, const ArrayUA_t<String_t>& locales, IntrusivePtr_t<DataValue_t>& dataValue);
  
 //*****************************************************************************/
 /**Function used to write the data value
  *
  * @param[out] dataValue
  * data which is to be store after reading from base data type.
  *
  * @return
  * returns the status of the operation.
  */
  Status_t WriteValue(IntrusivePtr_t<const DataValue_t> dataValue);
    
public:
  ~LocalisationValueAttributeReaderWriter_t();

  //*****************************************************************************/
  /**Function used to initialize reader writer.
   *
   * @param[in] localizedText
   * localized text value
   *
   * @return
   * status of the initialization
   */
  Status_t Initialize(IntrusivePtr_t<LocalizedText_t> localizedText);

  //*****************************************************************************/
  /**Function used to initialize reader writer.
  *
  * @param[in] localizedText
  * localized text value
  *
  * @return
  * status of the operation
  */
  Status_t AddText(IntrusivePtr_t<LocalizedText_t> localizedText);

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

/** @} */

} // namespace uasdk

#endif //(UASDK_USE_HELPERS > 0)

#endif /* _LOCALISATION_VALUE_ATTRIBUTE_READER_WRITER_T_H_ */
