## Window Handles

- Windows are objects. They contain code and data but not c++ classes.
- Instead a program references a window by using a value called **handle**.
- A **handle** is an opaque type. It is a number that the operating system uses to identify an object.
- The datatype for **handle** is `HWND`. 
- Window **handles** are returned by functions that create windows : `CreateWindow` and `CreateWindowEx`.


## Repositioning a Window

- To perform this we typically call a function that takes an `HWND` value as parameter.
- To reposition a window on the screen we use the `MoveWindow` function.

```c++
BOOL MoveWindow(HWND hWnd, int x, int y, int nWidth, int nHeight, BOOL bRepaint);
```

## Windows Entry Point

- Every windows program includes an entry point function either named `WinMain` or `wWinMain`. The following code shows the signature of the `wWinMain` :-

```c++
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
```

- The `4` parameters are as follows :-
	- `hInstance` 