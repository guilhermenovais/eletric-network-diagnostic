#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

class Edge {
public:
  Vertex *from;
  Vertex *to;
  int capacity;
  int usedCapacity;

  Edge(Vertex *from, Vertex *to, int capacity);
};

#endif
