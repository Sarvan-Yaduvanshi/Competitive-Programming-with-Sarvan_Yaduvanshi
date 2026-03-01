/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.12 — EXTRACT LOWEST SET BIT                           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA: n & (-n)
═════════════════
    Isolates (extracts) the lowest set bit. Result is a power of 2.

MATHEMATICAL PROOF (Two's complement):
    -n = ~n + 1
    n   = ...a1₀₀₀  (a = higher bits, 1 = lowest set, trailing zeros)
    ~n  = ...ā0₁₁₁  (all bits flipped)
    -n  = ...ā1₀₀₀  (add 1: flips trailing 1s back, sets the 0 to 1)
    n & (-n) = ...01₀₀₀ = just the lowest set bit!

DRY RUN — n = 12 (1100₂):
    n  = 1100
    -n = 0100 (two's complement of 12 in 4-bit context)
    n & (-n) = 0100 = 4 (lowest set bit is at position 2, value 2²=4) ✓

DRY RUN — n = 10 (1010₂):
    n  = 1010
    -n = 0110
    n & (-n) = 0010 = 2 ✓

APPLICATIONS:
═════════════
    • Fenwick tree (Binary Indexed Tree): lowbit = i & (-i)
    • Iterate through set bits
    • Find position of lowest set bit: __builtin_ctz(n) = log₂(n & -n)

TIME: O(1)
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int extractLowestSetBit(int n) {
    return n & (-n);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   EXTRACT LOWEST SET BIT: n & (-n)             ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int tests[] = {12, 10, 7, 16, 15, 1, 6};
    for (int n : tests) {
        int lsb = extractLowestSetBit(n);
        cout << "  n=" << n << " (" << bitset<5>(n) << "): lowest set bit = "
             << lsb << " (" << bitset<5>(lsb) << ") at position "
             << __builtin_ctz(n) << endl;
    }

    // Fenwick Tree lowbit demonstration
    cout << "\n--- Fenwick Tree: lowbit(i) = i & (-i) ---" << endl;
    for (int i = 1; i <= 16; i++) {
        cout << "  i=" << i << ": lowbit=" << (i & -i) << endl;
    }

    assert(extractLowestSetBit(12) == 4);
    assert(extractLowestSetBit(10) == 2);
    assert(extractLowestSetBit(16) == 16);
    assert(extractLowestSetBit(7) == 1);

    cout << "\n✅ Extract lowest set bit verified!" << endl;
    return 0;
}

