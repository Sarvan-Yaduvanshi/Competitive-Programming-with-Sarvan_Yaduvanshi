// Author: sarvan.dp.grandmaster
// Created: 2026-03-18 22:19:57
// Problem: B. Heapify 1
// Contest: Codeforces - Codeforces Round 1080 (Div. 3)
// URL: https://codeforces.com/contest/2195/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms

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

/*
Problem: Codeforces 2195B - Heapify 1
URL: https://codeforces.com/contest/2195/problem/B
You are given a permutation a of length n.

You can perform the following operation any number of times (possibly zero):
  - Select an index i (1 <= i <= n / 2), and swap a_i and a_{2i}.

For example, when a = [1, 4, 2, 3, 5],
you can swap a_2 and a_4 to make it [1, 3, 2, 4, 5],
but you cannot swap a_2 and a_3.

Determine if the sequence a can be sorted in increasing order.

Input:
Each test contains multiple test cases.
The first line contains the number of test cases t (1 <= t <= 10^4).
The first line of each test case contains a single integer n (1 <= n <= 2 * 10^5).
The second line of each test case contains n distinct integers a_1, a_2, ..., a_n (1 <= a_i <= n).
It is guaranteed that the sum of n over all test cases does not exceed 2 * 10^5.

Output:
If a can be sorted in increasing order, output "YES".
Otherwise, output "NO".

Concept diagram (who can swap with whom):
indices form independent chains by repeatedly doubling:

                1
              /   \
             2     3
            / \   / \
           4   5 6   7
          /\
         8  9

Allowed direct swap edges are only (i <-> 2i):
1<->2, 2<->4, 4<->8, ... and similarly for every starting index.
So each chain is: i, 2i, 4i, 8i, ... (while <= n).

Key check:
Inside each chain, values can be permuted arbitrarily via adjacent swaps on that chain,
so sorted(values_on_chain) must equal sorted(indices_on_chain).
*/

void solve() {
    int n; cin >> n;
    
    vec<int> a(n);
    read(a);
    
    vec<bool> vis(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        
        vec<int> idx, val;
        
        // Collect one doubling-chain: i, 2i, 4i, 8i, ...
        int j = i;
        while (j <= n) {
            idx.pb(j);
            val.pb(a[j - 1]);
            vis[j] = true;
            j *= 2;
        }
        
        sort(all(idx));
        sort(all(val));
        
        for (int k = 0; k < sz(idx); k++) {
            if (idx[k] != val[k]) {
                cout << "NO" << nl;
                return;
            }
        }
    }
    
    cout << "YES" << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    
    return 0;
}