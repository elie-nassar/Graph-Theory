#include "graph.hpp"
#include "graph_coloring.hpp"

int main() {
    srand(time(0));

    graph G = graph::random(5,5);;

    G.save("img");

    vector<int> coloring = graph_coloring_backtracking(G,3);
    if(!coloring.empty()) {
        cout << "Coloration possible : bin/coloring.png" << endl;
        G.save("coloring",coloring);
    }else cout << "Coloration impossible" << endl;

    return 0;
}