/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07 — BINARY SEARCH ON ANSWER                             ║
║           From Zero to Grandmaster — Complete Foundation                    ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Monotonic Function Property
 2.  Feasibility Checking Pattern
 3.  Minimize Maximum (Binary Search on Answer)
 4.  Maximize Minimum (Binary Search on Answer)
 5.  Aggressive Cows (Classic)
 6.  Allocate Books (Classic)
 7.  Painters Partition
 8.  Parametric Search
 9.  Floating Point Binary Search

OVERVIEW:
─────────
Binary Search on Answer is the MOST IMPORTANT binary search pattern
in competitive programming. Instead of searching for an element in an
array, we search for the optimal VALUE of the answer.

KEY INSIGHT:
  If the answer has a MONOTONIC feasibility property:
  "For answer = X, is it feasible?"
  And feasibility is monotonic (FFF...TTT or TTT...FFF),
  then we can binary search on X!

PATTERN:
  lo = minimum possible answer
  hi = maximum possible answer
  while lo < hi:
    mid = (lo + hi) / 2
    if feasible(mid):
      hi = mid       // mid works, try smaller (minimize)
      // OR lo = mid  // mid works, try larger (maximize)
    else:
      lo = mid + 1   // mid doesn't work, need larger
      // OR hi = mid - 1  // need smaller

MINIMIZE MAXIMUM:
  "What is the minimum possible value of the maximum?"
  Feasibility: Can we achieve max ≤ mid?
  If yes → hi = mid (try smaller max)
  If no → lo = mid + 1 (need larger max)

MAXIMIZE MINIMUM:
  "What is the maximum possible value of the minimum?"
  Feasibility: Can we achieve min ≥ mid?
  If yes → lo = mid (try larger min)
  If no → hi = mid - 1 (need smaller min)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <cmath>
#include <climits>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: MONOTONIC FUNCTION PROPERTY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A function f(x) is MONOTONIC if:
   f(x) ≤ f(x+1) for all x (non-decreasing) or
   f(x) ≥ f(x+1) for all x (non-increasing)

 For binary search on answer, we need:
   "feasible(x)" to be monotonic:
   FFFFFFFF...TTTTTTTT  (find first T → minimize)
   TTTTTTTT...FFFFFFFF  (find last T → maximize)

 EXAMPLES:
   "Can we split array into k parts each with sum ≤ x?"
   As x increases, it becomes EASIER → FFFF...TTTT → minimize x

   "Can we place cows with minimum distance ≥ x?"
   As x increases, it becomes HARDER → TTTT...FFFF → maximize x

 HOW TO IDENTIFY:
   1. Answer has a range [lo, hi]
   2. There's a feasibility check for each answer value
   3. Feasibility is monotonic
   4. "Minimize the maximum" or "Maximize the minimum" → BS on answer
*/

