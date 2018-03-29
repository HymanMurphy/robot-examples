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

#include "audit_event_listener_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "attribute_id_mask_t.h"

namespace uasdk
{
	AuditEventListener_t::AuditEventListener_t()
	{
	}

	AuditEventListener_t::~AuditEventListener_t()
	{
		simpleAttributeOperandList.DeleteAll();
	}

	Status_t AuditEventListener_t::Initialise(IntrusivePtr_t<IAuditEventAttributeLogger_t> attributeLogger_)
	{
		attributeLogger = attributeLogger_;

		return AddBaseAttributeToLog();
	}

	void AuditEventListener_t::AuditEventOccured(IntrusivePtr_t<IAttributeAccess_t>& auditEvent) const
	{
		Status_t status;
		uint32_t count = simpleAttributeOperandList.Count();
		attributeLogger->LogAttribute("\n\n------------------\n");
		for (uint32_t i = 0; i < count; i++)
		{
			IntrusivePtr_t<SimpleAttributeOperand_t> simpleAttributeOperand = simpleAttributeOperandList.GetAtIndex(i);
			if (simpleAttributeOperand.is_set())
			{
				uint16_t namespaceIndex = 0;
				uint32_t typeId = auditEvent->TypeId(namespaceIndex);
				IntrusivePtr_t<BaseDataType_t> value = auditEvent->AttributeValue(typeId, simpleAttributeOperand->BrowsePath(), simpleAttributeOperand->AttributeId().Value(), simpleAttributeOperand->IndexRange(), status);
				attributeLogger->LogAttribute(value);
				attributeLogger->LogAttribute("\n");
			}
		}
	}

	Status_t AuditEventListener_t::AddAttributeToLog(IntrusivePtr_t<SimpleAttributeOperand_t>& simpleAttributeOperand)
	{
		if (!simpleAttributeOperand.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
		}

		return simpleAttributeOperandList.AddToTail(*simpleAttributeOperand);
	}

	Status_t AuditEventListener_t::AddBaseAttributeToLog(void)
	{
		Status_t status;
		uint32_t numberOfAttributes = 9;
		IntrusivePtr_t<NodeIdNumeric_t> baseEventTypeId = new RefCount_t<NodeIdNumeric_t>();
		if (!baseEventTypeId.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}

		baseEventTypeId->NamespaceIndex().Value(0);
		baseEventTypeId->Identifer().Value(2041);

		for (uint32_t i = 0; i < numberOfAttributes; i++)
		{
			IntrusivePtr_t<QualifiedName_t > qualifiedNames = new RefCount_t<QualifiedName_t>();
			if (!qualifiedNames.is_set())
			{
				UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
			}

			switch (i)
			{
			case 0:
				status = qualifiedNames->Name().CopyFrom("EventId");
				break;
			case 1:
				status = qualifiedNames->Name().CopyFrom("EventType");
				break;
			case 2:
				status = qualifiedNames->Name().CopyFrom("SourceNode");
				break;
			case 3:
				status = qualifiedNames->Name().CopyFrom("SourceName");
				break;
			case 4:
				status = qualifiedNames->Name().CopyFrom("Time");
				break;
			case 5:
				status = qualifiedNames->Name().CopyFrom("ReceiveTime");
				break;
			case 6:
				status = qualifiedNames->Name().CopyFrom("LocalTime");
				break;
			case 7:
				status = qualifiedNames->Name().CopyFrom("Message");
				break;
			case 8:
				status = qualifiedNames->Name().CopyFrom("Severity");
				break;
			default:
				break;
			}
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

			IntrusivePtr_t<SimpleAttributeOperand_t> temp = new RefCount_t<SimpleAttributeOperand_t >();
			if (!temp.is_set())
			{
				UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
			}

			temp->TypeId() = baseEventTypeId;
			status = temp->BrowsePath().Initialise(1);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

			temp->BrowsePath()[0] = qualifiedNames;
			temp->AttributeId() = AttributeId_t::ATTRIBUTE_ID_VALUE;
			status = temp->IndexRange().CopyFrom("0");
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

			status = AddAttributeToLog(temp);
      UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
		}

		return status;
	}
}

#endif //UASDK_INCLUDE_EVENTS

