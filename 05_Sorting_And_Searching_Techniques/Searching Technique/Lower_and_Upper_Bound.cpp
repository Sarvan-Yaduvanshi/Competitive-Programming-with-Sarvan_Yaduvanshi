/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-12 16:21:26
Fixed  : Binary Search Bounds
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

// ============================================================================
// BINARY SEARCH BOUNDS - GM LEVEL IMPLEMENTATION
// ============================================================================

// Algorithm: Lower Bound
// Definition: First position where arr[i] >= k (Greater than or Equal)
// Returns: Index of first element >= k, or n if all elements < k
// Invariant: All elements left of ans are < k, all elements >= ans are >= k
// Time Complexity: O(log N)
// Space Complexity: O(1)
// Example: arr = [1,2,2,3,5], k=2 → returns 1 (first occurrence of 2)
//          arr = [1,2,2,3,5], k=4 → returns 4 (first element >= 4 is 5)

int lowerBound(const vec<int>& arr, int k) {
    int n = sz(arr);
    int lo = 0, hi = n - 1;
    int ans = n;  // Default: no element >= k

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] >= k) {
            ans = mid;
            hi = mid - 1;  // Search left for earlier occurrence
        } else {
            lo = mid + 1;  // Search right
        }
    }

    return ans;
}

// Algorithm: Upper Bound
// Definition: First position where arr[i] > k (Strictly Greater)
// Returns: Index of first element > k, or n if all elements <= k
// Invariant: All elements left of ans are <= k, all elements >= ans are > k
// Time Complexity: O(log N)
// Space Complexity: O(1)
// Example: arr = [1,2,2,3,5], k=2 → returns 3 (first element > 2 is 3)
//          arr = [1,2,2,3,5], k=5 → returns 5 (no element > 5)

int upperBound(const vec<int>& arr, int k) {
    int n = sz(arr);
    int lo = 0, hi = n - 1;
    int ans = n;  // Default: no element > k

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > k) {
            ans = mid;
            hi = mid - 1;  // Search left for earlier occurrence
        } else {
            lo = mid + 1;  // Search right
        }
    }

    return ans;
}

// Algorithm: Equal Range (Combined Lower + Upper Bound)
// Definition: Returns pair of [lower_bound, upper_bound)
// Use Case: Find all occurrences of k in O(log N)
// Returns: {first position >= k, first position > k}
// Time Complexity: O(log N) - single pass finds both bounds
// Space Complexity: O(1)
// Example: arr = [1,2,2,2,5], k=2 → returns {1, 4} (range [1,4) contains all 2's)

pair<int, int> equalRange(const vec<int>& arr, int k) {
    int lb = lowerBound(arr, k);
    int ub = upperBound(arr, k);
    return {lb, ub};
}

// Algorithm: Distance (Count occurrences of k)
// Definition: Number of elements equal to k
// Formula: upper_bound(k) - lower_bound(k)
// Time Complexity: O(log N)
// Space Complexity: O(1)
// Example: arr = [1,2,2,2,5], k=2 → returns 3 (three 2's exist)

int distance(const vec<int>& arr, int k) {
    auto [lb, ub] = equalRange(arr, k);
    return ub - lb;
}

// ============================================================================
// C++ STL EQUIVALENTS
// ============================================================================
// lower_bound(arr.begin(), arr.end(), k) - returns iterator to first >= k
// upper_bound(arr.begin(), arr.end(), k) - returns iterator to first > k
// equal_range(arr.begin(), arr.end(), k) - returns pair of iterators [lb, ub)
// distance(it1, it2)                     - returns number of elements between iterators
//
// Usage:
//   auto it = lower_bound(all(arr), k);
//   int idx = it - arr.begin();  // Convert to index
//
//   auto [lb, ub] = equal_range(all(arr), k);  // C++17 structured binding
//   int count = distance(lb, ub);  // Count occurrences
//
// Note: STL functions return iterators, custom functions return indices
// ============================================================================

void solve() {
    // Test cases
    vec<int> arr = {1, 2, 2, 3, 5, 5, 7, 9};

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << nl << nl;

    // Test lower_bound
    cout << "=== LOWER BOUND (first position >= k) ===" << nl;
    for (int k : {0, 2, 4, 5, 10}) {
        int custom = lowerBound(arr, k);
        auto stl = lower_bound(all(arr), k);
        int stl_idx = stl - arr.begin();

        cout << "k=" << k << " → Custom: " << custom;
        if (custom < sz(arr)) cout << " (arr[" << custom << "]=" << arr[custom] << ")";
        cout << ", STL: " << stl_idx;
        if (stl_idx < sz(arr)) cout << " (arr[" << stl_idx << "]=" << arr[stl_idx] << ")";
        cout << " ✓" << (custom == stl_idx ? " MATCH" : " MISMATCH") << nl;
    }

    cout << nl << "=== UPPER BOUND (first position > k) ===" << nl;
    for (int k : {0, 2, 4, 5, 10}) {
        int custom = upperBound(arr, k);
        auto stl = upper_bound(all(arr), k);
        int stl_idx = stl - arr.begin();

        cout << "k=" << k << " → Custom: " << custom;
        if (custom < sz(arr)) cout << " (arr[" << custom << "]=" << arr[custom] << ")";
        cout << ", STL: " << stl_idx;
        if (stl_idx < sz(arr)) cout << " (arr[" << stl_idx << "]=" << arr[stl_idx] << ")";
        cout << " ✓" << (custom == stl_idx ? " MATCH" : " MISMATCH") << nl;
    }

    // Test equal_range
    cout << nl << "=== EQUAL RANGE (combined lower + upper) ===" << nl;
    for (int k : {2, 5, 8}) {
        auto [custom_lb, custom_ub] = equalRange(arr, k);
        auto [stl_lb, stl_ub] = equal_range(all(arr), k);
        int stl_lb_idx = stl_lb - arr.begin();
        int stl_ub_idx = stl_ub - arr.begin();

        cout << "k=" << k << " → Custom: [" << custom_lb << ", " << custom_ub << ")";
        cout << ", STL: [" << stl_lb_idx << ", " << stl_ub_idx << ")";
        cout << " ✓" << (custom_lb == stl_lb_idx && custom_ub == stl_ub_idx ? " MATCH" : " MISMATCH") << nl;
    }

    // Test distance (count occurrences)
    cout << nl << "=== DISTANCE (count occurrences) ===" << nl;
    for (int k : {2, 5, 8}) {
        int custom_count = distance(arr, k);
        auto [stl_lb, stl_ub] = equal_range(all(arr), k);
        int stl_count = std::distance(stl_lb, stl_ub);

        cout << "k=" << k << " → Custom count: " << custom_count;
        cout << ", STL count: " << stl_count;
        cout << " ✓" << (custom_count == stl_count ? " MATCH" : " MISMATCH") << nl;
    }

    // Count elements in range [L, R]
    cout << nl << "=== RANGE QUERY EXAMPLE ===" << nl;
    int L = 2, R = 5;
    int left = lower_bound(all(arr), L) - arr.begin();
    int right = upper_bound(all(arr), R) - arr.begin();
    cout << "Elements in [" << L << ", " << R << "]: " << (right - left) << nl;
    cout << "They are: ";
    for (int i = left; i < right; i++) cout << arr[i] << " ";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(10);

    solve();
    return 0;
}

