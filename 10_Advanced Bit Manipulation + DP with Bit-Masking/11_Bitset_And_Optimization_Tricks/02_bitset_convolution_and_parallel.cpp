/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 11.02 — BITSET CONVOLUTION & BIT PARALLEL TRICKS         ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

BITSET CONVOLUTION:
═══════════════════
    Multiply two polynomials modulo 2 (coefficients are 0 or 1).
    If we represent polynomial as bitset, multiplication is:
        for each bit i set in A: result ^= (B << i)
    This gives O(n²/64) convolution over GF(2).

BIT PARALLEL TRICKS:
════════════════════
    1. Bitset matrix multiplication: O(n³/64) instead of O(n³).
    2. Hamming distance of two bitsets: (a ^ b).count() in O(n/64).
    3. Common prefix/suffix: use bit operations on words.
    4. Batch AND/OR: process 64 elements at once.

APPLICATIONS:
═════════════
    • Speed up DP over boolean states
    • Fast matrix multiplication over GF(2)
    • Pattern matching with wildcards
    • Graph algorithms (transitive closure in O(V³/64))

TIME SAVINGS: Factor of 64 (or 32 on some architectures).
*/
#include <iostream>
#include <bitset>
#include <vector>
#include <chrono>
using namespace std;

const int N = 1000;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   BITSET CONVOLUTION & BIT PARALLEL TRICKS      ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Polynomial multiplication over GF(2) using bitset
    cout << "\n--- Polynomial Multiplication mod 2 ---" << endl;
    // A(x) = 1 + x + x³ = 1011₂ (coefficients)
    // B(x) = 1 + x² = 101₂
    // A×B mod 2:
    bitset<16> A, B, result;
    A[0] = A[1] = A[3] = 1; // 1 + x + x³
    B[0] = B[2] = 1;         // 1 + x²

    for (int i = 0; i < 16; i++) {
        if (A[i]) result ^= (B << i);
    }
    cout << "  A(x) = 1+x+x³  → " << A << endl;
    cout << "  B(x) = 1+x²    → " << B << endl;
    cout << "  A×B mod 2       → " << result << endl;
    // Expected: 1+x+x²+x³+x⁵ = 101111₂ → bit positions: 0,1,2,3,5
    cout << "  Coefficients: ";
    for (int i = 0; i < 8; i++) if (result[i]) cout << "x^" << i << " + ";
    cout << endl;

    // Hamming distance with bitset
    cout << "\n--- Hamming Distance (bitset) ---" << endl;
    bitset<64> s1, s2;
    s1 = 0b11010110;
    s2 = 0b10110101;
    cout << "  s1 = " << s1 << endl;
    cout << "  s2 = " << s2 << endl;
    cout << "  Hamming distance = " << (s1 ^ s2).count() << endl;

    // Matrix multiplication over GF(2) — O(n³/64)
    cout << "\n--- Matrix Multiply GF(2) (3×3 example) ---" << endl;
    vector<bitset<3>> matA(3), matB(3), matC(3);
    // A = [[1,0,1],[0,1,1],[1,1,0]]
    matA[0][0] = matA[0][2] = 1;
    matA[1][1] = matA[1][2] = 1;
    matA[2][0] = matA[2][1] = 1;
    // B = identity
    matB[0][0] = matB[1][1] = matB[2][2] = 1;

    // C = A × B (over GF(2)): C[i][j] = XOR over k of A[i][k] AND B[k][j]
    // With bitset: C[i] = XOR of B[k] for all k where A[i][k]=1
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++)
            if (matA[i][k]) matC[i] ^= matB[k];

    for (int i = 0; i < 3; i++)
        cout << "  C[" << i << "] = " << matC[i] << endl;

    // Performance: bitset vs manual
    cout << "\n--- Performance: Bitset is ~64× faster ---" << endl;
    cout << "  Bitset<10000> AND: O(10000/64) ≈ 156 word operations" << endl;
    cout << "  Manual loop: O(10000) bit operations" << endl;
    cout << "  Speedup: ~64×" << endl;

    cout << "\n✅ Bitset convolution and bit parallel tricks demonstrated!" << endl;
    return 0;
}

