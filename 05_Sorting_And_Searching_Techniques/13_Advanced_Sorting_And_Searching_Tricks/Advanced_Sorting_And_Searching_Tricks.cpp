/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 13 — ADVANCED SORTING & SEARCHING TRICKS                 ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Sweep Line
 2.  Offline Queries + Sorting
 3.  Mo's Algorithm (Value Sorting Idea)
 4.  Meet in the Middle
 5.  Coordinate Compression + BIT
 6.  Parallel Binary Search
 7.  Fractional Cascading
 8.  Convex Hull Trick Search
 9.  Aliens Trick (Lambda Optimization)

OVERVIEW:
─────────
These are GRANDMASTER-level techniques that combine sorting, searching,
and data structures in creative ways. Each one solves a class of problems
that simpler methods cannot handle efficiently.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <cmath>
#include <climits>
#include <map>
#include <set>
#include <deque>
#include <functional>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: SWEEP LINE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Sweep Line processes events in sorted order (usually by x-coordinate
 or time). As we "sweep" across events, we maintain a data structure
 that tracks active elements.

 PATTERN:
   1. Convert problem into events
   2. Sort events by coordinate/time
   3. Process events left-to-right, maintaining active set

 APPLICATIONS:
   • Max overlapping intervals → event sweep
   • Interval scheduling / coloring
   • Rectangle union area
   • Closest pair of points
   • Line segment intersection
*/

// Max overlapping intervals (Meeting Rooms)
int maxOverlapping(vector<pair<int, int>>& intervals) {
    vector<pair<int, int>> events; // (time, type): +1 start, -1 end
    for (auto& [s, e] : intervals) {
        events.push_back({s, +1});
        events.push_back({e, -1});
    }
    sort(events.begin(), events.end());

    int maxActive = 0, active = 0;
    for (auto& [t, type] : events) {
        active += type;
        maxActive = max(maxActive, active);
    }
    return maxActive;
}

// Points covered by at least one interval
int pointsCovered(vector<pair<int, int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end());

    int total = 0;
    int start = intervals[0].first, end = intervals[0].second;
    for (int i = 1; i < (int)intervals.size(); i++) {
        if (intervals[i].first <= end) {
            end = max(end, intervals[i].second);
        } else {
            total += (end - start);
            start = intervals[i].first;
            end = intervals[i].second;
        }
    }
    total += (end - start);
    return total;
}

// Skyline problem concept: Find max height at each x
vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> events; // (x, height) — negative height for start
    for (auto& b : buildings) {
        events.push_back({b[0], -b[2]}); // Building start
        events.push_back({b[1], b[2]});  // Building end
    }
    sort(events.begin(), events.end());

    vector<pair<int, int>> result;
    multiset<int> activeHeights = {0};
    int prevMax = 0;

    for (auto& [x, h] : events) {
        if (h < 0) activeHeights.insert(-h);      // Building starts
        else activeHeights.erase(activeHeights.find(h)); // Building ends

        int curMax = *activeHeights.rbegin();
        if (curMax != prevMax) {
            result.push_back({x, curMax});
            prevMax = curMax;
        }
    }
    return result;
}

