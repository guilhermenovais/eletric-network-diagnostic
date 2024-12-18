#include "../include/vertex.hpp"

Vertex::Vertex() : id(0), isGenerator(false), demand(0), receivedEnergy(0) {}

Vertex::Vertex(int id, bool isGenerator, int demand)
    : id(id), isGenerator(isGenerator), demand(demand), receivedEnergy(0) {}
