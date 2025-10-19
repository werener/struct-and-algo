#include "lib.hpp"
#include "Shannon-Fano.cpp"

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    auto table = get_compression_table("anusa");
    for(auto entry : table) {
        std::cout << entry.first << " " << entry.second << "\n";
    }
    std::cout << compress("мой котёнок очень странный, он не хочет есть сметану, к молоку не прикасался и от рыбки отказался.");
}