/*
Author: Sarvan Yaduvanshi
Created : 2026-09-08 15:49:09
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
    Problem: Permutations (LeetCode 46)
    Difficulty: Medium
    -> Given an array nums of distinct integers, return all the possible permutations.
       You can return the answer in any order.

    * Permutation: A permutation is a rearrangement of all the elements of an array.
      Formula: npr = n! / (n - r)!
	* Notes: Permutations are different from combinations. In permutations, the order of elements matters, while in combinations, the order does not matter.

	Example 1:
    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    Explanation: There are 6 possible permutations of the array [1,2,3].

    Example 2:
    Input: nums = [0,1]
    Output: [[0,1],[1,0]]
    Explanation: There are 2 possible permutations of the array [0,1].

    Constraints:
		    1 <= nums.length <= 6
		    -10 <= nums[i] <= 10
		    All the integers of nums are unique.
	Topics: Array, Backtracking
*/

static vector<vector<int>> permute(const vector<int>& nums){
	vector<vector<int>> ans;
	vector<bool> visited(nums.size(), false);
	vector<int> current;
	current.reserve(nums.size());

	auto dfs = [&](auto&& self) -> void{
		if (current.size() == nums.size()){
			ans.emplace_back(current);
			return;
		}

		for (int i = 0; i < nums.size(); i++){
			if (visited[i])
				continue;

			visited[i] = true;
			current.push_back(nums[i]);
			self(self);
			current.pop_back();
			visited[i] = false;
		}
	};

	dfs(dfs);
	return ans;
}


static vector<vector<int>> permute_optimal(vector<int>& nums){
	vector<vector<int>> ans;
	vector<int> curr;
	curr.reserve(nums.size());

	auto dfs = [&](auto&& self, const int idx) -> void{
		if (curr.size() == nums.size()){
			ans.emplace_back(curr);
			return;
		}

		for (int i = idx; i < nums.size(); i++){
			swap(nums[idx], nums[i]);
			self(self, idx + 1);
			swap(nums[idx], nums[i]);
		}
	};

	dfs(dfs, 0);
	return ans;
}

static void solve() {
    int n; cin >> n;

	vector<int> a(n);
	for (auto &x : a)
		cin >> x;

	// Get all permutations
	const auto permutations = permute(a);
	cout << "Total permutations: " << permutations.size() << "\n";
	cout << "[";
	for (int i = 0; i < permutations.size(); i++){
		cout << "[";
		for (int j = 0; j < permutations[i].size(); j++){
			cout << permutations[i][j];
			if (j + 1 < permutations[i].size())
				cout << ", ";
		}
		cout << "]";
		if (i + 1 < permutations.size())
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

