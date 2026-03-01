/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           CHAPTER 02 — CLASSICAL STRING PROBLEMS                             ║
║           From Zero to Grandmaster — Must-Know Problems                      ║
║           Author: Sarvan Yaduvanshi                                          ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. Anagram Check & Group Anagrams
 2. Isomorphic Strings
 3. Valid Parentheses (Bracket Matching)
 4. Longest Common Prefix
 5. Roman to Integer / Integer to Roman
 6. String Compression (Run-Length Encoding)
 7. Compare Version Numbers
 8. Reverse Words in a String
 9. Count Substrings (various patterns)

DIFFICULTY PROGRESSION:
 Easy:   Anagram, Valid Parentheses, Longest Common Prefix
 Medium: Isomorphic, Roman Conversion, String Compression, Reverse Words
 Hard:   Compare Versions, Count Substrings with conditions
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <cassert>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// PROBLEM 1: ANAGRAM CHECK & GROUP ANAGRAMS
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Two strings are anagrams if they contain the same characters
 with the same frequency, in any order.
 Example: "listen" and "silent" are anagrams.

 APPROACHES:
   (a) Sort both strings, compare — O(n log n)
   (b) Frequency count array — O(n) ✓ BEST
   (c) Prime multiplication — each char → prime, multiply — risk overflow

 GROUP ANAGRAMS:
   Given list of strings, group anagrams together.
   Key insight: sorted string is the canonical form.
   Use map<string, vector<string>> where key = sorted string
*/

// Method 1: Sort-based anagram check — O(n log n)
bool isAnagramSort(string a, string b) {
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

// Method 2: Frequency-based anagram check — O(n), OPTIMAL
bool isAnagramFreq(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    int freq[26] = {0};
    for (char c : a) freq[c - 'a']++;
    for (char c : b) freq[c - 'a']--;
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) return false;
    }
    return true;
}

// Group Anagrams — O(n * k log k) where k = max string length
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }
    return result;
}

// Frequency-key based grouping — O(n * k), truly optimal
vector<vector<string>> groupAnagramsOptimal(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (const string& s : strs) {
        // Build frequency key: "2#1#0#...#0" format
        int freq[26] = {0};
        for (char c : s) freq[c - 'a']++;
        string key;
        for (int i = 0; i < 26; i++) {
            key += to_string(freq[i]) + '#';
        }
        groups[key].push_back(s);
    }
    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }
    return result;
}

