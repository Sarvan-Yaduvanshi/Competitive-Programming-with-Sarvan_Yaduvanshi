/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 11:15:00
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
//  MODULE 06: REVERSAL & REARRANGEMENT
//  Level: ⭐⭐ Intermediate
//  Topics: Reverse, move zeros, Dutch flag, segregate, rearrange alternate
// =============================================================================

void printArr(const string& label, const vec<int>& arr) {
    cout << label << ": ";
    for (int i = 0; i < sz(arr); i++) {
        if (i > 0) cout << ' ';
        cout << arr[i];
    }
    cout << nl;
}

// -------------------------------------------------------------
// 1. REVERSE ARRAY
// -------------------------------------------------------------
// Time: O(N), Space: O(1)

// Manual implementation
void reverseArray(vec<int>& arr, int lo, int hi) {
    while (lo < hi) {
        swap(arr[lo], arr[hi]);
        lo++;
        hi--;
    }
}

// STL: reverse(arr.begin(), arr.end());
// STL: reverse(arr.begin() + lo, arr.begin() + hi + 1);

void demo_reverse() {
    cout << "--- Reverse Array ---" << nl;

    vec<int> arr = {1, 2, 3, 4, 5};
    printArr("Original", arr);

    reverseArray(arr, 0, sz(arr) - 1);
    printArr("Reversed", arr);

    // Reverse a portion [1, 3]
    arr = {1, 2, 3, 4, 5};
    reverseArray(arr, 1, 3);
    printArr("Reverse [1,3]", arr); // 1 4 3 2 5
}

// -------------------------------------------------------------
// 2. MOVE ALL ZEROS TO END — O(N)
// -------------------------------------------------------------
// LC 283: Move Zeroes
// Maintain order of non-zero elements.
//
// Approach: "Snowball" technique — track the position where the next
//           non-zero element should go.

void moveZerosToEnd(vec<int>& arr) {
    int n = sz(arr);
    int writePos = 0; // Position to place next non-zero

    // Pass 1: Move all non-zero elements to front
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[writePos++] = arr[i];
        }
    }

    // Pass 2: Fill remaining with zeros
    while (writePos < n) {
        arr[writePos++] = 0;
    }
}

// Single-pass version using swap (preserves relative order)
void moveZerosToEnd_swap(vec<int>& arr) {
    int writePos = 0;
    for (int i = 0; i < sz(arr); i++) {
        if (arr[i] != 0) {
            swap(arr[writePos], arr[i]);
            writePos++;
        }
    }
}

// Move zeros to front (just traverse in reverse)
void moveZerosToFront(vec<int>& arr) {
    int n = sz(arr);
    int writePos = n - 1;

    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] != 0) {
            arr[writePos--] = arr[i];
        }
    }
    while (writePos >= 0) {
        arr[writePos--] = 0;
    }
}

// -------------------------------------------------------------
// 3. SEGREGATE 0s AND 1s
// -------------------------------------------------------------
// Time: O(N), Space: O(1)
// Approach 1: Count 0s, fill 0s then 1s
// Approach 2: Two pointers (partitioning)

void segregate_01_count(vec<int>& arr) {
    int zeros = count(all(arr), 0);
    fill(arr.begin(), arr.begin() + zeros, 0);
    fill(arr.begin() + zeros, arr.end(), 1);
}

void segregate_01_twoPointer(vec<int>& arr) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo < hi) {
        // Find 1 from left
        while (lo < hi && arr[lo] == 0) lo++;
        // Find 0 from right
        while (lo < hi && arr[hi] == 1) hi--;

        if (lo < hi) {
            swap(arr[lo], arr[hi]);
            lo++;
            hi--;
        }
    }
}

// -------------------------------------------------------------
// 4. DUTCH NATIONAL FLAG — Sort 0, 1, 2 in O(N)
// -------------------------------------------------------------
// LC 75: Sort Colors
// Three-way partitioning by Dijkstra.
//
// Maintain three pointers:
//   lo: boundary for 0s (everything before lo is 0)
//   hi: boundary for 2s (everything after hi is 2)
//   mid: current element being examined
//
// Invariant at all times:
//   arr[0..lo-1]   → all 0s
//   arr[lo..mid-1]  → all 1s
//   arr[mid..hi]    → unprocessed
//   arr[hi+1..n-1]  → all 2s

