/*
╔══════════════════════════════════════════════════════════════════════════════╗
║       02 — SWEEP LINE + HEAP & EVENT SIMULATION                              ║
║           From Zero to Grandmaster — Advanced Competitive Patterns          ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Meeting Rooms II (LC 253) — Sweep Line + Min Heap
 2. The Skyline Problem (LC 218) — Sweep Line + Max Heap
 3. Event Simulation using Heap
 4. Offline Query + Heap

SWEEP LINE + PRIORITY QUEUE:
────────────────────────────
  A powerful technique combining:
    - Events at specific time points (sweep line)
    - Dynamic set maintenance (priority queue)

  Pattern:
  1. Create events (start/end points)
  2. Sort events by position/time
  3. Process events left-to-right, maintaining a PQ of active elements

MEETING ROOMS II (LC 253):
─────────────────────────
  Given intervals, find the minimum number of conference rooms needed.

  DRY RUN: [[0,30],[5,10],[15,20]]
  Events: (0,start), (5,start), (10,end), (15,start), (20,end), (30,end)

  Alternatively: Min heap of end times.
  Sort by start time. For each meeting:
    If heap.top() ≤ start → can reuse room (pop and push new end)
    Else → need new room (push end)

  ┌─────────────────────────────────────────────────────────┐
  │  Time: 0     5    10    15    20    30                  │
  │  Room1: ─────────────────────────────── [0,30]          │
  │  Room2:      ─────── [5,10]                             │
  │  Room2:                     ────── [15,20] (reused!)    │
  │                                                         │
  │  Max rooms at any time: 2                               │
  └─────────────────────────────────────────────────────────┘

SKYLINE PROBLEM (LC 218):
────────────────────────
  Given buildings [left, right, height], output skyline contour.

  Events: For each building, create (left, -height, right) and (right, 0, 0)
  Sort events. Maintain max heap of active building heights.
  When max height changes → add to skyline.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// MEETING ROOMS II (LC 253)
// ═══════════════════════════════════════════════════════════════

int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;

    sort(intervals.begin(), intervals.end());

    // Min heap of end times (earliest ending room on top)
    priority_queue<int, vector<int>, greater<int>> endTimes;
    endTimes.push(intervals[0][1]);

    for (int i = 1; i < (int)intervals.size(); i++) {
        // If earliest ending room is free
        if (endTimes.top() <= intervals[i][0]) {
            endTimes.pop();  // Reuse room
        }
        endTimes.push(intervals[i][1]);
    }

    return endTimes.size();
}

// Alternative: Sweep Line approach
int minMeetingRoomsSweep(vector<vector<int>>& intervals) {
    vector<pair<int,int>> events;
    for (auto& iv : intervals) {
        events.push_back({iv[0], 1});   // Start: +1 room
        events.push_back({iv[1], -1});  // End: -1 room
    }
    sort(events.begin(), events.end());

    int rooms = 0, maxRooms = 0;
    for (auto& [time, delta] : events) {
        rooms += delta;
        maxRooms = max(maxRooms, rooms);
    }
    return maxRooms;
}

// ═══════════════════════════════════════════════════════════════
// SKYLINE PROBLEM (LC 218)
// ═══════════════════════════════════════════════════════════════
/*
  DRY RUN: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]

  Events sorted:
  (2,-10,9), (3,-15,7), (5,-12,12), (7,0,0), (9,0,0), (12,0,0),
  (15,-10,20), (19,-8,24), (20,0,0), (24,0,0)

  Skyline output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
*/

vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    // Events: (x, type, height)
    // Start event: (left, -height, right)  (negative for start)
    // End event: (right, 0, 0)
    vector<tuple<int,int,int>> events;
    for (auto& b : buildings) {
        events.push_back({b[0], -b[2], b[1]});  // Start
        events.push_back({b[1], 0, 0});          // End
    }
    sort(events.begin(), events.end());

    // Max multiset of active heights (supports duplicate heights)
    multiset<int> heights = {0};  // Ground level
    // Map from right boundary to height (for removal)
    priority_queue<pair<int,int>> maxH;  // (height, right_boundary)

    // Simpler approach using multiset:
    // Actually let me use the clean multiset approach:
    vector<pair<int,int>> allEvents;
    for (auto& b : buildings) {
        allEvents.push_back({b[0], -b[2]});  // Start: negative height
        allEvents.push_back({b[1], b[2]});   // End: positive height
    }
    sort(allEvents.begin(), allEvents.end());

    multiset<int, greater<int>> activeHeights;
    activeHeights.insert(0);

    vector<vector<int>> result;
    int prevMax = 0;

    int i = 0, n = allEvents.size();
    while (i < n) {
        int curX = allEvents[i].first;
        // Process all events at same x
        while (i < n && allEvents[i].first == curX) {
            int h = allEvents[i].second;
            if (h < 0) {
                activeHeights.insert(-h);  // Building starts
            } else {
                activeHeights.erase(activeHeights.find(h));  // Building ends
            }
            i++;
        }
        int curMax = *activeHeights.begin();
        if (curMax != prevMax) {
            result.push_back({curX, curMax});
            prevMax = curMax;
        }
    }
    return result;
}

// ═══════════════════════════════════════════════════════════════
// MAXIMUM NUMBER OF EVENTS (LC 1353) — Greedy + Heap
// ═══════════════════════════════════════════════════════════════
/*
  Attend at most one event per day. Maximize total events attended.
  events[i] = [startDay, endDay]

  Greedy: Process day by day.
  Sort by start day. For each day:
    1. Add all events starting today to min-heap (by end day)
    2. Remove expired events from heap
    3. Attend the event ending soonest (greedy)
*/

int maxEvents(vector<vector<int>>& events) {
    sort(events.begin(), events.end());

    priority_queue<int, vector<int>, greater<int>> pq;  // Min heap of end days
    int i = 0, n = events.size(), attended = 0;
    int day = 1;

    while (i < n || !pq.empty()) {
        if (pq.empty() && i < n) day = events[i][0];

        // Add all events starting on this day
        while (i < n && events[i][0] <= day) {
            pq.push(events[i][1]);
            i++;
        }

        // Remove expired events
        while (!pq.empty() && pq.top() < day) pq.pop();

        // Attend the event ending soonest
        if (!pq.empty()) {
            pq.pop();
            attended++;
        }
        day++;
    }
    return attended;
}

// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  SWEEP LINE + HEAP & EVENT SIMULATION                    ║\n";
    cout << "║  Author: Sarvan Yaduvanshi                               ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n\n";

    // Meeting Rooms II
    cout << "═══ MEETING ROOMS II (LC 253) ═══\n";
    vector<vector<int>> m1 = {{0,30},{5,10},{15,20}};
    cout << "  [[0,30],[5,10],[15,20]] → " << minMeetingRooms(m1) << " rooms\n";
    cout << "  (sweep line) → " << minMeetingRoomsSweep(m1) << " rooms\n\n";

    // Skyline
    cout << "═══ SKYLINE PROBLEM (LC 218) ═══\n";
    vector<vector<int>> b1 = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    auto sky = getSkyline(b1);
    cout << "  Skyline: [";
    for (int i = 0; i < (int)sky.size(); i++) {
        cout << "[" << sky[i][0] << "," << sky[i][1] << "]";
        if (i+1<(int)sky.size()) cout << ",";
    }
    cout << "]\n\n";

    // Max Events
    cout << "═══ MAXIMUM EVENTS (LC 1353) ═══\n";
    vector<vector<int>> e1 = {{1,2},{2,3},{3,4}};
    cout << "  [[1,2],[2,3],[3,4]] → " << maxEvents(e1) << " events\n";
    vector<vector<int>> e2 = {{1,2},{2,3},{3,4},{1,2}};
    cout << "  [[1,2],[2,3],[3,4],[1,2]] → " << maxEvents(e2) << " events\n";

    cout << "\n═══════════════════════════════════════════════════════════\n";
    cout << "PRACTICE:\n";
    cout << "  LC 253  — Meeting Rooms II\n";
    cout << "  LC 218  — The Skyline Problem\n";
    cout << "  LC 1353 — Maximum Number of Events\n";
    cout << "  LC 502  — IPO\n";
    cout << "  LC 632  — Smallest Range Covering K Lists\n";
    cout << "═══════════════════════════════════════════════════════════\n";

    return 0;
}

