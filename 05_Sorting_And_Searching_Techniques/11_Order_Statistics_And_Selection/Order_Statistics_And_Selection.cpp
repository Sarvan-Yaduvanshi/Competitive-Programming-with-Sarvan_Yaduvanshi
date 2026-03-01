/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 11 — ORDER STATISTICS & SELECTION                        ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Kth Smallest Element
 2.  Kth Largest Element
 3.  QuickSelect Algorithm
 4.  Median of Two Sorted Arrays
 5.  Heap-Based Selection
 6.  Value Space Binary Search
 7.  Order Statistic Tree Concept (PBDS)

OVERVIEW:
─────────
Order Statistics deal with finding elements by their RANK in a sorted sequence.
The kth order statistic = kth smallest element.

METHODS COMPARISON:
┌──────────────────────┬────────────┬──────────────────────────────┐
│ Method               │ Time       │ Notes                        │
├──────────────────────┼────────────┼──────────────────────────────┤
│ Sort + index         │ O(n log n) │ Simplest, sorts entire array │
│ QuickSelect          │ O(n) avg   │ O(n²) worst, in-place        │
│ nth_element (STL)    │ O(n) avg   │ Wrapper around QuickSelect   │
│ Median of Medians    │ O(n) worst │ Deterministic, complex       │
│ Min-heap of size k   │ O(n log k) │ For kth largest              │
│ Max-heap of size k   │ O(n log k) │ For kth smallest             │
│ Value space BS       │ O(n log V) │ For matrix/special problems  │
│ Order Statistic Tree │ O(log n)   │ Dynamic insertion + kth query│
└──────────────────────┴────────────┴──────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <numeric>
#include <climits>
#include <cstdlib>

// For Policy-Based Data Structure (PBDS)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// Order Statistic Tree type alias
typedef tree<pair<int,int>, null_type, less<pair<int,int>>,
             rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: KTH SMALLEST ELEMENT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Find the kth smallest element in an unsorted array.

 APPROACHES:
   1. Sort: O(n log n)
   2. nth_element: O(n) average
   3. QuickSelect: O(n) average, O(n²) worst
   4. Max-heap of size k: O(n log k) — keep k smallest in heap
   5. Counting sort: O(n + range) — for small value range

 For CP: Use nth_element or sort (simple and fast).
*/

// Method 1: Sort
int kthSmallest_sort(vector<int> arr, int k) {
    sort(arr.begin(), arr.end());
    return arr[k - 1]; // 1-indexed k
}

// Method 2: nth_element (STL QuickSelect)
int kthSmallest_nth(vector<int> arr, int k) {
    nth_element(arr.begin(), arr.begin() + k - 1, arr.end());
    return arr[k - 1];
}

// Method 3: Max-heap of size k
int kthSmallest_heap(vector<int>& arr, int k) {
    priority_queue<int> maxHeap; // Max-heap
    for (int x : arr) {
        maxHeap.push(x);
        if ((int)maxHeap.size() > k) maxHeap.pop(); // Remove largest
    }
    return maxHeap.top(); // kth smallest = max of k smallest
}

