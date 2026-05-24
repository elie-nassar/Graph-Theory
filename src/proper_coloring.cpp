#include "proper_coloring.hpp"
#include "sat.hpp"

int choose_next_node(const graph& G, int k,const unordered_map<int,int>& coloring) {
    for(const auto& [id,n]:G.get_vertices())
        if(!coloring.contains(id) or coloring.at(id)==0) return id;
    return -1;
}

unordered_set<int> get_available_colors(const graph& G, int node_id, int k, const unordered_map<int,int>& coloring) {
    unordered_set<int> unavailable_colors;
    unavailable_colors.reserve(k);
    for(auto& neighbor_id:G.get_vertex_by_id(node_id).get_neighbor_ids()) {
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

bool verify_proper_coloring(const graph& G,int k, const unordered_map<int,int>& coloring) {
    if(coloring.empty()) return true;
    unordered_set<int> colors;
    colors.reserve(k);
    for(const auto& [id,n]:G.get_vertices()) {
        int color = coloring.at(id);
        colors.insert(color);
        for(int neighbor_id:n.get_neighbor_ids())
            if(coloring.at(neighbor_id)==color) return false;
    }
    return colors.size()<=k;
}

unordered_map<int,int> proper_coloring_backtracking(const graph& G, int k, unordered_map<int,int>& coloring) {
    int node_id = choose_next_node(G,k,coloring);
    if(node_id==-1) return coloring;
    
    for(int color:get_available_colors(G,node_id,k,coloring)) {
        coloring[node_id] = color;
        if(!proper_coloring_backtracking(G,k,coloring).empty()) return coloring;
        coloring[node_id] = 0;
    }

    return {};
}

unordered_map<int,int> proper_coloring_backtracking(const graph& G, int k) {
    unordered_map<int,int> coloring;
    coloring.reserve(G.size());
    return proper_coloring_backtracking(G,k,coloring);
}

unordered_map<int,int> proper_coloring_sat(const graph& G,int k) {
    vector<clause> clauses;
    for(const auto& [id,n]:G.get_vertices()) {
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
    auto assignment = SAT.solve_dpll();
    if(assignment.empty()) return {};

    unordered_map<int,int> coloring;
    for(const auto& [id,n]:G.get_vertices()) {
        for(int c=1;c<=k;c++) {
            if(assignment.at(id*k+c)) {
                coloring[id] = c;
                break;
            }
        }
    }

    return coloring;
}

unordered_map<int,int> proper_coloring_dp_naive(const graph& G, int k) {
    map<set<int>,unordered_map<int,int>> coloring_dp[k+1];
    vector<int> node_ids;
    for(const auto& [id,n]:G.get_vertices()) node_ids.push_back(id);

    set<set<int>> candidate_sets;
    for (int mask=1;mask<(1 << node_ids.size());mask++){
        set<int> candidate_set;
        for(int id=0;id<node_ids.size();id++) 
            if((mask >> id) & 1) candidate_set.insert(id);
        candidate_sets.insert(candidate_set);
    }

    // j=1
    for(const set<int>& candidate_set:candidate_sets) {
        bool is_independant = true;
        unordered_map<int,int> assignment;
        for(int id:candidate_set) {
            assignment[id]=1;
            for(int neighbor_id:G.get_vertex_by_id(id).get_neighbor_ids()) {
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
        for(const set<int>& candidate_set:candidate_sets) {
            vector<int> v(candidate_set.begin(),candidate_set.end());
            for (int mask=1;mask<(1 << v.size());mask++){
                set<int> p1,p2;
                for(int i=0;i<v.size();i++) {
                    if((mask >> i) & 1) p1.insert(v[i]);
                    else p2.insert(v[i]);
                }
                if(coloring_dp[1].contains(p1) and coloring_dp[j-1].contains(p2)) {
                    unordered_map<int,int> assignment;
                    for(const auto& [id,color]:coloring_dp[1][p1]) assignment[id] = color;
                    for(const auto& [id,color]:coloring_dp[j-1][p2]) assignment[id] = color+1;
                    coloring_dp[j][candidate_set] = assignment;
                    break;
                }
                if(coloring_dp[1].contains(p2) and coloring_dp[j-1].contains(p1)) {
                    unordered_map<int,int> assignment;
                    for(const auto& [id,color]:coloring_dp[1][p2]) assignment[id] = color;
                    for(const auto& [id,color]:coloring_dp[j-1][p1]) assignment[id] = color+1;
                    coloring_dp[j][candidate_set] = assignment;
                    break;
                }
            }

        }
    }

    set<int> node_ids_set = set<int>(node_ids.begin(),node_ids.end());
    if(coloring_dp[k].contains(node_ids_set)) return coloring_dp[k][node_ids_set];
    return {};
}

set<set<int>> get_maximal_independant_sets(const graph& G) {
    set<set<int>> maximal_independant_sets;
    set<int> unvisited_vertices;
    for(const auto& [id,vert]:G.get_vertices()) unvisited_vertices.insert(id);

    while(!unvisited_vertices.empty()) {
        int vertex_id = *unvisited_vertices.begin();
        set<int> indep_max = {vertex_id};
        set<int> next_vertices = unvisited_vertices;
        
    }


    return maximal_independant_sets;
} 

unordered_map<int,int> proper_coloring_dp(const graph& G, int k) {
    set<set<int>> maximal_independant_sets = get_maximal_independant_sets(G);
    for(const auto& indep_set:maximal_independant_sets) {
        for(const int& i:indep_set) cout << i << " ";
        cout << endl;
    }
    cout << "hey" << endl;
    return {};
}