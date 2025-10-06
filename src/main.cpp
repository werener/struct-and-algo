#include "Tree.hpp"
char get_char() {
    string _;
    std::getline(std::cin, _);
    return _[0];
}
char context_menu() {
    std::cout 
            << "\nChoose what to do:\n"
            << "0. Exit\t\t"    <<  "3. Print\n"
            << "1. Insert\t"    <<  "4. Find sum of leaves\n"
            << "2. Traverse\t"  <<  "5. Find height\n\n";
    return get_char();
}

void cli() {
    std::cout << "Enter all characters to fill the tree:\n";
    string _;
    std::getline(std::cin, _);

    Tree tree(_);
    std::cout << "Tree:\n"; 
    tree.print();

    while (true) {
        char choice = context_menu();
        switch(choice) {
            case '0':
                return;
            case '1':
                std::cout << "Enter char to insert:\t";
                tree.insert(get_char()); 
                std::cout << std::endl; break;    
            case '2':
                tree.traverse();
                std::cout << std::endl; break;
            case '3':
                std::cout << std::endl;
                tree.print();
                break;
            case '4':
                std::cout << "Sum of all leaves is " << tree.sum_of_leaves() << "\n"; break;
            case '5':
                std::cout << "Height is " << tree.height() << "\n"; break;
            default:
                std::cout << "No such option\n";        
        }
    }
}

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    cli();
}

