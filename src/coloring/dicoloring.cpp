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

int choose_next_node_dicoloring(const graph& G,int k,const std::vector<int> coloring) {
    for(int u=0;u<G.size();u++) if(coloring[u]==0) return u;
    return -1;
}

std::vector<int> dicoloring_backtracking(const graph& G,int k,std::vector<int>& coloring) {
    int node_id = choose_next_node_dicoloring(G,k,coloring);
    if(node_id==-1) return verify_dicoloring(G,k,coloring) ? coloring : std::vector<int>{};

    for(int color=1;color<=k;color++) {
        coloring[node_id] = color;
        if(!dicoloring_backtracking(G,k,coloring).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {};
}

std::vector<int> dicoloring_backtracking(const graph& G,int k) {
    std::vector<int> coloring(G.size(),0);
    return dicoloring_backtracking(G,k,coloring);
}

