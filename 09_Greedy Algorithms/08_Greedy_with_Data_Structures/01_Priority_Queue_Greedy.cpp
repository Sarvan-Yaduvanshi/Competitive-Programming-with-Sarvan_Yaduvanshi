/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Priority Queue Greedy Patterns
 *  Level   : Advanced
 * ============================================================================
 *
 *  PATTERN: Use a heap to always pick the "best" available option.
 *  This is the workhorse of greedy + DS problems.
 *
 *  COMMON PATTERNS:
 *  1. TWO-PQ PATTERN: Separate "available" and "locked" items (IPO)
 *  2. REGRET PQ: Add items to PQ, replace worst choice if better found
 *  3. EVENT PQ: Process events in order, use PQ for best decision
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 502: IPO — Two Priority Queue Greedy
// Maximize capital after at most k investments
// ============================================================================
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    vector<pair<int,int>> projects(n);
    for (int i = 0; i < n; i++) projects[i] = {capital[i], profits[i]};
    sort(projects.begin(), projects.end()); // Sort by capital required

    priority_queue<int> maxPQ; // Available profits
    int idx = 0;

    for (int i = 0; i < k; i++) {
        // Unlock all projects we can afford
        while (idx < n && projects[idx].first <= w) {
            maxPQ.push(projects[idx].second);
            idx++;
        }
        if (maxPQ.empty()) break;
        w += maxPQ.top(); maxPQ.pop(); // Pick most profitable
    }
    return w;
}

// ============================================================================
// LC 871: Minimum Refueling Stops — Regret-Based PQ Greedy
// ============================================================================
int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
    // Greedy: Drive as far as possible. When stuck, "retroactively" refuel
    // at the station with the most fuel (using max-heap of passed stations)
    priority_queue<int> maxPQ; // Fuel at passed stations
    int fuel = startFuel, stops = 0, idx = 0;

    while (fuel < target) {
        // Add all reachable stations to PQ
        while (idx < (int)stations.size() && stations[idx][0] <= fuel) {
            maxPQ.push(stations[idx][1]);
            idx++;
        }
        if (maxPQ.empty()) return -1; // Can't reach target
        fuel += maxPQ.top(); maxPQ.pop();
        stops++;
    }
    return stops;
}

// ============================================================================
// LC 630: Course Schedule III — Greedy + PQ (Replace worst)
// ============================================================================
int scheduleCourse(vector<vector<int>>& courses) {
    // Sort by deadline ascending
    sort(courses.begin(), courses.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });

    priority_queue<int> maxPQ; // Durations of taken courses
    int time = 0;

    for (auto& c : courses) {
        int duration = c[0], deadline = c[1];
        time += duration;
        maxPQ.push(duration);

        // If we exceed deadline, remove the longest course (regret)
        if (time > deadline) {
            time -= maxPQ.top(); maxPQ.pop();
        }
    }
    return maxPQ.size();
}

int main() {
    // IPO
    vector<int> profits = {1, 2, 3}, capital = {0, 1, 1};
    cout << "IPO max capital: " << findMaximizedCapital(2, 0, profits, capital) << endl; // 4

    // Refueling
    vector<vector<int>> stations = {{10,60}, {20,30}, {30,30}, {60,40}};
    cout << "Min refuels: " << minRefuelStops(100, 10, stations) << endl; // 2

    // Course Schedule
    vector<vector<int>> courses = {{100,200}, {200,1300}, {1000,1250}, {2000,3200}};
    cout << "Max courses: " << scheduleCourse(courses) << endl; // 3

    return 0;
}

