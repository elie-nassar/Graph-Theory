#include "graph.hpp"
#include "sat.hpp"
#include "coloring/proper_coloring.hpp"
#include "coloring/dominator_coloring.hpp"
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    graph g;
    g.add_vertex();
    g.add_vertex();
    g.add_edge(0,1);
    g.save("K3");
    vector<int> coloring = dominator_coloring_sat(g,2);
    g.save("coloring",coloring);

    return 0;
}