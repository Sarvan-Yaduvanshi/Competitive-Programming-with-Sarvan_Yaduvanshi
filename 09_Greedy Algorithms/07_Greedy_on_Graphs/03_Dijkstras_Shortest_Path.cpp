/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Dijkstra's Shortest Path Algorithm
 *  Level   : Advanced
 * ============================================================================
 *
 *  ALGORITHM:
 *  1. Initialize dist[source] = 0, dist[others] = INF
 *  2. Use min-heap: extract vertex with smallest distance
 *  3. For each neighbor, try to relax: if dist[u] + w < dist[v], update
 *  4. Repeat until heap is empty
 *
 *  TIME:  O((V + E) log V) with binary heap
 *  SPACE: O(V + E)
 *
 *  REQUIREMENT: No negative weight edges!
 *  (For negative weights, use Bellman-Ford)
 *
 *  WHY GREEDY WORKS:
 *  When we extract the minimum-distance vertex, its distance is final.
 *  Proof: Any other path would go through an unprocessed vertex with
 *  distance ≥ current (since we pick the minimum), and edges are non-negative,
 *  so that path can't be shorter.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

using pll = pair<long long, int>; // {distance, vertex}

vector<long long> dijkstra(int n, vector<vector<pll>>& adj, int src) {
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (d > dist[u]) continue; // Stale entry

        for (auto& [w, v] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n = 5;
    vector<vector<pll>> adj(n);
    auto addEdge = [&](int u, int v, long long w) {
        adj[u].push_back({w, v});
    };

    addEdge(0, 1, 10);
    addEdge(0, 4, 5);
    addEdge(1, 2, 1);
    addEdge(1, 4, 2);
    addEdge(2, 3, 4);
    addEdge(3, 2, 6);
    addEdge(3, 0, 7);
    addEdge(4, 1, 3);
    addEdge(4, 2, 9);
    addEdge(4, 3, 2);

    auto dist = dijkstra(n, adj, 0);
    cout << "Shortest distances from vertex 0:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  to " << i << ": " << dist[i] << endl;
    // 0→0:0, 0→1:8, 0→2:9, 0→3:7, 0→4:5

    return 0;
}

