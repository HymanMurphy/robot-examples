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

#ifndef _INODE_EVENT_LISTENER_T_
#define _INODE_EVENT_LISTENER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iattribute_access_t.h"

namespace uasdk
{

class IObjectNode_t;
class IViewNode_t;
class IAttributeAccess_t;

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Node Event Listener
*
* A class that is used to register events for a given node.
* Implementations of this interface must be thread safe.
*
*/
class INodeEventListener_t : public virtual IRefCount_t
{
public:
	virtual ~INodeEventListener_t() {};

	/*****************************************************************************/
	/** Event listener callback for Object Nodes.
	*
	*  @param[in] node
	*  Intrusive pointer of type IObjectNode_t, which can be used for getting the value
	*
	*  @param[in] eventAttributes
	*  Intrusive pointer of type IAttributeAccess_t, which can be used for getting the value
	*
	* @return
	*/
	virtual void EventNotify(IObjectNode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes) = 0;

	/*****************************************************************************/
	/** Event listener callback for View Nodes.
	*
	*  @param[in] node
	*  Intrusive pointer of type IViewNode_t, which can be used for getting the value
	*
	*  @param[in] eventAttributes
	*  Intrusive pointer of type IAttributeAccess_t, which can be used for getting the value
	*
	* @return 
	*/
	virtual void EventNotify(IViewNode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes) = 0;
};

/** @} */

}

#endif // UASDK_INCLUDE_EVENTS

#endif // _INODE_EVENT_LISTENER_T_
