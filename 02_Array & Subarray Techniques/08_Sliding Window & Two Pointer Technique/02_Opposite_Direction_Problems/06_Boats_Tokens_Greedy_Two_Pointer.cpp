/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Greedy Two Pointer Problems (Boats, Tokens, Merge to Palindrome)
 *  Level   : Medium
 * ============================================================================
 *
 *  PROBLEMS:
 *   LC 881  — Boats to Save People  https://leetcode.com/problems/boats-to-save-people/
 *   LC 948  — Bag of Tokens  https://leetcode.com/problems/bag-of-tokens/
 *   LC 2422 — Merge Ops to Make Palindrome
 *             https://leetcode.com/problems/merge-operations-to-turn-array-into-a-palindrome/
 *   LC 1498 — Number of Subsequences That Satisfy Sum Condition
 *             https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 *
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// ============================================================================
// LC 881: Boats to Save People
// ============================================================================
/*
 * Each boat carries at most 2 people, with weight limit.
 * Sort by weight. Pair lightest with heaviest if possible.
 * Greedy: always try to pair the extremes.
 */
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = (int)people.size() - 1;
    int boats = 0;

    while (left <= right) {
        if (people[left] + people[right] <= limit) {
            left++;  // Both fit in one boat
        }
        right--;  // Heaviest person always gets on a boat
        boats++;
    }
    return boats;
}

// ============================================================================
// LC 948: Bag of Tokens
// ============================================================================
/*
 * Play tokens face-up (spend power, gain score) or face-down (spend score, gain power).
 * Maximize score.
 *
 * Greedy: Sort tokens. Use cheapest to gain score, most expensive to gain power.
 */
int bagOfTokensScore(vector<int>& tokens, int power) {
    sort(tokens.begin(), tokens.end());
    int left = 0, right = (int)tokens.size() - 1;
    int score = 0, maxScore = 0;

    while (left <= right) {
        if (power >= tokens[left]) {
            // Play cheapest face-up: spend power, gain score
            power -= tokens[left];
            score++;
            left++;
            maxScore = max(maxScore, score);
        }
        else if (score > 0) {
            // Play most expensive face-down: spend score, gain power
            power += tokens[right];
            score--;
            right--;
        }
        else {
            break;  // Can't do anything
        }
    }
    return maxScore;
}

// ============================================================================
// LC 2422: Merge Operations to Turn Array into a Palindrome
// ============================================================================
/*
 * Can merge adjacent elements (sum them). Min operations to make palindrome.
 * Two pointer from ends: if left sum < right sum, merge left. Vice versa.
 */
int minimumOperations(vector<int>& nums) {
    int left = 0, right = (int)nums.size() - 1;
    long long leftSum = nums[left], rightSum = nums[right];
    int ops = 0;

    while (left < right) {
        if (leftSum == rightSum) {
            left++;
            right--;
            if (left < right) {
                leftSum = nums[left];
                rightSum = nums[right];
            }
        }
        else if (leftSum < rightSum) {
            left++;
            leftSum += nums[left];
            ops++;
        }
        else {
            right--;
            rightSum += nums[right];
            ops++;
        }
    }
    return ops;
}

int main() {
    // Boats
    vector<int> people = {3, 2, 2, 1};
    cout << "Boats needed: " << numRescueBoats(people, 3) << "\n"; // 3

    // Bag of Tokens
    vector<int> tokens = {100, 200, 300, 400};
    cout << "Max score: " << bagOfTokensScore(tokens, 200) << "\n"; // 2

    // Merge to Palindrome
    vector<int> nums = {4, 3, 2, 1, 2, 3, 1};
    cout << "Merge ops: " << minimumOperations(nums) << "\n"; // 2

    return 0;
}

