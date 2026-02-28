/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-28 12:15:00
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
//  MODULE 10: MERGE & PARTITION TECHNIQUES
//  Level: ⭐⭐⭐⭐ Expert
//  Topics: Merge sorted arrays, gap method, Lomuto/Hoare partition,
//          three-way partition, merge sort concept, inversion count
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
// 1. MERGE TWO SORTED ARRAYS — O(N + M) Time, O(N + M) Space
// -------------------------------------------------------------
// Classic two-pointer merge. Foundation of merge sort.
// LC 88: Merge Sorted Array

vec<int> mergeSorted(const vec<int>& a, const vec<int>& b) {
    int n = sz(a), m = sz(b);
    vec<int> result;
    result.reserve(n + m); // Pre-allocate for efficiency

    int i = 0, j = 0;

    while (i < n && j < m) {
        if (a[i] <= b[j]) {
            result.pb(a[i++]);
        } else {
            result.pb(b[j++]);
        }
    }

    // Append remaining elements
    while (i < n) result.pb(a[i++]);
    while (j < m) result.pb(b[j++]);

    return result;
}

// LC 88 variant: Merge into arr1 which has enough space at the end
// arr1 has m elements + n zeros at end, arr2 has n elements
void mergeInPlace_LC88(vec<int>& arr1, int m, const vec<int>& arr2, int n) {
    // Fill from the BACK (largest first) to avoid overwriting
    int i = m - 1;     // Last valid element in arr1
    int j = n - 1;     // Last element in arr2
    int k = m + n - 1; // Last position

    while (i >= 0 && j >= 0) {
        if (arr1[i] >= arr2[j]) {
            arr1[k--] = arr1[i--];
        } else {
            arr1[k--] = arr2[j--];
        }
    }
    // If arr2 has remaining (arr1 remaining is already in place)
    while (j >= 0) {
        arr1[k--] = arr2[j--];
    }
}

// -------------------------------------------------------------
// 2. MERGE TWO SORTED ARRAYS WITHOUT EXTRA SPACE — GAP METHOD
// -------------------------------------------------------------
// Given two sorted arrays arr1[n] and arr2[m], merge them so that
// arr1 has the smallest n elements and arr2 has the largest m elements,
// both sorted. NO extra space allowed.
//
// GAP METHOD (Shell Sort inspired):
//   Start with gap = ceil((n + m) / 2)
//   Compare and swap elements that are 'gap' apart
//   Reduce gap by half until gap = 0
//
// Time: O((N+M) * log(N+M)), Space: O(1)

void mergeWithoutExtraSpace(vec<int>& arr1, vec<int>& arr2) {
    int n = sz(arr1), m = sz(arr2);
    int total = n + m;
    int gap = (total + 1) / 2; // Ceiling division

    while (gap > 0) {
        int i = 0;

        while (i + gap < total) {
            int j = i + gap;

            // Both indices in arr1
            if (i < n && j < n) {
                if (arr1[i] > arr1[j]) swap(arr1[i], arr1[j]);
            }
            // i in arr1, j in arr2
            else if (i < n && j >= n) {
                if (arr1[i] > arr2[j - n]) swap(arr1[i], arr2[j - n]);
            }
            // Both indices in arr2
            else {
                if (arr2[i - n] > arr2[j - n]) swap(arr2[i - n], arr2[j - n]);
            }
            i++;
        }

        if (gap == 1) break;
        gap = (gap + 1) / 2;
    }
}

// -------------------------------------------------------------
// 3. LOMUTO PARTITION (QuickSort Standard)
// -------------------------------------------------------------
// Partitions array around a pivot (last element).
// All elements <= pivot go to left, > pivot go to right.
// Returns the final position of the pivot.
//
// Invariant:
//   arr[lo..i]     → elements <= pivot
//   arr[i+1..j-1]  → elements > pivot
//   arr[j..hi-1]   → unprocessed
//   arr[hi]         → pivot
//
// Time: O(N), Space: O(1)

int lomutoPartition(vec<int>& arr, int lo, int hi) {
    int pivot = arr[hi]; // Pivot is last element
    int i = lo - 1;      // Boundary for <= pivot

    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[hi]); // Place pivot at correct position
    return i + 1;
}

// Randomized Lomuto (avoids O(N²) worst case on sorted input)
int lomutoPartitionRandom(vec<int>& arr, int lo, int hi) {
    int randomIdx = lo + rng() % (hi - lo + 1);
    swap(arr[randomIdx], arr[hi]); // Move random pivot to end
    return lomutoPartition(arr, lo, hi);
}

