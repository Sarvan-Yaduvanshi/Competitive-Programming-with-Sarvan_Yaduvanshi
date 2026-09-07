/*
Author: Sarvan Yaduvanshi
Created : 2026-09-03 23:54:37
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
    Problem: Generate Parentheses (Leetcode 22)
    Difficulty: Medium
    Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses

    Example 1: Input: n = 3
               Output: ["((()))","(()())","(())()","()(())","()()()"]
               Explanation: The valid combinations of well-formed parentheses for n=3 are as shown above.
	Example 2: Input: n = 1
               Output: ["()"]
               Explanation: The only valid combination of well-formed parentheses for n=1 is "()".

    Constraints:
        1 <= n <= 8

        Topics: Backtracking, String, Recursion
*/

static vector<string> generateParenthesis(const int n){
	vector<string> ans;
	string str;
	
	auto dfs = [&](auto&& self, const int open, const int close) -> void{
		if (str.size() == 2 * n){
			ans.emplace_back(str);
			return;
		}

		if (open < n){
			str.push_back('(');
			self(self,open + 1, close);
			str.pop_back();
		}

		if (close < open){
			str.push_back(')');
			self(self, open, close + 1);
			str.pop_back();
		}
	};

	dfs(dfs, 0, 0);
	return ans;
}
static void solve() {
    int n; cin >> n;

	// Function one call
	vector<string> print1 = generateParenthesis(n);
	cout << "[";
	for (int i = 0; i < print1.size(); i++){
		cout << print1[i] << (i == print1.size() - 1 ? "" : ", ");
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

