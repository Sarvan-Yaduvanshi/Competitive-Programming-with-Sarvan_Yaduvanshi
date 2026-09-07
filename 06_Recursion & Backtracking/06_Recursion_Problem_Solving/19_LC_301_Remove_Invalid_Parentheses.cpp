/*
Author: Sarvan Yaduvanshi
Created : 2026-09-07 17:07:32
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
#include <unordered_set>
using namespace std;

/*
    Problem: Remove Invalid Parentheses (Leetcode 301)
    Difficulty: Hard
    Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to
    make the input string valid.
    Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.

    Example 1:
    Input: s = "()())()"
    Output: ["(())()","()()()"]
    Explanation: By removing one ')' from the string, we can obtain two valid strings: "(())()" and "()()()".

    Example 2:
    Input: s = "(a)())()"
    Output: ["(a())()","(a)()()"]
    Explanation: By removing one ')' from the string, we can obtain two valid strings: "( a())()" and "(a)()()".

    Example 3:
    Input: s = ")("
    Output: [""]
    Explanation: By removing both parentheses, we can obtain an empty string, which is valid.

    Constraints:
        1 <= s.length <= 25
        s consists of lowercase English letters and parentheses '(' and ')'.
        There will be at most 20 parentheses in s.
    Topics: Backtracking, String, Breadth-First Search, Depth-First Search,
*/

/*
CORE STRATEGY (Used in both approaches):
Before we start guessing which brackets to remove, we first count exactly
how many misplaced '(' and ')' exist in the string.
- Loop through the string.
- If '(', increment left_invalid.
- If ')', check if there is a matching '('. If yes, decrement left_invalid.
  If no, increment right_invalid.
This drastically limits our recursive backtracking choices.

--------------------------------------------------------------------------------
APPROACH 1: The HashSet Method (Approach)
--------------------------------------------------------------------------------
Concept:
We explore all possible valid strings by choosing to either "Keep" or "Remove"
each bracket. We build the string on the fly using string concatenation (curr + ch).
Because removing the 1st ')' or 2nd ')' in "())" results in the exact same
string "()", we use an unordered_set to automatically filter out duplicates.

Example Dry Run: s = "())"
1. left_rem = 0, right_rem = 1
2. Keep '('. String: "("
3. At 1st ')':
   - Branch A (Remove): String remains "(". Next we Keep 2nd ')'. Final: "()"
   - Branch B (Keep): String becomes "()". Next we Remove 2nd ')'. Final: "()"
4. Both branches generate "()". The unordered_set keeps only one.

Complexity:
- Time: O(2^N). For every bracket, we have 2 choices. String concatenation
  takes extra O(N) time per step.
- Space: O(2^N). We store many duplicate strings in the recursion tree and HashSet.

--------------------------------------------------------------------------------
APPROACH 2: The GM Optimized Method (In-Place + Pruning) - RECOMMENDED
--------------------------------------------------------------------------------
Concept:
We eliminate the two biggest bottlenecks from Approach 1:
1. No string concatenation: We pass a single string by reference and use
   push_back() and pop_back() to save memory allocation time.
2. No HashSet: We prevent duplicates from ever being generated using a
   'last_removed' boolean flag.

The Duplicate Rule:
If we have consecutive identical brackets (e.g., "))"), removing the 1st gives
the same result as removing the 2nd.
Therefore, we only allow removing the current bracket IF we also removed the
identical bracket immediately before it.

Example Dry Run: s = "())"
1. Keep '('. String: "("
2. At 1st ')' (idx 1): We branch into Remove and Keep.
3. At 2nd ')' (idx 2):
   - If we came from the Keep branch of idx 1: s[idx] == s[idx-1], and
     last_removed is FALSE. Our rule says we CANNOT remove this one!
     This instantly prunes the duplicate branch.
   - We only successfully generate "()" once. No HashSet needed!

Complexity:
- Time: O(2^N) worst-case, but practically much faster because duplicate
  branches are instantly killed.
- Space: O(N) for the recursive call stack and a single string buffer.
  Massive memory savings over Approach 1.

COMPARISON:
Approach 2 is vastly superior. It avoids heavy memory allocations, removes the
hashing overhead, and prunes the recursion tree early. It is the standard for
top-tier competitive programming.
================================================================================
*/

