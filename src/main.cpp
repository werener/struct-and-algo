#include "lib.h"

struct Subscription {
    ui32 number;
    string full_name;
    string address;
    bool valid;
    Subscription() {
        this->valid = false;
    }

    Subscription(ui32 number, string full_name, string address) {
        this->number = number;
        this->full_name = full_name;
        this->address = address; 
        this->valid = true;
        if ((number < 10000) || (number > 99999))
            this->valid = false; 
    }

    void fill(ui32 number, string full_name, string address) {
        this->number = number;
        this->full_name = full_name;
        this->address = address; 
    }
};


struct HashTable {
    static const ui32 C = 11, D = 7, Q = 100000 - 10000;
    std::vector<Subscription> table = std::vector(Q, Subscription());
    ui32 capacity = Q;
    ui32 num_of_elements = 0;
    //  iteration trait
    auto begin() const { return table.begin(); }
    auto end() const { return table.end(); }

    HashTable() { 
        num_of_elements = 5;
        for (int i = 0; i < 5; ++i)
            table[i] = Subscription(i+10000, "23", "33");
    }
    
    ui32 hashFunction(ui32 number) {
        return number % capacity;
    }

    void rehash() {}
    
    void insert(ui32 number, string full_name, string address) {
        ui32 hash_key = hashFunction(number);
        if (table[hash_key].valid) {
            int i = 0;
            while (table[hash_key].valid)
                hash_key = hashFunction(hash_key + C * i + D * i*i);
            table[hash_key] = Subscription(number, full_name, address);
            num_of_elements++;
        }

        else {
            num_of_elements++;
            table[hash_key] = Subscription(number, full_name, address);
        }

        if (num_of_elements > capacity * 0.75)
            rehash();
    }

    void print() {
        for(auto entry : *this)
            if (entry.valid)
                std::cout << "#" << entry.number << " registered to " << entry.full_name << ", " << entry.address << "\n";
    }
    void print_full() {
        for (int i = 0; i < capacity; ++i) {
            Subscription entry = this->table[i];
            if (entry.valid)
                std::cout << "#" << entry.number << "(hashed as " << i << ") registered to " << entry.full_name << ", " << entry.address << "\n";
        }
    }
};

int main() {
    auto a = HashTable();
    a.print_full();
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
