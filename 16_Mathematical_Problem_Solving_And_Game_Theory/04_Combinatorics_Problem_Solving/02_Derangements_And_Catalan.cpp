/*
 * ============================================================
 *  Topic   : Derangements & Catalan Numbers
 *  Pattern : Two of the most important counting sequences in CP
 *
 *  Problems:
 *    - CSES Christmas Party (1717) — Derangements
 *    - CSES Bracket Sequences I (2064) — Catalan
 *    - LeetCode 22 — Generate Parentheses
 *
 *  Complexity: O(n) for computing nth term
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

const int MAXN = 2'000'001;
i64 fact[MAXN], ifact[MAXN];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;
    ifact[MAXN - 1] = modpow(fact[MAXN - 1], MOD - 2, MOD);
    for (int i = MAXN - 2; i >= 0; i--)
        ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}

i64 C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * ifact[r] % MOD * ifact[n - r] % MOD;
}

/*
 * ============================================================
 *  DERANGEMENTS
 * ============================================================
 *
 *  D(n) = permutations of [1..n] where no element is in its
 *         original position (σ(i) ≠ i for all i)
 *
 *  RECURRENCE:
 *    D(0) = 1
 *    D(1) = 0
 *    D(n) = (n-1) * (D(n-1) + D(n-2))
 *
 *  CLOSED FORM:
 *    D(n) = n! * Σ_{k=0}^{n} (-1)^k / k!
 *
 *  APPROXIMATION:
 *    D(n) ≈ n! / e (nearest integer)
 *    P(derangement) = D(n)/n! ≈ 1/e ≈ 0.3679
 *
 *  INTUITION for recurrence:
 *    Element 1 goes to position j (n-1 choices).
 *    Case 1: j goes to position 1 → derange remaining n-2: D(n-2)
 *    Case 2: j doesn't go to position 1 → derange n-1 items: D(n-1)
 * ============================================================
 */

vec<i64> computeDerangements(int n) {
    vec<i64> D(n + 1);
    D[0] = 1;
    if (n >= 1) D[1] = 0;
    for (int i = 2; i <= n; i++) {
        D[i] = (i - 1) % MOD * ((D[i - 1] + D[i - 2]) % MOD) % MOD;
    }
    return D;
}

/*
 * ============================================================
 *  CATALAN NUMBERS
 * ============================================================
 *
 *  C(n) = C(2n, n) / (n + 1)       (closed form)
 *  C(n) = C(2n, n) - C(2n, n+1)    (ballot form / reflection)
 *
 *  RECURRENCE:
 *    C(0) = 1
 *    C(n) = Σ_{i=0}^{n-1} C(i) * C(n-1-i)
 *
 *  FIRST VALUES:
 *    1, 1, 2, 5, 14, 42, 132, 429, 1430, ...
 *
 *  WHAT CATALAN COUNTS:
 *    - Balanced parentheses with n pairs
 *    - Full binary trees with n+1 leaves
 *    - Triangulations of (n+2)-gon
 *    - Non-crossing partitions of n
 *    - Stack-sortable permutations of length n
 *    - Paths from (0,0) to (n,n) not crossing y=x diagonal
 * ============================================================
 */

// Method 1: Using nCr formula — O(1) with precomputation
i64 catalan_formula(int n) {
    // C(n) = C(2n, n) / (n+1)
    // = C(2n, n) * modinv(n+1)
    return C(2 * n, n) % MOD * modpow(n + 1, MOD - 2, MOD) % MOD;
}

// Method 2: Using reflection — C(2n,n) - C(2n,n+1)
i64 catalan_reflection(int n) {
    return (C(2 * n, n) - C(2 * n, n + 1) + MOD) % MOD;
}

// Method 3: DP / recurrence — O(n^2) but useful for understanding
vec<i64> catalan_dp(int n) {
    vec<i64> cat(n + 1, 0);
    cat[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            cat[i] = (cat[i] + cat[j] % MOD * cat[i - 1 - j]) % MOD;
        }
    }
    return cat;
}

void solve() {
    int n;
    cin >> n;

    // Derangement
    auto D = computeDerangements(n);
    cout << "D(" << n << ") = " << D[n] << nl;

    // Catalan
    cout << "Catalan(" << n << ") = " << catalan_formula(n) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    precompute();

    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

