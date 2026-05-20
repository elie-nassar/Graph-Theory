#include "graph.hpp"
#include "sat.hpp"
#include "graph_coloring.hpp"
#include <ctime>

int main() {
    srand(time(0));


    graph G = graph::random(4,4);
    G.save("img");

    clock_t before = clock();
    unordered_map<int,int> c_back = coloring_backtracking(G,3);
    clock_t duration_back = clock() - before;
    cout << "Backtracking : " << (float)duration_back / CLOCKS_PER_SEC << "sec" << endl;
    before = clock();
    unordered_map<int,int> c_sat = coloring_sat(G,3);
    clock_t duration_sat = clock() - before;
    cout << "SAT : " << (float)duration_sat / CLOCKS_PER_SEC << "sec" << endl;
    if(!verify_coloring(G,3,c_back)) cout << "ERREUR BACKTRACKING" << endl;
    if(!verify_coloring(G,3,c_sat)) cout << "ERREUR SAT" << endl;

    return 0;
}