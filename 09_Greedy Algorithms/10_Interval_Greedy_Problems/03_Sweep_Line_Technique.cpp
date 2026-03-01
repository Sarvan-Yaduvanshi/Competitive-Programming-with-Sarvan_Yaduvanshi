/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sweep Line Technique
 *  Level   : Expert
 * ============================================================================
 *
 *  ▶ WHAT IS SWEEP LINE?
 *  ─────────────────────
 *  A technique where we process EVENTS (interval starts/ends) in sorted order,
 *  maintaining a running state. Think of a vertical line sweeping left-to-right.
 *
 *  ▶ EVENT TYPES:
 *  1. +1 at start, -1 at end → count overlapping intervals
 *  2. Open/close events → track active intervals
 *  3. Point events + interval events → mixed queries
 *
 *  ▶ APPLICATIONS:
 *  - Maximum overlapping intervals (min platforms)
 *  - Rectangle union area
 *  - Skyline problem
 *  - Calendar booking
 *  - Employee free time
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

// ============================================================================
// Skyline Problem (LC 218) — Sweep Line + Max-Heap
// ============================================================================
vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    // Create events: (x, type, height)
    // type: 0 = building start (negate height for max-heap trick), 1 = building end
    vector<pair<int, int>> events;
    for (auto& b : buildings) {
        events.push_back({b[0], -b[2]}); // Start: negative height
        events.push_back({b[1], b[2]});   // End: positive height
    }

    // Sort: by x, then starts before ends, then taller starts first
    sort(events.begin(), events.end());

    multiset<int, greater<int>> activeHeights;
    activeHeights.insert(0); // Ground level
    int prevMax = 0;

    vector<vector<int>> result;

    for (auto& [x, h] : events) {
        if (h < 0) {
            activeHeights.insert(-h); // Building starts
        } else {
            activeHeights.erase(activeHeights.find(h)); // Building ends
        }

        int curMax = *activeHeights.begin();
        if (curMax != prevMax) {
            result.push_back({x, curMax});
            prevMax = curMax;
        }
    }
    return result;
}

// ============================================================================
// My Calendar I (LC 729) — Sweep line with TreeMap
// ============================================================================
class MyCalendar {
    map<int, int> events; // Sweep line: +1 at start, -1 at end
    // For non-overlapping, just check if interval is free
    map<int, int> bookings; // {start -> end}
public:
    bool book(int start, int end) {
        auto it = bookings.lower_bound(start);
        // Check overlap with next booking
        if (it != bookings.end() && it->first < end) return false;
        // Check overlap with previous booking
        if (it != bookings.begin()) {
            --it;
            if (it->second > start) return false;
        }
        bookings[start] = end;
        return true;
    }
};

// ============================================================================
// Employee Free Time (LC 759) — Merge all intervals, find gaps
// ============================================================================
vector<vector<int>> employeeFreeTime(vector<vector<vector<int>>>& schedule) {
    vector<vector<int>> all;
    for (auto& emp : schedule)
        for (auto& iv : emp)
            all.push_back(iv);

    sort(all.begin(), all.end());

    vector<vector<int>> result;
    int maxEnd = all[0][1];

    for (int i = 1; i < (int)all.size(); i++) {
        if (all[i][0] > maxEnd) {
            result.push_back({maxEnd, all[i][0]});
        }
        maxEnd = max(maxEnd, all[i][1]);
    }
    return result;
}

int main() {
    // Skyline
    vector<vector<int>> buildings = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    auto skyline = getSkyline(buildings);
    cout << "Skyline: ";
    for (auto& p : skyline) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    // Calendar
    MyCalendar cal;
    cout << "Book [10,20): " << cal.book(10, 20) << endl; // 1
    cout << "Book [15,25): " << cal.book(15, 25) << endl; // 0
    cout << "Book [20,30): " << cal.book(20, 30) << endl; // 1

    return 0;
}

