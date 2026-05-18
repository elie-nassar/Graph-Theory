#include "node.hpp"

node::node() : node(0) {}
node::node(int id) : node(id,set<int>()) {}
node::node(int id,const set<int>& neighbor_ids) : id(id), neighbor_ids(neighbor_ids) {}

const int node::get_id() const{
    return id;
}

const set<int>& node::get_neighbor_ids() const{
    return neighbor_ids;
}

void node::add_neighbor(int neighbor_id) {
    neighbor_ids.insert(neighbor_id);
}

void node::remove_neighbor(int neighbor_id) {
    neighbor_ids.erase(neighbor_id);
}