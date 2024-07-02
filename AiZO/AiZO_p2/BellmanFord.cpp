#include "BellmanFord.h"
#include <vector>
#include <iostream>
#include <limits>

void BellmanFord::findShortestPath(Graph* graph, int src, int dest) {
    int V = graph->getVerticesCount();
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    dist[src] = 0;

    std::vector<int> parent(V, -1);

    std::vector<Edge> edges = graph->getEdges();

    for (int i = 1; i < V; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != std::numeric_limits<int>::max() && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                parent[edge.v] = edge.u;
            }
            if (dist[edge.v] != std::numeric_limits<int>::max() && dist[edge.v] + edge.weight < dist[edge.u]) {
                dist[edge.u] = dist[edge.v] + edge.weight;
                parent[edge.u] = edge.v;
            }
        }
    }

    for (const auto& edge : edges) {
        if (dist[edge.u] != std::numeric_limits<int>::max() && dist[edge.u] + edge.weight < dist[edge.v]) {
            std::cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    if (dist[dest] != std::numeric_limits<int>::max()) {
        std::cout << "Shortest path from " << src << " to " << dest << " is " << dist[dest] << "\n";
        std::cout << "Path: ";
        for (int v = dest; v != -1; v = parent[v]) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No path from " << src << " to " << dest << "\n";
    }
}
