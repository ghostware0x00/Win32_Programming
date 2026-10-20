#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){
    MessageBoxW(NULL, L"Hello, World!", L"Hello World App", MB_OK);
    return 0;
}
