#include <fstream>
#include <iostream>

using namespace std;

class node {
    static int next_id;
    private:
        int id;
        int value;
        node* left_child;
        node* right_child;
    public:
        node(int value,node* left_child,node* right_child);
        node(int value);
        int get_value() const;
        int get_id() const;
        node* get_left_child() const;
        node* get_right_child() const;
        void set_right_child(node* right_child);
        void set_left_child(node* left_child);
        string to_dot() const;
};

class binary_tree {
    private:
        node root;
    public:
        binary_tree();
        node* get_root();
        string to_dot() const;
        friend ostream& operator<<(ostream& os, const binary_tree& bt);
        int save(string filename) const;
};