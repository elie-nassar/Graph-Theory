#include "graph.hpp"
#include "sat.hpp"
#include "coloring/proper_coloring.hpp"
#include "coloring/dominator_coloring.hpp"
#include "coloring/dicoloring.hpp"
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    graph g(true);
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_edge(0,1);
    g.add_edge(1,2);
    g.add_edge(2,3);
    g.add_edge(3,0);
    g.add_edge(0,2);
    g.save("graph");
    vector<int> coloring = {1,1,1,2};
    g.save("coloring",coloring);
    cout << verify_dicoloring(g,4,coloring) << endl;;

    return 0;
}