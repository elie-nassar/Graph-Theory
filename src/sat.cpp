#include "sat.hpp"

sat::sat(const vector<clause> &formula) : formula(formula) {
    for(const clause& c:formula) {
        for(const literal& l:c) {
            if(l<0) variables.push_back(-l);
            else variables.push_back(l);
        }
    }
}

sat::sat(const vector<clause> &formula,const vector<int>& variables) : formula(formula), variables(variables) {}

bool sat::evaluate(const unordered_map<int,bool>& assignment) const {
    for(const clause& c:formula) {
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

ostream& operator<<(ostream& os, const sat& SAT) {
    for(int i=0;i<(int)SAT.formula.size();i++) {
        clause c = SAT.formula[i];
        os << "(";
        for(int j=0;j<(int)c.size();j++) {
            if(c[j]<0) os << "-";
            os << "x" << abs(c[j]);
            if(j<(int)c.size()-1) os << " or ";
        }
        os << ")";
        if(i<(int)SAT.formula.size()-1) os << " and ";
    }
    return os;
}

unordered_map<int,bool> sat::solve_exhaustive() {
    unordered_map<int,bool> assignment;
    assignment.reserve(variables.size());
    for (int mask=0;mask<(1 << variables.size());mask++) {
        int i=0;
        for(int var:variables) {
            assignment[var] = (mask >> i) & 1;
            i++;
        }
        if(evaluate(assignment)) return assignment;
    }
    return {};
}

literal search_unary_clause(const vector<clause>& formula) {
    for(const clause& c:formula) {
        if(c.size()==1) return c[0];
    }
    return 0;
}

void sat::simplify(int variable, bool variable_assignment) {
    for(int i=formula.size()-1;i>=0;i--) {
        clause& c = formula[i];
        for(int j=c.size()-1;j>=0;j--) {
            literal l = c[j];
            if(abs(l)==variable) {
                if((l>0 and variable_assignment) or (l<0 and !variable_assignment)) {
                    formula.erase(formula.begin()+i);
                    break;
                }
                if((l<0 and variable_assignment) or (l>0 and !variable_assignment)) {
                    c.erase(c.begin()+j);
                }
            }
        }
    }
    for(int i=0;i<variables.size();i++) {
        if(variables[i]==variable) variables.erase(variables.begin()+i);
    }
}

unordered_map<int,bool> sat::solve_dpll() {
    unordered_map<int,bool> assignment;
    assignment.reserve(variables.size());
    for(int variable:variables) assignment[variable]=false;
    return solve_dpll(assignment);
}

unordered_map<int,bool> sat::solve_dpll(unordered_map<int,bool>& assignment) {
    if(formula.empty()) return assignment;
    for(const clause& c:formula) if(c.size()==0) return {};

    literal l = search_unary_clause(formula);
    vector<clause> old_formula = formula;
    if(l!=0) {
        assignment[abs(l)] = (l>0 ? true : false);
        simplify(abs(l),assignment[abs(l)]);
        unordered_map<int,bool> new_assignment = solve_dpll(assignment);
        formula = old_formula;
        return new_assignment;
    }
    int variable = abs(formula[0][0]);
    assignment[variable]=true;
    simplify(variable,assignment[variable]);
    if(!solve_dpll(assignment).empty()) {
        formula = old_formula;
        return assignment;
    }
    formula = old_formula;
    assignment[variable]=false;
    simplify(variable,assignment[variable]);
    unordered_map<int,bool> new_assignment = solve_dpll(assignment);
    formula = old_formula;
    return new_assignment;
}