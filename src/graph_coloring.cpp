#include "graph_coloring.hpp"
#include "sat.hpp"

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

bool verify_coloring(const graph& G,int k, const vector<int>& coloring) {
    if(coloring.empty()) return true;
    else {
        for(const auto& it:G.get_nodes()) {
            int id = it.first;
            node n = it.second;
            int color = coloring[id];
            for(int neighbor_id:n.get_neighbor_ids())
                if(coloring[neighbor_id]==color) return false;
        }
    }
    return true;
}

vector<int> coloring_backtracking(const graph& G, int k) {
    vector<int> coloring(G.size(),0);
    return coloring_backtracking(G,k,coloring);
}

vector<int> coloring_backtracking(const graph& G, int k, vector<int>& coloring) {
    int node_id = choose_next_node(G,k,coloring);
    if(node_id==-1) return coloring;
    
    for(int color:get_available_colors(G,node_id,k,coloring)) {
        coloring[node_id] = color;
        if(!coloring_backtracking(G,k,coloring).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {};
}

vector<int> coloring_sat(const graph& G,int k) {
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
    auto assignment = SAT.solve();
    if(assignment.empty()) return {};

    vector<int> coloring(G.size(),0);
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