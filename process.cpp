#include "pcx/process.h"

#include <vector>
#include <cstring>
#include <windows.h>

int pcx::process::execute(const std::string &command)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    std::vector<char> cmd(command.length() + 1);
    std::memcpy(cmd.data(), command.data(), cmd.size());

    CreateProcess(nullptr, cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD code;
    GetExitCodeProcess(pi.hProcess, &code);

    return static_cast<int>(code);
}
