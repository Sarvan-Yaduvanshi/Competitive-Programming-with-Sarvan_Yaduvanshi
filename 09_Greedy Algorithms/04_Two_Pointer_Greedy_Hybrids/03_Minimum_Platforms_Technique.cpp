/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Minimum Platforms / Event-Based Sweep
 *  Level   : Intermediate
 * ============================================================================
 *
 *  PROBLEM: Given arrival[] and departure[] times of trains at a station,
 *           find the minimum number of platforms needed.
 *
 *  APPROACH 1: Sweep Line — Create events (+1 for arrival, -1 for departure)
 *  APPROACH 2: Sort both arrays independently and use two pointers
 *
 *  TIME: O(N log N)
 *  SPACE: O(N) for sweep, O(1) for two-pointer (after sort)
 *
 *  KEY INSIGHT: This is equivalent to "maximum overlapping intervals at any point"
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// APPROACH 1: Sweep Line
int minPlatformsSweep(vector<int>& arrival, vector<int>& departure) {
    vector<pair<int,int>> events;
    for (int t : arrival) events.push_back({t, +1});
    for (int t : departure) events.push_back({t + 1, -1}); // +1 so departure doesn't conflict with same-time arrival

    sort(events.begin(), events.end());

    int maxPlatforms = 0, current = 0;
    for (auto& [time, delta] : events) {
        current += delta;
        maxPlatforms = max(maxPlatforms, current);
    }
    return maxPlatforms;
}

// APPROACH 2: Sort + Two Pointer
int minPlatformsTwoPointer(vector<int> arrival, vector<int> departure) {
    sort(arrival.begin(), arrival.end());
    sort(departure.begin(), departure.end());

    int i = 0, j = 0, n = arrival.size();
    int platforms = 0, maxPlatforms = 0;

    while (i < n) {
        if (arrival[i] <= departure[j]) {
            platforms++;
            i++;
        } else {
            platforms--;
            j++;
        }
        maxPlatforms = max(maxPlatforms, platforms);
    }
    return maxPlatforms;
}

int main() {
    vector<int> arrival    = {900, 940, 950, 1100, 1500, 1800};
    vector<int> departure  = {910, 1200, 1120, 1130, 1900, 2000};

    cout << "Sweep:       " << minPlatformsSweep(arrival, departure) << endl;     // 3
    cout << "Two Pointer: " << minPlatformsTwoPointer(arrival, departure) << endl; // 3

    return 0;
}

