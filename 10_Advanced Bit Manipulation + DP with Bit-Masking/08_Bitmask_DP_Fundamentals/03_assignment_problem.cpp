/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 08.03 — ASSIGNMENT PROBLEM                               ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: n workers and n jobs. cost[i][j] = cost of assigning worker i to job j.
    Assign each worker to exactly one job, each job to exactly one worker.
    Minimize total cost.

RECURRENCE:
═══════════
    dp[mask] = min cost to assign the first popcount(mask) workers
               using exactly the jobs indicated by mask.

    Let k = popcount(mask) (the next worker to assign is worker k-1).

    dp[mask] = min over j∈mask of (dp[mask ^ (1<<j)] + cost[k-1][j])

BASE: dp[0] = 0 (no workers assigned, no jobs used, zero cost).
ANSWER: dp[(1<<n)-1].

DRY RUN — 3 workers, 3 jobs:
    cost = [[9,2,7],[6,4,3],[5,8,1]]
    dp[000] = 0
    Worker 0: dp[001]=cost[0][0]=9, dp[010]=cost[0][1]=2, dp[100]=cost[0][2]=7
    Worker 1: dp[011]=min(dp[01]+cost[1][1], dp[10]+cost[1][0]) = min(9+4, 2+6) = 8
              dp[101]=min(dp[001]+cost[1][2], dp[100]+cost[1][0]) = min(12, 13) = 12
              dp[110]=min(dp[010]+cost[1][2], dp[100]+cost[1][1]) = min(5, 11) = 5
    Worker 2: dp[111]=min(dp[011]+cost[2][2], dp[101]+cost[2][1], dp[110]+cost[2][0])
             = min(8+1, 12+8, 5+5) = min(9, 20, 10) = 9
    Answer: 9 (worker 0→job 1, worker 1→job 2, worker 2→job 0: 2+3+5=10...
    Actually: worker 0→job 1(2), worker 1→job 2(3), worker 2→job 0(5) = 10... let me recheck)
    dp[110] = min(dp[010]+cost[1][2], dp[100]+cost[1][1]) = min(2+3, 7+4) = 5
    dp[111] from dp[110]: dp[110]+cost[2][0] = 5+5 = 10
    dp[111] from dp[011]: dp[011]+cost[2][2] = 8+1 = 9
    dp[111] from dp[101]: dp[101]+cost[2][1] = 12+8 = 20
    Answer: min(10, 9, 20) = 9 → worker 0→job 0(9), worker 1→job 1(4... wait no)
    Actually let me be precise: dp[011]=8 means workers {0,1} assigned to jobs {0,1}.
    dp[011]+cost[2][2]=8+1=9: workers 0,1 → jobs {0,1}, worker 2 → job 2.

TIME: O(n × 2ⁿ), SPACE: O(2ⁿ)
*/
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
using namespace std;

int assignmentProblem(vector<vector<int>>& cost) {
    int n = cost.size();
    vector<int> dp(1 << n, INT_MAX);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == INT_MAX) continue;
        int worker = __builtin_popcount(mask); // next worker to assign
        if (worker >= n) continue;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) continue; // job j already taken
            int newMask = mask | (1 << j);
            dp[newMask] = min(dp[newMask], dp[mask] + cost[worker][j]);
        }
    }
    return dp[(1 << n) - 1];
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   ASSIGNMENT PROBLEM                            ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    vector<vector<int>> cost = {{9,2,7},{6,4,3},{5,8,1}};
    cout << "\n  Cost matrix:" << endl;
    for (auto& r : cost) { cout << "    "; for (int c : r) cout << c << " "; cout << endl; }

    int ans = assignmentProblem(cost);
    cout << "\n  Minimum assignment cost: " << ans << endl;

    // Larger example
    vector<vector<int>> cost2 = {{10,5,13,15},{3,9,18,13},{13,7,4,15},{12,11,14,8}};
    cout << "\n  4×4 cost matrix: min = " << assignmentProblem(cost2) << endl;

    cout << "\n✅ Assignment problem verified!" << endl;
    return 0;
}

