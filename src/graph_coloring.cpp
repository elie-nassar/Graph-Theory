#include "graph_coloring.hpp"

int choose_next_node(const graph& G, int k, vector<int>& c) {
    for(int i=0;i<G.size();i++)
        if(c[i]==0) return i;
    return -1;
}

vector<int> get_available_colors(const graph& G, int node_id, int k, vector<int>& c) {
    set<int> unavailable_colors;
    for(auto& neighbor_id:G.get_node_by_id(node_id).get_neighbor_ids())
        unavailable_colors.insert(c[neighbor_id]);

    vector<int> available_colors;
    for(int color=1;color<=k;color++)
        if(!unavailable_colors.contains(color))
            available_colors.push_back(color);
    
    return available_colors;
}

vector<int> graph_coloring_backtracking(const graph& G, int k) {
    vector<int> c(G.size(),0);
    return graph_coloring_backtracking(G,k,c);
}

vector<int> graph_coloring_backtracking(const graph& G, int k, vector<int>& c) {
    int node_id = choose_next_node(G,k,c);
    if(node_id==-1) return c;
    
    for(int color:get_available_colors(G,node_id,k,c)) {
        c[node_id] = color;
        if(!graph_coloring_backtracking(G,k,c).empty()) return c;
        c[node_id] = 0;
    }

    return {};
}