
#ifndef MEMORY_EDITOR_H
#define MEMORY_EDITOR_H

#include "../core/IToolCore.h"
#include <windows.h>
#include <iostream>

class MemoryEditor : public IToolCore {
public:
    bool Init() override;

    void Run() override;

    void Clean() override;

private:
    HANDLE hProcess; 
                    
    DWORD targetPid; 
                    
};

#endif