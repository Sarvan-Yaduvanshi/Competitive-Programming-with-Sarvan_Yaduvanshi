/*
 * ============================================================================
 *  📘 03 — Derangements via Inclusion-Exclusion
 * ============================================================================
 *
 *  DERANGEMENT: A permutation where NO element is in its original position.
 *
 *  FORMULA: D(n) = n! × Σ_{i=0}^{n} (-1)^i / i!
 *
 *  PROOF (via IE):
 *    Let Aᵢ = {perms where element i is fixed}.
 *    |Aᵢ| = (n-1)!, |Aᵢ ∩ Aⱼ| = (n-2)!, etc.
 *    D(n) = n! - |A₁ ∪ ... ∪ Aₙ|
 *         = n! - C(n,1)(n-1)! + C(n,2)(n-2)! - ...
 *         = Σ (-1)^k × C(n,k) × (n-k)! = Σ (-1)^k × n!/k!
 *         = n! × Σ (-1)^k / k!  ∎
 *
 *  RECURRENCE: D(n) = (n-1) × (D(n-1) + D(n-2))
 *  Also: D(n) = n × D(n-1) + (-1)^n
 *
 *  APPROXIMATION: D(n) ≈ n!/e (rounded to nearest integer)
 *
 *  DRY RUN: D(4)
 *    D(4) = 4! × (1/0! - 1/1! + 1/2! - 1/3! + 1/4!)
 *         = 24 × (1 - 1 + 0.5 - 1/6 + 1/24)
 *         = 24 × 0.375 = 9
 *    {2143, 2341, 2413, 3142, 3412, 3421, 4123, 4312, 4321} → 9 ✓
 *
 *  CSES: Christmas Party (https://cses.fi/problemset/task/1717)
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())

constexpr i64 MOD = 1'000'000'007LL;

i64 binpow(i64 b, i64 e, i64 m) {
    i64 r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

// ============================================================================
//  📌 DERANGEMENTS via recurrence: D(n) = (n-1)(D(n-1) + D(n-2))
// ============================================================================

vec<i64> derangement_table(int n, i64 mod) {
    vec<i64> D(n + 1);
    D[0] = 1;
    if (n >= 1) D[1] = 0;
    for (int i = 2; i <= n; i++) {
        D[i] = (i - 1) % mod * ((D[i-1] + D[i-2]) % mod) % mod;
    }
    return D;
}

// ============================================================================
//  📌 CSES Christmas Party solver (just derangement D(n) mod 10^9+7)
// ============================================================================

void solve() {
    int n;
    cin >> n;
    auto D = derangement_table(n, MOD);
    cout << D[n] << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Derangements ===" << nl << nl;

    auto D = derangement_table(20, MOD);

    cout << "--- D(n) for n = 0..15 ---" << nl;
    for (int n = 0; n <= 15; n++) {
        cout << "D(" << n << ") = " << D[n] << nl;
    }
    // Expected: 1, 0, 1, 2, 9, 44, 265, 1854, 14833, ...

    // Brute verify D(4) = 9
    cout << nl << "--- Brute force D(4) ---" << nl;
    int cnt = 0;
    vec<int> perm = {1, 2, 3, 4};
    do {
        bool derangement = true;
        for (int i = 0; i < 4; i++) if (perm[i] == i + 1) derangement = false;
        if (derangement) cnt++;
    } while (next_permutation(perm.begin(), perm.end()));
    cout << "Brute D(4) = " << cnt << (cnt == 9 ? " ✓" : " ✗") << nl;

    // Ratio D(n)/n! → 1/e
    cout << nl << "--- D(n)/n! → 1/e ≈ 0.367879 ---" << nl;
    double fact = 1;
    for (int n = 1; n <= 10; n++) {
        fact *= n;
        cout << "n=" << n << ": D(n)/n! = " << D[n] / fact << nl;
    }

    return 0;
}

