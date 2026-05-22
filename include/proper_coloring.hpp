#pragma once
#include "graph.hpp"

bool verify_proper_coloring(const graph& G, int k, const unordered_map<int,int>& coloring);

unordered_map<int,int> proper_coloring_backtracking(const graph& G, int k);
unordered_map<int,int> proper_coloring_sat(const graph& G, int k);
unordered_map<int,int> proper_coloring_dp_naive(const graph& G, int k);
unordered_map<int,int> proper_coloring_dp(const graph& G, int k);