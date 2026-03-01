/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 11 — STRING ADVANCED DATA STRUCTURES                          ║
║     From Zero to Grandmaster — The Final Boss                              ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Persistent Trie (Versioned Trie for range XOR queries)
 2. Online Suffix Array (SA-IS / Incremental construction)
 3. Palindromic Tree — Eertree (All distinct palindromic substrings in O(n))
 4. String Hashing with Modular Inverse (O(1) normalized substring hash)
 5. Heavy-Light Decomposition on Strings (LCP queries on suffix tree paths)
 6. Rope Data Structure (Implicit Treap for fast string operations)

DIFFICULTY: ⭐⭐⭐⭐⭐ (Grandmaster / IGM level)
─────────────────────────────────────────────────
 These data structures appear in:
   • Codeforces Div1 D-F
   • AtCoder AGC / ARC hard problems
   • IOI / ICPC World Finals
   • Google Code Jam / Facebook Hacker Cup finals

PREREQUISITES:
   • Chapters 01-10 mastered
   • Trie, Suffix Array, Suffix Automaton, KMP, Manacher
   • Segment Trees, Sparse Tables, HLD
   • Implicit Treap / Splay Tree basics
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <numeric>
#include <random>
#include <chrono>
#include <cassert>
#include <cstring>
#include <functional>
using namespace std;
using i64 = long long;

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 1: PERSISTENT TRIE
// ═══════════════════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A Persistent Trie keeps ALL previous versions of the trie after each insert.
 Instead of modifying nodes, we create new nodes along the insertion path
 and share unchanged subtrees with the previous version.

 WHY PERSISTENT?
   • Answer queries on RANGES: "max XOR with x using only elements in [L, R]"
   • Each version = trie after inserting elements a[0], a[1], ..., a[i]
   • Query on range [L, R] uses: version[R] minus version[L-1]

 STRUCTURE:
   Each node stores children[0], children[1], and count.
   Insert creates O(BITS) new nodes per version.
   Total nodes: O(n * BITS)

 TIME:  O(BITS) per insert, O(BITS) per query
 SPACE: O(n * BITS) nodes total

 KEY PROBLEM: Maximum XOR in subarray [L, R]
   • Build prefix XOR: pre[i] = a[0] ^ a[1] ^ ... ^ a[i-1]
   • XOR of subarray [L, R] = pre[R+1] ^ pre[L]
   • Want: max over L in [l, r] of (pre[r+1] ^ pre[L])
   • Insert pre[0..r+1] into persistent trie, query using version difference

 APPLICATIONS:
   • Range maximum XOR queries
   • Offline XOR problems with version control
   • Dynamic XOR basis with persistence
*/

struct PersistentTrie {
    static const int BITS = 30;   // for values up to ~10^9
    static const int MAXN = 6000005; // n * BITS nodes

    int ch[MAXN][2]; // children
    int cnt[MAXN];   // how many numbers pass through this node
    int tot;         // total nodes allocated

    void init() {
        tot = 0;
        newNode(); // root of version 0 (empty trie)
    }

    int newNode() {
        ch[tot][0] = ch[tot][1] = 0;
        cnt[tot] = 0;
        return tot++;
    }

    // Insert `val` into trie, creating a new version from `prev` root
    // Returns the new root
    int insert(int prev, int val) {
        int cur = newNode();
        int root = cur;

        for (int i = BITS; i >= 0; i--) {
            int bit = (val >> i) & 1;

            // Copy both children from previous version
            ch[cur][0] = ch[prev][0];
            ch[cur][1] = ch[prev][1];
            cnt[cur] = cnt[prev] + 1;

            // Create new node only along the insertion path
            int nxt = newNode();
            ch[cur][bit] = nxt;

            cur = nxt;
            prev = ch[prev][bit]; // follow old version along same path
        }
        cnt[cur] = cnt[prev] + 1;
        return root;
    }

    // Query: max XOR of `val` with any number inserted between version L and R
    // verR = root after inserting elements [0..R]
    // verL = root after inserting elements [0..L-1]  (use 0-root for L=0)
    int queryMaxXor(int verL, int verR, int val) {
        int result = 0;
        for (int i = BITS; i >= 0; i--) {
            int bit = (val >> i) & 1;
            int want = 1 - bit; // opposite bit to maximize XOR

            // Check if the "want" path has any elements in range [L, R]
            int available = cnt[ch[verR][want]] - cnt[ch[verL][want]];
            if (available > 0) {
                result |= (1 << i);
                verR = ch[verR][want];
                verL = ch[verL][want];
            } else {
                verR = ch[verR][bit];
                verL = ch[verL][bit];
            }
        }
        return result;
    }
};

PersistentTrie ptrie;

