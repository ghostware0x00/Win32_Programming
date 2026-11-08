## Address Space of a Proces

- The private, virtual view of memory that the operating system assigns the running process.
- This gives the process the illusion it is allocated continguous memiry spaces.


## Memory Mapping Files

- A memory mapped file in an OS is a mechanism that links a portion of a file on disk directly into a process's virtual memory address space.
- This allows the process to access the file contents directly through memory operations.
- Instead of repeatedly calling `read`, `write` ... etc ... system calls to copy data into the user space buffers, memory mapping allows us to directly access file contents using memory pointers. In Linux this could be achieved using `mmap`. 
- No physical data is loaded into RAM immediately, the system only allocates the memory address range. The data is only loaded into the RAM when the file operation is called, like dynamically.

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



