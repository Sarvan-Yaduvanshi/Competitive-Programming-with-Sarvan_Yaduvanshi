/*
Author: Sarvan Yaduvanshi
Created : 2026-09-01 21:26:55
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
    Problem: Unique Subsequences of a String
    Difficulty: Medium
    Given a string s, return all the unique subsequences of the string in any order.
    A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
    For example, "ace" is a subsequence of "abcde".

    Example 1: Input: s = "abc"
               Output: ["a","b","c","ab","ac","bc","abc"]
               Explanation: The unique subsequences of "abc" are "a", "b", "c", "ab", "ac", "bc", and "abc".

    Example 2: Input: s = "aaa"
               Output: ["a","aa","aaa"]
               Explanation: The unique subsequences of "aaa" are "a", "aa", and "aaa".

    Constraints:
        1 <= s.length <= 15
        s consists of lowercase English letters.

        Topics: Backtracking, String, Hash Table, Recursion, Dynamic Programming
*/

/*
 * Core Idea:
 * 1. We CANNOT sort the string, because subsequences rely on original order.
 * 2. To avoid duplicates, we use a 'seen' boolean array inside the recursive lambda.
 * 3. This array resets for every new recursive call. It only tracks which characters
 *    have been used as a starting branch at the CURRENT depth level.
 * 4. If we see a character we've already branched on at this level, we skip it.
 *
 * Time Complexity: O(N * 2^N)
 * - N is the length of the string.
 * - In the worst case (all unique characters), there are 2^N unique subsequences.
 * - String copying takes O(N) time.
 *
 * Space Complexity: O(N)
 * - The recursion call stack goes up to a depth of N.
 * - The boolean array takes O(1) space (constant size 256).
 * - (Excluding the space required for the output array).
 */
static vector<string> uniqueSubsequences(string s) {
	vector<string> ans;
	string current;
	current.reserve(s.length());

	auto dfs = [&](auto&& self, int start) -> void {
		// Capture the subsequence at every step (excluding empty string)
		if (!current.empty()) {
			ans.emplace_back(current);
		}

		// A local array to track characters we've already branched on AT THIS LEVEL
		bool seen[256] = {false};

		for (int i = start; i < s.length(); ++i) {
			// Pruning: If we've already branched on this character at this level, skip it
			if (seen[s[i]]) {
				continue;
			}

			// Mark this character as used for this depth level
			seen[s[i]] = true;

			// Choose
			current.push_back(s[i]);

			// Explore
			self(self, i + 1);

			// Un-choose (Backtrack)
			current.pop_back();
		}
	};

	dfs(dfs, 0);
	// Sort the result for consistent output
	ranges::sort(ans);
	return ans;
}

static void solve() {
    string s; cin >> s;

	vector<string> result = uniqueSubsequences(s);
	cout << "Unique Subsequences of \"" << s << "\":\n";
    cout << "[";
	for (size_t i = 0; i < result.size(); ++i){
		cout << "\"" << result[i] << "\"";
        if (i != result.size() - 1) {
            cout << ", ";
        }
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

