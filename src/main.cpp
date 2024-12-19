#include "../include/graph.hpp"
#include "../include/solution.hpp"
#include <iostream>

int main() {
  int qtdVertices, qtdEdges;
  std::cin >> qtdVertices >> qtdEdges;

  Graph graph;

  for (int i = 0; i < qtdVertices; ++i) {
    int id, type;
    std::cin >> id >> type;
    graph.addVertex(id, type);
  }

  for (int i = 0; i < qtdEdges; ++i) {
    int from, to, capacity;
    std::cin >> from >> to >> capacity;
    graph.addEdge(from, to, capacity);
  }

  Solution solution;
  solution.run(graph);

  return 0;
}
