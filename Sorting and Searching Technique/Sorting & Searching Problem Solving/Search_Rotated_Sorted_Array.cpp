/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-12 19:57:43
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <numeric>
#include <random>
#include <chrono>

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

/*
 * Binary Search on Rotated Sorted Array (Recursive)
 *
 * At each step, one half of the array is sorted.
 * We recurse only into the half that can contain the target.
 *
 * Time Complexity: O(log N)
 * Space Complexity: O(log N)  // recursion stack
 */
int searchInRotatedArray(const vec<int>& a, int si, int en, int k) {
    // Base Case
    if (si > en)
        return -1;

    int mid = si + (en - si) / 2;

    // Case Found
    if (a[mid] == k) return mid;

    // mid-on Line1
    if (a[si] <= a[mid]) {
        // Case a : Left Part
        if (a[si] <= k && k <= a[mid]) {
            return searchInRotatedArray(a, si, mid - 1, k);
        } else {
            // Case b : Right Part
            return searchInRotatedArray(a, mid + 1, en, k);
        }
    }
    // mid-on Line2
    else {
        // Case c : Right Part
        if (a[mid] <= k && k <= a[en]) {
            return searchInRotatedArray(a, mid + 1, en, k);
        } else {
            // Case d : Left Part
            return searchInRotatedArray(a, si, mid - 1, k);
        }
    }
}

void solve() {
    int n; cin >> n;
    vec<int> a(n); read(a);

    int k; cin >> k;
    int ans = searchInRotatedArray(a, 0, n - 1, k);
    cout << ans << nl;

    /*
    * Binary Search on Rotated Sorted Array (Iterative)
    *
    * In every iteration, one sorted half is identified and the
    * other half is discarded based on target position.
    *
    * Time Complexity: O(log N)
    * Space Complexity: O(1)
    */

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

