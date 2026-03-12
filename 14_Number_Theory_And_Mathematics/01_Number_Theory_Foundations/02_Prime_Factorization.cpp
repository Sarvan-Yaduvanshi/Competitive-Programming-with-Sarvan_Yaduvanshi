/*
 * ============================================================================
 *  📘 02 — Prime Factorization (Trial Division)
 * ============================================================================
 *
 *  FUNDAMENTAL THEOREM OF ARITHMETIC:
 *    Every integer n > 1 has a UNIQUE representation:
 *      n = p1^a1 × p2^a2 × ... × pk^ak
 *    where p1 < p2 < ... < pk are primes, ai ≥ 1.
 *
 *  ALGORITHM: Trial Division
 *    - Try dividing by d = 2, 3, 4, ..., √n
 *    - For each d, divide out all factors of d
 *    - If n > 1 after loop, n itself is a prime factor
 *
 *  TIME: O(√n)
 *  SPACE: O(log n) — at most log₂(n) prime factors
 *
 *  DRY RUN: n = 360
 *    d=2: 360→180→90→45  → {2:3}
 *    d=3: 45→15→5         → {2:3, 3:2}
 *    d=4: 4² = 16 > 5     → STOP
 *    n=5 > 1              → {2:3, 3:2, 5:1}
 *    Answer: 360 = 2³ × 3² × 5¹ ✓
 *
 *  Reference: https://cp-algorithms.com/algebra/factorization.html
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
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }
#define nl '\n'

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// ============================================================================
//  📌 METHOD 1: Basic Trial Division — O(√n)
// ============================================================================
//  Returns vector of (prime, exponent) pairs.
//
//  WHY IT WORKS:
//    When we reach divisor d, all primes < d have already been divided out.
//    So if d divides n at this point, d must be prime.
//    (If d were composite, say d = a*b with a < d, then a would have
//     already been divided out, contradicting d | n.)
// ============================================================================

vec<pll> factorize_basic(i64 n) {
    vec<pll> factors;
    for (i64 d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            i64 cnt = 0;
            while (n % d == 0) {
                n /= d;
                cnt++;
            }
            factors.pb({d, cnt});
        }
    }
    if (n > 1) {
        factors.pb({n, 1});
    }
    return factors;
}

// ============================================================================
//  📌 METHOD 2: Optimized Trial Division — O(√n) with 2,3 skip
// ============================================================================
//  Observation: All primes > 3 are of the form 6k ± 1.
//  Proof: Any integer is 6k, 6k+1, 6k+2, 6k+3, 6k+4, or 6k+5.
//    - 6k: divisible by 6
//    - 6k+2, 6k+4: divisible by 2
//    - 6k+3: divisible by 3
//    Only 6k+1 and 6k+5 (= 6(k+1)-1) can be prime.
//
//  So we check d = 2, 3, then d = 5, 7, 11, 13, 17, 19, ...
//  (alternating +2, +4)
// ============================================================================

vec<pll> factorize_optimized(i64 n) {
    vec<pll> factors;

    // Handle factor 2
    if (n % 2 == 0) {
        i64 cnt = 0;
        while (n % 2 == 0) { n /= 2; cnt++; }
        factors.pb({2, cnt});
    }

    // Handle factor 3
    if (n % 3 == 0) {
        i64 cnt = 0;
        while (n % 3 == 0) { n /= 3; cnt++; }
        factors.pb({3, cnt});
    }

    // Check 6k ± 1
    for (i64 d = 5; d * d <= n; d += 6) {
        if (n % d == 0) {
            i64 cnt = 0;
            while (n % d == 0) { n /= d; cnt++; }
            factors.pb({d, cnt});
        }
        if (n % (d + 2) == 0) {
            i64 cnt = 0;
            while (n % (d + 2) == 0) { n /= (d + 2); cnt++; }
            factors.pb({d + 2, cnt});
        }
    }

    if (n > 1) factors.pb({n, 1});
    return factors;
}

// ============================================================================
//  📌 UTILITY: Print factorization nicely
// ============================================================================

void print_factorization(i64 n, const vec<pll>& factors) {
    cout << n << " = ";
    for (int i = 0; i < sz(factors); i++) {
        if (i > 0) cout << " × ";
        cout << factors[i].fi;
        if (factors[i].se > 1) cout << "^" << factors[i].se;
    }
    cout << nl;
}

// ============================================================================
//  📌 APPLICATIONS
// ============================================================================

// Count of divisors from prime factorization
// τ(n) = Π(ai + 1)
i64 divisor_count(const vec<pll>& factors) {
    i64 result = 1;
    for (auto [p, a] : factors) result *= (a + 1);
    return result;
}

// Sum of divisors from prime factorization
// σ(n) = Π((p^(a+1) - 1) / (p - 1))
i64 divisor_sum(const vec<pll>& factors) {
    i64 result = 1;
    for (auto [p, a] : factors) {
        i64 geo_sum = 1, pw = 1;
        for (int i = 0; i < a; i++) {
            pw *= p;
            geo_sum += pw;
        }
        result *= geo_sum;
    }
    return result;
}

// Product of divisors
// Product = n^(τ(n)/2)
// (computed using modular exponentiation if needed)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    cout << "=== Prime Factorization (Trial Division) ===" << nl << nl;

    // Test cases with dry run
    vec<i64> test = {2, 12, 36, 84, 100, 360, 1000000007LL, 999999937LL, 720720};

    for (i64 n : test) {
        vec<pll> factors = factorize_optimized(n);
        print_factorization(n, factors);
        cout << "  τ(" << n << ") = " << divisor_count(factors)
             << ", σ(" << n << ") = " << divisor_sum(factors) << nl;
    }

    cout << nl << "=== Detailed Dry Run: n = 360 ===" << nl;
    {
        i64 n = 360;
        cout << "Step-by-step:" << nl;
        i64 temp = n;

        // Factor 2
        int cnt = 0;
        while (temp % 2 == 0) { temp /= 2; cnt++; cout << "  " << temp * 2 << " / 2 = " << temp << nl; }
        cout << "  Factor 2 appears " << cnt << " times" << nl;

        // Factor 3
        cnt = 0;
        while (temp % 3 == 0) { temp /= 3; cnt++; cout << "  " << temp * 3 << " / 3 = " << temp << nl; }
        cout << "  Factor 3 appears " << cnt << " times" << nl;

        // Factor 5
        cnt = 0;
        while (temp % 5 == 0) { temp /= 5; cnt++; cout << "  " << temp * 5 << " / 5 = " << temp << nl; }
        cout << "  Factor 5 appears " << cnt << " times" << nl;

        cout << "  Remaining: " << temp << " (should be 1)" << nl;
        cout << "  360 = 2^3 × 3^2 × 5^1" << nl;
        cout << "  τ(360) = 4 × 3 × 2 = 24" << nl;
        cout << "  σ(360) = 15 × 13 × 6 = 1170" << nl;
    }

    return 0;
}