void dutchNationalFlag(vec<int>& arr) {
    int lo = 0, mid = 0, hi = sz(arr) - 1;

    while (mid <= hi) {
        if (arr[mid] == 0) {
            swap(arr[lo], arr[mid]);
            lo++;
            mid++;
        }
        else if (arr[mid] == 1) {
            mid++;
        }
        else { // arr[mid] == 2
            swap(arr[mid], arr[hi]);
            hi--;
            // DON'T increment mid! The swapped element needs checking.
        }
    }
}

// GM Note: This is a FUNDAMENTAL partitioning technique.
// Generalize it: partition around a pivot in quicksort uses the same idea.

// -------------------------------------------------------------
// 5. SORT ARRAY BY PARITY (LC 905)
// -------------------------------------------------------------
// Move all even numbers before odd numbers.
// Order within even/odd doesn't matter.

void sortByParity(vec<int>& arr) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo < hi) {
        // Find odd from left
        while (lo < hi && arr[lo] % 2 == 0) lo++;
        // Find even from right
        while (lo < hi && arr[hi] % 2 == 1) hi--;

        if (lo < hi) {
            swap(arr[lo], arr[hi]);
            lo++;
            hi--;
        }
    }
}

// Sort by parity preserving order: use stable_partition
void sortByParity_stable(vec<int>& arr) {
    stable_partition(all(arr), [](int x) { return x % 2 == 0; });
}

// -------------------------------------------------------------
// 6. REARRANGE POSITIVE AND NEGATIVE ALTERNATELY
// -------------------------------------------------------------
// Given: [-1, 2, -3, 4, 5, -6, 7, 8]
// Output: [2, -1, 4, -3, 5, -6, 7, 8] (or similar alternating pattern)
//
// This is a HARD problem to do in O(N) time + O(1) space + stable order.
// Most interview/CP solutions relax one constraint.

// Approach 1: Extra space O(N), preserves order
void rearrangeAlternate_extra(vec<int>& arr) {
    vec<int> pos, neg;
    for (int x : arr) {
        if (x >= 0) pos.pb(x);
        else neg.pb(x);
    }

    int i = 0, p = 0, n = 0;
    bool placePos = true; // Start with positive

    while (p < sz(pos) && n < sz(neg)) {
        if (placePos) arr[i++] = pos[p++];
        else arr[i++] = neg[n++];
        placePos = !placePos;
    }
    // Place remaining
    while (p < sz(pos)) arr[i++] = pos[p++];
    while (n < sz(neg)) arr[i++] = neg[n++];
}

// Approach 2: In-place, O(N²), preserves order (using right rotation)
void rearrangeAlternate_inplace(vec<int>& arr) {
    int n = sz(arr);

    for (int i = 0; i < n; i++) {
        // If position i should have positive but has negative (or vice versa)
        bool shouldBePositive = (i % 2 == 0);

        if (shouldBePositive && arr[i] < 0) {
            // Find next positive
            int j = i + 1;
            while (j < n && arr[j] < 0) j++;
            if (j < n) {
                // Right rotate arr[i..j] to bring arr[j] to position i
                int temp = arr[j];
                for (int k = j; k > i; k--) arr[k] = arr[k - 1];
                arr[i] = temp;
            }
        }
        else if (!shouldBePositive && arr[i] >= 0) {
            int j = i + 1;
            while (j < n && arr[j] >= 0) j++;
            if (j < n) {
                int temp = arr[j];
                for (int k = j; k > i; k--) arr[k] = arr[k - 1];
                arr[i] = temp;
            }
        }
    }
}

// -------------------------------------------------------------
// 7. REARRANGE ARRAY IN ALTERNATING HIGH-LOW (Wave Sort)
// -------------------------------------------------------------
// Output: arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] ...
// LC 280: Wiggle Sort
//
// Approach: At even indices, element should be >= neighbors
//           At odd indices, element should be <= neighbors

