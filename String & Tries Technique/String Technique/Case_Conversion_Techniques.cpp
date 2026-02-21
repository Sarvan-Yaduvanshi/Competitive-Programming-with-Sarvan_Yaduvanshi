/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-21 22:50:00
*/

/*
 * ============================================================================
 *       STRING CASE CONVERSION — ZERO TO GRAND MASTER (GM) LEVEL
 * ============================================================================
 *
 * TOPIC: Convert lowercase ↔ uppercase (and vice versa)
 *
 * ──────────────────────── ASCII TABLE FUNDAMENTALS ──────────────────────────
 *
 *   Character     ASCII Value
 *   ─────────     ───────────
 *   'A'           65
 *   'B'           66
 *   ...           ...
 *   'Z'           90
 *   'a'           97
 *   'b'           98
 *   ...           ...
 *   'z'           122
 *   '0'           48
 *   '9'           57
 *   ' '           32
 *
 *   KEY INSIGHT: 'a' - 'A' = 97 - 65 = 32
 *   So the difference between lowercase and uppercase is ALWAYS 32.
 *
 *   BITWISE INSIGHT:
 *   'A' = 0100 0001 (65)
 *   'a' = 0110 0001 (97)
 *              ^
 *   Only the 5th bit (bit index 5, value 32) differs!
 *   - SET bit 5 → lowercase
 *   - CLEAR bit 5 → uppercase
 *   - TOGGLE bit 5 → swap case
 *
 * ──────────────────────── USEFUL CHECKS ─────────────────────────────────────
 *
 *   isalpha(c)  → true if c is a letter (a-z or A-Z)
 *   isdigit(c)  → true if c is a digit (0-9)
 *   isalnum(c)  → true if c is alphanumeric (letter or digit)
 *   isspace(c)  → true if c is whitespace (space, tab, newline, etc.)
 *   islower(c)  → true if c is lowercase
 *   isupper(c)  → true if c is uppercase
 *   tolower(c)  → returns lowercase version of c
 *   toupper(c)  → returns uppercase version of c
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

using namespace std;
#define nl '\n'
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

/*
 * ============================================================================
 *  SECTION 1: LOWERCASE → UPPERCASE CONVERSION
 * ============================================================================
 */

// ─────────── Approach 1: Brute Force (Beginner) ───────────
// Manually check each character and subtract 32
// Time: O(n), Space: O(n)
string toUpperBrute(string s) {
    string result = "";
    for (int i = 0; i < sz(s); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            result += (char)(s[i] - 32);  // 'a'-32 = 'A'
        } else {
            result += s[i];
        }
    }
    return result;
}

// ─────────── Approach 2: Using 'a' - 'A' difference (Intermediate) ───────────
// More readable: use character arithmetic instead of magic number 32
// Time: O(n), Space: O(1) in-place
string toUpperCharMath(string s) {
    for (char &c : s) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';  // Map: a→A, b→B, ..., z→Z
        }
    }
    return s;
}

// ─────────── Approach 3: Using toupper() STL (Intermediate+) ───────────
// Time: O(n), Space: O(1) in-place
string toUpperSTL(string s) {
    for (char &c : s) {
        c = toupper(static_cast<unsigned char>(c));
    }
    return s;
}

// ─────────── Approach 4: Using transform() (Expert) ───────────
// One-liner using STL algorithm
// Time: O(n), Space: O(1) in-place
string toUpperTransform(string s) {
    transform(all(s), s.begin(), ::toupper);
    return s;
}

// ─────────── Approach 5: Bitwise AND — GM Level ───────────
// Clear the 5th bit (bit index 5) using AND with ~32 (i.e., 0xDF = 1101 1111)
// 'a' & 0xDF = 'A', 'b' & 0xDF = 'B', etc.
// Time: O(n), Space: O(1) in-place
// ⚡ FASTEST — no branch, no comparison
string toUpperBitwise(string s) {
    for (char &c : s) {
        if (c >= 'a' && c <= 'z') {
            c &= ~32;  // Clear bit 5 → uppercase
            // Equivalent: c &= 0xDF;
            // Equivalent: c &= '_';  (since '_' = 95 = 0101 1111)
        }
    }
    return s;
}

/*
 * ============================================================================
 *  SECTION 2: UPPERCASE → LOWERCASE CONVERSION
 * ============================================================================
 */

// ─────────── Approach 1: Brute Force (Beginner) ───────────
string toLowerBrute(string s) {
    string result = "";
    for (int i = 0; i < sz(s); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            result += (char)(s[i] + 32);  // 'A'+32 = 'a'
        } else {
            result += s[i];
        }
    }
    return result;
}

// ─────────── Approach 2: Character Math (Intermediate) ───────────
string toLowerCharMath(string s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';  // Map: A→a, B→b, ..., Z→z
        }
    }
    return s;
}

// ─────────── Approach 3: Using tolower() STL (Intermediate+) ───────────
string toLowerSTL(string s) {
    for (char &c : s) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return s;
}

