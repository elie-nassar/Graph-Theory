#pragma once
#include "graph.hpp"

bool verify_coloring(const graph& G, int k, const vector<int>& coloring);

vector<int> coloring_backtracking(const graph& G, int k);
vector<int> coloring_backtracking(const graph& G, int k, vector<int>& coloring);

vector<int> coloring_sat(const graph& G, int k);