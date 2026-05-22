#include "doctest.h"
#include "binary_tree.hpp"

TEST_CASE("binaray_tree constructor") {
    binary_tree bt;
    CHECK(bt.get_root().get_value()==0);
    CHECK(bt.get_root().get_left_child()==nullptr);
    CHECK(bt.get_root().get_right_child()==nullptr);
}

TEST_CASE("node constructor with value") {
    node n1(1);
    CHECK(n1.get_right_child()==nullptr);
    CHECK(n1.get_left_child()==nullptr);
    CHECK(n1.get_value()==1);
}

TEST_CASE("node consructor with children") {
    node c1(1);
    node c2(3);
    node p(2,&c1,&c2);
    CHECK(p.get_value()==2);
    CHECK(p.get_left_child()==&c1);
    CHECK(p.get_right_child()==&c2);
}