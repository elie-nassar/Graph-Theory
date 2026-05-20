#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

using literal = int;
using clause = vector<literal>;

class sat {
    private:
        vector<clause> formula;
        vector<int> variables;

    public:
        sat(const vector<clause> &formula);
        sat(const vector<clause> &formula,const vector<int>& variables);

        bool evaluate(const unordered_map<int,bool>& assignment) const;
        void simplify(int variable, bool variable_assignment);

        unordered_map<int,bool> solve_exhaustive();
        unordered_map<int,bool> solve_dpll();
        unordered_map<int,bool> solve_dpll(unordered_map<int,bool>& assignment);

        friend ostream& operator<<(ostream& os, const sat& SAT);
};