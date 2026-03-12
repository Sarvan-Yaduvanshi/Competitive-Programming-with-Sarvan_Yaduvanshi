/*
 * ============================================================================
 *  📘 02 — Pascal's Triangle & Binomial Properties
 * ============================================================================
 *
 *  PASCAL'S IDENTITY: C(n,r) = C(n-1,r-1) + C(n-1,r)
 *
 *  PROOF: n-th element is either chosen (pick r-1 from n-1)
 *         or not chosen (pick r from n-1). ∎
 *
 *  PROPERTIES:
 *    1. Row sum: Σ C(n,r) = 2^n        (set x=1 in (1+x)^n)
 *    2. Alternating: Σ(-1)^r C(n,r) = 0 (set x=-1)
 *    3. Symmetry: C(n,r) = C(n,n-r)
 *    4. Vandermonde: Σ C(m,k)C(n,r-k) = C(m+n,r)
 *    5. Hockey stick: Σ_{i=r}^{n} C(i,r) = C(n+1,r+1)
 *
 *  USE IN CP: build Pascal's triangle up to N for small N (≤5000).
 *  For large N with prime mod, use factorial + inverse factorial.
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

constexpr i64 MOD = 1'000'000'007LL;

// ============================================================================
//  📌 PASCAL'S TRIANGLE (mod p)
// ============================================================================

vvec<i64> build_pascal(int n, i64 mod) {
    vvec<i64> C(n + 1, vec<i64>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
        }
    }
    return C;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Pascal's Triangle ===" << nl << nl;

    auto C = build_pascal(15, MOD);

    // Print triangle
    cout << "--- Pascal's Triangle (n=0..10) ---" << nl;
    for (int n = 0; n <= 10; n++) {
        for (int r = 0; r <= n; r++) cout << C[n][r] << " ";
        cout << nl;
    }

    // Verify row sum = 2^n
    cout << nl << "--- Row Sums (should be 2^n) ---" << nl;
    for (int n = 0; n <= 10; n++) {
        i64 sum = 0;
        for (int r = 0; r <= n; r++) sum += C[n][r];
        cout << "n=" << n << ": " << sum << " = 2^" << n << "=" << (1LL << n)
             << (sum == (1LL << n) ? " ✓" : " ✗") << nl;
    }

    // Verify alternating sum = 0 (n > 0)
    cout << nl << "--- Alternating Sums (should be 0 for n>0) ---" << nl;
    for (int n = 1; n <= 10; n++) {
        i64 sum = 0;
        for (int r = 0; r <= n; r++) {
            sum += (r % 2 == 0 ? 1 : -1) * C[n][r];
        }
        cout << "n=" << n << ": " << sum << (sum == 0 ? " ✓" : " ✗") << nl;
    }

    // Hockey stick identity: C(r,r) + C(r+1,r) + ... + C(n,r) = C(n+1,r+1)
    cout << nl << "--- Hockey Stick: Σ C(i,2) for i=2..8 = C(9,3) ---" << nl;
    {
        i64 sum = 0;
        for (int i = 2; i <= 8; i++) sum += C[i][2];
        cout << "Sum = " << sum << ", C(9,3) = " << C[9][3]
             << (sum == C[9][3] ? " ✓" : " ✗") << nl;
    }

    // Vandermonde: Σ C(3,k)×C(4,3-k) = C(7,3)
    cout << nl << "--- Vandermonde: Σ C(3,k)×C(4,3-k) = C(7,3) ---" << nl;
    {
        i64 sum = 0;
        for (int k = 0; k <= 3; k++) sum += C[3][k] * C[4][3-k];
        cout << "Sum = " << sum << ", C(7,3) = " << C[7][3]
             << (sum == C[7][3] ? " ✓" : " ✗") << nl;
    }

    return 0;
}

