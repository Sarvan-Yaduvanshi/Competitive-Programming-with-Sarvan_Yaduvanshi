/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-21 23:00:00
*/

/*
 * ============================================================================
 *       STRING MANIPULATION — CP PROBLEM PATTERNS (GM LEVEL)
 * ============================================================================
 *
 * This file contains PRACTICAL CP problems that use:
 *   ✅ Whitespace removal
 *   ✅ Case conversion (upper ↔ lower)
 *   ✅ Character classification
 *   ✅ String cleaning/normalization
 *   ✅ Bitwise character tricks
 *
 * ============================================================================
 */

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <numeric>

using namespace std;
#define nl '\n'
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

/*
 * ============================================================================
 *  PROBLEM 1: Check if Two Strings are Anagrams (Case-Insensitive)
 * ============================================================================
 *  LC 242 — Valid Anagram (with case-insensitive twist)
 *  "Listen" and "Silent" → true
 *
 *  KEY CONCEPT: Normalize case, then check character frequencies match.
 */

// ─────────── Brute Force: Sort and compare ───────────
bool isAnagram_BruteForce(string a, string b) {
    // Clean and lowercase both strings
    string cleanA, cleanB;
    for (char c : a) if (isalpha((unsigned char)c)) cleanA += tolower((unsigned char)c);
    for (char c : b) if (isalpha((unsigned char)c)) cleanB += tolower((unsigned char)c);

    sort(all(cleanA));
    sort(all(cleanB));
    return cleanA == cleanB;
    // Time: O(n log n), Space: O(n)
}

// ─────────── Intermediate: Frequency array ───────────
bool isAnagram_Freq(const string &a, const string &b) {
    int freq[26] = {};
    int countA = 0, countB = 0;

    for (char c : a) {
        if (isalpha((unsigned char)c)) {
            freq[tolower((unsigned char)c) - 'a']++;
            countA++;
        }
    }
    for (char c : b) {
        if (isalpha((unsigned char)c)) {
            freq[tolower((unsigned char)c) - 'a']--;
            countB++;
        }
    }

    if (countA != countB) return false;
    for (int i = 0; i < 26; i++) if (freq[i] != 0) return false;
    return true;
    // Time: O(n), Space: O(1) — fixed 26 slots
}

// ─────────── GM Level: Bitwise lowercase + frequency ───────────
bool isAnagram_GM(const string &a, const string &b) {
    int freq[26] = {};
    int ca = 0, cb = 0;

    for (char c : a) {
        // Check if alpha using ranges (no function call overhead)
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            freq[(c | 32) - 'a']++;  // (c | 32) forces lowercase, bitwise trick
            ca++;
        }
    }
    for (char c : b) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            freq[(c | 32) - 'a']--;
            cb++;
        }
    }

    if (ca != cb) return false;
    for (int i = 0; i < 26; i++) if (freq[i]) return false;
    return true;
}


/*
 * ============================================================================
 *  PROBLEM 2: First Non-Repeating Character (Case-Insensitive)
 * ============================================================================
 *  LC 387 — First Unique Character in a String
 *  "Stress" → 'T' (index 0, 't' appears once treating case-insensitive)
 */

