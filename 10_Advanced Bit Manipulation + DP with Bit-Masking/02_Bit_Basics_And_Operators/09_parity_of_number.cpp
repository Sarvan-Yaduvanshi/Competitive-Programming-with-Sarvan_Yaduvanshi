/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.09 — PARITY OF A NUMBER                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

DEFINITION:
═══════════
    Parity = popcount(n) mod 2
    Even parity: even number of 1-bits → parity = 0
    Odd parity:  odd number of 1-bits  → parity = 1

FORMULA: parity(n) = __builtin_parity(n)
    Or: XOR all bits together (since XOR = addition mod 2)

DRY RUN:
    13 = 1101₂ → 3 set bits → odd parity (1)
    15 = 1111₂ → 4 set bits → even parity (0)
     7 = 0111₂ → 3 set bits → odd parity (1)

EFFICIENT METHOD — XOR FOLDING:
═══════════════════════════════
    For 32-bit: fold in half repeatedly
    x ^= (x >> 16);  // mix upper 16 into lower 16
    x ^= (x >> 8);   // mix upper 8 into lower 8
    x ^= (x >> 4);   // ... and so on
    x ^= (x >> 2);
    x ^= (x >> 1);
    return x & 1;

APPLICATION: Error detection in data transmission.

TIME: O(1)
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

int parity_naive(int n) {
    int p = 0;
    while (n) {
        p ^= (n & 1);
        n >>= 1;
    }
    return p;
}

int parity_kernighan(int n) {
    int p = 0;
    while (n) {
        p ^= 1;         // toggle parity for each set bit
        n = n & (n - 1); // remove lowest set bit
    }
    return p;
}

int parity_builtin(int n) {
    return __builtin_parity(n); // returns 1 if odd number of set bits
}

int parity_xor_fold(unsigned int x) {
    x ^= (x >> 16);
    x ^= (x >> 8);
    x ^= (x >> 4);
    x ^= (x >> 2);
    x ^= (x >> 1);
    return x & 1;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   PARITY OF A NUMBER                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int tests[] = {0, 1, 3, 7, 13, 15, 255};
    for (int x : tests) {
        cout << "  " << x << " (" << bitset<8>(x) << "): popcount=" << __builtin_popcount(x)
             << ", parity=" << parity_builtin(x)
             << " (" << (parity_builtin(x) ? "odd" : "even") << ")" << endl;
    }

    // Verify all methods agree
    for (int x : tests) {
        assert(parity_naive(x) == parity_builtin(x));
        assert(parity_kernighan(x) == parity_builtin(x));
        assert(parity_xor_fold(x) == parity_builtin(x));
    }

    cout << "\n✅ Parity of number verified!" << endl;
    return 0;
}

