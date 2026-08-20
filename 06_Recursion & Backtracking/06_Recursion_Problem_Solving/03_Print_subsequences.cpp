/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-19 20:39:08
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
   1. Print ALL subsequences
   2. Print subsequences with sum = K
   3. Count subsequences with sum = K
   4. Check if ANY subsequence has sum = K
   5. Generate all subsets (Power Set) — LC 78
*/

/*  Problem 1: Print ALL subsequences
 *  array = [3, 1, 2] (Subsequence maintain relative order)
 *  Subsequences: {} {3} {1} {2} {3,1} {3,2} {1,2} {3,1,2}
 *  Total Subsequences = 2^n = 2^3 = 8
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
	return final_output;
}

// variant no 2: print only unique subsequence(not include duplicates)
// example: n = 3, arr = {1, 2, 2}
//			output : [[], [1], [1, 2], [2], [2, 2], [1, 2, 2]]

// Template 1: Use the "Take / Not Take" Template for: Knapsack problems, Dynamic Programming, and True/False decisions.
static vector<vector<int>> res;
static vector<int> curr;
static vector<vector<int>> subsequenceWithDup(vector<int>& arr){
	// 1. Sort the array so duplicates are adjacent to each other
	ranges::sort(arr);

	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case: Processed all element
		if (idx == arr.size()){
			res.push_back(curr);
			return;
		}

		// CHOICE 1: Take the current element
		curr.push_back(arr[idx]);
		self(self, idx + 1);
		curr.pop_back();

		// CHOICE 2: Not Take the current element
		// GRANDMASTER PRUNING: If we choose NOT to take this element,
		// we must skip ALL subsequent duplicate elements!
		int next_idx = idx + 1;
		while (next_idx < arr.size() && arr[next_idx] == arr[idx])
			next_idx++;
		self(self, next_idx);
	};

	res.clear();
	curr.clear();
	dfs(dfs, 0);
	return res;
}

// Template 2: Use the "For-Loop" Template for: Subsets, Combinations, and Permutations (especially when duplicates are involved!).
static vector<vector<int>> ans;
static vector<int> curr_sub;
static vector<vector<int>> subsequenceWithDupTemp2(vector<int>& arr){
	// Still MUST sort first!
	ranges::sort(arr);

	auto dfs = [&](auto&& self, const int idx) -> void{
		// 1. In this template, EVERY recursive call represents a valid subset!
		// So we add it to the answer immediately, without waiting for a base case.
		ans.push_back(curr_sub);

		// 2. Explore all possible elements we can add to our current subset
		for (int i = idx; i < arr.size(); i++){
			// --- THE MAGIC DUPLICATE SKIPPER ---
			// If this is NOT the first element we are picking in this loop,
			// and it is identical to the previous element, skip it!
			if (i > idx && arr[i] == arr[i - 1])
				continue;

			curr_sub.push_back(arr[i]); // TAKE
			self(self, i + 1);  // EXPLORE (Pass i + 1, not start_idx + 1)
			curr_sub.pop_back();  // BACKTRACK
		}
	};

	ans.clear();
	curr_sub.clear();
	dfs(dfs, 0);
	return ans;
}

void solve() {
    int n; cin >> n;
	vector<int> arr(n);
	for (auto &x : arr)
		cin >> x;

	// Function one call
	vector<vector<int>> print1 = printAllSubsequence(arr);
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

	// function two call
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

	// function three call
	vector<vector<int>> print3 = subsequenceWithDupTemp2(arr);
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

