#include "doctest.h"

#include "graph.hpp"

TEST_CASE("graph default constructor") {
    graph g;

    CHECK(g.get_nodes().empty());
}

TEST_CASE("add_node") {
    graph g;
    int id0 = g.add_node();
    int id1 = g.add_node();
    CHECK(g.get_nodes().size()==2);
    CHECK(id0==0);
    CHECK(id1==1);
    CHECK(g.get_node_by_id(id0).get_id()==0);
    CHECK(g.get_node_by_id(id1).get_id()==1);
}

TEST_CASE("add_edge") {
    graph g;
    int id0 = g.add_node();
    int id1 = g.add_node();
    int id2 = g.add_node();
    g.add_edge(id0,id1);
    g.add_edge(id0,id2);
    CHECK(g.get_node_by_id(id0).get_neighbor_ids().contains(id1));
    CHECK(g.get_node_by_id(id0).get_neighbor_ids().contains(id2));
    CHECK(g.get_node_by_id(id1).get_neighbor_ids().contains(id0));
    CHECK(g.get_node_by_id(id2).get_neighbor_ids().contains(id0));
    CHECK(!g.get_node_by_id(id1).get_neighbor_ids().contains(id2));
    CHECK(!g.get_node_by_id(id2).get_neighbor_ids().contains(id1));
}