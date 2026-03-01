/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 09 — ADVANCED SEARCHING TECHNIQUES                       ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Ternary Search
 2.  Search in Rotated Sorted Array
 3.  Find Pivot in Rotated Array
 4.  Peak Element (1D)
 5.  Mountain Array
 6.  Exponential Search
 7.  Interpolation Search
 8.  Binary Lifting Concept

OVERVIEW:
─────────
These are advanced variations and extensions of binary search.
Each exploits a specific structural property of the data.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <climits>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: TERNARY SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Ternary Search finds the maximum/minimum of a UNIMODAL function.

 UNIMODAL FUNCTION:
   • Has exactly one peak (for maximum) or valley (for minimum)
   • Strictly increasing then strictly decreasing (or vice versa)
   • f increases → peak → f decreases

 ALGORITHM:
   Divide search space into 3 parts using two points: m1, m2
   lo ─── m1 ─── m2 ─── hi

   For finding MAXIMUM:
     if f(m1) < f(m2): peak is in [m1, hi] → lo = m1
     else: peak is in [lo, m2] → hi = m2

   Each iteration eliminates 1/3 of search space.
   Time: O(log₃ n) ≈ O(log n) — slightly worse constant than binary search

 WHEN TO USE:
   • Finding max/min of unimodal function
   • Optimization problems where cost function is convex/concave
   • Geometric problems (distance minimization)

 BINARY SEARCH vs TERNARY SEARCH:
   BS needs monotonic function (always increasing or decreasing)
   TS needs unimodal function (increases then decreases or vice versa)
   For monotonic → BS is better (fewer evaluations)
   For unimodal → TS is the way (or BS on derivative)
*/

// Ternary Search for maximum of unimodal function (discrete)
int ternarySearch_max_discrete(int lo, int hi, function<long long(int)> f) {
    while (hi - lo > 2) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1 + 1;
        else hi = m2 - 1;
    }
    // Check remaining candidates
    int best = lo;
    for (int i = lo + 1; i <= hi; i++) {
        if (f(i) > f(best)) best = i;
    }
    return best;
}

// Ternary Search for minimum of unimodal function (discrete)
int ternarySearch_min_discrete(int lo, int hi, function<long long(int)> f) {
    while (hi - lo > 2) {
        int m1 = lo + (hi - lo) / 3;
        int m2 = hi - (hi - lo) / 3;
        if (f(m1) > f(m2)) lo = m1 + 1;
        else hi = m2 - 1;
    }
    int best = lo;
    for (int i = lo + 1; i <= hi; i++) {
        if (f(i) < f(best)) best = i;
    }
    return best;
}

// Ternary Search for maximum (continuous / floating point)
double ternarySearch_max_continuous(double lo, double hi, function<double(double)> f) {
    for (int i = 0; i < 200; i++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2;
}

// Ternary Search for minimum (continuous / floating point)
double ternarySearch_min_continuous(double lo, double hi, function<double(double)> f) {
    for (int i = 0; i < 200; i++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (f(m1) > f(m2)) lo = m1;
        else hi = m2;
    }
    return (lo + hi) / 2;
}

void demo_ternary_search() {
    cout << "=== SECTION 1: TERNARY SEARCH ===" << endl;

    // Example: Find maximum of f(x) = -(x-5)² + 25 (peak at x=5)
    auto f = [](double x) -> double { return -(x - 5) * (x - 5) + 25; };
    double peak = ternarySearch_max_continuous(0, 10, f);
    cout << "Peak of -(x-5)²+25: x=" << peak << ", f(x)=" << f(peak) << endl;

    // Discrete: Find x that maximizes -|x - 7| in [0, 20]
    auto g = [](long long x) -> long long { return -abs(x - 7); };
    int best = ternarySearch_max_discrete(0, 20, g);
    cout << "Max of -|x-7|: x=" << best << ", f(x)=" << g(best) << endl;

    // Minimum of convex function f(x) = x² - 6x + 13 (valley at x=3)
    auto h = [](double x) -> double { return x * x - 6 * x + 13; };
    double valley = ternarySearch_min_continuous(-10, 20, h);
    cout << "Valley of x²-6x+13: x=" << valley << ", f(x)=" << h(valley) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: SEARCH IN ROTATED SORTED ARRAY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A sorted array is rotated at some pivot:
   [4, 5, 6, 7, 0, 1, 2] — rotated by 4 positions

 Property: One half is always sorted!
   At any mid point, either [lo..mid] or [mid..hi] is sorted.
   Use the sorted half to determine which side target is on.

 LC 33: No duplicates — O(log n)
 LC 81: With duplicates — O(n) worst case but O(log n) average
*/

// Version 1: No duplicates (LC 33)
int searchRotated(vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;

        if (nums[lo] <= nums[mid]) {
            // Left half is sorted
            if (nums[lo] <= target && target < nums[mid])
                hi = mid - 1; // Target in sorted left half
            else
                lo = mid + 1; // Target in right half
        } else {
            // Right half is sorted
            if (nums[mid] < target && target <= nums[hi])
                lo = mid + 1; // Target in sorted right half
            else
                hi = mid - 1; // Target in left half
        }
    }
    return -1;
}

// Version 2: With duplicates (LC 81)
bool searchRotated_dup(vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return true;

        // Handle duplicates: shrink boundaries
        if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
            lo++;
            hi--;
        } else if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid])
                hi = mid - 1;
            else
                lo = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[hi])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    return false;
}

