/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 10:45:00
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
//  MODULE 04: SEARCHING IN ARRAY
//  Level: ⭐⭐ Intermediate
//  Topics: Linear search, binary search, STL, rotated sorted array search
// =============================================================================

// -------------------------------------------------------------
// 1. LINEAR SEARCH — O(N)
// -------------------------------------------------------------
// When to use: Unsorted array, one-time query
// GM Note: Don't underestimate linear search. For N ≤ 10^6 with
//          one query, it's perfectly fine.

int linearSearch(const vec<int>& arr, int target) {
    for (int i = 0; i < sz(arr); i++) {
        if (arr[i] == target) return i; // Found: return index
    }
    return -1; // Not found
}

// Linear search for LAST occurrence
int linearSearchLast(const vec<int>& arr, int target) {
    int lastIdx = -1;
    for (int i = 0; i < sz(arr); i++) {
        if (arr[i] == target) lastIdx = i;
    }
    return lastIdx;
}

// Linear search — Count occurrences
int linearSearchCount(const vec<int>& arr, int target) {
    int cnt = 0;
    for (int x : arr) {
        if (x == target) cnt++;
    }
    return cnt;
    // STL equivalent: count(all(arr), target)
}

// -------------------------------------------------------------
// 2. BINARY SEARCH — O(log N)
// -------------------------------------------------------------
// PREREQUISITE: Array MUST be sorted!
// GM Note: Binary search is the single most important algorithm in CP.
//          Master it in your sleep.
//
// Three flavors:
//   (a) Find exact element
//   (b) Find first occurrence (lower_bound)
//   (c) Find last occurrence

// (a) Classic Binary Search — Find if element exists
int binarySearch(const vec<int>& arr, int target) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2; // GM: Avoid overflow vs (lo+hi)/2

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1; // Not found
}

// (b) Lower Bound — First index where arr[i] >= target
// This is what std::lower_bound does internally.
int lowerBound(const vec<int>& arr, int target) {
    int lo = 0, hi = sz(arr); // Note: hi = N (not N-1)

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid;
    }
    return lo; // lo == hi == first index where arr[lo] >= target
    // If all elements < target, returns N (past the end)
}

// (c) Upper Bound — First index where arr[i] > target
// This is what std::upper_bound does internally.
int upperBound(const vec<int>& arr, int target) {
    int lo = 0, hi = sz(arr);

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) lo = mid + 1;
        else hi = mid;
    }
    return lo; // first index where arr[lo] > target
}

// (d) Last Occurrence of target
int lastOccurrence(const vec<int>& arr, int target) {
    int ub = upperBound(arr, target);
    if (ub > 0 && arr[ub - 1] == target) return ub - 1;
    return -1;
}

// (e) First Occurrence of target
int firstOccurrence(const vec<int>& arr, int target) {
    int lb = lowerBound(arr, target);
    if (lb < sz(arr) && arr[lb] == target) return lb;
    return -1;
}

// (f) Count of target in sorted array
int countInSorted(const vec<int>& arr, int target) {
    return upperBound(arr, target) - lowerBound(arr, target);
}

// (g) Recursive Binary Search (for understanding, not for CP)
int binarySearchRecursive(const vec<int>& arr, int target, int lo, int hi) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, hi);
    return binarySearchRecursive(arr, target, lo, mid - 1);
}

// -------------------------------------------------------------
// 3. STL SEARCH FUNCTIONS (What GM Actually Uses in Contest)
// -------------------------------------------------------------

