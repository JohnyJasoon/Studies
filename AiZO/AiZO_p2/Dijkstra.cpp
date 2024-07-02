#include "Dijkstra.h"
#include <vector>
#include <queue>
#include <iostream>
#include <limits>

void Dijkstra::findShortestPath(Graph* graph, int src, int dest) {
    int V = graph->getVerticesCount();
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    dist[src] = 0;

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({ 0, src });

    std::vector<int> parent(V, -1);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == dest) break;

        for (const auto& edge : graph->getEdges()) {
            int v = (edge.u == u) ? edge.v : (edge.v == u) ? edge.u : -1;
            if (v != -1) {
                int weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                    parent[v] = u;
                }
            }
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
