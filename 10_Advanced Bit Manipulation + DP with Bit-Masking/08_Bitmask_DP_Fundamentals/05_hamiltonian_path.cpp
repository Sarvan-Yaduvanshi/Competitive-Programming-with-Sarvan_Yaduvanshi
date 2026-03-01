/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08.05 — HAMILTONIAN PATH                                 ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Does a Hamiltonian path exist (visit all n vertices exactly once)?
    Count Hamiltonian paths or find one.

RECURRENCE:
═══════════
    dp[mask][i] = number of Hamiltonian paths visiting exactly the vertices in mask
                  and ending at vertex i (where i ∈ mask).

    Transition: dp[mask | (1<<j)][j] += dp[mask][i]  for edge (i,j), j ∉ mask.

    Base: dp[1<<i][i] = 1 for all starting vertices i.

    Answer: Σ dp[(1<<n)-1][i] for all i.

TIME: O(n² × 2ⁿ), SPACE: O(n × 2ⁿ)

PRACTICE PROBLEMS:
══════════════════
    CSES: Hamiltonian Flights
    LeetCode 847: Shortest Path Visiting All Nodes
*/
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long countHamiltonianPaths(int n, vector<vector<bool>>& adj) {
    vector<vector<long long>> dp(1 << n, vector<long long>(n, 0));

    // Base: start at any vertex
    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!dp[mask][i]) continue;
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                if (!adj[i][j]) continue;
                dp[mask | (1 << j)][j] += dp[mask][i];
            }
        }
    }

    int fullMask = (1 << n) - 1;
    long long total = 0;
    for (int i = 0; i < n; i++) total += dp[fullMask][i];
    return total;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   HAMILTONIAN PATH                              ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // Complete graph K4: (4-1)! × 2 = 12... actually 4! = 24 directed paths
    // But since undirected, each is counted twice → 12... actually for directed Hamiltonian paths: 4!/1 = ...
    // In Kn with n vertices, directed Hamiltonian paths = n! (choose any permutation)
    int n = 4;
    vector<vector<bool>> adj(n, vector<bool>(n, true));
    for (int i = 0; i < n; i++) adj[i][i] = false;

    long long count = countHamiltonianPaths(n, adj);
    cout << "  K4: " << count << " directed Hamiltonian paths" << endl;
    // n! = 24 directed paths (each permutation is a path)
    assert(count == 24);

    // Path graph: 0-1-2-3
    vector<vector<bool>> adj2(4, vector<bool>(4, false));
    adj2[0][1] = adj2[1][0] = true;
    adj2[1][2] = adj2[2][1] = true;
    adj2[2][3] = adj2[3][2] = true;
    cout << "  Path 0-1-2-3: " << countHamiltonianPaths(4, adj2) << " paths" << endl;
    assert(countHamiltonianPaths(4, adj2) == 2); // 0→1→2→3 and 3→2→1→0

    cout << "\n✅ Hamiltonian path verified!" << endl;
    return 0;
}

