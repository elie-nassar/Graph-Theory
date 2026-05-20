#include "graph_coloring.hpp"
#include "sat.hpp"

int choose_next_node(const graph& G, int k,const unordered_map<int,int>& coloring) {
    for(const auto& [id,n]:G.get_nodes())
        if(!coloring.contains(id)) return id;
    return -1;
}

unordered_set<int> get_available_colors(const graph& G, int node_id, int k, const unordered_map<int,int>& coloring) {
    unordered_set<int> unavailable_colors;
    unavailable_colors.reserve(k);
    for(auto& neighbor_id:G.get_node_by_id(node_id).get_neighbor_ids()) {
        auto it_color = coloring.find(neighbor_id);
        if(it_color!=coloring.end()) unavailable_colors.insert(it_color->second);
    }

    unordered_set<int> available_colors;
    available_colors.reserve(k);
    for(int color=1;color<=k;color++)
        if(!unavailable_colors.contains(color))
            available_colors.insert(color);
    
    return available_colors;
}

bool verify_coloring(const graph& G,int k, const unordered_map<int,int>& coloring) {
    if(coloring.empty()) return true;
    unordered_set<int> colors;
    for(const auto& [id,n]:G.get_nodes()) {
        int color = coloring.at(id);
        colors.insert(color);
        for(int neighbor_id:n.get_neighbor_ids())
            if(coloring.at(neighbor_id)==color) return false;
    }
    return colors.size()<=k;
}

unordered_map<int,int> coloring_backtracking(const graph& G, int k) {
    unordered_map<int,int> coloring;
    return coloring_backtracking(G,k,coloring);
}

unordered_map<int,int> coloring_backtracking(const graph& G, int k, unordered_map<int,int>& coloring) {
    int node_id = choose_next_node(G,k,coloring);
    if(node_id==-1) return coloring;
    
    for(int color:get_available_colors(G,node_id,k,coloring)) {
        coloring[node_id] = color;
        if(!coloring_backtracking(G,k,coloring).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {};
}

unordered_map<int,int> coloring_sat(const graph& G,int k) {
    vector<clause> clauses;
    for(const auto& [id,n]:G.get_nodes()) {
        clause at_least_one;
        for(int c=1;c<=k;c++) at_least_one.push_back(id*k+c);
        clauses.push_back(at_least_one);
        
        for(int neighbor_id:n.get_neighbor_ids()) {
            if(neighbor_id>id) {
                for(int c=1;c<=k;c++) {
                    clauses.push_back({-(id*k+c),-(neighbor_id*k+c)});
                }
            }
        }
    }

    sat SAT(clauses);
    auto assignment = SAT.solve_naive();
    if(assignment.empty()) return {};

    unordered_map<int,int> coloring;
    for(const auto& [id,n]:G.get_nodes()) {
        for(int c=1;c<=k;c++) {
            if(assignment.at(id*k+c)) {
                coloring[id] = c;
                break;
            }
        }
    }

    return coloring;
}