/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.02 — LEFT SHIFT / RIGHT SHIFT                           ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

MATHEMATICAL DEFINITION:
════════════════════════
    Left Shift (<<):   x << k = x × 2^k
    Right Shift (>>):  x >> k = ⌊x / 2^k⌋  (for non-negative x)

LEFT SHIFT — x << k:
═════════════════════
    • Shifts all bits k positions to the left
    • Fills vacated positions (right) with 0s
    • Equivalent to multiplying by 2^k
    • Bits shifted out from the left are LOST

DRY RUN — 5 << 2:
══════════════════
    5 = 00000101₂
    << 2 positions:
    = 00010100₂ = 20
    Verify: 5 × 2² = 5 × 4 = 20 ✓

DRY RUN — 1 << k (creates power of 2):
═══════════════════════════════════════
    1 << 0 = 00000001 = 1   = 2⁰
    1 << 1 = 00000010 = 2   = 2¹
    1 << 2 = 00000100 = 4   = 2²
    1 << 3 = 00001000 = 8   = 2³
    1 << k = 2^k             ← VERY IMPORTANT!

RIGHT SHIFT — x >> k:
═════════════════════
    • Shifts all bits k positions to the right
    • For unsigned/positive: fills with 0s (logical shift)
    • For negative signed: implementation-defined (usually fills with 1s = arithmetic shift)
    • Equivalent to integer division by 2^k (floor division)

DRY RUN — 20 >> 2:
═══════════════════
    20 = 00010100₂
    >> 2 positions:
    = 00000101₂ = 5
    Verify: ⌊20 / 2²⌋ = ⌊20/4⌋ = 5 ✓

DRY RUN — 7 >> 1:
══════════════════
    7 = 0111₂
    >> 1 position:
    = 0011₂ = 3
    Verify: ⌊7/2⌋ = 3 ✓ (note: integer division rounds down)

IMPORTANT RULES:
════════════════
    • NEVER shift by negative amount → undefined behavior!
    • NEVER shift >= bit width → undefined behavior!
    • 1 << 31 is UNDEFINED for signed int (overflow). Use 1LL << 31.
    • For 64-bit shifts, use 1LL << k

TIME COMPLEXITY: O(1) — single CPU instruction

PRACTICE PROBLEMS:
══════════════════
    LeetCode 190: Reverse Bits
    LeetCode 338: Counting Bits
    LeetCode 461: Hamming Distance
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   LEFT SHIFT / RIGHT SHIFT                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // LEFT SHIFT
    cout << "\n═══ LEFT SHIFT (x << k = x × 2^k) ═══" << endl;
    for (int k = 0; k <= 5; k++) {
        cout << "  5 << " << k << " = " << bitset<8>(5 << k)
             << " = " << (5 << k) << " (= 5 × 2^" << k << ")" << endl;
    }

    cout << "\n--- Powers of 2 using 1<<k ---" << endl;
    for (int k = 0; k <= 10; k++) {
        cout << "  1 << " << k << " = " << (1 << k) << " = 2^" << k << endl;
    }

    // RIGHT SHIFT
    cout << "\n═══ RIGHT SHIFT (x >> k = ⌊x/2^k⌋) ═══" << endl;
    for (int k = 0; k <= 5; k++) {
        cout << "  100 >> " << k << " = " << bitset<8>(100 >> k)
             << " = " << (100 >> k) << " (= ⌊100/2^" << k << "⌋)" << endl;
    }

    cout << "\n--- Odd number right shift (floor division) ---" << endl;
    cout << "  7 >> 1 = " << (7 >> 1) << " (⌊7/2⌋ = 3, not 3.5)" << endl;
    cout << "  15 >> 2 = " << (15 >> 2) << " (⌊15/4⌋ = 3)" << endl;

    // Negative right shift (arithmetic)
    cout << "\n═══ NEGATIVE RIGHT SHIFT (arithmetic) ═══" << endl;
    int neg = -8;
    cout << "  -8 in binary: " << bitset<8>(neg) << endl;
    cout << "  -8 >> 1 = " << (neg >> 1) << " (arithmetic: fills with 1s)" << endl;
    cout << "  -8 >> 2 = " << (neg >> 2) << endl;

    // Common patterns
    cout << "\n═══ COMMON PATTERNS ═══" << endl;
    cout << "  Multiply by 2:   x << 1  (e.g., 7<<1 = " << (7<<1) << ")" << endl;
    cout << "  Multiply by 8:   x << 3  (e.g., 5<<3 = " << (5<<3) << ")" << endl;
    cout << "  Divide by 2:     x >> 1  (e.g., 14>>1 = " << (14>>1) << ")" << endl;
    cout << "  Divide by 4:     x >> 2  (e.g., 20>>2 = " << (20>>2) << ")" << endl;
    cout << "  Check even/odd:  x & 1   (e.g., 7&1 = " << (7&1) << " → odd)" << endl;

    // 64-bit shift warning
    cout << "\n═══ 64-BIT SHIFT WARNING ═══" << endl;
    cout << "  1 << 30 = " << (1 << 30) << " (OK for int)" << endl;
    cout << "  1LL << 40 = " << (1LL << 40) << " (need LL suffix!)" << endl;

    // Assertions
    assert((5 << 2) == 20);
    assert((20 >> 2) == 5);
    assert((1 << 10) == 1024);
    assert((7 >> 1) == 3);

    cout << "\n✅ All shift operations verified!" << endl;
    return 0;
}

