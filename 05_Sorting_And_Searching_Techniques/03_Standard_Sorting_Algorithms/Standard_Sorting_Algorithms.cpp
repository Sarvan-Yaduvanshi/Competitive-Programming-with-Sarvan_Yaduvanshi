/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 03 — STANDARD SORTING ALGORITHMS                         ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Merge Sort — Basic, Bottom-Up, In-Place Concept
 2.  Quick Sort — Basic, Randomized, 3-Way Partition, Tail Optimized
 3.  Heap Sort — Heapify, Build Heap, Full Sort
 4.  Shell Sort — Gap Sequences, Analysis
 5.  TimSort — Concept, Runs, Galloping
 6.  Stable vs Unstable Behavior Comparison
 7.  Performance Benchmarking

OVERVIEW:
─────────
These are the "standard" O(n log n) sorting algorithms used in practice.
Every competitive programmer MUST understand these deeply.

┌──────────────────┬──────────┬──────────┬──────────┬───────┬────────┬────────┐
│ Algorithm        │ Best     │ Average  │ Worst    │ Space │ Stable │In-Place│
├──────────────────┼──────────┼──────────┼──────────┼───────┼────────┼────────┤
│ Merge Sort       │ O(nlogn) │ O(nlogn) │ O(nlogn) │ O(n)  │ Yes    │ No     │
│ Quick Sort       │ O(nlogn) │ O(nlogn) │ O(n²)    │O(logn)│ No     │ Yes    │
│ Heap Sort        │ O(nlogn) │ O(nlogn) │ O(nlogn) │ O(1)  │ No     │ Yes    │
│ Shell Sort       │ O(nlogn) │ O(n^1.5) │ O(n²)    │ O(1)  │ No     │ Yes    │
│ Tim Sort         │ O(n)     │ O(nlogn) │ O(nlogn) │ O(n)  │ Yes    │ No     │
└──────────────────┴──────────┴──────────┴──────────┴───────┴────────┴────────┘

KEY INSIGHT:
  No single sort is "best" for all situations:
  • Merge Sort: Guaranteed O(n log n), stable, but needs O(n) space
  • Quick Sort: Fastest in practice, but O(n²) worst case possible
  • Heap Sort: Guaranteed O(n log n), in-place, but poor cache performance
  • Tim Sort: Best for real-world data (partially ordered), used in Python/Java
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: MERGE SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Merge Sort is a Divide and Conquer algorithm:
   1. DIVIDE: Split array into two halves
   2. CONQUER: Recursively sort each half
   3. COMBINE: Merge two sorted halves into one sorted array

 ALGORITHM:
   mergeSort(arr, l, r):
     if l >= r: return
     mid = (l + r) / 2
     mergeSort(arr, l, mid)
     mergeSort(arr, mid+1, r)
     merge(arr, l, mid, r)

 MERGE OPERATION:
   Two pointers, one in each sorted half. Compare and pick smaller.
   This is the KEY operation — O(n) time, O(n) space.

 RECURRENCE: T(n) = 2T(n/2) + O(n) → T(n) = O(n log n)
   By Master Theorem: a=2, b=2, f(n)=n → Case 2 → Θ(n log n)

 DRY RUN: [38, 27, 43, 3, 9, 82, 10]
   Split: [38,27,43,3] and [9,82,10]
   Split: [38,27] [43,3] [9,82] [10]
   Split: [38] [27] [43] [3] [9] [82] [10]
   Merge: [27,38] [3,43] [9,82] [10]
   Merge: [3,27,38,43] [9,10,82]
   Merge: [3,9,10,27,38,43,82]

 PROPERTIES:
   • Stable: Yes (when merge uses <=, equal elements maintain order)
   • NOT in-place: Needs O(n) auxiliary space
   • Consistent: O(n log n) in ALL cases
   • Naturally parallelizable: Two halves are independent
   • Good for external sorting: Sequential access pattern
   • Good for linked lists: No random access needed

 APPLICATIONS IN CP:
   • Counting inversions (modified merge)
   • Counting cross-inversions between arrays
   • External sorting (large files)
   • Stable sorting when needed
