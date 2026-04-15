#include <iostream>
#include <windows.h>
#include "core/IToolCore.h"
class ProcessEnumerator;
class MemoryEditor;
class ModuleEnumerator;
class MainController : public IToolCore
{
private:
    ProcessEnumerator* procEnum;
    MemoryEditor* memEditor;
    ModuleEnumerator* modEnum;  
                               

public:
    MainController();
    ~MainController() override;
    bool Init() override;
    void Run() override;
    void Clean() override;
};
#include "modules/ProcessEnumerator.h"
#include "modules/MemoryEditor.h"
#include "modules/ModuleEnumerator.h"

MainController::MainController()
{
    procEnum = new ProcessEnumerator();
    memEditor = new MemoryEditor();
    modEnum = new ModuleEnumerator();
}



MainController::~MainController()
{
    delete procEnum;
    delete memEditor;
    delete modEnum;
}



bool MainController::Init()
{
    std::cout << "[MainController] Reverse Tool Initializing..." << std::endl;
    if (!procEnum->Init()) return false;
    if (!memEditor->Init()) return false;
    if (!modEnum->Init()) return false;
    return true;
}



void MainController::Run()
{
    std::cout << "\n[MainController] Reverse Tool Running..." << std::endl;

    std::cout << "\n[MainController] ==== Stage 1: Process Enumeration ====" << std::endl;
    procEnum->Run();

    std::cout << "\n[MainController] ==== Stage 2: Memory Editor ====" << std::endl;
    memEditor->Run();

    std::cout << "\n[MainController] ==== Stage 3: Module Enumerator ====" << std::endl;
    modEnum->Run();
}

void MainController::Clean()
{
    std::cout << "\n[MainController] Reverse Tool Cleaning Up..." << std::endl;
    procEnum->Clean();
    memEditor->Clean();
    modEnum->Clean();
}

int main()
{
    IToolCore* controller = new MainController();
    if (!controller->Init())
    {
        delete controller;
        std::cout << "\nInit failed, press ENTER to exit..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        return -1;
    }
    controller->Run();
    controller->Clean();
    delete controller;
    std::cout << "\n[MainController] All tasks done, press ENTER to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    return 0;
}