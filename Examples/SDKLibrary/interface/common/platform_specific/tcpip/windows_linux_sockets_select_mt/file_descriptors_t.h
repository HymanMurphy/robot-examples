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

#ifndef _FILE_DESCRIPTORS_T_
#define _FILE_DESCRIPTORS_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT > 0)

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/select.h>
#define SOCKET int
#endif

#include "allocatable_t.h"
#include "intrusive_list_t.h"
#include "auto_lock_t.h"

namespace uasdk
{

class FileDescriptors_t : public IRefCount_t, public Allocatable_t
{
private:
  fd_set read_fds;
  fd_set write_fds;
  fd_set master_fds;

  Lock_t lock;

public:
  virtual ~FileDescriptors_t()
  {
  }
  /*****************************************************************************/
  /** This function used to initialize the file descriptor.
   *
   * @return
   * returns status of the operation.
   */
  Status_t Initialise(void)
  {
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_ZERO(&master_fds);
    return lock.Initialise();
  }

  /*****************************************************************************/
  /**Function used to set the Master file descriptor.
   *
   * @param[in]fd
   * File descriptor which is needs to be set.
   */
  void Add(SOCKET fd)
  {
    AutoLock_t lk(lock);
     FD_SET(fd, &master_fds);
  }

  /*****************************************************************************/
  /**Function used to clear the file descriptors.
   *
   * @param[in]fd
   * File descriptor which is needs to be clear.
   */
  void Remove(SOCKET fd)
  {
    AutoLock_t lk(lock);
    FD_CLR(fd, &master_fds);
    FD_CLR(fd, &read_fds);
    FD_CLR(fd, &write_fds);
  }

  /*****************************************************************************/
  /**Function used to Add the file descriptor set for reading operation.
   *
   * @param[in]fd
   * File descriptor which is to be set for read.
   */
  void AddToRead(SOCKET fd)
  {
    AutoLock_t lk(lock);
    if (FD_ISSET(fd, &master_fds))
    {
      FD_SET(fd, &read_fds);
    }
  }
  
  /*****************************************************************************/
  /**Function used to Add the file descriptor for writing operation.
   *
   * @param[in]fd
   * File descriptor which is to be set for write.
   */
  void AddToWrite(SOCKET fd)
  {
    AutoLock_t lk(lock);
    if (FD_ISSET(fd, &master_fds))
    {
      FD_SET(fd, &write_fds);
    }
  }

  /*****************************************************************************/
  /**Function used to clear the read file descriptor.
   *
   * @param[in]fd
   * File descriptor which is to be clear from read operation.
   */
  void RemoveFromRead(SOCKET fd)
  {
    AutoLock_t lk(lock);
    FD_CLR(fd, &read_fds);
  }

  /*****************************************************************************/
  /**Function used to clear the write file descriptor.
   *
   * @param[in]fd
   * File descriptor which is to be clear from write operation.
   */
  void RemoveFromWrite(SOCKET fd)
  {
    AutoLock_t lk(lock);
    FD_CLR(fd, &write_fds);
  }

  /*****************************************************************************/
  /**Function gets the Master file descriptor.
   *
   * @return
   * returns file descriptor value.
   */
  fd_set GetMaster(void)
  {
    AutoLock_t lk(lock);
    return master_fds;
  }

  /*****************************************************************************/
  /**Function gets the read file descriptor.
   *
   * @return
   * returns file descriptor value.
   */
  fd_set GetRead(void)
  {
    AutoLock_t lk(lock);
    return read_fds;
  }

  /*****************************************************************************/
  /**Function gets the write file descriptor.
   *
   * @return
   * returns file descriptor value.
   */
  fd_set GetWrite(void)
  {
    AutoLock_t lk(lock);
    return write_fds;
  }

};

}

#endif //UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT

#endif // _FILE_DESCRIPTORS_T_
