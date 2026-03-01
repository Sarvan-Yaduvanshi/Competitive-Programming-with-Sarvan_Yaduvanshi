/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09.02 — SUBSET CONVOLUTION                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Compute C[S] = Σ_{T⊆S} A[T] × B[S\T] for all S.
    This is convolution over the subset lattice (OR convolution won't work
    because we need T and S\T to be DISJOINT).

ALGORITHM (Ranked Subset Convolution):
══════════════════════════════════════
    1. Stratify by popcount: Â[k][mask] = A[mask] if popcount(mask)==k, else 0.
    2. Apply SOS (Möbius/Zeta) transform to each rank.
    3. Multiply ranks: Ĉ[k] = Σ_{j=0}^{k} Â[j] × B̂[k-j] (pointwise per mask).
    4. Inverse SOS transform each rank.
    5. C[mask] = Ĉ[popcount(mask)][mask].

    The rank separation ensures T ∩ (S\T) = ∅.

TIME: O(n² × 2ⁿ)

This is GRANDMASTER-level technique used in competitive programming.

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 914G, 800D
    AtCoder: problems with subset convolution
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void sosMobius(vector<vector<long long>>& f, int n, bool inverse) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i)) {
                if (!inverse) f[__builtin_popcount(mask)][mask] += f[__builtin_popcount(mask)][mask ^ (1 << i)]; // wrong approach
            }
    // Correct: apply zeta/mobius per rank
}

// Simplified version for understanding
void subsetConvolution(vector<long long>& A, vector<long long>& B, vector<long long>& C, int n) {
    int sz = 1 << n;
    // Rank-stratified arrays: ranked[k][mask]
    vector<vector<long long>> fA(n+1, vector<long long>(sz, 0));
    vector<vector<long long>> fB(n+1, vector<long long>(sz, 0));
    vector<vector<long long>> fC(n+1, vector<long long>(sz, 0));

    for (int mask = 0; mask < sz; mask++) {
        fA[__builtin_popcount(mask)][mask] = A[mask];
        fB[__builtin_popcount(mask)][mask] = B[mask];
    }

    // Zeta transform each rank
    for (int k = 0; k <= n; k++)
        for (int i = 0; i < n; i++)
            for (int mask = 0; mask < sz; mask++)
                if (mask & (1 << i)) {
                    fA[k][mask] += fA[k][mask ^ (1 << i)];
                    fB[k][mask] += fB[k][mask ^ (1 << i)];
                }

    // Pointwise multiply with rank convolution
    for (int mask = 0; mask < sz; mask++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= j; k++)
                fC[j][mask] += fA[k][mask] * fB[j-k][mask];

    // Möbius (inverse zeta) transform each rank
    for (int k = 0; k <= n; k++)
        for (int i = 0; i < n; i++)
            for (int mask = 0; mask < sz; mask++)
                if (mask & (1 << i))
                    fC[k][mask] -= fC[k][mask ^ (1 << i)];

    // Extract result
    for (int mask = 0; mask < sz; mask++)
        C[mask] = fC[__builtin_popcount(mask)][mask];
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SUBSET CONVOLUTION                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 2;
    int sz = 1 << n;
    vector<long long> A = {1, 1, 1, 1};
    vector<long long> B = {1, 1, 1, 1};
    vector<long long> C(sz, 0);

    subsetConvolution(A, B, C, n);

    // Brute force verify
    cout << "\n--- Subset Convolution Result (n=2) ---" << endl;
    for (int S = 0; S < sz; S++) {
        long long brute = 0;
        for (int T = S; ; T = (T-1) & S) {
            brute += A[T] * B[S ^ T];
            if (T == 0) break;
        }
        cout << "  C[" << bitset<2>(S) << "] = " << C[S] << " (brute: " << brute << ")" << endl;
        assert(C[S] == brute);
    }

    cout << "\n✅ Subset convolution verified!" << endl;
    return 0;
}

