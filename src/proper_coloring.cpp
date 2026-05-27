#include "proper_coloring.hpp"
#include "sat.hpp"
#include <map>

bool verify_proper_coloring(const graph& G,int k, const std::vector<int>& coloring) {
    if(coloring.empty()) return true;
    for(int u=0;u<G.get_adjacency_list().size();u++) {
        if(coloring[u]>k) return false;
        for(int v:G.get_neighbors(u)) {
            if(coloring[u]==coloring[v]) return false;
        }
    }
    return true;
}

int choose_next_node(const graph& G, int k,const std::vector<int>& coloring) {
    for(int u=0;u<G.get_adjacency_list().size();u++) if(coloring[u]==0) return u;
    return -1;
}

std::unordered_set<int> get_available_colors(const graph& G, int u, int k, const std::vector<int>& coloring) {
    std::vector<bool> colors(k,true);
    for(int v:G.get_neighbors(u))
        if(coloring[v]!=0) colors[coloring[v]-1] = false;

    std::unordered_set<int> available_colors;
    for(int color=1;color<=k;color++)
        if(colors[color-1]) available_colors.insert(color);
    
    return available_colors;
}

std::vector<int> proper_coloring_backtracking(const graph& G, int k, std::vector<int>& coloring) {
    int node_id = choose_next_node(G,k,coloring);
    if(node_id==-1) return coloring;
    
    for(int color:get_available_colors(G,node_id,k,coloring)) {
        coloring[node_id] = color;
        if(!proper_coloring_backtracking(G,k,coloring).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {};
}

std::vector<int> proper_coloring_backtracking(const graph& G, int k) {
    std::vector<int> coloring(G.size(),0);
    return proper_coloring_backtracking(G,k,coloring);
}

std::vector<int> proper_coloring_sat(const graph& G,int k) {
    std::vector<std::vector<int>> clauses;
    for(int u=0;u<G.size();u++) {
        std::vector<int> at_least_one;
        for(int c=1;c<=k;c++) at_least_one.push_back(u*k+c);
        clauses.push_back(at_least_one);
        
        for(int v:G.get_neighbors(u)) {
            if(v>u) {
                for(int c=1;c<=k;c++) {
                    clauses.push_back({-(u*k+c),-(v*k+c)});
                }
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
                coloring[u] = c;
                break;
            }
        }
    }
    return coloring;
}

std::vector<int> proper_coloring_dp_naive(const graph& G, int k) {
    std::map<std::set<int>,std::unordered_map<int,int>> coloring_dp[k+1];

    std::set<std::set<int>> candidate_sets;
    for (int mask=1;mask<(1 << G.size());mask++){
        std::set<int> candidate_set;
        for(int id=0;id<G.size();id++) 
            if((mask >> id) & 1) candidate_set.insert(id);
        candidate_sets.insert(candidate_set);
    }

    // j=1
    for(const std::set<int>& candidate_set:candidate_sets) {
        bool is_independant = true;
        std::unordered_map<int,int> assignment;
        for(int id:candidate_set) {
            assignment[id]=1;
            for(int neighbor_id:G.get_neighbors(id)) {
                if(candidate_set.find(neighbor_id)!=candidate_set.end()) {
                    is_independant = false;
                    break;
                }
            }
        }
        if(is_independant) coloring_dp[1][candidate_set] = assignment;
    }

    // 2<=j<=k
    for(int j=2;j<=k;j++) {
        for(const std::set<int>& candidate_set:candidate_sets) {
            std::vector<int> v(candidate_set.begin(),candidate_set.end());
            for (int mask=1;mask<(1 << v.size());mask++){
                std::set<int> p1,p2;
                for(int i=0;i<v.size();i++) {
                    if((mask >> i) & 1) p1.insert(v[i]);
                    else p2.insert(v[i]);
                }
                if(coloring_dp[1].contains(p1) and coloring_dp[j-1].contains(p2)) {
                    std::unordered_map<int,int> assignment;
                    for(const auto& [id,color]:coloring_dp[1][p1]) assignment[id] = color;
                    for(const auto& [id,color]:coloring_dp[j-1][p2]) assignment[id] = color+1;
                    coloring_dp[j][candidate_set] = assignment;
                    break;
                }
                if(coloring_dp[1].contains(p2) and coloring_dp[j-1].contains(p1)) {
                    std::unordered_map<int,int> assignment;
                    for(const auto& [id,color]:coloring_dp[1][p2]) assignment[id] = color;
                    for(const auto& [id,color]:coloring_dp[j-1][p1]) assignment[id] = color+1;
                    coloring_dp[j][candidate_set] = assignment;
                    break;
                }
            }

        }
    }

    std::set<int> node_ids_set;
    for(int i=0;i<G.size();i++) node_ids_set.insert(i);
    if(!coloring_dp[k].contains(node_ids_set)) return {};
    std::unordered_map<int,int> m = coloring_dp[k][node_ids_set];
    std::vector<int> assignment(G.size());
    for(int i=0;i<G.size();i++) assignment[i] = m[i];
    return assignment;
}