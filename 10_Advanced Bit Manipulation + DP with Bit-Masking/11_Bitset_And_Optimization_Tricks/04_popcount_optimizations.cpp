/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 11.04 — POPCOUNT OPTIMIZATIONS                           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

POPCOUNT METHODS (from slow to fast):
═════════════════════════════════════

1. NAIVE — O(32):
    while(n) { count += n&1; n >>= 1; }

2. BRIAN KERNIGHAN — O(popcount):
    while(n) { n &= n-1; count++; }

3. LOOKUP TABLE — O(1) amortized:
    Precompute popcount for all 16-bit values (65536 entries).
    Split 32-bit into two 16-bit halves, lookup each.

4. PARALLEL BIT COUNTING (Hamming weight) — O(1):
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    return (x * 0x01010101) >> 24;

5. HARDWARE — O(1):
    __builtin_popcount(x) — uses POPCNT instruction if available.
    Compile with -mpopcnt or -march=native.

6. BITSET — O(N/64):
    bitset<N> b; b.count();

WHICH TO USE IN CP:
═══════════════════
    Always use __builtin_popcount(x) or __builtin_popcountll(x).
    If you need popcount for all numbers 0..n, use DP:
        pc[i] = pc[i >> 1] + (i & 1)

PRACTICE PROBLEMS:
══════════════════
    LeetCode 338: Counting Bits
    LeetCode 191: Number of 1 Bits
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include <cassert>
using namespace std;

// Method 1: Naive
int popcount_naive(unsigned int n) {
    int c = 0;
    while (n) { c += n & 1; n >>= 1; }
    return c;
}

// Method 2: Brian Kernighan
int popcount_kernighan(unsigned int n) {
    int c = 0;
    while (n) { n &= n - 1; c++; }
    return c;
}

// Method 3: Lookup table
int popcount_table[65536];
void buildTable() {
    popcount_table[0] = 0;
    for (int i = 1; i < 65536; i++)
        popcount_table[i] = popcount_table[i >> 1] + (i & 1);
}
int popcount_lookup(unsigned int n) {
    return popcount_table[n & 0xFFFF] + popcount_table[n >> 16];
}

// Method 4: Parallel (Hamming weight formula)
int popcount_parallel(unsigned int x) {
    x = x - ((x >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = (x + (x >> 4)) & 0x0F0F0F0Fu;
    return (x * 0x01010101u) >> 24;
}

// Method 5: DP for all numbers 0..n
vector<int> countBitsDP(int n) {
    vector<int> pc(n + 1);
    pc[0] = 0;
    for (int i = 1; i <= n; i++)
        pc[i] = pc[i >> 1] + (i & 1);
    return pc;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   POPCOUNT OPTIMIZATIONS                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    buildTable();

    // Verify all methods agree
    cout << "\n--- All Methods Agree ---" << endl;
    for (unsigned int x : {0u, 1u, 7u, 13u, 255u, 1023u, 0xFFFFFFFFu}) {
        int a = popcount_naive(x);
        int b = popcount_kernighan(x);
        int c = popcount_lookup(x);
        int d = popcount_parallel(x);
        int e = __builtin_popcount(x);
        cout << "  " << x << ": naive=" << a << " kern=" << b << " lookup=" << c
             << " parallel=" << d << " builtin=" << e << endl;
        assert(a == b && b == c && c == d && d == e);
    }

    // DP for counting bits 0..15 (LeetCode 338)
    cout << "\n--- DP Popcount for 0..15 ---" << endl;
    auto pc = countBitsDP(15);
    for (int i = 0; i <= 15; i++) {
        cout << "  pc[" << i << "] = " << pc[i] << endl;
        assert(pc[i] == __builtin_popcount(i));
    }

    // Parallel popcount explanation
    cout << "\n--- Parallel Popcount Math ---" << endl;
    unsigned int x = 0b11011010;
    cout << "  x = " << bitset<8>(x) << endl;

    unsigned int step1 = x - ((x >> 1) & 0x55);
    cout << "  Step 1 (pair sums): " << bitset<8>(step1) << endl;
    // 11→10, 01→01, 10→01, 10→01 → 10 01 01 01

    unsigned int step2 = (step1 & 0x33) + ((step1 >> 2) & 0x33);
    cout << "  Step 2 (nibble sums): " << bitset<8>(step2) << endl;
    // 0011 0010 → groups of 4

    unsigned int step3 = (step2 + (step2 >> 4)) & 0x0F;
    cout << "  Step 3 (byte sum): " << bitset<8>(step3) << " = " << step3 << endl;
    cout << "  Popcount = " << step3 << " ✓ (builtin: " << __builtin_popcount(x) << ")" << endl;

    cout << "\n✅ Popcount optimizations verified!" << endl;
    return 0;
}

