/*
Author: Sarvan.DP.GrandMaster
Created : 2026-04-17 20:56:06
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

/* Problem: LeetCode 2129. Capitalize the Title
Given a string title consisting of one or more words separated by a single space,
capitalize the string by changing the capitalization of each word such that:
    If the length of a word is 1 or 2 letters, change all letters to lowercase.
    Otherwise, change the first letter to uppercase and the remaining letters to lowercase.

Return the capitalized title.

Example 1:
Input: title = "capiTalIze tHe titLe"
Output: "Capitalize The Title"
Explanation: Since all words have a length of at least 3, the first letter of each word is uppercase and the remaining letters are lowercase.

Example 2:
Input: title = "First leTTeR of EACH Word"
Output: "First Letter of Each Word"
Explanation: The word "of" has length 2, so it is all lowercase, while the remaining words have their first letter in uppercase and the rest in lowercase.

Example 3:
Input: title = "i lOve leetcode"
Output: "i Love Leetcode"
Explanation: The word "i" has length 1, so it is lowercase, while the remaining words have their first letter in uppercase and the rest in lowercase.

Constraints:
    • 1 <= title.length <= 100
    • title consists of words separated by a single space with no leading or trailing spaces.
    • Each word consists of uppercase and lowercase English letters only.
*/

// Approach 1: Use Two Pointer + String Concept
// Key Idea: Instead of modifying while iterating blindly, you need to:
//  1. Identify each word
//  2. Measure its length
//  3. Then apply rules
// Time Complexity -> O(n) || Space Complexity -> O(1)

string capitalizeTitle(string title){
    int n = (int)title.size();

    // Core Logic:
    // 1. left = start of word
    // 2. right = end of word
    // 3. find length len = right - left -> This gives exact word length before modifying anything
    // 4. check len > 2 than convert lower to upper case as first word

    int left = 0; // start first word
    while (left < n) {
        int right = left; // assign right = left take a word and traverse whole word until find space & convert everything in lowercase
        while (right < n && title[right] != ' '){
            title[right] |= 32; // convert lowercase
            right++;
        }

        // If the word length is greater than 2, capitalize the first letter
        if (right - left > 2) title[left] &= ~32; // Bitwise trick to make uppercase

        left = right + 1; // update left pointer to the next word
    }

    return title;
}
void solve() {
    string str;
    getline(cin, str);

    cout << str << "\n";
    cout << capitalizeTitle(str) << "\n";

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(10);
    
    // Multi-test case support (commented out for this demo)
    // int TC = 1;
    // cin >> TC;
    // while (TC--) solve();
    
    solve();
    return 0;
}

