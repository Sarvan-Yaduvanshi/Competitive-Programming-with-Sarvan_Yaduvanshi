/*
 * ============================================================================
 *  📘 01 — Trial Division Factorization
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
#include <cassert>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
using pll = pair<i64, i64>;
#define nl '\n'
#define sz(x) ((int)(x).size())

vec<pll> trial_factorize(i64 n) {
    vec<pll> factors;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) { n /= p; cnt++; }
            factors.push_back({p, cnt});
        }
    }
    if (n > 1) factors.push_back({n, 1});
    return factors;
}

// Divisor count from factorization: Π(aᵢ + 1)
i64 divisor_count(i64 n) {
    i64 result = 1;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int a = 0;
            while (n % p == 0) { n /= p; a++; }
            result *= (a + 1);
        }
    }
    if (n > 1) result *= 2;
    return result;
}

// All divisors (unsorted)
vec<i64> get_divisors(i64 n) {
    vec<i64> divs;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divs.push_back(d);
            if (d != n / d) divs.push_back(n / d);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Trial Division Factorization ===" << nl << nl;

    vec<i64> tests = {1, 12, 60, 100, 360, 720, 1000000007LL};
    for (i64 n : tests) {
        auto f = trial_factorize(n);
        cout << n << " = ";
        for (int i = 0; i < sz(f); i++) {
            if (i) cout << " × ";
            cout << f[i].first;
            if (f[i].second > 1) cout << "^" << f[i].second;
        }
        cout << "  [τ=" << divisor_count(n) << "]" << nl;
    }

    // Divisors example
    cout << nl << "Divisors of 60: ";
    for (i64 d : get_divisors(60)) cout << d << " ";
    cout << nl;

    return 0;
}

