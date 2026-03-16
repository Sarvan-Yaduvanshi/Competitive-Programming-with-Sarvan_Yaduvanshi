/*
 * ============================================================
 *  Topic   : Inclusion-Exclusion Principle & Burnside's Lemma
 *  Pattern : Count using IE bitmask, count under symmetry
 *
 *  Problems:
 *    - CSES Inclusion-Exclusion (2185)
 *    - LeetCode 1201 — Ugly Number III (IE + Binary Search)
 *    - CSES Counting Necklaces (2209) — Burnside
 *    - LeetCode 204 — Count Primes (Sieve / IE)
 *
 *  Complexity: O(2^k) for IE over k sets, O(n) for Burnside on cyclic group
 * ============================================================
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

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
    i64 res = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

/*
 * ============================================================
 *  INCLUSION-EXCLUSION PRINCIPLE
 * ============================================================
 *
 *  |A₁ ∪ A₂ ∪ ... ∪ Aₙ| =
 *    Σ|Aᵢ| − Σ|Aᵢ ∩ Aⱼ| + Σ|Aᵢ ∩ Aⱼ ∩ Aₖ| − ...
 *
 *  BITMASK IMPLEMENTATION:
 *  For k sets, iterate over all 2^k - 1 non-empty subsets.
 *  If subset has odd size → ADD, even size → SUBTRACT.
 *
 *  APPLICATIONS:
 *  1. Count coprime numbers in [1, n] to m
 *  2. Count numbers divisible by at least one of given primes
 *  3. Derangements (IE on fixed-point sets)
 *  4. Euler's totient via IE over prime factors
 *  5. Stars & Bars with upper bounds
 * ============================================================
 */

/*
 *  APPLICATION 1: Count numbers in [1, n] coprime to m
 *  Factorize m into distinct primes, then IE over subsets.
 */
vec<i64> getDistinctPrimeFactors(i64 m) {
    vec<i64> primes;
    for (i64 p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            primes.pb(p);
            while (m % p == 0) m /= p;
        }
    }
    if (m > 1) primes.pb(m);
    return primes;
}

// Count numbers in [1, n] coprime to m
i64 countCoprime(i64 n, i64 m) {
    vec<i64> primes = getDistinctPrimeFactors(m);
    int k = sz(primes);

    i64 result = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        i64 prod = 1;
        int bits = __builtin_popcount(mask);
        bool overflow = false;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                if (prod > n / primes[i]) { overflow = true; break; }
                prod *= primes[i];
            }
        }
        if (overflow) continue;
        if (bits & 1) result += n / prod;   // odd subset → add
        else          result -= n / prod;   // even subset → subtract
    }

    return n - result;  // total - divisible by at least one prime = coprime
}

/*
 *  APPLICATION 2: LeetCode 1201 — Ugly Number III
 *  Count numbers in [1, n] divisible by a OR b OR c.
 *  |A∪B∪C| = |A| + |B| + |C| - |A∩B| - |A∩C| - |B∩C| + |A∩B∩C|
 *  |A∩B| = count divisible by lcm(a,b)
 */
i64 countDivisibleByAny(i64 n, i64 a, i64 b, i64 c) {
    auto lcm = [](i64 x, i64 y) { return x / __gcd(x, y) * y; };

    i64 ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c);
    i64 abc = lcm(ab, c);

    return n/a + n/b + n/c - n/ab - n/ac - n/bc + n/abc;
}

// Binary search for k-th ugly number (divisible by a, b, or c)
i64 nthUglyNumber(int k, int a, int b, int c) {
    i64 lo = 1, hi = 2e9;
    while (lo < hi) {
        i64 mid = lo + (hi - lo) / 2;
        if (countDivisibleByAny(mid, a, b, c) >= k) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

/*
 *  APPLICATION 3: CSES 2185 — Count coprime pairs / IE on prime factors
 *  Given n, count numbers in [1,n] coprime to n.
 *  This is Euler's totient φ(n) = n × ∏(1 - 1/p) for each prime p | n
 *  Can be computed via IE or direct formula.
 */
i64 eulerTotientIE(i64 n) {
    return countCoprime(n, n);
}

/*
 * ============================================================
 *  BURNSIDE'S LEMMA
 * ============================================================
 *
 *  Count distinct objects under group of symmetries G:
 *    answer = (1/|G|) × Σ_{g ∈ G} |Fix(g)|
 *
 *  Fix(g) = number of objects that are unchanged by symmetry g.
 *
 *  NECKLACE COUNTING (n beads, k colors, rotational equivalence):
 *    G = cyclic group of rotations {0, 1, ..., n-1}
 *    Rotation by d positions: Fix = k^(gcd(n, d))
 *    Answer = (1/n) × Σ_{d=0}^{n-1} k^(gcd(n, d))
 *           = (1/n) × Σ_{d | n} φ(n/d) × k^d
 * ============================================================
 */

// Euler's totient function
i64 eulerTotient(i64 n) {
    i64 result = n;
    for (i64 p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Count distinct necklaces: n beads, k colors, rotational symmetry
// Answer mod MOD using Burnside
i64 countNecklaces(i64 n, i64 k) {
    // Answer = (1/n) × Σ_{d|n} φ(n/d) × k^d    (mod MOD)
    i64 sum = 0;
    for (i64 d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            // d divides n
            sum = (sum + eulerTotient(n / d) % MOD * modpow(k, d)) % MOD;
            if (d != n / d) {
                i64 d2 = n / d;
                sum = (sum + eulerTotient(d) % MOD * modpow(k, d2)) % MOD;
            }
        }
    }
    return sum % MOD * modpow(n, MOD - 2) % MOD;
}

/*
 * ============================================================
 *  STIRLING NUMBERS OF THE SECOND KIND
 * ============================================================
 *
 *  S(n, k) = number of ways to partition n elements into k non-empty subsets
 *
 *  RECURRENCE:
 *    S(n, k) = k × S(n-1, k) + S(n-1, k-1)
 *    S(0, 0) = 1, S(n, 0) = 0 for n > 0, S(0, k) = 0 for k > 0
 *
 *  CLOSED FORM (via IE):
 *    S(n, k) = (1/k!) × Σ_{j=0}^{k} (-1)^(k-j) × C(k,j) × j^n
 *
 *  Bell number B(n) = Σ_{k=0}^{n} S(n, k) = total partitions
 * ============================================================
 */

const int MAXN_STIR = 5001;
i64 stirling[MAXN_STIR][MAXN_STIR];  // use small if needed

void precomputeStirling(int maxN) {
    stirling[0][0] = 1;
    for (int n = 1; n <= maxN; n++) {
        for (int k = 1; k <= n; k++) {
            stirling[n][k] = (k * stirling[n-1][k] % MOD + stirling[n-1][k-1]) % MOD;
        }
    }
}

void solve() {
    i64 n;
    cin >> n;

    // Count numbers in [1, n] coprime to n (Euler's totient)
    cout << "φ(" << n << ") = " << countCoprime(n, n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