// -------------------------------------------------------------
// 4. HOARE PARTITION (Original, Faster in Practice)
// -------------------------------------------------------------
// Uses two pointers moving inward from both ends.
// On average, does ~3x fewer swaps than Lomuto.
//
// IMPORTANT DIFFERENCE:
//   - Lomuto returns exact pivot position
//   - Hoare returns a split point: arr[lo..j] <= pivot, arr[j+1..hi] >= pivot
//   - The pivot is NOT necessarily at position j!
//
// Time: O(N), Space: O(1)

int hoarePartition(vec<int>& arr, int lo, int hi) {
    int pivot = arr[lo + (hi - lo) / 2]; // Median-ish pivot (avoids worst case)
    int i = lo - 1;
    int j = hi + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);

        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

// GM Note: Hoare partition is used in std::sort implementations.
// For quickselect (kth element), Lomuto is easier to reason about.
// For quicksort, Hoare is ~3x faster due to fewer swaps.

// -------------------------------------------------------------
// 5. THREE-WAY PARTITION (Dutch National Flag Generalized)
// -------------------------------------------------------------
// Partition around a value: elements < val | elements == val | elements > val
// Returns {lo, hi} where arr[lo..hi] == val
//
// Used in: QuickSort with many duplicates (3-way quicksort)
// Time: O(N), Space: O(1)

pair<int,int> threeWayPartition(vec<int>& arr, int lo, int hi, int pivot) {
    int lt = lo;     // arr[lo..lt-1]    < pivot
    int mid = lo;    // arr[lt..mid-1]   == pivot
    int gt = hi;     // arr[gt+1..hi]    > pivot

    while (mid <= gt) {
        if (arr[mid] < pivot) {
            swap(arr[lt], arr[mid]);
            lt++;
            mid++;
        }
        else if (arr[mid] > pivot) {
            swap(arr[mid], arr[gt]);
            gt--;
        }
        else {
            mid++;
        }
    }
    return {lt, gt}; // arr[lt..gt] all equal to pivot
}

// -------------------------------------------------------------
// 6. QUICKSORT IMPLEMENTATION
// -------------------------------------------------------------
// Using Lomuto partition. Average: O(N log N), Worst: O(N²).
// Randomized pivot makes worst case astronomically unlikely.

void quickSort_lomuto(vec<int>& arr, int lo, int hi) {
    if (lo >= hi) return;

    int pivotIdx = lomutoPartitionRandom(arr, lo, hi);
    quickSort_lomuto(arr, lo, pivotIdx - 1);
    quickSort_lomuto(arr, pivotIdx + 1, hi);
}

// Three-way quicksort (optimal for arrays with many duplicates)
void quickSort_3way(vec<int>& arr, int lo, int hi) {
    if (lo >= hi) return;

    // Random pivot
    int randomIdx = lo + rng() % (hi - lo + 1);
    int pivot = arr[randomIdx];

    auto [lt, gt] = threeWayPartition(arr, lo, hi, pivot);
    quickSort_3way(arr, lo, lt - 1);
    quickSort_3way(arr, gt + 1, hi);
}

// -------------------------------------------------------------
// 7. MERGE SORT (Divide and Conquer)
// -------------------------------------------------------------
// Always O(N log N). Stable sort. Used for: linked lists, external sort,
// counting inversions.

void mergeStep(vec<int>& arr, int lo, int mid, int hi) {
    vec<int> temp;
    temp.reserve(hi - lo + 1);

    int i = lo, j = mid + 1;

    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j]) temp.pb(arr[i++]); // <= for stability
        else temp.pb(arr[j++]);
    }
    while (i <= mid) temp.pb(arr[i++]);
    while (j <= hi) temp.pb(arr[j++]);

    for (int k = lo; k <= hi; k++) {
        arr[k] = temp[k - lo];
    }
}

void mergeSort(vec<int>& arr, int lo, int hi) {
    if (lo >= hi) return;

    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid + 1, hi);
    mergeStep(arr, lo, mid, hi);
}

// -------------------------------------------------------------
// 8. COUNT INVERSIONS (Using Merge Sort) — GM Classic
// -------------------------------------------------------------
// An inversion is a pair (i, j) where i < j but arr[i] > arr[j].
// Brute force: O(N²). Merge sort: O(N log N).
//
// Key Insight: During merge, when we pick from the right half,
//              ALL remaining elements in the left half form inversions.

