#include "Graph.hpp"


int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    Graph g(3);
    for(auto a: g.vertices) {
        std::cout << a;
    }
}   