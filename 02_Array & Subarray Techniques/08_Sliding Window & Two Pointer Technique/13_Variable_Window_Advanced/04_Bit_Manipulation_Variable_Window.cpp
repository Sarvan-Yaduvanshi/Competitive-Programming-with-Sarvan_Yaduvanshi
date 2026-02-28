/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Bit Manipulation + Variable Sliding Window
 *  Level   : Hard → Expert (CF 1700 → 2200)
 * ============================================================================
 *
 *  ▶ WHY BITS + VARIABLE WINDOW?
 *  ─────────────────────────────
 *  Many CF and LC problems combine bitwise operations with variable window:
 *  - XOR is "toggle" → prefix XOR converts subarray XOR to two-point query
 *  - AND is monotone decreasing as window grows → shrinkable
 *  - OR is monotone increasing as window grows → shrinkable
 *  - Parity mask: track odd/even frequency of characters with bitmask
 *
 *  ▶ KEY INSIGHT — MONOTONICITY:
 *  ─────────────────────────────
 *  - AND: Adding elements can only DECREASE or maintain AND → window AND ≥ K
 *    is shrinkable (expand while AND ≥ K, shrink otherwise)
 *  - OR: Adding elements can only INCREASE or maintain OR → window OR ≥ K
 *    means once satisfied, all larger windows also satisfy
 *  - XOR: NOT monotone! Can't use simple shrink. Need prefix XOR + hashmap.
 *
 *  ▶ BIT FREQUENCY TRICK (for AND/OR variable window):
 *  ───────────────────────────────────────────────────
 *  Maintain bitCount[0..31]: how many elements in window have bit b set.
 *  - Current AND: bit b is set iff bitCount[b] == windowSize
 *  - Current OR: bit b is set iff bitCount[b] > 0
 *  - Add element: for each bit b, if (x >> b) & 1, bitCount[b]++
 *  - Remove element: for each bit b, if (x >> b) & 1, bitCount[b]--
 *
 *  PROBLEMS:
 *  LC 1371 — Longest Substring With Even Count of Vowels (parity mask)
 *            https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
 *  LC 1542 — Longest Awesome Substring (mask-based, at most 1 odd freq)
 *            https://leetcode.com/problems/find-longest-awesome-substring/
 *  LC 1915 — Number of Wonderful Substrings (mask counting)
 *            https://leetcode.com/problems/number-of-wonderful-substrings/
 *  LC 2401 — Longest Nice Subarray (bitwise AND of any two = 0)
 *            https://leetcode.com/problems/longest-nice-subarray/
 *  LC 2411 — Smallest Subarrays With Max Bitwise OR
 *            https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/
 *  LC 1712 — Ways to Split Array Into Three Parts (prefix + condition)
 *            https://leetcode.com/problems/ways-to-split-array-into-three-parts/
 *  CF 1878E — Iva & Pav (AND ≥ K, binary search + prefix bit count, 1400)
 *            https://codeforces.com/problemset/problem/1878/E
 *  CF 1004F — Sonya and Bitwise OR (segment tree + merge, 2400)
 *            https://codeforces.com/problemset/problem/1004/F
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
using ll = long long;

// ============================================================================
// SUBARRAY XOR = K — Prefix XOR + HashMap (NOT a sliding window!)
// ============================================================================
/*
 * XOR(l..r) = prefixXOR[r+1] ^ prefixXOR[l]
 * We want prefixXOR[r+1] ^ prefixXOR[l] = K
 * → prefixXOR[l] = prefixXOR[r+1] ^ K
 *
 * Count subarrays with XOR = K: scan prefix, count occurrences of (cur ^ K).
 * Longest subarray with XOR = K: store first occurrence of each prefix XOR.
 *
 * Time: O(N), Space: O(N)
 */
int countSubarraysXorK(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    freq[0] = 1; // Empty prefix
    int prefXor = 0, count = 0;

    for (int x : arr) {
        prefXor ^= x;
        int need = prefXor ^ k;
        if (freq.count(need)) count += freq[need];
        freq[prefXor]++;
    }
    return count;
}

