#include "binary_tree.hpp"

binary_tree::binary_tree() : root(node(0,nullptr,nullptr,false)) {}
node* binary_tree::get_root() {return &root;}
string binary_tree::to_dot() const{
    string s = "digraph {\n";
    s+=root.to_dot();
    s+="}";
    return s;
}
ostream &operator<<(ostream &os, const binary_tree &bt) {
    os << bt.to_dot();
    return os;
}
int binary_tree::save(string filename) const {
    string dot_file = "./bin/" + filename + ".dot";
    string png_file = "./bin/" + filename + ".png";

    ofstream f(dot_file);
    f << this->to_dot();
    f.close();

    return system(("dot -Tpng " + dot_file + " -o " + png_file).c_str());
}

int node::next_id = 0;
node::node(int value,node* left_child,node* right_child,bool minus) : value(value),left_child(left_child), right_child(right_child), minus(minus) {id=node::next_id;node::next_id++;}
node::node(int value) : node(value,nullptr,nullptr,false) {}
node::node(int value,bool minus) : node(value,nullptr,nullptr,minus) {}
int node::get_value() const {return value;}
int node::get_id() const {return id;}
bool node::get_minus() const {return minus;}
node* node::get_left_child() const {return left_child;}
node* node::get_right_child() const {return right_child;}
void node::set_right_child(node* right_child) {this->right_child = right_child;}
void node::set_left_child(node* left_child) {this->left_child = left_child;}
string node::to_dot() const {
    string s = to_string(id)+" [label=\""+(get_minus() ? "-" : "")+to_string(value)+"\"]\n";
    if(this->get_left_child()!=nullptr) {
        s+=to_string(id) + "->" + to_string(this->get_left_child()->get_id())+="\n";
        s+=this->get_left_child()->to_dot();
    }
    if(this->get_right_child()!=nullptr) {
        s+=to_string(id) + "->"+ to_string(this->get_right_child()->get_id())+="\n";
        s+=this->get_right_child()->to_dot();
    }
    return s;
}