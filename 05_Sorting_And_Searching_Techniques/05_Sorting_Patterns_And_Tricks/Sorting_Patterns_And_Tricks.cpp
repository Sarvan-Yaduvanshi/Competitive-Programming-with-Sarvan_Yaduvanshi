/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 05 — SORTING PATTERNS & TRICKS                             ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Custom Comparators
 2.  Sort by Multiple Keys
 3.  Pair Sorting & Struct Sorting
 4.  Sorting with Lambda
 5.  Sorting + Greedy
 6.  Sorting + Prefix Sum
 7.  Sorting + Two Pointer
 8.  Sorting by Absolute Difference
 9.  Sorting with Index Preservation
 10. Stable Sort Usage
 11. Partial Sort & nth_element
 12. Order Statistics

OVERVIEW:
─────────
This chapter covers the most IMPORTANT CP patterns involving sorting.
Mastering these patterns will solve 30-40% of competitive programming
problems. These aren't just algorithms — they're THINKING PATTERNS.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <functional>
#include <map>
#include <set>
#include <cmath>
#include <queue>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: CUSTOM COMPARATORS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A comparator defines the ordering for sort(). It must follow
 STRICT WEAK ORDERING:
   1. Irreflexive: comp(a, a) = false
   2. Asymmetric: if comp(a, b), then !comp(b, a)
   3. Transitive: if comp(a, b) and comp(b, c), then comp(a, c)

 COMMON MISTAKE:
   Using <= instead of < → violates irreflexive → UNDEFINED BEHAVIOR!
   WRONG: [](int a, int b) { return a <= b; }  // UB!
   RIGHT: [](int a, int b) { return a < b; }

 WAYS TO DEFINE COMPARATOR:
   1. Function pointer
   2. Functor (class with operator())
   3. Lambda (most common in CP)
   4. operator< overload
   5. std::greater<T> for reverse
*/

// Method 1: Function pointer
bool compareDesc(int a, int b) {
    return a > b;
}

// Method 2: Functor
struct CompareByAbsValue {
    bool operator()(int a, int b) const {
        return abs(a) < abs(b);
    }
};

void demo_custom_comparators() {
    cout << "=== SECTION 1: CUSTOM COMPARATORS ===" << endl;

    vector<int> arr = {-5, 3, -1, 8, -2, 7};

    // Function pointer
    vector<int> v1 = arr;
    sort(v1.begin(), v1.end(), compareDesc);
    cout << "Desc (func ptr): ";
    for (int x : v1) cout << x << " ";
    cout << endl;

    // Functor
    vector<int> v2 = arr;
    sort(v2.begin(), v2.end(), CompareByAbsValue());
    cout << "By |value| (functor): ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    // Lambda
    vector<int> v3 = arr;
    sort(v3.begin(), v3.end(), [](int a, int b) {
        return a % 2 < b % 2; // Even before odd
    });
    cout << "Even first (lambda): ";
    for (int x : v3) cout << x << " ";
    cout << endl;

    // greater<int>
    vector<int> v4 = arr;
    sort(v4.begin(), v4.end(), greater<int>());
    cout << "Desc (greater<>): ";
    for (int x : v4) cout << x << " ";
    cout << endl;

    // Largest Number (LC 179) — Custom string comparator
    vector<int> nums = {3, 30, 34, 5, 9};
    vector<string> strs;
    for (int x : nums) strs.push_back(to_string(x));
    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        return a + b > b + a; // "330" > "303" → 3 before 30
    });
    cout << "Largest Number: ";
    for (auto& s : strs) cout << s;
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: SORT BY MULTIPLE KEYS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Sort by primary key first, then secondary key for ties, etc.

 METHOD 1: Chained comparisons in lambda
   sort by (a, b, c): if a differs → use a; else if b differs → use b; else use c

 METHOD 2: Using std::tie() — elegant and clean
   return tie(a.x, a.y) < tie(b.x, b.y);

 METHOD 3: Using pair/tuple — automatically sorts by all fields

 CP PATTERN:
   Many problems require: "Sort by X ascending, ties by Y descending"
*/

