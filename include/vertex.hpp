#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

class Edge;

class Vertex {
public:
  int id;
  int type;
  int receivedEnergy;

  explicit Vertex(int id, int type);

  void addEdge(Edge *edge);
  const std::vector<Edge *> &getEdges() const;

private:
  std::vector<Edge *> edges;
};

#endif
