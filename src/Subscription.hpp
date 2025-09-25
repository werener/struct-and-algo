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