#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "Graph.h"
#include <vector>
#include <utility>

class ListGraph : public Graph {
private:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;

public:
    ListGraph(int v);
    void addEdge(int u, int v, int weight) override;
    void display() const override;
    int getVerticesCount() const override;
    std::vector<Edge> getEdges() const override;
};

#endif // LIST_GRAPH_H
