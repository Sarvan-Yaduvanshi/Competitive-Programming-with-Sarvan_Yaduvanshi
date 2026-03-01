/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 09 — STRING BITMASK & PARITY TECHNIQUES                       ║
║     From Zero to Grandmaster — Bit Tricks for Strings                      ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Parity Mask Trick (Core Concept)
 2. Palindrome Permutation Check
 3. Wonderful Substrings (LeetCode 1915)
 4. XOR Mask Window Technique
 5. Bit Compression for Small Alphabet

CORE THEORY — BITMASK ON STRINGS:
──────────────────────────────────
 For strings with SMALL ALPHABET (e.g., 26 lowercase letters, or 10 first letters),
 we can encode character PARITY (odd/even count) in a single integer bitmask.

 PARITY MASK:
   mask = 0 initially
   For each character c: mask ^= (1 << (c - 'a'))

   Bit i of mask = 1 if character 'a'+i has appeared an ODD number of times
   Bit i of mask = 0 if character 'a'+i has appeared an EVEN number of times

 KEY INSIGHT:
   Two positions have the same parity mask → the substring between them
   has ALL characters with EVEN frequency!

 WHY?
   If mask[l] = mask[r], then mask[l] ^ mask[r] = 0
   → All character frequencies in s[l+1..r] are even
   → This is a condition for palindrome permutation!

 POSSIBLE MASK VALUES:
   For k distinct characters: 2^k possible masks
   For 26 letters: 2^26 ≈ 67 million (feasible with hash map)
   For 10 letters: 2^10 = 1024 (very fast with array)

 APPLICATIONS:
   • Check if substring can be rearranged into palindrome
   • Count substrings where all chars have even frequency
   • Count "wonderful" substrings (at most one odd-frequency char)
   • Longest substring with at most K odd-frequency characters
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
using namespace std;
using i64 = long long;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: PARITY MASK TRICK (Core Concept)
// ═══════════════════════════════════════════════════════════════
/*
 BUILDING PARITY MASK:
   mask = 0
   for each char c in string:
     mask ^= (1 << (c - 'a'))

   After processing: bit i = 1 means char 'a'+i appears odd times

 PREFIX PARITY MASK:
   prefix[0] = 0
   prefix[i] = prefix[i-1] ^ (1 << (s[i-1] - 'a'))

   Parity mask of substring s[l..r] = prefix[r+1] ^ prefix[l]
   = prefix[l] ^ prefix[r+1]  (XOR is its own inverse)

 PALINDROME CONDITION:
   A string can be rearranged into a palindrome iff:
   At most ONE character has odd frequency
   → mask has at most one bit set
   → mask == 0 OR mask is a power of 2 (mask & (mask-1) == 0)
*/

// Build prefix parity mask array
vector<int> buildPrefixMask(const string& s) {
    int n = s.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] ^ (1 << (s[i] - 'a'));
    }
    return prefix;
}

// Check if substring s[l..r] can be rearranged into palindrome
bool canBePalindrome(const vector<int>& prefix, int l, int r) {
    int mask = prefix[r + 1] ^ prefix[l];
    return (mask & (mask - 1)) == 0;  // at most 1 bit set
}

// Get parity mask of entire string
int parityMask(const string& s) {
    int mask = 0;
    for (char c : s) mask ^= (1 << (c - 'a'));
    return mask;
}

// Print mask in binary for visualization
void printMask(int mask, int bits = 10) {
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((mask >> i) & 1);
    }
}

