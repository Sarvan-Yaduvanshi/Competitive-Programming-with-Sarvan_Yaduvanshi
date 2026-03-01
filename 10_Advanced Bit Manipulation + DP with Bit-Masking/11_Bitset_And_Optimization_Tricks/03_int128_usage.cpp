/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 11.03 — __int128 USAGE                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

__int128: GCC extension for 128-bit integers.
    Range: [-2¹²⁷, 2¹²⁷ - 1] (signed) ≈ ±1.7 × 10³⁸
    unsigned __int128: [0, 2¹²⁸ - 1] ≈ 3.4 × 10³⁸

USE CASES:
══════════
    • Avoid overflow in (a × b) % m when a,b can be up to 10¹⁸
    • Bitmask with n > 64 (up to 128)
    • Intermediate computation that exceeds 64-bit range

LIMITATIONS:
════════════
    • No cin/cout support — must write custom I/O
    • Not standard C++ — GCC/Clang only
    • Slower than 64-bit (2 instructions per operation)

MODULAR MULTIPLICATION WITHOUT OVERFLOW:
════════════════════════════════════════
    (a × b) % m where a,b,m ≤ 10¹⁸
    Use: (__int128)a * b % m
*/
#include <iostream>
#include <cstdint>
using namespace std;

// Custom print for __int128
void print128(__int128 x) {
    if (x < 0) { cout << '-'; x = -x; }
    if (x > 9) print128(x / 10);
    cout << (char)('0' + (int)(x % 10));
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   __int128 USAGE                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Basic usage
    __int128 a = 1;
    for (int i = 0; i < 100; i++) a *= 2;
    cout << "\n  2^100 = ";
    print128(a);
    cout << endl;

    // Overflow-safe modular multiplication
    cout << "\n--- Modular Multiplication (a×b mod m) ---" << endl;
    long long x = 999999999999999989LL; // close to 10^18
    long long y = 999999999999999999LL;
    long long mod = 1000000007;

    // This would overflow with long long × long long:
    long long result = ((__int128)x * y) % mod;
    cout << "  (" << x << " × " << y << ") % " << mod << " = " << result << endl;

    // Bitmask with __int128
    cout << "\n--- __int128 as 128-bit Bitmask ---" << endl;
    unsigned __int128 mask = 0;
    mask |= ((unsigned __int128)1 << 100);
    mask |= ((unsigned __int128)1 << 50);
    mask |= ((unsigned __int128)1 << 0);

    cout << "  Set bits at positions 0, 50, 100" << endl;
    cout << "  Bit 100 set? " << (bool)((mask >> 100) & 1) << endl;
    cout << "  Bit 50 set?  " << (bool)((mask >> 50) & 1) << endl;
    cout << "  Bit 75 set?  " << (bool)((mask >> 75) & 1) << endl;

    // Popcount for __int128
    auto popcount128 = [](unsigned __int128 x) -> int {
        return __builtin_popcountll((unsigned long long)x) +
               __builtin_popcountll((unsigned long long)(x >> 64));
    };
    cout << "  Popcount of mask: " << popcount128(mask) << endl;

    cout << "\n✅ __int128 usage demonstrated!" << endl;
    return 0;
}