void demo_monotonic() {
    cout << "=== SECTION 1: MONOTONIC FUNCTION ===" << endl;

    // Example: "Can we fit items into k boxes where each box holds ≤ capacity?"
    vector<int> items = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;

    auto canFitInKBoxes = [&](int capacity) -> bool {
        int boxes = 1, currentSum = 0;
        for (int item : items) {
            if (item > capacity) return false; // Single item too large
            if (currentSum + item > capacity) {
                boxes++;
                currentSum = item;
            } else {
                currentSum += item;
            }
        }
        return boxes <= k;
    };

    // Show monotonic property
    cout << "Capacity → Feasible:" << endl;
    for (int cap = 10; cap <= 55; cap += 5) {
        cout << "  cap=" << cap << " → " << (canFitInKBoxes(cap) ? "YES" : "NO") << endl;
    }
    // Notice: FFFF...TTTT — monotonic!

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: FEASIBILITY CHECKING PATTERN
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The core of binary search on answer is the FEASIBILITY CHECK.
 This is a function check(mid) → bool that determines if
 the answer "mid" is achievable.

 TEMPLATE:
   bool feasible(int mid) {
     // Greedy simulation to check if answer = mid works
     // Usually O(n) time
     return true or false;
   }

   int lo = min_answer, hi = max_answer;
   while (lo < hi) {
     int mid = lo + (hi - lo) / 2;
     if (feasible(mid)) hi = mid; // For minimization
     else lo = mid + 1;
   }
   return lo;

 THE FEASIBILITY CHECK IS ALWAYS GREEDY!
 You're checking: "Given this constraint, can I succeed?"
 → Greedily try to succeed with the given constraint.
*/

// Example: Minimum capacity to ship packages in D days (LC 1011)
int shipWithinDays(vector<int>& weights, int days) {
    // Feasibility: Can we ship all packages in ≤ 'days' with capacity 'cap'?
    auto canShip = [&](int cap) -> bool {
        int daysNeeded = 1, currentLoad = 0;
        for (int w : weights) {
            if (currentLoad + w > cap) {
                daysNeeded++;
                currentLoad = w;
            } else {
                currentLoad += w;
            }
        }
        return daysNeeded <= days;
    };

    int lo = *max_element(weights.begin(), weights.end()); // At least max weight
    int hi = accumulate(weights.begin(), weights.end(), 0); // At most total weight

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canShip(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

void demo_feasibility() {
    cout << "=== SECTION 2: FEASIBILITY CHECKING ===" << endl;

    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int days = 5;
    cout << "Ship in " << days << " days: min capacity = "
         << shipWithinDays(weights, days) << endl; // 15

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MINIMIZE MAXIMUM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 "Minimize the maximum" problems ask:
   "What is the SMALLEST possible value of the LARGEST element?"

 Pattern: FFFFFFFF...TTTTTTTT (find first T)
   lo = min possible answer
   hi = max possible answer
   while lo < hi:
     mid = (lo + hi) / 2
     if feasible(mid): hi = mid
     else: lo = mid + 1
   return lo

 CLASSIC EXAMPLES:
   • Split array into k parts, minimize max subarray sum
   • Allocate pages to students, minimize max pages
   • Ship packages in D days, minimize ship capacity
   • Cut wood into pieces, minimize max piece length
*/

// Split Array Largest Sum (LC 410)
// Minimize the maximum sum among k subarrays
int splitArray(vector<int>& nums, int k) {
    auto canSplit = [&](long long maxSum) -> bool {
        int parts = 1;
        long long currentSum = 0;
        for (int x : nums) {
            if (currentSum + x > maxSum) {
                parts++;
                currentSum = x;
            } else {
                currentSum += x;
            }
        }
        return parts <= k;
    };

    long long lo = *max_element(nums.begin(), nums.end());
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canSplit(mid)) hi = mid;
        else lo = mid + 1;
    }
    return (int)lo;
}

// CSES Array Division
// Same as splitArray
int arrayDivision(vector<int>& arr, int k) {
    return splitArray(arr, k);
}

void demo_minimize_max() {
    cout << "=== SECTION 3: MINIMIZE MAXIMUM ===" << endl;

    // Split Array Largest Sum
    vector<int> nums = {7, 2, 5, 10, 8};
    int k = 2;
    cout << "Split [7,2,5,10,8] into " << k << " parts: min max sum = "
         << splitArray(nums, k) << endl; // 18 (7+2+5 | 10+8)

    vector<int> nums2 = {1, 2, 3, 4, 5};
    cout << "Split [1,2,3,4,5] into 2: min max sum = "
         << splitArray(nums2, 2) << endl; // 9 (1+2+3 | 4+5)

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: MAXIMIZE MINIMUM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 "Maximize the minimum" problems ask:
   "What is the LARGEST possible value of the SMALLEST element?"

 Pattern: TTTTTTTT...FFFFFFFF (find last T)
   lo = min possible answer
   hi = max possible answer
   while lo < hi:
     mid = (lo + hi + 1) / 2  ← IMPORTANT: ceiling to avoid infinite loop!
     if feasible(mid): lo = mid
     else: hi = mid - 1
   return lo

 CLASSIC EXAMPLES:
   • Place cows to maximize minimum distance
   • Place routers to maximize minimum coverage
   • Distribute tasks to maximize minimum load
*/

// Maximize the minimum distance (place k items in n positions)
int maximizeMinDistance(vector<int>& positions, int k) {
    sort(positions.begin(), positions.end());

    auto canPlace = [&](int minDist) -> bool {
        int count = 1, lastPos = positions[0];
        for (int i = 1; i < (int)positions.size(); i++) {
            if (positions[i] - lastPos >= minDist) {
                count++;
                lastPos = positions[i];
            }
        }
        return count >= k;
    };

    int lo = 1;
    int hi = positions.back() - positions.front();

    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // Ceiling!
        if (canPlace(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

void demo_maximize_min() {
    cout << "=== SECTION 4: MAXIMIZE MINIMUM ===" << endl;

    vector<int> positions = {1, 2, 4, 8, 9};
    int k = 3;
    cout << "Positions: ";
    for (int x : positions) cout << x << " ";
    cout << endl;
    cout << "Place " << k << " items: max min distance = "
         << maximizeMinDistance(positions, k) << endl; // 3 (at 1, 4, 9)

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: AGGRESSIVE COWS (CLASSIC)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 PROBLEM (SPOJ AGGRCOW):
   N stalls at positions x1, x2, ..., xN.
   Place C cows in stalls such that the MINIMUM DISTANCE between
   any two cows is MAXIMIZED.

 APPROACH:
   Binary search on answer (minimum distance).
   For each candidate distance d:
     Greedily place cows — place first cow at leftmost stall,
     next cow at first stall that is ≥ d away, etc.
     If we can place all C cows → d is feasible.

 TIME: O(N log N + N log(maxDist))
*/

int aggressiveCows(vector<int>& stalls, int cows) {
    sort(stalls.begin(), stalls.end());
    int n = stalls.size();

    auto canPlace = [&](int minDist) -> bool {
        int placed = 1, lastPos = stalls[0];
        for (int i = 1; i < n; i++) {
            if (stalls[i] - lastPos >= minDist) {
                placed++;
                lastPos = stalls[i];
                if (placed >= cows) return true;
            }
        }
        return false;
    };

    int lo = 1, hi = stalls[n - 1] - stalls[0];
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (canPlace(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

void demo_aggressive_cows() {
    cout << "=== SECTION 5: AGGRESSIVE COWS ===" << endl;

    vector<int> stalls = {1, 2, 4, 8, 9};
    int cows = 3;
    cout << "Stalls: ";
    for (int x : stalls) cout << x << " ";
    cout << endl;
    cout << cows << " cows: max min distance = " << aggressiveCows(stalls, cows) << endl;
    // Optimal: Place at 1, 4, 9 → min dist = 3

    vector<int> stalls2 = {1, 2, 8, 4, 9};
    cout << "3 cows: " << aggressiveCows(stalls2, 3) << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: ALLOCATE BOOKS (CLASSIC)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 PROBLEM:
   N books with pages[i]. Allocate to M students such that:
   - Each student gets contiguous books
   - Every book is allocated
   - MINIMIZE the MAXIMUM pages any student reads

 APPROACH:
   Binary search on answer (max pages per student).
   Feasibility: Can we allocate all books to M students with max ≤ mid?
   Greedy: Assign books to current student until sum exceeds mid,
           then move to next student.

 TIME: O(N log(sum of pages))
*/

int allocateBooks(vector<int>& pages, int students) {
    int n = pages.size();
    if (students > n) return -1; // More students than books

    auto canAllocate = [&](long long maxPages) -> bool {
        int studentsNeeded = 1;
        long long currentPages = 0;
        for (int i = 0; i < n; i++) {
            if (pages[i] > maxPages) return false;
            if (currentPages + pages[i] > maxPages) {
                studentsNeeded++;
                currentPages = pages[i];
            } else {
                currentPages += pages[i];
            }
        }
        return studentsNeeded <= students;
    };

    long long lo = *max_element(pages.begin(), pages.end());
    long long hi = accumulate(pages.begin(), pages.end(), 0LL);

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canAllocate(mid)) hi = mid;
        else lo = mid + 1;
    }
    return (int)lo;
}

void demo_allocate_books() {
    cout << "=== SECTION 6: ALLOCATE BOOKS ===" << endl;

    vector<int> pages = {12, 34, 67, 90};
    int students = 2;
    cout << "Pages: ";
    for (int x : pages) cout << x << " ";
    cout << endl;
    cout << students << " students: min max pages = " << allocateBooks(pages, students) << endl;
    // Optimal: [12, 34, 67 | 90] max = 113 or [12, 34 | 67, 90] max = 157
    // Best: [12, 34, 67 | 90] → max(113, 90) = 113

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: PAINTERS PARTITION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 PROBLEM:
   N boards of lengths L1, L2, ..., LN.
   K painters, each paints contiguous boards.
   Each unit takes 1 unit time.
   MINIMIZE the maximum time any painter spends.

 IDENTICAL to Allocate Books / Split Array Largest Sum!

 APPROACH:
   Binary search on answer (max time).
   Same feasibility check as allocate books.

 VARIATION: Painters Partition with equal speed
   vs unequal speed (harder, different approach)
*/

int paintersPartition(vector<int>& boards, int painters) {
    return allocateBooks(boards, painters); // Same algorithm!
}

// CSES: Factory Machines
// N machines, machine i produces item in t[i] time. Produce k items minimum time.
long long factoryMachines(vector<int>& times, long long k) {
    auto canProduce = [&](long long totalTime) -> bool {
        long long items = 0;
        for (int t : times) {
            items += totalTime / t;
            if (items >= k) return true;
        }
        return false;
    };

    long long lo = 1;
    long long hi = (long long)*min_element(times.begin(), times.end()) * k;

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canProduce(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

void demo_painters_partition() {
    cout << "=== SECTION 7: PAINTERS PARTITION ===" << endl;

    vector<int> boards = {10, 20, 30, 40};
    int painters = 2;
    cout << "Boards: ";
    for (int x : boards) cout << x << " ";
    cout << endl;
    cout << painters << " painters: min max time = "
         << paintersPartition(boards, painters) << endl;
    // [10, 20, 30 | 40] → max(60, 40) = 60

    // Factory Machines (CSES)
    vector<int> machines = {3, 2, 5};
    long long items = 11;
    cout << "Factory: produce " << items << " items in "
         << factoryMachines(machines, items) << " time" << endl;

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: PARAMETRIC SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Parametric search is the generalization of binary search on answer.
 We parameterize the problem by a value X and check feasibility.

 MORE EXAMPLES:

 1. Koko Eating Bananas (LC 875):
    K piles of bananas. Koko eats at speed S bananas/hour.
    She has H hours. Find minimum S.
    → BS on S. Check: can she eat all in H hours at speed S?

 2. Magnetic Force (LC 1552):
    Place balls with max min distance → BS on distance

 3. Maximum Median (CF 1201C):
    n numbers, k operations (increment by 1).
    Maximize the median. → BS on median value

 4. Minimum time for K processes on N servers
    → BS on time, check feasibility

 5. Cutting wood (SPOJ EKO):
    Cut trees at height H. Collect wood ≥ M.
    Find maximum H.
*/

// Koko Eating Bananas (LC 875)
int kokoEatingBananas(vector<int>& piles, int h) {
    auto canEat = [&](int speed) -> bool {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + speed - 1) / speed; // ceil(pile/speed)
        }
        return hours <= h;
    };

    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canEat(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// EKO — Cut wood at height H, collect at least M meters
int cutWood(vector<int>& trees, long long needed) {
    auto canCollect = [&](int height) -> bool {
        long long collected = 0;
        for (int t : trees) {
            if (t > height) collected += (t - height);
        }
        return collected >= needed;
    };

    int lo = 0, hi = *max_element(trees.begin(), trees.end());
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // Ceiling — maximizing
        if (canCollect(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// Minimum Speed to Arrive on Time (LC 1870)
int minSpeedOnTime(vector<int>& dist, double hour) {
    int n = dist.size();
    auto canArrive = [&](int speed) -> bool {
        double time = 0;
        for (int i = 0; i < n - 1; i++) {
            time += ceil((double)dist[i] / speed);
        }
        time += (double)dist[n - 1] / speed;
        return time <= hour;
    };

    int lo = 1, hi = 1e7;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canArrive(mid)) hi = mid;
        else lo = mid + 1;
    }

    // Final check
    double time = 0;
    for (int i = 0; i < n - 1; i++) time += ceil((double)dist[i] / lo);
    time += (double)dist[n - 1] / lo;
    if (time > hour) return -1;
    return lo;
}

void demo_parametric_search() {
    cout << "=== SECTION 8: PARAMETRIC SEARCH ===" << endl;

    // Koko Eating Bananas
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    cout << "Koko min speed: " << kokoEatingBananas(piles, h) << endl; // 4

    // EKO cut wood
    vector<int> trees = {20, 15, 10, 17};
    long long needed = 7;
    cout << "Cut height for " << needed << "m wood: "
         << cutWood(trees, needed) << endl; // 15

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: FLOATING POINT BINARY SEARCH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When the answer is a real number (floating point), we can't use
 integer binary search. Instead:

 METHOD 1: Fixed number of iterations (most reliable)
   for (int iter = 0; iter < 100; iter++):  // 100 iterations ≈ 2^100 precision
     mid = (lo + hi) / 2
     if (feasible(mid)): hi = mid
     else: lo = mid

 METHOD 2: While loop with epsilon
   while (hi - lo > 1e-9):
     mid = (lo + hi) / 2
     ...

 METHOD 1 IS PREFERRED because:
   - No risk of infinite loop due to floating point imprecision
   - 100 iterations gives plenty of precision
   - Simple and robust

 APPLICATIONS:
   • Square root, cube root
   • Finding zero of monotonic function
   • Geometric problems (distance, angle)
   • Physics simulation (time to reach point)
*/

// Floating point square root
double sqrtBS(double x) {
    double lo = 0, hi = max(1.0, x);
    for (int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if (mid * mid <= x) lo = mid;
        else hi = mid;
    }
    return lo;
}

// Cube root (handles negative)
double cbrtBS(double x) {
    double lo = -1e9, hi = 1e9;
    for (int i = 0; i < 200; i++) {
        double mid = (lo + hi) / 2;
        if (mid * mid * mid <= x) lo = mid;
        else hi = mid;
    }
    return lo;
}

// Find zero of monotonic function f in [lo, hi]
double findZero(double lo, double hi, function<double(double)> f) {
    for (int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if (f(mid) <= 0) lo = mid;
        else hi = mid;
    }
    return lo;
}

// Rope problem: Cut rope into k pieces of at least length L
// Maximize L
double maxRopeLength(vector<double>& ropes, int k) {
    auto canCut = [&](double length) -> bool {
        int pieces = 0;
        for (double r : ropes) {
            pieces += (int)(r / length);
        }
        return pieces >= k;
    };

    double lo = 0, hi = *max_element(ropes.begin(), ropes.end());
    for (int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if (canCut(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

void demo_floating_point_bs() {
    cout << "=== SECTION 9: FLOATING POINT BS ===" << endl;

    cout << "sqrt(2) = " << sqrtBS(2.0) << endl;
    cout << "sqrt(144) = " << sqrtBS(144.0) << endl;
    cout << "cbrt(27) = " << cbrtBS(27.0) << endl;
    cout << "cbrt(-8) = " << cbrtBS(-8.0) << endl;

    // Find x where x^2 + 3x - 10 = 0 (positive root)
    double root = findZero(0, 10, [](double x) { return x * x + 3 * x - 10; });
    cout << "Root of x²+3x-10: " << root << endl; // ≈ 2

    // Rope cutting
    vector<double> ropes = {4.0, 7.0, 3.5, 5.2};
    int k = 11;
    printf("Max rope length for %d pieces: %.4f\n", k, maxRopeLength(ropes, k));

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// BONUS: MORE CLASSIC PROBLEMS
// ═══════════════════════════════════════════════════════════════

// Smallest Divisor Given a Threshold (LC 1283)
int smallestDivisor(vector<int>& nums, int threshold) {
    auto check = [&](int div) -> bool {
        long long sum = 0;
        for (int x : nums) {
            sum += (x + div - 1) / div; // ceil(x/div)
        }
        return sum <= threshold;
    };

    int lo = 1, hi = *max_element(nums.begin(), nums.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// Minimum Days to Make M Bouquets (LC 1482)
int minDays(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();
    if ((long long)m * k > n) return -1;

    auto canMake = [&](int day) -> bool {
        int bouquets = 0, consecutive = 0;
        for (int i = 0; i < n; i++) {
            if (bloomDay[i] <= day) {
                consecutive++;
                if (consecutive >= k) {
                    bouquets++;
                    consecutive = 0;
                }
            } else {
                consecutive = 0;
            }
        }
        return bouquets >= m;
    };

    int lo = *min_element(bloomDay.begin(), bloomDay.end());
    int hi = *max_element(bloomDay.begin(), bloomDay.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canMake(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

void demo_bonus() {
    cout << "=== BONUS PROBLEMS ===" << endl;

    // Smallest Divisor
    vector<int> nums = {1, 2, 5, 9};
    int threshold = 6;
    cout << "Smallest divisor (threshold=" << threshold << "): "
         << smallestDivisor(nums, threshold) << endl; // 5

    // Min Days for Bouquets
    vector<int> bloom = {1, 10, 3, 10, 2};
    int m = 3, k = 1;
    cout << "Min days for " << m << " bouquets of " << k << ": "
         << minDays(bloom, m, k) << endl; // 3

    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   CHAPTER 07: BINARY SEARCH ON ANSWER                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;

    demo_monotonic();
    demo_feasibility();
    demo_minimize_max();
    demo_maximize_min();
    demo_aggressive_cows();
    demo_allocate_books();
    demo_painters_partition();
    demo_parametric_search();
    demo_floating_point_bs();
    demo_bonus();

    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "All Chapter 07 demos completed successfully!" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         PRACTICE PROBLEMS                                  ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                            ║
║  🟢 EASY:                                                                  ║
║  1. Sqrt(x) (LC 69)                                                       ║
║  2. First Bad Version (LC 278)                                             ║
║  3. Koko Eating Bananas (LC 875)                                           ║
║                                                                            ║
║  🟡 MEDIUM:                                                                ║
║  4. Capacity To Ship Packages (LC 1011)                                    ║
║  5. Split Array Largest Sum (LC 410)                                       ║
║  6. Smallest Divisor (LC 1283)                                             ║
║  7. Min Days for Bouquets (LC 1482)                                        ║
║  8. Magnetic Force (LC 1552) — Aggressive Cows                             ║
║  9. CSES — Factory Machines                                                ║
║ 10. CSES — Array Division                                                  ║
║ 11. Min Speed to Arrive on Time (LC 1870)                                  ║
║                                                                            ║
║  🔴 HARD:                                                                  ║
║ 12. SPOJ EKO — Cut wood                                                   ║
║ 13. SPOJ AGGRCOW — Aggressive Cows                                        ║
║ 14. CF 1201C — Maximum Median                                              ║
║ 15. CF 1117C — Magic Ship                                                  ║
║ 16. Allocate Books (GFG / InterviewBit)                                    ║
║                                                                            ║
║  🔵 GRANDMASTER:                                                           ║
║ 17. CF 1468C — Boredom                                                     ║
║ 18. CF 1623C — Balanced Stone Heaps                                        ║
║ 19. CF 1486D — Max Median (BS + prefix)                                    ║
║ 20. Parallel Binary Search (CF problems)                                   ║
║ 21. USACO — Haybale Feast                                                  ║
║                                                                            ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