void demo_multi_key_sort() {
    cout << "=== SECTION 2: MULTI-KEY SORT ===" << endl;

    struct Student {
        string name;
        int grade;
        int age;
    };

    vector<Student> students = {
        {"Alice", 85, 20}, {"Bob", 90, 22}, {"Charlie", 85, 19},
        {"Diana", 90, 21}, {"Eve", 85, 20}
    };

    // Sort by grade (asc), then age (asc), then name (asc)
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.grade != b.grade) return a.grade < b.grade;
        if (a.age != b.age) return a.age < b.age;
        return a.name < b.name;
    });
    cout << "By grade→age→name: ";
    for (auto& s : students) cout << s.name << "(" << s.grade << "," << s.age << ") ";
    cout << endl;

    // Using std::tie (cleaner)
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return tie(a.grade, a.age, a.name) < tie(b.grade, b.age, b.name);
    });
    cout << "Using tie(): ";
    for (auto& s : students) cout << s.name << "(" << s.grade << "," << s.age << ") ";
    cout << endl;

    // Sort by grade DESC, then name ASC
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.grade != b.grade) return a.grade > b.grade; // DESC
        return a.name < b.name; // ASC
    });
    cout << "Grade DESC, Name ASC: ";
    for (auto& s : students) cout << s.name << "(" << s.grade << ") ";
    cout << endl;

    // Using pair for automatic multi-key sort
    vector<pair<int, string>> pairs = {{85, "Alice"}, {90, "Bob"}, {85, "Charlie"}};
    sort(pairs.begin(), pairs.end()); // Sorts by first, then second
    cout << "Pair sort: ";
    for (auto& [g, n] : pairs) cout << n << "(" << g << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: PAIR SORTING & STRUCT SORTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 PAIR SORTING:
   pair<T1,T2> has built-in operator< that sorts by first, then second.
   This is very useful in CP for encoding (value, index) or (key, satellite).

 STRUCT SORTING:
   Define operator< or use custom comparator.
   operator< allows use in sets, maps, priority_queues.

 COMMON PATTERNS:
   • Sort intervals: pair<int,int> → (start, end)
   • Sort with index: pair<int,int> → (value, original_index)
   • Sort events: pair<int,int> → (time, type)
*/

void demo_pair_struct_sort() {
    cout << "=== SECTION 3: PAIR & STRUCT SORTING ===" << endl;

    // Pair sorting — automatic
    vector<pair<int, int>> intervals = {{3, 5}, {1, 3}, {2, 7}, {1, 2}};
    sort(intervals.begin(), intervals.end());
    cout << "Sorted intervals: ";
    for (auto& [a, b] : intervals) cout << "(" << a << "," << b << ") ";
    cout << endl;

    // Sort by end time (for greedy interval scheduling)
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });
    cout << "By end time: ";
    for (auto& [a, b] : intervals) cout << "(" << a << "," << b << ") ";
    cout << endl;

    // Struct with operator<
    struct Edge {
        int u, v, w;
        bool operator<(const Edge& other) const {
            return w < other.w; // Sort by weight (for Kruskal's)
        }
    };

    vector<Edge> edges = {{1, 2, 5}, {2, 3, 1}, {1, 3, 3}};
    sort(edges.begin(), edges.end());
    cout << "Edges by weight: ";
    for (auto& e : edges) cout << "(" << e.u << "-" << e.v << ":" << e.w << ") ";
    cout << endl;

    // Tuple sorting (automatic multi-key)
    vector<tuple<int, int, int>> tuples = {{3, 1, 4}, {1, 5, 9}, {2, 6, 5}};
    sort(tuples.begin(), tuples.end());
    cout << "Tuple sort: ";
    for (auto& [a, b, c] : tuples) cout << "(" << a << "," << b << "," << c << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SORTING WITH LAMBDA
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Lambda functions are the most convenient way to write comparators in CP.

 SYNTAX: [capture](params) -> return_type { body }

 For sort: [](const T& a, const T& b) { return /* a before b */; }

 CAPTURE:
   [&] — capture all by reference (most common in CP)
   [=] — capture all by copy
   [&x, y] — capture x by ref, y by copy

 LAMBDA COMPARATORS allow capturing external state — very powerful!
*/

