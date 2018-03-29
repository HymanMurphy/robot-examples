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

#ifndef _IVARIABLE_NODE_T_
#define _IVARIABLE_NODE_T_

#include "uasdk_includes.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_double_t.h"
#include "opcua_node_class_t.h"
#include "inode_t.h"

namespace uasdk
{

class IVariableTypeNode_t;
class INodeValueAttributeReaderWriter_t;
class ICallbackNodeValueAttributeAccessCompleted_t;
class UInt32_t;
class DataValue_t;
class AccessLevel_t;
class Duration_t;
class IndexRange_t;
class DiagnosticInfo_t;

template<typename T> class ArrayUA_t;
template<typename T> class ArrayRef_t;

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief Variable Node Interface
 *
 * A class that represents a Variable node in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IVariableNode_t : public virtual INode_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(IVariableNode_t);

  virtual ~IVariableNode_t() {}

  /*****************************************************************************/
  /** Get the Value attribute of the node
   *
   *  Nodes can provide value attributes in a number of ways. All data types
   *  except for LocalizedText_t can be placed in the Value attribute for
   *  synchronous access by users of the node. The value can be unchanged,
   *  the owner of the node can update the value in an event driven fashion or the
   *  owner can register an attribute about to be read listener with the node
   *  and update the value on demand when a user of the node attempts a read.
   *  Similarly the node owner can register an attribute changed listener with
   *  the node to be notified when the value has been changed.
   *
   *  For value attributes that cannot be accessed synchronously due to a slow
   *  data source the node owner can register a value attribute reader and
   *  writer to perform the value attribute access asynchronously so as not to
   *  block the thread pool.
   *
   *  If this value is set then the Read Service will read the value synchronously
   *  rather than attempting to obtain the value asynchronously.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the Value
   * of the node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const DataValue_t> Value(void) const = 0;

  /*****************************************************************************/
  /** Set the Value attribute of the node
   *
   *  Nodes can provide value attributes in a number of ways. All data types
   *  except for LocalizedText_t can be placed in the Value attribute for
   *  synchronous access by users of the node. The value can be unchanged,
   *  the owner of the node can update the value in an event driven fashion or the
   *  owner can register an attribute about to be read listener with the node
   *  and update the value on demand when a user of the node attempts a read.
   *  Similarly the node owner can register an attribute changed listener with
   *  the node to be notified when the value has been changed.
   *
   *  For value attributes that cannot be accessed synchronously due to a slow
   *  data source the node owner can register a value attribute reader and
   *  writer to perform the value attribute access asynchronously so as not to
   *  block the thread pool.
   *
   *  If this value is set then the Read Service will read the value synchronously
   *  rather than attempting to obtain the value asynchronously.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the Value
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, the DataValue_t must have been created
   *    dynamically using a SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the value from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Value(IntrusivePtr_t<const DataValue_t> value) = 0;

  /*****************************************************************************/
  /** Get the DataType attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the DataType
   * of the node. All nodes have a DataType however the caller must test the
   * pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const NodeId_t> DataType(void) const = 0;

  /*****************************************************************************/
  /** Set the DataType attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the DataType
   * of the node. The value provided must satisfy a number of rules.
   * 1) No non-const references to the NodeId_t must exist, i.e. it must
   *    be immutable (to ensure thread safety).
   * 2) The NodeId_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value must be set (i.e. pointing to an actual object) as all
   *    variable type nodes require a DataType.
   *
   * @return
   * The result of the operation.
   */
virtual Status_t DataType(IntrusivePtr_t<const NodeId_t> value) = 0;

  /*****************************************************************************/
  /** Get the ValueRank attribute of the node
   *
   * @return
   * The ValueRank of the node.
   */
  virtual int32_t ValueRank(void) const = 0;

