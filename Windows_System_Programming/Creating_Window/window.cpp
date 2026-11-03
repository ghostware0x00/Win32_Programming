#include <Windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	// The `4` parameters are as follows : -
	//	-`hInstance` is the handle value the OS uses to identify the * *handle * *that is loaded into the memory.
	//	- `hPrevInstance` was used in 16 - bit Windows, but is now always zero.
	//	- `pCmdLine` contains the command line arguments as Unicode string.
	//	- `nCmdShow` is a flag that indicates whether the main application is minimized, maximized, or shown normally.


	/*
		MessageBox arguments :-
		1. HWND (handle value)
		2. long pointer to constant wide string (box content)
		3. long pointer to constant wide string (box title)
		4. box/window flag . for example :- MB_OK, MB_OKCANCEL
	*/
	MessageBox(NULL, L"Hello World", L"hwindow", MB_OK);
	return 0;
}