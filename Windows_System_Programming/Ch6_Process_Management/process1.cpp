#include <Windows.h>

int wmain(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWritten = 0;
    STARTUPINFOW sI = {0}; // this structure must be initialized to 0 otherwise the process will not open
    /*
        STARTUPINFO datatype in Windows is used to specify the appearence of the main window of the newly created process.
        STARTUPINFO structure
        <--------------------->
        typedef struct _STARTUPINFOA {
            DWORD  cb;              // Size of the structure, in bytes (must be initialized!)
            LPSTR  lpReserved;      // Reserved; must be NULL
            LPSTR  lpDesktop;       // Name of the desktop/window station
            LPSTR  lpTitle;         // Console window title
            DWORD  dwX;             // Initial X position of the window (in pixels)
            DWORD  dwY;             // Initial Y position of the window (in pixels)
            DWORD  dwXSize;         // Initial width of the window (in pixels)
            DWORD  dwYSize;         // Initial height of the window (in pixels)
            DWORD  dwXCountChars;   // Screen buffer width (in character columns) for console
            DWORD  dwYCountChars;   // Screen buffer height (in character rows) for console
            DWORD  dwFillAttribute; // Initial text and background colors for console
            DWORD  dwFlags;         // Bitfield determining which fields above are actually used
            WORD   wShowWindow;     // How the window is shown (e.g., SW_HIDE, SW_MAXIMIZE)
            WORD   cbReserved2;     // Reserved; must be 0
            LPBYTE lpReserved2;     // Reserved; must be NULL
            HANDLE hStdInput;       // Handle for standard input
            HANDLE hStdOutput;      // Handle for standard output
            HANDLE hStdError;       // Handle for standard error
        } STARTUPINFOA, *LPSTARTUPINFOA;
    */
    PROCESS_INFORMATION pI;
    /*
        PROCESS_INFORMATION structure contains the below data members
        <------------------------------------------------------------->
        typedef struct _PROCESS_INFORMATION {
            HANDLE hProcess;
            HANDLE hThread;
            DWORD  dwProcessId;
            DWORD  dwThreadId;
        } PROCESS_INFORMATION, *PPROCESS_INFORMATION, 

    */
    const wchar_t* processName = L"C:\\Windows\\System32\\notepad.exe";
    if(!CreateProcessW(processName, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sI, &pI)){
        const wchar_t* errMsg = L"[!] failed to create process\n";
        WriteFile(hOut, errMsg, lstrlenW(errMsg) * sizeof(wchar_t), &bWritten, NULL);
        return 1;
    }
    // closing the process handle or threads doesnt terminate the process
    // we still need to call the TerminateProcess() to close the process
    // this just closes the handle which references the process but NOT THE PROCESS ITSELF
    CloseHandle(pI.hProcess);
    CloseHandle(pI.hThread);
    return 0;
}