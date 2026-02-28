/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : 4Sum and General K-Sum Framework
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  PROBLEMS:
 *   LC 18   — 4Sum  https://leetcode.com/problems/4sum/
 *   LC 454  — 4Sum II  https://leetcode.com/problems/4sum-ii/
 *   CSES 1642 — Sum of Four Values  https://cses.fi/problemset/task/1642
 *
 *  APPROACH:
 *  ─────────
 *  4Sum: Sort, fix 2 elements, two pointer on remaining → O(N³)
 *  4Sum II: Split into 2 groups, HashMap → O(N²)
 *  K-Sum: Recursive — fix 1, solve (K-1)Sum → O(N^(K-1))
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// ============================================================================
// LC 18: 4Sum
// ============================================================================
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        // Early termination
        if ((long long)nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
        if ((long long)nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;

        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            // Early termination
            if ((long long)nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
            if ((long long)nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;

            int left = j + 1, right = n - 1;
            long long need = (long long)target - nums[i] - nums[j];

            while (left < right) {
                long long sum = (long long)nums[left] + nums[right];
                if (sum == need) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++; right--;
                }
                else if (sum < need) left++;
                else right--;
            }
        }
    }
    return result;
}

// ============================================================================
// LC 454: 4Sum II — Four different arrays, count tuples (i,j,k,l) summing to 0
// ============================================================================
/*
 * Split into two groups: (A+B) and (C+D).
 * Store all A[i]+B[j] in a hashmap.
 * For each C[k]+D[l], check if -(C[k]+D[l]) exists in map.
 * Time: O(N²), Space: O(N²)
 */
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    unordered_map<int, int> mp;

    // Store all sums of A+B
    for (int a : A)
        for (int b : B)
            mp[a + b]++;

    // Count matching -(C+D)
    int count = 0;
    for (int c : C)
        for (int d : D)
            if (mp.count(-(c + d)))
                count += mp[-(c + d)];

    return count;
}

// ============================================================================
// GENERAL K-SUM FRAMEWORK (Recursive)
// ============================================================================
/*
 * Reduce K-Sum to 2-Sum:
 * - If K > 2: fix one element, recursively solve (K-1)Sum
 * - If K == 2: use two pointer
 *
 * Time: O(N^(K-1))
 *
 * Works for ANY K!
 */
class KSumSolver {
public:
    vector<vector<int>> kSum(vector<int>& nums, long long target, int k) {
        sort(nums.begin(), nums.end());
        return kSumHelper(nums, target, k, 0);
    }

private:
    vector<vector<int>> kSumHelper(vector<int>& nums, long long target, int k, int start) {
        vector<vector<int>> result;
        int n = nums.size();

        if (start >= n || k < 2) return result;

        // Base case: 2-Sum with two pointer
        if (k == 2) {
            int left = start, right = n - 1;
            while (left < right) {
                long long sum = (long long)nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++; right--;
                }
                else if (sum < target) left++;
                else right--;
            }
            return result;
        }

        // Recursive case: fix one element, solve (K-1)Sum
        for (int i = start; i < n - k + 1; i++) {
            if (i > start && nums[i] == nums[i - 1]) continue;

            // Early termination
            long long minSum = 0, maxSum = 0;
            for (int j = 0; j < k; j++) minSum += nums[i + j];
            for (int j = 0; j < k; j++) maxSum += nums[n - 1 - j];
            if (minSum > target) break;
            if (maxSum < target) continue;

            auto subResult = kSumHelper(nums, target - nums[i], k - 1, i + 1);
            for (auto& sub : subResult) {
                sub.insert(sub.begin(), nums[i]);
                result.push_back(sub);
            }
        }
        return result;
    }
};

int main() {
    // 4Sum
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    auto res = fourSum(nums, 0);
    cout << "4Sum:\n";
    for (auto& q : res) {
        cout << "  [";
        for (int i = 0; i < 4; i++) cout << q[i] << (i < 3 ? ", " : "");
        cout << "]\n";
    }

    // General K-Sum (5-Sum example)
    KSumSolver solver;
    vector<int> nums2 = {1, 2, 3, 4, 5, 6, 7, -1, -2, -3};
    auto res5 = solver.kSum(nums2, 10, 5);
    cout << "\n5-Sum (target=10):\n";
    for (auto& v : res5) {
        cout << "  [";
        for (int i = 0; i < (int)v.size(); i++)
            cout << v[i] << (i < (int)v.size() - 1 ? ", " : "");
        cout << "]\n";
    }

    return 0;
}