// ─────────── Approach 4: Using transform() (Expert) ───────────
string toLowerTransform(string s) {
    transform(all(s), s.begin(), ::tolower);
    return s;
}

// ─────────── Approach 5: Bitwise OR — GM Level ───────────
// Set the 5th bit (bit index 5) using OR with 32 (i.e., 0x20)
// 'A' | 32 = 'a', 'B' | 32 = 'b', etc.
// ⚡ FASTEST — no branch, no comparison
string toLowerBitwise(string s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
            c |= 32;  // Set bit 5 → lowercase
            // Equivalent: c |= ' ';  (since ' ' = 32 = 0010 0000)
        }
    }
    return s;
}

/*
 * ============================================================================
 *  SECTION 3: TOGGLE CASE (swap upper ↔ lower)
 * ============================================================================
 */

// ─────────── Approach 1: Brute Force (Beginner) ───────────
string toggleCaseBrute(string s) {
    for (int i = 0; i < sz(s); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)(s[i] - 32);
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (char)(s[i] + 32);
        }
    }
    return s;
}

// ─────────── Approach 2: Using islower/isupper (Intermediate) ───────────
string toggleCaseSTL(string s) {
    for (char &c : s) {
        if (islower(static_cast<unsigned char>(c))) {
            c = toupper(static_cast<unsigned char>(c));
        } else if (isupper(static_cast<unsigned char>(c))) {
            c = tolower(static_cast<unsigned char>(c));
        }
    }
    return s;
}

// ─────────── Approach 3: XOR with 32 — GM Level ───────────
// XOR the 5th bit: if it's 0 (upper) → becomes 1 (lower), and vice versa
// 'A' ^ 32 = 'a', 'a' ^ 32 = 'A'
// ⚡ FASTEST — single operation, no branch
string toggleCaseBitwise(string s) {
    for (char &c : s) {
        if (isalpha(static_cast<unsigned char>(c))) {
            c ^= 32;  // Toggle bit 5 → swap case
            // Equivalent: c ^= ' ';
        }
    }
    return s;
}

/*
 * ============================================================================
 *  SECTION 4: CASE-INSENSITIVE COMPARISON
 * ============================================================================
 *  Very common in CP! Compare two strings ignoring case.
 */

// ─────────── Approach 1: Convert both to lower and compare ───────────
bool equalIgnoreCaseNaive(string a, string b) {
    if (sz(a) != sz(b)) return false;
    for (int i = 0; i < sz(a); i++) {
        char ca = (a[i] >= 'A' && a[i] <= 'Z') ? a[i] + 32 : a[i];
        char cb = (b[i] >= 'A' && b[i] <= 'Z') ? b[i] + 32 : b[i];
        if (ca != cb) return false;
    }
    return true;
}

// ─────────── Approach 2: Bitwise OR for case-insensitive compare — GM Level ───────────
// OR with 32 forces both to lowercase without creating new strings
bool equalIgnoreCaseBitwise(const string &a, const string &b) {
    if (sz(a) != sz(b)) return false;
    for (int i = 0; i < sz(a); i++) {
        if ((a[i] | 32) != (b[i] | 32)) return false;
    }
    return true;
}

/*
 * ============================================================================
 *  SECTION 5: CAPITALIZE FIRST LETTER OF EACH WORD
 * ============================================================================
 *  "hello world" → "Hello World"
 */

// ─────────── Approach 1: Track previous character (Intermediate) ───────────
string capitalizeWords(string s) {
    bool newWord = true;
    for (char &c : s) {
        if (c == ' ') {
            newWord = true;
        } else {
            if (newWord && c >= 'a' && c <= 'z') {
                c -= 32;  // or c = toupper(c);
            }
            newWord = false;
        }
    }
    return s;
}

// ─────────── Approach 2: Bitwise Version — GM Level ───────────
string capitalizeWordsBitwise(string s) {
    bool newWord = true;
    for (char &c : s) {
        if (c == ' ') {
            newWord = true;
        } else {
            if (newWord && (c >= 'a' && c <= 'z')) {
                c &= ~32;  // Clear bit 5 → uppercase
            }
            newWord = false;
        }
    }
    return s;
}

/*
 * ============================================================================
 *  SECTION 6: COUNT UPPERCASE, LOWERCASE, DIGITS, SPACES
 * ============================================================================
 */

void countCharTypes(const string &s) {
    int upper = 0, lower = 0, digits = 0, spaces = 0, special = 0;
    for (char c : s) {
        if (c >= 'A' && c <= 'Z') upper++;
        else if (c >= 'a' && c <= 'z') lower++;
        else if (c >= '0' && c <= '9') digits++;
        else if (c == ' ') spaces++;
        else special++;
    }
    cout << "Uppercase: " << upper << nl;
    cout << "Lowercase: " << lower << nl;
    cout << "Digits:    " << digits << nl;
    cout << "Spaces:    " << spaces << nl;
    cout << "Special:   " << special << nl;
}

