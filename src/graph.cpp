#include "../include/graph.hpp"

void Graph::addVertex(int id, int type) { vertices[id] = new Vertex(id, type); }

void Graph::addEdge(int from, int to, int capacity) {
  Edge *edge = new Edge(vertices[from], vertices[to], capacity);
  edges.push_back(edge);
  vertices[from]->addEdge(edge);
}

int Graph::calculateMaxCapacity() {
  int totalCapacity = 0;
  for (Edge *edge : edges) {
    totalCapacity += edge->capacity;
  }
  return totalCapacity;
}

int Graph::calculateUnmetDemand() {
  int unmetDemand = 0;
  for (const auto &[id, vertex] : vertices) {
    if (vertex->type > 0) {
      unmetDemand += std::max(0, vertex->type - vertex->receivedEnergy);
    }
  }
  return unmetDemand;
}

int Graph::calculateLostEnergy() {
  int energyCapacity = 0;
  int energyDelivered = 0;
  for (Edge *edge : edges) {
    if (edge->from->type == 0) {
      energyCapacity += edge->capacity;
      energyDelivered += edge->usedCapacity;
    }
  }
  return energyCapacity - energyDelivered;
}

std::vector<Edge *> Graph::findCriticalConnections() {
  std::vector<Edge *> criticalEdges;
  for (Edge *edge : edges) {
    if (edge->usedCapacity == edge->capacity) {
      criticalEdges.push_back(edge);
    }
  }
  sortEdgesByCapacity(criticalEdges);
  return criticalEdges;
}

void Graph::sortEdgesByCapacity(std::vector<Edge *> &edges) {
  for (size_t i = 0; i < edges.size(); ++i) {
    for (size_t j = i + 1; j < edges.size(); ++j) {
      if (edges[i]->capacity < edges[j]->capacity) {
        std::swap(edges[i], edges[j]);
      }
    }
  }
}
