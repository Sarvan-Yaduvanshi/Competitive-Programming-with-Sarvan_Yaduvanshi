/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.08 — MULTIPLY / DIVIDE BY POWERS OF TWO              ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL IDENTITIES:
════════════════════════
    x × 2^k = x << k       (left shift by k)
    x / 2^k = x >> k       (right shift by k, floor division)
    x × 2   = x << 1       (double)
    x / 2   = x >> 1       (halve, floor)
    x × 3   = (x << 1) + x    = x*2 + x
    x × 5   = (x << 2) + x    = x*4 + x
    x × 7   = (x << 3) - x    = x*8 - x
    x × 10  = (x << 3) + (x << 1) = x*8 + x*2

DRY RUN — 7 × 8:
    7 << 3 = 7 × 2³ = 56 ✓

DRY RUN — 100 / 4:
    100 >> 2 = ⌊100/4⌋ = 25 ✓

DRY RUN — 15 / 4:
    15 >> 2 = ⌊15/4⌋ = 3 (floor division, not 3.75) ✓

WARNING: Shift only works for POWERS OF 2, not arbitrary multipliers!
WARNING: Right shift of negative numbers is implementation-defined.

WHY USE SHIFTS?
═══════════════
    Modern compilers ALREADY optimize * and / by powers of 2 into shifts.
    In CP, use * and / for clarity. Shifts are for BIT MANIPULATION logic.

TIME: O(1)
*/
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MULTIPLY / DIVIDE BY POWERS OF TWO            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Multiply
    cout << "\n--- Multiply by Powers of 2 ---" << endl;
    int x = 7;
    for (int k = 0; k <= 5; k++) {
        cout << "  " << x << " × 2^" << k << " = " << x << " << " << k
             << " = " << (x << k) << endl;
    }

    // Divide
    cout << "\n--- Divide by Powers of 2 ---" << endl;
    x = 100;
    for (int k = 0; k <= 5; k++) {
        cout << "  " << x << " / 2^" << k << " = " << x << " >> " << k
             << " = " << (x >> k) << " (⌊" << x << "/" << (1<<k) << "⌋)" << endl;
    }

    // Multiply by non-power using shifts
    cout << "\n--- Multiply by Non-Powers Using Shifts ---" << endl;
    x = 13;
    cout << "  " << x << " × 3 = (x<<1)+x = " << ((x<<1)+x) << " (verify: " << x*3 << ")" << endl;
    cout << "  " << x << " × 5 = (x<<2)+x = " << ((x<<2)+x) << " (verify: " << x*5 << ")" << endl;
    cout << "  " << x << " × 7 = (x<<3)-x = " << ((x<<3)-x) << " (verify: " << x*7 << ")" << endl;
    cout << "  " << x << " × 10 = (x<<3)+(x<<1) = " << ((x<<3)+(x<<1)) << " (verify: " << x*10 << ")" << endl;

    assert((7 << 3) == 56);
    assert((100 >> 2) == 25);
    assert(((13 << 1) + 13) == 39);

    cout << "\n✅ Multiply/Divide by powers of 2 verified!" << endl;
    return 0;
}

