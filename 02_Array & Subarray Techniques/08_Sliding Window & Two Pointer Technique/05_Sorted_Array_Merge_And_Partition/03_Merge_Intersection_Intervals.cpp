/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Merge Sorted Array, Intersection, Interval Intersections,
 *            Sort Array By Parity II — Multi-Pointer on Multiple Arrays
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  LC 88   — Merge Sorted Array (merge from back trick)
 *            https://leetcode.com/problems/merge-sorted-array/
 *
 *  LC 349  — Intersection of Two Arrays (unique values)
 *            https://leetcode.com/problems/intersection-of-two-arrays/
 *
 *  LC 350  — Intersection of Two Arrays II (with duplicates / frequency)
 *            https://leetcode.com/problems/intersection-of-two-arrays-ii/
 *
 *  LC 922  — Sort Array By Parity II (even at even indices, odd at odd)
 *            https://leetcode.com/problems/sort-array-by-parity-ii/
 *
 *  LC 986  — Interval List Intersections (two pointer on intervals)
 *            https://leetcode.com/problems/interval-list-intersections/
 *
 *  GFG     — Merge Without Extra Space
 *            https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays5135/
 *
 *  CORE PATTERNS:
 *  ──────────────
 *  ► MERGE PATTERN: Two pointers, one on each sorted array, compare and pick smaller.
 *  ► INTERSECTION PATTERN: Both sorted → advance the smaller one, collect matches.
 *  ► INTERVAL PATTERN: Compare interval ends → intersection = [max(starts), min(ends)].
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// ============================================================================
// LC 88: Merge Sorted Array — Merge from the BACK (classic trick!)
// ============================================================================
/*
 * nums1 has m elements + n extra zeros. Merge nums2 into nums1 in-place.
 *
 * TRICK: Start filling from the END of nums1 to avoid overwriting.
 * Compare largest remaining from both arrays, place at position k--.
 *
 * Time: O(m + n), Space: O(1)
 */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;      // Last real element in nums1
    int j = n - 1;      // Last element in nums2
    int k = m + n - 1;  // Last position in merged result

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j])
            nums1[k--] = nums1[i--];
        else
            nums1[k--] = nums2[j--];
    }
    // If nums2 has remaining elements (nums1 elements already in place)
    while (j >= 0)
        nums1[k--] = nums2[j--];
}

// ============================================================================
// LC 349: Intersection of Two Arrays — Unique values only
// ============================================================================
/*
 * Two Approaches:
 *   1) Sort both + two pointer → O(N log N + M log M)
 *   2) HashSet → O(N + M)
 *
 * Showing both:
 */

// Approach 1: Sort + Two Pointer
vector<int> intersection_twoPtr(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> result;
    int i = 0, j = 0;

    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] == b[j]) {
            if (result.empty() || result.back() != a[i])
                result.push_back(a[i]);
            i++; j++;
        }
        else if (a[i] < b[j]) i++;
        else j++;
    }
    return result;
}

// Approach 2: HashSet
vector<int> intersection_set(vector<int>& a, vector<int>& b) {
    unordered_set<int> setA(a.begin(), a.end());
    unordered_set<int> res;
    for (int x : b)
        if (setA.count(x)) res.insert(x);
    return vector<int>(res.begin(), res.end());
}

// ============================================================================
// LC 350: Intersection of Two Arrays II — With duplicates (frequency matters)
// ============================================================================
/*
 * Sort both + two pointer. Include duplicates.
 * Time: O(N log N + M log M), Space: O(min(N,M))
 *
 * Follow-up: If one array is much smaller, use hashmap on the smaller.
 * Follow-up: If sorted on disk, two pointer is ideal (no random access needed).
 */
vector<int> intersect(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> result;
    int i = 0, j = 0;

    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] == b[j]) {
            result.push_back(a[i]);
            i++; j++;
        }
        else if (a[i] < b[j]) i++;
        else j++;
    }
    return result;
}

