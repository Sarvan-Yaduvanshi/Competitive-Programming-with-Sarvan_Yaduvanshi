/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sweep Line + Geometry Two Pointer (ICPC / Expert Level)
 *  Level   : Hard → GM (Codeforces 1800 → 2400+)
 * ============================================================================
 *
 *  ▶ WHAT IS SWEEP LINE + TWO POINTER?
 *  ────────────────────────────────────
 *  Sweep line is a technique where we process events (starts/ends of intervals,
 *  points, etc.) sorted by one coordinate, and use a data structure (set, multiset,
 *  or two pointers) to track the "active" elements.
 *
 *  When combined with two pointer:
 *  - Sort events by x-coordinate
 *  - Use two pointers to maintain a window of active y-values
 *  - Count/query within the active window
 *
 *  ▶ WHEN TO USE:
 *  ──────────────
 *  ✅ Overlapping intervals / rectangles
 *  ✅ Closest pair of points
 *  ✅ Maximum number of overlapping events
 *  ✅ Geometric problems (line sweep + two pointer on sorted coords)
 *
 *  PROBLEMS:
 *  LC 253  — Meeting Rooms II (min platforms / rooms)
 *            https://leetcode.com/problems/meeting-rooms-ii/
 *  LC 1851 — Minimum Interval to Include Each Query
 *            https://leetcode.com/problems/minimum-interval-to-include-each-query/
 *  LC 218  — The Skyline Problem
 *            https://leetcode.com/problems/the-skyline-problem/
 *  LC 1288 — Remove Covered Intervals (sort + greedy)
 *            https://leetcode.com/problems/remove-covered-intervals/
 *  CF 1409E — Two Platforms (sweep + two pointer, 1800)
 *            https://codeforces.com/problemset/problem/1409/E
 *  CF 1462F — The Treasure of the Segments (sort + two pointer, 1800)
 *            https://codeforces.com/problemset/problem/1462/F
 *  CF 1680E — Moving Chips (sweep + two pointer, 2200)
 *            https://codeforces.com/problemset/problem/1680/E
 *  CLOSEST PAIR — Classical O(N log N) divide & conquer with strip two pointer
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

// ============================================================================
// LC 253: Meeting Rooms II — Sweep Line (Min Platforms)
// ============================================================================
/*
 * Given intervals [start, end], find minimum rooms needed.
 *
 * SWEEP LINE approach:
 * Create events: +1 at start, -1 at end.
 * Sort events. Sweep through, track max active.
 *
 * TWO POINTER approach:
 * Sort starts and ends separately. Two pointer sweep.
 *
 * Time: O(N log N), Space: O(N)
 */
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<int> starts, ends;
    for (auto& iv : intervals) {
        starts.push_back(iv[0]);
        ends.push_back(iv[1]);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int rooms = 0, maxRooms = 0;
    int s = 0, e = 0;

    while (s < (int)starts.size()) {
        if (starts[s] < ends[e]) {
            rooms++;  // New meeting starts before earliest ends
            s++;
        } else {
            rooms--;  // A meeting ends
            e++;
        }
        maxRooms = max(maxRooms, rooms);
    }
    return maxRooms;
}

// ============================================================================
// LC 1288: Remove Covered Intervals — Sort + Greedy Sweep
// ============================================================================
/*
 * Interval [a,b] is "covered" by [c,d] if c ≤ a and b ≤ d.
 * Remove all covered intervals. Return count of remaining.
 *
 * TRICK: Sort by start ascending, then by end DESCENDING.
 * Sweep through, track maxEnd. If current end ≤ maxEnd, it's covered.
 *
 * Time: O(N log N), Space: O(1)
 */
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
    });

    int count = 0, maxEnd = 0;
    for (auto& iv : intervals) {
        if (iv[1] > maxEnd) {
            count++;          // Not covered
            maxEnd = iv[1];
        }
        // Else: iv is covered by a previous interval
    }
    return count;
}