int firstUnique_GM(const string &s) {
    int freq[26] = {};
    // Pass 1: Count frequencies (case-insensitive)
    for (char c : s) {
        if (isalpha((unsigned char)c)) {
            freq[(c | 32) - 'a']++;
        }
    }
    // Pass 2: Find first with freq == 1
    for (int i = 0; i < sz(s); i++) {
        if (isalpha((unsigned char)s[i]) && freq[(s[i] | 32) - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}


/*
 * ============================================================================
 *  PROBLEM 3: Caesar Cipher (Encryption/Decryption)
 * ============================================================================
 *  Shift each letter by `shift` positions. Wrap around z→a.
 *  "Hello" with shift=3 → "Khoor"
 *  Preserves case, ignores non-letters.
 */

// ─────────── Brute Force ───────────
string caesarBrute(string s, int shift) {
    shift = ((shift % 26) + 26) % 26;  // Normalize shift to 0-25
    for (char &c : s) {
        if (c >= 'a' && c <= 'z') {
            c = (c - 'a' + shift) % 26 + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' + shift) % 26 + 'A';
        }
    }
    return s;
}

// ─────────── GM Level: Single check using bitwise ───────────
string caesarGM(string s, int shift) {
    shift = ((shift % 26) + 26) % 26;
    for (char &c : s) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            // Determine base using bitwise: 'A' if uppercase, 'a' if lowercase
            char base = (c & 32) ? 'a' : 'A';  // bit 5 set → lowercase
            c = (c - base + shift) % 26 + base;
        }
    }
    return s;
}


/*
 * ============================================================================
 *  PROBLEM 4: Check if String is Pangram
 * ============================================================================
 *  A pangram contains every letter (a-z) at least once.
 *  "The Quick Brown Fox Jumps Over The Lazy Dog" → true
 */

// ─────────── Brute Force: Use a set ───────────
bool isPangram_Brute(const string &s) {
    bool seen[26] = {};
    for (char c : s) {
        if (isalpha((unsigned char)c)) {
            seen[tolower((unsigned char)c) - 'a'] = true;
        }
    }
    for (int i = 0; i < 26; i++) if (!seen[i]) return false;
    return true;
}

// ─────────── GM Level: Use bitmask (26 bits for 26 letters) ───────────
// Each bit represents one letter. When all 26 bits are set, it's a pangram.
bool isPangram_GM(const string &s) {
    int mask = 0;
    for (char c : s) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            mask |= (1 << ((c | 32) - 'a'));  // Set the bit for this letter
        }
    }
    return mask == (1 << 26) - 1;  // All 26 bits set = 0x3FFFFFF
    // Time: O(n), Space: O(1) — just one integer!
}


/*
 * ============================================================================
 *  PROBLEM 5: Determine if String Has All Unique Characters
 * ============================================================================
 *  "abcde" → true, "aabcde" → false
 */

// ─────────── GM Level: Bitmask for lowercase letters ───────────
bool hasUniqueChars_GM(const string &s) {
    int mask = 0;
    for (char c : s) {
        int idx = (c | 32) - 'a';
        if (idx >= 0 && idx < 26) {
            if (mask & (1 << idx)) return false;  // already seen
            mask |= (1 << idx);
        }
    }
    return true;
}


/*
 * ============================================================================
 *  PROBLEM 6: Detect Capital Use (LC 520)
 * ============================================================================
 *  A word has correct capital usage if:
 *  1. All letters are capitals: "USA" → true
 *  2. All letters are lowercase: "leetcode" → true
 *  3. Only first letter is capital: "Google" → true
 */

bool detectCapitalUse_Brute(const string &word) {
    int upperCount = 0;
    for (char c : word) {
        if (c >= 'A' && c <= 'Z') upperCount++;
    }
    // All upper, all lower, or only first is upper
    return upperCount == sz(word) || upperCount == 0
        || (upperCount == 1 && word[0] >= 'A' && word[0] <= 'Z');
}

// ─────────── GM Level: Bitwise check ───────────
bool detectCapitalUse_GM(const string &word) {
    int upCnt = 0;
    for (char c : word) {
        // Check if uppercase: bit 5 is NOT set for letters A-Z
        if (!(c & 32) && isalpha((unsigned char)c)) upCnt++;
    }
    return upCnt == sz(word) || upCnt == 0
        || (upCnt == 1 && !(word[0] & 32));
}


/*
 * ============================================================================
 *  PROBLEM 7: ROT13 Cipher
 * ============================================================================
 *  Each letter is shifted 13 places. Applying ROT13 twice returns original.
 *  "Hello" → "Uryyb", "Uryyb" → "Hello"
 */

