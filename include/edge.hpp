#ifndef EDGE_HPP
#define EDGE_HPP

class Edge {
public:
  int from, to;
  int capacity;
  int flow;

  Edge(int from, int to, int capacity);
  bool isCritical() const;
};

#endif
