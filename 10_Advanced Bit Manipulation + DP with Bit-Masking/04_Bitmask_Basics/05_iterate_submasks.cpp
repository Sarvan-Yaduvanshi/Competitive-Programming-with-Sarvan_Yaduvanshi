/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 04.05 — ITERATE SUBMASKS                                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given a mask m, iterate all submasks s ⊆ m (subsets of m's set bits).

ALGORITHM:
══════════
    for (int s = m; s > 0; s = (s - 1) & m)
        // process submask s
    // don't forget to process s = 0 (empty set) if needed

MATHEMATICAL PROOF:
═══════════════════
    s - 1 flips the lowest set bit and all bits below it.
    (s - 1) & m ensures we stay within the bits of m.
    This generates all submasks of m in decreasing order.

DRY RUN — m = 1101₂ (13):
══════════════════════════
    s = 1101 (13)
    s = (1100) & 1101 = 1100 (12)
    s = (1011) & 1101 = 1001 (9)
    s = (1000) & 1101 = 1000 (8)
    s = (0111) & 1101 = 0101 (5)
    s = (0100) & 1101 = 0100 (4)
    s = (0011) & 1101 = 0001 (1)
    s = (0000) & 1101 = 0000 (0) → loop ends

    Submasks: {13, 12, 9, 8, 5, 4, 1, 0} = 2³ = 8 submasks ✓
    (m has 3 set bits, so 2³ submasks)

TOTAL COMPLEXITY OVER ALL MASKS:
════════════════════════════════
    Σ (over all masks m) [number of submasks of m] = 3ⁿ
    Because each element has 3 choices: not in m, in m but not in s, in both m and s.

    This O(3ⁿ) is CRUCIAL for bitmask DP over submasks!

PRACTICE PROBLEMS:
══════════════════
    Codeforces: SOS DP problems
    CSES: problems involving subset iteration
*/
#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

void printSubset(int mask, int n) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            if (!first) cout << ",";
            cout << i;
            first = false;
        }
    }
    cout << "}";
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ITERATE SUBMASKS of a given mask              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int m = 0b1101; // = 13, set = {0,2,3}
    int n = 4;
    cout << "\nMask m = " << m << " (" << bitset<4>(m) << ") = ";
    printSubset(m, n);
    cout << endl;

    cout << "\n--- All submasks of m ---" << endl;
    int count = 0;
    for (int s = m; ; s = (s - 1) & m) {
        cout << "  s=" << bitset<4>(s) << " (" << s << ") = ";
        printSubset(s, n);
        cout << endl;
        count++;
        if (s == 0) break;
    }
    cout << "\nTotal submasks: " << count
         << " (= 2^" << __builtin_popcount(m) << " = " << (1 << __builtin_popcount(m)) << ")" << endl;
    assert(count == (1 << __builtin_popcount(m)));

    // Verify 3^n complexity
    cout << "\n--- Total submask iterations over ALL masks (n=3) ---" << endl;
    int totalIterations = 0;
    int nn = 3;
    for (int mask = 0; mask < (1 << nn); mask++) {
        int cnt = 0;
        for (int s = mask; ; s = (s - 1) & mask) {
            cnt++;
            if (s == 0) break;
        }
        totalIterations += cnt;
    }
    cout << "  Total iterations: " << totalIterations << " (3^" << nn << " = " << (3*3*3) << ")" << endl;
    assert(totalIterations == 27); // 3^3

    cout << "\n✅ Submask iteration verified!" << endl;
    return 0;
}