void demo_lambda_sort() {
    cout << "=== SECTION 4: LAMBDA SORTING ===" << endl;

    // Sort by distance from a target
    int target = 5;
    vector<int> arr = {1, 8, 3, 10, 2, 7};
    sort(arr.begin(), arr.end(), [target](int a, int b) {
        return abs(a - target) < abs(b - target);
    });
    cout << "By distance from " << target << ": ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Sort by custom priority using external array
    vector<int> priority = {3, 1, 4, 1, 5, 9, 2, 6}; // priority[i] for value i
    vector<int> arr2 = {0, 1, 2, 3, 4, 5, 6, 7};
    sort(arr2.begin(), arr2.end(), [&priority](int a, int b) {
        return priority[a] > priority[b];
    });
    cout << "By external priority: ";
    for (int x : arr2) cout << x << "(" << priority[x] << ") ";
    cout << endl;

    // Sort indices by array values (index sort)
    vector<int> values = {40, 10, 30, 20, 50};
    vector<int> indices(values.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&values](int i, int j) {
        return values[i] < values[j];
    });
    cout << "Index sort: ";
    for (int i : indices) cout << i << "(val=" << values[i] << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: SORTING + GREEDY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Many greedy problems require sorting as the first step.
 The key is to identify WHAT to sort by.

 CLASSIC PATTERNS:
   1. Activity Selection: Sort by end time → pick non-overlapping
   2. Fractional Knapsack: Sort by value/weight ratio
   3. Minimum Platforms: Sort arrival + departure events
   4. Job Scheduling: Sort by deadline or profit
   5. Huffman Coding: Sort by frequency (use priority queue)
   6. Assign Cookies: Sort both arrays, greedy matching
*/

void demo_sorting_greedy() {
    cout << "=== SECTION 5: SORTING + GREEDY ===" << endl;

    // Activity Selection — Max non-overlapping intervals
    vector<pair<int, int>> activities = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}};
    sort(activities.begin(), activities.end(), [](auto& a, auto& b) {
        return a.second < b.second; // Sort by END time
    });
    int count = 0, lastEnd = -1;
    cout << "Selected activities: ";
    for (auto& [s, e] : activities) {
        if (s >= lastEnd) {
            cout << "(" << s << "," << e << ") ";
            lastEnd = e;
            count++;
        }
    }
    cout << "\nMax non-overlapping: " << count << endl;

    // Assign Cookies (LC 455) — Greedy after sorting
    vector<int> children = {1, 2, 3}; // greed factor
    vector<int> cookies = {1, 1};      // cookie sizes
    sort(children.begin(), children.end());
    sort(cookies.begin(), cookies.end());
    int satisfied = 0, j = 0;
    for (int i = 0; i < (int)cookies.size() && j < (int)children.size(); i++) {
        if (cookies[i] >= children[j]) {
            satisfied++;
            j++;
        }
    }
    cout << "Satisfied children: " << satisfied << endl;

    // Minimum number of meeting rooms
    vector<pair<int, int>> meetings = {{0, 30}, {5, 10}, {15, 20}};
    vector<pair<int, int>> events; // (time, +1 for start, -1 for end)
    for (auto& [s, e] : meetings) {
        events.push_back({s, 1});
        events.push_back({e, -1});
    }
    sort(events.begin(), events.end());
    int rooms = 0, maxRooms = 0;
    for (auto& [t, type] : events) {
        rooms += type;
        maxRooms = max(maxRooms, rooms);
    }
    cout << "Min meeting rooms: " << maxRooms << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: SORTING + PREFIX SUM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Sort + Prefix Sum is a powerful combination:
   1. Sort array
   2. Build prefix sum on sorted array
   3. Use prefix sum for range queries

 APPLICATIONS:
   • Find max sum of k smallest/largest elements
   • Binary search on prefix sum for threshold queries
   • Minimize cost problems
*/

