/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-25 17:20:41
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
 * Problem: Leetcode 2044. Count Number of Maximum Bitwise-OR Subsets
 * Difficulty: Medium
 * Company: Amazon, Microsoft, Google, Facebook (Asked in interviews)
 * Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.
 * An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.
 * Two subsets are considered different if the indices of the elements chosen are different.
 * The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).

 * Example 1:
 * Input: nums = [3,1]
 * Output: 2
 * Explanation: The maximum possible bitwise OR of any subset is 3.
 * There are 2 subsets with a bitwise OR of 3:
 * - [3]
 * - [3,1]
 *
 * Example 2:
 * Input: nums = [2,2,2]
 * Output: 7
 * Explanation: The maximum possible bitwise OR of any subset is 2.
 * Every non-empty subset has a bitwise OR equal to 2.
 * There are 7 total subsets.
 *
 * Example 3:
 * Input: nums = [3,2,1,5]
 * Output: 6
 * Explanation: The maximum possible bitwise OR of any subset is 7.
 * There are 6 subsets with a bitwise OR of 7:
 * - [3,5]
 * - [3,1,5]
 * - [3,2,5]
 * - [3,2,1,5]
 * - [2,5]
 * - [2,1,5]
 *
 * Constraints:
 * 1 <= nums.length <= 16
 * 1 <= nums[i] <= 10^5
 *
 * Approach: 1. Find the maximum bitwise OR of the entire array.
 * 		     2. Use backtracking to generate all possible subsets of the array.
 * 			 3. For each subset, calculate its bitwise OR and compare it with the maximum bitwise OR found in step 1.
 * 			 4. Count the number of subsets that have the maximum bitwise OR.
 */

// Approach 1: Recursion & Backtracking (Brute Force)
// Time Complexity: O(2^n * n) — 2^n subsets, each takes O(n) to calculate OR
// Space Complexity: O(n) — recursion depth + current subset
static int countMaxOrSubsets(vector<int>& nums){
	int maxVal_OR = 0;
	for (int num : nums)
		maxVal_OR |= num;

	int cnt = 0;
	vector<int> current_subset;
	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case
		if (idx == nums.size()){
			int curr_Or = 0;
			for (int subset : current_subset)
				curr_Or |= subset;
			if (curr_Or == maxVal_OR)
				cnt++;
			return;
		}

		// Not take
		self(self, idx + 1);

		// Take
		current_subset.push_back(nums[idx]);
		self(self, idx + 1);
		current_subset.pop_back();
	};

	dfs(dfs, 0);
	return cnt;
}

/*    Approach 2: Recursion & Backtracking (Optimized with GM Pruning / Early Exit)
===========================================================================
  🧠 BITWISE OR SUBSETS (The GM Math Pruning / Early Exit)
===========================================================================

  THE CORE LOGIC:
  Bitwise OR only turns bits ON; it can never turn them OFF. If `curr_OR`
  reaches the maximum possible OR early, it will never change. We instantly
  add 2^(remaining_elements) using bitwise left shift `(1 << remaining_elements)`
  and kill the branch, skipping thousands of useless recursive calls!

  COMPLEXITY ANALYSIS:
  - Worst Case Time Complexity: O(2^n)
	Happens if the max OR is only possible by combining every single element
	(e.g., an array of exact powers of 2 like [1, 2, 4, 8]). The early exit
	never triggers until the end.

  - Best Case Time Complexity: O(n)
	Happens if the very first element already equals the max OR (e.g., [7, 1, 2, 4]).
	The "Take" branches die immediately in O(1) time, and the recursion tree
	collapses into a single straight line of "Not Take" calls!

  - Average Case Time Complexity: Sub-exponential (Significantly faster than O(2^n))
	Highly dependent on the input array, but usually prunes massive halves of
	the tree resulting in lightning-fast execution times.

  - Space (Auxiliary) Complexity: O(n)
	Maximum depth of the recursion tree is n. Zero extra arrays or memory used.
===========================================================================
*/
static int countMaxOrSubsetsOptimal(const vector<int>& nums){
	int maxVal_OR = 0;
	for (int num : nums)
		maxVal_OR |= num;

	int cnt = 0;
	int n = nums.size();
	auto dfs = [&](auto&& self, const int idx, const int current_OR) -> void{
		// --- GM PRUNING ---
		// If we have already reached the maximum OR, we don't need to explore further!
		// Any combination of the remaining elements will still yield maxVal_OR.
		if (maxVal_OR == current_OR){
			int remaining_elements = n - idx;
			// 1 << remaining_elements is fast bitwise math for 2^(remaining_elements)
			cnt += (1 << remaining_elements);
			return;
		}

		// Base Case : // We only reach here if we NEVER hit maxVal_OR (so we don't add to cnt)
		if (idx == n){
			return;
		}

		// Choice 1: Take
		self(self, idx + 1, current_OR | nums[idx]);

		// Choice 2: Not Take
		self(self, idx + 1, current_OR);
	};
	dfs(dfs, 0, 0);
	return cnt;
}

static void solve(){
	int n; cin >> n;
	vector<int> arr(n);
	for (auto &x: arr)
		cin >> x;

	cout << "The maximum possible bitwise OR of a subset is: " << countMaxOrSubsets(arr) << "\n";
	cout << "The maximum possible bitwise OR of a subset is: " << countMaxOrSubsetsOptimal(arr) << "\n";
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

