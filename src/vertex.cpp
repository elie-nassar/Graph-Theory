#include "vertex.hpp"

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