/*
 * ============================================================================
 *  SECTION 7: GM-LEVEL BITWISE TRICKS SUMMARY TABLE
 * ============================================================================
 *
 *  ┌──────────────────────────┬───────────────────────┬────────────────────┐
 *  │ Operation                │ Code                  │ How it Works       │
 *  ├──────────────────────────┼───────────────────────┼────────────────────┤
 *  │ To Uppercase             │ c & ~32  or  c & 0xDF │ Clear bit 5       │
 *  │ To Lowercase             │ c | 32   or  c | 0x20 │ Set bit 5         │
 *  │ Toggle Case              │ c ^ 32   or  c ^ 0x20 │ Flip bit 5        │
 *  │ Check if Lowercase       │ (c & 32) != 0         │ Bit 5 is set?     │
 *  │ Check if Uppercase       │ (c & 32) == 0         │ Bit 5 is clear?   │
 *  │ Case-insensitive compare │ (a|32) == (b|32)      │ Force both lower  │
 *  │ Get letter index (0-25)  │ (c | 32) - 'a'        │ Force lower, sub  │
 *  └──────────────────────────┴───────────────────────┴────────────────────┘
 *
 *  ⚠️ IMPORTANT: These bitwise tricks ONLY work on ASCII letters (a-z, A-Z).
 *     Always check isalpha(c) first if input may contain non-letters!
 *
 * ============================================================================
 *  SECTION 8: COMMON CP PATTERNS USING CASE CONVERSION
 * ============================================================================
 *
 *  Pattern 1: Normalize string for comparison
 *    → Convert everything to lowercase, remove non-alphanumeric
 *    → Used in: Palindrome checks, anagram checks
 *
 *  Pattern 2: Character frequency with case-insensitive counting
 *    → freq[(c | 32) - 'a']++ treats 'A' and 'a' as same
 *
 *  Pattern 3: Caesar Cipher / Rotation
 *    → newChar = (c - 'a' + shift) % 26 + 'a'
 *
 *  Pattern 4: Check if string has mixed case
 *    → hasUpper && hasLower
 *
 * ============================================================================
 */

void solve() {
    string test = "Hello World 123!";

    cout << "═══════ ORIGINAL ═══════" << nl;
    cout << "String: \"" << test << "\"" << nl << nl;

    cout << "═══════ TO UPPERCASE ═══════" << nl;
    cout << "Brute:     \"" << toUpperBrute(test) << "\"" << nl;
    cout << "CharMath:  \"" << toUpperCharMath(test) << "\"" << nl;
    cout << "STL:       \"" << toUpperSTL(test) << "\"" << nl;
    cout << "Transform: \"" << toUpperTransform(test) << "\"" << nl;
    cout << "Bitwise:   \"" << toUpperBitwise(test) << "\"" << nl << nl;

    cout << "═══════ TO LOWERCASE ═══════" << nl;
    cout << "Brute:     \"" << toLowerBrute(test) << "\"" << nl;
    cout << "CharMath:  \"" << toLowerCharMath(test) << "\"" << nl;
    cout << "STL:       \"" << toLowerSTL(test) << "\"" << nl;
    cout << "Transform: \"" << toLowerTransform(test) << "\"" << nl;
    cout << "Bitwise:   \"" << toLowerBitwise(test) << "\"" << nl << nl;

    cout << "═══════ TOGGLE CASE ═══════" << nl;
    cout << "Brute:     \"" << toggleCaseBrute(test) << "\"" << nl;
    cout << "STL:       \"" << toggleCaseSTL(test) << "\"" << nl;
    cout << "Bitwise:   \"" << toggleCaseBitwise(test) << "\"" << nl << nl;

    cout << "═══════ CASE-INSENSITIVE COMPARE ═══════" << nl;
    cout << "\"Hello\" vs \"hELLO\" (Naive):   " << equalIgnoreCaseNaive("Hello", "hELLO") << nl;
    cout << "\"Hello\" vs \"hELLO\" (Bitwise): " << equalIgnoreCaseBitwise("Hello", "hELLO") << nl;
    cout << "\"Hello\" vs \"World\" (Bitwise): " << equalIgnoreCaseBitwise("Hello", "World") << nl << nl;

    cout << "═══════ CAPITALIZE WORDS ═══════" << nl;
    string sentence = "the quick brown fox jumps over the lazy dog";
    cout << "Original:  \"" << sentence << "\"" << nl;
    cout << "Capitalized: \"" << capitalizeWords(sentence) << "\"" << nl;
    sentence = "the quick brown fox jumps over the lazy dog"; // reset
    cout << "Bitwise:     \"" << capitalizeWordsBitwise(sentence) << "\"" << nl << nl;

    cout << "═══════ CHARACTER COUNT ═══════" << nl;
    countCharTypes(test);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

