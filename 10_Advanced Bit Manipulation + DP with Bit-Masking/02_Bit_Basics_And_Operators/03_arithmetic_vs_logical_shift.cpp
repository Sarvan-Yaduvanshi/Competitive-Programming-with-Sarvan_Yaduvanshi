/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.03 — ARITHMETIC vs LOGICAL SHIFT                        ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

LOGICAL RIGHT SHIFT:
════════════════════
    • Always fills vacated bits with 0
    • Treats number as UNSIGNED bit pattern
    • Java: >>> operator. C++ unsigned types: >>

ARITHMETIC RIGHT SHIFT:
═══════════════════════
    • Fills vacated bits with the SIGN BIT (MSB)
    • Preserves the sign of the number
    • Equivalent to ⌊x / 2^k⌋ for negative numbers
    • C++: >> on signed types (implementation-defined but usually arithmetic)

DRY RUN — -8 >> 1 (8-bit):
═══════════════════════════
    -8 = 11111000₂

    Logical:     0|1111100₂ = 124  (fills with 0, changes sign!)
    Arithmetic:  1|1111100₂ = -4   (fills with 1, preserves sign)

    Arithmetic is correct: ⌊-8/2⌋ = -4 ✓

LEFT SHIFT:
═══════════
    Always the same for both: fill with 0s from right.
    Logical left shift = Arithmetic left shift.

IN C++:
═══════
    • Signed >> is IMPLEMENTATION-DEFINED (but arithmetic on all modern CPUs)
    • Unsigned >> is ALWAYS logical
    • To guarantee logical shift: cast to unsigned first
*/

#include <iostream>
#include <bitset>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ARITHMETIC vs LOGICAL SHIFT                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int x = -8;
    unsigned int ux = (unsigned int)x;

    cout << "\n--- Value: -8 ---" << endl;
    cout << "  Signed:   " << bitset<8>(x) << " = " << x << endl;
    cout << "  Unsigned: " << bitset<32>(ux) << " = " << ux << endl;

    cout << "\n--- Right Shift by 1 ---" << endl;
    cout << "  Arithmetic (signed >> 1):   " << bitset<8>(x >> 1) << " = " << (x >> 1) << endl;
    cout << "  Logical (unsigned >> 1):    " << bitset<32>(ux >> 1) << " = " << (ux >> 1) << endl;

    cout << "\n--- Right Shift by 2 ---" << endl;
    cout << "  Arithmetic (signed >> 2):   " << bitset<8>(x >> 2) << " = " << (x >> 2) << endl;
    cout << "  Logical (unsigned >> 2):    " << bitset<32>(ux >> 2) << " = " << (ux >> 2) << endl;

    cout << "\n--- Comparison for Positive Numbers ---" << endl;
    int pos = 100;
    unsigned int upos = 100;
    cout << "  100 signed >> 2 = " << (pos >> 2) << endl;
    cout << "  100 unsigned >> 2 = " << (upos >> 2) << endl;
    cout << "  Same result for positive! Both give " << (pos >> 2) << endl;

    cout << "\n--- Force Logical Shift in C++ ---" << endl;
    int neg = -16;
    unsigned int logical_result = ((unsigned int)neg) >> 2;
    int arithmetic_result = neg >> 2;
    cout << "  -16 arithmetic >> 2 = " << arithmetic_result << endl;
    cout << "  -16 logical >> 2    = " << logical_result << " (cast to unsigned)" << endl;

    cout << "\n✅ Arithmetic vs Logical shift demonstrated!" << endl;
    return 0;
}

