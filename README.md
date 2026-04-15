
MemReverseTool
中文介绍
MemReverseTool 是 Windows 平台下的内存与进程逆向辅助工具，支持快速读写进程内存、模块分析，可用于游戏辅助开发、软件逆向分析、驱动调试等场景。

核心功能
进程枚举 模块枚举 内存读写

开发信息
开发语言：C++ 支持系统：Windows 10/11 编译环境：MSYS2

编译说明
 g++ -std=c++17 -static -O2 -Wall ./core/IToolCore.cpp ./modules/ProcessEnumerator.cpp ./modules/MemoryEditor.cpp ./modules/ModuleEnumerator.cpp ./main.cpp -o ReverseTool.exe  
 
注意：编译生成的 exe 请在 MSYS2 终端内直接运行，不要双击或在 IDE 终端打开，否则程序执行后会因终端环境差异快速退出

English Introduction
MemReverseTool is a reverse engineering assistant tool for Windows platform, supporting fast reading/writing of process memory and module analysis. It can be used for game auxiliary development, software reverse analysis, driver debugging and other scenarios.

Core Features
Process Enumeration Module Enumeration Process Memory Reading & Writing

Development Information
Development Language: C++ Supported Systems: Windows 10/11 Build Environment: MSYS2

Build Instructions
 g++ -std=c++17 -static -O2 -Wall ./core/IToolCore.cpp ./modules/ProcessEnumerator.cpp ./modules/MemoryEditor.cpp ./modules/ModuleEnumerator.cpp ./main.cpp -o ReverseTool.exe

Note: Run the generated exe directly in the MSYS2 terminal, do not double-click or run it in the IDE terminal, otherwise it will exit quickly
