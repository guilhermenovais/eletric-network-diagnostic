#include "../include/edge.hpp"

Edge::Edge(Vertex *from, Vertex *to, int capacity)
    : from(from), to(to), capacity(capacity), usedCapacity(0) {}
