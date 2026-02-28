/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Monotonic Queue (Variable Constraint)
 *  Level   : Medium → Hard (CF 1500 → 2000)
 * ============================================================================
 *
 *  ▶ CORE PATTERN:
 *  ───────────────
 *  "Longest/shortest subarray where max - min ≤ K"
 *
 *  Unlike fixed-size deque problems (LC 239), here the WINDOW SIZE is variable.
 *  We maintain TWO deques:
 *  - maxDeque: monotone decreasing → front = current window max
 *  - minDeque: monotone increasing → front = current window min
 *
 *  Expand right. While max - min > K → shrink left.
 *  Each element is added/removed at most once per deque → O(N) total.
 *
 *  ▶ WHY TWO DEQUES?
 *  ──────────────────
 *  Deque gives O(1) access to max AND min simultaneously.
 *  A single multiset would give O(log N) per operation.
 *  Two deques = O(N) total vs multiset = O(N log N) total.
 *
 *  PROBLEMS:
 *  LC 1438 — Longest Subarray Abs Diff ≤ Limit (two deques)
 *            https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
 *  LC 2762 — Continuous Subarrays (max - min ≤ 2)
 *            https://leetcode.com/problems/continuous-subarrays/
 *  CF 602B — Approximating a Constant Range (max-min ≤ 1, 1500)
 *            https://codeforces.com/problemset/problem/602/B
 *  CF 514D — R2D2 and Droid Army (multi-attribute max deques, 1800)
 *            https://codeforces.com/problemset/problem/514/D
 *  CF 487B — Strip (min window + DP, 2000)
 *            https://codeforces.com/problemset/problem/487/B
 *  LC 2968 — Apply Operations to Maximize Frequency Score (sort + binary search + window)
 *            https://leetcode.com/problems/apply-operations-to-maximize-frequency-score/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// LC 1438: Longest Continuous Subarray With Absolute Diff ≤ Limit
// ============================================================================
/*
 * Find longest subarray where |max - min| ≤ limit.
 *
 * TWO DEQUES:
 * maxDq: decreasing → front = window max
 * minDq: increasing → front = window min
 *
 * Expand right. While max - min > limit → shrink left.
 * When shrinking: pop front of deque if its index == left.
 *
 * Time: O(N), Space: O(N)
 */
int longestSubarray(vector<int>& nums, int limit) {
    deque<int> maxDq, minDq; // Store indices
    int left = 0, best = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        // Maintain decreasing deque for max
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right])
            maxDq.pop_back();
        maxDq.push_back(right);

        // Maintain increasing deque for min
        while (!minDq.empty() && nums[minDq.back()] >= nums[right])
            minDq.pop_back();
        minDq.push_back(right);

        // Shrink while violation
        while (nums[maxDq.front()] - nums[minDq.front()] > limit) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 2762: Continuous Subarrays — Count subarrays where max - min ≤ 2
// ============================================================================
/*
 * Same deque setup. For each right, window [left, right] is the longest
 * valid window ending at right. All subarrays ending at right within
 * this window are valid → count += (right - left + 1).
 *
 * Time: O(N), Space: O(N)
 */
long long continuousSubarrays(vector<int>& nums) {
    deque<int> maxDq, minDq;
    int left = 0;
    ll count = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        while (!maxDq.empty() && nums[maxDq.back()] <= nums[right])
            maxDq.pop_back();
        maxDq.push_back(right);
        while (!minDq.empty() && nums[minDq.back()] >= nums[right])
            minDq.pop_back();
        minDq.push_back(right);

        while (nums[maxDq.front()] - nums[minDq.front()] > 2) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// CF 602B: Approximating a Constant Range — Longest with max-min ≤ 1
// ============================================================================
/*
 * Exactly the same pattern with limit = 1.
 * Demonstrates the versatility: just change the limit parameter.
 */
void solve_CF602B() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    cout << longestSubarray(a, 1) << "\n";
}

// ============================================================================
// Multi-Attribute Window — CF 514D Style (M Deques)
// ============================================================================
/*
 * N objects, each with M attributes. Given budget K.
 * Cost of window = sum of max of each attribute in window.
 * Find longest window with cost ≤ K.
 *
 * Use M separate max-deques, one per attribute.
 * Two pointer: expand right (add to all M deques),
 *              shrink left (remove from all M deques) while cost > K.
 */
int longestMultiAttrWindow(vector<vector<int>>& attrs, ll budget) {
    int n = attrs.size(), m = attrs[0].size();
    vector<deque<int>> maxDqs(m);
    int left = 0, best = 0;

    for (int right = 0; right < n; right++) {
        for (int j = 0; j < m; j++) {
            while (!maxDqs[j].empty() && attrs[maxDqs[j].back()][j] <= attrs[right][j])
                maxDqs[j].pop_back();
            maxDqs[j].push_back(right);
        }

        // Compute cost
        auto cost = [&]() -> ll {
            ll total = 0;
            for (int j = 0; j < m; j++)
                total += attrs[maxDqs[j].front()][j];
            return total;
        };

        while (cost() > budget) {
            for (int j = 0; j < m; j++)
                if (maxDqs[j].front() == left) maxDqs[j].pop_front();
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// Bounded Difference + Count — Template
// ============================================================================
/*
 * GENERAL: Count all subarrays where max - min ≤ K.
 * Use two deques + two pointer.
 * For each right, find leftmost left where max - min ≤ K.
 * count += (right - left + 1).
 * Total: O(N).
 */
ll countSubarraysBoundedDiff(vector<int>& nums, int k) {
    deque<int> maxDq, minDq;
    int left = 0;
    ll count = 0;

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
        count += (right - left + 1);
    }
    return count;
}

int main() {
    // LC 1438: Longest with |diff| ≤ limit
    vector<int> nums1 = {8, 2, 4, 7};
    cout << "Longest (limit=4): " << longestSubarray(nums1, 4) << "\n"; // 2

    vector<int> nums2 = {10, 1, 2, 4, 7, 2};
    cout << "Longest (limit=5): " << longestSubarray(nums2, 5) << "\n"; // 4

    // LC 2762: Continuous subarrays (|diff| ≤ 2)
    vector<int> nums3 = {5, 4, 2, 4};
    cout << "Continuous: " << continuousSubarrays(nums3) << "\n"; // 8

    // Count bounded diff subarrays
    vector<int> nums4 = {1, 3, 2, 4, 5};
    cout << "Count (diff≤2): " << countSubarraysBoundedDiff(nums4, 2) << "\n"; // 12

    return 0;
}

