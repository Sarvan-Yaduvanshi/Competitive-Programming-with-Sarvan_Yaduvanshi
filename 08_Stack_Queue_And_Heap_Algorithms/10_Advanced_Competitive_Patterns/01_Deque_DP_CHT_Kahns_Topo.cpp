/*
╔══════════════════════════════════════════════════════════════════════════════╗
║      01 — MONOTONIC DEQUE DP + CONVEX HULL TRICK + KAHN'S TOPO SORT         ║
║           From Zero to Grandmaster — Advanced Competitive Patterns          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Monotonic Deque DP Optimization
 2. Convex Hull Trick (Deque Variant)
 3. Kahn's Topological Sort (BFS)

MONOTONIC DEQUE DP:
──────────────────
  When DP transition looks like:
    dp[i] = min/max(dp[j]) + cost(i)  for j in [i-k, i-1]

  This is a "sliding window min/max" on dp values!
  Use monotonic deque → O(n) instead of O(nk).

  Classic example: Minimum cost to reach end, can jump 1..k steps.
  dp[i] = min(dp[i-k]...dp[i-1]) + cost[i]

  DRY RUN: cost=[1, 3, 1, 5, 2], k=2
  dp[0]=1
  dp[1]=min(dp[0])+3 = 1+3 = 4
  dp[2]=min(dp[0],dp[1])+1 = 1+1 = 2
  dp[3]=min(dp[1],dp[2])+5 = 2+5 = 7
  dp[4]=min(dp[2],dp[3])+2 = 2+2 = 4

KAHN'S ALGORITHM (TOPOLOGICAL SORT):
────────────────────────────────────
  BFS-based topological sort.
  1. Compute in-degree of all vertices
  2. Push all vertices with in-degree 0 into queue
  3. Process queue: for each vertex, reduce in-degree of neighbors
  4. If neighbor's in-degree becomes 0, push to queue

  DRY RUN: 5→0, 5→2, 4→0, 4→1, 2→3, 3→1

  in-degree: [2,2,1,1,0,0]  (0 has 2 incoming, etc.)
  Queue: [4, 5]  (in-degree 0)

  Process 4: reduce 0(→1), 1(→1) → Queue: [5]
  Process 5: reduce 0(→0), 2(→0) → Queue: [0, 2]
  Process 0: no outgoing → Queue: [2]
  Process 2: reduce 3(→0) → Queue: [3]
  Process 3: reduce 1(→0) → Queue: [1]
  Process 1: done

  Topo order: [4, 5, 0, 2, 3, 1] ✅

  Cycle detection: If processed count < n → cycle exists!

TIME: O(V + E)
*/

#include <iostream>
#include <queue>
#include <deque>
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// 1. MONOTONIC DEQUE DP: Min Cost Jump
// ═══════════════════════════════════════════════════════════════

int minCostJump(vector<int>& cost, int k) {
    int n = cost.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = cost[0];

    deque<int> dq;  // Stores indices, dp[idx] is increasing
    dq.push_back(0);

    for (int i = 1; i < n; i++) {
        // Remove out of window
        while (!dq.empty() && dq.front() < i - k) dq.pop_front();

        // dp[i] = min in window + cost[i]
        dp[i] = dp[dq.front()] + cost[i];

        // Maintain increasing deque
        while (!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    return dp[n - 1];
}

// ═══════════════════════════════════════════════════════════════
// LC 1425: Constrained Subsequence Sum
// dp[i] = nums[i] + max(0, max(dp[i-k]...dp[i-1]))
// ═══════════════════════════════════════════════════════════════

int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq;  // Decreasing deque of dp values' indices
    int ans = INT_MIN;

    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.front() < i - k) dq.pop_front();

        dp[i] = nums[i];
        if (!dq.empty()) dp[i] = max(dp[i], dp[dq.front()] + nums[i]);

        while (!dq.empty() && dp[dq.back()] <= dp[i]) dq.pop_back();
        dq.push_back(i);

        ans = max(ans, dp[i]);
    }
    return ans;
}

// ═══════════════════════════════════════════════════════════════
// 2. KAHN'S TOPOLOGICAL SORT
// ═══════════════════════════════════════════════════════════════

vector<int> kahnTopologicalSort(int n, vector<vector<int>>& adj) {
    vector<int> inDegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) q.push(v);
        }
    }

    if ((int)topoOrder.size() != n) {
        cout << "  ⚠️ CYCLE DETECTED! No valid topological order.\n";
        return {};
    }
    return topoOrder;
}

// ═══════════════════════════════════════════════════════════════
// COURSE SCHEDULE (LC 207 / CSES 1679)
// ═══════════════════════════════════════════════════════════════

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDegree(numCourses, 0);

    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        inDegree[p[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    int count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v : adj[u]) {
            if (--inDegree[v] == 0) q.push(v);
        }
    }
    return count == numCourses;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DEQUE DP + CONVEX HULL TRICK + KAHN'S TOPO SORT        ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Monotonic Deque DP
    cout << "═══ MONOTONIC DEQUE DP ═══\n";
    vector<int> cost = {1, 3, 1, 5, 2};
    cout << "  costs=[1,3,1,5,2], k=2 → min cost: " << minCostJump(cost, 2) << "\n";

    vector<int> nums = {10, 2, -10, 5, 20};
    cout << "  Constrained Subset Sum [10,2,-10,5,20] k=2: "
         << constrainedSubsetSum(nums, 2) << "\n\n";

    // Kahn's Topological Sort
    cout << "═══ KAHN'S TOPOLOGICAL SORT ═══\n";
    int n = 6;
    vector<vector<int>> adj(n);
    adj[5] = {0, 2};
    adj[4] = {0, 1};
    adj[2] = {3};
    adj[3] = {1};

    auto topo = kahnTopologicalSort(n, adj);
    cout << "  Graph: 5→0,2  4→0,1  2→3  3→1\n";
    cout << "  Topo order: ";
    for (int x : topo) cout << x << " ";
    cout << "\n\n";

    // Course Schedule
    cout << "═══ COURSE SCHEDULE (LC 207) ═══\n";
    vector<vector<int>> prereqs = {{1,0},{0,1}};
    cout << "  [[1,0],[0,1]] (cycle): " << (canFinish(2, prereqs) ? "YES" : "NO") << "\n";
    prereqs = {{1,0}};
    cout << "  [[1,0]]: " << (canFinish(2, prereqs) ? "YES" : "NO") << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 1425 — Constrained Subsequence Sum\n";
    cout << "  LC 207  — Course Schedule\n";
    cout << "  LC 210  — Course Schedule II\n";
    cout << "  CSES 1679 — Course Schedule\n";
    cout << "  CSES 1694 — Download Speed (network flow)\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

