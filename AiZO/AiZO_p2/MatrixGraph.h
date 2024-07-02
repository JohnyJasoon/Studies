#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "Graph.h"
#include <vector>

class MatrixGraph : public Graph {
private:
    int vertices;
    std::vector<std::vector<int>> matrix;

public:
    MatrixGraph(int v);
    void addEdge(int u, int v, int weight) override;
    void display() const override;
    int getVerticesCount() const override;
    std::vector<Edge> getEdges() const override;
};

#endif // MATRIX_GRAPH_H
