/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Multiset / Heap (Dynamic Order Statistics)
 *  Level   : Hard → Expert (CF 1800 → 2200)
 * ============================================================================
 *
 *  ▶ WHEN DEQUE IS NOT ENOUGH:
 *  ───────────────────────────
 *  Deque gives max/min. But sometimes you need:
 *  - Median of the window
 *  - K-th smallest/largest in window
 *  - Dynamic sorted order with insertions and deletions
 *
 *  ▶ APPROACHES:
 *  ─────────────
 *  1. Multiset: O(log N) insert, O(log N) erase, O(1) begin/rbegin.
 *     Maintain iterator to median. Careful with duplicates!
 *  2. Two Heaps (maxHeap of lower half, minHeap of upper half):
 *     Sliding median or dynamic k-th element.
 *     Lazy deletion for sliding window (mark as deleted, pop when exposed).
 *  3. Policy-based Tree (GNU): O(log N) order_of_key, find_by_order.
 *     __gnu_pbds::tree → gives k-th smallest directly.
 *
 *  PROBLEMS:
 *  LC 480  — Sliding Window Median (two multisets / two heaps)
 *            https://leetcode.com/problems/sliding-window-median/
 *  LC 295  — Find Median from Data Stream (two heaps)
 *            https://leetcode.com/problems/find-median-from-data-stream/
 *  LC 2102 — Sequentially Ordinal Rank Tracker (multiset)
 *            https://leetcode.com/problems/sequentially-ordinal-rank-tracker/
 *  CSES 1077 — Sliding Median
 *             https://cses.fi/problemset/task/1077
 *  CSES 1076 — Sliding Cost (min cost to equalize to median)
 *             https://cses.fi/problemset/task/1076
 *  CF 1409E — Two Platforms (left-right DP + sort + two pointer)
 *            https://codeforces.com/problemset/problem/1409/E
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;
using ll = long long;

// ============================================================================
// LC 480 / CSES 1077: Sliding Window Median — Two Multisets
// ============================================================================
/*
 * Maintain two multisets:
 * - lo: lower half (max at rbegin)
 * - hi: upper half (min at begin)
 *
 * Invariant: lo.size() == hi.size() or lo.size() == hi.size() + 1
 * Median = *lo.rbegin() (odd window) or avg(*lo.rbegin(), *hi.begin()) (even)
 *
 * Add: Insert into correct half, rebalance.
 * Remove: Erase from whichever half contains it, rebalance.
 *
 * Time: O(N log K), Space: O(K)
 */
struct SlidingMedian {
    multiset<int> lo, hi; // lo = lower half (max at end), hi = upper half (min at begin)

    void rebalance() {
        while (lo.size() > hi.size() + 1) {
            hi.insert(*lo.rbegin());
            lo.erase(prev(lo.end()));
        }
        while (hi.size() > lo.size()) {
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }
    }

    void add(int val) {
        if (lo.empty() || val <= *lo.rbegin())
            lo.insert(val);
        else
            hi.insert(val);
        rebalance();
    }

    void remove(int val) {
        auto it = lo.find(val);
        if (it != lo.end())
            lo.erase(it);
        else
            hi.erase(hi.find(val));
        rebalance();
    }

    double getMedian(bool isOdd) {
        if (isOdd) return *lo.rbegin();
        return ((double)*lo.rbegin() + *hi.begin()) / 2.0;
    }
};

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    SlidingMedian sm;
    vector<double> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        sm.add(nums[i]);
        if (i >= k) sm.remove(nums[i - k]);
        if (i >= k - 1) result.push_back(sm.getMedian(k & 1));
    }
    return result;
}

// ============================================================================
// CSES 1076: Sliding Cost — Min cost to make all equal (= median)
// ============================================================================
/*
 * For each window of size K, compute min operations to make all equal.
 * Optimal target = median. Cost = sum |x - median| for all x in window.
 *
 * Use SlidingMedian + track sum of lower and upper halves.
 *
 * Cost = (median * loSize - loSum) + (hiSum - median * hiSize)
 *
 * Time: O(N log K), Space: O(K)
 */
struct SlidingCost {
    multiset<ll> lo, hi;
    ll loSum = 0, hiSum = 0;

