/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 10 — ADVANCED COMPETITIVE STRING TRICKS                       ║
║     From Zero to Grandmaster — Competition Secrets                         ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Substring Counting Tricks (using SA + LCP)
 2. Contribution Counting (Character → All Substrings)
 3. Lexicographic Ranking (Rank of a string among permutations)
 4. String Periodicity (Period Lemma, Borders, Weak Period)
 5. Border Array (All borders efficiently)
 6. Minimal String Rotation (Booth's revisited + applications)
 7. Failure Links Usage (KMP automaton advanced tricks)
 8. String Combinatorics (Counting palindromes, distinct substrings)

COMPETITIVE PROGRAMMING MINDSET:
─────────────────────────────────
 These tricks appear in Codeforces Div1 C-E, AtCoder ARC/AGC, and IOI.
 They require COMBINING multiple algorithms creatively.
 Master these and you'll handle 2200+ rated problems on strings.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <stack>
#include <cassert>
using namespace std;
using i64 = long long;

// ─── HELPERS ───
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
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
        rank_ = tmp;
        if (rank_[sa[n-1]] == n-1) break;
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
// SECTION 1: SUBSTRING COUNTING TRICKS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 TOTAL SUBSTRINGS of string of length n: n*(n+1)/2

 DISTINCT SUBSTRINGS using SA + LCP:
   Total - sum(LCP[i]) = n*(n+1)/2 - Σ LCP[i]
   Each suffix sa[i] contributes (n - sa[i]) substrings
   But LCP[i] of them overlap with sa[i-1]
   So new substrings from sa[i] = (n - sa[i]) - LCP[i]

 K-TH SMALLEST DISTINCT SUBSTRING:
   Walk through suffix array, accumulate new substrings.
   When cumulative count >= K, extract the substring.

 COUNT OCCURRENCES OF A SPECIFIC SUBSTRING:
   Binary search in suffix array for the first and last occurrence.
   Count = last - first + 1
*/

// Count distinct substrings
i64 countDistinctSubstrings(const string& s) {
    int n = s.size();
    auto sa = buildSuffixArray(s);
    auto lcp = buildLCPArray(s, sa);
    i64 total = (i64)n * (n + 1) / 2;
    for (int x : lcp) total -= x;
    return total;
}

// K-th lexicographically smallest distinct substring (1-indexed)
string kthSmallestSubstring(const string& s, i64 k) {
    int n = s.size();
    auto sa = buildSuffixArray(s);
    auto lcp = buildLCPArray(s, sa);

    for (int i = 0; i < n; i++) {
        i64 newSubs = (n - sa[i]) - lcp[i];
        if (k <= newSubs) {
            return s.substr(sa[i], lcp[i] + k);
        }
        k -= newSubs;
    }
    return "";  // k too large
}

// Count occurrences of pattern using suffix array
int countPatternOccurrences(const string& s, const vector<int>& sa, const string& pattern) {
    int n = s.size(), m = pattern.size();
    // Lower bound
    int lo = 0, hi = n - 1, first = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], min(m, n - sa[mid]), pattern) >= 0)
            first = mid, hi = mid - 1;
        else
            lo = mid + 1;
    }
    // Upper bound
    lo = first; hi = n - 1;
    int last = first - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], min(m, n - sa[mid]), pattern) <= 0)
            last = mid, lo = mid + 1;
        else
            hi = mid - 1;
    }
    return max(0, last - first + 1);
}

