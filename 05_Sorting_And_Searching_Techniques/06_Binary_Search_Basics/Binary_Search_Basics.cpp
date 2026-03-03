/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 06 — BINARY SEARCH BASICS                                  ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Classic Binary Search — Iterative
 2.  Binary Search — Recursive Version
 3.  Lower Bound & Upper Bound
 4.  First Occurrence of Element
 5.  Last Occurrence of Element
 6.  Count of Element in Sorted Array
 7.  Search in Infinite Sorted Array
 8.  Binary Search Templates (Closed/Open Interval)
 9. STL Binary Search Functions

OVERVIEW:
─────────
Binary Search is THE most important searching algorithm.
It reduces O(n) search to O(log n) by halving the search space.

PREREQUISITE: The search space must have a MONOTONIC property.
  • Sorted array: arr[i] ≤ arr[i+1]
  • Predicate function: f(x) = false...false true...true

CORE IDEA:
  If the search space has size n:
  • 1 step → n/2
  • 2 steps → n/4
  • k steps → n/2^k
  • To reach 1: k = log₂(n)

BINARY SEARCH PARADIGMS:
  1. Search for a VALUE in sorted array
  2. Search for a POSITION (lower_bound, upper_bound)
  3. Search for an ANSWER (binary search on answer — Chapter 07)

COMMON MISTAKES:
  ❌ Off-by-one errors (lo vs hi, < vs <=)
  ❌ Infinite loops (forgetting to update lo or hi)
  ❌ Integer overflow: mid = (lo + hi) / 2 → use lo + (hi - lo) / 2
  ❌ Applying BS on unsorted data
  ❌ Wrong return value for not-found case

MASTER TEMPLATE:
  The KEY insight: Binary search finds the BOUNDARY between false and true.
  If predicate P(x) is monotonic (FFF...TTT), binary search finds
  the first T (or last F).
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
#include <climits>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CLASSIC BINARY SEARCH — ITERATIVE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Search for target in sorted array. Return index or -1.

 ALGORITHM:
   lo = 0, hi = n-1
   while lo <= hi:
     mid = lo + (hi - lo) / 2
     if arr[mid] == target: return mid
     if arr[mid] < target: lo = mid + 1
     else: hi = mid - 1
   return -1

 INVARIANT: If target exists, it's always in [lo, hi]

 TIME: O(log n)
 SPACE: O(1)

 VARIATIONS:
   1. Find exact match
   2. Find leftmost match (first occurrence)
   3. Find rightmost match (last occurrence)
   4. Find insertion point
*/

// Version 1: Standard Binary Search — find exact match
int binarySearch(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1; // Not found
}

// Version 2: Using STL
bool binarySearch_stl(const vector<int>& arr, int target) {
    return binary_search(arr.begin(), arr.end(), target);
}

