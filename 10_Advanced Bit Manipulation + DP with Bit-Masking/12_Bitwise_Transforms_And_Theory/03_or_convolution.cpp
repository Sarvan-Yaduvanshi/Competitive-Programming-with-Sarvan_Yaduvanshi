/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12.03 — OR CONVOLUTION                                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: C[k] = Σ_{i | j = k} A[i] × B[j]  (OR convolution)

METHOD: Use SUBSET SUM TRANSFORM (Zeta over subsets).
    Transform: f̂[mask] = Σ_{S ⊆ mask} f[S]  (sum over subsets)
    This is exactly SOS DP!

    After transform: ĉ[mask] = â[mask] × b̂[mask]
    Inverse (Möbius inversion).

BUTTERFLY FOR OR-TRANSFORM:
    for (len = 1; len < n; len <<= 1)
        for (i = 0; i < n; i += 2*len)
            for (j = 0; j < len; j++)
                a[i+j+len] += a[i+j];  // forward (subset sum)

    Inverse: a[i+j+len] -= a[i+j];

TIME: O(n log n)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void orTransform(vector<long long>& a, bool inverse) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                if (!inverse) a[i + j + len] += a[i + j];
                else a[i + j + len] -= a[i + j];
            }
        }
    }
}

vector<long long> orConvolution(vector<long long> A, vector<long long> B) {
    int n = A.size();
    orTransform(A, false);
    orTransform(B, false);
    vector<long long> C(n);
    for (int i = 0; i < n; i++) C[i] = A[i] * B[i];
    orTransform(C, true);
    return C;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   OR CONVOLUTION                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<long long> A = {1, 2, 3, 4};
    vector<long long> B = {5, 6, 7, 8};
    auto C = orConvolution(A, B);

    int n = 4;
    vector<long long> brute(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            brute[i | j] += A[i] * B[j];

    cout << "\n  A = {1,2,3,4}, B = {5,6,7,8}" << endl;
    cout << "  OR Convolution:" << endl;
    for (int k = 0; k < n; k++) {
        cout << "    C[" << k << "] = " << C[k] << " (brute: " << brute[k] << ")"
             << (C[k] == brute[k] ? " ✓" : " ✗") << endl;
        assert(C[k] == brute[k]);
    }

    cout << "\n✅ OR convolution verified!" << endl;
    return 0;
}

