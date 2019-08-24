#include "pcx/filesys.h"

#include <windows.h>

bool pcx::filesys::exists(const std::string &path)
{
    DWORD attr = GetFileAttributesA(path.c_str());
    return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

std::vector<std::string> pcx::filesys::find_files(const std::string &path)
{
    std::vector<std::string> v;

    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(path.c_str(), &fd);

    if(hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                std::string s(fd.cFileName);
                v.push_back(s);
            }
        }
        while(FindNextFile(hFind, &fd));

        FindClose(hFind);
    }

    return v;
}
