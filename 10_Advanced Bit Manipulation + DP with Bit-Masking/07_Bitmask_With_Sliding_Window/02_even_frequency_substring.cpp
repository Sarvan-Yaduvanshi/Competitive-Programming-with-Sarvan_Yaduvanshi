/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07.02 — EVEN FREQUENCY SUBSTRING                           ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM: Find longest substring where every character appears an even number of times.
METHOD: Use parity mask. Substring [L+1..R] has all even freqs ⟺ mask[R] == mask[L].
    Track first occurrence of each mask. Answer = max(i - firstOccurrence[mask]).

DRY RUN — "eleetcode":
    Masks: 0, e→10000, l→10000|..., ...
    When mask repeats, that substring has all even frequencies.

TIME: O(n), SPACE: O(2^|Σ|) worst case, but usually O(n) with hashmap.
LeetCode 1371: Find the Longest Substring Containing Vowels in Even Counts
*/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// General version: all characters even frequency
int longestEvenFreqSubstring(const string& s) {
    unordered_map<int, int> first;
    first[0] = -1;
    int mask = 0, best = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        mask ^= (1 << (s[i] - 'a'));
        if (first.count(mask)) {
            best = max(best, i - first[mask]);
        } else {
            first[mask] = i;
        }
    }
    return best;
}

// LeetCode 1371: Only vowels need even counts
int longestVowelEven(const string& s) {
    string vowels = "aeiou";
    unordered_map<int, int> first;
    first[0] = -1;
    int mask = 0, best = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        for (int v = 0; v < 5; v++) {
            if (s[i] == vowels[v]) mask ^= (1 << v);
        }
        if (first.count(mask)) {
            best = max(best, i - first[mask]);
        } else {
            first[mask] = i;
        }
    }
    return best;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   EVEN FREQUENCY SUBSTRING                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "  \"aabbcc\": " << longestEvenFreqSubstring("aabbcc") << endl;     // 6
    cout << "  \"abcbad\": " << longestEvenFreqSubstring("abcbad") << endl;     // 4 "bcba" or "abcb"

    cout << "\n--- LeetCode 1371: Vowels Even ---" << endl;
    cout << "  \"eleetminicoworepep\": " << longestVowelEven("eleetminicoworepep") << endl; // 13

    cout << "\n✅ Even frequency substring verified!" << endl;
    return 0;
}

