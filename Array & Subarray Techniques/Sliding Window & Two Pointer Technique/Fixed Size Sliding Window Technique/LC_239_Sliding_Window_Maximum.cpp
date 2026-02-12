/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-11 18:35:21
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

/* Problem: For every window of size k, return maximum element.
 * Example:- nums = [1,3,-1,-3,5,3,6,7], k = 3
* Window position                Max
* ---------------               -----
* [1  3  -1] -3  5  3  6  7       3
*  1 [3  -1  -3] 5  3  6  7       3
*  1  3 [-1  -3  5] 3  6  7       5
*  1  3  -1 [-3  5  3] 6  7       5
*  1  3  -1  -3 [5  3  6] 7       6
*  1  3  -1  -3  5 [3  6  7]      7
*  Answer -> [3 3 5 5 6 7]
*/

// Approach 1: Brute Force
// TC -> O(N * k) | SC -> O(k)
vec<int> maxSlidingWindowBruteForce(const vec<int>& arr, int k){
    int n = sz(arr);

    int mxNum = INT_MIN;
    vec<int> ans;

    for (int i = 0; i <= n - k; i++){
        int currMax = INT_MIN;
        for (int j = i; j < i + k; j++){
            currMax = max(currMax, arr[j]);
        }
        ans.pb(currMax);
    }
    return ans;
}

// Approach 2: Using Max Heap (Priority Queue)
// Time Complexity -> O(N logK) || Space Complexity -> O(K)
vec<int> maxSlidingWindowMaxHeap(const vec<int>& arr, int k){
    int n = sz(arr);
    vec<int> ans;
    priority_queue<pii> pq; // max heap -> store {value, index}

    for (int i = 0; i < n; i++){
        // Step 1: add curr element
        pq.push({arr[i], i});

        // Step 2: Remove out-of-window elements
        while (!pq.empty() && pq.top().se <= i - k)
            pq.pop();

        // Step 3: Answer
        if (i >= k - 1) ans.pb(pq.top().fi);
    }
    return ans;
}

// Approach 3: Using Multiset + Sliding Window Concept
// Time Complexity -> O(N logK) || Space Complexity -> O(K)
vec<int> maxSlidingWindowMultiSet(const vec<int>& arr, int k){
    int n = sz(arr);

    vec<int> ans;
    multiset<int> ms; // store value in sorted order | allow duplicate value

    for (int i = 0; i < n; i++){
        // Step 1: add a[i] to window
        ms.insert(arr[i]); // o(logk)

        // Step 2: remove a[i - k]
        if (i >= k){
            // delete only one occurrence
            ms.erase(ms.find(arr[i - k])); // o(logk)
        }

        // Step 3: Update Answer
        if (i >= k - 1){
            int largest = *ms.rbegin(); // o(1)
            ans.pb(largest);
        }
    }

    return ans;
}

// Approach 4: Monotonic Deque (Index Only)
// TC -> O(N) | SC -> O(K) (Only stores indices)
vec<int> maxSlidingWindowDeque(const vec<int>& arr, int k){
    int n = sz(arr);

    vec<int> ans;
    deque<int> deq;

    for (int i = 0; i < n; i++){
        // 1. MAINTAIN ORDER (Monotonic Decreasing)
        // Remove indices of elements that are smaller than the current element
        // because they can never be the maximum again.
        while (!deq.empty() && arr[deq.back()] <= arr[i])
            deq.pop_back();

        // 2. ADD current index
        deq.pb(i);

        // 3. REMOVE expired index
        // The element at the front is the largest. Check if it's out of the window.
        // Current window is [i-k+1 ... i]. If front == i-k, it's gone.
        if (deq.front() == i - k)
            deq.pop_front();

        // 4. ANSWER
        // The front of the deque ALWAYS has the index of the maximum element.
        if (i >= k - 1)
            ans.push_back(arr[deq.front()]);
    }
    return ans;
}



void solve() {
    
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

