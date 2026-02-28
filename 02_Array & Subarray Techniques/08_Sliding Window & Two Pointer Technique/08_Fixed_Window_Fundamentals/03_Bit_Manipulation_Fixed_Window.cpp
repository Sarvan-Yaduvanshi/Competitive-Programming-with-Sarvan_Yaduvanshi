/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Bit Manipulation + Fixed Sliding Window
 *  Level   : Medium → Hard (CF 1600 → 2000)
 * ============================================================================
 *
 *  ▶ CORE IDEA:
 *  ────────────
 *  Maintain bitwise properties (XOR, OR, AND, parity mask, set-bit count)
 *  of a fixed window of size K. Add right bit, remove left bit in O(1)
 *  per operation (XOR) or O(32) per operation (OR/AND with frequency).
 *
 *  ▶ KEY TECHNIQUES:
 *  ─────────────────
 *  1. XOR Window: xor_window ^= arr[right] ^ arr[left]  → O(1)
 *  2. OR Window:  Track bit frequency count[0..31]. OR = bits with count > 0.
 *  3. AND Window: Track bit frequency count[0..31]. AND = bits with count == k.
 *  4. Parity Mask: Use bitmask to track even/odd frequency of characters.
 *     Palindrome permutation = at most 1 bit set in parity mask.
 *
 *  PROBLEMS:
 *  LC 1461 — Check If String Contains All Binary Codes of Size K
 *            https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
 *  LC 1310 — XOR Queries of a Subarray (prefix XOR, not window but related)
 *            https://leetcode.com/problems/xor-queries-of-a-subarray/
 *  LC 1177 — Can Make Palindrome from Substring (parity mask + prefix)
 *            https://leetcode.com/problems/can-make-palindrome-from-substring/
 *  LC 2932 — Maximum Strong Pair XOR I
 *            https://leetcode.com/problems/maximum-strong-pair-xor-i/
 *  CF 1614D1 — Divan and Kostomuksha (Easy) (bit counting, 1700)
 *            https://codeforces.com/problemset/problem/1614/D1
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// ============================================================================
// XOR of Every Window of Size K — O(N) total
// ============================================================================
/*
 * XOR is its own inverse: a ^ a = 0.
 * So sliding: windowXOR ^= arr[right]; if window full: windowXOR ^= arr[left].
 */
vector<int> xorOfEveryWindow(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> result;
    int windowXor = 0;

    for (int i = 0; i < n; i++) {
        windowXor ^= arr[i];
        if (i >= k) windowXor ^= arr[i - k]; // Remove left
        if (i >= k - 1) result.push_back(windowXor);
    }
    return result;
}

// ============================================================================
// OR of Every Window of Size K — O(32 * N)
// ============================================================================
/*
 * OR can't be "removed" directly. Track bit frequency:
 * bitCount[b] = how many elements in window have bit b set.
 * OR = all bits where bitCount[b] > 0.
 */
vector<int> orOfEveryWindow(vector<int>& arr, int k) {
    int n = arr.size();
    int bitCount[32] = {};
    vector<int> result;

    for (int i = 0; i < n; i++) {
        // Add arr[i]
        for (int b = 0; b < 32; b++)
            if (arr[i] & (1 << b)) bitCount[b]++;

        // Remove arr[i-k]
        if (i >= k) {
            for (int b = 0; b < 32; b++)
                if (arr[i - k] & (1 << b)) bitCount[b]--;
        }

        if (i >= k - 1) {
            int orVal = 0;
            for (int b = 0; b < 32; b++)
                if (bitCount[b] > 0) orVal |= (1 << b);
            result.push_back(orVal);
        }
    }
    return result;
}

// ============================================================================
// AND of Every Window of Size K — O(32 * N)
// ============================================================================
/*
 * AND = bits where ALL k elements have that bit set.
 * AND = bits where bitCount[b] == k.
 */
