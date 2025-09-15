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


static const char alphabet[52] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};
const ui64 CONSTRAINT_MIN = 100000000000;
const ui64 CONSTRAINT_MAX = 1000000000000 - 1;


std::random_device rd;

std::tuple<ui64, string, string> gen_entry() {
    std::mt19937_64 gen_key(rd());
    std::uniform_int_distribution<ui64> distribution(CONSTRAINT_MIN, CONSTRAINT_MAX);
    std::uint64_t ISBN = distribution(gen_key);

    string author, title;
    
    return std::tuple<ui64, string, string>{ISBN, author, title};
}


void write_to_file(bool dump_txt=false) {

}


int main() {
    std::cout << (char)('Z' + 1) << " " << (int) 'a';
}