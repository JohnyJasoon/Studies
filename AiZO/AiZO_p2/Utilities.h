#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <memory> 

class Graph; 

Graph* readGraphFromFile(const std::string& filename, bool matrix);
Graph* generateRandomGraph(int vertices, double density, bool matrix);
void displayMenu();
void runAutomaticTests(const std::vector<int>& verticesCounts, int numTests, const std::vector<double>& densities);

#endif // UTILITIES_H
