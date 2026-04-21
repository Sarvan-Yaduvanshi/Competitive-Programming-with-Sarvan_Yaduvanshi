/*
Author: Sarvan.DP.GrandMaster
Created : 2026-04-19 12:32:09
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

/* Problem: Leetcode 443 String Compression
 * Problem Statement: You are given an array of characters chars. Compress it using the following algorithm:
    Begin with an empty string s. For each group of consecutive repeating characters in chars:
        If the group's length is 1, append the character to s.
        Otherwise, append the character followed by the group's length.
    The compressed string s should not be returned separately, but instead be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.
    After you are done modifying the input array, return the new length of the array.

 * Example 1:
 * Input: chars = ["a","a","b","b","c","c","c"]
 * Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
 * Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

 * Example 2:
 * Input: chars = ["a"]
 * Output: Return 1, and the first character of the input array should be: ["a"]
 * Explanation: The only group is "a", which remains uncompressed since it's a single character.

 * Example 3:
 * Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
 * Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
 * Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".

 * Constraints:
    • 1 <= chars.length <= 2000
    • chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.
 */

/*
 * Approach: Two-Pointer (Read/Write)
 * Time Complexity: O(N) | Space Complexity: O(1)
 * * Key Idea:
 * Use a `right` pointer to scan and count consecutive identical characters,
 * and a `left` pointer to overwrite the original array in-place.
 * For each group of characters:
 * 1. Write the character at the `left` pointer.
 * 2. If the count > 1, convert the count to a string and write each digit
 * to the `left` pointer.
 * This guarantees we never use extra memory for a new array.
 */

int stringCompression(vector<char>& chars){
    int n = (int)chars.size();

    int left = 0; // Write pointer (updates the answer)
    int right = 0; // Read pointer (scans the array)

    while (right < n){
        char ch = chars[right];
        int cnt = 0;

        // 1. Count consecutive matching characters
        while (right < n && chars[right] == ch){
            cnt++;
            right++;
        }

        // 2. ALWAYS write the character first
        chars[left++] = ch;
        // 3. ONLY write the count if it's greater than 1
        if (cnt > 1){
            for (char digit : to_string(cnt))
                chars[left++] = digit;
        }
    }

    // 4. Resize array to the new valid length
    chars.resize(left);
    return left;
}

int stringCompressionTwist(vector<char>& chars) {
    int n = chars.size();
    if (n == 0) return 0;

    // --- PASS 1: Calculate the exact final length ---
    int final_len = 0;
    int i = 0;
    while (i < n) {
        int count = 0;
        char ch = chars[i];
        while (i < n && chars[i] == ch) {
            count++;
            i++;
        }
        // Every group needs 1 slot for the char, plus slots for the digits
        final_len += 1 + to_string(count).size();
    }

    // Resize the array to hold the new larger string
    chars.resize(final_len);

    // --- PASS 2: Read and Write Right-to-Left ---
    int read = n - 1;             // End of original data
    int write = final_len - 1;    // End of resized array

    while (read >= 0) {
        char ch = chars[read];
        int count = 0;

        // Count the group going backwards
        while (read >= 0 && chars[read] == ch) {
            count++;
            read--;
        }

        // Since we are writing BACKWARDS:
        // For "12a", we must write 'a' first, then '2', then '1'

        // 1. Write the character
        chars[write--] = ch;

        // 2. Write the digits backwards
        string cnt_str = to_string(count);
        for (int j = cnt_str.size() - 1; j >= 0; j--) {
            chars[write--] = cnt_str[j];
        }
    }

    return final_len;
}

void solve() {
    int n; cin >> n;
    vector<char> ch(n);
    for (int i = 0; i < n; i++)
        cin >> ch[i];

    // Call Fun and store new length
    int newLen = stringCompression(ch);
    // print new length
    cout << "Length: " << newLen << "\n";

    // print modify array
    cout << "Array: ";
    for (char c : ch)
        cout << c << " ";
    cout << "\n";
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