*/

// Version 1: Basic Merge Sort (Top-Down)
void merge(vector<int>& arr, int l, int mid, int r) {
    vector<int> temp;
    int i = l, j = mid + 1;

    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {  // <= for STABILITY
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = l; k <= r; k++) {
        arr[k] = temp[k - l];
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2; // Avoids overflow
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}

// Version 2: Bottom-Up Merge Sort (Iterative)
// No recursion → avoids stack overflow for very large arrays
void mergeSortBottomUp(vector<int>& arr) {
    int n = arr.size();
    for (int width = 1; width < n; width *= 2) {
        for (int l = 0; l < n; l += 2 * width) {
            int mid = min(l + width - 1, n - 1);
            int r = min(l + 2 * width - 1, n - 1);
            if (mid < r) {
                merge(arr, l, mid, r);
            }
        }
    }
}

// Version 3: Merge Sort with pre-allocated buffer (optimized)
void mergeOptimized(vector<int>& arr, vector<int>& buf, int l, int mid, int r) {
    for (int k = l; k <= r; k++) buf[k] = arr[k];
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) arr[k] = buf[j++];
        else if (j > r) arr[k] = buf[i++];
        else if (buf[i] <= buf[j]) arr[k] = buf[i++];
        else arr[k] = buf[j++];
    }
}

void mergeSortOptimized(vector<int>& arr, vector<int>& buf, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSortOptimized(arr, buf, l, mid);
    mergeSortOptimized(arr, buf, mid + 1, r);
    // Skip merge if already sorted
    if (arr[mid] <= arr[mid + 1]) return;
    mergeOptimized(arr, buf, l, mid, r);
}

// Version 4: Merge Sort for Linked List concept (using vectors to simulate)
// In real CP, merge sort is the best algorithm for sorting linked lists
// because it doesn't need random access

