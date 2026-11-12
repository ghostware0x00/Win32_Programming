## HEAP 

# Windows Heap Management API

Heap is the part of the memory which is allocated at runtime(Dynamic Memory Allocation). This can come in handly when dont know the memory required by the process beforehand. We can modify the memory allocated to the process during runtime. 

## 1. HeapCreate()
`HeapCreate()` function initializes a private heap object that can be used by the calling process. A private heap object is a dedicated, isolated region of memory allocated by the operating system.

### Arguments required by HeapCreate()
```c
HANDLE HeapCreate(
    DWORD flOptions,
    SIZE_T dwInitialize,
    SIZE_T dwMaximumSize
);
```

* **`flOptions`**: The heap allocation options. Common flags include:
    * `0`: Default serialized behavior (thread-safe).
    * `HEAP_NO_SERIALIZE`: Disables mutual exclusion. Use only if a single thread accesses this heap.
    * `HEAP_GENERATE_EXCEPTIONS`: Causes the system to raise an exception (like `STATUS_NO_MEMORY`) instead of returning `NULL` if an allocation fails.
* **`dwInitialSize`**: The initial size of the heap, in bytes. This determines the amount of memory initially committed.
* **`dwMaximumSize`**: The maximum size of the heap, in bytes.
    * If this value is greater than `0`, the heap is non-growable and cannot exceed this size.
    * If this value is `0`, the heap is growable. It will automatically expand in virtual space as needed until physical memory runs out.

---

## 2. HeapDestroy()
`HeapDestroy()` function is used to destroy or deallocate the private space given to the Heap object.

### Arguments required by HeapDestroy()
```c
BOOL HeapDestoy(HANDLE hHeap);
```

* **`HANDLE hHeap`**: The handle variable used to create the heap using `HeapCreate()`.

### Advantages of using HeapDestroy:
* We dont need to write traversal code to traverse to each individual element free them.
* There is no need to deallocate each individual element.

---

## 3. HeapAlloc()
`HeapAlloc()` function is used to allocate a block of memory from the private heap.

### Arguments required by HeapAlloc()
```c
LPVOID HeapAlloc(
    HANDLE hHeap,
    DWORD dwFlags,
    SIZE_T dwBytes
);
```

* **`HANDLE hHeap`**: The handle variable used to create the heap using `HeapCreate()`. The specific memory segment where you want to allocate the block.
* **`DWORD dwFlags`**: For allocation control flags:
    * `0`: Default allocation behavior.
    * `HEAP_ZERO_MEMORY (0x8)`: Automatically initializes all allocated bytes to zero (similar to `calloc`).
    * `HEAP_GENERATE_EXCEPTIONS (0x4)`: Forces the system to raise an operating system exception (like `STATUS_NO_MEMORY`) if the allocation fails, instead of returning `NULL`.
    * `HEAP_NO_SERIALIZE (0x1)`: Disables mutual exclusion (thread safety) for this specific call to boost performance. **Warning:** Do not use this flag on the default process heap.
* **`SIZE_T dwBytes`**: The total number of bytes you wish to allocate. For non-growable heaps its limited to `0x7FFF8` (approx 0.5MB).

- **RETURN VALUES**
    - Function failure causes an exception when using `EXCEPTION_GENERATE_EXECEPTIONS`. The exception code is either `STATUS_NO_MEMORY` or `STATUS_ACCESS_VIOLATION`.
    - Without that exception, it returns `NULL` pointer.



## HEAP DIGARAM

- When a process is created the OS creates a virtual space for the process and within this virtual space .text .bss and other segments including heap is there and when malloc calloc or dynamic programming memory required, it is from this region its given.


```
 [ PRIVATE HEAP OBJECT (Created via HeapCreate) ]
 -------------------------------------------------------------

 |  [ Block 1 ]  |  [ Block 2 ]  |  [ Block 3 ]  |  ...      |
 -------------------------------------------------------------
        │                                 
        ▼                                 
  HeapFree(..., Block 1)                  
  Removes JUST Block 1.                   
  The container stays alive.              
```

