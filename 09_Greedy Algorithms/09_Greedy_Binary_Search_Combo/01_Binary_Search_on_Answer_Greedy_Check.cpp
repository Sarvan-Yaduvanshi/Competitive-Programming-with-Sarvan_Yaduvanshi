/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Binary Search on Answer + Greedy Feasibility Check
 *  Level   : Advanced
 * ============================================================================
 *
 *  ▶ THE PATTERN:
 *  ──────────────
 *  Many optimization problems can be converted to decision problems:
 *  "Can we achieve answer X?" → Greedy check in O(N)
 *
 *  If the answer has MONOTONICITY (if X works, then X+1 also works),
 *  we can binary search on X!
 *
 *  TEMPLATE:
 *    lo = min_possible_answer
 *    hi = max_possible_answer
 *    while (lo < hi):
 *        mid = (lo + hi) / 2
 *        if canAchieve(mid):   // Greedy check
 *            hi = mid          // Try smaller (for minimize)
 *        else:
 *            lo = mid + 1
 *    return lo
 *
 *  ▶ COMMON PROBLEMS:
 *  ──────────────────
 *  1. Split Array Largest Sum (LC 410) — minimize the max subarray sum
 *  2. Capacity to Ship (LC 1011) — minimize ship capacity
 *  3. Koko Eating Bananas (LC 875) — minimize eating speed
 *  4. Factory Machines (CSES 1620) — minimize time
 *  5. Min Days for Bouquets (LC 1482) — minimize days
 *
 *  ▶ HOW TO IDENTIFY:
 *  ──────────────────
 *  Keywords: "minimize the maximum", "maximize the minimum", "find the minimum X such that..."
 *  If you see these, think BS + Greedy!
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

// ============================================================================
// LC 410: Split Array Largest Sum
// Split array into m subarrays, minimize the largest subarray sum
// ============================================================================
bool canSplit(vector<int>& nums, int m, long long maxSum) {
    int count = 1;
    long long current = 0;
    for (int x : nums) {
        if (current + x > maxSum) {
            count++;
            current = x;
            if (count > m) return false;
        } else {
            current += x;
        }
    }
    return true;
}

int splitArray(vector<int>& nums, int m) {
    long long lo = *max_element(nums.begin(), nums.end());
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canSplit(nums, m, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return (int)lo;
}

// ============================================================================
// LC 1011: Capacity to Ship Packages Within D Days
// ============================================================================
bool canShip(vector<int>& weights, int days, int capacity) {
    int d = 1, current = 0;
    for (int w : weights) {
        if (current + w > capacity) {
            d++;
            current = w;
            if (d > days) return false;
        } else {
            current += w;
        }
    }
    return true;
}

int shipWithinDays(vector<int>& weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canShip(weights, days, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// ============================================================================
// LC 875: Koko Eating Bananas
// ============================================================================
bool canEat(vector<int>& piles, int h, int speed) {
    long long hours = 0;
    for (int p : piles) {
        hours += (p + speed - 1) / speed; // ceil(p / speed)
    }
    return hours <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canEat(piles, h, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// ============================================================================
// CSES 1620: Factory Machines — Minimize time to produce t products
// ============================================================================
bool canProduce(vector<long long>& machines, long long t, long long time) {
    long long total = 0;
    for (long long m : machines) {
        total += time / m;
        if (total >= t) return true; // Early exit
    }
    return total >= t;
}

long long factoryMachines(vector<long long>& machines, long long t) {
    long long lo = 1, hi = *min_element(machines.begin(), machines.end()) * t;

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canProduce(machines, t, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

// ============================================================================
// LC 1482: Minimum Number of Days to Make m Bouquets
// ============================================================================
bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int day) {
    int bouquets = 0, consecutive = 0;
    for (int b : bloomDay) {
        if (b <= day) {
            consecutive++;
            if (consecutive == k) {
                bouquets++;
                consecutive = 0;
            }
        } else {
            consecutive = 0;
        }
    }
    return bouquets >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    if ((long long)m * k > (long long)bloomDay.size()) return -1;

    int lo = *min_element(bloomDay.begin(), bloomDay.end());
    int hi = *max_element(bloomDay.begin(), bloomDay.end());

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canMakeBouquets(bloomDay, m, k, mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

int main() {
    // LC 410
    vector<int> nums = {7, 2, 5, 10, 8};
    cout << "Split Array (m=2): " << splitArray(nums, 2) << endl; // 18

    // LC 1011
    vector<int> weights = {1,2,3,4,5,6,7,8,9,10};
    cout << "Ship (days=5): " << shipWithinDays(weights, 5) << endl; // 15

    // LC 875
    vector<int> piles = {3, 6, 7, 11};
    cout << "Koko speed (h=8): " << minEatingSpeed(piles, 8) << endl; // 4

    // CSES 1620
    vector<long long> machines = {3, 2, 5};
    cout << "Factory time (t=8): " << factoryMachines(machines, 8) << endl; // 12

    // LC 1482
    vector<int> bloom = {1, 10, 3, 10, 2};
    cout << "Min days (m=3, k=1): " << minDays(bloom, 3, 1) << endl; // 3

    return 0;
}

