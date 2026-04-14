
#include "MemoryEditor.h"

bool MemoryEditor::Init() {
    std::cout << "[MemoryEditor] Please enter target PID: ";
    std::cin >> targetPid;

    if (!std::cin) {
        std::cerr << "[MemoryEditor] Error: Invalid PID input!" << std::endl;
        return false;
    }

    hProcess = OpenProcess(
        PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
        FALSE,
        targetPid
    );

    if (hProcess == NULL) {
        std::cerr << "[MemoryEditor] Error: Failed to open process! PID: " << targetPid << std::endl;
        return false;
    }

    std::cout << "[MemoryEditor] Successfully opened process! Handle: " << hProcess << std::endl;
    return true;
}

void MemoryEditor::Run() {
    std::cout << "\n[MemoryEditor] Starting memory operation demo..." << std::endl;

    LPVOID remoteAddr = VirtualAllocEx(
        hProcess,
        nullptr,
        4,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    if (remoteAddr == nullptr) {
        std::cerr << "[MemoryEditor] Error: VirtualAllocEx failed!" << std::endl;
        return;
    }

    std::cout << "[MemoryEditor] Allocated remote memory at: 0x" << std::hex << remoteAddr << std::dec << std::endl;

    int valueToWrite = 123456;
    BOOL writeResult = WriteProcessMemory(
        hProcess,
        remoteAddr,
        &valueToWrite,
        sizeof(int),
        nullptr
    );

    if (writeResult == 0) {
        std::cerr << "[MemoryEditor] Error: WriteProcessMemory failed!" << std::endl;
        VirtualFreeEx(hProcess, remoteAddr, 0, MEM_RELEASE);
        return;
    }

    std::cout << "[MemoryEditor] Wrote value: " << valueToWrite << std::endl;

    int readValue = 0;
    BOOL readResult = ReadProcessMemory(
        hProcess,
        remoteAddr,
        &readValue,
        sizeof(int),
        nullptr
    );

    if (readResult == 0) {
        std::cerr << "[MemoryEditor] Error: ReadProcessMemory failed!" << std::endl;
        VirtualFreeEx(hProcess, remoteAddr, 0, MEM_RELEASE);
        return;
    }

    std::cout << "[MemoryEditor] Read value back: " << readValue << std::endl;

    VirtualFreeEx(hProcess, remoteAddr, 0, MEM_RELEASE);
    std::cout << "[MemoryEditor] Memory operation demo completed." << std::endl;
}

void MemoryEditor::Clean() {
    std::cout << "\n[MemoryEditor] Cleaning up process handle..." << std::endl;
    if (hProcess != NULL) {
        CloseHandle(hProcess);
        hProcess = NULL;
    }
}