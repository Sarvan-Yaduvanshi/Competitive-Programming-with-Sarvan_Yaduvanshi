/*
 * ============================================================================
 *                      HOUSE ROBBER VARIANTS
 * ============================================================================
 * Author  : Sarvan Yaduvanshi
 * Chapter : 13 - Dynamic Programming
 * Topic   : 1D DP — House Robber I, II, and variants
 * Level   : ⭐ Beginner to ⭐⭐ Intermediate
 * ============================================================================
 *
 * HOUSE ROBBER I (LeetCode 198):
 *   Linear houses. Can't rob adjacent. Maximize money.
 *   dp[i] = max(dp[i-1], dp[i-2] + nums[i])
 *
 * HOUSE ROBBER II (LeetCode 213):
 *   Circular houses. First and last are adjacent.
 *   Solve twice: houses[0..n-2] and houses[1..n-1], take max.
 *
 * DELETE & EARN (LeetCode 740):
 *   Delete num[i] → earn num[i], but delete all num[i]-1 and num[i]+1
 *   Transform to House Robber on frequency array!
 *
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// House Robber I — Linear
int robLinear(vector<int>& nums, int lo, int hi) {
    int prev2 = 0, prev1 = 0;
    for (int i = lo; i <= hi; i++) {
        int curr = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int houseRobber1(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    return robLinear(nums, 0, n - 1);
}

// House Robber II — Circular
int houseRobber2(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    // Either rob houses[0..n-2] or houses[1..n-1]
    return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
}

// Delete and Earn (LeetCode 740)
int deleteAndEarn(vector<int>& nums) {
    int maxVal = *max_element(nums.begin(), nums.end());
    vector<int> earn(maxVal + 1, 0);

    // Transform: earn[x] = total points from deleting all x's
    for (int x : nums) earn[x] += x;

    // Now it's House Robber on earn[] array!
    int prev2 = 0, prev1 = 0;
    for (int i = 0; i <= maxVal; i++) {
        int curr = max(prev1, prev2 + earn[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// Maximum Sum Non-Adjacent Subsequence (generalization of House Robber)
long long maxSumNonAdjacent(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    if (n == 1) return max(0, arr[0]);

    long long prev2 = 0, prev1 = max(0, arr[0]);
    for (int i = 1; i < n; i++) {
        long long curr = max(prev1, prev2 + (long long)arr[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== HOUSE ROBBER VARIANTS ===" << endl;

    // House Robber I
    vector<int> houses1 = {2, 7, 9, 3, 1};
    cout << "\n--- House Robber I ---" << endl;
    cout << "Houses: "; for (int h : houses1) cout << h << " ";
    cout << "\nMax rob: " << houseRobber1(houses1) << endl;
    // Pick 2+9+1=12

    // House Robber II (circular)
    vector<int> houses2 = {2, 3, 2};
    cout << "\n--- House Robber II (Circular) ---" << endl;
    cout << "Houses: "; for (int h : houses2) cout << h << " ";
    cout << "\nMax rob: " << houseRobber2(houses2) << endl;
    // Can't rob 0 and 2 (circular), best = 3

    // Delete and Earn
    vector<int> nums = {3, 4, 2};
    cout << "\n--- Delete and Earn ---" << endl;
    cout << "Nums: "; for (int n : nums) cout << n << " ";
    cout << "\nMax earn: " << deleteAndEarn(nums) << endl;
    // Delete 4→earn 4, which removes 3. Then delete 2→earn 2. Total=6

    // Non-adjacent sum
    vector<int> arr = {5, 5, 10, 100, 10, 5};
    cout << "\n--- Max Sum Non-Adjacent ---" << endl;
    cout << "Array: "; for (int a : arr) cout << a << " ";
    cout << "\nMax sum: " << maxSumNonAdjacent(arr) << endl;
    // Pick 5+100+5=110

    return 0;
}

