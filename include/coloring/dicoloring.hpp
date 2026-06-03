#pragma once
#include "graph.hpp"

bool verify_dicoloring(const graph& G,int k,const std::vector<int>& coloring);

std::vector<int> dicoloring_backtracking(const graph& G,int k);