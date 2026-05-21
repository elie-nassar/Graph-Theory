#include "graph.hpp"
#include "sat.hpp"
#include "proper_coloring.hpp"
#include <ctime>

int main() {
    srand(time(0));

    graph G = graph();
    G.add_node();
    G.add_node();
    G.add_node();
    G.add_edge(0,1);
    G.add_edge(1,2);
    G.add_edge(2,0);
    G.save("oriented");

    /* for(int i=0;i<1;i++) {
        graph G = graph::random(20,40);
        G.save("img");

        clock_t before = clock();
        unordered_map<int,int> c_back = coloring_backtracking(G,3);
        clock_t duration_back = clock() - before;
        cout << "Backtracking : " << (float)duration_back / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        unordered_map<int,int> c_sat = proper_coloring_sat(G,3);
        clock_t duration_sat = clock() - before;
        cout << "SAT : " << (float)duration_sat / CLOCKS_PER_SEC << "sec" << endl;
        if(!verify_coloring(G,3,c_back)) cout << "ERREUR BACKTRACKING" << endl;
        if(!verify_proper_coloring(G,3,c_sat)) cout << "ERREUR SAT" << endl;
        G.save("coloring_backtracking",c_back);
        G.save("coloring_sat",c_sat);
    } */

    /* sat SAT = sat({
        {1,2,3},
        {-1,3},
        {1,2},
        {1,-2,3},
    });

    cout << SAT << endl;

    unordered_map<int,bool> sol = SAT.solve_dpll();
    for(auto [id,val]:sol) {
        cout << id << ":" << val << endl;
    } */

    return 0;
}