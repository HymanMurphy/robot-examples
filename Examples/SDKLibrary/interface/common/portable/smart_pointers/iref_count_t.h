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

#ifndef _IREF_COUNT_T_
#define _IREF_COUNT_T_

namespace uasdk
{
/** \addtogroup grpSmartPointer
 *@{*/

  /*****************************************************************************/
  /** This class used to count the references.
   *
   */
  class IRefCount_t
  {
  protected:
    virtual int RefCount(void) const = 0;

  public:
    virtual ~IRefCount_t() {};
	
    /*****************************************************************************/
    /** This function used to add the references..
     *
     */
    virtual void AddReference() const = 0;

    /*****************************************************************************/
    /** This function used to remove the references..
     *
     */
    virtual void RemoveReference() const = 0;
  };

  /*****************************************************************************/
  /** This class is used to add reference counting to another class.
  *
  */
  template<typename T> class Ref_t : public T, public IRefCount_t
  {
  };


/** @} */

} /* namespace uasdk */

#endif // _IREF_COUNT_T_
