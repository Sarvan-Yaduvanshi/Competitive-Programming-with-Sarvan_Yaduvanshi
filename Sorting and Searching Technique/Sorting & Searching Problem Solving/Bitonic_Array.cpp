/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-12 11:25:18
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

// inline i64 gcd(i64 a, i64 b) { return std::gcd(a, b); }
// inline i64 lcm(i64 a, i64 b) { return (a / std::gcd(a, b)) * b; }
//
// inline i64 modpow(i64 base, i64 exp, i64 mod = MOD) {
//     i64 res = 1;
//     base %= mod;
//     while (exp > 0) {
//         if (exp & 1) res = (res * base) % mod;
//         base = (base * base) % mod;
//         exp >>= 1;
//     }
//     return res;
// }
// Algorithm: Bitonic Array (Peak Finding Element)
// A bitonic array is a sequence with A[1] < A[2] < A[3] ... A[K] > A[K +1] > A[K + 2] ... A[N]
// Increasing than decreasing

// Algorithm: Bitonic Array (Peak Finding Element)
// Returns the index of the peak element
int peakFind(const vec<int>& arr) {
    int lo = 0;
    int hi = sz(arr) - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        // If A[mid] < A[mid+1], slope is increasing
        // Peak must exist on the right side
        if (arr[mid] < arr[mid + 1]) {
            lo = mid + 1;
        } else {
            // Slope is decreasing or mid itself is a peak
            // Do NOT discard mid
            hi = mid;
        }
    }
    // lo == hi points to a peak element
    return lo;
}

// Alterative Version Find Peak
/*
int findPeakElement(vector<int>& A) {
    // Compare mid with mid+1 → move toward the higher side, never drop mid if it can be the peak.
    int lo = 0;
    int hi = A.size() - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        // If A[mid] > A[mid+1], we are on a decreasing slope
        // Mid can be the peak, so keep it in the search space
        if (A[mid] > A[mid + 1]) hi = mid;
        // If A[mid] < A[mid+1], we are on an increasing slope
        // Peak must exist on the right side
        else lo = mid + 1;
    }

    // lo == hi points to a peak element
    return lo;
}
*/

// Increasing Binary Search
int increasingBS(const vector<int>& arr, int lo, int hi, int k) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] < k) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// Decreasing Binary Search
int decreasingBS(const vector<int>& arr, int lo, int hi, int k) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == k) return mid;
        else if (arr[mid] > k) lo = mid + 1; // Logic reversed for decreasing part
        else hi = mid - 1;
    }
    return -1;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vec<int> a(n); read(a);

    // Calculate peak ONCE outside the query loop
    int peak = peakFind(a);

    while (q--) {
        int k;
        cin >> k;

        vec<int> ans;

        // Search in the left (increasing) half: 0 to peak
        int p1 = increasingBS(a, 0, peak, k);
        // Search in the right (decreasing) half: peak + 1 to end
        int p2 = decreasingBS(a, peak + 1, n - 1, k);

        if (p1 != -1) ans.pb(p1 + 1); // Convert to 1-based index
        if (p2 != -1) ans.pb(p2 + 1);

        sort(all(ans));

        for (int x : ans) cout << x << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    int TC = 1;
    cin >> TC;
    while (TC--) solve();

    return 0;
}