void demo_sweep_line() {
    cout << "=== SECTION 1: SWEEP LINE ===" << endl;

    vector<pair<int, int>> intervals = {{1, 5}, {2, 6}, {4, 8}, {7, 9}};
    cout << "Max overlapping: " << maxOverlapping(intervals) << endl; // 3

    cout << "Points covered: " << pointsCovered(intervals) << endl;

    // Skyline
    vector<vector<int>> buildings = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}};
    auto skyline = getSkyline(buildings);
    cout << "Skyline: ";
    for (auto& [x, h] : skyline) cout << "(" << x << "," << h << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: OFFLINE QUERIES + SORTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When we have multiple queries on an array, we can sometimes
 answer them more efficiently by sorting the queries.

 PATTERN:
   1. Read all queries
   2. Sort queries by some criterion
   3. Process queries in sorted order
   4. Store answers, output in original order

 EXAMPLES:
   • Sort queries by right endpoint → process with BIT
   • Sort queries by value → answer while sweeping through sorted values
   • Sort queries by block (Mo's algorithm)

 WHY IT WORKS:
   Processing queries in sorted order allows maintaining a running
   state that can be updated incrementally.
*/

// Example: For each query [L, R], count distinct elements
// Offline approach: Sort queries by R, sweep with BIT
struct Query {
    int l, r, idx;
};

// Count distinct in ranges using offline + BIT
vector<int> countDistinct(vector<int>& arr, vector<Query>& queries) {
    int n = arr.size(), q = queries.size();

    // Sort queries by right endpoint
    sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        return a.r < b.r;
    });

    // BIT for point updates and prefix sum queries
    vector<int> bit(n + 2, 0);
    auto update = [&](int i, int val) {
        for (i++; i <= n; i += i & (-i)) bit[i] += val;
    };
    auto query_prefix = [&](int i) -> int {
        int sum = 0;
        for (i++; i > 0; i -= i & (-i)) sum += bit[i];
        return sum;
    };

    map<int, int> lastSeen; // value → last index
    vector<int> answers(q);
    int j = 0;

    for (int i = 0; i < n && j < q; i++) {
        // Update: if arr[i] was seen before, remove old position
        if (lastSeen.count(arr[i])) {
            update(lastSeen[arr[i]], -1);
        }
        lastSeen[arr[i]] = i;
        update(i, 1);

        // Answer all queries with r == i
        while (j < q && queries[j].r == i) {
            answers[queries[j].idx] = query_prefix(queries[j].r) -
                                       (queries[j].l > 0 ? query_prefix(queries[j].l - 1) : 0);
            j++;
        }
    }
    return answers;
}

