// applying basic caesar ciper to a file's contents with a key
// performing basic file encryption


// learn about boost library for command line argument parsing (C++)
#include <Windows.h>
#include <iostream>
#define BUFF_SIZE 256

int generate_key(){
    std::cout << "[*] generating key ..." << std::endl; 
    std::srand(static_cast<unsigned int>(time(0)));
    return rand() % 10;
}


int main(int argc, LPTSTR argv[]){
    if(argc != 2){
        std::cout << "[!] usage: fe.exe filename" << std::endl;
        return 1;
    }
    HANDLE h1;
    h1 = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(h1 == INVALID_HANDLE_VALUE){
        std::wcout << "[!] failed to access " << argv[1] << std::endl;
        std::cout << GetLastError() << std::endl;
        return 2;
    }
    CHAR buffer[BUFF_SIZE];
    DWORD bread = 0, bwritten = 0;
    int key = generate_key();
    std::cout << "[+] key generated" << std::endl;
    std::cout << "[*] encrypting file contents ..." << std::endl;
    while(ReadFile(h1, buffer, BUFF_SIZE, &bread, NULL) && bread > 0){
        // applying the encryption to each character inside the buffer
        for(DWORD i=0; i<bread; i++){
            buffer[i] = static_cast<CHAR>(buffer[i] + key);
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
        LARGE_INTEGER dmov;
        dmov.QuadPart = -static_cast<LONGLONG>(bread); // since we are resetting so we set bread to negative 
        if(!SetFilePointerEx(h1, dmov, NULL, FILE_CURRENT)){
            std::cout << "[!] SetFilePointerEx() failed: "  << GetLastError() << std::endl; 
            return 3;
        }

        // now writing the encrypted content to the file
        if(!WriteFile(h1, buffer, bread, &bwritten, NULL)){
            std::cout << "[!] WriteFile() failed: " << GetLastError() << std::endl;
            return 4;
        }
    }
    std::cout << "[+] file encryption done" << std::endl;
    CloseHandle(h1);
    return 0;
}