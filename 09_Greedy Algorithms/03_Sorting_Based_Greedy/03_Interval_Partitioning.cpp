/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Interval Partitioning — Minimum Rooms / Resources
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given N intervals, find the minimum number of rooms/resources
 *           needed so that all intervals can be scheduled (no two in same room overlap).
 *
 *  This equals the MAXIMUM NUMBER OF OVERLAPPING INTERVALS at any point.
 *
 *  APPROACH 1: Sweep Line — O(N log N)
 *  APPROACH 2: Sort + Min-Heap — O(N log N)
 *
 *  APPLICATIONS: Meeting Rooms II (LC 253), Minimum Platforms (GFG/Railway)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// APPROACH 1: Sweep Line (Event-based)
int minRoomsSweep(vector<vector<int>>& intervals) {
    vector<pair<int,int>> events;
    for (auto& iv : intervals) {
        events.push_back({iv[0], +1}); // start → +1
        events.push_back({iv[1], -1}); // end   → -1
    }
    sort(events.begin(), events.end());

    int maxRooms = 0, current = 0;
    for (auto& [time, delta] : events) {
        current += delta;
        maxRooms = max(maxRooms, current);
    }
    return maxRooms;
}

// APPROACH 2: Sort + Min-Heap
int minRoomsHeap(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end()); // Sort by start time
    priority_queue<int, vector<int>, greater<int>> pq; // Min-heap of end times

    for (auto& iv : intervals) {
        if (!pq.empty() && pq.top() <= iv[0]) {
            pq.pop(); // Reuse a room
        }
        pq.push(iv[1]);
    }
    return pq.size();
}

int main() {
    vector<vector<int>> intervals = {{0,30}, {5,10}, {15,20}};
    cout << "Sweep: " << minRoomsSweep(intervals) << " rooms" << endl; // 2
    cout << "Heap:  " << minRoomsHeap(intervals) << " rooms" << endl;  // 2
    return 0;
}

