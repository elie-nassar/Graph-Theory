#include "doctest.h"
#include "binary_tree.hpp"

TEST_CASE("binaray_tree constructor") {
    binary_tree bt;
    CHECK(bt.get_root()->get_value()==0);
    CHECK(bt.get_root()->get_left_child()==nullptr);
    CHECK(bt.get_root()->get_right_child()==nullptr);
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

TEST_CASE("node set_left/right_child") {
    binary_tree bt;
    node c12(2);
    node c1m2(-2);
    node cm12(2);
    node cm1m2(-2);
    node c1(1,&c12,&c1m2);
    node cm1(-1,&cm12,&cm1m2);
    bt.get_root()->set_left_child(&c1);
    bt.get_root()->set_right_child(&cm1);
}