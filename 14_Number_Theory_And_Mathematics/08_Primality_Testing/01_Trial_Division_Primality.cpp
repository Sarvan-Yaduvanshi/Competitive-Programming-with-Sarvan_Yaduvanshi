/*
 * ============================================================================
 *  📘 01 — Trial Division Primality Check
 * ============================================================================
 *
 *  O(√n) primality test + comparison with Miller-Rabin.
 *
 *  Reference: https://cp-algorithms.com/algebra/primality_tests.html
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
#define nl '\n'

bool is_prime_trial(i64 n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (i64 i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Trial Division Primality ===" << nl << nl;

    // Primes up to 100
    cout << "Primes up to 100: ";
    for (int i = 2; i <= 100; i++)
        if (is_prime_trial(i)) cout << i << " ";
    cout << nl;

    // Large primes
    cout << nl << "Large tests:" << nl;
    vec<i64> tests = {999999937, 1000000007, 998244353, 999999999999999989LL};
    for (i64 n : tests) {
        cout << n << ": " << (is_prime_trial(n) ? "PRIME" : "COMPOSITE") << nl;
    }

    return 0;
}

