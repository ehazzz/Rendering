#include "File.h"

#include <fstream>


NAMESPACE_BEGIN(Engine)
Bool File::Delete(const Path& path)
{
    if (!Exist(path))
        return false;

    std::filesystem::remove(path);
    return true;
}

Bool File::Exist(const Path& path)
{
    return std::fstream(path, std::ios::in).is_open();
}

SizeType File::GetSize(const Path& path)
{
    return std::filesystem::file_size(path);
}

Bool File::Move(const Path& from, const Path& to)
{
    if (!Exist(from) || Exist(to))
        return false;

    std::filesystem::rename(from, to);
    return true;
}

Void File::ReadAllBytes(Void** outputBuffer, SizeType* outputByteCount, const Path& path)
{
    SizeType byteCount = GetSize(path);
    Void* buffer = Allocator::Allocate<Byte>(byteCount);

    std::fstream fileStream(path, std::ios::in | std::ios::binary);
    fileStream.read(Cast<Char*>(buffer), byteCount);

    // output
    {
        *outputBuffer = buffer;
        *outputByteCount = byteCount;
    }
}

Buffer File::ReadAllBytes(const Path& path)
{
    Void* buffer = nullptr;
    SizeType byteCount = 0;
    ReadAllBytes(&buffer, &byteCount, path);

    return Buffer{ buffer, byteCount };
}

Void File::WriteAllBytes(const Void* buffer, SizeType byteCount, const Path& path)
{
    std::fstream fileStream(path, std::ios::out | std::ios::binary | std::ios::trunc);
    fileStream.write((Char*)buffer, byteCount);
}

Void File::WriteAllBytes(const Buffer& buffer, const Path& path)
{
    WriteAllBytes(buffer.GetBuffer(), buffer.GetByteCount(), path);
}
NAMESPACE_END(Engine)