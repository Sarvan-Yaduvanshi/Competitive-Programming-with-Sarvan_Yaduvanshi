/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Anagram / Permutation in String — Fixed Window + Frequency
 *  Level   : Medium
 * ============================================================================
 *
 *  LC 567  — Permutation in String
 *            https://leetcode.com/problems/permutation-in-string/
 *  LC 438  — Find All Anagrams in a String
 *            https://leetcode.com/problems/find-all-anagrams-in-a-string/
 *  LC 242  — Valid Anagram
 *            https://leetcode.com/problems/valid-anagram/
 *  LC 187  — Repeated DNA Sequences
 *            https://leetcode.com/problems/repeated-dna-sequences/
 *  LC 1876 — Substrings of Size Three with Distinct Characters
 *            https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/
 *
 *  TECHNIQUE:
 *  ──────────
 *  Fixed window of size len(p). Maintain frequency count of window.
 *  Compare window frequency with pattern frequency.
 *  Use a "matched" counter to avoid comparing full arrays each time.
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// ============================================================================
// LC 567: Permutation in String — Is any permutation of s1 a substring of s2?
// ============================================================================
bool checkInclusion(string s1, string s2) {
    if (s1.size() > s2.size()) return false;

    int freq1[26] = {}, freq2[26] = {};
    int k = s1.size();

    for (char c : s1) freq1[c - 'a']++;
    for (int i = 0; i < k; i++) freq2[s2[i] - 'a']++;

    // Count how many of 26 chars have matching frequency
    int matched = 0;
    for (int i = 0; i < 26; i++)
        if (freq1[i] == freq2[i]) matched++;

    if (matched == 26) return true;

    for (int i = k; i < (int)s2.size(); i++) {
        // Add s2[i]
        int idx = s2[i] - 'a';
        if (freq1[idx] == freq2[idx]) matched--;
        freq2[idx]++;
        if (freq1[idx] == freq2[idx]) matched++;

        // Remove s2[i-k]
        idx = s2[i - k] - 'a';
        if (freq1[idx] == freq2[idx]) matched--;
        freq2[idx]--;
        if (freq1[idx] == freq2[idx]) matched++;

        if (matched == 26) return true;
    }
    return false;
}

// ============================================================================
// LC 438: Find All Anagrams — Return all start indices of anagrams of p in s
// ============================================================================
vector<int> findAnagrams(string s, string p) {
    if (p.size() > s.size()) return {};

    int freq_p[26] = {}, freq_s[26] = {};
    int k = p.size();
    vector<int> result;

    for (char c : p) freq_p[c - 'a']++;
    for (int i = 0; i < k; i++) freq_s[s[i] - 'a']++;

    int matched = 0;
    for (int i = 0; i < 26; i++)
        if (freq_p[i] == freq_s[i]) matched++;

    if (matched == 26) result.push_back(0);

    for (int i = k; i < (int)s.size(); i++) {
        int idx = s[i] - 'a';
        if (freq_p[idx] == freq_s[idx]) matched--;
        freq_s[idx]++;
        if (freq_p[idx] == freq_s[idx]) matched++;

        idx = s[i - k] - 'a';
        if (freq_p[idx] == freq_s[idx]) matched--;
        freq_s[idx]--;
        if (freq_p[idx] == freq_s[idx]) matched++;

        if (matched == 26) result.push_back(i - k + 1);
    }
    return result;
}

// ============================================================================
// LC 187: Repeated DNA Sequences — Fixed window of 10 + hashing
// ============================================================================
vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<string, int> seen;
    vector<string> result;

    for (int i = 0; i + 10 <= (int)s.size(); i++) {
        string sub = s.substr(i, 10);
        seen[sub]++;
        if (seen[sub] == 2) result.push_back(sub);
    }
    return result;
}

int main() {
    // Permutation in String
    cout << "checkInclusion(ab, eidbaooo): " << checkInclusion("ab", "eidbaooo") << "\n"; // 1

    // Find All Anagrams
    auto res = findAnagrams("cbaebabacd", "abc");
    cout << "Anagram starts: ";
    for (int x : res) cout << x << " ";
    cout << "\n"; // 0 6

    // DNA Sequences
    auto dna = findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    cout << "Repeated DNA: ";
    for (auto& s : dna) cout << s << " ";
    cout << "\n";

    return 0;
}

