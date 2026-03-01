/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Deque-Based Greedy — Sliding Window Greedy
 *  Level   : Advanced
 * ============================================================================
 *
 *  PATTERN: Use deque to maintain greedy window properties.
 *  - Sliding Window Maximum/Minimum
 *  - Greedy decisions within a moving window
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Sliding Window Maximum (LC 239) — Monotone Decreasing Deque
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // Indices in decreasing order of values
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove elements outside window
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // Remove smaller elements (they can never be the max)
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();

        dq.push_back(i);

        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

// Shortest Subarray with Sum at Least K (LC 862) — Deque + Prefix Sum
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];

    deque<int> dq;
    int minLen = n + 1;

    for (int i = 0; i <= n; i++) {
        // Check if prefix[i] - prefix[dq.front()] >= k
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            minLen = min(minLen, i - dq.front());
            dq.pop_front();
        }
        // Maintain increasing order of prefix sums
        while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    return minLen <= n ? minLen : -1;
}

int main() {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto result = maxSlidingWindow(nums, 3);
    cout << "Sliding Window Max: ";
    for (int x : result) cout << x << " ";
    cout << endl; // 3 3 5 5 6 7

    vector<int> nums2 = {2, -1, 2};
    cout << "Shortest subarray >= 3: " << shortestSubarray(nums2, 3) << endl; // 3

    return 0;
}

