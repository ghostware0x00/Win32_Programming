#include <Windows.h>
#include <iostream>

int wmain(){
    // HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // HANDLE hp = GetCurrentProcess();
    DWORD newPID;
    std::wcout << "Enter the PID of the process to terminate: ";
    std::cin >> newPID;
    DWORD pid = GetCurrentProcessId();
    /*
        printing the below handles was a way to check what gets printed. 
        this has nothing to do with the current program just an experiment.
    */
    // std::wcout << "Current Process HANDLE: " << hp << std::endl;
    // std::wcout << "stdout handle: " << hOut << std::endl;
    std::wcout << "Current Process ID: " << pid << std::endl;

    // getting handle of another processs and terminating it
    // so we created a process handle of an exisiting process so that we can terminate it.

    // this np handle is only used to terminate the process of the PID we mention
    HANDLE nP = OpenProcess(PROCESS_TERMINATE, FALSE, newPID);
    if(nP == INVALID_HANDLE_VALUE){
        std::wcout << "[!] failed to open the process" << newPID << std::endl;
        return 2;
    }
    if(!TerminateProcess(nP, 1)){
        std::wcout << "[!] failed to terminate the process" << std::endl;
        return 3;
    }
    std::wcout << "[*] process terminated successfully" << std::endl;
    CloseHandle(nP);
    return 0;
}