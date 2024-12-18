#include "../include/graph.hpp"
#include "../include/solution.hpp"
#include <iostream>

int main() {
  Graph graph;
  int V, E;

  std::cin >> V >> E;

  for (int i = 0; i < V; ++i) {
    int id, capacity;
    std::cin >> id >> capacity;
    if (capacity == 0) {
      graph.addVertex(id, true);
    } else {
      graph.addVertex(id, false, capacity);
    }
  }

  for (int i = 0; i < E; ++i) {
    int startVertex, endVertex, capacity;
    std::cin >> startVertex >> endVertex >> capacity;
    graph.addEdge(startVertex, endVertex, capacity);
  }

  Solution solution;

  int totalEnergy = solution.getMaxEnergyTransmission(graph);
  int missingEnergy = solution.getUnmetEnergy(graph);
  int lostEnergy = solution.getLostEnergy(graph);
  auto criticalConnections = solution.getCriticalConnections(graph);

  std::cout << totalEnergy << "\n";
  std::cout << missingEnergy << "\n";
  std::cout << lostEnergy << "\n";
  std::cout << criticalConnections.size() << "\n";
  for (const Edge &edge : criticalConnections) {
    std::cout << edge.from << " " << edge.to << " " << edge.flow << "\n";
  }

  return 0;
}
