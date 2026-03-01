/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.10 — BRIAN KERNIGHAN'S ALGORITHM                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM:
══════════
    Count set bits by repeatedly removing the lowest set bit.
    while (n != 0):
        n = n & (n - 1)    // remove lowest set bit
        count++

MATHEMATICAL INSIGHT:
═════════════════════
    n & (n-1) clears the lowest set bit.
    Each iteration removes exactly one set bit.
    Number of iterations = number of set bits = popcount(n).

    Time: O(popcount(n)) — better than O(32) when few bits are set!

DRY RUN — n = 52 (110100₂):
════════════════════════════
    Iteration 1: n=110100, n-1=110011, n&(n-1)=110000, count=1
    Iteration 2: n=110000, n-1=101111, n&(n-1)=100000, count=2
    Iteration 3: n=100000, n-1=011111, n&(n-1)=000000, count=3
    Answer: 3 set bits ✓

APPLICATIONS:
═════════════
    • Count set bits efficiently
    • Check power of 2: n & (n-1) == 0
    • Iterate through set bits (combine with extracting lowest set bit)
    • Calculate Hamming distance: popcount(a ^ b)

PRACTICE PROBLEMS:
══════════════════
    LeetCode 191: Number of 1 Bits
    LeetCode 338: Counting Bits
    LeetCode 461: Hamming Distance
*/
#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int brianKernighan(int n) {
    int count = 0;
    cout << "  Trace for n=" << n << " (" << bitset<8>(n) << "):" << endl;
    while (n) {
        cout << "    n=" << bitset<8>(n) << " → n&(n-1)=" << bitset<8>(n & (n-1)) << endl;
        n = n & (n - 1);
        count++;
    }
    return count;
}

// Iterate through set bit positions
void iterateSetBits(int n) {
    cout << "  Set bit positions of " << n << " (" << bitset<8>(n) << "): ";
    while (n) {
        int lowest = n & (-n);            // isolate lowest set bit
        int pos = __builtin_ctz(lowest);  // position of that bit
        cout << pos << " ";
        n = n & (n - 1);                 // remove it
    }
    cout << endl;
}

// Hamming distance = popcount(a ^ b)
int hammingDistance(int a, int b) {
    int x = a ^ b;
    int count = 0;
    while (x) { x &= (x-1); count++; }
    return count;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BRIAN KERNIGHAN'S ALGORITHM                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Count Set Bits ---" << endl;
    int c1 = brianKernighan(52);
    cout << "  Result: " << c1 << " set bits" << endl;
    assert(c1 == 3);

    cout << endl;
    int c2 = brianKernighan(255);
    cout << "  Result: " << c2 << " set bits" << endl;
    assert(c2 == 8);

    cout << "\n--- Iterate Set Bit Positions ---" << endl;
    iterateSetBits(52);   // positions: 2, 4, 5
    iterateSetBits(13);   // positions: 0, 2, 3

    cout << "\n--- Hamming Distance ---" << endl;
    cout << "  Distance(1, 4) = " << hammingDistance(1, 4) << endl; // 001 vs 100 → 2
    cout << "  Distance(3, 1) = " << hammingDistance(3, 1) << endl; // 11 vs 01 → 1
    assert(hammingDistance(1, 4) == 2);
    assert(hammingDistance(3, 1) == 1);

    cout << "\n✅ Brian Kernighan's algorithm verified!" << endl;
    return 0;
}