void demo_rotated_search() {
    cout << "=== SECTION 2: ROTATED SORTED ARRAY ===" << endl;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    cout << "Search 0: " << searchRotated(nums, 0) << endl;  // 4
    cout << "Search 3: " << searchRotated(nums, 3) << endl;  // -1
    cout << "Search 6: " << searchRotated(nums, 6) << endl;  // 2

    // With duplicates
    vector<int> nums2 = {2, 5, 6, 0, 0, 1, 2};
    cout << "Search 0 (dups): " << searchRotated_dup(nums2, 0) << endl; // true

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: FIND PIVOT IN ROTATED ARRAY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The pivot is the minimum element in a rotated sorted array.
 Or equivalently, the rotation count.

 LC 153: Find Minimum — no duplicates
 LC 154: Find Minimum — with duplicates
*/

// Find minimum in rotated sorted array (no dups) — LC 153
int findMin(vector<int>& nums) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1; // Min is in right half
        else hi = mid; // Mid could be the min
    }
    return nums[lo];
}

// Find minimum with duplicates — LC 154
int findMin_dup(vector<int>& nums) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else if (nums[mid] < nums[hi]) hi = mid;
        else hi--; // Can't determine, shrink
    }
    return nums[lo];
}

// Find rotation count (index of minimum element)
int findRotationCount(vector<int>& nums) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void demo_find_pivot() {
    cout << "=== SECTION 3: FIND PIVOT ===" << endl;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << "Min: " << findMin(nums) << endl;  // 0
    cout << "Rotation count: " << findRotationCount(nums) << endl;  // 4

    vector<int> nums2 = {2, 2, 2, 0, 1};
    cout << "Min (dups): " << findMin_dup(nums2) << endl;  // 0

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: PEAK ELEMENT (1D)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A peak element is strictly greater than its neighbors.
 The array may have multiple peaks — find any one.

 KEY INSIGHT:
   If arr[mid] < arr[mid+1], there MUST be a peak on the right side.
   (Because the array goes up, and must come down eventually or hit boundary)
   Similarly, if arr[mid] < arr[mid-1], peak is on the left.

 LC 162: Find Peak Element — O(log n)
*/

int findPeakElement(vector<int>& nums) {
    int lo = 0, hi = (int)nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < nums[mid + 1]) lo = mid + 1; // Peak on right
        else hi = mid; // Mid could be peak (or peak is on left)
    }
    return lo;
}

void demo_peak_element() {
    cout << "=== SECTION 4: PEAK ELEMENT ===" << endl;

    vector<int> nums = {1, 2, 3, 1};
    cout << "Peak index: " << findPeakElement(nums)
         << " (value " << nums[findPeakElement(nums)] << ")" << endl; // 2 (value 3)

    vector<int> nums2 = {1, 2, 1, 3, 5, 6, 4};
    int peak = findPeakElement(nums2);
    cout << "Peak index: " << peak << " (value " << nums2[peak] << ")" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: MOUNTAIN ARRAY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A mountain array increases then decreases with exactly one peak.
 [0, 1, 2, 4, 2, 1]  — peak at index 3

 PROBLEMS:
   1. Find peak in mountain array — O(log n)
   2. Search in mountain array — O(log n): find peak, then BS each half
   3. Valid Mountain Array — O(n) check

 LC 852: Peak Index in a Mountain Array
 LC 1095: Find in Mountain Array
 LC 941: Valid Mountain Array
*/

// Find peak in mountain array
int peakIndexInMountainArray(vector<int>& arr) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < arr[mid + 1]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

// Search in mountain array (LC 1095)
int searchMountainArray(vector<int>& arr, int target) {
    int peak = peakIndexInMountainArray(arr);

    // Binary search in ascending part [0, peak]
    int lo = 0, hi = peak;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }

    // Binary search in descending part [peak+1, n-1]
    lo = peak + 1;
    hi = (int)arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] > target) lo = mid + 1; // Descending!
        else hi = mid - 1;
    }

    return -1;
}

