/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — TOP K FREQUENT ELEMENTS (LC 347)                              ║
║           From Zero to Grandmaster — Priority Queue Patterns                ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Given array, return K most frequent elements.
  Input: nums=[1,1,1,2,2,3], k=2  → Output: [1,2]

APPROACH:
  1. Count frequency using hash map → O(n)
  2. Use min-heap of size K to keep K most frequent → O(n log k)

DRY RUN: [1,1,1,2,2,3], k=2
  freq: {1:3, 2:2, 3:1}
  Process (freq, val) pairs with min-heap (by freq):
    (3,1): push → heap=[(3,1)]
    (2,2): push → heap=[(2,2),(3,1)]
    (1,3): 1 < heap.top().freq=2 → skip (not in top-K)
  Result: [1, 2] ✅

TIME: O(n log k)  SPACE: O(n)
*/

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    // Step 1: Count frequencies
    unordered_map<int, int> freq;
    for (int num : nums) freq[num]++;

    // Step 2: Min heap of size K (by frequency)
    // pair<freq, value> — min heap by freq
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minH;

    for (auto& [val, cnt] : freq) {
        minH.push({cnt, val});
        if ((int)minH.size() > k) minH.pop();
    }

    // Step 3: Extract results
    vector<int> result;
    while (!minH.empty()) {
        result.push_back(minH.top().second);
        minH.pop();
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// MERGE K SORTED ARRAYS (extension of LC 23)
// ═══════════════════════════════════════════════════════════════
/*
  Merge K sorted arrays into one sorted array.
  Use min-heap of (value, array_index, element_index).

  DRY RUN: [[1,4,5], [1,3,4], [2,6]]
  Init heap: (1,0,0), (1,1,0), (2,2,0)

  Pop (1,0,0) → result=[1], push (4,0,1) → heap={(1,1,0),(2,2,0),(4,0,1)}
  Pop (1,1,0) → result=[1,1], push (3,1,1) → heap={(2,2,0),(3,1,1),(4,0,1)}
  Pop (2,2,0) → result=[1,1,2], push (6,2,1)
  Pop (3,1,1) → result=[1,1,2,3], push (4,1,2)
  Pop (4,0,1) → result=[1,1,2,3,4], push (5,0,2)
  Pop (4,1,2) → result=[1,1,2,3,4,4], array 1 exhausted
  Pop (5,0,2) → result=[1,1,2,3,4,4,5], array 0 exhausted
  Pop (6,2,1) → result=[1,1,2,3,4,4,5,6], array 2 exhausted

  Result: [1,1,2,3,4,4,5,6] ✅

TIME: O(N log K) where N = total elements, K = number of arrays
*/

vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    // (value, array_idx, element_idx)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>,
                   greater<tuple<int,int,int>>> minH;

    // Initialize with first element of each array
    for (int i = 0; i < (int)arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minH.push({arrays[i][0], i, 0});
        }
    }

    vector<int> result;
    while (!minH.empty()) {
        auto [val, ai, ei] = minH.top();
        minH.pop();
        result.push_back(val);

        if (ei + 1 < (int)arrays[ai].size()) {
            minH.push({arrays[ai][ei + 1], ai, ei + 1});
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  TOP K FREQUENT + MERGE K SORTED                         ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Top K Frequent
    cout << "═══ TOP K FREQUENT (LC 347) ═══\n";
    vector<int> nums = {1,1,1,2,2,3};
    auto freq = topKFrequent(nums, 2);
    cout << "  [1,1,1,2,2,3], k=2 → [";
    for (int i = 0; i < (int)freq.size(); i++) {
        cout << freq[i]; if (i+1 < (int)freq.size()) cout << ",";
    }
    cout << "]\n\n";

    // Merge K Sorted
    cout << "═══ MERGE K SORTED ARRAYS ═══\n";
    vector<vector<int>> arrays = {{1,4,5},{1,3,4},{2,6}};
    auto merged = mergeKSorted(arrays);
    cout << "  [[1,4,5],[1,3,4],[2,6]] → [";
    for (int i = 0; i < (int)merged.size(); i++) {
        cout << merged[i]; if (i+1 < (int)merged.size()) cout << ",";
    }
    cout << "]\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 347  — Top K Frequent Elements\n";
    cout << "  LC 23   — Merge K Sorted Lists\n";
    cout << "  LC 692  — Top K Frequent Words\n";
    cout << "  LC 373  — K Pairs with Smallest Sums\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

