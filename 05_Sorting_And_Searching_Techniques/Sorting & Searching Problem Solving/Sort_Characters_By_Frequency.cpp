/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-22 01:06:12
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

// Approach 1 : Use Costume Comparator
// TC -> O(N logN) | SC -> O(1)
string frequencySort(string &s){
    unordered_map<char, int> freq;
    for (char ch : s) freq[ch]++;

    sort(all(s), [&](char a, char b){
        if (freq[a] != freq[b]) return freq[a] > freq[b];
        return a < b;
    });

    return s;
}

// Approach 2 : Using Counting Sort
// TC -> O(N logN) | SC -> O(1)
string freqCountingSort(string &s){
    int n = sz(s);

    vec<int> freq(256, 0);
    for (char ch : s) freq[(unsigned char)ch]++;

    vec<vec<char>> bucket(n + 1);
    for (int ch = 0; ch < 256; ch++){
        if (freq[ch] > 0) bucket[freq[ch]].pb((char) ch);
    }

    string ans = "";
    for (int i = n; i >= 1; i++){
        for (char ch : bucket[i]){
            ans += string(i, ch);
        }
    }

    return ans;
}
void solve() {
    string s; cin >> s;
    // s = frequencySort(s);
    s = freqCountingSort(s);
    cout << s << nl;

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

