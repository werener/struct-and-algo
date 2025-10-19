#include "lib.hpp"
#include "Shannon-Fano.cpp"

int main() {
    const string s = "Zhizhikin Leonid Sergeevych";
    auto table = create_compression_table(s);

    // for(auto entry : table) {
    //     std::cout << entry.first << " " << entry.second << "\n";
    // }
    std::cout << "Compressed: " << compress(s, table) << std::endl;
    std::cout << "Decompressed: " << decompress(compress(s, table), table) << std::endl;
}