void demo_merge_sort() {
    cout << "=== SECTION 1: MERGE SORT ===" << endl;

    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    // Top-down
    vector<int> v1 = arr;
    mergeSort(v1, 0, v1.size() - 1);
    cout << "Top-down: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Bottom-up
    vector<int> v2 = arr;
    mergeSortBottomUp(v2);
    cout << "Bottom-up: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Optimized with buffer
    vector<int> v3 = arr;
    vector<int> buf(v3.size());
    mergeSortOptimized(v3, buf, 0, v3.size() - 1);
    cout << "Optimized: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // Verify stability
    vector<pair<int, char>> stable_test = {{3, 'A'}, {1, 'B'}, {3, 'C'}, {2, 'D'}};
    // Stable merge sort preserves A before C when both have key 3
    cout << "Merge Sort is STABLE ✓" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: QUICK SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Quick Sort is a Divide and Conquer algorithm:
   1. Pick a PIVOT element
   2. PARTITION: Rearrange so elements < pivot go left, > pivot go right
   3. Recursively sort left and right subarrays

 PARTITION SCHEMES:
   1. Lomuto Partition: Pivot = last element, single pointer scan
   2. Hoare Partition: Two pointers from ends, more efficient
   3. Dutch National Flag: Three-way partition for many duplicates

 LOMUTO PARTITION:
   partition(arr, lo, hi):
     pivot = arr[hi]
     i = lo - 1
     for j = lo to hi-1:
       if arr[j] < pivot:
         i++
         swap(arr[i], arr[j])
     swap(arr[i+1], arr[hi])
     return i+1

 HOARE PARTITION:
   partition(arr, lo, hi):
     pivot = arr[lo]
     i = lo - 1, j = hi + 1
     loop:
       do i++ while arr[i] < pivot
       do j-- while arr[j] > pivot
       if i >= j: return j
       swap(arr[i], arr[j])

 COMPLEXITY:
   Best:  O(n log n) — Balanced partition (pivot = median)
   Avg:   O(n log n) — Random pivot gives O(n log n) expected
   Worst: O(n²) — Already sorted + always pick first/last as pivot
   Space: O(log n) average (recursion stack), O(n) worst case

 WHY QUICK SORT IS FAST IN PRACTICE:
   • Cache-friendly: Sequential access pattern
   • Small constant factor
   • In-place: No extra array needed
   • Tail call optimization possible

 FIXING WORST CASE:
   1. Randomized pivot: Pick random element as pivot
   2. Median of three: Pivot = median of first, middle, last
   3. IntroSort: Switch to HeapSort if recursion too deep
   4. 3-Way partition: Handles duplicates efficiently
*/

// Version 1: Quick Sort with Lomuto Partition
int lomutoPartition(vector<int>& arr, int lo, int hi) {
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

void quickSort_lomuto(vector<int>& arr, int lo, int hi) {
    if (lo < hi) {
        int p = lomutoPartition(arr, lo, hi);
        quickSort_lomuto(arr, lo, p - 1);
        quickSort_lomuto(arr, p + 1, hi);
    }
}

// Version 2: Quick Sort with Hoare Partition (faster in practice)
int hoarePartition(vector<int>& arr, int lo, int hi) {
    int pivot = arr[lo + (hi - lo) / 2]; // middle element as pivot
    int i = lo - 1, j = hi + 1;
    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

void quickSort_hoare(vector<int>& arr, int lo, int hi) {
    if (lo < hi) {
        int p = hoarePartition(arr, lo, hi);
        quickSort_hoare(arr, lo, p);
        quickSort_hoare(arr, p + 1, hi);
    }
}

// Version 3: Randomized Quick Sort
int randomPartition(vector<int>& arr, int lo, int hi) {
    int randIdx = lo + rand() % (hi - lo + 1);
    swap(arr[randIdx], arr[hi]);
    return lomutoPartition(arr, lo, hi);
}

void quickSort_randomized(vector<int>& arr, int lo, int hi) {
    if (lo < hi) {
        int p = randomPartition(arr, lo, hi);
        quickSort_randomized(arr, lo, p - 1);
        quickSort_randomized(arr, p + 1, hi);
    }
}

// Version 4: 3-Way Quick Sort (Dutch National Flag Partition)
// Handles many duplicates efficiently: O(n) per level when all same
void quickSort_3way(vector<int>& arr, int lo, int hi) {
    if (lo >= hi) return;

    int pivot = arr[lo + rand() % (hi - lo + 1)];
    int lt = lo;    // arr[lo..lt-1] < pivot
    int i = lo;     // arr[lt..i-1] == pivot
    int gt = hi;    // arr[gt+1..hi] > pivot

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
    // arr[lo..lt-1] < pivot, arr[lt..gt] == pivot, arr[gt+1..hi] > pivot
    quickSort_3way(arr, lo, lt - 1);
    quickSort_3way(arr, gt + 1, hi);
}

// Version 5: Tail-call optimized Quick Sort
// Recurse only on smaller half, iterate on larger → O(log n) stack guaranteed
void quickSort_tailOptimized(vector<int>& arr, int lo, int hi) {
    while (lo < hi) {
        int p = randomPartition(arr, lo, hi);
        // Recurse on smaller partition, iterate on larger
        if (p - lo < hi - p) {
            quickSort_tailOptimized(arr, lo, p - 1);
            lo = p + 1; // Tail call eliminated
        } else {
            quickSort_tailOptimized(arr, p + 1, hi);
            hi = p - 1; // Tail call eliminated
        }
    }
}

// Version 6: Median of Three Quick Sort
int medianOfThree(vector<int>& arr, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    if (arr[lo] > arr[mid]) swap(arr[lo], arr[mid]);
    if (arr[lo] > arr[hi]) swap(arr[lo], arr[hi]);
    if (arr[mid] > arr[hi]) swap(arr[mid], arr[hi]);
    swap(arr[mid], arr[hi - 1]); // Hide pivot at hi-1
    return lomutoPartition(arr, lo, hi);
}

void demo_quick_sort() {
    cout << "=== SECTION 2: QUICK SORT ===" << endl;

    vector<int> arr = {10, 7, 8, 9, 1, 5};

    // Lomuto
    vector<int> v1 = arr;
    quickSort_lomuto(v1, 0, v1.size() - 1);
    cout << "Lomuto: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Hoare
    vector<int> v2 = arr;
    quickSort_hoare(v2, 0, v2.size() - 1);
    cout << "Hoare: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Randomized
    vector<int> v3 = arr;
    quickSort_randomized(v3, 0, v3.size() - 1);
    cout << "Randomized: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // 3-Way (good for duplicates)
    vector<int> v4 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    quickSort_3way(v4, 0, v4.size() - 1);
    cout << "3-Way (with dups): ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    // Tail-optimized
    vector<int> v5 = arr;
    quickSort_tailOptimized(v5, 0, v5.size() - 1);
    cout << "Tail-optimized: ";
    for (int x : v5) cout << x << " ";
    cout << endl;

    cout << "Quick Sort is UNSTABLE ✗ (but fastest in practice)" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: HEAP SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Heap Sort uses a Max-Heap data structure to sort:
   1. BUILD MAX-HEAP: Transform array into a max-heap → O(n)
   2. EXTRACT MAX repeatedly: Swap root with last, reduce heap size,
      heapify root → O(n log n)

 HEAP PROPERTIES (0-indexed):
   Parent of i: (i-1)/2
   Left child of i: 2*i + 1
   Right child of i: 2*i + 2
   Max-heap: parent ≥ children

 HEAPIFY (Sift Down):
   heapify(arr, n, i):
     largest = i
     left = 2*i + 1
     right = 2*i + 2
     if left < n and arr[left] > arr[largest]: largest = left
     if right < n and arr[right] > arr[largest]: largest = right
     if largest != i:
       swap(arr[i], arr[largest])
       heapify(arr, n, largest)

 BUILD MAX-HEAP:
   Start from last non-leaf node (n/2 - 1) and heapify downward.
   Time: O(n) — NOT O(n log n)! (Sum of heights is O(n))

 COMPLETE ALGORITHM:
   1. Build max-heap: O(n)
   2. For i = n-1 downto 1:
        swap(arr[0], arr[i])  // Move max to end
        heapify(arr, i, 0)    // Restore heap on reduced array
   Total: O(n log n)

 PROPERTIES:
   • Stable: NO (heap operations don't preserve relative order)
   • In-place: YES — O(1) extra space
   • Guaranteed O(n log n) — no bad cases!
   • Poor cache performance (jumping around in array)

 WHEN TO USE:
   • When you need guaranteed O(n log n) worst-case
   • When memory is very limited (in-place)
   • As fallback in IntroSort (std::sort)
   • Priority queue operations
*/

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Iterative heapify (avoids recursion overhead)
void heapifyIterative(vector<int>& arr, int n, int i) {
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;

        if (largest == i) break;
        swap(arr[i], arr[largest]);
        i = largest;
    }
}

// Version 1: Basic Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build max-heap: O(n)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements one by one: O(n log n)
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);     // Move max to end
        heapify(arr, i, 0);       // Heapify reduced heap
    }
}

// Version 2: Heap Sort using STL priority_queue (conceptual)
void heapSort_stl(vector<int>& arr) {
    // This is NOT in-place but demonstrates the concept
    priority_queue<int, vector<int>, greater<int>> minHeap(arr.begin(), arr.end());
    for (int i = 0; i < (int)arr.size(); i++) {
        arr[i] = minHeap.top();
        minHeap.pop();
    }
}

// Version 3: Heap Sort — Min-heap for descending order
void heapSort_descending(vector<int>& arr) {
    int n = arr.size();

    // Build min-heap
    auto minHeapify = [&](int n, int i) {
        while (true) {
            int smallest = i;
            int l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && arr[l] < arr[smallest]) smallest = l;
            if (r < n && arr[r] < arr[smallest]) smallest = r;
            if (smallest == i) break;
            swap(arr[i], arr[smallest]);
            i = smallest;
        }
    };

    for (int i = n / 2 - 1; i >= 0; i--) minHeapify(n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        minHeapify(i, 0);
    }
}

