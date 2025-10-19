#include "lib.hpp"

struct Symbol {
    union { char c; char character; };
    union { ui64 f; ui64 frequency; };
    string code;

    Symbol(char c, ui64 f) { this->c = c; this->f = f; }
    
    static bool compare(Symbol a, Symbol b) {
        return a.frequency > b.frequency;
    }
};

void SFsplit(std::vector<Symbol>& symbols, size_t left, size_t right, string currentCode="") {
    if (left > right)
        return;

    if (left == right) {
        symbols[left].code = currentCode;
        return;
    }

    ui64 len = 0;
    for (size_t i = left; i <= right; ++i) 
        len += symbols[i].f;
    

    int s = 0;
    int cur = left;

    for (int i = left; i <= right; ++i) {
        s += symbols[i].frequency;
        if (len - s <= s) {
            // s - l/2 < |s - l/2 - cur_symbol|
            // 2s - l < cur_symbol
            cur = (2 * s - len < symbols[i].frequency) ? i : i - 1;
            break;
        }
    }
    SFsplit(symbols, left, cur, currentCode + "0");
    SFsplit(symbols, cur + 1, right, currentCode + "1");
}

std::unordered_map<char, string> get_compression_table(string data) {
    std::vector<Symbol> symbols;
    std::unordered_map<char, ui64> frequency_map;
    std::unordered_map<char, string> compression_table;

    for (char c : data) 
        frequency_map[c]++;
    for (auto pair : frequency_map) 
        symbols.push_back(Symbol(pair.first, pair.second));
        
    std::sort(symbols.begin(), symbols.end(), Symbol::compare);
    SFsplit(symbols, 0, symbols.size() - 1);
 
    for (auto& symbol : symbols) 
        compression_table[symbol.character] = symbol.code;
    return compression_table;
}

string compress(string data) {
    string compressed_data = "";
    auto table = get_compression_table(data);

    for (char c : data)
        compressed_data += table[c];
    return compressed_data;
}