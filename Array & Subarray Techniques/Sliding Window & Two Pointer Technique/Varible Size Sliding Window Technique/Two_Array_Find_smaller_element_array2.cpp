/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-26 13:13:22
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

/* Problem: Give 2 sorted arrays, for each element in the first array,
 * find the number of elements in the second array that are smaller than it.
 * Example: 1
 * Input: A = [1, 3, 5], B = [2, 4, 6]
 * Output: [0, 1, 2]
 * Explanation: For 1, there are 0 elements in B smaller than it. For 3, there is 1 element (2) in B smaller than it. For 5, there are 2 elements (2 and 4) in B smaller than it.
 *
 * Example: 2
 * Input: A = [2, 4, 6, 10, 14, 17], B = [1, 3, 5, 7, 9, 11, 13, 15, 17]
 * Output: [1, 2, 5, 7, 9, 9]
 *
 * Constraints:
 * - 1 <= len(A), len(B) <= 10^5
 * - 1 <= A[i], B[i] <= 10^9
 * - Both A and B are sorted in non-decreasing order.
 */

// Approach 1: Custom Binary Search (Writing the Logic)
// Time Complexity: O(n log m) | Space Complexity: O(1)
int binarySearch(const vec<int>& arr2, int k){
    int lo = 0;
    int hi = sz(arr2);

    while (lo < hi){
        int mid = lo + (hi - lo) / 2;

        if (arr2[mid] < k) lo = mid + 1;
        else hi = mid;
    }

    return lo;
}
vec<int> cntSmaller(const vec<int>& arr1, const vec<int>& arr2){
    vec<int> ans;

    for (int x : arr1){
        ans.pb(binarySearch(arr2, x));
    }

    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<int> arr1(n), arr2(m);
    read(arr1);
    read(arr2);

    vec<int> result = cntSmaller(arr1, arr2);

    for (int x : result) {
        cout << x << " ";
    }
    cout << nl;
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

