/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-03 21:42:58
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

/* Floor and Ceil in Sorted Array
 * Given a sorted array and a target value, find the floor and ceil of the target.
 * Floor: largest element <= target, Math term: greatest integer less than or equal to target
 * Ceil: smallest element >= target, Math term: least integer greater than or equal to target
 * Example:
 *   arr = [1, 3, 5, 7, 9 ], target = 6
 *   Floor = 5, Ceil = 7
 *   Explanation: 5 is the largest element less than or equal to 6, and 7 is the smallest element greater than or equal to 6.
 *
 *   Logic: Floor = upper_bound(target) - 1, Ceil = lower_bound(target)
 *   Time complexity: O(log n) for both floor and ceil using binary search.
 */

// Manal implementation Floor: largest element <= target
int findFloor(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid; // arr[mid] >= target, could be the answer
    }
    return lo;
}

// Manual implementation Ceil: first index with arr[index] > target
int findCeil(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void solve() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    read(arr);

    int floorIdx = findFloor(arr, target) - 1; // Floor index
    int ceilIdx = findCeil(arr, target);        // Ceil index

    if (floorIdx >= 0) {
        cout << "Floor: " << arr[floorIdx] << " at index " << floorIdx << nl;
    } else {
        cout << "Floor does not exist" << nl;
    }

    if (ceilIdx < n) {
        cout << "Ceil: " << arr[ceilIdx] << " at index " << ceilIdx << nl;
    } else {
        cout << "Ceil does not exist" << nl;
    }

    cout << "<--------------------- Using STL -------------------->" << nl;
    // Using STL
    auto floorIt = ranges::upper_bound(arr, target);
    auto ceilIt = ranges::lower_bound(arr, target);

    if (floorIt != arr.begin()) {
        --floorIt;
        cout << "STL Floor: " << *floorIt << " at index " << (floorIt - arr.begin()) << nl;
    } else {
        cout << "STL Floor does not exist" << nl;
    }

    if (ceilIt != arr.end()) {
        cout << "STL Ceil: " << *ceilIt << " at index " << (ceilIt - arr.begin()) << nl;
    } else {
        cout << "STL Ceil does not exist" << nl;
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

