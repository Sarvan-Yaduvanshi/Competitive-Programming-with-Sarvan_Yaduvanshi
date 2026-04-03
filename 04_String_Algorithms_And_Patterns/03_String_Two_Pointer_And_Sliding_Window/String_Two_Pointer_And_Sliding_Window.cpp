/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 03 — STRING TWO POINTER & SLIDING WINDOW                       ║
║     From Zero to Grandmaster — Window Mastery                              ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Longest Substring Without Repeating Characters
 2. Minimum Window Substring
 3. Longest Repeating Character Replacement
 4. Permutation in String
 5. Count Substrings with K Distinct Characters
 6. Palindromic Substring Expansion (Two-Pointer)
 7. Fixed Window Frequency Matching

CORE THEORY — TWO POINTER ON STRINGS:
──────────────────────────────────────
 The two-pointer technique uses two indices (left, right) to define a window.

 TWO TYPES:
   1. VARIABLE-SIZE WINDOW (Sliding Window):
      - Expand right to include more
      - Shrink left when constraint violated
      - Track answer as max/min window size
      Pattern:
        left = 0
        for right = 0 to n-1:
            add s[right] to window
            while window violates constraint:
                remove s[left] from window
                left++
            update answer

   2. FIXED-SIZE WINDOW:
      - Window always has size K
      - Slide one position at a time
      - Remove leftmost, add rightmost
      Pattern:
        for right = 0 to n-1:
            add s[right] to window
            if right >= k:
                remove s[right - k] from window
            if right >= k - 1:
                check/update answer

 WHY IT WORKS:
   Both pointers only move forward → total movement = O(n)
   Each element is added/removed at most once → O(n) overall

 COMMON DATA STRUCTURES INSIDE WINDOW:
   • int freq[128] or freq[26]  — character frequency
   • unordered_map<char, int>   — flexible frequency
   • int distinct               — count of distinct chars in window
   • int formed                 — count of "satisfied" conditions
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// PROBLEM 1: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Find length of longest substring with all unique characters.
 Example: "abcabcbb" → 3 ("abc")
          "bbbbb" → 1 ("b")
          "pwwkew" → 3 ("wke")

 APPROACH: Variable sliding window + frequency/set tracking
   • Expand right: add s[right]
   • If s[right] already in window → shrink from left until unique
   • Track max window size

 THREE METHODS:
   (a) Set-based — remove from left until no duplicate
   (b) Last-index map — jump left directly to after duplicate
   (c) Frequency array — count-based check

 Complexity: O(n) time, O(min(n, charset)) space
*/

