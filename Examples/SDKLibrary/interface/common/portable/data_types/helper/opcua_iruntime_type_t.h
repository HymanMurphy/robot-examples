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


#ifndef UASDK_IRUNTIME_TYPE_H
#define UASDK_IRUNTIME_TYPE_H 1

namespace uasdk
{

/**
 * Interface from which a type must derive to support the UA SDK's runtime type
 * machinery. Runtime type support enables functionality roughly equivalent to 
 * dynamic_cast<>() without imposing the overhead of C++ RTTI on all polymorphic
 * types in the entire program.  
 *
 * Supporting runtime type discovery for a type T requires the following
 * if the class is NOT a template.
 *
 * 1. Derive T from IRuntimeType_t OR from a type the is ultimately derived from IRuntimeType_t (check the hierachy!). 
 * 2. Add UA_DECLARE_RUNTIME_TYPE(T); to the class definition (.h).
 * 3. Add UA_DEFINE_RUNTIME_TYPE[_x](T [, Base_0, Base_1, ..., Base_x] ) to the implementation
 *   (.cpp). 
 *
 * If the class is a template do the following:
 *
 * 1. Derive T from IRuntimeType_t
 * 2. Add UA_DEFINE_RUNTIME_TYPE_TMPL[_x](T[, Base_0, Base_1, ... Base_x] ) to the header.
 */
class IRuntimeType_t
{
public:
  virtual ~IRuntimeType_t();
  virtual void *AddressByTypeId(const void *typeId) = 0;
  virtual const void *AddressByTypeId(const void *typeId) const = 0;
};

template<typename T> struct RemovePointer_t ;
template<typename T> struct RemovePointer_t<T * > { typedef T Type; };
template<typename T> struct RemovePointer_t<T * const > { typedef T Type; };
template<typename T> struct RemovePointer_t<T * volatile > { typedef T Type; };
template<typename T> struct RemovePointer_t<T * const volatile > { typedef T Type; };

template<typename ToPtr, typename FromT>
ToPtr RuntimeCast(FromT &from)
{
  return RemovePointer_t<ToPtr>::Type::Cast(from);
}

template<typename ToPtr, typename FromT>
ToPtr RuntimeCast(FromT const &from)
{
  return RemovePointer_t<ToPtr>::Type::Cast(from);
}

#if 0
template<typename ToPtr, typename FromT>
ToPtr RuntimeCast(const FromT *from)
{
  return RemovePointer_t<ToPtr>::Type::Cast(from);
}

template<typename ToPtr, typename FromT>
ToPtr RuntimeCast(FromT *from)
{
  return RemovePointer_t<ToPtr>::Type::Cast(from);
}
#endif

}

#define UA_DECLARE_RUNTIME_TYPE(Klazz) \
  static const Klazz *Cast(IRuntimeType_t const &); \
  static Klazz *Cast(IRuntimeType_t &); \
  static const Klazz *Cast(const IRuntimeType_t *); \
  static Klazz *Cast(IRuntimeType_t *); \
  virtual const void *AddressByTypeId(const void *) const; \
  virtual void *AddressByTypeId(const void *)


