#pragma once
#include "graph.hpp"

bool verify_coloring(const graph& G, int k, const unordered_map<int,int>& coloring);

unordered_map<int,int> coloring_backtracking(const graph& G, int k);
unordered_map<int,int> coloring_backtracking(const graph& G, int k, unordered_map<int,int>& coloring);

unordered_map<int,int> coloring_sat(const graph& G, int k);