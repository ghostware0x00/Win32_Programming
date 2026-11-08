#include <Windows.h>
#include <tchar.h>
#include <print>

int _tmain(){
    /*
        using GetSystemInfo() function to retrieve details of the current system's hardware resources, architecture, page size, boundaries, and active processor count.
        arguments required by GetSystemInfo() :-
        <---------------------------------------->
        VOID GetSystemInfo(LPSYSTEM_INFO lpSystemInfo)

        • lpSystemInfo
            • A pointer to a SYSTEM_INFO structure. This structure fills its members with data related to the host machine.
    */
    SYSTEM_INFO sysInfo; // declaring the SYSTEM_INFO structure variable where the host machine contents will be stored
    GetSystemInfo(&sysInfo); // invoking the function by passing the structure variable by reference
    std::println("+-------------------- System Information --------------------+");
    std::println("| Processor Architecture: {}",sysInfo.wProcessorArchitecture);
    std::println("| Page Size: {}", sysInfo.dwPageSize); // shows the page size. this is the size in which OS divides the memory in chunks of ... called pages
    std::println("| Minimum Address Boundary: {}", sysInfo.lpMinimumApplicationAddress); // lowest memory address that user-mode application is allowed access
    std::println("| Maximum Address Boundary: {}", sysInfo.lpMaximumApplicationAddress); // highest memory address a user mode program can access in a 64bit/32 bit environment
    std::println("| Active Processor Mask: {}", sysInfo.dwActiveProcessorMask); // bitmask representating the number of available CPU threads 
    std::println("| Number of Processors: {}", sysInfo.dwNumberOfProcessors); 
    std::println("| Allocation Granularity: {}", sysInfo.dwAllocationGranularity); // 
    std::println("+-------------------------------------------------------------+");
    return 0;
}