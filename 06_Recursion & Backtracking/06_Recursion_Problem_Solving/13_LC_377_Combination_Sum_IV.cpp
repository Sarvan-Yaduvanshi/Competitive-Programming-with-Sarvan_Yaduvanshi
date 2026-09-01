/*
Author: Sarvan.DP.GrandMaster
Created : 2026-08-30 23:50:34
*/


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
#include <unordered_set>
using namespace std;

/* Problem: Combination Sum IV (LeetCode 377)
 * Difficulty: Medium
 * Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.
 * The answer is guaranteed to fit in a 32-bit integer.
 * Example 1: Input: nums = [1,2,3], target = 4
 *              Output: 7
 * Explanation: The possible combination ways are:
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 *
 * Example 2: Input: nums = [9], target = 3
 *            Output: 0
 * Constraints:
 * - 1 <= nums.length <= 200
 * - 1 <= nums[i] <= 1000
 * - All the elements of nums are unique.
 * - 1 <= target <= 1000
 *
 * Topics: Dynamic Programming, Backtracking
 *
 * Follow up: What if negative numbers are allowed in the given array? How does it change the problem?
 * What limitation we need to add to the question to allow negative numbers?
 */

/* Problem Understanding:
 *		This problem different from combination sum I and II, III
 *		because in this problem we can use the same number multiple times and the order of numbers matters.
 *		For example, if we have nums = [1, 2] and target = 3, the combinations (1, 2) and (2, 1) are considered different.
 *		But in combination sum I and II, the order of numbers does not matter.
 *		So This problem is more similar to permutation problems, where the order of elements matters.
 */

/*
=============================================================
COMBINATION SUM IV — RECURSION / BACKTRACKING (Approach 1)
============================================================
    APPROACH:
        - Start from target.
        - At every step, try every nums[i].
        - Reduce target by nums[i].
        - When tar == 0, one valid ORDERED combination is found.
        - Order matters:
                1 + 2 + 1
                2 + 1 + 1
            are counted separately.
-------------------------------------------------------------
RECURSION IDEA:
    dfs(tar)
        |
        |-- choose nums[0] → dfs(tar - nums[0])
        |-- choose nums[1] → dfs(tar - nums[1])
        |-- choose nums[2] → dfs(tar - nums[2])
        |
        └── continue until tar == 0

    Example:
        nums = {1,2,3}
        target = 4
        Valid ordered combinations:
            1+1+1+1
            1+1+2
            1+2+1
            2+1+1
            1+3
            3+1
            2+2
        Answer = 7
-------------------------------------------------------------
TIME COMPLEXITY:
    Let:
        N = nums.size(), T = target, Each recursive call can branch into N choices.
        Maximum recursion depth: T / min(nums)
    ->  Worst-case recursion tree is exponential.
            Loose upper bound: O(N^T)
            Therefore: TIME = O(N^T)   // Exponential
            The actual number of calls depends on nums and target.
-------------------------------------------------------------
SPACE COMPLEXITY:
    No DP/memo array is used., Only recursion stack is used.
    Maximum depth: T / min(nums)
    Therefore:
        SPACE = O(T / min(nums))
    If nums contains 1: SPACE = O(T)
-------------------------------------------------------------
WHY THIS CAN TLE:
    MAIN REASON: Exponential recursion + repeated subproblems.
    The main problem is REPEATED SUBPROBLEMS., The same dfs(tar) is calculated many times.
    Example:
        dfs(4)
            ├── dfs(3)
            │     ├── dfs(2)
            │     └── dfs(1)
            │
            ├── dfs(2)   ← repeated
            │
            └── dfs(1)   ← repeated
    So: Same target -> calculated again and again -> huge recursion tree -> exponential number of calls -> TLE

-------------------------------------------------------------
TLE EXAMPLE:
    nums = [2,1,3],   target = 35
    This test case can cause TLE on a constrained judge.
    REASON: 1 is present, so we can make very long sequences:
    35 → 34 → 33 → 32 → ... → 0
    But at every target we can also choose 2 or 3:
        dfs(35)
        ├── dfs(34)   // choose 1
        ├── dfs(33)   // choose 2
        └── dfs(32)   // choose 3
        Then:
            dfs(34)
                ├── dfs(33)   ← already calculated
                ├── dfs(32)   ← already calculated
                └── dfs(31)
            dfs(33)
                ├── dfs(32)   ← calculated AGAIN
                ├── dfs(31)   ← calculated AGAIN
                └── dfs(30)
        The repeated calls grow exponentially.
        Therefore:
            nums = [2,1,3]
                target = 35 -> huge recursion tree -> many repeated dfs(tar) -> TLE
-------------------------------------------------------------
PRACTICAL CONSTRAINT NOTE:
    Small target: T <= 20-30  → usually manageable
    Around: T = 35 → can become slow / TLE depending on judge
    Large target: T >= 50 → pure recursion is generally impractical
    There is NO fixed maximum passing constraint because it
        depends on: - nums values, - target, - number of elements, - judge time limit, - hardware
-------------------------------------------------------------
KEY ISSUE:
    Current code does NOT remember the answer for dfs(tar).
    So if dfs(10) is needed 100 times, the code calculates dfs(10) 100 times.
    Memoization changes this by storing:
        dp[tar] = answer for dfs(tar)
        Then each target is solved only once.
FIX:
    Memoization / DP.
-------------------------------------------------------------
*/

