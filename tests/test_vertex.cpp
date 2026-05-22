#include "doctest.h"
#include "vertex.hpp"

#include <set>

TEST_CASE("node default constructor") {
    vertex n;

    CHECK(n.get_id() == 0);
    CHECK(n.get_neighbor_ids().empty());
}

TEST_CASE("node constructor with id") {
    vertex n(5);

    CHECK(n.get_id() == 5);
    CHECK(n.get_neighbor_ids().empty());
}

TEST_CASE("node constructor with id and neighbors") {
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