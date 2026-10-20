#include <iostream>
#include <print>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    // 1. Argument Validation
    if (argc != 3) {
        std::println("[!] Usage : cp file1 file2");
        return 1;
    }

    // 2. Open Streams (Replaces CreateFile)
    std::ifstream src(argv[1], std::ios::binary);
    if (!src) {
        std::cerr << "Cannot open input file.\n";
        return 2;
    }

    std::ofstream dst(argv[2], std::ios::binary);
    if (!dst) {
        std::cerr << "Cannot open output file.\n";
        return 3;
    }

    // 3. Buffer Loop (Replaces ReadFile/WriteFile loop)
    constexpr std::size_t BUF_SIZE = 256;
    std::vector<char> buffer(BUF_SIZE);

    while (src.read(buffer.data(), buffer.size()) || src.gcount() > 0) {
        dst.write(buffer.data(), src.gcount());
        if (!dst) {
            std::cerr << "Fatal write error.\n";
            return 4;
        }
    }

    // 4. Cleanup (Streams automatically close when they go out of scope!)
    return 0;
}
