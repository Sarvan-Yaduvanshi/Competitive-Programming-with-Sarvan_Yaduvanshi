/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.19 — RANGE OF INTEGERS                                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

FORMULA (Two's Complement):
═══════════════════════════
    n-bit signed:    [-2^(n-1),  2^(n-1) - 1]
    n-bit unsigned:  [0,         2^n - 1]

COMPLETE TABLE:
═══════════════
    Type            Bits  Min                    Max                     ≈10^?
    ─────────────────────────────────────────────────────────────────────────
    char (signed)    8    -128                   127                     10²
    unsigned char    8    0                      255                     10²
    short           16    -32,768                32,767                  10⁴
    unsigned short  16    0                      65,535                  10⁴
    int             32    -2,147,483,648         2,147,483,647           10⁹
    unsigned int    32    0                      4,294,967,295           10⁹
    long long       64    -9,223,372,036,854,775,808    9.22×10¹⁸       10¹⁸
    unsigned LL     64    0                      18,446,744,073,709,551,615  10¹⁹

CRITICAL CP KNOWLEDGE:
══════════════════════
    • If max value ≤ 10⁹  → use int
    • If max value ≤ 10¹⁸ → use long long
    • If max value > 10¹⁸ → use __int128 or big integer
    • Product of two ints can overflow int! Use (long long)a * b
    • 2³¹ - 1 = 2,147,483,647 ≈ 2.1 × 10⁹
    • 2⁶³ - 1 ≈ 9.2 × 10¹⁸
*/

#include <iostream>
#include <climits>
#include <cstdint>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   RANGE OF INTEGERS                             ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Signed Types ---" << endl;
    cout << "  char:      [" << SCHAR_MIN << ", " << SCHAR_MAX << "]" << endl;
    cout << "  short:     [" << SHRT_MIN << ", " << SHRT_MAX << "]" << endl;
    cout << "  int:       [" << INT_MIN << ", " << INT_MAX << "]" << endl;
    cout << "  long long: [" << LLONG_MIN << ", " << LLONG_MAX << "]" << endl;

    cout << "\n--- Unsigned Types ---" << endl;
    cout << "  unsigned char:      [0, " << UCHAR_MAX << "]" << endl;
    cout << "  unsigned short:     [0, " << USHRT_MAX << "]" << endl;
    cout << "  unsigned int:       [0, " << UINT_MAX << "]" << endl;
    cout << "  unsigned long long: [0, " << ULLONG_MAX << "]" << endl;

    cout << "\n--- sizeof() in bytes ---" << endl;
    cout << "  char:      " << sizeof(char) << endl;
    cout << "  short:     " << sizeof(short) << endl;
    cout << "  int:       " << sizeof(int) << endl;
    cout << "  long:      " << sizeof(long) << endl;
    cout << "  long long: " << sizeof(long long) << endl;

    cout << "\n--- CP Quick Reference ---" << endl;
    cout << "  10^9 fits in int?       " << (1000000000LL <= INT_MAX ? "YES" : "NO") << endl;
    cout << "  10^10 fits in int?      " << (10000000000LL <= INT_MAX ? "YES" : "NO") << endl;
    cout << "  10^18 fits in long long? " << (true ? "YES" : "NO") << endl;

    cout << "\n✅ Range of integers demonstrated!" << endl;
    return 0;
}

