/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07.01 — PARITY MASK                                      ║
║           Bit Manipulation — Bitmask With Sliding Window                   ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

CONCEPT: Track parity (even/odd count) of characters using XOR on a bitmask.
    mask = 0 initially.
    For character c: mask ^= (1 << (c - 'a'))
    Bit i = 1 ⟺ character ('a'+i) has appeared ODD number of times so far.
    Bit i = 0 ⟺ character has appeared EVEN number of times.

KEY INSIGHT: mask at position R ⊕ mask at position L gives parity of substring [L+1..R].
    If mask[R] == mask[L], then substring (L..R] has all even frequencies.
    If mask[R] ⊕ mask[L] has exactly 1 bit set, substring has exactly 1 odd-freq char.

APPLICATIONS:
═════════════
    • Palindrome permutation substring: popcount(mask[R] ⊕ mask[L]) ≤ 1
    • Even frequency substring: mask[R] == mask[L]
    • Longest awesome substring (LeetCode 1542)

DRY RUN — "aabb":
    mask after 'a': 0001
    mask after 'a': 0000 (even 'a')
    mask after 'b': 0010
    mask after 'b': 0000 (all even → palindrome permutation possible!)
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
using namespace std;

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   PARITY MASK                                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    string s = "aabbcc";
    int mask = 0;
    cout << "\n--- Parity Mask Trace for \"" << s << "\" ---" << endl;
    cout << "  Initial: " << bitset<8>(mask) << endl;
    for (char c : s) {
        mask ^= (1 << (c - 'a'));
        cout << "  After '" << c << "': " << bitset<8>(mask)
             << " (odd-freq chars: ";
        bool first = true;
        for (int i = 0; i < 26; i++) {
            if (mask & (1 << i)) {
                if (!first) cout << ",";
                cout << (char)('a'+i);
                first = false;
            }
        }
        cout << (first ? "none" : "") << ")" << endl;
    }
    cout << "  Final mask = 0 → all frequencies even ✓" << endl;

    // Find longest substring with all even frequencies
    cout << "\n--- Longest Even-Frequency Substring ---" << endl;
    s = "abcbad";
    mask = 0;
    unordered_map<int, int> firstOccurrence;
    firstOccurrence[0] = -1;
    int best = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        mask ^= (1 << (s[i] - 'a'));
        if (firstOccurrence.count(mask)) {
            best = max(best, i - firstOccurrence[mask]);
        } else {
            firstOccurrence[mask] = i;
        }
    }
    cout << "  \"" << s << "\": longest even-freq substring length = " << best << endl;

    cout << "\n✅ Parity mask demonstrated!" << endl;
    return 0;
}

