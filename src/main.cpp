#include "lib.h"

struct Subscription {
    ui32 number;
    string full_name;
    string address;
};

struct HashTable {

};

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
