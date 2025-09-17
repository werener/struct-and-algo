#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <ios>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>

typedef unsigned u;

typedef std::uint64_t ui64;
typedef std::string string;

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

string read_until_escape(std::ifstream &file) {
    char cur;
    string s = "";
    cur = file.get();
    while (cur != '\0') {
        s.push_back(cur);
        cur = file.get();
        if (file.eof())
            return s;
    }
    return s;
}

std::vector<Book> read_file(std::ifstream &file) {
    std::vector<Book> entries;
    ui64 ISBN;
    char cur;
    while (true) {
        //  get ISBN
        file.read((char*) &ISBN, sizeof(ui64));
        //  check if the file has ended
        if(file.eof())
            return entries;
        entries.push_back(Book(
            ISBN, 
            read_until_escape(file),    //  author
            read_until_escape(file)     //  title
        ));
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

    static bool compare(Cell c1, Cell c2) {
        return c1.ISBN < c2.ISBN;
    }
    
    void print() {
        std::cout << this->ISBN << " " << this->offset << "\n";
    }
};

std::vector<Cell> read_to_table(std::ifstream &file) {
    file.seekg(0);
    std::vector<Cell> table;
    Cell cell(0, 0);
    while (true) {
        //  get current cell's contents
        file.read((char*) &cell.ISBN, sizeof(ui64));
        cell.offset = file.tellg();
        //  skip to next key
        read_until_escape(file);
        read_until_escape(file);
        if (file.eof()) {
            std::sort(table.begin(), table.end(), Cell::compare);
            return table;
        }
        table.push_back(cell);
    }
}

//  creation of lookup table
size_t* make_lookup(std::vector<Cell> table) {
    int n = log2(table.size());
    size_t *lookup_table = (size_t*)malloc(n * sizeof(size_t));
    
    int pow = 1;
    int i = 0;
    do {
        pow <<= 1;
        lookup_table[i] = (n + (pow >> 1)) / pow;
    } while (lookup_table[i++] != 0);
    return lookup_table;
}

typedef std::pair<std::vector<Cell>, size_t*> ttp;
int uniform_binary_search(ttp pair, ui64 key) {
    std::vector<Cell> table = pair.first;
    size_t *lookup_table = pair.second;
    // mid point
    size_t cur = lookup_table[0] - 1;

    int i = 0;
    while (lookup_table[i] != 0) {
        if (key == table[cur].ISBN)
            return cur;
        else if (key < table[cur].ISBN)
            cur -= lookup_table[++i];
        else
            cur += lookup_table[++i];
    }
    return cur;
}

Book get_cell_info(Cell cell, std::ifstream &file) {
    file.seekg(cell.offset);
    return Book(
        cell.ISBN, 
        read_until_escape(file),
        read_until_escape(file)
    );
}

using namespace std::chrono;

void task1();
void task2();
void task3();
int main() {
    
}
void task3() {
    write_to_file(100);
    std::ifstream f("./files/data.dat", std::ios::binary);
    std::vector<Cell> table = read_to_table(f);
    f.close();
    // get key of the first entry to check the worst case scenario
    auto search_for = table[0];
    std::cout << "Looking for:\t";
    search_for.print();
    auto lookup = make_lookup(table);
    for (int i = 0; i < 3; ++i) {
        std::ifstream f("./files/data.dat", std::ios::binary);
        // get measurement
        auto start = high_resolution_clock::now();
        Cell found_cell = table[
            uniform_binary_search(ttp(table, lookup), search_for.ISBN)
        ];
        auto end = high_resolution_clock::now();

        Book found_book = get_cell_info(found_cell, f);
        // output
        double duration = duration_cast<microseconds>(end - start).count();
        std::cout << "Measurement #" << i + 1 << ": " << duration / 1000 << " ms\n Found:\t";
        found_book.print();
    }
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