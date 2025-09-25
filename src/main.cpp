#include "lib.hpp"
#include "HashTable.hpp"

int main() {
    auto a = HashTable(10);
    a.print_full();
    ui32 n;
    while(n!=1){
        std::cin >> n;
        a.find((ui32)n).print();
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
