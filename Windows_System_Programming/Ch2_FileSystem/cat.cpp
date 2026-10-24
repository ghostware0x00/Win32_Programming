#include <Windows.h>
#include <iostream>
#define BUFF_SIZE 256

int _tmain(int argc, LPTSTR argv[]){
    // implementing the "cat" command using Windows win32 programming
    if(argc != 2){
        std::cout << "[!] usage: cat.exe filename" << std::endl;
        return 1;
    }
    /* 
        to implement the "cat" command in Windows we will use the following Windows function
        HANDLE GetStdHandle(DWORD nStdHandle)

        nStdHandle might have one the below values :-
        -> STD_INPUT_HANDLE
        -> STD_OUTPUT_HANDLE
        -> STD_ERROR_HANDLE

        what does each value mean ?
        <---------------------------->
        • STD_OUTPUT_HANDLE: Retrieves the handle for the standard output buffer (your console's text display screen).
        • STD_INPUT_HANDLE: Retrieves the handle for the standard input buffer (your console's keyboard input).
        • STD_ERROR_HANDLE: Retrieves the handle for the standard error buffer.


        Return Values

        • Valid Handle: If successful, it returns an active OS handle to the requested stream.
        • INVALID_HANDLE_VALUE: If the function fails, it returns this error value. You can call GetLastError() to find out why.
        • NULL: If the application does not have associated standard handles (such as a standard graphical Windows GUI app running without a detached console), it returns NULL.
    */
    HANDLE h1, h2;
    h1 = GetStdHandle(STD_OUTPUT_HANDLE); // handle to display the file content as stdout
    h2 = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // accessing the file to read its contents
    if(h2 == INVALID_HANDLE_VALUE){
        std::wcout << "[!] failed to access " << argv[1] << std::endl;
        std::cout << GetLastError() << std::endl;
        return 2;
    }
    CHAR buff[BUFF_SIZE];
    DWORD bytesRead;
    DWORD bytesWritten;
    /*
        so each iteration we get 256 characters
        and the previous buff gets overwritten with the new buff characters
    */
    while(ReadFile(h2, buff, BUFF_SIZE, &bytesRead, NULL) && bytesRead > 0){
        WriteFile(h1, buff, bytesRead, &bytesWritten, NULL);
        if(bytesRead != bytesWritten){
            std::cout << "[!] fatal write" << std::endl;
            std::cout << GetLastError() << std::endl;
            return 3;
        }
    }
    //CloseHandle(h1); since OS manages the lifecycle of standard handles we don't need to close it explicitly
    /*
        The reason we dont' close standard handles because these standard handles like stdout and stuff are used by other processes
        like for stdout or printing something on the screen printf is used. This handle is used by almost every other handle. Closing this sort of handle
        would result in malfunctioning of the other functions 
    */
    CloseHandle(h2);
    return 0;
}