#include "lib.hpp"


typedef size_t Vertex;

struct Edge {
    union { Vertex u; Vertex from; };
    union { Vertex v; Vertex to; };
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
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    Graph(size_t size, std::vector<string> edges={}) {
        this->size = size;
        vertices = std::vector<Vertex>(size);
        std::iota(vertices.begin(), vertices.end(), 0);
        
        size_t u, v;
        i64 w;
        for (string edge : edges) {
            std::istringstream iss(edge);
            iss >> u >> v >> w;
            if (u < size && v < size && u != v)
                this->add_edge(u, v, w);
        }
    }

    void add_vertex() { 
        vertices.push_back(size); 
        std::cout << "Created new vertex #" << size++ << std::endl;
    }

    void add_edge(Vertex u, Vertex v, i64 w) {
        if (u == v)
            std::cout << "Trying to create a self-loop\n";
        else if (u < size && v < size)
            edges.push_back(Edge(u, v, w));
        else
            std::cout << "One of the vertices doesn't exist\n";
    }
    void add_non_directed_edge(Vertex u, Vertex v, i64 w) {
        if (u == v)
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
            std::cout << e.u << " " << e.v << "  w = " << e.w << "\n";
    }
};