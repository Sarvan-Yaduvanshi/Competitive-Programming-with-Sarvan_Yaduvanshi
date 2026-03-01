/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 10 — TWO POINTER ON SORTED ARRAY                         ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Pair Sum (Two Sum II)
 2.  Triplet Sum (3Sum)
 3.  Count Pairs Under Constraint
 4.  Count Pairs in Range
 5.  K-Sum Problems (4Sum and Generalized)
 6.  Merge Two Sorted Arrays
 7.  Sliding Window After Sorting

OVERVIEW:
─────────
Two pointers on sorted arrays is one of the most powerful patterns
in competitive programming. After sorting, many O(n²) or O(n³)
problems become O(n) or O(n²).

KEY INSIGHT:
  On a sorted array, if arr[lo] + arr[hi] < target → lo++
  if arr[lo] + arr[hi] > target → hi--
  This eliminates many candidates in O(1) per step.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: PAIR SUM (TWO SUM II)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Given SORTED array, find pair with sum = target.

 APPROACH: Two pointers from both ends
   lo = 0, hi = n-1
   if sum < target → lo++ (need larger)
   if sum > target → hi-- (need smaller)
   if sum == target → found!

 TIME: O(n)
 SPACE: O(1)

 VARIANTS:
   • Find one pair
   • Find all pairs
   • Count pairs
   • Closest pair to target
   • Pair with given difference
*/

// Find one pair with sum = target (LC 167)
pair<int, int> twoSum(vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum == target) return {lo, hi};
        if (sum < target) lo++;
        else hi--;
    }
    return {-1, -1};
}

// Find ALL pairs with sum = target
vector<pair<int, int>> twoSum_all(vector<int>& arr, int target) {
    vector<pair<int, int>> result;
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum == target) {
            result.push_back({arr[lo], arr[hi]});
            // Skip duplicates
            int a = arr[lo], b = arr[hi];
            while (lo < hi && arr[lo] == a) lo++;
            while (lo < hi && arr[hi] == b) hi--;
        } else if (sum < target) lo++;
        else hi--;
    }
    return result;
}

// Count pairs with sum = target
long long countPairsWithSum(vector<int>& arr, int target) {
    long long count = 0;
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum < target) lo++;
        else if (sum > target) hi--;
        else {
            if (arr[lo] == arr[hi]) {
                long long len = hi - lo + 1;
                count += len * (len - 1) / 2;
                break;
            }
            long long cntLo = 1, cntHi = 1;
            while (lo + 1 < hi && arr[lo] == arr[lo + 1]) { lo++; cntLo++; }
            while (hi - 1 > lo && arr[hi] == arr[hi - 1]) { hi--; cntHi++; }
            count += cntLo * cntHi;
            lo++; hi--;
        }
    }
    return count;
}

// Closest pair to target
pair<int, int> closestPairSum(vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    int bestDiff = INT_MAX;
    pair<int, int> best = {-1, -1};
    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (abs(sum - target) < bestDiff) {
            bestDiff = abs(sum - target);
            best = {arr[lo], arr[hi]};
        }
        if (sum < target) lo++;
        else hi--;
    }
    return best;
}

// Pair with given difference
pair<int, int> pairWithDifference(vector<int>& arr, int diff) {
    // Sort + two pointers (both moving forward)
    int n = arr.size();
    int i = 0, j = 1;
    while (j < n) {
        if (i == j) { j++; continue; }
        int d = arr[j] - arr[i];
        if (d == diff) return {arr[i], arr[j]};
        if (d < diff) j++;
        else i++;
    }
    return {-1, -1};
}

