#include "../include/edge.hpp"

Edge::Edge(int from, int to, int capacity)
    : from(from), to(to), capacity(capacity), flow(0) {}

bool Edge::isCritical() const { return flow == capacity; }
