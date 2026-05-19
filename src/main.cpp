#include "graph.hpp"
#include "sat.hpp"
#include "graph_coloring.hpp"

int main() {
    srand(time(0));

    graph G = graph::random(15,20);;

    G.save("img");

    vector<int> coloring = coloring_backtracking(G,4);
    if(!coloring.empty()) {
        cout << "Coloration possible : bin/coloring.png" << endl;
        G.save("coloring",coloring);
    }else cout << "Coloration impossible" << endl;

    sat SAT = sat({
        {literal(0),literal(1),literal(0,true)},
        {literal(0),literal(2)},
        {literal(0),literal(1),literal(3,true)}
    });

    cout << SAT << endl;
    cout << SAT.get_variable_count() << endl;

    return 0;
}