/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05.02 — SUBMASK ITERATION (Detailed)                     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

See 04.05 for basics. This file covers advanced applications.

KEY FORMULA:
    for (int s = m; s > 0; s = (s-1) & m)  // iterates all non-empty submasks

TOTAL COMPLEXITY PROOF (3ⁿ):
═════════════════════════════
    For each of n positions, there are 3 states:
        (0 in mask, 0 in submask), (1 in mask, 0 in submask), (1 in mask, 1 in submask)
    So Σ_{mask} Σ_{submask⊆mask} 1 = 3ⁿ

APPLICATION: Split mask into two complementary submasks.
    For each mask, try all ways to split: (s, mask ^ s) where s ⊆ mask.
*/
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SUBMASK ITERATION — ADVANCED                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Split mask into two complementary halves
    int mask = 0b1110; // {1,2,3}
    cout << "  Split mask " << bitset<4>(mask) << " into (A, B) where A∪B=mask, A∩B=∅:" << endl;

    for (int a = mask; a > 0; a = (a - 1) & mask) {
        int b = mask ^ a;
        if (a >= b) { // avoid duplicates
            cout << "    A=" << bitset<4>(a) << ", B=" << bitset<4>(b) << endl;
        }
    }
    // Also include (0, mask)
    cout << "    A=" << bitset<4>(0) << ", B=" << bitset<4>(mask) << endl;

    // Count submasks for each mask in small universe
    cout << "\n--- Submask count per mask (n=3) ---" << endl;
    int n = 3;
    int total = 0;
    for (int m = 0; m < (1 << n); m++) {
        int cnt = 0;
        for (int s = m; ; s = (s-1) & m) { cnt++; if (s == 0) break; }
        cout << "  mask=" << bitset<3>(m) << ": " << cnt << " submasks" << endl;
        total += cnt;
    }
    cout << "  Total: " << total << " (= 3^" << n << " = " << (3*3*3) << ")" << endl;

    cout << "\n✅ Submask iteration advanced demonstrated!" << endl;
    return 0;
}

