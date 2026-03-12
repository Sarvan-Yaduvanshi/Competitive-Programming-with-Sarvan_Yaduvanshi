/*
 * ============================================================================
 *  📘 01 — Inclusion-Exclusion Principle
 * ============================================================================
 *
 *  |A₁ ∪ A₂ ∪ ... ∪ Aₙ| = Σ|Aᵢ| - Σ|Aᵢ∩Aⱼ| + Σ|Aᵢ∩Aⱼ∩Aₖ| - ...
 *
 *  COMPLEMENT FORM (most used in CP):
 *  Count of elements in NONE of the sets:
 *    |Ā₁ ∩ Ā₂ ∩ ... ∩ Āₙ| = |U| - |A₁ ∪ ... ∪ Aₙ|
 *
 *  BITMASK IMPLEMENTATION:
 *    For n properties, iterate over all 2^n - 1 non-empty subsets.
 *    For subset S: if |S| is odd, add |∩_{i∈S} Aᵢ|; if even, subtract.
 *
 *  Reference: https://cp-algorithms.com/combinatorics/inclusion-exclusion.html
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
//  📌 COPRIME COUNT using Inclusion-Exclusion
// ============================================================================
//  Count integers in [1, N] that are coprime to m.
//
//  Method: Factor m into distinct primes p₁, p₂, ..., pₖ.
//  Use IE: subtract multiples of each pᵢ, add back multiples of pᵢpⱼ, etc.
//
//  DRY RUN: Count coprime to 30 in [1, 30]
//    30 = 2 × 3 × 5, primes = {2, 3, 5}
//    Total = 30
//    Subtract: ⌊30/2⌋ + ⌊30/3⌋ + ⌊30/5⌋ = 15 + 10 + 6 = 31
//    Add back: ⌊30/6⌋ + ⌊30/10⌋ + ⌊30/15⌋ = 5 + 3 + 2 = 10
//    Subtract: ⌊30/30⌋ = 1
//    Coprime count = 30 - 31 + 10 - 1 = 8
//    Check: φ(30) = 30 × (1-1/2)(1-1/3)(1-1/5) = 8 ✓
// ============================================================================

i64 coprime_count(i64 N, i64 m) {
    // Get distinct prime factors of m
    vec<i64> primes;
    i64 temp = m;
    for (i64 p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            primes.push_back(p);
            while (temp % p == 0) temp /= p;
        }
    }
    if (temp > 1) primes.push_back(temp);

    int k = sz(primes);
    i64 result = 0;

    // Iterate over all 2^k subsets
    for (int mask = 0; mask < (1 << k); mask++) {
        i64 product = 1;
        int bits = __builtin_popcount(mask);

        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                product *= primes[i];
                if (product > N) break;  // optimization
            }
        }

        if (product > N && bits > 0) continue;

        i64 count = N / product;
        if (bits % 2 == 0) result += count;  // even: add
        else result -= count;                 // odd: subtract
    }

    return result;
}

// ============================================================================
//  📌 DERANGEMENT D(n)
// ============================================================================
//  Permutations where no element is in its original position.
//  D(n) = n! × Σ_{i=0}^{n} (-1)^i / i!
//  D(n) = (n-1) × (D(n-1) + D(n-2))  [recurrence]
//  D(n) ≈ n! / e  (rounded to nearest integer)
// ============================================================================

i64 derangement(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    vec<i64> D(n + 1);
    D[0] = 1; D[1] = 0;
    for (int i = 2; i <= n; i++) {
        D[i] = (i - 1) * (D[i-1] + D[i-2]);
    }
    return D[n];
}

// ============================================================================
//  📌 COUNT NUMBERS IN [1,N] DIVISIBLE BY AT LEAST ONE ELEMENT OF A SET
// ============================================================================

i64 count_divisible(i64 N, const vec<i64>& divisors) {
    int k = sz(divisors);
    i64 result = 0;

    for (int mask = 1; mask < (1 << k); mask++) {
        i64 lcm = 1;
        int bits = 0;
        bool overflow = false;

        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                bits++;
                lcm = lcm / __gcd(lcm, divisors[i]) * divisors[i];
                if (lcm > N) { overflow = true; break; }
            }
        }

        if (overflow) continue;

        if (bits % 2 == 1) result += N / lcm;
        else result -= N / lcm;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Inclusion-Exclusion Principle ===" << nl << nl;

    // Coprime count
    cout << "--- Coprime Count ---" << nl;
    vec<pair<i64,i64>> tests = {{30, 30}, {100, 30}, {1000, 42}, {1000000, 30}};
    for (auto [N, m] : tests) {
        cout << "Coprime to " << m << " in [1," << N << "]: " << coprime_count(N, m) << nl;
    }

    // Verify with Euler totient
    cout << nl << "--- Verify: coprime_count(n, n) = φ(n) ---" << nl;
    for (int n = 1; n <= 20; n++) {
        i64 cc = coprime_count(n, n);
        // Compute φ(n) directly
        i64 phi = n;
        int temp = n;
        for (int p = 2; p * p <= temp; p++) {
            if (temp % p == 0) {
                phi -= phi / p;
                while (temp % p == 0) temp /= p;
            }
        }
        if (temp > 1) phi -= phi / temp;
        cout << "n=" << n << ": IE=" << cc << ", φ=" << phi << (cc == phi ? " ✓" : " ✗") << nl;
    }

    // Derangements
    cout << nl << "--- Derangements ---" << nl;
    for (int n = 0; n <= 12; n++) {
        cout << "D(" << n << ") = " << derangement(n) << nl;
    }

    // Count divisible
    cout << nl << "--- Numbers in [1,100] divisible by 2, 3, or 5 ---" << nl;
    cout << count_divisible(100, {2, 3, 5}) << nl;
    cout << "Expected: " << 100 - coprime_count(100, 30) << nl;

    return 0;
}

