/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-15 23:22:12
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
 *  🎯 Problems in this file:
	   1. Generate all binary strings (Gfg)
	   2. Leetcode (3211) : Generate Binary Strings Without Adjacent Zeros
*/
/* Problem 1: Generate all binary strings
 * Given an integer n, generate all binary strings of length n.
 * A binary string is a string that consists only of the characters '0' and '1'.
 * Note: Return the strings in ascending order.
 * Example:
 * input: n = 3
 * Output: ["000", "001", "010", "011", "100", "101", "110", "111"]
 * input: n = 2
 * Output: ["00", "01", "10", "11"]
 * Explanation: As each position can be either 0 or 1, the total possible combinations are 4.
 *
 * Expected Complexities: O(2^n * n) time and O(n) space.
 * Constraints: 1 <= n <= 20
 * Topics: Recursion, Backtracking, Bit Manipulation
 */

/*
   Dry Run: n = 3 -> ["000", "001", "010", "011", "100", "101", "110", "111"]

                       idx=0
						  ""
					   /      \
					 0          1
					/            \
				idx=1           idx=1          (Recursion Tree Build)
				  "0"             "1"
				 /   \           /   \
				0     1         0     1
			   /       \       /       \
		   idx=2      idx=2  idx=2     idx=2
			"00"       "01"  "10"       "11"
			/  \       /  \   /  \       /  \
		   0    1     0    1 0    1     0    1
		  /      \   /      \ /      \   /      \
	 idx=3    idx=3 ...   ...     ... ...    idx=3
	"000"    "001" "010" "011" "100" "101" "110" "111"
	  ↓        ↓     ↓     ↓     ↓     ↓     ↓     ↓
     ADD      ADD   ADD   ADD   ADD   ADD   ADD   ADD
*/

// Idea: Think of it as “choose → go deeper → finish → undo choice → try next choice.”

static vector<string> ans;
static string str;
vector<string> binstr(int n){
	// Write Recursive Lambda Function to generate all binary strings of length n
	auto generate_binstr = [&](auto&& self, const int idx) -> void{
		// Base Case: if idx == n, add the current string to the answer and return
		if (idx == n){
			ans.push_back(str);
			return;
		}

		// Choice 1: Take '0' at idx
		str.push_back('0'); // left branch (GO DOWN)
		self(self, idx + 1); // recursion call (EXPLORE)
		str.pop_back(); // Backtrack (COME BACK)

		// Choice 2: Take '1' at idx
		str.push_back('1'); // right branch (GO DOWN)
		self(self, idx + 1); // recursion call (EXPLORE)
		str.pop_back(); // Backtrack (COME BACK)
	};

	ans.clear();
	str.clear();
	generate_binstr(generate_binstr, 0);
	return ans;
}

/* Custom Rule: Any Binary String reverse binary string are same so only store one value
 * ---> For example: 001 and 100 are same so only store 001
 * Example: n = 3 -> ["000", "001", 010", "011", "100", "101", "110", "111"] -> ["000", "001", "010", "011", "101", "111"]
 * How to handle this case? We can use a set to store the binary strings and check if the reverse of the string is already in the set.
 *                          If it is, we don't add it to the answer.
*/

static vector<string> res;
static set<string> seen;
static string s;
static vector<string> withoutDuplicateBinStr(int n){
	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case
		if (idx == n){
			// 1. Create the "duplicate" version of the current string
			string revStr = s;
			// reverse(revStr.begin(), revStr.end());
			ranges::reverse(revStr);
			if (!seen.contains(s) && !seen.contains(revStr)){
				seen.insert(s);
				res.push_back(s);
			}
			return;
		}

		s.push_back('0');
		self(self, idx + 1);
		s.pop_back();

		s.push_back('1');
		self(self, idx + 1);
		s.pop_back();
	};

	res.clear();
	s.clear();
	dfs(dfs, 0);
	return res;
}

/* Problem 2: Leetcode (3211) : Generate Binary Strings Without Adjacent Zeros
 * Difficulty Level: Medium
 * You are given a positive integer n.
 * A binary string x is valid if all substrings of x of length 2 contain at least one "1".
 * Return all valid strings with length n, in any order
 * Example 1:
 * input: n = 3
 * output: ["010", "011", "101", "110", "111"]
 * Explanation: The valid strings of length 3 are: "010", "011", "101", "110", and "111".
 * Example 2:
 * input: n = 1
 * output: ["0", "1"]
 * Explanation: The valid strings of length 1 are: "0" and "1".
 * Constraints: 1 <= n <= 18
 * Topics: String, Recursion, Backtracking, Bit Manipulation
*/

static vector<string> final_output;
static string temp_str;

vector<string> validStrings(int n){
	auto dfs = [&](auto&& self, const int idx) -> void{
		// Base Case
		if (idx == n){
			final_output.push_back(temp_str);
			return;
		}

		// Append '0' only if the string is empty or does not already end with '0'.
		// Recursively process the next index, then backtrack by removing the appended character.
		if (temp_str.empty() || temp_str.back() != '0'){
			temp_str.push_back('0');
			self(self, idx + 1);
			temp_str.pop_back();
		}

		temp_str.push_back('1');
		self(self, idx + 1);
		temp_str.pop_back();
	};

	final_output.clear();
	temp_str.clear();
	dfs(dfs, 0);
	return final_output;
}
void solve(){
	int n; cin >> n;
	cout << "[";
	vector<string> temp = binstr(n);
	for (int i = 0; i < temp.size(); i++)
		cout << temp[i] << (i == temp.size() - 1 ? "" : ", ");
	cout << "]\n";

	vector<string> temp2 = withoutDuplicateBinStr(n);
	for (int i = 0; i < temp2.size(); i++)
		cout << temp2[i] << (i == temp2.size() - 1 ? "" : ", ");
	cout << "]\n";

	vector<string> temp3 = validStrings(n);
	for (int i = 0; i < temp3.size(); i++)
		cout << temp3[i] << (i == temp3.size() - 1 ? "" : ", ");
	cout << "]\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
	return 0;
}
