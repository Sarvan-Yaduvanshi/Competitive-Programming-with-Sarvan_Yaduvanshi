/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.11 — REMOVE LOWEST SET BIT                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: n & (n - 1)
═════════════════════
    Removes (clears) the lowest (rightmost) set bit.

MATHEMATICAL PROOF:
    n   = ...a1b₀₀₀  (a = higher bits, 1 = lowest set bit, b₀₀₀ = trailing zeros)
    n-1 = ...a0b₁₁₁  (borrow flips lowest 1 and all trailing 0s)
    n & (n-1) = ...a0b₀₀₀ (lowest set bit cleared!)

DRY RUN — n = 12 (1100₂):
    n   = 1100
    n-1 = 1011
    n & (n-1) = 1000 = 8 (lowest set bit at position 2 removed) ✓

DRY RUN — n = 10 (1010₂):
    n   = 1010
    n-1 = 1001
    n & (n-1) = 1000 = 8 ✓

APPLICATIONS:
═════════════
    • Brian Kernighan's algorithm: count set bits
    • Check power of two: n & (n-1) == 0
    • Iterate through set bits efficiently

TIME: O(1)
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int removeLowestSetBit(int n) {
    return n & (n - 1);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   REMOVE LOWEST SET BIT: n & (n-1)             ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int tests[] = {12, 10, 7, 16, 15, 1};
    for (int n : tests) {
        int result = removeLowestSetBit(n);
        cout << "  n=" << n << " (" << bitset<5>(n) << ") → "
             << result << " (" << bitset<5>(result) << ")" << endl;
    }

    // Chain: remove all set bits one by one
    cout << "\n--- Remove set bits one by one from 13 ---" << endl;
    int n = 13;
    while (n) {
        cout << "  " << n << " (" << bitset<4>(n) << ") → ";
        n = n & (n - 1);
        cout << n << " (" << bitset<4>(n) << ")" << endl;
    }

    assert(removeLowestSetBit(12) == 8);
    assert(removeLowestSetBit(10) == 8);
    assert(removeLowestSetBit(1) == 0);
    assert(removeLowestSetBit(16) == 0); // power of 2

    cout << "\n✅ Remove lowest set bit verified!" << endl;
    return 0;
}

