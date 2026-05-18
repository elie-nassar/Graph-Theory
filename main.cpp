#include "graph.hpp"
#include "algorithms.hpp"

int main() {

    graph G = graph();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_node();

    G.add_edge(0,1);
    G.add_edge(1,2);
    G.add_edge(2,3);
    G.add_edge(3,0);


    cout << G.is_well_formed() << endl;

    cout << "Graph :" << std::endl;
    for (const auto& it : G.get_nodes()) {
        int id = it.first;
        const node& n = it.second;
        cout << " node : " << id << std::endl;
        for (int neighbor : n.get_neighbor_ids())
            cout << "  neighbor : " << neighbor << std::endl;
    }
    
    cout << choice(G,2,empty(G)) << endl;
    map<int,int> coloration = color(G,2,empty(G));

    return 0;
}