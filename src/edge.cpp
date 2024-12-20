#include "../include/edge.hpp"

Edge::Edge(Vertex *from, Vertex *to, int capacity, bool isReverse)
    : from(from), to(to), capacity(capacity), usedCapacity(0),
      isReverse(isReverse) {}
