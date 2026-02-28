/*
 * ============================================================================
 *  Author  : Sarvan Yaduvanshi
 *  Topic   : Rolling Hash — Rabin-Karp & Repeated Substrings of Fixed Length
 *  Level   : Medium → Hard (CF 1600 → 2200)
 * ============================================================================
 *
 *  ▶ WHAT IS ROLLING HASH?
 *  ───────────────────────
 *  A hash function for a fixed-length substring that can be updated in O(1)
 *  when the window slides one position:
 *    hash(s[i+1..i+k]) = (hash(s[i..i+k-1]) - s[i]*base^(k-1)) * base + s[i+k]
 *
 *  This allows pattern matching in O(N) average time (Rabin-Karp).
 *
 *  ▶ RABIN-KARP ALGORITHM:
 *  ───────────────────────
 *  1. Compute hash of pattern.
 *  2. Slide a window of pattern-length over text, maintaining rolling hash.
 *  3. If hashes match → verify characters (to avoid hash collisions).
 *
 *  ▶ DOUBLE HASHING:
 *  ─────────────────
 *  Use TWO different (base, mod) pairs. Both must match → collision probability ≈ 0.
 *
 *  PROBLEMS:
 *  LC 187  — Repeated DNA Sequences (fixed window K=10)
 *            https://leetcode.com/problems/repeated-dna-sequences/
 *  LC 1044 — Longest Duplicate Substring (binary search + rolling hash)
 *            https://leetcode.com/problems/longest-duplicate-substring/
 *  LC 28   — Find the Index of the First Occurrence (Rabin-Karp or KMP)
 *            https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
 *  LC 1062 — Longest Repeating Substring
 *            https://leetcode.com/problems/longest-repeating-substring/
 *  LC 2156 — Find Substring With Given Hash Value
 *            https://leetcode.com/problems/find-substring-with-given-hash-value/
 *  CF 271D — Good Substrings (trie/hash, 1800)
 *            https://codeforces.com/problemset/problem/271/D
 *  CF 126B — Password (Z-function or hash, 1700)
 *            https://codeforces.com/problemset/problem/126/B
 *
 * ============================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;
using ll = long long;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1e9 + 9;
const ll BASE1 = 31;
const ll BASE2 = 37;

// ============================================================================
// Rabin-Karp: Find pattern in text — Rolling Hash O(N + M)
// ============================================================================
/*
 * Hash = s[0]*B^(k-1) + s[1]*B^(k-2) + ... + s[k-1]*B^0
 * Roll: hash = (hash - s[left]*B^(k-1)) * B + s[right+1]
 *
 * All arithmetic mod a large prime.
 */
vector<int> rabinKarp(string text, string pattern) {
    int n = text.size(), m = pattern.size();
    if (m > n) return {};

    vector<int> result;
    ll patHash = 0, textHash = 0;
    ll highPow = 1; // BASE^(m-1)

    for (int i = 0; i < m - 1; i++)
        highPow = highPow * BASE1 % MOD1;

    // Compute pattern hash and initial text window hash
    for (int i = 0; i < m; i++) {
        patHash = (patHash * BASE1 + pattern[i]) % MOD1;
        textHash = (textHash * BASE1 + text[i]) % MOD1;
    }

    for (int i = 0; i <= n - m; i++) {
        if (textHash == patHash) {
            // Verify to avoid collision (optional for competitive programming)
            if (text.substr(i, m) == pattern)
                result.push_back(i);
        }
        if (i + m < n) {
            // Roll hash: remove text[i], add text[i+m]
            textHash = (textHash - text[i] * highPow % MOD1 + MOD1) % MOD1;
            textHash = (textHash * BASE1 + text[i + m]) % MOD1;
        }
    }
    return result;
}

// ============================================================================
// Detect Repeated Substrings of Length K — Rolling Hash + HashSet
// ============================================================================
/*
 * Find all substrings of length K that appear more than once.
 * Compute rolling hash for each window, store in set.
 * If hash already seen → potential repeat (verify if needed).
 *
 * Time: O(N), Space: O(N)
 */
vector<string> repeatedSubstringsOfLengthK(string s, int k) {
    int n = s.size();
    if (k > n) return {};

    unordered_map<ll, int> seen; // hash → first occurrence index
    unordered_set<string> result;

    ll hash1 = 0, highPow = 1;
    for (int i = 0; i < k - 1; i++)
        highPow = highPow * BASE1 % MOD1;

    for (int i = 0; i < k; i++)
        hash1 = (hash1 * BASE1 + s[i]) % MOD1;

    seen[hash1] = 0;

    for (int i = 1; i + k - 1 < n; i++) {
        hash1 = (hash1 - s[i - 1] * highPow % MOD1 + MOD1) % MOD1;
        hash1 = (hash1 * BASE1 + s[i + k - 1]) % MOD1;

        if (seen.count(hash1))
            result.insert(s.substr(i, k));
        else
            seen[hash1] = i;
    }
    return vector<string>(result.begin(), result.end());
}

