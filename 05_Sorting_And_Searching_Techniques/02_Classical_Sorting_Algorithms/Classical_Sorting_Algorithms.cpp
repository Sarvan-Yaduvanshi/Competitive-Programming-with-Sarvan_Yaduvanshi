/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02 — CLASSICAL SORTING ALGORITHMS                        ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Bubble Sort — Basic, Optimized, Recursive
 2.  Selection Sort — Basic, Stable Variant
 3.  Insertion Sort — Basic, Binary Insertion, Recursive
 4.  Comparison & Analysis
 5.  Counting Inversions (Bonus)
 6.  When O(n²) Sorts are Useful in CP

OVERVIEW:
─────────
These are the "elementary" sorting algorithms. They are O(n²) worst-case
but have educational value and real practical uses:

  • Understanding sorting fundamentals
  • Small input sizes (n ≤ 1000)
  • Nearly-sorted data (Insertion Sort shines: O(n))
  • Used as building blocks in advanced sorts (TimSort uses Insertion Sort)
  • Interview questions & competitive programming basics

COMPARISON AT A GLANCE:
┌───────────────────┬──────────┬──────────┬──────────┬───────┬────────┐
│ Algorithm         │ Best     │ Average  │ Worst    │ Stable│Adaptive│
├───────────────────┼──────────┼──────────┼──────────┼───────┼────────┤
│ Bubble Sort       │ O(n)     │ O(n²)    │ O(n²)    │ Yes   │ Yes    │
│ Selection Sort    │ O(n²)    │ O(n²)    │ O(n²)    │ No*   │ No     │
│ Insertion Sort    │ O(n)     │ O(n²)    │ O(n²)    │ Yes   │ Yes    │
└───────────────────┴──────────┴──────────┴──────────┴───────┴────────┘
  * Selection sort can be made stable with linked list or shifting

ADAPTIVE means: algorithm is faster when data is nearly sorted.
  • Bubble Sort: Stops early if no swaps in a pass → O(n) for sorted
  • Insertion Sort: Each element shifts little → O(n) for sorted
  • Selection Sort: Always does n(n-1)/2 comparisons → NOT adaptive
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <climits>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BUBBLE SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Bubble Sort repeatedly swaps adjacent elements if they are in the
 wrong order. After each pass, the largest unsorted element "bubbles"
 to its correct position at the end.

 ALGORITHM:
   for i = 0 to n-1:
     for j = 0 to n-2-i:
       if arr[j] > arr[j+1]:
         swap(arr[j], arr[j+1])

 DRY RUN: [5, 3, 8, 1, 2]
   Pass 1: [3,5,1,2,8]  — 8 bubbled to end
   Pass 2: [3,1,2,5,8]  — 5 bubbled to position
   Pass 3: [1,2,3,5,8]  — 3 bubbled to position
   Pass 4: [1,2,3,5,8]  — No swaps, DONE (optimized)

 PROPERTIES:
   • Stable: Yes (only swaps adjacent, never jumps equal elements)
   • In-place: Yes, O(1) extra space
   • Adaptive: Yes (with optimization flag)
   • Number of swaps = Number of inversions

 INVERSIONS:
   An inversion is a pair (i,j) where i < j but arr[i] > arr[j].
   Bubble sort performs exactly one swap per inversion.
   So total swaps = total inversions in the array.

 WHEN TO USE:
   • Educational purposes
   • When you need to count inversions (swaps = inversions)
   • Tiny arrays (n ≤ 100)
   • When array is nearly sorted (with optimization: O(n))
*/

// Version 1: Basic Bubble Sort
void bubbleSort_basic(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Version 2: Optimized Bubble Sort (with early termination)
// If no swaps in a pass, array is sorted → stop early
void bubbleSort_optimized(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Array is sorted!
    }
}

