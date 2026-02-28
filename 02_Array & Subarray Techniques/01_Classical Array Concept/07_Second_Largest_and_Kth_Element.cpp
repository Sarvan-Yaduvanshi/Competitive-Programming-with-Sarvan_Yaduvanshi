/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 11:30:00
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
//  MODULE 07: SECOND LARGEST & KTH ELEMENT
//  Level: ⭐⭐⭐ Advanced
//  Topics: Second largest/smallest, Kth element (sort, heap, quickselect)
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
// 1. SECOND LARGEST ELEMENT — O(N), Single Pass
// -------------------------------------------------------------
// Approach: Track the largest and second largest simultaneously.
//
// GM Note: This is a classic interview question. The key insight is
//          that when we find a new largest, the OLD largest becomes
//          the second largest.
//
// Edge cases:
//   - All elements same → no second largest (return -1 or INT_MIN)
//   - Only 1 element → no second largest

int secondLargest(const vec<int>& arr) {
    int n = sz(arr);
    if (n < 2) return INT_MIN;

    int first = INT_MIN;
    int second = INT_MIN;

    for (int x : arr) {
        if (x > first) {
            second = first; // Old first becomes second
            first = x;
        }
        else if (x > second && x != first) {
            // Strictly less than first, but greater than current second
            // x != first handles duplicates of the max
            second = x;
        }
    }
    return second; // INT_MIN if no valid second largest
}

// Second Smallest (mirror logic)
int secondSmallest(const vec<int>& arr) {
    int n = sz(arr);
    if (n < 2) return INT_MAX;

    int first = INT_MAX;
    int second = INT_MAX;

    for (int x : arr) {
        if (x < first) {
            second = first;
            first = x;
        }
        else if (x < second && x != first) {
            second = x;
        }
    }
    return second;
}

// -------------------------------------------------------------
// 2. KTH LARGEST — Sorting Approach
// -------------------------------------------------------------
// Sort descending, return arr[k-1].
// Time: O(N log N), Space: O(1) if in-place
// When to use: When you need ALL elements sorted anyway.

int kthLargest_sort(vec<int> arr, int k) {
    // Note: Taking arr by value (copy) to avoid modifying original
    sort(all(arr), greater<int>());
    return arr[k - 1]; // 1-indexed
}

int kthSmallest_sort(vec<int> arr, int k) {
    sort(all(arr));
    return arr[k - 1];
}

// -------------------------------------------------------------
// 3. KTH LARGEST — MIN HEAP Approach
// -------------------------------------------------------------
// Maintain a min-heap of size K.
// For each element:
//   - If heap.size < K: push
//   - If element > heap.top(): pop top, push element
// After processing all: heap.top() = Kth largest
//
// Time: O(N log K), Space: O(K)
// When to use: K << N (e.g., find 5th largest in 10^6 elements)
//
// WHY min-heap and not max-heap?
//   Min-heap of size K keeps the K largest elements.
//   The SMALLEST among them (heap.top()) is the Kth largest.

int kthLargest_heap(const vec<int>& arr, int k) {
    // priority_queue<int, vector<int>, greater<int>> = min-heap
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int x : arr) {
        minHeap.push(x);
        if (sz(minHeap) > k) {
            minHeap.pop(); // Remove smallest, keeping K largest
        }
    }
    return minHeap.top(); // Kth largest
}

// Kth Smallest using max-heap of size K
int kthSmallest_heap(const vec<int>& arr, int k) {
    priority_queue<int> maxHeap; // Default: max-heap

    for (int x : arr) {
        maxHeap.push(x);
        if (sz(maxHeap) > k) {
            maxHeap.pop();
        }
    }
    return maxHeap.top(); // Kth smallest
}

// -------------------------------------------------------------
// 4. KTH LARGEST — QUICKSELECT (Hoare's Selection Algorithm)
// -------------------------------------------------------------
// Based on QuickSort's partition step.
// Average: O(N), Worst: O(N²) — but randomized pivot makes worst case rare.
//
// Idea:
//   1. Pick a random pivot
//   2. Partition: elements > pivot go left, elements < pivot go right
//   3. If pivot's position == k-1, we found the kth largest
//   4. Else recurse on the correct half
//
// GM Note: This is the OPTIMAL expected-time algorithm for selection.
//          Used internally by std::nth_element.

