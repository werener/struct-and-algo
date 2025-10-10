#include "lib.hpp"


typedef size_t Vertex;
struct Edge {
    union { Vertex u; Vertex from; Vertex source; };
    union { Vertex v; Vertex to; Vertex dest;};
    union { i64 w; i64 weight; };

    Edge() {}
    Edge(Vertex u_, Vertex v_, i64 w_) {
        u = u_;
        v = v_;
        w = w_;
    }
};


struct Graph {
    size_t size;
    std::vector<Edge> edges;

    Graph(size_t size, std::vector<string> edges={}) {
        this->size = size;
        size_t u, v;
        i64 w;
        for (string edge : edges) {
            std::istringstream iss(edge);
            iss >> u >> v >> w;
            if (u <= size && v <= size && u != v)
                this->add_edge(u, v, w);
        }
    }

    void add_vertex() { std::cout << "Created new vertex #" << size++ << std::endl; }

    void add_edge(Vertex u, Vertex v, i64 w) {
        if (u-- == v--)
            std::cout << "Trying to create a self-loop\n";
        else if (u < size && v < size)
            edges.push_back(Edge(u, v, w));
        else
            std::cout << "One of the vertices doesn't exist\n";
    }
    void add_edge(string edge){
        size_t u, v;
        i64 w;
        std::istringstream iss(edge);
        iss >> u >> v >> w;
        if (u <= size && v <= size && u != v)
            this->add_edge(u, v, w);
    }
    
    void add_non_directed_edge(string edge) {
        size_t u, v;
        i64 w;
        std::istringstream iss(edge);
        iss >> u >> v >> w;
        if (u <= size && v <= size && u != v)
            this->add_non_directed_edge(u, v, w);
    }

    void add_non_directed_edge(Vertex u, Vertex v, i64 w) {
        if (u-- == v--)
            std::cout << "Trying to create a self-loop\n";
        else if (u < size && v < size) {
            edges.push_back(Edge(u, v, w));
            edges.push_back(Edge(v, u, w));
        }
        else
            std::cout << "One of the vertices doesn't exist\n";
    }

    void print_edges() {
        for (Edge e : edges)
            std::cout << e.u + 1 << " " << e.v + 1 << "  w = " << e.w << "\n";
    }

    std::vector<i64> bellman_ford(Vertex source) {
        std::vector<i64> distance(size, INT_MAX);
        distance[--source] = 0;
        //  construct distance vector for each vertex
        for (size_t i = 0; i < size - 1; ++i) 
            for (const Edge e : this->edges)
                if (distance[e.from] != INT_MAX && distance[e.from] + e.weight < distance[e.to]) 
                    distance[e.to] = distance[e.from] + e.weight;            
        
        //  check for negative-weight cycles
        for (const Edge e : this->edges) {
            if (distance[e.from] != INT_MAX &&
                distance[e.from] + e.weight < distance[e.to]) {
                std::cout << "Graph contains negative weight cycle\n" << "Distance to any node is infinitely small\n";
                std::fill(distance.begin(), distance.end(), INT_MIN);
                return distance;
            }
        }

        //  result
        std::cout << "Vertex distances from " << source + 1 << "\n";
        for (size_t i = 0; i < size; ++i) {
            if (distance[i] == INT_MAX)
                std::cout << source + 1 << " -> " << i + 1 << "\t\t" << "UNREACHABLE\n";
            else
                std::cout << source + 1 << " -> " << i + 1 << "\t\t" << distance[i] << "\n";
        }
        return distance;
    }
};