/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 11:00:00
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

// =============================================================================
//  MODULE 05: ARRAY ROTATION CONCEPTS
//  Level: ⭐⭐ Intermediate
//  Topics: Left/Right rotation, reversal algo, juggling, cyclic, std::rotate
// =============================================================================

// Helper
void printArr(const string& label, const vec<int>& arr) {
    cout << label << ": ";
    for (int i = 0; i < sz(arr); i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << nl;
}

// -------------------------------------------------------------
// ROTATION OVERVIEW
// -------------------------------------------------------------
/*
 * LEFT ROTATION by K:
 *   [1, 2, 3, 4, 5] → left by 2 → [3, 4, 5, 1, 2]
 *   First K elements move to the end.
 *
 * RIGHT ROTATION by K:
 *   [1, 2, 3, 4, 5] → right by 2 → [4, 5, 1, 2, 3]
 *   Last K elements move to the front.
 *
 * RELATIONSHIP:
 *   Right rotate by K = Left rotate by (N - K)
 *   Left rotate by K  = Right rotate by (N - K)
 *
 * IMPORTANT: Always do K = K % N to handle K >= N
 *
 * ┌───────────────────────────────────┬────────┬────────┐
 * │ Algorithm                         │ Time   │ Space  │
 * ├───────────────────────────────────┼────────┼────────┤
 * │ Brute Force (rotate by 1, K times)│ O(NK)  │ O(1)   │
 * │ Using Temp Array                  │ O(N)   │ O(N)   │
 * │ Reversal Algorithm ★             │ O(N)   │ O(1)   │
 * │ Juggling Algorithm                │ O(N)   │ O(1)   │
 * │ Cyclic Replacement                │ O(N)   │ O(1)   │
 * │ Block Swap                        │ O(N)   │ O(1)   │
 * │ std::rotate (STL)                 │ O(N)   │ O(1)   │
 * └───────────────────────────────────┴────────┴────────┘
 * ★ = Most commonly used, easiest to code
 */

// -------------------------------------------------------------
// 1. LEFT ROTATE BY 1 (Warm-up)
// -------------------------------------------------------------
// Store first element, shift all left, put stored at end.
// Time: O(N), Space: O(1)

void leftRotateByOne(vec<int>& arr) {
    if (arr.empty()) return;
    int first = arr[0];
    for (int i = 0; i < sz(arr) - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr.back() = first;
}

// -------------------------------------------------------------
// 2. BRUTE FORCE — Left Rotate by K (Do "rotate by 1" K times)
// -------------------------------------------------------------
// Time: O(N * K), Space: O(1)
// Status: TLE for large N and K

void leftRotateBrute(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n; // Handle k >= n
    for (int i = 0; i < k; i++) {
        leftRotateByOne(arr);
    }
}

// -------------------------------------------------------------
// 3. USING TEMP ARRAY — Left Rotate by K
// -------------------------------------------------------------
// Time: O(N), Space: O(N)
// Simple and fast, but uses extra memory.

void leftRotateTemp(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    vec<int> temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = arr[(i + k) % n]; // GM: This formula is KEY
    }
    arr = temp;
}

// GM Note on the formula: arr[(i + k) % n]
// After left rotation by k, element at index i comes from index (i + k) % n
// This is the fundamental INDEX MAPPING for rotation.

// -------------------------------------------------------------
// 4. REVERSAL ALGORITHM ★ (Left Rotate by K)
// -------------------------------------------------------------
// The CLEANEST and MOST POPULAR approach. MEMORIZE THIS.
//
// Steps for left rotate by K:
//   Step 1: Reverse first K elements     [0..K-1]
//   Step 2: Reverse remaining elements   [K..N-1]
//   Step 3: Reverse the entire array     [0..N-1]
//
// Example: [1, 2, 3, 4, 5], K=2
//   Step 1: [2, 1, | 3, 4, 5]
//   Step 2: [2, 1, | 5, 4, 3]
//   Step 3: [3, 4, 5, 1, 2] ✓
//
// WHY IT WORKS (GM Proof):
//   Let A = first K elements, B = remaining.
//   Original: AB
//   After rev(A) rev(B): A'B'
//   After rev(A'B'): (A'B')' = BA  ← which is the rotated array!
//
// Time: O(N) — exactly 2N element moves
// Space: O(1)

void leftRotateReversal(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    reverse(arr.begin(), arr.begin() + k);       // Reverse [0, k)
    reverse(arr.begin() + k, arr.end());          // Reverse [k, n)
    reverse(arr.begin(), arr.end());              // Reverse [0, n)
}

// RIGHT Rotate by K using Reversal
void rightRotateReversal(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    // Right rotate by K = Left rotate by (N - K)
    // OR: Reverse entire → Reverse first K → Reverse rest
    reverse(arr.begin(), arr.end());              // Reverse [0, n)
    reverse(arr.begin(), arr.begin() + k);        // Reverse [0, k)
    reverse(arr.begin() + k, arr.end());          // Reverse [k, n)
}

// -------------------------------------------------------------
// 5. JUGGLING ALGORITHM — Left Rotate by K
// -------------------------------------------------------------
// Idea: Divide array into GCD(N, K) sets. Rotate each set.
//
// Each element is moved directly to its final position.
// Elements are moved in cycles, and there are exactly GCD(N,K) cycles.
//
// Time: O(N), Space: O(1)
// GM Note: Harder to code than reversal, same complexity. Rarely needed.

void leftRotateJuggling(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    int g = gcd(n, k); // Number of cycles

    for (int i = 0; i < g; i++) {
        int temp = arr[i];
        int j = i;

        while (true) {
            int next = (j + k) % n;
            if (next == i) break;
            arr[j] = arr[next];
            j = next;
        }
        arr[j] = temp;
    }
}

// Trace for [1,2,3,4,5,6], K=2, GCD=2:
// Cycle 0: 1→3→5→1  →  arr: [3, 2, 5, 4, 1, 6] → then [3,2,5,4,1,6]
// Cycle 1: 2→4→6→2  →  arr: [3, 4, 5, 6, 1, 2]

// -------------------------------------------------------------
// 6. CYCLIC REPLACEMENT — Left Rotate by K (LC 189 approach)
// -------------------------------------------------------------
// Each element is placed at its correct position directly.
// Handle the cycle: when we return to starting index, move to next.
// Count total moves; stop when count == N.
//
// Time: O(N), Space: O(1)

void leftRotateCyclic(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    int count = 0;
    for (int start = 0; count < n; start++) {
        int current = start;
        int prev = arr[start];

        do {
            int next = (current + k) % n;
            int temp = arr[next];
            arr[next] = prev;
            prev = temp;
            current = next;
            count++;
        } while (current != start);
    }
}

// GM Note: This is essentially the same as juggling but coded differently.
// For RIGHT rotate, use k = n - k at the start.

// -------------------------------------------------------------
// 7. BLOCK SWAP ALGORITHM
// -------------------------------------------------------------
// Idea: Recursively swap blocks.
// If rotating left by K on array of size N:
//   If K < N-K: swap A[0..K-1] with A[N-K..N-1], then recurse on A[K..N-1]
//   If K > N-K: swap A[0..N-K-1] with A[K..N-1], then recurse on A[0..K-1]
//   If K == N-K: just swap the two halves
//
// Time: O(N), Space: O(log N) recursion stack (or O(1) iterative)
// GM Note: Elegant but complex. Reversal algorithm is preferred.

void blockSwap(vec<int>& arr, int start, int end, int k) {
    // Swap arr[start..start+k-1] with arr[end-k+1..end]
    for (int i = 0; i < k; i++) {
        swap(arr[start + i], arr[end - k + 1 + i]);
    }
}

void leftRotateBlockSwap(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0 || k == 0) return;
    k %= n;
    if (k == 0) return;

    int a = k;        // Size of left block
    int b = n - k;    // Size of right block

    int lo = 0;
    while (a != b) {
        if (a < b) {
            // Swap left block with rightmost 'a' elements of right block
            for (int i = 0; i < a; i++) {
                swap(arr[lo + i], arr[lo + b + i]);
            }
            b -= a;
        } else {
            // Swap right block with leftmost 'b' elements of left block
            for (int i = 0; i < b; i++) {
                swap(arr[lo + i], arr[lo + a + i]);
            }
            lo += b;
            a -= b;
        }
    }
    // a == b: swap the two equal blocks
    for (int i = 0; i < a; i++) {
        swap(arr[lo + i], arr[lo + a + i]);
    }
}

