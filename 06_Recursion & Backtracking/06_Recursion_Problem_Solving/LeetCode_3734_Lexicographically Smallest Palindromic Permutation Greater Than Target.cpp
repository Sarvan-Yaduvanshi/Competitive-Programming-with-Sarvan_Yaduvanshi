/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-28 13:10:04
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
 * Problem: LeetCode 3734 - Lexicographically Smallest Palindromic Permutation Greater Than Target
 * Difficulty: Hard Version
 * You are given two strings s and target, each of length n, consisting of lowercase English letters.
 * Return the lexicographically smallest string that is both a palindromic permutation of s and strictly greater than target.
 * If no such permutation exists, return an empty string.
 *
 * Example 1:
 * Input: s = "baba", target = "abba"
 * Output: "baab"
 * Explanation:
 *       1. The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
 *       2. The lexicographically smallest permutation that is strictly greater than target is "baab".
 *
 * Example 2:
 * Input: s = "abc", target = "cba"
 * Output: ""
 * Explanation:
 * There are no palindromic permutations of s that are strictly greater than target.
 *
 * Constraints:
 * n == s.length == target.length
 * 1 <= n <= 10^5
 * s and target consist of lowercase English letters.
 *
 * Topics: String, Backtracking, Greedy, Two Pointers
 */

