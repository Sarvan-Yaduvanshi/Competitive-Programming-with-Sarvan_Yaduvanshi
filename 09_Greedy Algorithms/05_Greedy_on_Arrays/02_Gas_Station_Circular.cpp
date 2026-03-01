/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Gas Station — Circular Greedy
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM (LC 134): N gas stations in a circle.
 *  gas[i] = fuel at station i, cost[i] = fuel to travel from i to i+1.
 *  Find the starting station index to complete the circuit, or -1.
 *
 *  GREEDY INSIGHT:
 *  1. If total gas ≥ total cost, a solution ALWAYS exists.
 *  2. If running surplus goes negative at position i, start from i+1.
 *     (Because any start in [start..i] would also fail at or before i)
 *
 *  TIME: O(N), SPACE: O(1)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalSurplus = 0, currentSurplus = 0, start = 0;

    for (int i = 0; i < (int)gas.size(); i++) {
        int diff = gas[i] - cost[i];
        totalSurplus += diff;
        currentSurplus += diff;

        if (currentSurplus < 0) {
            // Can't start from 'start' to 'i', try i+1
            start = i + 1;
            currentSurplus = 0;
        }
    }

    return totalSurplus >= 0 ? start : -1;
}

int main() {
    vector<int> gas  = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};
    cout << "Start at: " << canCompleteCircuit(gas, cost) << endl; // 3

    vector<int> gas2  = {2, 3, 4};
    vector<int> cost2 = {3, 4, 3};
    cout << "Start at: " << canCompleteCircuit(gas2, cost2) << endl; // -1

    return 0;
}