void demo_anagram() {
    cout << "=== PROBLEM 1: ANAGRAM ===" << endl;
    cout << "listen/silent (sort): " << isAnagramSort("listen", "silent") << endl;
    cout << "listen/silent (freq): " << isAnagramFreq("listen", "silent") << endl;
    cout << "hello/world: " << isAnagramFreq("hello", "world") << endl;

    vector<string> words = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto groups = groupAnagrams(words);
    cout << "Group Anagrams:" << endl;
    for (auto& group : groups) {
        cout << "  [";
        for (int i = 0; i < (int)group.size(); i++) {
            if (i) cout << ", ";
            cout << group[i];
        }
        cout << "]" << endl;
    }
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 2: ISOMORPHIC STRINGS
// ═══════════════════════════════════════════════════════════════
/*
 DEFINITION:
 ──────────
 Two strings s and t are isomorphic if characters in s can be replaced
 to get t, with a 1-to-1 mapping (no two chars map to the same char).

 Examples:
   "egg" ↔ "add"    → YES (e→a, g→d)
   "foo" ↔ "bar"    → NO  (o maps to both a and r? No, o→a first, o→r conflict)
   Actually: f→b, o→a, o→r → conflict, so NO

 APPROACH:
   Maintain TWO mappings: s→t and t→s (both must be consistent)
   Time: O(n), Space: O(1) (at most 128 mappings)

 RELATED: Word Pattern (same idea but with words instead of chars)
*/

bool isIsomorphic(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    char mapST[128] = {0};  // s[i] → t[i]
    char mapTS[128] = {0};  // t[i] → s[i]

    for (int i = 0; i < (int)s.size(); i++) {
        char cs = s[i], ct = t[i];

        if (mapST[(int)cs] == 0 && mapTS[(int)ct] == 0) {
            // New mapping
            mapST[(int)cs] = ct;
            mapTS[(int)ct] = cs;
        } else if (mapST[(int)cs] != ct || mapTS[(int)ct] != cs) {
            return false;  // Conflict
        }
    }
    return true;
}

// Word Pattern: "abba" pattern with "dog cat cat dog" → true
bool wordPattern(const string& pattern, const string& str) {
    stringstream ss(str);
    string word;
    vector<string> words;
    while (ss >> word) words.push_back(word);

    if (pattern.size() != words.size()) return false;

    unordered_map<char, string> charToWord;
    unordered_map<string, char> wordToChar;

    for (int i = 0; i < (int)pattern.size(); i++) {
        char c = pattern[i];
        const string& w = words[i];

        if (charToWord.count(c) && charToWord[c] != w) return false;
        if (wordToChar.count(w) && wordToChar[w] != c) return false;

        charToWord[c] = w;
        wordToChar[w] = c;
    }
    return true;
}

void demo_isomorphic() {
    cout << "\n=== PROBLEM 2: ISOMORPHIC STRINGS ===" << endl;
    cout << "egg/add: " << isIsomorphic("egg", "add") << endl;      // 1
    cout << "foo/bar: " << isIsomorphic("foo", "bar") << endl;      // 0
    cout << "paper/title: " << isIsomorphic("paper", "title") << endl;  // 1
    cout << "Pattern 'abba' / 'dog cat cat dog': "
         << wordPattern("abba", "dog cat cat dog") << endl;  // 1
    cout << "Pattern 'abba' / 'dog cat cat fish': "
         << wordPattern("abba", "dog cat cat fish") << endl;  // 0
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 3: VALID PARENTHESES (BRACKET MATCHING)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Given a string containing '(', ')', '{', '}', '[', ']',
 determine if the input string is valid.

 RULES:
   1. Open brackets must be closed by the same type
   2. Open brackets must be closed in the correct order
   3. Every close bracket has a corresponding open bracket

 APPROACH: Use a STACK
   • Push open brackets
   • For close brackets: check top of stack matches, then pop
   • At end: stack must be empty

 Time: O(n), Space: O(n)

 VARIATIONS:
   • Minimum additions to make valid
   • Longest valid parentheses substring (DP or stack)
   • Score of parentheses
   • Remove invalid parentheses
*/

bool isValidParentheses(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

// Minimum insertions to make valid (only '(' and ')')
int minInsertionsToMakeValid(const string& s) {
    int open = 0, insertions = 0;
    for (char c : s) {
        if (c == '(') {
            open++;
        } else {
            if (open > 0) {
                open--;
            } else {
                insertions++;  // need to insert '('
            }
        }
    }
    return insertions + open;  // open = unmatched '(' needing ')'
}

// Longest valid parentheses substring — O(n) stack approach
int longestValidParentheses(const string& s) {
    stack<int> st;
    st.push(-1);  // base index
    int maxLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i);  // new base
            } else {
                maxLen = max(maxLen, i - st.top());
            }
        }
    }
    return maxLen;
}

void demo_parentheses() {
    cout << "\n=== PROBLEM 3: VALID PARENTHESES ===" << endl;
    cout << "(){}: " << isValidParentheses("(){}") << endl;          // 1
    cout << "(]: " << isValidParentheses("(]") << endl;              // 0
    cout << "([{}]): " << isValidParentheses("([{}])") << endl;      // 1
    cout << "Min insertions '())': " << minInsertionsToMakeValid("())") << endl;  // 1
    cout << "Longest valid ')()())': " << longestValidParentheses(")()())") << endl;  // 4
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 4: LONGEST COMMON PREFIX
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Find the longest common prefix string among an array of strings.

 APPROACHES:
   (a) Vertical scanning — compare char by char across all strings — O(S)
   (b) Horizontal scanning — reduce LCP pairwise — O(S)
   (c) Divide & conquer — split, find LCP of halves, merge — O(S)
   (d) Binary search on length — O(S * log m)
   (e) Trie-based — insert all, find longest common path — O(S)

 where S = sum of all character lengths, m = min string length

 OPTIMAL: Vertical scanning — simplest and efficient.
*/

// Method 1: Vertical scanning — O(S), S = total chars
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    for (int i = 0; i < (int)strs[0].size(); i++) {
        char c = strs[0][i];
        for (int j = 1; j < (int)strs.size(); j++) {
            if (i >= (int)strs[j].size() || strs[j][i] != c) {
                return strs[0].substr(0, i);
            }
        }
    }
    return strs[0];
}

