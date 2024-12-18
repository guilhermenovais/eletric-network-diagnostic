#include "../include/solution.hpp"
#include <climits>
#include <queue>

int Solution::getMaxEnergyTransmission(Graph &graph) {
  int maxFlow = 0;

  std::unordered_map<int, std::unordered_map<int, int>> residual;
  for (const Edge &edge : graph.edges) {
    residual[edge.from][edge.to] = edge.capacity;
  }

  int source = -1, sink = -1;

  for (const auto vertex : graph.vertices) {
    if (vertex.second.isGenerator) {
      source = vertex.first;
    }
    if (!vertex.second.isGenerator && vertex.second.demand > 0) {
      sink = vertex.first;
    }
  }

  if (source == -1 || sink == -1) {
    return 0;
  }

  std::unordered_map<int, int> parent;

  while (bfs(residual, source, sink, parent)) {
    int pathFlow = INT_MAX;

    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      pathFlow = std::min(pathFlow, residual[u][v]);
    }

    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      residual[u][v] -= pathFlow;
      residual[v][u] += pathFlow;
    }

    maxFlow += pathFlow;
  }

  for (Edge &edge : graph.edges) {
    if (residual[edge.to][edge.from] > 0) {
      edge.flow = edge.capacity - residual[edge.from][edge.to];
    }
  }

  return maxFlow;
}

int Solution::getUnmetEnergy(Graph &graph) {
  int unmetEnergy = 0;
  for (const auto vertex : graph.vertices) {
    if (!vertex.second.isGenerator) {
      unmetEnergy +=
          std::max(0, vertex.second.demand - vertex.second.receivedEnergy);
    }
  }
  return unmetEnergy;
}

int Solution::getLostEnergy(Graph &graph) {
  int totalGenerated = 0, totalReceived = 0;
  for (const auto vertex : graph.vertices) {
    if (vertex.second.isGenerator) {
      totalGenerated += vertex.second.receivedEnergy;
    } else {
      totalReceived += vertex.second.receivedEnergy;
    }
  }
  return totalGenerated - totalReceived;
}

std::vector<Edge> Solution::getCriticalConnections(Graph &graph) {
  std::vector<Edge> criticalConnections;
  for (const Edge &edge : graph.edges) {
    if (edge.isCritical()) {
      criticalConnections.push_back(edge);
    }
  }
  sortEdgesByFlow(criticalConnections);
  return criticalConnections;
}

void Solution::sortEdgesByFlow(std::vector<Edge> &edges) {
  for (size_t i = 0; i < edges.size(); ++i) {
    size_t maxIndex = i;
    for (size_t j = i + 1; j < edges.size(); ++j) {
      if (edges[j].flow > edges[maxIndex].flow) {
        maxIndex = j;
      }
    }
    if (maxIndex != i) {
      Edge temp = edges[i];
      edges[i] = edges[maxIndex];
      edges[maxIndex] = temp;
    }
  }
}

bool Solution::bfs(
    std::unordered_map<int, std::unordered_map<int, int>> &residual, int source,
    int sink, std::unordered_map<int, int> &parent) {
  std::queue<int> q;
  std::unordered_map<int, bool> visited;

  q.push(source);
  visited[source] = true;
  parent[source] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (const auto res : residual[u]) {
      if (!visited[res.first] && res.second > 0) {
        q.push(res.first);
        parent[res.first] = u;
        visited[res.first] = true;

        if (res.first == sink) {
          return true;
        }
      }
    }
  }

  return false;
}
