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

#ifndef _UASERVER_T_
#define _UASERVER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SERVER > 0)

#if (UASDK_INCLUDE_SERVER_WINDOWS_LINUX_MT > 0)

#include "scoped_ptr_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_message_security_mode_t.h"
#include "iserver_core_t.h"
#include "intrusive_embedded_queue_t.h"
#include "irunnable_t.h"
#include "itimer_provider_t.h"
#include "ithread_pool_t.h"
#include "tcp_connection_platform_t.h"
#include "file_descriptors_t.h"
#include <thread>
#include "opcua_server_state_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)
#include "system_status_change_event_type_data_t.h"
#endif

namespace uasdk
{

/** \addtogroup grpServer_MT
 *@{*/

/*****************************************************************************/
/** \brief UA Server
 *
 * A class that integrate the UA Server implementations.
 *
 */
class UAServer_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IServerCore_t> core
   * Intrusive pointer to the Server core
   */
  IntrusivePtr_t<IServerCore_t> core;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IThreadPool_t> threadPool
   * Intrusive pointer to the thread pool
   */
  IntrusivePtr_t<IThreadPool_t> threadPool;

  /*****************************************************************************/
  /* @var IntrusiveEmbeddedQueue_t<IRunnable_t> runQueue
   * Intrusive pointer to the run queue
   */
  IntrusiveEmbeddedQueue_t<IRunnable_t> runQueue;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ITimerProvider_t> timerProvider
   * Intrusive pointer to the timer provider
   */
  IntrusivePtr_t<ITimerProvider_t> timerProvider;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<FileDescriptors_t> fileDescriptors
   * Intrusive pointer to the file descriptors
   */
  IntrusivePtr_t<FileDescriptors_t> fileDescriptors;

  std::thread tcpipThread;
  Atomic_t<bool> quit;

  /*****************************************************************************/
  /** Check if the poll is Due
   *
   * @param[in] uint32_t* last_poll_time_ms
   * Last poll time in millisecond
   *
   * @param[in] uint32_t* next_poll_time_ms
   * Next poll time in millisecond
   *
   * @param[in] uint32_t serverCyclicRate
   * Server cyclic rate
   *
   * @return
   * Status of the Initialize operation.
   */
  static bool IsPollDue(uint32_t* last_poll_time_ms, uint32_t* next_poll_time_ms, uint32_t serverCyclicRate);

  /*****************************************************************************/
  /** Poll delay
   *
   * @param[in] uint32_t last_poll_time_ms
   * Last poll time in millisecond
   *
   * @param[in] uint32_t next_poll_time_ms
   * Next poll time in millisecond
   *
   * @return
   * poll delay seconds
   */
  static suseconds_t PollDelay(uint32_t last_poll_time_ms, uint32_t next_poll_time_ms);

  /*****************************************************************************/
  /** Get the TCP connection
   *
   * @param[in] IntrusiveList_t<TcpConnectionPlatform_t>& connections
   * TCP connection
   *
   * @param[in] SOCKET fd
   * TCP socket file descriptor
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TcpConnectionPlatform_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<TcpConnectionPlatform_t> GetConnection(IntrusiveList_t<TcpConnectionPlatform_t>& connections, SOCKET fd);

  /*****************************************************************************/
  /** Run the server.
   *
   * @param[in] IntrusiveList_t<IServerCore_t>& core
   * Server core
   *
   * @param[in] IntrusiveList_t<ITimerProvider_t>& timerProvider
   * timer provider
   *
   */
  void TcpipRun(IntrusivePtr_t<IServerCore_t> core, IntrusivePtr_t<ITimerProvider_t> timerProvider);


  /*****************************************************************************/
  /** Start the TCP socket listener
   *
   * @param[in] uint32_t port
   * TCP port number
   *
   */
  static SOCKET Start_listener(uint32_t port);

public:
  virtual ~UAServer_t();

