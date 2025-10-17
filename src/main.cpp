#include "Graph.hpp"

Graph user_input() {
    size_t size;    
    std::vector<string> edges;    
    std::cout << "Enter amount of Vertices:\t"; std::cin >> size;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Start entering your Edges, empty to exit:\n";
    string s="00 00 00";
    while (true) {
        std::getline(std::cin, s);
        if (s == "\0")
            break;
        edges.push_back(s);
    }
    return Graph(size, edges);
}

void task() {
    const std::vector<string> edges = 
    { 
        "1 2 23", "1 3 12",
        "2 3 25", "2 5 22", "2 8 35", 
        "3 4 18", 
        "5 6 23",  "5 7 14", 
        "6 7 24", 
        "7 8 16" 
    };
    Graph g(8);
    for (const string edge : edges) {
        g.add_non_directed_edge(edge);
    }
    // g.print_edges();
    for (int i = 0; i < 8; ++i) {
        std::cout << "\nVERTEX #" << i + 1 << "\n";
        g.bellman_ford(i + 1, true);
    }
}

void task_one_vertex(size_t vertex) {
    const std::vector<string> edges = 
    { 
        "1 2 23", "1 3 12",
        "2 3 25", "2 5 22", "2 8 35", 
        "3 4 18", 
        "5 6 23",  "5 7 14", 
        "6 7 24", 
        "7 8 16" 
    };
    Graph g(8);
    for (const string edge : edges) {
        g.add_non_directed_edge(edge);
    }
    g.bellman_ford(vertex, true);

}

void task_one_route(size_t from, size_t to) {
    const std::vector<string> edges = 
    { 
        "1 2 23", "1 3 12",
        "2 3 25", "2 5 22", "2 8 35", 
        "3 4 18", 
        "5 6 23",  "5 7 14", 
        "6 7 24", 
        "7 8 16" 
    };
    Graph g(8);
    for (const string edge : edges) {
        g.add_non_directed_edge(edge);
    }

    if (to <= 8)
        std::cout << "Distance from " << from << " to " << to << " is " << g.bellman_ford(from)[to - 1] << std::endl; 
    else
        std::cout << "Destination doesn't exist\n";
    }



int main() {
    // task_one_route(1, 7);
    task();

    
    // Graph g = user_input();
    // g.print_edges();
    // g.bellman_ford(1);
}   