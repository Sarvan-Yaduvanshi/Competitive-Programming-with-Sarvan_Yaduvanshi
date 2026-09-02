/*
Author: Sarvan Yaduvanshi
Created : 2026-08-30 23:55:10
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
Problem: Non-decreasing Subsequences (Leetcode 491)
Difficulty: Medium
Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements.
You may return the answer in any order.

Example 1: Input: nums = [4,6,7,7]
		   Output: [[4,6],[4,7],[4,6,7],[4,6,7,7],[6,7],[6,7,7],[7,7],[4,7,7]]
Explanation: The non-decreasing subsequences of the array are shown above. Note that duplicates are not allowed in the answer.

Example 2: Input: nums = [4,4,3,2,1]
           Output: [[4,4]]
Explanation: The only non-decreasing subsequence of the array is [4,4].

Constraints:
	1 <= nums.length <= 15
    100 <= nums[i] <= 100
Topics: Backtracking, Array, Hash Table, Recursion
*/

/*	Approach 1: implementation using a loop-based Backtracking tree instead of Take/Not-Take.
	 * Core Idea:
	 * 1. Since this is a subsequence problem, we CANNOT sort 'nums' to group duplicates.
	 * 2. To avoid generating duplicate combinations, we use a local 'seen' boolean array
	 *    inside the recursive function to track which numbers we've branched on at the
	 *    CURRENT depth level.
	 * 3. The constraints say numbers are between -100 and 100. We map this to 0-200
	 *    by adding 100 to the number when accessing the boolean array.
	 * 4. We only pick a number if it is greater than or equal to the last picked number.
	 *
	 * Time Complexity: O(2^N)
	 * - N is the length of the array (max 15).
	 * - In the worst case, every element is increasing and unique, so we generate 2^N states.
	 * - We completely eliminate the O(K log K) time (where K is the number of combinations)
	 *   that was required to sort the 2D vector in the brute-force approach.
	 *
	 * Space Complexity: O(N)
	 * - The recursion depth is at most N.
	 * - Each level creates a boolean array of size 205, which is O(1) space.
	 * - Overall auxiliary space is strictly bounded by O(N) for the call stack and 'current' array.
	 * - (Excluding the space required for the output array).
	 */

static vector<vector<int>> findSubsequences(const vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> current;
	current.reserve(nums.size());

	auto dfs = [&](auto&& self, const int start_idx) -> void{
		// If we have at least 2 elements, we capture the valid state.
		// We do NOT return here, because we want to keep building longer subsequences.
		if (current.size() >= 2)
			ans.emplace_back(current);

		// Local boolean array to track which numbers we have seen at THIS level
		// Size 205 safely covers the [-100, 100] range mapped to [0, 200]
		bool seen[205] = {false};

		// Loop through the remaining elements starting from 'start_idx'
		for (int i = start_idx; i < nums.size(); i++){
			// If we already branched on this exact number at this level, skip it
			if (seen[nums[i] + 100])
				continue;

			// If it's valid to add (either empty, or maintaining non-decreasing order)
			if (current.empty() || nums[i] >= current.back()){
				// Mark this number as seen for this specific recursive level
				seen[nums[i] + 100] = true;

				current.emplace_back(nums[i]); // Choose
				self(self, i + 1); // Explore
				current.pop_back(); // Un-choose (Backtrack)
			}
		}
	};

	dfs(dfs, 0);
	return ans;
}

// Approach 2: Using recursive & backtracking & sorting + erase-unique to remove duplicates
// Core Idea:
//     Remove all duplicates by sorting the final result and using std::unique to erase duplicates.
// This approach is less efficient than the first one, but it is simpler to implement and understand.
static vector<vector<int>> findSubsequencesWithSorting(const vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> current;
	current.reserve(nums.size());

	auto dfs = [&](auto&& self, const int start_idx) -> void{
		// Base Case: If we have reached the end of the array, check if the current subsequence is valid
		if (start_idx == nums.size()){
			if (current.size() >= 2)
				ans.emplace_back(current);
			return;
		}

		// Take the current number if it's valid (either empty, or maintaining non-decreasing order)
		if (current.empty() || nums[start_idx] >= current.back()){
			current.emplace_back(nums[start_idx]); // Choose
			self(self, start_idx + 1); // Explore
			current.pop_back(); // Un-choose (Backtrack)
		}

		// Not Take: Skip duplicates by moving the index forward until we find a different number
		int next_idx = start_idx + 1;
		while (next_idx < nums.size() && nums[next_idx] == nums[start_idx]){
			next_idx++;
		}

		self(self, next_idx); // Explore the next unique number
	};

	dfs(dfs, 0);
	// Sort the result and remove duplicates
	ranges::sort(ans);
	// Remove duplicates from the sorted result
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	return ans;
}
static void solve() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto& x : nums) cin >> x;

	// Approach 2: Using recursive & backtracking & sorting + erase-unique to remove duplicates
	// vector<vector<int>> subsequences = findSubsequencesWithSorting(nums);

	// Approach 1: Using a loop-based Backtracking tree with a local 'seen' array
	vector<vector<int>> subsequences = findSubsequences(nums);
	cout << "Non-decreasing Subsequences:\n";
	cout << "[\n";
	for (int i = 0; i < subsequences.size(); i++){
		cout << "  [";
		for (int j = 0; j < subsequences[i].size(); j++){
			cout << subsequences[i][j];
			if (j != subsequences[i].size() - 1) cout << ", ";
		}
		cout << "]";
		if (i != subsequences.size() - 1) cout << ",";
		cout << "\n";
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

