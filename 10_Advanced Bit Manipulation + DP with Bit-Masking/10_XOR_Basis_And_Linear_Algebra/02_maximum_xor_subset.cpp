/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 10.02 — MAXIMUM XOR SUBSET                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given array of n numbers, find maximum XOR of any subset.

ALGORITHM: Build XOR basis, then greedily maximize.
    Starting from result=0, for each basis vector from highest bit to lowest:
        result = max(result, result ^ basis[i])

PROOF: At each step, XOR with basis[i] either sets bit i (increasing result)
    or doesn't improve it. Greedy works because higher bits dominate.

TIME: O(n × 60) for construction + O(60) for query

PRACTICE PROBLEMS:
══════════════════
    SPOJ: XMAX
    Codeforces: 959F
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long maxXorSubset(vector<long long>& arr) {
    long long basis[60] = {};
    for (long long x : arr) {
        for (int i = 59; i >= 0; i--) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) { basis[i] = x; break; }
            x ^= basis[i];
        }
    }
    long long result = 0;
    for (int i = 59; i >= 0; i--)
        result = max(result, result ^ basis[i]);
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MAXIMUM XOR SUBSET                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<long long> arr = {5, 2, 1, 4, 3};
    cout << "  Array: {5,2,1,4,3}" << endl;
    cout << "  Max XOR subset: " << maxXorSubset(arr) << endl;
    assert(maxXorSubset(arr) == 7); // 5^2 or 4^3 or 4^2^1

    vector<long long> arr2 = {11, 6, 5, 18};
    cout << "  Array: {11,6,5,18}" << endl;
    cout << "  Max XOR subset: " << maxXorSubset(arr2) << endl;

    cout << "\n✅ Maximum XOR subset verified!" << endl;
    return 0;
}

