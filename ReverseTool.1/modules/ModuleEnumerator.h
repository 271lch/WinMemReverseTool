#ifndef MODULE_ENUMERATOR_H
#define MODULE_ENUMERATOR_H

#include "../core/IToolCore.h"
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>


class ModuleEnumerator : public IToolCore
{
public:
    bool Init() override;

    void Run() override;

    void Clean() override;

private:
    DWORD targetPid;     
                        
    HANDLE hProcess;    
                        
};

#endif