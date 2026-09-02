/*
Author: Sarvan Yaduvanshi
Created : 2026-08-30 23:51:19
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
    Problem: Letter Combinations of a Phone Number (Leetcode 17)
    Difficulty: Medium
    Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
    Return the answer in any order.
    A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
    ┌───────────┬───────────┬───────────┐
    │  1 ∞      │  2 abc    │  3 def    │
    ├───────────┼───────────┼───────────┤
    │  4 ghi    │  5 jkl    │  6 mno    │
    ├───────────┼───────────┼───────────┤
    │  7 pqrs   │  8 tuv    │  9 wxyz   │
    ├───────────┼───────────┼───────────┤
    │  * +      │  0 _      │  # ⇧      │
    └───────────┴───────────┴───────────┘

    Example 1: Input: digits = "23"
			   Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
			   Explanation: The mapping of digits to letters is as follows:
					2 -> "abc"
					3 -> "def"
					 String "23" can be represented by the combinations of letters from "abc" and "def".
	Example 2: Input: digits = "2"
			   Output: ["a","b","c"]
			   Explanation: The mapping of digits to letters is as follows:
					2 -> "abc"
					 String "2" can be represented by the combinations of letters from "abc".
	Example 3: Input: digits = ""
			   Output: []
			   Explanation: Since the input is an empty string, there are no combinations to return.

	Constraints:
		0 <= digits.length <= 4
		digits[i] is a digit in the range ['2', '9'].

		Topics: Backtracking, String, Hash Table, Recursion
*/

static vector<string> letterCombinations(const string& digits){
	// GM Fix 1: Early exit for edge case
	if (digits.empty())
		return {};

	vector<string> ans;
	string current_str;
	// GM Fix 2: Pre-allocate the string capacity
	current_str.reserve(digits.size());

	// GM Fix 3: Use a static array for phoneMap to avoid repeated construction
	string phoneMap[] = {
		"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
	};

	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case: We've picked one letter for every digit
		if (idx == digits.size()){
			ans.emplace_back(current_str);
			return;
		}

		// Get the letters for the current digit
		string& letters = phoneMap[digits[idx] - '0'];
		for (const char ch : letters){
			current_str.push_back(ch);
			self(self, idx + 1);
			current_str.pop_back();
		}
	};

	dfs(dfs, 0);
	return ans;
}

static void solve() {
    string str;
	cin >> str;

	// Get the letter combinations for the input digits
	vector<string> combinations = letterCombinations(str);
	cout << "[";
	for (size_t i = 0; i < combinations.size(); ++i){
		cout << "\"" << combinations[i] << "\"";
        if (i < combinations.size() - 1)
            cout << ",";
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