void demo_substring_counting() {
    cout << "=== SECTION 1: SUBSTRING COUNTING TRICKS ===" << endl;
    string s = "banana";
    cout << "Distinct substrings of '" << s << "': " << countDistinctSubstrings(s) << endl;
    cout << "1st smallest: " << kthSmallestSubstring(s, 1) << endl;  // a
    cout << "2nd smallest: " << kthSmallestSubstring(s, 2) << endl;  // an
    cout << "3rd smallest: " << kthSmallestSubstring(s, 3) << endl;  // ana

    auto sa = buildSuffixArray(s);
    cout << "Occurrences of 'ana': " << countPatternOccurrences(s, sa, "ana") << endl;  // 2
    cout << "Occurrences of 'ban': " << countPatternOccurrences(s, sa, "ban") << endl;  // 1
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: CONTRIBUTION COUNTING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Instead of iterating over all substrings, count each CHARACTER's
 contribution to the answer.

 PRINCIPLE: For character at position i:
   It appears in substrings starting at [0..i] and ending at [i..n-1]
   Number of substrings containing s[i] = (i + 1) * (n - i)

 APPLICATION 1: Sum of ASCII values across all substrings
   For each position i: contribution = s[i] * (i + 1) * (n - i)

 APPLICATION 2: Count total characters across all substrings
   Answer = Σ (i + 1) * (n - i)

 APPLICATION 3: For each character c, count substrings where c appears
   Sum of (i + 1) * (n - i) for all positions where s[i] == c

 APPLICATION 4: Sum of unique characters across all substrings
   For each character c, find substrings where c appears.
   Use "contribution of distinct" technique:
   For position i with character c, find previous occurrence of c (prev)
   and next occurrence of c (next).
   Substrings where s[i] is the first occurrence of c among positions:
   (i - prev) * (next - i)
*/

// Sum of ASCII values of all substrings
i64 sumAsciiAllSubstrings(const string& s) {
    int n = s.size();
    i64 total = 0;
    for (int i = 0; i < n; i++) {
        total += (i64)s[i] * (i + 1) * (n - i);
    }
    return total;
}

// Count substrings containing character c at least once
i64 countSubstringsContaining(const string& s, char c) {
    int n = s.size();
    i64 total = (i64)n * (n + 1) / 2;

    // Subtract substrings NOT containing c
    int gap = 0;  // length of current gap without c
    i64 without = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] != c) {
            gap++;
        } else {
            without += (i64)gap * (gap + 1) / 2;
            gap = 0;
        }
    }
    without += (i64)gap * (gap + 1) / 2;

    return total - without;
}

// Sum of count of unique characters across all substrings
// For each position i, count how many substrings have s[i] as a "new" character
// (first occurrence from left within the substring)
i64 uniqueCharContribution(const string& s) {
    int n = s.size();
    i64 total = 0;

    // For each character, find previous and next occurrence
    int lastOccurrence[26];
    fill(lastOccurrence, lastOccurrence + 26, -1);

    // Need next occurrence too
    vector<int> nextOcc(n, n);
    int nextOccArr[26];
    fill(nextOccArr, nextOccArr + 26, n);
    for (int i = n - 1; i >= 0; i--) {
        nextOcc[i] = nextOccArr[s[i] - 'a'];
        nextOccArr[s[i] - 'a'] = i;
    }

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        int prev = lastOccurrence[c];
        int next = nextOcc[i];

        // s[i] contributes to substrings [l..r] where:
        // l is in (prev, i] and r is in [i, next)
        // Number of such substrings = (i - prev) * (next - i)
        total += (i64)(i - prev) * (next - i);

        lastOccurrence[c] = i;
    }
    return total;
}

