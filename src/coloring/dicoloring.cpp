#include "coloring/dicoloring.hpp"

bool verify_dicoloring(const graph& G,int k,const std::vector<int>& coloring) {
    if(coloring.empty()) return true;
    for(int color=1;color<=k;color++) {
        std::vector<bool> same_color(G.size(),false);
        int same_color_count = 0;
        for(int u=0;u<G.size();u++) if(coloring[u]==color) {same_color[u]=true;same_color_count++;}

        bool is_cyclic = false;
        while(!is_cyclic && same_color_count>0) {
            is_cyclic=true;
            for(int u=0;u<G.size();u++) if(same_color[u]){
                bool is_leaf = true;
                for(int v:G.get_neighbors(u)) if(same_color[v]) {
                    is_leaf=false;
                    break;
                }
                if(is_leaf) {
                    is_cyclic=false;
                    same_color[u]=false;
                    same_color_count--;
                }
            }
        }
        if(same_color_count>0) return false;
    }
    return true;
}

