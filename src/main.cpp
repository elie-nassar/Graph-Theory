#include "graph.hpp"
#include "sat.hpp"
#include "graph_coloring.hpp"

int main() {
    srand(time(0));

    for(int i=0;i<5;i++) {
        graph G = graph::random(5,5);
        vector<int> c_bat = coloring_backtracking(G,2);
        vector<int> c_sat = coloring_backtracking(G,2);
        if(!verify_coloring(G,3,c_bat)) cout << "ERREUR BACKTRACKING" << endl;
        if(!verify_coloring(G,3,c_sat)) cout << "ERREUR SAT" << endl;
    }
    return 0;
}