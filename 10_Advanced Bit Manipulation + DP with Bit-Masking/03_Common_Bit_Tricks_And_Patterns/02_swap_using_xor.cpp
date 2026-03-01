/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.02 — SWAP USING XOR                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ALGORITHM:
══════════
    a = a ^ b    // a now holds a⊕b
    b = a ^ b    // b = (a⊕b)⊕b = a  (by cancellation)
    a = a ^ b    // a = (a⊕b)⊕a = b  (by cancellation)

DRY RUN — Swap a=5, b=3:
    a = 5 (101), b = 3 (011)
    Step 1: a = 5⊕3 = 6 (110)      → a=6, b=3
    Step 2: b = 6⊕3 = 5 (101)      → a=6, b=5
    Step 3: a = 6⊕5 = 3 (011)      → a=3, b=5  ✓

WARNING: Does NOT work if a and b are the same variable!
    a = a ^ a = 0, then b = 0 ^ b = 0, a = 0 ^ 0 = 0 → BOTH ZERO!
    In practice, use std::swap(). XOR swap is just a trick.

TIME: O(1), SPACE: O(1) — no temporary variable needed
*/

#include <iostream>
#include <cassert>
using namespace std;

void xorSwap(int &a, int &b) {
    if (&a == &b) return;  // Guard against same address
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SWAP USING XOR                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int a = 5, b = 3;
    cout << "  Before: a=" << a << ", b=" << b << endl;
    xorSwap(a, b);
    cout << "  After:  a=" << a << ", b=" << b << endl;
    assert(a == 3 && b == 5);

    int x = 100, y = 200;
    cout << "\n  Before: x=" << x << ", y=" << y << endl;
    xorSwap(x, y);
    cout << "  After:  x=" << x << ", y=" << y << endl;
    assert(x == 200 && y == 100);

    cout << "\n✅ XOR swap verified!" << endl;
    return 0;
}

