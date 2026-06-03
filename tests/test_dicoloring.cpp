#include "doctest.h"

#include "graph.hpp"
#include "coloring/dicoloring.hpp"

TEST_CASE("dicoloring_backtracking") {
    graph g(true);
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_edge(0,1);
    g.add_edge(1,2);
    g.add_edge(2,3);
    g.add_edge(3,0);
    g.add_edge(0,2);
    CHECK(dicoloring_backtracking(g,1).empty());
    CHECK(!dicoloring_backtracking(g,2).empty());
    g.add_edge(1,3);
    CHECK(dicoloring_backtracking(g,1).empty());
    CHECK(!dicoloring_backtracking(g,2).empty());
}