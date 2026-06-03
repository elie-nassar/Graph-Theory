#include "graph.hpp"
#include "sat.hpp"
#include "coloring/proper_coloring.hpp"
#include "coloring/dominator_coloring.hpp"
#include "coloring/dicoloring.hpp"
#include "rook_graph.hpp"
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    rook_graph R = rook_graph::random_directed(3);
    while(R.find_dichromatic_number()<=2) R = rook_graph::random_directed(3);
    R.save("Colored_rook_graph",dicoloring_backtracking(R,R.find_dichromatic_number()));
    
    return 0;
}