// Method 2: Sort-based trick — O(n * k log k + m)
// After sorting, only compare FIRST and LAST strings!
string longestCommonPrefixSort(vector<string> strs) {
    if (strs.empty()) return "";
    sort(strs.begin(), strs.end());
    string& first = strs[0];
    string& last = strs.back();
    int i = 0;
    while (i < (int)first.size() && i < (int)last.size() && first[i] == last[i]) {
        i++;
    }
    return first.substr(0, i);
}

void demo_lcp() {
    cout << "\n=== PROBLEM 4: LONGEST COMMON PREFIX ===" << endl;
    vector<string> v1 = {"flower", "flow", "flight"};
    cout << "LCP [flower,flow,flight]: " << longestCommonPrefix(v1) << endl;  // "fl"

    vector<string> v2 = {"dog", "racecar", "car"};
    cout << "LCP [dog,racecar,car]: " << longestCommonPrefix(v2) << endl;  // ""

    vector<string> v3 = {"abc", "abcd", "abcde"};
    cout << "LCP [abc,abcd,abcde]: " << longestCommonPrefix(v3) << endl;   // "abc"
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 5: ROMAN TO INTEGER / INTEGER TO ROMAN
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Roman numerals: I=1, V=5, X=10, L=50, C=100, D=500, M=1000

 SUBTRACTION RULE: When a smaller value appears before a larger one:
   IV=4, IX=9, XL=40, XC=90, CD=400, CM=900

 ROMAN → INTEGER:
   Traverse right to left. If current < previous, subtract; else add.
   Time: O(n)

 INTEGER → ROMAN:
   Use greedy: pick largest symbol that fits, subtract, repeat.
   Use table: {1000,900,500,400,100,90,50,40,10,9,5,4,1}
*/

int romanToInt(const string& s) {
    unordered_map<char, int> val = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };

    int result = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (i + 1 < (int)s.size() && val[s[i]] < val[s[i + 1]]) {
            result -= val[s[i]];  // subtraction case
        } else {
            result += val[s[i]];
        }
    }
    return result;
}

string intToRoman(int num) {
    vector<pair<int, string>> table = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string result;
    for (auto& [value, symbol] : table) {
        while (num >= value) {
            result += symbol;
            num -= value;
        }
    }
    return result;
}

