#pragma once
#include "graph.hpp"

int choose_next_node(const graph& G, int k, vector<int>& c);
vector<int> get_available_colors(const graph& G, int node_id, int k, vector<int>& c);

bool verify_coloring(const graph& G, int k, const vector<int>& c);

vector<int> coloring_backtracking(const graph& G, int k);
vector<int> coloring_backtracking(const graph& G, int k, vector<int>& c);

vector<int> coloring_sat(const graph& G, int k);