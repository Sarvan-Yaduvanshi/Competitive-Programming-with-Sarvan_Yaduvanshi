/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 06 — PATTERN MATCHING ALGORITHMS                              ║
║     From Zero to Grandmaster — The Core Algorithms                         ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. KMP Algorithm (Knuth-Morris-Pratt)
 2. Z-Algorithm
 3. Manacher's Algorithm (Longest Palindromic Substring in O(n))
 4. Suffix Array (O(n log²n) construction)
 5. LCP Array (Kasai's Algorithm)
 6. Suffix Automaton (SAM)
 7. Aho-Corasick (Multi-pattern matching)
 8. Booth's Algorithm (Minimum String Rotation)
 9. Lyndon Decomposition (Duval's Algorithm)

COMPARISON TABLE:
─────────────────────────────────────────────────────
 Algorithm     │ Purpose                    │ Time
─────────────────────────────────────────────────────
 KMP           │ Single pattern match       │ O(n+m)
 Z-Algorithm   │ Single pattern match       │ O(n+m)
 Rabin-Karp    │ Single/multi pattern       │ O(n+m) avg
 Manacher      │ All palindromes            │ O(n)
 Suffix Array  │ All substrings sorted      │ O(n log²n)
 LCP (Kasai)   │ Longest common prefix      │ O(n)
 Suffix Auto.  │ All substrings DAG         │ O(n)
 Aho-Corasick  │ Multi-pattern match        │ O(n+m+z)
 Booth's       │ Min rotation               │ O(n)
 Lyndon        │ String factorization       │ O(n)
─────────────────────────────────────────────────────
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cassert>
#include <cstring>
#include <numeric>
using namespace std;
using i64 = long long;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: KMP ALGORITHM (Knuth-Morris-Pratt)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 KMP avoids re-comparing characters by using the FAILURE FUNCTION (LPS array).

 LPS (Longest Proper Prefix which is also Suffix):
   lps[i] = length of the longest proper prefix of pattern[0..i]
            which is also a suffix of pattern[0..i]

 Example: pattern = "ABCABD"
   lps = [0, 0, 0, 1, 2, 0]
   "ABCAB" → longest prefix=suffix = "AB" → lps[4] = 2

 HOW KMP WORKS:
   1. Build lps[] array in O(m) — preprocessing
   2. Match text against pattern:
      - If mismatch at pattern[j], jump j = lps[j-1] (instead of j = 0)
      - Never go backwards in text!

 WHY O(n+m)?
   Text pointer i never decreases → moves at most n times
   Pattern pointer j never increases more than i → total O(n+m)

 APPLICATIONS:
   • Single pattern matching
   • Count occurrences of pattern
   • String periodicity: period = n - lps[n-1]
   • Pattern appears as prefix-suffix → lps chain
*/

// Build LPS (failure function) array — O(m)
vector<int> buildLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;  // length of previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];  // don't increment i
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP Search — returns all occurrence positions
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size(), m = pattern.size();
    if (m > n) return result;

    vector<int> lps = buildLPS(pattern);
    int i = 0, j = 0;  // i for text, j for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            result.push_back(i - j);  // match found
            j = lps[j - 1];           // continue searching
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return result;
}

// Count occurrences of pattern in text
int kmpCount(const string& text, const string& pattern) {
    return kmpSearch(text, pattern).size();
}

void demo_kmp() {
    cout << "=== SECTION 1: KMP ALGORITHM ===" << endl;
    string text = "AABAACAADAABAABA";
    string pattern = "AABA";

    vector<int> lps = buildLPS(pattern);
    cout << "LPS of '" << pattern << "': ";
    for (int x : lps) cout << x << " ";
    cout << endl;

    auto matches = kmpSearch(text, pattern);
    cout << "Pattern '" << pattern << "' found at: ";
    for (int pos : matches) cout << pos << " ";
    cout << endl;

    cout << "Count: " << kmpCount(text, pattern) << endl;

    // Periodicity: string period = n - lps[n-1]
    string s = "abcabcabc";
    auto lps2 = buildLPS(s);
    int period = s.size() - lps2.back();
    cout << "Period of '" << s << "': " << period << endl;  // 3
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: Z-ALGORITHM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 z[i] = length of the longest substring starting at position i
        that matches a PREFIX of the string.

 z[0] is undefined (or set to 0 or n by convention).

 Example: s = "aabxaab"
   z = [0, 1, 0, 0, 3, 1, 0]
   z[4] = 3 because s[4..6] = "aab" = prefix "aab"

 PATTERN MATCHING WITH Z:
   Concatenate: str = pattern + '$' + text
   Build Z-array. Wherever z[i] == m, match found at i - m - 1 in text.
   The '$' is a sentinel character not in the alphabet.

 HOW Z WORKS:
   Maintain [l, r] = rightmost z-box found so far.
   For each i:
   - If i > r: compute z[i] naively, update [l,r]
   - If i <= r: z[i] = min(z[i-l], r-i+1), then extend if possible

 Time: O(n) — each character is visited at most twice.
*/

vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// Z-based pattern matching
vector<int> zSearch(const string& text, const string& pattern) {
    string combined = pattern + "$" + text;
    vector<int> z = zFunction(combined);
    int m = pattern.size();

    vector<int> result;
    for (int i = m + 1; i < (int)combined.size(); i++) {
        if (z[i] == m) {
            result.push_back(i - m - 1);
        }
    }
    return result;
}

void demo_z_algorithm() {
    cout << "\n=== SECTION 2: Z-ALGORITHM ===" << endl;
    string s = "aabxaab";
    auto z = zFunction(s);
    cout << "Z-array of '" << s << "': ";
    for (int x : z) cout << x << " ";
    cout << endl;

    auto matches = zSearch("AABAACAADAABAABA", "AABA");
    cout << "Pattern 'AABA' found at: ";
    for (int pos : matches) cout << pos << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: MANACHER'S ALGORITHM
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Finds ALL palindromic substrings in O(n) time.

 IDEA: Transform string to handle odd/even uniformly.
   "abc" → "^#a#b#c#$"
   Now all palindromes are odd-length in the transformed string.

 p[i] = radius of palindrome centered at position i in transformed string.

 ALGORITHM:
   Maintain: C = center of rightmost palindrome, R = right boundary
   For each i:
   - mirror = 2*C - i
   - If i < R: p[i] = min(p[mirror], R - i)
   - Expand while chars match
   - If i + p[i] > R: update C = i, R = i + p[i]

 RESULT:
   p[i] in transformed string = length of palindrome in original string.

 Time: O(n), Space: O(n)
*/

// Returns array where d1[i] = number of odd-length palindromes centered at i
// d1[i] = radius (half-length) of longest odd palindrome centered at i
vector<int> manacherOdd(const string& s) {
    int n = s.size();
    vector<int> d1(n, 0);  // d1[i] = max k such that s[i-k..i+k] is palindrome
    int l = 0, r = -1;     // [l, r] = rightmost palindrome boundary

    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 0 : min(d1[l + r - i], r - i);
        while (i - k - 1 >= 0 && i + k + 1 < n && s[i - k - 1] == s[i + k + 1]) {
            k++;
        }
        d1[i] = k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return d1;
}

// d2[i] = max k such that s[i-k..i+k-1] is palindrome (even-length)
vector<int> manacherEven(const string& s) {
    int n = s.size();
    vector<int> d2(n, 0);
    int l = 0, r = -1;

    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d2;
}

// Combined: find longest palindromic substring
string longestPalindromeManacher(const string& s) {
    if (s.empty()) return "";

    // Transform: insert '#' between chars and at boundaries
    string t = "^";
    for (char c : s) {
        t += '#';
        t += c;
    }
    t += "#$";

    int n = t.size();
    vector<int> p(n, 0);
    int c = 0, r = 0;  // center and right boundary

    for (int i = 1; i < n - 1; i++) {
        int mirror = 2 * c - i;
        if (i < r) p[i] = min(r - i, p[mirror]);
        while (t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }

    // Find maximum
    int maxLen = 0, center = 0;
    for (int i = 1; i < n - 1; i++) {
        if (p[i] > maxLen) {
            maxLen = p[i];
            center = i;
        }
    }

    int start = (center - maxLen - 1) / 2;  // convert back to original index
    return s.substr(start, maxLen);
}

// Count total palindromic substrings using Manacher — O(n)
long long countAllPalindromes(const string& s) {
    auto d1 = manacherOdd(s);
    auto d2 = manacherEven(s);
    long long count = 0;
    for (int x : d1) count += x + 1;  // +1 for the single char
    for (int x : d2) count += x;
    return count;
}

void demo_manacher() {
    cout << "\n=== SECTION 3: MANACHER'S ALGORITHM ===" << endl;
    cout << "Longest palindrome in 'babad': " << longestPalindromeManacher("babad") << endl;
    cout << "Longest palindrome in 'cbbd': " << longestPalindromeManacher("cbbd") << endl;
    cout << "Longest palindrome in 'abacaba': " << longestPalindromeManacher("abacaba") << endl;
    cout << "Total palindromes in 'aaa': " << countAllPalindromes("aaa") << endl;  // 6
    cout << "Total palindromes in 'abc': " << countAllPalindromes("abc") << endl;  // 3
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: SUFFIX ARRAY
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A SUFFIX ARRAY is a sorted array of all suffixes of a string.
 sa[i] = starting index of the i-th smallest suffix.

 Example: s = "banana"
   Suffixes: banana, anana, nana, ana, na, a
   Sorted:   a, ana, anana, banana, na, nana
   sa = [5, 3, 1, 0, 4, 2]

 CONSTRUCTION:
   Naive: sort all suffixes → O(n² log n)
   Prefix doubling: O(n log²n) — practical and common in CP
   SA-IS / DC3: O(n) — complex but optimal

 APPLICATIONS:
   • Find pattern in text: binary search on suffix array → O(m log n)
   • Count distinct substrings: n*(n+1)/2 - sum(lcp[i])
   • Longest repeated substring: max(lcp[i])
   • Longest common substring of two strings

 WHY SUFFIX ARRAY OVER SUFFIX TREE?
   • Same power, less memory (O(n) vs O(n*Σ))
   • Cache-friendly (array vs pointer-based tree)
   • Easier to implement
*/

// Suffix Array construction — O(n log²n) prefix doubling
vector<int> buildSuffixArray(const string& s) {
    int n = s.size();
    vector<int> sa(n), rank_(n), tmp(n);

    // Initialize
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rank_[i] = s[i];

    for (int k = 1; k < n; k <<= 1) {
        // Compare (rank[i], rank[i+k]) pairs
        auto cmp = [&](int a, int b) {
            if (rank_[a] != rank_[b]) return rank_[a] < rank_[b];
            int ra = (a + k < n) ? rank_[a + k] : -1;
            int rb = (b + k < n) ? rank_[b + k] : -1;
            return ra < rb;
        };

        sort(sa.begin(), sa.end(), cmp);

        // Rebuild ranks
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank_ = tmp;

        // Early termination if all ranks are unique
        if (rank_[sa[n - 1]] == n - 1) break;
    }
    return sa;
}

// Pattern search using suffix array — O(m log n)
vector<int> searchSA(const string& s, const vector<int>& sa, const string& pattern) {
    int n = s.size(), m = pattern.size();
    vector<int> result;

    // Binary search for lower bound
    int lo = 0, hi = n - 1, first = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], m, pattern) >= 0) {
            first = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    // Binary search for upper bound
    lo = first;
    hi = n - 1;
    int last = first - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (s.compare(sa[mid], m, pattern) <= 0) {
            last = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    for (int i = first; i <= last; i++) {
        result.push_back(sa[i]);
    }
    sort(result.begin(), result.end());
    return result;
}

void demo_suffix_array() {
    cout << "\n=== SECTION 4: SUFFIX ARRAY ===" << endl;
    string s = "banana";
    auto sa = buildSuffixArray(s);
    cout << "Suffix Array of '" << s << "': ";
    for (int x : sa) cout << x << " ";
    cout << endl;

    cout << "Suffixes in sorted order:" << endl;
    for (int i : sa) cout << "  " << i << ": " << s.substr(i) << endl;

    // Pattern search
    auto matches = searchSA(s, sa, "ana");
    cout << "Pattern 'ana' found at: ";
    for (int pos : matches) cout << pos << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: LCP ARRAY (Kasai's Algorithm)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 LCP[i] = length of the Longest Common Prefix between
           sa[i] and sa[i-1] (consecutive suffixes in sorted order).
 LCP[0] = 0 by convention.

 KASAI'S ALGORITHM:
   Key insight: If LCP(sa[rank[i]-1], sa[rank[i]]) = k,
   then LCP(sa[rank[i+1]-1], sa[rank[i+1]]) >= k - 1

   This means we can compute LCP in O(n) by processing suffixes
   in original order (not sorted order).

 APPLICATIONS:
   • Longest repeated substring = max(lcp[i])
   • Count distinct substrings = n*(n+1)/2 - sum(lcp[i])
   • Longest common prefix of any two suffixes: range minimum query on LCP
*/

vector<int> buildLCPArray(const string& s, const vector<int>& sa) {
    int n = s.size();
    vector<int> rank_(n), lcp(n, 0);

    // Build rank from sa (inverse permutation)
    for (int i = 0; i < n; i++) rank_[sa[i]] = i;

    int k = 0;  // current LCP length
    for (int i = 0; i < n; i++) {
        if (rank_[i] == 0) { k = 0; continue; }

        int j = sa[rank_[i] - 1];  // previous suffix in sorted order
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank_[i]] = k;

        if (k > 0) k--;  // key optimization of Kasai's
    }
    return lcp;
}

// Count distinct substrings using SA + LCP
i64 countDistinctSubstrings(const string& s) {
    auto sa = buildSuffixArray(s);
    auto lcp = buildLCPArray(s, sa);
    int n = s.size();
    i64 total = (i64)n * (n + 1) / 2;
    for (int x : lcp) total -= x;
    return total;
}

void demo_lcp() {
    cout << "\n=== SECTION 5: LCP ARRAY (Kasai) ===" << endl;
    string s = "banana";
    auto sa = buildSuffixArray(s);
    auto lcp = buildLCPArray(s, sa);

    cout << "SA:  ";
    for (int x : sa) cout << x << " ";
    cout << endl;
    cout << "LCP: ";
    for (int x : lcp) cout << x << " ";
    cout << endl;

    // Longest repeated substring
    int maxLCP = *max_element(lcp.begin(), lcp.end());
    int idx = max_element(lcp.begin(), lcp.end()) - lcp.begin();
    cout << "Longest repeated substring: " << s.substr(sa[idx], maxLCP) << " (len=" << maxLCP << ")" << endl;

    // Distinct substrings
    cout << "Distinct substrings of '" << s << "': " << countDistinctSubstrings(s) << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: SUFFIX AUTOMATON (SAM)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A Suffix Automaton is the smallest DFA that accepts all suffixes of a string.
 It contains ALL substring information in O(n) states and O(n) transitions.

 STRUCTURE:
   Each state represents an equivalence class of substrings.
   • link: suffix link → longest proper suffix that's in a different class
   • len: length of the longest substring in this class
   • minLen: length of shortest = link.len + 1

 PROPERTIES:
   • At most 2n-1 states and 3n-4 transitions
   • Can check if a pattern is a substring in O(m)
   • Can count occurrences, find distinct substrings, etc.

 CONSTRUCTION: Online, O(n) — add one character at a time

 APPLICATIONS:
   • Check if pattern is substring: O(m)
   • Count distinct substrings: sum of (len[v] - len[link[v]])
   • Count occurrences of each substring
   • Longest common substring of multiple strings
   • Smallest cyclic shift
*/

struct SuffixAutomaton {
    struct State {
        int len, link;
        map<char, int> next;
        i64 cnt;  // number of times this state's substrings appear
    };

    vector<State> st;
    int last;

    void init() {
        st.clear();
        st.push_back({0, -1, {}, 0});
        last = 0;
    }

    void extend(char c) {
        int cur = st.size();
        st.push_back({st[last].len + 1, -1, {}, 1});
        int p = last;

        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back({st[p].len + 1, st[q].link, st[q].next, 0});
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = clone;
                st[cur].link = clone;
            }
        }
        last = cur;
    }

    void build(const string& s) {
        init();
        for (char c : s) extend(c);
    }

    // Check if pattern is a substring
    bool contains(const string& pattern) {
        int cur = 0;
        for (char c : pattern) {
            if (!st[cur].next.count(c)) return false;
            cur = st[cur].next[c];
        }
        return true;
    }

    // Count distinct substrings
    i64 countDistinct() {
        i64 count = 0;
        for (int i = 1; i < (int)st.size(); i++) {
            count += st[i].len - st[st[i].link].len;
        }
        return count;
    }

    // Count occurrences of each substring (need topological sort)
    void countOccurrences() {
        // Topological sort by len (descending)
        int n = st.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });

        for (int v : order) {
            if (st[v].link >= 0) {
                st[st[v].link].cnt += st[v].cnt;
            }
        }
    }
};

void demo_suffix_automaton() {
    cout << "\n=== SECTION 6: SUFFIX AUTOMATON ===" << endl;
    SuffixAutomaton sam;
    sam.build("abcbc");

    cout << "States: " << sam.st.size() << endl;
    cout << "Contains 'bc': " << sam.contains("bc") << endl;    // 1
    cout << "Contains 'abc': " << sam.contains("abc") << endl;  // 1
    cout << "Contains 'xyz': " << sam.contains("xyz") << endl;  // 0
    cout << "Distinct substrings: " << sam.countDistinct() << endl;  // 12

    SuffixAutomaton sam2;
    sam2.build("aaa");
    cout << "Distinct substrings of 'aaa': " << sam2.countDistinct() << endl;  // 3
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: AHO-CORASICK (Multi-pattern matching)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Aho-Corasick = Trie + KMP failure links → multi-pattern matching.

 Given K patterns and text of length N:
   • Build a trie of all patterns
   • Add failure links (like KMP's failure function, but on trie)
   • Process text character by character, following transitions

 FAILURE LINK: From node u, go to the longest proper suffix of u's
              string that is also a prefix of some pattern in the trie.

 Time: O(N + M + Z) where M = total pattern length, Z = total matches
 Space: O(M * Σ)

 APPLICATIONS:
   • Find all occurrences of multiple patterns in text
   • DNA sequence matching
   • Spam filtering
   • Virus signature detection
*/

struct AhoCorasick {
    static const int ALPHA = 26;

    struct Node {
        int children[ALPHA];
        int fail;        // failure link
        int output;      // output link (which patterns end here)
        bool isEnd;
        vector<int> patternIds;  // which patterns end at this node

        Node() : fail(0), output(-1), isEnd(false) {
            memset(children, -1, sizeof(children));
        }
    };

    vector<Node> nodes;

    AhoCorasick() { nodes.push_back(Node()); }

    // Insert a pattern with given id
    void insert(const string& pattern, int id) {
        int cur = 0;
        for (char c : pattern) {
            int idx = c - 'a';
            if (nodes[cur].children[idx] == -1) {
                nodes[cur].children[idx] = nodes.size();
                nodes.push_back(Node());
            }
            cur = nodes[cur].children[idx];
        }
        nodes[cur].isEnd = true;
        nodes[cur].patternIds.push_back(id);
    }

    // Build failure links using BFS
    void build() {
        queue<int> q;

        // Initialize: children of root that exist have fail = 0
        for (int c = 0; c < ALPHA; c++) {
            if (nodes[0].children[c] == -1) {
                nodes[0].children[c] = 0;  // point back to root
            } else {
                nodes[nodes[0].children[c]].fail = 0;
                q.push(nodes[0].children[c]);
            }
        }

        // BFS to build failure links
        while (!q.empty()) {
            int u = q.front(); q.pop();

            // Output link: nearest ancestor with isEnd via fail chain
            int f = nodes[u].fail;
            nodes[u].output = nodes[f].isEnd ? f : nodes[f].output;

            for (int c = 0; c < ALPHA; c++) {
                if (nodes[u].children[c] == -1) {
                    // Implicit transition via failure links
                    nodes[u].children[c] = nodes[nodes[u].fail].children[c];
                } else {
                    nodes[nodes[u].children[c]].fail = nodes[nodes[u].fail].children[c];
                    q.push(nodes[u].children[c]);
                }
            }
        }
    }

    // Search text for all pattern occurrences
    // Returns: for each pattern id, list of starting positions
    vector<vector<int>> search(const string& text, int numPatterns) {
        vector<vector<int>> result(numPatterns);
        int cur = 0;

        for (int i = 0; i < (int)text.size(); i++) {
            cur = nodes[cur].children[text[i] - 'a'];

            // Collect all patterns ending here
            int temp = cur;
            while (temp > 0) {
                if (nodes[temp].isEnd) {
                    for (int id : nodes[temp].patternIds) {
                        // Pattern id ends at position i
                        result[id].push_back(i);
                    }
                }
                temp = nodes[temp].output;
                if (temp == -1) break;
            }
        }
        return result;
    }
};

void demo_aho_corasick() {
    cout << "\n=== SECTION 7: AHO-CORASICK ===" << endl;
    AhoCorasick ac;
    vector<string> patterns = {"he", "she", "his", "hers"};
    for (int i = 0; i < (int)patterns.size(); i++) {
        ac.insert(patterns[i], i);
    }
    ac.build();

    string text = "ahishers";
    auto results = ac.search(text, patterns.size());

    for (int i = 0; i < (int)patterns.size(); i++) {
        cout << "Pattern '" << patterns[i] << "' found at end positions: ";
        for (int pos : results[i]) cout << pos << " ";
        cout << endl;
    }
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: BOOTH'S ALGORITHM (Minimum String Rotation)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Given a string s, find the rotation that is lexicographically smallest.
 A rotation of "abcd": "abcd", "bcda", "cdab", "dabc"
 Minimum rotation of "dcba": "adcb"

 NAIVE: Generate all n rotations, find minimum — O(n²)
 BOOTH'S: O(n) time, O(n) space

 ALGORITHM (Modified failure function):
   Concatenate s with itself: ss = s + s
   Build a modified failure function on ss
   The algorithm tracks the starting position of the minimum rotation.

 APPLICATIONS:
   • Circular string comparison
   • Necklace equivalence
   • Minimum representation of circular buffer
*/

int boothMinRotation(const string& s) {
    int n = s.size();
    string ss = s + s;
    vector<int> f(2 * n, -1);
    int k = 0;  // starting position of current minimum rotation

    for (int j = 1; j < 2 * n; j++) {
        int i = f[j - 1 - k];
        while (i != -1 && ss[j] != ss[k + i + 1]) {
            if (ss[j] < ss[k + i + 1]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (i == -1 && ss[j] != ss[k + i + 1]) {
            if (ss[j] < ss[k + i + 1]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}

string minRotation(const string& s) {
    int k = boothMinRotation(s);
    return s.substr(k) + s.substr(0, k);
}

void demo_booth() {
    cout << "\n=== SECTION 8: BOOTH'S ALGORITHM ===" << endl;
    cout << "Min rotation of 'dcba': " << minRotation("dcba") << endl;    // adcb
    cout << "Min rotation of 'bca': " << minRotation("bca") << endl;      // abc
    cout << "Min rotation of 'abcabc': " << minRotation("abcabc") << endl;// abcabc
    cout << "Min rotation of 'cba': " << minRotation("cba") << endl;      // acb
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: LYNDON DECOMPOSITION (Duval's Algorithm)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A LYNDON WORD is a string that is strictly smaller than all its proper rotations.
 Examples: "a", "ab", "aab", "abcd" are Lyndon words
 Non-examples: "ba" (ba > ab), "aa" (aa = aa, not strictly)

 LYNDON FACTORIZATION:
   Every string s can be uniquely decomposed as s = w1 w2 ... wk
   where each wi is a Lyndon word and w1 >= w2 >= ... >= wk

 DUVAL'S ALGORITHM: O(n) time, O(1) space

 APPLICATIONS:
   • Finding minimum rotation (smallest Lyndon rotation = minimum)
   • String combinatorics
   • Computing Lyndon array
   • Related to suffix array construction
*/

vector<string> lyndonDecomposition(const string& s) {
    int n = s.size();
    vector<string> result;
    int i = 0;

    while (i < n) {
        int j = i, k = i + 1;
        while (k < n && s[j] <= s[k]) {
            if (s[j] < s[k]) {
                j = i;  // reset j
            } else {
                j++;    // s[j] == s[k]
            }
            k++;
        }
        // Lyndon word length = k - j
        int len = k - j;
        while (i <= j) {
            result.push_back(s.substr(i, len));
            i += len;
        }
    }
    return result;
}

// Minimum rotation using Lyndon decomposition
string minRotationLyndon(const string& s) {
    string ss = s + s;
    auto decomp = lyndonDecomposition(ss);
    // The minimum rotation starts at the beginning of the first Lyndon
    // word that covers position 0..n-1
    // Simpler: just take first n characters of the decomposition
    string result;
    for (auto& w : decomp) {
        result += w;
        if ((int)result.size() >= (int)s.size()) break;
    }
    return result.substr(0, s.size());
}

void demo_lyndon() {
    cout << "\n=== SECTION 9: LYNDON DECOMPOSITION ===" << endl;
    auto decomp = lyndonDecomposition("abbaabba");
    cout << "Lyndon decomposition of 'abbaabba': ";
    for (auto& w : decomp) cout << "[" << w << "] ";
    cout << endl;

    decomp = lyndonDecomposition("cbabc");
    cout << "Lyndon decomposition of 'cbabc': ";
    for (auto& w : decomp) cout << "[" << w << "] ";
    cout << endl;

    decomp = lyndonDecomposition("aab");
    cout << "Lyndon decomposition of 'aab': ";
    for (auto& w : decomp) cout << "[" << w << "] ";
    cout << endl;  // [aab] — it's already a Lyndon word
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_kmp();
    demo_z_algorithm();
    demo_manacher();
    demo_suffix_array();
    demo_lcp();
    demo_suffix_automaton();
    demo_aho_corasick();
    demo_booth();
    demo_lyndon();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 9 Pattern Matching Algorithms covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  ── KMP ──                                                      ║
║  LeetCode 28   — Find Index of First Occurrence                 ║
║  LeetCode 459  — Repeated Substring Pattern                     ║
║  CF 126B       — Password                                        ║
║  ── Z-Algorithm ──                                              ║
║  CF 126B       — Password (Z-array approach)                     ║
║  CF 432D       — Prefixes and Suffixes                           ║
║  ── Manacher ──                                                 ║
║  LeetCode 5    — Longest Palindromic Substring                  ║
║  LeetCode 647  — Palindromic Substrings                         ║
║  CF 17E        — Palisection                                     ║
║  ── Suffix Array + LCP ──                                       ║
║  CSES          — Substring Order I / II                          ║
║  CSES          — Repeating Substring                             ║
║  SPOJ DISUBSTR — Distinct Substrings                            ║
║  ── Suffix Automaton ──                                         ║
║  SPOJ SUBST1   — New Distinct Substrings                        ║
║  CF 235C       — Cyclical Quest                                  ║
║  ── Aho-Corasick ──                                             ║
║  CSES          — Finding Patterns                                ║
║  CF 710F       — String Set Queries                              ║
║  ── Booth's / Lyndon ──                                         ║
║  CF 182D       — Common Divisors (string periodicity)            ║
║  SPOJ MINMOVE  — Minimum Rotation                                ║
╚══════════════════════════════════════════════════════════════════╝
*/

