#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <ios>
#include <string>
#include <random>
#include <chrono>

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
        if (this->ISBN == CONSTRAINT_MAX + 1)
            std::cout << "No such book\n";
        else
            std::cout << ISBN <<  " " << author << " " << title << "\n";
    }
};

void task1();
void task2();

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

Book linear_search(ui64 key, std::ifstream &file) {
    for (auto book: read_file(file)) 
        if (book.ISBN == key) 
            return book;
    return Book(CONSTRAINT_MAX + 1, "", "");
}

struct Cell {
    ui64 ISBN;
    std::streampos offset;


    Cell(ui64 ISBN, std::streampos offset) {
        this->ISBN = ISBN;
        this->offset = offset;
    }

    void print() {
        std::cout << this->ISBN << " " << this->offset << "\n";
    }

    static bool compare(Cell c1, Cell c2) {
        return c1.ISBN < c2.ISBN;
    }
};

std::vector<Cell> read_to_table(std::ifstream &file) {
    file.seekg(0);
    std::vector<Cell> table;
    Cell cell(0, 0);
    while (!file.eof()) {
        //  get current cell's contents
        file.read((char*) &cell.ISBN, sizeof(ui64));
        cell.offset = file.tellg();
        // 
        char cur;
        cur = file.get();
        while (cur != '\0') {
            cur = file.get();
            if (file.eof())
                return table;
        }
        cur = file.get();
        while (cur != '\0') {
            cur = file.get();
            if (file.eof())
                return table;   
        }
        table.push_back(cell);
    }
    return table;
}

using namespace std::chrono;
int main() {
    std::ifstream f("./files/data.dat", std::ios::binary);
    auto table = read_to_table(f);
    for(auto a:table)
        a.print();

}

void task2() {
    write_to_file(100);
    // get key of the last entry to check the worst case scenario
    std::ifstream f("./files/data.dat", std::ios::binary);
    auto entries = read_file(f);
    ui64 last_entry_key = entries[entries.size() - 1].ISBN;
    for (int i = 0; i < 3; ++i) {
        std::ifstream f("./files/data.dat", std::ios::binary);
        // get measurement
        auto start = high_resolution_clock::now();
        Book book = linear_search(last_entry_key, f);
        auto end = high_resolution_clock::now();
        double duration = duration_cast<microseconds>(end - start).count();
        // output
        std::cout << "Measurement #" << i + 1 << ": " << duration / 1000 << " ms\n";
        book.print();
    }
}
void task1() {
    write_to_file(100);
    std::ifstream f("./files/data.dat", std::ios::binary);
    auto entries = read_file(f);
    f.close();
    for (int i = 0; i < entries.size(); i += 10)
        entries[i].print();
}