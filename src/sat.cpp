#include "sat.hpp"

sat::sat(const set<set<literal>> &formula, int variable_count) : formula(formula), variable_count(variable_count) {}
sat::sat(const set<set<literal>> &formula) : formula(formula) {
    map<int,bool> ids;
    variable_count = 0;
    for(const set<literal> &disjonction:formula) {
        for(const literal &x : disjonction) {
            if(!ids[x.get_id()]) {
                ids[x.get_id()]=true;
                variable_count++;
            }
        }
    }
}

int sat::get_variable_count() const {return variable_count;}

map<int, bool> sat::solve() {

}

map<int,bool> sat::solve(map<int,bool> &m) {
    if(m.size()==formula.size()) return m;

}

ostream &operator<<(ostream &os, const sat &SAT) {
    int dis_count = 0;
    int lit_count = 0;
    for (const set<literal> &disjonction : SAT.formula)
    {
        os << "(";
        lit_count = 0;
        for (const literal &x : disjonction)
        {
            if (x.is_neg())
                os << "-";
            os << "x_" << x.get_id();
            if (lit_count < disjonction.size() - 1)
                os << " or ";
            lit_count++;
        }
        os << ")";
        if (dis_count < SAT.formula.size() - 1)
            os << " and ";
        dis_count++;
    }
    return os;
}