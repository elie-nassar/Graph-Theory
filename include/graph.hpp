#pragma once
#include <set>
#include <vector>
#include <fstream>
#include <iostream>


class graph {
    private:
        std::vector<std::set<int>> adjacency_list;
        bool directed;

    public:
        graph();
        graph(bool directed);
        
        const std::vector<std::set<int>>& get_adjacency_list() const;
        const std::set<int>& get_neighbors(int id) const;
        int add_vertex();
        void add_edge(int u,int v);
        bool is_well_formed() const;
        bool is_connected() const;
        int size() const;
        int save(std::string filename) const;
        int save(std::string filename,const std::vector<int>& coloring) const;
        std::string to_dot() const;
        std::string to_dot(const std::vector<int>& coloring) const;
        friend std::ostream& operator<<(std::ostream& os, const graph& G);
        static graph random(int vertex_count, int edge_count);
};
