/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : K Closest Elements, Subsequences Satisfy Sum,
 *            Successful Pairs, Subarray Distinct Values
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  LC 658  — Find K Closest Elements (BS + Two Pointer shrink)
 *            https://leetcode.com/problems/find-k-closest-elements/
 *
 *  LC 1498 — Number of Subsequences That Satisfy the Given Sum Condition
 *            https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 *
 *  LC 2300 — Successful Pairs of Spells and Potions (sort + BS)
 *            https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
 *
 *  CSES 2428 — Subarray Distinct Values (two pointer + map)
 *              https://cses.fi/problemset/task/2428
 *
 *  LC 826  — Most Profit Assigning Work (sort + two pointer)
 *            https://leetcode.com/problems/most-profit-assigning-work/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

// Fast power for modular exponentiation
ll power(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// ============================================================================
// LC 658: Find K Closest Elements — Binary Search + Two Pointer Shrink
// ============================================================================
/*
 * Sorted array. Find k closest elements to value x.
 *
 * APPROACH: Start with the full array as a window of size n.
 * Shrink from the end that is farther from x, until window has size k.
 *
 * Alternatively: Binary search for the left boundary of the k-length window.
 *
 * Time: O(N - K) or O(log N + K), Space: O(1) extra
 */

// Approach 1: Two pointer shrink
vector<int> findClosestElements_2ptr(vector<int>& arr, int k, int x) {
    int left = 0, right = (int)arr.size() - 1;

    while (right - left + 1 > k) {
        // Remove the element farther from x
        if (abs(arr[left] - x) > abs(arr[right] - x))
            left++;
        else
            right--;
    }
    return vector<int>(arr.begin() + left, arr.begin() + right + 1);
}

// Approach 2: Binary search for left bound (optimal)
vector<int> findClosestElements_bs(vector<int>& arr, int k, int x) {
    int lo = 0, hi = (int)arr.size() - k;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        // Compare: is mid or mid+k closer to x?
        if (x - arr[mid] > arr[mid + k] - x)
            lo = mid + 1;
        else
            hi = mid;
    }
    return vector<int>(arr.begin() + lo, arr.begin() + lo + k);
}

// ============================================================================
// LC 1498: Number of Subsequences That Satisfy the Given Sum Condition
// ============================================================================
/*
 * Count non-empty subsequences where min + max ≤ target.
 *
 * KEY INSIGHT: Sort the array. If a[left] + a[right] ≤ target:
 * - a[left] is the min, a[right] is the max of any subsequence
 *   using elements in [left..right]
 * - The elements in between can be freely included or excluded
 * - That gives 2^(right - left) subsequences
 *
 * Use two pointer: fix left, find rightmost right where sum ≤ target.
 *
 * Time: O(N log N), Space: O(N) for precomputing powers
 */
int numSubseq(vector<int>& nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());

    // Precompute powers of 2
    vector<ll> pow2(n);
    pow2[0] = 1;
    for (int i = 1; i < n; i++)
        pow2[i] = pow2[i - 1] * 2 % MOD;

    ll result = 0;
    int left = 0, right = n - 1;

    while (left <= right) {
        if (nums[left] + nums[right] <= target) {
            result = (result + pow2[right - left]) % MOD;
            left++;
        } else {
            right--;
        }
    }
    return (int)result;
}

// ============================================================================
// LC 2300: Successful Pairs of Spells and Potions — Sort + Binary Search
// ============================================================================
/*
 * For each spell, count potions where spell * potion >= success.
 * Sort potions. For each spell, binary search for minimum potion
 * that satisfies: potion >= ceil(success / spell).
 *
 * Time: O((N + M) log M), Space: O(1) extra
 */
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
    sort(potions.begin(), potions.end());
    int m = potions.size();
    vector<int> result;

    for (int spell : spells) {
        // Need potion >= ceil(success / spell)
        ll minPotion = (success + spell - 1) / spell;
        // Binary search: first potion >= minPotion
        int idx = (int)(lower_bound(potions.begin(), potions.end(), (int)minPotion) - potions.begin());
        result.push_back(m - idx);
    }
    return result;
}

// ============================================================================
// CSES 2428: Subarray Distinct Values — Two Pointer + HashMap
// ============================================================================
/*
 * Count subarrays with at most K distinct values.
 * Classic variable two pointer with hashmap.
 *
 * For each right, shrink left until distinct count ≤ K.
 * count += (right - left + 1) for all valid subarrays ending at right.
 *
 * Time: O(N), Space: O(K)
 */
ll subarrayDistinctValues(vector<int>& a, int k) {
    int n = a.size();
    unordered_map<int, int> freq;
    ll count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        freq[a[right]]++;
        while ((int)freq.size() > k) {
            freq[a[left]]--;
            if (freq[a[left]] == 0) freq.erase(a[left]);
            left++;
        }
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// LC 826: Most Profit Assigning Work — Sort + Two Pointer
// ============================================================================
/*
 * Workers have abilities, jobs have (difficulty, profit).
 * Each worker does at most one job (difficulty ≤ ability).
 * Maximize total profit.
 *
 * Sort jobs by difficulty, sort workers by ability.
 * Two pointer: for each worker, advance job pointer to find best profit.
 *
 * Time: O(N log N + M log M), Space: O(N)
 */
int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    int n = difficulty.size();
    vector<pair<int,int>> jobs(n);
    for (int i = 0; i < n; i++)
        jobs[i] = {difficulty[i], profit[i]};
    sort(jobs.begin(), jobs.end());
    sort(worker.begin(), worker.end());

    int totalProfit = 0, bestProfit = 0, j = 0;
    for (int ability : worker) {
        while (j < n && jobs[j].first <= ability) {
            bestProfit = max(bestProfit, jobs[j].second);
            j++;
        }
        totalProfit += bestProfit;
    }
    return totalProfit;
}

int main() {
    // LC 658: K Closest Elements
    vector<int> arr = {1, 2, 3, 4, 5};
    auto res = findClosestElements_2ptr(arr, 4, 3);
    cout << "K Closest: ";
    for (int x : res) cout << x << " ";
    cout << "\n"; // 1 2 3 4

    // LC 1498: Subsequences Satisfy Sum
    vector<int> nums = {3, 5, 6, 7};
    cout << "Subsequences (target=9): " << numSubseq(nums, 9) << "\n"; // 4

    // CSES 2428: Subarray Distinct Values
    vector<int> a = {1, 2, 1, 3, 2};
    cout << "Subarrays with ≤2 distinct: " << subarrayDistinctValues(a, 2) << "\n"; // 10

    // LC 826: Most Profit
    vector<int> diff = {2, 4, 6, 8, 10};
    vector<int> prof = {10, 20, 30, 40, 50};
    vector<int> workers = {4, 5, 6, 7};
    cout << "Max profit: " << maxProfitAssignment(diff, prof, workers) << "\n"; // 100

    return 0;
}