// Version 3: Further Optimized — Track last swap position
// Elements after last swap are already sorted
void bubbleSort_further_optimized(vector<int>& arr) {
    int n = arr.size();
    int newn;
    do {
        newn = 0;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                newn = i + 1; // Last position where swap happened
            }
        }
        n = newn; // Everything after newn is sorted
    } while (newn > 0);
}

// Version 4: Recursive Bubble Sort
void bubbleSort_recursive(vector<int>& arr, int n) {
    if (n <= 1) return;
    bool swapped = false;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
            swapped = true;
        }
    }
    if (!swapped) return;
    bubbleSort_recursive(arr, n - 1);
}

// Version 5: Bubble Sort with swap/inversion counting
long long bubbleSort_count_swaps(vector<int>& arr) {
    int n = arr.size();
    long long swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
    return swaps;
}

// Version 6: Cocktail Shaker Sort (Bidirectional Bubble Sort)
// Bubbles in both directions — slightly better for some inputs
void cocktailShakerSort(vector<int>& arr) {
    int n = arr.size();
    int start = 0, end = n - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        // Forward pass
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        end--;
        if (!swapped) break;
        swapped = false;
        // Backward pass
        for (int i = end; i > start; i--) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        start++;
    }
}

void demo_bubble_sort() {
    cout << "=== SECTION 1: BUBBLE SORT ===" << endl;

    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    // Basic
    vector<int> v1 = arr;
    bubbleSort_basic(v1);
    cout << "Basic: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Optimized
    vector<int> v2 = arr;
    bubbleSort_optimized(v2);
    cout << "Optimized: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Further Optimized
    vector<int> v3 = arr;
    bubbleSort_further_optimized(v3);
    cout << "Further Optimized: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // Recursive
    vector<int> v4 = arr;
    bubbleSort_recursive(v4, v4.size());
    cout << "Recursive: ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    // Count swaps
    vector<int> v5 = arr;
    long long swaps = bubbleSort_count_swaps(v5);
    cout << "Swaps (= inversions): " << swaps << endl;

    // Cocktail Shaker
    vector<int> v6 = arr;
    cocktailShakerSort(v6);
    cout << "Cocktail Shaker: ";
    for (int x : v6) cout << x << " ";
    cout << endl;

    // Test adaptive behavior
    vector<int> sorted_arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v7 = sorted_arr;
    bubbleSort_optimized(v7); // Should terminate after 1 pass
    cout << "Already sorted → Optimized Bubble is O(n)" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: SELECTION SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Selection Sort divides the array into sorted (left) and unsorted (right).
 In each iteration, it SELECTS the minimum from the unsorted portion
 and places it at the beginning of the unsorted portion.

 ALGORITHM:
   for i = 0 to n-2:
     minIdx = i
     for j = i+1 to n-1:
       if arr[j] < arr[minIdx]:
         minIdx = j
     swap(arr[i], arr[minIdx])

 DRY RUN: [64, 25, 12, 22, 11]
   Pass 1: min=11 at idx 4, swap with idx 0 → [11, 25, 12, 22, 64]
   Pass 2: min=12 at idx 2, swap with idx 1 → [11, 12, 25, 22, 64]
   Pass 3: min=22 at idx 3, swap with idx 2 → [11, 12, 22, 25, 64]
   Pass 4: min=25 at idx 3, swap with idx 3 → [11, 12, 22, 25, 64]

 PROPERTIES:
   • Stable: NO (swap can jump over equal elements)
     Example: [5a, 3, 5b, 2] → min=2, swap 5a↔2 → [2, 3, 5b, 5a] → 5a after 5b!
   • In-place: Yes, O(1) extra space
   • Adaptive: NO — always does exactly n(n-1)/2 comparisons
   • Number of swaps: O(n) — at most n-1 swaps (good for expensive writes!)

 KEY INSIGHT:
   Selection Sort minimizes the number of SWAPS.
   • Bubble Sort: O(n²) swaps in worst case
   • Selection Sort: O(n) swaps always
   → Use Selection Sort when writes are expensive (e.g., flash memory)

 WHEN TO USE:
   • When write operations are costly
   • When you need minimum number of swaps
   • When n is very small
*/

// Version 1: Basic Selection Sort
void selectionSort_basic(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Version 2: Double Selection Sort (find both min and max per pass)
void selectionSort_double(vector<int>& arr) {
    int n = arr.size();
    int left = 0, right = n - 1;
    while (left < right) {
        int minIdx = left, maxIdx = left;
        for (int i = left; i <= right; i++) {
            if (arr[i] < arr[minIdx]) minIdx = i;
            if (arr[i] > arr[maxIdx]) maxIdx = i;
        }
        swap(arr[left], arr[minIdx]);
        // If max was at position left, it moved to minIdx after the swap
        if (maxIdx == left) maxIdx = minIdx;
        swap(arr[right], arr[maxIdx]);
        left++;
        right--;
    }
}

// Version 3: Stable Selection Sort (using shifting instead of swapping)
// This preserves relative order of equal elements
void selectionSort_stable(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Instead of swap, shift elements right and insert min at i
        int key = arr[minIdx];
        for (int j = minIdx; j > i; j--) {
            arr[j] = arr[j - 1]; // shift right
        }
        arr[i] = key;
    }
}

// Version 4: Selection Sort counting swaps
int selectionSort_count_swaps(vector<int>& arr) {
    int n = arr.size();
    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            swaps++;
        }
    }
    return swaps;
}