// -------------------------------------------------------------
// 8. STD::ROTATE (What GM Uses in Contest)
// -------------------------------------------------------------
// std::rotate(first, new_first, last)
// Makes the element pointed by new_first become the first element.
// Time: O(N), Space: O(1)

void leftRotateSTL(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    // Left rotate by k: make arr[k] the new first element
    rotate(arr.begin(), arr.begin() + k, arr.end());
}

void rightRotateSTL(vec<int>& arr, int k) {
    int n = sz(arr);
    if (n == 0) return;
    k %= n;
    if (k == 0) return;

    // Right rotate by k: make arr[n-k] the new first element
    rotate(arr.begin(), arr.begin() + (n - k), arr.end());
    // Or equivalently: rotate(arr.rbegin(), arr.rbegin() + k, arr.rend());
}

// -------------------------------------------------------------
// 9. CHECK IF ARRAY IS A ROTATION OF ANOTHER
// -------------------------------------------------------------
// Trick: Concatenate arr1 with itself, then check if arr2 is a substring.
// Time: O(N), Space: O(N)

bool isRotation(const vec<int>& a, const vec<int>& b) {
    if (sz(a) != sz(b)) return false;
    if (a.empty()) return true;

    // Concatenate a with itself
    vec<int> doubled(a);
    doubled.insert(doubled.end(), all(a));

    // Check if b is a contiguous subsequence of doubled
    // Using std::search (KMP internally in many implementations)
    return search(all(doubled), all(b)) != doubled.end();
}

