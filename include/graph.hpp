#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "edge.hpp"
#include "vertex.hpp"
#include <unordered_map>
#include <vector>

class Graph {
public:
  std::unordered_map<int, Vertex> vertices;
  std::vector<Edge> edges;

  void addVertex(int id, bool isGenerator, int demand = 0);
  void addEdge(int from, int to, int capacity);
  std::vector<Edge> getOutgoingEdges(int vertexId);
};

#endif
