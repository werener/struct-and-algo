#include "lib.hpp"
#include "HashTable.hpp"

void cli() {
    ui32 init_len;
    std::cout << "Enter amount of numbers to initialize HashTable with:\n";
    if(!(std::cin >> init_len))
        break;
    HashTable a;
}


int main() {
    auto a = HashTable(10);
    a.print_full();
    int n=0;
    while(n != 1) {
        if(!(std::cin >> n))
            break;
        auto b = a.find((int)n);
        if (b.valid) b.print();
    }
}


void task3() {
    using namespace std::chrono;
    for (int i = 0; i < 3; ++i) {
        std::ifstream f("./files/data.dat", std::ios::binary);
        // get measurement
        auto start = high_resolution_clock::now();
        auto end = high_resolution_clock::now();
    }
}
