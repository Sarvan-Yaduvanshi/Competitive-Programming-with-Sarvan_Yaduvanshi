/*
 * ============================================================================
 *  📘 04 — Catalan Numbers & Counting Formulas
 * ============================================================================
 *
 *  CATALAN NUMBERS:
 *    C_n = C(2n, n) / (n+1) = C(2n, n) - C(2n, n+1)
 *    C_0=1, C_1=1, C_2=2, C_3=5, C_4=14, C_5=42, ...
 *
 *  APPLICATIONS:
 *    - Balanced parentheses with n pairs
 *    - Binary trees with n+1 leaves
 *    - Monotonic lattice paths not crossing diagonal
 *    - Triangulations of (n+2)-gon
 *    - Stack-sortable permutations
 *
 *  PROOF (Reflection/André):
 *    Bad paths (crossing y=-1) biject to paths ending at (2n,-2).
 *    Count of bad paths = C(2n, n-1).
 *    Good = C(2n,n) - C(2n,n-1) = C(2n,n)/(n+1). ∎
 *
 *  STARS AND BARS:
 *    n identical balls into k boxes: C(n+k-1, k-1)
 *    With each box ≥ 1: C(n-1, k-1)
 *
 *  DERANGEMENTS:
 *    D(n) = n! × Σ_{i=0}^{n} (-1)^i / i! ≈ n!/e
 *    D(n) = (n-1)(D(n-1) + D(n-2))
 *
 *  STIRLING NUMBERS (2nd kind):
 *    S(n,k) = ways to partition n elements into k non-empty subsets
 *    S(n,k) = k × S(n-1,k) + S(n-1,k-1)
 *
 *  Reference: https://cp-algorithms.com/combinatorics/catalan-numbers.html
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
template<class T> using vvec = vector<vector<T>>;
#define nl '\n'
#define sz(x) ((int)(x).size())

constexpr i64 MOD = 1'000'000'007LL;

i64 binpow(i64 b, i64 e, i64 m) {
    i64 r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}

struct Combo {
    vec<i64> fact, ifact;
    i64 mod;
    Combo(int n, i64 m) : mod(m), fact(n+1), ifact(n+1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % mod;
        ifact[n] = binpow(fact[n], mod - 2, mod);
        for (int i = n-1; i >= 0; i--) ifact[i] = ifact[i+1] * (i+1) % mod;
    }
    i64 C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] % mod * ifact[r] % mod * ifact[n-r] % mod;
    }
    i64 catalan(int n) { return (C(2*n, n) - C(2*n, n+1) + mod) % mod; }
    i64 stars_bars(int n, int k) { return C(n + k - 1, k - 1); }
};

// Derangements mod p
vec<i64> derangement_table(int n, i64 mod) {
    vec<i64> D(n + 1);
    D[0] = 1; D[1] = 0;
    for (int i = 2; i <= n; i++)
        D[i] = (i - 1) % mod * ((D[i-1] + D[i-2]) % mod) % mod;
    return D;
}

// Stirling numbers (2nd kind) S(n, k)
vvec<i64> stirling2_table(int n, i64 mod) {
    vvec<i64> S(n + 1, vec<i64>(n + 1, 0));
    S[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (j * S[i-1][j] % mod + S[i-1][j-1]) % mod;
    return S;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Combo combo(2000000, MOD);

    cout << "=== Catalan & Counting ===" << nl << nl;

    // Catalan numbers
    cout << "--- Catalan Numbers ---" << nl;
    for (int n = 0; n <= 15; n++)
        cout << "C_" << n << " = " << combo.catalan(n) << nl;

    // Stars and bars
    cout << nl << "--- Stars and Bars ---" << nl;
    cout << "5 balls, 3 boxes: " << combo.stars_bars(5, 3) << nl;
    cout << "10 balls, 4 boxes: " << combo.stars_bars(10, 4) << nl;
    cout << "100 balls, 10 boxes: " << combo.stars_bars(100, 10) << nl;

    // Derangements
    cout << nl << "--- Derangements D(n) ---" << nl;
    auto D = derangement_table(15, MOD);
    for (int n = 0; n <= 15; n++)
        cout << "D(" << n << ") = " << D[n] << nl;

    // Stirling 2nd kind
    cout << nl << "--- Stirling Numbers S(n,k) ---" << nl;
    auto S = stirling2_table(8, MOD);
    for (int n = 0; n <= 8; n++) {
        for (int k = 0; k <= n; k++) cout << S[n][k] << " ";
        cout << nl;
    }

    return 0;
}

