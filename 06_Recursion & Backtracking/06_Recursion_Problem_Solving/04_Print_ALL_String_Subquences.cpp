/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-21 17:56:33
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
 * Problem: All Subsequences of a String (GeeksforGeeks)
 * Difficulty Level: Medium
 * Given a string s, generate all possible subsequences of the string (including the empty subsequence)
 * and return them in lexicographical order.
 * A subsequence is obtained by deleting zero or more characters from the string without changing the relative order of the remaining characters.
 * Examples:
 * Input: s = "abc"
 * Output: ["", "a", "ab", "abc", "ac", "b", "bc", "c"]
 * Explanation: There are a total of 8 non-empty subsequences for the given string.
 *			   These subsequences are listed above in lexicographical order.
 * Input: s = "aa"
 * Output: ["", "a", "a", "aa"]
 * Constraints: 1 <= n <= 16
 * s consists of lowercase English letters.
 * Expected Complexities: O(2^n * n) time and O(2^n * n) space for storing the subsequences.
 * Topics: Recursion, Backtracking, String Manipulation, Mathematics, Combinatorics
 */

static vector<string> ans;
static string str;
static vector<string> powerSet(string &s) {
	auto isGenerateSubsequence = [&](auto&& self, const int idx) -> void{
		// Base Case: Processed all string
		if (idx == s.size()){
			ans.push_back(str);
			return;
		}

		// Choice 1: Take
		str.push_back(s[idx]);
		self(self, idx + 1);
		str.pop_back();

		// Choice 2: Not Take
		self(self, idx + 1);
	};

	ans.clear();
	str.clear();
	isGenerateSubsequence(isGenerateSubsequence, 0);
	// sort the output to return in lexicographical order
	ranges::sort(ans);
	return ans;
}
static void solve(){
	string s; cin >> s;
    vector<string> temp = powerSet(s);
    cout << "[";
    for (int i = 0; i < temp.size(); i++)
        cout << "\"" << temp[i] << "\"" << (i == temp.size() - 1 ? "" : ", ");
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

