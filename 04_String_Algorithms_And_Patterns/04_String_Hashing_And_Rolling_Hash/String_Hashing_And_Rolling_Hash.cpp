/*
╔══════════════════════════════════════════════════════════════════════════════╗
║     CHAPTER 04 — STRING HASHING & ROLLING HASH                            ║
║     From Zero to Grandmaster — Hash Everything                             ║
║     Author: Sarvan Yaduvanshi                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Polynomial Rolling Hash (Theory + Implementation)
 2. Rabin–Karp Pattern Matching
 3. Double Hashing (Collision-safe)
 4. Prefix Hash Array (Build once, query O(1))
 5. Substring Hash Queries O(1)
 6. Avoiding Collisions (Techniques & Best Practices)
 7. Repeated Substring Detection

CORE THEORY — STRING HASHING:
─────────────────────────────
 A hash function maps a string to an integer.
 Goal: Two DIFFERENT strings should (almost certainly) have DIFFERENT hashes.

 POLYNOMIAL HASH:
   hash(s) = s[0]*p^0 + s[1]*p^1 + s[2]*p^2 + ... + s[n-1]*p^(n-1)  (mod M)

   Where:
   • p = prime base (commonly 31 for lowercase, 53 for mixed)
   • M = large prime modulus (1e9+7 or 1e9+9)

 WHY POLYNOMIAL?
   • Different strings give different hash values (with high probability)
   • We can compute hash of any substring in O(1) using prefix hashes
   • Rolling: adding/removing characters is O(1)

 COLLISION PROBABILITY:
   For a single comparison: ~1/M ≈ 10^(-9) with good M
   For n comparisons: ~n/M
   With double hashing (two different M): ~n/M1/M2 ≈ 10^(-18) per query

 CHOOSING PARAMETERS:
   Base p:  31 (lowercase), 37, 53 (mixed case), 131
   Mod M:   1e9+7, 1e9+9, large primes near 2^61
   NEVER use M = 2^k (easy to hack!)

 APPLICATIONS:
   • Pattern matching (Rabin-Karp)
   • Counting distinct substrings
   • Longest common substring (binary search + hashing)
   • Palindrome checking O(1) per query
   • String comparison in suffix arrays
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <chrono>
#include <cassert>
using namespace std;
using i64 = long long;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: POLYNOMIAL ROLLING HASH
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 hash(s[0..n-1]) = Σ (s[i] - 'a' + 1) * p^i  (mod M)

 We add 1 to avoid (s[i] - 'a') = 0, which would make leading chars invisible.

 ROLLING PROPERTY:
   To slide window from s[l..r] to s[l+1..r+1]:
     new_hash = (old_hash - s[l] * p^0) / p + s[r+1] * p^(window_size-1)
   Using modular inverse instead of division.

 SIMPLE HASH (full string):
   Just iterate and accumulate: hash = hash * p + s[i]
*/

// Simple polynomial hash of entire string
i64 polyHash(const string& s, i64 p = 31, i64 mod = 1000000007LL) {
    i64 hash = 0;
    i64 power = 1;
    for (char c : s) {
        hash = (hash + (c - 'a' + 1) * power) % mod;
        power = (power * p) % mod;
    }
    return hash;
}

// Alternative: hash computed as hash = hash * p + c (Horner's method)
// This puts more weight on the FIRST character
i64 hornerHash(const string& s, i64 p = 31, i64 mod = 1000000007LL) {
    i64 hash = 0;
    for (char c : s) {
        hash = (hash * p + (c - 'a' + 1)) % mod;
    }
    return hash;
}

