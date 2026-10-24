// implementing Windows equivalent of mv command which is in Linux
// This will help was to rename or move a file to a new location.

#include <Windows.h>
#include <iostream>

int _tmain(int argc, LPTSTR argv[]){
    #ifdef UNICODE
        std::cout << "[i] The compiler is using UNICODE mode." << std::endl;
    #else
        std::cout << "[i] The compiler is using ANSI/ASCII mode." << std::endl;
    #endif
        return 0;
    if(argc != 3){
        std::cout << "[!] usage: mv.exe file1 file2" << std::endl;
        return 1;
    }
    /*
        We are going to use the MoveFileEx() function instead of MoveFile() because 
        MoveFileEx() can overrite the newfile which is existing with the file we are tryint to move or rename
        wherease MoveFile() would fail to rename a file with a name that's already exisiting

        arguments required by MoveFileEx() :-
        <------------------------------------->
        BOOL MoveFileEx(
            LPCWSTR lpExistingFileName, // [in] Path to the existing file or directory
            LPCWSTR lpNewFileName,      // [in] New path or name (can be NULL for deletions)
            DWORD   dwFlags             // [in] Move options (flags)
        );

        1. lpExistingFileName: The path to the file or directory you want to move or rename.
        2. lpNewFileName: The target path.
            • If you are moving a file, this must be a new path.
            • If you are using the MOVEFILE_DELAY_UNTIL_REBOOT flag to delete a file on restart, this argument must be NULL.
        3. dwFlags: One or more bitwise flags (|) that tell Windows how to handle the move.
    */
    if(!MoveFileEx(argv[1], argv[2], NULL)){
        std::wcout << "[!] failed to move or rename " << argv[1] << std::endl;
        return 2;
    }
    return 0;
}