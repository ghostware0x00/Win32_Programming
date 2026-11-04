#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, LPTSTR argv[]){
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

        RETURN VALUES
        Unlike many Win32 functions, RegOpenKeyEx does not return a boolean or set GetLastError(). Instead, it directly returns an LSTATUS (long integer) error code:
        • ERROR_SUCCESS (0): The function succeeded.
        • ERROR_FILE_NOT_FOUND (2): The specified registry key does not exist.
        • ERROR_ACCESS_DENIED (5): The calling process lacks the required permissions specified in samDesired
    */
    
    return 0;
}