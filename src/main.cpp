#include "lib.hpp"

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
        if ((number < 10000) || (number > 99999) || (full_name == "") || (address == "")) 
            this->valid = false; 
    }

    void fill(ui32 number, string full_name, string address) {
        this->number = number;
        this->full_name = full_name;
        this->address = address; 
    }

    void print() {
        std::cout << "#" << number 
        << " registered to " << full_name << ", " 
        << address << "\n";
    }
};


struct HashTable {
    static const ui32 C = 1, D = 3;

    ui32 capacity;
    ui32 num_of_elements = 0;
    std::vector<Subscription> table; 
    
    //  iteration trait
    auto begin() const { return table.begin(); }
    auto end() const { return table.end(); }

    HashTable() { 
        capacity = 10;
        table = std::vector(capacity, Subscription());
    }
    HashTable(int init_len) {
        capacity = init_len * 2; 
        for (int i = 0; i < init_len; ++i) {
            this->insert(10000 + (rand()) % 90000, "23", "33", true);
        }
    }


    ui32 hashFunction(ui32 number) {
        return number % capacity;
    }

    void rehash() {
        table.resize(table.size() * 2);
        capacity = table.size();
    }
    
    void insert(ui32 number, string full_name, string address, bool initializing = false) {
        ui32 hash_key = hashFunction(number);
        Subscription hashed_entry = Subscription(number, full_name, address);
        if (!hashed_entry.valid) {
            std::cout << "Tried to hash invalid subscription:\n";
            hashed_entry.print();
            std::cout << "\n";
            return;
        }

        if (++num_of_elements > capacity * 0.75) {
            std::cout << "Element limit exceeded. Rehashing.\n";
            rehash();
            std::cout << "Rehashed successfully.\nNew capacity: " << this->table.size() << "\n\n" ;
        }

        if (table[hash_key].valid) {
            int i = 0;
            std::cout << "Trying to prevent hash collision at " << hash_key << std::endl;
            while (table[hash_key].valid) 
                hash_key = hashFunction(hash_key + C * ++i + D * i*i);
            std::cout << "Found free key " << hash_key << "\n\n";
        }

        table[hash_key] = hashed_entry;
        if (!initializing) {        
            hashed_entry.print();
            std::cout << "Successfully inserted at " << hash_key << "\n\n";
        }
        
    }

    void print() {
        for(auto entry : *this)
            if (entry.valid)
                entry.print();
                
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
    a.insert(41282, "SVO", "332");
    a.insert(41282, "ABJ", "31241231232");
    a.insert(4128, "asdsad", "2367472y43");
    a.insert(41282, "12312", "2367472y43");
    
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