void demo_stl_search() {
    cout << nl << "--- STL Search Functions ---" << nl;

    vec<int> arr = {1, 2, 2, 3, 3, 3, 4, 5, 5};

    // std::find — Linear search, returns iterator
    auto it1 = find(all(arr), 3);
    if (it1 != arr.end())
        cout << "find(3): index " << (it1 - arr.begin()) << nl;

    // std::binary_search — Just returns bool (exists or not)
    // GM Warning: Doesn't give index! Almost useless in CP.
    bool exists = binary_search(all(arr), 3);
    cout << "binary_search(3): " << exists << nl;

    // std::lower_bound — First >= target (MOST USEFUL)
    auto it2 = lower_bound(all(arr), 3);
    cout << "lower_bound(3): index " << (it2 - arr.begin()) << nl; // 3

    // std::upper_bound — First > target
    auto it3 = upper_bound(all(arr), 3);
    cout << "upper_bound(3): index " << (it3 - arr.begin()) << nl; // 6

    // Count of 3 = upper_bound - lower_bound
    cout << "Count of 3: " << (it3 - it2) << nl; // 3

    // std::equal_range — Returns pair(lower_bound, upper_bound)
    auto [lo, hi] = equal_range(all(arr), 3);
    cout << "equal_range(3): [" << (lo - arr.begin()) << ", " << (hi - arr.begin()) << ")" << nl;

    // std::count — Linear O(N), use for unsorted
    cout << "count(3): " << count(all(arr), 3) << nl;

    // GM Tip: lower_bound on a set/map is O(log N) too!
    set<int> s = {1, 3, 5, 7, 9};
    auto sit = s.lower_bound(4);
    if (sit != s.end()) cout << "Set lower_bound(4): " << *sit << nl; // 5
}

// -------------------------------------------------------------
// 4. SEARCH IN ROTATED SORTED ARRAY — O(log N)
// -------------------------------------------------------------
// Problem: Array was sorted, then rotated K times.
//          e.g., [4,5,6,7,0,1,2] (original: [0,1,2,4,5,6,7])
//          Find the index of a target, or return -1.
//
// Key Insight: At least one half (left or right of mid) is always sorted.
//              Determine which half is sorted, then check if target is in that half.
//
// LC 33: Search in Rotated Sorted Array

int searchRotated(const vec<int>& arr, int target) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == target) return mid;

        // LEFT HALF IS SORTED (arr[lo] <= arr[mid])
        if (arr[lo] <= arr[mid]) {
            // Is target in the sorted left half?
            if (arr[lo] <= target && target < arr[mid]) {
                hi = mid - 1; // Search left
            } else {
                lo = mid + 1; // Search right
            }
        }
        // RIGHT HALF IS SORTED
        else {
            // Is target in the sorted right half?
            if (arr[mid] < target && target <= arr[hi]) {
                lo = mid + 1; // Search right
            } else {
                hi = mid - 1; // Search left
            }
        }
    }
    return -1;
}

// -------------------------------------------------------------
// 5. SEARCH IN ROTATED SORTED ARRAY WITH DUPLICATES — O(N) worst
// -------------------------------------------------------------
// LC 81: When duplicates exist, arr[lo] == arr[mid] == arr[hi] is possible.
// In that case, we can't determine which half is sorted → shrink both.

bool searchRotatedDuplicates(const vec<int>& arr, int target) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == target) return true;

        // AMBIGUOUS CASE: can't determine sorted half
        if (arr[lo] == arr[mid] && arr[mid] == arr[hi]) {
            lo++;
            hi--;
        }
        // Left half is sorted
        else if (arr[lo] <= arr[mid]) {
            if (arr[lo] <= target && target < arr[mid])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        // Right half is sorted
        else {
            if (arr[mid] < target && target <= arr[hi])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    return false;
}

// -------------------------------------------------------------
// 6. FIND MINIMUM IN ROTATED SORTED ARRAY — O(log N)
// -------------------------------------------------------------
// LC 153: The minimum is the "pivot" point of rotation.

int findMinRotated(const vec<int>& arr) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        // If mid element > right element, minimum is in right half
        if (arr[mid] > arr[hi]) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return arr[lo]; // lo == hi == index of minimum
}

// Find the number of rotations (= index of minimum)
int countRotations(const vec<int>& arr) {
    int lo = 0, hi = sz(arr) - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > arr[hi]) lo = mid + 1;
        else hi = mid;
    }
    return lo; // Number of times array was rotated
}

// -------------------------------------------------------------
// 7. FIND PEAK ELEMENT — O(log N)
// -------------------------------------------------------------
// LC 162: Find ANY element that is greater than its neighbors.
// Key: If arr[mid] < arr[mid+1], peak is on the right. Otherwise, left.

int findPeakElement(const vec<int>& arr) {
    int lo = 0, hi = sz(arr) - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] < arr[mid + 1]) {
            lo = mid + 1; // Peak is on the right
        } else {
            hi = mid; // Peak is mid or to the left
        }
    }
    return lo; // Index of a peak element
}

