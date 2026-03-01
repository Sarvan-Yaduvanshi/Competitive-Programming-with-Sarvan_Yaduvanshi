/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 01 — STRING BASICS & OPERATIONS                            ║
║           From Zero to Grandmaster — Complete Foundation                     ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1.  Input / Output (cin, getline, stringstream)
 2.  Length of String
 3.  Traversal Techniques (index, iterator, range-for, reverse)
 4.  Reverse a String (multiple methods)
 5.  Case Conversion Technique (toupper, tolower, bit tricks)
 6.  Remove Spaces, Whitespace & String Cleaning
 7.  String Manipulation (insert, erase, replace, swap)
 8.  Palindrome Check (multiple methods)
 9.  Frequency Count (array, map, bitset)
10.  Character Array vs std::string (definitions & differences)
11.  ASCII Tricks (digit check, letter check, toggling case)
12.  Basic Substring (substr, find, rfind, find_first_of)
13.  Concatenation (+ operator, append, push_back, stringstream)

WHAT IS A STRING?
─────────────────
A string is a sequence of characters. In C++:
  • char array:   char s[] = "hello";     // C-style, null-terminated '\0'
  • std::string:  string s = "hello";     // C++ STL, dynamic, safe

KEY PROPERTIES:
  • Strings are 0-indexed: s[0] is the first character
  • std::string is mutable — you can change individual characters
  • Time: s[i] is O(1), s.size() is O(1), s.substr() is O(k)
  • std::string internally uses a dynamic array (like vector<char>)

ASCII TABLE (MUST MEMORIZE):
  'A' = 65,  'Z' = 90
  'a' = 97,  'z' = 122
  '0' = 48,  '9' = 57
  ' ' = 32,  '\n' = 10, '\t' = 9
  Difference: 'a' - 'A' = 32

COMPETITIVE PROGRAMMING TIPS:
  • Always use std::string (safer, faster to code)
  • Use getline() when input has spaces
  • Use s.reserve(n) when you know the size in advance
  • Prefer s += c over s = s + c (avoids O(n) copy)
  • Use '\n' instead of endl (faster output)
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <cstring>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: INPUT / OUTPUT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 (a) cin >> s;       → Reads ONE word (stops at whitespace)
 (b) getline(cin,s); → Reads ENTIRE line (including spaces)
 (c) cin.ignore();   → Flush leftover newline before getline
 (d) stringstream    → Parse string into tokens

 COMMON PITFALL:
   cin >> n;           // reads number, leaves '\n' in buffer
   getline(cin, s);    // reads the leftover '\n' → empty string!
   FIX: cin.ignore() between cin and getline

 FAST I/O:
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
*/

