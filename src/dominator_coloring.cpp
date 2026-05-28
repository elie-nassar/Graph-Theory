#include "dominator_coloring.hpp"

bool verify_dominator_coloring(const graph& G,int k, const std::vector<int>& coloring) {
    for(int u=0;u<G.size();u++) {
        std::vector<bool> colors(k,false);
        colors[coloring[u]-1] = true;
        for(int v:G.get_neighbors(u)) colors[coloring[v]-1] = true;
        for(bool color:colors) if(!color) return false;
    }
    return true;
}