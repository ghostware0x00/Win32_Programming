#include <iostream>
#include <Windows.h> // stuff like PCSTR PCWSTR can be used because of this

int main() {
	std::cout << "<--------------------------->" << std::endl;
	std::cout << "[+] variable values :" << std::endl;
	std::cout << "<--------------------------->" << std::endl;
	/*
		REASON WHY wchar_t or WCHAR was developed when we have std::string and char
		main reason is because of historical reason
		1. char is of 8 bits = 1 byte = 256 slots
		2. wchar_t is of 16 bit = 2 bytes = 256 x 256 = 65536
	*/
	wchar_t a = L'a';
	const wchar_t *b = L"hello"; // when assigning string we need to use a constant wchar_t pointer
	std::wcout << a << std::endl; // to print wide characters we use wcout 
	std::wcout << b << std::endl; // to print wide characters we use wcout
	PCSTR name = "sourav"; // PCSTR means constant string and c++ strings need to be constant
	std::cout << name << std::endl;
	PCWSTR d = L"bose";
	std::wcout << d << std::endl; 
	std::cout << "<--------------------------->" << std::endl;
	std::cout << "[+] size of variables :" << std::endl;
	std::cout << "<--------------------------->" << std::endl;
	std::cout << sizeof(a) << std::endl; // 2 bytes
	// the below variables are pointers and based on the architecture of the system is 64 bit so 8 bytes
	std::cout << sizeof(b) << std::endl; // 8 bytes 
	std::cout << sizeof(d) << std::endl; // 8 bytes
	std::cout << sizeof(name) << std::endl; // 8 bytes
	UINT x = 10; // UINT is unsigned int
	std::cout << x << std::endl;
	const WCHAR *test = L"test"; // WCHAR is a Windows macro and alias for wchar_t 
	std::wcout << test << std::endl;
	std::cout << sizeof(test) << std::endl;
	return 0;
}