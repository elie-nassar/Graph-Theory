#include "sat.hpp"
#include <unordered_map>

sat::sat(const std::vector<std::vector<int>> &formula) : formula(formula) {
    std::unordered_set<int> variables;
    for(const auto& clause:formula) {
        for(const auto& lit:clause) variables.insert(abs(lit));
    }
    variable_count = variables.size();
}

bool sat::evaluate(const std::vector<bool>& assignment) const {
    for(const auto& clause:formula) {
        bool clause_sat = false;
        for(const auto& lit:clause) {
            if(abs(lit)>assignment.size()) return false;
            if((lit>0 and assignment[lit-1]) || (lit<0 and !assignment[-lit-1])) {
                clause_sat=true;
                break;
            }
        };
        if(!clause_sat) return false; 
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const sat& SAT) {
    for(int i=0;i<(int)SAT.formula.size();i++) {
        std::vector<int> c = SAT.formula[i];
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

std::vector<bool> sat::solve_exhaustive() {
    std::vector<bool> assignment(variable_count);
    for (int mask=0;mask<(1 << variable_count);mask++) {
        for(int i=0;i<variable_count;i++) {
            assignment[i] = (mask >> i) & 1;
        }
        if(evaluate(assignment)) return assignment;
    }
    return {};
}

int search_next_literal(const std::vector<std::vector<int>>& formula) {
    std::unordered_map<int,int> pol;
    for(const auto& clause:formula) {
        if(clause.size()==1) return clause[0];
        for(const auto& lit:clause) {
            if(!pol.contains(lit)) pol[abs(lit)]= lit;
            else if((pol[abs(lit)]<0 and lit>0) or (pol[abs(lit)]>0 and lit<0)) pol[abs(lit)] = 0;
        }
    }
    for(const auto& [id,lit]:pol) if(lit!=0) return lit;
    return 0;
}

void sat::simplify(int variable, bool variable_assignment) {
    for(int i=formula.size()-1;i>=0;i--) {
        std::vector<int>& clause = formula[i];
        for(int j=clause.size()-1;j>=0;j--) {
            int l = clause[j];
            if(abs(l)==variable) {
                if((l>0 and variable_assignment) or (l<0 and !variable_assignment)) {
                    formula.erase(formula.begin()+i);
                    break;
                }
                if((l<0 and variable_assignment) or (l>0 and !variable_assignment)) {
                    clause.erase(clause.begin()+j);
                }
            }
        }
    }
    variable_count--;
}

std::vector<bool> sat::solve_dpll() {
    std::vector<bool> assignment(variable_count,false);
    return solve_dpll(assignment);
}

std::vector<bool> sat::solve_dpll(std::vector<bool>& assignment) {
    if(formula.empty()) return assignment;
    for(const auto& clause:formula) if(clause.size()==0) return {};

    int lit = search_next_literal(formula);
    std::vector<std::vector<int>> old_formula = formula;
    if(lit!=0) {
        assignment[abs(lit)-1] = (lit>0 ? true : false);
        simplify(abs(lit),assignment[abs(lit)-1]);
        if(solve_dpll(assignment).empty()) {
            formula = old_formula;
            return {};
        }else {
            formula=old_formula;
            return assignment;
        }
    }
    int variable = abs(formula[0][0]);
    assignment[variable-1]=true;
    simplify(variable,assignment[variable-1]);
    if(!solve_dpll(assignment).empty()) {
        formula = old_formula;
        return assignment;
    }
    formula = old_formula;
    assignment[variable-1]=false;
    simplify(variable,assignment[variable-1]);
    if(solve_dpll(assignment).empty()) {
        formula = old_formula;
        return {};
    }else {
        formula=old_formula;
        return assignment;
    }
}