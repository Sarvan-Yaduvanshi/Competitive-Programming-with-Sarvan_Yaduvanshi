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

static vector<vector<int>> combinationSum(vector<int>& candidates, int target){
    vector<vector<int>> ans;
    vector<int> current;

    auto dfs = [&](auto&& self, const int idx) -> void{
        // Base Case
        if (curr_sum == target){
            ans.push_back(current);
            return;
        }

        for (int i = idx; i < candidates.size(); i++){
            if (candidates[i] < target){

            }
        }
    };
}
static void solve() {
    
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