// ============================================================================
// LC 187: Repeated DNA Sequences — Fixed window K=10 + rolling hash
// ============================================================================
/*
 * DNA = A, C, G, T. Find all 10-letter sequences that occur more than once.
 * Can use rolling hash or just string hashing (K=10 is small).
 */
vector<string> findRepeatedDnaSequences(string s) {
    if (s.size() <= 10) return {};
    unordered_map<string, int> freq;
    vector<string> result;

    for (int i = 0; i + 10 <= (int)s.size(); i++) {
        string sub = s.substr(i, 10);
        freq[sub]++;
        if (freq[sub] == 2) result.push_back(sub);
    }
    return result;
}

// Optimized with bitmask (A=00, C=01, G=10, T=11)
vector<string> findRepeatedDna_bitmask(string s) {
    if (s.size() <= 10) return {};
    auto encode = [](char c) -> int {
        switch (c) { case 'A': return 0; case 'C': return 1;
                     case 'G': return 2; case 'T': return 3; }
        return 0;
    };

    unordered_map<int, int> seen;
    vector<string> result;
    int mask = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        mask = ((mask << 2) | encode(s[i])) & ((1 << 20) - 1); // 10 chars * 2 bits
        if (i >= 9) {
            seen[mask]++;
            if (seen[mask] == 2) result.push_back(s.substr(i - 9, 10));
        }
    }
    return result;
}

// ============================================================================
// LC 1044: Longest Duplicate Substring — Binary Search + Rolling Hash
// ============================================================================
/*
 * Find longest substring that appears at least twice.
 * Binary search on length K. For each K, use rolling hash to check duplicates.
 *
 * Time: O(N log N) average, Space: O(N)
 */
string longestDupSubstring(string s) {
    int n = s.size();

    auto check = [&](int len) -> string {
        ll hash1 = 0, highPow = 1;
        for (int i = 0; i < len - 1; i++)
            highPow = highPow * BASE1 % MOD1;
        for (int i = 0; i < len; i++)
            hash1 = (hash1 * BASE1 + s[i]) % MOD1;

        unordered_map<ll, vector<int>> seen;
        seen[hash1].push_back(0);

        for (int i = 1; i + len - 1 < n; i++) {
            hash1 = (hash1 - s[i - 1] * highPow % MOD1 + MOD1) % MOD1;
            hash1 = (hash1 * BASE1 + s[i + len - 1]) % MOD1;

            if (seen.count(hash1)) {
                // Verify (avoid collision)
                string cur = s.substr(i, len);
                for (int j : seen[hash1])
                    if (s.substr(j, len) == cur) return cur;
            }
            seen[hash1].push_back(i);
        }
        return "";
    };

    int lo = 1, hi = n - 1;
    string best = "";
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        string found = check(mid);
        if (!found.empty()) {
            best = found;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return best;
}

// ============================================================================
// Double Hashing Template — Minimize collision probability
// ============================================================================
struct DoubleHash {
    ll h1, h2, hp1, hp2; // hashes and high powers
    int len;

    DoubleHash() : h1(0), h2(0), hp1(1), hp2(1), len(0) {}

    void init(string& s, int k) {
        len = k;
        h1 = h2 = 0;
        hp1 = hp2 = 1;
        for (int i = 0; i < k - 1; i++) {
            hp1 = hp1 * BASE1 % MOD1;
            hp2 = hp2 * BASE2 % MOD2;
        }
        for (int i = 0; i < k; i++) {
            h1 = (h1 * BASE1 + s[i]) % MOD1;
            h2 = (h2 * BASE2 + s[i]) % MOD2;
        }
    }

    void roll(char remove, char add) {
        h1 = (h1 - remove * hp1 % MOD1 + MOD1) % MOD1;
        h1 = (h1 * BASE1 + add) % MOD1;
        h2 = (h2 - remove * hp2 % MOD2 + MOD2) % MOD2;
        h2 = (h2 * BASE2 + add) % MOD2;
    }

    ll combined() { return h1 * MOD2 + h2; } // Unique combined hash
};

int main() {
    // Rabin-Karp
    auto matches = rabinKarp("aabaabaa", "aab");
    cout << "Rabin-Karp matches: ";
    for (int i : matches) cout << i << " ";
    cout << "\n"; // 0 3

    // Repeated substrings of length 3
    auto reps = repeatedSubstringsOfLengthK("abcabcabc", 3);
    cout << "Repeated (k=3): ";
    for (auto& s : reps) cout << s << " ";
    cout << "\n"; // abc

    // DNA sequences
    auto dna = findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    cout << "Repeated DNA: ";
    for (auto& s : dna) cout << s << " ";
    cout << "\n";

    // Longest duplicate substring
    cout << "Longest dup: " << longestDupSubstring("banana") << "\n"; // "ana"

    return 0;
}

