#include "coloring/dominator_coloring.hpp"
#include "sat.hpp"
#include <unordered_set>

bool verify_dominator_coloring(const graph& G,int k, const std::vector<int>& coloring) {
    if(coloring.empty()) return true;
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

std::vector<int> dominator_coloring_sat(const graph& G,int k) {
    std::vector<std::vector<int>> clauses;
    for(int u=0;u<G.size();u++) {
        for(int c=1;c<=k;c++) {
            std::vector<int> dominator_neighborhood = {u*k+c};
            for(int v:G.get_neighbors(u)) dominator_neighborhood.push_back(v*k+c);
            clauses.push_back(dominator_neighborhood);
        }

        for(int c1=1;c1<=k;c1++) {
            for(int c2=c1+1;c2<=k;c2++) {
                clauses.push_back({-(u*k+c1),-(u*k+c2)});
            }
        }
    }

    sat SAT(clauses);
    auto assignment = SAT.solve_dpll();
    if(assignment.empty()) return {};

    std::vector<int> coloring(G.size(),0);
    for(int u=0;u<G.size();u++) {
        for(int c=0;c<=k-1;c++) {
            if(assignment[u*k+c]) {
                coloring[u] = c+1;
                break;
            }
        }
        if(coloring[u]==0) coloring[u]=1;
    }
    return coloring;
}


std::vector<int> dominator_coloring_dp(const graph& G,int k) {
    int n = G.size();    
    std::vector<int> adj(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : G.get_neighbors(u)) {
            adj[u] = adj[u] | (1 << v); 
        }
    }

    std::vector<bool> is_dominator(1 << n, false);
    
    for (int mask = 0; mask<(1<<n); mask++) {
        int Dmask = mask;
        for(int u=0;u<G.size();u++) if((mask>>u)&1) Dmask |= adj[u];
        if(Dmask==(1<<n)-1) is_dominator[mask]=true;
    }

    std::vector<int> minimal_dominator_sets;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (!is_dominator[mask]) continue;
        
        bool is_minimal = true;
        for (int u = 0; u < n; u++) if((mask>>u)&1) {
                int mask_u = mask ^ (1<<u);
                if (is_dominator[mask_u]) {
                    is_minimal = false;
                    break;
                }
            }
        
        if (is_minimal) {
            minimal_dominator_sets.push_back(mask);
        }
    }
    
    std::vector<int> Xd(1 << n, 0);
    std::vector<int> parent(1 << n, 0);
    Xd[0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int mds : minimal_dominator_sets) {
            if((mds | mask)== mask) {
                int prev_mask = mask & ~mds;
                if (prev_mask != mask) {
                    if (Xd[prev_mask] + 1 > Xd[mask]) {
                        Xd[mask] = Xd[prev_mask] + 1;
                        parent[mask] = mask & mds; 
                    }
                }
            }
        }
    }

    if (Xd[(1 << n) - 1] < k) return {};

    std::vector<int> coloring(n, 0);
    int current_mask = (1 << n) - 1;
    int current_color = 1;

    while (current_mask > 0) {
        int colored_subset = parent[current_mask];
        if(colored_subset==0) break;
        for (int u = 0; u < n; u++) {
            if ((colored_subset >> u) & 1) {
                coloring[u] = (current_color > k ? k : current_color);
            }
        }
        current_mask ^= colored_subset;
        current_color++;
    }
    for(int u=0;u<G.size();u++) if(coloring[u]==0) coloring[u]=1;
    return coloring;
}