void demo_contribution() {
    cout << "\n=== SECTION 2: CONTRIBUTION COUNTING ===" << endl;
    string s = "abc";
    cout << "Sum ASCII of all substrings of 'abc': " << sumAsciiAllSubstrings(s) << endl;
    cout << "Substrings containing 'b' in 'abcb': " << countSubstringsContaining("abcb", 'b') << endl;
    cout << "Sum unique chars across all substrings of 'abc': " << uniqueCharContribution("abc") << endl;
    // Substrings: a(1), b(1), c(1), ab(2), bc(2), abc(3) → 1+1+1+2+2+3 = 10
    cout << "Sum unique chars across all substrings of 'aba': " << uniqueCharContribution("aba") << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: LEXICOGRAPHIC RANKING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Given a string, find its rank among all permutations of its characters
 in lexicographic order.

 APPROACH:
   For each position i from left to right:
     Count how many characters to the right of i are smaller than s[i].
     Those characters, if placed at position i, would give a smaller permutation.
     Multiply by factorial of remaining positions (adjusting for duplicates).

 WITH DUPLICATES:
   rank = Σ (count_smaller * (n-i-1)! / Π freq[c]!)

 MODULAR ARITHMETIC needed for large strings.

 INVERSE PROBLEM: Given rank, find the string (unranking).
*/

// Factorial with modular inverse (for ranking with mod)
const i64 MOD = 1e9 + 7;

i64 power(i64 base, i64 exp, i64 mod) {
    i64 result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

i64 modInverse(i64 a, i64 mod) { return power(a, mod - 2, mod); }

// Rank of string among all permutations (1-indexed, with duplicates)
i64 lexicographicRank(const string& s) {
    int n = s.size();
    // Precompute factorials
    vector<i64> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;

    int freq[26] = {0};
    for (char c : s) freq[c - 'a']++;

    i64 rank = 0;

    for (int i = 0; i < n; i++) {
        // Count characters smaller than s[i] that are still available
        int smaller = 0;
        for (int c = 0; c < s[i] - 'a'; c++) {
            smaller += freq[c];
        }

        // Permutations = smaller * (n-i-1)! / (prod of freq[c]!)
        i64 perms = (i64)smaller % MOD * fact[n - i - 1] % MOD;

        // Divide by product of factorials of remaining frequencies
        i64 denom = 1;
        for (int c = 0; c < 26; c++) {
            denom = denom * fact[freq[c]] % MOD;
        }
        perms = perms % MOD * modInverse(denom, MOD) % MOD;

        rank = (rank + perms) % MOD;

        // Use current character
        freq[s[i] - 'a']--;
    }

    return (rank + 1) % MOD;  // 1-indexed
}

void demo_ranking() {
    cout << "\n=== SECTION 3: LEXICOGRAPHIC RANKING ===" << endl;
    cout << "Rank of 'abc': " << lexicographicRank("abc") << endl;  // 1
    cout << "Rank of 'bac': " << lexicographicRank("bac") << endl;  // 3
    cout << "Rank of 'cba': " << lexicographicRank("cba") << endl;  // 6
    cout << "Rank of 'baa': " << lexicographicRank("baa") << endl;  // 2 (aab=1, aba=2... wait)
    // "aab"=1, "aba"=2, "baa"=3
    cout << "Rank of 'aab': " << lexicographicRank("aab") << endl;  // 1
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: STRING PERIODICITY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 PERIOD: p is a period of s if s[i] = s[i+p] for all 0 ≤ i ≤ n-p-1.
   The string "repeats" with period p (possibly with incomplete last copy).
   Smallest period = n - lps[n-1] (from KMP).

 BORDER: A border is a string that is both a prefix and suffix.
   Longest border length = lps[n-1].
   All borders: follow lps chain.

 PERIOD LEMMA (Fine & Wilf):
   If p and q are periods of s, and p + q ≤ n + gcd(p,q),
   then gcd(p,q) is also a period of s.

   CONSEQUENCE: If two short periods exist, an even shorter one must exist.

 WEAK PERIOD: p is a weak period if s[i] = s[i+p] for all valid i,
   but p doesn't necessarily divide n.

 CRITICAL FACTORIZATION THEOREM:
   Every string has a critical position where local period = global period.

 APPLICATION: Determine if string is "primitive" (cannot be written as t^k for k≥2)
   Primitive iff smallest period = n (or equivalently, lps[n-1] = 0 or n % period != 0)
*/

// All periods of a string
vector<int> allPeriods(const string& s) {
    int n = s.size();
    auto z = zFunction(s);
    vector<int> periods;
    for (int p = 1; p <= n; p++) {
        bool isPeriod = true;
        // Check: for this period p, z[p] should be >= n - p (or p == n)
        if (p == n) { periods.push_back(p); continue; }
        if (z[p] >= n - p) periods.push_back(p);
    }
    return periods;
}

// Check if string is primitive (not a power of shorter string)
bool isPrimitive(const string& s) {
    int n = s.size();
    auto lps = buildLPS(s);
    int period = n - lps[n - 1];
    return (n % period != 0) || period == n;
}

// Find all periods that exactly divide n (exact repetition periods)
vector<int> exactPeriods(const string& s) {
    int n = s.size();
    auto lps = buildLPS(s);
    int smallestPeriod = n - lps[n - 1];
    vector<int> result;
    for (int p = smallestPeriod; p <= n; p += smallestPeriod) {
        if (n % p == 0) {
            result.push_back(p);
        }
    }
    return result;
}

// Power of a string: if s = t^k, return k (and t)
pair<int, string> stringPower(const string& s) {
    int n = s.size();
    auto lps = buildLPS(s);
    int period = n - lps[n - 1];
    if (n % period == 0) {
        return {n / period, s.substr(0, period)};
    }
    return {1, s};
}

void demo_periodicity() {
    cout << "\n=== SECTION 4: STRING PERIODICITY ===" << endl;
    string s = "abcabcabc";
    auto periods = allPeriods(s);
    cout << "All periods of '" << s << "': ";
    for (int p : periods) cout << p << " ";
    cout << endl;

    cout << "Is 'abcabc' primitive? " << isPrimitive("abcabc") << endl;  // 0 (no, period 3 doesn't divide 7... actually 7%3!=0, so it IS primitive)
    cout << "Is 'abcabcabc' primitive? " << isPrimitive("abcabcabc") << endl;  // 0 (9%3==0)
    cout << "Is 'abcd' primitive? " << isPrimitive("abcd") << endl;  // 1

    auto [k, t] = stringPower("abcabcabc");
    cout << "'" << "abcabcabc" << "' = '" << t << "'^" << k << endl;

    auto exact = exactPeriods("abcabcabc");
    cout << "Exact periods: ";
    for (int p : exact) cout << p << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: BORDER ARRAY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The BORDER ARRAY is essentially the KMP failure function (LPS array).
 border[i] = length of longest proper prefix of s[0..i] that is also a suffix.

 APPLICATIONS:
   • All borders of the full string: follow chain from border[n-1]
   • Count of border lengths at each position
   • Number of strings that appear as both prefix and suffix
   • Autocorrelation of the string

 BORDER CHAIN: Starting from border[n-1], follow border[border[n-1]-1], etc.
   This gives all border lengths in decreasing order.
   Number of borders = length of this chain.

 COUNTING PREFIX-SUFFIXES THAT ALSO APPEAR IN THE MIDDLE:
   A border of length k appears in the middle if border[i] == k for some i < n-1.
   This is CF 432D "Prefixes and Suffixes".
*/

// Count for each border length, how many times it appears as a prefix-suffix
vector<pair<int,int>> borderLengthsWithCount(const string& s) {
    int n = s.size();
    auto lps = buildLPS(s);

    // Count how many positions have each lps value
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) cnt[lps[i]]++;

    // Propagate: if lps[j] = k, then borders of length lps[k-1] also get this count
    // Actually, sum up along the chain
    // cnt[k] = number of positions where border length is exactly k
    // But a border of length k implies borders of length lps[k-1], lps[lps[k-1]-1], etc.

    // For the full string, get all border lengths and their occurrence count
    vector<pair<int,int>> result;
    int len = lps[n - 1];
    while (len > 0) {
        // Count positions where this border length appears
        result.push_back({len, cnt[len]});
        len = lps[len - 1];
    }
    return result;
}

void demo_border_array() {
    cout << "\n=== SECTION 5: BORDER ARRAY ===" << endl;
    string s = "abacaba";
    auto lps = buildLPS(s);
    cout << "Border array of '" << s << "': ";
    for (int x : lps) cout << x << " ";
    cout << endl;

    // All borders of full string
    cout << "All borders: ";
    int len = lps.back();
    while (len > 0) {
        cout << s.substr(0, len) << "(" << len << ") ";
        len = lps[len - 1];
    }
    cout << endl;

    auto info = borderLengthsWithCount(s);
    cout << "Border lengths with counts: ";
    for (auto [l, c] : info) cout << l << ":" << c << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: MINIMAL STRING ROTATION (Applications)
// ═══════════════════════════════════════════════════════════════
/*
 Booth's algorithm finds the starting index of the minimum rotation in O(n).
 (Implementation in Chapter 06)

 APPLICATIONS:
   1. Circular string comparison: Two circular strings are equal iff
      their minimum rotations are equal.
   2. Necklace equivalence: Necklaces (circular sequences) are grouped
      by their canonical form (minimum rotation).
   3. Count distinct necklaces of length n with k colors.
*/

int boothMinRotation(const string& s) {
    int n = s.size();
    string ss = s + s;
    vector<int> f(2 * n, -1);
    int k = 0;
    for (int j = 1; j < 2 * n; j++) {
        int i = f[j - 1 - k];
        while (i != -1 && ss[j] != ss[k + i + 1]) {
            if (ss[j] < ss[k + i + 1]) k = j - i - 1;
            i = f[i];
        }
        if (i == -1 && ss[j] != ss[k + i + 1]) {
            if (ss[j] < ss[k + i + 1]) k = j;
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}

string canonicalRotation(const string& s) {
    int k = boothMinRotation(s);
    return s.substr(k) + s.substr(0, k);
}

// Check if two strings are rotations of each other
bool areRotations(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) return false;
    return canonicalRotation(s1) == canonicalRotation(s2);
}

// Count distinct rotations of a string
int countDistinctRotations(const string& s) {
    int n = s.size();
    set<string> rotations;
    for (int i = 0; i < n; i++) {
        rotations.insert(s.substr(i) + s.substr(0, i));
    }
    return rotations.size();
}

void demo_min_rotation() {
    cout << "\n=== SECTION 6: MINIMAL ROTATION ===" << endl;
    cout << "Canonical of 'bca': " << canonicalRotation("bca") << endl;  // abc
    cout << "Canonical of 'cab': " << canonicalRotation("cab") << endl;  // abc
    cout << "Are 'bca' and 'cab' rotations? " << areRotations("bca", "cab") << endl;  // 1
    cout << "Distinct rotations of 'aab': " << countDistinctRotations("aab") << endl;  // 3
    cout << "Distinct rotations of 'aaa': " << countDistinctRotations("aaa") << endl;  // 1
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: FAILURE LINKS USAGE (Advanced KMP Tricks)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The KMP failure function creates a TREE structure (failure tree / border tree).
 Each node i has parent lps[i] (or -1 if lps[i] == 0, parent is root).

 FAILURE TREE PROPERTIES:
   • Node i represents prefix s[0..i]
   • Edge from i to lps[i]: "the longest border of prefix i"
   • The root (node 0 / virtual root) has lps = -1
   • Subtree of node i: all prefixes whose "longest border chain" passes through i

 APPLICATIONS:
   1. For each prefix, count how many times it appears as a prefix-suffix
      → DFS on failure tree, count subtree sizes
   2. Count total occurrences of each prefix in the string
      → The failure tree encodes this information
   3. Matching in multiple texts: reuse KMP automaton
*/

// Build failure tree and count occurrences of each prefix
vector<int> prefixOccurrenceCounts(const string& s) {
    int n = s.size();
    auto lps = buildLPS(s);

    // Build failure tree
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; i++) {
        // Edge from lps[i] to i (or handle lps[i] == 0 as root's child)
        tree[lps[i]].push_back(i);
    }
    // Node 0's parent is virtual root, but we handle it separately

    // DFS to count subtree sizes (= number of positions where this prefix appears as border)
    vector<int> cnt(n, 1);  // each prefix appears at least once (itself)

    // Process in reverse order (children before parents)
    // Actually, we need topological order: nodes with larger lps values first
    // Simplest: process from n-1 down to 0
    for (int i = n - 1; i > 0; i--) {
        cnt[lps[i]] += cnt[i];  // this is a simpler way: propagate up the failure chain
    }

    // Wait, this counts how many times prefix of length (i+1) appears.
    // Actually cnt[i] = how many positions j where s[0..i] is a suffix of s[0..j]
    return cnt;
}

void demo_failure_links() {
    cout << "\n=== SECTION 7: FAILURE LINKS USAGE ===" << endl;
    string s = "abacaba";
    auto cnt = prefixOccurrenceCounts(s);
    cout << "Prefix occurrence counts for '" << s << "':" << endl;
    for (int i = 0; i < (int)s.size(); i++) {
        cout << "  '" << s.substr(0, i + 1) << "' appears " << cnt[i] << " times as border" << endl;
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: STRING COMBINATORICS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 COUNTING PROBLEMS on strings are common in competitive programming.

 1. COUNT DISTINCT SUBSTRINGS → SA + LCP (Section 1)

 2. COUNT PALINDROMIC SUBSTRINGS → Manacher O(n) (Chapter 06)

 3. COUNT DISTINCT PALINDROMIC SUBSTRINGS → Eertree O(n) (Chapter 11)

 4. NUMBER OF SUBSEQUENCES OF LENGTH K
    dp[i][j] = number of distinct subsequences of length j using first i chars

 5. TOTAL NUMBER OF DISTINCT SUBSEQUENCES (including empty)
    dp[i] = total distinct subsequences of s[0..i-1]
    dp[0] = 1 (empty subsequence)
    dp[i] = 2 * dp[i-1] - dp[lastOccurrence[s[i-1]] - 1]

 6. BINOMIAL COEFFICIENT IN STRINGS
    "How many subsets of k positions form a palindrome?"
    Usually involves bitmask DP or contribution counting.
*/

// Count distinct subsequences (all lengths, including empty)
i64 countDistinctSubsequences(const string& s) {
    int n = s.size();
    vector<i64> dp(n + 1);
    dp[0] = 1;  // empty subsequence

    int lastOcc[26];
    fill(lastOcc, lastOcc + 26, -1);

    for (int i = 1; i <= n; i++) {
        dp[i] = 2 * dp[i - 1] % MOD;
        int c = s[i - 1] - 'a';
        if (lastOcc[c] != -1) {
            dp[i] = (dp[i] - dp[lastOcc[c] - 1] + MOD) % MOD;
        }
        lastOcc[c] = i;
    }
    return dp[n];  // includes empty subsequence
}

// Number of distinct subsequences of exactly length K
i64 countSubsequencesOfLengthK(const string& s, int K) {
    int n = s.size();
    if (K > n) return 0;

    // dp[j] = number of distinct subsequences of length j ending at or before current position
    vector<i64> dp(K + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        // Process right to left to avoid counting same char twice
        for (int j = min(i + 1, K); j >= 1; j--) {
            dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }
    return dp[K];
}

// Number of binary strings of length n with no two consecutive 1s
i64 countNoConsecutiveOnes(int n) {
    if (n == 0) return 1;
    i64 a = 1, b = 1;  // a = ending with 0, b = ending with 1
    for (int i = 2; i <= n; i++) {
        i64 na = (a + b) % MOD;
        i64 nb = a;
        a = na;
        b = nb;
    }
    return (a + b) % MOD;
}

void demo_combinatorics() {
    cout << "\n=== SECTION 8: STRING COMBINATORICS ===" << endl;
    cout << "Distinct subsequences of 'abc': " << countDistinctSubsequences("abc") << endl;  // 8 (including empty)
    cout << "Distinct subsequences of 'aab': " << countDistinctSubsequences("aab") << endl;  // 7
    cout << "Subsequences of length 2 in 'abcd': " << countSubsequencesOfLengthK("abcd", 2) << endl;  // 6
    cout << "Binary strings len 5, no consec 1s: " << countNoConsecutiveOnes(5) << endl;  // 13
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_substring_counting();
    demo_contribution();
    demo_ranking();
    demo_periodicity();
    demo_border_array();
    demo_min_rotation();
    demo_failure_links();
    demo_combinatorics();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 8 Advanced Competitive Tricks covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  CSES — Substring Order I / II (K-th substring)                ║
║  CSES — Finding Borders                                         ║
║  CSES — Finding Periods                                         ║
║  CSES — Minimal Rotation                                        ║
║  CSES — Distinct Substrings (SA + LCP)                          ║
║  CF 432D — Prefixes and Suffixes                                ║
║  CF 526D — Om Nom and Necklaces                                ║
║  CF 1466F — Euclid's Nightmare (string periodicity)            ║
║  CF 25E — Test (shortest superstring)                           ║
║  LeetCode 828 — Count Unique Characters of All Substrings       ║
║  LeetCode 940 — Distinct Subsequences II                        ║
║  LeetCode 899 — Orderly Queue (rotation + sorting)             ║
║  AtCoder ABC 241E — Putting Candies (string periodicity)       ║
╚══════════════════════════════════════════════════════════════════╝
*/

