#include "Kruskal.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

void Kruskal::findMST(Graph* graph) {
    int V = graph->getVerticesCount();
    std::vector<Edge> edges = graph->getEdges();
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
        });

    std::vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    std::function<int(int)> find = [&](int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
        };

    std::function<void(int, int)> unite = [&](int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v]) {
                std::swap(u, v);
            }
            parent[v] = u;
            if (rank[u] == rank[v]) {
                rank[u]++;
            }
        }
        };

    for (const auto& edge : edges) {
        if (find(edge.u) != find(edge.v)) {
            std::cout << edge.u << " - " << edge.v << " with weight " << edge.weight << "\n";
            unite(edge.u, edge.v);
        }
    }
}