void demo_poly_hash() {
    cout << "=== SECTION 1: POLYNOMIAL ROLLING HASH ===" << endl;
    string s1 = "hello", s2 = "world", s3 = "hello";
    cout << "hash('hello'): " << polyHash(s1) << endl;
    cout << "hash('world'): " << polyHash(s2) << endl;
    cout << "hash('hello') again: " << polyHash(s3) << endl;
    cout << "Same? " << (polyHash(s1) == polyHash(s3)) << endl;  // 1

    cout << "Horner hash('hello'): " << hornerHash(s1) << endl;
    cout << "Horner hash('world'): " << hornerHash(s2) << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: RABIN–KARP PATTERN MATCHING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Instead of comparing pattern with every substring (O(nm)):
   1. Compute hash of pattern
   2. Slide window over text, compute hash of each window in O(1)
   3. When hash matches → verify with actual comparison (avoid false positive)

 ROLLING HASH UPDATE:
   Using Horner: hash(s[l+1..r+1]) = (hash(s[l..r]) - s[l]*p^(m-1)) * p + s[r+1]

 Time: O(n + m) average, O(nm) worst case (many collisions)
 With double hashing: practically O(n + m) always.

 RABIN-KARP vs KMP:
   • KMP: O(n+m) guaranteed, harder to code
   • Rabin-Karp: O(n+m) expected, easier to code, extends to 2D
*/

vector<int> rabinKarp(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size(), m = pattern.size();
    if (m > n) return result;

    const i64 p = 31;
    const i64 mod = 1000000007LL;

    // Precompute p^m
    i64 pm = 1;
    for (int i = 0; i < m; i++) pm = (pm * p) % mod;

    // Hash of pattern
    i64 hashP = 0, power = 1;
    for (int i = 0; i < m; i++) {
        hashP = (hashP + (pattern[i] - 'a' + 1) * power) % mod;
        power = (power * p) % mod;
    }

    // Rolling hash of text windows
    i64 hashT = 0;
    power = 1;
    for (int i = 0; i < m; i++) {
        hashT = (hashT + (text[i] - 'a' + 1) * power) % mod;
        if (i < m - 1) power = (power * p) % mod;
    }

    // Check first window
    if (hashT == hashP && text.substr(0, m) == pattern) {
        result.push_back(0);
    }

    // Slide window
    for (int i = 1; i <= n - m; i++) {
        // Remove text[i-1], add text[i+m-1]
        hashT = (hashT - (text[i - 1] - 'a' + 1) + mod) % mod;
        hashT = (hashT * modPow(p, mod - 2, mod)) % mod;  // divide by p
        // This is slow! Better approach: use prefix hashes (Section 4)
        // OR use different formulation

        // Let me use a cleaner Horner-based approach:
        break;  // will use prefix hash approach instead
    }
    result.clear();

    // CLEAN RABIN-KARP using prefix hashes:
    // Build prefix hash array
    vector<i64> h(n + 1, 0), pw(n + 1, 1);
    for (int i = 0; i < n; i++) {
        h[i + 1] = (h[i] + (text[i] - 'a' + 1) * pw[i]) % mod;
        pw[i + 1] = (pw[i] * p) % mod;
    }

    // Hash of pattern using same scheme
    hashP = 0;
    for (int i = 0; i < m; i++) {
        hashP = (hashP + (pattern[i] - 'a' + 1) * pw[i]) % mod;
    }

    // Check each window
    for (int i = 0; i <= n - m; i++) {
        // hash of text[i..i+m-1] = (h[i+m] - h[i]) / p^i
        // Equivalent: hash(text[i..i+m-1]) * p^i = h[i+m] - h[i]
        // Compare: (h[i+m] - h[i]) with hashP * p^i
        i64 textHash = (h[i + m] - h[i] + mod) % mod;
        i64 patHash = (hashP * pw[i]) % mod;

        if (textHash == patHash) {
            // Verify (optional with double hashing, but safer)
            if (text.substr(i, m) == pattern) {
                result.push_back(i);
            }
        }
    }

    return result;
}

// Helper: modular exponentiation
i64 modPow(i64 base, i64 exp, i64 mod) {
    i64 result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

void demo_rabin_karp() {
    cout << "\n=== SECTION 2: RABIN-KARP ===" << endl;
    auto matches = rabinKarp("aabaabaaab", "aab");
    cout << "Pattern 'aab' in 'aabaabaaab' at: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;

    matches = rabinKarp("abcabcabc", "abc");
    cout << "Pattern 'abc' in 'abcabcabc' at: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: DOUBLE HASHING (Collision-safe)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Single hash collision probability: ~1/M per comparison
 With n comparisons: ~n/M (birthday paradox makes it worse: ~n²/M)

 DOUBLE HASHING: Use TWO independent hash functions
   hash1 with (p1, M1)
   hash2 with (p2, M2)
   Collision probability: ~1/(M1*M2) per comparison ≈ 10^(-18)

 PRACTICALLY UNHACKABLE when using random bases!

 ANTI-HACK TECHNIQUE:
   Generate random base at runtime:
     mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
     int p = uniform_int_distribution<int>(256, 1e9)(rng);
*/

struct DoubleHash {
    i64 h1, h2;
    bool operator==(const DoubleHash& o) const { return h1 == o.h1 && h2 == o.h2; }
};

struct DoubleHasher {
    static const i64 MOD1 = 1000000007LL;
    static const i64 MOD2 = 998244353LL;
    i64 p1, p2;

    DoubleHasher() {
        // Random bases for anti-hack
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        p1 = uniform_int_distribution<i64>(31, 1000000)(rng);
        p2 = uniform_int_distribution<i64>(37, 1000000)(rng);
    }

    DoubleHash hashString(const string& s) {
        i64 h1 = 0, h2 = 0;
        i64 pow1 = 1, pow2 = 1;
        for (char c : s) {
            h1 = (h1 + (c - 'a' + 1) * pow1) % MOD1;
            h2 = (h2 + (c - 'a' + 1) * pow2) % MOD2;
            pow1 = (pow1 * p1) % MOD1;
            pow2 = (pow2 * p2) % MOD2;
        }
        return {h1, h2};
    }
};

void demo_double_hash() {
    cout << "\n=== SECTION 3: DOUBLE HASHING ===" << endl;
    DoubleHasher dh;
    auto h1 = dh.hashString("hello");
    auto h2 = dh.hashString("world");
    auto h3 = dh.hashString("hello");
    cout << "hash('hello'): (" << h1.h1 << ", " << h1.h2 << ")" << endl;
    cout << "hash('world'): (" << h2.h1 << ", " << h2.h2 << ")" << endl;
    cout << "Same hello? " << (h1 == h3) << endl;  // 1
    cout << "hello == world? " << (h1 == h2) << endl;  // 0
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4 & 5: PREFIX HASH ARRAY + O(1) SUBSTRING QUERIES
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 BUILDING PREFIX HASH: O(n)
   h[0] = 0
   h[i] = h[i-1] + s[i-1] * p^(i-1)   (mod M)

 QUERYING SUBSTRING HASH s[l..r] in O(1):
   hash(s[l..r]) = (h[r+1] - h[l]) * inverse(p^l)   (mod M)

 Equivalently (avoiding modular inverse):
   hash(s[l..r]) * p^l = h[r+1] - h[l]
   Compare: (h[r1+1] - h[l1]) * p^l2 == (h[r2+1] - h[l2]) * p^l1

 OR use the NORMALIZED approach: compare (h[r+1] - h[l]) directly,
 but multiply the shorter one by appropriate power of p.

 THIS IS THE MOST USEFUL STRING HASHING STRUCTURE IN CP!
*/

struct StringHasher {
    // Double hashing for safety
    static const i64 MOD1 = 1000000007LL;
    static const i64 MOD2 = 998244353LL;

    int n;
    vector<i64> h1, h2, pw1, pw2;
    i64 p1, p2;

    StringHasher() : n(0), p1(31), p2(37) {}

    StringHasher(const string& s, i64 base1 = 31, i64 base2 = 37)
        : n(s.size()), p1(base1), p2(base2) {
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        pw1.resize(n + 1, 1);
        pw2.resize(n + 1, 1);

        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] + (s[i] - 'a' + 1) * pw1[i]) % MOD1;
            h2[i + 1] = (h2[i] + (s[i] - 'a' + 1) * pw2[i]) % MOD2;
            pw1[i + 1] = (pw1[i] * p1) % MOD1;
            pw2[i + 1] = (pw2[i] * p2) % MOD2;
        }
    }

    // Get hash of substring s[l..r] (0-indexed, inclusive)
    // Returns {hash1, hash2} both multiplied by p^l (avoid modular inverse)
    pair<i64, i64> getHash(int l, int r) const {
        i64 hash1 = (h1[r + 1] - h1[l] + MOD1) % MOD1;
        i64 hash2 = (h2[r + 1] - h2[l] + MOD2) % MOD2;
        return {hash1, hash2};
    }

    // Compare substring s[l1..r1] with s[l2..r2] in O(1)
    bool compare(int l1, int r1, int l2, int r2) const {
        auto [ha1, ha2] = getHash(l1, r1);
        auto [hb1, hb2] = getHash(l2, r2);

        // Normalize: multiply each by the other's starting power
        // ha * p^l2 == hb * p^l1
        i64 left1 = ha1 * pw1[l2] % MOD1;
        i64 right1 = hb1 * pw1[l1] % MOD1;
        i64 left2 = ha2 * pw2[l2] % MOD2;
        i64 right2 = hb2 * pw2[l1] % MOD2;

        return left1 == right1 && left2 == right2;
    }

    // Compare s[l1..r1] with another string's t[l2..r2]
    bool compareWith(int l1, int r1, const StringHasher& other, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false;
        auto [ha1, ha2] = getHash(l1, r1);
        auto [hb1, hb2] = other.getHash(l2, r2);

        i64 left1 = ha1 * pw1[l2] % MOD1;
        i64 right1 = hb1 * pw1[l1] % MOD1;
        i64 left2 = ha2 * pw2[l2] % MOD2;
        i64 right2 = hb2 * pw2[l1] % MOD2;

        return left1 == right1 && left2 == right2;
    }

    // Check if s[l..r] is a palindrome using forward + reverse hash
    // Need separate reverse hasher for this
};

// Reverse hasher for palindrome checking
struct PalindromeHasher {
    StringHasher fwd, rev;

    PalindromeHasher(const string& s) : fwd(s) {
        string r = s;
        reverse(r.begin(), r.end());
        rev = StringHasher(r);
    }

    bool isPalindrome(int l, int r) {
        int n = fwd.n;
        // Reverse of s[l..r] is rev[(n-1-r)..(n-1-l)]
        return fwd.compare(l, r, 0, 0) ? false : // placeholder
               fwd.getHash(l, r).first * fwd.pw1[n - 1 - r] % StringHasher::MOD1 ==
               rev.getHash(n - 1 - r, n - 1 - l).first * fwd.pw1[l] % StringHasher::MOD1
               &&
               fwd.getHash(l, r).second * fwd.pw2[n - 1 - r] % StringHasher::MOD2 ==
               rev.getHash(n - 1 - r, n - 1 - l).second * fwd.pw2[l] % StringHasher::MOD2;
    }
};

void demo_prefix_hash() {
    cout << "\n=== SECTION 4 & 5: PREFIX HASH + O(1) QUERIES ===" << endl;
    string s = "abcabcabc";
    StringHasher sh(s);

    // Compare s[0..2] = "abc" with s[3..5] = "abc"
    cout << "s[0..2] == s[3..5]: " << sh.compare(0, 2, 3, 5) << endl;  // 1
    cout << "s[0..2] == s[6..8]: " << sh.compare(0, 2, 6, 8) << endl;  // 1
    cout << "s[0..2] == s[1..3]: " << sh.compare(0, 2, 1, 3) << endl;  // 0

    // Cross-string comparison
    StringHasher sh2("xyzabcxyz");
    cout << "s[0..2] == sh2[3..5]: " << sh.compareWith(0, 2, sh2, 3, 5) << endl;  // 1
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: AVOIDING COLLISIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 COLLISION = Two different strings have the same hash.

 HOW TO AVOID:
   1. USE LARGE PRIME MODULUS: 1e9+7 or 1e9+9
      Never use mod = 2^k (trivially hackable)

   2. DOUBLE HASHING: Two independent (base, mod) pairs
      Probability of collision: ~1/(M1*M2) per comparison

   3. RANDOM BASE: Generate base at runtime
      Prevents adversarial test cases (anti-hack)

   4. VERIFY ON MATCH: When hashes match, do actual string comparison
      Makes it O(nm) worst case, but practically O(n+m)

   5. USE __int128 for very large modulus (near 2^61 - 1)

 BIRTHDAY PARADOX WARNING:
   With n strings and mod M:
   Expected collisions ≈ n²/(2M)
   For n = 10^5 and M = 10^9: collisions ≈ 5000! → Need double hash

 RECOMMENDED SETUP:
   Base: random in [256, 10^6]
   Mod1: 1e9 + 7 = 1000000007
   Mod2: 1e9 + 9 = 1000000009  (or 998244353)
*/

// Anti-hack hasher with random base
struct AntiHackHasher {
    static const i64 MOD = (1LL << 61) - 1;  // Mersenne prime, very large
    i64 base;
    int n;
    vector<i64> h, pw;

    // Modular multiplication for large numbers
    static i64 modmul(i64 a, i64 b) {
        __int128 res = (__int128)a * b;
        return (i64)(res % MOD);
    }

    static i64 modsub(i64 a, i64 b) {
        return a >= b ? a - b : a + MOD - b;
    }

    AntiHackHasher() {}
    AntiHackHasher(const string& s) : n(s.size()), h(s.size() + 1), pw(s.size() + 1) {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        base = uniform_int_distribution<i64>(256, MOD - 1)(rng);
        pw[0] = 1;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = modmul(pw[i], base);
        }
        h[0] = 0;
        for (int i = 0; i < n; i++) {
            h[i + 1] = (modmul(h[i], base) + s[i]) % MOD;
        }
    }

    // Hash of s[l..r], Horner-style (most significant first)
    i64 getHash(int l, int r) const {
        return modsub(h[r + 1], modmul(h[l], pw[r - l + 1]));
    }
};

void demo_collision_avoidance() {
    cout << "\n=== SECTION 6: COLLISION AVOIDANCE ===" << endl;
    AntiHackHasher ah("abcabcabc");
    cout << "hash[0..2]: " << ah.getHash(0, 2) << endl;
    cout << "hash[3..5]: " << ah.getHash(3, 5) << endl;
    cout << "Same? " << (ah.getHash(0, 2) == ah.getHash(3, 5)) << endl;  // 1
    cout << "hash[0..2] vs [1..3]: " << (ah.getHash(0, 2) == ah.getHash(1, 3)) << endl;  // 0
    cout << "Using Mersenne prime 2^61-1 for maximum safety" << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: REPEATED SUBSTRING DETECTION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 PROBLEM 1: Does string s have a repeated substring of length L?
   → Hash all substrings of length L, check for duplicates.
   → O(n) with hashing, O(n log n) with sorting.

 PROBLEM 2: Longest repeated substring
   → Binary search on length L + hashing check.
   → O(n log n)

 PROBLEM 3: Repeated substring pattern (s = t+t+...+t?)
   → s has period p if s[i] == s[i+p] for all valid i
   → Period p divides n and s is made of n/p copies of s[0..p-1]
   → Check: (s+s).find(s, 1) < n

 PROBLEM 4: Count distinct substrings
   → Sum over all lengths L: distinct hashes of length-L substrings
   → O(n²) with hashing, O(n) with suffix array
*/

// Check if there's a repeated substring of exactly length L
bool hasRepeatedSubstring(const string& s, int L) {
    if (L == 0) return true;
    int n = s.size();
    AntiHackHasher ah(s);
    unordered_set<i64> seen;
    for (int i = 0; i + L - 1 < n; i++) {
        i64 h = ah.getHash(i, i + L - 1);
        if (seen.count(h)) return true;
        seen.insert(h);
    }
    return false;
}

// Longest repeated substring — Binary search + hashing — O(n log n)
string longestRepeatedSubstring(const string& s) {
    int n = s.size();
    int lo = 0, hi = n - 1, bestLen = 0;
    int bestPos = 0;

    AntiHackHasher ah(s);

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        // Check if there's a repeated substring of length mid
        unordered_map<i64, int> seen;  // hash → first occurrence index
        bool found = false;
        for (int i = 0; i + mid - 1 < n; i++) {
            i64 h = ah.getHash(i, i + mid - 1);
            if (seen.count(h)) {
                found = true;
                bestLen = mid;
                bestPos = i;
                break;
            }
            seen[h] = i;
        }
        if (found) lo = mid + 1;
        else hi = mid - 1;
    }

    return bestLen > 0 ? s.substr(bestPos, bestLen) : "";
}

// Count distinct substrings — O(n²) with hashing
i64 countDistinctSubstrings(const string& s) {
    int n = s.size();
    AntiHackHasher ah(s);
    unordered_set<i64> seen;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            seen.insert(ah.getHash(i, j));
        }
    }
    return seen.size();
}

