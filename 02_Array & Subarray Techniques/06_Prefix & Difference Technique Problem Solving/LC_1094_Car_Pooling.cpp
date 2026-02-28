/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-03 18:40:56
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

// Approach 1 : Coordinate Compression / Sweep Line
// Complexity: O(N log N) Time | O(N) Space
// GM Note: This is the most robust solution for sparse coordinates (e.g., location up to 10^9).
bool carPooling_Sweep(vvec<int>& trips, int capacity) {
    vec<pii> events;
    events.reserve(trips.size() * 2); // Optimization: Prevent dynamic reallocation

    for (const auto& t : trips) {
        events.eb(t[1], t[0]);  // pickup
        events.eb(t[2], -t[0]); // drop
    }

    // Step 2: sort by location
    sort(all(events));

    // Step 3: sweep line
    int curr_load = 0;
    for (const auto& [loc, change] : events) {
        curr_load += change;
        if (curr_load > capacity) return false;
    }
    return true;
}

// Approach 2 : Difference Array (Static Range Update) (Optimal)
// Complexity: O(N + M) Time | O(M) Space where M is coordinate range (1001)
// GM Note: Best for dense/small coordinate ranges. Beats O(N log N) by avoiding sort.
bool carPooling_DiffArray(vvec<int>& trips, int capacity) {
    int diff[1002] = {0};

    for (const auto& t : trips) {
        diff[t[1]] += t[0]; // Range update start
        diff[t[2]] -= t[0]; // Range update end (exclusive)
    }

    int curr_load = 0;
    for (int i = 0; i <= 1000; ++i) {
        curr_load += diff[i];
        if (curr_load > capacity) return false;
    }
    return true;
}

// Approach 3 : Map-based Difference Array
// Complexity: O(N log N) Time | O(N) Space
bool carPooling_Map(vvec<int>& trips, int capacity) {
    map<int, int> events;

    for (const auto& t : trips) {
        events[t[1]] += t[0];
        events[t[2]] -= t[0]; // Fix: Must subtract at drop-off
    }

    int curr_load = 0;
    for (const auto& [loc, delta] : events) {
        curr_load += delta;
        if (curr_load > capacity) return false;
    }
    return true;
}

void solve() {
    int n; cin >> n;

    // 2. Read Trips: [numPassengers, from, to]
    vvec<int> trips(n, vec<int>(3));
    for(int i = 0; i < n; ++i) {
        cin >> trips[i][0] >> trips[i][1] >> trips[i][2];
    }

    // 3. Read Capacity
    int capacity;
    cin >> capacity;

    // 4. Output Result
    // Using the Difference Array approach (Optimal)
    if (carPooling_DiffArray(trips, capacity)) {
        cout << "true" << nl;
    } else {
        cout << "false" << nl;
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

