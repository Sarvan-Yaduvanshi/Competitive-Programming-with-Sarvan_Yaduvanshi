/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-19 20:39:08
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <iomanip>
#include <random>
#include <chrono>
using namespace std;

/*
    ================================================================
                        SUBSEQUENCE — THEORY
    ================================================================

    Definition:
    A subsequence is formed by deleting zero or more elements from
    the original sequence WITHOUT changing the relative order of
    the remaining elements.

    Example:
        nums = [2, 1, 2]
        Valid: [[], [2], [1], [2, 1], [2, 2], [1, 2], [2, 1, 2]]
        Invalid:
            [1, 2, 2]   // changes relative order by rearranging elements

    Core Rule:
        SUBSEQUENCE = SELECT / SKIP + ORDER PRESERVED

    Formula:
        For n elements: Number of index-based subsequences = 2^n
        Reason:
            Every element has 2 choices:
                - Take
                - Skip
            Therefore:
                2 × 2 × ... × 2  (n times) = 2^n

    Empty subsequence:
        [] is also a valid subsequence.

    ---------------------------------------------------------------
                         DUPLICATE SUBSEQUENCES
    ---------------------------------------------------------------

    Duplicate definition:
    Two subsequences are duplicates when their resulting value
    sequences are identical, even if they came from different
    indices.

    Example:
        nums = [2, 1, 2]
        Taking:
            first 2
        and:
            second 2
        can both produce:
            [2]
        These are the SAME value subsequence.

    Therefore:
        Index-based subsequences:
            Treat different index selections as different.
        Unique subsequences:
            Treat identical resulting vectors as ONE subsequence.
    Example:
        nums = [2, 1, 2]
        Total index-based subsequences = 2^3 = 8
        Unique value subsequences = 7

    ---------------------------------------------------------------
                     SUBSET vs SUBSEQUENCE
    ---------------------------------------------------------------

        SUBSET: Order does NOT matter.
            {1, 2} == {2, 1}
        SUBSEQUENCE:
            Relative order MUST be preserved.
            [1, 2] != [2, 1]

    Memory Trick:
        SUBSET       → SELECT
        SUBSEQUENCE  → SELECT + ORDER

    For duplicate handling:
        - Brute force + set  → generate duplicates, then remove them.
        - Per-level `seen`   → prevent duplicate branches during DFS.
    ================================================================
*/

/*
🎯 Problems in this file:
   1. Print ALL subsequences (including duplicates)
   2. Print only unique subsequences (no duplicates)
*/

/*  Problem 1: Print ALL subsequences
 *  array = [3, 1, 2] (Subsequence maintain relative order)
 *  Subsequences: {} {3} {1} {2} {3,1} {3,2} {1,2} {3,1,2}
 *  Total Subsequences = 2^n = 2^3 = 8
 *  Leaves of the recursion tree represent all possible subsequences.
 *  leaf nodes = 2^n = 2^3 = 8
 *
 *  Recursive Tree:
 *  - At each index, we have two choices: TAKE or NOT TAKE the current element
 *  - This leads to a binary tree of choices, with each leaf representing a unique subsequence.


 Recursion tree:
                           []
                        /      \
                   [3]            []
                  /    \        /     \
             [3,1]    [3]      [1]      []
            /  \      /  \    /   \     / \
     [3,1,2] [3,1] [3,2] [3] [1,2] [1] [2] []

   Time: O(2^n * n) — 2^n subsequences, each takes O(n) to print
   Space: O(n) — recursion depth + current subsequence
*/

// Variant No 1: Print all subsequence with duplicates
// example: n = 3, arr = {1, 2, 2}
//			output : [[], [1], [1, 2], [1, 2], [2], [2, 2], [2, 2], [1, 2, 2]]
static vector<vector<int>> final_output;
static vector<int> curr_subsequence;
static vector<vector<int>> printAllSubsequence(const vector<int>& arr){
	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case: processed all element
		if (idx == arr.size()){
			final_output.push_back(curr_subsequence);
			return;
		}

		// Choice 1: Not take arr[idx]
		self(self, idx + 1);

		// Choice 2: Take arr[idx]
		curr_subsequence.push_back(arr[idx]);
		self(self, idx + 1); // recursive call
		curr_subsequence.pop_back(); // Backtrack Undo the choice
	};

	final_output.clear();
	curr_subsequence.clear();
	dfs(dfs, 0);

	// If u need output sorted than used custom comparator
	// arr = {3, 1, 2} -> [[], [1], [2], [3], [1, 2], [3, 1], [3, 2], [3, 1, 2]]
	/*
	ranges::sort(final_output,
	             [](const vector<int>& a, const vector<int>& b) -> bool{
		             if (a.size() != b.size()) return a.size() < b.size();
		             return a < b;
	             });
	 */
	// Remove all duplicates subsequence and return sorted subsequence
	// ranges::sort(final_output);
	// final_output.erase(ranges::unique(final_output).begin(), final_output.end());
	return final_output;
}

