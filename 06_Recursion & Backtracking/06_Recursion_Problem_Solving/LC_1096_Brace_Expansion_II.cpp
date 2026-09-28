/*
Author: Sarvan Yaduvanshi
Created : 2026-09-25 23:47:21
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
	Problem: Brace Expansion II (LeetCode 1096)
	Difficulty: Hard
	Company: Google, Adobe, Amazon, Microsoft, Facebook
	Topics: Recursion, Backtracking, String Manipulation, Set, Sorting, Stack, Hash Table, Breadth-First Search, Depth-First Search

	Under the grammar given below, strings can represent a set of lowercase words.
	Let R(expr) denote the set of words the expression represents.

	The grammar can best be understood through simple examples:
		Single letters represent a singleton set containing that word:
			R("a") = {"a"}
			R("w") = {"w"}
		When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
			R("{a,b,c}") = {"a","b","c"}
			R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
		When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
			R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
			R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
	Formally, the three rules for our grammar:
		For every lowercase letter x, we have R(x) = {x}.
		For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
		For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)},
			where + denotes concatenation, and × denotes the cartesian product.
	Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.

	Example 1:
		Input: expression = "{a,b}{c,{d,e}}"
		Output: ["ac","ad","ae","bc","bd","be"]
	Example 2:
		Input: expression = "{{a,z},a{b,c},{ab,z}}"
		Output: ["a","ab","ac","z"]
		Explanation: Each distinct word is written only once in the final answer.

	Constraints:
		1 <= expression.length <= 60
		expression[i] consists of '{', '}', ','or lowercase English letters.
		The given expression represents a set of words based on the grammar given in the description.
*/


/*
CORE STRATEGY: Recursive Descent Parser
We treat this as an expression evaluation problem.
- ',' acts as Addition (Union).
- Adjacency acts as Multiplication (Cartesian Product).

We use two Set buckets at every level:
- 'res' accumulates the final results separated by commas.
- 'cur' accumulates the current concatenation string. (Starts as {""})

Helper Function: combine(setA, setB)
This performs the Cartesian Product. Example:
combine({"a", "b"}, {"c", "d"}) returns {"ac", "ad", "bc", "bd"}.

--------------------------------------------------------------------------------
Example Dry Run: expression = "{a,b}{c,{d,e}}"
--------------------------------------------------------------------------------
Level 0: parse() called. i = 0.
- Reads '{'. Calls parse() for inner expression. i jumps to 1.
    Level 1: parse() processing "a,b"
    - cur = {""}
    - Reads 'a'. cur becomes {"a"}. i = 2.
    - Reads ','. Dumps cur into res. res = {"a"}. cur resets to {""}. i = 3.
    - Reads 'b'. cur becomes {"b"}. i = 4.
    - Reads '}'. Dumps cur into res. res = {"a", "b"}. RETURNS res. i = 5.
- Back in Level 0: combine(cur {""}, inner {"a", "b"}) -> cur = {"a", "b"}.
- Reads '{'. Calls parse(). i jumps to 6.
    Level 1: parse() processing "c,{d,e}"
    - Reads 'c'. cur = {"c"}. i = 7.
    - Reads ','. Dumps cur into res. res = {"c"}. cur = {""}. i = 8.
    - Reads '{'. Calls parse().
        Level 2: parse() processing "d,e"
        - Returns {"d", "e"}.
    - Back in Level 1: cur becomes combine({""}, {"d", "e"}) -> {"d", "e"}.
    - Reads '}'. RETURNS res {"c"} U {"d", "e"} -> {"c", "d", "e"}.
- Back in Level 0: cur = combine({"a", "b"}, {"c", "d", "e"}).
  cur becomes {"ac", "ad", "ae", "bc", "bd", "be"}.
- String ends. RETURN cur.

--------------------------------------------------------------------------------
COMPLEXITY:
- Time: O(N * 2^N) in the absolute worst case because Cartesian products grow
  exponentially. Using `set` keeps the lists deduplicated and sorted.
- Space: O(N * 2^N) to store the expanding combinations in memory.
================================================================================
*/
static  vector<string> braceExpansionII(const string& expression){
	int idx = 0; // The global pointer for our parser

	// Helper: Performs Cartesian Product (Multiplication) of two sets
	auto combine = [&](const set<string>& word1, const set<string>& word2) -> set<string>{
		set<string> Cartesian_product;
		for (const string& w1 : word1){
			for (const string& w2 : word2)
				Cartesian_product.insert(w1 + w2);
		}

		return Cartesian_product;
	};

	// Recursive Parser
	auto parse = [&](auto&& self) -> set<string>{
		set<string> ans;
		set<string> curr = {""}; // Starts empty to multiply properly

		while (idx < expression.size()){
			if (expression[idx] == '{'){ // Case 1: curr char is '{', start a new recursive parse
				idx++; // Move past '{'
				set<string> inner = self(self); // Recursively parse the inner expression
				curr = combine(curr, inner); // // Multiplication curr = curr * inner

			} else if (expression[idx] == '}'){ // Case 2: curr char is '}', end of current recursive parse
				idx++; // Move past '}'
				ans.insert(curr.begin(), curr.end()); // Finalize current block
				return ans; // End of this scope

			} else if (expression[idx] == ','){ // Case 3: curr char is ',', separate current block (OR / another choice)
				idx++; // Move past ','
				ans.insert(curr.begin(), curr.end()); // Add current block to final answer
				// Reset for the next term for eg:{ab,cd} -> first term = ab, second term = cd -> ans = {ab, cd}
				curr = {""};

			} else{ // Case 4: curr char is a letter, add it to the current block
				// Handle: {a{b,c}} -> first term = ab, second term = ac -> ans = {ab, ac}
				set<string> nxt_curr;
				for (const string& c : curr)
					nxt_curr.insert(c + expression[idx]);

				curr = nxt_curr; // Can also use std::move(nxt_curr) for a tiny micro-optimization
				idx++;
			}
		}

		// Finalize the last block if we reach the end of the string
		ans.insert(curr.begin(), curr.end());
		return ans;
	};

	// Start the parsing process
	set<string> ans_set = parse(parse);

	// Convert the final sorted set to a vector
	return vector<string>(ans_set.begin(), ans_set.end());
}

static void solve(){
	string str; cin >> str;

	auto ans = braceExpansionII(str);
	cout << "[";
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << (i == ans.size() - 1 ? "" : ", ");
	cout << "]\n";
}


int main(){
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
