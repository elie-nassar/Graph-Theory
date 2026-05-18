#pragma once
#include "map"
#include "fstream"
#include "iostream"
#include "node.hpp"

using namespace std;

class graph {
    private:
        map<int,node> nodes;
        int next_id = 0;

    public:
        graph();
        graph(map<int,node> nodes);
        
        const map<int,node>& get_nodes() const;
        const node& get_node_by_id(int id) const;
        int add_node();
        void add_edge(int u,int v);
        void add_edge(node& u,node& v);
        bool is_well_formed() const;
        friend ostream& operator<<(ostream& os, const graph& G);
        int size() const;
        int save(string filename) const;
};