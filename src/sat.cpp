#include "sat.hpp"

sat::sat(const vector<clause> &clauses) : clauses(clauses) {
    for(const clause& c:clauses) {
        for(const literal& l:c) {
            if(l<0) variables.push_back(-l);
            else variables.push_back(l);
        }
    }
}

bool sat::evaluate(const unordered_map<int,bool>& assignment) const {
    for(const clause& c:clauses) {
        bool clause_sat = false;
        for(const literal& l:c) {
            if((l>0 and assignment.at(l)) or (l<0 and !assignment.at(-l))) {
                clause_sat=true;
                break;
            }
        };
        if(!clause_sat) return false;
    }
    return true;
}

unordered_map<int,bool> sat::solve_naive() {
    unordered_map<int,bool> assignment;
    assignment.reserve(variables.size());
    for (int mask=0;mask<(1 << variables.size());mask++) {
        for(int i=0;i<(int)variables.size();i++) assignment[variables[i]] = (mask >> i) & 1;
        if(evaluate(assignment)) return assignment;
    }
    return {};
}

ostream& operator<<(ostream& os, const sat& SAT) {
    for(int i=0;i<(int)SAT.clauses.size();i++) {
        clause c = SAT.clauses[i];
        os << "(";
        for(int j=0;j<(int)c.size();j++) {
            if(c[j]<0) os << "-";
            os << "x" << abs(c[j]);
            if(j<(int)c.size()-1) os << " or ";
        }
        os << ")";
        if(i<(int)SAT.clauses.size()-1) os << " and ";
    }
    return os;
}