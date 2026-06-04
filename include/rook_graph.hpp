#pragma once
#include "graph.hpp"

class rook_graph : public graph {
    private:
        int n;
    public:
        rook_graph(int n);
        std::string to_dot(const std::vector<int> &coloring) const;
        int save(std::string filename) const;
        int save(std::string filename, const std::vector<int> &coloring) const;
        static rook_graph random_directed(int n);
};

int convert(int x,int y,int n);
int getX(int u,int n);
int getY(int u,int n);