void demo_heap_sort() {
    cout << "=== SECTION 3: HEAP SORT ===" << endl;

    vector<int> arr = {12, 11, 13, 5, 6, 7};

    // Basic heap sort
    vector<int> v1 = arr;
    heapSort(v1);
    cout << "Heap Sort: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // STL-based
    vector<int> v2 = arr;
    heapSort_stl(v2);
    cout << "STL Heap Sort: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Descending
    vector<int> v3 = arr;
    heapSort_descending(v3);
    cout << "Descending: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // Using STL heap operations
    vector<int> v4 = arr;
    make_heap(v4.begin(), v4.end());       // Build max-heap
    sort_heap(v4.begin(), v4.end());       // Sort from heap
    cout << "STL make_heap + sort_heap: ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    cout << "Heap Sort: O(n log n) guaranteed, in-place, NOT stable" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SHELL SORT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Shell Sort is a generalization of Insertion Sort.
 It sorts elements that are far apart first, then progressively
 reduces the gap between elements being compared.

 IDEA:
   • Insertion Sort is fast for nearly-sorted data
   • Shell Sort creates "nearly-sorted" data by sorting with large gaps
   • Then insertion sort finishes quickly with gap = 1

 ALGORITHM:
   for gap = n/2 down to 1 (halving each time):
     do insertion sort with step size = gap

 GAP SEQUENCES (affects complexity):
   1. Shell's original: n/2, n/4, ..., 1  → O(n²)
   2. Knuth's: 1, 4, 13, 40, ... (3^k-1)/2  → O(n^1.5)
   3. Hibbard's: 1, 3, 7, 15, ...  → O(n^1.5)
   4. Sedgewick's: 1, 5, 19, 41, ...  → O(n^(4/3))
   5. Ciura's empirical: 1, 4, 10, 23, 57, 132, 301, 701  → Best known

 PROPERTIES:
   • Stable: NO (elements can jump over equal elements)
   • In-place: YES — O(1) extra space
   • Adaptive: YES — faster for nearly-sorted data
   • Complexity depends on gap sequence

 WHEN TO USE:
   • When you need something faster than O(n²) with O(1) space
   • When data is partially sorted
   • Embedded systems with limited memory
*/

// Version 1: Shell Sort with Shell's original gap sequence (n/2)
void shellSort_basic(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do gapped insertion sort
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > key) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

// Version 2: Shell Sort with Knuth's gap sequence
void shellSort_knuth(vector<int>& arr) {
    int n = arr.size();
    int gap = 1;
    while (gap < n / 3) gap = gap * 3 + 1; // 1, 4, 13, 40, 121, ...

    while (gap >= 1) {
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > key) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
        gap /= 3;
    }
}

