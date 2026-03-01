/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       03 — MULTISET VS DEQUE + OFFLINE QUERIES + MULTI-QUEUE SIMULATION      ║
║           From Zero to Grandmaster — Advanced Competitive Patterns          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Multiset vs Deque for Sliding Window
 2. Offline Queries + Sorting + Heap
 3. Multi-Queue Simulation Problems

MULTISET vs DEQUE for SLIDING WINDOW:
────────────────────────────────────
  Both can maintain sliding window max/min, but with trade-offs:

  ┌──────────────────┬──────────────┬────────────────────────────┐
  │ Feature          │ Deque        │ Multiset                   │
  ├──────────────────┼──────────────┼────────────────────────────┤
  │ Insert           │ O(1) amort.  │ O(log n)                   │
  │ Remove (expired) │ O(1) front   │ O(log n) by iterator       │
  │ Query max/min    │ O(1) front   │ O(1) begin/rbegin          │
  │ Query BOTH       │ Need 2 deques│ O(1) both ends             │
  │ Arbitrary delete │ ❌ Not easy   │ ✅ O(log n) by iterator     │
  │ Memory           │ O(k)         │ O(k)                       │
  │ Total for n ops  │ O(n)         │ O(n log n)                 │
  └──────────────────┴──────────────┴────────────────────────────┘

  WHEN TO USE WHAT:
    Deque: When you only need max OR min, and removal is only from front
    Multiset: When you need both max AND min, or arbitrary deletion

  Example: LC 1438 (|max-min| ≤ limit) → Deque is better (O(n))
  Example: LC 480 (Sliding Window Median) → Multiset is easier

OFFLINE QUERIES + HEAP:
──────────────────────
  When queries arrive in any order, sometimes it's better to:
    1. Sort queries by some criterion
    2. Process in sorted order using a heap to track candidates

  Example: "For each query (L, R, K), find Kth smallest in arr[L..R]"
    Sort queries by R. Sweep left-to-right adding elements to a max-heap of size K.

  Example: CSES 1077 — Sliding Window Cost
    Maintain two halves (small/large) with removals.
*/

#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. SLIDING WINDOW WITH MULTISET (Both max and min)
// ═══════════════════════════════════════════════════════════════

// LC 1438: Longest subarray with |max - min| ≤ limit
// Using multiset (cleaner but O(n log n))
int longestSubarrayMultiset(vector<int>& nums, int limit) {
    multiset<int> window;
    int left = 0, ans = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        window.insert(nums[right]);

        // Shrink window if condition violated
        while (*window.rbegin() - *window.begin() > limit) {
            window.erase(window.find(nums[left]));
            left++;
        }

        ans = max(ans, right - left + 1);
    }
    return ans;
}

// ═══════════════════════════════════════════════════════════════
// 2. OFFLINE QUERIES — SORT AND SWEEP WITH HEAP
// ═══════════════════════════════════════════════════════════════
/*
  Problem: Given array, answer queries: "What is the max in range [L,R]?"

  Offline approach (when online isn't required):
    1. Sort queries by R (right endpoint)
    2. Sweep from left to right, maintaining candidate set
    3. For each query, answer when R reaches that query's right endpoint

  This is useful when combined with heaps for tracking top-K, etc.

  DRY RUN: arr = [3,1,4,1,5,9,2,6], queries = [(0,3), (2,5), (1,7)]
  Sort by R: [(0,3), (2,5), (1,7)]

  Sweep right:
    r=0..3: Add elements [3,1,4,1], answer query (0,3): max=4
    r=4..5: Add [5,9], answer query (2,5): max in [4,1,5,9]=9
    r=6..7: Add [2,6], answer query (1,7): max in [1,4,1,5,9,2,6]=9
*/

struct Query {
    int l, r, idx;
};

vector<int> offlineMaxQueries(vector<int>& arr, vector<pair<int,int>>& rawQueries) {
    int n = arr.size(), q = rawQueries.size();
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i] = {rawQueries[i].first, rawQueries[i].second, i};
    }

    // Sort by right endpoint
    sort(queries.begin(), queries.end(), [](Query& a, Query& b) {
        return a.r < b.r;
    });

    vector<int> answers(q);

    // For max in range, we can use sparse table or segment tree online,
    // but here's a simple offline approach with suffix max:
    // Actually for general offline, let's demonstrate the pattern:

    int ptr = 0;  // Current right position in array
    // For each query sorted by R
    for (auto& query : queries) {
        // Extend to query.r (add elements to our data structure)
        while (ptr <= query.r) {
            // In a real problem, add arr[ptr] to heap/structure
            ptr++;
        }

        // Answer query: find max in [query.l, query.r]
        int maxVal = *max_element(arr.begin() + query.l, arr.begin() + query.r + 1);
        answers[query.idx] = maxVal;
    }

    return answers;
}

// ═══════════════════════════════════════════════════════════════
// 3. MULTI-QUEUE SIMULATION — TASK PROCESSING
// ═══════════════════════════════════════════════════════════════
/*
  Simulate multiple queues processing tasks.

  Example: K servers, each takes time to process.
  Incoming requests at various times.
  Find the server that handles each request.

  Pattern:
    - Min heap for "available servers" (ordered by availability time)
    - Queue for pending requests

  LC 1882: Process Tasks Using Servers
    servers[i] = processing weight
    tasks[j] arrives at time j
    Assign to server with smallest weight (tie: smallest index)
    If no free server, wait until one frees up
*/

vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
    int m = servers.size(), n = tasks.size();

    // (weight, index) — available servers
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> available;
    // (freeTime, weight, index) — busy servers
    priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>,
                   greater<tuple<long long,int,int>>> busy;

    for (int i = 0; i < m; i++) {
        available.push({servers[i], i});
    }

    vector<int> result(n);

    for (int j = 0; j < n; j++) {
        long long time = j;

        // Free up servers that are done by time j
        while (!busy.empty() && get<0>(busy.top()) <= time) {
            auto [freeTime, weight, idx] = busy.top();
            busy.pop();
            available.push({weight, idx});
        }

        // If no server available, jump to earliest free time
        if (available.empty()) {
            auto [freeTime, weight, idx] = busy.top();
            busy.pop();
            time = freeTime;
            available.push({weight, idx});

            // Free all servers available at this time
            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [ft, w, id] = busy.top();
                busy.pop();
                available.push({w, id});
            }
        }

        // Assign task to best available server
        auto [weight, idx] = available.top();
        available.pop();
        result[j] = idx;
        busy.push({time + tasks[j], weight, idx});
    }

    return result;
}

// ═══════════════════════════════════════════════════════════════
// 4. CSES 1163 — TRAFFIC LIGHTS (Multiset Pattern)
// ═══════════════════════════════════════════════════════════════
/*
  Street of length x. Traffic lights added one by one at positions.
  After each addition, report the longest passage without a light.

  Maintain: set of light positions + multiset of segment lengths.
  When adding light at position p:
    1. Find segment containing p using set (lower_bound)
    2. Remove old segment length from multiset
    3. Add two new segment lengths
    4. Max segment = *multiset.rbegin()

  DRY RUN: x=8, lights at [3, 6, 2]

  Init: positions={0,8}, segments={8}
  Add 3: split 8 into [0,3]=3 and [3,8]=5
         segments={3,5}, max=5
  Add 6: split 5 into [3,6]=3 and [6,8]=2
         segments={2,3,3}, max=3
  Add 2: split 3 (first segment [0,3]) into [0,2]=2 and [2,3]=1
         segments={1,2,2,3}, max=3

  Output: 5 3 3

TIME: O(n log n)
*/

vector<int> trafficLights(int x, vector<int>& positions) {
    set<int> lights;
    lights.insert(0);
    lights.insert(x);

    multiset<int> segments;
    segments.insert(x);

    vector<int> result;

    for (int p : positions) {
        // Find the segment containing p
        auto it = lights.upper_bound(p);  // First light AFTER p
        int right = *it;
        int left = *prev(it);

        // Remove old segment
        segments.erase(segments.find(right - left));

        // Add two new segments
        segments.insert(p - left);
        segments.insert(right - p);

        lights.insert(p);

        // Max segment
        result.push_back(*segments.rbegin());
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MULTISET vs DEQUE + OFFLINE QUERIES + SIMULATION        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Multiset sliding window
    cout << "═══ MULTISET SLIDING WINDOW (LC 1438) ═══\n";
    vector<int> n1 = {8, 2, 4, 7};
    cout << "  [8,2,4,7], limit=4 → " << longestSubarrayMultiset(n1, 4) << "\n\n";

    // Offline queries
    cout << "═══ OFFLINE QUERIES ═══\n";
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    vector<pair<int,int>> queries = {{0,3}, {2,5}, {1,7}};
    auto answers = offlineMaxQueries(arr, queries);
    for (int i = 0; i < (int)queries.size(); i++) {
        cout << "  max in [" << queries[i].first << "," << queries[i].second
             << "] = " << answers[i] << "\n";
    }

    // Task assignment
    cout << "\n═══ TASK ASSIGNMENT (LC 1882 style) ═══\n";
    vector<int> servers = {3, 3, 2};
    vector<int> tasks = {1, 2, 3, 2, 1, 2};
    auto assigned = assignTasks(servers, tasks);
    cout << "  Servers: [3,3,2], Tasks: [1,2,3,2,1,2]\n  Assigned: [";
    for (int i = 0; i < (int)assigned.size(); i++) {
        cout << assigned[i]; if (i+1<(int)assigned.size()) cout << ",";
    }
    cout << "]\n";

    // Traffic Lights
    cout << "\n═══ TRAFFIC LIGHTS (CSES 1163) ═══\n";
    vector<int> pos = {3, 6, 2};
    auto tl = trafficLights(8, pos);
    cout << "  x=8, lights at [3,6,2]\n  Max passages: ";
    for (int x : tl) cout << x << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  CSES 1163 — Traffic Lights (Multiset)\n";
    cout << "  CSES 1077 — Sliding Window Cost\n";
    cout << "  LC 1882  — Process Tasks Using Servers\n";
    cout << "  LC 1606  — Find Servers That Handled Most Requests\n";
    cout << "  CF 797E  — Array Queries (Offline + Sqrt)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

