## TYPEDEFS

- typedefs are like aliases in programming where we can create an alias for a certain datatype ... like a shorthand
- windows has a lot of typedefs 

## INTEGERS


| Data Type | Size | Signed / Unsigned |
| :--- | :--- | :--- |
| **BYTE** | 8 bits | Unsigned |
| **DWORD** | 32 bits | Unsigned |
| **INT32** | 32 bits | Signed |
| **INT64** | 64 bits | Signed |
| **LONG** | 32 bits | Signed |
| **LONGLONG** | 64 bits | Signed |
| **UINT32** | 32 bits | Unsigned |
| **UINT64** | 64 bits | Unsigned |
| **ULONG** | 32 bits | Unsigned |
| **ULONGLONG** | 64 bits | Unsigned |
| **WORD** | 16 bits | Unsigned |


## signed vs unsigned data

- `signed` : 
	- negative, zero or positive data.
	- typically uses 2's complement.
	- the msb bit is reserved for the sign bit. `0` = positive and `1` = negative


- `unsigned` :
	- zero or positive data.
	- all bits define the data value. no presence of sign bits.


## BOOLEAN TYPE

- In win32 `BOOL` occupies **4 bytes(32 bits)** of memory because its `int`.
- In win32 we don't have `boolean` which contains **true** and **false**.
- Instead we use `#define` to create alias for `0` as `FALSE` and `1` as `TRUE`.
- Instead of writing code by checking for `if(c1 == TRUE) or if(c1 == FALSE`. write like as shown below.

```c++
if(somevalue){ // here if(somevalue) means it checks only non zero conditions
	...something...
}
else{
	...something...
}
```


## POINTER TYPE

- In windows win32 pointer usually has a prefix `P`(pointer) or `LP`(long pointer).
- For example :- `LPRECT` means a pointer to a **RECT** structure.
- The pointer size depends on the application. Like if the application is built in a 32 bit system then its 4 bytes(32 bit) and if the application is 64 bit then the pointer is 64 bit. Based on how you compile the program the pointer takes that size. That being said a 32 bit application cannot compile as 64 bit.

```c++
RECT* rect; // pointer to rect structure
PRECT rect; // same thing
LPRECT rect; // same thing
```

## WORKING WITH STRINGS

- `wchar_t` used for wide character.
- `2 bytes` each character because of UTF-16(Windows) so 16 bits = 16 / 2 = 2 bytes.
- The `L` forces the compiler to allocate `2 bytes`(Windows) and is used for wide characters
	- `L''` is used for single characters
	- `L""` is used for multi characters 


```c++
wchar_t a = L'a'; // single character
wchar_t b = L"abc"; // multi character
```


### Windows String Typedef Mapping

| Windows Typedef | C++ Native Type | Meaning |
| :--- | :--- | :--- |
| **`CHAR`** | `char` | Standard 8-bit character |
| **`PSTR`** / **`LPSTR`** | `char*` | Pointer to a standard character string |
| **`PCSTR`** / **`LPCSTR`** | `const char*` | Pointer to a **constant** standard character string |
| **`PWSTR`** / **`LPWSTR`** | `wchar_t*` | Pointer to a wide character string |
| **`PCWSTR`** / **`LPCWSTR`** | `const wchar_t*` | Pointer to a **constant** wide character string |
