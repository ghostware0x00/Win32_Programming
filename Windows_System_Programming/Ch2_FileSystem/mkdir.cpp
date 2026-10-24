// creating a directory in Windows using Windows functions via Win32
#include <Windows.h>
#include <tchar.h>
#include <iostream>

int _tmain(int argc, LPTSTR argv[]){
    if(argc != 2){
        std::cout << "[!] usage: mkdir.exe <directory_name>" << std::endl;
        return 1;
    }
    /*
    CreateDirectory() is used to create a directory :-
    arguments required :-
    <--------------------->
        BOOL CreateDirectory(
            LPCSTR                lpPathName,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes
        );
    */
    if(!CreateDirectory(argv[1], NULL)){
        if(GetLastError() == ERROR_ALREADY_EXISTS){
            std::cout << "[!] Directory already exists" << std::endl;
        }
        else{
            std::cout << GetLastError() << std::endl;
        }
        return 2;
    }
    return 0;
}