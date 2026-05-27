#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>

class sat {
    public:
        std::vector<std::vector<int>> formula;
        int variable_count;

    public:
        sat(const std::vector<std::vector<int>>& formula);

        bool evaluate(const std::vector<bool>& assignment) const;
        void simplify(int variable, bool variable_assignment);

        std::vector<bool> solve_exhaustive();
        std::vector<bool> solve_dpll();
        std::vector<bool> solve_dpll(std::vector<bool>& assignment);

        friend std::ostream& operator<<(std::ostream& os, const sat& SAT);
};