// Check if s is a repeated pattern (s = t^k for some t and k >= 2)
bool isRepeatedPattern(const string& s) {
    string doubled = s + s;
    // Find s in doubled starting from index 1
    size_t pos = doubled.find(s, 1);
    return pos < s.size();
}

// Find shortest period of string
int shortestPeriod(const string& s) {
    int n = s.size();
    AntiHackHasher ah(s);
    for (int p = 1; p <= n; p++) {
        if (n % p != 0) continue;
        // Check if s[0..p-1] repeated n/p times equals s
        bool ok = true;
        for (int i = p; i < n; i += p) {
            if (ah.getHash(0, p - 1) != ah.getHash(i, i + p - 1)) {
                ok = false;
                break;
            }
        }
        if (ok) return p;
    }
    return n;
}

void demo_repeated() {
    cout << "\n=== SECTION 7: REPEATED SUBSTRING DETECTION ===" << endl;
    cout << "Has repeated len 3 in 'abcabc': " << hasRepeatedSubstring("abcabc", 3) << endl;  // 1
    cout << "Longest repeated in 'banana': " << longestRepeatedSubstring("banana") << endl;    // "ana"
    cout << "Distinct substrings of 'abc': " << countDistinctSubstrings("abc") << endl;        // 6
    cout << "Distinct substrings of 'aaa': " << countDistinctSubstrings("aaa") << endl;        // 3
    cout << "Is 'abcabc' repeated pattern? " << isRepeatedPattern("abcabc") << endl;           // 1
    cout << "Is 'abcab' repeated pattern? " << isRepeatedPattern("abcab") << endl;             // 0
    cout << "Shortest period of 'abcabc': " << shortestPeriod("abcabc") << endl;               // 3 (but 7%3!=0, so 7)
    cout << "Shortest period of 'abcabcabc': " << shortestPeriod("abcabcabc") << endl;         // 3
    cout << "Shortest period of 'aaaa': " << shortestPeriod("aaaa") << endl;                   // 1
}

