## Standard Compilation Flags Reference

Here is a breakdown of the essential switches you should always use with cl.exe:

| Flag | Meaning | Why You Need It |
| :--- | :--- | :--- |
| `/EHsc` | Enable C++ Exception Handling | Crucial for C++ files using `<iostream>`, `<fstream>`, or vectors to prevent warning C4530. |
| `/std:c++17` | Set Language Standard | Enables modern features like `std::filesystem`. You can use `/std:c++17` or `/std:c++20`. |
| `/W4` | Warning Level 4 | Shows strict warnings to catch code errors before they become bugs. |
| `/Fe:` | File Executable Name | Sets the name of the final `.exe` file. (Replaces the Linux `-o` flag). |
| `/TC` | Treat all files as C | Forces the compiler to treat files as C code, regardless of extension. |
| `/TP` | Treat all files as C++ | Forces the compiler to treat files as C++ code, regardless of extension. |

## `.cpp` compilation

```cmd
cl /EHsc /std:c++latest /W4 test2.cpp /Fe:my_program.exe
```


## `.cp` compilation

```cmd
cl /EHsc /std:c++17 /W4 /TP test.cp /Fe:my_program.exe
```