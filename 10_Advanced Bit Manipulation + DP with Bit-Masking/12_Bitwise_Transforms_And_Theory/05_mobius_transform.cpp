/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 12.05 — MÖBIUS TRANSFORM (Inverse of Zeta)               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

MÖBIUS INVERSION (Subset Lattice):
══════════════════════════════════
    If g[mask] = Σ_{sub⊆mask} f[sub]   (Zeta)
    Then f[mask] = Σ_{sub⊆mask} (-1)^|mask\sub| × g[sub]   (Möbius)

ALGORITHM (reverse the Zeta transform):
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1<<n); mask++)
            if (mask & (1<<i))
                f[mask] -= f[mask ^ (1<<i)];

SUPERSET MÖBIUS:
    for (int i = 0; i < n; i++)
        for (int mask = (1<<n)-1; mask >= 0; mask--)
            if (!(mask & (1<<i)))
                f[mask] -= f[mask | (1<<i)];

RELATIONSHIP TO INCLUSION-EXCLUSION:
═════════════════════════════════════
    Möbius inversion IS inclusion-exclusion on the subset lattice!
    The (-1)^|S\T| signs are exactly the inclusion-exclusion coefficients.

TIME: O(n × 2ⁿ) — same as Zeta

PRACTICE PROBLEMS:
══════════════════
    Codeforces: 449D, 914G
    Problems involving "exactly k" from "at least k" via inclusion-exclusion
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
using namespace std;

void subsetZeta(vector<long long>& f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                f[mask] += f[mask ^ (1 << i)];
}

void subsetMobius(vector<long long>& f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask & (1 << i))
                f[mask] -= f[mask ^ (1 << i)];
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   MÖBIUS TRANSFORM                              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    int n = 3;
    vector<long long> original = {1, 2, 3, 4, 5, 6, 7, 8};

    // Apply Zeta then Möbius → should get original back
    auto f = original;
    cout << "\n--- Original: ";
    for (auto x : f) cout << x << " ";
    cout << endl;

    subsetZeta(f, n);
    cout << "--- After Zeta: ";
    for (auto x : f) cout << x << " ";
    cout << endl;

    subsetMobius(f, n);
    cout << "--- After Möbius (inverse): ";
    for (auto x : f) cout << x << " ";
    cout << endl;

    for (int i = 0; i < (1 << n); i++)
        assert(f[i] == original[i]);
    cout << "--- Matches original ✓" << endl;

    // Application: "at least" to "exactly"
    cout << "\n--- Application: At-Least to Exactly ---" << endl;
    // g[mask] = count of elements that have AT LEAST the bits in mask set
    // f[mask] = count of elements that have EXACTLY the bits in mask set
    // g = superset zeta of f, so f = superset Möbius of g

    vector<int> arr = {0b111, 0b110, 0b101, 0b100, 0b010};
    vector<long long> atLeast(1 << n, 0);
    for (int x : arr) atLeast[x]++;

    // Apply superset zeta to get "at least" counts
    for (int i = 0; i < n; i++)
        for (int mask = (1<<n)-1; mask >= 0; mask--)
            if (!(mask & (1 << i)))
                atLeast[mask] += atLeast[mask | (1 << i)];

    cout << "  Elements: {111, 110, 101, 100, 010}" << endl;
    cout << "  At-least counts:" << endl;
    for (int mask = 0; mask < (1 << n); mask++) {
        cout << "    mask " << bitset<3>(mask) << ": " << atLeast[mask] << " elements" << endl;
    }

    cout << "\n✅ Möbius transform verified!" << endl;
    return 0;
}

