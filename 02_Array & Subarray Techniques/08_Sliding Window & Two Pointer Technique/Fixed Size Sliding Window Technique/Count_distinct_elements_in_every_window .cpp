/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-10 00:23:34
*/

#include <unordered_set>
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
/* Given an integer array arr[] and a number k.
 * Find the count of distinct elements in every window of size k in the array.
 * Example:- arr = [1 2 1 3 4 2 3], k = 4
 * First window is [1, 2, 1, 3], count of distinct numbers is 3.
 * Second window is [2, 1, 3, 4] count of distinct numbers is 4.
 * Third window is [1, 3, 4, 2] count of distinct numbers is 4.
 * Fourth window is [3, 4, 2, 3] count of distinct numbers is 3
 * Answer -> [3 4 4 3]
 */

// Approach 1: Brute force + set
// TC -> O(N * K) | TC -> O(k)
vec<int> countDistinct(const vec<int> &arr, int k){
    int n = sz(arr);
    vec<int> ans;

    for (int i = 0; i <= n - k; i++){
        unordered_set<int> st;
        for (int j = i; j < i + k; j++){
            st.insert(arr[j]);
        }
        ans.pb(st.size());
    }
    return ans;
}

// Approach 2: Sliding Window + Frequency Map (GM Style)
// TC -> O(N) | SC -> O(K) or O(Max_Value)
// Note: Use vector<int> freq if values are <= 10^6 for O(1) strict access.
vec<int> countDistinctOptimal(const vec<int>& arr, int k){
    int n = sz(arr);

    // GM Tip: If constraints are small (e.g., arr[i] <= 10^5), use this:
    // vector<int> freq(100001, 0);
    // Otherwise use map:
    unordered_map<int, int> freq; // freq count;
    vec<int> ans; // answer store
    int distinct_cnt = 0;

    for (int i = 0; i < n; i++){
        // 1. ACQUIRE (Add new element to window)
        // If it's the first time we see this number in current window, distinct++
        if (freq[arr[i]] == 0) distinct_cnt++;
        freq[arr[i]]++;

        // If frequency drops to 0, it is no longer in the window
        if (i >= k){
            int removal_val = arr[i - k];
            freq[removal_val]--;

            if (freq[removal_val] == 0) {
                distinct_cnt--;
                // Optional: freq.erase(remove_val) to save map space
            }
        }

        // 3. RECORD ANSWER
        // We have a full window of size k starting from i = k - 1
        if (i >= k - 1) ans.pb(distinct_cnt);
    }
    return ans;
}

void solve() {
    int n, k; cin >> n >> k;
    vec<int> arr(n);
    read(arr);

    vec<int> ans = countDistinctOptimal(arr, k);
    cout << "[";
    for (int i = 0; i < sz(ans); i++){
        cout << ans[i] << (i + 1 == sz(ans) ? "" : ", ");
    }
    cout << "]";
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

