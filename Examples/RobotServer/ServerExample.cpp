// ServerExample.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>

#include <iuser_permissions_provider_t.h>
#include <iuser_permissions_t.h>

#include "opcua_iruntime_type_t.h"

#include "opcua_boolean_t.h"
#include "opcua_byte_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_float_t.h"
#include "opcua_uint64_t.h"
#include "opcua_double_t.h"
#include "opcua_string_t.h"
#include "status_t.h"

#include "intrusive_ptr_t.h"
#include "allocatable_t.h"
#include "safe_ref_count_t.h"
#include "itransaction_listener_t.h"
#include "iserver_state_listener_t.h"
#include "iaddress_space_t.h"
#include "opcua_build_info_t.h"
#include "iserver_configuration_t.h"
#include "opcua_user_identity_token_type_t.h"
#include "std_file_t.h"
#include "access_level_t.h"
#include "write_mask_t.h"
#include "ilog_listener_t.h"
#include "certificate_generation_parameters_t.h"
#include "icertificate_private_key_password_provider_t.h"
#include "certificate_validation_options_t.h"
#include "opcua_node_id_numeric_t.h"
#include "uasdk_default_build_config.h"
#include "opcua_qualified_name_t.h"
#include "opcua_bytestring_t.h"
#include "utilities.h"
#include "opcua_guid_t.h"
#include "uaserver_t.h"
#include "inode_value_attribute_reader_writer_t.h"
#include "localizable_text_stored_t.h"
#include "logger_t.h"
#include "folder_t.h"
#include "base_data_variable_t.h"
#include "inode_attribute_changed_listener_t.h"
#include "inode_attribute_about_to_be_read_listener_t.h"
#include "opcua_localized_text_t.h"
#include "localizable_text_stored_t.h"
#include "method_t.h"
#include "opcua_call_method_request_t.h"
#include "opcua_call_method_result_t.h"
#include "event_notifier_t.h"

using namespace uasdk;

class UserPermissions_t : public IUserPermissions_t, public Allocatable_t
{
public:
	virtual ~UserPermissions_t() {};

	virtual bool operator==(IUserPermissions_t const & obj) const
	{
		UASDK_UNUSED(obj);
		return true;
	}

	virtual bool operator!=(IUserPermissions_t const & obj) const
	{
		UASDK_UNUSED(obj);
		return false;
	}

	virtual Status_t GetVariableNodeUserAccessLevel(const IVariableNode_t& node,
		AccessLevel_t& userAccessLevel) const
	{
		userAccessLevel = node.AccessLevel();
		return OpcUa_Good;
	}

	virtual Status_t SetVariableNodeUserAccessLevel(IVariableNode_t& node,
		AccessLevel_t userAccessLevel)
	{
		UASDK_UNUSED(node);
		UASDK_UNUSED(userAccessLevel);
		UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
	}

	virtual Status_t GetNodeUserWriteMask(const INode_t& node,
		WriteMask_t& userWriteMask) const
	{
		userWriteMask = node.WriteMask();
		return OpcUa_Good;
	}

	virtual Status_t SetNodeUserWriteMask(const INode_t& node,
		WriteMask_t userWriteMask)
	{
		UASDK_UNUSED(node);
		UASDK_UNUSED(userWriteMask);
		UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
	}

	virtual Status_t GetNodeUserVisibility(const INode_t& node,
		bool& visible) const
	{
		UASDK_UNUSED(node);
		visible = true;
		return OpcUa_Good;
	}

	virtual Status_t SetNodeUserVisibility(INode_t& node,
		bool visible)
	{
		UASDK_UNUSED(node);
		UASDK_UNUSED(visible);
		UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
	}

	virtual Status_t GetMethodNodeUserExecutable(const IMethodNode_t& method,
		bool& userExecutable) const
	{
		userExecutable = method.Executable();
		return OpcUa_Good;
	}

	virtual Status_t SetMethodNodeUserExecutable(IMethodNode_t& method,
		bool userExecutable)
	{
		UASDK_UNUSED(method);
		UASDK_UNUSED(userExecutable);
		UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
	}

};

class UserPermissionsProvider_t : public IUserPermissionsProvider_t, public Allocatable_t
{
public:
	virtual ~UserPermissionsProvider_t() {};

	virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
		const String_t& userName,
		const String_t& password,
		IntrusivePtr_t<IUserPermissions_t>& userPermissions) const
	{
		UASDK_UNUSED(sessionId);
		UASDK_UNUSED(userName);
		UASDK_UNUSED(password);
		UASDK_UNUSED(userPermissions);
		UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
	}

	virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
		const X509IdentityToken_t& userIdentityToken,
		IntrusivePtr_t<IUserPermissions_t>& userPermissions) const
	{
		UASDK_UNUSED(sessionId);
		UASDK_UNUSED(userIdentityToken);
		UASDK_UNUSED(userPermissions);
		UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
	}

	virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
		const AnonymousIdentityToken_t& userIdentityToken,
		IntrusivePtr_t<IUserPermissions_t>& userPermissions) const
	{
		UASDK_UNUSED(sessionId);
		UASDK_UNUSED(userIdentityToken);
		userPermissions = new SafeRefCount_t<UserPermissions_t>();
		if (!userPermissions.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}
		return OpcUa_Good;
	}
};

