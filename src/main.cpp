#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>


#define u unsigned

using std::cout;

void task_1_a_b() {
    u char x;
    x = 255;
    u char num_bit;
    num_bit = 5;

    x &= (~(1 << (num_bit - 1)));

    std::cout << "Fifth bit:  " << (int)x << std::endl;

    x = 255;
    num_bit = 7;
    x &= (~(1 << (num_bit - 1)));

    std::cout << "Seventh bit:  " << (int)x << std::endl;
}

void task_1_c() {
    //setlocale(LC_ALL, "Russian"); // russian language support
    u int x = 25;
    const int n = sizeof(int) * 8; 
    unsigned mask = (1 << n - 1); 
    cout << "Initial mask: " << std::bitset<n>(mask) << "\n";
    cout << "Result: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & mask) >> (n - i));
        mask = mask >> 1;
    }
    cout << std::endl;
    system("pause");
}

void task_2_a() {
    u short magnitude, n;
    cout << "Input amount of numbers: ";
    std::cin >> n;
    cout << "Enter " << n << " numbers: ";
    u char bitarr = 0;

    u short input;
    for (int i = 0; i < n; ++i) {
        std::cin >> (input);
        bitarr = bitarr | (1 << input);
    }
    auto bitset = std::bitset<8>(bitarr);
    for (int i = 0; i < 8; ++i)
        if (bitset[i] == 1)
            cout << i << " ";
}
    
void task_2_b() {
    u short n;
    cout << "Input amount of numbers: ";
    std::cin >> n;
    cout << "Enter " << n << " numbers: ";

    u long long bitarr = 0;

    u short input;
    for (int i = 0; i < n; ++i) {
        std::cin >> (input);
        bitarr = bitarr | ((long long)1 << input);
    }
    auto bitset = std::bitset<64>(bitarr);
    for (int i = 0; i < sizeof(bitarr) * 8; ++i)
        if (bitset[i] == 1)
            cout << i << " ";
}

void task_2_с() {
    const u char CHARS_IN_LL = sizeof(long long) / sizeof(char), BIT_IN_CHAR = 8;
    u short n, input;
    cout << "Input amount of numbers: "; std::cin >> n;

    u char *bitarr  = (u char*)malloc(sizeof(long long));
    memset(bitarr, 0, sizeof(long long));

    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> (input);
        bitarr[input / (CHARS_IN_LL)] |= (1 << (input % BIT_IN_CHAR));
        //cout << "Slice: " << input / CHARS_IN_LL << " Index: " << (input % 8) << "\n";
    }
    auto bitset = std::bitset<BIT_IN_CHAR>();
    for (int i = 0; i < CHARS_IN_LL; ++i) {
        bitset = std::bitset<BIT_IN_CHAR>(bitarr[i]);
        //cout << bitset << "\n";
        for (int j = 0; j < BIT_IN_CHAR; ++j)
            if (bitset[j] == 1)
                cout << j + i * BIT_IN_CHAR << " ";
    }
}

void generate_file(std::string path) {
    std::fstream file(path, std::ios::out);
    std::vector<u int> vec;
    for (u int i = 1000000; i < 10000000; ++i)
        vec.push_back(i);
    auto rng = std::default_random_engine {};
    std::shuffle(vec.begin(), vec.end(), rng);

    for (u int el: vec) 
        file << el << '\n';
    file.close();
}

const std::string PATH_IN = "/mnt/c/Users/werener/Desktop/gitfolder/struct-and-algo/files/task5.txt";
const std::string PATH_OUT = "/mnt/c/Users/werener/Desktop/gitfolder/struct-and-algo/files/task5_result.txt";

const int N = 10000000 - 1000000;
const int CUTOFF = N / 2;
void task_3_real() {
    std::fstream in(PATH_IN), out(PATH_OUT);
    // this vector is 4.5mil bit (or ~0.54MB) 
    std::vector<bool> bitarr(CUTOFF, 0); 
    int element;
    while (in) {
        in >> element;
        if (element < CUTOFF - 1)
            bitarr[element - 1000000] = 1;
    }
    // reset pointer in file
    in.clear();
    in.seekg(0);
    fill(bitarr.begin(), bitarr.end(), 0);
    while (in) {
        in >> element;
        if (element >= CUTOFF + 1000000 - 1)
            bitarr[element - (CUTOFF + 1000000)] = 1;
    }
    for (int i = 0; i < N; ++i)
        if (bitarr[i])
            out << i << "\n";
    in.close(); out.close();
}

void task_3();


#include <chrono>
using namespace std::chrono;
int main() {
    for (int i = 0; i < 5; ++i) {
        auto start = high_resolution_clock::now();
        task_3_real();
        auto end = high_resolution_clock::now();
        int duration = duration_cast<milliseconds>(end - start).count();
        cout << i + 1 << ": " << duration << "ms" << std::endl; 
    }
}

void task_3() {
    std::fstream in(PATH_IN), out(PATH_OUT);

    /* 1 MB = 1048576 byte = 8388608 bit
    It is a vector<bool> with 8388608 0s
    We need 9 * 10^6, so it's not possible
    to fit the criteria with 7-digit numbers*/

    std::vector<bool> bitarr(N, 0); 
    int element;
    while (in) {
        in >> element;
        bitarr[element - 1000000] = 1;
    }
    for (int i = 0; i < N; ++i)
        if (bitarr[i])
            out << i << "\n";
    in.close(); out.close();
}
