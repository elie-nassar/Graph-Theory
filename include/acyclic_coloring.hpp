#pragma once
#include "graph.hpp"

bool verify_acyclic_coloring(const graph& G, int k, const unordered_map<int,int>& coloring);