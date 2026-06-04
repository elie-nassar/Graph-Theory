#include "coloring/rook_graph_dicoloring.hpp"
#include <unordered_set>


bool is_3_cyclic(const rook_graph& G, int u1, int u2, int u3) {
    return G.get_neighbors(u1).contains(u2)
        && G.get_neighbors(u2).contains(u3)
        && G.get_neighbors(u3).contains(u1);
}

std::unordered_set<int> get_available_colors_C3(const rook_graph& G, int u, int k, const std::vector<int>& coloring) {
    std::vector<bool> colors(k,true);
    int n = sqrt(G.size());   
    int x = getX(u,n);
    int y = getY(u,n);

    if(x<n-2) {
        int u1 = u;
        int u2 = convert(x+1,y,n);
        int u3 = convert(x+2,y,n);
        if(coloring[u2]!=0 && coloring[u2]==coloring[u3] && colors[coloring[u2]-1] && (is_3_cyclic(G,u1,u2,u3) || is_3_cyclic(G,u3,u2,u1))) colors[coloring[u2]-1] = false;
    }
    if(x>0 && x<n-1) {
        int u1 = convert(x-1,y,n);
        int u2 = u;
        int u3 = convert(x+1,y,n);
        if(coloring[u1]!=0 && coloring[u1]==coloring[u3] && colors[coloring[u1]-1] && (is_3_cyclic(G,u1,u2,u3) || is_3_cyclic(G,u3,u2,u1))) colors[coloring[u1]-1] = false;
    }
    if(x>1) {
        int u1 = convert(x-2,y,n);
        int u2 = convert(x-1,y,n);
        int u3 = u;
        if(coloring[u1]!=0 && coloring[u1]==coloring[u2] && colors[coloring[u1]-1] && (is_3_cyclic(G,u1,u2,u3) || is_3_cyclic(G,u3,u2,u1))) colors[coloring[u1]-1] = false;
    }

    if(y<n-2) {
        int u1 = u;
        int u2 = convert(x,y+1,n);
        int u3 = convert(x,y+2,n);
        if(coloring[u2]!=0 && coloring[u2]==coloring[u3] && colors[coloring[u2]-1] && (is_3_cyclic(G,u1,u2,u3) || is_3_cyclic(G,u3,u2,u1))) colors[coloring[u2]-1] = false;
    }
    if(y>0 && y<n-1) {
        int u1 = convert(x,y-1,n);
        int u2 = u;
        int u3 = convert(x,y+1,n);
        if(coloring[u1]!=0 && coloring[u1]==coloring[u3] && colors[coloring[u1]-1] && (is_3_cyclic(G,u1,u2,u3) || is_3_cyclic(G,u3,u2,u1))) colors[coloring[u1]-1] = false;
    }
    if(y>1) {
        int u1 = convert(x,y-2,n);
        int u2 = convert(x,y-1,n);
        int u3 = u;
        if(coloring[u1]!=0 && coloring[u1]==coloring[u2] && colors[coloring[u1]-1] && (is_3_cyclic(G,u1,u2,u3) || is_3_cyclic(G,u3,u2,u1))) colors[coloring[u1]-1] = false;
    }

    std::unordered_set<int> available_colors;
    for(int color=1;color<=k;color++)
        if(colors[color-1]) available_colors.insert(color);

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