void waveSort(vec<int>& arr) {
    int n = sz(arr);
    for (int i = 0; i < n; i++) {
        // Even index: should be local maximum
        if (i % 2 == 0) {
            if (i > 0 && arr[i] < arr[i - 1])
                swap(arr[i], arr[i - 1]);
            if (i + 1 < n && arr[i] < arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }
    }
}

// Simpler version: sort first, then swap adjacent pairs
void waveSort_simple(vec<int>& arr) {
    sort(all(arr));
    for (int i = 0; i + 1 < sz(arr); i += 2) {
        swap(arr[i], arr[i + 1]);
    }
}

// -------------------------------------------------------------
// 8. REMOVE ELEMENT IN-PLACE (LC 27)
// -------------------------------------------------------------
// Remove all instances of val. Return new length.
// Order can change.

int removeElement(vec<int>& arr, int val) {
    int writePos = 0;
    for (int i = 0; i < sz(arr); i++) {
        if (arr[i] != val) {
            arr[writePos++] = arr[i];
        }
    }
    return writePos; // New size
}

// -------------------------------------------------------------
// 9. REMOVE DUPLICATES FROM SORTED ARRAY (LC 26)
// -------------------------------------------------------------
// Return new length with unique elements.

int removeDuplicates(vec<int>& arr) {
    if (arr.empty()) return 0;

    int writePos = 1; // arr[0] is always unique
    for (int i = 1; i < sz(arr); i++) {
        if (arr[i] != arr[i - 1]) {
            arr[writePos++] = arr[i];
        }
    }
    return writePos;
}

// STL way: arr.erase(unique(all(arr)), arr.end());

// -------------------------------------------------------------
// 10. SQUARES OF SORTED ARRAY (LC 977)
// -------------------------------------------------------------
// Input sorted array (may have negatives): [-4, -1, 0, 3, 10]
// Output sorted squares: [0, 1, 9, 16, 100]
// Two pointer from both ends, fill result array from back.

vec<int> sortedSquares(const vec<int>& arr) {
    int n = sz(arr);
    vec<int> result(n);
    int lo = 0, hi = n - 1;
    int pos = n - 1; // Fill from the end (largest first)

    while (lo <= hi) {
        int leftSq = arr[lo] * arr[lo];
        int rightSq = arr[hi] * arr[hi];

        if (leftSq >= rightSq) {
            result[pos--] = leftSq;
            lo++;
        } else {
            result[pos--] = rightSq;
            hi--;
        }
    }
    return result;
}

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 06: Reversal & Rearrangement   ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    // 1. Reverse
    demo_reverse();

    // 2. Move Zeros
    cout << nl << "--- Move Zeros to End ---" << nl;
    vec<int> z = {0, 1, 0, 3, 12};
    moveZerosToEnd(z);
    printArr("After", z); // 1 3 12 0 0

    // 3. Segregate 0s and 1s
    cout << nl << "--- Segregate 0s and 1s ---" << nl;
    vec<int> bin = {0, 1, 0, 1, 1, 0, 0, 1};
    segregate_01_twoPointer(bin);
    printArr("After", bin);

    // 4. Dutch National Flag
    cout << nl << "--- Dutch National Flag ---" << nl;
    vec<int> colors = {2, 0, 1, 2, 0, 1, 0, 2, 1};
    dutchNationalFlag(colors);
    printArr("After", colors); // 0 0 0 1 1 1 2 2 2

    // 5. Sort by Parity
    cout << nl << "--- Sort by Parity ---" << nl;
    vec<int> parity = {3, 1, 2, 4, 6, 5};
    sortByParity(parity);
    printArr("After", parity);

    // 6. Rearrange Alternate
    cout << nl << "--- Rearrange Pos/Neg Alternately ---" << nl;
    vec<int> pn = {-1, 2, -3, 4, 5, -6, 7, 8};
    rearrangeAlternate_extra(pn);
    printArr("After", pn);

    // 7. Wave Sort
    cout << nl << "--- Wave Sort ---" << nl;
    vec<int> wave = {1, 2, 3, 4, 5, 6};
    waveSort_simple(wave);
    printArr("After", wave);

    // 8. Sorted Squares
    cout << nl << "--- Sorted Squares ---" << nl;
    vec<int> neg = {-4, -1, 0, 3, 10};
    vec<int> sq = sortedSquares(neg);
    printArr("Squares", sq); // 0 1 9 16 100
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