## SUMMARY OF HEAP MANAGEMENT

Summary: Heap Management
The normal process for using heaps is straightforward.
1. Get a heap handle with either or `HeapCreate` or `GetProcessHeap`
2. Allocate blocks within the heap using `HeapAlloc`
3. Optionally, free some or all of the individual blocks with `HeapFree`
4. Destroy the heap and close the handle with `HeapDestroy`


| Feature | `GetProcessHeap()` | `HeapCreate()` |
| :--- | :--- | :--- |
| **What it does** | Borrows the program's default shared heap | Carves out a brand-new private heap |
| **Who manages lifetime** | Managed automatically by Windows | Managed manually by you |
| **Must call `HeapDestroy`?** | **No** (will crash or corrupt your process) | **Yes** (otherwise causes memory leaks) |
| **Performance benefit** | Standard speed; shared with other modules | High; eliminates fragmentation via batch deallocation |



## What is Memory Fragmentation?

Imagine a parking lot (the default heap) where cars (memory blocks allocated by you and various DLLs) are constantly parking and leaving.
1. At the start: The parking lot is completely empty. Cars park right next to each other in perfect rows.
2. Over time: A background library frees up 3 spots over here. You free up 2 spots over there. A system component takes 1 spot somewhere else.
3. The "Messy" Result: The parking lot now has plenty of total space, but it is scattered into tiny, individual open spots all over the place.
If your program suddenly needs to park a giant tour bus (allocate a single, large continuous block of memory), the Heap Manager might look at the lot and say: "I have enough total room for a bus, but it's split up into 50 tiny spots. I don't have one single, unbroken space big enough for your bus."
When this happens, the operating system has to work extra hard to rearrange things or request brand-new virtual memory pages from the kernel, which slows down your application.


## When should you use a Private Heap (HeapCreate) instead?

- You don't need a private heap for everyday tasks. However, creating your own isolated private heap is incredibly useful in two specific scenarios:
    - Massive amounts of small allocations: If you are building something like a game or a compiler that creates and destroys millions of tiny nodes (like a linked list or tree), keeping them in a private heap stops them from cluttering up the default "parking lot."
    - Instant, lightning-fast cleanup: If you allocate 10,000 items inside a private heap for a temporary task, you don't have to spend time freeing all 10,000 items individually. You just call HeapDestroy(hPrivateHeap) and the entire "parking lot" vanishes instantly.

---

# Memory Mapped Files

- As we talked earlier about memory mapped files being an os mechanism that links a portion of the disk directly to a process's virtual address space. So memory mapped file is the HIGH LEVEL CONCEPT.


# Kernel File Object

- The kernel file object is a low level OS construct that links the contents of the file directly to the process's virtual address space. 


## 4. CreateFileMapping()

- `CreateFileMapping()` creates a **kernel file mapping object object** which has a **handle**, on an open file and then map all or part of the file to the process's virtual address space. File object can be named so that they can be accessed by other processes. 

- mapping of a file means creating a direct link of the file but `CreateFileMapping()` doesn't build the link yet. It only builds the blueprint saying this file will be linked and creates the **kernel file mapping object**.



### Arguments required by CreateFileMapping()

```c
HANDLE CreateFileMapping(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCTSTR               lpName
);
```

The `CreateFileMappingA` (or `CreateFileMappingW`) function creates or opens a named or unnamed file mapping object for a specified file.


