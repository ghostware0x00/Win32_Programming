// we are going to use the SetFilePointerEx() function which uses 64 bit
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#define BUFF_SIZE 256

int _tmain(int argc, LPTSTR argv[]){
    if(argc != 2){
        _tprintf(_T("[!] Usage: fileptr.exe filename")); // _tprintf() comes with code portability. Depending on the environment (Unicode or ANSII) the printf becomes wprintf or remains printf
        return 1;
    }
    HANDLE hIn = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hIn == INVALID_HANDLE_VALUE){
        _tprintf(_T("[!] cannot acess %s\n. Error %lu\n"), argv[1], GetLastError());
        return 2;
    }
    /*
        the file pointer will move after reading the section we just read previously
        so we need to move the file pointer back to its previous position so that we can encrypt those file contents with buffer + key
    */
    /*
        to write the encrypted contents we need to reset our filepointer so we need to use SetFilePointerEx() :-
        arguments required by SetFilePointerEx :-
        <----------------------------------------->
        BOOL SetFilePointerEx(
            HANDLE         hFile,          // 1. The handle to your open file
            LARGE_INTEGER  liDistanceToMove, // 2. How many bytes to move (64-bit)
            PLARGE_INTEGER lpNewFilePointer, // 3. Variable to store the new position (Optional)
            DWORD          dwMoveMethod    // 4. Starting point for the move
        );
    
        • .LowPart: The lower 32 bits of the number (unsigned).
        • .HighPart: The higher 32 bits of the number (signed).
        • .QuadPart: The entire 64-bit signed integer as a single value.
    */
    LARGE_INTEGER distance; // distance or number of bytes to move the filepointer
    distance.QuadPart = 7;
    if(!SetFilePointerEx(hIn, distance, NULL, FILE_CURRENT)){
        _tprintf(_T("[!] SetFilePointerEx() failed. Error %lu\n"), GetLastError());
        return 3;
    }
    CHAR buff[BUFF_SIZE];
    DWORD bread = 0, bwrite = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    while(ReadFile(hIn, buff, BUFF_SIZE, &bread, NULL)&& bread > 0){
        WriteFile(hOut, buff, bread, &bwrite, NULL); // stdout will show : bose hello world because we moved past 7 bytes using SetFilePointerEx()
    }
    return 0;
}


