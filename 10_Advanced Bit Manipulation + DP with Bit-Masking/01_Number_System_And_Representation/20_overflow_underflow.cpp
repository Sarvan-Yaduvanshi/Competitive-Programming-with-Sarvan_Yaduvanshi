/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01.20 — OVERFLOW AND UNDERFLOW                           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION:
═══════════
OVERFLOW:  Result exceeds maximum representable value → wraps around.
UNDERFLOW: Result goes below minimum representable value → wraps around.

MATHEMATICAL MODEL (n-bit two's complement):
════════════════════════════════════════════
    Arithmetic is done modulo 2ⁿ.
    If result R is in [2^(n-1), 2ⁿ-1], it wraps to R - 2ⁿ (negative).
    If result R is in [-2ⁿ, -2^(n-1)-1], it wraps to R + 2ⁿ (positive).

DRY RUN — 8-BIT SIGNED OVERFLOW:
═════════════════════════════════
    127 + 1 = ?
    01111111 + 00000001 = 10000000 = -128 (OVERFLOW!)

    Mathematically: 128 mod 256 = 128, interpreted as 128 - 256 = -128

DRY RUN — 8-BIT SIGNED UNDERFLOW:
══════════════════════════════════
    -128 - 1 = ?
    10000000 + 11111111 = 01111111 = +127 (UNDERFLOW!)

    Mathematically: -129 mod 256 = 127

DRY RUN — UNSIGNED OVERFLOW:
════════════════════════════
    255 + 1 = ?  (8-bit unsigned)
    11111111 + 00000001 = 100000000 → truncated to 00000000 = 0

DETECTION IN CP:
════════════════
    • If a + b > INT_MAX → check: a > INT_MAX - b
    • If a * b overflows → check: a > INT_MAX / b (when b > 0)
    • Use long long to avoid int overflow: (long long)a * b

PRACTICE PROBLEMS:
══════════════════
    LeetCode 7: Reverse Integer (handle overflow)
    LeetCode 8: String to Integer (atoi)
*/

#include <iostream>
#include <climits>
#include <bitset>
using namespace std;

// Safe addition check
bool willOverflowAdd(int a, int b) {
    if (b > 0 && a > INT_MAX - b) return true;
    if (b < 0 && a < INT_MIN - b) return true;
    return false;
}

// Safe multiplication check
bool willOverflowMul(int a, int b) {
    if (a == 0 || b == 0) return false;
    if (a > 0 && b > 0 && a > INT_MAX / b) return true;
    if (a < 0 && b < 0 && a < INT_MAX / b) return true;
    if (a > 0 && b < 0 && b < INT_MIN / a) return true;
    if (a < 0 && b > 0 && a < INT_MIN / b) return true;
    return false;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   OVERFLOW AND UNDERFLOW                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // 8-bit signed overflow
    cout << "\n--- 8-bit Signed Overflow ---" << endl;
    signed char a = 127;
    signed char b = a + 1;
    cout << "  127 + 1 = " << (int)b << " (overflow! wraps to -128)" << endl;

    // 8-bit signed underflow
    cout << "\n--- 8-bit Signed Underflow ---" << endl;
    signed char c = -128;
    signed char d = c - 1;
    cout << "  -128 - 1 = " << (int)d << " (underflow! wraps to 127)" << endl;

    // 8-bit unsigned overflow
    cout << "\n--- 8-bit Unsigned Overflow ---" << endl;
    unsigned char e = 255;
    unsigned char f = e + 1;
    cout << "  255 + 1 = " << (int)f << " (wraps to 0)" << endl;

    // 32-bit overflow detection
    cout << "\n--- 32-bit Overflow Detection ---" << endl;
    cout << "  INT_MAX + 1 overflows? " << (willOverflowAdd(INT_MAX, 1) ? "YES" : "NO") << endl;
    cout << "  100 + 200 overflows?   " << (willOverflowAdd(100, 200) ? "YES" : "NO") << endl;
    cout << "  INT_MAX * 2 overflows? " << (willOverflowMul(INT_MAX, 2) ? "YES" : "NO") << endl;

    // Safe way: use long long
    cout << "\n--- Safe Way: Cast to long long ---" << endl;
    int x = 1000000, y = 1000000;
    cout << "  int * int = " << x * y << " (OVERFLOW!)" << endl;
    cout << "  (long long) * int = " << (long long)x * y << " (SAFE)" << endl;

    cout << "\n✅ Overflow/Underflow concepts demonstrated!" << endl;
    return 0;
}

