/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-29 16:52:57
*/

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

/*
Problem: Combination Sum (LeetCode 39)
Problem statement: Given an array of distinct integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers sum to target.
You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times.
Two combinations are unique if the frequency of at least one of the chosen numbers is different.
It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []

Constraints:
1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500
*/

// Approach 1: Take/NotTake with duplicate skipping
static vector<vector<int>> combinationSum(vector<int>& candidates, int target){
    int n = candidates.size();
    vector<vector<int>> ans;
    vector<int> current;

    auto dfs = [&](auto&& self, const int idx, const int tar) -> void{
        // Base Case
        if (tar == 0){
            ans.emplace_back(current);
            return;
        }

        // Invalid Case: if we have exhausted all candidates or the target has gone negative
        if (idx == n || tar < 0)
            return;

        // TAKE cand[index] — stay at SAME index (can reuse!)
        if (candidates[idx] <= tar){
            current.emplace_back(candidates[idx]);
            self(self, idx, tar - candidates[idx]);
            current.pop_back();
        }

        // NOT TAKE — move to next index
        self(self, idx + 1, tar);
    };

    dfs(dfs, 0, target);
    return ans;
}

/* Approach 2: Loop-based Backtracking (more common in interviews) (optimized)
 * Core Idea:
 * 1. Sort the candidates first. This allows us to stop early (prune) when a candidate
 *    exceeds the remaining target, preventing useless recursive calls.
 * 2. Use a loop-based backtracking approach instead of Take/Not-Take. We iterate from
 *    the current 'idx' to 'n-1'.
 * 3. At each step, if candidates[i] > target, we 'break' the loop entirely because
 *    the array is sorted and all subsequent numbers will also be too large.
 * 4. We pass 'i' (not i + 1) into the next recursive call to allow reusing the same element.
 *
 * Time Complexity: O(N^(T/M) + N log N)
 * - N is candidates.size(), T is the target, and M is the minimum value in candidates.
 * - N log N is for sorting.
 * - The recursion tree can go as deep as T/M (e.g., target 10, min element 2, max depth 5).
 * - The number of nodes in the worst case is loosely bounded by N^(T/M).
 *
 * Space Complexity: O(T/M)
 * - The space is dictated by the maximum depth of the recursion tree (call stack)
 *   and the 'current' vector storing the path. In the worst case, this is T/M.
 * - (Note: We do not count the space used to store the final answers).
 */
static vector<vector<int>> combinationSumOptimized(vector<int>& candidates, int target){
    // Sorting is the key to GM-level optimization here
    ranges::sort(candidates);

    vector<vector<int>> ans;
    vector<int> current;

    // Lambda function for DFS with loop-based backtracking
    auto dfs = [&](auto&& self, const int start_idx, const int tar) -> void{
        // Base Case: Target is met
        if (tar == 0){
            ans.emplace_back(current); // emplace_back is slightly faster than push_back
            return;
        }

        // Loop-based exploration from start_idx to end of candidates
        for (int i = start_idx; i < candidates.size(); i++){
            // GM Pruning: If the current number is strictly greater than the remaining target,
            // we can stop the loop completely because all future numbers are even bigger.
            if (candidates[i] > tar)
                break;

            current.emplace_back(candidates[i]);

            // Pass 'i' instead of 'i + 1' because we are allowed to reuse the same number
            self(self, i, tar - candidates[i]);
            current.pop_back(); // Backtrack to explore other combinations
        }
    };

    dfs(dfs, 0, target);
    return ans;
}


static void solve() {
    int n, target;
    cin >> n >> target;

    vector<int> candidates(n);
    for (auto &x : candidates)
        cin >> x;

    // vector<vector<int>> result = combinationSum(candidates, target);

    // Using the optimized version
    vector<vector<int>> result = combinationSumOptimized(candidates, target);
    cout << "[";
    for (int i = 0; i < result.size(); i++){
        cout << "[";
        for (int j = 0; j < result[i].size(); j++){
            cout << result[i][j];
            if (j + 1 < result[i].size())
                cout << ", ";
        }
        cout << "]";
        if (i + 1 < result.size())
            cout << ", ";
    }
    cout << "]\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

