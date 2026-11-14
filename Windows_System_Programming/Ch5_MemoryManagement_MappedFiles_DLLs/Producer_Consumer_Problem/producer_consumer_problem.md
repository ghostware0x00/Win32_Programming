## PRODUCER CONSUMER PROBLEM


## How Shared Memory IPC Actually Works

1. Physical Memory (The Shared Bridge): 
    - When the Producer calls CreateFileMapping, Windows allocates a block of physical RAM (backed by the system pagefile) and gives it a kernel name ("Local\\PracticeIPC").
2. Producer's Virtual Mapping: 
    - When the Producer calls MapViewOfFile, Windows maps that physical RAM to a virtual address inside the Producer (for example, 0x000001A00000).
3. Consumer's Virtual Mapping: 
    - When the Consumer calls OpenFileMapping and MapViewOfFile, Windows maps that exact same physical RAM to a completely different virtual address inside the Consumer (for example, 0x000002B00000).


```bash
Producer Process                         Consumer Process
Virtual Addr: 0x000001A00000             Virtual Addr: 0x000002B00000
         │                                        │
         ▼                                        ▼
    ┌──────────────────────────────────────────────────┐
    │       Shared Physical RAM ("Local\PracticeIPC")  │
    └──────────────────────────────────────────────────┘
```

- When the Producer writes "Hello" to 0x000001A00000, the CPU's Memory Management Unit (MMU) translates that address and writes the bytes onto the shared physical RAM.
- When the Consumer reads from 0x000002B00000, the MMU translates its address to the exact same physical RAM and immediately sees "Hello".
- If the Consumer tried to read the Producer's virtual address (0x000001A00000) directly, it would either read garbage from its own memory or crash with an Access Violation.