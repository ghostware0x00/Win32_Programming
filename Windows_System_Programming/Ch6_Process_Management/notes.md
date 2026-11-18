## Process

- A running program which has an assigned PID and resources allocated by the OS is called a Process.

## Threads

- Its the smallest execution unit inside a process.
- It allows multiple tasks to run simultaneously.

## TLS

- TLS stands for Thread Local Storage.
- Its an array like collection of pointers giving each thread the ability to allocate storage to create its own unique data environment.

![Process and Its Threads](image.png)


## Process Handle Tables

- a data structure maintained by the OS for each individual process to keep track of what system resources are allocated to these processes like (open files, registry keys, threads ... etc ...)


# Windows Process Management API

## CreateProcess()

- launches the application/program/process and creates the primary thread i.e. point to the entry point of the program (such as main, wmain or tmain)

```c
BOOL CreateProcessW(
  LPCWSTR lpApplicationName, 
  LPWSTR lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes, 
  BOOL bInheritHandles, 
  DWORD dwCreationFlags,
  LPVOID lpEnvironment, 
  LPCWSTR lpCurrentDirectory, 
  LPSTARTUPINFOW lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
);
```

## Arguments

- **`lpApplicationName and lpCommandLine`**: The executable path and command-line arguments (the command line buffer must be writable for Unicode calls). If **NULL** is passed then the first white-space delimited token is the program name. **example**: if you pass `notepad.exe file.txt` then it will conside `notepad.exe`

- **`LPSECURITY_ATTRIBUTES lpProcessAttributes and lpThreadAttributes`**: point to the process and thread security. It accepts security descriptors (NULL for defaults). 

- **`BOOL bInheritHandles`**: determines whether the new process inherits the copies of the calling process's inheritable open handles like(files, mappings ... etc ...)

- **`DWORD dwCreationFlags`**: 
    - `CREATE_SUSPENDED` indicates that the primary thread is in a suspended state and will run only when the program calls ResumeThread.
    - `DETACHED_PROCESS` lauches the console application without giving it the console window and without letting it inherit the parent process's console.

    - `CREATE_NEW_CONSOLE` creates a brand-new independent console window for the child process.

    - `CREATE_UNICODE_ENVIRONMENT` should be set if UNICODE (or _UNICODE) is defined (and a custom Unicode environment block is passed in lpEnvironment).

    - `CREATE_NEW_PROCESS_GROUP` makes the new process the root of a new process group, where group ID equals to the new process's ID(`dwProcessID`).

- **`LPVOID lpEnvironment`** points to an environment block holding **environment variables**. For example:- `PATH` or `TEMP` variable. 

- **`LPCWSTR lpCurrentDirectory`** specifies the drive and directory for the new process. If **NULL** the parent's working directory is used.

- **`LPSTARTUPINFO lpStartInfo`** is complex and specifies the main window appearance of the newly created process and standard device handles for the new process. Windows needs to know how to display the new application to the user. Instead of letting the new program open at its default size and position, STARTUPINFO lets your program override those defaults.

## Return Value

- `NON ZERO` if process created successfully
- `ZERO` if failed to create process


## WaitForSingleObject()

- pauses the execution of the calling thread until a specified kernel object becomes signaled or a set time-out interval elapses. 
- This mainly used for synchronization purposes because when we create a process, that process runs asynchronously so both the calling process and the newly created process run solo ... so lets say one process is dependent on the other one so we use this function to synchronize them and use p2 to write to p1 and then read it from there (just an example).

```c
DWORD WaitForSingleObject(
  HANDLE hHandle,
  DWORD  dwMilliseconds
);
```

## Arguments

- **`Handle`**: Handle to a synchronization object (mutex, event, semaphore, process, or thread).

- **`dwMilliseconds`**: Time-out interval in milliseconds (0 for immediate return; INFINITE or 0xFFFFFFFF to wait indefinitely).

## Return Values
	
- **`WAIT_OBJECT_0 (0x00000000)`**: Object is signaled (compare explicitly, as this evaluates to 0).

- **`WAIT_TIMEOUT (0x00000102)`**: Time-out interval elapsed first.

- **`WAIT_ABANDONED (0x00000080)`**: Mutex was abandoned by its owning thread.

- **`WAIT_FAILED`**: Function failed due to an invalid handle or error