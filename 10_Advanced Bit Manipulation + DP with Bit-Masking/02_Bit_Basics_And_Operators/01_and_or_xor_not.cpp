/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02.01 — AND, OR, XOR, NOT OPERATORS                        ║
║           Bit Manipulation — Bit Basics & Operators                          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TRUTH TABLES:
═════════════
    AND (&)          OR (|)           XOR (^)          NOT (~)
    A  B  A&B        A  B  A|B        A  B  A^B        A  ~A
    0  0   0         0  0   0         0  0   0         0   1
    0  1   0         0  1   1         0  1   1         1   0
    1  0   0         1  0   1         1  0   1
    1  1   1         1  1   1         1  1   0

MATHEMATICAL PROPERTIES:
════════════════════════
    AND:  a & b = min(a_i, b_i) per bit    "Both must be 1"
          a & 0 = 0,  a & a = a,  a & ~a = 0
          a & (b|c) = (a&b) | (a&c)  [distributive]

    OR:   a | b = max(a_i, b_i) per bit    "At least one must be 1"
          a | 0 = a,  a | a = a,  a | ~a = all 1s
          a | (b&c) = (a|b) & (a|c)  [distributive]

    XOR:  a ^ b = (a_i + b_i) mod 2 per bit  "Exactly one must be 1"
          a ^ 0 = a,  a ^ a = 0,  a ^ ~a = all 1s
          Commutative: a^b = b^a
          Associative: (a^b)^c = a^(b^c)
          Self-inverse: a^b^b = a

    NOT:  ~a = flip all bits
          ~a = -a - 1 (in two's complement: ~a = -(a+1))
          ~~a = a

DRY RUN — 13 & 7:
══════════════════
    13 = 1101₂
     7 = 0111₂
    ──────────
    &  = 0101₂ = 5   (only positions where BOTH are 1)

DRY RUN — 13 | 7:
══════════════════
    13 = 1101₂
     7 = 0111₂
    ──────────
    |  = 1111₂ = 15  (positions where AT LEAST ONE is 1)

DRY RUN — 13 ^ 7:
══════════════════
    13 = 1101₂
     7 = 0111₂
    ──────────
    ^  = 1010₂ = 10  (positions where EXACTLY ONE is 1)

DRY RUN — ~13 (32-bit):
════════════════════════
    13   = 00000000 00000000 00000000 00001101
    ~13  = 11111111 11111111 11111111 11110010 = -14
    (because ~a = -(a+1) → ~13 = -14)

KEY IDENTITY: a & b + a | b = a + b  (for any integers a, b)
PROOF: Each bit position contributes min(a_i,b_i) + max(a_i,b_i) = a_i + b_i

PRACTICE PROBLEMS:
══════════════════
    LeetCode 191: Number of 1 Bits
    LeetCode 201: Bitwise AND of Numbers Range
    LeetCode 268: Missing Number
    Codeforces: 1721B
*/

#include <iostream>
#include <bitset>
#include <cassert>
using namespace std;

void demonstrateAND(int a, int b) {
    cout << "  " << a << " & " << b << ":" << endl;
    cout << "    " << bitset<8>(a) << " (" << a << ")" << endl;
    cout << "  & " << bitset<8>(b) << " (" << b << ")" << endl;
    cout << "  = " << bitset<8>(a & b) << " (" << (a & b) << ")" << endl;
}

void demonstrateOR(int a, int b) {
    cout << "  " << a << " | " << b << ":" << endl;
    cout << "    " << bitset<8>(a) << " (" << a << ")" << endl;
    cout << "  | " << bitset<8>(b) << " (" << b << ")" << endl;
    cout << "  = " << bitset<8>(a | b) << " (" << (a | b) << ")" << endl;
}

void demonstrateXOR(int a, int b) {
    cout << "  " << a << " ^ " << b << ":" << endl;
    cout << "    " << bitset<8>(a) << " (" << a << ")" << endl;
    cout << "  ^ " << bitset<8>(b) << " (" << b << ")" << endl;
    cout << "  = " << bitset<8>(a ^ b) << " (" << (a ^ b) << ")" << endl;
}

void demonstrateNOT(int a) {
    cout << "  ~" << a << ":" << endl;
    cout << "    " << bitset<32>(a) << " (" << a << ")" << endl;
    cout << "  = " << bitset<32>(~a) << " (" << (~a) << ")" << endl;
    cout << "  Note: ~" << a << " = -(" << a << "+1) = " << -(a+1) << endl;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   AND, OR, XOR, NOT OPERATORS                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n═══ AND (&) — Both bits must be 1 ═══" << endl;
    demonstrateAND(13, 7);
    cout << endl;
    demonstrateAND(15, 9);

    cout << "\n═══ OR (|) — At least one bit must be 1 ═══" << endl;
    demonstrateOR(13, 7);
    cout << endl;
    demonstrateOR(10, 5);

    cout << "\n═══ XOR (^) — Exactly one bit must be 1 ═══" << endl;
    demonstrateXOR(13, 7);
    cout << endl;
    demonstrateXOR(15, 15);  // x ^ x = 0

    cout << "\n═══ NOT (~) — Flip all bits ═══" << endl;
    demonstrateNOT(13);
    cout << endl;
    demonstrateNOT(0);

    cout << "\n═══ Properties Verification ═══" << endl;
    int a = 42, b = 73;
    cout << "  a=" << a << ", b=" << b << endl;
    cout << "  a & b + a | b = " << (a&b) << " + " << (a|b) << " = " << ((a&b)+(a|b)) << endl;
    cout << "  a + b = " << a+b << " (should be equal)" << endl;
    assert((a & b) + (a | b) == a + b);

    cout << "  a ^ a = " << (a ^ a) << " (always 0)" << endl;
    cout << "  a ^ 0 = " << (a ^ 0) << " (always a)" << endl;
    cout << "  ~(~a) = " << (~~a) << " (always a)" << endl;
    assert((a ^ a) == 0);
    assert((a ^ 0) == a);

    cout << "\n✅ All bitwise operators verified!" << endl;
    return 0;
}