//class CertificatePrivateKeyPasswordProvider_t : public ICertificatePrivateKeyPasswordProvider_t, public Allocatable_t
//{
//public:
//  virtual ~CertificatePrivateKeyPasswordProvider_t() {};
//
//  virtual Status_t GetPassword(UA_CertificateType_t type, UA_CertificateGroup_t group, String_t& password) const
//  {
//    UASDK_UNUSED(type);
//    UASDK_UNUSED(group);
//    return password.CopyFrom("password");
//  }
//};

class LogListener_t : public ILogListener_t, public Allocatable_t
{
private:
	mutable Lock_t lock;
	LogLevel_t minimumLevel;

	void PrintTime(void) const
	{
#define EPOCH_DIFF 11644473600LL
#define SCALE_TO_S 10000000LL

		int64_t date_time = UASDK_datetime();

		int64_t file_time_s = date_time / SCALE_TO_S;
		int64_t linux_time_s = file_time_s - EPOCH_DIFF;
		int milliseconds = (date_time % SCALE_TO_S) / 10000LL;

		struct timeval time_of_day;
		time_of_day.tv_sec = static_cast<long>(linux_time_s);

#ifdef _WIN32
		time_t t = time_of_day.tv_sec;
		struct tm* time = new tm();
		errno_t returnValue = localtime_s(time, &t);
		if (0 != returnValue)
		{
			printf("Error while getting localtime");
		}
#elif defined __linux
		struct tm* time = localtime(&time_of_day.tv_sec);
#endif

		char time_string[20];
		strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time);

		printf("%s.%03d - ", time_string, milliseconds);
	}

	void PrintLevel(LogLevel_t logLevel) const
	{
		switch (logLevel)
		{
		case LOG_LEVEL_INFORMATION:
			printf("INFORMATION - ");
			break;

		case LOG_LEVEL_WARNING:
			printf("WARNING - ");
			break;

		case LOG_LEVEL_ERROR:
			printf("ERROR - ");
			break;

		case LOG_LEVEL_CRITICAL:
			printf("CRITICAL - ");
			break;

		default:
			break;
		}
	}

public:
	Status_t Initialise(void)
	{
		this->minimumLevel = LOG_LEVEL_WARNING;
		return lock.Initialise();
	}

	Status_t Initialise(LogLevel_t minimumLevel)
	{
		this->minimumLevel = minimumLevel;
		return lock.Initialise();
	}

	void LogMessage(LogLevel_t logLevel, const char* format, va_list& args) const
	{
		if (logLevel < minimumLevel) return;
		AutoLock_t lk(lock);

		PrintTime();
		PrintLevel(logLevel);

		vprintf(format, args);
		printf("\n");
	}

	void LogMessage(LogLevel_t logLevel, const char* functionName, int lineNumber, const char* format, va_list& args) const
	{
		if (logLevel < minimumLevel) return;
		AutoLock_t lk(lock);

		PrintTime();
		PrintLevel(logLevel);

		printf("In function %s, at line %d - ", functionName, lineNumber);

		vprintf(format, args);
		printf("\n");
	}
};

class ServerStateListener_t : public IServerStateListener_t
{
public:
	virtual void StateHasChanged(ServerState_t::Enum_t state) const
	{
		if (state == ServerState_t::OPCUA_SERVER_STATE_FAILED)
		{
			//Shutdown/restart the server or generate an exception (this will only occur in an out of memory condition)
		}
	}

	virtual void UnhandledError(Status_t errorCode) const
	{
		if (errorCode != OpcUa_Good)
		{
			std::cout << std::endl << "***** Bad Status Code " << std::hex << errorCode.Value() << " not handled by Server *****" << std::endl;
		}
	}
};

Status_t GetNodeWithReferenceType(const INode_t& node, IAddressSpace_t& addressSpace, const String_t& browseName, uint32_t referenceType, IntrusivePtr_t<INode_t>& result)
{
	Status_t status;
	IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
	if (!references.is_set())
	{
		return status;
	}
	IntrusivePtr_t<IReference_t> reference;
	do
	{
		reference = references->Next();
		if (reference.is_set())
		{
			NodeIdNumeric_t refType(0, referenceType);
			if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && !reference->IsInverse())
			{
				//Check browse name
				IntrusivePtr_t<INode_t> target = reference->TargetNode(addressSpace);
				if (target.is_set() && (target->BrowseName()->Name() == browseName))
				{
					result = target;
					if (result.is_set())
					{
						return OpcUa_Good;
					}
					else
					{
						UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
					}
				}
			}
		}
	} while (reference.is_set());

	return OpcUa_BadNotFound;
}

Status_t GetMethodWithReferenceType(const INode_t& node,
	IAddressSpace_t& addressSpace,
	const String_t& browseName,
	uint32_t referenceType,
	IntrusivePtr_t<IMethodNode_t>& result)
{
	IntrusivePtr_t<INode_t> tempNode;
	Status_t status = GetNodeWithReferenceType(node, addressSpace, browseName, OpcUaId_HasComponent, tempNode);
	if (status.IsBad() || !tempNode.is_set())
	{
		UASDK_RETURN_BAD_STATUS(status.Value());
	}
	result = AddressSpaceUtilities_t::NodeDownCast<IMethodNode_t>(*tempNode);
	if (!result.is_set())
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
	}
	return OpcUa_Good;
}

