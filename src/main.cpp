#include "lib.hpp"

struct Subscription {
    ui32 number;
    string full_name;
    string address;
    bool valid;

    static Subscription generate_random() {
        const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd; std::mt19937_64 gk(rd());
        std::uniform_int_distribution<int> num_gen(10000, 99999);
        std::uniform_int_distribution<size_t> char_gen(0, characters.size()-1);
        //  gen name
        string name = "", address = "";
        name.push_back(characters[char_gen(gk) % 26]);
        name.push_back('.');
        name.push_back(characters[char_gen(gk) % 26]);
        name.push_back('.');
        name.push_back(characters[char_gen(gk) % 26]);
        for (int i = 0; i < 7 + rand() % 10; ++i)
            name += characters[26 + char_gen(gk) % 26];
        //  gen address
        for (int i = 0; i < 10 + rand() % 20; ++i)
            address += characters[char_gen(gk)];

        return Subscription(num_gen(gk), name, address);
    }

    Subscription() { this->valid = false; }

    Subscription(ui32 number, string full_name, string address) {
        this->number = number;
        this->full_name = full_name;
        this->address = address; 
        this->valid = true;
        if ((number < 10000) || (number > 99999) || (full_name == "") || (address == "")) 
            this->valid = false; 
    }

    void print() {
        std::cout << "#" << number 
        << " registered to " << full_name 
        << ", " << address << "\n";
    }
};


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
        while(num_of_elements < init_len) 
            this->insert(Subscription::generate_random(), false);
        
        c = capacity - 1;
        d = capacity + 1;
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
            else
                while (table[hash_key].valid) 
                    hash_key = hashFunction(hash_key + c * ++i + d * i*i);
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
    auto a = HashTable(20);
   
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
