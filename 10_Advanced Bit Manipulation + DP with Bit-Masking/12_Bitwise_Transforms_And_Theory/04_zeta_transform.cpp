/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12.04 — ZETA TRANSFORM (Subset Sum / Superset Sum)       ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

ZETA TRANSFORM (Subset Sum):
════════════════════════════
    f̂[mask] = Σ_{sub ⊆ mask} f[sub]

    This is the SOS DP from Chapter 09.01!

    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1<<n); mask++)
            if (mask & (1<<i))
                f[mask] += f[mask ^ (1<<i)];

SUPERSET ZETA TRANSFORM:
════════════════════════
    f̂[mask] = Σ_{mask ⊆ super} f[super]

    for (int i = 0; i < n; i++)
        for (int mask = (1<<n)-1; mask >= 0; mask--)
            if (!(mask & (1<<i)))
                f[mask] += f[mask | (1<<i)];

RELATIONSHIP:
═════════════
    • Subset zeta = "OR-transform" (used in OR convolution)
    • Superset zeta = "AND-transform" (used in AND convolution)
    • XOR uses Walsh-Hadamard (different structure)

TIME: O(n × 2ⁿ)
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void subsetZeta(vector<long long>& f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                f[mask] += f[mask ^ (1 << i)];
}

void supersetZeta(vector<long long>& f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = (1 << n) - 1; mask >= 0; mask--)
            if (!(mask & (1 << i)))
                f[mask] += f[mask | (1 << i)];
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ZETA TRANSFORM                                ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 3;
    vector<long long> f = {1, 2, 3, 4, 5, 6, 7, 8};

    // Subset zeta
    auto subZ = f;
    subsetZeta(subZ, n);
    cout << "\n--- Subset Zeta (f̂[mask] = Σ_{sub⊆mask} f[sub]) ---" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long brute = 0;
        for (int sub = mask; ; sub = (sub-1) & mask) {
            brute += f[sub]; if (sub == 0) break;
        }
        cout << "  f̂[" << bitset<3>(mask) << "] = " << subZ[mask]
             << " (brute: " << brute << ")" << endl;
        assert(subZ[mask] == brute);
    }

    // Superset zeta
    auto supZ = f;
    supersetZeta(supZ, n);
    cout << "\n--- Superset Zeta (f̂[mask] = Σ_{mask⊆super} f[super]) ---" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long brute = 0;
        for (int s = mask; s < (1 << n); s = (s + 1) | mask) {
            brute += f[s];
        }
        cout << "  f̂[" << bitset<3>(mask) << "] = " << supZ[mask]
             << " (brute: " << brute << ")" << endl;
        assert(supZ[mask] == brute);
    }

    cout << "\n✅ Zeta transforms verified!" << endl;
    return 0;
}

