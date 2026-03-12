/*
 * ============================================================================
 *  📘 02 — SPF Sieve Factorization
 * ============================================================================
 *
 *  Precompute smallest prime factor (SPF) via linear sieve.
 *  Then factorize any n ≤ N in O(log n) by repeatedly dividing by spf[n].
 *
 *  See 07_Prime_Generation/03_Linear_Sieve.cpp for the full sieve.
 *  This file provides a lightweight factorization-focused version.
 *
 *  TIME: O(N) preprocess, O(log n) per factorization
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
using pii = pair<int, int>;
#define nl '\n'
#define sz(x) ((int)(x).size())

constexpr int MAXN = 10'000'001;
int spf[MAXN];  // smallest prime factor

void build_spf() {
    for (int i = 2; i < MAXN; i++) {
        if (spf[i] == 0) {
            for (int j = i; j < MAXN; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

vec<pii> factorize_spf(int n) {
    vec<pii> factors;
    while (n > 1) {
        int p = spf[n], cnt = 0;
        while (n % p == 0) { n /= p; cnt++; }
        factors.push_back({p, cnt});
    }
    return factors;
}

// Get all divisors from factorization
vec<int> get_divisors(int n) {
    vec<int> divs = {1};
    while (n > 1) {
        int p = spf[n], cnt = 0;
        while (n % p == 0) { n /= p; cnt++; }
        int old_sz = sz(divs);
        int pw = 1;
        for (int i = 0; i < cnt; i++) {
            pw *= p;
            for (int j = 0; j < old_sz; j++) {
                divs.push_back(divs[j] * pw);
            }
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_spf();

    cout << "=== SPF Sieve Factorization ===" << nl << nl;

    vec<int> tests = {12, 60, 360, 720, 1000000, 9999991};
    for (int n : tests) {
        auto f = factorize_spf(n);
        cout << n << " = ";
        for (int i = 0; i < sz(f); i++) {
            if (i) cout << " × ";
            cout << f[i].first;
            if (f[i].second > 1) cout << "^" << f[i].second;
        }
        cout << nl;
    }

    // Divisors demo
    cout << nl << "--- Divisors of 60 ---" << nl;
    for (int d : get_divisors(60)) cout << d << " ";
    cout << nl;

    cout << nl << "--- Divisors of 360 ---" << nl;
    auto d360 = get_divisors(360);
    cout << "Count: " << sz(d360) << nl;
    for (int d : d360) cout << d << " ";
    cout << nl;

    return 0;
}

