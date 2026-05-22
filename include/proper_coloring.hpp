#pragma once
#include "graph.hpp"
#include "binary_tree.hpp"

bool verify_proper_coloring(const graph& G, int k, const unordered_map<int,int>& coloring);

unordered_map<int,int> proper_coloring_backtracking(const graph& G, int k);
unordered_map<int,int> proper_coloring_sat(const graph& G, int k);
unordered_map<int,int> proper_coloring_dp_naive(const graph& G, int k);
unordered_map<int,int> proper_coloring_dp(const graph& G, int k);
binary_tree get_subgraphs_binary_tree(const graph& G);