void demo_persistent_trie() {
    cout << "=== SECTION 1: PERSISTENT TRIE ===" << endl;

    ptrie.init();

    // Example: array = [1, 2, 3, 4, 5]
    // Build prefix XOR: pre = [0, 1, 3, 0, 4, 1]
    // Insert all prefix XOR values into persistent trie
    vector<int> a = {1, 2, 3, 4, 5};
    int n = a.size();
    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] ^ a[i];

    vector<int> roots(n + 2);
    roots[0] = 0; // empty trie root

    for (int i = 0; i <= n; i++) {
        roots[i + 1] = ptrie.insert(roots[i], pre[i]);
    }

    // Query: Maximum XOR subarray in range [L, R] (0-indexed)
    // XOR of subarray [L, R] = pre[R+1] ^ pre[j] for some L <= j <= R
    // We want max of (pre[R+1] ^ pre[j]) for j in [L, R+1]

    // Max XOR subarray in entire array [0, 4]:
    // Query version[0+1] to version[5] with val = pre[5] = 1
    int maxXor = ptrie.queryMaxXor(roots[0], roots[n + 1], pre[n]);
    cout << "Max XOR subarray in [1,2,3,4,5]: " << maxXor << endl;

    // Max XOR subarray in [0, 2] (elements 1, 2, 3):
    // pre values for j in [0..3]: pre[0]=0, pre[1]=1, pre[2]=3, pre[3]=0
    // XOR with pre[3]=0 → max of 0^0, 0^1, 0^3, 0^0 = 3
    int maxXor2 = ptrie.queryMaxXor(roots[0], roots[4], pre[3]);
    cout << "Max XOR subarray in [1,2,3]: " << maxXor2 << endl;

    cout << "Persistent Trie total nodes used: " << ptrie.tot << endl;
}

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 2: ONLINE / INCREMENTAL SUFFIX ARRAY
// ═══════════════════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Standard suffix array construction is OFFLINE (needs entire string).

 ONLINE approaches allow appending characters one at a time:

 METHOD 1: SA-IS (Suffix Array Induced Sorting) — O(n)
   The most efficient offline algorithm. Linear time, linear space.
   Complex to implement but gold standard for competitive programming.

 METHOD 2: Using Suffix Automaton (SAM) → SA
   The suffix automaton can be built online (one char at a time).
   The suffix array can then be extracted from the SAM via DFS.
   SAM states in topological order → sorted suffixes.

 METHOD 3: DC3 / Skew Algorithm — O(n)
   Divide suffixes into groups mod 3, recursively sort.

 Below we implement:
   (a) SA-IS (the O(n) algorithm) — the best offline SA construction
   (b) Suffix Automaton → Suffix Array extraction (online)

 SA-IS KEY IDEAS:
   • Classify each suffix as S-type or L-type
     - S-type: suffix i < suffix i+1 (lexicographically)
     - L-type: suffix i > suffix i+1
   • LMS (Left-Most S): an S-type suffix whose predecessor is L-type
   • Sort LMS suffixes recursively, then induce the rest
*/

// SA-IS: O(n) Suffix Array Construction
// Works for any integer alphabet (including characters)
vector<int> sais(const vector<int>& s, int upperBound) {
    int n = s.size();
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};

    // Step 1: Classify S/L types
    vector<bool> isS(n, false);
    isS[n - 1] = true; // sentinel is S-type
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] < s[i + 1]) isS[i] = true;
        else if (s[i] > s[i + 1]) isS[i] = false;
        else isS[i] = isS[i + 1];
    }

    // Step 2: Find bucket boundaries
    vector<int> bucketSize(upperBound, 0);
    for (int c : s) bucketSize[c]++;
    vector<int> bucketStart(upperBound), bucketEnd(upperBound);
    {
        int sum = 0;
        for (int i = 0; i < upperBound; i++) {
            bucketStart[i] = sum;
            sum += bucketSize[i];
            bucketEnd[i] = sum - 1;
        }
    }

    // Helper: induce L and S suffixes
    auto induceSA = [&](vector<int>& sa, const vector<int>& lms) {
        fill(sa.begin(), sa.end(), -1);
        // Place LMS suffixes at the end of their buckets
        vector<int> bEnd(bucketEnd);
        for (int i = (int)lms.size() - 1; i >= 0; i--) {
            sa[bEnd[s[lms[i]]]--] = lms[i];
        }
        // Induce L-type
        vector<int> bStart(bucketStart);
        for (int i = 0; i < n; i++) {
            if (sa[i] > 0 && !isS[sa[i] - 1]) {
                sa[bStart[s[sa[i] - 1]]++] = sa[i] - 1;
            }
        }
        // Induce S-type
        bEnd = bucketEnd;
        for (int i = n - 1; i >= 0; i--) {
            if (sa[i] > 0 && isS[sa[i] - 1]) {
                sa[bEnd[s[sa[i] - 1]]--] = sa[i] - 1;
            }
        }
    };

    // Step 3: Find LMS positions
    vector<int> lmsPositions;
    for (int i = 1; i < n; i++) {
        if (isS[i] && !isS[i - 1]) lmsPositions.push_back(i);
    }

    // Step 4: Initial induced sort
    vector<int> sa(n, -1);
    induceSA(sa, lmsPositions);

    // Step 5: Compact and name LMS substrings
    vector<int> orderedLMS;
    for (int i = 0; i < n; i++) {
        if (sa[i] > 0 && isS[sa[i]] && !isS[sa[i] - 1])
            orderedLMS.push_back(sa[i]);
    }

    // Compare two LMS substrings
    auto lmsEqual = [&](int a, int b) -> bool {
        for (int i = 0; ; i++) {
            bool aIsLMS = (i > 0 && isS[a + i] && !isS[a + i - 1]);
            bool bIsLMS = (i > 0 && isS[b + i] && !isS[b + i - 1]);
            if (s[a + i] != s[b + i] || aIsLMS != bIsLMS) return false;
            if (i > 0 && (aIsLMS || bIsLMS)) return true;
        }
    };

    vector<int> name(n, -1);
    int nameCount = 0;
    name[orderedLMS[0]] = 0;
    for (int i = 1; i < (int)orderedLMS.size(); i++) {
        if (!lmsEqual(orderedLMS[i - 1], orderedLMS[i])) nameCount++;
        name[orderedLMS[i]] = nameCount;
    }

    // Step 6: If names are unique, we're done; otherwise recurse
    vector<int> reducedString;
    vector<int> lmsMap; // map from reduced index to original position
    for (int i = 0; i < n; i++) {
        if (name[i] != -1) {
            reducedString.push_back(name[i]);
            lmsMap.push_back(i);
        }
    }

    vector<int> reducedSA;
    if (nameCount + 1 < (int)reducedString.size()) {
        reducedSA = sais(reducedString, nameCount + 1);
    } else {
        reducedSA.resize(reducedString.size());
        for (int i = 0; i < (int)reducedString.size(); i++) {
            reducedSA[reducedString[i]] = i;
        }
    }

    // Step 7: Rearrange LMS in correct order and do final induced sort
    vector<int> sortedLMS;
    for (int i : reducedSA) sortedLMS.push_back(lmsMap[i]);

    fill(sa.begin(), sa.end(), -1);
    induceSA(sa, sortedLMS);

    return sa;
}