  /*****************************************************************************/
  /** Set the ValueRank attribute of the node
   *
   * @param[in] value
   * The required ValueRank of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ValueRank(int32_t value) = 0;

  /*****************************************************************************/
  /** Get the ArrayDimensions attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ArrayDimensions of the node. All variable type nodes do not have
   * ArrayDimensions and the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ArrayUA_t<UInt32_t> > ArrayDimensions(void) const = 0;

  /*****************************************************************************/
  /** Set the ArrayDimensions attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the ArrayDimensions
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the ArrayUA_t<UInt32_t> must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the ArrayUA_t<UInt32_t> must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the ArrayDimensions attribute from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ArrayDimensions(IntrusivePtr_t<const ArrayUA_t<UInt32_t> > value) = 0;

  /*****************************************************************************/
  /** Get the AccessLevel attribute of the node
   *
   * @return
   * The AccessLevel of the node.
   */
  virtual AccessLevel_t AccessLevel(void) const = 0;

  /*****************************************************************************/
  /** Set the AccessLevel attribute of the node
   *
   * @param[in] value
   * The required AccessLevel of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t AccessLevel(AccessLevel_t value) = 0;

  /*****************************************************************************/
  /** Get the UserAccessLevel attribute of the node
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * The UserAccessLevel of the node.
   */
  virtual AccessLevel_t UserAccessLevel(const IUserPermissions_t& userPermissions) const = 0;

  /*****************************************************************************/
  /** Set the UserAccessLevel attribute of the node
   *
   * @param[in] value
   * The required UserAccessLevel of the node
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t UserAccessLevel(AccessLevel_t value, IUserPermissions_t& userPermissions) = 0;

  /*****************************************************************************/
  /** Get the MinimumSamplingInterval attribute of the node
   *
   * @return
   * The MinimumSamplingInterval of the node.
   */
  virtual Duration_t MinimumSamplingInterval(void) const = 0;

  /*****************************************************************************/
  /** Set the MinimumSamplingInterval attribute of the node
   *
   * @param[in] value
   * The required MinimumSamplingInterval of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t MinimumSamplingInterval(Duration_t value) = 0;

  /*****************************************************************************/
  /** Get the Historizing attribute of the node
   *
   * @return
   * The Historizing of the node.
   */
  virtual bool Historizing(void) const = 0;

  /*****************************************************************************/
  /** Set the Historizing attribute of the node
   *
   * @param[in] value
   * The required Historizing of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Historizing(bool value) = 0;

  /*****************************************************************************/
  /** Is monitored item value attribute sampling disabled?
   *
   *  For nodes with very large value attributes monitored item sampling of the
   *  value attribute can be disabled to protect the platform resources from
   *  exhaustion.
   *
   * @return
   * "true" if sampling is disabled.
   */
  virtual bool DisableSampling(void) const = 0;

  /*****************************************************************************/
  /** Set monitored item value attribute sampling disabled
   *
   *  For nodes with very large value attributes monitored item sampling of the
   *  value attribute can be disabled to protect the platform resources from
   *  exhaustion.
   *
   * @param[in] value
   * "true" if sampling is disabled.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t DisableSampling(bool value) = 0;

  /*****************************************************************************/
  /** Get the value attribute reader/writer of the node
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the 
  * ValueAttributeReaderWriter of the node.
  */
  virtual IntrusivePtr_t<INodeValueAttributeReaderWriter_t> ValueAttributeReaderWriter(void) = 0;

  /*****************************************************************************/
  /** Set the value attribute reader/writer of the node
   *
   *  Nodes can provide value attributes in a number of ways. All data types
   *  except for LocalizedText_t can be placed in the Value attribute for
   *  synchronous access by users of the node. The value can be unchanged,
   *  the owner of the node can update the value in an event driven fashion or the
   *  owner can register an attribute about to be read listener with the node
   *  and update the value on demand when a user of the node attempts a read.
   *
   *  For value attributes that cannot be accessed synchronously due to a slow
   *  data source the node owner can register a value attribute reader and
   *  writer to perform the value attribute access asynchronously so as not to
   *  block the thread pool.
   *
   *  The value attribute reader is used by the node to read the value
   *  attribute. Only a single reader can be registered at any given time.
   *  Any software component registering a reader with the node is responsible
   *  for removing the reader if required.
   *
   * Limitations:
   *  1. If the Value attribute is stored in the address space, then value cannot be retrived
   *     with the help of ValueAttributeReaderWriter
   *  2. If the Node's value is retrived from the ValueAttributeReaderWriter, and if there is
   *     a value attribute changed listener then changed listner will not be trigerred.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the reader
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, the INodeValueAttributeReader_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the reader from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ValueAttributeReaderWriter(IntrusivePtr_t<INodeValueAttributeReaderWriter_t> value) = 0;

  /*****************************************************************************/
  /** Can the value attribute be read synchronously?
   *
   *  Value attribute for variable node can be read synchronously or asynchronously
   *  using this function before reading the value attribute, developer can identify
   *  whether the value attribute can be read synchronously
   *
   * @return
   * returns true if the value attribute can be read synchronously
   */
  virtual bool CanReadValueSynchronously(void) const = 0;

