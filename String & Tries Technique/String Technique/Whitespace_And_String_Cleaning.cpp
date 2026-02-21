/*
Author: Sarvan.DP.GrandMaster
Created : 2026-02-21 22:55:00
*/

/*
 * ============================================================================
 *   STRING WHITESPACE & CLEANING — ZERO TO GRAND MASTER (GM) LEVEL
 * ============================================================================
 *
 *  This file covers ALL whitespace/cleaning operations you'll ever need in CP:
 *
 *  1. Remove ALL spaces
 *  2. Remove ALL whitespace (space, tab, newline, etc.)
 *  3. Remove leading spaces (left trim)
 *  4. Remove trailing spaces (right trim)
 *  5. Remove leading + trailing (trim)
 *  6. Collapse multiple spaces into one
 *  7. Remove non-alphanumeric characters
 *  8. Remove specific characters
 *
 *  ──────────── WHITESPACE CHARACTERS (ASCII) ────────────
 *   Character      ASCII   Name
 *   ──────────     ─────   ────
 *   ' '            32      Space
 *   '\t'           9       Horizontal Tab
 *   '\n'           10      Newline (Line Feed)
 *   '\r'           13      Carriage Return
 *   '\v'           11      Vertical Tab
 *   '\f'           12      Form Feed
 *
 *   isspace(c) returns true for ALL of the above.
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
 *  SECTION 1: REMOVE ALL SPACES — 4 Approaches
 * ============================================================================
 */

// ─────────── 1A: New String (Beginner) ───────────
// Build a new string without spaces
// Time: O(n), Space: O(n)
string removeSpaces_V1(const string &s) {
    string result = "";
    for (char c : s) {
        if (c != ' ') result += c;
    }
    return result;
}

// ─────────── 1B: Two-Pointer In-Place (Intermediate) ───────────
// Overwrite characters in place using a write pointer
// Time: O(n), Space: O(1) [in-place]
string removeSpaces_V2(string s) {
    int j = 0;  // write pointer
    for (int i = 0; i < sz(s); i++) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
    }
    s.resize(j);
    return s;
}

// ─────────── 1C: Erase-Remove Idiom (Expert) ───────────
// Classic C++ idiom: remove() + erase()
// remove() shifts non-matching elements forward, returns new end
// erase() removes the garbage at the end
// Time: O(n), Space: O(1) [in-place]
string removeSpaces_V3(string s) {
    s.erase(remove(all(s), ' '), s.end());
    return s;
}

// ─────────── 1D: C++20 erase_if (GM Level) ───────────
// Cleanest and most modern approach
// Time: O(n), Space: O(1) [in-place]
string removeSpaces_V4(string s) {
    erase_if(s, [](char c) { return c == ' '; });
    return s;
}

/*
 * ============================================================================
 *  SECTION 2: REMOVE ALL WHITESPACE (space, tab, newline, etc.)
 * ============================================================================
 */

// ─────────── 2A: Using isspace() check (Intermediate) ───────────
string removeAllWhitespace_V1(string s) {
    int j = 0;
    for (int i = 0; i < sz(s); i++) {
        if (!isspace(static_cast<unsigned char>(s[i]))) {
            s[j++] = s[i];
        }
    }
    s.resize(j);
    return s;
}

// ─────────── 2B: Erase-Remove with lambda (Expert) ───────────
string removeAllWhitespace_V2(string s) {
    s.erase(
        remove_if(all(s), [](unsigned char c) { return isspace(c); }),
        s.end()
    );
    return s;
}

// ─────────── 2C: C++20 erase_if (GM Level) ───────────
string removeAllWhitespace_V3(string s) {
    erase_if(s, [](unsigned char c) { return isspace(c); });
    return s;
}

/*
 * ============================================================================
 *  SECTION 3: TRIM — Remove Leading and/or Trailing Whitespace
 * ============================================================================
 *
 *  "   Hello World   " → "Hello World"     (trim both)
 *  "   Hello World   " → "Hello World   "  (ltrim only)
 *  "   Hello World   " → "   Hello World"  (rtrim only)
 */

// ─────────── Left Trim (remove leading whitespace) ───────────
string ltrim(string s) {
    int i = 0;
    while (i < sz(s) && isspace(static_cast<unsigned char>(s[i]))) i++;
    return s.substr(i);
}

// ─────────── Right Trim (remove trailing whitespace) ───────────
string rtrim(string s) {
    int i = sz(s) - 1;
    while (i >= 0 && isspace(static_cast<unsigned char>(s[i]))) i--;
    return s.substr(0, i + 1);
}

// ─────────── Full Trim (both sides) ───────────
string trim(const string &s) {
    return ltrim(rtrim(s));
}

// ─────────── GM Level: Using find_first/last_not_of ───────────
string trimGM(const string &s) {
    const string WHITESPACE = " \t\n\r\v\f";
    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == string::npos) return "";  // all whitespace
    size_t end = s.find_last_not_of(WHITESPACE);
    return s.substr(start, end - start + 1);
}