void demo_sorting_prefix() {
    cout << "=== SECTION 6: SORTING + PREFIX SUM ===" << endl;

    vector<int> arr = {5, 2, 8, 1, 9, 3, 7};
    sort(arr.begin(), arr.end());

    // Prefix sum of sorted array
    vector<long long> prefix(arr.size() + 1, 0);
    for (int i = 0; i < (int)arr.size(); i++)
        prefix[i + 1] = prefix[i] + arr[i];

    cout << "Sorted: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Sum of k smallest
    int k = 3;
    cout << "Sum of " << k << " smallest: " << prefix[k] << endl;

    // Sum of k largest
    int n = arr.size();
    cout << "Sum of " << k << " largest: " << prefix[n] - prefix[n - k] << endl;

    // Minimum cost to make all elements equal
    // Sort, pick median, use prefix sum for cost
    int median = arr[n / 2];
    long long cost = 0;
    for (int x : arr) cost += abs(x - median);
    cout << "Min cost to equalize (median=" << median << "): " << cost << endl;

    // Count pairs with sum ≤ threshold using sort + prefix + binary search
    int threshold = 8;
    int pairs = 0;
    for (int i = 0; i < n; i++) {
        int maxPartner = threshold - arr[i];
        int pos = upper_bound(arr.begin(), arr.end(), maxPartner) - arr.begin();
        pairs += pos; // Count elements ≤ maxPartner
        if (arr[i] <= maxPartner) pairs--; // Don't pair with self
    }
    pairs /= 2; // Each pair counted twice
    cout << "Pairs with sum ≤ " << threshold << ": " << pairs << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: SORTING + TWO POINTER
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Two pointers on a sorted array is one of the most common CP patterns.

 REQUIRES: Array must be sorted (or sortable).

 CLASSIC PROBLEMS:
   1. Two Sum (sorted): O(n) with two pointers
   2. Three Sum: Sort + fix one + two pointer = O(n²)
   3. Container With Most Water: Two pointer from ends
   4. Closest pair to target sum
   5. Count pairs in range [lo, hi]
*/

void demo_sorting_two_pointer() {
    cout << "=== SECTION 7: SORTING + TWO POINTER ===" << endl;

    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Already sorted

    // Two Sum
    int target = 11;
    int lo = 0, hi = (int)arr.size() - 1;
    cout << "Pairs summing to " << target << ": ";
    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum == target) {
            cout << "(" << arr[lo] << "+" << arr[hi] << ") ";
            lo++; hi--;
        } else if (sum < target) lo++;
        else hi--;
    }
    cout << endl;

    // Three Sum = 0
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    sort(nums.begin(), nums.end());
    cout << "3Sum = 0: ";
    for (int i = 0; i < (int)nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates
        int left = i + 1, right = (int)nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                cout << "(" << nums[i] << "," << nums[left] << "," << nums[right] << ") ";
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++; right--;
            } else if (sum < 0) left++;
            else right--;
        }
    }
    cout << endl;

    // CSES Apartments — Sort both, greedily match
    vector<int> applicants = {60, 45, 80, 60};
    vector<int> apartments = {30, 60, 75};
    int tolerance = 5;
    sort(applicants.begin(), applicants.end());
    sort(apartments.begin(), apartments.end());
    int i = 0, j = 0, matched = 0;
    while (i < (int)applicants.size() && j < (int)apartments.size()) {
        if (abs(applicants[i] - apartments[j]) <= tolerance) {
            matched++; i++; j++;
        } else if (applicants[i] < apartments[j]) i++;
        else j++;
    }
    cout << "Apartment matches: " << matched << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: SORTING BY ABSOLUTE DIFFERENCE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Sort elements by their absolute difference from a target value.
 Useful for "K closest elements" problems.

 APPROACH:
   sort by |arr[i] - target|, tiebreak by value or index

 LC 658: Find K Closest Elements
 LC 973: K Closest Points to Origin
*/

void demo_abs_diff_sort() {
    cout << "=== SECTION 8: SORT BY ABSOLUTE DIFFERENCE ===" << endl;

    // K closest elements to target
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 6, k = 4;

    // Method 1: Sort by distance
    vector<int> indices(arr.size());
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        int d1 = abs(arr[i] - target);
        int d2 = abs(arr[j] - target);
        if (d1 != d2) return d1 < d2;
        return arr[i] < arr[j]; // Prefer smaller value on tie
    });

    cout << k << " closest to " << target << ": ";
    vector<int> closest;
    for (int i = 0; i < k; i++) closest.push_back(arr[indices[i]]);
    sort(closest.begin(), closest.end());
    for (int x : closest) cout << x << " ";
    cout << endl;

    // K Closest Points to Origin (LC 973)
    vector<pair<int, int>> points = {{3, 3}, {5, -1}, {-2, 4}, {1, 1}};
    k = 2;
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a.first * a.first + a.second * a.second <
               b.first * b.first + b.second * b.second;
    });
    cout << k << " closest to origin: ";
    for (int i = 0; i < k; i++)
        cout << "(" << points[i].first << "," << points[i].second << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: SORTING WITH INDEX PRESERVATION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Often we need the sorted ORDER but want to know original positions.

 METHODS:
   1. Sort array of indices
   2. Sort array of (value, index) pairs
   3. Use argsort concept

 APPLICATIONS:
   • "After sorting, what was the original index of each element?"
   • Rank computation
   • Matching problems
*/

