/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-02 21:48:36
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

#define v1(v, n) vec<i64> v(n)
#define take(v) for(auto &x : v) cin >> x
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

// ==========================================
//      METHOD 1: STL (The GM Choice)
// ==========================================
/*
   Complexity: Time O(N) | Space O(1)
   Why use it: It is highly optimized, concise, and less error-prone.
*/
template<typename T>
void reverseSTL(vec<T>& arr) {
    reverse(all(arr));
}

// ==========================================
//      METHOD 2: Two Pointers (Manual)
// ==========================================
/*
   Complexity: Time O(N) | Space O(1)
   Logic: Swap elements at 'start' and 'end' moving inward.
*/
template<typename T>
void reverseTwoPointers(vec<T>& arr) {
    int left = 0;
    int right = (int)arr.size() - 1;

    while (left < right) {
        // Swap values, not indices!
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}

// ==========================================
//      METHOD 3: Recursive (Interview)
// ==========================================
/*
   Complexity: Time O(N) | Space O(N) due to stack depth
   Note: GMs rarely use this in CP due to recursion overhead and stack overflow risk.
*/
template<typename T>
void reverseRecursive(vec<T>& arr, int start, int end) {
    if (start >= end) return;

    swap(arr[start], arr[end]);
    reverseRecursive(arr, start + 1, end - 1);
}

// ==========================================
//      METHOD 4: Using Auxiliary Stack
// ==========================================
/*
   Complexity: Time O(N) | Space O(N)
   Logic: Stack is LIFO (Last In First Out). Push all, then Pop all.
*/
template<typename T>
void reverseStack(vec<T>& arr) {
    stack<T> s;
    // 1. Push everything to stack
    for (T x : arr) s.push(x);

    // 2. Pop back to array
    for (int i = 0; i < (int)arr.size(); i++) {
        arr[i] = s.top();
        s.pop();
    }
}

// --- Helper to Print ---
template<typename T>
void printArray(const vec<T>& arr, string method) {
    cout << "[" << method << "]: ";
    for (const auto& val : arr) cout << val << " ";
    cout << nl;
}

void solve() {
    // Input
    int n;
    cin >> n;
    vec<i64> v(n);
    for(auto &x : v) cin >> x;

    // 1. Two Pointers (Manual Swap)
    vec<i64> v1 = v; // Copy to test
    reverseTwoPointers(v1);
    printArray(v1, "Two Pointers");

    // 2. Recursive
    vec<i64> v2 = v;
    reverseRecursive(v2, 0, n - 1);
    printArray(v2, "Recursive   ");

    // 3. Stack (Auxiliary Space)
    vec<i64> v3 = v;
    reverseStack(v3);
    printArray(v3, "Stack Method");

    // 4. STL (Best)
    vec<i64> v4 = v;
    reverseSTL(v4);
    printArray(v4, "STL Reverse ");
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

    // 1. Setup
    vector<int> a = {1, 2, 3, 4, 5};

    cout << "Original array 'a': ";
    for(int x : a) cout << x << " ";
    cout << "\n";

    // ---------------------------------------------------------
    // TRICK 1: Print backwards without touching 'a'
    // ---------------------------------------------------------
    cout << "Printing backwards: ";
    // it starts at 5. ++it moves to 4, then 3...
    for (auto it = a.rbegin(); it != a.rend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // Prove 'a' is not changed
    cout << "Is 'a' modified?  : " << (a[0] == 1 ? "No" : "Yes") << "\n";

    // ---------------------------------------------------------
    // TRICK 2: Create reversed vector 'b' in one line
    // ---------------------------------------------------------
    // The constructor reads 'a' from back to front and fills 'b'
    vector<int> b(a.rbegin(), a.rend());

    cout << "New vector 'b'    : ";
    for(int x : b) cout << x << " "; // Prints 5 4 3 2 1
    cout << "\n";

    return 0;
}

