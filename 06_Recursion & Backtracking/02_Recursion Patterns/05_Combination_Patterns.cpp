/*
╔══════════════════════════════════════════════════════════════╗
║  05. COMBINATION PATTERNS — Combination Sum I, II, III       ║
║  Level 2 — Recursion Patterns                                ║
╚══════════════════════════════════════════════════════════════╝

These are CLASSIC interview + CP problems. All use Take/Not-Take
with small variations.

🎯 Problems:
   1. Combination Sum I  — LC 39 (unlimited reuse, distinct elements)
   2. Combination Sum II — LC 40 (each used once, may have duplicates)
   3. Combination Sum III — LC 216 (k numbers, no duplicates, sum=n)
   4. Subsets II — LC 90 (subsets with duplicates in input)

════════════════════════════════════════════════════════════════
🧠 KEY DIFFERENCES:
════════════════════════════════════════════════════════════════

| Problem        | Reuse element? | Input has dups? | Avoid dup results? |
|----------------|----------------|-----------------|---------------------|
| Combination I  | YES            | NO              | NO                  |
| Combination II | NO             | YES             | YES (sort + skip)   |
| Combination III| NO             | NO              | NO                  |
| Subsets II     | NO             | YES             | YES (sort + skip)   |

════════════════════════════════════════════════════════════════
🔑 HOW TO HANDLE DUPLICATES:
════════════════════════════════════════════════════════════════

1. SORT the array first
2. In the "not take" branch, SKIP all consecutive duplicates:

   while (index + 1 < n && arr[index] == arr[index + 1]) index++;

   This ensures duplicate values only generate ONE branch.

════════════════════════════════════════════════════════════════
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define pb push_back
#define nl '\n'

template<class T>
void read(vec<T> &v) {
    for (auto &x : v) cin >> x;
}


// ═══════════════════════════════════════════════════════════
// 1️⃣ COMBINATION SUM I — LC 39
// ═══════════════════════════════════════════════════════════
/*
   Given distinct integers and a target, find all UNIQUE combinations
   where chosen numbers sum to target. Same number may be used
   UNLIMITED times.

   candidates = [2,3,6,7], target = 7
   Output: [[2,2,3], [7]]

   🧠 KEY: When we TAKE, we DON'T move to index+1. We stay at same
   index because we can reuse!

   Time: O(2^t) where t = target/min_element (branching factor)
*/
void combinationSum1(vec<int>& cand, int index, int target,
                     vec<int>& current, vec<vec<int>>& result) {
    // Base cases
    if (target == 0) {
        result.pb(current);
        return;
    }
    if (index == sz(cand) || target < 0) return;

    // TAKE cand[index] — stay at SAME index (can reuse!)
    if (cand[index] <= target) {
        current.pb(cand[index]);
        combinationSum1(cand, index, target - cand[index], current, result);
        current.pop_back();
    }

    // NOT TAKE — move to next index
    combinationSum1(cand, index + 1, target, current, result);
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ COMBINATION SUM II — LC 40
// ═══════════════════════════════════════════════════════════
/*
   Each number may be used ONCE. Input may contain DUPLICATES.
   Find all unique combinations that sum to target.

   candidates = [10,1,2,7,6,1,5], target = 8
   Output: [[1,1,6], [1,2,5], [1,7], [2,6]]

   🧠 KEY: Sort first. When we "NOT TAKE", skip all duplicates.

   Alternative approach: iterate from index, skip if same as prev.
*/

// Approach 1: Take/NotTake with duplicate skipping
void combinationSum2_v1(vec<int>& cand, int index, int target,
                        vec<int>& current, vec<vec<int>>& result) {
    if (target == 0) {
        result.pb(current);
        return;
    }
    if (index == sz(cand) || target < 0) return;

    // TAKE cand[index] — move to index+1 (can't reuse)
    current.pb(cand[index]);
    combinationSum2_v1(cand, index + 1, target - cand[index], current, result);
    current.pop_back();

    // NOT TAKE — skip ALL duplicates of cand[index]
    int skip = index;
    while (skip + 1 < sz(cand) && cand[skip + 1] == cand[index]) skip++;
    combinationSum2_v1(cand, skip + 1, target, current, result);
}

// Approach 2: Loop-based (more common in interviews)
void combinationSum2_v2(vec<int>& cand, int start, int target,
                        vec<int>& current, vec<vec<int>>& result) {
    if (target == 0) {
        result.pb(current);
        return;
    }

    for (int i = start; i < sz(cand); i++) {
        // Skip duplicates: if cand[i] == cand[i-1], skip (same level)
        if (i > start && cand[i] == cand[i - 1]) continue;

        if (cand[i] > target) break;  // Pruning (array is sorted)

        current.pb(cand[i]);
        combinationSum2_v2(cand, i + 1, target - cand[i], current, result);
        current.pop_back();
    }
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ COMBINATION SUM III — LC 216
// ═══════════════════════════════════════════════════════════
/*
   Find all valid combinations of k numbers (from 1-9) that sum to n.
   Each number used at most once.

   k=3, n=7 → Output: [[1,2,4]]
   k=3, n=9 → Output: [[1,2,6], [1,3,5], [2,3,4]]
*/
void combinationSum3(int num, int k, int target,
                     vec<int>& current, vec<vec<int>>& result) {
    if (sz(current) == k) {
        if (target == 0) result.pb(current);
        return;
    }
    if (num > 9 || target < 0) return;

    // TAKE num
    current.pb(num);
    combinationSum3(num + 1, k, target - num, current, result);
    current.pop_back();

    // NOT TAKE num
    combinationSum3(num + 1, k, target, current, result);
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ SUBSETS II — LC 90
// ═══════════════════════════════════════════════════════════
/*
   Given array with possible duplicates, return all unique subsets.

   nums = [1, 2, 2]
   Output: [[], [1], [1,2], [1,2,2], [2], [2,2]]

   🧠 Same duplicate-skipping technique as Combination Sum II
*/
void subsetsWithDup(vec<int>& nums, int index,
                    vec<int>& current, vec<vec<int>>& result) {
    if (index == sz(nums)) {
        result.pb(current);
        return;
    }

    // TAKE nums[index]
    current.pb(nums[index]);
    subsetsWithDup(nums, index + 1, current, result);
    current.pop_back();

    // NOT TAKE — skip duplicates
    int skip = index;
    while (skip + 1 < sz(nums) && nums[skip + 1] == nums[index]) skip++;
    subsetsWithDup(nums, skip + 1, current, result);
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST ALL FUNCTIONS
// ═══════════════════════════════════════════════════════════

void printResult(vec<vec<int>>& result) {
    cout << "[" << nl;
    for (auto& v : result) {
        cout << "  [";
        for (int i = 0; i < sz(v); i++) {
            cout << v[i] << (i + 1 < sz(v) ? "," : "");
        }
        cout << "]" << nl;
    }
    cout << "]" << nl;
}

void solve() {
    // 1. Combination Sum I
    {
        cout << "=== COMBINATION SUM I ===" << nl;
        cout << "candidates=[2,3,6,7], target=7" << nl;
        vec<int> cand = {2, 3, 6, 7};
        vec<int> cur;
        vec<vec<int>> res;
        combinationSum1(cand, 0, 7, cur, res);
        printResult(res);
    }

    // 2. Combination Sum II
    {
        cout << nl << "=== COMBINATION SUM II ===" << nl;
        cout << "candidates=[10,1,2,7,6,1,5], target=8" << nl;
        vec<int> cand = {10, 1, 2, 7, 6, 1, 5};
        sort(all(cand));  // MUST SORT for duplicate handling!
        vec<int> cur;
        vec<vec<int>> res;
        combinationSum2_v2(cand, 0, 8, cur, res);
        printResult(res);
    }

    // 3. Combination Sum III
    {
        cout << nl << "=== COMBINATION SUM III ===" << nl;
        cout << "k=3, n=9" << nl;
        vec<int> cur;
        vec<vec<int>> res;
        combinationSum3(1, 3, 9, cur, res);
        printResult(res);
    }

    // 4. Subsets II
    {
        cout << nl << "=== SUBSETS II ===" << nl;
        cout << "nums=[1,2,2]" << nl;
        vec<int> nums = {1, 2, 2};
        sort(all(nums));  // MUST SORT!
        vec<int> cur;
        vec<vec<int>> res;
        subsetsWithDup(nums, 0, cur, res);
        printResult(res);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

