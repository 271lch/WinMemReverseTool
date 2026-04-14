
#include "ModuleEnumerator.h"

bool ModuleEnumerator::Init()
{
    std::cout << "[ModuleEnumerator] Enter PID to enumerate modules: ";
    std::cin >> targetPid;

    if (!std::cin)
    {
        std::cerr << "[ModuleEnumerator] Error: Invalid PID!" << std::endl;
        return false;
    }

    hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        targetPid
    );

    if (!hProcess)
    {
        std::cerr << "[ModuleEnumerator] OpenProcess failed." << std::endl;
        return false;
    }

    std::cout << "[ModuleEnumerator] Init success." << std::endl;
    return true;
}

void ModuleEnumerator::Run()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, targetPid);

    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "[ModuleEnumerator] Snapshot failed." << std::endl;
        return;
    }

    MODULEENTRY32 me32 = {0};
    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hSnapshot, &me32))
    {
        CloseHandle(hSnapshot);
        return;
    }

    std::cout << "\n[ModuleEnumerator] === Loaded Modules ===" << std::endl;
    std::cout << "Base Address    Size(KB)    Module Name" << std::endl;

    do
    {
        std::cout << "0x" << std::hex << me32.modBaseAddr
                  << "    " << std::dec << me32.modBaseSize / 1024
                  << " KB    " << me32.szModule << std::endl;
    } while (Module32Next(hSnapshot, &me32));

    CloseHandle(hSnapshot);
    std::cout << "[ModuleEnumerator] Enumerate done." << std::endl;
}

void ModuleEnumerator::Clean()
{
    if (hProcess)
    {
        CloseHandle(hProcess);
        hProcess = NULL;
    }
    std::cout << "[ModuleEnumerator] Cleaned up." << std::endl;
}