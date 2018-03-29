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

#include "std_file_t.h"

#if (UASDK_INCLUDE_FILE_WINDOWS_LINUX > 0)

#include "uasdk_includes.h"
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

namespace uasdk
{

StdFile_t::~StdFile_t()
{
  uint32_t i;
  uintptr_t context;

  for(i = 0; i < contexts.Count(); i++)
  {
    context = *(contexts.GetAtIndex(i));
    fclose((FILE*)context);
  }
}

Status_t StdFile_t::Initialise(bool writable_, IntrusivePtr_t<String_t>& filename_)
{
  Status_t status = OpcUa_BadInternalError;

  if(!initialised)
  {
    writable = writable_;
    filename = filename_;
    initialised = true;
    status = OpcUa_Good;
  }

  return status;
}

Status_t StdFile_t::OpenFile(const char* mode, bool append, uintptr_t& context) const
{
  FILE* fp = 0;

  ScopedPtr_t<Array_t<char> > name;

  Status_t status = filename->ToString(name);
  if(status.IsBad())
  {
    return 0;
  }

  if((!filename.is_set()) || (name->Value() == 0) || (mode == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

#ifdef _WIN32
  errno_t err = fopen_s(&fp, name->Value(), mode);
  if (err != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
#else
  fp = fopen(name->Value(), mode);
#endif  //_WIN32

  if (fp)
  {
    context = (uintptr_t)fp;
    if(!contexts.AddToTail(context))
    {
      fclose(fp);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
    }

    if(append)
    {
      if(fseek(fp, 0, SEEK_END) != 0)
      {
        fclose(fp);
        UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
      }
    }
  }
  else
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  return OpcUa_Good;
}

uint64_t StdFile_t::Size() const
{
  uint64_t size = 0;
  int fd = 0;
  ScopedPtr_t<Array_t<char> > name;

  Status_t status = filename->ToString(name);
  if(status.IsBad())
  {
    return 0;
  }

  if((!filename.is_set()) || (name->Value() == 0))
  {
    return 0;
  }

  const char* file = name->Value();

  FILE* fp = 0;

#ifdef _WIN32
  errno_t err = fopen_s(&fp, name->Value(), "rb");
  if (err != 0)
  {
    return 0;
  }
#else
  fp = fopen( file, "rb");
#endif  //_WIN32

  if (fp)
  {
    struct stat buf;
#ifdef _WIN32
    if((fd = _fileno(fp)) < 0)
#else
    if ((fd = fileno(fp)) < 0)
#endif  //_WIN32
    {
      fclose(fp);
      return 0;
    }
    fstat(fd, &buf);
    size = buf.st_size;
    fclose(fp);
  }

  return size;
}

bool StdFile_t::Writable(void) const
{
  return writable;
}

uint16_t StdFile_t::OpenCount(void) const
{
  return contexts.Count();
}

Status_t StdFile_t::OpenForReading(uintptr_t& context) const
{
  if(openedForWriting)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
  }

  return OpenFile("rb", false, context);
}

Status_t StdFile_t::Open(bool allowReading,
                         bool allowWriting,
                         bool eraseExisting,
                         bool append,
                         uintptr_t& context)

{
  Status_t status = OpcUa_Good;
  
  if(!writable)
  {
    if(allowWriting || eraseExisting || append)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }
  }

  if(allowReading)
  {
    status = OpenForReading(context);
  }
  else
  {
    if(contexts.Count() > 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
    }
    
    if(eraseExisting)
    {
      status = OpenFile("wb", false, context);
    }

    else if((allowWriting) || (append))
    {
      status = OpenFile("a", append, context);
    }

    else
    {
      status = OpcUa_BadInvalidArgument;
    }

    if(status.IsBad())
    {
      return status;
    }

    openedForWriting = true;
  }

  return status;
}

Status_t StdFile_t::Close(uintptr_t context) const
{
  if((context == 0) || (contexts.Find(context) == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if(fclose((FILE*)context) != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  if(contexts.DeleteSpecific(context) == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  return OpcUa_Good;
}

Status_t StdFile_t::Read(uintptr_t context, int32_t length, ByteString_t& data) const
{
  Status_t status = OpcUa_BadInternalError;

  if((context == 0) || (contexts.Find(context) == 0) || (length == 0) || ((data.Length() != 0) && (data.Length() < length)))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if(data.Length() == 0)
  {
    status = data.Initialise(length);
    if(status.IsBad())
    {
      return status;
    }
  }

  if(length != (int32_t) fread(data.Data(), sizeof(uint8_t), length, (FILE*)context))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  return OpcUa_Good;
}

Status_t StdFile_t::Write(uintptr_t context, const ByteString_t& data)
{
  if((!writable) || (context == 0) || (contexts.Find(context) == 0) || (data.Data() == 0) || (data.Length() == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if(data.Length() != (int32_t) fwrite(data.Data(), sizeof(uint8_t), data.Length(), (FILE*)context))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  return OpcUa_Good;
}

Status_t StdFile_t::GetPosition(uintptr_t context, uint64_t& position) const
{
  if((context == 0) || (contexts.Find(context) == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  long int position_;
  position_ = ftell((FILE*) context);

  if(position_ < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  position = (uint64_t)position_;

  return OpcUa_Good;
}

Status_t StdFile_t::SetPosition(uintptr_t context, uint64_t position) const
{
  if((context == 0) || (contexts.Find(context) == 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  long int size = 0;

  if(fseek((FILE *)context, 0, SEEK_END) != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  size = ftell((FILE *)context);
  if(size < 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  rewind((FILE *)context);

  uint32_t retVal = 0;
  if(position <= (uint64_t) size)
  {
#ifdef _WIN32
    retVal = fseek((FILE *)context, static_cast<long>(position), SEEK_SET);
#else
    retVal = fseek((FILE *)context, position, SEEK_SET);
#endif  //_WIN32
  }
  else
  {
    retVal = fseek((FILE *)context, 0, SEEK_END);
  }

  if(retVal != 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  return OpcUa_Good;
}

} //namespace uasdk

#endif //UASDK_INCLUDE_FILE_WINDOWS_LINUX
