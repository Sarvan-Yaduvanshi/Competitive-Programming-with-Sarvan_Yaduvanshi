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
#include <cassert>
using namespace std;

/*
🎯 Problems in this file:
    1. Print subsequences with sum = K
    2. Count subsequences with sum = K
    3. Check if ANY subsequence has sum = K
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

static vector<vector<int>> ans;
static vector<int> current;
static vector<vector<int>> subsequenceWithSumEqualK(vector<int>& arr, const int k){
    auto dfs = [&](auto&& self, const int idx, int curr_sum) -> void{
        // PRUNING: if all elements are non-negative and sum already > K, stop
        // (only valid when all arr[i] >= 0)
        // if (currentSum > K) return;
        if (curr_sum > k)
            return;

        // Base Case: if current sum == k than add current subsequence to ans
        if (idx == arr.size()){
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

    ans.clear();
    current.clear();
    dfs(dfs, 0, 0);
    return ans;
}
static void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (auto &x : arr)
        cin >> x;

    vector<vector<int>> result = subsequenceWithSumEqualK(arr, k);
    cout << "[";
    for (int i = 0; i < result.size(); i++){
        cout << "[";
        for (int j = 0; j < result[i].size(); j++){
            cout << result[i][j] << (j == result[i].size() - 1 ? "" : ", ");
        }
        cout << "]" << (i == result.size() - 1 ? "" : ", ");
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

