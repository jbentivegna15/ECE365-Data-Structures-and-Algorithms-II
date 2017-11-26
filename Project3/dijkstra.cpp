/*
Joseph Bentivegna
Professor Sable
DSA2 Project 3
*/

#include <fstream>
#include <iostream>
#include <string>
#include "graph.h"

int main() {
  std::string start;
  std::string graphFile, outputPath;
  std::string line;
  graph g;

  std::cout << "\nEnter name of graph file: ";
  std::cin >> graphFile;

  std::ifstream graphList (graphFile.c_str());
  if (!graphList) {
    std::cout << "Error: could not open " << graphFile <<"\n";
  }

  if (graphList.is_open()) {
    while (std::getline(graphList, line)) {
      g.insert(line);
    }
    graphList.close();
  }

  while (!g.hasNode(start)) {
    std::cout << "Enter a valid vertix ID for the starting vertex: ";
    std::cin >> start;
  }

  clock_t begin = clock();
  g.dijkstra(start);
  clock_t end = clock();
  double elapsed_secs = ((double)(end-begin)) / CLOCKS_PER_SEC;
  std::cout << "Total time (in seconds) to apply dijkstra's algorithm: " << elapsed_secs << "\n";

  std::cout << "Enter name of output file: ";
  std::cin >> outputPath;

  std::ofstream outputFile (outputPath.c_str());
  if(!outputFile) {
    std::cout << "Error: could not open " << outputPath << "\n";
  }

  g.exportFile(outputFile);
  outputFile.close();

  return 0;
}