void demo_parity_mask() {
    cout << "=== SECTION 1: PARITY MASK TRICK ===" << endl;

    string s = "aab";
    int mask = parityMask(s);
    cout << "Parity mask of 'aab': ";
    printMask(mask);
    cout << " → bit 1 set (b appears odd times)" << endl;

    s = "aabb";
    mask = parityMask(s);
    cout << "Parity mask of 'aabb': ";
    printMask(mask);
    cout << " → all zero (can rearrange to palindrome)" << endl;

    // Prefix masks
    string t = "abcba";
    auto prefix = buildPrefixMask(t);
    cout << "\nPrefix masks of 'abcba':" << endl;
    for (int i = 0; i <= (int)t.size(); i++) {
        cout << "  prefix[" << i << "] = ";
        printMask(prefix[i]);
        cout << endl;
    }

    // Substring palindrome check
    cout << "Can s[0..4]='abcba' be palindrome? " << canBePalindrome(prefix, 0, 4) << endl;  // 1
    cout << "Can s[0..2]='abc' be palindrome? " << canBePalindrome(prefix, 0, 2) << endl;    // 0
    cout << "Can s[1..3]='bcb' be palindrome? " << canBePalindrome(prefix, 1, 3) << endl;    // 1
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: PALINDROME PERMUTATION CHECK
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Can the string be rearranged to form a palindrome?

 SOLUTION using bitmask:
   mask = parity mask of string
   Can be palindrome iff mask == 0 or mask is power of 2

 EXTENDED: Given string, find all substrings that can be rearranged to palindrome.
   Use prefix masks: for each pair (l, r) where prefix[l] == prefix[r+1]
   or they differ in exactly one bit.

 COUNT ALL PALINDROMIC-PERMUTATION SUBSTRINGS:
   Count pairs (i, j) where prefix[i] ^ prefix[j] has at most 1 bit set.
*/

bool canFormPalindrome(const string& s) {
    int mask = 0;
    for (char c : s) mask ^= (1 << (c - 'a'));
    return (mask & (mask - 1)) == 0;
}

// Count substrings that can be rearranged to palindrome
// For 10 first letters (a-j): O(n * 2^10) with array
i64 countPalindromePermSubstrings(const string& s) {
    int n = s.size();
    auto prefix = buildPrefixMask(s);
    i64 count = 0;

    // Two approaches based on alphabet size:
    // For small alphabet (≤ 20): use array of size 2^20
    // For large alphabet (26): use hash map

    // Approach with hash map (works for any alphabet)
    unordered_map<int, int> freq;
    freq[0] = 1;  // prefix[0] = 0

    for (int i = 1; i <= n; i++) {
        int mask = prefix[i];

        // Case 1: all even frequencies → same mask appeared before
        if (freq.count(mask)) {
            count += freq[mask];
        }

        // Case 2: exactly one odd frequency → differ in exactly one bit
        for (int bit = 0; bit < 26; bit++) {
            int target = mask ^ (1 << bit);
            if (freq.count(target)) {
                count += freq[target];
            }
        }

        freq[mask]++;
    }
    return count;
}

void demo_palindrome_permutation() {
    cout << "\n=== SECTION 2: PALINDROME PERMUTATION ===" << endl;
    cout << "Can 'aab' form palindrome? " << canFormPalindrome("aab") << endl;    // 1 (aba)
    cout << "Can 'abc' form palindrome? " << canFormPalindrome("abc") << endl;    // 0
    cout << "Can 'carerac' form palindrome? " << canFormPalindrome("carerac") << endl;  // 1 (racecar)

    cout << "Count palindrome-perm substrings of 'aab': "
         << countPalindromePermSubstrings("aab") << endl;
    cout << "Count palindrome-perm substrings of 'abcba': "
         << countPalindromePermSubstrings("abcba") << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: WONDERFUL SUBSTRINGS (LeetCode 1915)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM:
 ───────
 A "wonderful" string has AT MOST ONE character with odd frequency.
 Count the number of wonderful substrings.
 Alphabet: first 10 lowercase letters (a-j).

 APPROACH: Parity Mask + Counting
   prefix[i] = XOR of (1 << (s[k] - 'a')) for k in [0, i)

   Substring s[l..r] is wonderful if prefix[l] ^ prefix[r+1] has ≤ 1 bit set.

   This means: prefix[l] == prefix[r+1]                (0 bits differ)
           OR: prefix[l] and prefix[r+1] differ in 1 bit (1 bit differs)

 Count pairs:
   For each prefix[i]:
     count += freq[prefix[i]]           (same mask)
     For each bit b in 0..9:
       count += freq[prefix[i] ^ (1 << b)]  (differ in bit b)

 Since alphabet size = 10, 2^10 = 1024 possible masks → use array!

 Time: O(n * 10), Space: O(1024) = O(1)
*/

i64 wonderfulSubstrings(const string& word) {
    int freq[1024] = {0};  // 2^10 possible masks
    freq[0] = 1;  // empty prefix
    int mask = 0;
    i64 count = 0;

    for (char c : word) {
        mask ^= (1 << (c - 'a'));

        // Same mask (all even)
        count += freq[mask];

        // Differ in exactly one bit (one odd)
        for (int bit = 0; bit < 10; bit++) {
            count += freq[mask ^ (1 << bit)];
        }

        freq[mask]++;
    }
    return count;
}

void demo_wonderful() {
    cout << "\n=== SECTION 3: WONDERFUL SUBSTRINGS ===" << endl;
    cout << "aba: " << wonderfulSubstrings("aba") << endl;      // 4
    cout << "aabb: " << wonderfulSubstrings("aabb") << endl;    // 9
    cout << "he: " << wonderfulSubstrings("he") << endl;        // 2
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: XOR MASK WINDOW TECHNIQUE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Combine parity masks with sliding window / two-pointer techniques.

 PROBLEM 1: Longest substring where at most K characters have odd frequency.
   → Sliding window where popcount(mask) <= K

 PROBLEM 2: Count substrings where EXACTLY K characters have odd frequency.
   → Same prefix mask trick, but count masks that differ in exactly K bits.
   → For small K: enumerate all masks with K bits flipped.

 PROBLEM 3: Longest awesome substring (LeetCode 1542)
   → "Awesome" = can rearrange to palindrome = mask has ≤ 1 bit set
   → Find longest substring with mask == 0 or mask = power of 2
   → Use first-occurrence array for each mask
*/

// Longest substring where mask has at most K bits (K odd-frequency chars)
int longestKOddChars(const string& s, int K) {
    int n = s.size();
    int mask = 0, maxLen = 0;

    // For small K, use "earliest occurrence" approach
    // But for general K, sliding window on popcount doesn't work directly
    // because XOR isn't monotonic.

    // Use prefix mask + hash map of first occurrence
    unordered_map<int, int> firstOccurrence;
    firstOccurrence[0] = -1;

    for (int i = 0; i < n; i++) {
        mask ^= (1 << (s[i] - 'a'));

        // Try all masks that differ from current mask in at most K bits
        // For K=0: just check same mask
        // For K=1: check 26 neighbors
        // For general K: this becomes exponential → need different approach

        // For K <= 1 (palindrome case):
        if (__builtin_popcount(mask) <= K) {
            maxLen = i + 1;  // from start
        }

        // Check same mask
        if (firstOccurrence.count(mask)) {
            maxLen = max(maxLen, i - firstOccurrence[mask]);
        } else {
            firstOccurrence[mask] = i;
        }

        // Check masks differing in 1 bit
        if (K >= 1) {
            for (int b = 0; b < 26; b++) {
                int target = mask ^ (1 << b);
                if (firstOccurrence.count(target)) {
                    maxLen = max(maxLen, i - firstOccurrence[target]);
                }
            }
        }
    }
    return maxLen;
}

// Longest Awesome Substring (LeetCode 1542)
// Digits 0-9, find longest substring that can be rearranged to palindrome
int longestAwesome(const string& s) {
    int n = s.size();
    vector<int> first(1024, n);  // first occurrence of each mask
    first[0] = -1;
    int mask = 0, maxLen = 0;

    for (int i = 0; i < n; i++) {
        mask ^= (1 << (s[i] - '0'));

        // Same mask → all even frequencies
        if (first[mask] < n) {
            maxLen = max(maxLen, i - first[mask]);
        } else {
            first[mask] = i;
        }

        // Differ in one bit → one odd frequency (still palindrome-able)
        for (int b = 0; b < 10; b++) {
            int target = mask ^ (1 << b);
            if (first[target] < n) {
                maxLen = max(maxLen, i - first[target]);
            }
        }
    }
    return maxLen;
}

void demo_xor_window() {
    cout << "\n=== SECTION 4: XOR MASK WINDOW ===" << endl;
    cout << "Longest awesome '3242415': " << longestAwesome("3242415") << endl;  // 5
    cout << "Longest awesome '12345678': " << longestAwesome("12345678") << endl;  // 1
    cout << "Longest awesome '213123': " << longestAwesome("213123") << endl;    // 6

    cout << "Longest <=1 odd in 'aabaa': " << longestKOddChars("aabaa", 1) << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: BIT COMPRESSION FOR SMALL ALPHABET
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When the alphabet is small, we can pack character sets into integers.

 CHARACTER SET: For each position or window, track which characters appear
   using a bitmask. set |= (1 << (c - 'a'))

 APPLICATIONS:
   1. Count substrings with all distinct characters
      → substring is valid if popcount(charSet) == window length
   2. Check if two strings have common characters
      → (set1 & set2) != 0
   3. Find minimum window containing all K distinct characters
      → popcount(windowSet) == K

 PANGRAM CHECK:
   A string is a pangram if it contains all 26 letters.
   set = 0; for c in s: set |= (1 << (c - 'a'))
   isPangram = (set == (1 << 26) - 1)

 SUBSET OF CHARACTERS:
   "aab" → set = 0b11 (bits for a and b)
   Check if set A ⊆ set B: (A & B) == A
   Check if set A and B are disjoint: (A & B) == 0
   Union: A | B
   Intersection: A & B
*/

// Check if string is a pangram (contains all 26 letters)
bool isPangram(const string& s) {
    int charSet = 0;
    for (char c : s) {
        if (isalpha(c)) {
            charSet |= (1 << (tolower(c) - 'a'));
        }
    }
    return charSet == (1 << 26) - 1;
}

// Count substrings where all characters are distinct
// Using bitmask to track character set
i64 countAllDistinctCharSubstrings(const string& s) {
    int n = s.size();
    i64 count = 0;
    int left = 0;
    int charSet = 0;

    for (int right = 0; right < n; right++) {
        int bit = 1 << (s[right] - 'a');

        // Shrink window if character already in set
        while (charSet & bit) {
            charSet ^= (1 << (s[left] - 'a'));
            left++;
        }
        charSet |= bit;

        // All substrings [left..right], [left+1..right], ..., [right..right]
        // have distinct chars
        count += (right - left + 1);
    }
    return count;
}

// Find if any permutation of pattern exists as substring of text
// Using character set bitmask + frequency match
bool hasPermutation(const string& text, const string& pattern) {
    int m = pattern.size();
    if ((int)text.size() < m) return false;

    // Track character frequencies as bitmask of "satisfied" chars
    int freq[26] = {0};
    for (char c : pattern) freq[c - 'a']++;

    int windowFreq[26] = {0};
    int satisfied = 0;  // bitmask of satisfied characters
    int required = 0;

    // Build required mask
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) required |= (1 << i);
    }

    for (int i = 0; i < (int)text.size(); i++) {
        int idx = text[i] - 'a';
        windowFreq[idx]++;
        if (windowFreq[idx] == freq[idx] && freq[idx] > 0) {
            satisfied |= (1 << idx);
        } else if (windowFreq[idx] > freq[idx]) {
            satisfied &= ~(1 << idx);
        }

        if (i >= m) {
            int lidx = text[i - m] - 'a';
            if (windowFreq[lidx] == freq[lidx] && freq[lidx] > 0) {
                satisfied |= (1 << lidx);
            }
            windowFreq[lidx]--;
            if (windowFreq[lidx] < freq[lidx]) {
                satisfied &= ~(1 << lidx);
            }
        }

        if (satisfied == required && i >= m - 1) return true;
    }
    return false;
}

// Count substrings containing all characters of pattern using bitmask
i64 countSubstringsContainingAll(const string& s, const string& chars) {
    int n = s.size();
    int required = 0;
    for (char c : chars) required |= (1 << (c - 'a'));

    i64 count = 0;
    int left = 0;
    int freq[26] = {0};
    int currentSet = 0;

    for (int right = 0; right < n; right++) {
        int idx = s[right] - 'a';
        freq[idx]++;
        currentSet |= (1 << idx);

        while ((currentSet & required) == required) {
            count += (n - right);  // all extensions to the right are valid
            int lidx = s[left] - 'a';
            freq[lidx]--;
            if (freq[lidx] == 0) currentSet &= ~(1 << lidx);
            left++;
        }
    }
    return count;
}

void demo_bit_compression() {
    cout << "\n=== SECTION 5: BIT COMPRESSION ===" << endl;
    cout << "Is 'The quick brown fox jumps over the lazy dog' pangram? "
         << isPangram("The quick brown fox jumps over the lazy dog") << endl;  // 1
    cout << "Is 'hello world' pangram? " << isPangram("hello world") << endl;  // 0

    cout << "Count all-distinct substrings of 'abcabc': "
         << countAllDistinctCharSubstrings("abcabc") << endl;

    cout << "Has permutation of 'abc' in 'cbadabcx': "
         << hasPermutation("cbadabcx", "abc") << endl;  // 1

    cout << "Substrings of 'abcabc' containing all of 'abc': "
         << countSubstringsContainingAll("abcabc", "abc") << endl;
}

// ═══════════════════════════════════════════════════════════════
// BONUS: MAXIMUM XOR OF SUBSTRING HASHES
// ═══════════════════════════════════════════════════════════════
/*
 Combine string bitmask concepts with XOR operations.

 Problem: Given binary string, find two non-overlapping substrings
          that maximize XOR of their values.
 This bridges bitmask + trie (from Chapter 05) + string techniques.
*/

void demo_bonus() {
    cout << "\n=== BONUS ===" << endl;
    // Example: Count substrings where set of characters is a subset of {a,b,c}
    string s = "abcdeabc";
    int allowed = (1 << 0) | (1 << 1) | (1 << 2);  // a, b, c
    int count = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int charSet = 0;
        for (int j = i; j < (int)s.size(); j++) {
            charSet |= (1 << (s[j] - 'a'));
            if ((charSet & ~allowed) == 0) count++;
            else break;  // once we include a char outside {a,b,c}, all extensions invalid
        }
    }
    cout << "Substrings of 'abcdeabc' using only {a,b,c}: " << count << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_parity_mask();
    demo_palindrome_permutation();
    demo_wonderful();
    demo_xor_window();
    demo_bit_compression();
    demo_bonus();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 5 Bitmask & Parity Techniques covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 266  — Palindrome Permutation                         ║
║  LeetCode 1915 — Number of Wonderful Substrings                 ║
║  LeetCode 1542 — Find Longest Awesome Substring                 ║
║  LeetCode 1371 — Find the Longest Substring Even Vowels         ║
║  LeetCode 1297 — Maximum Number of Occurrences of a Substring   ║
║  LeetCode 1100 — Find K-Length Substrings With No Repeated Chars║
║  LeetCode 1044 — Longest Duplicate Substring (hash + binary)    ║
║  CF 1234D      — Distinct Characters Queries                     ║
║  CF 1352G      — Special Permutation (bitmask)                  ║
║  CF 1418G      — Three Occurrences (bitmask + sliding window)   ║
║  AtCoder ABC242E — (Xor mask counting)                           ║
╚══════════════════════════════════════════════════════════════════╝
*/

