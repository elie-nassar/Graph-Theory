#include "doctest.h"
#include "graph.hpp"

TEST_CASE("graph default constructor") {
    graph g;

    CHECK(g.get_adjacency_list().empty());
}

TEST_CASE("directed graph") {
    graph g(true);
    CHECK(g.get_adjacency_list().empty());
    g.add_vertex();
    g.add_vertex();
    CHECK(g.get_adjacency_list().size()==2);
    g.add_edge(0,1);
    CHECK(g.get_neighbors(0).size()==1);
    CHECK(g.get_neighbors(1).size()==0);
    CHECK(g.is_well_formed());
}

TEST_CASE("add_node") {
    graph g;
    int id0 = g.add_vertex();
    int id1 = g.add_vertex();
    CHECK(g.get_adjacency_list().size()==2);
    CHECK(id0==0);
    CHECK(id1==1);
    CHECK(g.is_well_formed());
}

TEST_CASE("add_edge") {
    graph g;
    int id0 = g.add_vertex();
    int id1 = g.add_vertex();
    int id2 = g.add_vertex();
    g.add_edge(id0,id1);
    g.add_edge(id0,id2);
    CHECK(g.get_neighbors(id0).contains(id1));
    CHECK(g.get_neighbors(id0).contains(id2));
    CHECK(g.get_neighbors(id1).contains(id0));
    CHECK(g.get_neighbors(id2).contains(id0));
    CHECK(!g.get_neighbors(id1).contains(id2));
    CHECK(!g.get_neighbors(id2).contains(id1));
    CHECK(g.is_well_formed());
}

TEST_CASE("random") {
    for(int i=2;i<10;i++) {
        graph g = graph::random(i,i*2);
        CHECK(g.is_well_formed());
    }
}

TEST_CASE("connected") {
    graph g;
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    CHECK(!g.is_connected());
    g.add_edge(0,1);
    CHECK(!g.is_connected());
    g.add_edge(0,2);
    CHECK(g.is_connected());
    g.add_edge(1,2);
    CHECK(g.is_connected());
}