#pragma once
#include "map"
#include "node.hpp"

using namespace std;

class graph {
    private:
        map<int,node> nodes;

    public:
        graph();
        graph(map<int,node> nodes);
        
        const map<int,node>& get_nodes() const;
        const node& get_node_by_id(int id) const;
        int add_node();
        void add_edge(int u,int v);
        void add_edge(node& u,node& v);
        bool is_well_formed() const;
};