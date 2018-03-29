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

#ifndef _ICONDITION_T_
#define _ICONDITION_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "inode_t.h"
#include "inode_method_handler_t.h"
#include "condition_type_data_t.h"

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ICondition_t
*
* This is an interface class which should be implemented by all the conditions.
*
*/
class ICondition_t : public INodeMethodHandler_t, public IRuntimeType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ICondition_t);

  virtual ~ICondition_t() {}

  /*****************************************************************************/
  /** ConditionId()
   *
   * @return
   * A unique condition Id.
   */
  virtual IntrusivePtr_t<const NodeId_t> ConditionId(void) = 0;

	/*****************************************************************************/
	/** MountToAddressSpace()
	*  Mount the condition to the addressSpace
	*
	*  @param[in] browseName
	*  browseName of the condition
	*
	*  @param[in] hasTypeDefinitionId
	*  TypeDefinitionId of the condition
	*
	*  @param[in] parentNodeId
	*  nodeId of the parentNode in addressSpace under which the condition is going to be mounted
	*
	* @return
	* status of the operation
	*/
	virtual Status_t MountToAddressSpace(const String_t& browseName, uint32_t hasTypeDefinitionId, NodeId_t& parentNodeId) = 0;
	
	/*****************************************************************************/
	/** UnmountFromAddressSpace()
	*  Unmount the condition from the addressSpace
	*
	* @return
	* status of the operation
	*/
	virtual void UnmountFromAddressSpace(void) = 0;

  /*****************************************************************************/
  /** RelocateInAddressSpace()
  *  Change the location of the condition in the addressSpace. If the condition is not mounted earlier, it will be mounted in the addressSpace
  *
  *  @param[in] browseName
  *  browseName of the condition
  *
  *  @param[in] hasTypeDefinitionId
  *  TypeDefinitionId of the condition
  *
  *  @param[in] newParentNodeId
  *  nodeId of new node under which the condition needs to be relocated
  *
  * @return
  * status of the operation
  */
  virtual Status_t RelocateInAddressSpace(const String_t& browseName, uint32_t hasTypeDefinitionId, NodeId_t& newParentNodeId) = 0;

  /*****************************************************************************/
  /** ConditionData()
  *  Get the condition data instance
  *
  * @return
  * condition data instance
  */
  virtual IntrusivePtr_t<ConditionTypeData_t>& ConditionData(void) = 0;

  /*****************************************************************************/
  /** GetEventData()
  * GetEventData to be fired to the client
  *
  * @param[out] data
  * copy of the data to be sent as an event
  *
  * @param[out] sourceNodeId
  * source node id associated with the event
  *
  * @return
  * status of the operation
  */
  virtual Status_t GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId) = 0;

  /*****************************************************************************/
  /** IsMountedToAddressSpace()
  * IsMountedToAddressSpace is used to determine if the condition is mounted in the address space.
  *
  * @return
  * return true if the condition is mounted in the address space, else return false
  */
  virtual bool IsMountedToAddressSpace(void) = 0;

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _ICONDITION_T_
