#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include "vertex.hpp"


class graph {
    private:
        map<int,vertex> vertices;
        int next_id = 0;
        bool directed;

    public:
        graph();
        graph(bool directed);
        
        const map<int,vertex>& get_vertices() const;
        const vertex& get_vertex_by_id(int id) const;
        int add_vertex();
        void add_edge(int u,int v);
        void add_edge(vertex& u,vertex& v);
        bool is_well_formed() const;
        int size() const;
        int save(string filename) const;
        int save(string filename,const unordered_map<int,int>& coloring) const;
        string to_dot() const;
        string to_dot(const unordered_map<int,int>& coloring) const;
        friend ostream& operator<<(ostream& os, const graph& G);
        static graph random(int vertex_count, int edge_count);
};