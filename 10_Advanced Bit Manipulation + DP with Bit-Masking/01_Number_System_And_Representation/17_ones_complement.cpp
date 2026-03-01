/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.17 — ONE'S COMPLEMENT REPRESENTATION                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION:
═══════════
One's complement of x = ~x (invert all bits).
To negate: -x = ~x  (just flip all bits).

For n-bit one's complement:
    Positive: Same as unsigned (MSB=0)
    Negative: Invert all bits of the positive value
    Range: [-(2^(n-1) - 1), 2^(n-1) - 1]

PROBLEM: Two representations of zero!
    +0 = 00000000
    -0 = 11111111

DRY RUN (8-bit):
═════════════════
    +5  = 00000101
    -5  = ~(00000101) = 11111010   (one's complement)

    Compare with two's complement:
    -5  = 11111010 + 1 = 11111011  (two's complement)

    One's complement: 11111010 = -(01111111 - 01111010) = -(01111010 XOR 01111111) = -5
    Two's complement: 11111011 = -128 + 123 = -5

WHY IT'S OBSOLETE:
══════════════════
    1. Two zeros (+0 and -0) complicate comparisons
    2. Addition requires end-around carry
    3. Two's complement is simpler in hardware
    4. Modern CPUs all use two's complement

ADDITION IN ONE'S COMPLEMENT:
═════════════════════════════
    3 + (-1) in 8-bit one's complement:
      00000011  (+3)
    + 11111110  (-1 in one's complement)
    = 100000001 → carry out! Add carry back: 00000001 + 1 = 00000010 = 2 ✓
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ONE'S COMPLEMENT REPRESENTATION               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- One's Complement = Bitwise NOT ---" << endl;
    for (int x : {5, 13, 0, 127}) {
        unsigned char oc = ~((unsigned char)x);
        cout << "  +" << x << " = " << bitset<8>(x)
             << " → one's complement = " << bitset<8>(oc) << endl;
    }

    cout << "\n--- Two Zeros Problem ---" << endl;
    cout << "  +0 = " << bitset<8>(0) << endl;
    cout << "  -0 = " << bitset<8>(0xFF) << " (all 1s)" << endl;

    cout << "\n--- Comparison: One's vs Two's Complement ---" << endl;
    for (int x : {1, 5, 13, 42}) {
        unsigned char ones = ~((unsigned char)x);
        unsigned char twos = ones + 1;
        cout << "  -" << x << ": one's = " << bitset<8>(ones)
             << ", two's = " << bitset<8>(twos) << endl;
    }

    cout << "\n✅ One's complement concept demonstrated!" << endl;
    return 0;
}

