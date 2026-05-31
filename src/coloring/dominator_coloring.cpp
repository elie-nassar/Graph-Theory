#include "coloring/dominator_coloring.hpp"
#include "sat.hpp"
#include <unordered_set>

bool verify_dominator_coloring(const graph& G,int k, const std::vector<int>& coloring) {
    for(int u=0;u<G.size();u++) {
        std::vector<bool> colors(k,false);
        colors[coloring[u]-1] = true;
        for(int v:G.get_neighbors(u)) colors[coloring[v]-1] = true;
        for(bool color:colors) if(!color) return false;
    }
    return true;
}

int choose_next_node(const graph& G,int k,const std::vector<int> coloring) {
    for(int u=0;u<G.size();u++) if(coloring[u]==0) return u;
    return -1;
}

std::unordered_set<int> get_available_colors_dominator(const graph& G, int u, int k, const std::vector<int>& coloring) {
    std::vector<bool> colors(k,true);
    int neighbors_without_color = G.get_neighbors(u).size()+1;
    int missing_colors = k;
    for(int v:G.get_neighbors(u))
        if(coloring[v]!=0) {
            neighbors_without_color--;
            if(colors[coloring[v]-1]) {
                colors[coloring[v]-1] = false;
                missing_colors--;
            }
        }

    if(missing_colors>neighbors_without_color) return {};

    std::unordered_set<int> available_colors;
    for(int color=1;color<=k;color++)
        if(colors[color-1]) available_colors.insert(color);
    if(available_colors.empty()) available_colors = {1};
    return available_colors;
}

std::vector<int> dominator_coloring_backtracking(const graph& G,int k,std::vector<int>& coloring) {
    int node_id = choose_next_node(G,k,coloring);
    if(node_id==-1) return coloring;

    for(int color:get_available_colors_dominator(G,node_id,k,coloring)) {
        coloring[node_id] = color;
        if(!dominator_coloring_backtracking(G,k,coloring).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {};
}


std::vector<int> dominator_coloring_backtracking(const graph& G,int k) {
    std::vector<int> coloring(G.size(),0);
    return dominator_coloring_backtracking(G,k,coloring);
}