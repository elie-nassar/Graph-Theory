#include "doctest.h"

#include "graph.hpp"

#include <set>

TEST_CASE("vertex default constructor") {
    vertex n;

    CHECK(n.get_id() == 0);
    CHECK(n.get_neighbor_ids().empty());
}

TEST_CASE("vertex constructor with id") {
    vertex n(5);

    CHECK(n.get_id() == 5);
    CHECK(n.get_neighbor_ids().empty());
}

TEST_CASE("vertex constructor with id and neighbors") {
    std::set<int> neighbors = {1, 2, 3};

    vertex n(10, neighbors);

    CHECK(n.get_id() == 10);
    CHECK(n.get_neighbor_ids() == neighbors);
}

TEST_CASE("add_neighbor") {
    vertex n(1);

    n.add_neighbor(2);
    n.add_neighbor(3);

    std::set<int> expected = {2, 3};

    CHECK(n.get_neighbor_ids() == expected);

    n.add_neighbor(2);
    n.add_neighbor(2);
    n.add_neighbor(2);

    CHECK(n.get_neighbor_ids().size() == 2);
    CHECK(n.get_neighbor_ids().count(2) == 1);
}

TEST_CASE("remove_neighbor") {
    vertex n(1);

    n.add_neighbor(2);
    n.add_neighbor(3);

    n.remove_neighbor(2);

    std::set<int> expected = {3};

    CHECK(n.get_neighbor_ids() == expected);
    n.remove_neighbor(999);
    CHECK(n.get_neighbor_ids() == expected);
}

TEST_CASE("add_neighbor and remove_neighbor") {
    vertex n(1);

    n.add_neighbor(1);
    n.add_neighbor(2);
    n.add_neighbor(3);

    n.remove_neighbor(2);
    n.add_neighbor(4);
    n.remove_neighbor(1);

    std::set<int> expected = {3, 4};

    CHECK(n.get_neighbor_ids() == expected);
}

TEST_CASE("graph default constructor") {
    graph g;

    CHECK(g.get_vertices().empty());
}

TEST_CASE("directed graph") {
    graph g(true);
    CHECK(g.get_vertices().empty());
    g.add_vertex();
    g.add_vertex();
    CHECK(g.get_vertices().size()==2);
    g.add_edge(0,1);
    CHECK(g.get_vertex_by_id(0).get_neighbor_ids().size()==1);
    CHECK(g.get_vertex_by_id(1).get_neighbor_ids().size()==0);
    CHECK(g.is_well_formed());
}

TEST_CASE("add_node") {
    graph g;
    int id0 = g.add_vertex();
    int id1 = g.add_vertex();
    CHECK(g.get_vertices().size()==2);
    CHECK(id0==0);
    CHECK(id1==1);
    CHECK(g.get_vertex_by_id(id0).get_id()==0);
    CHECK(g.get_vertex_by_id(id1).get_id()==1);
    CHECK(g.is_well_formed());
}

TEST_CASE("add_edge") {
    graph g;
    int id0 = g.add_vertex();
    int id1 = g.add_vertex();
    int id2 = g.add_vertex();
    g.add_edge(id0,id1);
    g.add_edge(id0,id2);
    CHECK(g.get_vertex_by_id(id0).get_neighbor_ids().contains(id1));
    CHECK(g.get_vertex_by_id(id0).get_neighbor_ids().contains(id2));
    CHECK(g.get_vertex_by_id(id1).get_neighbor_ids().contains(id0));
    CHECK(g.get_vertex_by_id(id2).get_neighbor_ids().contains(id0));
    CHECK(!g.get_vertex_by_id(id1).get_neighbor_ids().contains(id2));
    CHECK(!g.get_vertex_by_id(id2).get_neighbor_ids().contains(id1));
    CHECK(g.is_well_formed());
}

TEST_CASE("random") {
    for(int i=2;i<10;i++) {
        graph g = graph::random(i,i*2);
        CHECK(g.is_well_formed());
    }
}