void demo_kth_smallest() {
    cout << "=== SECTION 1: KTH SMALLEST ===" << endl;

    vector<int> arr = {7, 10, 4, 3, 20, 15};
    int k = 3;

    cout << k << "rd smallest (sort): " << kthSmallest_sort(arr, k) << endl;
    cout << k << "rd smallest (nth): " << kthSmallest_nth(arr, k) << endl;
    cout << k << "rd smallest (heap): " << kthSmallest_heap(arr, k) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: KTH LARGEST ELEMENT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 kth largest = (n - k + 1)th smallest

 APPROACHES:
   Same as kth smallest, just adjust index or use min-heap.
   Min-heap of size k: O(n log k) — keep k largest in heap

 LC 215: Kth Largest Element in an Array
*/

int kthLargest_sort(vector<int> arr, int k) {
    sort(arr.begin(), arr.end(), greater<int>());
    return arr[k - 1];
}

int kthLargest_nth(vector<int> arr, int k) {
    int n = arr.size();
    nth_element(arr.begin(), arr.begin() + k - 1, arr.end(), greater<int>());
    return arr[k - 1];
}

int kthLargest_heap(vector<int>& arr, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : arr) {
        minHeap.push(x);
        if ((int)minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

void demo_kth_largest() {
    cout << "=== SECTION 2: KTH LARGEST ===" << endl;

    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;

    cout << k << "nd largest (sort): " << kthLargest_sort(arr, k) << endl;
    cout << k << "nd largest (nth): " << kthLargest_nth(arr, k) << endl;
    cout << k << "nd largest (heap): " << kthLargest_heap(arr, k) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: QUICKSELECT ALGORITHM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 QuickSelect is a selection algorithm based on QuickSort's partition.
 It finds the kth smallest element in O(n) average time.

 ALGORITHM:
   1. Pick a pivot and partition
   2. If pivot position == k: return pivot
   3. If pivot position > k: recurse on LEFT half
   4. If pivot position < k: recurse on RIGHT half

 Unlike QuickSort which recurses on BOTH halves, QuickSelect
 only recurses on ONE half → O(n) average.

 ANALYSIS:
   Average: O(n) — T(n) = T(n/2) + O(n) → O(n)
   Worst: O(n²) — bad pivot choice (like QS)
   FIX: Randomized pivot → O(n) expected

 MEDIAN OF MEDIANS:
   Deterministic O(n) worst case algorithm:
   1. Divide into groups of 5
   2. Find median of each group
   3. Recursively find median of medians
   4. Use this as pivot → guaranteed good partition
   Rarely used in CP (constant factor too large).
*/

// Randomized QuickSelect
int quickSelect(vector<int>& arr, int lo, int hi, int k) {
    if (lo == hi) return arr[lo];

    // Random pivot
    int randIdx = lo + rand() % (hi - lo + 1);
    swap(arr[randIdx], arr[hi]);

    // Lomuto partition
    int pivot = arr[hi];
    int i = lo;
    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[hi]);

    // i is the position of pivot
    if (i == k) return arr[i];
    if (i > k) return quickSelect(arr, lo, i - 1, k);
    return quickSelect(arr, i + 1, hi, k);
}

int kthSmallest_quickselect(vector<int> arr, int k) {
    return quickSelect(arr, 0, arr.size() - 1, k - 1); // 0-indexed
}

// Iterative QuickSelect (avoids stack overflow)
int quickSelect_iterative(vector<int>& arr, int k) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        int randIdx = lo + rand() % (hi - lo + 1);
        swap(arr[randIdx], arr[hi]);
        int pivot = arr[hi], i = lo;
        for (int j = lo; j < hi; j++)
            if (arr[j] <= pivot) swap(arr[i++], arr[j]);
        swap(arr[i], arr[hi]);
        if (i == k) return arr[i];
        if (i > k) hi = i - 1;
        else lo = i + 1;
    }
    return arr[lo];
}

void demo_quickselect() {
    cout << "=== SECTION 3: QUICKSELECT ===" << endl;

    vector<int> arr = {12, 3, 5, 7, 4, 19, 26};
    int k = 3;
    cout << k << "rd smallest (quickselect): " << kthSmallest_quickselect(arr, k) << endl; // 5

    vector<int> arr2 = arr;
    cout << k << "rd smallest (iterative): " << quickSelect_iterative(arr2, k - 1) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: MEDIAN OF TWO SORTED ARRAYS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Given two sorted arrays of sizes m and n, find the median of their
 combined sorted array in O(log(min(m,n))) time.

 LC 4: Hard problem, but elegant binary search solution.

 KEY IDEA:
   The median splits the combined array into two equal halves.
   Binary search on the partition point of the smaller array.

   Let arrays be A[0..m-1] and B[0..n-1].
   Total elements = m + n.
   Left partition should have (m + n + 1) / 2 elements.

   Binary search on i (partition of A):
     j = half - i (partition of B)
     Check: A[i-1] ≤ B[j] and B[j-1] ≤ A[i]
     If so: median found.

 TIME: O(log(min(m, n)))
 SPACE: O(1)
*/

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Ensure nums1 is the smaller array
    if (nums1.size() > nums2.size()) swap(nums1, nums2);

    int m = nums1.size(), n = nums2.size();
    int lo = 0, hi = m;
    int half = (m + n + 1) / 2;

    while (lo <= hi) {
        int i = lo + (hi - lo) / 2; // Partition of nums1
        int j = half - i;           // Partition of nums2

        int left1 = (i > 0) ? nums1[i - 1] : INT_MIN;
        int right1 = (i < m) ? nums1[i] : INT_MAX;
        int left2 = (j > 0) ? nums2[j - 1] : INT_MIN;
        int right2 = (j < n) ? nums2[j] : INT_MAX;

        if (left1 <= right2 && left2 <= right1) {
            // Found correct partition
            if ((m + n) % 2 == 1) {
                return max(left1, left2); // Odd total
            } else {
                return (max(left1, left2) + min(right1, right2)) / 2.0; // Even total
            }
        } else if (left1 > right2) {
            hi = i - 1; // Too far right in nums1
        } else {
            lo = i + 1; // Too far left in nums1
        }
    }
    return -1; // Should never reach
}

void demo_median_two_arrays() {
    cout << "=== SECTION 4: MEDIAN OF TWO SORTED ARRAYS ===" << endl;

    vector<int> a = {1, 3};
    vector<int> b = {2};
    cout << "Median of [1,3] and [2]: " << findMedianSortedArrays(a, b) << endl; // 2.0

    vector<int> c = {1, 2};
    vector<int> d = {3, 4};
    cout << "Median of [1,2] and [3,4]: " << findMedianSortedArrays(c, d) << endl; // 2.5

    vector<int> e = {1, 5, 8, 10, 18, 20};
    vector<int> f = {2, 3, 6, 7};
    cout << "Median of [1,5,8,10,18,20] and [2,3,6,7]: "
         << findMedianSortedArrays(e, f) << endl; // 6.5

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: HEAP-BASED SELECTION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Heaps are excellent for order statistics in streaming/online settings.

 PATTERNS:
   1. Kth largest → Min-heap of size k → top is answer
   2. Kth smallest → Max-heap of size k → top is answer
   3. Running median → Two heaps (max-heap + min-heap)
   4. Top-K elements → Min-heap of size K

 RUNNING MEDIAN (LC 295):
   Maintain two heaps:
   • maxHeap: lower half (contains smaller elements)
   • minHeap: upper half (contains larger elements)
   • Balance: |maxHeap| - |minHeap| ∈ {0, 1}
   • Median = maxHeap.top() or avg(maxHeap.top(), minHeap.top())
*/

class MedianFinder {
    priority_queue<int> maxHeap;                              // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap;   // Upper half

public:
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        // Balance: maxHeap should have equal or one more element
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size())
            return maxHeap.top();
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

// Top K Frequent Elements (LC 347)
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    // Min-heap of size k by frequency
    auto cmp = [](pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);

    for (auto& [val, f] : freq) {
        minHeap.push({val, f});
        if ((int)minHeap.size() > k) minHeap.pop();
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }
    return result;
}

void demo_heap_selection() {
    cout << "=== SECTION 5: HEAP-BASED SELECTION ===" << endl;

    // Running Median
    MedianFinder mf;
    mf.addNum(1);
    cout << "After 1: median = " << mf.findMedian() << endl; // 1
    mf.addNum(2);
    cout << "After 2: median = " << mf.findMedian() << endl; // 1.5
    mf.addNum(3);
    cout << "After 3: median = " << mf.findMedian() << endl; // 2
    mf.addNum(4);
    cout << "After 4: median = " << mf.findMedian() << endl; // 2.5

    // Top K Frequent
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    auto topK = topKFrequent(nums, 2);
    cout << "Top 2 frequent: ";
    for (int x : topK) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: VALUE SPACE BINARY SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When the array is too large to sort, or elements come from a special
 structure (matrix, multiple arrays), binary search on the VALUE space.

 PATTERN:
   lo = min possible value
   hi = max possible value
   while lo < hi:
     mid = (lo + hi) / 2
     if countLessOrEqual(mid) < k: lo = mid + 1
     else: hi = mid

 This finds the kth smallest value without explicitly sorting.

 APPLICATIONS:
   • Kth smallest in sorted matrix (LC 378)
   • Kth smallest pair distance (LC 719)
   • Kth smallest number in multiplication table (LC 668)
*/

// Kth Smallest Pair Distance (LC 719)
int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int n = nums.size();

    int lo = 0, hi = nums.back() - nums.front();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        // Count pairs with distance ≤ mid
        int count = 0;
        int left = 0;
        for (int right = 0; right < n; right++) {
            while (nums[right] - nums[left] > mid) left++;
            count += (right - left);
        }

        if (count < k) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

// Kth Smallest in Multiplication Table (LC 668)
int findKthNumber(int m, int n, int k) {
    int lo = 1, hi = m * n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        int count = 0;
        for (int i = 1; i <= m; i++) {
            count += min(mid / i, n);
        }

        if (count < k) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

void demo_value_space_bs() {
    cout << "=== SECTION 6: VALUE SPACE BS ===" << endl;

    // Kth Smallest Pair Distance
    vector<int> nums = {1, 3, 1};
    cout << "1st smallest pair distance: " << smallestDistancePair(nums, 1) << endl; // 0
    cout << "2nd smallest pair distance: " << smallestDistancePair(nums, 2) << endl; // 2

    // Kth in Multiplication Table
    cout << "Kth in 3x3 table (k=5): " << findKthNumber(3, 3, 5) << endl; // 3
    // Table: 1 2 3 / 2 4 6 / 3 6 9. Sorted: 1,2,2,3,3,4,6,6,9 → k=5 → 3

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: ORDER STATISTIC TREE (PBDS)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 C++ Policy-Based Data Structure (PBDS) provides an Order Statistic Tree:
   - Balanced BST (Red-Black tree)
   - Supports all set operations + ORDER STATISTICS in O(log n)

 KEY OPERATIONS:
   find_by_order(k): Returns iterator to kth element (0-indexed)
   order_of_key(x): Returns number of elements strictly less than x

 INCLUDE:
   #include <ext/pb_ds/assoc_container.hpp>
   #include <ext/pb_ds/tree_policy.hpp>

 DECLARATION:
   typedef tree<int, null_type, less<int>,
                rb_tree_tag, tree_order_statistics_node_update> ordered_set;

 HANDLING DUPLICATES:
   Use pair<int, int> where second is unique ID (e.g., insertion order)

 APPLICATIONS:
   • Dynamic kth smallest/largest
   • Count inversions online
   • Range rank queries
   • Sliding window kth element
*/

void demo_pbds() {
    cout << "=== SECTION 7: ORDER STATISTIC TREE (PBDS) ===" << endl;

    ordered_set os;
    int id = 0;

    // Insert elements (using pair to handle duplicates)
    for (int x : {5, 3, 8, 1, 4, 7, 2, 6}) {
        os.insert({x, id++});
    }

    cout << "Elements: ";
    for (auto& [val, _] : os) cout << val << " ";
    cout << endl;

    // find_by_order(k): kth element (0-indexed)
    cout << "0th element: " << os.find_by_order(0)->first << endl; // 1
    cout << "3rd element: " << os.find_by_order(3)->first << endl; // 4
    cout << "7th element: " << os.find_by_order(7)->first << endl; // 8

    // order_of_key(x): count of elements < x
    cout << "Elements < 5: " << os.order_of_key({5, 0}) << endl; // 4 (1,2,3,4)
    cout << "Elements < 3: " << os.order_of_key({3, 0}) << endl; // 2 (1,2)

    // Dynamic kth smallest with insertions and deletions
    os.erase(os.find_by_order(2)); // Remove 3rd element (3)
    cout << "After removing 3rd: ";
    for (auto& [val, _] : os) cout << val << " ";
    cout << endl;

    // Count inversions online
    cout << "\nOnline inversion count:" << endl;
    ordered_set inv_tree;
    int inv_id = 0;
    vector<int> sequence = {5, 3, 4, 1, 2};
    long long inversions = 0;
    for (int x : sequence) {
        // Elements already in tree that are > x
        int greater_count = inv_tree.size() - inv_tree.order_of_key({x + 1, 0});
        inversions += greater_count;
        inv_tree.insert({x, inv_id++});
    }
    cout << "Inversions in [5,3,4,1,2]: " << inversions << endl; // 7

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    srand(42);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 11: ORDER STATISTICS & SELECTION                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_kth_smallest();
    demo_kth_largest();
    demo_quickselect();
    demo_median_two_arrays();
    demo_heap_selection();
    demo_value_space_bs();
    demo_pbds();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 11 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Kth Largest Element (LC 215)                                           ║
║  2. Top K Frequent Elements (LC 347)                                       ║
║  3. Sort Characters By Frequency (LC 451)                                  ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  4. Kth Smallest in Sorted Matrix (LC 378)                                 ║
║  5. Find Median from Data Stream (LC 295)                                  ║
║  6. Kth Largest in a Stream (LC 703)                                       ║
║  7. CSES — Josephus Problem II (PBDS)                                      ║
║  8. Kth Smallest Element in BST (LC 230)                                   ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║  9. Median of Two Sorted Arrays (LC 4)                                     ║
║ 10. Kth Smallest Pair Distance (LC 719)                                    ║
║ 11. Kth Smallest Number in Mult. Table (LC 668)                            ║
║ 12. Sliding Window Median (LC 480)                                         ║
║ 13. CSES — List Removals (PBDS)                                            ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 14. CF 1042D — Petya and Array (PBDS inversions)                           ║
║ 15. Count inversions using PBDS/BIT                                        ║
║ 16. Median of medians algorithm implementation                             ║
║ 17. CF 1515E — Dynamic order statistics                                    ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

