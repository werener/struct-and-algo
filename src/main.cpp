#include "lib.h"

struct Subscription {
    ui32 number;
    string full_name;
    string address;

    Subscription(ui32 number, string full_name, string address) {
        this->number = number;
        this->full_name = full_name;
        this->address = address; 
    }
};

const ui32 C, D;
struct HashTable {
    std::vector<Subscription> table;
    ui32 capacity;
    ui32 num_of_elements;
    //  iteration trait
    auto begin() const { return table.begin(); }
    auto end() const { return table.end(); }

    HashTable() { 
        for (int i = 0; i < 5; ++i)
            table.push_back(Subscription(i+10000,"23", "33"));
    }
    
    ui32 hashFunction(ui32 number) {
        return number % capacity;
    }
};

int main() {
    auto a = HashTable();
    for(auto i : a)
        std::cout << i.number << " ";
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