i64 mergeSortCountInv(vec<int>& arr, int lo, int hi) {
    if (lo >= hi) return 0;

    int mid = lo + (hi - lo) / 2;
    i64 inversions = 0;

    inversions += mergeSortCountInv(arr, lo, mid);
    inversions += mergeSortCountInv(arr, mid + 1, hi);

    // Merge and count
    vec<int> temp;
    temp.reserve(hi - lo + 1);
    int i = lo, j = mid + 1;

    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j]) {
            temp.pb(arr[i++]);
        } else {
            // arr[i] > arr[j]: all arr[i..mid] form inversions with arr[j]
            inversions += (mid - i + 1);
            temp.pb(arr[j++]);
        }
    }
    while (i <= mid) temp.pb(arr[i++]);
    while (j <= hi) temp.pb(arr[j++]);

    for (int k = lo; k <= hi; k++) arr[k] = temp[k - lo];

    return inversions;
}

// -------------------------------------------------------------
// 9. STD::PARTITION AND STABLE_PARTITION
// -------------------------------------------------------------
// STL partition: rearranges so that elements satisfying predicate come first.
// partition: NOT stable (relative order may change)
// stable_partition: stable (preserves relative order) but uses O(N) space

void demo_stl_partition() {
    cout << nl << "--- STL Partition ---" << nl;

    vec<int> arr = {1, 8, 3, 6, 2, 7, 4, 5};

    // Partition around 5: elements < 5 first
    auto pivot = partition(all(arr), [](int x) { return x < 5; });
    cout << "After partition (<5): ";
    for (int x : arr) cout << x << " ";
    cout << nl;
    cout << "Pivot points to: " << *pivot << " at index " << (pivot - arr.begin()) << nl;

    // Stable partition: preserves order
    arr = {1, 8, 3, 6, 2, 7, 4, 5};
    stable_partition(all(arr), [](int x) { return x % 2 == 0; });
    cout << "After stable_partition (evens first): ";
    for (int x : arr) cout << x << " ";
    cout << nl;
}

// -------------------------------------------------------------
// 10. MEDIAN OF TWO SORTED ARRAYS — O(log(min(N,M)))
// -------------------------------------------------------------
// LC 4: THE hardest binary search problem.
//
// Idea: Binary search on the partition point of the smaller array.
//       Ensure all left elements <= all right elements.

double medianOfTwoSorted(const vec<int>& a, const vec<int>& b) {
    // Ensure a is the smaller array
    if (sz(a) > sz(b)) return medianOfTwoSorted(b, a);

    int n = sz(a), m = sz(b);
    int lo = 0, hi = n;

    while (lo <= hi) {
        int partA = (lo + hi) / 2;
        int partB = (n + m + 1) / 2 - partA;

        int leftA  = (partA == 0) ? INT_MIN : a[partA - 1];
        int rightA = (partA == n) ? INT_MAX : a[partA];
        int leftB  = (partB == 0) ? INT_MIN : b[partB - 1];
        int rightB = (partB == m) ? INT_MAX : b[partB];

        if (leftA <= rightB && leftB <= rightA) {
            // Found the correct partition
            if ((n + m) % 2 == 1) {
                return max(leftA, leftB);
            } else {
                return (max(leftA, leftB) + min(rightA, rightB)) / 2.0;
            }
        }
        else if (leftA > rightB) {
            hi = partA - 1;
        }
        else {
            lo = partA + 1;
        }
    }
    return 0.0; // Should never reach here
}

