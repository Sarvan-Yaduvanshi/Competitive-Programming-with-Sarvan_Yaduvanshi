/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-09 18:34:32
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

// Approach 1: Brute Force
// TC -> O(N^2) | SC -> O(K)
vec<int> firstNegInt(const vec<int>& arr, int k) {
    int n = sz(arr);
    vec<int> ans;

    for (int i = 0; i <= n - k; i++) {
        bool flag = false;
        for (int j = i; j < i + k; j++) {
            if (arr[j] < 0) {
                ans.push_back(arr[j]);
                flag = true;
                break;
            }
        }
        if (!flag) ans.push_back(0);
    }
    return ans;
}

// Approach 2: Sliding Window + Deque (Optimized)
// TC -> O(N) | SC -> O(K) (Deque stores useful indices only)
vec<int> firstNegIntOptimal(const vec<int>& arr, int k){
    int n = sz(arr);

    deque<int> dq; // store indices of negative number
    vec<int> ans; // store answer

    for (int i = 0; i < n; i++){
        // 1. if curr element is negative, add its idx
        if (arr[i] < 0) dq.pb(i);

        // 2. Remove: Current window is [i-k+1 ... i]. So index <= i-k is expired
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // 3. Answer: Only record answer once first window is formed
        if (i >= k - 1){
            if (dq.empty()) ans.pb(0); // No negative number in this window
            else ans.pb(arr[dq.front()]); // Front is always the first valid negative
        }
    }
    return ans;
}

// Approach 3: Two-Pointer Optimization (The "Smart Caterpillar")
// why O(N) -> Even though there is a nested loop, the inner pointer only moves forward and never resets, so total operations are linear
// TC -> O(N) (Amortized) || SC -> O(1) (Auxiliary Space)
vec<int> firstNegIntPointerTrick(const vec<int>& arr, int k){
    int n = sz(arr);

    vec<int> ans;
    int firstNegIdx = 0; // Track idx of first negative number

    for (int i = 0; i <= n - k; i++){
        // Optimization: if last idx negative found than curr window start
        // // we must jump it forward to at least 'i'
        if (firstNegIdx < i) firstNegIdx = i;

        // Search Forward: Find the next negative number inside the current window [i ... i+k-1]
        // Note: We don't reset 'firstNegIdx' to 'i' every time. We continue from where we left off!
        while (firstNegIdx < i + k && arr[firstNegIdx] >= 0)
            firstNegIdx++;

        // Logic: Did we find a negative number inside valid range?
        if (firstNegIdx < i + k) ans.pb(arr[firstNegIdx]); // Found one!
        else ans.pb(0); // Window has no negative numbers
    }

    return ans;
}
void solve() {
    int n, k;
    cin >> n >> k;

    vec<int> a(n);
    read(a);

    vec<int> ans = firstNegIntOptimal(a, k);
    cout << "[";
    for (int i = 0; i < sz(ans); i++)
        cout << ans[i] << (i + 1 == sz(ans) ? "" : ", ");
    cout << "]" << nl;
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

