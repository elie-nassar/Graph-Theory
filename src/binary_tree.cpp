#include "binary_tree.hpp"

binary_tree::binary_tree() : root(node(0,nullptr,nullptr)) {}
node binary_tree::get_root() const {return root;}

node::node(int value,node* left_child,node* right_child) : value(value),left_child(left_child), right_child(right_child) {}
node::node(int value) : value(value),left_child(nullptr), right_child(nullptr) {}
int node::get_value() const {return value;}
node* node::get_left_child() const {return left_child;}
node* node::get_right_child() const {return right_child;}
void node::set_right_child(node* right_child) {this->right_child = right_child;}
void node::set_left_child(node* left_child) {this->left_child = left_child;}