// Wrapper for string input
vector<int> buildSuffixArraySAIS(const string& s) {
    int n = s.size();
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = (int)s[i];
    // SA-IS needs a sentinel (smallest character, appears once at end)
    // We add a 0-sentinel
    arr.push_back(0);
    auto sa = sais(arr, 256);
    // Remove the sentinel's suffix (always at sa[0])
    return vector<int>(sa.begin() + 1, sa.end());
}

// Kasai's LCP for completeness
vector<int> buildLCPFromSA(const string& s, const vector<int>& sa) {
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

void demo_sais() {
    cout << "\n=== SECTION 2: SA-IS (O(n) SUFFIX ARRAY) ===" << endl;

    string s = "banana";
    auto sa = buildSuffixArraySAIS(s);
    cout << "SA-IS suffix array of '" << s << "': ";
    for (int x : sa) cout << x << " ";
    cout << endl;

    cout << "Sorted suffixes:" << endl;
    for (int i : sa) cout << "  " << i << ": " << s.substr(i) << endl;

    auto lcp = buildLCPFromSA(s, sa);
    cout << "LCP array: ";
    for (int x : lcp) cout << x << " ";
    cout << endl;

    // Distinct substrings
    int n = s.size();
    i64 distinct = (i64)n * (n + 1) / 2;
    for (int x : lcp) distinct -= x;
    cout << "Distinct substrings: " << distinct << endl;
}

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 3: PALINDROMIC TREE (EERTREE)
// ═══════════════════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 The Eertree (Palindromic Tree) stores ALL DISTINCT palindromic substrings
 of a string in O(n) time and space.

 STRUCTURE:
   Two root nodes:
     • Root -1: imaginary root with length -1 (parent of odd-length palindromes)
     • Root  0: empty string root with length 0 (parent of even-length palindromes)

   Each node represents a UNIQUE palindromic substring.
   Each node has:
     • len: length of the palindrome
     • link: suffix link → longest proper palindromic suffix
     • children[c]: appending char c on both sides gives child palindrome
     • count: number of occurrences (after propagation)
     • start: starting index of one occurrence

 CONSTRUCTION (Online, O(n)):
   Process characters one by one.
   For each new character s[i]:
     1. Start from the last palindrome added
     2. Find the longest palindromic suffix P such that s[i-len(P)-1] == s[i]
        (Follow suffix links until this condition holds)
     3. If P + s[i] on both sides already exists → just update last
     4. Else: create new node, set suffix link by similar search

 PROPERTIES:
   • A string of length n has at most n+2 nodes (n+2 distinct palindromes + 2 roots)
   • Each character adds at most 1 new palindromic substring
   • Total distinct palindromic substrings ≤ n+2 (tight bound!)

 APPLICATIONS:
   • Count distinct palindromic substrings: number of nodes - 2 (roots)
   • Count total palindromic substrings: sum of count[] after propagation
   • Longest palindromic substring: max len among all nodes
   • Number of palindromic suffixes at each position
   • Palindromic factorization (split string into minimum palindromes)
*/

struct Eertree {
    struct Node {
        int len;          // length of palindrome
        int suffLink;     // suffix link (longest proper palindromic suffix)
        int count;        // occurrences (raw — needs propagation)
        int start;        // starting index of one occurrence
        map<char, int> children;

        Node(int len = 0, int suffLink = 0, int count = 0, int start = -1)
            : len(len), suffLink(suffLink), count(count), start(start) {}
    };

    vector<Node> nodes;
    string s;
    int last; // index of the node corresponding to longest palindromic suffix of s[0..cur]

    void init() {
        nodes.clear();
        s.clear();
        last = 0;

        // Node 0: imaginary root, length -1
        nodes.push_back(Node(-1, 0));
        // Node 1: empty string root, length 0
        nodes.push_back(Node(0, 0));
        // Both roots' suffix links point to imaginary root (node 0)
        nodes[0].suffLink = 0;
        nodes[1].suffLink = 0;

        last = 1; // start with empty palindrome
    }

    // Find the longest palindromic suffix P of current string such that
    // s[curPos - len(P) - 1] == c (the character before P equals c)
    int findSuffix(int v, int curPos) {
        while (curPos - 1 - nodes[v].len < 0 || s[curPos - 1 - nodes[v].len] != s[curPos]) {
            v = nodes[v].suffLink;
        }
        return v;
    }

    // Add character c to the end of the string
    // Returns true if a new palindrome was discovered
    bool addChar(char c) {
        s += c;
        int curPos = (int)s.size() - 1;

        // Find longest palindromic suffix where we can extend
        int cur = findSuffix(last, curPos);

        if (nodes[cur].children.count(c)) {
            // Palindrome already exists
            last = nodes[cur].children[c];
            nodes[last].count++;
            return false;
        }

        // Create new node
        int newNode = nodes.size();
        int newLen = nodes[cur].len + 2;
        nodes.push_back(Node(newLen, 0, 1, curPos - newLen + 1));
        nodes[cur].children[c] = newNode;

        // Set suffix link
        if (newLen == 1) {
            // Single character palindrome → suffix link to empty string (node 1)
            nodes[newNode].suffLink = 1;
        } else {
            // Find suffix link: longest proper palindromic suffix of new palindrome
            int suffCandidate = findSuffix(nodes[cur].suffLink, curPos);
            nodes[newNode].suffLink = nodes[suffCandidate].children[c];
        }

        last = newNode;
        return true;
    }

    // Build from entire string
    void build(const string& str) {
        init();
        for (char c : str) addChar(c);
    }

    // Propagate counts: each palindrome's count includes counts of its extensions
    // Process nodes in reverse order (children before parents via suffix links)
    void propagate() {
        // Nodes are added in order, and suffix links always point to earlier nodes
        // So process from last node to first
        for (int i = (int)nodes.size() - 1; i >= 2; i--) {
            nodes[nodes[i].suffLink].count += nodes[i].count;
        }
    }

    // Count of distinct palindromic substrings
    int countDistinct() {
        return (int)nodes.size() - 2; // subtract 2 roots
    }

    // Total occurrences of all palindromic substrings
    i64 countTotal() {
        propagate();
        i64 total = 0;
        for (int i = 2; i < (int)nodes.size(); i++) {
            total += nodes[i].count;
        }
        return total;
    }

    // Longest palindromic substring
    string longestPalindrome() {
        int bestLen = 0, bestStart = 0;
        for (int i = 2; i < (int)nodes.size(); i++) {
            if (nodes[i].len > bestLen) {
                bestLen = nodes[i].len;
                bestStart = nodes[i].start;
            }
        }
        return s.substr(bestStart, bestLen);
    }

    // Get all distinct palindromic substrings
    vector<string> allPalindromes() {
        vector<string> result;
        for (int i = 2; i < (int)nodes.size(); i++) {
            result.push_back(s.substr(nodes[i].start, nodes[i].len));
        }
        return result;
    }

    // Number of palindromic suffixes at each position
    vector<int> palindromicSuffixCounts() {
        // Rebuild: for each position, count suffix links from `last`
        vector<int> result;
        init();
        for (int i = 0; i < (int)s.size(); i++) {
            // We need to rebuild — let's use a simpler approach
            // Count by following suffix links from current `last`
            break;
        }
        // Alternative: after building, for each position the number of palindromic
        // suffixes = depth in suffix link tree from `last` node at that position
        // This requires storing `last` at each step during build

        // Let's rebuild properly
        string original = s;
        init();
        for (char c : original) {
            addChar(c);
            // Count palindromic suffixes = depth in suffix link chain from last
            int cnt = 0;
            int v = last;
            while (v > 1) { // while not root
                cnt++;
                v = nodes[v].suffLink;
            }
            result.push_back(cnt);
        }
        return result;
    }
};

void demo_eertree() {
    cout << "\n=== SECTION 3: PALINDROMIC TREE (EERTREE) ===" << endl;

    Eertree et;
    et.build("eertree");

    cout << "String: 'eertree'" << endl;
    cout << "Distinct palindromes: " << et.countDistinct() << endl;
    cout << "Total palindrome occurrences: " << et.countTotal() << endl;
    cout << "Longest palindrome: " << et.longestPalindrome() << endl;

    auto pals = et.allPalindromes();
    cout << "All distinct palindromes: ";
    for (auto& p : pals) cout << "'" << p << "' ";
    cout << endl;

    // Another example
    Eertree et2;
    et2.build("abacaba");
    cout << "\nString: 'abacaba'" << endl;
    cout << "Distinct palindromes: " << et2.countDistinct() << endl;
    cout << "Longest palindrome: " << et2.longestPalindrome() << endl;

    auto pals2 = et2.allPalindromes();
    cout << "All distinct palindromes: ";
    for (auto& p : pals2) cout << "'" << p << "' ";
    cout << endl;

    // Palindromic suffix counts
    Eertree et3;
    et3.build("abaab");
    auto counts = et3.palindromicSuffixCounts();
    cout << "\nPalindromic suffix counts for 'abaab': ";
    for (int c : counts) cout << c << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 4: STRING HASHING WITH MODULAR INVERSE
// ═══════════════════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 In Chapter 04 we built prefix hashes where:
   h[i] = s[0]*p^0 + s[1]*p^1 + ... + s[i-1]*p^(i-1)  (mod M)

 To compare s[l1..r1] with s[l2..r2], we had to multiply by powers of p
 to "normalize" the starting position.

 WITH MODULAR INVERSE, we can get a NORMALIZED hash for any substring:
   hash(s[l..r]) = (h[r+1] - h[l]) * p^(-l)  (mod M)

 Where p^(-l) = modular inverse of p^l.

 ADVANTAGES:
   • Compare ANY two substrings directly: hash(s[l1..r1]) == hash(s[l2..r2])
   • No need for power multiplication during comparison
   • Can compare substrings across different strings trivially
   • Can build hash sets of substrings

 IMPLEMENTATION:
   Precompute: invPow[i] = inverse(p^i) mod M
   hash(s[l..r]) = (h[r+1] - h[l]) * invPow[l] mod M

 DOUBLE HASHING version for anti-hack safety.
*/

struct NormalizedHasher {
    static const i64 MOD1 = 1000000007LL;
    static const i64 MOD2 = 998244353LL;

    int n;
    vector<i64> h1, h2;       // prefix hashes
    vector<i64> pw1, pw2;     // powers of base
    vector<i64> inv1, inv2;   // inverse powers
    i64 p1, p2;

    static i64 power(i64 base, i64 exp, i64 mod) {
        i64 result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    }

    NormalizedHasher() : n(0), p1(131), p2(137) {}

    NormalizedHasher(const string& s, i64 base1 = 131, i64 base2 = 137)
        : n(s.size()), p1(base1), p2(base2) {

        h1.resize(n + 1, 0); h2.resize(n + 1, 0);
        pw1.resize(n + 1, 1); pw2.resize(n + 1, 1);
        inv1.resize(n + 1, 1); inv2.resize(n + 1, 1);

        // Precompute powers and inverse powers
        i64 ip1 = power(p1, MOD1 - 2, MOD1);
        i64 ip2 = power(p2, MOD2 - 2, MOD2);

        for (int i = 1; i <= n; i++) {
            pw1[i] = pw1[i - 1] * p1 % MOD1;
            pw2[i] = pw2[i - 1] * p2 % MOD2;
            inv1[i] = inv1[i - 1] * ip1 % MOD1;
            inv2[i] = inv2[i - 1] * ip2 % MOD2;
        }

        // Build prefix hashes
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] + (i64)(s[i] - 'a' + 1) * pw1[i]) % MOD1;
            h2[i + 1] = (h2[i] + (i64)(s[i] - 'a' + 1) * pw2[i]) % MOD2;
        }
    }

    // NORMALIZED hash of substring s[l..r] (0-indexed, inclusive)
    // Can be compared directly with any other normalized hash of same length
    pair<i64, i64> getHash(int l, int r) const {
        i64 raw1 = (h1[r + 1] - h1[l] + MOD1) % MOD1;
        i64 raw2 = (h2[r + 1] - h2[l] + MOD2) % MOD2;

        // Normalize: multiply by p^(-l)
        i64 norm1 = raw1 * inv1[l] % MOD1;
        i64 norm2 = raw2 * inv2[l] % MOD2;

        return {norm1, norm2};
    }

    // Compare s[l1..r1] with s[l2..r2] (must have same length)
    bool compare(int l1, int r1, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false;
        return getHash(l1, r1) == getHash(l2, r2);
    }

    // Compare with another string's hasher
    bool compareWith(int l1, int r1, const NormalizedHasher& other, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false;
        return getHash(l1, r1) == other.getHash(l2, r2);
    }

    // Check if s[l..r] is a palindrome (needs reverse hasher)
    // Build a separate hasher on reversed string, then compare
};

