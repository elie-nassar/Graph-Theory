#include "graph.hpp"
#include "sat.hpp"
#include "proper_coloring.hpp"
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {1,2,3};
    graph g = graph::random(5,5);
    g.save("coloring",proper_coloring_dp(g,2));

    /* float tot_back = 0, tot_sat = 0;
    for(int i=0;i<100;i++) {
        graph G = graph::random(50,250);
        //G.save("img");

        clock_t before = clock();
        //std::vector<int> c_back = proper_coloring_backtracking(G,3);
        clock_t duration_back = clock() - before;
        cout << "Backtracking : " << (float)duration_back / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        vector<int> c_sat = proper_coloring_sat(G,3);
        clock_t duration_sat = clock() - before;
        cout << "SAT : " << (float)duration_sat / CLOCKS_PER_SEC << "sec" << endl;
        //before = clock();
        //unordered_map<int,int> c_dp = proper_coloring_dp(G,3);
        //clock_t duration_dp = clock() - before;
        //cout << "DP : " << (float)duration_dp / CLOCKS_PER_SEC << "sec" << endl;
        //if(!verify_proper_coloring(G,3,c_back)) cout << "ERREUR BACKTRACKING" << endl;
        if(!verify_proper_coloring(G,3,c_sat)) cout << "ERREUR SAT" << endl;
        //if(!verify_proper_coloring(G,3,c_dp)) cout << "ERREUR DP" << endl;
        //G.save("coloring_backtracking",c_back);
        //G.save("coloring_sat",c_sat);
        tot_back+=(float)duration_back / CLOCKS_PER_SEC;
        tot_sat+=(float)duration_sat / CLOCKS_PER_SEC;
    }
    cout << "Moyenne Backtracking : " << tot_back/100 << "sec" << endl;
    cout << "Moyenne SAT : " << tot_sat/100 << "sec" << endl; */

    /* sat SAT = sat({
        {1,2,3},
        {-1,3},
        {1,2},
    });

    cout << SAT << endl;

    vector<bool> sol = SAT.solve_dpll();
    cout << sol.size() << endl;
    for(int i=0;i<sol.size();i++) {
        cout << i+1 << " " << sol[i] << endl;
    } */

    return 0;
}