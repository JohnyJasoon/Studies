#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

struct Edge {
    int u, v, weight;
};

class Graph {
public:
    virtual ~Graph() = default;
    //virtual void displayMatrix() const = 0;
    //virtual void displayList() const = 0;
    virtual void addEdge(int u, int v, int weight) = 0;
    virtual void display() const = 0;
    virtual int getVerticesCount() const = 0;
    virtual std::vector<Edge> getEdges() const = 0;
};

#endif // GRAPH_H