#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

class Dijkstra {
public:
    static void findShortestPath(Graph* graph, int src, int dest);
};

#endif // DIJKSTRA_H
