/*
 * ============================================================================
 *  📘 01 — Divisibility & Integer Properties
 * ============================================================================
 *  Topics:
 *    - Division Algorithm: a = d*q + r
 *    - Divisibility check
 *    - Floor and Ceiling in C++
 *    - Finding all divisors of n
 *    - Divisibility rules implementation
 *
 *  Complexity:
 *    - Divisibility check: O(1)
 *    - Find all divisors: O(√n)
 *
 *  Reference: cp-algorithms.com/algebra/
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
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

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
//  📌 CONCEPT 1: Division Algorithm
// ============================================================================
//  For any integer a and positive integer d:
//      a = d * q + r,  where 0 <= r < d
//
//  q = a / d  (quotient)
//  r = a % d  (remainder)
//
//  CAUTION in C++:
//    -7 / 3 = -2  (truncated toward zero, NOT floor)
//    -7 % 3 = -1  (can be negative!)
//
//  To get proper mathematical mod (always non-negative):
//    ((a % d) + d) % d
// ============================================================================

void demo_division_algorithm() {
    cout << "=== Division Algorithm ===" << nl;

    // Positive case
    int a = 17, d = 5;
    int q = a / d, r = a % d;
    cout << a << " = " << d << " * " << q << " + " << r << nl;
    // Output: 17 = 5 * 3 + 2

    // Negative case — C++ truncates toward zero
    a = -17; d = 5;
    q = a / d; r = a % d;
    cout << a << " = " << d << " * " << q << " + " << r << nl;
    // Output: -17 = 5 * -3 + -2  (mathematical remainder should be 3)

    // Correct mathematical modulo
    int math_r = ((a % d) + d) % d;
    int math_q = (a - math_r) / d;
    cout << "Mathematical: " << a << " = " << d << " * " << math_q << " + " << math_r << nl;
    // Output: -17 = 5 * -4 + 3

    cout << nl;
}

// ============================================================================
//  📌 CONCEPT 2: Ceiling Division
// ============================================================================
//  ceil(a / b) for positive a, b:
//    Method 1: (a + b - 1) / b     ← most common in CP
//    Method 2: (a - 1) / b + 1     ← works when a >= 1
// ============================================================================

void demo_ceiling_division() {
    cout << "=== Ceiling Division ===" << nl;

    i64 a = 7, b = 3;
    i64 floor_div = a / b;
    i64 ceil_div = (a + b - 1) / b;

    cout << "floor(" << a << "/" << b << ") = " << floor_div << nl;  // 2
    cout << "ceil(" << a << "/" << b << ") = " << ceil_div << nl;    // 3

    // More examples
    for (auto [x, y] : vector<pll>{{10,3},{10,5},{10,2},{1,7}}) {
        cout << "ceil(" << x << "/" << y << ") = " << (x + y - 1) / y << nl;
    }
    cout << nl;
}

// ============================================================================
//  📌 CONCEPT 3: Find All Divisors of n — O(√n)
// ============================================================================
//  Key Insight: If d | n, then (n/d) | n too.
//  So divisors come in pairs (d, n/d) where d ≤ √n.
//
//  DRY RUN for n = 36:
//    d=1: 36%1==0 → add 1, 36     divisors = {1, 36}
//    d=2: 36%2==0 → add 2, 18     divisors = {1, 2, 18, 36}
//    d=3: 36%3==0 → add 3, 12     divisors = {1, 2, 3, 12, 18, 36}
//    d=4: 36%4==0 → add 4, 9      divisors = {1, 2, 3, 4, 9, 12, 18, 36}
//    d=5: 36%5!=0 → skip
//    d=6: 36%6==0, 6*6=36 → add 6 only (avoid duplicate)
//    Final: {1, 2, 3, 4, 6, 9, 12, 18, 36} → 9 divisors
// ============================================================================

vec<i64> get_divisors(i64 n) {
    vec<i64> divisors;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divisors.pb(d);
            if (d != n / d) {
                divisors.pb(n / d);
            }
        }
    }
    sort(all(divisors));
    return divisors;
}

void demo_divisors() {
    cout << "=== Find All Divisors ===" << nl;

    for (i64 n : {1LL, 12LL, 36LL, 100LL, 360LL}) {
        vec<i64> divs = get_divisors(n);
        cout << "Divisors of " << n << " (" << sz(divs) << "): ";
        for (auto d : divs) cout << d << " ";
        cout << nl;
    }
    cout << nl;
}

// ============================================================================
//  📌 CONCEPT 4: Perfect Numbers
// ============================================================================
//  A perfect number equals the sum of its proper divisors.
//  Example: 6 = 1 + 2 + 3, 28 = 1 + 2 + 4 + 7 + 14
// ============================================================================

bool is_perfect(i64 n) {
    if (n <= 1) return false;
    i64 sum = 0;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            sum += d;
            if (d != n / d && n / d != n) {
                sum += n / d;
            }
        }
    }
    return sum == n;
}

void demo_perfect_numbers() {
    cout << "=== Perfect Numbers up to 10000 ===" << nl;
    for (i64 n = 2; n <= 10000; n++) {
        if (is_perfect(n)) {
            cout << n << " is perfect" << nl;
        }
    }
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    demo_division_algorithm();
    demo_ceiling_division();
    demo_divisors();
    demo_perfect_numbers();

    return 0;
}

