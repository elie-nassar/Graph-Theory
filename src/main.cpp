#include "graph.hpp"
#include "sat.hpp"
#include "proper_coloring.hpp"
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    float tot_back = 0, tot_sat = 0, tot_dp = 0, tot_dp_naive = 0, tot_dp_max = 0;
    int N = 50;
    for(int i=0;i<N;i++) {
        graph G = graph::random(20,40);

        clock_t before = clock();
        std::vector<int> c_back = proper_coloring_backtracking(G,3);
        clock_t duration_back = clock() - before;
        cout << "Backtracking : " << (float)duration_back / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        vector<int> c_sat = proper_coloring_sat(G,3);
        clock_t duration_sat = clock() - before;
        cout << "SAT : " << (float)duration_sat / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        //vector<int> c_dp = proper_coloring_dp(G,3);
        clock_t duration_dp = clock() - before;
        cout << "DP : " << (float)duration_dp / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        //vector<int> c_dp_naive = proper_coloring_dp_naive(G,3);
        clock_t duration_dp_naive = clock() - before;
        cout << "DP Naif : " << (float)duration_dp_naive / CLOCKS_PER_SEC << "sec" << endl;
        before = clock();
        vector<int> c_dp_max = proper_coloring_dp_max_independant_sets(G,3);
        clock_t duration_dp_max = clock() - before;
        cout << "DP Max : " << (float)duration_dp_max / CLOCKS_PER_SEC << "sec" << endl;
        if(!verify_proper_coloring(G,3,c_back)) cout << "ERREUR BACKTRACKING" << endl;
        if(!verify_proper_coloring(G,3,c_sat)) cout << "ERREUR SAT" << endl;
        if(!verify_proper_coloring(G,3,c_dp_max)) cout << "ERREUR DP MAX" << endl;
        //if(!verify_proper_coloring(G,3,c_dp_naive)) cout << "ERREUR DP Naif" << endl;
        //if(!verify_proper_coloring(G,3,c_dp)) cout << "ERREUR DP" << endl;
        tot_back+=(float)duration_back / CLOCKS_PER_SEC;
        tot_sat+=(float)duration_sat / CLOCKS_PER_SEC;
        tot_dp+=(float)duration_dp / CLOCKS_PER_SEC;
        tot_dp_naive+=(float)duration_dp_naive / CLOCKS_PER_SEC;
        tot_dp_max+=(float)duration_dp_max / CLOCKS_PER_SEC;
    }
    cout << "Moyenne Backtracking : " << tot_back/N << "sec" << endl;
    cout << "Moyenne SAT : " << tot_sat/N << "sec" << endl;
    cout << "Moyenne DP naif : " << tot_dp_naive/N << "sec" << endl;
    cout << "Moyenne DP : " << tot_dp/N << "sec" << endl;
    cout << "Moyenne DP MAX : " << tot_dp_max/N << "sec" << endl;

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