#define UA_DEFINE_RUNTIME_TYPE_ROOT(Klazz) \
  static const void *const Klazz##_TypeID = &Klazz##_TypeID; \
  const Klazz *Klazz::Cast(IRuntimeType_t const &other) \
  { \
    return static_cast<const Klazz *>(other.AddressByTypeId(Klazz##_TypeID)); \
  } \
  Klazz *Klazz::Cast(IRuntimeType_t &other) \
  { \
    return static_cast<Klazz *>(other.AddressByTypeId(Klazz##_TypeID)); \
  } \
  const Klazz *Klazz::Cast(const IRuntimeType_t *other) \
  { \
    return (other ? static_cast<const Klazz *>(other->AddressByTypeId(Klazz##_TypeID)) : NULL); \
  } \
  Klazz *Klazz::Cast(IRuntimeType_t *other) \
  { \
    return (other ? static_cast<Klazz *>(other->AddressByTypeId(Klazz##_TypeID)) : NULL); \
  } \
  const void *Klazz::AddressByTypeId(const void *typeId) const \
  { \
    if (Klazz##_TypeID == typeId) \
    { \
      return this; \
    } \
    return NULL; \
  } \
  void *Klazz::AddressByTypeId(const void *typeId) \
  { \
    if (Klazz##_TypeID == typeId) \
    { \
      return this; \
    } \
    return NULL; \
  }  

#define UA_DEFINE_RUNTIME_TYPE(Klazz, BaseKlazz) \
  static const void *const Klazz##_TypeID = &Klazz##_TypeID; \
  const Klazz *Klazz::Cast(IRuntimeType_t const &other) \
  { \
    return static_cast<const Klazz *>(other.AddressByTypeId(Klazz##_TypeID)); \
  } \
  Klazz *Klazz::Cast(IRuntimeType_t &other) \
  { \
    return static_cast<Klazz *>(other.AddressByTypeId(Klazz##_TypeID)); \
  } \
  const Klazz *Klazz::Cast(const IRuntimeType_t *other) \
  { \
    return (other ? static_cast<const Klazz *>(other->AddressByTypeId(Klazz##_TypeID)) : NULL); \
  } \
  Klazz *Klazz::Cast(IRuntimeType_t *other) \
  { \
    return (other ? static_cast<Klazz *>(other->AddressByTypeId(Klazz##_TypeID)) : NULL); \
  } \
  const void *Klazz::AddressByTypeId(const void *typeId) const \
  { \
    if (Klazz##_TypeID == typeId) \
    { \
      return this; \
    } \
    if (const void *p = this->BaseKlazz::AddressByTypeId(typeId)) \
    { \
      return p; \
    } \
    return NULL; \
  } \
  void *Klazz::AddressByTypeId(const void *typeId) \
  { \
    if (Klazz##_TypeID == typeId)		\
    { \
      return this; \
    } \
    if (void *p = this->BaseKlazz::AddressByTypeId(typeId)) \
    { \
      return p; \
    } \
    return NULL; \
  }  

#define UA_DEFINE_RUNTIME_TYPE_2(Klazz, BaseKlazz1, BaseKlazz2) \
  static const void *const Klazz##_TypeID = &Klazz##_TypeID; \
  const Klazz *Klazz::Cast(IRuntimeType_t const &other) \
  { \
    return static_cast<const Klazz *>(other.AddressByTypeId(Klazz##_TypeID)); \
  } \
  Klazz *Klazz::Cast(IRuntimeType_t &other) \
  { \
    return static_cast<Klazz *>(other.AddressByTypeId(Klazz##_TypeID)); \
  } \
  const Klazz *Klazz::Cast(const IRuntimeType_t *other) \
  { \
    return (other ? static_cast<const Klazz *>(other->AddressByTypeId(Klazz##_TypeID)) : NULL); \
  } \
  Klazz *Klazz::Cast(IRuntimeType_t *other) \
  { \
    return (other ? static_cast<Klazz *>(other->AddressByTypeId(Klazz##_TypeID)) : NULL); \
  } \
  const void *Klazz::AddressByTypeId(const void *typeId) const \
  { \
    if (Klazz##_TypeID == typeId) \
    { \
      return this; \
    } \
    if (const void *p = this->BaseKlazz1::AddressByTypeId(typeId)) \
    { \
      return p; \
    } \
    if (const void *p = this->BaseKlazz2::AddressByTypeId(typeId)) \
    { \
      return p; \
    } \
    return NULL; \
  } \
  void *Klazz::AddressByTypeId(const void *typeId) \
  { \
    if (Klazz##_TypeID == typeId) \
    { \
      return this; \
    } \
    if (void *p = this->BaseKlazz1::AddressByTypeId(typeId)) \
    { \
      return p; \
    } \
    if (void *p = this->BaseKlazz2::AddressByTypeId(typeId)) \
    { \
      return p; \
    } \
    return NULL; \
  }

#define UA_DEFINE_RUNTIME_TYPE_TMPL(Klazz, BaseKlazz) \
  static const void * Get##Klazz##TypeId() \
  { \
    static const void *const Klazz##_TypeId = &Klazz##_TypeId; \
    return Klazz##_TypeId; \
  } \
  static const Klazz *Cast(IRuntimeType_t const &other) \
  { \
    return static_cast<const Klazz *>(other.AddressByTypeId(Get##Klazz##TypeId())); \
  } \
  static Klazz *Cast(BaseDataType_t &other) \
  { \
    return static_cast<Klazz *>(other.AddressByTypeId(Get##Klazz##TypeId())); \
  } \
  const void *AddressByTypeId(const void *typeId) const \
  { \
    if (Get##Klazz##TypeId() == typeId) \
    { \
      return this; \
    } \
    return this->BaseKlazz::AddressByTypeId(typeId); \
  } \
  void *AddressByTypeId(const void *typeId) \
  { \
    if (Get##Klazz##TypeId() == typeId) \
    { \
      return this; \
    } \
    return this->BaseKlazz::AddressByTypeId(typeId); \
  }

#endif