string rot13(string s) {
    for (char &c : s) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            char base = (c & 32) ? 'a' : 'A';
            c = (c - base + 13) % 26 + base;
        }
    }
    return s;
}


/*
 * ============================================================================
 *  PROBLEM 8: Isomorphic Strings (LC 205)
 * ============================================================================
 *  "egg" and "add" → true (e→a, g→d)
 *  "foo" and "bar" → false
 *  Case-sensitive, but concept uses character mapping.
 */

bool isIsomorphic(const string &s, const string &t) {
    if (sz(s) != sz(t)) return false;

    int mapST[256] = {};  // s[i] → t[i] mapping
    int mapTS[256] = {};  // t[i] → s[i] mapping (reverse)

    for (int i = 0; i < sz(s); i++) {
        unsigned char cs = s[i], ct = t[i];

        if (mapST[cs] == 0 && mapTS[ct] == 0) {
            mapST[cs] = ct + 1;  // +1 to distinguish from "not set" (0)
            mapTS[ct] = cs + 1;
        } else if (mapST[cs] != ct + 1 || mapTS[ct] != cs + 1) {
            return false;
        }
    }
    return true;
}


/*
 * ============================================================================
 *  PROBLEM 9: String Compression (LC 443)
 * ============================================================================
 *  "aabbccc" → "a2b2c3"
 *  "abc" → "abc" (single chars not compressed)
 */

string compress(const string &s) {
    string result;
    int n = sz(s);
    int i = 0;

    while (i < n) {
        char ch = s[i];
        int count = 0;
        while (i < n && s[i] == ch) { count++; i++; }
        result += ch;
        if (count > 1) result += to_string(count);
    }
    return result;
}


/*
 * ============================================================================
 *  PROBLEM 10: Count Words in a String (Handling Multiple Spaces)
 * ============================================================================
 *  "  Hello   World  " → 2 words
 */

int countWords(const string &s) {
    int count = 0;
    bool inWord = false;
    for (char c : s) {
        if (isspace((unsigned char)c)) {
            inWord = false;
        } else {
            if (!inWord) count++;
            inWord = true;
        }
    }
    return count;
}


/*
 * ============================================================================
 *  MASTER SUMMARY — ALL BITWISE CHARACTER TRICKS
 * ============================================================================
 *
 *  ┌────────────────────────────────┬──────────────────────────────────┐
 *  │ Operation                      │ Code                             │
 *  ├────────────────────────────────┼──────────────────────────────────┤
 *  │ char → lowercase               │ c | 32     or  c | ' '           │
 *  │ char → uppercase               │ c & ~32    or  c & '_'           │
 *  │ Toggle case                    │ c ^ 32     or  c ^ ' '           │
 *  │ Is lowercase? (letter only)    │ (c & 32) != 0                    │
 *  │ Is uppercase? (letter only)    │ (c & 32) == 0                    │
 *  │ Case-insensitive compare       │ (a | 32) == (b | 32)             │
 *  │ Letter index (0-25)            │ (c | 32) - 'a'                   │
 *  │ Check if letter                │ ((c|32) >= 'a' && (c|32) <= 'z') │
 *  │ Check if digit                 │ c >= '0' && c <= '9'             │
 *  │ Digit value                    │ c - '0'                          │
 *  │ Pangram check (bitmask)        │ mask |= (1 << ((c|32) - 'a'))    │
 *  │ All unique (bitmask)           │ if (mask & (1 << idx)) → dupe    │
 *  │ Caesar shift                   │ (c - base + shift) % 26 + base   │
 *  │ Get base ('A' or 'a')          │ (c & 32) ? 'a' : 'A'             │
 *  └────────────────────────────────┴──────────────────────────────────┘
 *
 *  🔥 TIP: In competitive programming, (c | 32) - 'a' is the fastest way
 *     to get a letter's index (0-25) regardless of case. Use it for:
 *     - Frequency arrays
 *     - Bitmask operations
 *     - Hash computations
 *
 * ============================================================================
 */