// Simpler: check using index arithmetic
bool isRotation_simple(const vec<int>& a, const vec<int>& b) {
    int n = sz(a);
    if (n != sz(b)) return false;

    // Find starting position of b in a
    for (int start = 0; start < n; start++) {
        bool match = true;
        for (int j = 0; j < n && match; j++) {
            if (a[(start + j) % n] != b[j]) match = false;
        }
        if (match) return true;
    }
    return false;
}

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 05: Array Rotation Concepts    ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    int k = 2;
    vec<int> original = {1, 2, 3, 4, 5, 6, 7};

    // 1. Brute Force
    vec<int> arr = original;
    leftRotateBrute(arr, k);
    printArr("Brute Force Left by 2", arr);

    // 2. Temp Array
    arr = original;
    leftRotateTemp(arr, k);
    printArr("Temp Array Left by 2 ", arr);

    // 3. Reversal Algorithm ★
    arr = original;
    leftRotateReversal(arr, k);
    printArr("Reversal Left by 2   ", arr);

    // 4. Right Rotate
    arr = original;
    rightRotateReversal(arr, k);
    printArr("Reversal Right by 2  ", arr);

    // 5. Juggling
    arr = original;
    leftRotateJuggling(arr, k);
    printArr("Juggling Left by 2   ", arr);

    // 6. Cyclic
    arr = original;
    leftRotateCyclic(arr, k);
    printArr("Cyclic Left by 2     ", arr);

    // 7. Block Swap
    arr = original;
    leftRotateBlockSwap(arr, k);
    printArr("Block Swap Left by 2 ", arr);

    // 8. STL
    arr = original;
    leftRotateSTL(arr, k);
    printArr("STL Left by 2        ", arr);

    arr = original;
    rightRotateSTL(arr, k);
    printArr("STL Right by 2       ", arr);

    // 9. Rotation Check
    vec<int> rotated = {3, 4, 5, 6, 7, 1, 2};
    cout << nl << "Is {3,4,5,6,7,1,2} a rotation of {1..7}? "
         << (isRotation(original, rotated) ? "YES" : "NO") << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

