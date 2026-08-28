/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-25 18:48:43
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
 * 🎯 Problems in this file:
 *      1. Given subsets finds the original array
 *      2. Leetcode 1982. Find Array Given Subset Sums(Positive sums)
 *      3. Leetcode 1982. Find Array Given Subset Sums(Negative & Positive sums)
 */

// Problem 1: Given subset finds the original array
// Logic: Loop through traverse subset sum find how size == 1 this is original array
// Time Complexity: O(N) Traverse through the subset sum
// Space Complexity: O(N) for storing the original array
static vector<int> recoverArray(vector<vector<int>>& subsets){
    // Step 1: Create a new array store original array
    vector<int> original_array;

    // Step 2: Loop through traverse whole subsets
    for (const vector<int>& subset : subsets){
        // If the subset has exactly 1 element, it is part of the original array!
        if (subset.size() == 1)
            original_array.push_back(subset[0]);
    }

    return original_array;
}

/*
    Problem 2: Leetcode 1982. Find Array Given Subset Sums(Positive sums)
            Example: Input: n = 3, sums = [0,1,2,3,4,5,6,7] Output: [1,2,4]
            Example: Input: n = 2, sums = [0,1,2,3] Output: [1,2]
--> CORE IDEA:
            Suppose smallest_element = x.
            Every subset sum comes in a pair:
            S  -> subset does NOT contain x
            S + x -> same subset but DOES contain x
            So:
                keep S
                remove S + x
        Example:
            S = 3, x = 1
            3     -> without 1
            3 + 1 = 4 -> with 1
        After removing all (S + x) pairs, the remaining sums are subset sums of the remaining elements.
        Also:
        0 is always the smallest subset sum. Therefore, the second smallest sum = next original element.
        Repeat until only 0 remains.
        *** --> One-line memory trick: Find x → pair every S with S+x → keep S → remove S+x → repeat.

    Time Complexity: O(N log N) for sorting the sums and removing elements from the multiset
    Space Complexity: O(N) for storing the original array and the multiset
*/
static vector<int> recoverArray(int n, vector<int>& sums){
    // A multiset keeps our sums sorted and handles duplicates automatically
    multiset<int> st(sums.begin(), sums.end());
    vector<int> original_array;

    // Keep going until only the empty subset sum (0) is left
    while (st.size() > 1){
        auto it = st.begin(); // point to first smallest element{0} -> empty subset first time
        ++it; // Move from the 0 to the second smallest number
        // second smallest element is 1 so is valid answer push it to original array
        int smallest_element = *it;
        original_array.push_back(smallest_element);

        // Create a new set for the next round
        multiset<int> remaining_sum;
        // Pair up S and (S + smallest_element) and destroy the larger half
        while (!st.empty()){
            int S = *st.begin();
            // Keep S for the next round
            remaining_sum.insert(S);

            // Erase S and its partner (S + smallest_element) from the current set
            st.erase(S);
            st.erase(st.find(S + smallest_element));
        }

        // Move to the next round with half the elements
        st = remaining_sum;
    }
    return original_array;
}

/*
Problem 3: Leetcode 1982. Find Array Given Subset Sums(Negative & Positive sums)
Difficulty Level: Hard Version
You are given an integer n representing the length of an unknown array that you are trying to recover.
You are also given an array sums containing the values of all 2^n subset sums of the unknown array (in no particular order).
Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.
Note: Test cases are generated such that there will always be at least one correct answer.

Example 1:
Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
Output: [1, 2, -3]
Explanation: [1,2,-3] is able to achieve the given subset sums:
- []: sum is 0
- [1]: sum is 1
- [2]: sum is 2
- [1,2]: sum is 3
- [-3]: sum is -3
- [1,-3]: sum is -2
- [2,-3]: sum is -1
- [1,2,-3]: sum is 0
Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.

Example 2:
Input: n = 2, sums = [0,0,0,0]
Output: [0,0]
Explanation: The only correct answer is [0,0].
Constraints:
1 <= n <= 15
Sums.length == 2^n
-10^4 <= sums[i] <= 10^4
Topics: Array, Hash Table, Sorting, Counting, Backtracking, Bit Manipulation, Divide and Conquer
*/

