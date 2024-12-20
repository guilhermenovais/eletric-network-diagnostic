#include "../include/graph.hpp"
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_map>

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

  std::vector<Vertex *> generators;
  std::vector<Vertex *> consumers;

  for (auto entry : vertices) {
    Vertex *vertex = entry.second;
    if (vertex->type == 0) {
      generators.push_back(vertex);
    } else if (vertex->type > 0) {
      consumers.push_back(vertex);
    }
  }

  for (Vertex *generator : generators) {
    for (Vertex *consumer : consumers) {
      int flow = edmondsKarp(generator, consumer);
      totalCapacity += flow;
    }
  }

  return totalCapacity;
}

int Graph::edmondsKarp(Vertex *source, Vertex *sink) {
  if (sink->type == sink->receivedEnergy)
    return 0;

  int maxFlow = 0;
  std::unordered_map<Vertex *, Edge *> parentMap;

  while (bfs(source, sink, parentMap)) {
    int pathFlow = INT_MAX;

    for (Vertex *v = sink; v != source; v = parentMap[v]->from) {
      Edge *edge = parentMap[v];
      pathFlow = std::min(pathFlow, edge->capacity - edge->usedCapacity);
    }

    pathFlow = std::min(pathFlow, sink->type - sink->receivedEnergy);

    sink->receivedEnergy += pathFlow;

    for (Vertex *v = sink; v != source; v = parentMap[v]->from) {
      Edge *edge = parentMap[v];
      edge->usedCapacity += pathFlow;

      bool reverseEdgeFound = false;
      for (Edge *reverseEdge : edge->to->getEdges()) {
        if (reverseEdge->to == edge->from) {
          reverseEdge->usedCapacity -= pathFlow;
          reverseEdgeFound = true;
          break;
        }
      }

      if (!reverseEdgeFound) {
        Edge *reverseEdge = new Edge(edge->to, edge->from, 0);
        reverseEdge->usedCapacity = -pathFlow;
        edge->to->addEdge(reverseEdge);
        edges.push_back(reverseEdge);
      }
    }

    maxFlow += pathFlow;

    if (sink->type == sink->receivedEnergy)
      break;
  }

  return maxFlow;
}

bool Graph::bfs(Vertex *source, Vertex *sink,
                std::unordered_map<Vertex *, Edge *> &parentMap) {
  std::queue<Vertex *> q;
  std::unordered_map<Vertex *, bool> visited;

  q.push(source);
  visited[source] = true;
  parentMap.clear();

  while (!q.empty()) {
    Vertex *current = q.front();
    q.pop();

    for (Edge *edge : current->getEdges()) {
      Vertex *neighbor = edge->to;

      if (!visited[neighbor] && edge->capacity > edge->usedCapacity) {
        parentMap[neighbor] = edge;
        visited[neighbor] = true;

        if (neighbor == sink) {
          return true;
        }
        q.push(neighbor);
      }
    }
  }
  return false;
}

int Graph::calculateUnmetDemand() {
  int unmetDemand = 0;
  for (auto it = vertices.begin(); it != vertices.end(); ++it) {
    Vertex *vertex = it->second;
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