void solve() {
    cout << "═══════════════════════════════════════════════════" << nl;
    cout << "  STRING MANIPULATION — CP PROBLEM DEMOS" << nl;
    cout << "═══════════════════════════════════════════════════" << nl << nl;

    // Problem 1: Anagram
    cout << "─── ANAGRAM CHECK ───" << nl;
    cout << "\"Listen\" vs \"Silent\": " << isAnagram_GM("Listen", "Silent") << nl;
    cout << "\"Hello\" vs \"World\":   " << isAnagram_GM("Hello", "World") << nl;
    cout << "\"Dormitory\" vs \"Dirty Room\": " << isAnagram_GM("Dormitory", "DirtyRoom") << nl << nl;

    // Problem 2: First Unique
    cout << "─── FIRST UNIQUE CHARACTER ───" << nl;
    cout << "\"leetcode\" → index " << firstUnique_GM("leetcode") << nl;
    cout << "\"loveleetcode\" → index " << firstUnique_GM("loveleetcode") << nl;
    cout << "\"aabb\" → index " << firstUnique_GM("aabb") << nl << nl;

    // Problem 3: Caesar Cipher
    cout << "─── CAESAR CIPHER ───" << nl;
    cout << "\"Hello World\" shift 3: \"" << caesarGM("Hello World", 3) << "\"" << nl;
    cout << "\"Khoor Zruog\" shift -3: \"" << caesarGM("Khoor Zruog", -3) << "\"" << nl << nl;

    // Problem 4: Pangram
    cout << "─── PANGRAM CHECK ───" << nl;
    cout << "\"The Quick Brown Fox Jumps Over The Lazy Dog\": "
         << isPangram_GM("The Quick Brown Fox Jumps Over The Lazy Dog") << nl;
    cout << "\"Hello World\": " << isPangram_GM("Hello World") << nl << nl;

    // Problem 5: Unique Characters
    cout << "─── UNIQUE CHARACTERS ───" << nl;
    cout << "\"abcde\": " << hasUniqueChars_GM("abcde") << nl;
    cout << "\"aabcde\": " << hasUniqueChars_GM("aabcde") << nl << nl;

    // Problem 6: Detect Capital
    cout << "─── DETECT CAPITAL ───" << nl;
    cout << "\"USA\": " << detectCapitalUse_GM("USA") << nl;
    cout << "\"leetcode\": " << detectCapitalUse_GM("leetcode") << nl;
    cout << "\"Google\": " << detectCapitalUse_GM("Google") << nl;
    cout << "\"FlaG\": " << detectCapitalUse_GM("FlaG") << nl << nl;

    // Problem 7: ROT13
    cout << "─── ROT13 ───" << nl;
    cout << "\"Hello World\" → \"" << rot13("Hello World") << "\"" << nl;
    cout << "\"Uryyb Jbeyq\" → \"" << rot13("Uryyb Jbeyq") << "\"" << nl << nl;

    // Problem 8: Isomorphic
    cout << "─── ISOMORPHIC STRINGS ───" << nl;
    cout << "\"egg\" & \"add\": " << isIsomorphic("egg", "add") << nl;
    cout << "\"foo\" & \"bar\": " << isIsomorphic("foo", "bar") << nl;
    cout << "\"paper\" & \"title\": " << isIsomorphic("paper", "title") << nl << nl;

    // Problem 9: Compression
    cout << "─── STRING COMPRESSION ───" << nl;
    cout << "\"aabbccc\" → \"" << compress("aabbccc") << "\"" << nl;
    cout << "\"abc\" → \"" << compress("abc") << "\"" << nl;
    cout << "\"aaabbbbcc\" → \"" << compress("aaabbbbcc") << "\"" << nl << nl;

    // Problem 10: Word Count
    cout << "─── WORD COUNT ───" << nl;
    cout << "\"  Hello   World  \": " << countWords("  Hello   World  ") << " words" << nl;
    cout << "\"OneWord\": " << countWords("OneWord") << " word" << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