vector<int> andOfEveryWindow(vector<int>& arr, int k) {
    int n = arr.size();
    int bitCount[32] = {};
    vector<int> result;

    for (int i = 0; i < n; i++) {
        for (int b = 0; b < 32; b++)
            if (arr[i] & (1 << b)) bitCount[b]++;
        if (i >= k) {
            for (int b = 0; b < 32; b++)
                if (arr[i - k] & (1 << b)) bitCount[b]--;
        }
        if (i >= k - 1) {
            int andVal = 0;
            for (int b = 0; b < 32; b++)
                if (bitCount[b] == k) andVal |= (1 << b);
            result.push_back(andVal);
        }
    }
    return result;
}

// ============================================================================
// Parity Mask Window — Palindrome Permutation Check
// ============================================================================
/*
 * Parity mask: bitmask where bit i = 1 means char i has ODD frequency.
 * A string is a permutation of a palindrome iff at most 1 bit is set.
 * Check: mask == 0 || (mask & (mask - 1)) == 0
 *
 * Sliding: add char → flip bit. Remove char → flip bit (same operation!).
 */
vector<bool> palindromePermutationWindows(string s, int k) {
    int n = s.size();
    vector<bool> result;
    int mask = 0;

    for (int i = 0; i < n; i++) {
        mask ^= (1 << (s[i] - 'a')); // Toggle bit for s[i]
        if (i >= k) mask ^= (1 << (s[i - k] - 'a')); // Remove left

        if (i >= k - 1) {
            // At most 1 bit set → palindrome permutation possible
            result.push_back(mask == 0 || (mask & (mask - 1)) == 0);
        }
    }
    return result;
}

// ============================================================================
// LC 1461: Check If String Contains All Binary Codes of Size K
// ============================================================================
/*
 * Check if all binary strings of length K appear as substrings.
 * Fixed window of size K on binary string. Use rolling hash or set.
 * Total possible = 2^K. If set size == 2^K → all present.
 *
 * Time: O(N*K) with set, or O(N) with rolling bitmask for small K.
 */
bool hasAllCodes(string s, int k) {
    if ((int)s.size() < k) return false;
    unordered_set<string> seen;
    for (int i = 0; i + k <= (int)s.size(); i++)
        seen.insert(s.substr(i, k));
    return (int)seen.size() == (1 << k);
}

// Optimized: rolling bitmask for K ≤ 20
bool hasAllCodes_fast(string s, int k) {
    if ((int)s.size() < k + (1 << k) - 1) return false;
    int total = 1 << k;
    vector<bool> seen(total, false);
    int count = 0, mask = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        mask = ((mask << 1) | (s[i] - '0')) & (total - 1);
        if (i >= k - 1) {
            if (!seen[mask]) { seen[mask] = true; count++; }
            if (count == total) return true;
        }
    }
    return false;
}

// ============================================================================
// Window with Exactly K Set Bits in Sum
// ============================================================================
/*
 * Count windows of size W where the sum has exactly K set bits.
 * Maintain window sum, check __builtin_popcount(sum) == K.
 */
int countWindowsWithKSetBits(vector<int>& arr, int w, int k) {
    int n = arr.size(), sum = 0, count = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (i >= w) sum -= arr[i - w];
        if (i >= w - 1 && __builtin_popcount(sum) == k) count++;
    }
    return count;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};

    // XOR windows
    auto xors = xorOfEveryWindow(arr, 3);
    cout << "XOR windows (k=3): ";
    for (int x : xors) cout << x << " ";
    cout << "\n"; // 1^2^3=0, 2^3^4=5, 3^4^5=2

    // OR windows
    auto ors = orOfEveryWindow(arr, 3);
    cout << "OR windows (k=3): ";
    for (int x : ors) cout << x << " ";
    cout << "\n"; // 3, 7, 7

    // AND windows
    auto ands = andOfEveryWindow(arr, 3);
    cout << "AND windows (k=3): ";
    for (int x : ands) cout << x << " ";
    cout << "\n"; // 0, 0, 0

    // Palindrome permutation windows
    auto palins = palindromePermutationWindows("aabcba", 3);
    cout << "Palindrome perm windows (k=3): ";
    for (bool b : palins) cout << b << " ";
    cout << "\n";

    // All binary codes
    cout << "Has all codes(k=2): " << hasAllCodes_fast("00110110", 2) << "\n"; // 1

    return 0;
}

