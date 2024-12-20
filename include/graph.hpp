#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../include/edge.hpp"
#include "../include/vertex.hpp"
#include <map>
#include <unordered_map>
#include <vector>

class Graph {
public:
  ~Graph();
  void addVertex(int id, int type);
  void addEdge(int from, int to, int capacity);

  int calculateMaxCapacity();
  int calculateUnmetDemand();
  int calculateLostEnergy();
  std::vector<Edge *> findCriticalConnections();

private:
  std::map<int, Vertex *> vertices;
  std::vector<Edge *> edges;

  void sortEdgesByCapacity(std::vector<Edge *> &edges);
  int edmondsKarp(Vertex *source, Vertex *sink);
  bool bfs(Vertex *source, Vertex *sink,
           std::unordered_map<Vertex *, Edge *> &parentMap);
};

#endif
