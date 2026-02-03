/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-10 19:21:49
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
using pii = pair<int, int>;
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

// Input helper
template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}
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

/**
 * Prefix Sum Construction (Brute Force)
 *
 * prefixSum[i] = arr[0] + arr[1] + ... + arr[i]
 *
 * Approach:
 * - For each index i, recompute the sum from 0 to i
 * - No reuse of previous computations
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
void prefixSumCal(const vec<int>& arr){
    int n = sz(arr);

    vec<int> prefixSum(n);
    for (int i = 0; i < n; i++){
        prefixSum[i] = 0;
        for (int j = 0; j <= i; j++){
            prefixSum[i] += arr[j];
        }
    }

    for (int i = 0; i < n; i++){
        cout << prefixSum[i] << " ";
    }
    cout << nl;
}

/**
 * Prefix Sum Construction (Optimal)
 *
 * pref[i] = sum of arr[0 .... i-1]
 * Enables O(1) range sum queries using:
 * sum(l, r) = pref[r + 1] - pref[l]
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
vec<i64> optimalPrefixSum(const vec<int>& arr){
    int n = sz(arr);

    // pref[0] = 0 simplifies boundary handling
    vec<i64> pref(n + 1, 0);

    // Build prefix sums
    for (int i = 0; i < n; i++){
        pref[i + 1] = pref[i] + arr[i];
    }

    return pref;
}

/**
 * Brute Force Range Sum Query
 *
 * Problem Context:
 * - Given a static array and multiple queries [l, r],
 *   compute the sum of elements from index l to r (inclusive).
 *
 * Time Complexity:
 * - Per Query: O(r - l + 1) ⟶ O(N) in the worst case
 * - Total: O(N × Q)
 *   Suitable only when:
 *   - Q is small, or
 *   - N is small (e.g., N ≤ 10⁴)
 *
 * Space Complexity:
 * - O(1) extra space
 * - No auxiliary data structures required
 *
 * Constraints & Limitations:
 * - Inefficient for large Q (e.g., Q ≥ 10⁵)
 * - Recomputes overlapping sums repeatedly
 * - Not scalable for competitive programming time limits
 */
void prefixSumQuery(const vec<int>& arr){
    int n = sz(arr);

    int q; cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;

        i64 sum = 0;
        for (int i = l; i <= r; i++){
            sum += arr[i];
        }

        cout << sum << nl;
    }
}

void solve() {
    int n;
    cin >> n;

    vec<int> a(n);
    read(a);

    // Precompute prefix sums in O(N)
    vec<i64> prefixSum = optimalPrefixSum(a);

    // Step 1: Check Problem statement
    // If it says 1 ≤ l ≤ r ≤ n → 1-based
    // If it says 0 ≤ l ≤ r < n → 0-based

    int Q; cin >> Q;

    // Process each query in O(1)
    while (Q--) {
        int l, r;
        cin >> l >> r;   // l and r are 1-based

        // Validity check (optional but safe)
        // if (l >= 1 && r <= n && l <= r) {
        //     i64 currSum = prefixSum[r] - prefixSum[l - 1]; // 1 based index formula
        //     cout << currSum << nl;
        // }
        // if use 0 based index than formula :- currSum = pref[r + 1] - pref[l];
        if (l >= 0 && r < n && l <= r){
            i64 currSum = prefixSum[r + 1] - prefixSum[l];
            cout << currSum << nl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

