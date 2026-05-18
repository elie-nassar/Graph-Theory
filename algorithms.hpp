#pragma once
#include "graph.hpp"

map<int,int> empty(const graph& G){
    map<int,int> m;
    for(const auto& it:G.get_nodes()) {
        m[it.first]=-1;
    }
    return m;
}

int choice(const graph& G,int k,map<int,int> c) {
    for(const auto& it:G.get_nodes()){
        if(c[it.first]==-1) return it.first;
    }
    return -1;
}

vector<int> availableColors(graph G, int k, map<int,int> c) 

int graphColoring(graph G,int k,int c[]) {

}