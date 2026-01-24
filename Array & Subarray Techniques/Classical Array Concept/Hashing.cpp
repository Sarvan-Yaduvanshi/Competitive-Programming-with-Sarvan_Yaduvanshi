/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-08 02:27:43
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

// Method 1: Brute-force frequency counter
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// NOTE: Works only for small constraints (n ≤ ~5000)
vec<pair<int, int>> countFreqBruteForce(const vec<int>& arr) {
    int n = sz(arr);

    // Marks whether index i has already been counted
    vec<char> visited(n, 0);

    // Stores (value, frequency)
    vec<pair<int, int>> ans;

    for (int i = 0; i < n; i++) {
        // Skip elements already processed
        if (visited[i]) continue;

        int cnt = 1;          // Current element counts itself
        visited[i] = 1;       // Mark current index as processed

        // Count occurrences of arr[i] in the remaining suffix
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                visited[j] = 1;   // Mark duplicate as processed
                cnt++;
            }
        }

        // Record frequency of arr[i]
        ans.pb({arr[i], cnt});
    }

    return ans;
}

// Frequency counter using hashing
// Average Time Complexity: O(N)
// Space Complexity: O(N)
// Suitable for large constraints (n up to ~2e5)
vec<pair<int, int>> countFreq(const vec<int>& arr) {
    unordered_map<int, int> freqCount;
    freqCount.reserve(sz(arr));
    freqCount.max_load_factor(0.7);

    // Count frequencies
    for (int val : arr)
        freqCount[val]++;

    vec<pair<int, int>> ans;
    ans.reserve(freqCount.size());

    // Collect results (order is unspecified)
    for (const auto &it : freqCount)
        ans.pb({it.fi, it.se});

    return ans;
}

void solve() {
    int n; cin >> n;
    vec<int> arr(n); read(arr);

    vec<pair<int, int>> ans = countFreqBruteForce(arr);
    for (auto &[val, cnt] : ans){
        cout << val << " : " << cnt << nl;
    }

    cout << "<-------- Using Map Freq count O(N) : -------->" << nl;

    vec<pair<int, int>> res = countFreq(arr);
    for (auto &[val, cnt] : res) cout << val << " : " << cnt << nl;

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

