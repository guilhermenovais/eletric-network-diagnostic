#include "../include/graph.hpp"
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>

Graph::~Graph() {
  for (auto edge : edges) {
    delete edge;
  }
  for (auto entry : vertices) {
    delete entry.second;
  }
}

void Graph::addVertex(int id, int type) { vertices[id] = new Vertex(id, type); }

void Graph::addEdge(int from, int to, int capacity) {
  Edge *edge = new Edge(vertices[from], vertices[to], capacity);
  edges.push_back(edge);
  vertices[from]->addEdge(edge);
}

int Graph::calculateMaxCapacity() {
  int totalCapacity = 0;

  for (const auto &[id, vertex] : vertices) {
    if (vertex->type == 0) { // Generator
      for (const auto &[cid, consumer] : vertices) {
        if (consumer->type > 0 &&
            consumer->type >
                consumer->receivedEnergy) { // Consumer with unmet demand
          while (true) {
            std::vector<Edge *> path;

            if (!bfs(vertex, consumer, path)) {
              break;
            }

            int remainingDemand = consumer->type - consumer->receivedEnergy;
            int bottleneck = INT_MAX;

            for (Edge *edge : path) {
              bottleneck =
                  std::min(bottleneck, edge->capacity - edge->usedCapacity);
            }

            int flow = std::min(bottleneck, remainingDemand);

            for (Edge *edge : path) {
              edge->usedCapacity += flow;
            }

            consumer->receivedEnergy += flow;
            totalCapacity += flow;

            if (flow == remainingDemand) {
              break;
            }
          }
        }
      }
    }
  }

  return totalCapacity;
}

bool Graph::bfs(Vertex *source, Vertex *target, std::vector<Edge *> &path) {
  std::unordered_map<Vertex *, Edge *> parent;
  std::queue<Vertex *> q;
  std::unordered_set<Vertex *> visited;

  q.push(source);
  visited.insert(source);

  while (!q.empty()) {
    Vertex *current = q.front();
    q.pop();

    for (Edge *edge : current->getEdges()) {
      if (edge->capacity > edge->usedCapacity &&
          visited.find(edge->to) == visited.end()) {
        parent[edge->to] = edge;
        visited.insert(edge->to);
        q.push(edge->to);

        if (edge->to == target) {
          Vertex *v = target;
          while (v != source) {
            path.insert(path.begin(), parent[v]);
            v = parent[v]->from;
          }
          return true;
        }
      }
    }
  }

  return false;
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
