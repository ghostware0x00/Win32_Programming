#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(){
    /*
        We are going to be working with Window Registry
        In this program we will learn to use RegOpenEx() function
        RegOpenEx() function is used to open Windows Registry key. These Registry keys can contain other subkeys which can contain other specific configuration settings.
        arguments required by RegOpenEx() are:-
        <--------------------------------------->
        LSTATUS RegOpenKeyExW(
            HKEY    hKey,
            LPCWSTR lpSubKey,
            DWORD   ulOptions,
            REGSAM  samDesired,
            PHKEY   phkResult
        );

        • HKEY hkey
            • handle top open a registry.
        • LPCWSTR lpSubKey
            • pointer to a null terminated string containing name of the registry subkey to open. This is case-insensitive. 
              If this parameter is NULL, or empty string, then the function will open another handle to be represented by the hkey.
        • DWORD ulOptions 
            • Specifes the options to apply when opening the registry.
              This is reserved and must be set to 0, or REG_OPTION_OPEN_LINK
        • REGSAM samDesired
            • defines the access rights, or permission rights of the registry key.
              Common values include KEY_READ, KEY_WRITE, or KEY_ALL_ACCESS.
        • PHKEY phkResult
            • pointer to an HKEY. 
              we use the address of hKey(phkey) so that when the function (RegOpenKeyEx) makes a change to hKey (by filling it with the ticket number), 
              so that change is reflected back in your main program.
              the reason we need to pass the address of the hkey because the RegOpenKeyEx() is already returning a status code of success or failure so it needs a way to send the data of the result and a program in c/c++ cannot return more than 1 thing at a time so ... we gotta pass the address of hkey

        RETURN VALUES
        Unlike many Win32 functions, RegOpenKeyEx does not return a boolean or set GetLastError(). Instead, it directly returns an LSTATUS (long integer) error code:
        • ERROR_SUCCESS (0): The function succeeded.
        • ERROR_FILE_NOT_FOUND (2): The specified registry key does not exist.
        • ERROR_ACCESS_DENIED (5): The calling process lacks the required permissions specified in samDesired

        also since we are using or handling Windows Registry so we need to add the Advapi32.lib
    */
    HKEY hKey = HKEY_LOCAL_MACHINE; // predefined root key
    const TCHAR* subkey = _T(R"(SOFTWARE\Microsoft\Windows\CurrentVersion)"); // since the path involves backslashes(\) so we add the subkey path in R"()" (raw strings) present in c++11
    LSTATUS status = RegOpenKeyEx(hKey, subkey, 0, KEY_READ, &hKey);
    if(status == ERROR_SUCCESS){
        _tprintf(_T("[+] successfully opened registry key"));
        RegCloseKey(hKey);
    }
    else if(status == ERROR_ACCESS_DENIED)
        _ftprintf(stderr, _T("[!] failed to open registry key. Access denied\n"));
    else if(status == ERROR_FILE_NOT_FOUND)
        _ftprintf(stderr, _T("[!] failed to open registry key. The specified registry file path doesn't exist\n"));
    else
        _ftprintf(stderr, _T("error\n"));
    return 0;
}