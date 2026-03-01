/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12.02 — AND CONVOLUTION                                  ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: C[k] = Σ_{i & j = k} A[i] × B[j]  (AND convolution)

METHOD: Use SUPERSET SUM TRANSFORM (Zeta over supersets).
    Transform: f̂[mask] = Σ_{mask ⊆ S} f[S]  (sum over supersets)

    After transform: ĉ[mask] = â[mask] × b̂[mask]

    Inverse (Möbius): f[mask] = Σ_{mask ⊆ S} (-1)^|S\mask| f̂[S]

BUTTERFLY FOR AND-TRANSFORM:
    for (len = 1; len < n; len <<= 1)
        for (i = 0; i < n; i += 2*len)
            for (j = 0; j < len; j++)
                a[i+j] += a[i+j+len];  // forward (superset sum)

    Inverse: a[i+j] -= a[i+j+len];

TIME: O(n log n)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void andTransform(vector<long long>& a, bool inverse) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                if (!inverse) a[i + j] += a[i + j + len];
                else a[i + j] -= a[i + j + len];
            }
        }
    }
}

vector<long long> andConvolution(vector<long long> A, vector<long long> B) {
    int n = A.size();
    andTransform(A, false);
    andTransform(B, false);
    vector<long long> C(n);
    for (int i = 0; i < n; i++) C[i] = A[i] * B[i];
    andTransform(C, true);
    return C;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   AND CONVOLUTION                               ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<long long> A = {1, 2, 3, 4};
    vector<long long> B = {5, 6, 7, 8};
    auto C = andConvolution(A, B);

    int n = 4;
    vector<long long> brute(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            brute[i & j] += A[i] * B[j];

    cout << "\n  A = {1,2,3,4}, B = {5,6,7,8}" << endl;
    cout << "  AND Convolution:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "    C[" << k << "] = " << C[k] << " (brute: " << brute[k] << ")"
             << (C[k] == brute[k] ? " ✓" : " ✗") << endl;
        assert(C[k] == brute[k]);
    }

    cout << "\n✅ AND convolution verified!" << endl;
    return 0;
}