void demo_input_output() {
    cout << "=== SECTION 1: INPUT / OUTPUT ===" << endl;

    // Method 1: Direct string creation
    string s1 = "Hello World";
    cout << "Direct: " << s1 << endl;

    // Method 2: From char array
    char arr[] = "Hello from char array";
    string s2(arr);
    cout << "From char[]: " << s2 << endl;

    // Method 3: Fill constructor — string(count, char)
    string s3(5, '*');
    cout << "Fill constructor: " << s3 << endl;  // *****

    // Method 4: Substring constructor
    string s4(s1, 6, 5);  // from index 6, length 5
    cout << "Substring constructor: " << s4 << endl;  // World

    // Method 5: stringstream for parsing
    string line = "10 20 30 hello";
    stringstream ss(line);
    int a, b, c;
    string word;
    ss >> a >> b >> c >> word;
    cout << "Parsed: " << a << " " << b << " " << c << " " << word << endl;

    // Method 6: Reading multiple tokens from stringstream
    string csv = "apple,banana,cherry";
    stringstream ss2(csv);
    string token;
    cout << "CSV tokens: ";
    while (getline(ss2, token, ',')) {
        cout << "[" << token << "] ";
    }
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: LENGTH OF STRING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 • s.size()   → returns size_t (unsigned), O(1)
 • s.length() → SAME as size(), just an alias
 • s.empty()  → true if size == 0
 • strlen(c)  → for C-style char arrays, O(n) — scans for '\0'

 ⚠️ PITFALL: s.size() returns unsigned. If s.size() - 1 when empty → underflow!
    FIX: Cast to int: (int)s.size() - 1  OR  use sz(s) macro
*/

void demo_length() {
    cout << "\n=== SECTION 2: LENGTH ===" << endl;

    string s = "Hello";
    cout << "size(): " << s.size() << endl;      // 5
    cout << "length(): " << s.length() << endl;  // 5
    cout << "empty(): " << s.empty() << endl;     // 0 (false)

    string empty_str = "";
    cout << "empty string empty(): " << empty_str.empty() << endl;  // 1 (true)

    // C-style length
    char c[] = "Hello";
    cout << "strlen: " << strlen(c) << endl;  // 5 (does NOT count '\0')

    // Safe subtraction
    string t = "";
    int n = (int)t.size();  // 0, safe to do n-1 = -1
    cout << "Safe size: " << n << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: TRAVERSAL TECHNIQUES
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 4 ways to traverse a string:
   (a) Index-based:     for(int i = 0; i < s.size(); i++)
   (b) Range-based:     for(char c : s)
   (c) Iterator-based:  for(auto it = s.begin(); it != s.end(); it++)
   (d) Reverse:         for(int i = s.size()-1; i >= 0; i--)
                         for(auto it = s.rbegin(); it != s.rend(); it++)

 All are O(n). Use index-based when you need position, range-based for simplicity.
*/

void demo_traversal() {
    cout << "\n=== SECTION 3: TRAVERSAL ===" << endl;
    string s = "Hello";

    // Method 1: Index-based
    cout << "Index: ";
    for (int i = 0; i < (int)s.size(); i++) {
        cout << s[i] << " ";
    }
    cout << endl;

    // Method 2: Range-based (C++11)
    cout << "Range: ";
    for (char c : s) {
        cout << c << " ";
    }
    cout << endl;

    // Method 3: Iterator
    cout << "Iterator: ";
    for (auto it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // Method 4: Reverse traversal
    cout << "Reverse: ";
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        cout << s[i] << " ";
    }
    cout << endl;

    // Method 5: Reverse iterator
    cout << "Rev Iterator: ";
    for (auto it = s.rbegin(); it != s.rend(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // Method 6: Traverse with modification (reference)
    string t = "hello";
    for (char& c : t) {
        c = toupper(c);  // modifies in-place
    }
    cout << "Modified: " << t << endl;  // HELLO
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: REVERSE A STRING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Methods to reverse:
   (a) std::reverse(s.begin(), s.end()) — in-place, O(n)
   (b) Two-pointer swap — manual, O(n)
   (c) string(s.rbegin(), s.rend()) — creates new reversed string, O(n)
   (d) Recursion — O(n) time, O(n) stack space
   (e) Stack-based — push all chars, pop to build reversed

 IN COMPETITIVE PROGRAMMING: Always use std::reverse — fastest to type.
*/

// Method 1: STL reverse
string reverseSTL(string s) {
    reverse(s.begin(), s.end());
    return s;
}

// Method 2: Two-pointer
string reverseTwoPointer(string s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
    return s;
}

// Method 3: New reversed string
string reverseNew(const string& s) {
    return string(s.rbegin(), s.rend());
}

// Method 4: Recursive reverse
string reverseRecursive(const string& s) {
    if (s.size() <= 1) return s;
    return reverseRecursive(s.substr(1)) + s[0];
}

void demo_reverse() {
    cout << "\n=== SECTION 4: REVERSE ===" << endl;
    string s = "abcdef";
    cout << "Original: " << s << endl;
    cout << "STL reverse: " << reverseSTL(s) << endl;
    cout << "Two-pointer: " << reverseTwoPointer(s) << endl;
    cout << "New string: " << reverseNew(s) << endl;
    cout << "Recursive: " << reverseRecursive(s) << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: CASE CONVERSION TECHNIQUE
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 • toupper(c) → converts char to uppercase
 • tolower(c) → converts char to lowercase

 ASCII BIT TRICK (VERY POWERFUL):
   • 'A' = 01000001  (65)
   • 'a' = 01100001  (97)
   • Difference is bit 5 (value 32)!

   • TO LOWERCASE:   c |= 32    OR  c |= (1 << 5)    OR  c | ' '
   • TO UPPERCASE:   c &= ~32   OR  c &= ~(1 << 5)   OR  c & '_'
   • TOGGLE CASE:    c ^= 32    OR  c ^= (1 << 5)     OR  c ^ ' '

 These bit tricks work ONLY for ASCII letters. Always check isalpha() first!
*/

string toUpperCase(string s) {
    for (char& c : s) {
        if (c >= 'a' && c <= 'z') {
            c = c - 32;  // OR c = toupper(c); OR c &= ~32;
        }
    }
    return s;
}

string toLowerCase(string s) {
    for (char& c : s) {
        if (c >= 'A' && c <= 'Z') {
            c = c + 32;  // OR c = tolower(c); OR c |= 32;
        }
    }
    return s;
}

string toggleCase(string s) {
    for (char& c : s) {
        if (isalpha(c)) {
            c ^= 32;  // toggle bit 5
        }
    }
    return s;
}

// Convert first letter of each word to uppercase (Title Case)
string titleCase(string s) {
    bool newWord = true;
    for (char& c : s) {
        if (c == ' ') {
            newWord = true;
        } else if (newWord) {
            c = toupper(c);
            newWord = false;
        } else {
            c = tolower(c);
        }
    }
    return s;
}

void demo_case_conversion() {
    cout << "\n=== SECTION 5: CASE CONVERSION ===" << endl;
    string s = "Hello World 123";
    cout << "Upper: " << toUpperCase(s) << endl;
    cout << "Lower: " << toLowerCase(s) << endl;
    cout << "Toggle: " << toggleCase(s) << endl;
    cout << "Title: " << titleCase("hELLO wORLD") << endl;

    // Bit trick demo
    char ch = 'A';
    cout << "A to lower (bit): " << (char)(ch | 32) << endl;   // a
    cout << "a to upper (bit): " << (char)('a' & ~32) << endl;  // A
    cout << "Toggle A: " << (char)(ch ^ 32) << endl;             // a
}

// ═══════════════════════════════════════════════════════════════
// SECTION 6: REMOVE SPACES, WHITESPACE & STRING CLEANING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 String cleaning = removing unwanted characters (spaces, tabs, newlines, etc.)

 METHODS:
   (a) Erase-remove idiom: s.erase(remove(s.begin(), s.end(), ' '), s.end());
   (b) Manual copy with filtering
   (c) Remove leading/trailing whitespace (trim)
   (d) Collapse multiple spaces into one
   (e) Remove all non-alphanumeric characters

 isspace(c)  → true for ' ', '\t', '\n', '\r', '\f', '\v'
 isalnum(c)  → true for letters and digits
 isalpha(c)  → true for letters only
 isdigit(c)  → true for '0'-'9'
*/

// Remove ALL spaces
string removeAllSpaces(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

// Remove ALL whitespace (spaces, tabs, newlines)
string removeAllWhitespace(string s) {
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    return s;
}

// Trim leading and trailing spaces
string trim(const string& s) {
    int start = 0, end = (int)s.size() - 1;
    while (start <= end && s[start] == ' ') start++;
    while (end >= start && s[end] == ' ') end--;
    return s.substr(start, end - start + 1);
}

// Collapse multiple spaces into single space
string collapseSpaces(const string& s) {
    string result;
    bool lastWasSpace = false;
    for (char c : s) {
        if (c == ' ') {
            if (!lastWasSpace) {
                result += c;
                lastWasSpace = true;
            }
        } else {
            result += c;
            lastWasSpace = false;
        }
    }
    return trim(result);
}

// Keep only alphanumeric + convert to lowercase (useful for palindrome checks)
string cleanForPalindrome(const string& s) {
    string result;
    for (char c : s) {
        if (isalnum(c)) {
            result += tolower(c);
        }
    }
    return result;
}

void demo_cleaning() {
    cout << "\n=== SECTION 6: STRING CLEANING ===" << endl;
    string s = "  Hello   World  \t\n ";
    cout << "Remove spaces: [" << removeAllSpaces(s) << "]" << endl;
    cout << "Remove whitespace: [" << removeAllWhitespace(s) << "]" << endl;
    cout << "Trim: [" << trim("   hello   ") << "]" << endl;
    cout << "Collapse: [" << collapseSpaces("  hello    world   ") << "]" << endl;
    cout << "Clean: [" << cleanForPalindrome("A man, a plan, a canal: Panama") << "]" << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: STRING MANIPULATION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 std::string provides these manipulation operations:

 INSERTION:
   s.insert(pos, str)        — insert str at position pos
   s.insert(pos, n, ch)      — insert n copies of ch at pos

 ERASURE:
   s.erase(pos, len)         — erase len characters starting at pos
   s.erase(it)               — erase char at iterator
   s.pop_back()              — remove last character

 REPLACEMENT:
   s.replace(pos, len, str)  — replace len chars at pos with str

 SWAP:
   s.swap(t) or swap(s, t)   — O(1) swap

 RESIZE:
   s.resize(n)               — resize to n (truncate or pad with '\0')
   s.resize(n, 'x')          — resize to n, pad with 'x'

 CLEAR:
   s.clear()                 — make empty

 All position-based operations are O(n) due to shifting!
*/

void demo_manipulation() {
    cout << "\n=== SECTION 7: STRING MANIPULATION ===" << endl;

    string s = "Hello World";

    // Insert
    string s1 = s;
    s1.insert(5, " Beautiful");
    cout << "Insert: " << s1 << endl;  // Hello Beautiful World

    // Erase
    string s2 = s;
    s2.erase(5, 6);  // erase " World"
    cout << "Erase: " << s2 << endl;   // Hello

    // Replace
    string s3 = s;
    s3.replace(6, 5, "C++");
    cout << "Replace: " << s3 << endl;  // Hello C++

    // Pop back
    string s4 = "Hello!";
    s4.pop_back();
    cout << "Pop back: " << s4 << endl;  // Hello

    // Swap
    string a = "first", b = "second";
    swap(a, b);
    cout << "After swap: a=" << a << " b=" << b << endl;

    // Resize
    string s5 = "Hello";
    s5.resize(10, '!');
    cout << "Resize: " << s5 << endl;   // Hello!!!!!

    // Assign
    string s6;
    s6.assign(3, 'x');
    cout << "Assign: " << s6 << endl;   // xxx
}

// ═══════════════════════════════════════════════════════════════
// SECTION 8: PALINDROME CHECK
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 A palindrome reads the same forwards and backwards.
 Examples: "madam", "racecar", "121", "abba"

 METHODS:
   (a) Compare s == reverse(s)               — O(n) time, O(n) space
   (b) Two-pointer from both ends             — O(n) time, O(1) space ✓ BEST
   (c) Recursive check                        — O(n) time, O(n) stack
   (d) Clean & check (ignore non-alnum)       — for real-world strings

 EDGE CASES:
   • Empty string → palindrome
   • Single character → palindrome
   • Even length: "abba" → center between b,b
   • Odd length: "aba" → center at 'b'
*/

// Method 1: Reverse comparison
bool isPalindromeReverse(const string& s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return s == rev;
}

// Method 2: Two-pointer (BEST for competitive programming)
bool isPalindromeTwoPointer(const string& s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// Method 3: Recursive
bool isPalindromeRecursive(const string& s, int left, int right) {
    if (left >= right) return true;
    if (s[left] != s[right]) return false;
    return isPalindromeRecursive(s, left + 1, right - 1);
}

// Method 4: Real-world palindrome (ignore case, non-alnum)
bool isPalindromeReal(const string& s) {
    string cleaned = cleanForPalindrome(s);
    return isPalindromeTwoPointer(cleaned);
}

// Check if a substring s[l..r] is palindrome
bool isSubstrPalindrome(const string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

void demo_palindrome() {
    cout << "\n=== SECTION 8: PALINDROME CHECK ===" << endl;
    cout << "madam (reverse): " << isPalindromeReverse("madam") << endl;
    cout << "madam (two-ptr): " << isPalindromeTwoPointer("madam") << endl;
    string t = "racecar";
    cout << "racecar (recursive): " << isPalindromeRecursive(t, 0, t.size()-1) << endl;
    cout << "A man, a plan... (real): " << isPalindromeReal("A man, a plan, a canal: Panama") << endl;
    cout << "hello (two-ptr): " << isPalindromeTwoPointer("hello") << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 9: FREQUENCY COUNT
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 Counting character frequencies is one of the MOST COMMON operations.

 METHODS:
   (a) int freq[26] = {0};           — for lowercase only, O(1) lookup
   (b) int freq[128] = {0};          — for all ASCII characters
   (c) unordered_map<char, int>      — for any character, hash-based
   (d) map<char, int>                — sorted by character, tree-based

 WHEN TO USE WHAT:
   • freq[26]:  Most competitive programming problems (lowercase only)
   • freq[128]: When mixed case/digits/symbols
   • map:       When you need sorted output
   • unordered_map: When charset is unknown/large

 TRICK: For lowercase, index = c - 'a'
        For uppercase, index = c - 'A'
        For digits, index = c - '0'
*/

// Method 1: Array-based frequency (FASTEST)
void frequencyArray(const string& s) {
    int freq[26] = {0};
    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
        }
    }
    cout << "Array freq: ";
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << (char)('a' + i) << ":" << freq[i] << " ";
        }
    }
    cout << endl;
}

// Method 2: Map-based frequency
void frequencyMap(const string& s) {
    map<char, int> freq;
    for (char c : s) freq[c]++;
    cout << "Map freq: ";
    for (auto& [ch, cnt] : freq) {
        cout << ch << ":" << cnt << " ";
    }
    cout << endl;
}

// Method 3: Find most frequent character
char mostFrequent(const string& s) {
    int freq[128] = {0};
    for (char c : s) freq[(int)c]++;
    int maxFreq = 0;
    char result = '\0';
    for (int i = 0; i < 128; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            result = (char)i;
        }
    }
    return result;
}

// Method 4: Check if two strings have same frequency (anagram check)
bool sameFrequency(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    int freq[26] = {0};
    for (char c : a) freq[c - 'a']++;
    for (char c : b) freq[c - 'a']--;
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) return false;
    }
    return true;
}

void demo_frequency() {
    cout << "\n=== SECTION 9: FREQUENCY COUNT ===" << endl;
    frequencyArray("programming");
    frequencyMap("hello world");
    cout << "Most frequent in 'banana': " << mostFrequent("banana") << endl;
    cout << "Anagram 'listen'/'silent': " << sameFrequency("listen", "silent") << endl;
}

// ═══════════════════════════════════════════════════════════════
// SECTION 10: CHARACTER ARRAY vs std::string
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 ┌──────────────────┬──────────────────────┬──────────────────────────┐
 │ Feature          │ char array (C-style) │ std::string (C++ STL)    │
 ├──────────────────┼──────────────────────┼──────────────────────────┤
 │ Declaration      │ char s[100];         │ string s;                │
 │ Size             │ Fixed at compile     │ Dynamic (auto-resize)    │
 │ Null terminated  │ Yes (must have '\0') │ Internally yes, but safe │
 │ Length           │ strlen(s) → O(n)     │ s.size() → O(1)          │
 │ Comparison       │ strcmp(a,b)          │ a == b, a < b            │
 │ Concatenation    │ strcat(a,b)          │ a + b, a += b            │
 │ Copy             │ strcpy(dst,src)      │ dst = src                │
 │ Safety           │ Buffer overflow risk │ Safe, bounds managed     │
 │ Passing          │ Decays to pointer    │ Pass by ref (const&)     │
 │ Memory           │ Stack allocated      │ Heap allocated (SSO*)    │
 └──────────────────┴──────────────────────┴──────────────────────────┘

 *SSO = Small String Optimization: strings < ~22 chars stored on stack

 CONVERSION:
   char[] → string:   string s(charArray);
   string → char[]:   s.c_str() returns const char*
                       strcpy(arr, s.c_str())

 IN CP: ALWAYS prefer std::string. Use char[] only for legacy C functions.
*/

void demo_char_vs_string() {
    cout << "\n=== SECTION 10: CHAR ARRAY vs STRING ===" << endl;

    // C-style char array
    char c1[20] = "Hello";
    char c2[20] = "World";
    cout << "C strlen: " << strlen(c1) << endl;
    cout << "C strcmp: " << strcmp(c1, c2) << endl;  // negative (H < W)
    strcat(c1, c2);
    cout << "C strcat: " << c1 << endl;  // HelloWorld

    // C++ string
    string s1 = "Hello";
    string s2 = "World";
    cout << "C++ size: " << s1.size() << endl;
    cout << "C++ compare: " << (s1 == s2) << endl;
    cout << "C++ concat: " << s1 + s2 << endl;

    // Conversions
    string fromC(c1);
    cout << "char[] to string: " << fromC << endl;

    const char* toC = s1.c_str();
    cout << "string to char*: " << toC << endl;

    // Important: string can contain '\0' in middle, char[] cannot!
    string withNull = "Hello";
    withNull += '\0';
    withNull += "World";
    cout << "String with null (size): " << withNull.size() << endl;  // 11
    cout << "String with null (c_str len): " << strlen(withNull.c_str()) << endl;  // 5
}

// ═══════════════════════════════════════════════════════════════
// SECTION 11: ASCII TRICKS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 ASCII is the backbone of string manipulation in competitive programming.

 KEY TRICKS:
   1. Check if digit:     c >= '0' && c <= '9'  OR  isdigit(c)
   2. Check if lowercase: c >= 'a' && c <= 'z'  OR  islower(c)
   3. Check if uppercase: c >= 'A' && c <= 'Z'  OR  isupper(c)
   4. Check if letter:    isalpha(c)
   5. Char to digit:      c - '0'  → gives int 0-9
   6. Digit to char:      d + '0'  → gives char '0'-'9'
   7. Lowercase index:    c - 'a'  → gives 0-25
   8. Uppercase index:    c - 'A'  → gives 0-25
   9. Toggle case:        c ^= 32
  10. Distance between:   abs(c1 - c2) → useful in Caesar cipher

 CAESAR CIPHER:
   encrypted = ((c - 'a' + shift) % 26) + 'a';
   decrypted = ((c - 'a' - shift + 26) % 26) + 'a';
*/

// Convert character to its alphabet position (a=1, b=2, ...)
int charPosition(char c) {
    if (isupper(c)) return c - 'A' + 1;
    if (islower(c)) return c - 'a' + 1;
    return -1;
}

// Caesar cipher encryption
string caesarCipher(const string& s, int shift) {
    string result;
    for (char c : s) {
        if (islower(c)) {
            result += (char)(((c - 'a' + shift) % 26) + 'a');
        } else if (isupper(c)) {
            result += (char)(((c - 'A' + shift) % 26) + 'A');
        } else {
            result += c;
        }
    }
    return result;
}

// Count digits, letters, spaces, special chars
void characterClassify(const string& s) {
    int digits = 0, letters = 0, spaces = 0, special = 0;
    for (char c : s) {
        if (isdigit(c)) digits++;
        else if (isalpha(c)) letters++;
        else if (isspace(c)) spaces++;
        else special++;
    }
    cout << "Digits:" << digits << " Letters:" << letters
         << " Spaces:" << spaces << " Special:" << special << endl;
}

void demo_ascii() {
    cout << "\n=== SECTION 11: ASCII TRICKS ===" << endl;

    // Character to int and vice versa
    cout << "'A' ASCII: " << (int)'A' << endl;   // 65
    cout << "'a' ASCII: " << (int)'a' << endl;   // 97
    cout << "'0' ASCII: " << (int)'0' << endl;   // 48
    cout << "Char '7' to int: " << ('7' - '0') << endl;  // 7
    cout << "Int 3 to char: " << (char)(3 + '0') << endl; // '3'

    // Position
    cout << "Position of 'c': " << charPosition('c') << endl;  // 3

    // Caesar cipher
    cout << "Caesar +3: " << caesarCipher("Hello World", 3) << endl;   // Khoor Zruog
    cout << "Caesar -3: " << caesarCipher("Khoor Zruog", 23) << endl;  // Hello World

    // Classify
    characterClassify("Hello World! 123");
}

// ═══════════════════════════════════════════════════════════════
// SECTION 12: BASIC SUBSTRING OPERATIONS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 SUBSTRING EXTRACTION:
   s.substr(pos)        — from pos to end
   s.substr(pos, len)   — from pos, length len
   Both return a NEW string, O(len)

 FINDING:
   s.find(str)          — first occurrence, returns index or string::npos
   s.rfind(str)         — last occurrence
   s.find(str, pos)     — first occurrence starting from pos
   s.find_first_of(chars) — first occurrence of ANY char in chars
   s.find_last_of(chars)
   s.find_first_not_of(chars)
   s.find_last_not_of(chars)

 string::npos = (size_t)(-1) = maximum value of size_t
 Always check: if (s.find(x) != string::npos)

 COMPARISON:
   s.compare(t)          — like strcmp: <0, 0, >0
   s == t, s < t, s > t  — lexicographic comparison

 COUNTING OCCURRENCES:
   No built-in! Use a loop with find.
*/

// Count occurrences of pattern in text
int countOccurrences(const string& text, const string& pattern) {
    int count = 0;
    size_t pos = 0;
    while ((pos = text.find(pattern, pos)) != string::npos) {
        count++;
        pos++;  // pos += pattern.size() for non-overlapping
    }
    return count;
}

// Extract all substrings of length k
vector<string> allSubstringsOfLengthK(const string& s, int k) {
    vector<string> result;
    for (int i = 0; i <= (int)s.size() - k; i++) {
        result.push_back(s.substr(i, k));
    }
    return result;
}

// Check if s1 is a rotation of s2
bool isRotation(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) return false;
    string doubled = s1 + s1;
    return doubled.find(s2) != string::npos;
}

void demo_substring() {
    cout << "\n=== SECTION 12: BASIC SUBSTRING ===" << endl;
    string s = "Hello World";

    // substr
    cout << "substr(6): " << s.substr(6) << endl;       // World
    cout << "substr(0,5): " << s.substr(0, 5) << endl;  // Hello

    // find
    cout << "find('World'): " << s.find("World") << endl;  // 6
    cout << "find('xyz'): " << (s.find("xyz") == string::npos ? "NOT FOUND" : "FOUND") << endl;
    cout << "rfind('l'): " << s.rfind('l') << endl;  // 9

    // find_first_of / find_last_of
    cout << "find_first_of('aeiou'): " << s.find_first_of("aeiou") << endl;  // 1 (e)
    cout << "find_last_of('aeiou'): " << s.find_last_of("aeiou") << endl;    // 7 (o)

    // Count occurrences
    cout << "Count 'l' in 'Hello World': " << countOccurrences("Hello World", "l") << endl;  // 3

    // Substrings of length k
    auto subs = allSubstringsOfLengthK("abcd", 2);
    cout << "Substrings of len 2: ";
    for (auto& sub : subs) cout << sub << " ";
    cout << endl;

    // Rotation check
    cout << "Is 'lloHe' rotation of 'Hello'? " << isRotation("Hello", "lloHe") << endl;  // 1
}

// ═══════════════════════════════════════════════════════════════
// SECTION 13: CONCATENATION
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ───────
 METHODS:
   (a) s + t           — creates new string, O(n+m) — SLOW in loop!
   (b) s += t          — appends to s, amortized O(m) — PREFERRED
   (c) s.append(t)     — same as +=
   (d) s.push_back(c)  — append single char, amortized O(1)
   (e) stringstream    — build string from mixed types
   (f) to_string(num)  — convert number to string
   (g) stoi/stol/stoll — convert string to number

 ⚠️ PERFORMANCE:
   SLOW:  for (int i = 0; i < n; i++) s = s + "x";  → O(n²)!
   FAST:  for (int i = 0; i < n; i++) s += "x";      → O(n) amortized

   REASON: s = s + "x" creates a NEW string each time → copy entire s!
           s += "x" appends in-place with amortized O(1)

 NUMBER ↔ STRING CONVERSIONS:
   to_string(42)       → "42"
   to_string(3.14)     → "3.140000"
   stoi("42")          → 42
   stol("1234567890")  → 1234567890L
   stoll("9999999999") → 9999999999LL
   stod("3.14")        → 3.14
*/

void demo_concatenation() {
    cout << "\n=== SECTION 13: CONCATENATION ===" << endl;

    // Operator +
    string a = "Hello";
    string b = " World";
    cout << "a + b: " << a + b << endl;

    // Operator +=
    string c = "Hello";
    c += " World";
    cout << "c += : " << c << endl;

    // append
    string d = "Hello";
    d.append(" World");
    d.append(3, '!');  // append 3 exclamation marks
    cout << "append: " << d << endl;

    // push_back
    string e;
    for (char ch = 'a'; ch <= 'e'; ch++) {
        e.push_back(ch);
    }
    cout << "push_back: " << e << endl;

    // stringstream for building
    stringstream ss;
    ss << "Name: " << "Sarvan" << ", Age: " << 25 << ", Score: " << 99.5;
    cout << "stringstream: " << ss.str() << endl;

    // Number to string
    cout << "to_string(42): " << to_string(42) << endl;
    cout << "to_string(3.14): " << to_string(3.14) << endl;

    // String to number
    cout << "stoi(\"42\"): " << stoi("42") << endl;
    cout << "stoll(\"9999999999\"): " << stoll("9999999999") << endl;
    cout << "stod(\"3.14\"): " << stod("3.14") << endl;

    // Join vector of strings
    vector<string> words = {"Hello", "World", "From", "C++"};
    string joined;
    for (int i = 0; i < (int)words.size(); i++) {
        if (i > 0) joined += " ";
        joined += words[i];
    }
    cout << "Joined: " << joined << endl;

    // Split string by delimiter
    string csv = "a,b,c,d,e";
    vector<string> tokens;
    stringstream ss2(csv);
    string tok;
    while (getline(ss2, tok, ',')) {
        tokens.push_back(tok);
    }
    cout << "Split: ";
    for (auto& t : tokens) cout << "[" << t << "] ";
    cout << endl;
}

// ═══════════════════════════════════════════════════════════════
// MAIN — Run all demonstrations
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_input_output();
    demo_length();
    demo_traversal();
    demo_reverse();
    demo_case_conversion();
    demo_cleaning();
    demo_manipulation();
    demo_palindrome();
    demo_frequency();
    demo_char_vs_string();
    demo_ascii();
    demo_substring();
    demo_concatenation();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 13 String Basics concepts covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                               ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 344  — Reverse String                                  ║
║  LeetCode 125  — Valid Palindrome                                ║
║  LeetCode 709  — To Lower Case                                   ║
║  LeetCode 387  — First Unique Character in a String              ║
║  LeetCode 242  — Valid Anagram                                   ║
║  LeetCode 13   — Roman to Integer                                ║
║  LeetCode 14   — Longest Common Prefix                           ║
║  LeetCode 58   — Length of Last Word                             ║
║  LeetCode 28   — Find the Index of First Occurrence              ║
║  LeetCode 459  — Repeated Substring Pattern                      ║
║  CF 71A        — Way Too Long Words                              ║
║  CF 112A       — Petya and Strings                               ║
║  CF 282A       — Bit++                                           ║
╚══════════════════════════════════════════════════════════════════╝
*/

