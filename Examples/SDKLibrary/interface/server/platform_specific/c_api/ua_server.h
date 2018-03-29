/** @file */

/**
 * \defgroup grpUserAuthentication_C_API User Authentication Functions
 * \defgroup grpDiagnostics_C_API Diagnostic and Test Functions
 * \defgroup grpTranslate_C_API Translation and Text Lookup Functions
 * \defgroup grpFileTransfer_C_API File Transfer Functions
 * \defgroup grpDeferredReads_C_API Deferred Read Functions
 * \defgroup grpNoSecurity_C_API Certificate Functions For Compilation Without Security
 * \defgroup grpAddressSpace_C_API Address Space Functions
 * \defgroup grpTcpIp_C_API TCP/IP Functions
 * \defgroup grpSecurity_C_API Security Functions
 * \defgroup grpConfig_C_API Configuration and Control Functions for
 * \defgroup grpReadWrite_C_API Read and Write Functions
 * \defgroup grpMemory_C_API Memory Allocation Functions
 *
 */

/** \addtogroup grpServer_C_API
 *@{*/


/*****************************************************************************/
/** \file ua_server.h
 *  \brief The OPC-UA Embedded Server SDK API Definition.
 *
 */

/*****************************************************************************/
/* Copyright (c) 2009 - 2013 MatrikonOPC.
 *
 * ALL RIGHTS RESERVED.
 *
 * The information contained herein is the confidential and proprietary product
 * of MatrikonOPC.  Any unauthorized use, reproduction or
 * transfer of this information is strictly prohibited.
 */

#ifndef _UA_SERVER_
#define _UA_SERVER_

#include "uasdk_includes.h"
#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

/*****************************************************************************/
/* Include Files
 */
#include "ua_types.h"
#include "ua_server_config.h"

