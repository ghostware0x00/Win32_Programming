#include <Windows.h>
#include <tchar.h>

// trying to find the filesize using windows function
int _tmain(int argc, LPTSTR argv[]){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWrite = 0;
    if(argc != 2){
        TCHAR errMsg[] = _T("[!] Usage: filesize.exe filename");
        /*
            _tcslen() counts number of characters and sizeof() calculates number of bytes
            now in unicode we have TCHAR = wchar_t which is 2 bytes so we need to write bytes 2 times or twice the size
            also _tcslen(errMsg) and sizeof(TCHAR) evaluates to size_t which is 64 bit but the arg expects DWORD = 32 bit so explicitly typecast it
        */
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
        return 1;
    }
    /*
        Using windows GetFileSize() we retrieve the uncompressed size of a specified file in bytes.
        arguments required by the GetFileSize :-
        <---------------------------------------->
        DWORD GetFileSize(
            HANDLE  hFile,
            LPDWORD lpFileSizeHigh
        );

        • hFile (Input): A valid open HANDLE to the file (typically created using CreateFile). The handle must have at least read or write access.
        • lpFileSizeHigh (Output / Optional): A pointer to a DWORD variable where the high-order 32 bits of a 64-bit file size will be stored.
            • If your target files will never exceed 4 GB, you can pass NULL.
            • If the file is larger than 4 GB, you must pass a valid pointer to capture the full size
    */
    HANDLE h1 = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(h1 == INVALID_HANDLE_VALUE){
        bWrite = 0;
        TCHAR errMsg[] = _T("[!] couldn't access file");
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
        return 2;
    }
    DWORD fileSize = GetFileSize(h1, NULL);
    if(fileSize == INVALID_FILE_SIZE){
        bWrite = 0;
        TCHAR errMsg[] = _T("[!] error retrieving filesize");
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
        return 3;
    }
    CloseHandle(h1);
    bWrite = 0;
    /*
        we cannot directly send the DWORD filesize to WriteFile() or console output because it will interpret the data wrong because of the following reason
        lets say the file has 65 bytes which is 0x41 in hex
        so writefile takes DWORD which is 4 bytes (0x41 0x00 0x00 0x00) and sends them to console output
        console sees those 4 bytes and tries to map them to ASCII
        0x41 = 'A' in ASCII and we see nothing on the screen because after 0x41 we have 0x00 which is null terminator for string
        when sending data to the windows console engine (conhost.exe) the console's only job is to display text
        so the console interprets every value as a string

        the above are the reasons why we need to use wsprintf
        also wsprintf is part of the user32.lib so add it to linker when compiling
        arguments required by wsprintf():
        <--------------------------------->
        int wsprintf(
            LPTSTR  lpOut,    // Argument 1: Destination Buffer
            LPCTSTR lpFmt,    // Argument 2: Format String
            ...               // Argument 3+: Variables to format
        );
    */
    TCHAR buff[64];
    int numberofchars = wsprintf(buff, _T("File Size: %lu bytes\n"), fileSize);
    WriteFile(hOut, &buff, (DWORD)numberofchars * sizeof(TCHAR), &bWrite, NULL);
    return 0;
}