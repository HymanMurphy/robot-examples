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

#ifndef _ISERVERCORE_T_
#define _ISERVERCORE_T_

#include "uasdk_includes.h"
#include "intrusive_ptr_t.h"
#include "opcua_message_security_mode_t.h"
#include "ixml_nodeset_io_t.h"
#include"opcua_date_time_t.h"

#if (UASDK_INCLUDE_SERVER > 0)

#if (UASDK_INCLUDE_EVENTS > 0)
#include "iattribute_access_t.h"
#endif //UASDK_INCLUDE_EVENTS

namespace uasdk
{

class IOperationCompleteListener_t;
class ITcpConnectionPlatform_t;
class IThreadPool_t;
class IAddressSpace_t;
class IUserPermissionsProvider_t;
class IServerStateListener_t;
class BuildInfo_t;
class MessageSecurityMode_t;
class UserTokenPolicy_t;
class ICertificatePrivateKeyPasswordProvider_t;
class ICertificateRejectedListListener_t;
class ITransactionListener_t;
class IRegisterNodeListener_t;
class IMonitoredItemListener_t;
class ITimerProvider_t;
class ILocalesProvider_t;
class ILogListener_t;
class ServerStackConfiguration_t;
class ServerCoreServicesConfiguration_t;
class ServerDataAccessConfiguration_t;
class ServerCapabilitiesConfiguration_t;
class CertificateGenerationParameters_t;
class LogMessage_t;
class TraceMessage_t;
class String_t;
class ByteString_t;
class IServerConfiguration_t;
class IThreadPool_t;

#if (UASDK_INCLUDE_EVENTS > 0)
class IAuditEventListener_t;
#endif

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Server Core
 *
 * A class that integrate the Server core implementations.
 *
 */
class IServerCore_t : public IRefCount_t
{
public:
  virtual ~IServerCore_t() {};

  /*****************************************************************************/
  /** Create the instance of the Server Core
   *
   * @param[out] result
   * The result of the server creation status
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the IServerCore_t
   * The caller must test the pointer before dereferencing it.
   */
  static IntrusivePtr_t<IServerCore_t> Create(Status_t& result);

  /*****************************************************************************/
  /** Create the Server Configuration
   *
   * @param[out] result
   * The result of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerConfiguration_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IServerConfiguration_t> CreateConfiguration(Status_t& result);

  /*****************************************************************************/
  /** Create an XML Nodeset I/O Utility
  *
  * @param[out] result
  * The result of the operation
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * IXmlNodesetIO_t. The caller must test the pointer
  * before dereferencing it.
  */
  static IntrusivePtr_t<IXmlNodesetIO_t> CreateXmlNodesetIO(bool doNotAllowDuplicateNodeId, Status_t& result);

  /*****************************************************************************/
  /** Create the address space
  *
  * @param[in] hashTableNoOfBuckets
  * Number of buckets in hash table
  *
  * @param[out] result
  * The result of the Server configuration creation status
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * IAddressSpace_t. The caller must test the pointer
  * before dereferencing it.
  */
  static IntrusivePtr_t<IAddressSpace_t> CreateAddressSpace(uint32_t hashTableNoOfBuckets, Status_t& result);

  /*****************************************************************************/
  /** Create the address space
  *
  * @param[out] result
  * The result of the Server configuration creation status
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * IAddressSpace_t. The caller must test the pointer
  * before dereferencing it.
  */
  static IntrusivePtr_t<IAddressSpace_t> CreateAddressSpace(Status_t& result);

  /*****************************************************************************/
  /** Create an allocator on the heap
  *
  * @param[in] buffer
  * pointer to buffer
  *
  * @param[in] bufferLengthInBytes
  * buffer length in Bytes
  *
  * @param[in] maxAllocationSizeInBytes
  * Maximum Allocation Size in Bytes
  *
  * @return
  * The result of the operation
  */
  static Status_t CreateAllocator(uint8_t* buffer, uint32_t bufferLengthInBytes, uint32_t maxAllocationSizeInBytes);

  /*****************************************************************************/
  /** Initialize the Server
   *
   * @param[in] configuration
   * The Server configuration
   *
   * @param[in] threadPool
   * The thread pool object to support multi threading
   *
   * @param[in] timerProvider
   * The timer object to be used by the server.
   *
   * @param[in] completeCallback
   * On successful completion of the Initialize operation
   * the call back method(OperationComplete) of * IOperationCompleteListener_t
   * will be called
   *
   * @return
   * Status of the Initialize operation.
   */
  virtual Status_t Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration,
                              IntrusivePtr_t<IThreadPool_t> threadPool,
                              IntrusivePtr_t<ITimerProvider_t> timerProvider,
                              IntrusivePtr_t<IOperationCompleteListener_t> completeCallback) = 0;

  /*****************************************************************************/
  /** Start the Server
   *
   * @param[in] completeCallback
   * On successful completion of the Start operation
   * the call back method(OperationComplete) of * IOperationCompleteListener_t
   * will be called
   *
   * @return
   * Status of the Initialize operation.
   */
  virtual Status_t Start(IntrusivePtr_t<IOperationCompleteListener_t> completeCallback) = 0;

