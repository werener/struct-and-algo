#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <ios>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>

typedef unsigned u;

typedef std::uint32_t ui32;
typedef std::string string;

struct Subscription {
    
};

void task3();

int main() {
    std::cout << sizeof(ui32);
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
