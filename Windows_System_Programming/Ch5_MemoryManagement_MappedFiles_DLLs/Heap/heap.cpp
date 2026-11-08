#include <Windows.h>
#include <tchar.h>

int _tmain(){
    /*
        Heap is the part of the memory which is allocated at runtime(Dynamic Memory Allocation).
        This can come in handly when dont know the memory required by the process beforehand.
        We can modify the memory allocated to the process during runtime.

        HeapCreate() function initializes a private heap object that can be used by the calling process
        A private heap object is a dedicated, isolated region of memory allocated by the operating system.
        arguments required by HeapCreate() :-
        <------------------------------------->
        HANDLE HeapCreate(
            DWORD flOptions,
            SIZE_T dwInitialize,
            SIZE_T dwMaximumSize
        );

        • flOptions: The heap allocation options. Common flags include:
            • 0: Default serialized behavior (thread-safe).
            • HEAP_NO_SERIALIZE: Disables mutual exclusion. Use only if a single thread accesses this heap.
            • HEAP_GENERATE_EXCEPTIONS: Causes the system to raise an exception (like STATUS_NO_MEMORY) instead of returning NULL if an allocation fails.
        • dwInitialSize: The initial size of the heap, in bytes. This determines the amount of memory initially committed.
        • dwMaximumSize: The maximum size of the heap, in bytes.
            • If this value is greater than 0, the heap is non-growable and cannot exceed this size.
            • If this value is 0, the heap is growable. It will automatically expand in virtual space as needed until physical memory runs out.
    */
        
}