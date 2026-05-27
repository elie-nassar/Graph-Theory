#include "graph.hpp"

graph::graph() : adjacency_list({}), directed(false) {}
graph::graph(bool directed) : adjacency_list({}), directed(directed) {}

const std::vector<std::set<int>>& graph::get_adjacency_list() const {
    return adjacency_list;
}

const std::set<int>& graph::get_neighbors(int id) const {
    return adjacency_list[id];
}

int graph::add_vertex() {
    adjacency_list.push_back({});
    return adjacency_list.size()-1;
}

void graph::add_edge(int u, int v) {
    adjacency_list[u].insert(v);
    if(!directed) adjacency_list[v].insert(u);
}

bool graph::is_well_formed() const {
    for(int u=0;u<(int)adjacency_list.size();u++) {
        for(int v:adjacency_list[u]) {
            if(v>=(int)adjacency_list.size()) return false;
            if(!directed && !adjacency_list[v].contains(u)) return false;
        }
    } 
    return true;
}

std::string graph::to_dot() const {
    return to_dot({});
}

std::string graph::to_dot(const std::vector<int> &coloring) const{
    std::string s = directed ? "digraph {\n" : "graph {\n";
    for(int u=0;u<(int)adjacency_list.size();u++) {
        if (!coloring.empty()) {
            s += "  " + std::to_string(u) + " [fillcolor=\"/rdbu11/"+std::to_string(coloring[u]) + "\" style=filled]\n";
        }
        else s += "  " + std::to_string(u) + "\n";
        for (int v:adjacency_list[u])
            if(!directed) {
                if (v > u) s += "  " + std::to_string(u) + "--" + std::to_string(v) + "\n";
            }else {
                s += "  " + std::to_string(u) + "->" + std::to_string(v) + "\n";
            }
    }
    s += "}";
    return s;
}

std::ostream &operator<<(std::ostream &os, const graph &G) {
    os << G.to_dot();
    return os;
}

int graph::size() const {
    return adjacency_list.size();
}

int graph::save(std::string filename) const {
    return save(filename, {});
}

int graph::save(std::string filename, const std::vector<int> &coloring) const {
    std::string dot_file = "./bin/" + filename + ".dot";
    std::string png_file = "./bin/" + filename + ".png";

    std::ofstream f(dot_file);
    f << this->to_dot(coloring);
    f.close();

    return system(("circo -Tpng " + dot_file + " -o " + png_file).c_str());
}

graph graph::random(int node_count, int edge_count) {
    graph g = graph();
    for(int i=0;i<node_count;i++) g.add_vertex();
    std::vector<std::pair<int,int>> edges;
    for(int i=0;i<node_count;i++)
        for(int j=i+1;j<node_count;j++)
            edges.push_back({i,j});
    
    for (int i=edges.size()-1;i>=0;i--) {
        int j = rand()%(i + 1);
        std::pair<int,int> tmp = edges[i];
        edges[i] = edges[j];
        edges[j] = tmp;
        if(i<edge_count) g.add_edge(edges[i].first,edges[i].second);
    }
    
    return g;
}