#include "MatrixGraph.h"
#include <iostream>

MatrixGraph::MatrixGraph(int v) : vertices(v), matrix(v, std::vector<int>(v, 0)) {}

void MatrixGraph::addEdge(int u, int v, int weight) {
    matrix[u][v] = weight;
    matrix[v][u] = weight; // Assuming undirected graph
}

void MatrixGraph::display() const {
    std::cout << "Matrix Representation:\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int MatrixGraph::getVerticesCount() const {
    return vertices;
}

std::vector<Edge> MatrixGraph::getEdges() const {
    std::vector<Edge> edges;
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            if (matrix[i][j] != 0) {
                edges.push_back({ i, j, matrix[i][j] });
            }
        }
    }
    return edges;
}
