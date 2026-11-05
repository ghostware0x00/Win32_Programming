#include <Windows.h>
#include <tchar.h>
#include <print>


int _tmain(){
    /*
        RegEnumEx() function enumerates subkey names of an open registry
        arguments required by RegEnumEx() :-
        <------------------------------------>
        LSTATUS RegEnumKeyExW(
            HKEY      hKey,
            DWORD     dwIndex,
            LPWSTR    lpName,
            LPDWORD   lpcchName,
            LPDWORD   lpReserved,
            LPWSTR    lpClass,
            LPDWORD   lpcchClass,
            PFILETIME lpftLastWriteTime
        );

        • hKey [in]: Open registry key handle (requires KEY_ENUMERATE_SUB_KEYS or KEY_READ).
        • dwIndex [in]: Subkey index to retrieve, starting at 0 and incrementing per call. Always is 0
        • lpName [out]: Buffer receiving the subkey name.
        • lpcchName [in, out]: Buffer size in characters (must be reset to full size before each loop iteration).
        • lpReserved [in]: Must be NULL.
        • lpClass / lpcchClass / lpftLastWriteTime: Optional class buffer, class size, and FILETIME pointer (can be NULL)

        Returns an LSTATUS error code:
        • ERROR_SUCCESS (0): Subkey retrieved successfully.
        • ERROR_NO_MORE_ITEMS (259): Enumeration complete.
        • ERROR_MORE_DATA (234): Buffer too small.
        • Other codes: Standard Windows system errors (e.g., ERROR_ACCESS_DENIED).
    */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD bWrite = 0;
    HKEY hKey = HKEY_CURRENT_USER;
    //TCHAR subkey[] = _T(R"(Software)");
    TCHAR subKeyName[MAX_PATH];
    if(RegOpenKeyEx(hKey, _T(R"(Software)"), 0, KEY_READ, &hKey) != ERROR_SUCCESS){
        TCHAR errMsg[] = _T("[!] failed to open registry");
        WriteFile(hOut, errMsg, (DWORD)_tcslen(errMsg) * sizeof(TCHAR), &bWrite, NULL);
        return 1;
    }
    // RegEnumEx() enumerates values, names and corresponding data of the opened registry key. the one we opened using HKEY hKey in the above code
    LSTATUS enumStatus;
    DWORD ccName;
    DWORD dwIndex = 0;
    TCHAR newLine = '\n';
    do{
        ccName = sizeof(subKeyName)/sizeof(subKeyName[0]); 
        /*
            we need to recalculate the size everytime for the buffer(subKeyName) everytime because after each subkey buffer variable receives that subkey size
            will be written in ccName and we are passing it in RegEnumEx() so in each iteration we need to recalculate the size of the buffer 
            in each iteration a new subkey is being overwritten in the buffer(subKeyName)
        */
        enumStatus = RegEnumKeyEx(hKey, dwIndex, subKeyName, &ccName, NULL, NULL, NULL, NULL);
        if(enumStatus == ERROR_SUCCESS){
            WriteFile(hOut, subKeyName, (DWORD)_tcslen(subKeyName) * sizeof(TCHAR), &bWrite, NULL);
            bWrite = 0;
            WriteFile(hOut, &newLine, sizeof(TCHAR), &bWrite, NULL);
            dwIndex++;
        }
    }while(enumStatus == ERROR_SUCCESS);
    RegCloseKey(hKey);
    return 0;
}