// ============================================================================
// CF 1462F: The Treasure of the Segments — Sort + Two Pointer
// ============================================================================
/*
 * N segments [l, r]. Choose one segment to modify (stretch/shrink) freely.
 * Maximize the number of segments that share at least one common point.
 *
 * REFORMULATION: For each segment [l, r], count how many other segments
 * overlap with [l, r]. The answer is n - min_segments_to_remove.
 *
 * EFFICIENT: Sort all 2N endpoints. For each segment [l, r], count
 * segments that DON'T intersect it: those entirely to the left (end < l)
 * or entirely to the right (start > r). Use binary search or two pointer.
 *
 * Time: O(N log N), Space: O(N)
 */
void solve_CF1462F() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

        // Sort starts and ends separately
        vector<int> starts(l.begin(), l.end());
        vector<int> ends(r.begin(), r.end());
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        int best = 0;
        for (int i = 0; i < n; i++) {
            // Count segments that DON'T overlap with [l[i], r[i]]
            // Segments entirely to the right: start > r[i]
            int rightCount = (int)(starts.end() - upper_bound(starts.begin(), starts.end(), r[i]));
            // Segments entirely to the left: end < l[i]
            int leftCount = (int)(lower_bound(ends.begin(), ends.end(), l[i]) - ends.begin());
            int overlapping = n - leftCount - rightCount;
            best = max(best, overlapping);
        }
        cout << best << "\n";
    }
}

// ============================================================================
// CLOSEST PAIR OF POINTS — Divide & Conquer with Strip Two Pointer
// ============================================================================
/*
 * Classic computational geometry problem.
 * Given N points in 2D, find the pair with minimum Euclidean distance.
 *
 * APPROACH:
 * 1. Sort by x-coordinate.
 * 2. Divide into left and right halves. Recursively find closest in each.
 * 3. d = min(d_left, d_right).
 * 4. STRIP: Points within distance d of the dividing line.
 *    Sort strip by y. For each point, compare with next 6-7 points only!
 *    This is the "two pointer on sorted strip" part.
 *
 * Time: O(N log² N) or O(N log N) with merge sort trick
 *
 * WHY AT MOST 7? In a d×2d rectangle, at most 8 points with pairwise dist ≥ d.
 */
struct Point { double x, y; };

double dist(Point& a, Point& b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double closestPairStrip(vector<Point>& strip, double d) {
    double minDist = d;
    // Sort strip by y-coordinate
    sort(strip.begin(), strip.end(), [](auto& a, auto& b) { return a.y < b.y; });

    int n = strip.size();
    for (int i = 0; i < n; i++) {
        // Only check next 7 points (proven by geometry)
        for (int j = i + 1; j < n && (strip[j].y - strip[i].y) < minDist; j++) {
            minDist = min(minDist, dist(strip[i], strip[j]));
        }
    }
    return minDist;
}

double closestPairUtil(vector<Point>& pts, int lo, int hi) {
    if (hi - lo <= 3) {
        double minD = 1e18;
        for (int i = lo; i < hi; i++)
            for (int j = i + 1; j < hi; j++)
                minD = min(minD, dist(pts[i], pts[j]));
        return minD;
    }

    int mid = lo + (hi - lo) / 2;
    double midX = pts[mid].x;

    double dLeft = closestPairUtil(pts, lo, mid);
    double dRight = closestPairUtil(pts, mid, hi);
    double d = min(dLeft, dRight);

    // Build strip
    vector<Point> strip;
    for (int i = lo; i < hi; i++) {
        if (abs(pts[i].x - midX) < d)
            strip.push_back(pts[i]);
    }

    return min(d, closestPairStrip(strip, d));
}

double closestPair(vector<Point>& pts) {
    sort(pts.begin(), pts.end(), [](auto& a, auto& b) { return a.x < b.x; });
    return closestPairUtil(pts, 0, pts.size());
}

int main() {
    // Meeting Rooms II
    vector<vector<int>> intervals = {{0,30},{5,10},{15,20}};
    cout << "Min rooms: " << minMeetingRooms(intervals) << "\n"; // 2

    // Remove Covered Intervals
    vector<vector<int>> ivs = {{1,4},{3,6},{2,8}};
    cout << "Remaining: " << removeCoveredIntervals(ivs) << "\n"; // 2

    // Closest Pair
    vector<Point> pts = {{2,3},{12,30},{40,50},{5,1},{12,10},{3,4}};
    cout << "Closest pair dist: " << closestPair(pts) << "\n"; // ~1.41

    return 0;
}

