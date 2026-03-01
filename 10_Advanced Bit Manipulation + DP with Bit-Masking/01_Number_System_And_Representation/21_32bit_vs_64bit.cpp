/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.21 — 32-BIT vs 64-BIT INTEGERS                       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL SUMMARY:
═════════════════════
    32-bit signed int:
        Range: [-2³¹, 2³¹ - 1] = [-2,147,483,648, 2,147,483,647]
        ≈ ±2.1 × 10⁹
        Bits: [b₃₁ b₃₀ ... b₁ b₀]

    64-bit signed long long:
        Range: [-2⁶³, 2⁶³ - 1] = [-9,223,372,036,854,775,808, 9,223,372,036,854,775,807]
        ≈ ±9.2 × 10¹⁸
        Bits: [b₆₃ b₆₂ ... b₁ b₀]

WHEN TO USE WHAT IN CP:
═══════════════════════
    • n ≤ 10⁹            → int is fine
    • n ≤ 2 × 10⁹        → DANGER ZONE! Use long long
    • n ≤ 10¹⁸           → long long
    • Product of two ints → ALWAYS cast: (long long)a * b
    • Factorials: 13! > INT_MAX, 21! > LLONG_MAX
    • nCr for large n    → use modular arithmetic

COMMON PITFALL:
═══════════════
    int a = 100000;
    int b = 100000;
    int c = a * b;       // OVERFLOW! Result = 1410065408 (garbage)
    long long d = a * b; // STILL OVERFLOW! a*b computed as int first!
    long long e = (long long)a * b; // CORRECT! Cast BEFORE multiply

MEMORY:
═══════
    int:       4 bytes = 32 bits
    long long: 8 bytes = 64 bits
    In CP, memory is rarely an issue. Prefer long long when in doubt.

    Array of 10⁷ ints  = 40 MB  (usually fine)
    Array of 10⁷ longs = 80 MB  (borderline)
*/

#include <iostream>
#include <climits>
#include <cstdint>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   32-BIT vs 64-BIT INTEGERS                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Size comparison
    cout << "\n--- Size in Bytes ---" << endl;
    cout << "  sizeof(int)       = " << sizeof(int) << " bytes = " << sizeof(int)*8 << " bits" << endl;
    cout << "  sizeof(long long) = " << sizeof(long long) << " bytes = " << sizeof(long long)*8 << " bits" << endl;

    // Range comparison
    cout << "\n--- Range Comparison ---" << endl;
    cout << "  int max:       " << INT_MAX << endl;
    cout << "  long long max: " << LLONG_MAX << endl;
    cout << "  Ratio: long long is ~" << (LLONG_MAX / (long long)INT_MAX) << "× larger" << endl;

    // Overflow demonstration
    cout << "\n--- Overflow Pitfall ---" << endl;
    int a = 100000, b = 100000;
    cout << "  int a=100000, b=100000" << endl;
    cout << "  a * b (as int):        " << a * b << " ← OVERFLOW!" << endl;
    cout << "  (long long)a * b:      " << (long long)a * b << " ← CORRECT" << endl;

    // Factorial limits
    cout << "\n--- Factorial Limits ---" << endl;
    long long fact = 1;
    for (int i = 1; i <= 20; i++) {
        fact *= i;
        string fits_int = (fact <= INT_MAX) ? "fits int" : "needs long long";
        string fits_ll = (i <= 20) ? "fits LL" : "overflows LL";
        if (i >= 10)
            cout << "  " << i << "! = " << fact << " (" << fits_int << ", " << fits_ll << ")" << endl;
    }
    cout << "  21! overflows long long!" << endl;

    // 1LL trick
    cout << "\n--- 1LL Shift Trick ---" << endl;
    cout << "  1 << 31 = " << (1 << 31) << " (undefined behavior on signed!)" << endl;
    cout << "  1LL << 31 = " << (1LL << 31) << " (correct)" << endl;
    cout << "  1LL << 40 = " << (1LL << 40) << endl;

    cout << "\n✅ 32-bit vs 64-bit concepts demonstrated!" << endl;
    return 0;
}