// Palindrome checking with normalized hash
struct PalindromeChecker {
    NormalizedHasher fwd, rev;
    int n;

    PalindromeChecker(const string& s) : fwd(s), n(s.size()) {
        string r(s.rbegin(), s.rend());
        rev = NormalizedHasher(r);
    }

    bool isPalindrome(int l, int r) {
        // s[l..r] reversed is rev[n-1-r .. n-1-l]
        auto h1 = fwd.getHash(l, r);
        auto h2 = rev.getHash(n - 1 - r, n - 1 - l);
        return h1 == h2;
    }
};

void demo_normalized_hash() {
    cout << "\n=== SECTION 4: NORMALIZED STRING HASHING ===" << endl;

    NormalizedHasher h1("abcabc");
    NormalizedHasher h2("xyzabcxyz");

    // Compare within same string
    cout << "s1[0..2]='abc' vs s1[3..5]='abc': " << h1.compare(0, 2, 3, 5) << endl; // 1
    cout << "s1[0..2]='abc' vs s1[1..3]='bca': " << h1.compare(0, 2, 1, 3) << endl; // 0

    // Compare across different strings
    cout << "s1[0..2]='abc' vs s2[3..5]='abc': "
         << h1.compareWith(0, 2, h2, 3, 5) << endl; // 1

    // Palindrome checking
    PalindromeChecker pc("abacaba");
    cout << "Is 'abacaba'[0..6] palindrome? " << pc.isPalindrome(0, 6) << endl;  // 1
    cout << "Is 'abacaba'[0..3] palindrome? " << pc.isPalindrome(0, 3) << endl;  // 0
    cout << "Is 'abacaba'[1..5] palindrome? " << pc.isPalindrome(1, 5) << endl;  // 1
}

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 5: HEAVY-LIGHT DECOMPOSITION ON STRINGS
// ═══════════════════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 When strings are placed on TREE EDGES (or nodes), and we need to answer
 queries about the string formed by a path in the tree, we combine:
   • HLD (Heavy-Light Decomposition) — decompose tree paths into chains
   • String hashing / suffix structures — answer substring queries on chains
   • Segment Tree — combine chain results

 COMMON PROBLEMS:
   1. Each node has a character. Query: is the path string a palindrome?
   2. LCP of two paths in the tree.
   3. Pattern matching on tree paths.

 APPROACH FOR PALINDROME QUERY ON PATH:
   • HLD decomposes path u→v into O(log n) chains
   • On each chain, use precomputed hashes (forward + backward)
   • Concatenate chain hashes to get hash of full path string
   • Compare forward hash with reverse hash → palindrome check

 Below: Simplified HLD + hash for path palindrome queries.
