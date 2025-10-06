#include "Graph.hpp"


int main() {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    Graph g(3, std::vector<string>{"1 2 2", "0 2 -1", "0 3 229", "2 2 2"});
    g.print_edges();
}   