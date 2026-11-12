## Address Space of a Proces

- The private, virtual view of memory that the operating system assigns the running process.
- This gives the process the illusion it is allocated continguous memiry spaces.


## Memory Mapping Files

- A memory mapped file in an OS is a mechanism that links a portion of a file on disk directly into a process's virtual memory address space.
- This allows the process to access the file contents directly through memory operations.
- Instead of repeatedly calling `read`, `write` ... etc ... system calls to copy data into the user space buffers, memory mapping allows us to directly access file contents using memory pointers. In Linux this could be achieved using `mmap`. 
- No physical data is loaded into RAM immediately, the system only allocates the memory address range. The data is only loaded into the RAM when the file operation is called, like dynamically.
- Dynamic memory related variables are allocated in the Heap region, so OS creates a paging or virtual address space for this value/object. This address may be non continguos in the PHYSICAL RAM but paging makes it look like its contiguos. Without fragmentation(contiguous memory) the program/process can perform simpler array element lookups without complex math, The MMU does the heavy lifting in the background, without paging we would as programmers would have had to perform complex array element lookups, program would have gotten more complex.

## Page Faults

- an except or interrupt raised by the Memory Management Unit(MMU) when a process is trying to access a memory address(page) that is not currenly mapped to the Physical RAM.

- a program must be written to minimize number of page faults.

### RESONS WHY PAGE FAULTS ARE LET TO HAPPEN

- page faults are unmapped virtual memory addresses.
- not all pages are mapped when the process is running and thats to optimally use the physical memory. only the pages used actively are loaded, and rest are left unmapped.

### TYPES OF PAGE FAULTS

- minor page fault (required data is in RAM but the page is not linked to that address yet)
- major page fault (required data is not in RAM, and must be fetched from secondary storage before linking the address)
- illegal page fault (process trying to read data on an address its not permitted to. this causes segmentation faults. can happen if the process is trying to access the memory address when its already terminated by the OS)

### WINDOWS MEMORY MANAGEMENT ARCHITECTURE DIAGRAM

![Windows Memory Management Architecture](./image.png)


## DLLs

- DLLs stands for Dynamic Linked Library
- Not executable directly unlike `.exe` we double click and execute.
- These DLLs are shared by multiple processes having same code so instead of creating multiple copies of the same code and consuming disk space, these DLLs are created so that multiple processes can share them.
- Advantages:
    - memory effificent:
        - not wasting disk space to create multiple redundant copies of the same code. one common point of access.
    - code reusability
        - the DLL is reused by multiple processes having the same checks or operations required to perform.
    - easier updates: 
        - only update that DLL code part instead of updating each and every program
            

## ADVANTAGES OF MEMORY MAPPED FILES OVER STANDARD I/O

* **Zero-copy performance.** 
    - Standard I/O copies file data from the disk into the OS kernel cache, and then copies it a second time into your program's user buffer. Memory mapping points your variable directly at the kernel cache, cutting out the extra copy and saving both CPU cycles and RAM.
* **No system call overhead during reads and writes.** 
    - Calling `ReadFile` or `WriteFile` in a loop forces the CPU to constantly switch between User Mode and Kernel Mode. With a memory-mapped file, you read and write using normal C/C++ pointers (`ptr[i]`), which execute at full CPU memory speed without OS context switches.
* **Lazy loading (Demand Paging).** 
    - Mapping a 10 GB file does not load 10 GB into RAM. Windows only loads small 4 KB chunks ("pages") from the disk into physical RAM at the exact moment your code tries to read those specific memory addresses.
* **Effortless random access.** 
    - Jumping back and forth inside a huge file with standard I/O requires constant `SetFilePointer` calls to move the file cursor. With memory mapping, jumping to any byte in the file is instant pointer math (`basePtr + offset`).
* **Built-in Inter-Process Communication (IPC).** 
    - Two or more separate programs can map the exact same file or shared memory object at the same time. Because Windows maps both programs' virtual pointers to the same underlying physical RAM pages, changes made by one program appear instantly to the other.
* **Simpler parsing of structured files.** 
    - If a file contains C-style structs, arrays, or binary headers, you can cast the mapped pointer directly to your struct type (`MyHeader* hdr = (MyHeader*)pBuf;`) instead of manually reading, parsing, and unpacking byte buffers.