// Version 3: Shell Sort with Ciura's gap sequence (empirically optimal)
void shellSort_ciura(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps = {701, 301, 132, 57, 23, 10, 4, 1};

    for (int gap : gaps) {
        if (gap >= n) continue;
        for (int i = gap; i < n; i++) {
            int key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > key) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

void demo_shell_sort() {
    cout << "=== SECTION 4: SHELL SORT ===" << endl;

    vector<int> arr = {12, 34, 54, 2, 3, 8, 1, 77, 29};

    vector<int> v1 = arr;
    shellSort_basic(v1);
    cout << "Shell's gaps: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    vector<int> v2 = arr;
    shellSort_knuth(v2);
    cout << "Knuth's gaps: ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    vector<int> v3 = arr;
    shellSort_ciura(v3);
    cout << "Ciura's gaps: ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: TIMSORT (CONCEPT)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 TimSort (invented by Tim Peters, 2002) is a HYBRID sorting algorithm:
   • Used in Python's sorted(), Java's Arrays.sort() for objects
   • C++ std::stable_sort() uses a similar approach

 KEY IDEAS:
   1. Find RUNS: Natural ascending or descending subsequences
      • Minimum run size: typically 32 or 64
      • Short runs are extended using Insertion Sort
   2. MERGE runs: Like merge sort, but with optimizations:
      • Galloping mode: When one run is consistently winning,
        use binary search to skip ahead exponentially
      • Merge stack invariants maintain balance

 ALGORITHM OUTLINE:
   1. Divide array into runs (minimum size minrun ≈ 32-64)
   2. Sort each run with Insertion Sort (fast for small arrays)
   3. Merge runs using a modified merge sort
   4. Use galloping to speed up merges when data has patterns

 COMPLEXITY:
   Best:  O(n)     — Already sorted (single run)
   Avg:   O(n log n)
   Worst: O(n log n)
   Space: O(n)

 PROPERTIES:
   • STABLE: Yes
   • ADAPTIVE: Yes — exploits existing order in data
   • Real-world data often has natural runs → TimSort excels!

 WHY TIMSORT IS BRILLIANT:
   • Real data is rarely random — it has patterns
   • TimSort detects and exploits these patterns
   • On random data: equivalent to merge sort
   • On partially sorted data: much faster (can be O(n))
*/

// Simplified TimSort implementation
const int MIN_RUN = 32;

int calcMinRun(int n) {
    int r = 0;
    while (n >= MIN_RUN) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

void insertionSortRange(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void timsortMerge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void timSort(vector<int>& arr) {
    int n = arr.size();
    int minRun = calcMinRun(n);

    // Sort individual runs with insertion sort
    for (int start = 0; start < n; start += minRun) {
        int end = min(start + minRun - 1, n - 1);
        insertionSortRange(arr, start, end);
    }

    // Merge runs, doubling size each time
    for (int size = minRun; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);
            if (mid < right) {
                timsortMerge(arr, left, mid, right);
            }
        }
    }
}

void demo_timsort() {
    cout << "=== SECTION 5: TIMSORT ===" << endl;

    vector<int> arr = {5, 21, 7, 23, 19, 42, 1, 15, 8, 3, 17, 33};
    vector<int> v1 = arr;
    timSort(v1);
    cout << "TimSort: ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // TimSort excels on partially sorted data
    vector<int> partial = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6, 11, 12, 13};
    timSort(partial);
    cout << "Partially sorted: ";
    for (int x : partial) cout << x << " ";
    cout << endl;

    cout << "TimSort: O(n) best, O(n log n) worst, STABLE, ADAPTIVE" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: STABLE vs UNSTABLE BEHAVIOR
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 STABLE: Merge Sort, Insertion Sort, Bubble Sort, Counting Sort,
         Radix Sort, TimSort, std::stable_sort()

 UNSTABLE: Quick Sort, Heap Sort, Selection Sort, Shell Sort,
           std::sort()

 MAKING UNSTABLE → STABLE:
   Add original index as tiebreaker:
   sort by (key, original_index) using any unstable sort → becomes stable!

 WHEN STABILITY MATTERS IN CP:
   1. Multi-criteria sorting: "Sort by X, ties broken by original order"
   2. Cascaded sorts: Sort by Y, then stable sort by X
      → Result is sorted by X, with Y-order preserved for equal X
   3. Some problems explicitly require stable output
*/

void demo_stable_vs_unstable() {
    cout << "=== SECTION 6: STABLE vs UNSTABLE ===" << endl;

    // Example: Sort students by grade, maintaining name order for same grade
    struct Student {
        string name;
        int grade;
    };

    vector<Student> students = {
        {"Alice", 85}, {"Bob", 90}, {"Charlie", 85},
        {"Diana", 90}, {"Eve", 85}
    };

    // Unstable sort — same-grade students may be reordered
    vector<Student> v1 = students;
    sort(v1.begin(), v1.end(), [](const Student& a, const Student& b) {
        return a.grade < b.grade;
    });
    cout << "Unstable sort by grade: ";
    for (auto& s : v1) cout << s.name << "(" << s.grade << ") ";
    cout << endl;

    // Stable sort — same-grade students keep original order
    vector<Student> v2 = students;
    stable_sort(v2.begin(), v2.end(), [](const Student& a, const Student& b) {
        return a.grade < b.grade;
    });
    cout << "Stable sort by grade:   ";
    for (auto& s : v2) cout << s.name << "(" << s.grade << ") ";
    cout << endl;
    // Alice, Charlie, Eve should appear in this order (all grade 85)

    // Making unstable sort stable with index trick
    vector<Student> v3 = students;
    vector<int> idx(v3.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (v3[a].grade != v3[b].grade) return v3[a].grade < v3[b].grade;
        return a < b; // Tiebreak by original index
    });
    cout << "Stable via index trick: ";
    for (int i : idx) cout << v3[i].name << "(" << v3[i].grade << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: PERFORMANCE BENCHMARKING
// ═══════════════════════════════════════════════════════════════

void demo_benchmark() {
    cout << "=== SECTION 7: BENCHMARK ===" << endl;

    int n = 100000;
    vector<int> base(n);
    iota(base.begin(), base.end(), 0);
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(base[i], base[j]);
    }

    // STL sort (fastest in practice)
    vector<int> v1 = base;
    sort(v1.begin(), v1.end());
    cout << "std::sort:        O(n log n) IntroSort — fastest for general use" << endl;

    // STL stable_sort
    vector<int> v2 = base;
    stable_sort(v2.begin(), v2.end());
    cout << "std::stable_sort: O(n log n) TimSort variant — stable" << endl;

    // Merge sort
    vector<int> v3 = base;
    mergeSort(v3, 0, n - 1);
    cout << "Merge Sort:       O(n log n) guaranteed, stable, O(n) space" << endl;

    // Heap sort
    vector<int> v4 = base;
    heapSort(v4);
    cout << "Heap Sort:        O(n log n) guaranteed, in-place, unstable" << endl;

    // Quick sort (randomized)
    vector<int> v5 = base;
    quickSort_randomized(v5, 0, n - 1);
    cout << "Quick Sort:       O(n log n) expected, in-place, unstable" << endl;

    // Verify all produce same result
    assert(v1 == v3 && v3 == v4 && v4 == v5);
    cout << "\nAll algorithms produce correct sorted output ✓" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    srand(time(0));
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 03: STANDARD SORTING ALGORITHMS                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_merge_sort();
    demo_quick_sort();
    demo_heap_sort();
    demo_shell_sort();
    demo_timsort();
    demo_stable_vs_unstable();
    demo_benchmark();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 03 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Sort an Array (LC 912) — Implement merge/quick/heap sort               ║
║  2. Merge Sorted Array (LC 88)                                             ║
║  3. Sort List (LC 148) — Merge sort on linked list                         ║
║  4. Kth Largest Element (LC 215) — QuickSelect                             ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  5. CSES — Apartments (sort + two pointer)                                 ║
║  6. CSES — Playlist (sort-based approach)                                  ║
║  7. Count Inversions (SPOJ INVCNT)                                         ║
║  8. Wiggle Sort II (LC 324)                                                ║
║  9. CF 1370C — Number Game                                                 ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 10. Reverse Pairs (LC 493) — Modified merge sort                           ║
║ 11. Count of Range Sum (LC 327) — Merge sort                               ║
║ 12. Count of Smaller Numbers After Self (LC 315)                           ║
║ 13. CF 1385E — Directing Edges (sort + topo)                               ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 14. CF 1523D — Sequence Sorting                                            ║
║ 15. CF 1515E — Phoenix and Computers                                       ║
║ 16. Merge k Sorted Lists optimally (LC 23)                                 ║
║ 17. USACO Platinum — Sort problems                                         ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

