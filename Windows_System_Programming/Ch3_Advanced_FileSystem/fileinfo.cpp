#include <Windows.h>
#include <tchar.h>
#include <iostream>

// we are going to gather file information in this program using GetFileAttributesEx
int _tmain(int argc, LPTSTR argv[]){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWrite = 0;
    if(argc != 2){
        TCHAR errMsg[] = _T("[!]Usage: fileinfo.exe <FILENAME/DIRECTORY_NAME>");
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
        return 1;
    }
    /*
        GetFileAttributesEx() is used to find out the following stuff :-
        - filesize when last modified.
        - checking files stored on remote network shares or NAS Drives
        BOOL result = GetFileAttributesExW(
            filePath,                  // 1st Argument: The target path (File or Directory)
            GetFileExInfoStandard,     // 2nd Argument: The info level flag (Must be this value)
            &attributeData             // 3rd Argument: Output memory address to store metadata
        );
        
        • lpFileName [In]
            • Absolute path or relative path of the file
        • fInfoLevelId [In]
            • Type: GET_FILEEX_INFO_LEVELS (Enumeration)
            • Purpose: Determines what structure to populate. Must be passed as GetFileExInfoStandard.
        • lpFileInformation [Out]
            • Type: LPVOID (Pointer to void)
            • Purpose: The memory pointer to receive the data. You must pass the address of a allocated WIN32_FILE_ATTRIBUTE_DATA structure (&attributeData).
    */
    WIN32_FILE_ATTRIBUTE_DATA fileAttribute; // win32 api structure that acts as a container for a file and directory's core metadata 
    /*
        typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
            DWORD    dwFileAttributes; // contains info about a file like hidden, read-only ...etc...
            FILETIME ftCreationTime;   
            FILETIME ftLastAccessTime;
            FILETIME ftLastWriteTime;   
            DWORD    nFileSizeHigh;
            DWORD    nFileSizeLow;
        } WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
    */
    if(!GetFileAttributesEx(argv[1], GetFileExInfoStandard, &fileAttribute)){
        TCHAR errMsg[] = _T("[!] fileinfo failed");
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
        return 2;
    }
    /* 
        GetFileAttributesEx() fills the fileAttribute WIN32_FILE_ATTRIBUTE_DATA struct with the file metadata
        now we need to fill display the info accordingly
    */

    // file type detection (dwFileAttributes)
    if(fileAttribute.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // FILE_ATTRIBUTE_DIRECTORY is a windows constant for directory 
        _tprintf(_T("Type: directory\n"));
    else
        _tprintf(_T("Type: file\n"));
    
    // display file size 
    ULARGE_INTEGER fileSize;
    // modern file sizes can become more than 32 bit i.e more than 4 GB thats why we have .LowPart and .HighPart
    // the .LowPart and .HighPart are combined together to align the 64 bit value perfectly
    fileSize.LowPart = fileAttribute.nFileSizeLow;
    fileSize.HighPart = fileAttribute.nFileSizeHigh;
    _tprintf(_T("Size: %llu bytes\n"), fileSize.QuadPart); // llu for long long unsigned 64 bit memory representation
    FILETIME localFileTime; // Windows created structure to store time as a 64 bit raw integer based on UTC timeline since 1st January 1601
    SYSTEMTIME sysTime; // a strcture broken down into fields which can be read easily by humans like years, months, days, hours, minutes, seconds ...etc...
    /*
        Windows writes tracks the file using UTC timeline
        Convertion last write time from utc to local file time, then to system time
    */
    if(FileTimeToLocalFileTime(&fileAttribute.ftLastWriteTime, &localFileTime) && FileTimeToSystemTime(&localFileTime, &sysTime)){
        /* 
            FileTimeToLocalFileTime() :- 
            <---------------------------->
            arg1 -> requires memory address of UTC timestamp which we pullfrom fileAttribute.ftLastWriteTime
            arg2 -> the blank FILETIME variable where the function will write the 64 bit integer

            FileTimeToSystemTime() :-
            <------------------------->
            arg1 -> requires memory address of the FILETIME structure where the function will write the timezone adjusted 64 bit integer
            arg2 -> the memory address of a blank SYSTEMTIME struct variable where the system time will be stored

            The if checking is to check whether both the functions completed their working correctly or not
        */
        _tprintf(_T("Last Modified: %04d-%02d-%02d %02d:%02d:%02d\n"),
            sysTime.wYear, sysTime.wMonth, sysTime.wDay,
            sysTime.wHour, sysTime.wMinute, sysTime.wSecond
        );
    }
    return 0;
}