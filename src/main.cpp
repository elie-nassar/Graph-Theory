#include "graph.hpp"
#include "sat.hpp"
#include "proper_coloring.hpp"
#include "binary_tree.hpp"
#include <ctime>
#include <set>

int main() {
    srand(time(0));

    binary_tree bt;
    node c12(2);
    node c1m2(-2);
    node cm12(2);
    node cm1m2(-2);
    node c1(1,&c12,&c1m2);
    node cm1(-1,&cm12,&cm1m2);
    bt.get_root()->set_left_child(&c1);
    bt.get_root()->set_right_child(&cm1);
    cout << bt.get_root()->get_left_child()->get_value() << endl;
    cout << bt.to_dot() << endl;
    bt.save("binary_tree");

    /* for(int i=0;i<1;i++) {
        graph G = graph::random(20,50);
        //G.save("img");

        clock_t before = clock();
        unordered_map<int,int> c_back = proper_coloring_backtracking(G,3);
        clock_t duration_back = clock() - before;
        cout << "Backtracking : " << (float)duration_back / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        unordered_map<int,int> c_sat = proper_coloring_sat(G,3);
        clock_t duration_sat = clock() - before;
        cout << "SAT : " << (float)duration_sat / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        unordered_map<int,int> c_dp = proper_coloring_dp(G,3);
        clock_t duration_dp = clock() - before;
        cout << "DP : " << (float)duration_dp / CLOCKS_PER_SEC << "sec" << endl;
        if(!verify_proper_coloring(G,3,c_back)) cout << "ERREUR BACKTRACKING" << endl;
        if(!verify_proper_coloring(G,3,c_sat)) cout << "ERREUR SAT" << endl;
        if(!verify_proper_coloring(G,3,c_dp)) cout << "ERREUR DP" << endl;
        //G.save("coloring_backtracking",c_back);
        //G.save("coloring_sat",c_sat);
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