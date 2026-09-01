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

