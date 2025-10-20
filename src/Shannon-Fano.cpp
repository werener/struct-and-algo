#include "lib.hpp"

struct Symbol {
    union { char c; char ch; char character; };
    union { ui64 f; ui64 freq; ui64 frequency; };
    string code;

    Symbol(char c, ui64 f) { this->c = c; this->f = f; }
    
    static bool compare(Symbol a, Symbol b) {
        return a.freq > b.freq;
    }
};

void SFsplit(std::vector<Symbol>& symbols, int left, int right, string currentCode="") {
    if (left > right) 
        return;
    if (left == right) {
        symbols[left].code = currentCode;
        return;
    }
    
    ui64 len = 0;
    for (int i = left; i <= right; ++i) 
        len += symbols[i].f;
    
    ui64 s = 0;
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

/*    creating compression and decompression tables       */
#define uomap std::unordered_map

uomap<char, string> create_compression_table(string data) {
    std::vector<Symbol> symbols;
    uomap<char, ui64> frequency_map;
    uomap<char, string> compression_table;

    for (char c : data) 
        frequency_map[c]++;
    for (auto char_freq : frequency_map) 
        symbols.push_back(Symbol(char_freq.first, char_freq.second));

    std::sort(symbols.begin(), symbols.end(), Symbol::compare);
    SFsplit(symbols, 0, symbols.size() - 1);
    for (auto& symbol : symbols) 
        compression_table[symbol.character] = symbol.code;
    return compression_table;
}
uomap<string, char> create_decompression_table(uomap<char, string> compression_table) {
    uomap<string, char> decompression_table;
    for (auto pair : compression_table) 
        decompression_table[pair.second] = pair.first;
    return decompression_table;
}

#undef uomap


/*      compression and decompression      */
string compress(string data, std::unordered_map<char, string> compression_table) {
    string compressed_data("");
    for (char c : data)
        compressed_data += compression_table[c];
    return compressed_data;
}

string decompress(string compressed_data, std::unordered_map<char, string> compression_table) {
    auto decompression_table = create_decompression_table(compression_table);

    string cur_code(""), data("");
    for (char c : compressed_data) {
        cur_code.push_back(c);
        if (decompression_table.find(cur_code) != decompression_table.end()) {
            data.push_back(decompression_table[cur_code]);
            cur_code = "";
        }
    }
    return data;
}
