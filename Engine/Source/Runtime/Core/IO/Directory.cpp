#include "Directory.h"


NAMESPACE_BEGIN(Engine)
Bool Directory::Create(const Path& path)
{
    if (Exist(path))
        return false;

    std::filesystem::create_directory(path);
    return true;
}

Bool Directory::Delete(const Path& path)
{
    if (!Exist(path))
        return false;

    std::filesystem::remove_all(path);
    return true;
}

Bool Directory::Exist(const Path& path)
{
    return std::filesystem::directory_entry(path).is_directory();
}

Bool Directory::Move(const Path& from, const Path& to)
{
    if (!Exist(from) || Exist(to))
        return false;

    std::filesystem::rename(from, to);
    return true;
}
NAMESPACE_END(Engine)
