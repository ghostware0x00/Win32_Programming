#include <Windows.h>
#include <iostream>


int wmain(){
    /*
        in CreateFileMapping() we either name a real file or share a temporary block of RAM
        So in the first argument of CreateFileMapping() will be the handle of the file you opened using CreateFile() or just INVALID_HANDLE_VALUE if you are not trying to open a file ... probably just allocate a random block in the RAM.
    */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWritten = 0;
    const wchar_t* mmf = L"myMap"; // name of the kernel file mapping object. allocates a random block in the RAM which is shared by the specified processes. The first argument in the CreateFileMappingW() is either the name of the file or nothing. You first CreateFile() and get a handle of that file and then use CreateFileMapping() + kernel file object with get an handle which is again used with MapViewOfFile() to map that file data to you process's virtual memory or if its just a block of memory you can read or write it and other processes can access it and do the same.
    DWORD buffSize = 256; 
    HANDLE hfo = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, buffSize, mmf); // creating the file object
    // giving PAGE_READWRITE allows other processes to perform read/write operations
    // 0 is the max higher order bits
    if(hfo == INVALID_HANDLE_VALUE){
        const wchar_t* errMsg = L"[!] memory file mapping creation failed\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        CloseHandle(hfo);
        return 1;
    }
    // mapping the file object to the process's virtual memory address
    // FILE_MAP_ALL_ACCESS = gives read/write access to the current process on that virtual address range
    LPVOID hmo = MapViewOfFile(hfo, FILE_MAP_ALL_ACCESS, 0, 0, buffSize);
    if(hmo == nullptr){
        const wchar_t* errMsg = L"[!] failed to map file object to current process's virtual memory address\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        CloseHandle(hfo);
        return 3;
    }
    const wchar_t* msg = L"[*] new message from Producer: Calling all Autobots!";
    std::memcpy(hmo, msg, lstrlenW(msg) * sizeof(wchar_t));
    const wchar_t* newMsg = L"[*] message written to virtual address\n";
    WriteFile(hOut, newMsg, lstrlenW(newMsg) * sizeof(wchar_t), &bWritten, NULL);
    std::cin.get();
    UnmapViewOfFile(hmo);
    hmo = nullptr;
    CloseHandle(hfo);
    return 0;
}