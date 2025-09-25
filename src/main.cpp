#include "lib.hpp"
#include "HashTable.hpp"

char user_selection_menu() {
    std::cout 
        << "\n0. Exit program \t" << "1. Insert element \n"
        << "2. Delete element \t"  << "3. Find element \n"
        << "4. Print HashTable \t" << "5. Print HashTable with hash info \n"
        << "Choose what you want to do:\t" ;
    char input;
    std::cin >> input;
    std::cout << "\n";
    if('0' <= input && input <= '5')
        return input; 
    else
        std::cout << "No such option \n\n";
    return user_selection_menu();
     
}

void cli() {
    ui32 init_len;
    std::cout << "Enter amount of numbers to initialize HashTable with:\n";
    if(!(std::cin >> init_len))
        return;

    HashTable table(init_len);
    std::cout << "Table created succesfully\n"; 

    
    while (true) {
        Subscription found;
        ui32 key;
        string name, address;
        char selected_option = user_selection_menu();
        switch (selected_option) {
            case '0':
                return;
            case '1':
                std::cout << "Enter key, name of owner and address (separated by spaces) to insert: \n";
                std::cin >> key >> name >> address;
                table.insert(key, name, address);
                break;
            case '2':
                std::cout << "Enter key to delete: \n";
                std::cin >> key;
                table.del(key);
                break;
            case '3':
                std::cout << "Enter key to find: \n";
                std::cin >> key;
                found = table.find(key);
                if (!found.valid)
                    break;
                std::cout << "Found entry: \n";
                found.print();
                break;
            case '4':
                table.print();
                break;
            case '5':
                table.print_full();
                break;
        }
    }
}

int main() {
    cli();
}