// -------------------------------------------------------------
// 8. BINARY SEARCH ON ANSWER (GM Pattern)
// -------------------------------------------------------------
// Instead of searching in an array, search the ANSWER SPACE.
// Used in: "Minimize the maximum", "Maximize the minimum"
//
// Template:
//   lo = min possible answer
//   hi = max possible answer
//   while (lo < hi) {
//       mid = (lo + hi) / 2;
//       if (feasible(mid)) hi = mid;   // Can we do better?
//       else lo = mid + 1;              // Need more
//   }
//   answer = lo;

// Example: Minimum capacity to ship packages in D days (LC 1011)
bool canShipInDays(const vec<int>& weights, int D, int capacity) {
    int days = 1, load = 0;
    for (int w : weights) {
        if (load + w > capacity) {
            days++;
            load = 0;
        }
        load += w;
    }
    return days <= D;
}

int shipWithinDays(const vec<int>& weights, int D) {
    int lo = *max_element(all(weights)); // At least max weight
    int hi = accumulate(all(weights), 0); // At most total weight

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canShipInDays(weights, D, mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

// -------------------------------------------------------------
// COMPLEXITY CHEAT SHEET
// -------------------------------------------------------------
/*
 * ┌──────────────────────────────────┬────────────┬───────────┐
 * │ Algorithm                        │ Time       │ Space     │
 * ├──────────────────────────────────┼────────────┼───────────┤
 * │ Linear Search                    │ O(N)       │ O(1)      │
 * │ Binary Search                    │ O(log N)   │ O(1)      │
 * │ Binary Search (recursive)        │ O(log N)   │ O(log N)  │
 * │ std::find (unsorted)             │ O(N)       │ O(1)      │
 * │ std::lower_bound (sorted)        │ O(log N)   │ O(1)      │
 * │ Search in rotated sorted         │ O(log N)   │ O(1)      │
 * │ Search rotated with duplicates   │ O(N) worst │ O(1)      │
 * │ Find min in rotated              │ O(log N)   │ O(1)      │
 * │ Binary search on answer          │ O(N log S) │ O(1)      │
 * └──────────────────────────────────┴────────────┴───────────┘
 * where S = answer space size
 */

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 04: Searching in Array         ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    // --- Linear Search Demo ---
    vec<int> unsorted = {5, 3, 8, 1, 9, 2, 7};
    cout << "Array: {5,3,8,1,9,2,7}" << nl;
    cout << "Linear search for 9: index " << linearSearch(unsorted, 9) << nl;
    cout << "Linear search for 6: index " << linearSearch(unsorted, 6) << nl;

    // --- Binary Search Demo ---
    vec<int> sorted = {1, 2, 3, 3, 3, 4, 5, 6, 7};
    cout << nl << "Sorted: {1,2,3,3,3,4,5,6,7}" << nl;
    cout << "Binary search for 3: index " << binarySearch(sorted, 3) << nl;
    cout << "Lower bound of 3: index " << lowerBound(sorted, 3) << nl;
    cout << "Upper bound of 3: index " << upperBound(sorted, 3) << nl;
    cout << "First occurrence of 3: " << firstOccurrence(sorted, 3) << nl;
    cout << "Last occurrence of 3: " << lastOccurrence(sorted, 3) << nl;
    cout << "Count of 3: " << countInSorted(sorted, 3) << nl;

    // --- STL Demo ---
    demo_stl_search();

    // --- Rotated Search Demo ---
    vec<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << nl << "Rotated: {4,5,6,7,0,1,2}" << nl;
    cout << "Search 0: index " << searchRotated(rotated, 0) << nl;
    cout << "Search 3: index " << searchRotated(rotated, 3) << nl;
    cout << "Min element: " << findMinRotated(rotated) << nl;
    cout << "Rotations: " << countRotations(rotated) << nl;

    // --- Peak Element Demo ---
    vec<int> peaks = {1, 3, 5, 4, 2};
    cout << nl << "Peaks: {1,3,5,4,2}" << nl;
    cout << "Peak index: " << findPeakElement(peaks) << nl;

    // --- Binary Search on Answer Demo ---
    vec<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << nl << "Ship within 5 days: capacity = " << shipWithinDays(weights, 5) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

