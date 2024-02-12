#include "../include/tdoku.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

const int option = 4;
// X means "force empty", number means force that number,
// . means unconstrained.
const std::unordered_map<int, std::string> constraintsOptions = {
    // brick by brick
    {4, "....XX........X............XXX.....................XXX............X........XX...."}

};
const std::unordered_map<int, std::string> solutionConstraintsOptions = {
    //   835612974249873165167594328451926783672138549983745612598261437714389256326457891
    //   974512386285673941613984527451726839826139754397845612138297465549361278762458193
    {4, "....12........3............451.....................612............3........45...."}
};
const std::unordered_map<int, std::string> patternOptions {
    {4, std::string(81, '.')}
};


struct Generator {
    string constraints = constraintsOptions.at(option);
    string pattern = patternOptions.at(option);
    string solutionConstraints = solutionConstraintsOptions.at(option);

    bool HasUniqueSolution(const char *puzzle) {
        char solution[81];
        size_t guesses = 0;
        return TdokuSolverDpllTriadSimd(puzzle, 2, 0, solution, &guesses) == 1;
    }

    double Evaluate(const char *puzzle) {
        char eval_puzzle[729];
        strncpy(eval_puzzle, puzzle, 729);

        double loss = 0.0;
        if (HasUniqueSolution(eval_puzzle)) {
            // Try to stay close to `constraints`.
            double num_changes = 0.;
            for (int i = 0; i < 81; i++) {
                if (pattern[i] != eval_puzzle[i]) {
                    num_changes += 1.0;
                }
            }
            loss += num_changes;
        } else {
            loss = numeric_limits<double>::max();
        }
        return loss;
    }

    void Generate() {
        char puzzle[729];

        size_t size = 81;
        for (uint64_t i = 0; i < 20000; i++) {
            // Always use the same puzzle
            memcpy(puzzle, pattern.c_str(), size);
            if (size == 81) puzzle[81] = '\0';

            if (!TdokuConstrain(false, puzzle, constraints, solutionConstraints)) {
                continue;
            }
            // Minimize
            TdokuMinimize(false, false, puzzle, constraints);
            double loss = Evaluate(puzzle);
            if (loss < 22) cout << puzzle << " " << loss << endl;
        }
    }
};

int main(int argc, char **argv) {
    Generator generator;
    generator.Generate();
}
