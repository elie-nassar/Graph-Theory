#include "graph.hpp"

graph::graph() : nodes(map<int,node>()) {}
graph::graph(map<int,node> nodes) : nodes(nodes) {}

const map<int,node>& graph::get_nodes() const{
    return nodes;
}

const node& graph::get_node_by_id(int id) const{
    return nodes.at(id);
}

int graph::add_node() {
    nodes[next_id] = node(next_id);
    return next_id++;
}

void graph::add_edge(int u, int v) {
    add_edge(nodes.at(u),nodes.at(v));
}

void graph::add_edge(node& u,node& v) {
    u.add_neighbor(v.get_id());
    v.add_neighbor(u.get_id());
}

bool graph::is_well_formed() const{
    for(const auto& it1 : nodes) {
        int id1 = it1.first;
        node n1 = it1.second;
        if(n1.get_id() != id1) return false;
        for(int id2 : n1.get_neighbor_ids()) {
            if(!nodes.contains(id2)) return false;
            node n2 = nodes.at(id2);
            if(!n2.get_neighbor_ids().contains(id1)) return false;
        }
    }
    return true;
}

string graph::to_dot() const {
    return to_dot({});
}

string graph::to_dot(const vector<int>& c) const {
    string s = "graph {\n";
    for (const auto& it : nodes) {
        int id = it.first;
        const node& n = it.second;
        if(!c.empty())
            s += "  " + to_string(id) + " [fillcolor=\"/paired12/" + to_string(c[id]) + "\" style=filled]\n";
        else
            s += "  " + to_string(id) + "\n";
        for (int neighbor_id : n.get_neighbor_ids())
            if(neighbor_id > id)
                s += "  " + to_string(id) + "--" + to_string(neighbor_id) + "\n";
    }
    s += "}";
    return s;
}

ostream& operator<<(ostream& os, const graph& G) {
    os << G.to_dot();
    return os;
}

int graph::size() const{
    return next_id;
}

int graph::save(string filename) const {
    return save(filename,{});
}

int graph::save(string filename,const vector<int>& c) const {
    string dot_file = "./bin/"+filename + ".dot";
    string png_file = "./bin/"+filename + ".png";

    ofstream f(dot_file);
    f << this->to_dot(c);
    f.close();

    return system(("circo -Tpng " + dot_file + " -o " + png_file).c_str());
}