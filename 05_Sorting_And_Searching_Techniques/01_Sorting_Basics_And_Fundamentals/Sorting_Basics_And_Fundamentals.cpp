/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01 — SORTING BASICS & FUNDAMENTALS                         ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Why Sorting? — Motivation & Applications
 2.  Stability in Sorting (Stable vs Unstable)
 3.  In-Place vs Not In-Place Sorting
 4.  Comparison-Based vs Non-Comparison Sorting
 5.  Time Complexity Analysis — Best / Average / Worst
 6.  Space Complexity Analysis
 7.  STL sort() Internals — IntroSort
 8.  Sorting Classification Summary Table
 9.  Practical Demonstrations

WHY SORTING?
─────────────
Sorting is the foundation of algorithmic problem-solving.
Nearly 40% of competitive programming problems require sorting as a
preprocessing step. Sorted data unlocks:
  • Binary search → O(log n) lookups
  • Two-pointer techniques
  • Greedy algorithms (activity selection, interval scheduling)
  • Efficient duplicate detection
  • Merge-based divide & conquer
  • Median / percentile queries
  • Sweep line algorithms

SORTING CLASSIFICATION:
───────────────────────
┌─────────────────────┬────────────────────────────────────────────┐
│ Criteria            │ Categories                                 │
├─────────────────────┼────────────────────────────────────────────┤
│ Stability           │ Stable (Merge, Insertion, Counting, Radix) │
│                     │ Unstable (Quick, Heap, Selection)          │
├─────────────────────┼────────────────────────────────────────────┤
│ Memory              │ In-place (Quick, Heap, Bubble, Selection)  │
│                     │ Not in-place (Merge, Counting, Radix)      │
├─────────────────────┼────────────────────────────────────────────┤
│ Method              │ Comparison-based (Merge, Quick, Heap)      │
│                     │ Non-comparison (Counting, Radix, Bucket)   │
├─────────────────────┼────────────────────────────────────────────┤
│ Complexity          │ O(n²): Bubble, Selection, Insertion        │
│                     │ O(n log n): Merge, Quick, Heap             │
│                     │ O(n+k) / O(nk): Counting, Radix, Bucket    │
└─────────────────────┴────────────────────────────────────────────┘

MASTER COMPLEXITY TABLE:
────────────────────────
┌──────────────────┬──────────┬──────────┬──────────┬───────┬────────┬────────┐
│ Algorithm        │ Best     │ Average  │ Worst    │ Space │ Stable │In-Place│
├──────────────────┼──────────┼──────────┼──────────┼───────┼────────┼────────┤
│ Bubble Sort      │ O(n)     │ O(n²)    │ O(n²)    │ O(1)  │ Yes    │ Yes    │
│ Selection Sort   │ O(n²)    │ O(n²)    │ O(n²)    │ O(1)  │ No     │ Yes    │
│ Insertion Sort   │ O(n)     │ O(n²)    │ O(n²)    │ O(1)  │ Yes    │ Yes    │
│ Merge Sort       │ O(nlogn) │ O(nlogn) │ O(nlogn) │ O(n)  │ Yes    │ No     │
│ Quick Sort       │ O(nlogn) │ O(nlogn) │ O(n²)    │O(logn)│ No     │ Yes    │
│ Heap Sort        │ O(nlogn) │ O(nlogn) │ O(nlogn) │ O(1)  │ No     │ Yes    │
│ Counting Sort    │ O(n+k)   │ O(n+k)   │ O(n+k)   │ O(k)  │ Yes    │ No     │
│ Radix Sort       │ O(nk)    │ O(nk)    │ O(nk)    │ O(n+k)│ Yes    │ No     │
│ Bucket Sort      │ O(n+k)   │ O(n+k)   │ O(n²)    │ O(n)  │ Yes    │ No     │
│ Shell Sort       │ O(nlogn) │ O(n^1.5) │ O(n²)    │ O(1)  │ No     │ Yes    │
│ Tim Sort         │ O(n)     │ O(nlogn) │ O(nlogn) │ O(n)  │ Yes    │ No     │
│ STL sort()       │ O(nlogn) │ O(nlogn) │ O(nlogn) │O(logn)│ No     │ Yes    │
│ STL stable_sort()│ O(nlogn) │ O(nlogn) │ O(nlogn) │ O(n)  │ Yes    │ No     │
└──────────────────┴──────────┴──────────┴──────────┴───────┴────────┴────────┘

