/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : At Most K Distinct Characters/Elements
 *  Level   : Medium
 * ============================================================================
 *
 *  LC 340  — Longest Substring with At Most K Distinct Characters
 *            https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
 *  LC 159  — Longest Substring with At Most Two Distinct Characters
 *            https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
 *  LC 904  — Fruit Into Baskets (= at most 2 distinct)
 *            https://leetcode.com/problems/fruit-into-baskets/
 *  LC 1695 — Maximum Erasure Value (= longest subarray with all distinct)
 *            https://leetcode.com/problems/maximum-erasure-value/
 *  LC 2958 — Length of Longest Subarray With at Most K Frequency
 *            https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/
 *  GFG     — Longest K Unique Characters Substring
 *            https://practice.geeksforgeeks.org/problems/longest-k-unique-characters-substring/
 *
 *  TEMPLATE: At Most K Distinct
 *  ────────────────────────────
 *  int left = 0, best = 0;
 *  unordered_map<T, int> freq;
 *  for (int right = 0; right < N; right++) {
 *      freq[arr[right]]++;
 *      while (freq.size() > K) {
 *          freq[arr[left]]--;
 *          if (freq[arr[left]] == 0) freq.erase(arr[left]);
 *          left++;
 *      }
 *      best = max(best, right - left + 1);
 *  }
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 340: Longest Substring with At Most K Distinct
// ============================================================================
int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> freq;
    int left = 0, best = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[s[right]]++;

        while ((int)freq.size() > k) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) freq.erase(s[left]);
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 904: Fruit Into Baskets (= longest subarray with at most 2 distinct)
// ============================================================================
int totalFruit(vector<int>& fruits) {
    unordered_map<int, int> freq;
    int left = 0, best = 0;

    for (int right = 0; right < (int)fruits.size(); right++) {
        freq[fruits[right]]++;
        while ((int)freq.size() > 2) {
            freq[fruits[left]]--;
            if (freq[fruits[left]] == 0) freq.erase(fruits[left]);
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 1695: Maximum Erasure Value (longest subarray with all distinct, max sum)
// ============================================================================
int maximumUniqueSubarray(vector<int>& nums) {
    unordered_map<int, int> freq;
    int left = 0, sum = 0, best = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        sum += nums[right];
        freq[nums[right]]++;

        while (freq[nums[right]] > 1) {
            sum -= nums[left];
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
        best = max(best, sum);
    }
    return best;
}

// ============================================================================
// LC 2958: Length of Longest Subarray With at Most K Frequency
// ============================================================================
int maxSubarrayLength(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int left = 0, best = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        freq[nums[right]]++;
        while (freq[nums[right]] > k) {
            freq[nums[left]]--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

int main() {
    // At Most K Distinct
    cout << "AtMostK (eceba, K=2): " << lengthOfLongestSubstringKDistinct("eceba", 2) << "\n"; // 3

    // Fruit Into Baskets
    vector<int> fruits = {1, 2, 1};
    cout << "Fruits: " << totalFruit(fruits) << "\n"; // 3

    // Max Erasure Value
    vector<int> nums = {4, 2, 4, 5, 6};
    cout << "Max Erasure: " << maximumUniqueSubarray(nums) << "\n"; // 17

    return 0;
}

