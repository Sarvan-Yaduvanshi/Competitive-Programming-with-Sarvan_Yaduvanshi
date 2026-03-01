/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.04 — CHECK i-th BIT                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA:
════════
    Check if bit i is set (1) in number n:

    Method 1: (n >> i) & 1
        Shift bit i to position 0, then AND with 1.

    Method 2: n & (1 << i)
        Create mask with only bit i set, AND with n.
        Returns 0 (not set) or 2^i (set).

DRY RUN — Check bit 2 in n=13 (1101₂):
════════════════════════════════════════
    Method 1: (13 >> 2) & 1 = (0011) & 1 = 1  ✓ (bit 2 is set)
    Method 2: 13 & (1 << 2) = 1101 & 0100 = 0100 = 4 ≠ 0  ✓ (set)

DRY RUN — Check bit 1 in n=13 (1101₂):
════════════════════════════════════════
    Method 1: (13 >> 1) & 1 = (0110) & 1 = 0  ✓ (bit 1 is NOT set)
    Method 2: 13 & (1 << 1) = 1101 & 0010 = 0000 = 0  ✓ (not set)

BIT NUMBERING: 0-indexed from right (LSB = bit 0)
    Number: 1 1 0 1
    Bit:    3 2 1 0

TIME COMPLEXITY: O(1)

PRACTICE PROBLEMS:
══════════════════
    LeetCode 191: Number of 1 Bits
    LeetCode 342: Power of Four
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

// Method 1: (n >> i) & 1 — returns 0 or 1
bool checkBit_v1(int n, int i) {
    return (n >> i) & 1;
}

// Method 2: n & (1 << i) — returns 0 or 2^i
bool checkBit_v2(int n, int i) {
    return (n & (1 << i)) != 0;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   CHECK i-th BIT                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 13; // 1101₂
    cout << "\nn = " << n << " = " << bitset<4>(n) << "₂" << endl;
    cout << "Bit positions: [3][2][1][0]" << endl;

    cout << "\n--- Check each bit ---" << endl;
    for (int i = 3; i >= 0; i--) {
        cout << "  Bit " << i << ": " << checkBit_v1(n, i)
             << " (Method 1: (n>>" << i << ")&1 = " << ((n>>i)&1) << ")" << endl;
    }

    // Assertions
    assert(checkBit_v1(13, 0) == true);   // bit 0 of 1101 = 1
    assert(checkBit_v1(13, 1) == false);  // bit 1 of 1101 = 0
    assert(checkBit_v1(13, 2) == true);   // bit 2 of 1101 = 1
    assert(checkBit_v1(13, 3) == true);   // bit 3 of 1101 = 1
    assert(checkBit_v2(13, 0) == true);
    assert(checkBit_v2(13, 1) == false);

    // Practical: print all set bits
    cout << "\n--- All set bit positions in 42 (101010₂) ---" << endl;
    int x = 42;
    cout << "  " << x << " = " << bitset<8>(x) << "₂" << endl;
    cout << "  Set bits at positions: ";
    for (int i = 7; i >= 0; i--) {
        if (checkBit_v1(x, i)) cout << i << " ";
    }
    cout << endl;

    cout << "\n✅ Check i-th bit verified!" << endl;
    return 0;
}