// Approach 1: HashSet Method (Backtracking with String Concatenation)
// This method is simpler to implement but less efficient due to string concatenation and duplicate generation.
// Also handle duplicates without use set -> before return ans simple sort ans and used stl erase(unique(ans.begin(), ans.end()), ans.end());
static vector<string> removeInvalidParentheses(const string& s){
    vector<string> ans;
    unordered_set<string> seen; // To avoid duplicates in the answer

    int left_invalid_bracket = 0; // count of '(' that need to be removed
    int right_invalid_bracket = 0; // count of ')' that need to be removed

    // Loop through the string to count the number of invalid '(' and ')' brackets
    for (const char ch : s){
        if (ch == '(') // If we encounter a '(', we increment the count of left invalid brackets
            left_invalid_bracket++;
        else if (ch == ')'){ // If we encounter a ')', we check if there is a matching '('
            if (left_invalid_bracket > 0) // found a matching '(', so we decrement the count of left invalid brackets
                left_invalid_bracket--;
            else
                right_invalid_bracket++; // No matching '(', so we increment the count of right invalid brackets
        }
    }

    // Recursive DFS function to explore all possible valid strings
    auto dfs = [&](auto&& self, const int idx, const int l_rem_b, const int r_rem_b, const int open_cnt, const string& curr) -> void{
        // Base Case: If we have processed all characters in the string
        if (idx == s.size()){
            // If we have removed all invalid brackets and have a valid string, we add it to the answer
            if (l_rem_b == 0 && r_rem_b == 0 && open_cnt == 0){
                if (!seen.contains(curr)){ // If the current string is not already in the answer, we add it
                    ans.emplace_back(curr);
                    seen.insert(curr);
                }
            }
            return;
        }

        // get the current character
        const char ch = s[idx];

        // If the current character is a letter, we always keep it and move to the next character
        if (ch >= 'a' && ch <= 'z'){
            self(self, idx + 1, l_rem_b, r_rem_b, open_cnt, curr + ch);
            return;
        }

        // If the current character is a '(', we have two choices: remove it or keep it

        // Choice 1: If we remove it, we decrement the count of left invalid brackets and move to the next character
        if (ch == '(')
            self(self, idx + 1, l_rem_b - 1, r_rem_b, open_cnt, curr);

        // If the current character is a ')', we have two choices: remove it or keep it
        // Choice 1: If we remove it, we decrement the count of right invalid brackets and move to the
        if (ch == ')')
            self(self, idx + 1, l_rem_b, r_rem_b - 1, open_cnt, curr);

        // Choice 2: keep it, but only if it is a '(' or if it is a ')' and there is a matching '('
        if (ch == '(')
            self(self, idx + 1, l_rem_b, r_rem_b, open_cnt + 1, curr + '(');

        // Choice 2: keep it, but only if it is a ')' and there is a matching '(' (open_cnt > 0)
        if (ch == ')'){
            if (open_cnt > 0)
                self(self, idx + 1, l_rem_b, r_rem_b, open_cnt - 1, curr + ')');
        }
    };

    const string curr;
    dfs(dfs, 0, left_invalid_bracket, right_invalid_bracket, 0, curr);
    return ans;
}

// Approach 2: GM Optimized Method (In-Place + Pruning)
static vector<string> removeInvalidParenthesesOptimal(const string& s){
    vector<string> ans;
    string curr;
    curr.reserve(s.size());

    // Step 1: Count misplaced brackets
    int left_rem = 0, right_rem = 0;
    for (const char ch : s){
        if (ch == '(') // If we encounter a '(', we increment the count of left invalid brackets
            left_rem++;
        else if (ch == ')'){
            if (left_rem > 0) // found a matching '(', so we decrement the count of left invalid brackets
                left_rem--;
            else
                right_rem++; // No matching '(', so we increment the count of right invalid brackets
        }
    }

    // last_removed flag prevents duplicate generation
    auto dfs = [&](auto&& self, const int idx, const int l_rem, const int r_rem, const int open_cnt, bool last_remove) -> void{
        // Base Case: If we have processed all characters in the string
        if (idx == s.size()){
            // No unordered_set needed! We are guaranteed this is unique.
            if (l_rem == 0 && r_rem == 0 && open_cnt == 0)
                ans.emplace_back(curr);
            return;
        }

        // Get the current character
        const char ch = s[idx];

        // --- IF IT IS A LETTER ---
        if (ch != '(' && ch != ')'){
            curr.push_back(ch); // Always keep letters
            self(self, idx + 1, l_rem, r_rem, open_cnt, false); // Recurse to the next character
            curr.pop_back(); // Backtrack
            return;
        }

        // --- OPTION 1: REMOVE ---
        // GM Pruning: If this char is the same as the previous one, and we DID NOT
        // remove the previous one, removing this one would create a duplicate string.
        bool can_remove = true;
        if (idx > 0 && s[idx] == s[idx - 1] && !last_remove)
            can_remove = false;

        // if duplicate removal is allowed, we can remove the current bracket
        if (can_remove){
            if (ch == '(' && l_rem > 0)
                self(self, idx + 1, l_rem - 1, r_rem, open_cnt, true); // last_removed = true
            else if (ch == ')' && r_rem > 0)
                self(self, idx + 1, l_rem, r_rem - 1, open_cnt, true); // last_removed = true
        }

        // --- OPTION 2: KEEP ---
        curr.push_back(ch); // Action
        if (ch == '(')
            self(self, idx + 1, l_rem, r_rem, open_cnt + 1, false); // last_removed = false
        else if (ch == ')'){
            if (open_cnt > 0)
                self(self, idx + 1, l_rem, r_rem, open_cnt - 1, false); // last_removed = false
        }

        curr.pop_back(); // Backtrack
    };

    dfs(dfs, 0, left_rem, right_rem, 0, false);
    return ans;
}

static void solve() {
    string s; cin >> s;

    // Get the valid strings after removing invalid parentheses(approach 1)
    const vector<string> ans = removeInvalidParentheses(s);
    cout << "[";
    for (int i = 0; i < ans.size(); i++){
        cout << ans[i] << (i == ans.size() - 1 ? "" : ", ");
    }
    cout << "]\n";

    // GM Optimized Method (In-Place + Pruning) - RECOMMENDED
    const vector<string> ans_optimal = removeInvalidParenthesesOptimal(s);
    cout << "[";
    for (int i = 0; i < ans_optimal.size(); i++){
        cout << ans_optimal[i] << (i == ans_optimal.size() - 1 ? "" : ", ");
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