/*
 * ============================================================================
 *  SECTION 4: COLLAPSE MULTIPLE SPACES INTO ONE
 * ============================================================================
 *  "Hello    World   !" → "Hello World !"
 */

// ─────────── 4A: Track Previous Character (Intermediate) ───────────
string collapseSpaces_V1(const string &s) {
    string result;
    bool prevSpace = false;
    for (char c : s) {
        if (c == ' ') {
            if (!prevSpace) result += c;
            prevSpace = true;
        } else {
            result += c;
            prevSpace = false;
        }
    }
    return result;
}

// ─────────── 4B: unique + erase (Expert) ───────────
// std::unique removes consecutive duplicates (when predicate matches)
string collapseSpaces_V2(string s) {
    auto newEnd = unique(all(s), [](char a, char b) {
        return a == ' ' && b == ' ';
    });
    s.erase(newEnd, s.end());
    return s;
}

/*
 * ============================================================================
 *  SECTION 5: REMOVE NON-ALPHANUMERIC CHARACTERS
 * ============================================================================
 *  "A man, a plan, a canal: Panama!" → "AmsnaplanacanalPanama"
 *  VERY common in palindrome problems!
 */

// ─────────── 5A: New String (Beginner) ───────────
string keepAlphanumeric_V1(const string &s) {
    string result;
    for (char c : s) {
        if (isalnum(static_cast<unsigned char>(c))) {
            result += c;
        }
    }
    return result;
}

// ─────────── 5B: Two-Pointer (Intermediate) ───────────
string keepAlphanumeric_V2(string s) {
    int j = 0;
    for (int i = 0; i < sz(s); i++) {
        if (isalnum(static_cast<unsigned char>(s[i]))) {
            s[j++] = s[i];
        }
    }
    s.resize(j);
    return s;
}

// ─────────── 5C: Erase-Remove (Expert) ───────────
string keepAlphanumeric_V3(string s) {
    s.erase(
        remove_if(all(s), [](unsigned char c) { return !isalnum(c); }),
        s.end()
    );
    return s;
}

// ─────────── 5D: Keep alphanumeric + convert to lowercase (GM Palindrome Prep) ───────────
// This is the EXACT preprocessing needed for LC 125: Valid Palindrome
string cleanForPalindrome(const string &s) {
    string result;
    for (char c : s) {
        if (isalnum(static_cast<unsigned char>(c))) {
            result += (char)(c | 32);  // force lowercase using bitwise OR
            // NOTE: This works for letters. For digits, OR with 32
            // doesn't change them (digits are 48-57, bit 5 is already 1 for some).
            // So use tolower() for safety:
        }
    }
    return result;
}

