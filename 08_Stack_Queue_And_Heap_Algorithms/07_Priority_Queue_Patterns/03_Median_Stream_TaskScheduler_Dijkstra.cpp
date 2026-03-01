/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — FIND MEDIAN FROM DATA STREAM (LC 295)                         ║
║           From Zero to Grandmaster — Priority Queue Patterns                ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Design a class that supports adding numbers and finding median.

THE TWO-HEAP TECHNIQUE:
──────────────────────
  ┌─────────────────────────────────────────────────────┐
  │  MAX HEAP (left half)    │    MIN HEAP (right half)  │
  │  Stores smaller half     │    Stores larger half     │
  │  Top = largest of left   │    Top = smallest of right│
  │                          │                           │
  │  [..., 3, 5, 7]         │    [8, 10, 12, ...]       │
  │           ↑ maxH.top()   │    ↑ minH.top()          │
  │                          │                           │
  │  Median = maxH.top() if odd count                    │
  │  Median = (maxH.top() + minH.top()) / 2 if even     │
  └─────────────────────────────────────────────────────┘

  Rules:
  1. maxH.size() >= minH.size() (max heap never smaller)
  2. maxH.size() - minH.size() <= 1 (balanced)
  3. All elements in maxH ≤ all elements in minH

DRY RUN: add(1), add(2), add(3), findMedian()

  add(1): maxH=[1], minH=[]       → median=1
  add(2): maxH=[1], minH=[2]      → median=(1+2)/2=1.5
  add(3): maxH=[1,2], minH=[3]
    Wait, let me trace carefully:

  add(1): Push to maxH → maxH=[1], minH=[]
  add(2): Push to maxH → maxH=[2,1]
          maxH.size()-minH.size()=2 > 1 → move top to minH
          maxH=[1], minH=[2]
          median = (1+2)/2 = 1.5
  add(3): Push to maxH → maxH=[3,1]
          maxH.top()=3 > minH.top()=2 → swap tops
          pop 3 from maxH, pop 2 from minH
          push 2 to maxH, push 3 to minH
          maxH=[2,1], minH=[3]
          size ok (2 vs 1)
          median = maxH.top() = 2

TIME: O(log n) per add, O(1) per findMedian
*/

#include <iostream>
#include <queue>
using namespace std;

class MedianFinder {
    priority_queue<int> maxH;                                // Left half
    priority_queue<int, vector<int>, greater<int>> minH;     // Right half

public:
    void addNum(int num) {
        maxH.push(num);

        // Ensure maxH.top() <= minH.top()
        if (!minH.empty() && maxH.top() > minH.top()) {
            int a = maxH.top(); maxH.pop();
            int b = minH.top(); minH.pop();
            maxH.push(b);
            minH.push(a);
        }

        // Balance sizes: maxH can be at most 1 larger
        if ((int)maxH.size() > (int)minH.size() + 1) {
            minH.push(maxH.top());
            maxH.pop();
        }
    }

    double findMedian() {
        if (maxH.size() > minH.size()) {
            return maxH.top();
        }
        return (maxH.top() + minH.top()) / 2.0;
    }
};

// ═══════════════════════════════════════════════════════════════
// TASK SCHEDULER (LC 621)
// ═══════════════════════════════════════════════════════════════
/*
  Schedule tasks with cooldown n. Same task needs n intervals apart.
  Return minimum intervals to finish all tasks.

  Greedy + Max Heap: Always pick the most frequent task first.

  DRY RUN: tasks=["A","A","A","B","B","B"], n=2
  freq: A=3, B=3

  Round 1: pick A(3), B(2) → schedule A,B,idle → A(2),B(2)
  Round 2: pick A(2), B(2) → A,B,idle → A(1),B(1)
  Round 3: pick A(1), B(1) → A,B → done

  Total: A B _ A B _ A B = 8 ✅
*/

int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char c : tasks) freq[c - 'A']++;

    priority_queue<int> maxH;
    for (int f : freq) if (f > 0) maxH.push(f);

    int time = 0;
    while (!maxH.empty()) {
        vector<int> temp;
        int cycle = n + 1;  // Each round is n+1 slots

        for (int i = 0; i < cycle; i++) {
            if (!maxH.empty()) {
                int top = maxH.top(); maxH.pop();
                if (top > 1) temp.push_back(top - 1);
            }
            time++;
            if (maxH.empty() && temp.empty()) break;
        }

        for (int f : temp) maxH.push(f);
    }
    return time;
}

// ═══════════════════════════════════════════════════════════════
// DIJKSTRA WITH PRIORITY QUEUE
// ═══════════════════════════════════════════════════════════════
/*
  Shortest path from source to all vertices.
  Min-heap of (distance, node).

  DRY RUN: Graph with 4 nodes
  0 --(1)--> 1
  0 --(4)--> 2
  1 --(2)--> 2
  1 --(6)--> 3
  2 --(3)--> 3

  dist = [0, INF, INF, INF], src=0
  Heap: [(0,0)]

  Pop (0,0): relax 1→dist[1]=1, relax 2→dist[2]=4
  Heap: [(1,1),(4,2)]
  Pop (1,1): relax 2→dist[2]=min(4,3)=3, relax 3→dist[3]=7
  Heap: [(3,2),(4,2),(7,3)]
  Pop (3,2): relax 3→dist[3]=min(7,6)=6
  Heap: [(4,2),(6,3),(7,3)]
  Pop (4,2): already processed, skip
  Pop (6,3): done

  dist = [0, 1, 3, 6] ✅
*/

vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;  // Stale entry

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  MEDIAN STREAM + TASK SCHEDULER + DIJKSTRA               ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Median Finder
    cout << "═══ FIND MEDIAN FROM STREAM (LC 295) ═══\n";
    MedianFinder mf;
    for (int v : {1, 2, 3, 4, 5}) {
        mf.addNum(v);
        cout << "  Add " << v << " → median = " << mf.findMedian() << "\n";
    }

    // Task Scheduler
    cout << "\n═══ TASK SCHEDULER (LC 621) ═══\n";
    vector<char> tasks = {'A','A','A','B','B','B'};
    cout << "  tasks=[A,A,A,B,B,B], n=2 → " << leastInterval(tasks, 2) << " intervals\n";

    // Dijkstra
    cout << "\n═══ DIJKSTRA'S SHORTEST PATH ═══\n";
    int n = 4;
    vector<vector<pair<int,int>>> adj(n);
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 4});
    adj[1].push_back({2, 2});
    adj[1].push_back({3, 6});
    adj[2].push_back({3, 3});

    auto dist = dijkstra(n, adj, 0);
    cout << "  Shortest distances from 0: ";
    for (int i = 0; i < n; i++) cout << "d[" << i << "]=" << dist[i] << " ";
    cout << "\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 295  — Find Median from Data Stream\n";
    cout << "  LC 621  — Task Scheduler\n";
    cout << "  LC 743  — Network Delay Time (Dijkstra)\n";
    cout << "  LC 767  — Reorganize String\n";
    cout << "  CSES 1671 — Shortest Routes I\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

