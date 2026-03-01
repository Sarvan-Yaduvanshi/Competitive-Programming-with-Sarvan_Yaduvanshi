/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 07.04 — LONGEST AWESOME SUBSTRING                        ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

PROBLEM (LeetCode 1542): Find longest substring where you can rearrange it to form
a palindrome. Only digits '0'-'9', so mask is 10 bits.

CONDITION: popcount(mask[R] ⊕ mask[L]) ≤ 1 (at most 1 odd-frequency digit).

METHOD: For each position, track earliest occurrence of each mask.
    Check mask (exact match) + 10 neighbors (differ by 1 bit).
    Answer = max(i - earliest[target_mask]).

TIME: O(n × 10) = O(n)
LeetCode 1542: Find Longest Awesome Substring
*/
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

int longestAwesome(const string& s) {
    int n = s.size();
    vector<int> first(1 << 10, n); // first[mask] = earliest index with this mask
    first[0] = -1;
    int mask = 0, best = 0;

    for (int i = 0; i < n; i++) {
        mask ^= (1 << (s[i] - '0'));
        // Check exact match (all even)
        if (first[mask] < n) best = max(best, i - first[mask]);
        // Check differ by 1 bit
        for (int b = 0; b < 10; b++) {
            int target = mask ^ (1 << b);
            if (first[target] < n) best = max(best, i - first[target]);
        }
        if (first[mask] == n) first[mask] = i;
    }
    return best;
}

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   LONGEST AWESOME SUBSTRING                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    cout << "  \"3242415\": " << longestAwesome("3242415") << endl; // 5: "24241"
    cout << "  \"12345678\": " << longestAwesome("12345678") << endl; // 1
    cout << "  \"213123\": " << longestAwesome("213123") << endl; // 6

    assert(longestAwesome("3242415") == 5);
    assert(longestAwesome("12345678") == 1);
    assert(longestAwesome("213123") == 6);

    cout << "\n✅ Longest awesome substring verified!" << endl;
    return 0;
}

