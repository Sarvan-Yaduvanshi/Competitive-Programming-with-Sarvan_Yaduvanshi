/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.16 — TWO'S COMPLEMENT REPRESENTATION                  ║
║           Bit Manipulation — Internal Representation                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
For an n-bit two's complement number with bits b_(n-1), ..., b_1, b_0:

    Value = -b_(n-1) × 2^(n-1) + Σ (i=0 to n-2) [ b_i × 2^i ]

The sign bit b_(n-1) has NEGATIVE weight -2^(n-1).

TO NEGATE A NUMBER (find -x from x):
═════════════════════════════════════
    Method 1: -x = ~x + 1  (invert all bits, add 1)
    Method 2: -x = (2ⁿ - x) mod 2ⁿ

PROOF THAT ~x + 1 = -x:
════════════════════════
    x + ~x = all 1s = 2ⁿ - 1  (every bit position has exactly one 1)
    Therefore: ~x = 2ⁿ - 1 - x
    So: ~x + 1 = 2ⁿ - x = -x (in two's complement mod 2ⁿ)

DRY RUN — REPRESENT -5 IN 8-BIT TWO'S COMPLEMENT:
═══════════════════════════════════════════════════
    Step 1: Write +5 in binary:    00000101
    Step 2: Invert all bits (~5):  11111010
    Step 3: Add 1:                 11111011

    Verify: -128 + 64+32+16+8+0+2+1 = -128+123 = -5 ✓

DRY RUN — WHAT IS 11110011₂ IN TWO'S COMPLEMENT?
═════════════════════════════════════════════════
    MSB = 1, so negative.
    Method: Invert and add 1:
    ~11110011 = 00001100
    + 1       = 00001101 = 13₁₀
    Answer: -13

    Verify: -128+64+32+16+0+0+2+1 = -128+115 = -13 ✓

SPECIAL CASES:
══════════════
    • 0: 00000000 → ~0+1 = 11111111+1 = 100000000 → overflow to 00000000 = 0 ✓
    • -128: 10000000 → ~10000000+1 = 01111111+1 = 10000000 = -128 (NO POSITIVE!)
    • This is why range is [-2^(n-1), 2^(n-1)-1] — asymmetric!
    • |INT_MIN| > INT_MAX (abs of INT_MIN overflows!)

KEY PROPERTY FOR BIT MANIPULATION:
═══════════════════════════════════
    -x = ~x + 1
    x & (-x) = lowest set bit of x  ← CRUCIAL for BIT tricks
    x & (x-1) = x with lowest set bit removed ← Brian Kernighan

PRACTICE PROBLEMS:
══════════════════
    LeetCode 191: Number of 1 Bits
    LeetCode 231: Power of Two
    LeetCode 1009: Complement of Base 10 Integer
*/

#include <iostream>
#include <bitset>
#include <climits>
#include <cassert>
using namespace std;

// Show two's complement step by step
void showTwosComplement(int n, int bits = 8) {
    cout << "Two's complement of " << n << " (" << bits << "-bit):" << endl;

    if (n >= 0) {
        cout << "  +" << n << " = " << bitset<8>(n) << endl;
        int neg = ~n + 1;  // -n using two's complement
        cout << "  ~" << n << " = " << bitset<8>(~n) << "  (invert)" << endl;
        cout << "  +1  = " << bitset<8>(neg) << "  = " << (signed char)neg << endl;
    } else {
        cout << "  Bits: " << bitset<8>(n) << endl;
        int pos = ~n + 1;  // find magnitude
        cout << "  ~bits: " << bitset<8>(~n) << endl;
        cout << "  +1:    " << bitset<8>(pos) << " = " << pos << endl;
        cout << "  So value = -" << pos << endl;
    }
}

// Verify two's complement formula
int twosComplementValue(unsigned char bits) {
    // Value = -b7 × 128 + b6×64 + ... + b0×1
    int result = 0;
    if (bits & 0x80) result -= 128;  // sign bit
    result += (bits & 0x7F);         // remaining 7 bits
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   TWO'S COMPLEMENT REPRESENTATION               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Demo 1: Negate positive numbers
    cout << "\n--- Negating Positive Numbers ---" << endl;
    showTwosComplement(5);
    cout << endl;
    showTwosComplement(13);
    cout << endl;
    showTwosComplement(1);

    // Demo 2: Decode negative numbers
    cout << "\n--- Decoding Negative Bit Patterns ---" << endl;
    showTwosComplement(-5);
    cout << endl;
    showTwosComplement(-13);

    // Demo 3: Key identity: -x = ~x + 1
    cout << "\n--- Key Identity: -x = ~x + 1 ---" << endl;
    for (int x : {1, 5, 13, 42, 100}) {
        int neg = ~x + 1;
        cout << "  x=" << x << ": ~x+1 = " << neg << ", -x = " << -x
             << (neg == -x ? " ✓" : " ✗") << endl;
    }

    // Demo 4: Lowest set bit using two's complement
    cout << "\n--- x & (-x) = Lowest Set Bit ---" << endl;
    for (int x : {12, 10, 7, 16, 6}) {
        cout << "  x=" << x << " (" << bitset<8>(x) << "): "
             << "x&(-x) = " << (x & -x) << " (" << bitset<8>(x & -x) << ")" << endl;
    }

    // Demo 5: Special case — INT_MIN
    cout << "\n--- Special Case: INT_MIN ---" << endl;
    cout << "  INT_MIN = " << INT_MIN << endl;
    cout << "  Bits: " << bitset<32>(INT_MIN) << endl;
    cout << "  -INT_MIN overflows! (no positive equivalent)" << endl;

    // Assertions
    assert((~5 + 1) == -5);
    assert((~13 + 1) == -13);
    assert((12 & -12) == 4);  // lowest set bit of 1100₂ is 100₂ = 4
    assert((10 & -10) == 2);  // lowest set bit of 1010₂ is 10₂ = 2

    cout << "\n✅ All two's complement concepts verified!" << endl;
    return 0;
}

