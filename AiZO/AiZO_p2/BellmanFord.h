#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "Graph.h"

class BellmanFord {
public:
    static void findShortestPath(Graph* graph, int src, int dest);
};

#endif // BELLMANFORD_H