* **`hFile`** (`HANDLE`): Handle to a file from `CreateFile`. Pass `INVALID_HANDLE_VALUE` to create an object backed by the system paging file for shared memory.
* **`lpFileMappingAttributes`** (`LPSECURITY_ATTRIBUTES`): Pointer to a security structure determining if child processes can inherit the handle. Pass `NULL` for default security.
* **`flProtect`** (`DWORD`): Page protection for the file view, such as `PAGE_READONLY` or `PAGE_READWRITE`. Must match the access rights used when opening `hFile`.
* **`dwMaximumSizeHigh`** (`DWORD`): High-order 32 bits of the maximum size of the file mapping object.
* **`dwMaximumSizeLow`** (`DWORD`): Low-order 32 bits of the maximum size. If both size parameters are `0`, the object matches the current file size.
* **`lpName`** (`LPCSTR` / `LPCWSTR`): Name of the mapping object (can use `Global\` or `Local\` prefixes). Pass `NULL` for an unnamed object.

## Return Value

* **Success:** Returns a `HANDLE` to the newly created file mapping object. If an object with the same name already existed, it returns a handle to the existing object, and calling `GetLastError()` returns `ERROR_ALREADY_EXISTS`.
* **Failure:** Returns `NULL`. Call `GetLastError()` for extended error details.


## OpenFileMapping (Windows API)

Opens an existing named file mapping object (`OpenFileMappingA` for ANSI, `OpenFileMappingW` for Unicode, defined in `winbase.h` via `windows.h`).

## Syntax

```c
HANDLE OpenFileMappingW(
  [in] DWORD   dwDesiredAccess,
  [in] BOOL    bInheritHandle,
  [in] LPCWSTR lpName
);
```

## Arguments

* **`dwDesiredAccess` (`DWORD`)**: Access rights to the file mapping object (checked against its security descriptor).
  * Common flags: `FILE_MAP_READ`, `FILE_MAP_WRITE`, `FILE_MAP_ALL_ACCESS`, `FILE_MAP_COPY`, `FILE_MAP_EXECUTE`.
* **`bInheritHandle` (`BOOL`)**: Handle inheritance flag for child processes created via `CreateProcess`.
  * `TRUE`: Child processes can inherit the handle.
  * `FALSE`: Handle cannot be inherited.
* **`lpName` (`LPCSTR` / `LPCWSTR`)**: Null-terminated name of the existing file mapping object.
  * Supports `Global\` or `Local\` namespace prefixes; the remainder cannot contain backslashes (`\`).

## Return Values

* **Success**: An open `HANDLE` to the specified file mapping object.
* **Failure**: `NULL` (call `GetLastError()` for extended error info, such as `ERROR_FILE_NOT_FOUND`).


## MapViewOfFile (Windows API)

Maps a view of a file mapping object into the address space of a calling process (`memoryapi.h` via `windows.h`).

## Syntax

```c
LPVOID MapViewOfFile(
  [in] HANDLE hFileMappingObject,
  [in] DWORD  dwDesiredAccess,
  [in] DWORD  dwFileOffsetHigh,
  [in] DWORD  dwFileOffsetLow,
  [in] SIZE_T dwNumberOfBytesToMap
);
```

## Arguments

* **`hFileMappingObject` (`HANDLE`)**: A handle to a file mapping object returned by `CreateFileMapping` or `OpenFileMapping`.
* **`dwDesiredAccess` (`DWORD`)**: Type of access to the file view, which determines the page protection of the pages.
  * Common flags: `FILE_MAP_ALL_ACCESS`, `FILE_MAP_READ`, `FILE_MAP_WRITE`, `FILE_MAP_COPY` (copy-on-write), `FILE_MAP_EXECUTE`.
* **`dwFileOffsetHigh` (`DWORD`)**: High-order `DWORD` of the file offset where the view begins.
* **`dwFileOffsetLow` (`DWORD`)**: Low-order `DWORD` of the file offset where the view begins.
  * Note: The combined offset must be a multiple of the system's memory allocation granularity (typically 64 KB).
* **`dwNumberOfBytesToMap` (`SIZE_T`)**: Number of bytes of the file mapping to map to the view.
  * Set to `0` to map from the specified offset all the way to the end of the file mapping object.

## Return Values

* **Success**: The starting memory address (`LPVOID`) of the mapped view.
* **Failure**: `NULL` (call `GetLastError()` for extended error info).


