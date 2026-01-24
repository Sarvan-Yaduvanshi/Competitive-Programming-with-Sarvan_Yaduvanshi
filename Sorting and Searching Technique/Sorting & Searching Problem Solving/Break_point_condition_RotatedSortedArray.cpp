/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-13 13:06:50
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
using ld = long double;
template<class T>
using vec = vector<T>;
template<class T>
using vvec = vector<vector<T>>;
using pii = pair<int, int>;
using pll = pair<i64, i64>;

// --- Constants ---
constexpr i64 INF64 = 4e18;
constexpr int INF32 = 2e9;
constexpr i64 MOD = 1'000'000'007LL;
constexpr i64 MOD9 = 998'244'353LL;
constexpr ld PI = 3.14159265358979323846;

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
void read(vec<T>& v){
    for (auto& x : v) cin >> x;
}

#define nl '\n'
#define YES cout << "YES" << nl
#define NO cout << "NO" << nl

inline i64 gcd(i64 a, i64 b){ return std::gcd(a, b); }
inline i64 lcm(i64 a, i64 b){ return (a / std::gcd(a, b)) * b; }

inline i64 modpow(i64 base, i64 exp, i64 mod = MOD){
    i64 res = 1;
    base %= mod;
    while (exp > 0){
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Method 1 : Simple Linear Method
// Time Complexity -> O(N)
// Space Complexity -> O(N)
vec<int> restoreOriginal(const vec<int>& a){
    int n = sz(a);

    int pivotIdx = 0;
    for (int i = 0; i < n - 1; i++){
        if (a[i] > a[i + 1]){
            pivotIdx = i + 1;
            break;
        }
    }

    vec<int> ans;
    for (int i = pivotIdx; i < n; i++) ans.pb(a[i]); // Right part
    for (int i = 0; i < pivotIdx; i++) ans.pb(a[i]); // Left part

    return ans;
}

bool isSortedOrRotated(const vector<int>& a) {
    int n = a.size();
    int breaks = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > a[(i + 1) % n]) breaks++;
        if (breaks > 1) return false;
    }
    return true;
}

// Method 2 : Use Binary Search
// Time Complexity -> O(logN)
// Space Complexity -> O(N)
vector<int> restoreOriginal(vector<int> a) {
    int n = a.size();
    if (n == 0) return {};

    // if not valid rotated-sorted -> return empty or handle as you want
    if (!isSortedOrRotated(a)) return {};

    // Find pivot (index of minimum) - duplicate safe
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (a[mid] < a[hi]) hi = mid;
        else if (a[mid] > a[hi]) lo = mid + 1;
        else hi--; // duplicates case
    }

    int pivot = lo;

    vector<int> ans;
    for (int i = pivot; i < n; i++) ans.push_back(a[i]);
    for (int i = 0; i < pivot; i++) ans.push_back(a[i]);

    return ans;
}


void solve(){
    int n; cin >> n;
    vec<int> a(n); read(a);


}


int main(){
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

