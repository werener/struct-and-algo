#include "lib.hpp"
#include "Trie.hpp"

void task_1();
void task_1_if_reverse();
void task_2();

int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    // task_1();
    task_1_if_reverse();
    // task_2();
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
    std::set<string> patterns{};
    std::ifstream file("./files/task1.txt");
    string text, cur_string;
    getline(file, text);

    //  preprocess the text
    text = preprocess(text);
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

void task_1_if_reverse() {
    std::vector<string> words{};
    std::ifstream file("./files/task_1_rev.txt");
    string text, cur_string;
    getline(file, text);

    //  preprocess the text
    text = preprocess(text);
    std::cout << "\tSearching in:\n" << text << "\n\n";

    //  create set of searched prefixes
    for (char c : text) {
        if (c == ' ') {
            if (!cur_string.empty()) 
                words.push_back(cur_string);
            cur_string = "";
            continue;
        }
        cur_string.push_back(c);
    } if (!cur_string.empty()) 
        words.push_back(cur_string);

    for (int i = 0; i < words.size(); ++i) {
        string checked = words[i];

        std::reverse(checked.begin(), checked.end());
        for (int j = i + 1; j < words.size(); ++j) {
            if (checked == words[j]) {
                std::cout << " #" << i + 1 << " '" << words[i] << "' and #" << j + 1 << " '" <<  words[j] << "'\n" ;
            }
        }
        
    }
}
/*      task 2      */

std::vector<size_t> computeLPSArray(string pattern) {
    int saved_len = 0;
    std::vector<size_t> LPS(pattern.length());

    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[saved_len]) 
            LPS[i++] = ++saved_len;
        else {
            if (saved_len)
                saved_len = LPS[saved_len - 1];
            else 
                LPS[i++] = 0;
        }
    }
    return LPS;
}

std::vector<std::tuple<string, size_t, size_t>> KMP(string pattern, string text) {
    int m = pattern.length();
    int n = text.length();

    std::vector<std::tuple<string, size_t, size_t>> ans {std::tuple{"", 0, 0}};

    std::vector<size_t> LPS = computeLPSArray(pattern);
    
    size_t i = 0, j = 0;
    string cur_found = "";
    while (i < n) {
        if (pattern[j] == text[i]) {
            cur_found.push_back(pattern[j]);
            i++;
            j++;
        }

        if (j == m) {
            ans.push_back(std::tuple{cur_found, i - j, i});
            j = LPS[j - 1];
            cur_found = "";
        }

        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) { 
                j = LPS[j - 1];
                cur_found = "";
            }
            else
                i++;
        }
    }
    return ans;
}

std::tuple<string, size_t, size_t> KMP_first(string pattern, string text) {
    int m = pattern.length();
    int n = text.length();
    std::vector<size_t> LPS = computeLPSArray(pattern);

    size_t i = 0, j = 0;
    string cur_found = "";
    while (i < n) {
        if (pattern[j] == text[i]) {
            cur_found.push_back(pattern[j]);
            i++;
            j++;
        }

        if (j == m) 
            return (std::tuple{cur_found, i - j, i});

        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) { 
                j = LPS[j - 1];
                cur_found = "";
            }
            else
                i++;
        }
    }
    return std::tuple{ "", 0, 0 };
}


void task_2() {
    const int CASES = 3;
    string a_c[CASES] = {"isddkhuf", "scvbrressdg", "aaaaa"};
    string b_c[CASES] = {"dfposgofdgisddkjm", "scvhfjsscvbrrj21", "babaabaaaabaaabaaaaab"};
    for (int i = 0; i < CASES; ++i) {
        string a = a_c[i], b = b_c[i];

        string word; 
        size_t start, end;
        for (int i = a.length(); i >= 0; --i) {
            std::tie(word, start, end) = KMP_first(a.substr(0, i), b);
            if (word != "") {
                std::cout << "found: '" << word << "' with length " << i << "\n";
                b.insert(end, "|");
                b.insert(start, "|");
                std::cout << b << "\n";
                break;
            }
            if (i == 0) {
                std::cout << "found: '" << word << "' with length " << i << "\n";
                b.insert(end, "|");
                b.insert(start, "|");
                std::cout << b << "\n";
            }
        }
        std::cout << std::endl;
    }
}