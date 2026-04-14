
#ifndef PROCESS_ENUMERATOR_H
#define PROCESS_ENUMERATOR_H

#include "../core/IToolCore.h"
#include <windows.h>
#include <tlhelp32.h>


class ProcessEnumerator : public IToolCore {
public:
    bool Init() override;

    void Run() override;

    void Clean() override;

private:
    HANDLE hProcessSnapshot; // Process snapshot handle
                           
};

#endif