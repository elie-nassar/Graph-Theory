#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using literal = int;
using clause = vector<literal>;

class sat {
    private:
        vector<clause> clauses;
        vector<int> variables;

    public:
        sat(const vector<clause> &clauses);

        bool evaluate(const unordered_map<int,bool>& assignment) const;
        unordered_map<int,bool> solve_naive();

        friend ostream& operator<<(ostream& os, const sat& SAT);
};