void demo_selection_sort() {
    cout << "=== SECTION 2: SELECTION SORT ===" << endl;

    vector<int> arr = {64, 25, 12, 22, 11};

    // Basic
    vector<int> v1 = arr;
    selectionSort_basic(v1);
    cout << "Basic: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Double
    vector<int> v2 = arr;
    selectionSort_double(v2);
    cout << "Double: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Stable
    vector<int> v3 = arr;
    selectionSort_stable(v3);
    cout << "Stable: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // Count swaps
    vector<int> v4 = arr;
    int swaps = selectionSort_count_swaps(v4);
    cout << "Swaps: " << swaps << " (max n-1 = " << arr.size() - 1 << ")" << endl;

    // Demonstrate instability
    cout << "Instability demo: ";
    vector<pair<int, char>> data = {{5, 'A'}, {3, 'B'}, {5, 'C'}, {2, 'D'}};
    // Manual selection sort on pairs (sort by first only)
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (data[j].first < data[minIdx].first) minIdx = j;
        swap(data[i], data[minIdx]);
    }
    for (auto& p : data) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;
    // Notice: 5A and 5C may be reordered → UNSTABLE

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: INSERTION SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Insertion Sort builds the sorted array one element at a time.
 It takes each element and inserts it into its correct position
 in the already-sorted left portion.

 Think of it like sorting playing cards in your hand:
   Pick up cards one by one, insert each into the correct position.

 ALGORITHM:
   for i = 1 to n-1:
     key = arr[i]
     j = i - 1
     while j >= 0 and arr[j] > key:
       arr[j+1] = arr[j]   // shift right
       j--
     arr[j+1] = key         // insert at correct position

 DRY RUN: [5, 3, 8, 1, 2]
   i=1: key=3, shift 5 right → [3, 5, 8, 1, 2]
   i=2: key=8, no shift → [3, 5, 8, 1, 2]
   i=3: key=1, shift 8,5,3 right → [1, 3, 5, 8, 2]
   i=4: key=2, shift 8,5,3 right → [1, 2, 3, 5, 8]

 PROPERTIES:
   • Stable: Yes (shifts, never swaps past equal elements)
   • In-place: Yes, O(1) extra space
   • Adaptive: Yes — O(n) for nearly sorted data!
   • Online: Can sort as data arrives (stream processing)

 COMPLEXITY ANALYSIS:
   Best:  O(n)   — Already sorted, inner loop never executes
   Avg:   O(n²)  — Each element shifts ~n/4 positions on average
   Worst: O(n²)  — Reverse sorted, each element shifts to position 0
   Total shifts = number of inversions in the array

 WHY INSERTION SORT IS IMPORTANT:
   1. Used as base case in IntroSort (std::sort) for n ≤ 16
   2. Used in TimSort for small runs
   3. Best for nearly-sorted data
   4. Best for online/streaming data
   5. Stable and simple

 BINARY INSERTION SORT:
   Instead of linear search for correct position, use binary search.
   • Reduces comparisons from O(n²) to O(n log n)
   • But shifts are still O(n²) → overall still O(n²)
   • Useful when comparison is expensive (e.g., string comparison)
