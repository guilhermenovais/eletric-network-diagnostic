#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "graph.hpp"

class Solution {
public:
  int getMaxEnergyTransmission(Graph &graph);
  int getUnmetEnergy(Graph &graph);
  int getLostEnergy(Graph &graph);
  std::vector<Edge> getCriticalConnections(Graph &graph);

private:
  void sortEdgesByFlow(std::vector<Edge> &edges);
  bool bfs(std::unordered_map<int, std::unordered_map<int, int>> &residual,
           int source, int sink, std::unordered_map<int, int> &parent);
};

#endif
