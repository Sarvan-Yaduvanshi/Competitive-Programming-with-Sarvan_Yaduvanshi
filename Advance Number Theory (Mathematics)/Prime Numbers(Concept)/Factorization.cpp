/*
Author: Sarvan.DP.GrandMaster
Created : 2025-12-28 01:12:20
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

// --- Type Definitions ---
using i64 = long long;
using u64 = unsigned long long;
using ld  = long double;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
template<class A, class B> using pii = pair<A,B>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD   = 1'000'000'007LL;
constexpr i64 MOD9  = 998'244'353LL;
constexpr ld PI     = 3.14159265358979323846;

// --- Random Number Generator ---
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// --- Macros ---
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Method 1 : Brute Force works up to 10^6 but not for 10^12
// Time Complexity O(N)
void factorization(const i64 n) {
    // use vector if all factor print sorted
    for (i64 i = 1; i <= n; i++) {
        if (n % i == 0) cout << i << " ";
    }
    cout << nl;
}

// Method 2 : Optimized Sqrt work 10^12...
// Time Complexity O(Sqrt(N))
void factorization2(const i64 n) {
    // Execution Speed: The time complexity is O(Sqrt(N).
    // It's technically faster because it avoids the O(DlogD) sorting step
    vec<i64> front_factors;
    vec<i64> back_factors;

    for (i64 i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            front_factors.pb(i);
            if (i != n / i) back_factors.pb(n / i);
        }
    }

    // Print the first half
    for (auto x : front_factors) cout << x << " ";

    // Print the second half in reverse (GM-safe)
    for (int i = sz(back_factors); i-- > 0; ) {
        cout << back_factors[i] << " ";
    }
    cout << nl;

    // if avoid two vector than use single vector than sort all element
    // Execution Speed: The time complexity is O(Sqrt(N) +DlogD),
    // where D is the number of divisors.
    /*
    vector<i64> factors;
    for (i64 i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            if (n / i != i) factors.push_back(n / i);
        }
    }
    sort(all(factors));
    */

    // Both Method are Great But Generally CP Use Single Vector
}

// Method 3 :- print all factors using prime logic
// Calculates prime factorization of n in O(sqrt(N)).
// Returns a map where key is the prime and value is its exponent.
// Example: 72 -> { {2, 3}, {3, 2} } representing 2^3 * 3^2.
map<i64, int> getPrimeFactorization(i64 n) {
    map<i64, int> prime_factors;
    for (i64 i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            prime_factors[i]++;
            n /= i;
        }
    }
    if (n > 1) prime_factors[n]++;
    return prime_factors;
}

// Recursively generates all factors from a prime factorization.
// 'primes' is a vector of {prime, exponent} pairs. 'all_factors' is the output vector.
void generateFactors(int k, i64 current_factor, const vec<pii<i64, int>>& primes, vec<i64>& all_factors) {
    // Base case: all prime factors have been considered. A new factor is found.
    if (k == sz(primes)) {
        all_factors.push_back(current_factor);
        return;
    }

    i64 p = primes[k].fi; // The current prime base
    int a = primes[k].se; // Its maximum exponent
    i64 p_power = 1;

    // Recursive step: iterate through all possible powers of the current prime (from p^0 to p^a).
    for (int i = 0; i <= a; ++i) {
        generateFactors(k + 1, current_factor * p_power, primes, all_factors);
        p_power *= p;
    }
}

void solve() {
    i64 n; cin >> n;

    // Method 1 : simple brute force
    factorization(n);

    cout << "<----------------------->" << endl;
    // Method 2 : Optimized
    factorization2(n);

    // Step 1: Get the prime factorization as a map.
    map<i64, int> prime_map = getPrimeFactorization(n);

    // Step 2: Convert map to a vector of pairs for easier iteration in the recursive function.
    vec<pii<i64, int>> primes(all(prime_map));

    // Step 3: Recursively generate all factors.
    vec<i64> all_factors;
    generateFactors(0, 1, primes, all_factors);

    // --- FIX WAS HERE ---
    // Step 4: The calculated factors must be sorted and printed.
    sort(all(all_factors));
    for (i64 factor : all_factors) {
        cout << factor << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);
    solve();

    return 0;
}