  /*****************************************************************************/
  /** Begins reading the value attribute of the node asynchronously
   *
   *  This function internally calls the value attribute reader registered with
   *  the node. If this function returns a good status code
   *  completedCallback.ReadValueAttributeCompleted() will be called by the reader
   *  when the read has completed. If this function returns a bad status code
   *  completedCallback.ReadValueAttributeCompleted() will not be called by the
   *  reader.
   *
   * @param[in] maxAge
   * The maxAge of the value in milliseconds provided by the Read Service. The reader
   * can optionally consider this when replying to the caller.
   * Should be set to zero where no maxAge is provided.
   *
   * @param[in] timestampsToReturn
   * The timestamps to return in the data value.
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
  virtual Status_t BeginReadValue(
      uint32_t maxAge,
      TimestampsToReturn_t::Enum_t timestampsToReturn,
      IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
      IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
      uint32_t transactionId,
      uint32_t timeoutHint,
      IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t> completedCallback) const = 0;

  /*****************************************************************************/
  /** Reading the value attribute of the node synchronously
   *
   * @param[in] maxAge
   * The maxAge of the value in milliseconds provided by the Read Service. The reader
   * can optionally consider this when replying to the caller.
   * Should be set to zero where no maxAge is provided.
   *
   * @param[in] timestampsToReturn
   * The timestamps to return in the data value.
   *
   * @param[in] locales
   * A list of locales in order of preference to use when reading LocalizedText.
   *
   * @param[in] indexRange
   * The index range to apply to the value if it is an array.
   *
   * @param[out] dataValue
   * That read from the node will be update to the dataValue
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
   * @return
   * The result of the operation.
   *
   */
  virtual Status_t ReadValue(
      uint32_t maxAge,
      TimestampsToReturn_t::Enum_t timestampsToReturn,
      const ArrayUA_t<String_t>& locales,
      const Array_t<IndexRange_t>& indexRange,
      uint32_t transactionId,
      uint32_t timeoutHint,
      IntrusivePtr_t<DataValue_t>& dataValue,
      IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo) const = 0;


  /*****************************************************************************/
  /** Can the value attribute be written synchronously?
   *
   *  Value attribute for variable node can be written synchronously or asynchronously
   *  using this function before writing the value attribute, developer can identify
   *  whether the value attribute can be written synchronously
   *
   * @return
   * returns true if the value attribute can be written synchronously
   */
  virtual bool CanWriteValueSynchronously(void) const = 0;

  /*****************************************************************************/
  /** Begins writing the value attribute of the node asynchronously
   *
   *  This function internally calls the value attribute writer registered with
   *  the node. If this function returns a good status code
   *  completedCallback.WriteValueAttributeCompleted() will be called by the writer
   *  when the write has completed. If this function returns a bad status code
   *  completedCallback.WriteValueAttributeCompleted() will not be called by the
   *  writer.
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
  virtual Status_t BeginWriteValue(
      IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
      IntrusivePtr_t<const DataValue_t> dataValue,
      uint32_t transactionId,
      uint32_t timeoutHint,
      IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t> completedCallback) = 0;

  /*****************************************************************************/
  /** Writing the value attribute of the node Synchronously
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
  virtual Status_t WriteValue(
      const Array_t<IndexRange_t>& indexRange,
      IntrusivePtr_t<const DataValue_t> dataValue,
      uint32_t transactionId,
      uint32_t timeoutHint,
      IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo) = 0;

};

/** @} */

}

#endif // _IVARIABLE_NODE_T_
