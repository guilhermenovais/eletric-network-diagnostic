#include "../include/graph.hpp"

void Graph::addVertex(int id, bool isGenerator, int demand) {
  vertices[id] = Vertex(id, isGenerator, demand);
}

void Graph::addEdge(int from, int to, int capacity) {
  edges.emplace_back(from, to, capacity);
}

std::vector<Edge> Graph::getOutgoingEdges(int vertexId) {
  std::vector<Edge> outgoing;
  for (Edge &edge : edges) {
    if (edge.from == vertexId) {
      outgoing.push_back(edge);
    }
  }
  return outgoing;
}
