class node {
    private:
        int value;
        node* left_child;
        node* right_child;
    public:
        node(int value,node* left_child,node* right_child);
        node(int value);
        int get_value() const;
        node* get_left_child() const;
        node* get_right_child() const;
        void set_right_child(node* right_child);
        void set_left_child(node* left_child);
};

class binary_tree {
    private:
        node root;
    public:
        binary_tree();
        node get_root() const;
};