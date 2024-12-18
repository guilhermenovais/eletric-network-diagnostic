#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex {
public:
  int id;
  bool isGenerator;
  int demand;
  int receivedEnergy;

  Vertex();
  Vertex(int id, bool isGenerator, int demand = 0);
};

#endif
