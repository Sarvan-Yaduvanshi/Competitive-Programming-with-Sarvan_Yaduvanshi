/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.13 — BUILT-IN BIT FUNCTIONS (GCC/G++)                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

COMPLETE LIST OF GCC BUILT-IN BIT FUNCTIONS:
═════════════════════════════════════════════

    Function                    Returns                     Time
    ─────────────────────────────────────────────────────────────
    __builtin_popcount(x)       Number of set bits (int)    O(1)
    __builtin_popcountll(x)     Same for long long          O(1)
    __builtin_clz(x)            Count Leading Zeros (int)   O(1)
    __builtin_clzll(x)          Same for long long          O(1)
    __builtin_ctz(x)            Count Trailing Zeros (int)  O(1)
    __builtin_ctzll(x)          Same for long long          O(1)
    __builtin_parity(x)         1 if odd # set bits (int)   O(1)
    __builtin_parityll(x)       Same for long long          O(1)
    __builtin_ffs(x)            Position of first set bit   O(1)
                                (1-indexed), 0 if x=0

MATHEMATICAL MEANINGS:
══════════════════════
    clz(x) = 31 - ⌊log₂(x)⌋     (for 32-bit int, x > 0)
    ctz(x) = position of lowest set bit = log₂(x & -x)
    ffs(x) = ctz(x) + 1  (1-indexed)

    Highest set bit position = 31 - clz(x)
    ⌊log₂(x)⌋ = 31 - clz(x)

WARNING: clz(0) and ctz(0) are UNDEFINED! Always check x > 0.

C++20: std::popcount, std::countl_zero, std::countr_zero in <bit>

PRACTICE PROBLEMS:
══════════════════
    LeetCode 191: Number of 1 Bits
    LeetCode 190: Reverse Bits
    Codeforces: various bit manipulation problems
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BUILT-IN BIT FUNCTIONS                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int tests[] = {1, 2, 7, 12, 16, 255, 1024};

    cout << "\n--- __builtin_popcount (count set bits) ---" << endl;
    for (int x : tests) {
        cout << "  popcount(" << x << ") = " << __builtin_popcount(x)
             << "  (" << bitset<11>(x) << ")" << endl;
    }

    cout << "\n--- __builtin_clz (count leading zeros, 32-bit) ---" << endl;
    for (int x : tests) {
        cout << "  clz(" << x << ") = " << __builtin_clz(x)
             << ", highest bit at position " << (31 - __builtin_clz(x))
             << ", ⌊log₂⌋ = " << (31 - __builtin_clz(x)) << endl;
    }

    cout << "\n--- __builtin_ctz (count trailing zeros) ---" << endl;
    for (int x : tests) {
        cout << "  ctz(" << x << ") = " << __builtin_ctz(x)
             << " (lowest set bit at position " << __builtin_ctz(x) << ")" << endl;
    }

    cout << "\n--- __builtin_parity ---" << endl;
    for (int x : tests) {
        cout << "  parity(" << x << ") = " << __builtin_parity(x)
             << " (" << ((__builtin_parity(x)) ? "odd" : "even") << " set bits)" << endl;
    }

    cout << "\n--- __builtin_ffs (first set bit, 1-indexed) ---" << endl;
    for (int x : tests) {
        cout << "  ffs(" << x << ") = " << __builtin_ffs(x) << endl;
    }
    cout << "  ffs(0) = " << __builtin_ffs(0) << " (special case: returns 0)" << endl;

    // Useful derived operations
    cout << "\n═══ DERIVED OPERATIONS ═══" << endl;
    int x = 12;
    cout << "  x = " << x << " (" << bitset<5>(x) << ")" << endl;
    cout << "  ⌊log₂(x)⌋ = " << (31 - __builtin_clz(x)) << endl;
    cout << "  Highest set bit = " << (1 << (31 - __builtin_clz(x))) << endl;
    cout << "  Next power of 2 ≥ x = " << (1 << (32 - __builtin_clz(x - 1))) << endl;

    // Long long versions
    cout << "\n--- Long Long Versions ---" << endl;
    long long big = (1LL << 40) + (1LL << 10);
    cout << "  n = 2^40 + 2^10 = " << big << endl;
    cout << "  popcountll = " << __builtin_popcountll(big) << endl;
    cout << "  clzll = " << __builtin_clzll(big) << endl;
    cout << "  ctzll = " << __builtin_ctzll(big) << endl;

    assert(__builtin_popcount(7) == 3);
    assert(__builtin_ctz(12) == 2);
    assert(31 - __builtin_clz(16) == 4);

    cout << "\n✅ All built-in bit functions demonstrated!" << endl;
    return 0;
}