// ─────────── 5E: SAFE version for palindrome (handles digits correctly) ───────────
string cleanForPalindromeSafe(const string &s) {
    string result;
    for (char c : s) {
        if (isalnum(static_cast<unsigned char>(c))) {
            result += tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

/*
 * ============================================================================
 *  SECTION 6: REMOVE SPECIFIC CHARACTERS
 * ============================================================================
 *  Remove all occurrences of characters in a given set
 */

// ─────────── Using a set of characters to remove ───────────
string removeChars(string s, const string &chars) {
    // Build a lookup (for O(1) check)
    bool toRemove[256] = {};
    for (unsigned char c : chars) toRemove[c] = true;

    int j = 0;
    for (int i = 0; i < sz(s); i++) {
        if (!toRemove[(unsigned char)s[i]]) {
            s[j++] = s[i];
        }
    }
    s.resize(j);
    return s;
}

/*
 * ============================================================================
 *  SECTION 7: SPLIT STRING BY WHITESPACE
 * ============================================================================
 *  "Hello   World  Foo" → {"Hello", "World", "Foo"}
 *  Very useful for parsing input in CP.
 */

// ─────────── Using stringstream (Intermediate) ───────────
#include <sstream>
vector<string> splitByWhitespace(const string &s) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// ─────────── Manual split (Expert — more control) ───────────
vector<string> splitManual(const string &s) {
    vector<string> tokens;
    int i = 0, n = sz(s);
    while (i < n) {
        // Skip whitespace
        while (i < n && isspace(static_cast<unsigned char>(s[i]))) i++;
        if (i >= n) break;
        // Find end of word
        int j = i;
        while (j < n && !isspace(static_cast<unsigned char>(s[j]))) j++;
        tokens.push_back(s.substr(i, j - i));
        i = j;
    }
    return tokens;
}

/*
 * ============================================================================
 *  SECTION 8: REVERSE WORDS IN A STRING
 * ============================================================================
 *  "Hello World" → "World Hello"
 *  LC 151: Reverse Words in a String
 */

string reverseWords(string s) {
    // Step 1: Trim and collapse spaces
    vector<string> words = splitByWhitespace(s);
    // Step 2: Reverse the words
    reverse(all(words));
    // Step 3: Join with single space
    string result;
    for (int i = 0; i < sz(words); i++) {
        if (i > 0) result += ' ';
        result += words[i];
    }
    return result;
}

// ─────────── GM Level: In-place O(1) extra space ───────────
// Step 1: Reverse entire string
// Step 2: Reverse each word
// Step 3: Clean up extra spaces
string reverseWordsInPlace(string s) {
    // Trim and collapse
    int n = sz(s);

    // Step 1: Reverse entire string
    reverse(all(s));

    // Step 2: Reverse each word and compact
    int i = 0, j = 0;
    while (i < n) {
        if (s[i] == ' ') { i++; continue; }
        if (j != 0) s[j++] = ' ';  // add single space between words
        int start = j;
        while (i < n && s[i] != ' ') s[j++] = s[i++];
        reverse(s.begin() + start, s.begin() + j);
    }
    s.resize(j);
    return s;
}


void solve() {
    cout << "═══════ REMOVE SPACES ═══════" << nl;
    string s1 = "Hello World Program";
    cout << "Original: \"" << s1 << "\"" << nl;
    cout << "V1 (New String):     \"" << removeSpaces_V1(s1) << "\"" << nl;
    cout << "V2 (Two-Pointer):    \"" << removeSpaces_V2(s1) << "\"" << nl;
    cout << "V3 (Erase-Remove):   \"" << removeSpaces_V3(s1) << "\"" << nl;
    cout << "V4 (C++20 erase_if): \"" << removeSpaces_V4(s1) << "\"" << nl << nl;

    cout << "═══════ REMOVE ALL WHITESPACE ═══════" << nl;
    string s2 = "Hello\tWorld\nFoo";
    cout << "Original (with tab+newline): \"Hello\\tWorld\\nFoo\"" << nl;
    cout << "V1: \"" << removeAllWhitespace_V1(s2) << "\"" << nl;
    s2 = "Hello\tWorld\nFoo";
    cout << "V2: \"" << removeAllWhitespace_V2(s2) << "\"" << nl;
    s2 = "Hello\tWorld\nFoo";
    cout << "V3: \"" << removeAllWhitespace_V3(s2) << "\"" << nl << nl;

    cout << "═══════ TRIM ═══════" << nl;
    string s3 = "   Hello World   ";
    cout << "Original: \"" << s3 << "\"" << nl;
    cout << "LTrim:    \"" << ltrim(s3) << "\"" << nl;
    cout << "RTrim:    \"" << rtrim(s3) << "\"" << nl;
    cout << "Trim:     \"" << trim(s3) << "\"" << nl;
    cout << "TrimGM:   \"" << trimGM(s3) << "\"" << nl << nl;

    cout << "═══════ COLLAPSE SPACES ═══════" << nl;
    string s4 = "Hello    World   !";
    cout << "Original:  \"" << s4 << "\"" << nl;
    cout << "V1:        \"" << collapseSpaces_V1(s4) << "\"" << nl;
    cout << "V2:        \"" << collapseSpaces_V2(s4) << "\"" << nl << nl;

    cout << "═══════ KEEP ALPHANUMERIC ═══════" << nl;
    string s5 = "A man, a plan, a canal: Panama!";
    cout << "Original: \"" << s5 << "\"" << nl;
    cout << "V1:       \"" << keepAlphanumeric_V1(s5) << "\"" << nl;
    cout << "V2:       \"" << keepAlphanumeric_V2(s5) << "\"" << nl;
    s5 = "A man, a plan, a canal: Panama!";
    cout << "V3:       \"" << keepAlphanumeric_V3(s5) << "\"" << nl;
    cout << "Clean+Lower: \"" << cleanForPalindromeSafe("A man, a plan, a canal: Panama!") << "\"" << nl << nl;

    cout << "═══════ REMOVE SPECIFIC CHARS ═══════" << nl;
    cout << "Remove vowels from \"Hello World\": \""
         << removeChars("Hello World", "aeiouAEIOU") << "\"" << nl << nl;

    cout << "═══════ SPLIT BY WHITESPACE ═══════" << nl;
    string s6 = "  Hello   World   Foo  ";
    auto tokens = splitByWhitespace(s6);
    cout << "Original: \"" << s6 << "\"" << nl;
    cout << "Tokens: ";
    for (auto &t : tokens) cout << "[" << t << "] ";
    cout << nl << nl;

    cout << "═══════ REVERSE WORDS ═══════" << nl;
    string s7 = "  the sky  is  blue  ";
    cout << "Original: \"" << s7 << "\"" << nl;
    cout << "Reversed: \"" << reverseWords(s7) << "\"" << nl;
    cout << "In-Place: \"" << reverseWordsInPlace(s7) << "\"" << nl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

