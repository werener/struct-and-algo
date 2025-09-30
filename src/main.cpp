#include "lib.hpp"
#include "Trie.hpp"

void task_1();
void task_2();

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    task_1();
}


char lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c - ('X' - 'x');
    return c;
}


const string PUNCTUATION_SEPARATORS = ",\n\t.-:;@#~\"{}[]()!?";
const string PUNCTUATION_CONNECTORS = "-:_`\'";
string preprocess(string text) {
    for (auto s : PUNCTUATION_SEPARATORS) {
        std::replace( text.begin(), text.end(), s, ' ' );
    }
    for (auto s : PUNCTUATION_CONNECTORS) {
        text.erase(std::remove(text.begin(), text.end(), s), text.end());
    }
    std::transform( text.begin(), text.end(), text.begin(), 
                    [](unsigned char c){ return std::tolower(c); } );
    return " " + text + " ";
}

void task_1 () {
    std::unordered_set<string> patterns{};

    std::ifstream file("./files/task1_apparent.txt");
    string text_raw;
    getline(file, text_raw);
   
    
    string text = preprocess(text_raw);
    string cur_string;
    std::cout << "\tSearching in:\n" << text << "\n\n";

    //  create set of searched prefixes
    for (char c : text) {
        if (c == ' ') {
            if (cur_string != "") 
                patterns.insert(" " + cur_string);
            cur_string = "";
            continue;
        }
        cur_string.push_back(c);
    }
    if (cur_string != "") 
        patterns.insert(" " + cur_string);
    
    
    //  search
    Trie trie = Trie(patterns);
    auto matches = trie.search(text);
    
    /*
        Если добавить еще 1 char в рамки вхождения, то этот символ -
        пробел тогда и только тогда, когда этим вхождением является
        всё искомое слово, а не сокращение
    */
    
    string text_highlighted = text;
    int count_inserts = 0;
    for(int i = 0; i < matches.size(); ++i) {
        string word;
        size_t start, end;
        
        std::tie(word, start, end) = matches[i];
        // std::cout << word << ":  at " << start << " - " << end << "\n";
        if (text.substr(start, end - start + 1) != word + " ") {
            //  if the word has already been highlighted
            if (text_highlighted.substr(start + (2  * count_inserts), end - start + 1).find("|") != string::npos) {
                text_highlighted.insert(end + (2  * count_inserts), "|");
                text_highlighted.insert(start - 1 + (2 * count_inserts), "|");
            }
            else {
                text_highlighted.insert(end + (2  * count_inserts), "|");
                text_highlighted.insert(start + 1 + (2 * count_inserts), "|");
            }
            ++count_inserts;
            // std::cout << "\tHighlighted prefixes:\n" << text_highlighted << "\n";
        }
        // std::cout << string(30, '-') << "\n";
        
    }
    std::cout << "\tHighlighted prefixes:\n" << text_highlighted << "\n";
}