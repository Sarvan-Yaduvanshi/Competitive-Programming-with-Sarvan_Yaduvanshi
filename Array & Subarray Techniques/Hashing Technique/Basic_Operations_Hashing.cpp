/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-14 17:22:02
*/

#include <unordered_set>
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

// Part 1: FUNDAMENTALS - Understanding the Tools
// What are these data structures?
void solve_part1(){
    // SET - Stores UNIQUE elements only
    set<int> s; // Ordered (sorted), O(log n)
    unordered_set<int> us; // Unordered (hash-based), O(1) average

    // MAP - Stores KEY-VALUE pairs, UNIQUE keys
    map<int, int> mp; // Ordered (sorted by keys), O(log n)
    unordered_map<int, int> ump; // Unordered (hash-based), O(1)

    // MULTISET/MULTIMAP - Allows DUPLICATES
    multiset<int> ms; // Sorted, allows duplicates
    multimap<int, int> mmp; // Allows duplicate keys

    /*
     * Note: When to use what?
     * Set: Need unique elements, don't care about frequency
     * Map → Need to store associated data with keys
     * Ordered → Need sorted order OR range queries
     * Unordered → Just need fast lookup, no order needed
     */
}

// Part 2: MAP-Complete Operations
// Basic Operations
void solve_part2(){
    unordered_map<int, int> mp;

    // Insertion
    mp[5] = 10;                 // Method 1: Direct assignment
    mp.insert({3, 10});    // Method 2: insert()
    mp[5] = 15;                 // Updates value if key exists

    // Access
    cout << mp[5] << nl;    // Outputs: 15
    cout << mp[99];         // Creates key 99 with value 0 if doesn't exist!

    // SAFE ACCESS (doesn't create key)
    if (mp.find(99) != mp.end()){
        cout << mp[99];
    }

    // SAFE ACCESS (doesn't create key) Use contains() -> func
    if (mp.contains(99)){
        cout << mp[99];
    }

    // CHECK EXISTENCE
    if (mp.count(5))    // Method 1
        cout << "Key 5 exists";

    if (mp.find(5) != mp.end()) {   // Method 2 (preferred)
        cout << "Key 5 exists\n";
    }

    if (mp.contains(5)) {   // Method 3 (preferred C++20)
        cout << "Key 5 exists\n";
    }

    // Delection
    mp.erase(5);  // Remove key 5

    // size
    cout << map.size() << nl;

    // <------------- Set Operation --------------->
    set<int> s;

    // ===== INSERTION =====
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(2);  // Ignored (already exists)

    // Current set: {2, 5, 8} - automatically sorted!

    // ===== ACCESS/CHECK =====
    if (s.find(5) != s.end()) {
        cout << "5 exists\n";
    }

    if (s.count(5)) {  // Returns 0 or 1
        cout << "5 exists\n";
    }

    // ===== DELETION =====
    s.erase(5);  // Remove element
    auto it = s.find(8);
    if (it != s.end()) {
        s.erase(it);  // Remove using iterator
    }

    // ===== ITERATION (always sorted in set) =====
    for (int x : s) {
        cout << x << " ";
    }

    // Find Larget in set
    int larget = *s.rbegin();
}

// Iteration - Loop through Map
void solve_part3(){
    unordered_map<string, int> mp;
    mp["apple"] = 5;
    mp["banana"] = 10;
    mp["cherry"] = 15;

    // ===== METHOD 1: Auto (Best for C++11+) =====
    for (auto &it : mp) {
        cout << it.first << " -> " << it.second << "\n";
    }

    // ===== METHOD 2: Iterator =====
    for (auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->first << " -> " << it->second << "\n";
    }

    // ===== METHOD 3: Structured binding (C++17) =====
    for (auto &[key, value] : mp) {
        cout << key << " -> " << value << "\n";
    }
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

