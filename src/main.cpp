#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <ios>
#include <string>
#include <random>

#define u unsigned
#define ui64 std::uint64_t
#define string std::string


static const char upper[26] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 
    'O', 'P', 'Q', 'R', 'S', 'T', 
    'U', 'V', 'W', 'X', 'Y', 'Z',
};
static const char lower[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
};
const ui64 CONSTRAINT_MIN = 100000000000;
const ui64 CONSTRAINT_MAX = 1000000000000 - 1;


std::random_device rd;

std::tuple<ui64, string, string> gen_entry() {
    std::mt19937_64 gen_key(rd());
    std::uniform_int_distribution<ui64> distribution(CONSTRAINT_MIN, CONSTRAINT_MAX);
    string author = string(".."), title = string(1, upper[rand() % 26]);
    //  ISBN
    ui64 ISBN = distribution(gen_key);
    //  author
    author.insert(author.begin(), upper[rand() % 26]);
    author.insert(author.begin() + 2, upper[rand() % 26]);
    author.insert(author.end(), upper[rand() % 26]);
    for (int i = 0; i < 5 + rand() % 6;++i)
        author.insert(author.end(), lower[rand() % 26]);
    //  title
    for (int i = 0; i < 9 + rand() % 16; ++i)
        title.insert(title.end(), lower[rand() % 26]);

    return std::tuple<ui64, string, string>{ISBN, author, title};
}


void write_to_file(int num_entries, string path="./files/data.dat") {
    std::ofstream file(path, std::ios::binary);
    ui64 ISBN;
    string author, title;
    for(int i = 0; i < num_entries; ++i) {
        tie(ISBN, author, title) = gen_entry();
        file.write((char*) &ISBN, sizeof(ui64));
        //  \0 - terminating character
        file.write(author.c_str(), author.length() + 1);
        file.write(title.c_str(), title.length() + 1);
    }
    file.close();
}


int main() {
    write_to_file(100);
}