void demo_offline_queries() {
    cout << "=== SECTION 2: OFFLINE QUERIES + SORTING ===" << endl;

    vector<int> arr = {1, 2, 1, 3, 2, 1};
    vector<Query> queries = {{0, 3, 0}, {1, 4, 1}, {2, 5, 2}};

    auto answers = countDistinct(arr, queries);
    for (int i = 0; i < (int)answers.size(); i++) {
        cout << "Query " << i << " [" << queries[i].l << "," << queries[i].r
             << "]: " << answers[i] << " distinct" << endl;
    }

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MO'S ALGORITHM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Mo's Algorithm answers offline range queries in O((N+Q)√N) time.

 KEY IDEA:
   Sort queries by (L/√N, R) — block decomposition.
   Maintain a "current window" [curL, curR].
   Expand/shrink the window to match each query.
   Total movement of L pointer: O(Q√N)
   Total movement of R pointer: O(N√N)

 REQUIREMENTS:
   1. Add element to window: O(1) or O(log n)
   2. Remove element from window: O(1) or O(log n)
   3. Answer query from current window state: O(1)

 APPLICATIONS:
   • Count distinct elements in range
   • Frequency queries in range
   • Xor of range
   • Count of elements with frequency ≥ k
*/

struct MoQuery {
    int l, r, idx;
};

int block_size;

bool moCompare(const MoQuery& a, const MoQuery& b) {
    int block_a = a.l / block_size;
    int block_b = b.l / block_size;
    if (block_a != block_b) return block_a < block_b;
    return (block_a & 1) ? (a.r > b.r) : (a.r < b.r); // Zigzag optimization
}

// Mo's Algorithm: Count distinct elements in range
vector<int> moDistinct(vector<int>& arr, vector<MoQuery>& queries) {
    int n = arr.size(), q = queries.size();
    block_size = max(1, (int)sqrt(n));
    sort(queries.begin(), queries.end(), moCompare);

    vector<int> freq(1000001, 0); // Frequency of each value
    int distinct = 0;
    vector<int> answers(q);

    auto add = [&](int idx) {
        if (freq[arr[idx]]++ == 0) distinct++;
    };
    auto remove = [&](int idx) {
        if (--freq[arr[idx]] == 0) distinct--;
    };

    int curL = 0, curR = -1;
    for (auto& query : queries) {
        while (curR < query.r) add(++curR);
        while (curL > query.l) add(--curL);
        while (curR > query.r) remove(curR--);
        while (curL < query.l) remove(curL++);
        answers[query.idx] = distinct;
    }
    return answers;
}

void demo_mos_algorithm() {
    cout << "=== SECTION 3: MO'S ALGORITHM ===" << endl;

    vector<int> arr = {1, 2, 1, 3, 2, 1, 4};
    vector<MoQuery> queries = {{0, 3, 0}, {1, 5, 1}, {2, 6, 2}, {0, 6, 3}};

    auto answers = moDistinct(arr, queries);
    for (int i = 0; i < (int)queries.size(); i++) {
        // Note: queries reordered, but answers are by original index
        cout << "Query " << i << ": " << answers[i] << " distinct" << endl;
    }

    cout << "Mo's: O((N+Q)√N) time" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: MEET IN THE MIDDLE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Split the problem in half, solve each half, combine results.
 Reduces O(2^n) to O(2^(n/2) * log(2^(n/2))) = O(2^(n/2) * n)

 PATTERN:
   1. Split array into two halves
   2. Generate all subsets/combinations for each half
   3. Sort one half
   4. For each element in the other half, binary search in sorted half

 CLASSIC PROBLEMS:
   • Subset sum closest to target
   • Count subsets with sum = target (when n ≤ 40)
   • 4-sum = 0 using two pair-sums
*/

// Count subsets with sum = target (n ≤ 40)
long long subsetSumCount(vector<int>& arr, long long target) {
    int n = arr.size();
    int half1 = n / 2, half2 = n - half1;

    // Generate all subset sums for first half
    vector<long long> sums1;
    for (int mask = 0; mask < (1 << half1); mask++) {
        long long sum = 0;
        for (int i = 0; i < half1; i++)
            if (mask & (1 << i)) sum += arr[i];
        sums1.push_back(sum);
    }

    // Sort first half's sums
    sort(sums1.begin(), sums1.end());

    // For each subset of second half, binary search in first half
    long long count = 0;
    for (int mask = 0; mask < (1 << half2); mask++) {
        long long sum = 0;
        for (int i = 0; i < half2; i++)
            if (mask & (1 << i)) sum += arr[half1 + i];

        long long need = target - sum;
        // Count occurrences of 'need' in sums1
        count += upper_bound(sums1.begin(), sums1.end(), need)
               - lower_bound(sums1.begin(), sums1.end(), need);
    }
    return count;
}

// Closest subset sum to target
long long closestSubsetSum(vector<int>& arr, long long target) {
    int n = arr.size();
    int half1 = n / 2, half2 = n - half1;

    vector<long long> sums1;
    for (int mask = 0; mask < (1 << half1); mask++) {
        long long sum = 0;
        for (int i = 0; i < half1; i++)
            if (mask & (1 << i)) sum += arr[i];
        sums1.push_back(sum);
    }
    sort(sums1.begin(), sums1.end());

    long long closest = LLONG_MAX;
    for (int mask = 0; mask < (1 << half2); mask++) {
        long long sum = 0;
        for (int i = 0; i < half2; i++)
            if (mask & (1 << i)) sum += arr[half1 + i];

        long long need = target - sum;
        auto it = lower_bound(sums1.begin(), sums1.end(), need);
        if (it != sums1.end())
            closest = min(closest, abs(target - (sum + *it)));
        if (it != sums1.begin()) {
            --it;
            closest = min(closest, abs(target - (sum + *it)));
        }
    }
    return closest;
}

void demo_meet_in_middle() {
    cout << "=== SECTION 4: MEET IN THE MIDDLE ===" << endl;

    vector<int> arr = {3, 7, 1, 8, -2, 4};
    long long target = 12;
    cout << "Subsets with sum " << target << ": " << subsetSumCount(arr, target) << endl;
    cout << "Closest to " << target << " distance: " << closestSubsetSum(arr, target) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: COORDINATE COMPRESSION + BIT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When values are up to 10^9 but count is ≤ 10^5:
   1. Compress coordinates to [0, n-1]
   2. Use BIT/Segment Tree on compressed range

 APPLICATIONS:
   • Count inversions
   • Count elements less than X in prefix
   • Range rank queries
*/

long long countInversions_BIT(vector<int>& arr) {
    int n = arr.size();

    // Coordinate compression
    vector<int> sorted_vals = arr;
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    int m = sorted_vals.size();

    // BIT
    vector<int> bit(m + 1, 0);
    auto update = [&](int i) {
        for (i++; i <= m; i += i & (-i)) bit[i]++;
    };
    auto query = [&](int i) -> int {
        int sum = 0;
        for (i++; i > 0; i -= i & (-i)) sum += bit[i];
        return sum;
    };

    long long inv = 0;
    for (int i = 0; i < n; i++) {
        int compressed = lower_bound(sorted_vals.begin(), sorted_vals.end(), arr[i])
                        - sorted_vals.begin();
        inv += i - query(compressed);
        update(compressed);
    }
    return inv;
}

void demo_compression_bit() {
    cout << "=== SECTION 5: COORD COMPRESSION + BIT ===" << endl;

    vector<int> arr = {1000000000, 3, 500000000, 1, 999999999};
    cout << "Inversions: " << countInversions_BIT(arr) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: PARALLEL BINARY SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When you have Q queries, each needing binary search over time/events,
 and each check requires simulating events:

 NAIVE: Q × log(T) × cost_of_check → Too slow!
 PARALLEL BS: Process all queries' binary searches simultaneously.

 ALGORITHM:
   1. Each query has its own [lo, hi] range
   2. For each "round":
      a. Compute mid for each query
      b. Group queries by mid
      c. Simulate events up to each mid, check feasibility
      d. Update lo/hi for each query
   3. After O(log T) rounds, all queries answered

 TIME: O(log(T) × (N + Q) × cost_per_event)

 APPLICATIONS:
   • "When does query i become satisfiable?" for Q queries
   • Dynamic connectivity / threshold problems
*/

// Simplified example: Each query asks "at what time does
// the prefix sum first reach target[i]?"
vector<int> parallelBS(vector<int>& events, vector<int>& targets) {
    int n = events.size(), q = targets.size();
    vector<int> lo(q, 0), hi(q, n - 1), ans(q, -1);

    for (int iter = 0; iter < 20; iter++) { // log(n) iterations
        // Group queries by their mid value
        vector<vector<int>> bucket(n);
        bool done = true;
        for (int i = 0; i < q; i++) {
            if (lo[i] <= hi[i]) {
                int mid = (lo[i] + hi[i]) / 2;
                bucket[mid].push_back(i);
                done = false;
            }
        }
        if (done) break;

        // Simulate events and check queries
        long long prefSum = 0;
        for (int t = 0; t < n; t++) {
            prefSum += events[t];
            for (int qi : bucket[t]) {
                if (prefSum >= targets[qi]) {
                    ans[qi] = t;
                    hi[qi] = (lo[qi] + hi[qi]) / 2 - 1;
                } else {
                    lo[qi] = (lo[qi] + hi[qi]) / 2 + 1;
                }
            }
        }
    }
    return ans;
}

void demo_parallel_bs() {
    cout << "=== SECTION 6: PARALLEL BINARY SEARCH ===" << endl;

    vector<int> events = {3, 1, 4, 1, 5, 9, 2, 6}; // Values added at each time
    vector<int> targets = {5, 10, 20}; // When does prefix sum reach these?

    auto answers = parallelBS(events, targets);
    for (int i = 0; i < (int)targets.size(); i++) {
        cout << "Prefix sum first ≥ " << targets[i] << " at time " << answers[i] << endl;
    }

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: FRACTIONAL CASCADING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Fractional Cascading speeds up binary search across multiple sorted lists.

 PROBLEM: Given k sorted lists, search for x in ALL of them.
   Naive: O(k log n) — binary search each list
   Fractional Cascading: O(k + log n)

 IDEA:
   Build augmented lists by merging every other element from list[i+1]
   into list[i]. Store pointers between lists.
   After finding position in first list, "cascade" to other lists in O(1) each.

 USED IN:
   • Range tree queries
   • Multi-level data structure searching
   • Theoretical optimization for merge-sort-tree queries

 Note: In competitive programming, this is rarely implemented directly
 but the CONCEPT is important for understanding optimized range queries.
*/

// Simplified 2-list fractional cascading
struct FractionalCascade {
    // Two sorted lists with augmented pointers
    vector<int> list1, list2;
    vector<int> merged;            // Merged augmented list
    vector<int> ptr_to_list2;      // For each merged element, pointer to list2

    void build(vector<int>& l1, vector<int>& l2) {
        list1 = l1;
        list2 = l2;

        // Merge l1 and every other element of l2
        merged.clear();
        ptr_to_list2.clear();
        int i = 0, j = 0;
        while (i < (int)l1.size() || j < (int)l2.size()) {
            if (j >= (int)l2.size() || (i < (int)l1.size() && l1[i] <= l2[j])) {
                merged.push_back(l1[i]);
                ptr_to_list2.push_back(j); // Where this maps in l2
                i++;
            } else {
                if (j % 2 == 0) { // Only every other element
                    merged.push_back(l2[j]);
                    ptr_to_list2.push_back(j);
                }
                j++;
            }
        }
    }

    // Search x in both lists
    pair<int, int> search(int x) {
        // Search in list1 using normal BS
        int pos1 = (int)(lower_bound(list1.begin(), list1.end(), x) - list1.begin());
        // Search in list2 using normal BS (in full implementation, use cascade)
        int pos2 = (int)(lower_bound(list2.begin(), list2.end(), x) - list2.begin());
        return {pos1, pos2};
    }
};

void demo_fractional_cascading() {
    cout << "=== SECTION 7: FRACTIONAL CASCADING ===" << endl;

    vector<int> l1 = {2, 5, 8, 13, 21};
    vector<int> l2 = {3, 7, 11, 17, 23};

    FractionalCascade fc;
    fc.build(l1, l2);

    auto [p1, p2] = fc.search(10);
    cout << "Search 10: position in L1=" << p1 << ", L2=" << p2 << endl;

    cout << "Fractional Cascading: O(k + log n) instead of O(k log n)" << endl;
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: CONVEX HULL TRICK SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Convex Hull Trick (CHT) optimizes DP of the form:
   dp[i] = min/max over j { m[j] * x[i] + b[j] }

 IDEA:
   Each candidate j defines a line y = m[j]*x + b[j].
   We want the line that gives min/max at each query point x.
   Maintain a "convex hull" of lines.
   For sorted queries, O(n) total using deque.
   For arbitrary queries, O(n log n) using binary search on hull.

 WHEN TO USE:
   • DP transition: dp[i] = min(dp[j] + cost(j, i)) where cost
     can be decomposed as m(j) * x(i) + b(j)
   • Slope trick / Li Chao tree (dynamic CHT)

 TWO VARIANTS:
   1. Sorted queries: Use deque, O(n) amortized
   2. Arbitrary queries: Use binary search on hull, O(log n) per query
*/

struct Line {
    long long m, b; // y = mx + b
    long long eval(long long x) { return m * x + b; }
};

// CHT for minimum queries (lines added with decreasing slope)
class ConvexHullTrick {
    deque<Line> hull;

    bool bad(Line l1, Line l2, Line l3) {
        // l2 is unnecessary if intersection of l1,l3 is below l2
        return (double)(l3.b - l1.b) * (l1.m - l2.m) <=
               (double)(l2.b - l1.b) * (l1.m - l3.m);
    }

public:
    void addLine(long long m, long long b) {
        Line l = {m, b};
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull[hull.size() - 1], l))
            hull.pop_back();
        hull.push_back(l);
    }

    // Query minimum at x (queries must be increasing)
    long long queryMin(long long x) {
        while (hull.size() >= 2 && hull[0].eval(x) >= hull[1].eval(x))
            hull.pop_front();
        return hull[0].eval(x);
    }

    // Query minimum at arbitrary x (binary search) O(log n)
    long long queryMinBS(long long x) {
        int lo = 0, hi = (int)hull.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (hull[mid].eval(x) > hull[mid + 1].eval(x)) lo = mid + 1;
            else hi = mid;
        }
        return hull[lo].eval(x);
    }
};

void demo_cht() {
    cout << "=== SECTION 8: CONVEX HULL TRICK ===" << endl;

    ConvexHullTrick cht;
    // Add lines (decreasing slopes for min queries)
    cht.addLine(3, 0);   // y = 3x
    cht.addLine(1, 3);   // y = x + 3
    cht.addLine(-1, 10);  // y = -x + 10

    cout << "Min at x=0: " << cht.queryMinBS(0) << endl;  // min(0, 3, 10) = 0
    cout << "Min at x=2: " << cht.queryMinBS(2) << endl;  // min(6, 5, 8) = 5
    cout << "Min at x=5: " << cht.queryMinBS(5) << endl;  // min(15, 8, 5) = 5

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: ALIENS TRICK (LAMBDA OPTIMIZATION)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Also known as "WQS Binary Search" or "Lagrangian Relaxation".

 PROBLEM: Solve optimization problem with constraint "use exactly k items"
   f(k) = min cost using exactly k items

 If f(k) is CONVEX, we can use the aliens trick:
   1. Add penalty λ for each item used: g(λ) = min_k { f(k) + λ*k }
   2. For each λ, g(λ) is easy to compute (no constraint on k!)
   3. Binary search on λ to find the one that gives exactly k items

 WHY "ALIENS"?
   Named after the IOI problem "Aliens" that popularized this technique.

 REQUIREMENTS:
   • f(k) must be convex (slopes are non-decreasing)
   • You can solve the unconstrained version efficiently
   • Binary search on λ finds the right penalty

 TEMPLATE:
   Binary search on λ:
     For each λ, solve unconstrained problem getting (cost, count)
     If count > k: increase λ (make items more expensive)
     If count < k: decrease λ (make items cheaper)
     If count == k: answer is cost - λ*k
*/

// Example: Select exactly k elements from array to minimize sum of |arr[i] - arr[i+1]|
// after removing n-k elements (simplified concept)
pair<long long, int> solveWithPenalty(vector<int>& arr, long long penalty) {
    // Greedy: Select elements, paying 'penalty' for each selected
    int n = arr.size();
    long long totalCost = 0;
    int selected = 0;

    // Simple greedy: select if benefit > penalty
    // This is a simplified illustration
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        if (arr[i] - penalty > 0) { // Benefit of selecting
            totalCost += arr[i];
            selected++;
        }
    }
    return {totalCost - penalty * selected, selected};
}

void demo_aliens_trick() {
    cout << "=== SECTION 9: ALIENS TRICK ===" << endl;

    cout << "Aliens Trick / WQS Binary Search:" << endl;
    cout << "1. Add penalty λ per item used" << endl;
    cout << "2. Solve unconstrained problem for each λ" << endl;
    cout << "3. Binary search on λ to hit target k" << endl;
    cout << "Reduces constrained optimization to unconstrained + BS" << endl;
    cout << "Time: O(solve(n) × log(V)) where V = value range of λ" << endl;

    // Simplified demonstration
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    int target_k = 3;
    long long lo = 0, hi = 20;
    long long bestCost = 0;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        auto [cost, count] = solveWithPenalty(arr, mid);
        if (count >= target_k) {
            bestCost = cost + mid * target_k;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << "Optimal cost selecting " << target_k << " elements: " << bestCost << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 13: ADVANCED SORTING & SEARCHING TRICKS           ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_sweep_line();
    demo_offline_queries();
    demo_mos_algorithm();
    demo_meet_in_middle();
    demo_compression_bit();
    demo_parallel_bs();
    demo_fractional_cascading();
    demo_cht();
    demo_aliens_trick();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 13 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Merge Intervals (LC 56) — Sweep Line                                   ║
║  2. Meeting Rooms (LC 252/253) — Sweep Line                                ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  3. CSES — Distinct Values Queries (offline + BIT)                         ║
║  4. CF 1353E — K-periodic Garland                                          ║
║  5. The Skyline Problem (LC 218) — Sweep Line                              ║
║  6. SPOJ DQUERY — D-query (Mo's / offline)                                 ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║  7. SPOJ MKTHNUM — Kth Number (merge sort tree)                            ║
║  8. CF 1042D — Petya and Array (offline + BIT)                              ║
║  9. CF 86D — Powerful Array (Mo's Algorithm)                                ║
║ 10. Meet in the Middle problems (CF various)                                ║
║ 11. CSES — Meet in the Middle                                              ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 12. CF 319C — Kalila and Dimna (CHT)                                       ║
║ 13. CF 1083E — Track (parallel BS)                                          ║
║ 14. IOI 2016 Aliens (WQS binary search)                                    ║
║ 15. CF 1515E — Phoenix and Computers (aliens trick)                         ║
║ 16. Li Chao Tree problems                                                  ║
║ 17. CF 868F — Yet Another Minimization (divide & conquer optimization)     ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

