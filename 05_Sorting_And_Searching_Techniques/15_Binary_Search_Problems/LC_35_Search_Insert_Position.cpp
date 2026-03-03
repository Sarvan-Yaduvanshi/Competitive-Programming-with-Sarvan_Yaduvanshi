/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-03 19:49:27
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

/* Problem: LC 35. Search Insert Position
   Difficulty: Easy
   Given a sorted array of distinct integers and a target value,
   return the index if the target is found. If not, return the index where it would be if it were inserted in order.

EXAMPLES:
   [1, 3, 5, 6], target=5 → 2 (exists at index 2)
   [1, 3, 5, 6], target=2 → 1 (insert between 1 and 3)
   [1, 3, 5, 6], target=7 → 4 (insert at end)
   [1, 3, 5, 6], target=0 → 0 (insert at beginning)

   Constraints:
   - 1 <= nums.length <= 10^4
   - -10^4 <= nums[i] <= 10^4
   - nums contains distinct values sorted in ascending order.
   - -10^4 <= target <= 10^4
*/

// This is exactly lower_bound!
// If target exists: return its index
// If not: return the index where it should be inserted
// Time: O(log n), Space: O(1)
int searchInsert(const vec<int> arr, int k){
    int lo = 0, hi = sz(arr);

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < k) lo = mid + 1;
        else hi = mid;
    }

    return lo;

    // STL version:
    // auto it = lower_bound(arr.begin(), arr.end(), k);
    // return it - arr.begin();
}

void solve() {
    int n, k;
    cin >> n >> k;
    vec<int> arr(n);
    read(arr);

    cout << searchInsert(arr, k) << nl;
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