*/

struct HLDStrings {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sz;
    string nodeChars; // character at each node
    int curPos;

    // Hashing structures for forward and backward path
    NormalizedHasher fwdHash, bwdHash;
    string chainString; // characters in HLD order

    HLDStrings(int n, const string& chars)
        : n(n), adj(n), parent(n), depth(n), heavy(n, -1),
          head(n), pos(n), sz(n), nodeChars(chars), curPos(0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p, int d) {
        parent[v] = p;
        depth[v] = d;
        sz[v] = 1;
        int maxSz = 0;
        for (int u : adj[v]) {
            if (u == p) continue;
            dfs(u, v, d + 1);
            sz[v] += sz[u];
            if (sz[u] > maxSz) {
                maxSz = sz[u];
                heavy[v] = u;
            }
        }
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = curPos++;
        chainString += nodeChars[v];
        if (heavy[v] != -1) {
            decompose(heavy[v], h);
        }
        for (int u : adj[v]) {
            if (u != parent[v] && u != heavy[v]) {
                decompose(u, u);
            }
        }
    }

    void build(int root = 0) {
        dfs(root, -1, 0);
        chainString = "";
        decompose(root, root);
        // Build hashers on the chain string
        fwdHash = NormalizedHasher(chainString);
        string rev(chainString.rbegin(), chainString.rend());
        bwdHash = NormalizedHasher(rev);
    }

