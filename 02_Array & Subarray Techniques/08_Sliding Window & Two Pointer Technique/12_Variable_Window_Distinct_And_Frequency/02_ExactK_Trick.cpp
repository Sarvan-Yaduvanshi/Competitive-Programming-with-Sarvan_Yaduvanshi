/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : The Exact K Trick — Most Important Sliding Window Pattern!
 *  Level   : Medium → Hard
 * ============================================================================
 *
 *  🔥 THE EXACT K TRICK:
 *  ─────────────────────
 *  exactlyK(K) = atMostK(K) − atMostK(K − 1)
 *
 *  WHY? atMostK(K) counts subarrays with 0, 1, 2, ..., K distinct elements.
 *       atMostK(K-1) counts subarrays with 0, 1, 2, ..., K-1 distinct elements.
 *       Subtracting gives ONLY subarrays with exactly K distinct elements.
 *
 *  PROBLEMS:
 *  LC 992  — Subarrays with K Different Integers
 *            https://leetcode.com/problems/subarrays-with-k-different-integers/
 *  LC 930  — Binary Subarrays With Sum
 *            https://leetcode.com/problems/binary-subarrays-with-sum/
 *  LC 1248 — Count Number of Nice Subarrays (exactly K odds)
 *            https://leetcode.com/problems/count-number-of-nice-subarrays/
 *  LC 1358 — Number of Substrings Containing All Three Characters
 *            https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
 *  LC 2962 — Count Subarrays Where Max Element Appears at Least K Times
 *            https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ============================================================================
// Helper: Count subarrays with at most K distinct integers
// ============================================================================
int atMostKDistinct(vector<int>& nums, int k) {
    if (k == 0) return 0;
    unordered_map<int, int> freq;
    int left = 0, count = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        freq[nums[right]]++;
        while ((int)freq.size() > k) {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
        count += (right - left + 1); // All subarrays ending at right with ≤ K distinct
    }
    return count;
}

// ============================================================================
// LC 992: Subarrays with K Different Integers — EXACT K TRICK
// ============================================================================
int subarraysWithKDistinct(vector<int>& nums, int k) {
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}

// ============================================================================
// Helper: Count subarrays with sum at most goal (binary array)
// ============================================================================
int atMostSum(vector<int>& nums, int goal) {
    if (goal < 0) return 0;
    int left = 0, sum = 0, count = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        sum += nums[right];
        while (sum > goal) {
            sum -= nums[left];
            left++;
        }
        count += (right - left + 1);
    }
    return count;
}

// ============================================================================
// LC 930: Binary Subarrays With Sum — EXACT K TRICK on sum
// ============================================================================
int numSubarraysWithSum(vector<int>& nums, int goal) {
    return atMostSum(nums, goal) - atMostSum(nums, goal - 1);
}

// ============================================================================
// LC 1248: Count Number of Nice Subarrays — Exactly K odd numbers
// ============================================================================
/*
 * TRICK: Replace each element with 1 if odd, 0 if even.
 * Then "exactly K odds" = "subarray sum exactly K" = atMost(K) - atMost(K-1)
 */
int numberOfSubarrays(vector<int>& nums, int k) {
    // Convert: 1 if odd, 0 if even
    vector<int> binary(nums.size());
    for (int i = 0; i < (int)nums.size(); i++)
        binary[i] = nums[i] % 2;
    return atMostSum(binary, k) - atMostSum(binary, k - 1);
}

// ============================================================================
// LC 1358: Number of Substrings Containing All Three Characters (a, b, c)
// ============================================================================
/*
 * Variable window: shrink while window contains all 3 chars.
 * When condition met, ALL extensions to the right also work.
 * count += left (or equivalently, count += n - right for each valid left).
 */
int numberOfSubstrings(string s) {
    int freq[3] = {};
    int left = 0, count = 0;
    int n = s.size();

    for (int right = 0; right < n; right++) {
        freq[s[right] - 'a']++;
        while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {
            count += (n - right); // All extensions to the right are valid
            freq[s[left] - 'a']--;
            left++;
        }
    }
    return count;
}

// ============================================================================
// LC 2962: Count Subarrays Where Max Appears at Least K Times
// ============================================================================
long long countSubarrays(vector<int>& nums, int k) {
    int maxVal = *max_element(nums.begin(), nums.end());
    int left = 0, maxCount = 0;
    long long count = 0;
    int n = nums.size();

    for (int right = 0; right < n; right++) {
        if (nums[right] == maxVal) maxCount++;
        while (maxCount >= k) {
            count += (n - right); // All extensions to the right are valid
            if (nums[left] == maxVal) maxCount--;
            left++;
        }
    }
    return count;
}

int main() {
    // LC 992: Subarrays with K Different
    vector<int> nums1 = {1, 2, 1, 2, 3};
    cout << "Subarrays K=2 distinct: " << subarraysWithKDistinct(nums1, 2) << "\n"; // 7

    // LC 930: Binary Subarrays with Sum
    vector<int> nums2 = {1, 0, 1, 0, 1};
    cout << "Binary sum=2: " << numSubarraysWithSum(nums2, 2) << "\n"; // 4

    // LC 1248: Nice Subarrays
    vector<int> nums3 = {1, 1, 2, 1, 1};
    cout << "Nice (k=3): " << numberOfSubarrays(nums3, 3) << "\n"; // 2

    // LC 1358: Substrings with a, b, c
    cout << "All 3 chars (abcabc): " << numberOfSubstrings("abcabc") << "\n"; // 10

    return 0;
}

