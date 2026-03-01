/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.07 — FAST EXPONENTIATION (Binary Exponentiation)      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL IDEA:
══════════════════
    To compute a^n, observe that n can be written in binary: n = Σ b_i × 2^i

    a^n = a^(b₀×2⁰ + b₁×2¹ + b₂×2² + ...)
        = a^(b₀) × a^(b₁×2) × a^(b₂×4) × ...

    We compute a^1, a^2, a^4, a^8, ... by repeated squaring.
    Multiply those where the corresponding bit of n is 1.

RECURRENCE:
═══════════
    a^n = { 1                    if n = 0
          { (a^(n/2))² × a      if n is odd
          { (a^(n/2))²          if n is even

DRY RUN — 3^13 (13 = 1101₂):
═════════════════════════════
    Bit 0 (1): result *= 3^1 = 3,        base = 3² = 9
    Bit 1 (0): skip,                     base = 9² = 81
    Bit 2 (1): result *= 81,    result = 3×81 = 243, base = 81² = 6561
    Bit 3 (1): result *= 6561, result = 243×6561 = 1594323

    Verify: 3^13 = 1,594,323 ✓

MODULAR VERSION: (a^n) mod m — ESSENTIAL for CP
    At each step: result = (result * base) % m, base = (base * base) % m

TIME: O(log n) — only log₂(n) multiplications!
SPACE: O(1) iterative, O(log n) recursive

PRACTICE PROBLEMS:
══════════════════
    CSES: Exponentiation, Exponentiation II
    LeetCode 50: Pow(x, n)
    Codeforces: Almost all modular arithmetic problems
*/
#include <iostream>
#include <cassert>
using namespace std;

// Iterative binary exponentiation
long long binpow(long long a, long long n) {
    long long result = 1;
    while (n > 0) {
        if (n & 1) result *= a;  // if current bit of n is 1
        a *= a;                   // square the base
        n >>= 1;                  // next bit
    }
    return result;
}

// Modular binary exponentiation
long long binpow_mod(long long a, long long n, long long mod) {
    long long result = 1;
    a %= mod;
    while (n > 0) {
        if (n & 1) result = result * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return result;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   FAST EXPONENTIATION (Binary Power)            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Trace
    cout << "\n--- Trace: 3^13 (13 = 1101₂) ---" << endl;
    long long a = 3, n = 13, result = 1;
    int step = 0;
    while (n > 0) {
        cout << "  Bit " << step << " (" << (n&1) << "): ";
        if (n & 1) {
            result *= a;
            cout << "multiply → result=" << result;
        } else {
            cout << "skip";
        }
        a *= a;
        cout << ", base²=" << a << endl;
        n >>= 1;
        step++;
    }
    cout << "  Final: 3^13 = " << result << endl;

    assert(binpow(3, 13) == 1594323);
    assert(binpow(2, 10) == 1024);
    assert(binpow(2, 0) == 1);

    // Modular
    cout << "\n--- Modular: 2^10 mod 1000 ---" << endl;
    cout << "  " << binpow_mod(2, 10, 1000) << endl;
    assert(binpow_mod(2, 10, 1000) == 24);

    long long MOD = 1e9 + 7;
    cout << "  2^(10^9) mod (10^9+7) = " << binpow_mod(2, 1000000000, MOD) << endl;

    cout << "\n✅ Fast exponentiation verified!" << endl;
    return 0;
}