// -------------------------------------------------------------
// COMPLEXITY CHEAT SHEET
// -------------------------------------------------------------
/*
 * ┌──────────────────────────────────┬────────────────┬───────────┐
 * │ Algorithm                        │ Time           │ Space     │
 * ├──────────────────────────────────┼────────────────┼───────────┤
 * │ Merge two sorted (extra space)   │ O(N + M)       │ O(N + M)  │
 * │ Merge in-place (LC 88)           │ O(N + M)       │ O(1)      │
 * │ Merge without extra space (gap)  │ O((N+M)log)    │ O(1)      │
 * │ Lomuto Partition                 │ O(N)           │ O(1)      │
 * │ Hoare Partition                  │ O(N)           │ O(1)      │
 * │ Three-Way Partition              │ O(N)           │ O(1)      │
 * │ QuickSort                        │ O(N log N) avg │ O(log N)  │
 * │ MergeSort                        │ O(N log N)     │ O(N)      │
 * │ Count Inversions                 │ O(N log N)     │ O(N)      │
 * │ Median of Two Sorted             │ O(log min(N,M))│ O(1)      │
 * └──────────────────────────────────┴────────────────┴───────────┘
 *
 * PARTITION COMPARISON:
 * ┌──────────┬────────────┬────────────┬────────────────────────┐
 * │ Type     │ Swaps      │ Stability  │ Best For               │
 * ├──────────┼────────────┼────────────┼────────────────────────┤
 * │ Lomuto   │ ~N         │ Not stable │ QuickSelect, simple    │
 * │ Hoare    │ ~N/3       │ Not stable │ QuickSort (fastest)    │
 * │ 3-Way   │ ~N         │ Not stable │ Many duplicates        │
 * └──────────┴────────────┴────────────┴────────────────────────┘
 */

void solve() {
    cout << "╔════════════════════════════════════════╗" << nl;
    cout << "║  MODULE 10: Merge & Partition           ║" << nl;
    cout << "╚════════════════════════════════════════╝" << nl;

    // 1. Merge Two Sorted Arrays
    cout << "--- Merge Two Sorted ---" << nl;
    vec<int> a = {1, 3, 5, 7};
    vec<int> b = {2, 4, 6, 8, 9};
    vec<int> merged = mergeSorted(a, b);
    printArr("Merged", merged);

    // 2. Merge In-Place (LC 88)
    cout << nl << "--- Merge In-Place (LC 88) ---" << nl;
    vec<int> arr1 = {1, 2, 3, 0, 0, 0};
    vec<int> arr2 = {2, 5, 6};
    mergeInPlace_LC88(arr1, 3, arr2, 3);
    printArr("Merged", arr1);

    // 3. Merge Without Extra Space
    cout << nl << "--- Merge Without Extra Space ---" << nl;
    vec<int> x = {1, 5, 9, 10, 15, 20};
    vec<int> y = {2, 3, 8, 13};
    mergeWithoutExtraSpace(x, y);
    printArr("arr1", x);
    printArr("arr2", y);

    // 4. Lomuto Partition
    cout << nl << "--- Lomuto Partition ---" << nl;
    vec<int> lom = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    printArr("Before", lom);
    int pivotIdx = lomutoPartition(lom, 0, sz(lom) - 1);
    printArr("After ", lom);
    cout << "Pivot 4 at index: " << pivotIdx << nl;

    // 5. Three-Way Partition
    cout << nl << "--- Three-Way Partition ---" << nl;
    vec<int> twp = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
    printArr("Before", twp);
    auto [lt, gt] = threeWayPartition(twp, 0, sz(twp) - 1, 4);
    printArr("After ", twp);
    cout << "Equal range [" << lt << ", " << gt << "]" << nl;

    // 6. QuickSort
    cout << nl << "--- QuickSort ---" << nl;
    vec<int> qs = {5, 3, 8, 6, 2, 7, 1, 4};
    quickSort_lomuto(qs, 0, sz(qs) - 1);
    printArr("Sorted", qs);

    // 7. MergeSort
    cout << nl << "--- MergeSort ---" << nl;
    vec<int> ms = {5, 3, 8, 6, 2, 7, 1, 4};
    mergeSort(ms, 0, sz(ms) - 1);
    printArr("Sorted", ms);

    // 8. Count Inversions
    cout << nl << "--- Count Inversions ---" << nl;
    vec<int> inv = {2, 4, 1, 3, 5};
    i64 invCount = mergeSortCountInv(inv, 0, sz(inv) - 1);
    cout << "Inversions in {2,4,1,3,5}: " << invCount << nl; // 3

    // 9. STL Partition
    demo_stl_partition();

    // 10. Median of Two Sorted
    cout << nl << "--- Median of Two Sorted Arrays ---" << nl;
    vec<int> s1 = {1, 3};
    vec<int> s2 = {2};
    cout << "Median of {1,3} and {2}: " << medianOfTwoSorted(s1, s2) << nl; // 2.0

    s1 = {1, 2};
    s2 = {3, 4};
    cout << "Median of {1,2} and {3,4}: " << medianOfTwoSorted(s1, s2) << nl; // 2.5
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    solve();

    return 0;
}

