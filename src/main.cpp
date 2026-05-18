#include "graph.hpp"
#include "algorithms.hpp"

int main() {

    graph G = graph();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();

    G.add_edge(0,1);
    G.add_edge(1,2);
    G.add_edge(2,3);
    G.add_edge(3,0);


    cout << G.is_well_formed() << endl;

    cout << G << endl;
    G.save("img");
    return 0;
}