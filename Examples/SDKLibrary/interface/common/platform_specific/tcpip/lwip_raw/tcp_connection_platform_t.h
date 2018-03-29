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

#ifndef _TCP_CONNECTION_PLATFORM_T_
#define _TCP_CONNECTION_PLATFORM_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_TCPIP_LWIP_RAW > 0)

#include "tcp.h"
#include "itcp_connection_platform_t.h"
#include "allocatable_t.h"
#include "ip_endpoint_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_string_t.h"
#include "itcp_connection_core_t.h"
#include "intrusive_list_t.h"
#include "storage_buffer_t.h"

extern "C" err_t opcua_sent(void *arg, struct tcp_pcb *pcb, u16_t len);

namespace uasdk
{

class TcpConnectionPlatform_t : public ITcpConnectionPlatform_t, public Allocatable_t
{
private:
  class DummyIPEndpoint_t : public IPEndpoint_t
  {
    uint16_t Port(void) const
    {
      return 0;
    }

    IntrusivePtr_t<String_t> ToString(void) const
    {
        IntrusivePtr_t<String_t> empty;
        return empty;
    }
  };

  //uint64_t remote_endpoint;
  IntrusiveList_t<TcpConnectionPlatform_t>* connections;
  IntrusivePtr_t<ITcpConnectionCore_t> coreConnection;

  void NotifyCoreWhenNetworkReady(void);

public:
  virtual ~TcpConnectionPlatform_t()
  {
  }

  struct tcp_pcb *pcb;
  StorageBuffer_t rxBuffer;

  Status_t Initialise(struct tcp_pcb *pcb_, IntrusiveList_t<TcpConnectionPlatform_t>& connections_);

  const IPEndpoint_t& IPEndpoint(void) const;

  void CoreOpened(IntrusivePtr_t<ITcpConnectionCore_t> connection);

  Status_t Close(void);

  virtual Status_t Send(IntrusivePtr_t<const IBuffer_t> buffer);

  virtual Status_t Receive(IBuffer_t& buffer);

  virtual void NotifyCoreWhenDataAvailable(void);

  //IntrusivePtr_t<ITcpConnectionCore_t> CoreConnection(void);

  Status_t DataAvailable(void);

  Status_t NetworkReady(void);
};

}

#endif //(UASDK_INCLUDE_TCPIP_LWIP_RAW > 0)

#endif // _TCP_CONNECTION_PLATFORM_T_
