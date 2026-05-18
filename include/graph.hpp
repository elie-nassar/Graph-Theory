#pragma once
#include "map"
#include "vector"
#include "fstream"
#include "iostream"
#include "node.hpp"


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
        int size() const;
        int save(string filename) const;
        int save(string filename,const vector<int>& c) const;
        string to_dot() const;
        string to_dot(const vector<int>& c) const;
        friend ostream& operator<<(ostream& os, const graph& G);
};