static string lexPalindromicPermutation(string s, string target){
	int n = s.size();
	int half_len = n / 2;
	char mid_char = 0;
	string ans;

	// 1. Map character frequencies
	vector<int> counts(26, 0);
	for (const char ch : s)
		counts[ch - 'a']++;

	// 2. Validate palindrome possibility and find middle character
	int odd_cnt = 0;
	for (int i = 0; i < n; i++){
		if (counts[i] & 1){
			odd_cnt++;
			mid_char = i + 'a';
		}
	}

	// Cannot form a palindrome
	if (odd_cnt > 1)
		return "";

	// If there's an odd character, reserve one instance for the exact center
	if (odd_cnt == 1)
		counts[mid_char - 'a']--;

	// The Lambda Backtracking Function
	auto backtrack = [&](auto&& self, const int idx, bool is_greater, string& curr_left) -> bool{
		// Base case: We have successfully built the left half
		if (idx == half_len){
			// Construct the full palindrome
			string right = curr_left;
			ranges::reverse(right);

			string pal = curr_left;
			if (mid_char != 0)
				pal += mid_char; // Insert center character for odd-length strings
			pal += right;

			// Final check: Is the full palindrome strictly greater than target?
			if (pal > target){
				ans = pal;
				return true; // We found the smallest valid palindrome!
			}
			return false;
		}

		// Try placing characters in alphabetical order ('a' to 'z')
		for (int i = 0; i < 26; i++){
			if (counts[i] == 0) // No pairs of this letter left
				continue;

			const char ch = i + 'a';

			// PRUNING: If our string is still tied with the target,
			// we cannot pick a letter alphabetically smaller than the target's letter.
			if (!is_greater && (ch < target[idx]))
				continue;

			// DO: Make the choice
			counts[i] -= 2; // Consume a pair (one for left, one for right)
			curr_left.push_back(ch);

			// Determine if this choice breaks the tie with the target
			bool next_is_greater = is_greater || (ch > target[idx]);

			// RECURSE: Move to the next index
			if (self(self, idx + 1, next_is_greater, curr_left))
				return true; // Stop exploring! We found the best answer.

			// UNDO: Backtrack if the choice didn't lead to a valid answer
			curr_left.pop_back();
			counts[i] += 2;
		}
		return false; // No valid palindrome found on this path
	};

	// 3. Start Backtracking
	string curr_left;
	backtrack(backtrack, 0, false, curr_left);
	return ans;
}
static void solve(){
	string str, target;
	cin >> str >> target;

	string result = lexPalindromicPermutation(str, target);
	if (result.empty())
		cout << "No valid palindromic permutation greater than target exists." << endl;
	else
		cout << "Lexicographically smallest palindromic permutation greater than target: " << result << endl;
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

/*
PATTERN: BACKTRACKING + PRUNING + CONSTRUCTIVE PALINDROME
PROBLEM IDEA:
	Find the smallest palindrome that:
		Uses exactly the characters from the given string.
		Is strictly greater than the target string.

	1. OBSERVATION: PALINDROME HAS SYMMETRY
			A palindrome is completely determined by its left half.
			Example:
				left   center   right
				abc             cba
			Once we choose the left half, the right half is forced by reversing the left half.
			Therefore:
				-> We only need to construct n / 2 characters.
				-> The remaining half is automatically determined.

	2. COUNT CHARACTERS
			Use a frequency array to track how many copies of each character are available.
			Why consume 2 characters at a time?
			If we put character 'c' at one position in the left half,
			we must put another 'c' at the symmetric position in the right half.
			Therefore:
				choose 'c'
					-> consume 2 copies
					-> one for LEFT
					-> one for RIGHT
	3. HANDLE THE CENTER CHARACTER
			For an even-length palindrome: Every character must have an even frequency.
			For an odd-length palindrome: At most ONE character can have an odd frequency.
			If more than one character has an odd frequency:
				-> A palindrome cannot be formed.
			If exactly one character has an odd frequency:
				-> Reserve that character for the center.
				-> Remove it from the frequency array.

	4. REDUCE THE PROBLEM
			After handling the center:
				Original problem: "Build the smallest valid palindrome."
				Becomes: "Build the smallest valid LEFT HALF."
			Because the right half is automatically determined.

	5. BACKTRACKING STATE
			At every position of the left half, we need to remember:
				index
					-> Which position are we currently filling?
				current_left
					-> What have we built so far?
				counts
					-> Which character pairs are still available?
				is_greater
					-> Is our prefix already greater than target?

	6. TRY CHARACTERS IN SORTED ORDER
		Try characters from 'a' -> 'z'.
		Why?
			We need the SMALLEST valid answer.
			If we always explore smaller characters first, then:
				first valid complete palindrome = smallest valid palindrome
			Therefore, once a valid answer is found,
			we can immediately stop searching.

	7. PRUNING
		Important condition:
			if (!is_greater && c < target[index])
				skip this choice
			Reason:
				If our prefix is still equal to the target and we choose:
					candidate character < target character
				then the final palindrome can NEVER become greater later.

		Example:
			target    = b.....
			candidate = a.....
			Since:
				a < b
				the whole candidate will always be smaller.
		Therefore:
			-> No need to explore this branch.
			-> Prune it immediately.

	8. is_greater STATE:
		If: c > target[index] -> then our candidate becomes greater at this position.
		From that point onward: is_greater = true
		Once the prefix is greater, it can never become "not greater" again.
		Therefore:
			next_is_greater = is_greater || (c > target[index])
			If: c == target[index] -> we are still tied.

	9. DO -> RECURSE -> UNDO
		This is the CORE BACKTRACKING PATTERN.
			DO:
				Make a temporary choice.
					counts[i] -= 2
					current_left.push_back(c)
				RECURSE: Try to solve the remaining positions.

			UNDO:
				If this branch fails, restore the exact previous state.
					current_left.pop_back()
					counts[i] += 2
			Why undo?
				The choice is only temporary.
				If choosing 'c' cannot produce an answer,
				we must return to the previous decision point
				and try the next possible character.
			Important mental model:
					choose -> explore -> (success -> keep choice) -> (failure -> undo choice) -> try next choice

	10. BASE CASE
		When: index == half_len
			the entire left half has been constructed.
			Now construct the full palindrome:
				right = reverse(current_left)
				palindrome = current_left + center (if needed) + right
			Then check:
				palindrome > target
			If yes:
				-> We found the smallest valid answer.
				-> Return immediately because characters were explored from smallest to largest.

	11. WHY THIS WORKS
		Three ideas work together:
			BACKTRACKING
				-> explores different possible left halves.
			PRUNING
				-> removes branches that can never beat target.
			SORTED SEARCH
				-> tries smaller characters first.
			Therefore:
				first valid palindrome found = smallest palindrome greater than target.

	12. GENERAL BACKTRACKING TEMPLATE
		For similar problems, think:
			1. What is the structure of the answer?
			2. Can I reduce the amount I need to build?
			3. What are my choices at each position?
			4. What state do I need to remember?
			5. Which choices are immediately invalid?
			6. Can I prune those choices?
			7. What is my base case?
			8. What do I DO before recursion?
			9. What do I UNDO after recursion?
			10. Does the order of choices let me stop early?

		Core pattern:
			for each possible choice:
				if choice is invalid:
					continue
				MAKE CHOICE
				RECURSE
				if solution found:
					return
				UNDO CHOICE

	13. COMPLEXITY:
		Let n = length of the string. Only n/2 positions need to be constructed.
		Backtracking is exponential in the number of positions.
		Loose worst-case time:
			Time: O(26^(n/2) * n)
				The extra n comes from constructing/checking the complete palindrome at the base case.
			Space: O(n)
				Reason:
					- recursion depth = O(n)
					- current_left = O(n)
					- constructed palindrome = O(n)
					- counts array = O(26) = O(1)

	13. KEY TAKEAWAY:
		Do NOT memorize the code.
		Remember the thought process:
				PALINDROME
					↓
			Only build LEFT HALF
					↓
			COUNT AVAILABLE PAIRS
					↓
			BACKTRACK OVER POSITIONS
					↓
			TRY SMALLEST CHARACTER FIRST
					↓
			PRUNE IF PREFIX CAN NEVER BE GREATER
					↓
			DO → RECURSE → UNDO
					↓
			MIRROR LEFT HALF
					↓
			FIRST VALID ANSWER = SMALLEST ANSWER
*/

