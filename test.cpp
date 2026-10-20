#include <iostream>


std::string hello_world() {
	return "hello world";
}

int main() {
	std::string hw = hello_world();
	std::cout << hw << std::endl;
	return 0;
}