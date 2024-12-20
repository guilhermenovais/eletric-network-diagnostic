#ifndef EDGE_HPP
#define EDGE_HPP

class Vertex;

class Edge {
public:
  Vertex *from;
  Vertex *to;
  int capacity;
  int usedCapacity;
  bool isReverse;

  Edge(Vertex *from, Vertex *to, int capacity, bool isReverse);
};

#endif
