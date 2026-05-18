#include "graph.hpp"
#include "algorithms.hpp"

int main() {

    graph G = graph();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();

    for(int i=0;i<5;i++)
        for(int j=i+1;j<5;j++) 
            G.add_edge(i,j);

    vector<int> coloring = graph_coloring_backtracking(G,5);
    for(int i=0;i<coloring.size();i++) {
        cout << i << " : " << coloring[i] << endl;
    }

    G.save("img",coloring);

    return 0;
}