/*
Author: Sarvan.DP.GrandMaster
Created : 2026-03-06 11:15:41
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

/* Problem: Fair Workload
 * Given an array of workloads, split it among K workers, such that maximum work that any worker has to do is minimized.
 * (can't change order of workloads).
 * Example: workloads = [10, 20, 30, 40, 50, 60, 70, 80, 90], K = 3
 * Dry Run (K=3):  10, 20, 30, 40, 50 | 60, 70 | 80, 90
 * First worker does 150, second does 130, third does 170 → max is 170.
 * Is it possible to partition the workload in a way that the highest workload of any worker is less than 170?
 * Answer: No. 170 is the absolute optimal minimum max workload for 3 workers.
 */

// Approach: Binary Search on Answer
bool possible(const vector<int>& workloads, int maxWorkload, int k) {
    int usedWorkers = 1; // Start with one worker
    int currentLoad = 0;

    for (const auto& workload : workloads) {
        // Single workload exceeds max limit, entirely impossible
        if (workload > maxWorkload) return false;

        // If we can add this task to the current worker without breaking the limit
        if (currentLoad + workload <= maxWorkload) {
            currentLoad += workload;
        } else {
            // Otherwise, we need a new worker
            usedWorkers++;
            if (usedWorkers > k) return false; // Need more workers than we have

            // The new worker's load starts exactly with this task
            currentLoad = workload;
        }
    }

    return true; // All workloads assigned within maxWorkload and k workers
}
void solve() {
    int n, k; cin >> n >> k;

    vec<int> workloads(n);
    read(workloads);

    int lo = 0;

    // The maximum possible workload for any worker is if one worker does all the work
    i64 hi = accumulate(all(workloads), 0LL);
    i64 ans = hi; // Store the best answer found

    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if (possible(workloads, mid, k)){
            ans = mid; // Update answer
            hi = mid - 1; // Try to find a smaller maximum workload
        } else {
            lo = mid + 1; // Need to allow more workload per worker
        }
    }

    cout << ans << nl;
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

