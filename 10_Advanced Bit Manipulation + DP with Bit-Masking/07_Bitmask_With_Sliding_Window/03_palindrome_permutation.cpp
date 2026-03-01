/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07.03 — PALINDROME PERMUTATION                           ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

KEY THEOREM: A string can be rearranged into a palindrome ⟺ at most ONE character
has an odd frequency. In bitmask terms: popcount(parity_mask) ≤ 1.

PROBLEM VARIANTS:
    1. Can string be rearranged to palindrome? → check popcount(mask) ≤ 1
    2. Count substrings that are palindrome permutations → mask[R]==mask[L] or differ by 1 bit
    3. Longest such substring → track first occurrence of each mask

For counting: need mask[R] ⊕ mask[L] has popcount ≤ 1.
    That means mask[R] == mask[L] OR mask[R] differs from mask[L] in exactly 1 bit.
    Check mask itself + all 26 neighbors (flip each bit).

TIME: O(n × |Σ|) for counting variant
LeetCode 266: Palindrome Permutation
LeetCode 1542: Find Longest Awesome Substring
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
using namespace std;

bool canFormPalindrome(const string& s) {
    int mask = 0;
    for (char c : s) mask ^= (1 << (c - 'a'));
    return __builtin_popcount(mask) <= 1;
}

// Count palindrome permutation substrings
long long countPalinPermuSubstrings(const string& s) {
    unordered_map<int, long long> freq;
    freq[0] = 1;
    int mask = 0;
    long long count = 0;
    for (char c : s) {
        mask ^= (1 << (c - 'a'));
        // Exact match (all even)
        count += freq[mask];
        // Differ by 1 bit (at most 1 odd)
        for (int b = 0; b < 26; b++) {
            count += freq[mask ^ (1 << b)];
        }
        freq[mask]++;
    }
    return count;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   PALINDROME PERMUTATION                        ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "\n--- Can Form Palindrome? ---" << endl;
    for (string s : {"racecar", "aabb", "abc", "aab", "a"}) {
        cout << "  \"" << s << "\": " << (canFormPalindrome(s) ? "YES" : "NO") << endl;
    }
    assert(canFormPalindrome("racecar") == true);
    assert(canFormPalindrome("abc") == false);

    cout << "\n--- Count Palindrome Permutation Substrings ---" << endl;
    cout << "  \"aab\": " << countPalinPermuSubstrings("aab") << endl;
    // Substrings: "a"(yes), "a"(yes), "b"(yes), "aa"(yes), "ab"(no), "aab"(yes) = 5

    cout << "\n✅ Palindrome permutation verified!" << endl;
    return 0;
}

