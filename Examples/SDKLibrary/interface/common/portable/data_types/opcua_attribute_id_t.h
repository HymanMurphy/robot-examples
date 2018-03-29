/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
COPYRIGHT (c) 2009 - 2017
HONEYWELL INC.,
ALL RIGHTS RESERVED

This software is a copyrighted work and/or information protected as a trade
secret. Legal rights of Honeywell Inc. in this software are distinct from
ownership of any medium in which the software is embodied. Copyright or trade
secret notices included must be reproduced in any copies authorized by
Honeywell Inc. The information in this software is subject to change without
notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef _ATTRIBUTEID_T_
#define _ATTRIBUTEID_T_

#include "uasdk_includes.h"
#include "opcua_uint32_t.h"

namespace uasdk
{

  class AttributeId_t
  {

  public:
    typedef enum
    {
      ATTRIBUTE_ID_INVALID = 0,
      ATTRIBUTE_ID_NODEID = 1,
      ATTRIBUTE_ID_NODECLASS = 2,
      ATTRIBUTE_ID_BROWSENAME = 3,
      ATTRIBUTE_ID_DISPLAYNAME = 4,
      ATTRIBUTE_ID_DESCRIPTION = 5,
      ATTRIBUTE_ID_WRITEMASK = 6,
      ATTRIBUTE_ID_USERWRITEMASK = 7,
      ATTRIBUTE_ID_ISABSTRACT = 8,
      ATTRIBUTE_ID_SYMMETRIC = 9,
      ATTRIBUTE_ID_INVERSENAME = 10,
      ATTRIBUTE_ID_CONTAINSNOLOOPS = 11,
      ATTRIBUTE_ID_EVENTNOTIFIER = 12,
      ATTRIBUTE_ID_VALUE = 13,
      ATTRIBUTE_ID_DATATYPE = 14,
      ATTRIBUTE_ID_VALUERANK = 15,
      ATTRIBUTE_ID_ARRAYDIMENSIONS = 16,
      ATTRIBUTE_ID_ACCESSLEVEL = 17,
      ATTRIBUTE_ID_USERACCESSLEVEL = 18,
      ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL = 19,
      ATTRIBUTE_ID_HISTORIZING = 20,
      ATTRIBUTE_ID_EXECUTABLE = 21,
      ATTRIBUTE_ID_USEREXECUTABLE = 22,
      ATTRIBUTE_ID_END = 23
    } Enum_t;
  };

}//namespace

#endif /* _ATTRIBUTEID_T_ */
