/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — SLIDING WINDOW MAXIMUM (LC 239) — MONOTONIC DEQUE             ║
║           From Zero to Grandmaster — Queue & Deque Patterns                 ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM:
────────
  Given array and window size k, find the maximum in each window.
  Input:  nums = [1,3,-1,-3,5,3,6,7], k = 3
  Output: [3,3,5,5,6,7]

APPROACH: Monotonic Deque (Decreasing)
──────────────────────────────────────
  Deque stores INDICES. Front = current max. Maintain decreasing order.

  Rules:
  1. Remove from front if out of window (idx ≤ i - k)
  2. Remove from back if value ≤ current (they can't be future max)
  3. Push current index at back
  4. When i ≥ k-1, front of deque = max of window

DRY RUN: [1, 3, -1, -3, 5, 3, 6, 7], k=3

  ┌──────┬────────┬───────────────┬────────────────┬──────────┐
  │  i   │ num[i] │ Deque (idx)   │ Deque (values) │ Window   │
  ├──────┼────────┼───────────────┼────────────────┼──────────┤
  │  0   │  1     │ [0]           │ [1]            │ —        │
  │  1   │  3     │ [1]           │ [3]            │ —        │
  │  2   │ -1     │ [1,2]         │ [3,-1]         │ max=3    │
  │  3   │ -3     │ [1,2,3]       │ [3,-1,-3]      │ max=3    │
  │  4   │  5     │ [4]           │ [5]            │ max=5    │
  │  5   │  3     │ [4,5]         │ [5,3]          │ max=5    │
  │  6   │  6     │ [6]           │ [6]            │ max=6    │
  │  7   │  7     │ [7]           │ [7]            │ max=7    │
  └──────┴────────┴───────────────┴────────────────┴──────────┘

  Detail at i=4 (num=5):
    - Back of deque has -3,-1,3 → all ≤ 5, pop all
    - Front of deque was idx=1 → 1 ≤ 4-3=1 → remove (out of window)
    - Push 4 → deque=[4]

  Result: [3, 3, 5, 5, 6, 7] ✅

TIME: O(n) — each element pushed/popped at most once
SPACE: O(k) for the deque

  Visual of window sliding:
  ┌─────────────────────────────────────────────────┐
  │ [1, 3, -1] -3  5  3  6  7  →  max = 3          │
  │  1 [3, -1, -3] 5  3  6  7  →  max = 3          │
  │  1  3 [-1, -3, 5] 3  6  7  →  max = 5          │
  │  1  3  -1 [-3, 5, 3] 6  7  →  max = 5          │
  │  1  3  -1  -3 [5, 3, 6] 7  →  max = 6          │
  │  1  3  -1  -3  5 [3, 6, 7] →  max = 7          │
  └─────────────────────────────────────────────────┘
*/

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SLIDING WINDOW MAXIMUM
// ═══════════════════════════════════════════════════════════════

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // Stores indices, decreasing values
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove out-of-window indices from front
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Remove smaller elements from back
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Record result when window is complete
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// SLIDING WINDOW MINIMUM (Mirror)
// ═══════════════════════════════════════════════════════════════

vector<int> minSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // Stores indices, increasing values
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] >= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// FIRST NEGATIVE IN EVERY WINDOW OF SIZE K
// ═══════════════════════════════════════════════════════════════
/*
  Maintain queue of indices of negative numbers.
  For each window, front of queue is the first negative.
*/

vector<int> firstNegativeInWindow(vector<int>& nums, int k) {
    deque<int> negIdx;
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove out-of-window
        while (!negIdx.empty() && negIdx.front() <= i - k) {
            negIdx.pop_front();
        }

        if (nums[i] < 0) negIdx.push_back(i);

        if (i >= k - 1) {
            result.push_back(negIdx.empty() ? 0 : nums[negIdx.front()]);
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  SLIDING WINDOW MAX / MIN / FIRST NEGATIVE               ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    cout << "Array: ";
    for (int x : nums) cout << x << " ";
    cout << "\nk = " << k << "\n\n";

    auto maxW = maxSlidingWindow(nums, k);
    cout << "Sliding Window Max: ";
    for (int x : maxW) cout << x << " ";
    cout << "\n";

    auto minW = minSlidingWindow(nums, k);
    cout << "Sliding Window Min: ";
    for (int x : minW) cout << x << " ";
    cout << "\n";

    auto negW = firstNegativeInWindow(nums, k);
    cout << "First Negative:     ";
    for (int x : negW) cout << x << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 239  — Sliding Window Maximum\n";
    cout << "  LC 1438 — Longest Subarray with |max-min| ≤ Limit\n";
    cout << "  LC 862  — Shortest Subarray with Sum at Least K\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