LOWER BOUND THEOREM:
────────────────────
Any comparison-based sorting algorithm must make at least Ω(n log n)
comparisons in the worst case. This is proven by the decision tree model.
  • Decision tree has n! leaves (all permutations)
  • Height ≥ log₂(n!) = Ω(n log n)  [Stirling's approximation]
  • So Merge Sort & Heap Sort are OPTIMAL comparison-based sorts.

Non-comparison sorts (Counting, Radix, Bucket) bypass this bound by
exploiting the structure/range of input values.

COMPETITIVE PROGRAMMING TIPS:
─────────────────────────────
  • Use std::sort() for 99% of problems — it's O(n log n) guaranteed
  • Use std::stable_sort() when you need stability
  • Know when O(n²) is acceptable: n ≤ 5000
  • Know when O(n log n) is needed: n ≤ 10^6
  • Custom comparators are CRUCIAL for CP
  • Sorting is often the FIRST step in greedy problems
  • Always think: "Would sorting help here?"
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <functional>
#include <cstring>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: WHY SORTING? — MOTIVATION & APPLICATIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Sorting transforms chaos into order. Once data is sorted, many
 operations become dramatically faster:

 Without sorting:
   • Search: O(n)
   • Find duplicates: O(n²) or O(n) with hash
   • Find pair with sum X: O(n²)
   • Find median: O(n) [using quickselect]

 With sorting:
   • Search: O(log n) [binary search]
   • Find duplicates: O(n) [adjacent check]
   • Find pair with sum X: O(n) [two pointers]
   • Find median: O(1) [middle element]

 APPLICATIONS IN CP:
   1. Greedy: Sort by deadline, weight, ratio, etc.
   2. Binary Search: Sort + BS = O(n log n + q log n)
   3. Two Pointers: Only works on sorted data
   4. Sweep Line: Events sorted by coordinate/time
   5. Coordinate Compression: Sort + unique + BS
   6. Counting Inversions: Merge sort variant
   7. Interval Problems: Sort by start/end time
*/

void demo_why_sorting() {
    cout << "=== SECTION 1: WHY SORTING ===" << endl;

    // Example 1: Finding duplicates — O(n) after sorting vs O(n²) brute force
    vector<int> arr = {5, 3, 8, 3, 1, 5, 9, 1};

    // Brute force O(n²)
    bool has_dup_brute = false;
    for (int i = 0; i < (int)arr.size(); i++)
        for (int j = i + 1; j < (int)arr.size(); j++)
            if (arr[i] == arr[j]) has_dup_brute = true;

    // After sorting O(n log n + n)
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    bool has_dup_sort = false;
    for (int i = 1; i < (int)sorted_arr.size(); i++)
        if (sorted_arr[i] == sorted_arr[i - 1]) has_dup_sort = true;

    assert(has_dup_brute == has_dup_sort);
    cout << "Duplicates found: " << (has_dup_sort ? "Yes" : "No") << endl;

    // Example 2: Two-pointer pair sum after sorting
    // Find if any pair sums to 10
    int target = 10;
    int lo = 0, hi = (int)sorted_arr.size() - 1;
    bool found = false;
    while (lo < hi) {
        int sum = sorted_arr[lo] + sorted_arr[hi];
        if (sum == target) { found = true; break; }
        else if (sum < target) lo++;
        else hi--;
    }
    cout << "Pair with sum " << target << ": " << (found ? "Yes" : "No") << endl;

    // Example 3: Binary search after sorting
    int key = 8;
    bool exists = binary_search(sorted_arr.begin(), sorted_arr.end(), key);
    cout << "Element " << key << " exists: " << (exists ? "Yes" : "No") << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: STABILITY IN SORTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A sorting algorithm is STABLE if it preserves the relative order of
 elements with equal keys.

 Example:
   Input:  [(A,2), (B,1), (C,2), (D,1)]
   Sort by second element:

   STABLE result:   [(B,1), (D,1), (A,2), (C,2)]
     → B comes before D (original order preserved for equal keys)
     → A comes before C (original order preserved for equal keys)

   UNSTABLE result: [(D,1), (B,1), (C,2), (A,2)]  — also valid but order not guaranteed

 WHY STABILITY MATTERS:
   1. Multi-key sorting: Sort by name, then stable sort by grade
      → Students with same grade remain sorted by name
   2. When original order has meaning (e.g., input order = priority)
   3. Required in some problems explicitly

 STABLE algorithms:    Bubble, Insertion, Merge, Counting, Radix, TimSort
 UNSTABLE algorithms:  Selection, Quick, Heap, Shell

 C++ STL:
   std::sort()        → UNSTABLE (IntroSort)
   std::stable_sort() → STABLE   (TimSort variant / Merge Sort)

 KEY INSIGHT for CP:
   If you need stability with std::sort(), encode the original index
   as a secondary key: sort by (value, original_index)
*/

void demo_stability() {
    cout << "=== SECTION 2: STABILITY ===" << endl;

    // Demonstrate stability with pair sorting
    // Pair: (name_char, score)
    vector<pair<int, char>> students = {
        {85, 'A'}, {90, 'B'}, {85, 'C'}, {90, 'D'}, {85, 'E'}
    };

    // std::sort — UNSTABLE: equal elements may be reordered
    vector<pair<int, char>> v1 = students;
    sort(v1.begin(), v1.end());
    cout << "std::sort (unstable): ";
    for (auto& p : v1) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // std::stable_sort — STABLE: equal elements keep original order
    vector<pair<int, char>> v2 = students;
    stable_sort(v2.begin(), v2.end());
    cout << "std::stable_sort:     ";
    for (auto& p : v2) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;
    // For stable_sort: 85s must appear as A,C,E (original order)

    // Achieving stability with unstable sort: encode original index
    vector<pair<int, char>> v3 = students;
    vector<int> idx(v3.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (v3[a].first != v3[b].first) return v3[a].first < v3[b].first;
        return a < b; // tiebreak by original index → makes it stable
    });
    cout << "sort + index trick:   ";
    for (int i : idx) cout << "(" << v3[i].first << "," << v3[i].second << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: IN-PLACE vs NOT IN-PLACE SORTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 IN-PLACE sorting: Uses O(1) or O(log n) extra space.
   The algorithm sorts the data within the original array.
   Examples: Bubble, Selection, Insertion, Quick, Heap, Shell

 NOT IN-PLACE sorting: Uses O(n) or more extra space.
   The algorithm needs auxiliary arrays.
   Examples: Merge Sort (O(n) extra), Counting Sort (O(k) extra),
             Radix Sort (O(n+k) extra), Bucket Sort (O(n) extra)

 WHY IT MATTERS:
   • Memory-constrained environments prefer in-place
   • In-place sorts often have better cache performance
   • Not in-place sorts can be faster or more stable

 SPACE COMPLEXITY:
   O(1)     : Bubble, Selection, Insertion, Heap
   O(log n) : Quick Sort (recursion stack)
   O(n)     : Merge Sort, Tim Sort
   O(k)     : Counting Sort (k = range of values)
   O(n+k)   : Radix Sort
*/

void demo_inplace_vs_not() {
    cout << "=== SECTION 3: IN-PLACE vs NOT IN-PLACE ===" << endl;

    // In-place example: Bubble sort — modifies array directly
    vector<int> arr1 = {5, 3, 8, 1, 2};
    // Bubble sort in-place — O(1) extra space
    for (int i = 0; i < (int)arr1.size(); i++)
        for (int j = 0; j < (int)arr1.size() - 1 - i; j++)
            if (arr1[j] > arr1[j + 1])
                swap(arr1[j], arr1[j + 1]);
    cout << "In-place (Bubble): ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // Not in-place example: Counting sort — needs O(k) extra array
    vector<int> arr2 = {5, 3, 8, 1, 2};
    int maxVal = *max_element(arr2.begin(), arr2.end());
    vector<int> count(maxVal + 1, 0); // O(k) extra space
    for (int x : arr2) count[x]++;
    vector<int> result;
    for (int i = 0; i <= maxVal; i++)
        while (count[i]-- > 0) result.push_back(i);
    cout << "Not in-place (Counting): ";
    for (int x : result) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMPARISON-BASED vs NON-COMPARISON SORTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 COMPARISON-BASED: Only uses pairwise comparisons (< > == ≤ ≥)
   • Lower bound: Ω(n log n) — proven by decision tree argument
   • Examples: Bubble, Selection, Insertion, Merge, Quick, Heap
   • Works on ANY data type that supports comparison

 NON-COMPARISON: Uses arithmetic / indexing on values
   • Can achieve O(n) time by exploiting value range/structure
   • Examples: Counting Sort, Radix Sort, Bucket Sort
   • Requires values to be integers or have bounded range

 DECISION TREE LOWER BOUND PROOF:
   • n elements have n! possible permutations
   • Each comparison has 2 outcomes (yes/no) → binary tree
   • Binary tree with n! leaves has height ≥ log₂(n!)
   • log₂(n!) = Ω(n log n) by Stirling's approximation
   • Therefore: Any comparison sort needs Ω(n log n) comparisons

 WHEN TO USE WHICH:
   • General data, unknown range → Comparison-based (std::sort)
   • Small integer range [0..k], k ≈ n → Counting Sort O(n+k)
   • Large integers, fixed digits → Radix Sort O(d*(n+b))
   • Uniformly distributed floats → Bucket Sort O(n) expected
*/

void demo_comparison_vs_non() {
    cout << "=== SECTION 4: COMPARISON vs NON-COMPARISON ===" << endl;

    // Comparison-based: std::sort uses IntroSort internally
    vector<int> arr = {9, 4, 7, 2, 5, 1, 8, 3, 6};
    sort(arr.begin(), arr.end()); // O(n log n) comparison-based
    cout << "Comparison (std::sort): ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Non-comparison: Counting sort — O(n + k) where k = max value
    vector<int> arr2 = {4, 2, 2, 8, 3, 3, 1};
    int k = *max_element(arr2.begin(), arr2.end());
    vector<int> cnt(k + 1, 0);
    for (int x : arr2) cnt[x]++;
    cout << "Non-comparison (Counting): ";
    for (int i = 0; i <= k; i++)
        for (int j = 0; j < cnt[i]; j++)
            cout << i << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: TIME COMPLEXITY ANALYSIS — Best / Average / Worst
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Understanding WHEN each case occurs is critical:

 BUBBLE SORT:
   Best:  O(n)     — Already sorted, optimized version with flag
   Avg:   O(n²)    — Random permutation
   Worst: O(n²)    — Reverse sorted

 SELECTION SORT:
   Best:  O(n²)    — Always scans entire unsorted portion
   Avg:   O(n²)    — Always same number of comparisons
   Worst: O(n²)    — Same

 INSERTION SORT:
   Best:  O(n)     — Already sorted, each insert is O(1)
   Avg:   O(n²)    — Random permutation
   Worst: O(n²)    — Reverse sorted, each insert shifts all

 MERGE SORT:
   Best:  O(n log n) — Always divides in half, merges in O(n)
   Avg:   O(n log n) — Same
   Worst: O(n log n) — Same (very consistent!)

 QUICK SORT:
   Best:  O(n log n) — Balanced partition each time
   Avg:   O(n log n) — Random pivot gives expected balanced
   Worst: O(n²)      — Already sorted + bad pivot (first/last)
   FIX: Randomized pivot → O(n log n) expected

 HEAP SORT:
   Best:  O(n log n) — Always builds heap + extracts
   Avg:   O(n log n) — Same
   Worst: O(n log n) — Same (guaranteed!)

 COUNTING SORT:
   All: O(n + k) where k = range of values
   Bad when k >> n (wastes space and time)

 IMPORTANT INSIGHT:
   • For n ≤ 1000: O(n²) is fine (~10⁶ operations)
   • For n ≤ 10⁵: Need O(n log n) (~1.7 × 10⁶ operations)
   • For n ≤ 10⁷: Need O(n) or O(n log n) with small constant

 AMORTIZED / EXPECTED:
   • Quick Sort with random pivot: O(n log n) EXPECTED
   • IntroSort (C++ sort): O(n log n) WORST CASE guaranteed
     → Starts QuickSort, switches to HeapSort if depth > 2log(n)
*/

void demo_complexity() {
    cout << "=== SECTION 5: COMPLEXITY ANALYSIS ===" << endl;

    // Demonstrate how input order affects performance
    int n = 10000;

    // Best case for Insertion Sort: already sorted
    vector<int> sorted_arr(n);
    iota(sorted_arr.begin(), sorted_arr.end(), 0);

    // Worst case for Insertion Sort: reverse sorted
    vector<int> reverse_arr(n);
    iota(reverse_arr.begin(), reverse_arr.end(), 0);
    reverse(reverse_arr.begin(), reverse_arr.end());

    // Average case: random
    vector<int> random_arr(n);
    iota(random_arr.begin(), random_arr.end(), 0);
    // Simple shuffle
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(random_arr[i], random_arr[j]);
    }

    // Count comparisons for insertion sort
    auto count_insertion_comparisons = [](vector<int> arr) -> long long {
        long long comp = 0;
        for (int i = 1; i < (int)arr.size(); i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && (++comp, arr[j] > key)) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return comp;
    };

    long long best_comp = count_insertion_comparisons(sorted_arr);
    long long worst_comp = count_insertion_comparisons(reverse_arr);
    long long avg_comp = count_insertion_comparisons(random_arr);

    cout << "Insertion Sort comparisons (n=" << n << "):" << endl;
    cout << "  Best case (sorted):  " << best_comp << endl;
    cout << "  Worst case (reverse): " << worst_comp << endl;
    cout << "  Average case (random): " << avg_comp << endl;
    cout << "  Ratio worst/best: " << (double)worst_comp / max(best_comp, 1LL) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: SPACE COMPLEXITY ANALYSIS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Space complexity = extra memory used (beyond input).

 O(1) — Constant space:
   Bubble, Selection, Insertion, Heap Sort
   These only use a few variables for swapping.

 O(log n) — Logarithmic space:
   Quick Sort — recursion call stack depth
   (Can be O(n) in worst case without tail recursion optimization)

 O(n) — Linear space:
   Merge Sort — needs auxiliary array of size n
   Tim Sort — needs auxiliary array
   stable_sort() in C++ — O(n) extra

 O(k) — Depends on range:
   Counting Sort — O(k) where k = max - min + 1
   Radix Sort — O(n + b) where b = base (usually 10 or 256)

 CP INSIGHT:
   Memory limit is usually 256 MB.
   • int array of 10⁷ ≈ 40 MB → OK
   • int array of 10⁸ ≈ 400 MB → MLE!
   • In-place sort saves memory when n is large
*/

void demo_space() {
    cout << "=== SECTION 6: SPACE COMPLEXITY ===" << endl;

    cout << "In-place sorts (O(1) extra): Bubble, Selection, Insertion, Heap" << endl;
    cout << "O(log n) extra: Quick Sort (stack depth)" << endl;
    cout << "O(n) extra: Merge Sort, Stable Sort, Tim Sort" << endl;
    cout << "O(k) extra: Counting Sort (k = value range)" << endl;

    // Practical: Memory usage comparison
    int n = 1000000;
    cout << "\nFor n = " << n << ":" << endl;
    cout << "  In-place sort: ~" << n * 4 / (1024 * 1024) << " MB (input only)" << endl;
    cout << "  Merge sort:    ~" << n * 8 / (1024 * 1024) << " MB (input + aux)" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: STL sort() INTERNALS — INTROSORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 std::sort() in C++ implements INTROSORT (Introspective Sort):
   1. Starts with Quick Sort (fast in practice)
   2. If recursion depth exceeds 2*log₂(n), switches to Heap Sort
      → This prevents Quick Sort's O(n²) worst case
   3. For small subarrays (n ≤ 16), uses Insertion Sort
      → Insertion Sort has smaller constant factor for tiny arrays

 This gives us:
   • Average case: O(n log n) — from QuickSort's good average
   • Worst case: O(n log n) — HeapSort's guarantee kicks in
   • Small arrays: Fast — InsertionSort's low overhead

 std::stable_sort() uses:
   • Merge Sort variant (TimSort-like)
   • O(n) extra space
   • Guaranteed O(n log n) and STABLE

 IMPORTANT: std::sort is NOT stable!
   If you need stability, use std::stable_sort()
   or add index as secondary key.

 UNDER THE HOOD (GCC libstdc++):
   __introsort_loop():
     - partition with median-of-three pivot
     - recurse on smaller half, iterate on larger (tail call optimization)
     - if depth_limit == 0, call partial_sort (heap sort)
   __final_insertion_sort():
     - called after introsort loop
     - handles small partitions with insertion sort

 PRACTICAL PERFORMANCE:
   std::sort is 2-3x faster than hand-written merge sort
   due to cache-friendliness and constant factor optimization.
*/

void demo_stl_sort() {
    cout << "=== SECTION 7: STL sort() INTERNALS ===" << endl;

    vector<int> arr = {9, 1, 4, 7, 2, 8, 3, 6, 5};

    // Default sort — ascending
    sort(arr.begin(), arr.end());
    cout << "sort() ascending: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Descending — using greater<int>
    sort(arr.begin(), arr.end(), greater<int>());
    cout << "sort() descending: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Descending — using reverse iterators
    sort(arr.rbegin(), arr.rend());
    // This sorts in ascending order on reverse iterators = descending on normal
    // Wait — rbegin/rend with default < gives ascending on reversed = ascending again
    // Actually: sort(rbegin, rend) with default < sorts in descending order
    sort(arr.rbegin(), arr.rend()); // descending
    cout << "sort() rbegin/rend: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Custom comparator with lambda
    sort(arr.begin(), arr.end(), [](int a, int b) {
        return a % 2 < b % 2; // even numbers first, then odd
    });
    cout << "sort() even first: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // stable_sort preserves relative order of equal elements
    vector<pair<int, int>> data = {{3, 1}, {1, 2}, {3, 3}, {2, 4}, {1, 5}};
    stable_sort(data.begin(), data.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first < b.first;
    });
    cout << "stable_sort by first: ";
    for (auto& p : data) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: SORTING ALGORITHM SELECTION GUIDE
// ═══════════════════════════════════════════════════════════════
/*
 WHEN TO USE WHAT:
 ─────────────────

 ┌─────────────────────────────┬───────────────────────────────────────┐
 │ Situation                   │ Best Algorithm                        │
 ├─────────────────────────────┼───────────────────────────────────────┤
 │ General purpose             │ std::sort() — IntroSort               │
 │ Need stability              │ std::stable_sort() or Merge Sort      │
 │ Nearly sorted data          │ Insertion Sort or Tim Sort            │
 │ Small arrays (n ≤ 50)       │ Insertion Sort                        │
 │ Memory constrained          │ Heap Sort (in-place, O(1) extra)      │
 │ Small integer range         │ Counting Sort                         │
 │ Large integers, d digits    │ Radix Sort                            │
 │ Uniform float distribution  │ Bucket Sort                           │
 │ External sorting (disk)     │ Merge Sort (sequential access)        │
 │ Parallel sorting            │ Merge Sort (naturally parallelizable) │
 │ Online (streaming) data     │ Insertion Sort                        │
 │ Linked list sorting         │ Merge Sort (no random access needed)  │
 └─────────────────────────────┴───────────────────────────────────────┘

 CP DECISION TREE:
   1. n ≤ 5000? → Any O(n²) sort works
   2. Need stable? → stable_sort()
   3. Integer range small? → Counting Sort
   4. Otherwise → sort() (always correct choice in CP)
*/

void demo_selection_guide() {
    cout << "=== SECTION 8: ALGORITHM SELECTION GUIDE ===" << endl;

    cout << "For CP, 99% of the time: use std::sort()" << endl;
    cout << "Need stability? → std::stable_sort()" << endl;
    cout << "Counting integers in [0,k]? → Counting sort when k is small" << endl;

    // Demo: Sorting different data types
    // 1. Sort integers
    vector<int> ints = {5, 2, 8, 1, 9};
    sort(ints.begin(), ints.end());

    // 2. Sort strings (lexicographic)
    vector<string> strs = {"banana", "apple", "cherry"};
    sort(strs.begin(), strs.end());
    cout << "Sorted strings: ";
    for (auto& s : strs) cout << s << " ";
    cout << endl;

    // 3. Sort pairs (by first, then second)
    vector<pair<int, int>> pairs = {{3, 1}, {1, 2}, {3, 0}};
    sort(pairs.begin(), pairs.end());
    cout << "Sorted pairs: ";
    for (auto& p : pairs) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // 4. Sort array (C-style)
    int c_arr[] = {7, 3, 5, 1};
    sort(c_arr, c_arr + 4);
    cout << "Sorted C-array: ";
    for (int x : c_arr) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: PRACTICAL DEMONSTRATIONS & EDGE CASES
// ═══════════════════════════════════════════════════════════════
/*
 COMMON MISTAKES AND EDGE CASES:
 ────────────────────────────────
 1. Empty array → sort works fine, no crash
 2. Single element → already sorted
 3. All same elements → O(n) for some, O(n log n) for others
 4. Negative numbers → work fine with default comparator
 5. Integer overflow in comparator → use subtraction carefully!
    WRONG: return a - b; (can overflow!)
    RIGHT: return a < b;
 6. Sorting structs without operator< → compile error
    FIX: Define operator< or use custom comparator
*/

void demo_edge_cases() {
    cout << "=== SECTION 9: EDGE CASES ===" << endl;

    // Edge case 1: Empty array
    vector<int> empty;
    sort(empty.begin(), empty.end());
    cout << "Empty array sort: OK (size=" << empty.size() << ")" << endl;

    // Edge case 2: Single element
    vector<int> single = {42};
    sort(single.begin(), single.end());
    cout << "Single element: " << single[0] << endl;

    // Edge case 3: All same elements
    vector<int> same(10, 5);
    sort(same.begin(), same.end());
    cout << "All same: ";
    for (int x : same) cout << x << " ";
    cout << endl;

    // Edge case 4: Negative numbers
    vector<int> neg = {-3, 5, -1, 0, -7, 2};
    sort(neg.begin(), neg.end());
    cout << "With negatives: ";
    for (int x : neg) cout << x << " ";
    cout << endl;

    // Edge case 5: Large values — comparator safety
    vector<long long> big = {2000000000LL, -2000000000LL, 1000000000LL};
    sort(big.begin(), big.end()); // Default < is safe
    cout << "Large values: ";
    for (long long x : big) cout << x << " ";
    cout << endl;

    // Edge case 6: Sorting a subarray
    vector<int> arr = {5, 3, 8, 1, 2, 7, 4, 6};
    sort(arr.begin() + 2, arr.begin() + 6); // Sort indices [2, 6)
    cout << "Partial sort [2,6): ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 01: SORTING BASICS & FUNDAMENTALS                 ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_why_sorting();
    demo_stability();
    demo_inplace_vs_not();
    demo_comparison_vs_non();
    demo_complexity();
    demo_space();
    demo_stl_sort();
    demo_selection_guide();
    demo_edge_cases();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 01 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Sort an Array (LC 912)                                                 ║
║  2. Sort Colors (LC 75) — Dutch National Flag                              ║
║  3. Squares of a Sorted Array (LC 977)                                     ║
║  4. Valid Anagram (LC 242) — Sort both strings                             ║
║  5. Relative Sort Array (LC 1122)                                          ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  6. CF 1291A — Even But Not Even                                           ║
║  7. CF 1370A — Maximum GCD                                                 ║
║  8. Largest Number (LC 179) — Custom comparator                            ║
║  9. Sort Characters By Frequency (LC 451)                                  ║
║ 10. CSES — Apartments (sorting + two pointer)                              ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 11. CF 1133E — K Balanced Teams                                            ║
║ 12. Maximum Gap (LC 164) — Bucket sort O(n)                                ║
║ 13. CSES — Tasks and Deadlines                                             ║
║ 14. Count of Smaller Numbers After Self (LC 315)                           ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 15. CF 1208F — Bits And Pieces (sorting + bitmask)                         ║
║ 16. Inversion Count using Merge Sort                                       ║
║ 17. SPOJ INVCNT — Inversion Count                                          ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