// ═══════════════════════════════════════════════════════════════
// BONUS: LONGEST COMMON SUBSTRING (Binary Search + Hashing)
// ═══════════════════════════════════════════════════════════════
/*
 PROBLEM: Find longest common substring between two strings.
 APPROACH: Binary search on length + hashing check.

 For each candidate length L:
   • Hash all substrings of length L in s1 → store in set
   • Hash all substrings of length L in s2 → check against set
   • If match found → try longer, else try shorter

 Time: O((n+m) * log(min(n,m))), Space: O(n+m)
*/

string longestCommonSubstring(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    int lo = 0, hi = min(n, m), bestLen = 0, bestPos = 0;

    AntiHackHasher ah1(s1), ah2(s2);

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (mid == 0) { lo = 1; continue; }

        unordered_set<i64> hashes;
        for (int i = 0; i + mid - 1 < n; i++) {
            hashes.insert(ah1.getHash(i, i + mid - 1));
        }

        bool found = false;
        for (int i = 0; i + mid - 1 < m; i++) {
            if (hashes.count(ah2.getHash(i, i + mid - 1))) {
                found = true;
                bestLen = mid;
                bestPos = i;  // position in s2
                break;
            }
        }

        if (found) lo = mid + 1;
        else hi = mid - 1;
    }

    return bestLen > 0 ? s2.substr(bestPos, bestLen) : "";
}

