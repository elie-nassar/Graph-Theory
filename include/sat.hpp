#pragma once
#include "literal.hpp"
#include <set>
#include <map>
#include <iostream>

using namespace std;

class sat {
    private:
        set<set<literal>> formula;
        int variable_count;

    public:
        sat(const set<set<literal>> &formula);
        sat(const set<set<literal>> &formula, int variable_count);

        int get_variable_count() const;
        map<int,bool> solve();
        map<int,bool> solve(map<int,bool> &m);
        friend ostream &operator<<(ostream &os, const sat& SAT);
};