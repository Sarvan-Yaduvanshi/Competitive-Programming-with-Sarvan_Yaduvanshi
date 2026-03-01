/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 07 — ADVANCED STRING ALGORITHMS                               ║
║     From Zero to Grandmaster — KMP/Z/Suffix Applications                   ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

This chapter covers ADVANCED APPLICATIONS of the algorithms from Chapter 06.
Chapter 06 = "Learn the algorithms"
Chapter 07 = "Master their applications in competitive programming"

TABLE OF CONTENTS:
─────────────────
 1. KMP Failure Link Applications
    • Period & Border analysis
    • All prefix-suffixes of a string
    • String periodicity lemma
 2. Z-Function Applications
    • Count pattern occurrences
    • All periods of a string
    • String matching with wildcards
    • Compress string representation
 3. Suffix Array Advanced Applications
    • LCP-based queries with Sparse Table
    • Number of distinct substrings
    • K-th smallest substring
    • Longest common substring of 2 strings
 4. Automaton-Based String Matching
    • Building DFA for pattern matching
    • String matching with finite automaton
 5. Bitwise String Matching (BNDM / Shift-Or)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include <cassert>
#include <cstring>
#include <cmath>
using namespace std;
using i64 = long long;

// ═══════════════════════════════════════════════════════════════
// HELPER: KMP LPS (from Chapter 06)
// ═══════════════════════════════════════════════════════════════
vector<int> buildLPS(const string& s) {
    int n = s.size();
    vector<int> lps(n, 0);
    int len = 0, i = 1;
    while (i < n) {
        if (s[i] == s[len]) { lps[i++] = ++len; }
        else if (len) { len = lps[len - 1]; }
        else { lps[i++] = 0; }
    }
    return lps;
}

// HELPER: Z-function (from Chapter 06)
vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