void demo_pair_sum() {
    cout << "=== SECTION 1: PAIR SUM ===" << endl;

    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 11;

    auto [a, b] = twoSum(arr, target);
    cout << "Pair with sum " << target << ": (" << arr[a] << "," << arr[b] << ")" << endl;

    auto all = twoSum_all(arr, target);
    cout << "All pairs: ";
    for (auto& [x, y] : all) cout << "(" << x << "," << y << ") ";
    cout << endl;

    cout << "Count pairs sum=" << target << ": " << countPairsWithSum(arr, target) << endl;

    auto [cx, cy] = closestPairSum(arr, 13);
    cout << "Closest to 13: (" << cx << "," << cy << ")" << endl;

    auto [dx, dy] = pairWithDifference(arr, 3);
    cout << "Pair diff=3: (" << dx << "," << dy << ")" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: TRIPLET SUM (3SUM)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Find all unique triplets with sum = target.

 APPROACH: Fix one element, then two-pointer on remaining
   Sort array
   for i = 0 to n-3:
     skip duplicate i
     lo = i+1, hi = n-1
     two-pointer for target - arr[i]

 TIME: O(n²)  — optimal for this problem
 SPACE: O(1) extra (excluding output)

 LC 15: 3Sum (target = 0)
 LC 16: 3Sum Closest
*/

vector<vector<int>> threeSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates

        int lo = i + 1, hi = n - 1;
        int need = target - nums[i];

        while (lo < hi) {
            int sum = nums[lo] + nums[hi];
            if (sum == need) {
                result.push_back({nums[i], nums[lo], nums[hi]});
                while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
                while (lo < hi && nums[hi] == nums[hi - 1]) hi--;
                lo++; hi--;
            } else if (sum < need) lo++;
            else hi--;
        }
    }
    return result;
}

// 3Sum Closest (LC 16)
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int closest = nums[0] + nums[1] + nums[2];

    for (int i = 0; i < n - 2; i++) {
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            int sum = nums[i] + nums[lo] + nums[hi];
            if (abs(sum - target) < abs(closest - target)) closest = sum;
            if (sum < target) lo++;
            else if (sum > target) hi--;
            else return target; // Exact match
        }
    }
    return closest;
}

// Count triplets with sum < target
long long countTripletsLessThan(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    long long count = 0;
    int n = nums.size();

    for (int i = 0; i < n - 2; i++) {
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            if (nums[i] + nums[lo] + nums[hi] < target) {
                count += (hi - lo); // All pairs (lo, lo+1...hi) work
                lo++;
            } else {
                hi--;
            }
        }
    }
    return count;
}

void demo_triplet_sum() {
    cout << "=== SECTION 2: TRIPLET SUM ===" << endl;

    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto triplets = threeSum(nums, 0);
    cout << "3Sum = 0: ";
    for (auto& t : triplets) cout << "(" << t[0] << "," << t[1] << "," << t[2] << ") ";
    cout << endl;

    vector<int> nums2 = {-1, 2, 1, -4};
    cout << "3Sum Closest to 1: " << threeSumClosest(nums2, 1) << endl; // 2

    vector<int> nums3 = {-2, 0, 1, 3};
    cout << "Triplets < 2: " << countTripletsLessThan(nums3, 2) << endl; // 2

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: COUNT PAIRS UNDER CONSTRAINT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Common patterns:
   • Count pairs with sum < K
   • Count pairs with sum > K
   • Count pairs with |diff| < K
   • Count pairs with product < K
*/

// Count pairs with sum < target
long long countPairsSumLess(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    long long count = 0;
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        if (arr[lo] + arr[hi] < target) {
            count += (hi - lo); // All pairs (lo, lo+1..hi) have sum < target
            lo++;
        } else {
            hi--;
        }
    }
    return count;
}

// Count pairs with sum > target
long long countPairsSumGreater(vector<int>& arr, int target) {
    sort(arr.begin(), arr.end());
    long long count = 0;
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo < hi) {
        if (arr[lo] + arr[hi] > target) {
            count += (hi - lo); // All pairs (lo..hi-1, hi) have sum > target
            hi--;
        } else {
            lo++;
        }
    }
    return count;
}

// Count pairs with absolute difference < K
long long countPairsDiffLess(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
    long long count = 0;
    int n = arr.size();
    int right = 0;
    for (int left = 0; left < n; left++) {
        while (right < n && arr[right] - arr[left] < k) right++;
        count += (right - left - 1);
    }
    return count;
}

void demo_count_pairs() {
    cout << "=== SECTION 3: COUNT PAIRS ===" << endl;

    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Pairs sum < 6: " << countPairsSumLess(arr, 6) << endl;   // 3: (1,2),(1,3),(1,4)
    cout << "Pairs sum > 6: " << countPairsSumGreater(arr, 6) << endl; // 4: (2,5),(3,4),(3,5),(4,5)
    cout << "Pairs |diff| < 3: " << countPairsDiffLess(arr, 3) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: COUNT PAIRS IN RANGE
// ═══════════════════════════════════════════════════════════════

// Count pairs with sum in range [lo_sum, hi_sum]
long long countPairsInRange(vector<int>& arr, int lo_sum, int hi_sum) {
    vector<int> a = arr;
    sort(a.begin(), a.end());

    // pairs with sum <= hi_sum minus pairs with sum <= lo_sum - 1
    auto countLeq = [&](int target) -> long long {
        long long cnt = 0;
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            if (a[lo] + a[hi] <= target) {
                cnt += (hi - lo);
                lo++;
            } else hi--;
        }
        return cnt;
    };

    return countLeq(hi_sum) - countLeq(lo_sum - 1);
}

