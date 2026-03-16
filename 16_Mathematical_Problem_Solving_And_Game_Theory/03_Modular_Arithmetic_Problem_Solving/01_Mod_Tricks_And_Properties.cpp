/*
 * ============================================================
 *  Topic   : Modular Arithmetic Tricks & Properties
 *  Pattern : Handle negative mod, avoid overflow, modular ops
 *
 *  Complexity: O(1) per operation, O(log b) for modpow
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

/*
 * ============================================================
 *  SAFE MODULAR OPERATIONS
 * ============================================================
 */

// Safe mod (handles negative numbers)
inline i64 safemod(i64 a, i64 m) {
    return ((a % m) + m) % m;
}

// Modular addition
inline i64 addmod(i64 a, i64 b, i64 m = MOD) {
    return safemod(a + b, m);
}

// Modular subtraction
inline i64 submod(i64 a, i64 b, i64 m = MOD) {
    return safemod(a - b, m);
}

// Modular multiplication (safe for i64 range)
inline i64 mulmod(i64 a, i64 b, i64 m = MOD) {
    return safemod(safemod(a, m) * safemod(b, m), m);
}

// Modular multiplication using __int128 (safe for any i64 values)
inline i64 mulmod128(i64 a, i64 b, i64 m) {
    return ((__int128)a * b) % m;
}

/*
 * ============================================================
 *  KEY MODULAR PROPERTIES - Demonstration
 * ============================================================
 *
 *  1. (a + b) % m = ((a%m) + (b%m)) % m        ✓ Always works
 *  2. (a - b) % m = ((a%m) - (b%m) + m) % m     ✓ Need +m for negative
 *  3. (a * b) % m = ((a%m) * (b%m)) % m          ✓ Watch overflow
 *  4. (a / b) % m = (a * modinv(b,m)) % m        ✓ Need modular inverse
 *  5. (a ^ b) % m = use binary exponentiation     ✓ O(log b)
 *
 *  PROPERTIES:
 *  - (a % m) is in range [0, m-1] if a ≥ 0
 *  - C++ % can give negative result if a < 0
 *  - For m = 1e9+7 and a,b < m: a*b fits in i64 (< 10^18)
 *  - For m > 10^9.5: need __int128 for a*b
 * ============================================================
 */

// Sum of array elements mod m
i64 arraySumMod(vec<i64>& a, i64 m) {
    i64 sum = 0;
    for (auto x : a) {
        sum = addmod(sum, x, m);
    }
    return sum;
}

// Product of array elements mod m
i64 arrayProductMod(vec<i64>& a, i64 m) {
    i64 prod = 1;
    for (auto x : a) {
        prod = mulmod(prod, x, m);
    }
    return prod;
}

/*
 *  COUNTING SUBARRAYS WITH SUM DIVISIBLE BY k
 *  ──────────────────────────────────────────
 *  Use prefix sums mod k. If prefix[i] == prefix[j] (mod k),
 *  then subarray sum (i,j] is divisible by k.
 *  Count pairs of equal remainders.
 */
i64 countSubarraysDivisibleByK(vec<int>& a, int k) {
    map<int,int> cnt;
    cnt[0] = 1;  // empty prefix has sum 0
    i64 prefix = 0, ans = 0;
    for (int x : a) {
        prefix += x;
        int r = ((prefix % k) + k) % k;
        ans += cnt[r];
        cnt[r]++;
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vec<int> a(n);
    read(a);

    cout << countSubarraysDivisibleByK(a, k) << nl;
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

