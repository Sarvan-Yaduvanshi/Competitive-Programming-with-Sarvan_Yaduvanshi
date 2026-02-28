/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — PRIORITY_QUEUE COMPLETE GUIDE                               ║
║           From Zero to Grandmaster — Heap Power                            ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Max Heap (default) and Min Heap
 2. Top-K Elements Pattern
 3. Merge K Sorted Lists
 4. Dijkstra's Shortest Path
 5. Custom Comparator for Structs

PRIORITY_QUEUE:
───────────────
  Max Heap (default): largest element on top
    priority_queue<int> pq;

  Min Heap: smallest element on top
    priority_queue<int, vector<int>, greater<int>> pq;

  push() → O(log n),  pop() → O(log n),  top() → O(1)
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: MAX HEAP AND MIN HEAP
// ═══════════════════════════════════════════════════════════════

void demonstrateHeaps() {
    cout << "═══ MAX HEAP AND MIN HEAP ═══\n\n";

    // MAX HEAP (default)
    priority_queue<int> maxHeap;
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) maxHeap.push(x);

    cout << "Max Heap (desc order): ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << "\n";

    // MIN HEAP
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) minHeap.push(x);

    cout << "Min Heap (asc order):  ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << "\n";

    // Build from vector (heapify — O(n))
    vector<int> v = {3, 1, 4, 1, 5, 9};
    priority_queue<int> fromVec(v.begin(), v.end());
    cout << "From vector: top = " << fromVec.top() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: TOP-K ELEMENTS
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Find K largest elements.

 APPROACH 1: Max heap, pop K times → O(N + K log N)
 APPROACH 2: Min heap of size K → O(N log K) — BETTER when K << N

 DRY RUN (Approach 2): arr = [3,1,4,1,5,9,2,6], K=3
   Min heap (keep only 3 largest):
   Push 3 → heap: {3}
   Push 1 → heap: {1, 3}
   Push 4 → heap: {1, 3, 4}
   Push 1 → 1 < heap.top()=1, skip (or push+pop)
   Push 5 → push, pop min(1) → heap: {3, 4, 5}
   Push 9 → push, pop min(3) → heap: {4, 5, 9}
   Push 2 → 2 < 4, skip
   Push 6 → push, pop min(4) → heap: {5, 6, 9}
   Answer: {5, 6, 9}
*/

void topKElements() {
    cout << "═══ TOP-K ELEMENTS ═══\n\n";

    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int K = 3;

    // Min heap of size K
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : arr) {
        minHeap.push(x);
        if ((int)minHeap.size() > K) minHeap.pop();  // Remove smallest
    }

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTop " << K << " elements: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MERGE K SORTED LISTS
// ═══════════════════════════════════════════════════════════════
/*
 DRY RUN: lists = [[1,4,7], [2,5,8], [3,6,9]]
   Min heap: {(1,0,0), (2,1,0), (3,2,0)}
   Pop (1,0,0) → output 1, push (4,0,1)
   Pop (2,1,0) → output 2, push (5,1,1)
   Pop (3,2,0) → output 3, push (6,2,1)
   ...
   Result: [1,2,3,4,5,6,7,8,9]
*/

void mergeKSorted() {
    cout << "═══ MERGE K SORTED LISTS ═══\n\n";

    vector<vector<int>> lists = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

    // {value, list_index, element_index}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>> pq;

    // Push first element from each list
    for (int i = 0; i < (int)lists.size(); i++) {
        if (!lists[i].empty()) pq.push({lists[i][0], i, 0});
    }

    vector<int> merged;
    while (!pq.empty()) {
        auto [val, li, ei] = pq.top();
        pq.pop();
        merged.push_back(val);
        if (ei + 1 < (int)lists[li].size()) {
            pq.push({lists[li][ei + 1], li, ei + 1});
        }
    }

    cout << "Lists: ";
    for (auto& l : lists) {
        cout << "[";
        for (int x : l) cout << x << " ";
        cout << "] ";
    }
    cout << "\nMerged: ";
    for (int x : merged) cout << x << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: DIJKSTRA'S SHORTEST PATH
// ═══════════════════════════════════════════════════════════════
/*
 Dijkstra uses a min-heap to always process the closest unvisited node.
 Time: O((V + E) log V)
*/

void dijkstra() {
    cout << "═══ DIJKSTRA'S SHORTEST PATH ═══\n\n";

    int n = 5;
    vector<vector<pair<int, int>>> adj(n);  // {neighbor, weight}
    adj[0] = {{1, 4}, {2, 1}};
    adj[1] = {{3, 1}};
    adj[2] = {{1, 2}, {3, 5}};
    adj[3] = {{4, 3}};

    vector<int> dist(n, INT_MAX);
    // {distance, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;  // Skip outdated entries

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from node 0:\n";
    for (int i = 0; i < n; i++) {
        cout << "  Node " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CUSTOM COMPARATOR
// ═══════════════════════════════════════════════════════════════

void customComparatorPQ() {
    cout << "═══ CUSTOM COMPARATOR PQ ═══\n\n";

    // Sort by second element of pair (min heap on second)
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;  // Min on second
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

    pq.push({1, 30});
    pq.push({2, 10});
    pq.push({3, 20});

    cout << "PQ sorted by second (min): ";
    while (!pq.empty()) {
        auto [a, b] = pq.top();
        pq.pop();
        cout << "(" << a << "," << b << ") ";
    }
    cout << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateHeaps();
    topKElements();
    mergeKSorted();
    dijkstra();
    customComparatorPQ();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. Default PQ = max heap. Min heap: greater<int>\n";
    cout << "2. Top-K: min heap of size K → O(N log K)\n";
    cout << "3. Merge K sorted: min heap of K elements\n";
    cout << "4. Dijkstra: min heap of {dist, node}\n";
    cout << "5. Custom comparator: lambda with decltype\n";

    return 0;
}

/*
 PRACTICE:
 1. [CSES Shortest Routes I] https://cses.fi/problemset/task/1671 (Dijkstra)
 2. [LC Top K Frequent]      https://leetcode.com/problems/top-k-frequent-elements/
 3. [LC Merge K Sorted]      https://leetcode.com/problems/merge-k-sorted-lists/
*/