void demo_pairs_in_range() {
    cout << "=== SECTION 4: PAIRS IN RANGE ===" << endl;

    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Pairs sum in [4,7]: " << countPairsInRange(arr, 4, 7) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: K-SUM PROBLEMS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 K-SUM: Find k numbers that sum to target.

 COMPLEXITY:
   2Sum: O(n)        — two pointers
   3Sum: O(n²)       — fix 1 + two pointers
   4Sum: O(n³)       — fix 2 + two pointers
   kSum: O(n^(k-1))  — fix (k-2) + two pointers

 OPTIMIZATION for 4Sum:
   Can achieve O(n² log n) using hash map of pair sums.
   But two-pointer approach is cleaner for CP.
*/

// 4Sum (LC 18)
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            int lo = j + 1, hi = n - 1;
            long long need = (long long)target - nums[i] - nums[j];

            while (lo < hi) {
                long long sum = nums[lo] + nums[hi];
                if (sum == need) {
                    result.push_back({nums[i], nums[j], nums[lo], nums[hi]});
                    while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
                    while (lo < hi && nums[hi] == nums[hi - 1]) hi--;
                    lo++; hi--;
                } else if (sum < need) lo++;
                else hi--;
            }
        }
    }
    return result;
}

// Generic kSum using recursion + two pointer base case
vector<vector<int>> kSum(vector<int>& nums, long long target, int k, int start) {
    vector<vector<int>> result;
    int n = nums.size();

    if (k == 2) {
        int lo = start, hi = n - 1;
        while (lo < hi) {
            long long sum = nums[lo] + nums[hi];
            if (sum == target) {
                result.push_back({nums[lo], nums[hi]});
                while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
                while (lo < hi && nums[hi] == nums[hi - 1]) hi--;
                lo++; hi--;
            } else if (sum < target) lo++;
            else hi--;
        }
        return result;
    }

    for (int i = start; i < n - k + 1; i++) {
        if (i > start && nums[i] == nums[i - 1]) continue;
        auto sub = kSum(nums, target - nums[i], k - 1, i + 1);
        for (auto& v : sub) {
            v.insert(v.begin(), nums[i]);
            result.push_back(v);
        }
    }
    return result;
}

void demo_ksum() {
    cout << "=== SECTION 5: K-SUM ===" << endl;

    vector<int> nums = {1, 0, -1, 0, -2, 2};
    auto quads = fourSum(nums, 0);
    cout << "4Sum = 0: ";
    for (auto& q : quads)
        cout << "(" << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << ") ";
    cout << endl;

    // Generic 5Sum
    vector<int> nums2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sort(nums2.begin(), nums2.end());
    auto fives = kSum(nums2, 25, 5, 0);
    cout << "5Sum = 25, count: " << fives.size() << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: MERGE TWO SORTED ARRAYS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Classic two-pointer merge: O(n + m) time, O(n + m) space.

 VARIANTS:
   • Merge into existing array (LC 88)
   • Merge k sorted arrays (use min-heap)
   • Find median of two sorted arrays (LC 4) — Chapter 11
   • Intersection / Union of sorted arrays
*/

// Standard merge
vector<int> mergeSorted(vector<int>& a, vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] <= b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
    }
    while (i < (int)a.size()) result.push_back(a[i++]);
    while (j < (int)b.size()) result.push_back(b[j++]);
    return result;
}

// Merge in-place (LC 88): nums1 has enough space
void merge_inplace(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] >= nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    while (j >= 0) nums1[k--] = nums2[j--];
}

// Intersection of two sorted arrays
vector<int> intersectSorted(vector<int>& a, vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] == b[j]) {
            result.push_back(a[i]);
            i++; j++;
        } else if (a[i] < b[j]) i++;
        else j++;
    }
    return result;
}

// Union of two sorted arrays (no duplicates)
vector<int> unionSorted(vector<int>& a, vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] < b[j]) result.push_back(a[i++]);
        else if (a[i] > b[j]) result.push_back(b[j++]);
        else { result.push_back(a[i]); i++; j++; }
    }
    while (i < (int)a.size()) result.push_back(a[i++]);
    while (j < (int)b.size()) result.push_back(b[j++]);
    return result;
}

