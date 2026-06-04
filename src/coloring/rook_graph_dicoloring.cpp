#include "coloring/rook_graph_dicoloring.hpp"
#include <unordered_set>


bool is_3_cyclic(const rook_graph& G, int u1, int u2, int u3) {
    return G.get_neighbors(u1).contains(u2)
        && G.get_neighbors(u2).contains(u3)
        && G.get_neighbors(u3).contains(u1);
}

std::unordered_set<int> get_available_colors_C3(const rook_graph& G, int u, int k, const std::vector<int>& coloring) {
    std::unordered_set<int> available_colors;
    int n = sqrt(G.size());   
    int x = getX(u,n);
    int y = getY(u,n);

    if(x<n-2) {
        
    }
    
    return available_colors;
}

std::vector<int> dicoloring_C3_backtracking(const rook_graph& G,int k, std::vector<int>& coloring,int node_id) {
    if(node_id>=G.size()) return coloring;

    for(int color:get_available_colors_C3(G,node_id,k,coloring)) {
        coloring[node_id] = color;
        if(!dicoloring_C3_backtracking(G,k,coloring,node_id+1).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {}; 
}

std::vector<int> dicoloring_C3_backtracking(const rook_graph& G,int k) {
    std::vector<int> coloring(G.size(),0);
    return dicoloring_C3_backtracking(G,k,coloring,0);
}   