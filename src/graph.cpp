#include "graph.hpp"

graph::graph() : vertices(map<int, vertex>()), directed(false) {}
graph::graph(bool directed) : vertices(map<int, vertex>()), directed(directed) {}

const map<int, vertex> &graph::get_vertices() const {
    return vertices;
}

const vertex &graph::get_vertex_by_id(int id) const {
    return vertices.at(id);
}

int graph::add_vertex() {
    vertices[next_id] = vertex(next_id);
    return next_id++;
}

void graph::add_edge(int u, int v) {
    add_edge(vertices.at(u), vertices.at(v));
}

void graph::add_edge(vertex &u, vertex &v) {
    u.add_neighbor(v.get_id());
    if(!directed) v.add_neighbor(u.get_id());
}

bool graph::is_well_formed() const {
    for (const auto &[id1,n1] : vertices) {
        if (n1.get_id() != id1) return false;

        for (int id2 : n1.get_neighbor_ids()) {
            if (!vertices.contains(id2)) return false;
            vertex n2 = vertices.at(id2);
            if (!directed and !n2.get_neighbor_ids().contains(id1))
                return false;
        }
    }
    return true;
}

string graph::to_dot() const {
    return to_dot({});
}

string graph::to_dot(const unordered_map<int,int> &coloring) const{
    string s = directed ? "digraph {\n" : "graph {\n";
    for (const auto& [id,n] : vertices) {
        if (!coloring.empty()) {
            s += "  " + to_string(id) + " [fillcolor=\"/rdbu11/"+to_string(coloring.at(id)) + "\" style=filled]\n";
        }
        else s += "  " + to_string(id) + "\n";
        for (int neighbor_id : n.get_neighbor_ids())
            if(!directed) {
                if (neighbor_id > id) s += "  " + to_string(id) + "--" + to_string(neighbor_id) + "\n";
            }else {
                s += "  " + to_string(id) + "->" + to_string(neighbor_id) + "\n";
            }
    }
    s += "}";
    return s;
}

ostream &operator<<(ostream &os, const graph &G) {
    os << G.to_dot();
    return os;
}

int graph::size() const {
    return next_id;
}

int graph::save(string filename) const {
    return save(filename, {});
}

int graph::save(string filename, const unordered_map<int,int> &coloring) const {
    string dot_file = "./bin/" + filename + ".dot";
    string png_file = "./bin/" + filename + ".png";

    ofstream f(dot_file);
    f << this->to_dot(coloring);
    f.close();

    return system(("circo -Tpng " + dot_file + " -o " + png_file).c_str());
}

graph graph::random(int node_count, int edge_count) {
    graph g = graph();
    for(int i=0;i<node_count;i++) g.add_vertex();
    vector<pair<int,int>> edges;
    for(int i=0;i<node_count;i++)
        for(int j=i+1;j<node_count;j++)
            edges.push_back({i,j});
    
    for (int i=edges.size()-1;i>=0;i--) {
        int j = rand()%(i + 1);
        pair<int,int> tmp = edges[i];
        edges[i] = edges[j];
        edges[j] = tmp;
        if(i<edge_count) g.add_edge(edges[i].first,edges[i].second);
    }
    
    return g;
}

vertex::vertex() : vertex(0) {}
vertex::vertex(int id) : vertex(id,set<int>()) {}
vertex::vertex(int id,const set<int>& neighbor_ids) : id(id), neighbor_ids(neighbor_ids) {}

const int vertex::get_id() const{
    return id;
}

const set<int>& vertex::get_neighbor_ids() const{
    return neighbor_ids;
}

void vertex::add_neighbor(int neighbor_id) {
    neighbor_ids.insert(neighbor_id);
}

void vertex::remove_neighbor(int neighbor_id) {
    neighbor_ids.erase(neighbor_id);
}