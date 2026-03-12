/*
 * ============================================================================
 *  📘 02 — Sieve of Eratosthenes
 * ============================================================================
 *
 *  ALGORITHM:
 *    1. Create boolean array is_prime[0..N] = true
 *    2. Set is_prime[0] = is_prime[1] = false
 *    3. For each p from 2 to √N:
 *       If is_prime[p]: mark all multiples p², p²+p, p²+2p, ... as false
 *
 *  WHY START FROM p²?
 *    Multiples 2p, 3p, ..., (p-1)p already marked by smaller primes.
 *    e.g., 6 = 2×3 is already marked when p=2.
 *
 *  TIME:  O(n log log n)  — by Mertens' theorem
 *  SPACE: O(n)
 *
 *  DRY RUN (N=30):
 *    p=2: cross 4,6,8,10,12,14,16,18,20,22,24,26,28,30
 *    p=3: cross 9,15,21,27
 *    p=5: cross 25
 *    Result: {2,3,5,7,11,13,17,19,23,29}
 *
 *  Reference: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
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
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>
#include <bitset>

using namespace std;
using i64 = long long;
template<class T> using vec = vector<T>;
#define nl '\n'
#define sz(x) ((int)(x).size())
#define pb push_back

constexpr i64 MOD = 1'000'000'007LL;

// ============================================================================
//  📌 BASIC SIEVE
// ============================================================================

vec<bool> sieve_basic(int n) {
    vec<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; (i64)p * p <= n; p++) {
        if (is_prime[p]) {
            for (int j = p * p; j <= n; j += p) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// ============================================================================
//  📌 SIEVE RETURNING PRIME LIST
// ============================================================================

vec<int> get_primes(int n) {
    vec<bool> is_prime = sieve_basic(n);
    vec<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes.pb(i);
    }
    return primes;
}

// ============================================================================
//  📌 OPTIMIZED SIEVE (only odd numbers)
// ============================================================================
//  Store only odd numbers → half the memory.
//  Index i represents number 2i+1.
// ============================================================================

vec<int> sieve_odd_only(int n) {
    vec<int> primes;
    if (n >= 2) primes.pb(2);

    int half = n / 2;
    vec<bool> is_composite(half + 1, false);

    for (int i = 1; i <= half; i++) {  // i represents number 2i+1
        if (!is_composite[i]) {
            int p = 2 * i + 1;
            primes.pb(p);
            // Mark multiples starting from p²
            // p² = (2i+1)² = 4i²+4i+1, index = (4i²+4i)/2 = 2i²+2i = 2i(i+1)
            for (i64 j = 2LL * i * (i + 1); j <= half; j += p) {
                is_composite[j] = true;
            }
        }
    }
    return primes;
}

// ============================================================================
//  📌 BITSET SIEVE (memory efficient for very large N)
// ============================================================================

constexpr int MAXN = 10'000'001;
bitset<MAXN> is_composite_bs;

vec<int> sieve_bitset(int n) {
    is_composite_bs.reset();
    is_composite_bs[0] = is_composite_bs[1] = 1;

    vec<int> primes;
    for (int i = 2; i <= n; i++) {
        if (!is_composite_bs[i]) {
            primes.pb(i);
            if ((i64)i * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    is_composite_bs[j] = 1;
                }
            }
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Sieve of Eratosthenes ===" << nl << nl;

    // Visual dry run
    cout << "--- Dry Run: Sieve up to 50 ---" << nl;
    {
        int N = 50;
        vec<bool> is_p(N + 1, true);
        is_p[0] = is_p[1] = false;

        cout << "Initial: ";
        for (int i = 2; i <= N; i++) cout << i << " ";
        cout << nl << nl;

        for (int p = 2; p * p <= N; p++) {
            if (is_p[p]) {
                cout << "p=" << p << ": cross out ";
                bool first = true;
                for (int j = p * p; j <= N; j += p) {
                    if (is_p[j]) {
                        if (!first) cout << ",";
                        cout << j;
                        first = false;
                    }
                    is_p[j] = false;
                }
                cout << nl;

                cout << "  Remaining: ";
                for (int i = 2; i <= N; i++) {
                    if (is_p[i]) cout << i << " ";
                }
                cout << nl;
            }
        }

        cout << nl << "Primes up to " << N << ": ";
        for (int i = 2; i <= N; i++) if (is_p[i]) cout << i << " ";
        cout << nl;
    }

    // Count primes
    cout << nl << "--- Prime Counting Function π(n) ---" << nl;
    auto primes = get_primes(10000000);
    vec<int> milestones = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    for (int m : milestones) {
        int cnt = upper_bound(primes.begin(), primes.end(), m) - primes.begin();
        cout << "π(" << m << ") = " << cnt << nl;
    }

    // Verification: different methods give same result
    cout << nl << "--- Verification ---" << nl;
    auto p1 = get_primes(100000);
    auto p2 = sieve_odd_only(100000);
    auto p3 = sieve_bitset(100000);
    assert(p1 == p2);
    assert(p1 == p3);
    cout << "All 3 sieve methods agree: " << sz(p1) << " primes up to 100000" << nl;

    return 0;
}

