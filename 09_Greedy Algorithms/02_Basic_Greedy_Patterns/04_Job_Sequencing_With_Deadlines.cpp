/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Job Sequencing with Deadlines
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given N jobs, each with a deadline d[i] and profit p[i].
 *           Each job takes 1 unit of time. Maximize total profit.
 *           A job must be completed before its deadline.
 *
 *  APPROACH 1: Sort by profit (descending) + slot assignment — O(N²)
 *  APPROACH 2: Sort by profit (descending) + DSU for slot finding — O(N α(N))
 *
 *  KEY INSIGHT: Always try to schedule the most profitable job first.
 *  For each job, assign it to the latest available slot ≤ deadline.
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// APPROACH 1: Brute Force Slot Assignment — O(N * maxDeadline)
pair<int,int> jobSequencingBrute(vector<pair<int,int>>& jobs) {
    // jobs[i] = {deadline, profit}
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a.second > b.second; // Sort by profit descending
    });

    int maxDeadline = 0;
    for (auto& [d, p] : jobs) maxDeadline = max(maxDeadline, d);

    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0, count = 0;

    for (auto& [deadline, profit] : jobs) {
        // Find latest available slot ≤ deadline
        for (int j = deadline; j >= 1; j--) {
            if (!slot[j]) {
                slot[j] = true;
                totalProfit += profit;
                count++;
                break;
            }
        }
    }
    return {count, totalProfit};
}

// APPROACH 2: DSU-Optimized — O(N log N + N α(N))
class DSU {
    vector<int> parent;
public:
    DSU(int n) : parent(n + 1) { iota(parent.begin(), parent.end(), 0); }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) { parent[find(x)] = find(y); }
};

pair<int,int> jobSequencingDSU(vector<pair<int,int>>& jobs) {
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    int maxDeadline = 0;
    for (auto& [d, p] : jobs) maxDeadline = max(maxDeadline, d);

    DSU dsu(maxDeadline);
    int totalProfit = 0, count = 0;

    for (auto& [deadline, profit] : jobs) {
        int slot = dsu.find(min(deadline, maxDeadline));
        if (slot > 0) {
            totalProfit += profit;
            count++;
            dsu.unite(slot, slot - 1); // Mark slot as used
        }
    }
    return {count, totalProfit};
}

int main() {
    vector<pair<int,int>> jobs = {{4,20}, {1,10}, {1,40}, {1,30}};

    auto [cnt1, profit1] = jobSequencingBrute(jobs);
    cout << "Brute: " << cnt1 << " jobs, profit = " << profit1 << endl;

    auto [cnt2, profit2] = jobSequencingDSU(jobs);
    cout << "DSU:   " << cnt2 << " jobs, profit = " << profit2 << endl;

    return 0;
}

