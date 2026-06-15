#pragma once
#include "rook_graph.hpp"

std::vector<int> dicoloring_C3_backtracking(const rook_graph& G,int k);
std::vector<int> dicoloring_C3_sat(const rook_graph& G,int k);

int dichromatic_number_C3(const rook_graph& G);