void demo_roman() {
    cout << "\n=== PROBLEM 5: ROMAN ↔ INTEGER ===" << endl;
    cout << "III → " << romanToInt("III") << endl;       // 3
    cout << "LVIII → " << romanToInt("LVIII") << endl;   // 58
    cout << "MCMXCIV → " << romanToInt("MCMXCIV") << endl;  // 1994
    cout << "3 → " << intToRoman(3) << endl;           // III
    cout << "58 → " << intToRoman(58) << endl;         // LVIII
    cout << "1994 → " << intToRoman(1994) << endl;     // MCMXCIV
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 6: STRING COMPRESSION (RUN-LENGTH ENCODING)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Compress consecutive identical characters:
   "aabcccccaaa" → "a2b1c5a3"

 LeetCode version: Only add count if > 1, modify in-place.
   "aabcccccaaa" → ["a","2","b","c","5","a","3"]

 DECODE: Read char, then digits → repeat char that many times.

 RLE is basis for many compression algorithms.
 Time: O(n), Space: O(1) extra for in-place variant
*/

// Basic RLE compression
string compress(const string& s) {
    if (s.empty()) return "";
    string result;
    int count = 1;
    for (int i = 1; i <= (int)s.size(); i++) {
        if (i < (int)s.size() && s[i] == s[i - 1]) {
            count++;
        } else {
            result += s[i - 1];
            result += to_string(count);
            count = 1;
        }
    }
    // Return compressed only if shorter
    return result.size() < s.size() ? result : s;
}

// LeetCode 443: In-place compression — return new length
int compressInPlace(vector<char>& chars) {
    int write = 0, read = 0;
    while (read < (int)chars.size()) {
        char currentChar = chars[read];
        int count = 0;
        while (read < (int)chars.size() && chars[read] == currentChar) {
            read++;
            count++;
        }
        chars[write++] = currentChar;
        if (count > 1) {
            string countStr = to_string(count);
            for (char c : countStr) {
                chars[write++] = c;
            }
        }
    }
    return write;
}

// RLE Decompression
string decompress(const string& s) {
    string result;
    int i = 0;
    while (i < (int)s.size()) {
        char c = s[i++];
        string numStr;
        while (i < (int)s.size() && isdigit(s[i])) {
            numStr += s[i++];
        }
        int count = numStr.empty() ? 1 : stoi(numStr);
        result += string(count, c);
    }
    return result;
}

void demo_compression() {
    cout << "\n=== PROBLEM 6: STRING COMPRESSION ===" << endl;
    cout << "Compress 'aabcccccaaa': " << compress("aabcccccaaa") << endl;
    cout << "Compress 'abc': " << compress("abc") << endl;  // abc (shorter)
    cout << "Decompress 'a2b1c5a3': " << decompress("a2b1c5a3") << endl;

    vector<char> chars = {'a','a','b','b','c','c','c'};
    int len = compressInPlace(chars);
    cout << "In-place compress: ";
    for (int i = 0; i < len; i++) cout << chars[i];
    cout << " (length=" << len << ")" << endl;
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 7: COMPARE VERSION NUMBERS
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 Compare "1.2.3" with "1.2.4" → -1
 Compare "1.0.0" with "1" → 0 (trailing zeros don't matter)

 APPROACH:
   Split by '.', compare each revision number as integers.
   If one version has more parts, treat missing parts as 0.

 Time: O(n + m), Space: O(n + m) for split
 Optimized: Use two pointers without splitting — O(n + m) space O(1)
*/

int compareVersion(const string& version1, const string& version2) {
    int i = 0, j = 0;
    int n = version1.size(), m = version2.size();

    while (i < n || j < m) {
        // Extract number from version1
        int num1 = 0;
        while (i < n && version1[i] != '.') {
            num1 = num1 * 10 + (version1[i] - '0');
            i++;
        }
        i++;  // skip '.'

        // Extract number from version2
        int num2 = 0;
        while (j < m && version2[j] != '.') {
            num2 = num2 * 10 + (version2[j] - '0');
            j++;
        }
        j++;  // skip '.'

        if (num1 < num2) return -1;
        if (num1 > num2) return 1;
    }
    return 0;
}

void demo_version() {
    cout << "\n=== PROBLEM 7: COMPARE VERSION NUMBERS ===" << endl;
    cout << "1.2 vs 1.10: " << compareVersion("1.2", "1.10") << endl;      // -1
    cout << "1.01 vs 1.001: " << compareVersion("1.01", "1.001") << endl;  // 0
    cout << "1.0 vs 1.0.0: " << compareVersion("1.0", "1.0.0") << endl;   // 0
    cout << "0.1 vs 1.1: " << compareVersion("0.1", "1.1") << endl;       // -1
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 8: REVERSE WORDS IN A STRING
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 "  the sky  is blue  " → "blue is sky the"

 Rules: Remove leading/trailing spaces, collapse multiple spaces.

 APPROACHES:
   (a) Split by spaces, reverse vector, join — O(n) time, O(n) space
   (b) Reverse entire string, then reverse each word — O(n) time, O(1) space ✓
   (c) Stack-based — push words, pop to build result

 The O(1) space method:
   1. Clean extra spaces
   2. Reverse entire string
   3. Reverse each individual word
*/

// Method 1: Split & reverse — easy to code
string reverseWordsSplit(const string& s) {
    stringstream ss(s);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    string result;
    for (int i = (int)words.size() - 1; i >= 0; i--) {
        if (!result.empty()) result += " ";
        result += words[i];
    }
    return result;
}

// Method 2: In-place with reverse — O(1) extra space
string reverseWordsInPlace(string s) {
    // Step 1: Clean extra spaces
    int write = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] != ' ' || (write > 0 && s[write - 1] != ' ')) {
            s[write++] = s[i];
        }
    }
    // Remove trailing space
    if (write > 0 && s[write - 1] == ' ') write--;
    s.resize(write);

    // Step 2: Reverse entire string
    reverse(s.begin(), s.end());

    // Step 3: Reverse each word
    int start = 0;
    for (int i = 0; i <= (int)s.size(); i++) {
        if (i == (int)s.size() || s[i] == ' ') {
            reverse(s.begin() + start, s.begin() + i);
            start = i + 1;
        }
    }
    return s;
}

void demo_reverse_words() {
    cout << "\n=== PROBLEM 8: REVERSE WORDS ===" << endl;
    cout << "Split: [" << reverseWordsSplit("  the sky  is blue  ") << "]" << endl;
    cout << "In-place: [" << reverseWordsInPlace("  the sky  is blue  ") << "]" << endl;
    cout << "Split: [" << reverseWordsSplit("hello world") << "]" << endl;
}

// ═══════════════════════════════════════════════════════════════
// PROBLEM 9: COUNT SUBSTRINGS (Various Patterns)
// ═══════════════════════════════════════════════════════════════
/*
 THEORY:
 ──────
 A string of length n has n*(n+1)/2 substrings (including empty: +1).

 COMMON COUNTING PROBLEMS:
   (a) Count palindromic substrings
   (b) Count substrings with exactly K distinct characters
   (c) Count substrings containing all vowels
   (d) Count substrings that are anagrams of pattern
   (e) Total number of distinct substrings

 APPROACHES:
   • Expand around center — for palindromes — O(n²)
   • Sliding window — for K-distinct, anagram — O(n)
   • Suffix array — for distinct substrings — O(n log n)
   • DP — for complex conditions

 TRICK: "Exactly K" = "At most K" - "At most K-1"
*/

// Count all palindromic substrings — Expand around center — O(n²)
int countPalindromicSubstrings(const string& s) {
    int n = s.size(), count = 0;
    for (int center = 0; center < n; center++) {
        // Odd-length palindromes
        int left = center, right = center;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        // Even-length palindromes
        left = center;
        right = center + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    }
    return count;
}

// Count substrings with AT MOST K distinct characters — O(n)
int countAtMostKDistinct(const string& s, int k) {
    int n = s.size();
    int freq[128] = {0};
    int distinct = 0, count = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        if (freq[(int)s[right]] == 0) distinct++;
        freq[(int)s[right]]++;

        while (distinct > k) {
            freq[(int)s[left]]--;
            if (freq[(int)s[left]] == 0) distinct--;
            left++;
        }
        count += (right - left + 1);  // all substrings ending at right
    }
    return count;
}

