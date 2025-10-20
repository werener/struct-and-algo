#include "lib.hpp"
#include "Shannon-Fano.cpp"
#include "Huffman.cpp"

int main() {
    const string s = "Жижикин Леонид Сергеевич";
    std::cout << "\tShannon-Fano\n";
    auto table = create_compression_table(s);
    std::cout << "Compressed: " << compress(s, table) << std::endl;
    std::cout << "Decompressed: " << decompress(compress(s, table), table) << "\n\n";

    std::cout << "\tHuffman\n";
    auto huffman_tree = create_huffman_tree(s);
    std::cout << "Compressed: " << encode(s) << std::endl;
    std::cout << "Decompressed: " << decode(encode(s), huffman_tree) << "\n";
}