/*
    CORE IDEA:
        1. Sort all subset sums.
        2. The difference between the first two sums gives:
                d = |next original element|
        3. Every subset sum S has a partner:
                S + d
        So split all sums into pairs:
                S       -> LEFT
                S + d   -> RIGHT
        Use `used[]` so each sum is used exactly once.
        4. We still don't know whether the element is +d or -d.
        Check where 0 goes:
                0 in LEFT  -> element = +d
                0 in RIGHT -> element = -d
        Why?
            0 represents the empty subset, so its side tells us
            which group represents the subset sums without the recovered element.
        5. Keep the correct half and repeat.

    MEMORY TRICK: Find d -> Pair S with S+d -> Split LEFT / RIGHT -> Check where 0 is -> Choose +d or -d -> Keep that half -> Repeat
    Time Complexity: O(N 2^N) for sorting the sums and splitting them into pairs
    Space Complexity: O(2^N) for storing the original array and the left/right halves of the sums
*/
static vector<int> recoverArrayNeg(int n, vector<int>& sums){
    // 1. Sort the sums so we can safely find 'd' and use two pointers
    ranges::sort(sums);
    vector<int> ans;

    // Repeat exactly n times to find all n original elements
    for (int i = 0; i < n; i++){
        // d is the absolute value of our next original element
        int d = sums[1] - sums[0];
        vector<int> left, right;
        vector<bool> used(sums.size(), false);
        bool zero_in_left = false;

        // The right pointer to find the S + d partner
        int r = 0;

        // 2. The Great Split
        for (int l = 0; l < sums.size(); l++){
            if (used[l]) continue;

            // Add the smaller number to the left half
            left.push_back(sums[l]);
            if (sums[l] == 0) zero_in_left = true; // Track if 0 is in left
            used[l] = true;

            // Move 'r' forward to find the matching partner (sums[i] + d)
            r = max(r, l + 1);
            while (r < sums.size() && (used[r] || sums[r] != sums[l] + d))
                r++;

            // Add the partner to the right half
            right.push_back(sums[r]);
            used[r] = true;
        }

        // 3. The Zero Check
        if (zero_in_left){
            ans.push_back(d); // Keep the left half for the next round
            sums = left;
        } else{
            ans.push_back(-d);
            sums = right; // Keep the right half for the next round
        }
    }

    return ans;
}
static void solve() {
    int n;
    cin >> n;

    vector<int> sums(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        cin >> sums[i];
    }

    // Function call to recover the original array from the subsets
    // vector<vector<int>> subsets = {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}};
    // vector<int> ans = recoverArray(subsets);
    // cout << "1) -> Print original array given subsets\n [";
    // for (int i = 0; i < ans.size(); i++)
    //     cout << ans[i] << (i == ans.size() - 1 ? "" : ", ");
    // cout << "]\n";

    // Function call to recover the original array from the subset sums
    // vector<int> original_array = recoverArray(n, sums);
    // cout << "2) -> Print original array given subset sums\n [";
    // for (int i = 0; i < original_array.size(); i++)
    //     cout << original_array[i] << (i == original_array.size() - 1 ? "" : ", ");
    // cout << "]\n";

    // Function call to recover array from subset sums with negative and positive sums
    vector<int> original_array_neg_pos = recoverArrayNeg(n, sums);
    cout << "3) -> Print original array given subset sums with negative and positive sums\n [";
    for (int i = 0; i < original_array_neg_pos.size(); i++)
        cout << original_array_neg_pos[i] << (i == original_array_neg_pos.size() - 1 ? "" : ", ");
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