// Count substrings with EXACTLY K distinct characters
int countExactlyKDistinct(const string& s, int k) {
    return countAtMostKDistinct(s, k) - countAtMostKDistinct(s, k - 1);
}

// Count substrings where every character appears at least K times
// Using binary search on answer + sliding window
int countSubstringsAllCharsKTimes(const string& s, int k) {
    int n = s.size(), count = 0;
    // For each unique character count (1 to 26)
    for (int target = 1; target <= 26; target++) {
        int freq[26] = {0};
        int left = 0, unique = 0, countAtLeastK = 0;

        for (int right = 0; right < n; right++) {
            int c = s[right] - 'a';
            if (freq[c] == 0) unique++;
            freq[c]++;
            if (freq[c] == k) countAtLeastK++;

            while (unique > target) {
                int lc = s[left] - 'a';
                if (freq[lc] == k) countAtLeastK--;
                freq[lc]--;
                if (freq[lc] == 0) unique--;
                left++;
            }

            if (unique == target && countAtLeastK == target) {
                count++;
            }
        }
    }
    return count;
}

void demo_count_substrings() {
    cout << "\n=== PROBLEM 9: COUNT SUBSTRINGS ===" << endl;
    cout << "Palindromic substrings in 'aaa': " << countPalindromicSubstrings("aaa") << endl;  // 6
    cout << "Palindromic substrings in 'abc': " << countPalindromicSubstrings("abc") << endl;  // 3
    cout << "At most 2 distinct in 'eceba': " << countAtMostKDistinct("eceba", 2) << endl;
    cout << "Exactly 2 distinct in 'eceba': " << countExactlyKDistinct("eceba", 2) << endl;

    // Total substrings of length n
    string s = "abc";
    int n = s.size();
    cout << "Total substrings of '" << s << "': " << n * (n + 1) / 2 << endl;
}

