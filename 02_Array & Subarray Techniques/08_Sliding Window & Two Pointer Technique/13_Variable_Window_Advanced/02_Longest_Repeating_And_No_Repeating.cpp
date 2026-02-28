/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Longest Repeating Character Replacement & Longest Without Repeating
 *  Level   : Medium
 * ============================================================================
 *
 *  LC 424  — Longest Repeating Character Replacement
 *            https://leetcode.com/problems/longest-repeating-character-replacement/
 *  LC 3    — Longest Substring Without Repeating Characters
 *            https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *  LC 395  — Longest Substring with At Least K Repeating Characters
 *            https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 *
 * ============================================================================
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// ============================================================================
// LC 424: Longest Repeating Character Replacement
// ============================================================================
/*
 * PROBLEM: Replace at most K characters to make longest uniform substring.
 *
 * KEY INSIGHT: Window is valid when:
 *   windowLength - maxFreqInWindow ≤ K
 *   (i.e., the number of characters we need to replace ≤ K)
 *
 * We DON'T need to decrease maxFreq when shrinking!
 * Why? If maxFreq decreases, the window only gets smaller, so we
 * won't find a better answer. We only care about when maxFreq increases.
 *
 * Time: O(N), Space: O(26) = O(1)
 */
int characterReplacement(string s, int k) {
    int freq[26] = {};
    int left = 0, maxFreq = 0, best = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[s[right] - 'A']++;
        maxFreq = max(maxFreq, freq[s[right] - 'A']);

        // Window invalid: need to replace more than K chars
        while ((right - left + 1) - maxFreq > k) {
            freq[s[left] - 'A']--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 3: Longest Substring Without Repeating Characters
// ============================================================================
/*
 * PROBLEM: Find longest substring with all unique characters.
 *
 * Variable window: expand right, if duplicate found, shrink left past the
 * previous occurrence.
 *
 * Two approaches:
 * 1. Set-based: maintain set of chars in window. On duplicate, remove from left.
 * 2. Map-based: store last index of each char. On duplicate, jump left.
 *
 * Time: O(N), Space: O(min(N, alphabet_size))
 */

// Approach 1: Using unordered_set
int lengthOfLongestSubstring_set(string s) {
    unordered_set<char> window;
    int left = 0, best = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        while (window.count(s[right])) {
            window.erase(s[left]);
            left++;
        }
        window.insert(s[right]);
        best = max(best, right - left + 1);
    }
    return best;
}

// Approach 2: Using map (last index) — slightly faster
int lengthOfLongestSubstring_map(string s) {
    unordered_map<char, int> lastIdx;
    int left = 0, best = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        if (lastIdx.count(s[right]) && lastIdx[s[right]] >= left) {
            left = lastIdx[s[right]] + 1;
        }
        lastIdx[s[right]] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 395: Longest Substring with At Least K Repeating Characters
// ============================================================================
/*
 * PROBLEM: Find longest substring where every character appears ≥ K times.
 *
 * APPROACH: Divide and Conquer
 * Find a character with freq < K. It can't be in ANY valid substring.
 * Split string at that character and recurse on each part.
 *
 * Alternative: For each possible number of unique chars (1..26), use
 * sliding window to find longest valid substring.
 *
 * Time: O(26 * N) = O(N), Space: O(N)
 */

// Divide and Conquer approach
int longestSubstring_dc(const string& s, int k, int start, int end) {
    if (end - start < k) return 0;

    int freq[26] = {};
    for (int i = start; i < end; i++) freq[s[i] - 'a']++;

    for (int i = start; i < end; i++) {
        if (freq[s[i] - 'a'] < k) {
            // Split at this character
            int j = i + 1;
            while (j < end && freq[s[j] - 'a'] < k) j++;
            return max(longestSubstring_dc(s, k, start, i),
                       longestSubstring_dc(s, k, j, end));
        }
    }
    return end - start; // All chars have freq ≥ k
}

int longestSubstring(string s, int k) {
    return longestSubstring_dc(s, k, 0, s.size());
}

// Sliding window approach (enumerate # of unique chars)
int longestSubstring_sw(string s, int k) {
    int n = s.size(), best = 0;

    for (int maxUnique = 1; maxUnique <= 26; maxUnique++) {
        int freq[26] = {};
        int left = 0, uniqueCount = 0, validCount = 0;

        for (int right = 0; right < n; right++) {
            int idx = s[right] - 'a';
            if (freq[idx] == 0) uniqueCount++;
            freq[idx]++;
            if (freq[idx] == k) validCount++;

            while (uniqueCount > maxUnique) {
                int lidx = s[left] - 'a';
                if (freq[lidx] == k) validCount--;
                freq[lidx]--;
                if (freq[lidx] == 0) uniqueCount--;
                left++;
            }

            if (uniqueCount == maxUnique && validCount == maxUnique)
                best = max(best, right - left + 1);
        }
    }
    return best;
}

int main() {
    // LC 424
    cout << "Replacement (AABABBA, K=1): " << characterReplacement("AABABBA", 1) << "\n"; // 4

    // LC 3
    cout << "No repeat (abcabcbb): " << lengthOfLongestSubstring_set("abcabcbb") << "\n"; // 3
    cout << "No repeat (pwwkew): " << lengthOfLongestSubstring_map("pwwkew") << "\n"; // 3

    // LC 395
    cout << "At least K (aaabb, K=3): " << longestSubstring("aaabb", 3) << "\n"; // 3
    cout << "At least K (ababbc, K=2): " << longestSubstring_sw("ababbc", 2) << "\n"; // 5

    return 0;
}

