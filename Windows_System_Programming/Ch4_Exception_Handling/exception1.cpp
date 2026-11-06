// learning how to use Exception Handling in Windows

#include <Windows.h>
#include <tchar.h>

int _tmain(){
    /*
        In this code we are going to learn about GetExceptionCode() windows function
        The GetExceptionCode function (which is actually a compiler intrinsic macro in Win32) takes zero arguments.
        <------------------------------->
        DWORD GetExceptionCode(void);

        We can only use this exception inside a _try and _except block otherwise we will get error code
    */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWrite = 0;
    _try{
        int a = 10; // numerator
        int b = 0; // denominator is 0 
        int result = a / b; // so we will get an error here so to handle that we will use exception handling
    }
    /* 
        GetExceptionCode() in this scenario gives an error code of 0xC0000094 which matches the EXCEPTION_INT_DIVIDE_BY_ZERO
        EXCEPTION_EXECUTE_HANDLER states Windows that => "I recognize this error, and I have a block of code ready to handle it."
        EXCEPTION_CONTINUE_SEARCH states Windows that => "I don't know what this error is, or I don't want to deal with it." this means windows essentially skips this without causing any compile time error
    */
    _except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH){
        TCHAR errMsg[] = _T("numerator cannot be divided by 0\n");
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
    }
    return 0;
}