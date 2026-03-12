/*
 * ============================================================================
 *  📘 03 — Lucas Theorem
 * ============================================================================
 *
 *  STATEMENT: For prime p:
 *    C(n, r) mod p = Π C(n_i, r_i) mod p
 *    where n = n_k...n_1n_0 in base p, r = r_k...r_1r_0 in base p
 *
 *  PROOF:
 *    By Fermat: (1+x)^p ≡ 1 + x^p (mod p)
 *    Expanding (1+x)^n where n = q*p + r:
 *    (1+x)^n = ((1+x)^p)^q × (1+x)^r ≡ (1+x^p)^q × (1+x)^r (mod p)
 *    Comparing coefficients of x^k gives the result by induction. ∎
 *
 *  USE CASE: C(n, r) mod p where p is SMALL (≤ 10^6) but n can be huge (≤ 10^18)
 *
 *  TIME: O(p + log_p(n)) per query
 *
 *  DRY RUN: C(10, 3) mod 3
 *    10 in base 3: 101
 *    3 in base 3:  010
 *    C(10,3) mod 3 = C(1,0) × C(0,1) × C(1,0) = 1 × 0 × 1 = 0
 *    Check: C(10,3) = 120, 120 mod 3 = 0 ✓
 *
 *  Reference: https://cp-algorithms.com/combinatorics/binomial-coefficients.html
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())

// ============================================================================
//  📌 LUCAS THEOREM IMPLEMENTATION
// ============================================================================

struct Lucas {
    int p;
    vec<vec<i64>> C_table;  // C_table[n][r] = C(n,r) mod p for 0 ≤ n,r < p

    Lucas(int p) : p(p), C_table(p, vec<i64>(p, 0)) {
        // Precompute C(n, r) mod p for n, r < p using Pascal's triangle
        for (int n = 0; n < p; n++) {
            C_table[n][0] = 1;
            for (int r = 1; r <= n; r++) {
                C_table[n][r] = (C_table[n-1][r-1] + C_table[n-1][r]) % p;
            }
        }
    }

    // C(n, r) mod p using Lucas theorem
    i64 C(i64 n, i64 r) const {
        if (r < 0 || r > n) return 0;

        i64 result = 1;
        while (n > 0 || r > 0) {
            int ni = n % p;
            int ri = r % p;
            if (ri > ni) return 0;  // C(ni, ri) = 0
            result = result * C_table[ni][ri] % p;
            n /= p;
            r /= p;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Lucas Theorem ===" << nl << nl;

    // Example: p = 3
    cout << "--- C(n, r) mod 3 ---" << nl;
    Lucas lucas3(3);
    for (auto [n, r] : vec<pair<i64,i64>>{{10,3},{100,50},{1000000000000LL,500000000000LL},{7,2},{5,2}}) {
        cout << "C(" << n << ", " << r << ") mod 3 = " << lucas3.C(n, r) << nl;
    }

    // Example: p = 7
    cout << nl << "--- C(n, r) mod 7 ---" << nl;
    Lucas lucas7(7);
    for (auto [n, r] : vec<pair<i64,i64>>{{10,3},{50,25},{100,50},{1000000000LL,42}}) {
        cout << "C(" << n << ", " << r << ") mod 7 = " << lucas7.C(n, r) << nl;
    }

    // Dry run trace
    cout << nl << "--- Dry Run: C(10, 3) mod 3 ---" << nl;
    {
        i64 n = 10, r = 3;
        int p = 3;
        cout << "10 in base 3: ";
        vec<int> digits_n, digits_r;
        i64 tn = n, tr = r;
        while (tn > 0) { digits_n.push_back(tn % p); tn /= p; }
        while (tr > 0) { digits_r.push_back(tr % p); tr /= p; }
        while (sz(digits_r) < sz(digits_n)) digits_r.push_back(0);

        for (int i = sz(digits_n) - 1; i >= 0; i--) cout << digits_n[i];
        cout << nl << " 3 in base 3: ";
        for (int i = sz(digits_r) - 1; i >= 0; i--) cout << digits_r[i];
        cout << nl;

        cout << "Product: ";
        for (int i = sz(digits_n) - 1; i >= 0; i--) {
            cout << "C(" << digits_n[i] << "," << digits_r[i] << ")";
            if (i > 0) cout << " × ";
        }
        cout << " = " << lucas3.C(10, 3) << nl;
    }

    // Verification: compare with direct computation for small values
    cout << nl << "--- Verification: p=5, n≤20 ---" << nl;
    Lucas lucas5(5);
    // Direct Pascal's triangle
    vec<vec<i64>> pascal(21, vec<i64>(21, 0));
    pascal[0][0] = 1;
    for (int n = 1; n <= 20; n++) {
        pascal[n][0] = 1;
        for (int r = 1; r <= n; r++)
            pascal[n][r] = pascal[n-1][r-1] + pascal[n-1][r];
    }
    bool all_ok = true;
    for (int n = 0; n <= 20; n++) {
        for (int r = 0; r <= n; r++) {
            if (lucas5.C(n, r) != pascal[n][r] % 5) {
                cout << "MISMATCH at C(" << n << "," << r << ")" << nl;
                all_ok = false;
            }
        }
    }
    if (all_ok) cout << "All values match! ✓" << nl;

    return 0;
}

