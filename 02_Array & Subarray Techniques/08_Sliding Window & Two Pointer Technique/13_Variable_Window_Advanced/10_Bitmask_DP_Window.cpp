/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Sliding Window + Bitmask DP Hybrid
 *  Level   : Hard → Expert (CF 1800 → 2200)
 * ============================================================================
 *
 *  ▶ CORE IDEA:
 *  ────────────
 *  Combine bitmask (tracking character coverage / state) with sliding window.
 *  Typical alphabet: 26 letters → 26-bit mask (but usually ≤ 10-20 relevant).
 *
 *  ▶ PATTERNS:
 *  ───────────
 *  1. Minimum Window Covering Mask: Find smallest window containing all
 *     required characters (generalization of LC 76).
 *  2. Window Mask Transitions: Track which characters are present in window
 *     using bitmask. Sliding adds/removes bits.
 *  3. Small Alphabet Compression: When alphabet ≤ 10-20, use bitmask
 *     instead of frequency array for O(1) state checks.
 *  4. Cover All Characters: Find window that has at least one of each
 *     required character. Use mask to track coverage.
 *
 *  PROBLEMS:
 *  LC 76   — Minimum Window Substring (covered in Module 13/01, but mask version here)
 *            https://leetcode.com/problems/minimum-window-substring/
 *  LC 1358 — Substrings Containing All Three Characters (mask coverage)
 *            https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
 *  LC 3006 — Find Beautiful Indices in the Given Array I
 *            https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-i/
 *  LC 1163 — Last Substring in Lexicographic Order (suffix, advanced)
 *            https://leetcode.com/problems/last-substring-in-lexicographical-order/
 *  CF 1016B — Segment Occurrences (pattern mask matching, 1300)
 *            https://codeforces.com/problemset/problem/1016/B
 *  CF 1234D — Distinct Characters Queries (bitmask per char, 1400)
 *            https://codeforces.com/problemset/problem/1234/D
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================================
// Minimum Window Covering All Required Characters — Bitmask Version
// ============================================================================
/*
 * Given string s and required characters (as a set/mask).
 * Find smallest window of s containing at least one of each required char.
 *
 * Track windowMask: bit i set if char i is present in window.
 * When windowMask ⊇ requiredMask → valid window, try shrinking.
 *
 * Time: O(N * 26) worst, O(N) amortized for small alphabets
 */
int minWindowCoveringMask(string s, string required) {
    int reqMask = 0;
    for (char c : required) reqMask |= (1 << (c - 'a'));

    int n = s.size();
    int freq[26] = {};
    int left = 0, best = n + 1;

    auto getMask = [&]() -> int {
        int mask = 0;
        for (int i = 0; i < 26; i++)
            if (freq[i] > 0) mask |= (1 << i);
        return mask;
    };

    for (int right = 0; right < n; right++) {
        freq[s[right] - 'a']++;

        while ((getMask() & reqMask) == reqMask) {
            best = min(best, right - left + 1);
            freq[s[left] - 'a']--;
            left++;
        }
    }
    return best == n + 1 ? -1 : best;
}

// Optimized: Track coverage count instead of recomputing mask
int minWindowCoveringMask_fast(string s, string required) {
    int reqMask = 0;
    for (char c : required) reqMask |= (1 << (c - 'a'));
    int reqCount = __builtin_popcount(reqMask);

    int n = s.size();
    int freq[26] = {};
    int covered = 0; // How many required chars are present
    int left = 0, best = n + 1;

    for (int right = 0; right < n; right++) {
        int ch = s[right] - 'a';
        freq[ch]++;
        if ((reqMask & (1 << ch)) && freq[ch] == 1) covered++;

        while (covered == reqCount) {
            best = min(best, right - left + 1);
            int lch = s[left] - 'a';
            freq[lch]--;
            if ((reqMask & (1 << lch)) && freq[lch] == 0) covered--;
            left++;
        }
    }
    return best == n + 1 ? -1 : best;
}

// ============================================================================
// LC 1358: Number of Substrings Containing All Three Characters
// ============================================================================
/*
 * Count substrings of "abc..." containing at least one a, b, c.
 * Use 3-bit mask or just count.
 * For each right, find leftmost left where all 3 are present.
 * count += left (all starting points 0..left-1 also work).
 */
int numberOfSubstrings(string s) {
    int n = s.size();
    int freq[3] = {};
    int left = 0, count = 0;

    for (int right = 0; right < n; right++) {
        freq[s[right] - 'a']++;
        while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {
            freq[s[left] - 'a']--;
            left++;
        }
        count += left; // All substrings starting before left are valid
    }
    return count;
}

// ============================================================================
// Window Mask Transitions — Track state changes
// ============================================================================
/*
 * As we slide the window, the mask changes:
 * Add char c: if freq[c] was 0, set bit c in mask. freq[c]++.
 * Remove char c: freq[c]--. if freq[c] becomes 0, clear bit c in mask.
 *
 * This gives O(1) mask update per add/remove.
 */
struct WindowMask {
    int mask = 0;
    int freq[26] = {};

    void add(char c) {
        int i = c - 'a';
        if (freq[i]++ == 0) mask |= (1 << i);
    }

    void remove(char c) {
        int i = c - 'a';
        if (--freq[i] == 0) mask &= ~(1 << i);
    }

    int getMask() { return mask; }
    int distinctCount() { return __builtin_popcount(mask); }
};

// ============================================================================
// Bitmask DP + Window: Count substrings with all characters in set S
// ============================================================================
/*
 * For small required set (≤ 20 chars), use bitmask DP.
 * State = which chars are covered. Transition = extend/shrink window.
 *
 * dp[mask] = count of windows achieving this coverage mask.
 * For competitive: often just track mask as you sweep and count.
 */

// Count substrings covering exactly the mask of characters present
// (no external target — just count per mask)
vector<long long> countPerMask(string s) {
    int n = s.size();
    // This is O(N * 2^alphabet) which is only feasible for very small alphabets
    // For a-z (26), this is too large. For a-j (10), it's 1024 → feasible.
    // Here we demonstrate for digits (10 chars).

    vector<long long> result(1 << 10, 0);
    WindowMask wm;

    // For each starting point, extend right and record mask
    // This is O(N^2) brute force — for better, use prefix mask + hashmap
    // (like LC 1915 wonderful substrings approach)

    // Prefix mask approach for counting:
    vector<long long> prefixCount(1 << 10, 0);
    prefixCount[0] = 1;
    int mask = 0;
    long long total = 0;

    for (char c : s) {
        mask ^= (1 << (c - '0'));
        // Substrings with same prefix mask = even frequency of all
        total += prefixCount[mask];
        prefixCount[mask]++;
    }
    result[0] = total; // Count of substrings with all even frequencies
    return result;
}

int main() {
    // Min window covering required chars
    cout << "Min window covering 'abc': "
         << minWindowCoveringMask_fast("adobecodebanc", "abc") << "\n"; // 4 ("banc")

    // Substrings containing all three
    cout << "Substrings with a,b,c: "
         << numberOfSubstrings("abcabc") << "\n"; // 10

    // Window mask demo
    WindowMask wm;
    wm.add('a'); wm.add('b'); wm.add('c');
    cout << "Mask after abc: " << wm.getMask() << " (distinct: " << wm.distinctCount() << ")\n"; // 7, 3
    wm.remove('b');
    cout << "Mask after removing b: " << wm.getMask() << " (distinct: " << wm.distinctCount() << ")\n"; // 5, 2

    return 0;
}

