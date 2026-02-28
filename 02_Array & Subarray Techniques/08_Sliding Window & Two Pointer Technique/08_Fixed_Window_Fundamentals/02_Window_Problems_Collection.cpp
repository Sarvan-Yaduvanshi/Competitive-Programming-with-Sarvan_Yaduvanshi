/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : First Negative & Count Distinct in Every Window of Size K
 *  Level   : Easy → Medium
 * ============================================================================
 *
 *  GFG — First Negative in Every Window of Size K
 *        https://practice.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k/
 *
 *  GFG — Count Distinct Elements in Every Window
 *        https://practice.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/
 *
 *  LC 1456 — Max Number of Vowels in Substring of Given Length
 *            https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
 *
 *  LC 1343 — # Subarrays Size K, Avg ≥ Threshold
 *            https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/
 *
 *  LC 2090 — K Radius Subarray Averages
 *            https://leetcode.com/problems/k-radius-subarray-averages/
 *
 *  LC 1052 — Grumpy Bookstore Owner
 *            https://leetcode.com/problems/grumpy-bookstore-owner/
 *
 *  LC 1984 — Min Difference Between Highest and Lowest of K Scores
 *            https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/
 *
 *  LC 2379 — Min Recolors to Get K Black Blocks
 *            https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/
 *
 *  LC 2461 — Max Sum Distinct Subarrays Length K
 *            https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// First Negative in Every Window of Size K — Deque
// ============================================================================
vector<int> firstNegativeInWindow(vector<int>& arr, int k) {
    int n = arr.size();
    deque<int> negIdx;  // Indices of negatives in current window
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) negIdx.push_back(i);

        // Remove elements outside window
        while (!negIdx.empty() && negIdx.front() <= i - k)
            negIdx.pop_front();

        if (i >= k - 1) {
            result.push_back(negIdx.empty() ? 0 : arr[negIdx.front()]);
        }
    }
    return result;
}

// ============================================================================
// Count Distinct in Every Window of Size K — HashMap
// ============================================================================
vector<int> countDistinctInWindow(vector<int>& arr, int k) {
    int n = arr.size();
    unordered_map<int, int> freq;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;

        if (i >= k) {
            freq[arr[i - k]]--;
            if (freq[arr[i - k]] == 0) freq.erase(arr[i - k]);
        }

        if (i >= k - 1) {
            result.push_back(freq.size());
        }
    }
    return result;
}

// ============================================================================
// LC 1456: Max Vowels in Substring of Given Length
// ============================================================================
int maxVowels(string s, int k) {
    auto isVowel = [](char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int count = 0, maxCount = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        count += isVowel(s[i]);
        if (i >= k) count -= isVowel(s[i - k]);
        if (i >= k - 1) maxCount = max(maxCount, count);
    }
    return maxCount;
}

// ============================================================================
// LC 2461: Max Sum of Distinct Subarrays of Length K
// ============================================================================
ll maximumSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> freq;
    ll sum = 0, best = 0;

    for (int i = 0; i < n; i++) {
        sum += nums[i];
        freq[nums[i]]++;

        if (i >= k) {
            sum -= nums[i - k];
            freq[nums[i - k]]--;
            if (freq[nums[i - k]] == 0) freq.erase(nums[i - k]);
        }

        if (i >= k - 1 && (int)freq.size() == k) {
            best = max(best, sum);
        }
    }
    return best;
}

// ============================================================================
// LC 1052: Grumpy Bookstore Owner
// ============================================================================
int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    int n = customers.size();
    int alwaysSatisfied = 0;
    for (int i = 0; i < n; i++)
        if (!grumpy[i]) alwaysSatisfied += customers[i];

    // Fixed window: find window of 'minutes' that saves most grumpy customers
    int windowSave = 0, maxSave = 0;
    for (int i = 0; i < n; i++) {
        if (grumpy[i]) windowSave += customers[i];
        if (i >= minutes && grumpy[i - minutes])
            windowSave -= customers[i - minutes];
        if (i >= minutes - 1) maxSave = max(maxSave, windowSave);
    }
    return alwaysSatisfied + maxSave;
}

int main() {
    // First Negative
    vector<int> arr = {12, -1, -7, 8, -15, 30, 16, 28};
    auto neg = firstNegativeInWindow(arr, 3);
    cout << "First Negatives: ";
    for (int x : neg) cout << x << " ";
    cout << "\n"; // -1 -1 -7 -15 -15 0

    // Count Distinct
    vector<int> arr2 = {1, 2, 1, 3, 4, 2, 3};
    auto dist = countDistinctInWindow(arr2, 4);
    cout << "Distinct counts: ";
    for (int x : dist) cout << x << " ";
    cout << "\n"; // 3 4 4 3

    // Max Vowels
    cout << "Max vowels: " << maxVowels("abciiidef", 3) << "\n"; // 3

    return 0;
}

