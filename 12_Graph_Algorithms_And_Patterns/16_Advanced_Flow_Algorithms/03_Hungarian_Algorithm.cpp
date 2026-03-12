/*
╔══════════════════════════════════════════════════════════════════╗
║         03 — HUNGARIAN ALGORITHM                                ║
║         Minimum cost assignment / weighted bipartite matching   ║
╚══════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
DEFINITION
═══════════════════════════════════════════════════════════════════

Given n workers and n jobs with cost matrix C[i][j],
assign each worker to exactly one job to MINIMIZE total cost.

This is the ASSIGNMENT PROBLEM — solved by Hungarian Algorithm.

═══════════════════════════════════════════════════════════════════
ALGORITHM (O(n³) — Competitive Programming version)
═══════════════════════════════════════════════════════════════════

Uses potential function approach:
1. For each row (worker), try to find an augmenting path
   in the "equality subgraph"
2. If stuck, adjust potentials (dual variables) to create new edges
3. Repeat until perfect matching found

═══════════════════════════════════════════════════════════════════
DRY RUN (3×3 cost matrix)
═══════════════════════════════════════════════════════════════════

Cost matrix:
     Job1 Job2 Job3
W1 [  9    2    7  ]
W2 [  6    4    3  ]
W3 [  5    8    1  ]

Optimal: W1→Job2(2), W2→Job1(6), W3→Job3(1) = 9
Or:      W1→Job2(2), W2→Job3(3), W3→Job1(5) = 10
Best = 9

═══════════════════════════════════════════════════════════════════
COMPLEXITY
  Time:  O(n³)    Space: O(n²)
═══════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vector<T>>;
constexpr i64 INF64 = 4e18;
#define nl '\n'

// Hungarian Algorithm O(n³)
// Finds min-cost perfect matching in n×n cost matrix
// For max cost: negate all values
struct Hungarian {
    int n;
    vvec<i64> cost;
    vec<i64> u, v; // potentials
    vec<int> matchL, matchR;

    Hungarian(int n) : n(n), cost(n, vec<i64>(n)), u(n+1), v(n+1),
                       matchL(n+1, -1), matchR(n+1, -1) {}

    i64 solve() {
        // 1-indexed internally for cleaner code
        // cost[i][j] is 0-indexed

        u.assign(n+1, 0);
        v.assign(n+1, 0);
        matchL.assign(n+1, 0); // matchL[i] = job assigned to worker i
        matchR.assign(n+1, 0); // matchR[j] = worker assigned to job j

        for (int i = 1; i <= n; i++) {
            vec<i64> dist(n+1, INF64);
            vec<bool> used(n+1, false);
            vec<int> prev(n+1, 0);

            matchR[0] = i;
            int j0 = 0;

            do {
                used[j0] = true;
                int i0 = matchR[j0], j1 = 0;
                i64 delta = INF64;

                for (int j = 1; j <= n; j++) {
                    if (used[j]) continue;
                    i64 cur = cost[i0-1][j-1] - u[i0] - v[j];
                    if (cur < dist[j]) {
                        dist[j] = cur;
                        prev[j] = j0;
                    }
                    if (dist[j] < delta) {
                        delta = dist[j];
                        j1 = j;
                    }
                }

                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        u[matchR[j]] += delta;
                        v[j] -= delta;
                    } else {
                        dist[j] -= delta;
                    }
                }

                j0 = j1;
            } while (matchR[j0] != 0);

            // Update matching along augmenting path
            do {
                int j1 = prev[j0];
                matchR[j0] = matchR[j1];
                j0 = j1;
            } while (j0);
        }

        // Total cost
        i64 result = 0;
        for (int j = 1; j <= n; j++) {
            if (matchR[j] != 0) {
                result += cost[matchR[j]-1][j-1];
            }
        }

        return result;
    }

    // Get assignment: returns assignment[worker] = job (0-indexed)
    vec<int> getAssignment() {
        vec<int> assignment(n);
        for (int j = 1; j <= n; j++) {
            if (matchR[j] != 0) {
                assignment[matchR[j]-1] = j-1;
            }
        }
        return assignment;
    }
};

void solve() {
    int n;
    cin >> n;

    Hungarian hung(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> hung.cost[i][j];

    i64 minCost = hung.solve();
    cout << "Minimum assignment cost: " << minCost << nl;

    auto assignment = hung.getAssignment();
    cout << "Assignment:" << nl;
    for (int i = 0; i < n; i++) {
        cout << "  Worker " << i+1 << " → Job " << assignment[i]+1
             << " (cost=" << hung.cost[i][assignment[i]] << ")" << nl;
    }
}

/*
Input: 1\n3\n9 2 7\n6 4 3\n5 8 1
Output:
Minimum assignment cost: 9
Assignment:
  Worker 1 → Job 2 (cost=2)
  Worker 2 → Job 1 (cost=6)
  Worker 3 → Job 3 (cost=1)
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC; while (TC--) solve();
}