*/

// Version 1: Basic Insertion Sort
void insertionSort_basic(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // shift right
            j--;
        }
        arr[j + 1] = key; // insert at correct position
    }
}

// Version 2: Insertion Sort with swap-based approach
// Less efficient but simpler to understand
void insertionSort_swap(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

// Version 3: Binary Insertion Sort
// Uses binary search to find insertion position
void insertionSort_binary(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        // Binary search for position in arr[0..i-1]
        int lo = 0, hi = i;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] <= key) lo = mid + 1; // <= for stability
            else hi = mid;
        }
        // Shift elements from lo to i-1 right by one
        for (int j = i; j > lo; j--) {
            arr[j] = arr[j - 1];
        }
        arr[lo] = key;
    }
}

// Version 4: Recursive Insertion Sort
void insertionSort_recursive(vector<int>& arr, int n) {
    if (n <= 1) return;
    insertionSort_recursive(arr, n - 1);
    int key = arr[n - 1];
    int j = n - 2;
    while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = key;
}

// Version 5: Insertion Sort counting shifts
long long insertionSort_count_shifts(vector<int>& arr) {
    int n = arr.size();
    long long shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            shifts++;
        }
        arr[j + 1] = key;
    }
    return shifts;
}

// Version 6: Insertion Sort for nearly-sorted data
// When each element is at most k positions from its sorted position
// Time: O(nk) which is O(n) when k is constant
void insertionSort_kSorted(vector<int>& arr, int k) {
    // Same as basic insertion sort — it's naturally optimal for this case
    // Each inner loop runs at most k times
    insertionSort_basic(arr);
}

