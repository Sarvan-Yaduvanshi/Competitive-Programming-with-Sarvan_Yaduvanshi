/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-21 18:17:34
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
using namespace std;

/*
🎯 Problems in this file:
    1. Print subsequences with sum = K
    2. Check if ANY subsequence has sum = K
    3. Count subsequences with sum = K
*/

/*
 * Problem: Print subsequences with sum = K
 * Given an array of integers and a target sum K, print all subsequences of the array that sum up to K.
 * Examples:
 * Input: arr = [3, 1, 2], K = 3
 * Output: [[3], [1, 2]]
 * Explanation: The subsequences [3] and [1, 2] both sum to 3.
 * Input: arr = [1, 2, 3], K = 4
 * Output: [[1, 3]
 * Explanation: The subsequences [1, 3] and [2, 2] both sum to 4.
 */

static vector<vector<int>> subsequenceWithSumEqualK(const vector<int>& arr, const int k){
    int n = arr.size();
    vector<vector<int>> ans;
    vector<int> current;

    // --- GM PRE-COMPUTATION: Suffix Sums ---
    // suffix_sum[i] stores the total sum of all elements from index i to the end.
    vector<int> suffix_sum(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
        suffix_sum[i] = suffix_sum[i + 1] + arr[i];

    auto dfs = [&](auto&& self, const int idx, int curr_sum) -> void{
        // PRUNING: if all elements are non-negative and sum already > K, stop
        // (only valid when all arr[i] >= 0)
        // if (currentSum > K) return;
        if (curr_sum > k) return;

        // 2. THE FLOOR: Is it mathematically impossible to reach k?
        // If current sum + EVERY remaining element is still less than k, DIE!
        if (curr_sum + suffix_sum[idx] < k) return;

        // Base Case: if current sum == k than add current subsequence to ans
        if (idx == n){
            if (curr_sum == k)
                ans.push_back(current);

            return;
        }

        // Choice 1: Take
        current.push_back(arr[idx]);
        self(self, idx + 1, curr_sum + arr[idx]);
        current.pop_back();

        // Choice 2: Not take
        self(self, idx + 1, curr_sum);
    };

    dfs(dfs, 0, 0);
    return ans;
}

/*
 * Problem 2: Check if ANY subsequence has sum = K
 * Given an array of integers and a target sum K, check if there exists any subsequence
 * of the array that sums up to K. Return true if such a subsequence exists, otherwise return false.
 * Examples:
 * Input: arr = [3, 1, 2], K = 3
 * Output: true
 * Explanation: The subsequence [3] sums to 3.
 * Input: arr = [1, 2, 3], K = 7
 * Output: false
 * Explanation: No subsequence sums to 7.
 * Constraints:
 * 1 ≤ arr.length ≤ 2000
 * 1 ≤ arr[i] ≤ 1000
 * 1 ≤ target ≤ 2000
 * Topics: Recursion, Backtracking, Subset Sum Problem, Dynamic Programming
 * Expected Complexities:
 * Time Complexity: O(N * K) && Auxiliary Space: O(N * K) for DP table (if using DP approach)
 *
 * Currently, we will implement a recursive backtracking solution with pruning.
 * So worst case time complexity is O(2^N) but with pruning it will be much faster in practice.
 *
 */

static bool checkSubsequenceSum(const vector<int>& arr, const int k){
    int n = arr.size();

    vector<int> suffix_sum(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
        suffix_sum[i] = suffix_sum[i + 1] + arr[i];

    auto dfs = [&](auto&& self, const int idx, const int curr_sum) -> bool{
        if (curr_sum > k) return false; // Ceiling
        if (curr_sum + suffix_sum[idx] < k) return false; // Floor

        // Base Case:
        if (idx == n)
            return curr_sum == k;

        // --- CHOICE 1: TAKE ---
        // If the "Take" branch found the answer, immediately return true to the parent!
        if (self(self, idx + 1, curr_sum + arr[idx]) == true)
            return true;

        // --- CHOICE 2: NOT TAKE ---
        // If the "Not Take" branch found the answer, immediately return true!
        if (self(self, idx + 1, curr_sum) == true)
            return true;

        return false;
    };

    // If both choices failed, this path is a dead end.
    return dfs(dfs, 0, 0);
}

/*
 * Problem 3: Count subsequences with sum = K
 * Given an array of integers and a target sum K, count the number of subsequences of
 * the array that sum up to K. Return the count as an integer.
 * Examples:
 * Input: arr = [3, 1, 2], K = 3
 * Output: 2
 * Explanation: The subsequences [3] and [1, 2] both sum to 3.
 * Input: arr = [1, 2, 3], K = 4
 * Output: 1
 * Explanation: The only one subsequence [1, 3] sums to 4.
 * Constraints:
 * 1 ≤ arr.length ≤ 2000
 * 1 ≤ arr[i] ≤ 1000
 * 1 ≤ target ≤ 2000
 * Topics: Recursion, Backtracking, Subset Sum Problem, Dynamic Programming
 * Expected Complexities:
 * Time Complexity: O(N * K) && Auxiliary Space: O(N * K) for DP table (if using DP approach)
 */

static int CountSubsequencesWithSum(const vector<int>& arr, const int k){
    auto dfs = [&](auto&& self, const int idx, const int curr_sum) -> int{
        // Base Case:
        if (idx == arr.size()){
            return (curr_sum == k ? 1 : 0);
        }

        // TAKE + NOT TAKE → sum their counts
        int take = self(self, idx + 1, curr_sum + arr[idx]);
        int not_take = self(self, idx + 1, curr_sum);

        return (take + not_take);
    };

    return dfs(dfs, 0, 0);
}
static void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (auto &x : arr)
        cin >> x;

    // vector<vector<int>> result = subsequenceWithSumEqualK(arr, k);
    // cout << "[";
    // for (int i = 0; i < result.size(); i++){
    //     cout << "[";
    //     for (int j = 0; j < result[i].size(); j++){
    //         cout << result[i][j] << (j == result[i].size() - 1 ? "" : ", ");
    //     }
    //     cout << "]" << (i == result.size() - 1 ? "" : ", ");
    // }
    // cout << "]\n";

    // Function 2: call checkSubsequenceSum == k
    // bool exists = checkSubsequenceSum(arr, k);
    // cout << (exists ? "YES" : "NO") << "\n";

    // Function 3: call CountSubsequencesWithSum == k
    int count = CountSubsequencesWithSum(arr, k);
    cout << count << "\n";
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

