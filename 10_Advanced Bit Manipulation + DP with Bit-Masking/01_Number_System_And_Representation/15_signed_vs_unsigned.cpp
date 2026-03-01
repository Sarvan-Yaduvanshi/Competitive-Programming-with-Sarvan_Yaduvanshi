/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.15 — SIGNED vs UNSIGNED INTEGERS                      ║
║           Bit Manipulation — Internal Representation                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
For an n-bit integer:

UNSIGNED:
    • All n bits represent magnitude
    • Range: [0, 2ⁿ - 1]
    • For 32-bit: [0, 4,294,967,295] = [0, 2³² - 1]
    • Value = Σ (i=0 to n-1) [ b_i × 2^i ]

SIGNED (Two's Complement — standard in modern hardware):
    • MSB (bit n-1) is the sign bit: 0 = positive, 1 = negative
    • Range: [-2^(n-1), 2^(n-1) - 1]
    • For 32-bit: [-2,147,483,648, 2,147,483,647]
    • Value = -b_(n-1) × 2^(n-1) + Σ (i=0 to n-2) [ b_i × 2^i ]

EXAMPLE (8-bit):
════════════════
    Unsigned:               Signed (Two's Complement):
    00000000 = 0            00000000 =  0
    00000001 = 1            00000001 =  1
    01111111 = 127          01111111 = +127 (max positive)
    10000000 = 128          10000000 = -128 (min negative)
    10000001 = 129          10000001 = -127
    11111111 = 255          11111111 = -1

DRY RUN — SAME BITS, DIFFERENT INTERPRETATION:
═══════════════════════════════════════════════
    Bits: 11111111 (8-bit)

    As unsigned:  1×128+1×64+1×32+1×16+1×8+1×4+1×2+1×1 = 255
    As signed:   -1×128+1×64+1×32+1×16+1×8+1×4+1×2+1×1 = -128+127 = -1

    Bits: 10000000 (8-bit)
    As unsigned: 128
    As signed:  -128

CRITICAL INSIGHT FOR CP:
════════════════════════
    • int = 32-bit signed → max ≈ 2.1×10⁹
    • unsigned int = 32-bit unsigned → max ≈ 4.3×10⁹
    • long long = 64-bit signed → max ≈ 9.2×10¹⁸
    • Comparing signed and unsigned is DANGEROUS (implicit conversion!)
    • (int)(-1) < (unsigned)(0) → FALSE! (-1 becomes 4294967295)

PRACTICE PROBLEMS:
══════════════════
    LeetCode 7: Reverse Integer (overflow handling)
    LeetCode 371: Sum of Two Integers
*/

#include <iostream>
#include <climits>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SIGNED vs UNSIGNED INTEGERS                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // 8-bit demonstration
    cout << "\n--- 8-bit Signed vs Unsigned ---" << endl;
    unsigned char uc = 255;
    signed char sc = -1;
    cout << "Bits: 11111111" << endl;
    cout << "  As unsigned char: " << (int)uc << endl;  // 255
    cout << "  As signed char:   " << (int)sc << endl;  // -1

    uc = 128;
    sc = -128;
    cout << "Bits: 10000000" << endl;
    cout << "  As unsigned char: " << (int)uc << endl;  // 128
    cout << "  As signed char:   " << (int)sc << endl;  // -128

    // 32-bit ranges
    cout << "\n--- 32-bit Ranges ---" << endl;
    cout << "int min:          " << INT_MIN << endl;
    cout << "int max:          " << INT_MAX << endl;
    cout << "unsigned int max: " << UINT_MAX << endl;

    // 64-bit ranges
    cout << "\n--- 64-bit Ranges ---" << endl;
    cout << "long long min:          " << LLONG_MIN << endl;
    cout << "long long max:          " << LLONG_MAX << endl;
    cout << "unsigned long long max: " << ULLONG_MAX << endl;

    // Dangerous comparison
    cout << "\n--- DANGER: Signed vs Unsigned Comparison ---" << endl;
    int a = -1;
    unsigned int b = 0;
    cout << "int a = -1, unsigned b = 0" << endl;
    cout << "(a < b) = " << (a < b) << " ← WRONG! Should be true but is "
         << ((a < b) ? "true" : "false (BUG!)") << endl;
    cout << "Because -1 is interpreted as " << (unsigned int)a << " in unsigned" << endl;

    // Bitset visualization
    cout << "\n--- Bit Patterns ---" << endl;
    int x = -1;
    cout << "-1 in 32 bits: " << bitset<32>(x) << endl;
    x = INT_MIN;
    cout << "INT_MIN:       " << bitset<32>(x) << endl;
    x = INT_MAX;
    cout << "INT_MAX:       " << bitset<32>(x) << endl;

    cout << "\n✅ Signed vs Unsigned concepts demonstrated!" << endl;
    return 0;
}