  /*****************************************************************************/
  /** Stop the server
   *
   * @param[in] completeCallback
   * On successful completion of the Stop operation
   * the call back method(OperationComplete) of * IOperationCompleteListener_t
   * will be called
   *
   * @return
   * Status of the Initialize operation.
   */
  virtual Status_t Stop(IntrusivePtr_t<IOperationCompleteListener_t> completeCallback) = 0;

  /*****************************************************************************/
  /** Shutdown the server
  *
  * @return
  * Status of the Initialize operation.
  */
  virtual Status_t Shutdown(void) = 0;

  /*****************************************************************************/
  /** Get the Server Configuration
   *
   * @param[out] result
   * The result of the get Server configuration status
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerConfiguration_t. The caller must test the pointer
   * before dereferencing it.
   */
  virtual IntrusivePtr_t<IServerConfiguration_t> GetConfiguration(Status_t& result) = 0;

  /*****************************************************************************/
  /** Allocates requested size of bytes
   *
   * @param[in] size
   * Number of bytes to allocate
   *
   * @return
   * A pointer to the first byte of allocated space
   */
  virtual void* Malloc(size_t size) = 0;

  /*****************************************************************************/
  /** Allocates requested size of bytes and initializes to zero
   *
   * @param[in] size
   * Number of bytes to allocate
   *
   * @return
   * A pointer to the first byte of allocated space
   */
  virtual void* Calloc(size_t size) = 0;

  /*****************************************************************************/
  /** Change the size of previously allocated space
   *
   * @param[in] pointer
   * Pointer to the previously allocated memory
   *
   * @param[in] size
   * Number of bytes to allocate
   *
   * @return
   * A pointer to the first byte of allocated space
   */
  virtual void* Realloc(void* ptr, size_t size) = 0;

  /*****************************************************************************/
  /** Allocates requested size of bytes and
   *
   * @param[in] pointer
   * Pointer to the memory to be deallocated
   */
  virtual void Free(void* ptr) = 0;

  /*****************************************************************************/
  /** Validate the application instance certificate based on the security policy
   *
   * @param[in] policy
   * The Security policy configuration
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SecurityValidateApplicationInstanceCertificate(SecurityPolicy_t securityPolicy) = 0;

  /*****************************************************************************/
  /** Create the Self-signed application instance certificate
   *
   * @param[in] parameters
   *  The Certificate Parameters
   *
   * @param[in] completeCallback
   * On successful completion of the operation the call back method(OperationComplete)
   * of IOperationCompleteListener_t will be called
   *
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SecurityCreateSelfSignedApplicationInstanceCertificate(
      IntrusivePtr_t<const CertificateGenerationParameters_t> parameters,
      IntrusivePtr_t<IOperationCompleteListener_t> completeCallback) = 0;

  /*****************************************************************************/
  /** Refresh the certificate directory stores
   *
   * @param[in] group
   * The certificate group
   *
   * @param[in] completeCallback
   * On successful completion of the Start operation
   * the call back method(OperationComplete) of * IOperationCompleteListener_t
   * will be called
   *
   * @return
   * Status of the Initialize operation.
   */
  virtual Status_t SecurityRefreshCertificateDirectoryStores(UA_CertificateGroup_t group,
                                                             IntrusivePtr_t<IOperationCompleteListener_t> completeCallback) = 0;

  /*****************************************************************************/
  /** Create the Certificate directory stores
   *
   * @param[in] completeCallback
   * On successful completion of the Start operation
   * the call back method(OperationComplete) of * IOperationCompleteListener_t
   * will be called
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t SecurityCreateCertificateDirectoryStores(IntrusivePtr_t<IOperationCompleteListener_t> completeCallback) = 0;

  /*****************************************************************************/
  /** This function is used to establish new TCP connection
   *
   * @param[in] connection
   * New connection which needs to be eshtablished
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t TCPNewConnectionReceived(IntrusivePtr_t<ITcpConnectionPlatform_t> connection) = 0;

#if (UASDK_INCLUDE_EVENTS > 0)
  /*****************************************************************************/
   /** Fire event
    *
    * This function will be called when the server application want to fire an event
    *
    * @param[in] event
    * The event to be fired
    *
    * @param[in] eventSource
    * The event source node Id of the event to be fired
    *
    * @param[in] receiveTime
    * The UTC time that the event is received or generated
    *
    * @return
    * Status of the operation.
    */
  virtual Status_t FireEvent(IntrusivePtr_t<IAttributeAccess_t> event,
														 IntrusivePtr_t<NodeId_t>& eventSource,
														 IntrusivePtr_t<UtcTime_t>& receiveTime) = 0;


  /**************************************************************************/
  /** Register Audit Event Listener
   *
   * This function is called by the server application to register a callback for audit events
   * 
   * @param[in] auditEventListener
   * The listener to receive the callback.  Provide an empty pointer to clear the registered listener.
   *
   * @return
   * Status of the operation
   */

  virtual Status_t RegisterAuditEventListener(IntrusivePtr_t<IAuditEventListener_t> &auditEventListener) = 0;

 #endif //UASDK_INCLUDE_EVENTS

};

/** @} */

}
#endif //#if (UASDK_INCLUDE_SERVER > 0)
#endif // _ISERVERCORE_T_
