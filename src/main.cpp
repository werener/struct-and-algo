#include "lib.hpp"
#include "Trie.hpp"

void task_1();
void task_2();

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    // task_1();
    task_2();
}


    const string PUNCTUATION_SEPARATORS = ",\n\t.-:;@#~\"{}[]()!?";
    const string PUNCTUATION_CONNECTORS = "-:_`\'";
string preprocess(string text) {
    for (auto s : PUNCTUATION_SEPARATORS) 
        std::replace( text.begin(), text.end(), s, ' ' );

    for (auto s : PUNCTUATION_CONNECTORS) 
        text.erase(std::remove(text.begin(), text.end(), s), text.end());
    
    std::transform( text.begin(), text.end(), text.begin(), 
                    [](unsigned char c){ return std::tolower(c); } );
    return " " + text + " ";
}

string highlight_matches(string text, std::vector<std::tuple<string, size_t, size_t>> matches, bool highlight_all_prefixes=true) {
    string text_highlighted = text;
    int count_inserts = 0;
    for(auto match : matches) {
        string word;
        size_t start, end;
        
        std::tie(word, start, end) = match;
        /*
            Если добавить еще 1 char в рамки вхождения, то этот символ -
            пробел тогда и только тогда, когда этим вхождением является
            искомое слово, а не сокращение
        */
        if (text.substr(start, end - start + 1) != word + " ") {
            //  word has already been higlighted if it has the right '|' 
            auto pos_h = text_highlighted.substr(start + count_inserts, end - start + 1).find("|");
            if (pos_h != string::npos) {
                if (highlight_all_prefixes)
                    text_highlighted.insert(end + count_inserts++, "\\");
                continue;
            }
            text_highlighted.insert(end + count_inserts++, "|");
            text_highlighted.insert(start + count_inserts++, "|");
        }
    }
    return text_highlighted;
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
            if (!cur_string.empty()) 
                patterns.insert(" " + cur_string);
            cur_string = "";
            continue;
        }
        cur_string.push_back(c);
    } if (!cur_string.empty()) 
        patterns.insert(" " + cur_string);
    
    
    //  search
    Trie trie = Trie(patterns);
    auto matches = trie.search(text);
    const bool HIGHLIGHT_ALL = true;
    std::cout << "\tHighlighted prefixes:\n" << highlight_matches(text, matches, HIGHLIGHT_ALL) << "\n";
    }





std::vector<int> computeLPSArray(string pattern, int m) {
    int length = 0;
    std::vector<int> LPS(pattern.length());
    LPS[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == 
            pattern[length++]) {
            LPS[i++] = length;
        }
        else {
            if (length != 0)
                length = LPS[length - 1];
            else 
                LPS[i++] = 0;
        }
    }
    return LPS;
}

std::vector<int> KMP(string pattern, string text) {
    int m = pattern.length();
    int n = text.length();

    std::vector<int> ans;

    std::vector<int> LPS = computeLPSArray(pattern, m);

    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            ans.push_back(i - j);
            j = LPS[j - 1];
        }

        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) 
                j = LPS[j - 1];
            else 
                i++;
        }
    }
    return ans;
}

void task_2() {
    std::ifstream file("./files/task1_apparent.txt");
    string text;
    getline(file, text);
    auto a =  KMP("word_matchabcsd", text);
    for (auto c : a)
        std::cout << c << "\n";
}

