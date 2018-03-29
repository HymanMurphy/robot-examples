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

#ifndef _ICODEC_T_
#define _ICODEC_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

namespace uasdk
{

class Boolean_t;
class SByte_t;
class Byte_t;
class Int16_t;
class UInt16_t;
class Int32_t;
class UInt32_t;
class Int64_t;
class UInt64_t;
class Float_t;
class Double_t;
class String_t;
class DateTime_t;
class Guid_t;
class ByteString_t;
class Xmlelement_t;
class NodeId_t;
class NodeIdString_t;
class NodeIdGuid_t;
class NodeIdNumeric_t;
class NodeIdOpaque_t;
class ExpandedNodeId_t;
class StatusCode_t;
class QualifiedName_t;
class LocalizedText_t;
class Structure_t;
class DataValue_t;
class BaseDataType_t;
class DiagnosticInfo_t;
class IBuffer_t;
class XmlElement_t;
class MessageUA_t;
class RequestMessage_t;
class ResponseMessage_t;

/** \addtogroup grpMiscellaneous
 *@{*/

class ICodec_t
{
public:
  virtual ~ICodec_t() {}

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Boolean_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const SByte_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Byte_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Int16_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const UInt16_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Int32_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const UInt32_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Int64_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const UInt64_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Float_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Double_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const String_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const DateTime_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const Guid_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const ByteString_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const XmlElement_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(IntrusivePtr_t<const NodeId_t> value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const NodeIdString_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const NodeIdOpaque_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const NodeIdGuid_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const NodeIdNumeric_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const ExpandedNodeId_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const StatusCode_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const QualifiedName_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const LocalizedText_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t EncodeExtensionObject(IntrusivePtr_t<const Structure_t> value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t EncodeExtensionObject(const Structure_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const DataValue_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t EncodeVariant(IntrusivePtr_t<const BaseDataType_t> value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t EncodeVariant(const BaseDataType_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const DiagnosticInfo_t& value, IBuffer_t& buffer) = 0;

  /*****************************************************************************/ 
  /** Encode the value passed 
   * 
   * @param[in] value 
   * Value to be encoded 
   * 
   * @param[in] IBuffer_t& buffer 
   * Ecode buffer 
   * 
   * @return 
   * returns Status of the operation 
   */ 
  virtual Status_t Encode(const MessageUA_t& value, IBuffer_t& buffer) = 0;
   
  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Boolean_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, SByte_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Byte_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Int16_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, UInt16_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Int32_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, UInt32_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Int64_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, UInt64_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Float_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Double_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, String_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, DateTime_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, Guid_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, ByteString_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, XmlElement_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<NodeId_t>& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, ExpandedNodeId_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, StatusCode_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, QualifiedName_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, LocalizedText_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<Structure_t>& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, DataValue_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<BaseDataType_t>& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, DiagnosticInfo_t& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<RequestMessage_t>& result) = 0;

  /*****************************************************************************/ 
  /** Decode the value from the buffer
   * 
   * @param[in] const IBuffer_t& buffer 
   * 
   * @param[out] Result 
   * Reference to the decoded value
   * 
   * @return  
   * returns Status of the operation 
   */
  virtual Status_t Decode(const IBuffer_t& buffer, IntrusivePtr_t<ResponseMessage_t>& result) = 0;

};

/** @} */

} // namespace uasdk

#endif // _ICODEC_T_
