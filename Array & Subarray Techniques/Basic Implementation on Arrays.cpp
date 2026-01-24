/*
Author: Sarvan.DP.GrandMaster
Created : 2026-01-02 17:13:57
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

// =========================
//  MANUAL ARRAY OPERATIONS
// =========================
// NOTE: In real CP contests, we usually use std::vector.
// These functions demonstrate the underlying logic of shifting elements.

// Forward Traversal | Time: O(N)
void forwardTraversal(const vector<int>& arr) {
    for (int i = 0; i < sz(arr); i++) {
        cout << arr[i] << " ";
    }
    cout << nl;
}

// Range-based Traversal | Time: O(N)
void traverseRange(const vector<int>& arr) {
    for (auto val : arr) {
        cout << val << " ";
    }
    cout << nl;
}

// Backward Traversal | Time: O(N)
void backwardTraversal(const vector<int>& arr) {
    for (int i = sz(arr) - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << nl;
}

// Insert at Beginning (Shifting Required) | Time: O(N)
void insertAtBeginning(int arr[], int& n, int capacity, int value) {
    if (n >= capacity) {
        cout << "[Error] Array is full!" << nl;
        return;
    }
    // Shift all elements to the right to make space at index 0
    for (int i = n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = value;
    n++;
}

// Insert at End | Time: O(1)
void insertAtEnd(int arr[], int& n, int capacity, int value) {
    if (n >= capacity) {
        cout << "[Error] Array is full!" << nl;
        return;
    }
    arr[n] = value;
    n++;
}

// Insert at Specific Position | Time: O(N)
void insertAtPosition(int arr[], int& n, int capacity, int pos, int value) {
    if (n >= capacity) {
        cout << "[Error] Array is full!" << nl;
        return;
    }
    if (pos < 0 || pos > n) {
        cout << "[Error] Invalid position!" << nl;
        return;
    }
    // Shift elements from 'pos' to the right
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    n++;
}

// Delete from Beginning | Time: O(N)
void deleteFromBeginning(int arr[], int& n) {
    if (n == 0) {
        cout << "[Error] Array is empty!" << nl;
        return;
    }
    // Shift elements to the left to overwrite index 0
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
}

// Delete from End | Time: O(1)
void deleteFromEnd(int arr[], int& n) {
    if (n == 0) {
        cout << "[Error] Array is empty!" << nl;
        return;
    }
    n--; // Logical deletion
}

// Delete from Position | Time: O(N)
void deleteFromPosition(int arr[], int& n, int pos) {
    if (n == 0 || pos < 0 || pos >= n) {
        cout << "[Error] Invalid Request!" << nl;
        return;
    }
    // Shift left to fill the gap
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
}

// Delete by Value | Time: O(N)
void deleteByValue(int arr[], int& n, int value) {
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        cout << "Value " << value << " not found!" << nl;
        return;
    }
    deleteFromPosition(arr, n, pos);
}

// =========================
//        MAIN SOLVER
// =========================

void demonstrateManualOperations() {
    cout << "--- Manual Array Implementation ---" << nl;
    const int CAPACITY = 10;
    int arr[CAPACITY] = {10, 20, 30, 40};
    int n = 4;

    cout << "Original: ";
    for(int i=0; i<n; ++i) cout << arr[i] << " "; cout << nl;

    insertAtBeginning(arr, n, CAPACITY, 5);
    cout << "After Insert 5 at Start: ";
    for(int i=0; i<n; ++i) cout << arr[i] << " "; cout << nl;
}

void demonstrateSTLOperations() {
    cout << nl << "--- STL Vector Implementation (CP Standard) ---" << nl;

    vector<int> v = {10, 20, 30, 40, 50};

    // 1. Insertion
    v.insert(v.begin(), 5);      // O(N) - Insert at Start
    v.push_back(60);             // O(1) - Insert at End (Preferred)
    v.insert(v.begin() + 2, 99); // O(N) - Insert at Index 2

    // 2. Deletion
    v.erase(v.begin());          // O(N) - Delete First
    v.pop_back();                // O(1) - Delete Last (Preferred)
    v.erase(v.begin() + 2);      // O(N) - Delete Index 2

    // 3. Delete by Value (Requires Algorithm)
    // Idiom: remove-erase
    auto it = remove(all(v), 30); // Moves 30 to end, returns new logical end
    v.erase(it, v.end());         // Physically removes the garbage at end

    cout << "Final Vector: ";
    for (int x : v) cout << x << " ";
    cout << nl;
}

void solve() {
    demonstrateManualOperations();
    demonstrateSTLOperations();

    /*

    vector<int> v;
    v.push_back(2); // [2]
    v.push_back(3); // [2, 3]
    v.push_back(5); // [2, 3, 5]
    v.push_back(7); // [2, 3, 5, 7]
    v[1] = 4; // sets element at index 1 to 4 --> [2, 4, 5, 7]
    v.erase(v.begin() + 1); // removes element at index 1 -> [2, 5, 7]
    // this remove method is O(n); to be avoided
    v.push_back(8); // [2, 5, 7, 8]
    v.erase(v.end() - 1); // [2, 5, 7]
    // here, we remove the element from the end of the list; this is O(1).
    v.push_back(4); // [2, 5, 7, 4]
    v.push_back(4); // [2, 5, 7, 4, 4]
    v.push_back(9); // [2, 5, 7, 4, 4, 9]
    cout << v[2] << nl; // print value index 2 --> 7
    v.erase(v.begin(), v.begin() + 3); // [4, 4, 9]
    // this erases the first three elements; O(n)

    // In a dynamic array, we can also add and delete
    // elements at the end in O(1) time.
    // However, we need to be careful that we only add elements to the end of the vector;
    // insertion and deletion in the middle of the vector is O(n)
    for (auto val : v) cout << val << " ";

    */
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);

    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}
