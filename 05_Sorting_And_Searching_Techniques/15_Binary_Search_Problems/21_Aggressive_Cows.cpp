/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-08 11:02:36
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

/* Problem: Aggressive cows
 * Platform: SPOJ
 * Farmer John has built a new long barn, with N (2 ≤ N ≤ 100,000) stalls.
 * The stalls are located along a straight line at positions x1 ... xN (0 ≤ xi ≤ 1,000,000,000).
 * His C (2 ≤ C ≤ N) cows don't like this barn layout and become aggressive towards each other once put into a stall.
 * To prevent the cows from hurting each other, FJ wants to assign the cows to the stalls,
 * such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?
 *
 * input:
 * t – the number of test cases, then t test cases follows.
 *    1. Line 1: Two space-separated integers: N and C
 *    2. Lines 2..N+1: Line i+1 contains an integer stall location, xi
 *
 * output:
 *    For each test case, output one integer: the largest minimum distance.
 *
 * Example:
 * input:
 * 3
 * 5 3
 * stalls: 1, 2, 8, 4, 9  and C=3 cows
 * Answer: 3 (place cows at 1, 4, 9)
 * 5 3
 * stalls: 10, 1, 2, 7, 5  and C=3 cows
 * Answer: 4 (place cows at 1, 5, 10)
 * 6 5
 * stalls: 2, 12, 11, 3, 26, 7 and C=5 cows
 * Answer: 1 (place cows at 2, 3, 7, 11, 12)
 *
 */

// Approach: Binary search on answer (minimum distance).
// Logic: 1. Sort stall positions.
//        2. For each candidate distance d, greedily place cows:
//           - Place first cow at leftmost stall.
//           - Next cow at first stall that is ≥ d away, etc.
//        3. If we can place all C cows → d is feasible.
// Time: O(N log N + N log(maxDist))
// Space: O(N)


void solve() {
    i64 n, k; cin >> n >> k;

    vec<i64> stalls(n);
    read(stalls);

    // Step 1: Sort stall positions
    sort(all(stalls));

    // Step 3: Feasibility check function
    auto canPlace = [&](i64 minDist) -> bool{
        i64 cows = 1; // Place first cow at leftmost stall
        i64 lastStallPos = stalls[0];

        for (int i = 1; i < n; i++) {
            if (stalls[i] - lastStallPos >= minDist) {
                cows++;
                lastStallPos = stalls[i];
                if (cows >= k) return true; // All cows placed successfully
            }
        }
        return false; // Not all cows could be placed with minDist
    };

    // Step 2: Binary search on answer (minimum distance)
    i64 lo = 1; // Minimum possible distance
    i64 hi = stalls[n - 1] - stalls[0]; // Maximum possible distance
    i64 ans = -1;

    while (lo <= hi){
        i64 mid = lo + (hi - lo) / 2;
        if (canPlace(mid)) {
            ans = mid; // mid is a valid minimum distance
            lo = mid + 1; // Try for a larger minimum distance
        } else {
            hi = mid - 1; // Try for a smaller minimum distance
        }
    }

    cout << ans << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}

