/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-30 23:48:44
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


/* Problem: Combination Sum II (LeetCode 40)
 * Difficulty: Medium
 * Given a collection of candidate numbers (candidates) and a target number (target),
 * find all unique combinations in candidates where the candidate numbers sum to target.
 * Each number in candidates may only be used once in the combination.
 * Note: The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
 *
 * Example 2:
 * Input: candidates = [2,5,2,1,2], target = 5
 * Output: [[1,2,2],[5]]
 *
 * Constraints:
 * 1 <= candidates.length <= 100
 * 1 <= candidates[i] <= 50
 * 1 <= target <= 30
 *
 * Topics: Backtracking, Recursion
 */

// Approach 1: Take/NotTake with duplicate skipping (Approach 2 is more common in interviews)
// Time Complexity: O(nlogn + 2^n * n) where n = candidates.size(), why *n ? because emplace_back(current) takes O(n) time in the worst case (when current has n elements).
// Space Complexity: O(n) for recursion stack + O(n) for current vector, not counting the output vector ans.
static vector<vector<int>> combinationSum2Better(vector<int>& candidates, const int target){
	// Sorting is the key to GM-level optimization here
	ranges::sort(candidates);

	vector<vector<int>> ans;
	vector<int> current;

	// Lambda function for DFS with Take/Not-Take and duplicate skipping
	auto dfs = [&](auto&& self, const int start_idx, const int tar) -> void{
		// Base Case: Target is met perfectly
		if (tar == 0){
			ans.emplace_back(current);
			return;
		}

		// Since array is sorted, if current candidate is too large,
		// all remaining candidates will also be too large.
		if (start_idx >= candidates.size() || candidates[start_idx] > tar)
			return;

		// Choice 1: Take
		// Take current candidate.
		// Move to start_idx + 1 because each element can be used only once.
		current.emplace_back(candidates[start_idx]);
		self(self, start_idx + 1, tar - candidates[start_idx]);
		current.pop_back(); // Backtrack to explore other combinations (Not-Take)

		// Choice 2: NOT TAKE — skip ALL duplicates of cand[index]
		int next_idx = start_idx + 1;
		while (next_idx < candidates.size() && candidates[next_idx] == candidates[start_idx])
			next_idx++;

		// Explore the Not-Take branch with the next unique candidate
		self(self, next_idx, tar);
	};

	dfs(dfs, 0, target);
	return ans;
}

/*
	 * Core Idea:
	 * 1. Sort the candidates to enable both branch pruning and easy duplicate detection.
	 * 2. Loop through candidates starting from 'start_num'. If a candidate exceeds the
	 *    remaining target, 'break' the loop (since all subsequent numbers are larger).
	 * 3. To avoid duplicate combinations, skip a number if it is the same as the previous
	 *    number AND it is not the first number picked in the current recursion depth.
	 *    (i.e., i > start_num && candidates[i] == candidates[i-1]).
	 * 4. Pass 'i + 1' to the recursive call because each number can only be used once.
	 *
	 * Time Complexity: O(2^N)
	 * - In the worst-case scenario (e.g., all 1s and target is the sum of all 1s),
	 *   the algorithm explores all possible subsets, which is 2^N.
	 * - The sorting step takes O(N log N), which is dominated by the recursive traversal.
	 *
	 * Space Complexity: O(N)
	 * - 'N' is candidates.size().
	 * - The recursion call stack can go as deep as N in the worst case.
	 * - The 'current' vector also stores at most N elements.
	 * - (We do not count the space required for the output 'ans' array).
	 */
// Approach 2: Loop-based Backtracking (more common in interviews)
static vector<vector<int>> combinationSum2Optimal(vector<int>& candidates, int target){
	// Sorting is the key to GM-level optimization here
	ranges::sort(candidates);

	vector<vector<int>> ans;
	vector<int> current;

	// Lambda function for DFS with loop-based backtracking
	auto dfs = [&](auto&& self, const int start_idx, const int tar) -> void{
		// Base Case: Target is met perfectly
		if (tar == 0){
			ans.emplace_back(current);
			return;
		}

		// Loop-based exploration from start_idx to end of candidates
		for (int i = start_idx; i < candidates.size(); i++){
			// Pruning: Array is sorted, so subsequent numbers will also be too big
			if (candidates[i] > tar)
				break;

			// Skip duplicates: if the current number is the same as the previous number
			if (i > start_idx && candidates[i] == candidates[i - 1])
				continue;

			// Choose the current candidate and explore further
			current.emplace_back(candidates[i]);

			// Move to i + 1 to ensure each element is only used once
			self(self, i + 1, tar - candidates[i]);
			current.pop_back(); // Backtrack to explore other combinations
		}
	};

	dfs(dfs, 0, target);
	return ans;
}

void solve() {
    int n, target;
	cin >> n >> target;

	vector<int> candidates(n);
	for (auto &x : candidates)
		cin >> x;

	// Call the combinationSum2Better function to get all unique combinations
	// vector<vector<int>> result = combinationSum2Better(candidates, target);

	// Call the combinationSum2Optimal function to get all unique combinations
	vector<vector<int>> result = combinationSum2Optimal(candidates, target);
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

