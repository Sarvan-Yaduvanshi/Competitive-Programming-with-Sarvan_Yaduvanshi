/*
Author: Sarvan Yaduvanshi
Created : 2026-09-01 20:02:05
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
    Problem: Generate all unique combinations(Subsets)
    Given a string s, return all possible unique combinations (subsets) of the characters in the string.
    The combinations can be returned in any order.
    Example 1: Input: s = "abc"
               Output: ["a","b","c","ab","ac","bc","abc"]
                Explanation: The unique combinations of the string "abc" are:
                    - Single character combinations: "a", "b", "c"
                    - Two character combinations: "ab", "ac", "bc"
                    - Three character combination: "abc"
    Example 2: Input: s = "aab"
               Output: ["a","aa","ab","b"]
               Explanation: The unique combinations of the string "aab" are:
                    - Single character combinations: "a", "b"
                    - Two character combinations: "aa", "ab"
                    - Three character combination: "aab"

 * Core Idea:
 * 1. A string is just an array of characters. We can use string::push_back
 *    and string::pop_back exactly like we do with vectors.
 * 2. Sort the input string first. This groups identical characters together
 *    so we can easily skip duplicates without using a slow hash set.
 * 3. We capture the 'current' state at every single step to get all subset
 *    lengths (from size 1 up to the full string length).
 * 4. Duplicate Pruning: If 'i > start' and s[i] == s[i-1], we skip it because
 *    we have already generated all combinations starting with that character
 *    at this specific recursion depth.
 *
 * Time Complexity: O(N * 2^N)
 * - N is the length of the string.
 * - In the worst case (all unique characters), there are 2^N unique combinations.
 * - Copying the 'current' string into the 'ans' array takes up to O(N) time.
 * - The O(N log N) sorting step is heavily dominated by the 2^N generation.
 *
 * Space Complexity: O(N)
 * - The recursion call stack goes up to a depth of N.
 * - The 'current' string takes O(N) space.
 * - (We do not count the O(N * 2^N) space required to hold the output array).
 */
static vector<string> stringCombinations(string s) {
    // 1. Sort to enable duplicate pruning
    ranges::sort(s);

    vector<string> ans;
    string current;

    // Prevent minor memory reallocations for our state string
    current.reserve(s.length());

    auto dfs = [&](auto&& self, const int start) -> void {
        // We capture the combination at every step (excluding the empty string)
        if (!current.empty()) {
            ans.emplace_back(current);
        }

        for (int i = start; i < s.length(); ++i) {
            // GM Pruning: Skip duplicate characters at the same depth level
            if (i > start && s[i] == s[i - 1])
                continue;

            // Choose
            current.push_back(s[i]);

            // Explore
            self(self, i + 1);

            // Un-choose (Backtrack)
            current.pop_back();
        }
    };

    dfs(dfs, 0);
    return ans;
}
static void solve() {
    string s;
    cin >> s;

    vector<string> combinations = stringCombinations(s);
    cout << "All unique combinations of the string \"" << s << "\":\n";
    cout << "[";
    for (size_t i = 0; i < combinations.size(); ++i){
        cout << "\"" << combinations[i] << "\"";
        if (i < combinations.size() - 1) {
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