    void rebalance() {
        while (lo.size() > hi.size() + 1) {
            ll val = *lo.rbegin();
            loSum -= val; hiSum += val;
            hi.insert(val); lo.erase(prev(lo.end()));
        }
        while (hi.size() > lo.size()) {
            ll val = *hi.begin();
            hiSum -= val; loSum += val;
            lo.insert(val); hi.erase(hi.begin());
        }
    }

    void add(ll val) {
        if (lo.empty() || val <= *lo.rbegin()) {
            lo.insert(val); loSum += val;
        } else {
            hi.insert(val); hiSum += val;
        }
        rebalance();
    }

    void remove(ll val) {
        auto it = lo.find(val);
        if (it != lo.end()) {
            loSum -= val; lo.erase(it);
        } else {
            it = hi.find(val);
            hiSum -= val; hi.erase(it);
        }
        rebalance();
    }

    ll getCost() {
        ll median = *lo.rbegin();
        return median * (ll)lo.size() - loSum + hiSum - median * (ll)hi.size();
    }
};

vector<ll> slidingCost(vector<int>& nums, int k) {
    SlidingCost sc;
    vector<ll> result;
    for (int i = 0; i < (int)nums.size(); i++) {
        sc.add(nums[i]);
        if (i >= k) sc.remove(nums[i - k]);
        if (i >= k - 1) result.push_back(sc.getCost());
    }
    return result;
}

// ============================================================================
// Two Heaps with Lazy Deletion — Alternative for Sliding Median
// ============================================================================
/*
 * When you can't afford multiset overhead, use priority_queue with lazy deletion.
 * Keep a "deleted" set/map. Don't actually remove from heap.
 * Pop when the top is marked as deleted.
 *
 * Useful in competitive programming where multiset is slower.
 */
struct LazyHeapMedian {
    priority_queue<int> maxHeap; // Lower half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Upper half
    unordered_map<int, int> deleted;
    int loSize = 0, hiSize = 0;

    void cleanMax() {
        while (!maxHeap.empty() && deleted[maxHeap.top()] > 0) {
            deleted[maxHeap.top()]--;
            maxHeap.pop();
        }
    }
    void cleanMin() {
        while (!minHeap.empty() && deleted[minHeap.top()] > 0) {
            deleted[minHeap.top()]--;
            minHeap.pop();
        }
    }

    void rebalance() {
        while (loSize > hiSize + 1) {
            cleanMax();
            minHeap.push(maxHeap.top()); maxHeap.pop();
            loSize--; hiSize++;
        }
        while (hiSize > loSize) {
            cleanMin();
            maxHeap.push(minHeap.top()); minHeap.pop();
            hiSize--; loSize++;
        }
    }

    void add(int val) {
        cleanMax();
        if (maxHeap.empty() || val <= maxHeap.top()) {
            maxHeap.push(val); loSize++;
        } else {
            minHeap.push(val); hiSize++;
        }
        rebalance();
    }

    void remove(int val) {
        deleted[val]++;
        cleanMax();
        if (!maxHeap.empty() && val <= maxHeap.top()) loSize--;
        else hiSize--;
        rebalance();
    }

    double getMedian(bool isOdd) {
        cleanMax(); cleanMin();
        if (isOdd) return maxHeap.top();
        return ((double)maxHeap.top() + minHeap.top()) / 2.0;
    }
};

// ============================================================================
// K-th Smallest in Dynamic Window — Using Policy-Based Tree or Multiset
// ============================================================================
/*
 * Maintain sorted window. K-th smallest = advance(begin(), k-1).
 * With multiset: O(K) per query for k-th (iterate k steps from begin).
 * With policy-based tree: O(log N) per query (find_by_order(k-1)).
 *
 * For CP: #include <ext/pb_ds/assoc_container.hpp>
 * using ordered_set = tree<pair<int,int>, null_type, less<>, rb_tree_tag,
 *                         tree_order_statistics_node_update>;
 * find_by_order(k) = iterator to k-th element (0-indexed)
 * order_of_key(x) = count of elements strictly less than x
 */

int main() {
    // Sliding Median
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    auto medians = medianSlidingWindow(nums, 3);
    cout << "Sliding medians (k=3): ";
    for (double m : medians) cout << m << " ";
    cout << "\n"; // 1 -1 -1 3 5 6

    // Sliding Cost
    auto costs = slidingCost(nums, 3);
    cout << "Sliding costs (k=3): ";
    for (ll c : costs) cout << c << " ";
    cout << "\n"; // 2 2 6 0 1 1

    return 0;
}

