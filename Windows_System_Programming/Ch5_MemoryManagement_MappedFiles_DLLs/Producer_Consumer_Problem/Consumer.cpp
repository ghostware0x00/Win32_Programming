#include <Windows.h>
#include <iostream>


int wmain(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWritten = 0;
    DWORD buffSize = 256;
    const wchar_t* mmf = L"myMap"; // same name of file object as the Producer object
    HANDLE hOfm = OpenFileMappingW(FILE_READ_ACCESS, FALSE, mmf);
    if(hOfm == INVALID_HANDLE_VALUE){
        const wchar_t* errMsg = L"[!] failed to open mapped file object\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        return 1;
    }
    LPVOID hMvf = MapViewOfFile(hOfm, FILE_MAP_READ, 0, 0, buffSize);
    if(hMvf == nullptr){
        const wchar_t* errMsg = L"[!] failed to map file object to current process's virtual memory address\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        CloseHandle(hOfm);
        return 1;
    }
    std::cout << "[*] mapped at virtual address: " << hMvf << std::endl;
    std::wcout << "[+] message received: " << static_cast<const wchar_t*>(hMvf) << std::endl;
    CloseHandle(hOfm);
    UnmapViewOfFile(hMvf);
    return 0;
}