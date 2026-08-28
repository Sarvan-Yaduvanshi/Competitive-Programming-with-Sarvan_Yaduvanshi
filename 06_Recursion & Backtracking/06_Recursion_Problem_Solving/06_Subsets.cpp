/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-22 14:28:24
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
 🎯 Problems in this file:
    1. Leetcode 78: Generate all subsets (Power Set)
	2. Leetcode 90: Subsets II (with duplicates)
	3.
	4. Check if ANY subsequence has sum = K
	5. Generate all subsets (Power Set) — LC 78
*/

/*
 * Problem 1: Generate all subsets (Power Set) — LeetCode 78
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * Examples:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 * Input: nums = [0]
 * Output: [[],[0]]
 * Constraints:
 * 1 ≤ nums.length ≤ 10
 * -10 ≤ nums[i] ≤ 10
 * All the numbers of nums are unique.
 * Topics: Recursion, Backtracking, Subset Generation, Bit Manipulation
 * Expected Complexities:
 * Time Complexity: O(2^N * N) && Auxiliary Space: O(N)
 */

vector<vector<int>> subsets(vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> curr_subset;

	auto isGenerateSubset = [&](auto&& self, const int idx) -> void{
		// Base Case
		if (idx == nums.size()){
			ans.push_back(curr_subset);
			return;
		}

		// Choice 1: Not Take
		self(self, idx + 1);

		// Choice 2: Take
		curr_subset.push_back(nums[idx]);
		self(self, idx + 1);
		curr_subset.pop_back();
	};

	isGenerateSubset(isGenerateSubset, 0);
	return ans;
}

/*
 * Problem 2: Generate all subsets (Power Set) with duplicates — LeetCode 90
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * Examples:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[2],[1,2],[2,2],[1,2,2]]
 * Input: nums = [0]
 * Output: [[],[0]]
 * Constraints:
 * 1 ≤ nums.length ≤ 10
 * -10 ≤ nums[i] ≤ 10
 * Topics: Recursion, Backtracking, Subset Generation, Bit Manipulation
 * Expected Complexities:
 * Time Complexity: O(2^N * N) && Auxiliary Space: O(N)
 */
vector<vector<int>> subsetsWithDup(vector<int>& nums){
	ranges::sort(nums); // Still MUST sort first!
	vector<vector<int>> ans;
	vector<int> curr_subset;

	auto isGenerateSubset = [&](auto&& self, const int idx) -> void{
		// 1. In this template, EVERY recursive call represents a valid subset!
		// So we add it to the answer immediately, without waiting for a base case.
		ans.push_back(curr_subset);

		// 2. Explore all possible elements we can add to our current subset
		for (int i = idx; i < nums.size(); i++){
			// --- THE MAGIC DUPLICATE SKIPPER ---
			// If this is NOT the first element we are picking in this loop,
			// and it is identical to the previous element, skip it!
			if (i > idx && nums[i] == nums[i - 1])
				continue;

			curr_subset.push_back(nums[i]); // TAKE
			self(self, i + 1); // EXPLORE (Pass i + 1, not idx + 1)
			curr_subset.pop_back(); // BACKTRACK
		}
	};

	isGenerateSubset(isGenerateSubset, 0);
	return ans;
}
void solve() {
    int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums)
		cin >> x;

	// Test LeetCode 78: Generate all subsets (Power Set)
	vector<vector<int>> ans = subsets(nums);
	cout << "[";
	for (int i = 0; i < ans.size(); i++){
		cout << "[";
		for (int j = 0; j < ans[i].size(); j++){
			cout << ans[i][j] << (j == ans[i].size() - 1 ? "" : ", ");
		}
		cout << "]" << (i == ans.size() - 1 ? "" : ", ");
	}
	cout << "]\n";

	// Test LeetCode 90: Generate all subsets (Power Set) with duplicates
	vector<vector<int>> ans_with_dup = subsetsWithDup(nums);
	cout << "[";
	for (int i = 0; i < ans_with_dup.size(); i++){
		cout << "[";
		for (int j = 0; j < ans_with_dup[i].size(); j++){
            cout << ans_with_dup[i][j] << (j == ans_with_dup[i].size() - 1 ? "" : ", ");
        }
		cout << "]" << (i == ans_with_dup.size() - 1 ? "" : ", ");
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