// Valid Mountain Array
bool validMountainArray(vector<int>& arr) {
    int n = arr.size();
    if (n < 3) return false;
    int i = 0;
    while (i + 1 < n && arr[i] < arr[i + 1]) i++;
    if (i == 0 || i == n - 1) return false; // No ascending or no descending
    while (i + 1 < n && arr[i] > arr[i + 1]) i++;
    return i == n - 1;
}

void demo_mountain_array() {
    cout << "=== SECTION 5: MOUNTAIN ARRAY ===" << endl;

    vector<int> mountain = {0, 1, 2, 4, 2, 1};
    cout << "Peak index: " << peakIndexInMountainArray(mountain) << endl; // 3

    cout << "Search 2: " << searchMountainArray(mountain, 2) << endl; // 2 (ascending)
    cout << "Search 1: " << searchMountainArray(mountain, 1) << endl; // 1 (ascending)

    cout << "Valid mountain: " << validMountainArray(mountain) << endl; // 1

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: EXPONENTIAL SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Exponential Search finds the range where target might be,
 then does binary search within that range.

 ALGORITHM:
   1. Start with bound = 1
   2. While arr[bound] < target: bound *= 2 (double)
   3. Binary search in [bound/2, min(bound, n-1)]

 TIME: O(log n) — even for unbounded arrays!
 BEST FOR: Unbounded arrays, element near the beginning

 ADVANTAGE over plain BS:
   If target is at position k, exponential search takes O(log k)
   instead of O(log n). Better when k << n.
*/

int exponentialSearch(vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;
    if (arr[0] == target) return 0;

    int bound = 1;
    while (bound < n && arr[bound] < target) bound *= 2;

    int lo = bound / 2;
    int hi = min(bound, n - 1);
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

void demo_exponential_search() {
    cout << "=== SECTION 6: EXPONENTIAL SEARCH ===" << endl;

    vector<int> arr = {2, 3, 4, 10, 40, 50, 60, 70, 80, 90, 100};
    cout << "Search 10: " << exponentialSearch(arr, 10) << endl;  // 3
    cout << "Search 100: " << exponentialSearch(arr, 100) << endl; // 10
    cout << "Search 5: " << exponentialSearch(arr, 5) << endl;    // -1

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: INTERPOLATION SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Interpolation Search estimates the position of the target based
 on the VALUE of the target relative to the endpoints.

 Instead of mid = (lo + hi) / 2, we use:
   mid = lo + ((target - arr[lo]) * (hi - lo)) / (arr[hi] - arr[lo])

 This is like how humans search a dictionary — if looking for "Z",
 start near the end, not the middle.

 COMPLEXITY:
   Best: O(1) — guess correctly
   Average: O(log log n) — for uniformly distributed data!
   Worst: O(n) — for exponentially distributed data

 REQUIREMENT: Sorted, uniformly distributed data
*/

int interpolationSearch(vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;

    while (lo <= hi && target >= arr[lo] && target <= arr[hi]) {
        if (lo == hi) {
            if (arr[lo] == target) return lo;
            return -1;
        }

        // Estimate position using interpolation
        long long pos = lo + (long long)(target - arr[lo]) * (hi - lo) / (arr[hi] - arr[lo]);

        if (arr[pos] == target) return (int)pos;
        if (arr[pos] < target) lo = (int)pos + 1;
        else hi = (int)pos - 1;
    }
    return -1;
}

void demo_interpolation_search() {
    cout << "=== SECTION 7: INTERPOLATION SEARCH ===" << endl;

    // Uniformly distributed data — interpolation search excels
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    cout << "Search 70: " << interpolationSearch(arr, 70) << endl;  // 6
    cout << "Search 45: " << interpolationSearch(arr, 45) << endl;  // -1

    // Non-uniform data — may degrade
    vector<int> arr2 = {1, 2, 3, 4, 100, 200, 300, 400, 500};
    cout << "Search 300 (non-uniform): " << interpolationSearch(arr2, 300) << endl; // 6

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: BINARY LIFTING CONCEPT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Binary Lifting is a technique used primarily in TREE problems:
   • Find kth ancestor of a node in O(log n)
   • LCA (Lowest Common Ancestor) in O(log n)

 IDEA:
   Pre-compute 2^j-th ancestor for each node.
   up[v][j] = 2^j-th ancestor of node v

   PRECOMPUTATION:
     up[v][0] = parent[v]  (direct parent)
     up[v][j] = up[up[v][j-1]][j-1]  (2^j = 2^(j-1) + 2^(j-1))

   QUERY for kth ancestor:
     Decompose k into binary: k = b₀ + 2*b₁ + 4*b₂ + ...
     For each set bit j in k: v = up[v][j]

 COMPLEXITY:
   Preprocessing: O(n log n)
   Query: O(log n)

 NOTE: Full implementation is in Tree Algorithms chapter.
 Here we show the concept applied to simpler problems.
*/

// Simple Binary Lifting on array: Find position after k jumps
// Each position i has next[i] = where you jump from i
class BinaryLifting {
    vector<vector<int>> up; // up[j][i] = position after 2^j jumps from i
    int LOG;

public:
    void build(vector<int>& next) {
        int n = next.size();
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(LOG, vector<int>(n));
        for (int i = 0; i < n; i++) up[0][i] = next[i];

        for (int j = 1; j < LOG; j++)
            for (int i = 0; i < n; i++)
                up[j][i] = up[j - 1][up[j - 1][i]]; // 2^j = 2^(j-1) + 2^(j-1)
    }

    int jump(int pos, int k) {
        for (int j = 0; j < LOG && k > 0; j++) {
            if (k & (1 << j)) {
                pos = up[j][pos];
                k ^= (1 << j);
            }
        }
        return pos;
    }
};

void demo_binary_lifting() {
    cout << "=== SECTION 8: BINARY LIFTING ===" << endl;

    // Example: Circular array, jump to next[i] from position i
    // next[i] = (i + 3) % n → jump 3 positions each time
    int n = 10;
    vector<int> next(n);
    for (int i = 0; i < n; i++) next[i] = (i + 3) % n;

    BinaryLifting bl;
    bl.build(next);

    cout << "Jump 1 from pos 0: " << bl.jump(0, 1) << endl;   // 3
    cout << "Jump 2 from pos 0: " << bl.jump(0, 2) << endl;   // 6
    cout << "Jump 5 from pos 0: " << bl.jump(0, 5) << endl;   // (0→3→6→9→2→5) = 5
    cout << "Jump 1000000 from pos 0: " << bl.jump(0, 1000000) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 09: ADVANCED SEARCHING TECHNIQUES                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_ternary_search();
    demo_rotated_search();
    demo_find_pivot();
    demo_peak_element();
    demo_mountain_array();
    demo_exponential_search();
    demo_interpolation_search();
    demo_binary_lifting();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 09 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Find Peak Element (LC 162)                                             ║
║  2. Peak Index in Mountain Array (LC 852)                                  ║
║  3. Valid Mountain Array (LC 941)                                          ║
║  4. Find Minimum in Rotated Array (LC 153)                                 ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  5. Search in Rotated Sorted Array (LC 33)                                 ║
║  6. Search in Rotated II (LC 81) — duplicates                              ║
║  7. Find in Mountain Array (LC 1095)                                       ║
║  8. Single Element in Sorted Array (LC 540)                                ║
║  9. CF 439D — Devu and Birthday Celebration (ternary)                      ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 10. Find Minimum in Rotated II (LC 154)                                    ║
║ 11. CF 1117C — Magic Ship (BS + geometry)                                  ║
║ 12. CF 1300E — Water Balance (ternary + stack)                             ║
║ 13. CSES — Company Queries I (binary lifting)                              ║
║ 14. CSES — Company Queries II (LCA with binary lifting)                    ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 15. CF 1523D — Sequence Sorting                                            ║
║ 16. Ternary search on convex functions in geometry                         ║
║ 17. Binary lifting for functional graph problems                           ║
║ 18. CF 1486D — Max Median (BS + prefix)                                    ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

