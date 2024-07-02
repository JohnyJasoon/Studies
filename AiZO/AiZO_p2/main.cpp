#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Utilities.h"

void executeMenu(Graph* matrixGraph, Graph* listGraph);
void runAlgorithm(Graph* graph, const std::string& representation, const std::string& algorithm);
void runAutomaticTests(const std::vector<int>& verticesCounts, int numTests);

int main() {
    std::unique_ptr<Graph> matrixGraph = nullptr;
    std::unique_ptr<Graph> listGraph = nullptr;

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            matrixGraph.reset(readGraphFromFile(filename, true));
            listGraph.reset(readGraphFromFile(filename, false));
            break;
        }
        case 2: {
            int vertices;
            double density;
            std::cout << "Enter number of vertices: ";
            std::cin >> vertices;
            std::cout << "Enter graph density (e.g., 0.25 for 25%): ";
            std::cin >> density;
            matrixGraph.reset(generateRandomGraph(vertices, density, true));
            listGraph.reset(generateRandomGraph(vertices, density, false));
            break;
        }
        case 3: {
            if (matrixGraph && listGraph) {
                std::cout << "MatrixGraph representation:\n";
                matrixGraph->display();
                std::cout << "ListGraph representation:\n";
                listGraph->display();
            }
            else {
                std::cout << "Graph not loaded or generated.\n";
            }
            break;
        }
        case 4:
        case 5:
        case 6: {
            if (!matrixGraph || !listGraph) {
                std::cout << "Graph not loaded or generated.\n";
                break;
            }
            std::string algorithm;
            if (choice == 3) algorithm = "Prim";
            else if (choice == 4) algorithm = "Kruskal";
            else if (choice == 5) algorithm = "Dijkstra";
            else if (choice == 6) algorithm = "BellmanFord";
            runAlgorithm(matrixGraph.get(), "Matrix", algorithm);
            runAlgorithm(listGraph.get(), "List", algorithm);
            break;
        }
        case 7: {
            std::vector<int> verticesCounts = { 100, 200, 300, 400, 500, 600, 700 };
            int numTests = 50;
            runAutomaticTests(verticesCounts, numTests);
            break;
        }
        case 8:
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void runAlgorithm(Graph* graph, const std::string& representation, const std::string& algorithm) {
    if (algorithm == "Prim") {
        std::cout << "Running Prim's algorithm on " << representation << " representation.\n";
        Prim::findMST(graph);
    }
    else if (algorithm == "Kruskal") {
        std::cout << "Running Kruskal's algorithm on " << representation << " representation.\n";
        Kruskal::findMST(graph);
    }
    else if (algorithm == "Dijkstra") {
        int src, dest;
        std::cout << "Enter source vertex: ";
        std::cin >> src;
        std::cout << "Enter destination vertex: ";
        std::cin >> dest;
        std::cout << "Running Dijkstra's algorithm on " << representation << " representation.\n";
        Dijkstra::findShortestPath(graph, src, dest);
    }
    else if (algorithm == "BellmanFord") {
        int src, dest;
        std::cout << "Enter source vertex: ";
        std::cin >> src;
        std::cout << "Enter destination vertex: ";
        std::cin >> dest;
        std::cout << "Running Bellman-Ford's algorithm on " << representation << " representation.\n";
        BellmanFord::findShortestPath(graph, src, dest);
    }
}


