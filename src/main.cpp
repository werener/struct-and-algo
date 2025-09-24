#include "lib.hpp"
#include "Subscription.hpp"


struct HashTable {
    ui32 c, d;
    ui32 capacity;
    ui32 num_of_elements = 0;
    std::vector<Subscription> table; 
    
    //  iteration trait
    auto begin() const { return table.begin(); }
    auto end() const { return table.end(); }

    HashTable() { 
        capacity = 10;
        //   make c and d coprime with capacity
        c = capacity - 1;
        d = capacity + 1;
        table = std::vector(capacity, Subscription());
    }
    HashTable(ui32 init_len) {
        capacity = init_len * 2; 
        table = std::vector(capacity, Subscription());
        c = capacity - 1;
        d = capacity + 1;
        while(num_of_elements < init_len) 
            this->insert(Subscription::generate_random(), false);
    }


    ui32 hashFunction(ui32 number) {
        return number % capacity;
    }

    void rehash() {
        table.resize(table.size() * 2);
        capacity = table.size();
        c = capacity - 1;
        d = capacity + 1;
    }

    void insert(Subscription hashed_entry, bool not_initializing = true) {
        ui32 hash_key = hashFunction(hashed_entry.number);

        if (!hashed_entry.valid) {
            std::cout << "Tried to hash invalid subscription:\n";
            hashed_entry.print();
            std::cout << "\n";
            return;
        }

        if (++num_of_elements > capacity * 0.7) {
            std::cout << "Element limit exceeded. Rehashing.\n";
            rehash();
            std::cout << "Rehashed successfully.\nNew capacity: " << this->table.size() << "\n\n" ;
        }

        if (table[hash_key].valid) {
            int i = 0;
            
            if (not_initializing) {
                std::cout << "Trying to prevent hash collision at " << hash_key << std::endl;
                while (table[hash_key].valid) 
                    hash_key = hashFunction(hash_key + c * ++i + d * i*i);
                std::cout << "Found free key " << hash_key << "\n\n";
            }
            else {
                while (table[hash_key].valid) {
                    hash_key = hashFunction(hash_key + c * ++i + d * i*i);
                    // std::cout << "stuck " << this->num_of_elements << " " << this->capacity << " " << i << " hash_key: " << hash_key << " " << c << std::endl;
                }
            }
        }

        table[hash_key] = hashed_entry;
        if (not_initializing) {
            hashed_entry.print();
            std::cout << "Successfully inserted at " << hash_key << "\n\n";
        }
    }
    void insert(ui32 number, string full_name, string address, bool not_initializing = true) {
        ui32 hash_key = hashFunction(number);
        Subscription hashed_entry = Subscription(number, full_name, address);
        this->insert(hashed_entry, not_initializing);
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
                std::cout 
                <<"Hash_key " << i << ": " 
                << "#" << entry.number 
                << " registered to " << entry.full_name 
                << ", " << entry.address << "\n";
        }
    }
};

int main() {
    auto a = HashTable(27);
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