// HELPER: Suffix Array (from Chapter 06)
vector<int> buildSuffixArray(const string& s) {
    int n = s.size();
    vector<int> sa(n), rank_(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rank_[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rank_[a] != rank_[b]) return rank_[a] < rank_[b];
            int ra = (a + k < n) ? rank_[a + k] : -1;
            int rb = (b + k < n) ? rank_[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rank_ = tmp;
        if (rank_[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

vector<int> buildLCPArray(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> rank_(n), lcp(n, 0);
    for (int i = 0; i < n; i++) rank_[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank_[i] == 0) { k = 0; continue; }
        int j = sa[rank_[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank_[i]] = k;
        if (k) k--;
    }
    return lcp;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 1: KMP FAILURE LINK APPLICATIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The LPS/failure array contains deep information about string structure.

 BORDER: A string's border is a prefix that is also a suffix.
   Example: "abcab" has border "ab" (prefix and suffix)
   lps[n-1] = length of longest border

 ALL BORDERS: Follow the failure chain: lps[n-1], lps[lps[n-1]-1], ...
   These give ALL border lengths in decreasing order.

 PERIOD: Length p is a period if s[i] = s[i+p] for all valid i.
   Smallest period = n - lps[n-1]

 PERIODICITY LEMMA (Fine & Wilf):
   If p and q are periods of s, and p+q <= |s|+gcd(p,q),
   then gcd(p,q) is also a period.

 PREFIX FUNCTION CHAIN:
   Count how many prefixes of s are also suffixes:
   Follow: lps[n-1] → lps[lps[n-1]-1] → ... → 0
*/

// Find ALL borders of a string (lengths of prefixes that are also suffixes)
vector<int> allBorders(const string& s) {
    auto lps = buildLPS(s);
    vector<int> borders;
    int len = lps.back();
    while (len > 0) {
        borders.push_back(len);
        len = lps[len - 1];
    }
    return borders;  // in decreasing order
}

// Find shortest period of string using KMP
int shortestPeriod(const string& s) {
    auto lps = buildLPS(s);
    return (int)s.size() - lps.back();
}

// Check if string has a period that divides its length
bool hasExactRepeatPattern(const string& s) {
    int n = s.size();
    int period = shortestPeriod(s);
    return n % period == 0;
}

// For each prefix s[0..i], find the shortest period
vector<int> allShortestPeriods(const string& s) {
    auto lps = buildLPS(s);
    int n = s.size();
    vector<int> periods(n);
    for (int i = 0; i < n; i++) {
        periods[i] = (i + 1) - lps[i];
    }
    return periods;
}

// Count prefixes of s that are also suffixes AND appear in the middle
// (i.e., at some position 1 <= j <= n-2, s[0..k-1] = s[j-k+1..j])
vector<int> prefixSuffixMiddle(const string& s) {
    int n = s.size();
    auto lps = buildLPS(s);
    // A prefix of length k appears in the middle if lps[i] == k for some i < n-1
    set<int> middleAppearances;
    for (int i = 0; i < n - 1; i++) {
        middleAppearances.insert(lps[i]);
    }

    // Get all borders (prefix-suffixes)
    vector<int> borders = allBorders(s);
    vector<int> result;
    for (int b : borders) {
        if (middleAppearances.count(b)) {
            result.push_back(b);
        }
    }
    return result;
}

void demo_kmp_advanced() {
    cout << "=== SECTION 1: KMP ADVANCED APPLICATIONS ===" << endl;

    string s = "abcabcabc";
    cout << "String: " << s << endl;

    // All borders
    auto borders = allBorders(s);
    cout << "All borders: ";
    for (int b : borders) cout << s.substr(0, b) << "(" << b << ") ";
    cout << endl;

    // Shortest period
    cout << "Shortest period: " << shortestPeriod(s) << endl;
    cout << "Has exact repeat? " << hasExactRepeatPattern(s) << endl;

    // All shortest periods for prefixes
    auto periods = allShortestPeriods(s);
    cout << "Shortest periods for each prefix: ";
    for (int p : periods) cout << p << " ";
    cout << endl;

    // CF 432D style: prefix-suffix that appears in middle
    string t = "abacaba";
    auto psm = prefixSuffixMiddle(t);
    cout << "Prefix-suffixes of '" << t << "' appearing in middle: ";
    for (int len : psm) cout << t.substr(0, len) << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: Z-FUNCTION APPLICATIONS
// ═══════════════════════════════════════════════════════════════
/*
 Z-function encodes how each suffix matches the prefix.

 APPLICATION 1: Count occurrences of pattern in text
   z-array of (pattern + $ + text), count z[i] == m

 APPLICATION 2: All periods of string
   p is a period iff z[p] + p >= n (z-value at p covers rest of string)

 APPLICATION 3: String compression
   Shortest period using z: smallest p where z[p] + p == n and n%p == 0

 APPLICATION 4: String matching with wildcards
   Special handling when pattern/text contains '*' or '?'
*/

// Count ALL occurrences of pattern in text
int countOccurrences(const string& text, const string& pattern) {
    string combined = pattern + "$" + text;
    auto z = zFunction(combined);
    int m = pattern.size();
    int count = 0;
    for (int i = m + 1; i < (int)combined.size(); i++) {
        if (z[i] == m) count++;
    }
    return count;
}

// Find ALL periods of string using Z-function
vector<int> allPeriods(const string& s) {
    int n = s.size();
    auto z = zFunction(s);
    vector<int> periods;
    for (int p = 1; p <= n; p++) {
        if (p == n || z[p] + p >= n) {
            // p is a period (possibly not exact — doesn't need to divide n)
            periods.push_back(p);
        }
    }
    return periods;
}

// String compression: find the shortest repeating unit
// "abcabcabc" → "abc" (period 3)
string compressString(const string& s) {
    int n = s.size();
    auto z = zFunction(s);
    for (int p = 1; p < n; p++) {
        if (n % p == 0 && z[p] == n - p) {
            return s.substr(0, p);
        }
    }
    return s;  // irreducible
}

// Count distinct strings in array using Z-function matching
int countDistinctByZ(vector<string>& strings) {
    sort(strings.begin(), strings.end());
    strings.erase(unique(strings.begin(), strings.end()), strings.end());
    return strings.size();
}

// For each position, find the longest prefix of s that matches starting at i
// This IS the z-function!
// But useful: find positions where ENTIRE prefix of length k matches
vector<int> positionsMatchingPrefix(const string& s, int k) {
    auto z = zFunction(s);
    vector<int> positions;
    for (int i = 1; i < (int)s.size(); i++) {
        if (z[i] >= k) positions.push_back(i);
    }
    return positions;
}

void demo_z_advanced() {
    cout << "\n=== SECTION 2: Z-FUNCTION APPLICATIONS ===" << endl;

    cout << "Count 'ab' in 'ababab': " << countOccurrences("ababab", "ab") << endl;  // 3

    string s = "abcabcabc";
    auto periods = allPeriods(s);
    cout << "All periods of '" << s << "': ";
    for (int p : periods) cout << p << " ";
    cout << endl;

    cout << "Compressed: " << compressString(s) << endl;  // abc

    cout << "Positions matching prefix 'abc' in 'abcabcabc': ";
    auto pos = positionsMatchingPrefix(s, 3);
    for (int p : pos) cout << p << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: SUFFIX ARRAY ADVANCED APPLICATIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 With Suffix Array + LCP array + Sparse Table for RMQ:
   • LCP of any two suffixes in O(1)
   • K-th smallest substring
   • Longest common substring of two strings

 SPARSE TABLE on LCP: Preprocess for range minimum queries.
   Build: O(n log n)
   Query: O(1) — minimum LCP between sa[i] and sa[j]
*/

// Sparse Table for Range Minimum Query
struct SparseTable {
    vector<vector<int>> table;
    vector<int> logs;

    void build(const vector<int>& arr) {
        int n = arr.size();
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        table.assign(LOG, vector<int>(n));
        logs.resize(n + 1);

        for (int i = 2; i <= n; i++) logs[i] = logs[i / 2] + 1;
        for (int i = 0; i < n; i++) table[0][i] = arr[i];
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                table[j][i] = min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        int k = logs[r - l + 1];
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

// LCP of suffixes starting at positions i and j in original string
struct SuffixStructure {
    string s;
    vector<int> sa, lcp, rank_;
    SparseTable st;

    void build(const string& str) {
        s = str;
        sa = buildSuffixArray(s);
        lcp = buildLCPArray(s, sa);
        int n = s.size();
        rank_.resize(n);
        for (int i = 0; i < n; i++) rank_[sa[i]] = i;
        st.build(lcp);
    }

    // LCP of suffixes starting at positions i and j
    int lcpQuery(int i, int j) {
        if (i == j) return (int)s.size() - i;
        int ri = rank_[i], rj = rank_[j];
        if (ri > rj) swap(ri, rj);
        return st.query(ri + 1, rj);
    }

    // K-th smallest distinct substring (1-indexed)
    string kthDistinctSubstring(i64 k) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            // Number of new substrings from sa[i]
            int newSubstrings = (n - sa[i]) - lcp[i];
            if (k <= newSubstrings) {
                // The k-th new substring starts at sa[i] with length lcp[i] + k
                return s.substr(sa[i], lcp[i] + k);
            }
            k -= newSubstrings;
        }
        return "";  // k exceeds total distinct substrings
    }
};

// Longest Common Substring of two strings using Suffix Array
string longestCommonSubstring(const string& s1, const string& s2) {
    // Concatenate: s1 + '#' + s2 (# not in alphabet)
    string combined = s1 + '#' + s2;
    int n1 = s1.size();
    int n = combined.size();

    auto sa = buildSuffixArray(combined);
    auto lcp = buildLCPArray(combined, sa);

    int bestLen = 0, bestPos = 0;
    for (int i = 1; i < n; i++) {
        // Check if sa[i-1] and sa[i] are from different strings
        bool prev_in_s1 = sa[i - 1] < n1;
        bool curr_in_s1 = sa[i] < n1;
        if (prev_in_s1 != curr_in_s1 && lcp[i] > bestLen) {
            bestLen = lcp[i];
            bestPos = sa[i];
        }
    }
    return combined.substr(bestPos, bestLen);
}

void demo_suffix_advanced() {
    cout << "\n=== SECTION 3: SUFFIX ARRAY ADVANCED ===" << endl;

    SuffixStructure ss;
    ss.build("banana");

    cout << "LCP of suffixes at 1 and 3: " << ss.lcpQuery(1, 3) << endl;  // "anana" vs "ana" → 3
    cout << "1st smallest distinct substring: " << ss.kthDistinctSubstring(1) << endl;  // "a"
    cout << "2nd smallest distinct substring: " << ss.kthDistinctSubstring(2) << endl;  // "an"
    cout << "3rd smallest distinct substring: " << ss.kthDistinctSubstring(3) << endl;  // "ana"

    cout << "LCS of 'abcdef' and 'xbcdyz': " << longestCommonSubstring("abcdef", "xbcdyz") << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: AUTOMATON-BASED STRING MATCHING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Build a DFA (Deterministic Finite Automaton) for pattern matching.

 States: 0 to m (pattern length)
 Transitions: For each state and character, where to go?

 DFA[state][char] = next state

 Building DFA: Use KMP's failure function to fill transitions.
   For each state j and character c:
     If pattern[j] == c: DFA[j][c] = j + 1
     Else: DFA[j][c] = DFA[lps[j-1]][c] (follow failure link)

 After building: Process text in O(n) with O(1) per character.
 Total: O(m*Σ) build + O(n) match
*/

struct PatternDFA {
    vector<vector<int>> dfa;
    int m;  // pattern length

    void build(const string& pattern) {
        m = pattern.size();
        dfa.assign(m + 1, vector<int>(26, 0));
        auto lps = buildLPS(pattern);

        // State 0: only pattern[0] goes to state 1
        dfa[0][pattern[0] - 'a'] = 1;

        // Build rest of DFA
        for (int j = 1; j <= m; j++) {
            for (int c = 0; c < 26; c++) {
                if (j < m && c == pattern[j] - 'a') {
                    dfa[j][c] = j + 1;
                } else {
                    // Follow failure link
                    int fallback = (j > 0) ? lps[j - 1] : 0;
                    dfa[j][c] = dfa[fallback][c];
                }
            }
        }
    }

    vector<int> search(const string& text) {
        vector<int> matches;
        int state = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            state = dfa[state][text[i] - 'a'];
            if (state == m) {
                matches.push_back(i - m + 1);
            }
        }
        return matches;
    }
};

void demo_dfa() {
    cout << "\n=== SECTION 4: DFA STRING MATCHING ===" << endl;
    PatternDFA dfa;
    dfa.build("aaba");
    auto matches = dfa.search("aabaacaadaabaaba");
    cout << "DFA search 'aaba' in 'aabaacaadaabaaba': ";
    for (int pos : matches) cout << pos << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: BITWISE STRING MATCHING (Shift-Or / Bitap)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The Shift-Or (Bitap) algorithm uses bitwise operations for pattern matching.
 Works for patterns up to 64 characters (fits in unsigned long long).

 IDEA:
   Maintain a bitmask R where bit j indicates:
     "the last j+1 characters of text match the first j+1 of pattern"

   For each new character c:
     R = (R << 1) | patternMask[c]

   If bit m-1 of R is 0 → match found!

 Time: O(n * ceil(m/64)), essentially O(n) for m <= 64

 ADVANTAGE: Very fast for short patterns, allows approximate matching.
*/

vector<int> shiftOrSearch(const string& text, const string& pattern) {
    vector<int> result;
    int m = pattern.size();
    if (m > 63 || m == 0) return result;  // pattern too long for single word

    unsigned long long patMask[256];
    memset(patMask, ~0ULL, sizeof(patMask));  // all 1s = "not matching"

    // Set bit j to 0 in patMask[pattern[j]] meaning "character matches at position j"
    for (int j = 0; j < m; j++) {
        patMask[(unsigned char)pattern[j]] &= ~(1ULL << j);
    }

    unsigned long long R = ~0ULL;  // all 1s initially (no match)
    unsigned long long acceptMask = 1ULL << (m - 1);

    for (int i = 0; i < (int)text.size(); i++) {
        R = (R << 1) | patMask[(unsigned char)text[i]];
        if ((R & acceptMask) == 0) {
            result.push_back(i - m + 1);
        }
    }
    return result;
}

void demo_shift_or() {
    cout << "\n=== SECTION 5: SHIFT-OR (BITAP) MATCHING ===" << endl;
    auto matches = shiftOrSearch("aabaacaadaabaaba", "aaba");
    cout << "Shift-Or search 'aaba': ";
    for (int pos : matches) cout << pos << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_kmp_advanced();
    demo_z_advanced();
    demo_suffix_advanced();
    demo_dfa();
    demo_shift_or();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 5 Advanced String Algorithm topics covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  CF 432D  — Prefixes and Suffixes (KMP chain)                   ║
║  CF 126B  — Password (KMP prefix-suffix in middle)              ║
║  CF 526D  — Om Nom and Necklaces (Z-function + periods)         ║
║  CF 182D  — Common Divisors (string periodicity)                ║
║  CSES     — Substring Order I (K-th substring via SA)           ║
║  CSES     — Substring Order II                                  ║
║  CSES     — Finding Borders (KMP failure chain)                 ║
║  CSES     — Finding Periods (Z-function periods)                ║
║  CSES     — Minimal Rotation                                    ║
║  SPOJ LCS — Longest Common Substring (SA + LCP)                ║
║  SPOJ LCS2 — LCS of multiple strings                           ║
║  SPOJ DISUBSTR — Count distinct substrings (SA + LCP)          ║
╚══════════════════════════════════════════════════════════════════╝
*/

