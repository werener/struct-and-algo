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
        capacity = 50;
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
        capacity *= 2;
        c = capacity - 1;
        d = capacity + 1;
        std::vector<Subscription> new_table(capacity, Subscription());

        ui32 hash_key; 
        for (auto entry : table) {
            hash_key = hashFunction(entry.number);
            if (new_table[hash_key].valid) {
                int i = 0;
                while (new_table[hash_key].valid)
                    hash_key = hashFunction(hash_key + c * ++i + d * i*i);
            }
            new_table[hash_key] = entry;
        }
        table = move(new_table);
        std::cout << "Rehashed successfully.\nNew capacity: " << this->table.size() << "\n\n" ;
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
    
    Subscription find(ui32 key) {
        ui32 hash_key = hashFunction(key);
        Subscription found = table[hash_key];
        if (found.valid && found.number == key)
            return found;
 
        int i = 0;
        while (i < 100) {
            hash_key = hashFunction(hash_key + c * ++i + d * i*i);
            found = table[hash_key];
            if ((found.valid) && (found.number == key))
                return found;
        }

        std::cout << "Can't find entry with this key\n";
        return Subscription();
    }

    void del(ui32 key) {
        ui32 hash_key = hashFunction(key);
        Subscription found = table[hash_key];
        if (found.valid && found.number == key) {
            table[hash_key].print();
            std::cout << "Successfully deleted from " << hash_key << "\n\n";
            table[hash_key] = Subscription();
            num_of_elements--;
            return;
        }
        int i = 0;
        while (i < 100) {
            hash_key = hashFunction(hash_key + c * ++i + d * i*i);
            found = table[hash_key];
            if ((found.valid) && (found.number == key)) {
                table[hash_key].print();
                std::cout << "Successfully deleted from " << hash_key << "\n\n";
                table[hash_key] = Subscription();
                num_of_elements--;
                return;
            }
        }

        std::cout << "Can't find entry with this key\n";
    }

    void print() {
        for(auto entry : *this)
            if (entry.valid)
                entry.print();
    }
    void print_full() {
        for (int i = 0; i < table.size(); ++i) {
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
