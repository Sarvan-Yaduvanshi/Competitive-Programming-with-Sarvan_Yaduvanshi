/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-30 23:49:43
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

/* Problem: Combination Sum III (LeetCode 216)
 * Difficulty: Medium
 * Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
 * Only numbers 1 through 9 are used.
 * Each number is used at most once.
 * Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.
 *
 * Example 1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 *
 * Example 2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6],[1,3,5],[2,3,4]]
 *
 * Example 3:
 * Input: k = 4, n = 1
 * Output: []
 *
 * Constraints:
 * 2 <= k <= 9
 * 1 <= n <= 60
 *
 * Topics: Backtracking, Recursion
 */

/*
	 * Core Idea:
	 * 1. No Physical Array: We don't need a vector for 1-9; we just loop 'i' from 1 to 9.
	 * 2. Strict Depth Pruning: Since we exactly need 'k' elements, the moment current.size()
	 *    equals 'k', we check if we hit the target. Regardless of the outcome, we return
	 *    immediately to prevent generating combinations of size k+1 or larger.
	 * 3. Capacity Pruning: We calculate how many more numbers we need ('needed'). If the
	 *    starting number is too high to provide 'needed' elements up to 9, we don't even loop.
	 * 4. Target Pruning: Because our loop goes in increasing order (1 to 9), if 'i > tar',
	 *    we break immediately as all subsequent numbers will also be too big.
	 *
	 * Time Complexity: O(9! / (k! * (9 - k)!)) -> O(1)
	 * - The absolute worst-case is choosing k items from 9, which is 9Ck (max 126 combinations).
	 * - With our aggressive pruning, we explore only a tiny fraction of that tree.
	 * - Since the input space is strictly bounded by numbers 1-9, it operates in O(1) time.
	 *
	 * Space Complexity: O(k)
	 * - The maximum depth of the recursion call stack is 'k'.
	 * - The 'current' vector holds at most 'k' elements.
	 * - (Excluding the memory required for the 'ans' output vector).
*/
static vector<vector<int>> combinationSum3(const int k, const int target){
	vector<vector<int>> ans;
	vector<int> current;
	current.reserve(k); // We know the exact max capacity we'll need

	// Lambda function for DFS with loop-based backtracking
	auto dfs = [&](auto&& self, const int start_idx, const int tar) -> void{
		// Base Case: If we have picked exactly k numbers
		if (current.size() == k){
			// If the sum of these k numbers equals the target, store the combination
			if (tar == 0)
				ans.emplace_back(current);
			return;
		}

		// Calculate how many more numbers we need to pick
		const int needed = k - current.size();
		// Calculate the maximum starting index to ensure we have enough numbers left to pick
		const int limit = 9 - needed + 1;

		// Loop through numbers starting from start_idx to limit
		for (int i = start_idx; i <= limit; i++){
			// If the current number exceeds the remaining target, break (pruning)
			// This is safe because the numbers are strictly increasing (1 to 9)
			if (i > tar)
				break;

			// Choose the current number and explore further
			current.emplace_back(i);
			// Pass 'i + 1' to ensure we don't reuse the same number
			self(self, i + 1, tar - i);
			current.pop_back(); // Backtrack to explore other combinations
		}
	};

	dfs(dfs, 1, target);
	return ans;
}

/*	 * Approach 2: Take/Not-Take style recursion (more common in interviews)
	 * Time Complexity: O(2^9) -> O(1)
	 * - For each number from 1 to 9, we have two choices: take or not take.
	 * - So the recursion explores at most 2^9 states (often fewer due to pruning).
	 * - Since 9 is fixed, this is constant time in strict asymptotic terms.
	 *
	 * Space Complexity: O(k)
	 * - The 'current' vector stores at most k picked elements.
	 * - Recursion depth can go up to 9 (constant), commonly expressed as O(9) -> O(1).
	 * - (Excluding the memory required for the 'ans' output vector).
*/
static vector<vector<int>> combinationSum3_v2(const int k, const int target){
	vector<vector<int>> ans;
	vector<int> current;
	current.reserve(k); // We know the exact max capacity we'll need

	// Lambda function for DFS with take/not-take recursion
	auto dfs = [&](auto&& self, const int num, const int tar) -> void{
		// Base Case: If we have picked exactly k numbers
		if (current.size() == k){
			// If the sum of these k numbers equals the target, store the combination
			if (tar == 0)
				ans.emplace_back(current);
			return;
		}

		// If we exceed the number 9 or the target becomes negative, return
		if (num > 9 || tar < 0)
			return;

		// Take the current number and explore further
		current.emplace_back(num);
		self(self, num + 1, tar - num); // Move to next number
		current.pop_back(); // Backtrack

		// Not take the current number and explore further
		self(self, num + 1, tar); // Move to next number without changing target
	};

	dfs(dfs, 1, target);
	return ans;
}
static void solve() {
    int k, n; cin >> k >> n;

	// Call the combinationSum3_v2 function to get all valid combinations
	// vector<vector<int>> result = combinationSum3_v2(k, n);

	// Call the combinationSum3 function to get all valid combinations
	vector<vector<int>> result = combinationSum3(k, n);
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