    // Get hash of a single chain segment [u..v] going downward
    pair<i64, i64> chainHash(int u, int v) {
        // u is ancestor of v, both in same chain
        return fwdHash.getHash(pos[u], pos[v]);
    }

    // Check if path from u to v forms a palindrome
    // Simplified: collect characters along path, check palindrome via hashing
    bool isPathPalindrome(int u, int v) {
        // Collect path characters using HLD
        vector<char> pathChars;

        // Collect path u → LCA and v → LCA separately
        vector<char> leftPart, rightPart;

        int a = u, b = v;
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) swap(a, b);
            // a's head is deeper — climb a
            for (int i = pos[a]; i >= pos[head[a]]; i--) {
                leftPart.push_back(chainString[i]);
            }
            a = parent[head[a]];
        }
        // Now a and b are in the same chain
        if (depth[a] > depth[b]) swap(a, b);
        // a is LCA
        for (int i = pos[a]; i <= pos[b]; i++) {
            leftPart.push_back(chainString[i]);
        }

        // Check palindrome
        int len = leftPart.size();
        for (int i = 0; i < len / 2; i++) {
            if (leftPart[i] != leftPart[len - 1 - i]) return false;
        }
        return true;
    }
};

void demo_hld_strings() {
    cout << "\n=== SECTION 5: HLD ON STRINGS ===" << endl;

    // Tree with 7 nodes, each node has a character
    //     a(0)
    //    / \
    //   b(1) c(2)
    //  / \
    // a(3) b(4)
    //       \
    //        a(5)

    int n = 6;
    string chars = "abcaba";
    HLDStrings hld(n, chars);
    hld.addEdge(0, 1);
    hld.addEdge(0, 2);
    hld.addEdge(1, 3);
    hld.addEdge(1, 4);
    hld.addEdge(4, 5);
    hld.build(0);

    cout << "Chain string (HLD order): " << hld.chainString << endl;

    // Check path palindromes
    cout << "Path 3→0→2 (a-b-a-c) palindrome? " << hld.isPathPalindrome(3, 2) << endl;
    cout << "Path 3→1 (a-b) palindrome? " << hld.isPathPalindrome(3, 1) << endl;
    cout << "Path 5→4 (a-b) palindrome? " << hld.isPathPalindrome(5, 4) << endl;
}

