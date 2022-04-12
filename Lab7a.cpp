#include <iostream>

int main() {
    uint64_t n;
    std::cin >> n;
    int len = ((n >> 32) != 0) ? 63 - __builtin_clz(static_cast<uint32_t>(n >> 32)) : 31 - __builtin_clz(static_cast<uint32_t>(n));
    if (n >> len) std::cout << 1;
    for (; len > 0; len--) {
        std::cout << (((n >> len) ^ (n >> (len - 1))) & 1);
    }
    std::cout << std::endl;
}