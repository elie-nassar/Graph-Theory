class binary_tree {
    private:
        node root;
    public:
        binary_tree();
        node get_root() const;
};

class node {
    private:
        int value;
        node* left_node;
        node* right_node;
    public:
        node(int value,node* left_node,node* right_node);
        int get_value() const;
        node* get_left_node() const;
        node* get_right_node() const;
        void set_right_node(node* right_node);
        void set_left_node(node* left_node);
};