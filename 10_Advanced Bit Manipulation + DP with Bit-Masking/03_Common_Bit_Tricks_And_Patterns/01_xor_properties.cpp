/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03.01 — XOR PROPERTIES                                   ║
║           Bit Manipulation — Common Tricks & Patterns                      ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

XOR PROPERTIES (MUST MEMORIZE):
═══════════════════════════════
    1. Identity:      a ⊕ 0 = a
    2. Self-inverse:  a ⊕ a = 0
    3. Commutative:   a ⊕ b = b ⊕ a
    4. Associative:   (a ⊕ b) ⊕ c = a ⊕ (b ⊕ c)
    5. Complement:    a ⊕ ~0 = ~a  (XOR with all 1s = NOT)
    6. Cancellation:  a ⊕ b ⊕ b = a  (XOR twice cancels)
    7. Bit-wise:      (a ⊕ b)_i = (a_i + b_i) mod 2

DERIVED PROPERTIES:
═══════════════════
    • XOR of same number appears even times = cancels out
    • XOR of array with all elements appearing twice except one → the single element
    • a ⊕ b = 0  ⟺  a = b
    • XOR is its own inverse: if c = a ⊕ b, then a = c ⊕ b, b = c ⊕ a

DRY RUN — XOR CANCELLATION:
════════════════════════════
    5 ⊕ 3 ⊕ 5 ⊕ 7 ⊕ 3
    = (5 ⊕ 5) ⊕ (3 ⊕ 3) ⊕ 7   [reorder by commutativity/associativity]
    = 0 ⊕ 0 ⊕ 7
    = 7 ✓

USEFUL IDENTITIES FOR CP:
══════════════════════════
    • XOR from 0 to n has a pattern based on n%4:
        XOR(0..n) = n    if n%4 == 0
                  = 1    if n%4 == 1
                  = n+1  if n%4 == 2
                  = 0    if n%4 == 3

    PROOF: 4k ⊕ (4k+1) ⊕ (4k+2) ⊕ (4k+3) = 0 for any k
*/

#include <iostream>
#include <cassert>
using namespace std;

// XOR from 0 to n in O(1)
long long xorRange(long long n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
    return 0;
}

// XOR from L to R in O(1)
long long xorLR(long long L, long long R) {
    return xorRange(R) ^ xorRange(L - 1);
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   XOR PROPERTIES                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Property demonstrations
    int a = 42, b = 73;
    cout << "\n--- Basic Properties (a=" << a << ", b=" << b << ") ---" << endl;
    cout << "  a ^ 0 = " << (a ^ 0) << " (identity)" << endl;
    cout << "  a ^ a = " << (a ^ a) << " (self-inverse)" << endl;
    cout << "  a ^ b = " << (a ^ b) << ", b ^ a = " << (b ^ a) << " (commutative)" << endl;
    cout << "  a ^ b ^ b = " << (a ^ b ^ b) << " (cancellation = a)" << endl;

    // XOR range pattern
    cout << "\n--- XOR(0..n) Pattern ---" << endl;
    for (int n = 0; n <= 15; n++) {
        long long brute = 0;
        for (int i = 0; i <= n; i++) brute ^= i;
        cout << "  XOR(0.." << n << ") = " << brute << " (formula: " << xorRange(n)
             << ") n%4=" << n%4 << endl;
        assert(brute == xorRange(n));
    }

    // XOR range query
    cout << "\n--- XOR(L..R) ---" << endl;
    cout << "  XOR(3..7) = " << xorLR(3, 7) << endl;
    long long verify = 3^4^5^6^7;
    cout << "  Verify: 3^4^5^6^7 = " << verify << endl;
    assert(xorLR(3, 7) == verify);

    cout << "\n✅ All XOR properties verified!" << endl;
    return 0;
}

