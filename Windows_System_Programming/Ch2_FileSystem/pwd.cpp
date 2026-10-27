// we are going to implement the pwd command 
// which would basically print the current working directory path

#include <Windows.h>
#include <tchar.h>
#define DIRNAME_LEN (MAX_PATH + 2) // MAX_PATH is Windows defined macro which is 260 characters


int _tmain(){
    /*
    GetCurrentDirectory() function is used retrieve the current directory of the running process.
    arguments required in GetCurrentDirectory() :-
    <---------------------------------------------->
    DWORD GetCurrentDirectory(
        DWORD  nBufferLength,
        LPTSTR lpBuffer
    );    

    • nBufferLength: The length of the buffer for the current directory string, in TCHARs. This must include room for a terminating null character.
    • lpBuffer: A pointer to the buffer that receives the current directory string. This null-terminated string specifies the absolute path to the current directory.
    */
    DWORD bWrite = 0;
    TCHAR dirBuff[DIRNAME_LEN]; // buffer where the current directory string will be stored
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // based on the path ... that many number of characters are stored inside hOut handle. so for example (C:\Users) path has 8 characters so hOut = 8.
    if(hOut == INVALID_HANDLE_VALUE)
        return 1; // stdout handle not initialized
    DWORD pwd = GetCurrentDirectory(DIRNAME_LEN, dirBuff);
    if(pwd == 0)
        return 2; // failed to get current working directory pathname 
    if(pwd > DIRNAME_LEN)
        return 3; // current working directory pathname too long 
    /*
        WHY WE DID pwd * sizeof(TCHAR)
        in unicode TCHAR becomes wchar_t and in wchar_t each character is of 2 bytes
        so if hOut = 8 characters we need to write twice that amount
        so pwd = 8 and sizeof(TCHAR) = 2 and hence 8 x 2 = 16
    */
    WriteFile(hOut, dirBuff, pwd * sizeof(TCHAR), &bWrite, NULL);
    TCHAR newline = _T('\n'); // here _T() is a macro which becomes _T(wchar_t) in Unicode and _T(ANSII) if Unicode not activated
    WriteFile(hOut, &newline, 1 * sizeof(TCHAR), &bWrite, NULL); // adding newline to display the output a bit clearly
    return 0;
}