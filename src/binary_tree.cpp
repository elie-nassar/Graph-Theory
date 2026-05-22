#include "binary_tree.hpp"

binary_tree::binary_tree() : root(node(0,nullptr,nullptr)) {}
node binary_tree::get_root() const {return root;}

node::node(int value,node* left_node,node* right_node) : value(value),left_node(left_node), right_node(right_node) {}
int node::get_value() const {return value;}
node* node::get_left_node() const {return left_node;}
node* node::get_right_node() const {return right_node;}
void node::set_right_node(node* right_node) {this->right_node = right_node;}
void node::set_left_node(node* left_node) {this->left_node = left_node;}
