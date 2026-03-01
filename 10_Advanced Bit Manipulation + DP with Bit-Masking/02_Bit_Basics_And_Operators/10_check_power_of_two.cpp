/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.10 — CHECK POWER OF TWO                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL INSIGHT:
═════════════════════
    Powers of 2 have exactly ONE bit set: 2^k = 100...0₂ (k zeros)

    2⁰ = 1    = 00000001
    2¹ = 2    = 00000010
    2² = 4    = 00000100
    2³ = 8    = 00001000

FORMULA: n > 0 && (n & (n-1)) == 0
═══════════════════════════════════
    If n is a power of 2: n = 100...0
    Then n-1 = 011...1  (all bits below the single set bit become 1)
    n & (n-1) = 0

DRY RUN:
    n=8:  1000 & 0111 = 0000 → power of 2 ✓
    n=6:  0110 & 0101 = 0100 ≠ 0 → NOT power of 2 ✓
    n=1:  0001 & 0000 = 0000 → power of 2 ✓ (2⁰ = 1)

ALTERNATIVE: popcount(n) == 1

PRACTICE PROBLEMS:
══════════════════
    LeetCode 231: Power of Two
    LeetCode 342: Power of Four
    LeetCode 326: Power of Three
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

bool isPowerOfTwo_popcount(int n) {
    return n > 0 && __builtin_popcount(n) == 1;
}

// Bonus: Power of 4
bool isPowerOfFour(int n) {
    // Power of 2 AND the single bit is at an even position
    // 0x55555555 = 01010101... (bits at even positions)
    return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   CHECK POWER OF TWO                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    for (int n = 0; n <= 16; n++) {
        cout << "  " << n << " (" << bitset<5>(n) << "): "
             << (isPowerOfTwo(n) ? "YES ✓" : "no") << endl;
    }

    cout << "\n--- Large Powers of 2 ---" << endl;
    for (int k = 0; k <= 30; k += 5) {
        int val = 1 << k;
        cout << "  2^" << k << " = " << val << ": "
             << (isPowerOfTwo(val) ? "YES" : "NO") << endl;
    }

    assert(isPowerOfTwo(1) == true);
    assert(isPowerOfTwo(2) == true);
    assert(isPowerOfTwo(4) == true);
    assert(isPowerOfTwo(6) == false);
    assert(isPowerOfTwo(0) == false);
    assert(isPowerOfTwo(-4) == false);

    cout << "\n✅ Power of two check verified!" << endl;
    return 0;
}