#ifdef __cplusplus
extern "C" {
#endif



/*****************************************************************************/
/** Function provided by host to enable library to time its internal operations
 *
 * The library requires a millisecond timer in order to operate. This timer is
 * implemented via a uint32_t which increments every millisecond. The host must
 * implement this function as it is called periodically by the stack.
 *
 * @return
 * A counter that increments every millisecond.
 */
uint32_t UAServer_Callback_millisecond(void);

/*****************************************************************************/
/** Function provided by host to enable library to obtain current date and time
 *
 * The library requires the current date and time in order to operate. This timer
 * is implemented via an int64_t which represents UTC time and data in
 * accordance with Windows FILETIME. This is the number of 100ns intervals
 * since January 1, 1601. The host must implement this function as it is called
 * periodically by the library.
 *
 * @return
 * Current date and time.
 */
int64_t UAServer_Callback_datetime(void);

/*****************************************************************************/
/** Function provided by host to provide pseudo-random numbers
 *
 * The library requires a pseudo-random number generator in order to operate.
 * The host must implement this function as it is called periodically by the
 * library.
 *
 * @return
 * A pseudo-random number.
 */
uint32_t UAServer_Callback_pseudeo_random_number(void);

/*****************************************************************************/
/** Function provided by host to provide a memcpy implementation
 *
 * Some platforms can dramatically improve the performance of memcpy for
 * large data blocks by using DMA or other techniques. If required, a custom
 * implementation may be inserted here. Where a custom implementation is not required
 * simply call the standard library implementation.
 *
 * @param[in] destination
 * Pointer to the destination array where the content is to be copied, type-casted
 * to a pointer of type void*.
 *
 * @param[in] source
 * Pointer to the source of data to be copied, type-casted to a pointer of type
 * const void*.
 *
 * @param[in] num
 * Number of bytes to copy. size_t is an unsigned integral type.
 *
 * @return
 * "destination" is returned.
 */
void* UAServer_Callback_memcpy(void * destination, const void * source, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a memchr implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] ptr
 * Pointer to the block of memory where the search is performed.
 *
 * @param[in] value
 * Value to be located. The value is passed as an int, but the function performs
 * a byte per byte search using the unsigned char conversion of this value.
 *
 * @param[in] num
 * Number of bytes to be analyzed. size_t is an unsigned integral type.
 *
 * @return
 * A pointer to the first occurrence of value in the block of memory pointed
 * by ptr. If the value is not found, the function returns a null pointer.
 */
const void* UAServer_Callback_memchr(const void* ptr, int32_t value, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a memset implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] ptr
 * Pointer to the block of memory to fill.
 *
 * @param[in] value
 * Value to be set. The value is passed as an int, but the function fills the
 * block of memory using the unsigned char conversion of this value.
 *
 * @param[in] num
 * Number of bytes to be set to the value. size_t is an unsigned integral type.
 *
 * @return
 * "ptr" is returned.
 */
void* UAServer_Callback_memset(void * ptr, int32_t value, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a memcmp implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] ptr1
 * Pointer to block of memory.
 *
 * @param[in] ptr2
 * Pointer to block of memory.
 *
 * @param[in] num
 * Number of bytes to compare.
 *
 * @return
 * Returns an integral value indicating the relationship between the content
 * of the memory blocks:
 * A zero value indicates that the contents of both memory blocks are equal.
 * A value greater than zero indicates that the first byte that does not match
 * in both memory blocks has a greater value in ptr1 than in ptr2 as if evaluated
 * as unsigned char values; And a value less than zero indicates the opposite.
 */
int UAServer_Callback_memcmp(const void * ptr1, const void * ptr2, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a strncpy implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] destination
 * Pointer to the destination array where the content is to be copied.
 *
 * @param[in] source
 * C string to be copied.
 *
 * @param[in] num
 * Maximum number of characters to be copied from source.
 * size_t is an unsigned integral type.
 *
 * @return
 * destination is returned.
 */
char* UAServer_Callback_strncpy(char *destination, const char *source, size_t num);



/** \addtogroup grpReadWrite_C_API
 *@{*/

/*****************************************************************************/
/** Function provided by host to enable library to read values
 *
 * The library requires the ability to read values from the host system in order
 * to operate. This ability is provided by this function which must be
 * implemented by the host system. This function is called by the library and
 * the implemented function must call UA_Perform_read() in order to perform
 * the actual read operation.
 *
 * @param[in] node_handle
 * A unique identifier that the host can use to efficiently look up the value.
 *
 * @param[in] value_type
 * In order to keep the API lean, this function returns the variable to the
 * library via a non type safe void pointer.
 * The value_type parameter provides run-time type safety by specifying
 * the data type the library expects for the value attribute of the node and
 * allowing the host to verify this against the node handle provided by the library.
 *
 * @param[in] max_array_length
 * Similar to the value_type parameter, the max_array_length parameter facilitates
 * run-time type safety by specifying the max array length the library expects
 * for the provided pointer allowing the host to verify this against the
 * node handle provided by the library.
 *
 * @param[in] read_context
 * A pointer to an opaque data structure providing context to the pending read
 * operation. The host must pass this pointer to UA_Perform_read().
 *
 */
void UAServer_Callback_read(uintptr_t node_handle,
		UA_Value_type_t value_type,
		uint32_t max_array_length,
		uintptr_t read_context);

/*****************************************************************************/
/** Performs a read operation
 *
 * The host calls this function from UA_Read_callback() to perform a read on
 * the requested node.
 *
 * @param[in] read_context
 * A pointer to an opaque data structure providing context to the pending read
 * operation. The user must pass this pointer to UA_Perform_read().
 *
 * @param[in] data_value
 * A pointer to the value required to be read by
 * the library or 0 if the input parameters failed verification or the value
 * is not readable. The value would not be readable if the host system's 
 * connection to the underlying data source was unavailable. In this case the
 * host may decide to simply return the most recent cached value (with a
 * corresponding old timestamp) or may return 0 in order to indicate that
 * the data cannot be read.
 *
 * @param[in] source_timestamp
 * Each time the host value is updated by the host, the host should timestamp
 * the update. This timestamp is provided to the library via this parameter and
 * communicated to the client in the DataValue structure.
 *
 * @param[in] status_code
 * For Data Access variable types the user must provide a data quality status code
 * to inform the client as to the status of the data read. For base data variable
 * calls this value is ignored by the library and the server returns Bad_NotReadable
 * if the call provides a 0 data_value pointer.
 * For Data Access variables it is expected that the user will write the correct
 * data quality value into this parameter on every call. For some systems only a
 * couple of the available values may be relevant and in this case it is not
 * necessary to use them all.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Perform_read(uintptr_t read_context,
                                  UA_Value_t data_value,
                                  int64_t source_timestamp,
                                  UA_Status_t status_code);

/*****************************************************************************/
/** Function provided by host to enable library to write values
 *
 * The library requires the ability to write values from the host system in order
 * to operate. This ability is provided by this function which must be
 * implemented by the host system. This function is called by the library and
 * the implemented function must call UA_Perform_write() in order to perform
 * the actual write operation.
 *
 * @param[in] node_handle
 * A unique identifier that the host can use to efficiently look up the value.
 *
 * @param[in] value_type
 * In order to keep the API lean, this function returns the variable to the
 * library via a non type safe void pointer.
 * The value_type parameter provides run-time type safety by specifying
 * the data type the library expects for the value attribute of the node and
 * allowing the host to verify this against the node handle provided by the library.
 *
 * @param[in] status_code
 * The status_code for the value written by the client.
 *
 * @param[in] max_array_length
 * Similar to the value_type parameter, the max_array_length parameter facilitates
 * run-time type safety by specifying the max array length the library expects
 * for the provided pointer allowing the host to verify this against the
 * node handle provided by the library.
 *
 * @param[in] write_context
 * A pointer to an opaque data structure providing context to the pending write
 * operation. The user must pass this pointer to UA_Perform_write().
 */
void UAServer_Callback_write(uintptr_t node_handle,
                             UA_Value_type_t value_type,
                             UA_Status_t status_code,
                             uint32_t max_array_length,
                             uintptr_t write_context);

/*****************************************************************************/
/** Performs a write operation
 *
 * The host calls this function from UA_Write_callback() to perform a write on
 * the requested node.
 *
 * @param[in] write_context
 * A pointer to an opaque data structure providing context to the pending write
 * operation. The user must pass this pointer to UA_Perform_write().
 *
 * @param[in] data_value
 * A pointer to the value required to be written by
 * the library or 0 if the input parameters failed verification or the value
 * is not writable. The value would not be writable if the host system's 
 * connection to the underlying data source was unavailable. In this case the
 * host may decide to simply provide the most recent cached value (with a
 * corresponding old timestamp) or may provide 0 in order to indicate that
 * the data cannot be written.
 *
 * @param[in] source_timestamp
 * The timestamp for the value when written by the client. This may be modified
 * by the library during the write if the client specified a source timestamp.
 *
 * @param[in] completes_asynchronously
 * If the write to the underlying system completes asynchronously then this
 * flag should be set. Alternatively if the write to the underlying system
 * completes before the completion of UAServer_Write_callback() this flag
 * should be cleared. The flag affects the result code the library returns to
 * the OPC-UA Client. If the call succeeds and the flag is set the
 * write operation level result is OpcUa_GoodCompletesAsynchronously. if the
 * write succeeds and the flag is not set the write operation level result
 * code is OpcUA_Good.
 *
 * @param[out] new_length_of_array
 * When a client writes to the value attribute of a node containing an array,
 * the client can change the length of the array by writing a complete array
 * that is shorter than the maximum array length. This parameter informs the
 * host what the new array length is after the write in case this information
 * is of interest.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Perform_write(uintptr_t write_context,
                                   UA_Value_t data_value,
                                   int64_t* source_timestamp,
                                   bool_t completes_asynchronously,
                                   uint32_t* new_length_of_array);

/*****************************************************************************/
/** Sets the result code of a write operation
 *
 * The host can optionally call this function from UA_Write_callback() to
 * revise the result code of a write operation. The Server SDK is a single
 * threaded design and it is highly highly recommended that callbacks are
 * completed promptly in order to reduce server latency and jitter. Where the
 * application performs activities in the callbacks that delay the server by
 * milliseconds server latency and jitter as experienced by the client can be poor.
 * For this reason write operations that complete over a serial line, backplane
 * or other slow medium should be buffered in the application and completed
 * asynchronously. Where it is feasible and desirable to complete a write within
 * the callback this call can be made after UAServer_Perform_write() and before
 * returning from the callback in order to modify the result of the write
 * operation, for example setting a bad operation level result due to a write
 * failure.
 *
 * @param[in] write_context
 * A pointer to an opaque data structure providing context to the pending write
 * operation. The user must pass this pointer to UA_Perform_write().
 *
 * @param[in] result_code
 * If the write to the underlying system completed synchronously after the
 * UAServer_Perform_write() call (i.e. that call only buffered the data prior to
 * the actual physical write) then this parameter specifies the actual
 * write operation level result code. The default result code populated during
 * UAServer_Perform_write() would have been OpcUa_Good.
 *
 */
void UAServer_Set_write_operation_level_result_code( uintptr_t write_context,
                                                     UA_Status_t result_code);

/*****************************************************************************/
/** Function provided by host to enable library to indicate that a monitored
 *  item has been created for a variable node
 *
 * Certain host systems may require notice from the library that a monitored
 * item has been created or destroyed in order to maintain an internal cache
 * of values or otherwise efficiently manage their read operations. This
 * callback function enables a host to do so if it wishes but can be ignored
 * if not required. Hosts must still be prepared to handle read callbacks for
 * variables that are not being monitored (OPC-UA Read Service).
 *
 * @param[in] node_handle
 * An identifier that the host can use to efficiently look up the value.
 *
 * @param[in] monitored_item_id
 * A unique identifier in the SDK for the monitored item.
 *
 * @param[in] operation
 * Indicates if a monitored item has been created, modified (for example had
 * its sample rate change) or destroyed.
 *
 * @param[in] sampling_interval_ms
 * The sampling interval in milliseconds.
 *
 */
void UAServer_Callback_monitored_item(uintptr_t node_handle, uint32_t monitored_item_id,
    UA_Mon_Item_Callback_Operation_t operation, uint64_t sampling_interval_ms);

/*@}*/

/** \addtogroup grpUserAuthentication_C_API
 *@{*/

/*****************************************************************************/
/** Function provided by host to enable users to login
 *
 * The library optionally requires the ability to authenticate users in order
 * to operate. This ability is provided by this function which must be
 * implemented by the host system. This function is called by the library to
 * authenticate username/password combinations provided by a client when
 * negotiating a session. The host maintains a table of valid user names and
 * corresponding passwords. If the provided username & password authenticates
 * successfully the host provides the library with a user index. The user index
 * is a value from 1 to 15 indicating the user that has logged in. The user
 * index provided by the host is used in conjunction with the node visibility
 * bit mask to filter nodes visible to the current user.
 *
 * @param[in] username
 * The user name provided.
 *
 * @param[in] password
 * The password provided.
 *
 * @param[out] user_index
 * The user index for this user. Must be set if function returns true.
 *
 * @return
 * True if user authenticates successfully, else false.
 */
bool_t UAServer_Callback_login_username_password(const UA_UTF8_string_t* username,
                               const UA_UTF8_string_t* password,
                               uint16_t* user_index);

/*****************************************************************************/
/** Function provided by host to enable users to login
 *
 * The library optionally requires the ability to authenticate users in order
 * to operate. This ability is provided by this function which must be
 * implemented by the host system although it is only necessary to handle the
 * callback if the host configures the SDK to support X509 certificates for
 * user authentication.
 *
 * This function is called by the library to authenticate X509V3 certificates
 * provided by a client when negotiating a session. The host maintains a table
 * of valid certificates. If the provided thumbprint authenticates
 * successfully the host provides the library with a user index. The user index
 * is a value from 1 to 15 indicating the user that has logged in. The user
 * index provided by the host is used in conjunction with the node visibility
 * bit mask to filter nodes visible to the current user.
 *
 * The certificate is provided here purely as a convenience to hosts
 * that are interested in it. Only the thumbprint is required to identify the
 * certificate and authenticate a user.
 *
 * This callback will only be executed if the certificate first validates for
 * trust, content, etc. using the user certificate trust and issuer stores.
 *
 * @param[in] certificate
 * The certificate provided by the client in DER format.
 *
 * @param[in] thumbprint
 * The certificate thumbprint.
 *
 * @param[out] user_index
 * The user index for this user. Must be set if function returns true.
 *
 * @return
 * True if user authenticates successfully, else false.
 */
bool_t UAServer_Callback_login_x509_certificate(const UA_Byte_string_t* certificate,
                               const UA_UTF8_string_t* thumbprint,
                               uint16_t* user_index);

/*@}*/

/** \addtogroup grpDiagnostics_C_API
 *@{*/

/*****************************************************************************/
/** Function provided by library to enable host to obtain current date and time
 *
 * Where the library is using time emulation the callback function for DateTime
 * is not used. THis function allows the host to obtain the date and time in
 * use by the library in order to print accurate log messages as an aid to
 * debugging.
 *
 * @return
 * Current date and time.
 */
int64_t UAServer_Get_datetime(void);

/*****************************************************************************/
/** Enable time emulation mode
 *
 * Call this function if the default (disabled) is unsuitable. When enabled,
 * time emulation sets the server date & time from incoming client request
 * packets in order to allow the server to operate with no date and time
 * infrastructure implemented on the host system. In this case,
 * UAServer_Callback_datetime is not called. Time emulation is for testing only
 * and is not standard compliant.
 *
 * @param[in] enable    Enable or disable time emulation mode
 */
void UAServer_Time_emulation_enabled(bool_t enable);

/*****************************************************************************/
/** A log message from the server stack
 *
 * Supports debugging of a server implementation.
 *
 * @param[in] severity
 * The severity of the log event
 *
 * @param[in] timestamp
 * The timestamp of the event
 *
 * @param[in] file_name
 * The source filename of the file generating the event
 *
 * @param[in] line_number
 * The source line number of the file generating the event
 *
 * @param[in] payload_type
 * The type of the payload accompanying the log event
 *
 * @param[in] payload
 * A pointer to payload related to the log event
 *
 * @param[in] payload_length
 * The length of the payload related to the log event
 *
 */
void UAServer_Callback_log(UA_Log_severity_t severity,
                          int64_t timestamp,
                          const char* file_name,
                          uint32_t line_number,
                          UA_Log_payload_t payload_type,
                          const void* payload,
                          uint32_t payload_length);

/*****************************************************************************/
/** A printf message from the server stack
 *
 * Supports debugging of a server implementation.
 *
 * @param[in] timestamp
 * The timestamp of the message
 *
 * @param[in] format
 * Message format string
 *
 * @param[in] ...
 * Variable argument list
 *
 */
void UAServer_Printf( int64_t timestamp, const char* format, ... );

/*****************************************************************************/
/** Get information about the memory utilisation
 *
 * @param[out] total_memory_provided
 * The total memory provided to the SDK.
 *
 * @param[out] memory_unusable
 * The memory that is unusable due to the characteristics of the allocator.
 * Modifying the amount of memory provided by this amount results in optimum
 * efficiency.
 *
 * @param[out] max_memory_used_this_run
 * The maximum memory used since the server was started.
 *
 * @param[out] total_memory_recommended
 * The total memory recommended. This assumes that the server has been stressed
 * to the maximum degree likely to be encountered in the field. The
 * max_memory_used_this_run is multiplied by a 1.5 safety margin.
 * total_memory_recommended is calculated based on the maximum amount of memory
 * used by the server since initialisation. If the server memory utilisation has
 * not been exercised to the maximum then the recommended figure is meaningless.
 * Operating the server with less than total_memory_recommended bytes can
 * result in failure over time due to exhaustion of the memory
 * subsystem.
 *
 * @return  The result of the operation. The output arguments are only valid if
 *          the return value == OpcUa_Good.
 */
UA_Status_t UAServer_memory_info(
    uint32_t* total_memory_provided,
    uint32_t* memory_unusable,
    uint32_t* max_memory_used_this_run,
    uint32_t* total_memory_recommended);

/*@}*/

/** \addtogroup grpConfig_C_API
 *@{*/

/*****************************************************************************/
/** Initialise the library
 *
 * This function returns OpcUa_Good if no errors are found during initialisation.
 * If security is excluded from the build all errors are unrecoverable and the
 * server will not start.
 * If security is included in the build errors related to the application
 * instance certificate are recoverable and the server will still start.
 *
 * Specifically:
 *
 * OpcUa_BadNoValidCertificates. An application instance certificate and private
 * key are not found. The initialisation was successful but a certificate must
 * be created or installed in order to proceed successfully.
 *
 * OpcUa_BadSecurityChecksFailed. The application instance certificate failed
 * validation for an undetermined reason (it may be corrupted). The initialisation
 * was successful but if a new certificate is not created or installed the server
 * may not interoperate correctly.
 *
 * OpcUa_BadCertificateTimeInvalid. The application instance certificate failed
 * validation due to an invalid time (it may have expired). The initialisation
 * was successful but if a new certificate is not created or installed the server
 * may not interoperate correctly. Also, operating the server with an expired
 * certificate may be against your stated security policy.
 *
 * OpcUa_BadCertificateRevoked. The application instance certificate failed
 * validation because it has been revoked or because the CA CRL could not be
 * found offline. The initialisation was successful but if a new certificate
 * is not created or installed the server may not interoperate correctly.
 * Also, operating the server with a revoked certificate may be against your
 * stated security policy. It is possible that this error is generated due to
 * initialising the server with an incorrect option bit configuration. To
 * avoid this initialise the server before setting validation option bits.
 *
 * @param[in] config
 * The requested server configuration data structure.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Initialise(const UA_Configuration_t* config);

/*****************************************************************************/
/** Terminate the library
 *
 * Releases all resources allocated by the library. Not required to be called
 * in a typical embedded environment.
 */
void UAServer_Terminate(void);

/*****************************************************************************/
/** Adds an IP address of a network interface
 *
 * Where the target device does not have a Hostname, the stack requires
 * the IP Address of the network interface in order to generate URI's and
 * application instance certificates. Up to MAX_IP_ADDRESSES may be added.
 * In general, IPAddresses should NOT be added where a Hostname has already
 * been added.
 *
 * @param[in] ip_address
 * A 4-byte long byte array containing the IP Address of the network interface.
 * Example: "192.168.2.1" == { 0xC0, 0xA8, 0x02, 0x01 }
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Add_IP_address(uint8_t* ip_address);

/*****************************************************************************/
/** Clears the list of IP addresses
 *
 * It is possible that when using DHCP, an IP Address may change during
 * server operation. In this case the list of IP addresses must be cleared by
 * calling this function followed immediately by one or more calls to
 * UA_Tcpip_add_IP_address().
 * It is only required to use this function where the device has no Hostname
 * and is using DHCP for IP Address assignment.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Clear_all_IP_addresses(void);

/*****************************************************************************/
/** Adds a Hostname of the device
 *
 * Where the target device has a Hostname, the stack requires this name in
 * order to generate URI's and application instance certificates.
 * Up to MAX_HOSTNAMES may be added. IPAddresses should NOT be added where
 * a Hostname has already been added.
 *
 * @param[in] hostname
 * A null terminated ANSI C string containing the hostname.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Add_hostname(const char* hostname);

/*****************************************************************************/
/** Clears the list of host names
 *
 * Host names rarely change. However, should a hostname change during server
 * operation it is required to clear the internal list of names and immediately
 * populate the list with the new name(s) using UA_Tcpip_add_hostname().
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Clear_all_hostnames(void);

/*****************************************************************************/
/** Poll library periodically
 *
 * The library must be polled at the cyclic rate specified in the
 * configuration data structure. No checking is performed internally on timing
 * so the timing behaviour of the server is directly dependent on the accuracy
 * of polling by the application.
 *
 */
void UAServer_Poll(void);

/*****************************************************************************/
/** Set Server URI
 *
 * The OPC-UA Server must be given a unique name or Universal Resource
 * Identifier (URI). This name will be cached by clients that regularly
 * connect to the server so for any particular device, the name must be
 * constant. This name can be stored in non-volatile storage as a constant, or
 * alternatively can be calculated dynamically during startup based on the
 * machine MAC address or some other constant, unique value.
 * The URI can be in any format. We recommend using the URN (Uniform Resource
 * Name) UUID (Universally Unique IDentifier) format as follows:
 * "urn:uuid:6e8bc430-9c3a-11d9-9669-0800200c9a66"
 *
 * @param[in] uri
 * A null terminated ANSI C string containing the URI.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Set_URI(const char* uri);

/*****************************************************************************/
/** Start Server
 *
 * Must be called in order to start the server.
 *
 * @param[in] license
 * Some distributions require a license string in order to start. If your
 * distribution does not require a license string simply provide a NULL pointer.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Start(const char* license);

/*****************************************************************************/
/** Stop Server
 *
 * Must be called in order to stop the server. Will stop the server immediately
 * if no clients are connected. Will change server status and forcibly
 * disconnect any connected clients after 60 seconds if clients are connected.
 * After stopping the server the application should poll UAServer_get_state to
 * detect when the shutdown is complete. The application can then call
 * UAServer_Terminate to release all resources. A stopped server will refuse
 * all attempts to create new TCP Binary connections.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Stop(void);

/*****************************************************************************/
/** Get Server State
 *
 * Reads the current server state.
 *
 * @param[out] shutdown_complete
 * If the server state is shutdown, the server may be in the process of shutting
 * down. In this state this variable informs the host whether or not the
 * shutdown is complete.
 *
 * @return  The result of the operation.
 */
UA_Server_state_t UAServer_Get_state(bool_t* shutdown_complete);

/*@}*/

/** \addtogroup grpNoSecurity_C_API
 *@{*/

/*****************************************************************************/
/** Generate Application Instance Certificate
 *
 * The OPC UA Server optionally requires an X.509 application instance certificate.
 * Version 1.02 of the OPC-UA Standard made this certificate optional for servers
 * that do not support secure channels (x509 authentication and encryption) but
 * for backward compatibility with OPC-UA Clients designed to version 1.01 of the
 * standard it it is recommended to always generate a certificate. This
 * certificate contains the server URI and server hostnames or IP addresses.
 * If this information changes the server certificate must be regenerated by
 * calling this function. This function creates a certificate including signing
 * of the certificate using RSA encryption. This is a resource intensive operation
 * so (depending on your platform) should only be done once during initialisation.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Generate_certificate(void);

/*****************************************************************************/
/** Read Application instance Certificate size
 *
 * Certificate generation via UAServer_Generate_certificate() is a resource
 * intensive operation that can be very slow on some platforms. If the IP
 * Address or Hostname of the server remains the same then the generated certificate
 * will be the same each time. Instead of generating the certificate on every POST,
 * the certificate can be generated (on a development system or on the target) once
 * and then provided at POST in order to shorten boot time.
 *
 * Provides the size of the generated certificate to facilitate the host application
 * allocating sufficient memory to read out the certificate.
 *
 * @param[out] size_in_bytes
 * The size of the generated certificate in bytes.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Get_certificate_size(uint32_t* size_in_bytes);

/*****************************************************************************/
/** Read Application instance Certificate
 *
 * Certificate generation via UAServer_Generate_certificate() is a resource
 * intensive operation that can be very slow on some platforms. If the IP
 * Address or Hostname of the server remains the same then the generated certificate
 * will be the same each time. Instead of generating the certificate on every POST,
 * the certificate can be generated (on a development system or on the target) once
 * and then provided at POST in order to shorten boot time.
 *
 * Copies the generated certificate into the byte string provided.
 *
 * @param[out] certificate
 * The generated certificate is copied into the preallocated byte string.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Read_certificate(UA_Byte_string_t* certificate);

/*****************************************************************************/
/** Write Application instance Certificate
 *
 * Certificate generation via UAServer_Generate_certificate() is a resource
 * intensive operation that can be very slow on some platforms. If the IP
 * Address or Hostname of the server remains the same then the generated certificate
 * will be the same each time. Instead of generating the certificate on every POST,
 * the certificate can be generated (on a development system or on the target) once
 * and then provided at POST in order to shorten boot time.
 *
 * Copies the certificate from the byte string provided and uses it as the
 * Application Instance Certificate.
 *
 * @param[in] certificate
 * The certificate is copied into the server from the byte string.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Write_certificate(UA_Byte_string_t* certificate);

/*@}*/

/** \addtogroup grpMemory_C_API
 *@{*/

/*****************************************************************************/
/** Allocate a block of memory from the SDK memory allocation subsystem
 *
 * If the application needs to perform dynamic memory allocation it can use the
 * SDK memory allocation subsystem rather than a general purpose heap (which in
 * any case may not be available). The allocation must be less than
 * UA_Configuration_Internals_t::MAX_ALLOCATION_SIZE_IN_BYTES specified in the
 * runtime configuration (typically by 8 bytes).
 *
 * @param[in] size
 * The size in bytes of the required block of memory.
 *
 * @return  A pointer to the allocated memory or NULL (0) on failure.
 */
void* UAServer_Malloc(size_t size);

/*****************************************************************************/
/** Allocate a block of memory from the SDK memory allocation subsystem
 * and zero the block. The allocation must be less than
 * UA_Configuration_Internals_t::MAX_ALLOCATION_SIZE_IN_BYTES specified in the
 * runtime configuration (typically by 8 bytes).
 *
 * @param[in] size
 * The size in bytes of the required block of memory.
 *
 * @return  A pointer to the allocated memory or NULL (0) on failure.
 */
void* UAServer_Calloc(size_t size);

/*****************************************************************************/
/** Increase or decrease the size of a previously allocated block of memory
 * from the SDK memory allocation subsystem. The allocation must be less than
 * UA_Configuration_Internals_t::MAX_ALLOCATION_SIZE_IN_BYTES specified in the
 * runtime configuration (typically by 8 bytes).
 *
 * @param[in] ptr
 * A pointer previously returned by one of the memory allocation routines.
 *
 * @param[in] size
 * The size in bytes of the required block of memory.
 *
 * @return  A pointer to the allocated memory or NULL (0) on failure.
 */
void* UAServer_Realloc(void* ptr, size_t size);

/*****************************************************************************/
/** Free a memory block previously allocated with UAServer_Malloc(),
 * UAServer_Calloc() or UAServer_Realloc().
 *
 * @param[in] ptr
 * The pointer previously returned by one of the memory allocation routines.
 *
 */
void UAServer_Free(void* ptr);

/*@}*/

/** \addtogroup grpDeferredReads_C_API
 *@{*/

/*****************************************************************************/
/** Is the current read callback invoked due to an asynchronous read request
 * or a monitored item sample?
 *
 * This function can only be called from UAServer_Callback_read().
 *
 * @param[in] read_context
 * The read context provided by the SDK.
 *
 * @return
 * TRUE if the read is part of an OPC UA Read Service Call.
 */
bool_t UAServer_Is_read_operation_asynchronous(uintptr_t read_context);

/*****************************************************************************/
/** Can the current read operation be deferred if we have to obtain the data value
 * from a slow remote data source?
 *
 * This function can only be called from UAServer_Callback_read().
 *
 * @param[in] read_context
 * The read context provided by the SDK.
 *
 * @return
 * TRUE if the read operation can be deferred.
 */
bool_t UAServer_Is_read_operation_deferrable(uintptr_t read_context);

/*****************************************************************************/
/** Is the current read operation a repeat of an operation that was previously
 * deferred?
 *
 * This function can only be called from UAServer_Callback_read().
 *
 * @param[in] read_context
 * The read context provided by the SDK.
 *
 * @return
 * TRUE if the read operation was previously deferred deferred.
 */
bool_t UAServer_Is_read_operation_deferred(uintptr_t read_context);

/*****************************************************************************/
/** Get Time Out Hint
*
* @param[in] read_context
* The read context provided by the SDK.
*
* @return
* time out value of the read operation.
*/
uint32_t UAServer_Get_Read_Timeout_Hint(uintptr_t read_context);

/*****************************************************************************/
/** Defer the current read operation as we have to obtain the data from a slow
 * remote data source and doing so synchronously would degrade server response
 * for all connected clients.
 *
 * This function can only be called from UAServer_Callback_read().
 *
 * @param[in] read_context
 * The read context provided by the SDK.
 *
 * @param[out] deferral_handle
 * A unique handle representing this specific deferral.
 *
 * @return
 * OpcUa_Good if the deferral was successful.
 */
UA_Status_t UAServer_Defer_read_operation(uintptr_t read_context, uintptr_t* deferral_handle);

/*****************************************************************************/
/** The read deferral is complete.
 *
 * The application notifies the SDK that the data has been obtained from the data
 * source and is now available for reading. After making this call the SDK will
 * immediately call UAServer_Callback_read() again.
 * This function must NOT be called from any server callback function.
 *
 * @param[in] deferral_handle
 * The deferral handle provided by the SDK.
 *
 * @param[out] status_code
 * The result of the asynchronous read operation.
 *
 * @return
 * OpcUa_Good if the call was successful.
 */
UA_Status_t UAServer_Read_deferral_complete(uintptr_t deferral_handle, UA_Status_t status_code);

/*****************************************************************************/
/** The deferred read operation is aborted.
 *
 * The application has previously deferred a read operation and received a deferral
 * handle for the deferred read. This call indicates that the deferral operation has
 * been cancelled by the SDK. This could be due to the client closing the session that
 * the read operation is associated with.
 * After receiving this callback the application must NOT call
 * UAServer_Read_deferral_complete() with this deferral handle as this will result in
 * the SDK dereferencing a free'd pointer.
 *
 * @param[in] deferral_handle
 * The deferral handle provided by the SDK.
 *
 */
void UAServer_Callback_deferred_read_operation_aborted(uintptr_t deferral_handle);

/*@}*/

/** \addtogroup grpTranslate_C_API
 *@{*/

/*****************************************************************************/
/** Function provided by host to enable library to translate text
 *
 * The library requires the ability to translate human readable text in order
 * to operate. This ability is provided by this function which must be
 * implemented by the host system. This function is called by the library to get
 * a pointer to the appropriate text for communication to a client using a
 * specified and supported locale. This function is used to lookup translations
 * for nodes created by the host system. A separate callback is used to lookup
 * translations for internal text that the library uses to expose standard OPC-UA
 * nodes in the address space.
 *
 * @param[in] locale_index
 * The index into the previously provided locale table. Ignore if only one locale
 * was provided.
 *
 * @param[in] text_handle
 * An identifier that the host can use to efficiently look up the text string.
 *
 * @return
 * A pointer to the text required to be communicated to the client, or 0 if
 * the text cannot be found. If the library receives a return value of 0 it
 * will retry with a variety of supported locales until it receives a valid
 * result or all locales have been tried.
 */
const UA_UTF8_string_t* UAServer_Callback_translate(uint16_t locale_index,
  uintptr_t text_handle);

/*****************************************************************************/
/** Function provided by host to enable library to translate enumerated text
 *
 * The library requires the ability to translate human readable text in order
 * to operate. This ability is provided by this function which must be
 * implemented by the host system. This function is called by the library to get
 * a pointer to the appropriate text for communication to a client using a
 * specified and supported locale. This function is used to lookup translations
 * for nodes created by the host system. A separate callback is used to lookup
 * translations for internal text that the library uses to expose standard OPC-UA
 * nodes in the address space.
 *
 * MultiStateDiscrete Data Access address space nodes contain an enumeration of
 * possible values with a human readable label for each value of the
 * enumeration. When creating the node the host passes in a handle to the
 * enumeration and the number of values. For translation the library calls this
 * function indicating the enumeration handle provided and the index of the
 * required label.
 *
 * @param[in] locale_index
 * The index into the previously provided locale table. Ignore if only one locale
 * was provided.
 *
 * @param[in] enum_handle
 * An identifier that the host can use to efficiently look up the enumeration.
 *
 * @param[in] enum_index
 * An index into the value of the enumeration indicating the label to be returned.
 *
 * @return
 * A pointer to the text required to be communicated to the client, or 0 if
 * the text cannot be found. If the library receives a return value of 0 it
 * will retry with a variety of supported locales until it receives a valid
 * result or all locales have been tried.
 */
const UA_UTF8_string_t* UAServer_Callback_translate_enumstrings(
  uint16_t locale_index,
  uintptr_t enum_handle,
  uint16_t enum_index);

/*****************************************************************************/
/** Function provided by host to enable library to translate internal text
 *
 * The library exposes some standard OPC-UA nodes in the server address space.
 * It may be desirable to translate the DisplayNames of these nodes. This
 * API callback is provided to facilitate translation of this text.
 * If you do not wish to provide translation of the internal text, simply return
 * the default English text to the library. If you do wish to provide translated
 * text for the internal text you should implement tables of UTF8 strings for
 * each supported locale.
 * Note: There is no requirement in the OPC-UA standard to provide translations
 * of the internal text even if your server supports multiple locales. In this
 * case nodes you add to the address space will be localized but the standard
 * OPC-UA nodes will not.
 *
 * @param[in] locale_index
 * The index into the previously provided locale table. Ignore if no table
 * was provided.
 *
 * @param[in] text_index
 * An identifier that the host can use to efficiently look up the text string
 * (a zero based table index).
 *
 * @return
 * A pointer to the text required to be communicated to the client, or 0 if
 * the text cannot be found. If the library receives a return value of 0 it
 * will retry with a variety of supported locales until it receives a valid
 * result or until all locales have been tried.
 */
const UA_UTF8_string_t* UAServer_Callback_translate_internal_text(
  uint16_t locale_index, uint32_t text_index);

/*@}*/

/** \addtogroup grpFileTransfer_C_API
 *@{*/

#if (UA_INCLUDE_FILE_TRANSFER_METHODS > 0)
/*****************************************************************************/
/** Function provided by host to enable file size to be reported
 *
 * The function UAServer_File_Size_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_Open_result() to complete the operation.
 *
 */
void UAServer_Callback_File_Size(
  uintptr_t node_handle,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file size operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_Size() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_Size().
 *
 * @param[in] size
 * The current size of the file in bytes.
 *
 * @param[in] result
 * 0                      Success.
 * Bad_UnexpectedError    See Part 4 for a general description.
 * Bad_NotFound           See Part 4 for a general description.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_Size_result(
    uintptr_t context,
    uint64_t size,
    UA_Status_t result);

/*****************************************************************************/
/** Function provided by host to enable files to be opened
 *
 * Open is used to open a file represented by an Object of FileType. When a
 * client opens a file it gets a file handle that is valid while the session
 * is open. Clients shall use the Close Method to release the handle when they
 * do not need access to the file anymore. Clients can open the same file
 * several times for read. A request to open for writing shall return
 * Bad_NotWritable when the file is already opened. A request to open for
 * reading shall return Bad_NotReadable when the file is already opened for writing.
 *
 * The function UAServer_File_Open_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] mode
 * Indicates whether the file should be opened only for read operations or
 * for read and write operations and where the initial position is set.
 * The mode is an 8-bit unsigned integer used as bit mask with the structure defined
 * in the following table:
 *
 * Field          Bit     Description
 *
 * Read           0       The file is opened for reading. If this bit is not
 *                        set the Read Method cannot be executed.
 *
 * Write          1       The file is opened for writing. If this bit is not
 *                        set the Write Method cannot be executed.
 *
 * EraseExisiting 2       This bit can only be set if the file is opened for
 *                        writing (Write bit is set). The existing content of the
 *                        file is erased and an empty file is provided.
 *
 * Append         3       When the Append bit is set the file is opened at end of
 *                        the file, otherwise at begin of the file. The SetPosition
 *                        Method can be used to change the position.
 *
 * Reserved       4:7     Reserved for future use. Shall always be zero..
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_Open_result() to complete the operation.
 *
 */
void UAServer_Callback_File_Open(
  uintptr_t node_handle,
    uint8_t mode,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file open operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_Open() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_Open().
 *
 * @param[in] file_handle
 * A handle for the file used in other method calls indicating not the file (this
 * is done by the Object of the Method call) but the access request and thus the
 * position in the file. The fileHandle is generated by the server and is unique
 * for the Session. Clients cannot transfer the fileHandle to another Session but
 * need to get a new fileHandle by calling the Open Method.
 *
 * @param[in] result
 * 0                      Success.
 * Bad_NotReadable        See Part 4 for a general description. File might be locked
 *                        and thus not readable.
 * Bad_NotWritable        See Part 4 for a general description.
 * Bad_InvalidState       See Part 4 for a general description. The file is locked
 *                        and thus not writable.
 * Bad_InvalidArgument    See Part 4 for a general description. Mode setting is invalid.
 * Bad_UnexpectedError    See Part 4 for a general description.
 * Bad_NotFound           See Part 4 for a general description.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_Open_result(
    uintptr_t context,
    uint32_t file_handle,
    UA_Status_t result);

/*****************************************************************************/
/** Function provided by host to enable files to be closed
 *
 * Close is used to close a file represented by a FileType. When a client
 * closes a file the handle becomes invalid.
 *
 * The function UAServer_File_Close_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] file_handle
 * A handle indicating the access request and thus indirectly the position
 * inside the file.
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_Close_result() to complete the operation.
 *
 */
void UAServer_Callback_File_Close(
  uintptr_t node_handle,
    uint32_t file_handle,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file close operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_Close() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_Close().
 *
 * @param[in] result
 * 0                      Success.
 * Bad_InvalidArgument    See Part 4 for a general description. Invalid file handle in call.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_Close_result(
    uintptr_t context,
    UA_Status_t result);

/*****************************************************************************/
/** Function provided by host to enable files to be read
 *
 * Read is used to read a part of the file starting from the current file
 * position. The file position is advanced by the number of bytes read.
 *
 * The function UAServer_File_Read_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] file_handle
 * A handle indicating the access request and thus indirectly the position
 * inside the file.
 *
 * @param[in] length
 * Defines the length in byte that should be returned in data, starting from
 * the current position of the file handle. If the end of file is reached only
 * all data till the end of the file are returned. If the specified length is
 * longer than the maximum allowed message size of the communication, only
 * those data fitting into the message size are returned. Only positive values
 * are allowed.
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_Read_result() to complete the operation.
 *
 */
void UAServer_Callback_File_Read(
  uintptr_t node_handle,
    uint32_t file_handle,
    int32_t length,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file read operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_Read() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_Read().
 *
 * @param[in] data
 * The data to be read.
 *
 * @param[in] result
 * 0                      Success.
 * Bad_InvalidState       See Part 4 for a general description. File was not opened
 *                        for read access.
 * Bad_InvalidArgument    See Part 4 for a general description. Invalid file handle in call
 *                        or non positive length.
 * Bad_UnexpectedError    See Part 4 for a general description.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_Read_result(
    uintptr_t context,
    UA_Byte_string_t data,
    UA_Status_t result);

/*****************************************************************************/
/** Function provided by host to enable files to be written
 *
 * Write is used to write a part of the file starting from the current file
 * position. The file position is advanced by the number of bytes written.
 *
 * The function UAServer_File_Write_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] file_handle
 * A handle indicating the access request and thus indirectly the position
 * inside the file.
 *
 * @param[in] data
 * Contains the data to be written at the position of the file. It is
 * server-dependent whether the written data are persistently stored if the
 * session is ended without calling the Close Method with the fileHandle.
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_Write_result() to complete the operation.
 *
 */
void UAServer_Callback_File_Write(
  uintptr_t node_handle,
    uint32_t file_handle,
    UA_Byte_string_t data,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file write operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_Write() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_Write().

 * @param[in] result
 * 0                      Success.
 * Bad_InvalidArgument    See Part 4 for a general description. Invalid file handle in call.
 * Bad_NotWritable        See Part 4 for a general description. File might be locked and
 *                        thus not writable.
 * Bad_InvalidState       See Part 4 for a general description. File was not opened for
 *                        write access.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_Write_result(
    uintptr_t context,
    UA_Status_t result);

/*****************************************************************************/
/** Function provided by host to enable file positions to be read
 *
 * GetPosition is used to provide the current position of the file handle.
  *
 * The function UAServer_File_GetPosition_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] file_handle
 * A handle indicating the access request and thus indirectly the position
 * inside the file.
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_GetPosition_result() to complete the operation.
 *
 */
void UAServer_Callback_File_GetPosition(
  uintptr_t node_handle,
    uint32_t file_handle,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file open operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_GetPosition() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_GetPosition().

 * @param[in] position
 * The position of the fileHandle in the file. If a Read or Write is called it
 * starts at that position.
 *
 * @param[in] result
 * 0                      Success.
 * Bad_InvalidArgument    See Part 4 for a general description. Invalid file handle in call.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_GetPosition_result(
    uintptr_t context,
    uint64_t position,
    UA_Status_t result);

/*****************************************************************************/
/** Function provided by host to enable file positions to be written
 *
 * SetPosition is used to set the current position of the file handle.
 *
 * The function UAServer_File_SetPosition_result() must be called within this function
 * body to complete the operation.
 *
 * @param[in] node_handle
 * The handle of the FileType node identifying the file in the address space.
 *
 * @param[in] file_handle
 * A handle indicating the access request and thus indirectly the position
 * inside the file.
 *
 * @param[in] position
 * The position to be set for the fileHandle in the file. If a Read or Write is
 * called it starts at that position. If the position is higher than the file
 * size the position is set to the end of the file.
 *
 * @param[in] context
 * A handle to the operation context which is passed to the library via
 * UAServer_File_SetPosition_result() to complete the operation.
 *
 */
void UAServer_Callback_File_SetPosition(
  uintptr_t node_handle,
    uint32_t file_handle,
    uint64_t position,
    uintptr_t context);

/*****************************************************************************/
/** Function to complete file set position operation
 *
 * This function must be called within the body of function
 * UAServer_Callback_File_SetPosition() to complete the operation.
 *
 * @param[in] context
 * A handle to the operation context received from UAServer_Callback_File_SetPosition().
 *
 * @param[in] result
 * 0                      Success.
 * Bad_InvalidArgument    See Part 4 for a general description. Invalid file handle in call.
 *
 * @return OPC-UA Status Code
 * 0                      Success.
 * >0                     Failure.
 */
UA_Status_t UAServer_File_SetPosition_result(
    uintptr_t context,
    UA_Status_t result);
#endif

/*@}*/

/** \addtogroup grpTcpIp_C_API
 *@{*/

/*****************************************************************************/
/** Informs the library that a new TCPIP connection has been made
 *
 * Whenever a new TCPIP connection is made on the UA Server listening TCP PORT
 * the host must call this function.
 *
 * @param[in]	connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_New_connection(uint64_t connection_id);

/*****************************************************************************/
/** Informs the library that a TCPIP connection has been terminated
 *
 * Whenever a TCPIP connection is closed or aborted on the UA Server listening
 * TCP PORT the host must call this function.
 *
 * @param[in]	connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Connection_closed(uint64_t connection_id);

/*****************************************************************************/
/** Instructs the host application to close the socket
 *
 * Whenever a TCP Binary connection is closed the library informs the host
 * application to close the corresponding socket.
 *
 * @param[in] connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 */
void UAServer_Callback_close_connection(uint64_t connection_id);

/*****************************************************************************/
/** Informs the library that new data has been received
 *
 * Whenever new data is received on a TCPIP connection the host must
 * call this function. The library responds by calling
 * UAServer_Callback_data_receive()
 *
 * @param[in] read_context
 * A pointer to an application specific data structure providing context to the
 * pending read operation. The library will pass this pointer to
 * UAServer_Receive_data_callback().
 *
 * @param[in]	connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_New_data_received(void* read_context, uint64_t connection_id);

/*****************************************************************************/
/** Read new data from TCP/IP stack
 *
 * Whenever new data is received on an active TCPIP connection the library
 * calls this function in response to UAServer_New_data_received()
 *
 * @param[in] application_context
 * A pointer to an application specific data structure providing context to the
 * pending read operation. The host must pass this pointer to
 * UAServer_New_data_received().
 *
 * @param[in]	connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @param[in]	buffer
 * A pointer to the data buffer
 *
 * @param[in]	max_length_in_bytes
 * The maximum length of data to write into the buffer in bytes
 *
 * @param[out]	no_of_bytes_received
 * The number of bytes read into the buffer
 *
 * @return  More data is available to be read.
 */
bool_t UAServer_Callback_data_receive(void* application_context,
                                      uint64_t connection_id,
                                      uint8_t* buffer,
                                      uint32_t max_length_in_bytes,
                                      uint32_t* no_of_bytes_received);

/*****************************************************************************/
/** Get queued data to send from the library
 *
 * When the library has data queued for transmission this function is called in
 * order to send the queued data. The library responds by calling
 * UAServer_Callback_data_send()
 *
 * @param[in] write_context
 * A pointer to an application specific data structure providing context to the
 * pending read operation. The library will pass this pointer to
 * UAServer_Send_data_callback().
 *
 * @param[in]	connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Get_data_to_send(void* write_context, uint64_t connection_id);

/*****************************************************************************/
/** Send new data to TCP/IP stack
 *
 * The library calls this function in response to UAServer_Get_data_to_send()
 *
 * @param[in] application_context
 * A pointer to an application specific data structure providing context to the
 * pending read operation. The host must pass this pointer to
 * UAServer_Get_data_to_send().
 *
 * @param[in]	connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @param[in]	buffer
 * Pointer to the buffer containing the data to send
 *
 * @param[in]	no_of_bytes_to_send
 * The length of data available to send in bytes
 *
 * @param[out] no_of_bytes_sent
 * The number of data bytes sent. If this number equals the
 * no_of_bytes_to_send the library may call the function again to send
 * more data if available.
 *
 * @return  The TCP/IP stack can accept more data.
 *
 */
bool_t UAServer_Callback_data_send(void* application_context,
                                   uint64_t connection_id,
                                   uint8_t* buffer,
                                   uint32_t no_of_bytes_to_send,
                                   uint32_t* no_of_bytes_sent);

/*****************************************************************************/
/** Can the connection receive any more data at present
 *
 * @param[in] connection_id
 * A unique identifier for this TCPIP connection. Where a socket API is in use
 * the socket file descriptor may be used. Where a raw API is in use a value
 * representing the remote endpoint may be used.
 *
 * @param[out]  result
 * True if the server can receive more data.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Ready_to_receive(uint64_t connection_id, bool_t* result);

/*@}*/

/** \addtogroup grpAddressSpace_C_API
 *@{*/

/*****************************************************************************/
/** Delete all host generated nodes in the address space
 *
 * Allows the host system to remove all nodes from the address space that it
 * has previously added.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Delete_all_nodes(void);

/*****************************************************************************/
/** Delete a specific host generated node from the address space
 *
 * Allows the host system to remove a specific node from the address space that
 * it has previously added.
 *
 * @param[in]	node_handle
 * The handle of the node to be deleted
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Delete_node(uintptr_t node_handle);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_Folder(UA_Folder_t* configuration);

/*****************************************************************************/
/** Create a folder node that will contain (or reference) other nodes
 *
 * Allows the host system to create a folder node in the address space
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_Folder(const UA_Folder_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_View(UA_View_t* configuration);

/*****************************************************************************/
/** Create a view node that will contain (or reference) other nodes
 *
 * Allows the host system to create a view node in the address space. The library
 * supports 15 different views. Each view created will be given a view index
 * of 1 - 15 in the order in which they are created. The view index is used
 * in conjunction with view masks that can be specified for references. See
 * the SDK user manual (Other Features and Further Information section) for
 * more information about views. A created view is automatically added to the
 * Views folder of the address space.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_View(const UA_View_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_Method(UA_Method_t* configuration);

/*****************************************************************************/
/** Create a method node
 *
 * Allows the host system to create a method node in the address space. While
 * method nodes can be created they are not functionally supported by the library
 * at present.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_Method(const UA_Method_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_BaseDataVariable(UA_BaseDataVariable_t* configuration);

/*****************************************************************************/
/** Create a BaseDataVariable node
 *
 * Allows the host system to create a BaseDataVariable node in the address space
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_BaseDataVariable(const UA_BaseDataVariable_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_DataItem(UA_DataItem_t* configuration);

/*****************************************************************************/
/** Create a DataItem node
 *
 * Allows the host system to create a DataItem node in the address space
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_DataItem(const UA_DataItem_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_AnalogItem(UA_AnalogItem_t* configuration);

/*****************************************************************************/
/** Create an AnalogItem node
 *
 * Allows the host system to create an AnalogItem node in the address space
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_AnalogItem(const UA_AnalogItem_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_TwoStateDiscrete(UA_TwoStateDiscrete_t* configuration);

/*****************************************************************************/
/** Create a TwoStateDiscrete node
 *
 * Allows the host system to create a TwoStateDiscrete node in the address space
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_TwoStateDiscrete(const UA_TwoStateDiscrete_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the 
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_MultiStateDiscrete(UA_MultiStateDiscrete_t* configuration);

/*****************************************************************************/
/** Create a MultiStateDiscrete node
 *
 * Allows the host system to create a MultiStateDiscrete node in the address space
 *
 * @param[in]	configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_MultiStateDiscrete(const UA_MultiStateDiscrete_t* configuration);

/*****************************************************************************/
/** Initialise a configuration structure for a new node with default values
 *
 * In order to add create a node in the address space, the host system must
 * configure a configuration structure for the node and then call the
 * appropriate 'Create' function. This function initializes a node
 * configuration structure to default values prior to configuring the structure
 * and calling the 'Create' function.
 *
 * @param[in] configuration
 * A pointer to the configuration data structure for the node
 */
void UAServer_Init_config_structure_File(UA_File_t* configuration);

#if (UA_INCLUDE_FILE_TRANSFER_METHODS > 0)
/*****************************************************************************/
/** Create a File node
 *
 * Allows the host system to create a File node in the address space
 *
 * @param[in] configuration
 * A pointer to the configuration data structure for the node
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Create_File(const UA_File_t* configuration);
#endif

/*****************************************************************************/
/** Add a node to a folder node
 *
 * Allows the host system to add a previously created node to a folder.
 * Specifically this creates a reference from the folder node to the target node.
 *
 * @param[in]	folder_handle
 * The handle of the folder node (source node of the reference)
 *
 * @param[in]	node_handle
 * The handle of the node to add to the folder (target node of the reference)
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Add_to_folder(uintptr_t folder_handle, uintptr_t node_handle);

/*****************************************************************************/
/** Add a node to a folder node while specifying a view mask
 *
 * Allows the host system to add a previously created node to a folder.
 * Specifically this creates a reference from the folder node to the target node.
 * This function allows the host to specify a view mask. This filters the
 * visibility of the reference depending on the view being browsed by the client.
 *
 * @param[in]	folder_handle
 * The handle of the folder node (source node of the reference)
 *
 * @param[in]	node_handle
 * The handle of the node to add to the folder (target node of the reference)
 *
 * @param[in]	view_mask
 * A bit mask with a bit set for each view where the reference is visible. Bit zero
 * is no view and bits 1 - 15 are the 15 supported views.
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Add_to_folder_with_view_mask(uintptr_t folder_handle,
  uintptr_t node_handle,
                                                  uint16_t view_mask);

/*****************************************************************************/
/** Add a node to the objects folder
 *
 * Allows the host system to add a previously created node to the objects folder.
 * Specifically this creates a reference from the objects folder node to the
 * target node. The objects folder is a standard object that is always present
 * in the address space.
 *
 * @param[in]	node_handle
 * The handle of the node to add to the objects folder (target node of the reference)
 *
 * @return  The result of the operation.
 */
UA_Status_t UAServer_Add_to_objects_folder(uintptr_t node_handle);

/*@}*/

/** \addtogroup grpSecurity_C_API
 *@{*/

#if (UA_INCLUDE_SECURITY > 0)

/*****************************************************************************/
/** Check if the application certificate and corresponding private key are
 * present.
 *
 * If there is no application certificate present the application may choose
 * to create a default self signed certificate if certificate creation
 * functionality is supported by the PKI component.
 *
 * @return OpcUa_Good if the certificate exists.
 */
UA_Status_t UASecurity_Check_application_certificate_exists(void);

/*****************************************************************************/
/** Create a self signed certificate.
 *
 * @param[in] sdk_configuration
 * The configuration structure used to initialize the SDK.
 *
 * @param[in] server_uri
 * The server URI.
 *
 * @param[in] hostnames
 * The array of hostnames assigned to the host that the server is running on
 * that the server is accessible from.
 *
 * @param[in] no_of_hostnames
 * The number of hostnames.
 *
 * @param[in] ip_addresses
 * The array of ip addresses assigned to the host that the server is running on
 * that the server is accessible from. If hostnames are available IP addresses
 * should not be used.
 *
 * @param[in] no_of_ip_addresses
 * The number of IP addresses.
 *
 * @return  OpcUa_Good if the operation succeeds.
 */
UA_Status_t UASecurity_Create_self_signed_certificate(
    const UA_Configuration_t* sdk_configuration,
    const char* server_uri,
    const char** hostnames, int no_of_hostnames,
    const char** ip_addresses, int no_of_ip_addresses);

/*****************************************************************************/
/** Reload the directory certificate stores.
 *
 * If the PKI component stores certificates in the filesystem it may load the
 * certificates only once on startup. If a certificate is added the application
 * may wish the PKI compnent to reload the stores from the filesystem following
 * the addition.
 *
 * @return OpcUa_Good if the operation succeeds.
 */
UA_Status_t UASecurity_Reload_directory_stores_now(void);

/*****************************************************************************/
/** Reload the directory certificate stores before every certificate
 * validation.
 *
 * If the PKI component stores certificates in the filesystem it may load the
 * certificates only once on startup. If it is possible for certificates to be
 * added or removed from the filesystem at any time and independently of the
 * application the application should instruct the PKI component to reload
 * certificates from the filesystem prior to every validation.
 *
 * @param[in] enable
 * enable or disable reloading.
 *
 */
void UASecurity_Reload_directory_stores_before_each_validation(bool_t enable);

/*****************************************************************************/
/** Create the directory certificate stores.
 *
 * Create the filesystem structure required for the certificate stores. There
 * are four certificate stores. There are trusted and issuer stores for both
 * application and user certificates.
 *
 * @return OpcUa_Good if the operation succeeds.
 */
UA_Status_t UASecurity_Create_directory_stores(void);

/*****************************************************************************/
/** Alter the behaviour of the certificate validation logic.
 *
 * @param[in] option_bits
 * Bitmap defining the behaviour required.
 *
 * The option bits are:
 *
 * Option Bit - Accept expired certificates
 * OB_SUPPRESS_CERTIFICATE_EXPIRED       (1<<0)
 *
 * Option Bit - Do not validate the application hostname
 * OB_SUPPRESS_HOSTNAME_INVALID          (1<<1)
 *
 * Option Bit - If checking certificate CRLs do not reject
 * a certificate if a CRL for the Issuer cannot be found
 * OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN (1<<2)
 *
 * Option Bit - Look for CRLs online (not currently supported)
 * OB_CHECK_REVOCATION_STATUS_ONLINE     (1<<3)
 *
 * Option Bit - Look for CRLs locally (typically in the local filesystem
 * OB_CHECK_REVOCATION_STATUS_OFFLINE    (1<<4)
 *
 */
void UASecurity_Set_validation_options(uint32_t option_bits);

/*****************************************************************************/
/** Alter the behaviour of the certificate validation logic.
 *
 * @param[in] option_bits
 * Bitmap defining the behaviour required.
 *
 * @param[in] trustAllClientsWhenTrustListIsEmpty
 * flag to trust all clients when trust list is empty
 *
 * @param[in] doNotSaveRejectedCertificates
 * flag to store the rejected certificate or not. 
 *
 * The option bits are:
 *
 * Option Bit - Accept expired certificates
 * OB_SUPPRESS_CERTIFICATE_EXPIRED       (1<<0)
 *
 * Option Bit - Do not validate the application hostname
 * OB_SUPPRESS_HOSTNAME_INVALID          (1<<1)
 *
 * Option Bit - If checking certificate CRLs do not reject
 * a certificate if a CRL for the Issuer cannot be found
 * OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN (1<<2)
 *
 * Option Bit - Look for CRLs online (not currently supported)
 * OB_CHECK_REVOCATION_STATUS_ONLINE     (1<<3)
 *
 * Option Bit - Look for CRLs locally (typically in the local filesystem
 * OB_CHECK_REVOCATION_STATUS_OFFLINE    (1<<4)
 *
 */
void UASecurity_Set_validation_options2(
  uint32_t option_bits,
  bool_t trustAllClientsWhenTrustListIsEmpty,
  bool_t doNotSaveRejectedCertificates);

/*****************************************************************************/
/** Get the certificate thumbprint.
 *
 * When storing certificates in a filesystem programmatically the SHA1
 * thumbprint should be used as the filename for the certificate with the .DER
 * file extension. This ensures that all certificates shall have a unique filename.
 * The OpenSSL PKI component does not make use of this file naming convention but
 * other PKI components may depend on it for correct operation.
 *
 * @return OpcUa_Good if the operation succeeds.
 */
UA_Status_t UASecurity_Get_thumbprint(const char* filepath, char* thumbprint, uint32_t thumbprint_max_length);

/*****************************************************************************/
/** Provide the password for the application certificate private key file.
 *
 * @param[out] password
 * The password for the private key PEM file.
 *
 */
void UASecurity_Callback_get_private_key_password(UA_Var_string_t* password);

/*****************************************************************************/
/** A certificate was added to the rejected certificate list.
 *
 * @param[in] type
 * The type of the certificate.
 *
 */
void UASecurity_Callback_certificate_added_to_rejected_list(UA_CertificateType_t type);

#endif /*(UA_INCLUDE_SECURITY > 0)*/

/*@}*/

/*@}*/
#ifdef __cplusplus
}
#endif

#endif //UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
#endif /*_UA_SERVER_*/
