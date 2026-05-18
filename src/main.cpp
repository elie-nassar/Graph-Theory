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


    cout << G.is_well_formed() << endl;

    cout << G << endl;
    G.save("img");
    return 0;
}