/*	// variant no 2: print only unique subsequence(not include duplicates)

	Approach 1: Recursion / Backtracking + Set
	Idea:
	- At every index, we have 2 choices:
		1. Take nums[idx]
		2. Do not take nums[idx]
	- This generates all possible subsequences.
	- Duplicate subsequences can be generated when nums contains duplicates.
	- Store each subsequence in set<vector<int>> to keep only unique subsequences.
	- We DO NOT sort nums because subsequence order must remain the same.

	Example:
		nums = {2, 1, 2}
		Unique subsequences:
		{}, {2}, {1}, {2,1}, {2,2}, {1,2}, {2,1,2}

	Why set?
	- vector<int> has lexicographical comparison, so it can be stored directly
	  inside std::set.
	- Before adding to ans, check whether curr already exists.

	Time Complexity:
	- There are 2^n possible subsequences.
	- Copying/storing a subsequence can take O(n).
	- Set insertion/search costs O(log U), where U <= 2^n.
	- Overall: O(n * 2^n * log(2^n))
	  ≈ O(n^2 * 2^n)

	Space Complexity:
	- Recursion stack + curr: O(n)
	- Set + answer storage: O(n * 2^n)
	- Overall: O(n * 2^n)

	Important:
	- This is the simple brute-force + set approach.
	- It is useful for learning recursion and duplicate handling.
	- A more optimized approach avoids generating duplicates in the first place.
*/
static vector<vector<int>> subsequenceWithDup(vector<int>& nums){
	vector<vector<int>> ans;
	set<vector<int>> seen; // used to store unique subsequences
	vector<int> curr;
	curr.reserve(nums.size());

	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case: If we have processed all elements
		if (idx == nums.size()){
			// Check if the current subsequence is already seen
			if (!seen.contains(curr)){
				ans.emplace_back(curr);
				seen.insert(curr);
			}
			return;
		}

		// not take
		self(self, idx + 1);

		// take
		curr.emplace_back(nums[idx]); // add current element to the current subsequence
		self(self, idx + 1); // recursive call to explore further elements
		curr.pop_back(); // backtrack (undo the choice)
	};

	dfs(dfs, 0);
	return ans;
}

/*
    Approach 2: Backtracking + Per-Level Hash Set
    Idea:
    - Every element from [start ... n-1] is a possible next element.
    - At each recursion depth, use a `seen` set to ensure the same value
      is selected only once at that depth.
    - If nums[i] was already used at the current depth, skip it.
    - Different recursion depths have different `seen` sets.
      Therefore, duplicate values can still be selected in the same subsequence.

    Why seen is per recursion level:
        nums = {2, 1, 2}
        At depth 0:
            seen = {}
            choose 2  -> seen = {2}
            choose 1  -> seen = {2,1}
            second 2  -> already seen -> skip

        But after choosing the first 2:
            curr = [2]
            New recursion level:
                seen = {}
            Now another 2 can be chosen:
                curr = [2,2]
        So:
            Same value + same depth  -> skip
            Same value + different depth -> allowed

    Why this handles unique subsequences:
    - We preserve the original array order.
    - We never sort the array.
    - We prevent duplicate choices at the same recursion level.
    - Every generated subsequence is therefore unique.

    Difference from Set Approach:
        Set Approach:
            Generate all 2^n subsequences
            → store in set
            → remove duplicates

        This Approach:
            Detect duplicate choices during DFS
            → never generate those duplicate branches

    Time Complexity:
    - There can be O(2^n) unique subsequences in the worst case.
    - Every generated subsequence/path requires O(n) work in the worst case.
    - Average practical complexity is much better than generating duplicates
      and inserting every result into a set.
    - Worst case: O(n * 2^n)

    Space Complexity:
    - Recursion stack + current subsequence: O(n)
    - `seen` sets across the recursion path: O(n) in the distinct-value case.
    - Output is O(n * U), where U = number of unique subsequences.
    - Auxiliary space excluding output: O(n).

    Important:
    - `seen` must be created INSIDE dfs().
    - Do NOT use one global `seen` set.
    - Do NOT sort nums because subsequence order matters.
*/
static vector<vector<int>> subsequenceWithDupOptimal(const vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> curr;
	curr.reserve(nums.size());

	auto dfs = [&](auto&& self, const int idx) -> void{
		// Every current path is a valid subsequence
		ans.emplace_back(curr);

		// Tracks values already chosen at THIS recursion depth
		unordered_set<int> seen;

		for (int i = idx; i < nums.size(); i++){
			// Same value already considered at this depth
			// Choosing it again would generate duplicate subsequences
			if (seen.contains(nums[i]))
				continue;

			// Mark this value as used at this depth
			seen.insert(nums[i]);

			curr.emplace_back(nums[i]); // Take nums[i]
			self(self, i + 1); // Continue with elements after i
			curr.pop_back(); // Backtrack
		}
	};

	dfs(dfs, 0);
	return ans;
}


static void solve() {
    int n; cin >> n;
	vector<int> arr(n);
	for (auto &x : arr)
		cin >> x;

	// Generate all subsequences (including duplicates) -> problem 1
	const auto print1 = printAllSubsequence(arr);
	cout << "[";
	for (int i = 0; i < print1.size(); i++){
		cout << "[";
		for (int j = 0; j < print1[i].size(); j++){
			cout << print1[i][j];
			if (j + 1 < print1[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < print1.size())
			cout << ", ";
	}
	cout << "]\n";

	// Generate unique subsequences -> problem 2 (method 1: using set)
	vector<vector<int>> print2 = subsequenceWithDup(arr);
	cout << "[";
	for (int i = 0; i < print2.size(); i++){
		cout << "[";
		for (int j = 0; j < print2[i].size(); j++){
			cout << print2[i][j];
			if (j + 1 < print2[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < print2.size())
			cout << ", ";
	}
	cout << "]\n";

	// Generate unique subsequences -> problem 2 (method 2: using unordered_set)
	vector<vector<int>> print3 = subsequenceWithDupOptimal(arr);
	cout << "[";
	for (int i = 0; i < print3.size(); i++){
		cout << "[";
		for (int j = 0; j < print3[i].size(); j++){
			cout << print3[i][j];
			if (j + 1 < print3[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < print3.size())
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