int longestSubarrayXorK(vector<int>& arr, int k) {
    unordered_map<int, int> firstOccurrence;
    firstOccurrence[0] = -1; // Empty prefix at index -1
    int prefXor = 0, maxLen = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        prefXor ^= arr[i];
        int need = prefXor ^ k;
        if (firstOccurrence.count(need))
            maxLen = max(maxLen, i - firstOccurrence[need]);
        if (!firstOccurrence.count(prefXor))
            firstOccurrence[prefXor] = i;
    }
    return maxLen;
}

// ============================================================================
// VARIABLE WINDOW + BITWISE AND ≥ K — Bit Frequency Array
// ============================================================================
/*
 * AND is monotone decreasing: adding elements can only keep/decrease AND.
 * So we can use shrinking: expand right, if AND < K → shrink left.
 *
 * Maintain bitCount[0..31]. Current AND bit b = (bitCount[b] == windowSize).
 * When we remove an element from left, update bitCount.
 *
 * Find: longest subarray with AND ≥ K.
 * Time: O(N * 32), Space: O(1)
 */
int longestSubarrayAndGeK(vector<int>& arr, int k) {
    int n = arr.size();
    int bitCount[32] = {};
    int best = 0, left = 0;

    auto getCurrentAND = [&](int windowSize) -> int {
        int andVal = 0;
        for (int b = 0; b < 32; b++)
            if (bitCount[b] == windowSize) andVal |= (1 << b);
        return andVal;
    };

    for (int right = 0; right < n; right++) {
        // Add arr[right]
        for (int b = 0; b < 32; b++)
            if (arr[right] & (1 << b)) bitCount[b]++;

        // Shrink while AND < K
        while (left <= right && getCurrentAND(right - left + 1) < k) {
            for (int b = 0; b < 32; b++)
                if (arr[left] & (1 << b)) bitCount[b]--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// VARIABLE WINDOW + BITWISE OR ≥ K — Bit Frequency Array
// ============================================================================
/*
 * OR is monotone increasing: adding elements can only keep/increase OR.
 * Find: SHORTEST subarray with OR ≥ K.
 * Expand right. Once OR ≥ K → try shrink left to find minimum.
 *
 * Time: O(N * 32), Space: O(1)
 */
int shortestSubarrayOrGeK(vector<int>& arr, int k) {
    int n = arr.size();
    int bitCount[32] = {};
    int best = n + 1, left = 0;

    auto getCurrentOR = [&]() -> int {
        int orVal = 0;
        for (int b = 0; b < 32; b++)
            if (bitCount[b] > 0) orVal |= (1 << b);
        return orVal;
    };

    for (int right = 0; right < n; right++) {
        for (int b = 0; b < 32; b++)
            if (arr[right] & (1 << b)) bitCount[b]++;

        while (getCurrentOR() >= k) {
            best = min(best, right - left + 1);
            for (int b = 0; b < 32; b++)
                if (arr[left] & (1 << b)) bitCount[b]--;
            left++;
        }
    }
    return best == n + 1 ? -1 : best;
}

// ============================================================================
// LC 2401: Longest Nice Subarray — AND of any pair = 0
// ============================================================================
/*
 * All elements in window must have disjoint set bits (no two share a bit).
 * Maintain usedBits mask. Add: if (arr[right] & usedBits) == 0 → OK.
 * Otherwise shrink left until no conflict.
 *
 * Time: O(N * 32) worst case, O(N) amortized since each element added/removed once
 */
int longestNiceSubarray(vector<int>& nums) {
    int usedBits = 0, left = 0, best = 0;
    for (int right = 0; right < (int)nums.size(); right++) {
        while (usedBits & nums[right]) {
            usedBits ^= nums[left]; // Remove left's bits
            left++;
        }
        usedBits |= nums[right]; // Add right's bits
        best = max(best, right - left + 1);
    }
    return best;
}

// ============================================================================
// LC 1371: Longest Substring With Even Count of Vowels — Parity Mask
// ============================================================================
/*
 * Track parity of each vowel (a,e,i,o,u) as a 5-bit mask.
 * mask bit = 1 means that vowel has odd count in prefix[0..i].
 * Substring [l+1..r] has all even vowels iff mask[r] == mask[l].
 * Store first occurrence of each mask. Answer = max(i - firstOcc[mask]).
 *
 * Time: O(N), Space: O(32) = O(1) for 5-bit mask
 */
int findTheLongestSubstring(string s) {
    unordered_map<int, int> firstOcc;
    firstOcc[0] = -1; // Empty prefix has mask 0
    int mask = 0, best = 0;
    string vowels = "aeiou";

    for (int i = 0; i < (int)s.size(); i++) {
        int pos = vowels.find(s[i]);
        if (pos != (int)string::npos) mask ^= (1 << pos);

        if (firstOcc.count(mask))
            best = max(best, i - firstOcc[mask]);
        else
            firstOcc[mask] = i;
    }
    return best;
}

// ============================================================================
// LC 1542: Find Longest Awesome Substring — Parity Mask (at most 1 odd)
// ============================================================================
/*
 * "Awesome" = can rearrange to form palindrome = at most 1 digit with odd freq.
 * Use 10-bit parity mask (digits 0-9).
 * Palindrome possible iff mask == 0 (all even) or mask has exactly 1 bit set.
 *
 * For each prefix mask: check if same mask seen before (all even),
 * or mask ^ (1 << d) seen before for each digit d (one odd allowed).
 *
 * Time: O(10N), Space: O(1024)
 */
int longestAwesome(string s) {
    vector<int> firstOcc(1 << 10, -2); // -2 = not seen
    firstOcc[0] = -1; // Empty prefix
    int mask = 0, best = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        mask ^= (1 << (s[i] - '0'));

        // Case 1: all even → same mask seen before
        if (firstOcc[mask] != -2)
            best = max(best, i - firstOcc[mask]);

        // Case 2: exactly one odd → mask ^ (1 << d) seen before
        for (int d = 0; d < 10; d++) {
            int target = mask ^ (1 << d);
            if (firstOcc[target] != -2)
                best = max(best, i - firstOcc[target]);
        }

        if (firstOcc[mask] == -2) firstOcc[mask] = i;
    }
    return best;
}

// ============================================================================
// LC 1915: Number of Wonderful Substrings — Count Parity Masks
// ============================================================================
/*
 * "Wonderful" = at most one character with odd frequency.
 * 10 possible characters (a-j) → 10-bit mask.
 * Count substrings: for each prefix mask, count previous masks that differ
 * by 0 bits (exact match) or 1 bit (exactly one odd character).
 *
 * Time: O(10N), Space: O(1024)
 */
long long wonderfulSubstrings(string word) {
    vector<ll> count(1 << 10, 0);
    count[0] = 1;
    int mask = 0;
    ll result = 0;

    for (char c : word) {
        mask ^= (1 << (c - 'a'));
        result += count[mask]; // Same mask → all even
        for (int b = 0; b < 10; b++)
            result += count[mask ^ (1 << b)]; // One bit different → one odd
        count[mask]++;
    }
    return result;
}

int main() {
    // Subarray XOR = K
    vector<int> a1 = {4, 2, 2, 6, 4};
    cout << "Count XOR=6: " << countSubarraysXorK(a1, 6) << "\n"; // 4
    cout << "Longest XOR=6: " << longestSubarrayXorK(a1, 6) << "\n"; // 4

    // Longest AND ≥ K
    vector<int> a2 = {7, 6, 3, 7, 5};
    cout << "Longest AND≥4: " << longestSubarrayAndGeK(a2, 4) << "\n"; // 2

    // Shortest OR ≥ K
    vector<int> a3 = {1, 2, 4, 8};
    cout << "Shortest OR≥7: " << shortestSubarrayOrGeK(a3, 7) << "\n"; // 3

    // Nice subarray
    vector<int> a4 = {1, 3, 8, 48, 10};
    cout << "Nice subarray: " << longestNiceSubarray(a4) << "\n"; // 3

    // Even vowels
    cout << "Even vowels: " << findTheLongestSubstring("eleetminicoworoep") << "\n"; // 13

    // Longest awesome
    cout << "Awesome: " << longestAwesome("3242415") << "\n"; // 5

    // Wonderful substrings
    cout << "Wonderful: " << wonderfulSubstrings("aba") << "\n"; // 4

    return 0;
}

