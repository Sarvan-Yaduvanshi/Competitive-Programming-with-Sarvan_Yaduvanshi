/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12.01 — FAST WALSH-HADAMARD TRANSFORM (FWHT)             ║
║           Bit Manipulation — Bitwise Transforms & Theory                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Compute C[k] = Σ_{i ⊕ j = k} A[i] × B[j]  (XOR convolution)
    This is the "bitwise convolution" where the combining operation is XOR.

WALSH-HADAMARD TRANSFORM:
═════════════════════════
    H(A)[k] = Σ_i (-1)^(popcount(k & i)) × A[i]

    Key property: H(A ⊛ B) = H(A) × H(B)  (pointwise multiplication)

ALGORITHM (Butterfly):
══════════════════════
    for (int len = 1; len < n; len <<= 1)
        for (int i = 0; i < n; i += len << 1)
            for (int j = 0; j < len; j++) {
                long long u = a[i+j], v = a[i+j+len];
                a[i+j] = u + v;        // "positive" butterfly
                a[i+j+len] = u - v;    // "negative" butterfly
            }

    Inverse: same butterfly, then divide by n.

DRY RUN — XOR convolution of A=[1,2,3,4] and B=[5,6,7,8]:
    C[k] = Σ_{i^j=k} A[i]×B[j]
    C[0] = A[0]B[0]+A[1]B[1]+A[2]B[2]+A[3]B[3] = 5+12+21+32 = 70
    C[1] = A[0]B[1]+A[1]B[0]+A[2]B[3]+A[3]B[2] = 6+10+24+28 = 68
    C[2] = A[0]B[2]+A[1]B[3]+A[2]B[0]+A[3]B[1] = 7+16+15+24 = 62
    C[3] = A[0]B[3]+A[1]B[2]+A[2]B[1]+A[3]B[0] = 8+14+18+20 = 60

TIME: O(n log n) where n = 2^k

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 914G, 449D
    AtCoder: ARC 100 E
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void fwht_xor(vector<long long>& a, bool inverse) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                long long u = a[i + j], v = a[i + j + len];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }
    if (inverse) {
        for (auto& x : a) x /= n;
    }
}

vector<long long> xorConvolution(vector<long long> A, vector<long long> B) {
    int n = A.size();
    fwht_xor(A, false);
    fwht_xor(B, false);
    vector<long long> C(n);
    for (int i = 0; i < n; i++) C[i] = A[i] * B[i];
    fwht_xor(C, true);
    return C;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   FAST WALSH-HADAMARD TRANSFORM (XOR Conv)      ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<long long> A = {1, 2, 3, 4};
    vector<long long> B = {5, 6, 7, 8};

    auto C = xorConvolution(A, B);

    // Brute force verify
    int n = 4;
    vector<long long> brute(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            brute[i ^ j] += A[i] * B[j];

    cout << "\n  A = {1,2,3,4}, B = {5,6,7,8}" << endl;
    cout << "\n  XOR Convolution:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "    C[" << k << "] = " << C[k] << " (brute: " << brute[k] << ")"
             << (C[k] == brute[k] ? " ✓" : " ✗") << endl;
        assert(C[k] == brute[k]);
    }

    cout << "\n  Time complexity: O(n log n) = O(4 × 2) = 8 operations" << endl;
    cout << "  vs brute force: O(n²) = 16 operations" << endl;

    cout << "\n✅ FWHT (XOR convolution) verified!" << endl;
    return 0;
}

