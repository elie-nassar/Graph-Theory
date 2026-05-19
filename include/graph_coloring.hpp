#pragma once
#include "graph.hpp"

int choose_next_node(const graph& G, int k, vector<int>& c);
vector<int> get_available_colors(const graph& G, int node_id, int k, vector<int>& c);

vector<int> graph_coloring_backtracking(const graph& G, int k);
vector<int> graph_coloring_backtracking(const graph& G, int k, vector<int>& c);