/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           01 — CONTAINER SELECTION GUIDE                                   ║
║           From Zero to Grandmaster — Choosing the Right Container          ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

 THE ULTIMATE CONTAINER SELECTION CHART:
 ───────────────────────────────────────

 "I need..."                            → USE THIS
 ─────────────────────────────────────────────────────
 Dynamic array, random access           → vector
 Push/pop from both ends                → deque
 Frequent mid-list insert/delete        → list (rare in CP)
 Sorted unique elements                 → set
 Sorted elements with duplicates        → multiset
 Sorted key-value pairs                 → map
 O(1) lookup by key                     → unordered_map (+ custom hash!)
 LIFO (last in, first out)              → stack
 FIFO (first in, first out)             → queue
 Always access min/max element          → priority_queue
 K-th smallest in O(log n)             → PBDS ordered_set
 Bit manipulation on sequences          → bitset
 Fixed-size array with STL interface    → array
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "═══ CONTAINER SELECTION BY PROBLEM TYPE ═══\n\n";

    cout << "FREQUENCY COUNTING:\n";
    cout << "  • unordered_map<T, int> — O(1) avg [+ custom hash]\n";
    cout << "  • map<T, int> — O(log n) but sorted output\n\n";

    cout << "GRAPH ADJACENCY LIST:\n";
    cout << "  • vector<vector<int>> adj(n) — THE standard\n";
    cout << "  • vector<vector<pair<int,int>>> — weighted graphs\n\n";

    cout << "SHORTEST PATH:\n";
    cout << "  • Unweighted: queue (BFS)\n";
    cout << "  • 0-1 weights: deque (0-1 BFS)\n";
    cout << "  • Positive weights: priority_queue (Dijkstra)\n";
    cout << "  • Negative weights: no PQ — use Bellman-Ford\n\n";

    cout << "SLIDING WINDOW:\n";
    cout << "  • Window max/min: deque (monotonic)\n";
    cout << "  • Window median: two multisets or two PQs\n";
    cout << "  • Window distinct: unordered_map (frequency)\n\n";

    cout << "SORTED QUERIES:\n";
    cout << "  • Predecessor/successor: set + lower_bound\n";
    cout << "  • K-th smallest: PBDS ordered_set\n";
    cout << "  • Interval management: set<pair<int,int>>\n\n";

    cout << "DP OPTIMIZATION:\n";
    cout << "  • Subset sum: bitset (64x speedup)\n";
    cout << "  • Convex hull trick: deque\n";
    cout << "  • Segment tree: vector-based\n\n";

    // ── VECTOR vs LIST BENCHMARK ──
    cout << "═══ VECTOR vs LIST BENCHMARK ═══\n\n";
    const int N = 100000;

    // Sequential access (vector wins due to cache)
    {
        vector<int> v(N);
        iota(v.begin(), v.end(), 0);
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < 100; i++)
            for (int x : v) sum += x;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "vector sequential (100×10^5): " << ms << " ms\n";
    }
    {
        list<int> lst;
        for (int i = 0; i < N; i++) lst.push_back(i);
        auto start = chrono::steady_clock::now();
        long long sum = 0;
        for (int i = 0; i < 100; i++)
            for (int x : lst) sum += x;
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "list sequential (100×10^5):   " << ms << " ms (slower!)\n";
    }
    cout << "Reason: vector is cache-friendly (contiguous memory)\n\n";

    // ── MAP vs UNORDERED_MAP ──
    cout << "═══ MAP vs UNORDERED_MAP ═══\n\n";
    {
        auto start = chrono::steady_clock::now();
        map<int, int> m;
        for (int i = 0; i < N; i++) m[i] = i;
        for (int i = 0; i < N; i++) m.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "map (10^5 ops):           " << ms << " ms\n";
    }
    {
        auto start = chrono::steady_clock::now();
        unordered_map<int, int> m;
        m.reserve(N);
        for (int i = 0; i < N; i++) m[i] = i;
        for (int i = 0; i < N; i++) m.find(i);
        auto ms = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start).count();
        cout << "unordered_map (10^5 ops): " << ms << " ms\n";
    }
    cout << "\n";

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. vector is THE default — use it unless you need something specific\n";
    cout << "2. set/map for sorted queries, unordered for pure lookup\n";
    cout << "3. priority_queue for Dijkstra, deque for 0-1 BFS\n";
    cout << "4. Cache matters: vector >> list for sequential access\n";
    cout << "5. When in doubt, use vector + sort + binary_search\n";

    return 0;
}

