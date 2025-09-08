#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#define u unsigned

using std::cout;

void task_1_a_b() {
    u char x;
    x = 255;
    u char num_bit;
    num_bit = 5;

    x &= (~(1 << num_bit - 1));

    std::cout << "Fifth bit:  " << (int)x << std::endl;

    x = 255;
    x &= (~(1 << num_bit - 1));

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

int main() {
    return 0;
}