void demo_insertion_sort() {
    cout << "=== SECTION 3: INSERTION SORT ===" << endl;

    vector<int> arr = {5, 3, 8, 1, 2};

    // Basic
    vector<int> v1 = arr;
    insertionSort_basic(v1);
    cout << "Basic: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Swap-based
    vector<int> v2 = arr;
    insertionSort_swap(v2);
    cout << "Swap-based: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Binary Insertion
    vector<int> v3 = arr;
    insertionSort_binary(v3);
    cout << "Binary Insertion: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // Recursive
    vector<int> v4 = arr;
    insertionSort_recursive(v4, v4.size());
    cout << "Recursive: ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    // Count shifts
    vector<int> v5 = arr;
    long long shifts = insertionSort_count_shifts(v5);
    cout << "Total shifts (inversions): " << shifts << endl;

    // Demonstrate adaptive behavior
    vector<int> nearly_sorted = {1, 2, 4, 3, 5, 7, 6, 8, 9, 10};
    vector<int> v6 = nearly_sorted;
    long long shifts2 = insertionSort_count_shifts(v6);
    cout << "Nearly sorted shifts: " << shifts2 << " (very few!)" << endl;

    vector<int> reverse_arr = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> v7 = reverse_arr;
    long long shifts3 = insertionSort_count_shifts(v7);
    cout << "Reverse sorted shifts: " << shifts3 << " (maximum!)" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COMPARISON & ANALYSIS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 HEAD-TO-HEAD COMPARISON:

 ┌─────────────────┬───────────┬──────────┬──────────┬────────────────────┐
 │ Property        │ Bubble    │ Selection│ Insertion│ Winner             │
 ├─────────────────┼───────────┼──────────┼──────────┼────────────────────┤
 │ Best case       │ O(n)      │ O(n²)    │ O(n)     │ Bubble/Insertion   │
 │ Worst case      │ O(n²)     │ O(n²)    │ O(n²)    │ Tie                │
 │ Avg case        │ O(n²)     │ O(n²)    │ O(n²)    │ Tie                │
 │ Swaps (worst)   │ O(n²)     │ O(n)     │ O(n²)    │ Selection          │
 │ Stable          │ Yes       │ No       │ Yes      │ Bubble/Insertion   │
 │ Adaptive        │ Yes       │ No       │ Yes      │ Bubble/Insertion   │
 │ Online          │ No        │ No       │ Yes      │ Insertion          │
 │ Practical speed │ Slowest   │ Middle   │ Fastest  │ Insertion          │
 └─────────────────┴───────────┴──────────┴──────────┴────────────────────┘

 VERDICT:
   • Insertion Sort is the BEST among O(n²) algorithms
   • It's used in practice as a subroutine in IntroSort and TimSort
   • Selection Sort is useful only when minimizing writes
   • Bubble Sort is mainly educational; rarely used in practice
*/

void demo_comparison() {
    cout << "=== SECTION 4: COMPARISON ===" << endl;

    int n = 5000;
    vector<int> random_arr(n);
    iota(random_arr.begin(), random_arr.end(), 0);
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(random_arr[i], random_arr[j]);
    }

    // Count operations for each sort
    vector<int> v1 = random_arr;
    long long bubble_swaps = bubbleSort_count_swaps(v1);

    vector<int> v2 = random_arr;
    int sel_swaps = selectionSort_count_swaps(v2);

    vector<int> v3 = random_arr;
    long long ins_shifts = insertionSort_count_shifts(v3);

    cout << "For random array of size " << n << ":" << endl;
    cout << "  Bubble Sort swaps:     " << bubble_swaps << endl;
    cout << "  Selection Sort swaps:  " << sel_swaps << endl;
    cout << "  Insertion Sort shifts: " << ins_shifts << endl;
    cout << "  Note: Bubble swaps = Insertion shifts = inversions" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: COUNTING INVERSIONS (BONUS)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 An INVERSION is a pair (i, j) where i < j but arr[i] > arr[j].
 Inversions measure how far the array is from being sorted.

 • Sorted array: 0 inversions
 • Reverse sorted: n(n-1)/2 inversions (maximum)

 METHODS:
 1. Brute force: O(n²) — check all pairs
 2. Bubble sort: Count swaps = inversions
 3. Merge sort: Count cross-inversions during merge → O(n log n)
 4. BIT/Fenwick tree: O(n log n)

 This is a CLASSIC problem: SPOJ INVCNT, HackerRank, CF
*/

// O(n²) brute force
long long countInversions_brute(vector<int>& arr) {
    int n = arr.size();
    long long count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) count++;
    return count;
}

// O(n log n) using merge sort
long long mergeCount(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long count = 0;
    count += mergeCount(arr, l, mid);
    count += mergeCount(arr, mid + 1, r);

    // Merge and count cross-inversions
    vector<int> temp;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
            count += (mid - i + 1); // All remaining in left half are inversions
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);
    for (int k = l; k <= r; k++) arr[k] = temp[k - l];
    return count;
}

long long countInversions_mergesort(vector<int> arr) {
    return mergeCount(arr, 0, arr.size() - 1);
}

