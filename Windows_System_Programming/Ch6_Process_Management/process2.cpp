#include <Windows.h>
#include <iostream>

int wmain(){
    // HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // HANDLE hp = GetCurrentProcess();
    DWORD pid = GetCurrentProcessId();
    /*
        printing the below handles was a way to check what gets printed. 
        this has nothing to do with the current program just an experiment.
    */
    // std::wcout << "Current Process HANDLE: " << hp << std::endl;
    // std::wcout << "stdout handle: " << hOut << std::endl;
    std::wcout << "Current Process ID: " << pid << std::endl;
    return 0;
}