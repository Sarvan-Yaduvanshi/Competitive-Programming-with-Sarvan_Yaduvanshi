/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy Validation Functions in Binary Search
 *  Level   : Advanced
 * ============================================================================
 *
 *  ▶ WRITING A GOOD GREEDY CHECK FUNCTION:
 *  ────────────────────────────────────────
 *  The check function must be:
 *  1. O(N) or O(N log N) — can't be too slow
 *  2. Monotonic — if check(x) is true, then check(x+1) must also be true
 *     (or vice versa for "maximize the minimum")
 *  3. GREEDY — simulate the process with the candidate answer
 *
 *  ▶ MAXIMIZE THE MINIMUM PATTERN:
 *  ───────────────────────────────
 *  "Place K items to maximize minimum distance between any two"
 *  BS: Binary search on the minimum distance D
 *  Check: Can we place K items with min distance ≥ D? (Greedy: place as early as possible)
 *
 *  ▶ MINIMIZE THE MAXIMUM PATTERN:
 *  ───────────────────────────────
 *  "Split array to minimize the maximum sum"
 *  BS: Binary search on the maximum sum S
 *  Check: Can we split into ≤ K subarrays with each sum ≤ S? (Greedy: fill greedily)
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
// MAXIMIZE THE MINIMUM: Aggressive Cows / Magnetic Balls
// Place C cows in N stalls to maximize minimum distance
// ============================================================================
bool canPlaceCows(vector<int>& stalls, int c, int minDist) {
    int placed = 1, lastPos = stalls[0];

    for (int i = 1; i < (int)stalls.size(); i++) {
        if (stalls[i] - lastPos >= minDist) {
            placed++;
            lastPos = stalls[i];
            if (placed >= c) return true;
        }
    }
    return placed >= c;
}

int aggressiveCows(vector<int>& stalls, int c) {
    sort(stalls.begin(), stalls.end());
    int lo = 1, hi = stalls.back() - stalls[0];

    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // Upper mid for maximize
        if (canPlaceCows(stalls, c, mid))
            lo = mid;       // Can achieve this distance, try larger
        else
            hi = mid - 1;   // Can't achieve, try smaller
    }
    return lo;
}

// ============================================================================
// LC 2064: Minimized Maximum of Products Distributed to Any Store
// Distribute products to stores, minimize max products per store
// ============================================================================
bool canDistribute(vector<int>& quantities, int n, int maxPerStore) {
    int storesNeeded = 0;
    for (int q : quantities) {
        storesNeeded += (q + maxPerStore - 1) / maxPerStore;
        if (storesNeeded > n) return false;
    }
    return true;
}

int minimizedMaximum(int n, vector<int>& quantities) {
    int lo = 1, hi = *max_element(quantities.begin(), quantities.end());

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canDistribute(quantities, n, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// ============================================================================
// LC 2226: Maximum Candies Allocated to K Children
// Maximize candies each child gets (equal distribution)
// ============================================================================
bool canGiveCandies(vector<int>& candies, long long k, int each) {
    long long count = 0;
    for (int c : candies) {
        count += c / each;
        if (count >= k) return true;
    }
    return count >= k;
}

int maximumCandies(vector<int>& candies, long long k) {
    int lo = 0, hi = *max_element(candies.begin(), candies.end());

    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (canGiveCandies(candies, k, mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

int main() {
    // Aggressive Cows
    vector<int> stalls = {1, 2, 4, 8, 9};
    cout << "Max min distance (3 cows): " << aggressiveCows(stalls, 3) << endl; // 3

    // Minimized Maximum
    vector<int> quantities = {11, 6};
    cout << "Min max per store (n=6): " << minimizedMaximum(6, quantities) << endl; // 3

    // Maximum Candies
    vector<int> candies = {5, 8, 6};
    cout << "Max candies (k=3): " << maximumCandies(candies, 3) << endl; // 5

    return 0;
}

