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


const ui64 CONSTRAINT_MIN = 100000000000;
const ui64 CONSTRAINT_MAX = 1000000000000 - 1;

struct Book {
    ui64 ISBN;
    string author;
    string title;
    Book(ui64 ISBN, string author, string title) {
        this->ISBN = ISBN;
        this->author = author;
        this->title = title;
    }
    void print() {
        std::cout << ISBN <<  " " << author << " " << title << "\n";
    }
};

std::random_device rd;
Book gen_entry() {
    std::mt19937_64 gen_key(rd());
    std::uniform_int_distribution<ui64> distribution(CONSTRAINT_MIN, CONSTRAINT_MAX);
    string author = string(".."), title = string(1, 'A' + rand() % 26);
    //  ISBN
    ui64 ISBN = distribution(gen_key);
    //  author
    author.insert(author.begin(), 'A' + rand() % 26);
    author.insert(author.begin() + 2, 'A' + rand() % 26);
    author.insert(author.end(), 'A' + rand() % 26);
    for (int i = 0; i < 5 + rand() % 6;++i)
        author.insert(author.end(), 'a' + rand() % 26);
    //  title
    for (int i = 0; i < 9 + rand() % 16; ++i)
        title.insert(title.end(), 'a' + rand() % 26);
    return Book(ISBN, author, title);
}

void write_to_file(int num_entries, string path="./files/data.dat") {
    std::ofstream file(path, std::ios::binary);
    ui64 ISBN;
    string author, title;
    for(int i = 0; i < num_entries; ++i) {
        Book book = gen_entry();
        file.write((char*) &book.ISBN, sizeof(ui64));
        //  \0 - terminating character
        file.write(book.author.c_str(), book.author.length() + 1);
        file.write(book.title.c_str(), book.title.length() + 1);
    }
    file.close();
}

std::vector<Book> read_file(std::ifstream &file) {
    std::vector<Book> entries;
    ui64 ISBN;
    string author, title;
    char cur;
    while (!file.eof()) {
        //  get ISBN
        file.read((char*) &ISBN, sizeof(ui64));
        //  get Author
        author = "";
        cur = file.get();
        while (cur != '\0') {
            author.push_back(cur);
            cur = file.get();
            if (file.eof())
                return entries;
        }
        //  get Title
        title = "";
        cur = file.get();
        while (cur != '\0') {
            title.push_back(cur);
            cur = file.get();
            if (file.eof())
                return entries;   
        }
        entries.push_back(Book(ISBN, author, title));
    }
    return entries;
}

int main() {
    write_to_file(100);
    std::ifstream f("./files/data.dat", std::ios::binary);
    auto entries = read_file(f);
    f.close();
    for (int i = 0; i < entries.size(); i += 10)
        entries[i].print();
}