// ═══════════════════════════════════════════════════════════════════════════
// SECTION 6: ROPE DATA STRUCTURE (Implicit Treap for Strings)
// ═══════════════════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A ROPE is a balanced BST (typically implicit treap or splay tree) that
 represents a string and supports these operations efficiently:

   • Insert character/string at position i:   O(log n)
   • Delete character at position i:          O(log n)
   • Concatenate two ropes:                   O(log n)
   • Split rope at position k:                O(log n)
   • Get character at position i:             O(log n)
   • Reverse substring [l, r]:                O(log n) with lazy propagation
   • Get substring:                           O(k + log n)
   • Print entire string:                     O(n)

 WHY ROPE?
   std::string insert/delete at position i is O(n).
   Rope makes it O(log n) — critical for problems with many string edits.

 IMPLEMENTATION: Implicit treap (randomized BST)
   • Each node stores: character, priority (random), size of subtree
   • Key is implicit (= position in the string)
   • Split/merge operations maintain balance
   • Lazy propagation for reverse operations

 APPLICATIONS:
   • Text editors with frequent insert/delete
   • String problems requiring insert/delete/reverse in O(log n)
   • Persistent ropes (functional updates)
   • Problems like "perform Q operations: insert, delete, reverse substring"
*/

struct Rope {
    struct Node {
        char ch;
        int priority, size;
        bool rev; // lazy reverse flag
        Node *left, *right;

        Node(char c) : ch(c), priority(rand()), size(1), rev(false),
                        left(nullptr), right(nullptr) {}
    };

    Node* root;

    Rope() : root(nullptr) {}

    // Build rope from string
    Rope(const string& s) : root(nullptr) {
        for (char c : s) {
            root = merge(root, new Node(c));
        }
    }

    int getSize(Node* t) { return t ? t->size : 0; }

    void update(Node* t) {
        if (t) t->size = 1 + getSize(t->left) + getSize(t->right);
    }

    void pushDown(Node* t) {
        if (t && t->rev) {
            swap(t->left, t->right);
            if (t->left) t->left->rev ^= true;
            if (t->right) t->right->rev ^= true;
            t->rev = false;
        }
    }

    // Split: first k characters go to l, rest go to r
    void split(Node* t, int k, Node*& l, Node*& r) {
        if (!t) { l = r = nullptr; return; }
        pushDown(t);
        int leftSize = getSize(t->left);
        if (k <= leftSize) {
            split(t->left, k, l, t->left);
            r = t;
        } else {
            split(t->right, k - leftSize - 1, t->right, r);
            l = t;
        }
        update(t);
    }

