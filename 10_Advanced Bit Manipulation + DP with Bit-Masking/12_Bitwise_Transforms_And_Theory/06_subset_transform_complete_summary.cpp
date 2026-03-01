/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12.06 — SUBSET TRANSFORM (Complete Summary)                ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

COMPLETE SUMMARY OF BITWISE TRANSFORMS:
════════════════════════════════════════

┌────────────────┬──────────────────────────────┬─────────────────────────────┐
│  Convolution   │  Transform (Zeta)            │  Butterfly                  │
├────────────────┼──────────────────────────────┼─────────────────────────────┤
│  OR  (i|j=k)   │  Subset sum                  │  a[i+j+len] += a[i+j]       │
│  AND (i&j=k)   │  Superset sum                │  a[i+j] += a[i+j+len]       │
│  XOR (i^j=k)   │  Walsh-Hadamard              │  (u+v, u-v) butterfly       │
└────────────────┴──────────────────────────────┴─────────────────────────────┘

CONVOLUTION RECIPE:
═══════════════════
    1. Apply forward transform to A and B.
    2. Pointwise multiply: Ĉ[i] = Â[i] × B̂[i].
    3. Apply inverse transform to C.

INVERSION:
══════════
    • OR  inverse: a[i+j+len] -= a[i+j]
    • AND inverse: a[i+j] -= a[i+j+len]
    • XOR inverse: same butterfly as forward, then divide by n

SUBSET CONVOLUTION (disjoint union):
════════════════════════════════════
    C[S] = Σ_{T⊆S} A[T] × B[S\T]  where T ∩ (S\T) = ∅
    → Requires ranked zeta (stratify by popcount) — see Chapter 09.02.

COMPLEXITY:
═══════════
    All transforms: O(n × 2ⁿ)
    Subset convolution: O(n² × 2ⁿ)

WHEN TO USE EACH:
═════════════════
    "Count pairs (i,j) where i⊕j has property P" → XOR convolution
    "Count pairs where i|j = target"              → OR convolution
    "Count pairs where i&j = target"              → AND convolution
    "Sum over all subsets"                         → SOS/Zeta
    "Convert at-least to exactly"                  → Möbius inversion
    "Disjoint subset pairs"                        → Subset convolution

PRACTICE PROBLEMS (COMPLETE LIST):
═══════════════════════════════════
    BEGINNER:
        LeetCode 78: Subsets
        LeetCode 136: Single Number
        LeetCode 191: Number of 1 Bits
        LeetCode 268: Missing Number
        LeetCode 338: Counting Bits

    INTERMEDIATE:
        LeetCode 260: Single Number III
        LeetCode 1371: Longest Vowel Even Substring
        LeetCode 1542: Longest Awesome Substring
        CSES: Apple Division
        CSES: Money Sums (bitset)

    ADVANCED:
        CSES: Hamiltonian Flights
        CSES: Elevator Rides
        CSES: Counting Tilings
        LeetCode 847: Shortest Path Visiting All Nodes
        LeetCode 698: Partition to K Equal Sum Subsets

    GRANDMASTER:
        Codeforces 165E: Compatible Numbers (SOS DP)
        Codeforces 449D: Jzzhu and Numbers (Möbius)
        Codeforces 914G: Sum the Fibonacci (Subset Conv)
        Codeforces 800D: Varying Subsets (Subset Conv)
        SPOJ: XMAX (XOR Basis)
        AtCoder ARC100-E (SOS DP / transforms)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// Unified transform function
enum TransformType { OR_CONV, AND_CONV, XOR_CONV };

void transform(vector<long long>& a, TransformType type, bool inverse) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                long long &u = a[i + j], &v = a[i + j + len];
                switch (type) {
                    case OR_CONV:
                        if (!inverse) v += u; else v -= u;
                        break;
                    case AND_CONV:
                        if (!inverse) u += v; else u -= v;
                        break;
                    case XOR_CONV: {
                        long long x = u, y = v;
                        u = x + y;
                        v = x - y;
                        break;
                    }
                }
            }
        }
    }
    if (type == XOR_CONV && inverse) {
        for (auto& x : a) x /= n;
    }
}

vector<long long> convolve(vector<long long> A, vector<long long> B, TransformType type) {
    int n = A.size();
    transform(A, type, false);
    transform(B, type, false);
    vector<long long> C(n);
    for (int i = 0; i < n; i++) C[i] = A[i] * B[i];
    transform(C, type, true);
    return C;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   SUBSET TRANSFORM — COMPLETE SUMMARY            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<long long> A = {1, 2, 3, 4};
    vector<long long> B = {5, 6, 7, 8};

    cout << "\n  A = {1,2,3,4}, B = {5,6,7,8}" << endl;

    // Test all three convolutions
    string names[] = {"OR", "AND", "XOR"};
    TransformType types[] = {OR_CONV, AND_CONV, XOR_CONV};

    for (int t = 0; t < 3; t++) {
        auto C = convolve(A, B, types[t]);

        // Brute force
        int n = 4;
        vector<long long> brute(n, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int k;
                switch (types[t]) {
                    case OR_CONV: k = i | j; break;
                    case AND_CONV: k = i & j; break;
                    case XOR_CONV: k = i ^ j; break;
                }
                brute[k] += A[i] * B[j];
            }

        cout << "\n  " << names[t] << " convolution: ";
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (C[i] != brute[i]) ok = false;
            cout << C[i] << " ";
        }
        cout << (ok ? "✓" : "✗") << endl;
        for (int i = 0; i < n; i++) assert(C[i] == brute[i]);
    }

    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "  ║  🎉 ALL 12 CHAPTERS COMPLETE!                            ║" << endl;
    cout << "  ║  Bit Manipulation & Bitmask DP: Zero → Grandmaster       ║" << endl;
    cout << "  ╚══════════════════════════════════════════════════════════╝" << endl;

    cout << "\n✅ All transforms verified! Course complete!" << endl;
    return 0;
}