int partition_random(vec<int>& arr, int lo, int hi) {
    // Random pivot to avoid worst case
    int pivotIdx = lo + rng() % (hi - lo + 1);
    swap(arr[pivotIdx], arr[hi]); // Move pivot to end

    int pivot = arr[hi];
    int i = lo; // Boundary: everything before i is >= pivot (for kth largest)

    for (int j = lo; j < hi; j++) {
        if (arr[j] >= pivot) { // >= for "kth largest" (descending partition)
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[hi]); // Place pivot at its correct position
    return i;
}

int quickselect(vec<int>& arr, int lo, int hi, int k) {
    // k is 0-indexed (kth largest = index k when sorted descending)
    if (lo == hi) return arr[lo];

    int pivotIdx = partition_random(arr, lo, hi);

    if (pivotIdx == k) {
        return arr[pivotIdx];
    }
    else if (pivotIdx < k) {
        return quickselect(arr, pivotIdx + 1, hi, k);
    }
    else {
        return quickselect(arr, lo, pivotIdx - 1, k);
    }
}

int kthLargest_quickselect(vec<int> arr, int k) {
    // Copy arr to avoid modifying original
    return quickselect(arr, 0, sz(arr) - 1, k - 1); // Convert to 0-indexed
}

// Iterative Quickselect (avoids stack overflow for huge N)
int kthLargest_quickselect_iterative(vec<int> arr, int k) {
    k--; // Convert to 0-indexed
    int lo = 0, hi = sz(arr) - 1;

    while (lo < hi) {
        int pivotIdx = partition_random(arr, lo, hi);

        if (pivotIdx == k) return arr[pivotIdx];
        else if (pivotIdx < k) lo = pivotIdx + 1;
        else hi = pivotIdx - 1;
    }
    return arr[lo];
}

// -------------------------------------------------------------
// 5. STD::NTH_ELEMENT (What GM Actually Uses)
// -------------------------------------------------------------
// Rearranges array so that:
//   - arr[k] = element that would be at position k if sorted
//   - arr[0..k-1] <= arr[k] (not necessarily sorted)
//   - arr[k+1..n-1] >= arr[k] (not necessarily sorted)
//
// Average: O(N), guaranteed by C++ standard (introselect internally)
// Space: O(1)

int kthSmallest_stl(vec<int> arr, int k) {
    // nth_element for kth smallest (0-indexed)
    nth_element(arr.begin(), arr.begin() + (k - 1), arr.end());
    return arr[k - 1];
}

int kthLargest_stl(vec<int> arr, int k) {
    // nth_element with greater comparator for kth largest
    nth_element(arr.begin(), arr.begin() + (k - 1), arr.end(), greater<int>());
    return arr[k - 1];
}

// GM Contest Tip: For "find the Kth largest/smallest", just use nth_element.
// It's O(N) average and already in the STL. Don't code quickselect.

// -------------------------------------------------------------
// 6. PARTIAL SORT — Get Top K sorted
// -------------------------------------------------------------
// When you need the top K elements in sorted order.
// Time: O(N log K), Space: O(1)

vec<int> topK_sorted(vec<int> arr, int k) {
    partial_sort(arr.begin(), arr.begin() + k, arr.end(), greater<int>());
    return vec<int>(arr.begin(), arr.begin() + k);
}

// -------------------------------------------------------------
// 7. THIRD MAXIMUM NUMBER (LC 414)
// -------------------------------------------------------------
// Find the third DISTINCT maximum. If < 3 distinct, return the maximum.

int thirdMax(const vec<int>& arr) {
    // Track top 3 distinct values
    i64 first = LLONG_MIN, second = LLONG_MIN, third = LLONG_MIN;
    // Using i64 to handle INT_MIN in the array

    for (int x : arr) {
        // Skip if already seen
        if (x == first || x == second || x == third) continue;

        if (x > first) {
            third = second;
            second = first;
            first = x;
        }
        else if (x > second) {
            third = second;
            second = x;
        }
        else if (x > third) {
            third = x;
        }
    }

    // If third was never set, return first (max)
    return (third == LLONG_MIN) ? (int)first : (int)third;
}

// -------------------------------------------------------------
// 8. MEDIAN FINDING
// -------------------------------------------------------------
// Median = middle element when sorted
// For odd N: arr[N/2]
// For even N: (arr[N/2 - 1] + arr[N/2]) / 2.0

double findMedian(vec<int> arr) {
    int n = sz(arr);
    nth_element(arr.begin(), arr.begin() + n / 2, arr.end());

    if (n % 2 == 1) {
        return arr[n / 2];
    } else {
        int mid2 = arr[n / 2];
        nth_element(arr.begin(), arr.begin() + n / 2 - 1, arr.end());
        int mid1 = arr[n / 2 - 1];
        return (mid1 + mid2) / 2.0;
    }
}

// -------------------------------------------------------------
// COMPLEXITY COMPARISON
// -------------------------------------------------------------
/*
 * ┌────────────────────────┬────────────┬────────────┬───────────┐
 * │ Method                 │ Time       │ Space      │ When to Use│
 * ├────────────────────────┼────────────┼────────────┼───────────┤
 * │ Sort + Index           │ O(N log N) │ O(1)       │ Simple, ok│
 * │ Min Heap (size K)      │ O(N log K) │ O(K)       │ K << N    │
 * │ Quickselect            │ O(N) avg   │ O(1)       │ General   │
 * │ nth_element (STL)      │ O(N) avg   │ O(1)       │ Contest ★ │
 * │ Partial Sort           │ O(N log K) │ O(1)       │ Top K sort│
 * │ Median of Medians      │ O(N) worst │ O(N)       │ Theory    │
 * └────────────────────────┴────────────┴────────────┴───────────┘
 *
 * GM Recommendation:
 *   - Contest: std::nth_element (1 line)
 *   - Interview: Quickselect (shows understanding)
 *   - Stream/Online: Min-heap (data arriving over time)
 */

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 07: Second Largest & Kth       ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    vec<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    printArr("Array", arr);

    // 1. Second Largest/Smallest
    cout << nl << "--- Second Largest/Smallest ---" << nl;
    cout << "Second Largest: " << secondLargest(arr) << nl;  // 6
    cout << "Second Smallest: " << secondSmallest(arr) << nl; // 2

    // 2. Kth Largest (K=3 → 3rd largest = 5)
    int k = 3;
    cout << nl << "--- Kth Largest (K=" << k << ") ---" << nl;
    cout << "Sort:        " << kthLargest_sort(arr, k) << nl;
    cout << "Min Heap:    " << kthLargest_heap(arr, k) << nl;
    cout << "Quickselect: " << kthLargest_quickselect(arr, k) << nl;
    cout << "STL:         " << kthLargest_stl(arr, k) << nl;

    // 3. Kth Smallest (K=3 → 3rd smallest = 2)
    cout << nl << "--- Kth Smallest (K=" << k << ") ---" << nl;
    cout << "Sort:        " << kthSmallest_sort(arr, k) << nl;
    cout << "Max Heap:    " << kthSmallest_heap(arr, k) << nl;
    cout << "STL:         " << kthSmallest_stl(arr, k) << nl;

    // 4. Third Maximum
    cout << nl << "--- Third Maximum ---" << nl;
    vec<int> t = {2, 2, 3, 1};
    cout << "Third max of {2,2,3,1}: " << thirdMax(t) << nl; // 1

    // 5. Top K sorted
    cout << nl << "--- Top " << k << " Sorted ---" << nl;
    vec<int> topk = topK_sorted(arr, k);
    printArr("Top 3", topk); // 9 6 5

    // 6. Median
    cout << nl << "--- Median ---" << nl;
    cout << "Median: " << findMedian(arr) << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

