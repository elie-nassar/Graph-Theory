#include "doctest.h"

#include "graph.hpp"
#include "proper_coloring.hpp"

TEST_CASE("proper_coloring_backtracking") {
    graph g;
    g.add_node();
    g.add_node();
    g.add_node();
    CHECK(!proper_coloring_backtracking(g,1).empty());
    g.add_edge(0,1);
    CHECK(proper_coloring_backtracking(g,1).empty());
    CHECK(!proper_coloring_backtracking(g,2).empty());
    CHECK(verify_proper_coloring(g,2,proper_coloring_backtracking(g,2)));
    g.add_edge(1,2);
    g.add_edge(2,0);
    CHECK(proper_coloring_backtracking(g,1).empty());
    CHECK(proper_coloring_backtracking(g,2).empty());
    CHECK(!proper_coloring_backtracking(g,3).empty());
    CHECK(verify_proper_coloring(g,3,proper_coloring_backtracking(g,3)));
}

TEST_CASE("proper_coloring_sat") {
    graph g;
    g.add_node();
    g.add_node();
    g.add_node();
    CHECK(!proper_coloring_sat(g,1).empty());
    g.add_edge(0,1);
    CHECK(proper_coloring_sat(g,1).empty());
    CHECK(!proper_coloring_sat(g,2).empty());
    CHECK(verify_proper_coloring(g,2,proper_coloring_sat(g,2)));
    g.add_edge(1,2);
    g.add_edge(2,0);
    CHECK(proper_coloring_sat(g,1).empty());
    CHECK(proper_coloring_sat(g,2).empty());
    CHECK(!proper_coloring_sat(g,3).empty());
    CHECK(verify_proper_coloring(g,3,proper_coloring_sat(g,3)));
}


TEST_CASE("proper_coloring_dp") {
    graph g;
    g.add_node();
    g.add_node();
    g.add_node();
    CHECK(!proper_coloring_dp(g,1).empty());
    g.add_edge(0,1);
    CHECK(proper_coloring_dp(g,1).empty());
    CHECK(!proper_coloring_dp(g,2).empty());
    CHECK(verify_proper_coloring(g,2,proper_coloring_dp(g,2)));
    g.add_edge(1,2);
    g.add_edge(2,0);
    CHECK(proper_coloring_dp(g,1).empty());
    CHECK(proper_coloring_dp(g,2).empty());
    CHECK(!proper_coloring_dp(g,3).empty());
    CHECK(verify_proper_coloring(g,3,proper_coloring_dp(g,3)));
}