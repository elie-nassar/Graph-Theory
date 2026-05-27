#pragma once
#include "graph.hpp"

bool verify_proper_coloring(const graph& G, int k, const std::vector<int>& coloring);

std::vector<int> proper_coloring_backtracking(const graph& G, int k);
std::vector<int> proper_coloring_sat(const graph& G, int k);
std::vector<int> proper_coloring_dp_naive(const graph& G, int k);
