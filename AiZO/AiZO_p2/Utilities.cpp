#include "Utilities.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

Graph* readGraphFromFile(const std::string& filename, bool isMatrix) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return nullptr;
    }

    int vertices, edges;
    file >> vertices >> edges;

    Graph* graph = isMatrix ? static_cast<Graph*>(new MatrixGraph(vertices)) : static_cast<Graph*>(new ListGraph(vertices));

    int u, v, weight;
    while (file >> u >> v >> weight) {
        graph->addEdge(u, v, weight);
    }

    file.close();
    return graph;
}

Graph* generateRandomGraph(int vertices, double density, bool isMatrix) {
    Graph* graph = isMatrix ? static_cast<Graph*>(new MatrixGraph(vertices)) : static_cast<Graph*>(new ListGraph(vertices));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weightDist(1, 100);
    std::uniform_int_distribution<> vertexDist(0, vertices - 1);

    int maxEdges = vertices * (vertices - 1) / 2;
    int targetEdges = static_cast<int>(density * maxEdges);

    std::vector<Edge> edges;
    for (int i = 1; i < vertices; ++i) {
        int u = i;
        int v = vertexDist(gen) % i;
        int weight = weightDist(gen);
        graph->addEdge(u, v, weight);
        edges.push_back({ u, v, weight });
    }

    std::uniform_int_distribution<> edgeDist(0, edges.size() - 1);
    while (edges.size() < targetEdges) {
        int u = vertexDist(gen);
        int v = vertexDist(gen);
        if (u != v) {
            int weight = weightDist(gen);
            edges.push_back({ u, v, weight });
            graph->addEdge(u, v, weight);
        }
    }

    return graph;
}

void displayMenu() {
    std::cout << "Select option:\n";
    std::cout << "1. Load graph from file\n";
    std::cout << "2. Generate random graph\n";
    std::cout << "3. Display graph\n";
    std::cout << "4. Run Prim's algorithm\n";
    std::cout << "5. Run Kruskal's algorithm\n";
    std::cout << "6. Run Dijkstra's algorithm\n";
    std::cout << "7. Run Bellman-Ford's algorithm\n";
    std::cout << "8. Run automatic tests\n";
    std::cout << "9. Exit\n";
}

void runAutomaticTests(const std::vector<int>& verticesCounts, int numTests) {
    std::ofstream resultFile("test_results.txt");

    for (int vertices : verticesCounts) {
        for (int i = 0; i < numTests; ++i) {
            double density = 0.99; // You can adjust this density
            std::unique_ptr<Graph> matrixGraph(generateRandomGraph(vertices, density, true));
            std::unique_ptr<Graph> listGraph(generateRandomGraph(vertices, density, false));

            auto start = std::chrono::high_resolution_clock::now();
            Prim::findMST(matrixGraph.get());
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            resultFile << "Prim,Matrix," << vertices << "," << density << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            Prim::findMST(listGraph.get());
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "Prim,List," << vertices << "," << density << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            Kruskal::findMST(matrixGraph.get());
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "Kruskal,Matrix," << vertices << "," << density << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            Kruskal::findMST(listGraph.get());
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "Kruskal,List," << vertices << "," << density << "," << elapsed.count() << "\n";

            int src = 0;
            int dest = vertices - 1;

            start = std::chrono::high_resolution_clock::now();
            Dijkstra::findShortestPath(matrixGraph.get(), src, dest);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "Dijkstra,Matrix," << vertices << "," << density << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            Dijkstra::findShortestPath(listGraph.get(), src, dest);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "Dijkstra,List," << vertices << "," << density << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            BellmanFord::findShortestPath(matrixGraph.get(), src, dest);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "BellmanFord,Matrix," << vertices << "," << density << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            BellmanFord::findShortestPath(listGraph.get(), src, dest);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultFile << "BellmanFord,List," << vertices << "," << density << "," << elapsed.count() << "\n";
        }
    }

    resultFile.close();
}
