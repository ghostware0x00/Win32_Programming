// using CopyFile() instead of manually Creating, Reading, Writing on a file
#include <Windows.h>
#include <tchar.h>
#include <iostream>

int _tmain(int argc, LPTSTR argv[]){
    /*
        CopyFile() is used to copy an existing file on Windows Operating System to another file(destination file).
        arguments required by CopyFile() :-
        <------------------------------------>
        BOOL CopyFile(
            LPCTSTR lpExistingFileName,
            LPCTSTR lpNewFileName,
            BOOL    bFailIfExists
        );

        1. lpExistingFileName (String)
            • Purpose: The path to the existing (source) file.
            • Character Limit: Limited to MAX_PATH (260 characters) by default. You can extend this limit to 32,767 characters by using Unicode (CopyFileW) and prepending the path with \\?\.
        2. lpNewFileName (String)
            • Purpose: The path to the new (destination) file.
            • Character Limit: Same character limits and path formatting options as the source file.
        3. bFailIfExists (Boolean)
            • Purpose: Dictates how the function acts if a file with the destination name already exists.
            • TRUE: The function fails immediately if the destination file already exists.
            • FALSE: The function overwrites the destination file if it already exists.

        Return Value

        • Returns non-zero (TRUE) if the copy succeeds.
        • Returns zero (FALSE) if the copy fails. To get extended error information (like ERROR_FILE_NOT_FOUND or ERROR_ACCESS_DENIED), you must call GetLastError().
    */
    if(argc != 3){
        std::cout << "[!] Usage: cf.exe file1 file2" << std::endl;
        return -1;
    }
    // CopyFile becomes CopyFileA() and accpets ANSI strings const char* cuz UNICODE is undefined
    if(!CopyFile(argv[1], argv[2], FALSE)){
        std::cout << "[!] CopyFile Error : " << GetLastError() << std::endl;
        return -2;
    }
    return 0;
}