void demo_lcs_hash() {
    cout << "\n=== BONUS: LONGEST COMMON SUBSTRING ===" << endl;
    cout << "LCS of 'abcdef' and 'xbcdyz': " << longestCommonSubstring("abcdef", "xbcdyz") << endl;
    cout << "LCS of 'abcabc' and 'cabcab': " << longestCommonSubstring("abcabc", "cabcab") << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_poly_hash();
    demo_rabin_karp();
    demo_double_hash();
    demo_prefix_hash();
    demo_collision_avoidance();
    demo_repeated();
    demo_lcs_hash();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 7 String Hashing concepts covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 28   — Implement strStr() [Rabin-Karp]               ║
║  LeetCode 187  — Repeated DNA Sequences                         ║
║  LeetCode 459  — Repeated Substring Pattern                     ║
║  LeetCode 1044 — Longest Duplicate Substring                    ║
║  LeetCode 718  — Maximum Length of Repeated Subarray             ║
║  LeetCode 1062 — Longest Repeating Substring                    ║
║  CSES          — String Hashing                                  ║
║  CSES          — Finding Patterns                                ║
║  CF 271D       — Good Substrings (hashing + trie)               ║
║  CF 126B       — Password (hashing + prefix)                    ║
║  SPOJ NHAY     — A Needle in the Haystack                       ║
║  SPOJ EPALIN   — Extend to Palindrome (hashing)                ║
╚══════════════════════════════════════════════════════════════════╝
*/

