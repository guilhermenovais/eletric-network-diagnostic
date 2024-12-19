#include "../include/solution.hpp"
#include <iostream>

void Solution::run(Graph &graph) {
  std::cout << graph.calculateMaxCapacity() << std::endl;
  std::cout << graph.calculateUnmetDemand() << std::endl;
  std::cout << graph.calculateLostEnergy() << std::endl;

  auto criticalConnections = graph.findCriticalConnections();
  std::cout << criticalConnections.size() << std::endl;
  for (Edge *edge : criticalConnections) {
    std::cout << edge->from->id << " " << edge->to->id << " " << edge->capacity
              << std::endl;
  }
}
