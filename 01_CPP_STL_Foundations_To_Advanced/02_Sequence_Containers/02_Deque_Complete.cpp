/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           02 — DEQUE COMPLETE GUIDE                                        ║
║           From Zero to Grandmaster — Double-Ended Power                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is Deque?
 2. push_front / push_back / pop
 3. Differences from Vector
 4. 0-1 BFS Trick (GM-Level)
 5. Sliding Window Maximum with Deque

WHAT IS DEQUE?
──────────────
  deque (double-ended queue) = dynamic array with O(1) insertion/removal
  at BOTH front and back.

  Internal: NOT contiguous! Uses blocks of memory.
  ┌─────┐  ┌─────┐  ┌─────┐
  │ a b │──│ c d │──│ e f │
  └─────┘  └─────┘  └─────┘

  O(1) push_front + O(1) push_back + O(1) random access

GM TIP: deque is used in CP for:
  1. BFS with 0-1 edge weights
  2. Monotonic queue (sliding window max/min)
  3. When you need both front and back operations
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: BASIC OPERATIONS
// ═══════════════════════════════════════════════════════════════

void demonstrateBasicOps() {
    cout << "═══ DEQUE BASIC OPERATIONS ═══\n\n";

    deque<int> dq;

    // Push operations
    dq.push_back(3);     // {3}
    dq.push_back(4);     // {3, 4}
    dq.push_front(2);    // {2, 3, 4}
    dq.push_front(1);    // {1, 2, 3, 4}
    dq.push_back(5);     // {1, 2, 3, 4, 5}

    cout << "After pushes: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";

    // Access
    cout << "Front: " << dq.front() << "\n";
    cout << "Back:  " << dq.back() << "\n";
    cout << "dq[2]: " << dq[2] << "\n";

    // Pop operations
    dq.pop_front();  // Remove 1 → {2, 3, 4, 5}
    dq.pop_back();   // Remove 5 → {2, 3, 4}

    cout << "After pops: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";
    cout << "Size: " << dq.size() << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: DEQUE vs VECTOR
// ═══════════════════════════════════════════════════════════════
/*
 ┌─────────────────┬──────────────┬──────────────┐
 │ Feature         │ vector       │ deque        │
 ├─────────────────┼──────────────┼──────────────┤
 │ push_back       │ O(1)*        │ O(1)*        │
 │ push_front      │ O(n) ❌       │ O(1)* ✓      │
 │ Random access   │ O(1)         │ O(1)         │
 │ Memory          │ Contiguous   │ Segmented    │
 │ Cache perf      │ Excellent    │ Good         │
 │ Iterator invalid│ On realloc   │ On insert    │
 │ Pointer to elem │ Stable*      │ Unstable     │
 └─────────────────┴──────────────┴──────────────┘

 RULE OF THUMB:
 • Use vector if you only need push_back (90% of cases)
 • Use deque if you need push_front too
 • Deque is slightly slower than vector for sequential access (cache)
*/

void demonstrateVsVector() {
    cout << "═══ DEQUE vs VECTOR PERFORMANCE ═══\n\n";

    const int N = 1000000;

    // Vector push_front (BAD — O(n) each!)
    // Don't even try for large N — way too slow

    // Deque push_front (GOOD — O(1) each!)
    {
        auto start = chrono::steady_clock::now();
        deque<int> dq;
        for (int i = 0; i < N; i++) dq.push_front(i);
        auto end = chrono::steady_clock::now();
        cout << "deque push_front (10^6): "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
    }

    // Vector push_back for comparison
    {
        auto start = chrono::steady_clock::now();
        vector<int> v;
        for (int i = 0; i < N; i++) v.push_back(i);
        auto end = chrono::steady_clock::now();
        cout << "vector push_back (10^6): "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n\n";
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: 0-1 BFS TRICK (GM-LEVEL)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Shortest path in a graph where edges have weight 0 or 1.

 APPROACH: Use deque instead of priority_queue!
   • Weight 0 edge → push_front (process sooner, like Dijkstra)
   • Weight 1 edge → push_back (process later)
   This gives O(V+E) instead of O((V+E) log V) with Dijkstra!

 DRY RUN:
   Graph: 0→1 (weight 1), 0→2 (weight 0), 2→1 (weight 0), 1→3 (weight 1)

   deque: [(0, dist=0)]
   Process 0: dist[0]=0
     Edge 0→1 (w=1): dist[1]=1, push_back → deque: [(2,0), (1,1)]
     Edge 0→2 (w=0): dist[2]=0, push_front → deque: [(2,0), (1,1)]
   Process 2: dist[2]=0
     Edge 2→1 (w=0): dist[1]=min(1,0)=0, push_front → deque: [(1,0), (1,1)]
   Process (1,0): dist[1]=0
     Edge 1→3 (w=1): dist[3]=1, push_back → deque: [(1,1), (3,1)]
   Process (1,1): 1 > dist[1]=0, skip
   Process (3,1): dist[3]=1

   Result: dist = {0, 0, 0, 1}
*/

void bfs01() {
    cout << "═══ 0-1 BFS WITH DEQUE ═══\n\n";

    int n = 4;
    // adj[u] = {(v, weight)}
    vector<vector<pair<int, int>>> adj(n);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 0});
    adj[2].push_back({1, 0});
    adj[1].push_back({3, 1});

    vector<int> dist(n, INT_MAX);
    dist[0] = 0;
    deque<int> dq;
    dq.push_back(0);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0)
                    dq.push_front(v);  // Weight 0 → front (process sooner)
                else
                    dq.push_back(v);   // Weight 1 → back (process later)
            }
        }
    }

    cout << "Shortest distances from node 0:\n";
    for (int i = 0; i < n; i++) {
        cout << "  Node " << i << ": " << dist[i] << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SLIDING WINDOW MAX WITH DEQUE (MONOTONIC DEQUE)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Given array and window size K, find max in each window.

 APPROACH: Maintain a DECREASING deque of indices.
   - Front of deque = index of maximum in current window
   - Remove from back if new element is >= back
   - Remove from front if out of window

 DRY RUN: arr = [1, 3, -1, -3, 5, 3, 6, 7], K = 3
   Window [1,3,-1]:  deque: [1(3)] → max=3
   Window [3,-1,-3]: deque: [1(3)] → max=3
   Window [-1,-3,5]: deque: [4(5)] → max=5
   Window [-3,5,3]:  deque: [4(5)] → max=5
   Window [5,3,6]:   deque: [6(6)] → max=6
   Window [3,6,7]:   deque: [7(7)] → max=7
   Answer: [3, 3, 5, 5, 6, 7]
*/

void slidingWindowMax() {
    cout << "═══ SLIDING WINDOW MAX (MONOTONIC DEQUE) ═══\n\n";

    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nWindow size: " << k << "\n\n";

    deque<int> dq;  // Stores INDICES, maintaining decreasing order of values
    vector<int> result;

    for (int i = 0; i < (int)arr.size(); i++) {
        // Remove elements outside window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        // Remove smaller elements from back (they'll never be max)
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        // Window is complete when i >= k-1
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
            cout << "Window [" << i - k + 1 << ".." << i << "]: max = "
                 << arr[dq.front()] << "\n";
        }
    }

    cout << "\nResult: ";
    for (int x : result) cout << x << " ";
    cout << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateBasicOps();
    demonstrateVsVector();
    bfs01();
    slidingWindowMax();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. deque = O(1) push/pop at BOTH ends\n";
    cout << "2. Use deque when you need push_front (vector can't)\n";
    cout << "3. 0-1 BFS with deque: O(V+E) vs O((V+E)logV) Dijkstra\n";
    cout << "4. Monotonic deque for sliding window max/min: O(n) total\n";
    cout << "5. vector is still preferred for simple push_back scenarios\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [LC Sliding Window Maximum] https://leetcode.com/problems/sliding-window-maximum/
 2. [CSES Sliding Window Max]   (Use monotonic deque)
 3. [CF 0-1 BFS problems]       Use deque-based BFS
*/

