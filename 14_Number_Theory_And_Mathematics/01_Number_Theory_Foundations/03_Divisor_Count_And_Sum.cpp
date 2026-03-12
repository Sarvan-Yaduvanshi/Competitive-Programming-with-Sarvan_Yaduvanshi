/*
 * ============================================================================
 *  📘 03 — Divisor Count τ(n) and Divisor Sum σ(n)
 * ============================================================================
 *
 *  Given n = p1^a1 × p2^a2 × ... × pk^ak:
 *
 *  NUMBER OF DIVISORS:
 *    τ(n) = (a1+1)(a2+1)...(ak+1)
 *
 *  SUM OF DIVISORS:
 *    σ(n) = Π [(pi^(ai+1) - 1) / (pi - 1)]
 *
 *  PRODUCT OF DIVISORS:
 *    Π d|n  d = n^(τ(n)/2)
 *
 *  These are MULTIPLICATIVE FUNCTIONS:
 *    If gcd(a,b) = 1, then f(ab) = f(a) × f(b)
 *
 *  Reference: https://cp-algorithms.com/algebra/divisors.html
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
//  📌 METHOD 1: Compute τ(n) directly — O(√n)
// ============================================================================
//  Count divisors by iterating up to √n.
//  Each pair (d, n/d) contributes 2, except when d = n/d.
// ============================================================================

i64 count_divisors(i64 n) {
    i64 cnt = 0;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            cnt++;                    // d is a divisor
            if (d != n / d) cnt++;    // n/d is also a divisor
        }
    }
    return cnt;
}

// ============================================================================
//  📌 METHOD 2: Compute σ(n) directly — O(√n)
// ============================================================================

i64 sum_divisors(i64 n) {
    i64 sum = 0;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            sum += d;
            if (d != n / d) sum += n / d;
        }
    }
    return sum;
}

// ============================================================================
//  📌 METHOD 3: Via Prime Factorization — O(√n)
// ============================================================================
//  More efficient for computing both τ and σ simultaneously.
//
//  DRY RUN: n = 72 = 2³ × 3²
//    τ(72) = (3+1)(2+1) = 12
//    σ(72) = (2⁴-1)/(2-1) × (3³-1)/(3-1) = 15 × 13 = 195
//
//  Verification: Divisors of 72 = {1,2,3,4,6,8,9,12,18,24,36,72}
//    Count = 12 ✓
//    Sum = 1+2+3+4+6+8+9+12+18+24+36+72 = 195 ✓
// ============================================================================

pair<i64, i64> count_and_sum_divisors(i64 n) {
    i64 tau = 1, sigma = 1;

    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            i64 a = 0;
            i64 geo = 1, pw = 1;  // geometric sum: 1 + p + p² + ...
            while (n % p == 0) {
                n /= p;
                a++;
                pw *= p;
                geo += pw;
            }
            tau *= (a + 1);
            sigma *= geo;
        }
    }
    if (n > 1) {
        tau *= 2;          // prime factor with exponent 1: (1+1) = 2
        sigma *= (1 + n);  // geometric sum: 1 + n
    }
    return {tau, sigma};
}

// ============================================================================
//  📌 METHOD 4: Sieve of Divisor Count — O(n log n)
// ============================================================================
//  Precompute τ(i) for all i from 1 to n.
//  For each d, add 1 to all multiples of d.
// ============================================================================

vec<int> sieve_divisor_count(int n) {
    vec<int> tau(n + 1, 0);
    for (int d = 1; d <= n; d++) {
        for (int multiple = d; multiple <= n; multiple += d) {
            tau[multiple]++;
        }
    }
    return tau;
}

// ============================================================================
//  📌 METHOD 5: Sieve of Divisor Sum — O(n log n)
// ============================================================================

vec<i64> sieve_divisor_sum(int n) {
    vec<i64> sigma(n + 1, 0);
    for (int d = 1; d <= n; d++) {
        for (int multiple = d; multiple <= n; multiple += d) {
            sigma[multiple] += d;
        }
    }
    return sigma;
}

// ============================================================================
//  📌 HIGHLY COMPOSITE NUMBERS
// ============================================================================
//  Numbers with more divisors than any smaller number.
//  1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, ...
//  These are important in CP for worst-case analysis.
//
//  Key fact: The maximum τ(n) for n ≤ N:
//    N ≤ 10^6:  τ ≤ 240
//    N ≤ 10^9:  τ ≤ 1344
//    N ≤ 10^18: τ ≤ 103680
// ============================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    cout << "=== Divisor Count and Sum ===" << nl << nl;

    // Single number tests
    cout << "--- Single Number Tests ---" << nl;
    vec<i64> tests = {1, 6, 12, 28, 36, 72, 100, 360, 720};

    for (i64 n : tests) {
        auto [tau, sigma] = count_and_sum_divisors(n);
        i64 tau2 = count_divisors(n);
        i64 sigma2 = sum_divisors(n);

        cout << "n=" << n << ": τ=" << tau << " σ=" << sigma;
        assert(tau == tau2 && sigma == sigma2);

        // Check if perfect number (σ(n) - n == n, i.e., σ(n) == 2n)
        if (sigma == 2 * n) cout << "  [PERFECT NUMBER!]";
        cout << nl;
    }

    // Sieve test
    cout << nl << "--- Sieve: Most Divisors up to 1000 ---" << nl;
    vec<int> tau_sieve = sieve_divisor_count(1000);
    int max_tau = 0, max_n = 0;
    for (int i = 1; i <= 1000; i++) {
        if (tau_sieve[i] > max_tau) {
            max_tau = tau_sieve[i];
            max_n = i;
        }
    }
    cout << "Most divisors: " << max_n << " has " << max_tau << " divisors" << nl;

    // Print highly composite numbers up to 1000
    cout << nl << "--- Highly Composite Numbers up to 1000 ---" << nl;
    int record = 0;
    for (int i = 1; i <= 1000; i++) {
        if (tau_sieve[i] > record) {
            record = tau_sieve[i];
            cout << i << " has " << record << " divisors" << nl;
        }
    }

    return 0;
}

