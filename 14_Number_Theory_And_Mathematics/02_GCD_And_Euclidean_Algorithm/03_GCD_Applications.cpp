/*
 * ============================================================================
 *  📘 03 — GCD Applications: Binary GCD, Coprime, Array Operations
 * ============================================================================
 *
 *  BINARY GCD (Stein's Algorithm):
 *    Uses only subtraction, bit shifts — no division/modulo.
 *    Rules:
 *      1. gcd(0, b) = b, gcd(a, 0) = a
 *      2. gcd(2a, 2b) = 2 × gcd(a, b)
 *      3. gcd(2a, odd_b) = gcd(a, odd_b)
 *      4. gcd(odd_a, odd_b) = gcd(|a-b|/2, min(a,b))
 *
 *    Complexity: O(log(a) × log(b)) worst case, O(log²(max))
 *
 *  Reference: https://cp-algorithms.com/algebra/euclid-algorithm.html
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
#define sz(x) ((int)(x).size())
#define pb push_back
#define fi first
#define se second
#define nl '\n'

template<class T>
void read(vec<T> &v) { for (auto &x : v) cin >> x; }

// ============================================================================
//  📌 BINARY GCD (Stein's Algorithm)
// ============================================================================
//
//  DRY RUN: binary_gcd(48, 18)
//    Both even: shift = ctz(48|18) = ctz(50) = 1 → factor out 2
//    a = 48 >> 1 = 24, remove trailing zeros: 24 → 3 (shift 3)
//    Wait, let me redo properly:
//
//  Actually using __builtin_ctz:
//    48 = 110000₂, 18 = 10010₂
//    shift = min(ctz(48), ctz(18)) = min(4, 1) = 1
//    a = 48 >> 1 = 24, b = 18 >> 1 = 9
//    Remove factors of 2 from a: 24 >> 3 = 3
//    Now a=3, b=9 (both odd)
//    |a-b| = 6, min = 3 → b=3, a=6>>1=3
//    a=3, b=3 → |a-b|=0, done. gcd = 3 × 2 = 6
//
//  Result: gcd(48, 18) = 6 ✓
// ============================================================================

i64 binary_gcd(i64 a, i64 b) {
    if (a == 0) return b;
    if (b == 0) return a;

    // Find common factor of 2
    int shift = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);

    do {
        b >>= __builtin_ctzll(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);

    return a << shift;
}

// ============================================================================
//  📌 COPRIME CHECK
// ============================================================================
//  Two numbers are coprime if gcd(a, b) = 1.
//  Coprime pairs are fundamental in many NT algorithms.
// ============================================================================

bool are_coprime(i64 a, i64 b) {
    return __gcd(a, b) == 1;
}

// ============================================================================
//  📌 COUNT COPRIME PAIRS in array — O(n²)
// ============================================================================

i64 count_coprime_pairs(const vec<i64>& arr) {
    int n = sz(arr);
    i64 count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (__gcd(arr[i], arr[j]) == 1)
                count++;
    return count;
}

// ============================================================================
//  📌 GCD of SUBARRAY / RANGE
// ============================================================================
//  Key property: GCD is monotonically non-increasing as range extends.
//  gcd(a[l..r]) ≥ gcd(a[l..r+1])
//
//  The number of distinct GCD values over all subarrays starting at l
//  is at most O(log(max_val)), because each new element either keeps
//  the GCD or reduces it by at least factor 2.
// ============================================================================

void demo_subarray_gcd(const vec<i64>& arr) {
    int n = sz(arr);
    cout << "Subarray GCD values:" << nl;

    // For each starting point, track distinct GCDs
    set<i64> all_gcds;

    for (int l = 0; l < n; l++) {
        i64 g = 0;
        for (int r = l; r < n; r++) {
            g = __gcd(g, arr[r]);
            all_gcds.insert(g);
            cout << "  gcd(a[" << l << ".." << r << "]) = " << g << nl;
        }
    }

    cout << "Distinct GCD values: " << sz(all_gcds) << nl;
    cout << "Values: ";
    for (i64 g : all_gcds) cout << g << " ";
    cout << nl;
}

// ============================================================================
//  📌 BEZOUT COEFFICIENTS APPLICATION
// ============================================================================
//  Problem: Given a, b, determine if we can make exactly N liters
//           using jugs of size a and b.
//  Answer: Yes iff gcd(a, b) | N
//  (This is the "Die Hard 3" water jug problem!)
// ============================================================================

bool can_measure(i64 a, i64 b, i64 target) {
    return target % __gcd(a, b) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== GCD Applications ===" << nl << nl;

    // Binary GCD tests
    cout << "--- Binary GCD ---" << nl;
    vec<pll> tests = {{48, 18}, {252, 105}, {100, 75}, {17, 13}, {0, 5}, {1000000007, 998244353}};
    for (auto [a, b] : tests) {
        i64 g1 = __gcd(a, b);
        i64 g2 = binary_gcd(a, b);
        cout << "gcd(" << a << ", " << b << ") = " << g1;
        assert(g1 == g2);
        cout << " ✓" << nl;
    }

    // Coprime tests
    cout << nl << "--- Coprime Check ---" << nl;
    vec<pll> coprime_tests = {{3, 7}, {4, 6}, {15, 28}, {12, 18}, {1, 100}};
    for (auto [a, b] : coprime_tests) {
        cout << "gcd(" << a << ", " << b << ") = " << __gcd(a, b)
             << " → " << (are_coprime(a, b) ? "COPRIME" : "NOT coprime") << nl;
    }

    // Subarray GCD
    cout << nl << "--- Subarray GCD ---" << nl;
    vec<i64> arr = {12, 8, 6, 4};
    demo_subarray_gcd(arr);

    // Water jug problem
    cout << nl << "--- Water Jug Problem ---" << nl;
    cout << "Jugs of 3 and 5 liters:" << nl;
    for (int target = 1; target <= 15; target++) {
        cout << "  Can measure " << target << "L? "
             << (can_measure(3, 5, target) ? "YES" : "NO") << nl;
    }

    return 0;
}

