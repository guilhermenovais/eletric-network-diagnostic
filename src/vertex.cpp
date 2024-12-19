#include "../include/vertex.hpp"
#include "../include/edge.hpp"

Vertex::Vertex(int id, int type) : id(id), type(type), receivedEnergy(0) {}

void Vertex::addEdge(Edge *edge) { edges.push_back(edge); }

const std::vector<Edge *> &Vertex::getEdges() const { return edges; }