  /*****************************************************************************/
  /** Create the Server Configuration
   *
   * @param[out] result
   * The result of the Server configuration creation status
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerConfiguration_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IServerConfiguration_t> CreateConfiguration(Status_t& result);


  /*****************************************************************************/
  /** Create the XLM node set IO
   *
   * @param[in] bool doNotAllowDuplicateNodeId
   * Do not allow dupilcate node id
   *
   * @param[out] result
   * The status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IXmlNodesetIO_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IXmlNodesetIO_t> CreateXmlNodesetIO(bool doNotAllowDuplicateNodeId, Status_t& result);

  /*****************************************************************************/
  /** Create the AddressSpace
   *
   * @param[out] result
   * The status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IAddressSpace_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IAddressSpace_t> CreateAddressSpace(Status_t& result);

  /*****************************************************************************/
  /** Create the AddressSpace
  *
  * @param[in] hashTableNoOfBuckets
  * Number of Hash table buckets
  *
  * @param[out] result
  * The status of the operation
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * IAddressSpace_t. The caller must test the pointer
  * before dereferencing it.
  */
  static IntrusivePtr_t<IAddressSpace_t> CreateAddressSpace(uint32_t hashTableNoOfBuckets, Status_t& result);

  /*****************************************************************************/
  /** Create the allocator
   *
   * @param[out] uint8_t* buffer
   *  Allocator Buffer
   *
   * @param[out] uint32_t bufferLengthInBytes
   * Buffer length in bytes
   *
   * @param[out] uint32_t maxAllocationSizeInBytes
   *  Maximum allocation size in bytes
   *
   * @return
   * Status of the operation
   */
  static Status_t CreateAllocator(uint8_t* buffer, uint32_t bufferLengthInBytes, uint32_t maxAllocationSizeInBytes);

   /*****************************************************************************/
   /** Initialize the Server
    *
    * @param[in] configuration
    * The Server configuration. An intrusive reference counting Boost-style smart
    * pointer to the IServerConfiguration_t.
    *
    * @param[in] threadPoolSize
    * Number of threads in the server thread pool.
    *
    * @return
    * Status of the Initialize operation.
    */
  Status_t Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration, uint32_t threadPoolSize);

   /*****************************************************************************/
   /** Start the Server
    *
    * @param[in] license
    * The Server License
    *
    * @return
    * Status of the Initialize operation.
    */
  Status_t Start(const String_t& license);

   /*****************************************************************************/
   /** Stop the server
    *
    * @return
    * Status of the Initialize operation.
    */
  Status_t Stop(void);

  /*****************************************************************************/
  /** Terminate the server
  *
  * @return
  * Status of the operation.
  */
  Status_t Terminate(void);

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
  IntrusivePtr_t<IServerConfiguration_t> GetConfiguration(Status_t& result);

   /*****************************************************************************/
   /** Validate the application instance certificate based on the security policy
    *
    * @param[in] policy
    * The Security policy configuration
    *
    * @return
    * Status of the operation.
    */
  Status_t SecurityValidateApplicationInstanceCertificate(SecurityPolicy_t securityPolicy);

   /*****************************************************************************/
   /** Create the Self-signed application instance certificate
    *
    * @param[in] parameters
    *  The Certificate generation Parameters
    *
    * @return
    * Status of the operation.
    */
  Status_t SecurityCreateSelfSignedApplicationInstanceCertificate(
      IntrusivePtr_t<const CertificateGenerationParameters_t> parameters);

   /*****************************************************************************/
   /** Create the Certificate directory stores
    *
    * @return
    * Status of the operation.
    */
  Status_t SecurityCreateCertificateDirectoryStores(void);

   /*****************************************************************************/
   /** Refresh the Application Certificate directory stores
    *
    * @return
    * Status of the operation.
    */
  Status_t SecurityRefreshApplicationCertificateDirectoryStores(void);

   /*****************************************************************************/
   /** Refresh the User Certificate directory stores
    *
    * @return
    * Status of the operation.
    */
  Status_t SecurityRefreshUserCertificateDirectoryStores(void);

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
  Status_t FireEvent(IntrusivePtr_t<IAttributeAccess_t> event,
										 IntrusivePtr_t<NodeId_t>& eventSource,
                     IntrusivePtr_t<UtcTime_t>& receiveTime);

  /*****************************************************************************/
   /** Fire System Status Change event
    *
    * This function is used to create and fire a System Status Change event
    *
    * @param[in] state
    * The server state to be changed into
    *
    * @return
    * Status of the operation.
    */
  Status_t FireSystemStatusChangeEvent(ServerState_t::Enum_t state);

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
	Status_t RegisterAuditEventListener(IntrusivePtr_t<IAuditEventListener_t>& auditEventListener);

#endif //UASDK_INCLUDE_EVENTS

};

/** @} */

}

#endif //UASDK_INCLUDE_SERVER_WINDOWS_LINUX_MT

#endif // if UASDK_INCLUDE_SERVER > 0

#endif // _UASERVER_T_
