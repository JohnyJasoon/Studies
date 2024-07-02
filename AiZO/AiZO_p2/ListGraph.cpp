#include "ListGraph.h"
#include <iostream>

ListGraph::ListGraph(int v) : vertices(v), adjList(v) {}

void ListGraph::addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
    adjList[v].emplace_back(u, weight); // Assuming undirected graph
}

void ListGraph::display() const {
    std::cout << "List Representation:\n";
    for (int i = 0; i < vertices; ++i) {
        std::cout << i << ": ";
        for (const auto& [v, weight] : adjList[i]) {
            std::cout << "(" << v << ", " << weight << ") ";
        }
        std::cout << std::endl;
    }
}

int ListGraph::getVerticesCount() const {
    return vertices;
}

std::vector<Edge> ListGraph::getEdges() const {
    std::vector<Edge> edges;
    for (int u = 0; u < vertices; ++u) {
        for (const auto& [v, weight] : adjList[u]) {
            if (u < v) { // Avoid duplicate edges in undirected graph
                edges.push_back({ u, v, weight });
            }
        }
    }
    return edges;
}
