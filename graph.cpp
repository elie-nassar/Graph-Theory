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
    int id=0;
    while(nodes.contains(id)) id++;
    nodes[id] = node(id);
    return id;
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
            auto it_node2 = nodes.find(id2);
            const node& n2 = it_node2->second;
            if(!n2.get_neighbor_ids().contains(id1)) return false;
        }
    }
    return true;
}