// ============================================================================
// LC 922: Sort Array By Parity II — Even at even index, odd at odd index
// ============================================================================
/*
 * Two pointers: one for even index (0, 2, 4, ...), one for odd index (1, 3, 5, ...).
 * Find misplaced elements and swap them.
 * Time: O(N), Space: O(1)
 */
vector<int> sortArrayByParityII(vector<int>& nums) {
    int n = nums.size();
    int even = 0, odd = 1;

    while (even < n && odd < n) {
        // Find misplaced even index (should be even, but is odd)
        while (even < n && nums[even] % 2 == 0) even += 2;
        // Find misplaced odd index (should be odd, but is even)
        while (odd < n && nums[odd] % 2 == 1) odd += 2;

        if (even < n && odd < n)
            swap(nums[even], nums[odd]);
    }
    return nums;
}

// ============================================================================
// LC 986: Interval List Intersections — Two Pointer on Intervals
// ============================================================================
/*
 * Two sorted lists of DISJOINT intervals. Find all intersections.
 *
 * KEY INSIGHT: Intersection of [a1,a2] and [b1,b2]:
 *   lo = max(a1, b1),  hi = min(a2, b2)
 *   If lo <= hi → valid intersection [lo, hi]
 *
 * After processing, advance the pointer whose interval ENDS first
 * (because that interval can't intersect anything else).
 *
 * Time: O(N + M), Space: O(1) excluding output
 */
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> result;
    int i = 0, j = 0;

    while (i < (int)A.size() && j < (int)B.size()) {
        int lo = max(A[i][0], B[j][0]);
        int hi = min(A[i][1], B[j][1]);

        if (lo <= hi)
            result.push_back({lo, hi});

        // Advance the one that ends first
        if (A[i][1] < B[j][1]) i++;
        else j++;
    }
    return result;
}

// ============================================================================
// GFG: Merge Without Extra Space (Gap / Shell Sort Method)
// ============================================================================
/*
 * Two sorted arrays, merge in-place (no extra space).
 * GAP method: Start with gap = ceil((n+m)/2), compare elements gap apart,
 * swap if out of order. Halve gap each time until gap = 0.
 * Time: O((N+M) * log(N+M)), Space: O(1)
 */
void mergeWithoutExtraSpace(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int gap = (n + m + 1) / 2;

    auto getVal = [&](int idx) -> int& {
        return idx < n ? a[idx] : b[idx - n];
    };

    while (gap > 0) {
        for (int i = 0; i + gap < n + m; i++) {
            if (getVal(i) > getVal(i + gap))
                swap(getVal(i), getVal(i + gap));
        }
        if (gap == 1) break;
        gap = (gap + 1) / 2;
    }
}

int main() {
    // LC 88: Merge Sorted Array
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    merge(nums1, 3, nums2, 3);
    cout << "Merged: ";
    for (int x : nums1) cout << x << " ";
    cout << "\n"; // 1 2 2 3 5 6

    // LC 349: Intersection
    vector<int> a = {1, 2, 2, 1}, b = {2, 2};
    auto res = intersection_twoPtr(a, b);
    cout << "Intersection: ";
    for (int x : res) cout << x << " ";
    cout << "\n"; // 2

    // LC 350: Intersection II
    auto res2 = intersect(a, b);
    cout << "Intersection II: ";
    for (int x : res2) cout << x << " ";
    cout << "\n"; // 2 2

    // LC 986: Interval Intersection
    vector<vector<int>> A = {{0,2},{5,10},{13,23},{24,25}};
    vector<vector<int>> B = {{1,5},{8,12},{15,24},{25,26}};
    auto iv = intervalIntersection(A, B);
    cout << "Interval Intersections: ";
    for (auto& v : iv) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "\n"; // [1,2] [5,5] [8,10] [15,23] [24,24] [25,25]

    return 0;
}