void demo_inversions() {
    cout << "=== SECTION 5: COUNTING INVERSIONS ===" << endl;

    vector<int> arr = {5, 3, 8, 1, 2};
    long long brute = countInversions_brute(arr);
    long long merge = countInversions_mergesort(arr);

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "Inversions (brute): " << brute << endl;
    cout << "Inversions (merge sort): " << merge << endl;
    assert(brute == merge);

    // Sorted = 0 inversions
    vector<int> sorted_arr = {1, 2, 3, 4, 5};
    cout << "Sorted inversions: " << countInversions_mergesort(sorted_arr) << endl;

    // Reverse sorted = max inversions
    vector<int> rev = {5, 4, 3, 2, 1};
    cout << "Reverse inversions: " << countInversions_mergesort(rev)
         << " (max = " << (int)rev.size() * ((int)rev.size() - 1) / 2 << ")" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: WHEN O(n²) SORTS ARE USEFUL IN CP
// ═══════════════════════════════════════════════════════════════
/*
 PRACTICAL CP SCENARIOS:
 ───────────────────────
 1. n ≤ 1000: Any O(n²) sort is fine within time limits
 2. Nearly sorted data: Insertion Sort → O(n)
 3. Counting minimum swaps to sort: Bubble Sort / cycle counting
 4. Sorting by custom expensive comparison: Minimize comparisons
 5. Problems asking to simulate sorting steps
 6. As subroutine in other algorithms

 EXAMPLE PROBLEMS:
   • "Minimum adjacent swaps to sort" → Bubble Sort / Inversions
   • "Sort a nearly sorted array" → Insertion Sort
   • "Minimum swaps to make array sorted" → Cycle decomposition
   • "Count inversions" → Merge Sort technique
*/

void demo_practical_uses() {
    cout << "=== SECTION 6: PRACTICAL USES ===" << endl;

    // Problem: Minimum adjacent swaps to sort = count inversions
    vector<int> arr = {3, 1, 2};
    cout << "Array: 3 1 2" << endl;
    cout << "Min adjacent swaps to sort: " << countInversions_mergesort(arr) << endl;
    // [3,1,2] → swap(3,1) → [1,3,2] → swap(3,2) → [1,2,3] = 2 swaps

    // Problem: Minimum swaps (not adjacent) to sort → cycle decomposition
    auto minSwaps = [](vector<int> arr) {
        int n = arr.size();
        vector<pair<int, int>> arrIdx(n);
        for (int i = 0; i < n; i++) arrIdx[i] = {arr[i], i};
        sort(arrIdx.begin(), arrIdx.end());

        vector<bool> visited(n, false);
        int swaps = 0;
        for (int i = 0; i < n; i++) {
            if (visited[i] || arrIdx[i].second == i) continue;
            int cycle_size = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = arrIdx[j].second;
                cycle_size++;
            }
            swaps += (cycle_size - 1);
        }
        return swaps;
    };

    vector<int> arr2 = {4, 3, 1, 2};
    cout << "Array: 4 3 1 2" << endl;
    cout << "Min swaps (any) to sort: " << minSwaps(arr2) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 02: CLASSICAL SORTING ALGORITHMS                  ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_bubble_sort();
    demo_selection_sort();
    demo_insertion_sort();
    demo_comparison();
    demo_inversions();
    demo_practical_uses();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 02 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Sort an Array (LC 912) — implement each algorithm                      ║
║  2. Insertion Sort (HackerRank)                                            ║
║  3. Sort Colors (LC 75) — counting sort variant                            ║
║  4. CF 339A — Helpfulness                                                  ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  5. Insertion Sort List (LC 147) — sort linked list                        ║
║  6. Count Inversions (SPOJ INVCNT)                                         ║
║  7. HackerRank — Insertion Sort Analysis (count shifts)                    ║
║  8. CF 1430C — Numbers on Whiteboard                                       ║
║  9. Minimum Swaps to Sort (GFG)                                            ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 10. Count of Smaller Numbers After Self (LC 315)                           ║
║ 11. Reverse Pairs (LC 493) — merge sort variant                            ║
║ 12. Global and Local Inversions (LC 775)                                   ║
║ 13. CSES — Inversion Count                                                 ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 14. CF 1430E — String Reversal (inversions with strings)                   ║
║ 15. CF 987C — Three displays (DP after sorting)                            ║
║ 16. Count inversions in a stream (online inversion counting)               ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

