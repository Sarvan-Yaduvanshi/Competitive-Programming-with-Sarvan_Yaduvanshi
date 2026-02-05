/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-03 23:58:16
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

// Approach 1: Sparse Difference Array (std::map)
// Time: O(N log N) | Space: O(N)
int maximumPopulation_Map(vvec<int>& logs){
    map<int, int> events;

    // 1. Record Events (O(N log N))
    for (const auto& log : logs){
        events[log[0]]++; // Birth
        events[log[1]]--; // Death
    }

    // 2. Sweep Line over sorted keys (O(N))
    int mx_pop = 0;
    int res_year = -1;
    int curr_pop = 0;

    for (const auto& [year, change] : events){
        curr_pop += change;

        if (curr_pop > mx_pop){
            mx_pop = curr_pop;
            res_year = year;
        }
    }

    return res_year;
}

// Approach 2: Event Sorting (The "Real" GM Way)
// Time: O(N log N) | Space: O(N)
int maximumPopulation_Sweep(vvec<int>& logs) {
    vec<pii> events; // pair<year, type>
    events.reserve(logs.size() * 2);

    // 1. Flatten intervals into points
    for (const auto& l : logs) {
        events.eb(l[0], 1);  // +1 Birth
        events.eb(l[1], -1); // -1 Death
    }

    // 2. Sort Events
    // Default pair sort: Sorts by Year first.
    // If Years equal, sorts by Type (-1 before 1).
    // This implies we process Deaths before Births in the same year.
    sort(all(events));

    int max_pop = 0;
    int res_year = -1;
    int curr_pop = 0;

    // 3. Linear Scan
    for (const auto& [year, change] : events) {
        curr_pop += change;
        if (curr_pop > max_pop) {
            max_pop = curr_pop;
            res_year = year;
        }
    }

    return res_year;
}

// Approach 3: Use Difference array + prefix sum + sweep line
// Time Complexity: O(N + Y) where Y is the range of years (100) -> Effectively O(N)
// Space Complexity: O(Y) -> O(1) constant space (size 101 or 2051)
int maximumPopulation(const vvec<int>& logs){
    // 1. Initialize Difference Array
    // Constraints are usually 1950 to 2050.
    int diff[2052] = {0};

    // 2. Populate Difference Array (O(N))
    for (const auto& person : logs){
        diff[person[0]] += 1; // Born +1
        diff[person[1]] -= 1; // Die -1
    }

    // 3. Sweep to find Max (O(Y))
    int mx_pop = 0;
    int res_year = 1950;
    int curr_pop = 0;

    for (int i = 1950; i <= 2050; i++){
        curr_pop += diff[i];

        if (curr_pop > mx_pop){
            mx_pop = curr_pop;
            res_year = i;
        }
    }
    return res_year;
}



void solve() {
    int n; cin >> n;

    vvec<int> logs(n, vec<int>(2));
    for (int i = 0; i < n; i++)
        cin >> logs[i][0] >> logs[i][1];

    int ans = maximumPopulation(logs);

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