// ═══════════════════════════════════════════════════════════════
// BONUS: ADDITIONAL CLASSICAL PROBLEMS
// ═══════════════════════════════════════════════════════════════

// Check if s2 is a subsequence of s1
bool isSubsequence(const string& s, const string& t) {
    int i = 0;
    for (int j = 0; j < (int)t.size() && i < (int)s.size(); j++) {
        if (s[i] == t[j]) i++;
    }
    return i == (int)s.size();
}

// Zigzag conversion: "PAYPALISHIRING" with 3 rows → "PAHNAPLSIIGYIR"
string zigzagConversion(const string& s, int numRows) {
    if (numRows <= 1) return s;
    vector<string> rows(min(numRows, (int)s.size()));
    int curRow = 0;
    bool goingDown = false;

    for (char c : s) {
        rows[curRow] += c;
        if (curRow == 0 || curRow == numRows - 1) {
            goingDown = !goingDown;
        }
        curRow += goingDown ? 1 : -1;
    }

    string result;
    for (auto& row : rows) result += row;
    return result;
}

// String multiply (multiply two large numbers as strings)
string multiplyStrings(const string& num1, const string& num2) {
    int n = num1.size(), m = num2.size();
    vector<int> result(n + m, 0);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + result[p2];

            result[p2] = sum % 10;
            result[p1] += sum / 10;
        }
    }

    string str;
    for (int d : result) {
        if (!(str.empty() && d == 0)) {
            str += to_string(d);
        }
    }
    return str.empty() ? "0" : str;
}

void demo_bonus() {
    cout << "\n=== BONUS PROBLEMS ===" << endl;
    cout << "Is 'ace' subseq of 'abcde'? " << isSubsequence("ace", "abcde") << endl;
    cout << "Zigzag 'PAYPALISHIRING' rows=3: " << zigzagConversion("PAYPALISHIRING", 3) << endl;
    cout << "Multiply '123' * '456': " << multiplyStrings("123", "456") << endl;  // 56088
}

// ═══════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demo_anagram();
    demo_isomorphic();
    demo_parentheses();
    demo_lcp();
    demo_roman();
    demo_compression();
    demo_version();
    demo_reverse_words();
    demo_count_substrings();
    demo_bonus();

    cout << "\n═══════════════════════════════════════════" << endl;
    cout << "✅ All 9+ Classical String Problems covered!" << endl;
    cout << "═══════════════════════════════════════════" << endl;

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════╗
║  PRACTICE PROBLEMS                                              ║
╠══════════════════════════════════════════════════════════════════╣
║  LeetCode 242  — Valid Anagram                                   ║
║  LeetCode 49   — Group Anagrams                                  ║
║  LeetCode 205  — Isomorphic Strings                              ║
║  LeetCode 290  — Word Pattern                                    ║
║  LeetCode 20   — Valid Parentheses                               ║
║  LeetCode 32   — Longest Valid Parentheses                       ║
║  LeetCode 14   — Longest Common Prefix                           ║
║  LeetCode 13   — Roman to Integer                                ║
║  LeetCode 12   — Integer to Roman                                ║
║  LeetCode 443  — String Compression                              ║
║  LeetCode 165  — Compare Version Numbers                         ║
║  LeetCode 151  — Reverse Words in a String                       ║
║  LeetCode 647  — Palindromic Substrings                          ║
║  LeetCode 392  — Is Subsequence                                  ║
║  LeetCode 6    — Zigzag Conversion                               ║
║  LeetCode 43   — Multiply Strings                                ║
║  CF 4C         — Registration System                             ║
║  CF 519B       — A and B and Compilation Errors                  ║
╚══════════════════════════════════════════════════════════════════╝
*/

