#include "graph.hpp"
#include "sat.hpp"
#include "graph_coloring.hpp"

int main() {
    srand(time(0));

    sat SAT = sat({
        {3,1,1},
        {1,-2,3},
        {2,2,-2},
    });
    cout << SAT << endl;
    unordered_map<int,bool> s = SAT.solve();
    for(auto it:s) {
        cout << it.first << " : " << it.second << endl;
    }

    return 0;
}