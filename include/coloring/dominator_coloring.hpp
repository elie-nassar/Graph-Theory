#pragma once
#include "graph.hpp"

bool verify_dominator_coloring(const graph& G, int k,const std::vector<int>& coloring);

std::vector<int> dominator_coloring_backtracking(const graph& G,int k);
std::vector<int> dominator_coloring_sat(const graph& G,int k);
std::vector<int> dominator_coloring_dp(const graph& G,int k);