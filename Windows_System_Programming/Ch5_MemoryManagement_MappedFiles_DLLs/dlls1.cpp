#include <Windows.h>
#include <iostream>


int wmain(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWritten = 0;
    /*
        Learning how to load a DLL file
        And printing the starting address of the exported function inside the DLL 
        And freeing the dll after use
    */
    
    // HMODULe is a handle to a DLL module
    HMODULE loadDll = LoadLibraryW(L"user32.dll"); //loading dll
    if(loadDll == nullptr){
        const wchar_t* errMsg = L"[!] failed to load library\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        return 1;
    }
    
    const wchar_t* msg = L"[+] loaded user32.lib\n";
    WriteFile(hOut, msg, lstrlenW(msg) * sizeof(wchar_t), &bWritten, NULL);
    
    /*
    
    printing the starting address of the exported function inside the user32.dll
    
    FARPROC is a generic function pointer ... like void* so we need to typecast it to the address value returned by that exported function. when we are trying to get a value the computer needs to perform some arithmetic on it but void* means nothing so we typecast it.


    typecasting is also necessary because lets say we call a function which requires arguments but since getprocaddress returns void* which takes no arguments so during calling that function it will cause compile time error

    since we are just printing the raw address of that function we dont need to typecast in this scenario
    */
    FARPROC funcAddr = GetProcAddress(loadDll, "MessageBoxW");
    std::wcout << "[*] user32.dll base address: " << loadDll << std::endl;
    /*
        std::wcout would silently convert the function's address to 1 because of the BOOL TRAP.
        When we pass a function to std::cout or std::wcout it doesn't have C's printf's (void*) inbuilt so wcout/cout checks whether the function's address is non zero and if true print 1 else 0.
    */
    std::wcout << "[*] MessageBoxW() function starting address: " << (void*) funcAddr << std::endl;  
    return 0;
}