// Approach 1: Recursion / Backtracking (TLE)
static int combinationSum4BruteForce(const vector<int>& nums, const int target){
	int combinations_cnt = 0;

	auto dfs = [&](auto&& self, const int tar) -> void{
	    // Base case: If target is 0, we found a valid combination
		if (tar == 0){
			combinations_cnt++;
			return;
		}

		for (const int num : nums){
		    // Ignore numbers greater than the current target
			if (num > tar)
				continue;

		    // Choose the current number and recurse with the reduced target
			self(self, tar - num);
		}
	};

	dfs(dfs, target);
	return combinations_cnt;
}

/*
     * Core Idea:
     * 1. This is a permutation counting problem, so Backtracking will TLE. We use Bottom-Up DP.
     * 2. Create an array `dp` of size `target + 1`. `dp[i]` stores the number of ways to make sum `i`.
     * 3. Base Case: dp[0] = 1 (There is 1 way to make sum 0).
     * 4. For every target sum 'i' from 1 to target:
     *      For every number 'num' in the array:
     *          If 'num <= i', the number of ways to make 'i' increases by the number of ways to make 'i - num'.
     *          Equation: dp[i] = dp[i] + dp[i - num]
     *
     * Time Complexity: O(T * N)
     * - T is the target, N is the size of the nums array.
     * - We have an outer loop running 'T' times and an inner loop running 'N' times.
     *
     * Space Complexity: O(T)
     * - We allocate an array of size 'target + 1' to store the DP states.
     */

// Approach 2: Dynamic Programming (Bottom-Up)
static int combinationSum4(vector<int>& nums, int target){
    // Use unsigned long long to prevent integer overflow on intermediate states
    // LeetCode test cases have paths that exceed INT_MAX before the final valid answer
    vector<unsigned long long> dp(target + 1, 0);

    // Base case: 1 way to make target 0
    dp[0] = 1;

    // Build the dp array from 1 up to target
    for (int i = 1; i <= target; i++){
        for (const int num : nums){
            // If the current number is small enough to contribute to the sum 'i'
            if (i >= num)
                dp[i] += dp[i - num];
        }
    }

    // Return the final answer, safely casted back to int as per function signature
    return dp[target];
}

// Consider:
// How would you modify the DP state if negative numbers were allowed but cycles had to be avoided?
/*
 * Core Idea:
 * We use DFS and maintain an unordered_set of the prefix sums we have
 * encountered on the CURRENT recursive path.
 * If adding a number results in a sum that is already in the set,
 * we skip it (prune the cycle).
 */

static int combinationSum4WithNegatives(const vector<int>& nums, const int target) {
    unordered_set<int> visited; // To track sums on the current path

    // Recursive DFS function to explore combinations
    auto dfs = [&](auto&& self, const int current_sum) -> int{
        // Base case: If we reach the target sum, count this as a valid combination
        if (current_sum == target) return 1;

        // If we exceed the target, this path is invalid
        int ways = 0;
        for (const int num : nums) {
            int next_sum = current_sum + num;

            // Cycle avoidance: Only explore if we haven't seen this sum on this path
            if (!visited.contains(next_sum)) {
                visited.insert(next_sum);            // Choose (mark visited)
                ways += self(self, next_sum); // Explore
                visited.erase(next_sum);             // Un-choose (backtrack)
            }
        }
        return ways;
    };
    return dfs(dfs, 0); // Start DFS from sum 0
}

static void solve() {
    int n, target;
	cin >> n >> target;

	vector<int> nums(n);
	for (auto& x : nums)
		cin >> x;

	// Using the DP approach to find the number of combinations
	const int result = combinationSum4(nums, target);
	cout << result << "\n";
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

