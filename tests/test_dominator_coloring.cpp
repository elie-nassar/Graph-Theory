#include "doctest.h"

#include "graph.hpp"
#include "coloring/dominator_coloring.hpp"

TEST_CASE("dominator_coloring_backtracking") {
    graph g;
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    CHECK(!dominator_coloring_backtracking(g,1).empty());
    CHECK(verify_dominator_coloring(g,1,dominator_coloring_backtracking(g,1)));
    CHECK(dominator_coloring_backtracking(g,2).empty());
    CHECK(dominator_coloring_backtracking(g,3).empty());
    g.add_edge(0,1);
    CHECK(!dominator_coloring_backtracking(g,1).empty());
    CHECK(verify_dominator_coloring(g,1,dominator_coloring_backtracking(g,1)));
    CHECK(dominator_coloring_backtracking(g,2).empty());
    CHECK(dominator_coloring_backtracking(g,3).empty());
    g.add_edge(0,2);
    CHECK(!dominator_coloring_backtracking(g,1).empty());
    CHECK(!dominator_coloring_backtracking(g,2).empty());
    CHECK(verify_dominator_coloring(g,2,dominator_coloring_backtracking(g,2)));
    CHECK(dominator_coloring_backtracking(g,3).empty());
    g.add_edge(1,2);
    CHECK(!dominator_coloring_backtracking(g,3).empty());
    CHECK(verify_dominator_coloring(g,3,dominator_coloring_backtracking(g,3)));
}