void demo_index_preserving() {
    cout << "=== SECTION 9: INDEX PRESERVATION ===" << endl;

    vector<int> arr = {40, 10, 50, 20, 30};
    int n = arr.size();

    // Method 1: Sort indices
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return arr[a] < arr[b];
    });
    cout << "Sorted order (index): ";
    for (int i : idx) cout << "arr[" << i << "]=" << arr[i] << " ";
    cout << endl;

    // Method 2: Rank of each element
    vector<int> rank_arr(n);
    for (int i = 0; i < n; i++) rank_arr[idx[i]] = i;
    cout << "Ranks: ";
    for (int i = 0; i < n; i++) cout << arr[i] << "→rank" << rank_arr[i] << " ";
    cout << endl;

    // Method 3: Sort pairs (value, index)
    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; i++) pairs[i] = {arr[i], i};
    sort(pairs.begin(), pairs.end());
    cout << "Value-Index pairs: ";
    for (auto& [v, i] : pairs) cout << "(" << v << ",idx" << i << ") ";
    cout << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 10: STABLE SORT USAGE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 std::stable_sort() guarantees that equal elements keep their
 relative order from the original array.

 USE CASES:
   1. Multi-criteria sort: Sort by X, then stable_sort by Y
      Result: sorted by Y, with X-order preserved for equal Y
   2. When problem says "maintain input order for ties"
   3. Cascaded sorting (sort multiple times, each stable)

 COMPLEXITY: O(n log n) time, O(n) space
*/

