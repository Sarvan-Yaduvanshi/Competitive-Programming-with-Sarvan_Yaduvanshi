/*
╔══════════════════════════════════════════════════════════════╗
║  03. RECURSION ON STRINGS: Reverse, Palindrome, etc.         ║
║  Level 1 — Recursion Fundamentals                            ║
╚══════════════════════════════════════════════════════════════╝

🎯 Problems:
   1. Reverse a string
   2. Check palindrome
   3. Remove a character from string
   4. Replace character (pi → 3.14)
   5. Move all 'x' to end
   6. Print all subsequences of a string (Preview of Level 2)
*/

#ifndef __APPLE__
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <climits>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

using i64 = long long;
template<class T> using vec = vector<T>;

#define sz(x) ((int)(x).size())
#define nl '\n'


// ═══════════════════════════════════════════════════════════
// 1️⃣ REVERSE A STRING
// ═══════════════════════════════════════════════════════════
/*
   Method 1: Two-pointer (like reverse array)
   Method 2: Build reversed string by recursion

   reverseStr("hello") → "olleh"
*/

// Method 1: In-place two pointer
void reverseStr(string& s, int left, int right) {
    if (left >= right) return;
    swap(s[left], s[right]);
    reverseStr(s, left + 1, right - 1);
}

// Method 2: Build new string (functional style)
// reverseStr2("hello") = reverseStr2("ello") + 'h' = "olle" + "h" = "olleh"
string reverseStr2(const string& s) {
    if (s.empty()) return "";
    return reverseStr2(s.substr(1)) + s[0];
}


// ═══════════════════════════════════════════════════════════
// 2️⃣ CHECK PALINDROME
// ═══════════════════════════════════════════════════════════
/*
   Compare s[left] and s[right], move inward
   Base case: left >= right → true (single char or empty = palindrome)

   isPalin("racecar") → true
   isPalin("hello")   → false
*/
bool isPalindrome(const string& s, int left, int right) {
    if (left >= right) return true;
    if (s[left] != s[right]) return false;
    return isPalindrome(s, left + 1, right - 1);
}


// ═══════════════════════════════════════════════════════════
// 3️⃣ REMOVE A CHARACTER FROM STRING
// ═══════════════════════════════════════════════════════════
/*
   removeChar("hello world", 'o') → "hell wrld"

   Pattern: Process character at index i
            - If it's the target: skip it
            - Otherwise: include it
*/
string removeChar(const string& s, int i, char target) {
    if (i == sz(s)) return "";
    string rest = removeChar(s, i + 1, target);
    if (s[i] == target) return rest;          // Skip
    return string(1, s[i]) + rest;            // Include
}


// ═══════════════════════════════════════════════════════════
// 4️⃣ REPLACE "pi" WITH "3.14"
// ═══════════════════════════════════════════════════════════
/*
   replacePi("xpighpirr") → "x3.14gh3.14rr"

   Pattern: Check current and next char, replace if "pi"
*/
string replacePi(const string& s, int i) {
    if (i >= sz(s)) return "";
    if (i + 1 < sz(s) && s[i] == 'p' && s[i + 1] == 'i') {
        return "3.14" + replacePi(s, i + 2);
    }
    return string(1, s[i]) + replacePi(s, i + 1);
}


// ═══════════════════════════════════════════════════════════
// 5️⃣ MOVE ALL 'x' TO END OF STRING
// ═══════════════════════════════════════════════════════════
/*
   moveXToEnd("axbxcxd") → "abcdxxx"

   🧠 Pattern: Separate into two parts:
      - non-x characters (in order)
      - all x's at the end
*/
string moveXToEnd(const string& s, int i) {
    if (i == sz(s)) return "";
    string rest = moveXToEnd(s, i + 1);
    if (s[i] == 'x') return rest + "x";      // x goes to end
    return string(1, s[i]) + rest;             // non-x stays in front
}


// ═══════════════════════════════════════════════════════════
// 6️⃣ POWER FUNCTION (Recursive) — IMPORTANT FOR CP!
// ═══════════════════════════════════════════════════════════
/*
   Two versions:
   A) Naive: O(n)
   B) Fast (Binary Exponentiation): O(log n) ← MUST KNOW for CP!

   power(2, 10) = 1024

   Fast Power Idea:
   - If exp is even: x^n = (x^(n/2))^2
   - If exp is odd:  x^n = x * x^(n-1)
*/

// Naive O(n)
i64 powerNaive(i64 base, int exp) {
    if (exp == 0) return 1;
    return base * powerNaive(base, exp - 1);
}

// Fast O(log n) — BINARY EXPONENTIATION
i64 powerFast(i64 base, i64 exp, i64 mod = 1'000'000'007LL) {
    if (exp == 0) return 1;

    i64 half = powerFast(base, exp / 2, mod);
    half = (half * half) % mod;

    if (exp & 1) half = (half * base) % mod;  // Odd exponent
    return half;
}


// ═══════════════════════════════════════════════════════════
// 7️⃣ TOWER OF HANOI — Classic Recursion Problem!
// ═══════════════════════════════════════════════════════════
/*
   Move n disks from source to destination using auxiliary peg.
   Rules:
   1. Only move one disk at a time
   2. Can't place larger disk on smaller disk

   Recurrence:
   - Move n-1 disks: source → auxiliary
   - Move disk n: source → destination
   - Move n-1 disks: auxiliary → destination

   Number of moves: 2^n - 1

   Time: O(2^n), Space: O(n) stack
*/
void towerOfHanoi(int n, char source, char destination, char auxiliary) {
    if (n == 0) return;

    // Step 1: Move n-1 disks from source to auxiliary
    towerOfHanoi(n - 1, source, auxiliary, destination);

    // Step 2: Move nth disk from source to destination
    cout << "Move disk " << n << " from " << source << " to " << destination << nl;

    // Step 3: Move n-1 disks from auxiliary to destination
    towerOfHanoi(n - 1, auxiliary, destination, source);
}


// ═══════════════════════════════════════════════════════════
// 🧪 TEST ALL FUNCTIONS
// ═══════════════════════════════════════════════════════════

void solve() {
    // Reverse string
    string s1 = "hello";
    cout << "Original: " << s1 << nl;
    reverseStr(s1, 0, sz(s1) - 1);
    cout << "Reversed (in-place): " << s1 << nl;
    cout << "Reversed (functional): " << reverseStr2("world") << nl;

    // Palindrome
    cout << nl << "Is 'racecar' palindrome? "
         << (isPalindrome("racecar", 0, 6) ? "YES" : "NO") << nl;
    cout << "Is 'hello' palindrome? "
         << (isPalindrome("hello", 0, 4) ? "YES" : "NO") << nl;

    // Remove character
    cout << nl << "Remove 'o' from 'hello world': "
         << removeChar("hello world", 0, 'o') << nl;

    // Replace pi
    cout << "Replace pi in 'xpighpirr': " << replacePi("xpighpirr", 0) << nl;

    // Move x to end
    cout << "Move x in 'axbxcxd': " << moveXToEnd("axbxcxd", 0) << nl;

    // Power
    cout << nl << "2^10 (naive) = " << powerNaive(2, 10) << nl;
    cout << "2^10 (fast) = " << powerFast(2, 10) << nl;
    cout << "2^60 mod 1e9+7 = " << powerFast(2, 60) << nl;

    // Tower of Hanoi
    cout << nl << "Tower of Hanoi (3 disks):" << nl;
    towerOfHanoi(3, 'A', 'C', 'B');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    while (TC--) solve();

    return 0;
}

