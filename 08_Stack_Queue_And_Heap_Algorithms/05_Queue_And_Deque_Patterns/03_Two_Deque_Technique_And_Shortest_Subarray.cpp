/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       03 — MAX-MIN ≤ K WINDOW + TWO DEQUE TECHNIQUE                          ║
║           From Zero to Grandmaster — Queue & Deque Patterns                 ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM (LC 1438): Longest Continuous Subarray with |max - min| ≤ limit
─────────────────────────────────────────────────────────────────────────
  Find the size of the longest subarray where the absolute difference
  between any two elements is less than or equal to `limit`.

APPROACH: TWO DEQUES + SLIDING WINDOW
──────────────────────────────────────
  Maintain two monotonic deques:
    maxDeque: decreasing order → front = current window maximum
    minDeque: increasing order → front = current window minimum

  Expand right pointer. If max - min > limit, shrink left pointer.
  Track maximum window size.

DRY RUN: nums = [8,2,4,7], limit = 4
  ┌────────┬──────────┬──────────┬────────┬───────────┬─────────┐
  │ left   │ right    │ maxDeque │ minDeque│ max-min   │ window  │
  ├────────┼──────────┼──────────┼────────┼───────────┼─────────┤
  │  0     │  0 (8)   │ [8]      │ [8]    │ 8-8=0 ≤4  │ 1       │
  │  0     │  1 (2)   │ [8,2]    │ [2]    │ 8-2=6 >4  │ shrink! │
  │  1     │  1 (2)   │ [2]      │ [2]    │ 2-2=0 ≤4  │ 1       │
  │  1     │  2 (4)   │ [4]      │ [2,4]  │ 4-2=2 ≤4  │ 2       │
  │  1     │  3 (7)   │ [7]      │ [2,4,7]│ 7-2=5 >4  │ shrink! │
  │  2     │  3 (7)   │ [7]      │ [4,7]  │ 7-4=3 ≤4  │ 2       │
  └────────┴──────────┴──────────┴────────┴───────────┴─────────┘

  Answer: 2 ✅

  Visual of two deques maintaining max and min:
  ┌────────────────────────────────────────────────────┐
  │  MAX DEQUE (decreasing):                           │
  │  front → [8] ... → gives window MAXIMUM            │
  │                                                     │
  │  MIN DEQUE (increasing):                           │
  │  front → [2] ... → gives window MINIMUM            │
  │                                                     │
  │  When max - min > limit:                           │
  │    Move left pointer forward                       │
  │    Remove expired elements from both deques        │
  └────────────────────────────────────────────────────┘

TIME: O(n)  SPACE: O(n)
*/

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// LC 1438: Longest Subarray with |max-min| ≤ limit
// ═══════════════════════════════════════════════════════════════

int longestSubarray(vector<int>& nums, int limit) {
    deque<int> maxDq, minDq;  // Store indices
    int left = 0, ans = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        // Maintain decreasing deque for max
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right])
            maxDq.pop_back();
        maxDq.push_back(right);

        // Maintain increasing deque for min
        while (!minDq.empty() && nums[minDq.back()] >= nums[right])
            minDq.pop_back();
        minDq.push_back(right);

        // Shrink window if condition violated
        while (nums[maxDq.front()] - nums[minDq.front()] > limit) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }

        ans = max(ans, right - left + 1);
    }
    return ans;
}

// ═══════════════════════════════════════════════════════════════
// COUNT SUBARRAYS WITH max-min ≤ K (Extension)
// ═══════════════════════════════════════════════════════════════
/*
  Count total subarrays where max - min ≤ K.
  Each valid window [left, right] contributes (right - left + 1) subarrays.
*/

long long countSubarrays(vector<int>& nums, int k) {
    deque<int> maxDq, minDq;
    int left = 0;
    long long count = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right]) maxDq.pop_back();
        maxDq.push_back(right);
        while (!minDq.empty() && nums[minDq.back()] >= nums[right]) minDq.pop_back();
        minDq.push_back(right);

        while (nums[maxDq.front()] - nums[minDq.front()] > k) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }

        count += (right - left + 1);  // All subarrays ending at right
    }
    return count;
}

// ═══════════════════════════════════════════════════════════════
// SHORTEST SUBARRAY WITH SUM ≥ K (LC 862) — Monotonic Deque
// ═══════════════════════════════════════════════════════════════
/*
  Given array (can have negatives), find shortest subarray with sum ≥ k.

  Key idea: Use prefix sums + monotonic deque.
  prefix[j] - prefix[i] ≥ k → subarray [i+1..j] has sum ≥ k

  Deque maintains increasing prefix sums.
  For each j:
    1. While prefix[j] - prefix[dq.front()] ≥ k → update answer, pop front
       (dq.front() can't give shorter answer for future j)
    2. While prefix[dq.back()] ≥ prefix[j] → pop back
       (j is better than dq.back() for future queries)
    3. Push j

TIME: O(n)  SPACE: O(n)
*/

int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];

    deque<int> dq;
    int ans = n + 1;

    for (int j = 0; j <= n; j++) {
        // Check if we found a valid subarray
        while (!dq.empty() && prefix[j] - prefix[dq.front()] >= k) {
            ans = min(ans, j - dq.front());
            dq.pop_front();
        }

        // Maintain increasing deque
        while (!dq.empty() && prefix[dq.back()] >= prefix[j]) {
            dq.pop_back();
        }

        dq.push_back(j);
    }

    return ans <= n ? ans : -1;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  TWO DEQUE TECHNIQUE + SHORTEST SUBARRAY SUM ≥ K         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // LC 1438
    cout << "═══ LONGEST SUBARRAY |max-min| ≤ limit (LC 1438) ═══\n";
    vector<int> n1 = {8, 2, 4, 7};
    cout << "  [8,2,4,7], limit=4 → " << longestSubarray(n1, 4) << "\n";

    vector<int> n2 = {10, 1, 2, 4, 7, 2};
    cout << "  [10,1,2,4,7,2], limit=5 → " << longestSubarray(n2, 5) << "\n";

    vector<int> n3 = {4, 2, 2, 2, 4, 4, 2, 2};
    cout << "  [4,2,2,2,4,4,2,2], limit=0 → " << longestSubarray(n3, 0) << "\n\n";

    // Count subarrays
    cout << "═══ COUNT SUBARRAYS WITH max-min ≤ K ═══\n";
    vector<int> n4 = {1, 3, 2, 4};
    cout << "  [1,3,2,4], k=2 → " << countSubarrays(n4, 2) << " subarrays\n\n";

    // LC 862
    cout << "═══ SHORTEST SUBARRAY WITH SUM ≥ K (LC 862) ═══\n";
    vector<int> s1 = {1};
    cout << "  [1], k=1 → " << shortestSubarray(s1, 1) << "\n";

    vector<int> s2 = {2, -1, 2};
    cout << "  [2,-1,2], k=3 → " << shortestSubarray(s2, 3) << "\n";

    vector<int> s3 = {1, 2};
    cout << "  [1,2], k=4 → " << shortestSubarray(s3, 4) << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 1438 — Longest Continuous Subarray (Two Deques)\n";
    cout << "  LC 862  — Shortest Subarray with Sum at Least K\n";
    cout << "  LC 1425 — Constrained Subsequence Sum\n";
    cout << "  CF 487B — Strip (Two Deque + Binary Search)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

