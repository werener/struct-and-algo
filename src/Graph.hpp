#include "lib.hpp"
typedef size_t Vertex;

struct Edge {
    union { Vertex u; Vertex from; };
    union { Vertex v; Vertex to; };
    union { i64 w; i64 weight; };

    Edge(Vertex u_, Vertex v_, i64 w_) {
        u = u_;
        v = v_;
        w = w_;
    }
};


struct Graph {
    size_t size;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    Graph(size_t size, std::vector<string> edges={}) {
        this->size = size;
        vertices = std::vector<Vertex>(size);
        std::iota(vertices.begin(), vertices.end(), 0);

        for (string edge : edges) {
            
        }
    }

    void add_vertex() { 
        vertices.push_back(size); 
        std::cout << "Created new vertex #" << size++ << std::endl;
    }

    void add_edge(Vertex u, Vertex v, i64 w) {
        if (u < size && v < size)
            edges.push_back(Edge(u, v, w));
        else
            std::cout << "One of the vertices doesn't exist\n";
    }
};