void demo_stable_sort() {
    cout << "=== SECTION 10: STABLE SORT ===" << endl;

    // Cascaded stable sort: Sort by name, then stable sort by grade
    struct Student { string name; int grade; };
    vector<Student> students = {
        {"Eve", 85}, {"Alice", 90}, {"Bob", 85},
        {"Diana", 90}, {"Charlie", 85}
    };

    // First sort by name
    stable_sort(students.begin(), students.end(), [](auto& a, auto& b) {
        return a.name < b.name;
    });
    cout << "After name sort: ";
    for (auto& s : students) cout << s.name << " ";
    cout << endl;

    // Then stable sort by grade — name order preserved within same grade
    stable_sort(students.begin(), students.end(), [](auto& a, auto& b) {
        return a.grade < b.grade;
    });
    cout << "After stable grade sort: ";
    for (auto& s : students) cout << s.name << "(" << s.grade << ") ";
    cout << endl;
    // Grade 85: Bob, Charlie, Eve (alphabetical — preserved from name sort!)
    // Grade 90: Alice, Diana (alphabetical — preserved from name sort!)

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 11: PARTIAL SORT & nth_element
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 std::partial_sort(first, middle, last):
   Sorts the range such that [first, middle) contains the smallest
   (middle - first) elements in sorted order.
   Rest of the range is unspecified.
   Time: O(n log k) where k = middle - first

 std::nth_element(first, nth, last):
   Rearranges such that:
   - Element at nth position is what would be there if sorted
   - Elements before nth are ≤ *nth
   - Elements after nth are ≥ *nth
   Time: O(n) average (like QuickSelect)

 USE CASES:
   • partial_sort: Top-K elements in sorted order
   • nth_element: Find kth smallest/median, partition around kth element

 COMPARISON:
   ┌─────────────────┬────────────────┬───────────────────────────────┐
   │ Function        │ Time           │ Result                        │
   ├─────────────────┼────────────────┼───────────────────────────────┤
   │ sort()          │ O(n log n)     │ Entire array sorted           │
   │ partial_sort()  │ O(n log k)     │ First k elements sorted       │
   │ nth_element()   │ O(n) avg       │ kth element in correct place  │
   │ partial_sort_cp │ O(n + k log n) │ Top-k sorted (heap-based)     │
   └─────────────────┴────────────────┴───────────────────────────────┘
*/

void demo_partial_sort() {
    cout << "=== SECTION 11: PARTIAL SORT & nth_element ===" << endl;

    vector<int> arr = {9, 3, 7, 1, 5, 8, 2, 6, 4, 10};

    // partial_sort: Get top 3 smallest in sorted order
    vector<int> v1 = arr;
    partial_sort(v1.begin(), v1.begin() + 3, v1.end());
    cout << "Top 3 smallest: ";
    for (int i = 0; i < 3; i++) cout << v1[i] << " ";
    cout << "(rest unsorted)" << endl;

    // partial_sort: Get top 3 largest in sorted order
    vector<int> v2 = arr;
    partial_sort(v2.begin(), v2.begin() + 3, v2.end(), greater<int>());
    cout << "Top 3 largest: ";
    for (int i = 0; i < 3; i++) cout << v2[i] << " ";
    cout << endl;

    // nth_element: Find median
    vector<int> v3 = arr;
    int n = v3.size();
    nth_element(v3.begin(), v3.begin() + n / 2, v3.end());
    cout << "Median (n/2 element): " << v3[n / 2] << endl;

    // nth_element: Find 3rd smallest
    vector<int> v4 = arr;
    nth_element(v4.begin(), v4.begin() + 2, v4.end()); // 0-indexed
    cout << "3rd smallest: " << v4[2] << endl;

    // nth_element: Partition around kth element
    vector<int> v5 = arr;
    nth_element(v5.begin(), v5.begin() + 5, v5.end());
    cout << "After nth_element(5): ";
    for (int x : v5) cout << x << " ";
    cout << "\n  → v5[5]=" << v5[5] << ", left ≤ " << v5[5] << ", right ≥ " << v5[5] << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 12: ORDER STATISTICS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The kth order statistic = kth smallest element.

 METHODS:
   1. Sort + index: O(n log n)
   2. nth_element: O(n) average (QuickSelect)
   3. Min-heap of size k: O(n log k)
   4. Max-heap of size k: O(n log k) — for kth largest
   5. Median of medians: O(n) worst case (theoretical)

 COMPETITIVE PROGRAMMING:
   • Kth smallest: nth_element or quickselect
   • Kth largest: nth_element(begin, begin + n - k, end)
   • Running kth element: Use two heaps or balanced BST
*/

void demo_order_statistics() {
    cout << "=== SECTION 12: ORDER STATISTICS ===" << endl;

    vector<int> arr = {7, 10, 4, 3, 20, 15};
    int k = 3; // 3rd smallest

    // Method 1: Sort
    vector<int> v1 = arr;
    sort(v1.begin(), v1.end());
    cout << k << "rd smallest (sort): " << v1[k - 1] << endl;

    // Method 2: nth_element
    vector<int> v2 = arr;
    nth_element(v2.begin(), v2.begin() + k - 1, v2.end());
    cout << k << "rd smallest (nth_element): " << v2[k - 1] << endl;

    // Method 3: Max-heap of size k → kth smallest
    priority_queue<int> maxHeap;
    for (int x : arr) {
        maxHeap.push(x);
        if ((int)maxHeap.size() > k) maxHeap.pop();
    }
    cout << k << "rd smallest (heap): " << maxHeap.top() << endl;

    // Kth largest using min-heap
    int kl = 2; // 2nd largest
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : arr) {
        minHeap.push(x);
        if ((int)minHeap.size() > kl) minHeap.pop();
    }
    cout << kl << "nd largest (heap): " << minHeap.top() << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 05: SORTING PATTERNS & TRICKS                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_custom_comparators();
    demo_multi_key_sort();
    demo_pair_struct_sort();
    demo_lambda_sort();
    demo_sorting_greedy();
    demo_sorting_prefix();
    demo_sorting_two_pointer();
    demo_abs_diff_sort();
    demo_index_preserving();
    demo_stable_sort();
    demo_partial_sort();
    demo_order_statistics();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 05 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Relative Sort Array (LC 1122) — Custom comparator                      ║
║  2. Sort Array by Parity (LC 905) — Even/Odd                               ║
║  3. Assign Cookies (LC 455) — Sort + Greedy                                ║
║  4. K Closest Points to Origin (LC 973)                                    ║
║  5. Kth Largest Element (LC 215) — nth_element                             ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  6. Largest Number (LC 179) — Custom string comparator                     ║
║  7. CSES — Apartments (sort + two pointer)                                 ║
║  8. Minimum Number of Arrows (LC 452) — Sort + Greedy                      ║
║  9. Non-overlapping Intervals (LC 435)                                     ║
║ 10. 3Sum (LC 15) — Sort + Two Pointer                                     ║
║ 11. Meeting Rooms II (LC 253) — Sort events                                ║
║ 12. Find K Closest Elements (LC 658)                                       ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 13. CSES — Tasks and Deadlines (sort + DP)                                 ║
║ 14. CF 1324D — Pair of Topics (sort + two pointer counting)                ║
║ 15. CF 1399D — Binary String To Subsequences                               ║
║ 16. Wiggle Sort II (LC 324) — nth_element + interleave                     ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 17. CF 1468J — Road Reform (sort edges + MST)                              ║
║ 18. CF 1208E — Let Them Slide (sort + deque)                               ║
║ 19. USACO — Closest Cow Wins (sort + greedy sweep)                         ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

