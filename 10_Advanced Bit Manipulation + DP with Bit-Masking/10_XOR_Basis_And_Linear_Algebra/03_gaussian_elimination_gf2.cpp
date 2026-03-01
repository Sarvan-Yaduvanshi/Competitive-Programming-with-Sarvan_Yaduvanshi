/*
╔══════════════════════════════════════════════════════════════════════════════╗
║  CHAPTER 10.03 — GAUSSIAN ELIMINATION IN GF(2), COUNT DISTINCT XORs,      ║
║                   LINEAR INDEPENDENCE IN BIT SPACE                          ║
║  Author: Sarvan Yaduvanshi                                                 ║
╚══════════════════════════════════════════════════════════════════════════════╝

GAUSSIAN ELIMINATION IN GF(2):
══════════════════════════════
    Same as normal Gaussian elimination, but + is XOR, × is AND.
    Pivoting: find row with 1 in the current column, XOR it into all other rows.
    Result: Reduced Row Echelon Form (RREF) where each basis vector has unique leading bit.

COUNT DISTINCT XOR VALUES:
══════════════════════════
    After building XOR basis of size k:
    Number of distinct XOR values = 2^k (including 0 = empty subset XOR).

LINEAR INDEPENDENCE:
════════════════════
    A set of numbers is linearly independent over GF(2) if no subset XORs to 0.
    Equivalently: XOR basis has same size as the set.

TIME: O(n × B) where B = number of bits
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct GF2Basis {
    long long basis[60] = {};
    int rank = 0;

    bool insert(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) { basis[i] = x; rank++; return true; }
            x ^= basis[i];
        }
        return false;
    }

    long long countDistinctXOR() { return 1LL << rank; }

    // RREF: make each basis vector have unique leading bit only
    void reduceToRREF() {
        for (int i = 59; i >= 0; i--) {
            if (!basis[i]) continue;
            for (int j = i + 1; j <= 59; j++) {
                if (basis[j] & (1LL << i)) basis[j] ^= basis[i];
            }
        }
    }
};

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   GF(2) LINEAR ALGEBRA                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    GF2Basis gb;
    vector<int> nums = {6, 3, 5, 7, 2};
    cout << "\n--- Building basis from {6,3,5,7,2} ---" << endl;
    for (int x : nums) {
        bool added = gb.insert(x);
        cout << "  " << x << ": " << (added ? "independent" : "dependent") << endl;
    }
    cout << "  Rank: " << gb.rank << endl;
    cout << "  Distinct XOR values: " << gb.countDistinctXOR() << endl;

    // Show basis
    cout << "\n--- Basis vectors ---" << endl;
    for (int i = 3; i >= 0; i--)
        if (gb.basis[i]) cout << "  bit " << i << ": " << gb.basis[i] << endl;

    // RREF
    gb.reduceToRREF();
    cout << "\n--- After RREF ---" << endl;
    for (int i = 3; i >= 0; i--)
        if (gb.basis[i]) cout << "  bit " << i << ": " << gb.basis[i] << endl;

    // Linear independence check
    cout << "\n--- Independence Check ---" << endl;
    GF2Basis check;
    vector<int> indep = {4, 2, 1}; // 100, 010, 001 — independent
    bool allIndep = true;
    for (int x : indep) allIndep &= check.insert(x);
    cout << "  {4,2,1}: " << (allIndep ? "independent" : "dependent") << endl;

    GF2Basis check2;
    vector<int> dep = {3, 5, 6}; // 011, 101, 110 — 3^5^6=0, dependent!
    bool allIndep2 = true;
    for (int x : dep) allIndep2 &= check2.insert(x);
    cout << "  {3,5,6}: " << (allIndep2 ? "independent" : "dependent") << endl;

    cout << "\n✅ GF(2) linear algebra verified!" << endl;
    return 0;
}

