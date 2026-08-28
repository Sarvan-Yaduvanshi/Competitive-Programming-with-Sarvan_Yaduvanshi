/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-19 20:06:02
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
 * Problem: Generate Binary Strings with Exact K Set Bits
 * Platform Equivalent: Similar to LeetCode 77 (Combinations), but applied to binary strings.
 * Given two integers n and k, generate all unique binary strings of length n that contain exactly k set bits (the character '1').
 * The remaining characters must be '0'.
 * Return the strings in lexicographical order (dictionary order).
 * Example 1:
 * Input: n = 3, k = 2
 * Output: ["011", "101", "110"]
 * Explanation: These are the only length-3 binary strings with exactly two '1's.
 * Example 2:
 * Input: n = 4, k = 1
 * Output: ["0001", "0010", "0100", "1000"]
 * Explanation: These are the only length-4 binary strings with exactly one '1'.
 * Constraints: 1 <= n <= 20, 0 <= k <= n
 * Topics: Recursion, Backtracking, Combinatorics
 * Expected Complexities: O(n choose k) time and O(n) space for recursion stack.
*/

/*       Dry Run: n = 3, K = 2
 *       Build Recursive Tree:
 *
 Level 0 (idx=0)                          [ "" ]
                                      /          \
                             Take '0'              Take '1'
                            /                        \
Level 1 (idx=1)          [ "0" ]                    [ "1" ]
                         /     \                    /     \
                     Take '0'  Take '1'         Take '0'  Take '1'
                    /            \              /            \
Level 2 (idx=2) [ "00" ]        [ "01" ]     [ "10" ]        [ "11" ]
                   |            /     \       /     \        /     \
             ❌ PRUNED!      T('0') T('1')  T('0') T('1')  T('0') T('1')
             (Floor Rule:     /         \    /         \    /         \
            Need two '1's, ["010"]  ["011"]["100"] ["101"]["110"]   ["111"]
            but only 1        |        |      |       |      |         |
            space left!)  ❌ PRUNED  ✅ ANS ❌ PRUNED ✅ ANS ✅ ANS  ❌ PRUNED!
                         (Floor Rule)       (Floor)                 (Ceiling Rule:
                                                                     ones_count > 2)

*/
vector<string> genersteExactSetBits(int n, int k){
	vector<string> ans;
	string str;

	// State tracks: current index (idx) and how many 1s we have placed (ones_count)
	auto solver = [&](auto&& self, const int idx, const int ones_count) -> void{
		// 1. Too many 1s placed? Stop exploring.
		if (ones_count > k) return;

		// 2. Impossible to reach k? (Not enough empty spaces left for the 1s we still need)
		int spaces_left = n - idx;
		int ones_needed = k - ones_count;
		if (ones_needed > spaces_left) return;

		// Base Case
		if (idx == n){
			ans.push_back(str);
			return;
		}

		// ------ Recursive Choices -----

		// Choice 1: Take '0'
		str.push_back('0');
		self(self, idx + 1, ones_count);  // ones_count stays the same!
		str.pop_back(); // BACKTRACK

		// Choice 2: Take '1'
		str.push_back('1');
		self(self, idx + 1, ones_count + 1);  // ones_count increases by 1!
		str.pop_back();  // BACKTRACK
	};

	solver(solver, 0, 0); // Start at index 0, with zero '1's placed
	return ans;
}
void solve() {
    int n, k;
	cin >> n >> k;

	vector<string> ans = genersteExactSetBits(n, k);
	cout << "[";
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << (i == ans.size() - 1 ? "" : ", ");
	cout << "]\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

