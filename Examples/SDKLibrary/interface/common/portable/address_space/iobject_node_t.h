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

#ifndef _IOBJECT_NODE_T_
#define _IOBJECT_NODE_T_

#include "uasdk_includes.h"
#include "inode_t.h"

namespace uasdk
{

class IVariableNode_t;
class IObjectTypeNode_t;
class EventNotifier_t;

#if (UASDK_INCLUDE_EVENTS > 0)
class INodeEventListener_t;
class IAttributeAccess_t;
#endif // UASDK_INCLUDE_EVENTS

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief Object Node Interface
 *
 * A class that represents an Object node in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IObjectNode_t : public virtual INode_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(IObjectNode_t);

  virtual ~IObjectNode_t() {}

  /*****************************************************************************/
  /** Get the EventNotifier attribute of the node
   *
   * @return
   * The EventNotifier of the node.
   */
  virtual EventNotifier_t EventNotifier(void) const = 0;

  /*****************************************************************************/
  /** Set the EventNotifier attribute of the node
   *
   * @param[in] value
   * The required EventNotifier of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t EventNotifier(EventNotifier_t value) = 0;

#if (UASDK_INCLUDE_EVENTS > 0)

	/*****************************************************************************/
	/** Adds an event listener to the node
	*
	*  Any software component with a non-const reference to a node may register
	*  an attribute changed listener with the node. The listener can specify the
	*  node attributes he is interested in and he will only be called when those
	*  specific attributes change. Any software component registering a listener
	*  with the node is responsible for removing the listener if required.
	*  There can be multiple attribute changed listeners registered at any given
	*  time.
	*
	* @param[in] value
	* An intrusive reference counting Boost-style smart pointer to the listener.
	* The value provided must satisfy a number of rules.
	* 1) If set, the INodeEventListener_t must have been created
	*    dynamically using a SafeRefCount_t (to ensure thread safety).
	* 2) The value pointer can be set or empty. Passing an empty pointer to this
	*    function removes the listener from the node.
	*
	* @return
	* The result of the operation.
	*/
  virtual Status_t EventListenerAdd(IntrusivePtr_t<INodeEventListener_t> value) = 0;

	/*****************************************************************************/
	/** Removes an event listener to the node
	*
	*  Any software component with a non-const reference to a node may register
	*  an attribute changed listener with the node. The listener can specify the
	*  node attributes he is interested in and he will only be called when those
	*  specific attributes change. Any software component registering a listener
	*  with the node is responsible for removing the listener if required.
	*  There can be multiple attribute changed listeners registered at any given
	*  time.
	*
	* @param[in] value
	* An intrusive reference counting Boost-style smart pointer to the listener.
	* The value provided must satisfy a number of rules.
	* 1) If set, the INodeEventListener_t must have been created
	*    dynamically using a SafeRefCount_t (to ensure thread safety).
	* 2) The value pointer can be set or empty. Passing an empty pointer to this
	*    function removes the listener from the node.
	*
	* @return
	* The result of the operation.
	*/
  virtual Status_t EventListenerRemove(IntrusivePtr_t<INodeEventListener_t> value) = 0;

	/*****************************************************************************/
	/** Calls the event listener to the node
	*
	*  Any software component with a non-const reference to a node may register
	*  an attribute changed listener with the node. The listener can specify the
	*  node attributes he is interested in and he will only be called when those
	*  specific attributes change. Any software component registering a listener
	*  with the node is responsible for removing the listener if required.
	*  There can be multiple attribute changed listeners registered at any given
	*  time.
	*
	* @param[in] value
	* An intrusive reference counting Boost-style smart pointer to the listener.
	* The value provided must satisfy a number of rules.
	* 1) If set, the IAttributeAccess_t must have been created
	*    dynamically using a SafeRefCount_t (to ensure thread safety).
	* 2) The value pointer can be set or empty. Passing an empty pointer to this
	*    function removes the listener from the node.
	*
	* @return
	* The result of the operation.
	*/
	virtual Status_t CallEventListeners(IntrusivePtr_t<IAttributeAccess_t>& eventAttribute) = 0;

#endif // UASDK_INCLUDE_EVENTS

};

/** @} */

}

#endif // _IOBJECT_NODE_T_