Status_t GetObjectWithReferenceType(const INode_t& node,
	IAddressSpace_t& addressSpace,
	const String_t& browseName,
	uint32_t referenceType,
	IntrusivePtr_t<IObjectNode_t>& result)
{
	IntrusivePtr_t<INode_t> tempNode;
	Status_t status = GetNodeWithReferenceType(node, addressSpace, browseName, referenceType, tempNode);
	if (status.IsBad() || !tempNode.is_set())
	{
		UASDK_RETURN_BAD_STATUS(status.Value());
	}
	result = AddressSpaceUtilities_t::NodeDownCast<IObjectNode_t>(*tempNode);
	if (!result.is_set())
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
	}
	return OpcUa_Good;
}

class UnderlyingSystem_t : public IRefCount_t, public Allocatable_t
{
private:
	short mode;
	short speed;
	bool laser;
	float axis1;
	float axis2;
	float axis3;
	float axis4;
	double period;
	double offset;

public:
	UnderlyingSystem_t() : mode(2), speed(0), laser(false), axis1(0.0), axis2(0.0), axis3(0.0), axis4(0.0), period(30.0), offset(0)
	{
		//offset = UASDK_datetime();
	}

	~UnderlyingSystem_t()
	{
	}

	Status_t GetSpeed(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		Int16_t finalResult(speed);
		dataValue->Value() = new SafeRefCount_t<Int16_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue->Value());
		dataValue->Value()->CopyFrom(finalResult);
		dataValue->SourceTimestamp() = new SafeRefCount_t<DateTime_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue->SourceTimestamp());
		*dataValue->SourceTimestamp() = UASDK_datetime();
		return OpcUa_Good;
	}

	Status_t SetSpeed(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Int16_t* newValue = RuntimeCast<const Int16_t*>(*dataValue->Value());
			if (newValue)
			{
				speed = newValue->Value();
				if (speed == 0) period = 30.0;
				if (speed == 1) period = 20.0;
				if (speed == 2) period = 10.0;
				if (speed == 3) period = 5.0;
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

	Status_t GetMode(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		Int16_t finalResult(mode);
		dataValue->Value() = new SafeRefCount_t<Int16_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue->Value());
		dataValue->Value()->CopyFrom(finalResult);
		dataValue->SourceTimestamp() = new SafeRefCount_t<DateTime_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue->SourceTimestamp());
		*dataValue->SourceTimestamp() = UASDK_datetime();
		return OpcUa_Good;
	}

	Status_t SetMode(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Int16_t* newValue = RuntimeCast<const Int16_t*>(*dataValue->Value());
			if (newValue)
			{
				mode = newValue->Value();
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

	Status_t GetLaser(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		Boolean_t finalResult(laser);
		dataValue->Value() = new SafeRefCount_t<Boolean_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue->Value());
		dataValue->Value()->CopyFrom(finalResult);
		dataValue->SourceTimestamp() = new SafeRefCount_t<DateTime_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue->SourceTimestamp());
		*dataValue->SourceTimestamp() = UASDK_datetime();
		return OpcUa_Good;
	}

	Status_t SetLaser(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Boolean_t* newValue = RuntimeCast<const Boolean_t*>(*dataValue->Value());
			if (newValue)
			{
				laser = newValue->Value();
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

	Status_t GetAxis1(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		if (mode == 2)
		{
			double seconds = (double)(UASDK_datetime() - offset) / 10000000;
			axis1 = 45.0 * sin(2 * 3.1415926 * seconds / period);
		}
		IntrusivePtr_t<Float_t> val(new SafeRefCount_t<Float_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(val);
		val->Value(axis1);
		dataValue->Value() = val;
		IntrusivePtr_t<DateTime_t> ts(new SafeRefCount_t<DateTime_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(ts);
		ts->Value(UASDK_datetime());
		dataValue->SourceTimestamp() = ts;
		return OpcUa_Good;
	}

	Status_t SetAxis1(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Float_t* newValue = RuntimeCast<const Float_t*>(*dataValue->Value());
			if (newValue)
			{
				axis1 = newValue->Value();
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

	Status_t GetAxis2(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		if (mode == 2)
		{
			double seconds = (double)(UASDK_datetime() - offset) / 10000000;
			axis2 = 45.0 * cos(2 * 3.1415926 * seconds / period);
		}
		IntrusivePtr_t<Float_t> val(new SafeRefCount_t<Float_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(val);
		val->Value(axis2);
		dataValue->Value() = val;
		IntrusivePtr_t<DateTime_t> ts(new SafeRefCount_t<DateTime_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(ts);
		ts->Value(UASDK_datetime());
		dataValue->SourceTimestamp() = ts;
		return OpcUa_Good;
	}

	Status_t SetAxis2(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Float_t* newValue = RuntimeCast<const Float_t*>(*dataValue->Value());
			if (newValue)
			{
				axis2 = newValue->Value();
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

	Status_t GetAxis3(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		if (mode == 2)
		{
			double seconds = (double)(UASDK_datetime() - offset) / 10000000;
			axis3 = 45.0 * sin(4 * 3.1415926 * seconds / period);
		}
		IntrusivePtr_t<Float_t> val(new SafeRefCount_t<Float_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(val);
		val->Value(axis3);
		dataValue->Value() = val;
		IntrusivePtr_t<DateTime_t> ts(new SafeRefCount_t<DateTime_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(ts);
		ts->Value(UASDK_datetime());
		dataValue->SourceTimestamp() = ts;
		return OpcUa_Good;
	}

	Status_t SetAxis3(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Float_t* newValue = RuntimeCast<const Float_t*>(*dataValue->Value());
			if (newValue)
			{
				axis3 = newValue->Value();
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

	Status_t GetAxis4(IntrusivePtr_t<DataValue_t>& dataValue)
	{
		if (mode == 2)
		{
			double seconds = (double)(UASDK_datetime() - offset) / 10000000;
			axis4 = -180.0 * cos(2 * 3.1415926 * seconds / period);
		}
		IntrusivePtr_t<Float_t> val(new SafeRefCount_t<Float_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(val);
		val->Value(axis4);
		dataValue->Value() = val;
		IntrusivePtr_t<DateTime_t> ts(new SafeRefCount_t<DateTime_t>());
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(ts);
		ts->Value(UASDK_datetime());
		dataValue->SourceTimestamp() = ts;
		return OpcUa_Good;
	}

	Status_t SetAxis4(IntrusivePtr_t<const DataValue_t>& dataValue)
	{
		if (dataValue->Value().is_set())
		{
			const Float_t* newValue = RuntimeCast<const Float_t*>(*dataValue->Value());
			if (newValue)
			{
				axis4 = newValue->Value();
				return OpcUa_Good;
			}
		}
		return OpcUa_BadOutOfRange;
	}

};

class SyncReaderWriter_t : public INodeValueAttributeReaderWriter_t, public INodeMethodHandler_t
{
private:
	Lock_t                          lock;
	IntrusivePtr_t<UnderlyingSystem_t>  underlyingSystem;
	IntrusivePtr_t<UAServer_t> uaserver;
	IntrusivePtr_t<IServerConfiguration_t> configuration;
	IntrusivePtr_t<IAddressSpace_t> addressSpace;
	
	IntrusivePtr_t<const NodeId_t> robot1NodeId;
	IntrusivePtr_t<const NodeId_t> speedNodeId;
	IntrusivePtr_t<const NodeId_t> modeNodeId;
	IntrusivePtr_t<const NodeId_t> laserNodeId;
	IntrusivePtr_t<const NodeId_t> axis4NodeId;
	IntrusivePtr_t<const NodeId_t> axis3NodeId;
	IntrusivePtr_t<const NodeId_t> axis2NodeId;
	IntrusivePtr_t<const NodeId_t> axis1NodeId;
	IntrusivePtr_t<const NodeId_t> multiplyNodeId;

public:

	SyncReaderWriter_t()
	{
	}

	Status_t Initialise(IntrusivePtr_t<UnderlyingSystem_t> underlyingSystem, IntrusivePtr_t<UAServer_t> uaserver)
	{
		UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(underlyingSystem);
		this->underlyingSystem = underlyingSystem;

		UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(uaserver);
		this->uaserver = uaserver;

		Status_t status;
		status = lock.Initialise();
		UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		AccessLevel_t accessLevel;
		accessLevel.CurrentRead(true);
		accessLevel.CurrentWrite(true);

		EventNotifier_t eventNotifier;
		eventNotifier.SubscribeToEvents(true);

		configuration = uaserver->GetConfiguration(status);
		UASDK_RETURN_UNEXPECTED_IF_NULL(configuration);
		addressSpace = configuration->AddressSpace();
		UASDK_RETURN_UNEXPECTED_IF_NULL(addressSpace);

		IntrusivePtr_t<IVariableNode_t> variableNode;
		String_t browseName;

		// Objects folder
		IntrusivePtr_t<const IObjectNode_t> objectsNode = addressSpace->FindObjectNode(NodeIdNumeric_t(0, OpcUaId_ObjectsFolder), status);
		UASDK_RETURN_UNEXPECTED_IF_NULL(objectsNode);

		// Robot1
		IntrusivePtr_t<IObjectNode_t> robot1Node;
		status = browseName.CopyFrom("Robot1");
		status = GetObjectWithReferenceType(*objectsNode, *addressSpace, browseName, OpcUaId_Organizes, robot1Node);
		if (robot1Node.is_set() && status.IsGood())
		{
			robot1NodeId = robot1Node->NodeId();
			robot1Node->EventNotifier(eventNotifier);

			// Speed
			status = browseName.CopyFrom("Speed");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				speedNodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Mode
			status = browseName.CopyFrom("Mode");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				modeNodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Laser
			status = browseName.CopyFrom("Laser");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				laserNodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Axis4
			status = browseName.CopyFrom("Axis4");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				axis4NodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Axis3
			status = browseName.CopyFrom("Axis3");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				axis3NodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Axis2
			status = browseName.CopyFrom("Axis2");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				axis2NodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Axis1
			status = browseName.CopyFrom("Axis1");
			status = AddressSpaceUtilities_t::GetProperty(*robot1Node, *addressSpace, browseName, variableNode);
			if (variableNode.is_set() && status.IsGood())
			{
				axis1NodeId = variableNode->NodeId();
				status = variableNode->ValueAttributeReaderWriter(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				status = variableNode->AccessLevel(accessLevel);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
			}

			// Multiply method
			status = browseName.CopyFrom("Multiply");
			IntrusivePtr_t<IMethodNode_t> multiplyNode;
			status = GetMethodWithReferenceType(*robot1Node, *addressSpace, browseName, OpcUaId_HasComponent, multiplyNode);
			if (multiplyNode.is_set() && status.IsGood())
			{
				multiplyNodeId = multiplyNode->NodeId();
				status = multiplyNode->SetMethodHandler(this);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

				// Input arguments
				IntrusivePtr_t<IVariableNode_t> multiplyInArgsNode;
				String_t browseName;
				status = browseName.CopyFrom("InputArguments");
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

				status = AddressSpaceUtilities_t::GetProperty(*multiplyNode, *addressSpace, browseName, multiplyInArgsNode);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

				IntrusivePtr_t<DataValue_t> multiplyInArgsDataValue(new SafeRefCount_t<DataValue_t>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(multiplyInArgsDataValue);

				IntrusivePtr_t<NodeId_t> doubleDataTypeId(new SafeRefCount_t<NodeIdNumeric_t>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(doubleDataTypeId);
				status = doubleDataTypeId->CopyFrom(NodeIdNumeric_t(0, OpcUaId_Double));
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

				IntrusivePtr_t<ArrayUA_t<Argument_t>> multiplyInArgsArray(new SafeRefCount_t<ArrayUA_t<Argument_t>>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(multiplyInArgsArray);
				IntrusivePtr_t<Argument_t> inArg0(new SafeRefCount_t<Argument_t>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(inArg0);
				inArg0->Name().CopyFrom("A");
				inArg0->DataType() = doubleDataTypeId;
				inArg0->ValueRank().Value(-1);

				IntrusivePtr_t<Argument_t> inArg1(new SafeRefCount_t<Argument_t>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(inArg1);
				inArg1->Name().CopyFrom("B");
				inArg1->DataType() = doubleDataTypeId;
				inArg1->ValueRank().Value(-1);

				status = multiplyInArgsArray->Initialise(2);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				(*multiplyInArgsArray)[0] = inArg0;
				(*multiplyInArgsArray)[1] = inArg1;
				multiplyInArgsDataValue->Value() = multiplyInArgsArray;

				IntrusivePtr_t<DateTime_t> sourceTimeStamp = new SafeRefCount_t<DateTime_t>();
				UASDK_RETURN_UNEXPECTED_IF_NULL(sourceTimeStamp);
				sourceTimeStamp->Value(UASDK_datetime());
				multiplyInArgsDataValue->SourceTimestamp() = sourceTimeStamp;

				multiplyInArgsNode->Value(multiplyInArgsDataValue);

				// Output arguments
				IntrusivePtr_t<IVariableNode_t> multiplyOutArgsNode;
				status = browseName.CopyFrom("OutputArguments");
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

				status = AddressSpaceUtilities_t::GetProperty(*multiplyNode, *addressSpace, browseName, multiplyOutArgsNode);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

				IntrusivePtr_t<DataValue_t> multiplyOutArgsDataValue(new SafeRefCount_t<DataValue_t>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(multiplyOutArgsDataValue);

				IntrusivePtr_t<ArrayUA_t<Argument_t> > multiplyOutArgsArray(new SafeRefCount_t<ArrayUA_t<Argument_t>>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(multiplyOutArgsArray);
				IntrusivePtr_t<Argument_t > outArg0(new SafeRefCount_t<Argument_t>());
				UASDK_RETURN_UNEXPECTED_IF_NULL(outArg0);
				outArg0->Name().CopyFrom("Result");
				outArg0->DataType() = doubleDataTypeId;
				outArg0->ValueRank().Value(-1);

				status = multiplyOutArgsArray->Initialise(1);
				UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
				(*multiplyOutArgsArray)[0] = outArg0;
				multiplyOutArgsDataValue->Value() = multiplyOutArgsArray;

				IntrusivePtr_t<DateTime_t> sourceTimeStamp2 = new SafeRefCount_t<DateTime_t>();
				UASDK_RETURN_UNEXPECTED_IF_NULL(sourceTimeStamp2);
				sourceTimeStamp2->Value(UASDK_datetime());
				multiplyOutArgsDataValue->SourceTimestamp() = sourceTimeStamp2;

				multiplyOutArgsNode->Value(multiplyOutArgsDataValue);
			}
		}
		return OpcUa_Good;
	}

	bool CanReadValueSynchronously(const IVariableNode_t& node)
	{
		return true;
	}

	Status_t ReadValueAttributeBegin(
		IntrusivePtr_t<const IVariableNode_t>& node,
		uint32_t maxAge,
		bool setSourceTimestamp,
		IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
		IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
		uint32_t transactionId,
		uint32_t timeoutHint,
		IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
	{
		return OpcUa_BadNotSupported;
	}

	Status_t ReadValueAttribute(
		const IVariableNode_t& node,
		uint32_t maxAge,
		bool setSourceTimestamp,
		const ArrayUA_t<String_t>& locales,
		const Array_t<IndexRange_t>& indexRange,
		uint32_t transactionId,
		uint32_t timeoutHint,
		IntrusivePtr_t<DataValue_t>& dataValue,
		IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
	{
		AutoLock_t lk(lock);

		dataValue = new SafeRefCount_t<DataValue_t>();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue);

		IntrusivePtr_t<const NodeId_t> nodeid = node.NodeId();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(nodeid);

		if (nodeid == speedNodeId)
		{
			return underlyingSystem->GetSpeed(dataValue);
		}

		if (nodeid == modeNodeId)
		{
			return underlyingSystem->GetMode(dataValue);
		}

		if (nodeid == laserNodeId)
		{
			return underlyingSystem->GetLaser(dataValue);
		}

		if (nodeid == axis4NodeId)
		{
			return underlyingSystem->GetAxis4(dataValue);
		}

		if (nodeid == axis3NodeId)
		{
			return underlyingSystem->GetAxis3(dataValue);
		}

		if (nodeid == axis2NodeId)
		{
			return underlyingSystem->GetAxis2(dataValue);
		}

		if (nodeid == axis1NodeId)
		{
			return underlyingSystem->GetAxis1(dataValue);
		}

		return OpcUa_BadNodeIdUnknown;
	}

	bool CanWriteValueSynchronously(const IVariableNode_t& node)
	{
		return true;
	}

	Status_t WriteValueAttributeBegin(
		IntrusivePtr_t<IVariableNode_t>& node,
		IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
		IntrusivePtr_t<const DataValue_t> dataValue,
		uint32_t transactionId,
		uint32_t timeoutHint,
		IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
	{
		return OpcUa_BadNotSupported;
	}

	Status_t WriteValueAttribute(
		IVariableNode_t& node,
		const Array_t<IndexRange_t>& indexRange,
		IntrusivePtr_t<const DataValue_t> dataValue,
		uint32_t transactionId,
		uint32_t timeoutHint,
		IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
	{
		AutoLock_t lk(lock);
		Status_t status;

		UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(dataValue);

		IntrusivePtr_t<const NodeId_t> nodeid = node.NodeId();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(nodeid);

		if (nodeid == speedNodeId)
		{
			return underlyingSystem->SetSpeed(dataValue);
		}

		if (nodeid == modeNodeId)
		{
			return underlyingSystem->SetMode(dataValue);
		}

		if (nodeid == laserNodeId)
		{
			return underlyingSystem->SetLaser(dataValue);
		}

		if (nodeid == axis4NodeId)
		{
			return underlyingSystem->SetAxis4(dataValue);
		}

		if (nodeid == axis3NodeId)
		{
			return underlyingSystem->SetAxis3(dataValue);
		}

		if (nodeid == axis2NodeId)
		{
			return underlyingSystem->SetAxis2(dataValue);
		}

		if (nodeid == axis1NodeId)
		{
			return underlyingSystem->SetAxis1(dataValue);
		}

		return OpcUa_BadNodeIdUnknown;
	}

	virtual Status_t CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
		uint32_t transactionId,
		const IUserPermissions_t& userPermissions,
		uint32_t timeoutHint,
		IntrusivePtr_t<INode_t>& componentOf,
		IntrusivePtr_t<IMethodNode_t>& method,
		IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
		IntrusivePtr_t<CallMethodResult_t>& result,
		IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
	{
		UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(method);

		if (!requestParameters.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadArgumentsMissing);
		}
		IntrusivePtr_t<const NodeId_t> componentOfid = componentOf->NodeId();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(componentOfid);
		IntrusivePtr_t<const NodeId_t> nodeid = method->NodeId();
		UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(nodeid);

		// Multiply method of Robot1
		if (componentOfid == robot1NodeId && nodeid == multiplyNodeId)
		{
			IntrusivePtr_t<Double_t> inArg0;
			IntrusivePtr_t<Double_t> inArg1;

			Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), inArg0, inArg1);
			if (!inArg0.is_set() || !inArg1.is_set() || status.IsBad())
			{
				UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
			}

			result.reset(new SafeRefCount_t<CallMethodResult_t>());
			UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(result);

			IntrusivePtr_t<Double_t> outArg0(new SafeRefCount_t<Double_t>());
			UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(outArg0);

			outArg0->Value(inArg0->Value() * inArg1->Value());

			status = result->OutputArguments().Initialise(1);
			UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

			status = outArg0->CopyTo((result->OutputArguments())[0]);
			UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

			result->StatusCode() = OpcUa_Good;

			return completedCallback->CallMethodCompleted(result);
		}

		return OpcUa_BadInvalidArgument;
	}
};

IntrusivePtr_t<UAServer_t> CreateAndConfigureServer(Status_t& result)
{
	IntrusivePtr_t<UAServer_t> uaserver;

	//Populate the address space with the help of nodeset file
	IntrusivePtr_t<IAddressSpace_t> addressSpace;
	if (!addressSpace.is_set())
	{
		addressSpace = UAServer_t::CreateAddressSpace(9973, result);
		if (!addressSpace.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}

		//Load Ua nodeset.
		IntrusivePtr_t<IXmlNodesetIO_t> xmlParser = UAServer_t::CreateXmlNodesetIO(true, result);
		if (!xmlParser.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}
		IntrusivePtr_t<StdFile_t> nodesetFile = new SafeRefCount_t<StdFile_t>();
		if (!nodesetFile.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}
		IntrusivePtr_t<String_t> filename = new SafeRefCount_t<String_t>();
		if (!filename.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}
		result = filename->CopyFrom("Opc.Ua.NodeSet2_1_03.xml");
		if (result.IsBad())
		{
			return uaserver;
		}
		result = nodesetFile->Initialise(false, filename);
		if (result.IsBad())
		{
			return uaserver;
		}
		result = xmlParser->Import(*nodesetFile, *addressSpace);
		if (result.IsBad())
		{
			return uaserver;
		}

		//Load Robot nodeset.
		IntrusivePtr_t<IXmlNodesetIO_t> xmlParser2 = UAServer_t::CreateXmlNodesetIO(true, result);
		if (!xmlParser2.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}
		IntrusivePtr_t<StdFile_t> nodesetFile2 = new SafeRefCount_t<StdFile_t>();
		if (!nodesetFile2.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}
		IntrusivePtr_t<String_t> filename2 = new SafeRefCount_t<String_t>();
		if (!filename2.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}
		result = filename2->CopyFrom("RobotServer.NodeSet2.xml");
		if (result.IsBad())
		{
			return uaserver;
		}
		result = nodesetFile2->Initialise(false, filename2);
		if (result.IsBad())
		{
			return uaserver;
		}
		result = xmlParser2->Import(*nodesetFile2, *addressSpace);
		if (result.IsBad())
		{
			return uaserver;
		}
	}

	//Create and configure server

	//Get the unique application URI from the Server Array in the address space (was imported from the nodeset file)
	NodeIdNumeric_t serverArrayNodeId;
	serverArrayNodeId.NamespaceIndex() = 0;
	serverArrayNodeId.Identifer() = OpcUaId_Server_ServerArray;
	IntrusivePtr_t<IVariableNode_t> serverArrayNode = addressSpace->FindVariableNode(serverArrayNodeId, result);
	if (!serverArrayNode.is_set())
	{
		result = OpcUa_BadConfigurationError;
		return uaserver;
	}
	IntrusivePtr_t<const DataValue_t> serverArrayValue = serverArrayNode->Value();
	if (!serverArrayValue.is_set() || !serverArrayValue->Value().is_set())
	{
		result = OpcUa_BadConfigurationError;
		return uaserver;
	}
	IntrusivePtr_t<const ArrayUA_t<String_t> > serverArray = RuntimeCast<const ArrayUA_t<String_t>*>(*serverArrayValue->Value());
	if (!serverArray.is_set() || (serverArray->Count() < 1) || !(*serverArray)[0].is_set())
	{
		result = OpcUa_BadConfigurationError;
		return uaserver;
	}

	IntrusivePtr_t<String_t> applicationURI = new SafeRefCount_t<String_t>();
	if (!applicationURI.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}
	result = applicationURI->CopyFrom(*(*serverArray)[0]);
	if (result.IsBad())
	{
		return uaserver;
	}

	IntrusivePtr_t<BuildInfo_t> buildInfo = new SafeRefCount_t<BuildInfo_t>();
	if (!buildInfo.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}
	result = buildInfo->ProductName().CopyFrom("Matrikon Flex OPC UA SDK Example Server");
	if (result.IsBad())
	{
		return uaserver;
	}
	result = buildInfo->ProductUri().CopyFrom("http://www.matrikonopc.com/UASDK");
	if (result.IsBad())
	{
		return uaserver;
	}

	IntrusivePtr_t<IServerConfiguration_t> configuration = UAServer_t::CreateConfiguration(result);
	if (!configuration.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}
	result = configuration->AddEndpointUserTokenPolicy(SECURITY_POLICY_NONE,
		MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_NONE,
		UserIdentityTokenType_t::OPCUA_USER_IDENTITY_TOKEN_TYPE_ANONYMOUS,
		SECURITY_POLICY_NONE);
	if (result.IsBad())
	{
		return uaserver;
	}

#if (UASDK_INCLUDE_SECURITY > 0)
	result = configuration->AddEndpointUserTokenPolicy(SECURITY_POLICY_BASIC128RSA15,
		MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGNANDENCRYPT,
		UserIdentityTokenType_t::OPCUA_USER_IDENTITY_TOKEN_TYPE_ANONYMOUS,
		SECURITY_POLICY_NONE);
	if (result.IsBad())
	{
		return uaserver;
	}

	ServerCertificateValidationOptions_t validationOptions;
	validationOptions.doNotSaveRejectedCertificates = false;

	IntrusivePtr_t<const ICertificatePrivateKeyPasswordProvider_t> passwordProvider = new SafeRefCount_t<CertificatePrivateKeyPasswordProvider_t>();
	if (!passwordProvider.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}

	IntrusivePtr_t<String_t> securityCertificateDirectoryStoresPath = new SafeRefCount_t<String_t>();
	if (!securityCertificateDirectoryStoresPath.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}
	result = securityCertificateDirectoryStoresPath->CopyFrom(".");
	if (result.IsBad())
	{
		return uaserver;
	}

	configuration->CertificateValidationOptions(validationOptions);
	configuration->SecurityCertificateDirectoryStoresPath(securityCertificateDirectoryStoresPath);
	configuration->CertificatePrivateKeyPasswordProvider(passwordProvider);
#endif

	IntrusivePtr_t<const IUserPermissionsProvider_t> userPermissionsProvider = new SafeRefCount_t<UserPermissionsProvider_t>();
	if (!userPermissionsProvider.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}

	IntrusivePtr_t<IServerStateListener_t> serverStateListener = new SafeRefCount_t<ServerStateListener_t>();
	if (!serverStateListener.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}

	configuration->ServerStateListener(serverStateListener);
	configuration->UserPermissionsProvider(userPermissionsProvider);
	configuration->ApplicationURI(applicationURI);
	configuration->BuildInfo(buildInfo);
	configuration->ServerEndpointTCPPort(55000);
	configuration->MaxMonitoredItems(10000);
	configuration->ServerCyclicRateInMs(100);
	configuration->MaxBrowseRefsPerNode(1000);
	configuration->AddressSpace(addressSpace);
	configuration->MaxMonItemQueueSize(500);

	//Create the server instance
	uaserver = new SafeRefCount_t<UAServer_t>();
	if (!uaserver.is_set())
	{
		result = OpcUa_BadOutOfMemory;
		return uaserver;
	}

	result = uaserver->Initialise(configuration, 10);
	if (result.IsBad())
	{
		return uaserver;
	}

#if (UASDK_INCLUDE_SECURITY > 0)
	result = uaserver->SecurityCreateCertificateDirectoryStores();
	if (result.IsBad())
	{
		return uaserver;
	}

	result = uaserver->SecurityRefreshApplicationCertificateDirectoryStores();
	if (result.IsBad())
	{
		;//Ignore initial error
	}

	//Try to validate certificates and create them if necessary
	result = uaserver->SecurityValidateApplicationInstanceCertificate(SECURITY_POLICY_BASIC128RSA15);
	if (result.IsBad())
	{
		//Create certificate
		IntrusivePtr_t<CertificateGenerationParameters_t> parameters = new SafeRefCount_t<CertificateGenerationParameters_t>();
		if (!parameters.is_set())
		{
			result = OpcUa_BadOutOfMemory;
			return uaserver;
		}

		parameters->type = UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE;
		parameters->group = UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP;
		parameters->privateKeyBitLength = 1024;

		result = configuration->CertificatePrivateKeyPasswordProvider()->GetPassword(parameters->type, parameters->group, parameters->privateKeyPassword);
		if (result.IsBad())
		{
			return uaserver;
		}
		parameters->start_date = UASDK_datetime();
		parameters->end_date = parameters->start_date.Value() + static_cast<int64_t>(315360e9);
		result = parameters->applicationUri.CopyFrom(*applicationURI);
		if (result.IsBad())
		{
			return uaserver;
		}

		result = parameters->ipAddresses.Initialise(1);
		if (result.IsBad())
		{
			return uaserver;
		}

		result = parameters->ipAddresses[0].CopyFrom("192.168.1.100");
		if (result.IsBad())
		{
			return uaserver;
		}

		result = parameters->commonName.CopyFrom("MatrikonOPC Test Server");
		if (result.IsBad())
		{
			return uaserver;
		}

		result = uaserver->SecurityCreateSelfSignedApplicationInstanceCertificate(parameters);
		if (result.IsBad())
		{
			return uaserver;
		}

		parameters->type = UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE;
		parameters->privateKeyBitLength = 2048;

		result = uaserver->SecurityCreateSelfSignedApplicationInstanceCertificate(parameters);
		if (result.IsBad())
		{
			return uaserver;
		}
	}

	result = uaserver->SecurityRefreshApplicationCertificateDirectoryStores();
	if (result.IsBad())
	{
		return uaserver;
	}
#endif

	return uaserver;
}

int main()
{
	Status_t status;

	srand(static_cast<unsigned int>(UASDK_datetime()));

	IntrusivePtr_t<LogListener_t> logListener;
	IntrusivePtr_t<UAServer_t> uaserver;

	//Enable logging
#if (UASDK_DEBUG > 0)
	logListener = new SafeRefCount_t<LogListener_t>();
	if (!logListener.is_set())
	{
	  exit(-1);
	}
	status = logListener->Initialise(ILogListener_t::LOG_LEVEL_WARNING);
	if (status.IsBad())
	{
	  exit(-1);
	}
	Logger_t::Initialise(*logListener);
#endif

	//Create and configure the server
	uaserver = CreateAndConfigureServer(status);
	if (!uaserver.is_set())
	{
		exit(-1);
	}

	IntrusivePtr_t<UnderlyingSystem_t> underlyingSystem = new SafeRefCount_t<UnderlyingSystem_t>();
	if (!underlyingSystem.is_set())
	{
		exit(-1);
	}

	IntrusivePtr_t<SyncReaderWriter_t> readerWriter = new SafeRefCount_t<SyncReaderWriter_t>();
	if (!readerWriter.is_set())
	{
		exit(-1);
	}
	status = readerWriter->Initialise(underlyingSystem, uaserver);
	if (status.IsBad())
	{
		exit(-1);
	}

	printf("****************************************************************************\n");
	printf("                    Server is running in Demo mode                        \n\n");
	printf("     Discovery and Server Endpoints are at: 'opc.tcp://localhost:55000'     \n");
	printf("****************************************************************************\n");
	printf("Press any key to exit...\n");

	String_t license;
	uaserver->Start(license);

	while (!_kbhit())
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	uaserver->Stop();
	uaserver->Terminate();

	return 0;
}
