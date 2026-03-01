/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.09 — MODULO POWER OF TWO TRICK                        ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL IDENTITY:
══════════════════════
    x mod 2^k = x & (2^k - 1)

PROOF:
══════
    2^k - 1 = 0...0 1...1  (k ones)
    x & (2^k - 1) keeps only the lower k bits of x.
    In positional notation: x = q × 2^k + r where 0 ≤ r < 2^k
    The lower k bits of x represent exactly r = x mod 2^k.

DRY RUN — 13 mod 8 (8 = 2³):
    2³ - 1 = 7 = 111₂
    13 & 7 = 1101 & 0111 = 0101 = 5
    Verify: 13 mod 8 = 5 ✓

DRY RUN — 100 mod 16 (16 = 2⁴):
    2⁴ - 1 = 15 = 1111₂
    100 & 15 = 1100100 & 0001111 = 0000100 = 4
    Verify: 100 mod 16 = 4 ✓

APPLICATIONS:
═════════════
    • Hash table with power-of-2 size: index = hash & (size - 1)
    • Circular buffer indexing
    • Fast modulo in tight loops
    • Checking if x is divisible by 2^k: x & (2^k - 1) == 0

TIME: O(1) — much faster than % operator for power-of-2 modulus
*/
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MODULO POWER OF TWO TRICK                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- x mod 2^k = x & (2^k - 1) ---" << endl;
    int tests[] = {13, 100, 255, 1000, 17};
    int powers[] = {2, 4, 8, 16, 32};
    for (int x : tests) {
        for (int p : powers) {
            int mod_result = x & (p - 1);
            int expected = x % p;
            cout << "  " << x << " mod " << p << " = " << x << " & " << (p-1)
                 << " = " << mod_result << (mod_result == expected ? " ✓" : " ✗") << endl;
            assert(mod_result == expected);
        }
    }

    // Check divisibility
    cout << "\n--- Check Divisibility by 2^k ---" << endl;
    for (int x : {8, 12, 16, 15, 32}) {
        cout << "  " << x << " divisible by 4? " << ((x & 3) == 0 ? "YES" : "NO")
             << " | by 8? " << ((x & 7) == 0 ? "YES" : "NO") << endl;
    }

    cout << "\n✅ Modulo power of two trick verified!" << endl;
    return 0;
}

