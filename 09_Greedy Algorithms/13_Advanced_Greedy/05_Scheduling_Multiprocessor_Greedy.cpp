/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Multiprocessor Scheduling — LPT, SPT, Load Balancing
 *  Level   : Grandmaster
 * ============================================================================
 *
 *  ▶ SCHEDULING ON MULTIPLE MACHINES:
 *  ──────────────────────────────────
 *
 *  PROBLEM: Assign N jobs to K identical machines to minimize makespan
 *  (maximum completion time across all machines).
 *
 *  GREEDY STRATEGIES:
 *
 *  1. LPT (Longest Processing Time First):
 *     Sort jobs descending by duration. Assign each to the machine
 *     with the LEAST total load.
 *     Approximation ratio: 4/3 - 1/(3K) ≈ 1.33× optimal
 *
 *  2. SPT (Shortest Processing Time First):
 *     Used for minimizing TOTAL completion time (sum of finish times).
 *
 *  3. ROUND-ROBIN:
 *     Assign jobs in round-robin order. Simple but not optimal.
 *
 *  4. LIST SCHEDULING:
 *     Process jobs in given order, assign to least-loaded machine.
 *     Approximation ratio: 2 - 1/K
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ============================================================================
// LPT Scheduling — Minimize makespan on K machines
// ============================================================================
int lptScheduling(vector<int>& jobs, int k) {
    sort(jobs.rbegin(), jobs.rend()); // Longest first

    // Min-heap of machine loads
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++) pq.push(0);

    for (int j : jobs) {
        int minLoad = pq.top(); pq.pop();
        pq.push(minLoad + j);
    }

    // Makespan = maximum load
    int makespan = 0;
    while (!pq.empty()) {
        makespan = max(makespan, pq.top());
        pq.pop();
    }
    return makespan;
}

// ============================================================================
// SPT Scheduling — Minimize total completion time on 1 machine
// ============================================================================
long long sptScheduling(vector<int>& jobs) {
    sort(jobs.begin(), jobs.end()); // Shortest first

    long long totalCompletion = 0, currentTime = 0;
    for (int j : jobs) {
        currentTime += j;
        totalCompletion += currentTime;
    }
    return totalCompletion;
}

// ============================================================================
// Load Balancing — Assign to minimize max load (same as LPT for identical)
// With DIFFERENT machine speeds: more complex, often BS+Greedy
// ============================================================================

int main() {
    // LPT
    vector<int> jobs = {6, 3, 5, 4, 2, 1, 7, 8};
    cout << "LPT makespan (k=3): " << lptScheduling(jobs, 3) << endl;
    // Sorted: 8,7,6,5,4,3,2,1. Machines: M1=8+4=12, M2=7+5=12, M3=6+3+2+1=12 → 12

    // SPT
    vector<int> jobs2 = {3, 1, 2};
    cout << "SPT total completion: " << sptScheduling(jobs2) << endl;
    // Sorted: 1,2,3. Completions: 1,3,6. Total=10

    return 0;
}