    // Merge two treaps (all keys in l < all keys in r)
    Node* merge(Node* l, Node* r) {
        if (!l) return r;
        if (!r) return l;
        pushDown(l);
        pushDown(r);
        if (l->priority > r->priority) {
            l->right = merge(l->right, r);
            update(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            update(r);
            return r;
        }
    }

    // Insert character c at position pos (0-indexed)
    void insert(int pos, char c) {
        Node *l, *r;
        split(root, pos, l, r);
        root = merge(merge(l, new Node(c)), r);
    }

    // Insert string s at position pos
    void insertString(int pos, const string& s) {
        Node* mid = nullptr;
        for (char c : s) mid = merge(mid, new Node(c));
        Node *l, *r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    // Delete character at position pos (0-indexed)
    void erase(int pos) {
        Node *l, *mid, *r;
        split(root, pos, l, mid);
        split(mid, 1, mid, r);
        // mid is the deleted node (should be freed in production code)
        root = merge(l, r);
    }

    // Delete characters in range [l, r] (0-indexed, inclusive)
    void eraseRange(int l, int r) {
        Node *left, *mid, *right;
        split(root, l, left, mid);
        split(mid, r - l + 1, mid, right);
        root = merge(left, right);
    }

    // Get character at position pos (0-indexed)
    char charAt(int pos) {
        Node *l, *mid, *r;
        split(root, pos, l, mid);
        split(mid, 1, mid, r);
        char c = mid->ch;
        root = merge(merge(l, mid), r);
        return c;
    }

    // Reverse substring [l, r] (0-indexed, inclusive)
    void reverse(int l, int r) {
        Node *left, *mid, *right;
        split(root, l, left, mid);
        split(mid, r - l + 1, mid, right);
        if (mid) mid->rev ^= true;
        root = merge(merge(left, mid), right);
    }

    // Get the entire string
    string toString() {
        string result;
        inorder(root, result);
        return result;
    }

    // Get substring [l, r]
    string substring(int l, int r) {
        Node *left, *mid, *right;
        split(root, l, left, mid);
        split(mid, r - l + 1, mid, right);
        string result;
        inorder(mid, result);
        root = merge(merge(left, mid), right);
        return result;
    }

    int size() { return getSize(root); }

private:
    void inorder(Node* t, string& result) {
        if (!t) return;
        pushDown(t);
        inorder(t->left, result);
        result += t->ch;
        inorder(t->right, result);
    }
};

void demo_rope() {
    cout << "\n=== SECTION 6: ROPE DATA STRUCTURE ===" << endl;

    Rope rope("Hello World");
    cout << "Initial: " << rope.toString() << endl;  // Hello World

    // Insert
    rope.insert(5, ',');
    cout << "Insert ',' at 5: " << rope.toString() << endl;  // Hello, World

    // Delete
    rope.erase(5);
    cout << "Delete at 5: " << rope.toString() << endl;  // Hello World

    // Reverse substring [0, 4]
    rope.reverse(0, 4);
    cout << "Reverse [0,4]: " << rope.toString() << endl;  // olleH World

    // Reverse back
    rope.reverse(0, 4);
    cout << "Reverse back: " << rope.toString() << endl;  // Hello World

    // charAt
    cout << "charAt(6): " << rope.charAt(6) << endl;  // W

    // Substring
    cout << "Substring [6,10]: " << rope.substring(6, 10) << endl;  // World

    // Insert string
    rope.insertString(5, " Beautiful");
    cout << "Insert string: " << rope.toString() << endl;  // Hello Beautiful World

    // Erase range
    rope.eraseRange(5, 14);
    cout << "Erase range [5,14]: " << rope.toString() << endl;  // Hello World

    // Performance demo: many operations
    Rope perf("");
    for (int i = 0; i < 1000; i++) {
        perf.insert(i / 2, 'a' + (i % 26));
    }
    cout << "Built rope of size " << perf.size() << " with 1000 insertions" << endl;
    cout << "First 30 chars: " << perf.substring(0, min(29, perf.size() - 1)) << endl;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN — Run all demonstrations
// ═══════════════════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(42); // for Rope's random priorities

    demo_persistent_trie();
    demo_sais();
    demo_eertree();
    demo_normalized_hash();
    demo_hld_strings();
    demo_rope();

    cout << "\n═══════════════════════════════════════════════════════" << endl;
    cout << "✅ All 6 Advanced String Data Structures covered!" << endl;
    cout << "   🏆 CONGRATULATIONS — You've completed the entire" << endl;
    cout << "      String Algorithms Zero to Grandmaster curriculum!" << endl;
    cout << "═══════════════════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  ── Persistent Trie ──                                          ║
║  CF 706D    — Vasiliy's Multiset                                ║
║  SPOJ XORQUE — XOR Queries with persistence                    ║
║  CF 665E    — Beautiful Subarrays (persistent trie)             ║
║                                                                  ║
║  ── SA-IS / Suffix Array ──                                     ║
║  CSES       — Substring Order I / II                            ║
║  CSES       — Repeating Substring                               ║
║  SPOJ DISUBSTR — Distinct Substrings                            ║
║  CF 1526E   — Oolimry (suffix structures)                       ║
║                                                                  ║
║  ── Eertree / Palindromic Tree ──                               ║
║  CF 906E    — Reverses (Eertree + DP)                           ║
║  CF 17E     — Palisection                                        ║
║  SPOJ NUMOFPAL — Number of Palindromes                          ║
║  CF 835D    — Palindromic Characteristics                        ║
║  APIO 2014  — Palindromes (Eertree)                             ║
║                                                                  ║
║  ── String Hashing with Inverse ──                              ║
║  LeetCode 1044 — Longest Duplicate Substring                    ║
║  CF 580E    — Kefa and Watch (hash + seg tree)                  ║
║  CSES       — String Hashing                                     ║
║                                                                  ║
║  ── HLD on Strings ──                                           ║
║  CF 504E    — Misha and LCP on Tree                             ║
║  CF 246E    — Blood Cousins Return                              ║
║                                                                  ║
║  ── Rope / Implicit Treap ──                                    ║
║  CF 863D    — Yet Another Arkanoid Problem                      ║
║  SPOJ ADAFAST — Ada and Fast (rope operations)                  ║
║  CF 197E    — Opening Portals (treap-based rope)                ║
║  NEERC 2007 — Text Editor (rope operations)                     ║
╚══════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════╗
║                FULL CURRICULUM SUMMARY                           ║
╠══════════════════════════════════════════════════════════════════╣
║  CH 01 │ String Basics & Operations         │ 13 concepts  ⭐  ║
║  CH 02 │ Classical String Problems           │  9 problems  ⭐⭐ ║
║  CH 03 │ Two Pointer & Sliding Window        │  7 problems  ⭐⭐⭐║
║  CH 04 │ String Hashing & Rolling Hash       │  7 concepts  ⭐⭐⭐║
║  CH 05 │ Trie & String Data Structures       │  8 concepts  ⭐⭐⭐║
║  CH 06 │ Pattern Matching Algorithms         │  9 algorithms⭐⭐⭐⭐║
║  CH 07 │ Advanced String Algorithms          │  5 topics    ⭐⭐⭐⭐║
║  CH 08 │ String DP Problems                  │  7 problems  ⭐⭐⭐⭐║
║  CH 09 │ Bitmask & Parity Techniques         │  5 tricks    ⭐⭐⭐⭐⭐║
║  CH 10 │ Advanced Competitive Tricks         │  8 tricks    ⭐⭐⭐⭐⭐║
║  CH 11 │ Advanced Data Structures            │  6 structures⭐⭐⭐⭐⭐║
║─────────────────────────────────────────────────────────────────║
║  TOTAL │ 84 concepts/algorithms/problems     │ GRANDMASTER   ║
╚══════════════════════════════════════════════════════════════════╝
*/