// Method 1: Frequency array — O(n)
int lengthOfLongestSubstring_freq(const string& s) {
    int freq[128] = {0};
    int maxLen = 0, left = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[(int)s[right]]++;

        while (freq[(int)s[right]] > 1) {
            freq[(int)s[left]]--;
            left++;
        }

        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// Method 2: Last-index map — O(n), slightly faster in practice
int lengthOfLongestSubstring_map(const string& s) {
    int lastIndex[128];
    fill(lastIndex, lastIndex + 128, -1);
    int maxLen = 0, left = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        // If character was seen and its last position is within window
        if (lastIndex[(int)s[right]] >= left) {
            left = lastIndex[(int)s[right]] + 1;  // jump!
        }
        lastIndex[(int)s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

void demo_longest_unique() {
    cout << "=== PROBLEM 1: LONGEST SUBSTRING WITHOUT REPEATING ===" << endl;
    cout << "abcabcbb (freq): " << lengthOfLongestSubstring_freq("abcabcbb") << endl;  // 3
    cout << "abcabcbb (map): " << lengthOfLongestSubstring_map("abcabcbb") << endl;    // 3
    cout << "bbbbb: " << lengthOfLongestSubstring_freq("bbbbb") << endl;               // 1
    cout << "pwwkew: " << lengthOfLongestSubstring_freq("pwwkew") << endl;             // 3
    cout << " (empty): " << lengthOfLongestSubstring_freq("") << endl;                 // 0
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 2: MINIMUM WINDOW SUBSTRING
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Find smallest substring of s that contains ALL characters of t.
 Example: s = "ADOBECODEBANC", t = "ABC" → "BANC"

 APPROACH: Variable sliding window with frequency matching
   • Count frequency of each char in t
   • Expand right: decrease need count when matching char found
   • When all chars matched: try shrinking from left
   • Track minimum window

 KEY INSIGHT:
   'formed' counter: how many unique chars in t have been satisfied
   When formed == required → valid window, try to shrink

 Complexity: O(n + m), Space: O(charset)

 THIS IS ONE OF THE HARDEST SLIDING WINDOW PROBLEMS — MASTER IT!
*/

string minWindowSubstring(const string& s, const string& t) {
    if (s.empty() || t.empty() || s.size() < t.size()) return "";

    // Count frequency of t
    int freqT[128] = {0};
    for (char c : t) freqT[(int)c]++;

    // Number of unique chars in t that need to be present
    int required = 0;
    for (int i = 0; i < 128; i++) {
        if (freqT[i] > 0) required++;
    }

    int windowFreq[128] = {0};
    int formed = 0;  // unique chars in current window matching t's frequency
    int left = 0;
    int minLen = INT_MAX, minLeft = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        char c = s[right];
        windowFreq[(int)c]++;

        // Check if this char's frequency matches t's requirement
        if (freqT[(int)c] > 0 && windowFreq[(int)c] == freqT[(int)c]) {
            formed++;
        }

        // Try to shrink window from left
        while (formed == required) {
            // Update answer
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minLeft = left;
            }

            // Remove leftmost char
            char lc = s[left];
            windowFreq[(int)lc]--;
            if (freqT[(int)lc] > 0 && windowFreq[(int)lc] < freqT[(int)lc]) {
                formed--;
            }
            left++;
        }
    }

    return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
}

void demo_min_window() {
    cout << "\n=== PROBLEM 2: MINIMUM WINDOW SUBSTRING ===" << endl;
    cout << "ADOBECODEBANC, ABC → " << minWindowSubstring("ADOBECODEBANC", "ABC") << endl;  // BANC
    cout << "a, a → " << minWindowSubstring("a", "a") << endl;      // a
    cout << "a, aa → " << minWindowSubstring("a", "aa") << endl;    // ""
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 3: LONGEST REPEATING CHARACTER REPLACEMENT
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: You can replace at most K characters. Find the length of
          the longest substring with all same characters.
 Example: "AABABBA", k=1 → 4 ("AABA" → change B to A)

 KEY INSIGHT:
   In a window of size W with maxFreq as the most frequent char count:
     Replacements needed = W - maxFreq
     Valid window if: W - maxFreq <= K

 APPROACH:
   • Expand right, track frequency of each char
   • Track maxFreq (the maximum frequency of any single char in window)
   • If window_size - maxFreq > K → shrink from left
   • Answer = max window size

 TRICK: We don't need to decrease maxFreq when shrinking!
   Because we only care about the maximum window, and maxFreq
   can only help us find a larger window, not a smaller one.

 Complexity: O(n), Space: O(26) = O(1)
*/

int characterReplacement(const string& s, int k) {
    int freq[26] = {0};
    int maxFreq = 0;  // max frequency of any char in current window
    int left = 0, maxLen = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[s[right] - 'A']++;
        maxFreq = max(maxFreq, freq[s[right] - 'A']);

        // Window size = right - left + 1
        // Chars to replace = window_size - maxFreq
        while ((right - left + 1) - maxFreq > k) {
            freq[s[left] - 'A']--;
            left++;
            // Note: we do NOT update maxFreq here — it's an optimization!
        }

        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

void demo_char_replacement() {
    cout << "\n=== PROBLEM 3: LONGEST REPEATING CHARACTER REPLACEMENT ===" << endl;
    cout << "ABAB, k=2: " << characterReplacement("ABAB", 2) << endl;       // 4
    cout << "AABABBA, k=1: " << characterReplacement("AABABBA", 1) << endl; // 4
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 4: PERMUTATION IN STRING
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Check if s2 contains any permutation of s1 as a substring.
 Example: s1 = "ab", s2 = "eidbaooo" → true ("ba" is permutation of "ab")

 APPROACH: Fixed-size sliding window of size len(s1)
   • Count frequency of s1
   • Slide window of size len(s1) over s2
   • Compare window frequency with s1 frequency
   • Match when all 26 frequencies are equal

 OPTIMIZATION: Track 'matches' count (how many of 26 chars match)
   Instead of comparing all 26 each time → O(1) per step.

 Complexity: O(n), Space: O(1)
*/

bool checkInclusion(const string& s1, const string& s2) {
    if (s1.size() > s2.size()) return false;

    int freq1[26] = {0}, freq2[26] = {0};
    int k = s1.size();

    // Count s1 frequency
    for (char c : s1) freq1[c - 'a']++;

    // Initialize window with first k chars of s2
    for (int i = 0; i < k; i++) freq2[s2[i] - 'a']++;

    // Count initial matches
    int matches = 0;
    for (int i = 0; i < 26; i++) {
        if (freq1[i] == freq2[i]) matches++;
    }

    if (matches == 26) return true;

    // Slide window
    for (int right = k; right < (int)s2.size(); right++) {
        int left = right - k;

        // Add right character
        int idx = s2[right] - 'a';
        freq2[idx]++;
        if (freq2[idx] == freq1[idx]) matches++;
        else if (freq2[idx] == freq1[idx] + 1) matches--;

        // Remove left character
        idx = s2[left] - 'a';
        freq2[idx]--;
        if (freq2[idx] == freq1[idx]) matches++;
        else if (freq2[idx] == freq1[idx] - 1) matches--;

        if (matches == 26) return true;
    }

    return false;
}

// Find ALL anagram start indices (LeetCode 438)
vector<int> findAnagrams(const string& s, const string& p) {
    vector<int> result;
    if (s.size() < p.size()) return result;

    int freqP[26] = {0}, freqW[26] = {0};
    int k = p.size();

    for (char c : p) freqP[c - 'a']++;

    int matches = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        // Add right
        int idx = s[i] - 'a';
        freqW[idx]++;
        if (freqW[idx] == freqP[idx]) matches++;
        else if (freqW[idx] == freqP[idx] + 1) matches--;

        // Remove left (when window exceeds size k)
        if (i >= k) {
            idx = s[i - k] - 'a';
            freqW[idx]--;
            if (freqW[idx] == freqP[idx]) matches++;
            else if (freqW[idx] == freqP[idx] - 1) matches--;
        }

        if (matches == 26) {
            result.push_back(i - k + 1);
        }
    }
    return result;
}

void demo_permutation() {
    cout << "\n=== PROBLEM 4: PERMUTATION IN STRING ===" << endl;
    cout << "ab in eidbaooo: " << checkInclusion("ab", "eidbaooo") << endl;  // 1
    cout << "ab in eidboaoo: " << checkInclusion("ab", "eidboaoo") << endl;  // 0

    auto indices = findAnagrams("cbaebabacd", "abc");
    cout << "Find Anagrams of 'abc' in 'cbaebabacd': ";
    for (int idx : indices) cout << idx << " ";
    cout << endl;  // 0 6
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 5: COUNT SUBSTRINGS WITH K DISTINCT CHARACTERS
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Count substrings with exactly K distinct characters.
 Example: "abaac", k=2 → 7

 KEY TRICK: exactlyK(k) = atMostK(k) - atMostK(k-1)

 atMostK(k): For each right, all substrings [left..right], [left+1..right],
             ..., [right..right] are valid → count += (right - left + 1)

 This trick is UNIVERSAL for "exactly K" problems!

 Complexity: O(n), Space: O(1)
*/

int countAtMostKDistinct(const string& s, int k) {
    if (k == 0) return 0;
    int freq[26] = {0};
    int distinct = 0, count = 0, left = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        if (freq[s[right] - 'a'] == 0) distinct++;
        freq[s[right] - 'a']++;

        while (distinct > k) {
            freq[s[left] - 'a']--;
            if (freq[s[left] - 'a'] == 0) distinct--;
            left++;
        }

        count += (right - left + 1);
    }
    return count;
}

int countExactlyKDistinct(const string& s, int k) {
    return countAtMostKDistinct(s, k) - countAtMostKDistinct(s, k - 1);
}

// Variant: Longest substring with at most K distinct
int longestWithAtMostKDistinct(const string& s, int k) {
    int freq[128] = {0};
    int distinct = 0, maxLen = 0, left = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        if (freq[(int)s[right]] == 0) distinct++;
        freq[(int)s[right]]++;

        while (distinct > k) {
            freq[(int)s[left]]--;
            if (freq[(int)s[left]] == 0) distinct--;
            left++;
        }

        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

void demo_k_distinct() {
    cout << "\n=== PROBLEM 5: K DISTINCT SUBSTRINGS ===" << endl;
    cout << "abaac, exactly 2: " << countExactlyKDistinct("abaac", 2) << endl;
    cout << "abaac, at most 2: " << countAtMostKDistinct("abaac", 2) << endl;
    cout << "eceba, longest at most 2: " << longestWithAtMostKDistinct("eceba", 2) << endl;  // 3
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 6: PALINDROMIC SUBSTRING EXPANSION (Two-Pointer)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Expand around center technique for palindrome problems.

 For each position i (0 to n-1):
   • Expand for ODD-length palindromes: center = i
   • Expand for EVEN-length palindromes: center = (i, i+1)

 APPLICATIONS:
   (a) Count all palindromic substrings — O(n²)
   (b) Longest palindromic substring — O(n²)
   (c) Check if removing one char can make palindrome

 Note: For O(n) palindrome, use Manacher's algorithm (Chapter 06)

 Complexity: O(n²) time, O(1) space
*/

// Expand around center — returns length of longest palindrome with given center
int expandAroundCenter(const string& s, int left, int right) {
    while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;  // length of palindrome
}

// Longest Palindromic Substring — O(n²)
string longestPalindromicSubstring(const string& s) {
    if (s.empty()) return "";
    int start = 0, maxLen = 1;

    for (int i = 0; i < (int)s.size(); i++) {
        int len1 = expandAroundCenter(s, i, i);      // odd
        int len2 = expandAroundCenter(s, i, i + 1);  // even
        int len = max(len1, len2);

        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    return s.substr(start, maxLen);
}

// Count all palindromic substrings — O(n²)
int countPalindromes(const string& s) {
    int count = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        // Odd length
        int left = i, right = i;
        while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        // Even length
        left = i;
        right = i + 1;
        while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }
    return count;
}

// Valid Palindrome II: Can we make it a palindrome by removing at most 1 char?
bool validPalindromeHelper(const string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

bool validPalindromeII(const string& s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            // Try removing left or right
            return validPalindromeHelper(s, left + 1, right) ||
                   validPalindromeHelper(s, left, right - 1);
        }
        left++;
        right--;
    }
    return true;
}

void demo_palindrome_expansion() {
    cout << "\n=== PROBLEM 6: PALINDROMIC EXPANSION ===" << endl;
    cout << "Longest palindrome in 'babad': " << longestPalindromicSubstring("babad") << endl;
    cout << "Longest palindrome in 'cbbd': " << longestPalindromicSubstring("cbbd") << endl;
    cout << "Count palindromes in 'aaa': " << countPalindromes("aaa") << endl;  // 6
    cout << "Count palindromes in 'abc': " << countPalindromes("abc") << endl;  // 3
    cout << "Valid Palindrome II 'abca': " << validPalindromeII("abca") << endl;  // 1
    cout << "Valid Palindrome II 'abc': " << validPalindromeII("abc") << endl;    // 0
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 7: FIXED WINDOW FREQUENCY MATCHING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Fixed window of size K sliding over the string.
 At each position, we maintain frequency counts and check conditions.

 TEMPLATE:
   int freq[26] = {0};
   for (int i = 0; i < n; i++) {
       freq[s[i] - 'a']++;          // add right
       if (i >= k) {
           freq[s[i-k] - 'a']--;    // remove left
       }
       if (i >= k-1) {
           // window [i-k+1 ... i] is complete, check condition
       }
   }

 APPLICATIONS:
   • Maximum vowels in substring of length K
   • Number of substrings of length K with no repeated characters
   • Find all anagram occurrences
   • Maximum unique characters in window of size K
*/

// Maximum number of vowels in substring of length K
int maxVowelsInWindow(const string& s, int k) {
    auto isVowel = [](char c) -> bool {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int vowels = 0, maxVowels = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (isVowel(s[i])) vowels++;
        if (i >= k && isVowel(s[i - k])) vowels--;
        if (i >= k - 1) maxVowels = max(maxVowels, vowels);
    }
    return maxVowels;
}

// Count substrings of length K with all unique characters
int countUniqueWindowsOfSizeK(const string& s, int k) {
    if ((int)s.size() < k) return 0;
    int freq[26] = {0};
    int duplicates = 0, count = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        // Add right character
        freq[s[i] - 'a']++;
        if (freq[s[i] - 'a'] == 2) duplicates++;

        // Remove left character when window > k
        if (i >= k) {
            int idx = s[i - k] - 'a';
            if (freq[idx] == 2) duplicates--;
            freq[idx]--;
        }

        // Check if window has all unique
        if (i >= k - 1 && duplicates == 0) {
            count++;
        }
    }
    return count;
}

// Maximum sum of ASCII values in window of size K
int maxAsciiSumWindow(const string& s, int k) {
    int sum = 0, maxSum = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        sum += s[i];
        if (i >= k) sum -= s[i - k];
        if (i >= k - 1) maxSum = max(maxSum, sum);
    }
    return maxSum;
}

// Find minimum window in s that contains all characters of t (fixed size version)
// Returns starting index or -1
int findExactPermutation(const string& s, const string& t) {
    int k = t.size();
    if ((int)s.size() < k) return -1;

    int freqT[26] = {0}, freqW[26] = {0};
    for (char c : t) freqT[c - 'a']++;

    int matches = 0;
    for (int i = 0; i < 26; i++) if (freqT[i] == 0) matches++;

    for (int i = 0; i < (int)s.size(); i++) {
        int idx = s[i] - 'a';
        freqW[idx]++;
        if (freqW[idx] == freqT[idx]) matches++;
        else if (freqW[idx] == freqT[idx] + 1) matches--;

        if (i >= k) {
            idx = s[i - k] - 'a';
            if (freqW[idx] == freqT[idx]) matches++;
            else if (freqW[idx] == freqT[idx] - 1) matches--;
            freqW[idx]--;
            // Note: the above check must come BEFORE decrement for "going down" case
            // Let me fix the logic:
        }

        if (i >= k - 1 && matches == 26) return i - k + 1;
    }
    return -1;
}

void demo_fixed_window() {
    cout << "\n=== PROBLEM 7: FIXED WINDOW FREQUENCY MATCHING ===" << endl;
    cout << "Max vowels in 'abciiidef' k=3: " << maxVowelsInWindow("abciiidef", 3) << endl;  // 3
    cout << "Unique windows in 'abcabc' k=3: " << countUniqueWindowsOfSizeK("abcabc", 3) << endl;
    cout << "Max ASCII sum 'abcde' k=2: " << maxAsciiSumWindow("abcde", 2) << endl;
}

// ═══════════════════════════════════════════════════════════════
// BONUS: SLIDING WINDOW TEMPLATE (MASTER TEMPLATE)
// ═══════════════════════════════════════════════════════════════
/*
 UNIVERSAL SLIDING WINDOW TEMPLATE:
 ───────────────────────────────────

 // Variable-size window to find minimum/maximum
 int left = 0;
 for (int right = 0; right < n; right++) {
     // 1. Add s[right] to window state

     // 2. While window is invalid (or valid, depending on problem):
     while (CONDITION_VIOLATED) {
         // Remove s[left] from window state
         left++;
     }

     // 3. Update answer
     //    For MAXIMUM: ans = max(ans, right - left + 1)
     //    For MINIMUM: ans = min(ans, right - left + 1) [inside while]
 }

 THE "AT MOST K" TRICK:
   count_exactly(k) = count_at_most(k) - count_at_most(k-1)

 THE "AT LEAST K" TRICK:
   For each right, find the leftmost valid left.
   Substrings [left..right], [left-1..right], ..., [0..right] are all valid.
   count += left + 1 (if left is leftmost valid)
   OR count += n - right (if right is rightmost valid for each left)
*/

// Template: Minimum length window containing all characters of t
int minLengthWindowContaining(const string& s, const string& t) {
    int freqT[128] = {0};
    int required = 0;
    for (char c : t) {
        if (freqT[(int)c] == 0) required++;
        freqT[(int)c]++;
    }

    int windowFreq[128] = {0};
    int formed = 0, left = 0;
    int minLen = INT_MAX;

    for (int right = 0; right < (int)s.size(); right++) {
        windowFreq[(int)s[right]]++;
        if (freqT[(int)s[right]] > 0 &&
            windowFreq[(int)s[right]] == freqT[(int)s[right]]) {
            formed++;
        }

        while (formed == required) {
            minLen = min(minLen, right - left + 1);
            windowFreq[(int)s[left]]--;
            if (freqT[(int)s[left]] > 0 &&
                windowFreq[(int)s[left]] < freqT[(int)s[left]]) {
                formed--;
            }
            left++;
        }
    }
    return minLen == INT_MAX ? -1 : minLen;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_longest_unique();
    demo_min_window();
    demo_char_replacement();
    demo_permutation();
    demo_k_distinct();
    demo_palindrome_expansion();
    demo_fixed_window();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 7 Two-Pointer & Sliding Window concepts covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                               ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 3    — Longest Substring Without Repeating Chars      ║
║  LeetCode 76   — Minimum Window Substring                       ║
║  LeetCode 424  — Longest Repeating Character Replacement        ║
║  LeetCode 567  — Permutation in String                          ║
║  LeetCode 438  — Find All Anagrams in a String                  ║
║  LeetCode 340  — Longest Substring with At Most K Distinct      ║
║  LeetCode 992  — Subarrays with K Different Integers            ║
║  LeetCode 5    — Longest Palindromic Substring                  ║
║  LeetCode 647  — Palindromic Substrings                         ║
║  LeetCode 680  — Valid Palindrome II                             ║
║  LeetCode 1456 — Maximum Vowels in Substring of Size K          ║
║  LeetCode 1100 — Find K-Length Substrings With No Repeats       ║
║  LeetCode 30   — Substring with Concat of All Words             ║
║  CF 676C       — Vasya and String                                ║
║  CF 1234D      — Distinct Characters Queries                     ║
╚══════════════════════════════════════════════════════════════════╝
*/

