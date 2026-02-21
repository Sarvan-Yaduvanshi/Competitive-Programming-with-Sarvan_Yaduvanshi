/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-21 22:45:07
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

// Problem: Remove Spaces from a String
// Given a string, remove all spaces from it and return the resulting string.
// Example:
// Input: "Hello World"
// Output: "HelloWorld"

// Approach 1: New String" Method (Beginner)
// Memory: O(n) for the new string, Time: O(n) for iterating through the original string.
string removeSpacesNaive(string s){
    string ans = "";
    for (const char ch : s){
        if (ch != ' ')
            ans += ch;
    }

    return ans;
}

// Approach 2: The Two-Pointer Method (Intermediate)
// Memory: O(1) for in-place modification, Time: O(n) for iterating through the string.
string removeSpacesTwoPointer(string s){
    int n = sz(s);
    int j = 0; // The "write" index

    for (int i = 0; i < n; i++){
        if (s[i] != ' '){
            s[j++] = s[i]; // Overwrite character at j with character at i
        }
    }

    // Resize to cut off the garbage characters left at the end
    s.resize(j);
    return s;
}

// Approach 3: The STL "Erase-Remove" Idiom (Expert)
// Memory: O(1) for in-place modification, Time: O(n) for iterating through the string.
string removeSpacesSTL(string s){
    // The "Erase-Remove" Idiom
    s.erase(remove(all(s), ' '), s.end());
    return s;
}

// Approach 4: GM Level (Modern C++ & Optimization)
// Memory: O(1) for in-place modification, Time: O(n) for iterating through the string.
string removeSpacesOptimized(string s){
    // C++20 approach using lambda function
    // std::erase_if is cleaner than erase-remove
    erase_if(s, [](char c) {
        return isspace(static_cast<unsigned char>(c));
    });
    return s;
}


void solve() {
    string input;
    cout << "Enter a string with spaces: ";
    getline(cin, input); // Read the entire line including spaces
    cout << "Original String: \"" << input << "\"" << nl;
    cout << "After Removing Spaces (Naive): \"" << removeSpacesNaive(input) << "\"" << nl;
    cout << "After Removing Spaces (Two-Pointer): \"" << removeSpacesTwoPointer(input) << "\"" << nl;
    cout << "After Removing Spaces (STL): \"" << removeSpacesSTL(input) << "\"" << nl;
    cout << "After Removing Spaces (Optimized): \"" << removeSpacesOptimized(input) << "\"" << nl;
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