void demo_classic_bs() {
    cout << "=== SECTION 1: CLASSIC BINARY SEARCH ===" << endl;

    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << "Search 7: index " << binarySearch(arr, 7) << endl;
    cout << "Search 10: index " << binarySearch(arr, 10) << " (not found)" << endl;
    cout << "Search 1: index " << binarySearch(arr, 1) << endl;
    cout << "Search 19: index " << binarySearch(arr, 19) << endl;

    // Trace for search 7:
    // lo=0, hi=9, mid=4, arr[4]=9 > 7 → hi=3
    // lo=0, hi=3, mid=1, arr[1]=3 < 7 → lo=2
    // lo=2, hi=3, mid=2, arr[2]=5 < 7 → lo=3
    // lo=3, hi=3, mid=3, arr[3]=7 == 7 → return 3 ✓

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: BINARY SEARCH — RECURSIVE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Same logic as iterative, but using recursion.
 Less common in CP (iterative is preferred for efficiency),
 but useful for understanding divide & conquer.

 RECURSION: T(n) = T(n/2) + O(1) → O(log n)
 SPACE: O(log n) for recursion stack
*/
int binarySearch_recursive(const vector<int>& arr, int target, int lo, int hi) {
    // Base Case: Search space is exhausted
    if (lo > hi) return -1;

    // GM Optimization: Prevents (low + high) overflow for large arrays
    int mid = lo + (hi - lo) / 2;

    if (arr[mid] == target) return mid; // Target found

    // Target is in the right half
    if (arr[mid] < target) return binarySearch_recursive(arr, target, mid + 1, hi);

    // Target is in the left half
    return binarySearch_recursive(arr, target, lo, mid - 1);
}

void demo_recursive_bs() {
    cout << "=== SECTION 2: RECURSIVE BINARY SEARCH ===" << endl;

    vector<int> arr = {2, 4, 6, 8, 10, 12, 14, 16};
    cout << "Search 10: index " << binarySearch_recursive(arr, 10, 0, arr.size() - 1) << endl;
    cout << "Search 5: index " << binarySearch_recursive(arr, 5, 0, arr.size() - 1) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LOWER BOUND & UPPER BOUND
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 LOWER BOUND: First position where arr[pos] >= target
   → Leftmost position where target can be inserted to keep sorted order

 UPPER BOUND: First position where arr[pos] > target
   → Rightmost position where target can be inserted to keep sorted order

 RELATIONSHIP:
   lower_bound(x) ≤ upper_bound(x)
   Count of x = upper_bound(x) - lower_bound(x)

 VISUAL:
   arr = [1, 2, 2, 2, 3, 4, 5], target = 2
          0  1  2  3  4  5  6
   lower_bound(2) = 1  (first 2)
   upper_bound(2) = 4  (first element > 2)
   count of 2 = 4 - 1 = 3

 STL:
   lower_bound(begin, end, val) → iterator to first >= val
   upper_bound(begin, end, val) → iterator to first > val

 IMPLEMENTATION INSIGHT:
   lower_bound: Find first index where arr[mid] >= target
   upper_bound: Find first index where arr[mid] > target
   The only difference is >= vs > in the condition!
*/

// Manual lower_bound: first index with arr[index] >= target
int lowerBound(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid; // arr[mid] >= target, could be the answer
    }
    return lo;
}

// Manual upper_bound: first index with arr[index] > target
int upperBound(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void demo_lower_upper_bound() {
    cout << "=== SECTION 3: LOWER BOUND & UPPER BOUND ===" << endl;

    vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Manual implementation
    cout << "lower_bound(2) = " << lowerBound(arr, 2) << endl; // 1
    cout << "upper_bound(2) = " << upperBound(arr, 2) << endl; // 4
    cout << "lower_bound(3) = " << lowerBound(arr, 3) << endl; // 4
    cout << "lower_bound(0) = " << lowerBound(arr, 0) << endl; // 0
    cout << "lower_bound(6) = " << lowerBound(arr, 6) << endl; // 7

    // STL
    auto lb = lower_bound(arr.begin(), arr.end(), 2);
    auto ub = upper_bound(arr.begin(), arr.end(), 2);
    cout << "STL lower_bound(2): index " << (lb - arr.begin()) << endl;
    cout << "STL upper_bound(2): index " << (ub - arr.begin()) << endl;
    cout << "Count of 2: " << (ub - lb) << endl;

    // equal_range: returns pair(lower_bound, upper_bound)
    auto [lo_it, hi_it] = equal_range(arr.begin(), arr.end(), 2);
    cout << "equal_range(2): [" << (lo_it - arr.begin()) << ", "
         << (hi_it - arr.begin()) << ")" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: FIRST OCCURRENCE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Find the FIRST (leftmost) occurrence of target in sorted array.
 This is essentially lower_bound, but returns -1 if not found.

 APPROACH: Binary search, but when arr[mid] == target,
 don't return immediately — keep searching LEFT (hi = mid - 1)
*/

int firstOccurrence(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    int result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            result = mid;  // Record answer
            hi = mid - 1;  // Keep searching left for earlier occurrence
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return result;
}

// Alternative: Using lower_bound
int firstOccurrence_v2(const vector<int>& arr, int target) {
    int pos = lowerBound(arr, target);
    if (pos < (int)arr.size() && arr[pos] == target) return pos;
    return -1;
}

void demo_first_occurrence() {
    cout << "=== SECTION 4: FIRST OCCURRENCE ===" << endl;

    vector<int> arr = {1, 2, 2, 2, 3, 3, 4, 5};
    cout << "First occurrence of 2: " << firstOccurrence(arr, 2) << endl;  // 1
    cout << "First occurrence of 3: " << firstOccurrence(arr, 3) << endl;  // 4
    cout << "First occurrence of 6: " << firstOccurrence(arr, 6) << endl;  // -1

    assert(firstOccurrence(arr, 2) == firstOccurrence_v2(arr, 2));

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: LAST OCCURRENCE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Find the LAST (rightmost) occurrence of target.
 When arr[mid] == target, keep searching RIGHT (lo = mid + 1).
 Alternative: upper_bound - 1
*/

int lastOccurrence(const vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    int result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            result = mid;
            lo = mid + 1; // Keep searching right
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return result;
}

// Alternative: Using upper_bound
int lastOccurrence_v2(const vector<int>& arr, int target) {
    int pos = upperBound(arr, target) - 1;
    if (pos >= 0 && arr[pos] == target) return pos;
    return -1;
}

void demo_last_occurrence() {
    cout << "=== SECTION 5: LAST OCCURRENCE ===" << endl;

    vector<int> arr = {1, 2, 2, 2, 3, 3, 4, 5};
    cout << "Last occurrence of 2: " << lastOccurrence(arr, 2) << endl;  // 3
    cout << "Last occurrence of 3: " << lastOccurrence(arr, 3) << endl;  // 5
    cout << "Last occurrence of 6: " << lastOccurrence(arr, 6) << endl;  // -1

    assert(lastOccurrence(arr, 2) == lastOccurrence_v2(arr, 2));

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: COUNT OF ELEMENT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Count = Last Occurrence - First Occurrence + 1
 Or: upper_bound - lower_bound

 TIME: O(log n) — two binary searches
*/

int countElement(const vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return 0;
    int last = lastOccurrence(arr, target);
    return last - first + 1;
}

// Using STL
int countElement_stl(const vector<int>& arr, int target) {
    auto [lo, hi] = equal_range(arr.begin(), arr.end(), target);
    return hi - lo;
}

void demo_count_element() {
    cout << "=== SECTION 6: COUNT OF ELEMENT ===" << endl;

    vector<int> arr = {1, 1, 2, 2, 2, 3, 3, 3, 3, 4};
    cout << "Count of 1: " << countElement(arr, 1) << endl;  // 2
    cout << "Count of 2: " << countElement(arr, 2) << endl;  // 3
    cout << "Count of 3: " << countElement(arr, 3) << endl;  // 4
    cout << "Count of 5: " << countElement(arr, 5) << endl;  // 0

    // Verify with STL
    assert(countElement(arr, 2) == countElement_stl(arr, 2));

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: SEARCH IN INFINITE SORTED ARRAY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 If the array is "infinite" (unknown size), we can't use hi = n-1.

 APPROACH: Exponential Search
   1. Start with range [0, 1]
   2. Double the range until arr[hi] >= target
   3. Binary search in [lo, hi]

 TIME: O(log n) where n is the position of the target
 This is optimal — we don't even know n!

 PRACTICAL USE:
   • Unbounded/streaming data
   • API-based access (you can query arr[i] but don't know size)
   • Often combined with binary search on answer
*/

// Simulates infinite array with boundary checking
int searchInfinite(const vector<int>& arr, int target) {
    // Step 1: Find bounds using exponential search
    int lo = 0, hi = 1;

    // In real infinite case, use API access instead of size()
    while (hi < (int)arr.size() && arr[hi] < target) {
        lo = hi;
        hi *= 2;
    }
    hi = min(hi, (int)arr.size() - 1);

    // Step 2: Binary search in [lo, hi]
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// Pure Exponential Search
int exponentialSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;
    if (arr[0] == target) return 0;

    int bound = 1;
    while (bound < n && arr[bound] < target) {
        bound *= 2;
    }

    // Binary search in [bound/2, min(bound, n-1)]
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

void demo_infinite_search() {
    cout << "=== SECTION 8: INFINITE ARRAY SEARCH ===" << endl;

    // Simulate a large sorted array
    vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) arr[i] = 2 * i + 1; // 1, 3, 5, 7, ...

    cout << "Search 501: " << searchInfinite(arr, 501) << endl;  // 250
    cout << "Search 999: " << exponentialSearch(arr, 999) << endl;  // 499
    cout << "Search 100: " << exponentialSearch(arr, 100) << endl;  // -1 (even)

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: BINARY SEARCH TEMPLATES
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 There are several binary search templates. Choose one and stick with it.

 TEMPLATE 1: CLOSED INTERVAL [lo, hi]
   lo = 0, hi = n-1
   while (lo <= hi)
     mid = lo + (hi-lo)/2
     if found: return mid
     if go right: lo = mid+1
     if go left: hi = mid-1
   return -1

 TEMPLATE 2: HALF-OPEN INTERVAL [lo, hi)  ← BEST FOR BOUNDS
   lo = 0, hi = n
   while (lo < hi)
     mid = lo + (hi-lo)/2
     if predicate(mid): hi = mid    // mid could be answer
     else: lo = mid+1               // mid is not answer
   return lo   // lo == hi == answer

 TEMPLATE 3: PREDICATE-BASED (Boolean BS)
   Find first position where predicate is true.
   Assumes: predicate is FFFF...TTTT (monotonic)

   lo = first_possible, hi = last_possible + 1
   while (lo < hi)
     mid = lo + (hi-lo)/2
     if predicate(mid): hi = mid
     else: lo = mid+1
   return lo

 WHICH TO USE?
   • Exact match: Template 1
   • Find boundary (lower/upper bound): Template 2
   • Binary search on answer: Template 3

 MY RECOMMENDATION FOR CP:
   Use Template 2 (half-open) for everything. It's the most versatile
   and least error-prone.
*/

// Template 2: Generic binary search for first position where predicate is true
// predicate: false...false true...true
// Returns first true position, or hi if all false
template<typename Predicate>
int binarySearchFirst(int lo, int hi, Predicate pred) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (pred(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// Template for last position where predicate is true
// predicate: true...true false...false
// Returns last true position, or lo-1 if all false
template<typename Predicate>
int binarySearchLast(int lo, int hi, Predicate pred) {
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // Ceiling division to avoid infinite loop
        if (pred(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

void demo_templates() {
    cout << "=== SECTION 9: BINARY SEARCH TEMPLATES ===" << endl;

    vector<int> arr = {1, 2, 4, 4, 4, 7, 8, 9};

    // Find first element >= 4 using template
    int pos = binarySearchFirst(0, (int)arr.size(), [&](int mid) {
        return arr[mid] >= 4;
    });
    cout << "First >= 4: index " << pos << " (value " << arr[pos] << ")" << endl;

    // Find last element <= 4 using template
    int pos2 = binarySearchLast(0, (int)arr.size() - 1, [&](int mid) {
        return arr[mid] <= 4;
    });
    cout << "Last <= 4: index " << pos2 << " (value " << arr[pos2] << ")" << endl;

    // Find first element > 4
    int pos3 = binarySearchFirst(0, (int)arr.size(), [&](int mid) {
        return arr[mid] > 4;
    });
    cout << "First > 4: index " << pos3 << " (value " << arr[pos3] << ")" << endl;

    // Find sqrt(50) using binary search on answer
    int sqrtVal = binarySearchLast(0, 50, [](int mid) {
        return (long long)mid * mid <= 50;
    });
    cout << "Floor sqrt(50) = " << sqrtVal << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: STL BINARY SEARCH FUNCTIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 C++ STL provides these binary search functions in <algorithm>:

 1. binary_search(first, last, val):
    Returns true if val exists in [first, last)
    Time: O(log n)

 2. lower_bound(first, last, val):
    Returns iterator to first element >= val
    Time: O(log n)

 3. upper_bound(first, last, val):
    Returns iterator to first element > val
    Time: O(log n)

 4. equal_range(first, last, val):
    Returns pair(lower_bound, upper_bound)
    Time: O(log n)

 ALL REQUIRE SORTED RANGE!

 CUSTOM COMPARATOR:
   All functions accept optional comparator:
   lower_bound(first, last, val, comp)

 IMPORTANT: These work on random-access iterators in O(log n).
   For forward iterators (like set), they work in O(n) because
   they can't jump to mid.
   → Use set.lower_bound() for O(log n) on sets!
*/

void demo_stl_functions() {
    cout << "=== SECTION 10: STL BINARY SEARCH ===" << endl;

    vector<int> arr = {1, 2, 4, 4, 4, 7, 8, 9};

    // binary_search
    cout << "Contains 4: " << binary_search(arr.begin(), arr.end(), 4) << endl;
    cout << "Contains 5: " << binary_search(arr.begin(), arr.end(), 5) << endl;

    // lower_bound
    auto lb = lower_bound(arr.begin(), arr.end(), 4);
    cout << "lower_bound(4): index " << (lb - arr.begin()) << endl;

    // upper_bound
    auto ub = upper_bound(arr.begin(), arr.end(), 4);
    cout << "upper_bound(4): index " << (ub - arr.begin()) << endl;

    // equal_range
    auto [lo, hi] = equal_range(arr.begin(), arr.end(), 4);
    cout << "equal_range(4): [" << (lo - arr.begin()) << ", " << (hi - arr.begin()) << ")" << endl;

    // Count of 4
    cout << "Count of 4: " << (ub - lb) << endl;

    // Custom comparator: search in descending sorted array
    vector<int> desc = {9, 8, 7, 4, 4, 4, 2, 1};
    auto lb_desc = lower_bound(desc.begin(), desc.end(), 4, greater<int>());
    cout << "lower_bound(4) in desc: index " << (lb_desc - desc.begin()) << endl;

    // On set (use member function for O(log n))
    set<int> s = {1, 3, 5, 7, 9};
    auto it = s.lower_bound(4); // O(log n) — member function
    cout << "set lower_bound(4): " << *it << endl; // 5

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// BONUS: COMMON BINARY SEARCH PATTERNS
// ═══════════════════════════════════════════════════════════════

void demo_common_patterns() {
    cout << "=== BONUS: COMMON BS PATTERNS ===" << endl;

    // Pattern 1: Floor of a value (largest element ≤ target)
    vector<int> arr = {1, 2, 4, 6, 8, 10};
    int target = 5;
    auto it = upper_bound(arr.begin(), arr.end(), target);
    if (it != arr.begin()) {
        --it;
        cout << "Floor of " << target << ": " << *it << endl; // 4
    }

    // Pattern 2: Ceil of a value (smallest element ≥ target)
    auto it2 = lower_bound(arr.begin(), arr.end(), target);
    if (it2 != arr.end()) {
        cout << "Ceil of " << target << ": " << *it2 << endl; // 6
    }

    // Pattern 3: Closest element to target
    auto it3 = lower_bound(arr.begin(), arr.end(), target);
    int closest;
    if (it3 == arr.end()) closest = arr.back();
    else if (it3 == arr.begin()) closest = arr.front();
    else {
        int right = *it3;
        int left = *prev(it3);
        closest = (target - left <= right - target) ? left : right;
    }
    cout << "Closest to " << target << ": " << closest << endl; // 4

    // Pattern 4: Count elements in range [lo, hi]
    int lo_val = 3, hi_val = 8;
    int count_in_range = upper_bound(arr.begin(), arr.end(), hi_val) -
                         lower_bound(arr.begin(), arr.end(), lo_val);
    cout << "Count in [" << lo_val << "," << hi_val << "]: " << count_in_range << endl; // 3 (4,6,8)

    // Pattern 5: Find square root using binary search
    long long n = 1000000000000LL;
    long long lo = 0, hi = 1000000;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (mid <= n / mid) lo = mid;
        else hi = mid - 1;
    }
    cout << "sqrt(" << n << ") = " << lo << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 06: BINARY SEARCH BASICS                           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_classic_bs();
    demo_recursive_bs();
    demo_lower_upper_bound();
    demo_first_occurrence();
    demo_last_occurrence();
    demo_count_element();
    demo_search_insert();
    demo_infinite_search();
    demo_templates();
    demo_stl_functions();
    demo_common_patterns();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 06 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                    ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  🟢 EASY:                                                                    ║
║  1. Binary Search (LC 704)                                                   ║
║  2. Search Insert Position (LC 35)                                           ║
║  3. First Bad Version (LC 278)                                               ║
║  4. Sqrt(x) (LC 69)                                                          ║
║  5. Guess Number Higher or Lower (LC 374)                                    ║
║                                                                              ║
║  🟡 MEDIUM:                                                                  ║
║  6. Find First and Last Position (LC 34)                                     ║
║  7. Find Minimum in Rotated Sorted Array (LC 153)                            ║
║  8. Search a 2D Matrix (LC 74)                                               ║
║  9. CSES — Factory Machines                                                  ║
║ 10. CF 1201C — Maximum Median                                                ║
║ 11. Single Element in Sorted Array (LC 540)                                  ║
║                                                                              ║
║  🔴 HARD:                                                                    ║
║ 12. Median of Two Sorted Arrays (LC 4)                                       ║
║ 13. Find in Mountain Array (LC 1095)                                         ║
║ 14. CSES — Array Division                                                    ║
║ 15. CF 1117C — Magic Ship                                                    ║
║                                                                              ║
║  🔵 GRANDMASTER:                                                             ║
║ 16. Kth Smallest Number in Multiplication Table (LC 668)                     ║
║ 17. CF 1468C — Boredom (BS on answer)                                        ║
║ 18. CSES — Minimizing Coins (BS variation)                                   ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/


