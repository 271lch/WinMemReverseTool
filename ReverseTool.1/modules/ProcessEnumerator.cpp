
#include "ProcessEnumerator.h"
#include <iostream>

bool ProcessEnumerator::Init() {
    std::cout << "[ProcessEnumerator] Initializing process snapshot..." << std::endl;
    hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "[ProcessEnumerator] Failed to create snapshot!" << std::endl;
        return false;
    }
    return true;
}

void ProcessEnumerator::Run() {
    std::cout << "\n[ProcessEnumerator] Running process list:" << std::endl;
    std::cout << "PID\tProcess Name" << std::endl;
    std::cout << "------------------------" << std::endl;

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnapshot, &pe32)) {
        std::cerr << "[ProcessEnumerator] Failed to get first process!" << std::endl;
        return;
    }

    do {
        std::cout << pe32.th32ProcessID << "\t" << pe32.szExeFile << std::endl;
    } while (Process32Next(hProcessSnapshot, &pe32));

    std::cout << "[ProcessEnumerator] Enumeration completed." << std::endl;
}

void ProcessEnumerator::Clean() {
    std::cout << "[ProcessEnumerator] Cleaning up snapshot..." << std::endl;
    if (hProcessSnapshot != INVALID_HANDLE_VALUE) {
        CloseHandle(hProcessSnapshot);
        hProcessSnapshot = INVALID_HANDLE_VALUE;
    }
}