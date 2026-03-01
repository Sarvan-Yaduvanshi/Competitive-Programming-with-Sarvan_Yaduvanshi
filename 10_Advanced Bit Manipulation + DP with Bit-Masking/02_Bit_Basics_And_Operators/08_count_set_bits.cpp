/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.08 — COUNT SET BITS (Population Count / Popcount)     ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION:
═══════════
    popcount(n) = number of 1-bits in the binary representation of n
    Also called: Hamming weight, population count, sideways sum

METHODS:
════════
    1. Naive: Check each bit → O(32) or O(64)
    2. Brian Kernighan: n = n & (n-1) removes lowest set bit → O(popcount)
    3. Lookup table: Precompute for 8/16 bits → O(1)
    4. Built-in: __builtin_popcount(n) → O(1) (hardware instruction)

DRY RUN — Brian Kernighan on n=13 (1101₂):
═══════════════════════════════════════════
    Iteration 1: n=1101, n-1=1100, n&(n-1)=1100, count=1
    Iteration 2: n=1100, n-1=1011, n&(n-1)=1000, count=2
    Iteration 3: n=1000, n-1=0111, n&(n-1)=0000, count=3
    n=0, done. Answer: 3 ✓

WHY n & (n-1) REMOVES LOWEST SET BIT:
═════════════════════════════════════
    n   = ...1000  (lowest set bit at some position)
    n-1 = ...0111  (borrow flips lowest set bit and all zeros below)
    n & (n-1) = ...0000  (lowest set bit cleared!)

PRACTICE PROBLEMS:
══════════════════
    LeetCode 191: Number of 1 Bits
    LeetCode 338: Counting Bits
    LeetCode 461: Hamming Distance
    CSES: Bit Strings
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

// Method 1: Naive — check each bit
int countBits_naive(int n) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if ((n >> i) & 1) count++;
    }
    return count;
}

// Method 2: Brian Kernighan — O(number of set bits)
int countBits_kernighan(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);  // Remove lowest set bit
        count++;
    }
    return count;
}

// Method 3: Built-in
int countBits_builtin(int n) {
    return __builtin_popcount(n);
}

// Method 4: For long long
int countBits_builtin64(long long n) {
    return __builtin_popcountll(n);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   COUNT SET BITS (Popcount)                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Brian Kernighan Trace for 13 (1101₂) ---" << endl;
    int n = 13, count = 0;
    while (n) {
        cout << "  n=" << bitset<4>(n) << ", n-1=" << bitset<4>(n-1)
             << ", n&(n-1)=" << bitset<4>(n & (n-1)) << endl;
        n = n & (n - 1);
        count++;
    }
    cout << "  Set bits: " << count << endl;

    cout << "\n--- All Methods Comparison ---" << endl;
    int tests[] = {0, 1, 7, 13, 15, 255, 1023};
    for (int x : tests) {
        cout << "  " << x << " (" << bitset<10>(x) << "): "
             << "naive=" << countBits_naive(x)
             << " kernighan=" << countBits_kernighan(x)
             << " builtin=" << countBits_builtin(x) << endl;
    }

    // Assertions
    assert(countBits_builtin(0) == 0);
    assert(countBits_builtin(1) == 1);
    assert(countBits_builtin(7) == 3);
    assert(countBits_builtin(13) == 3);
    assert(countBits_builtin(255) == 8);

    cout << "\n✅ Count set bits verified!" << endl;
    return 0;
}