void demo_merge() {
    cout << "=== SECTION 6: MERGE SORTED ARRAYS ===" << endl;

    vector<int> a = {1, 3, 5, 7, 9};
    vector<int> b = {2, 4, 5, 6, 8, 10};

    auto merged = mergeSorted(a, b);
    cout << "Merged: ";
    for (int x : merged) cout << x << " ";
    cout << endl;

    auto inter = intersectSorted(a, b);
    cout << "Intersection: ";
    for (int x : inter) cout << x << " ";
    cout << endl;

    auto uni = unionSorted(a, b);
    cout << "Union: ";
    for (int x : uni) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: SLIDING WINDOW AFTER SORTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Some problems need sorting FIRST, then sliding window on sorted data.

 PATTERN:
   1. Sort the array
   2. Use sliding window (fixed or variable size) on sorted array
   3. The sorted property gives monotonic behavior for the window

 EXAMPLES:
   • Min difference between max and min of k elements → sort + window of size k
   • Count subarrays with max-min ≤ K → sort + sliding window
   • CSES — Apartments: sort both arrays, two pointer matching
*/

// Minimum difference between max and min of any k elements
int minDiffKElements(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
    int minDiff = INT_MAX;
    for (int i = 0; i + k - 1 < (int)arr.size(); i++) {
        minDiff = min(minDiff, arr[i + k - 1] - arr[i]);
    }
    return minDiff;
}

// Maximum number of elements you can pick with max-min ≤ K
int maxElementsWithRange(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
    int maxCount = 0;
    int left = 0;
    for (int right = 0; right < (int)arr.size(); right++) {
        while (arr[right] - arr[left] > k) left++;
        maxCount = max(maxCount, right - left + 1);
    }
    return maxCount;
}

// CSES Apartments: Match applicants to apartments within tolerance
int matchApartments(vector<int>& applicants, vector<int>& apartments, int tolerance) {
    sort(applicants.begin(), applicants.end());
    sort(apartments.begin(), apartments.end());
    int matched = 0, i = 0, j = 0;
    while (i < (int)applicants.size() && j < (int)apartments.size()) {
        if (abs(applicants[i] - apartments[j]) <= tolerance) {
            matched++; i++; j++;
        } else if (applicants[i] < apartments[j]) i++;
        else j++;
    }
    return matched;
}

void demo_sliding_window_sorted() {
    cout << "=== SECTION 7: SLIDING WINDOW AFTER SORTING ===" << endl;

    vector<int> arr = {9, 4, 1, 7, 3, 8, 2};
    int k = 3;
    cout << "Min diff for " << k << " elements: " << minDiffKElements(arr, k) << endl;

    vector<int> arr2 = {1, 5, 3, 9, 7, 2};
    cout << "Max elements with range ≤ 3: " << maxElementsWithRange(arr2, 3) << endl;

    vector<int> app = {60, 45, 80, 60};
    vector<int> apt = {30, 60, 75};
    cout << "Apartment matches (tol=5): " << matchApartments(app, apt, 5) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 10: TWO POINTER ON SORTED ARRAY                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_pair_sum();
    demo_triplet_sum();
    demo_count_pairs();
    demo_pairs_in_range();
    demo_ksum();
    demo_merge();
    demo_sliding_window_sorted();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 10 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Two Sum II (LC 167)                                                    ║
║  2. Merge Sorted Array (LC 88)                                             ║
║  3. Intersection of Two Arrays II (LC 350)                                 ║
║  4. Squares of a Sorted Array (LC 977)                                     ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  5. 3Sum (LC 15)                                                           ║
║  6. 3Sum Closest (LC 16)                                                   ║
║  7. 4Sum (LC 18)                                                           ║
║  8. CSES — Apartments                                                      ║
║  9. CSES — Sum of Two Values                                               ║
║ 10. Count pairs with difference K (LC 532)                                 ║
║ 11. Boats to Save People (LC 881)                                          ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 12. CF 1324D — Pair of Topics                                              ║
║ 13. CSES — Sum of Three Values                                             ║
║ 14. CSES — Sum of Four Values                                              ║
║ 15. Count of Range Sum (LC 327)                                            ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 16. CF 1468J — Road Reform                                                 ║
║ 17. K-Sum with large k using meet-in-middle                                ║
║ 18. CF 1208E — Let Them Slide                                              ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

