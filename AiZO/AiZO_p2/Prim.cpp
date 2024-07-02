#include "Prim.h"
#include <vector>
#include <limits>
#include <iostream>
#include <queue>

void Prim::findMST(Graph* graph) {
    int V = graph->getVerticesCount();
    std::vector<int> key(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);
    std::vector<bool> inMST(V, false);

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({ 0, 0 }); // {weight, vertex}
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto& edge : graph->getEdges()) {
            if (edge.u == u || edge.v == u) {
                int v = (edge.u == u) ? edge.v : edge.u;
                if (!inMST[v] && edge.weight < key[v]) {
                    key[v] = edge.weight;
                    pq.push({ key[v], v });
                    parent[v] = u;
                }
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i << " with weight " << key[i] << "\n";
        }
    }
}
