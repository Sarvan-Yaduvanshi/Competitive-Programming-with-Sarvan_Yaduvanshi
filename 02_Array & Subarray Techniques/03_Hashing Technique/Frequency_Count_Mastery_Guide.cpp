/*
╔══════════════════════════════════════════════════════════════════════════════╗
║        FREQUENCY COUNT MASTERY GUIDE: Zero to Grandmaster Level              ║
║                    Author: Sarvan.DP.GrandMaster                             ║
║                    Created: 2026-02-15                                       ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
==================
1. What is Frequency Counting?
2. When to Use Which Data Structure?
3. Type 1: Integer Frequency Count
4. Type 2: Character Frequency Count (Lowercase a-z)
5. Type 3: Character Frequency Count (All ASCII)
6. Type 4: String Frequency Count
7. Type 5: Pair/Tuple Frequency Count
8. Type 6: 2D Coordinate Frequency
9. Advanced Techniques
10. Practice Problems List
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <array>

using namespace std;
using i64 = long long;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define nl '\n'

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    1. WHAT IS FREQUENCY COUNTING?                            ║
╚══════════════════════════════════════════════════════════════════════════════╝

Frequency counting = Count how many times each element appears in a collection.

Example: arr = [1, 2, 2, 3, 3, 3]
         Frequency: 1 → 1 time, 2 → 2 times, 3 → 3 times
*/

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║              2. WHEN TO USE WHICH DATA STRUCTURE?                            ║
╚══════════════════════════════════════════════════════════════════════════════╝

┌─────────────────────┬──────────────────┬──────────────────┬─────────────────────┐
│ Data Structure      │ Time Complexity  │ Space Complexity │ Best Use Case       │
├─────────────────────┼──────────────────┼──────────────────┼─────────────────────┤
│ vector<int> freq    │ O(1) access      │ O(max_value)     │ Small range values  │
│                     │                  │                  │ (0 to 10^6)         │
├─────────────────────┼──────────────────┼──────────────────┼─────────────────────┤
│ array<int, 26>      │ O(1) access      │ O(26) = O(1)     │ Lowercase letters   │
│                     │                  │                  │ only (a-z)          │
├─────────────────────┼──────────────────┼──────────────────┼─────────────────────┤
│ array<int, 256>     │ O(1) access      │ O(256) = O(1)    │ All ASCII chars     │
├─────────────────────┼──────────────────┼──────────────────┼─────────────────────┤
│ unordered_map       │ O(1) average     │ O(unique_elem)   │ Large range values, │
│                     │ O(n) worst       │                  │ sparse data         │
├─────────────────────┼──────────────────┼──────────────────┼─────────────────────┤
│ map                 │ O(log n)         │ O(unique_elem)   │ Need sorted order,  │
│                     │                  │                  │ custom types        │
└─────────────────────┴──────────────────┴──────────────────┴─────────────────────┘

🔥 GOLDEN RULE:
   - Values in range [0, 10^6] → Use vector<int>
   - Only lowercase letters → Use array<int, 26>
   - Large/negative values → Use unordered_map
   - Need sorted keys → Use map
*/

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║              3. TYPE 1: INTEGER FREQUENCY COUNT                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// Method 1: Brute-force frequency counter
// Time Complexity: O(N^2)
// Space Complexity: O(N)
// NOTE: Works only for small constraints (n ≤ ~5000)
vec<pair<int, int>> countFreqBruteForce(const vec<int>& arr) {
    int n = sz(arr);

    // Marks whether index i has already been counted
    vec<char> visited(n, 0);

    // Stores (value, frequency)
    vec<pair<int, int>> ans;

    for (int i = 0; i < n; i++) {
        // Skip elements already processed
        if (visited[i]) continue;

        int cnt = 1;          // Current element counts itself
        visited[i] = 1;       // Mark current index as processed

        // Count occurrences of arr[i] in the remaining suffix
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                visited[j] = 1;   // Mark duplicate as processed
                cnt++;
            }
        }

        // Record frequency of arr[i]
        ans.pb({arr[i], cnt});
    }

    return ans;
}

// ═══════════════════════════════════════════════════════════════════════════
// METHOD 1: Using Vector (BEST when values are in small range like 0 to 10^6)
// ═══════════════════════════════════════════════════════════════════════════

// Time: O(n), Space: O(max_value)
void frequencyWithVector() {
    cout << "=== METHOD 1: Vector Frequency ===\n";

    vector<int> arr = {1, 2, 2, 3, 3, 3, 5, 5};
    int maxVal = *max_element(all(arr)); // Find maximum value

    // Create frequency vector of size (maxVal + 1)
    vector<int> freq(maxVal + 1, 0);

    // Count frequencies
    for (int x : arr) {
        freq[x]++;
    }

    // Print frequencies
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << nl;

    for (int i = 0; i <= maxVal; i++) {
        if (freq[i] > 0) {
            cout << i << " appears " << freq[i] << " times\n";
        }
    }

    // USEFUL OPERATIONS:
    // freq[x]         → Get frequency of x (O(1))
    // freq[x]++       → Increment frequency of x
    // freq[x]--       → Decrement frequency of x
    // freq[x] > 0     → Check if x exists
}

// ═══════════════════════════════════════════════════════════════════════════
// METHOD 2: Using unordered_map (BEST for large/negative values or sparse data)
// ═══════════════════════════════════════════════════════════════════════════

// Time: O(n) average, Space: O(unique elements)
void frequencyWithUnorderedMap() {
    cout << "\n=== METHOD 2: Unordered Map Frequency ===\n";

    vector<int> arr = {-5, 1000000000, 2, -5, 1000000000, 1000000000};

    unordered_map<int, int> freq;

    // Count frequencies
    for (int x : arr) {
        freq[x]++;
    }

    // Print frequencies
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << nl;

    for (auto& [key, count] : freq) {
        cout << key << " appears " << count << " times\n";
    }

    // USEFUL OPERATIONS:
    // freq[x]              → Get frequency (creates entry with 0 if not exists)
    // freq.count(x)        → Check if x exists (returns 0 or 1)
    // freq.find(x)         → Returns iterator to element (or freq.end())
    // freq.erase(x)        → Remove element x
    // freq.size()          → Number of unique elements
}

// ═══════════════════════════════════════════════════════════════════════════
// METHOD 3: Using map (BEST when you need sorted order of keys)
// ═══════════════════════════════════════════════════════════════════════════

// Time: O(n log n), Space: O(unique elements)
void frequencyWithMap() {
    cout << "\n=== METHOD 3: Map Frequency (Sorted Keys) ===\n";

    vector<int> arr = {5, 2, 8, 2, 5, 5, 1};

    map<int, int> freq;

    for (int x : arr) {
        freq[x]++;
    }

    cout << "Frequencies in sorted order:\n";
    for (auto& [key, count] : freq) {
        cout << key << " appears " << count << " times\n";
    }
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║         4. TYPE 2: CHARACTER FREQUENCY (LOWERCASE a-z ONLY)                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

🔥 THIS IS SUPER IMPORTANT IN COMPETITIVE PROGRAMMING!
   Since there are only 26 lowercase letters, use array<int, 26> or int freq[26]

   Key Concept: 'a' - 'a' = 0, 'b' - 'a' = 1, ..., 'z' - 'a' = 25
*/

// ═══════════════════════════════════════════════════════════════════════════
// METHOD 1: Using array<int, 26> - MOST EFFICIENT
// ═══════════════════════════════════════════════════════════════════════════

void lowercaseFrequencyArray() {
    cout << "\n=== LOWERCASE FREQUENCY: Array Method ===\n";

    string s = "programming";

    // Method 1: Using array
    array<int, 26> freq = {0}; // Initialize all to 0

    // Count frequencies
    for (char c : s) {
        freq[c - 'a']++;  // 'a' → index 0, 'b' → index 1, ..., 'z' → index 25
    }

    cout << "String: " << s << nl;
    cout << "Character frequencies:\n";

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            char c = 'a' + i;  // Convert index back to character
            cout << c << " appears " << freq[i] << " times\n";
        }
    }

    // COMMON OPERATIONS:
    // freq[c - 'a']        → Get frequency of character c
    // freq[c - 'a']++      → Increment frequency
    // freq[c - 'a'] > 0    → Check if character exists
}

// ═══════════════════════════════════════════════════════════════════════════
// METHOD 2: Using int freq[26] - C-style array
// ═══════════════════════════════════════════════════════════════════════════

void lowercaseFrequencyCArray() {
    cout << "\n=== LOWERCASE FREQUENCY: C-Array Method ===\n";

    string s = "hello";

    int freq[26] = {0};  // All initialized to 0

    for (char c : s) {
        freq[c - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << (char)('a' + i) << ": " << freq[i] << nl;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// COMPARING TWO STRINGS (Anagram Check) - Classic Problem!
// ═══════════════════════════════════════════════════════════════════════════

bool areAnagrams(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;

    array<int, 26> freq = {0};

    // Add frequencies from s1, subtract from s2
    for (int i = 0; i < sz(s1); i++) {
        freq[s1[i] - 'a']++;
        freq[s2[i] - 'a']--;
    }

    // If all frequencies are 0, strings are anagrams
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) return false;
    }
    return true;
}

void anagramDemo() {
    cout << "\n=== ANAGRAM CHECK ===\n";

    string s1 = "listen", s2 = "silent";
    cout << s1 << " and " << s2 << " are anagrams? "
         << (areAnagrams(s1, s2) ? "YES" : "NO") << nl;

    s1 = "hello"; s2 = "world";
    cout << s1 << " and " << s2 << " are anagrams? "
         << (areAnagrams(s1, s2) ? "YES" : "NO") << nl;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║        5. TYPE 3: CHARACTER FREQUENCY (UPPERCASE + LOWERCASE + ALL)          ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// ═══════════════════════════════════════════════════════════════════════════
// UPPERCASE ONLY (A-Z) - 26 characters
// ═══════════════════════════════════════════════════════════════════════════

void uppercaseFrequency() {
    cout << "\n=== UPPERCASE FREQUENCY ===\n";

    string s = "HELLO";
    array<int, 26> freq = {0};

    for (char c : s) {
        freq[c - 'A']++;  // 'A' → 0, 'B' → 1, ..., 'Z' → 25
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << (char)('A' + i) << ": " << freq[i] << nl;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// BOTH UPPER & LOWERCASE (A-Z, a-z) - 52 characters
// ═══════════════════════════════════════════════════════════════════════════

void mixedCaseFrequency() {
    cout << "\n=== MIXED CASE FREQUENCY (52 chars) ===\n";

    string s = "HelloWorld";
    array<int, 52> freq = {0};

    // Index mapping:
    // 'A'-'Z' → 0-25
    // 'a'-'z' → 26-51

    for (char c : s) {
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            freq[c - 'a' + 26]++;
        }
    }

    cout << "Uppercase:\n";
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << (char)('A' + i) << ": " << freq[i] << nl;
        }
    }

    cout << "Lowercase:\n";
    for (int i = 26; i < 52; i++) {
        if (freq[i] > 0) {
            cout << (char)('a' + i - 26) << ": " << freq[i] << nl;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// CASE-INSENSITIVE FREQUENCY (treat 'A' and 'a' as same)
// ═══════════════════════════════════════════════════════════════════════════

void caseInsensitiveFrequency() {
    cout << "\n=== CASE-INSENSITIVE FREQUENCY ===\n";

    string s = "AaBbCcAA";
    array<int, 26> freq = {0};

    for (char c : s) {
        // Convert to lowercase
        char lower = tolower(c);  // or: (c >= 'A' && c <= 'Z') ? c + 32 : c
        freq[lower - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << (char)('a' + i) << ": " << freq[i] << nl;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// ALL ASCII CHARACTERS (0-255) - Use when string has digits, symbols, etc.
// ═══════════════════════════════════════════════════════════════════════════

void allASCIIFrequency() {
    cout << "\n=== ALL ASCII FREQUENCY ===\n";

    string s = "Hello, World! 123";
    array<int, 256> freq = {0};

    for (unsigned char c : s) {
        freq[c]++;
    }

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            if (i >= 32 && i <= 126) {  // Printable characters
                cout << "'" << (char)i << "': " << freq[i] << nl;
            } else {
                cout << "ASCII " << i << ": " << freq[i] << nl;
            }
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// DIGITS ONLY (0-9) - 10 characters
// ═══════════════════════════════════════════════════════════════════════════

void digitFrequency() {
    cout << "\n=== DIGIT FREQUENCY ===\n";

    string s = "a1b2c3d4e5112233";
    array<int, 10> freq = {0};

    for (char c : s) {
        if (c >= '0' && c <= '9') {
            freq[c - '0']++;  // '0' → 0, '1' → 1, ..., '9' → 9
        }
    }

    for (int i = 0; i < 10; i++) {
        if (freq[i] > 0) {
            cout << i << ": " << freq[i] << nl;
        }
    }
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    6. TYPE 4: STRING FREQUENCY COUNT                         ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

void stringFrequency() {
    cout << "\n=== STRING FREQUENCY ===\n";

    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};

    // Using unordered_map (faster, O(1) average)
    unordered_map<string, int> freq;

    for (const string& word : words) {
        freq[word]++;
    }

    cout << "Word frequencies:\n";
    for (auto& [word, count] : freq) {
        cout << word << ": " << count << nl;
    }

    // Using map (sorted order)
    cout << "\nSorted word frequencies:\n";
    map<string, int> sortedFreq(freq.begin(), freq.end());
    for (auto& [word, count] : sortedFreq) {
        cout << word << ": " << count << nl;
    }
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                  7. TYPE 5: PAIR/TUPLE FREQUENCY COUNT                       ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

void pairFrequency() {
    cout << "\n=== PAIR FREQUENCY ===\n";

    vector<pair<int, int>> points = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};

    // map works with pairs (unordered_map needs custom hash)
    map<pair<int, int>, int> freq;

    for (auto& p : points) {
        freq[p]++;
    }

    cout << "Point frequencies:\n";
    for (auto& [point, count] : freq) {
        cout << "(" << point.first << ", " << point.second << "): " << count << nl;
    }
}

// Custom hash for unordered_map with pairs
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<i64>()(((i64)p.first << 32) | p.second);
    }
};

void pairFrequencyUnordered() {
    cout << "\n=== PAIR FREQUENCY (Unordered) ===\n";

    vector<pair<int, int>> points = {{1, 2}, {3, 4}, {1, 2}};

    unordered_map<pair<int, int>, int, PairHash> freq;

    for (auto& p : points) {
        freq[p]++;
    }

    for (auto& [point, count] : freq) {
        cout << "(" << point.first << ", " << point.second << "): " << count << nl;
    }
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                 8. TYPE 6: 2D COORDINATE FREQUENCY                           ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

void coordinate2DFrequency() {
    cout << "\n=== 2D COORDINATE FREQUENCY ===\n";

    // When coordinates are small (0 to 1000), use 2D vector
    int maxX = 10, maxY = 10;
    vector<vector<int>> freq(maxX + 1, vector<int>(maxY + 1, 0));

    vector<pair<int, int>> points = {{1, 2}, {3, 4}, {1, 2}, {5, 6}};

    for (auto& [x, y] : points) {
        freq[x][y]++;
    }

    cout << "Non-zero frequencies:\n";
    for (int i = 0; i <= maxX; i++) {
        for (int j = 0; j <= maxY; j++) {
            if (freq[i][j] > 0) {
                cout << "(" << i << ", " << j << "): " << freq[i][j] << nl;
            }
        }
    }
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                       9. ADVANCED TECHNIQUES                                 ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 1: Find element with maximum frequency
// ═══════════════════════════════════════════════════════════════════════════

void findMaxFrequency() {
    cout << "\n=== FIND MAX FREQUENCY ELEMENT ===\n";

    vector<int> arr = {1, 3, 2, 3, 4, 3, 2, 3};

    unordered_map<int, int> freq;
    int maxFreq = 0, maxElement = arr[0];

    for (int x : arr) {
        freq[x]++;
        if (freq[x] > maxFreq) {
            maxFreq = freq[x];
            maxElement = x;
        }
    }

    cout << "Element " << maxElement << " has max frequency: " << maxFreq << nl;
}

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 2: Find all elements with frequency >= k
// ═══════════════════════════════════════════════════════════════════════════

void findFrequencyAtLeastK(int k) {
    cout << "\n=== ELEMENTS WITH FREQUENCY >= " << k << " ===\n";

    vector<int> arr = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};

    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    vector<int> result;
    for (auto& [elem, count] : freq) {
        if (count >= k) {
            result.push_back(elem);
        }
    }

    cout << "Elements: ";
    for (int x : result) cout << x << " ";
    cout << nl;
}

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 3: First unique element
// ═══════════════════════════════════════════════════════════════════════════

void firstUniqueElement() {
    cout << "\n=== FIRST UNIQUE ELEMENT ===\n";

    vector<int> arr = {4, 5, 1, 2, 1, 4, 2};

    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    for (int x : arr) {
        if (freq[x] == 1) {
            cout << "First unique element: " << x << nl;
            return;
        }
    }
    cout << "No unique element found\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 4: Count distinct elements
// ═══════════════════════════════════════════════════════════════════════════

void countDistinct() {
    cout << "\n=== COUNT DISTINCT ELEMENTS ===\n";

    vector<int> arr = {1, 2, 2, 3, 3, 3, 4};

    // Method 1: Using set
    unordered_set<int> distinct(arr.begin(), arr.end());
    cout << "Distinct count (set): " << distinct.size() << nl;

    // Method 2: Using frequency map
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;
    cout << "Distinct count (map): " << freq.size() << nl;
}

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 5: Frequency of frequencies
// ═══════════════════════════════════════════════════════════════════════════

void frequencyOfFrequencies() {
    cout << "\n=== FREQUENCY OF FREQUENCIES ===\n";

    vector<int> arr = {1, 1, 2, 2, 2, 3};
    // 1 appears 2 times, 2 appears 3 times, 3 appears 1 time
    // Frequency of freq 1 = 1, freq 2 = 1, freq 3 = 1

    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    unordered_map<int, int> freqOfFreq;
    for (auto& [elem, count] : freq) {
        freqOfFreq[count]++;
    }

    cout << "Element frequencies: ";
    for (auto& [elem, count] : freq) {
        cout << elem << "→" << count << " ";
    }
    cout << nl;

    cout << "Frequency of frequencies:\n";
    for (auto& [f, count] : freqOfFreq) {
        cout << "Frequency " << f << " appears " << count << " times\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 6: Sliding Window Frequency
// ═══════════════════════════════════════════════════════════════════════════

void slidingWindowFrequency() {
    cout << "\n=== SLIDING WINDOW FREQUENCY ===\n";

    vector<int> arr = {1, 2, 1, 3, 4, 2, 3};
    int k = 4;  // Window size

    unordered_map<int, int> freq;

    // Initialize first window
    for (int i = 0; i < k; i++) {
        freq[arr[i]]++;
    }

    cout << "Window [0, " << k-1 << "]: " << freq.size() << " distinct elements\n";

    // Slide the window
    for (int i = k; i < sz(arr); i++) {
        // Remove leftmost element
        freq[arr[i - k]]--;
        if (freq[arr[i - k]] == 0) {
            freq.erase(arr[i - k]);
        }

        // Add new element
        freq[arr[i]]++;

        cout << "Window [" << i-k+1 << ", " << i << "]: " << freq.size() << " distinct elements\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// TECHNIQUE 7: Check if two arrays have same frequency distribution
// ═══════════════════════════════════════════════════════════════════════════

bool haveSameFrequency(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;

    unordered_map<int, int> freq;
    for (int x : a) freq[x]++;
    for (int x : b) freq[x]--;

    for (auto& [key, count] : freq) {
        if (count != 0) return false;
    }
    return true;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║          10. VECTOR vs UNORDERED_MAP - PERFORMANCE COMPARISON                ║
╚══════════════════════════════════════════════════════════════════════════════╝

When to use VECTOR:
✅ Values are in range [0, 10^6] or similar small range
✅ Need O(1) guaranteed access (no hash collisions)
✅ Dense data (most values appear)
✅ Need to iterate through all possible values

When to use UNORDERED_MAP:
✅ Values can be negative or very large (> 10^7)
✅ Sparse data (few unique values out of large range)
✅ Need to iterate only through existing elements
✅ Memory-efficient for sparse data

When to use MAP:
✅ Need sorted order of keys
✅ Custom comparison needed
✅ Range queries on keys

PERFORMANCE BENCHMARK:
- Vector access: O(1) guaranteed
- Unordered_map access: O(1) average, O(n) worst case
- Map access: O(log n) guaranteed

⚠️ WARNING: In competitive programming, hackers can create anti-hash tests
   that make unordered_map O(n²). Use custom hash or map in such cases.
*/

// Custom hash to prevent anti-hash attacks
struct SafeHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#include <chrono>

void safeHashMapDemo() {
    cout << "\n=== SAFE HASH MAP (Anti-hack) ===\n";

    unordered_map<i64, int, SafeHash> safeMap;

    vector<i64> arr = {1, 2, 2, 3, 3, 3};
    for (i64 x : arr) safeMap[x]++;

    for (auto& [key, count] : safeMap) {
        cout << key << ": " << count << nl;
    }
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    11. PRACTICE PROBLEMS LIST                                ║
╚══════════════════════════════════════════════════════════════════════════════╝

🔥 BEGINNER LEVEL:
────────────────────────────────────────────────────────────────────────────────
1. LeetCode 217 - Contains Duplicate
   https://leetcode.com/problems/contains-duplicate/

2. LeetCode 242 - Valid Anagram
   https://leetcode.com/problems/valid-anagram/

3. LeetCode 383 - Ransom Note
   https://leetcode.com/problems/ransom-note/

4. LeetCode 387 - First Unique Character in a String
   https://leetcode.com/problems/first-unique-character-in-a-string/

5. LeetCode 169 - Majority Element
   https://leetcode.com/problems/majority-element/

6. CodeForces 1873A - Short Sort
   https://codeforces.com/problemset/problem/1873/A

7. CodeChef - EXPTSMPL (Explore Samples)
   https://www.codechef.com/practice/course/arrays/ARRAYS/problems/EXPTSMPL

🔥 INTERMEDIATE LEVEL:
────────────────────────────────────────────────────────────────────────────────
8. LeetCode 49 - Group Anagrams
   https://leetcode.com/problems/group-anagrams/

9. LeetCode 347 - Top K Frequent Elements
   https://leetcode.com/problems/top-k-frequent-elements/

10. LeetCode 438 - Find All Anagrams in a String
    https://leetcode.com/problems/find-all-anagrams-in-a-string/

11. LeetCode 560 - Subarray Sum Equals K
    https://leetcode.com/problems/subarray-sum-equals-k/

12. LeetCode 1 - Two Sum
    https://leetcode.com/problems/two-sum/

13. LeetCode 454 - 4Sum II
    https://leetcode.com/problems/4sum-ii/

14. CodeForces 1352C - K-th Not Divisible by n
    https://codeforces.com/problemset/problem/1352/C

15. CodeForces 1729B - Decode String
    https://codeforces.com/problemset/problem/1729/B

16. CSES - Distinct Numbers
    https://cses.fi/problemset/task/1621

🔥 ADVANCED LEVEL:
────────────────────────────────────────────────────────────────────────────────
17. LeetCode 76 - Minimum Window Substring
    https://leetcode.com/problems/minimum-window-substring/

18. LeetCode 567 - Permutation in String
    https://leetcode.com/problems/permutation-in-string/

19. LeetCode 992 - Subarrays with K Different Integers
    https://leetcode.com/problems/subarrays-with-k-different-integers/

20. LeetCode 1248 - Count Number of Nice Subarrays
    https://leetcode.com/problems/count-number-of-nice-subarrays/

21. LeetCode 930 - Binary Subarrays With Sum
    https://leetcode.com/problems/binary-subarrays-with-sum/

22. CodeForces 1624C - Division by Two and Permutation
    https://codeforces.com/problemset/problem/1624/C

23. CodeForces 1706C - Qpwoeirut And The City
    https://codeforces.com/problemset/problem/1706/C

🔥 GRANDMASTER LEVEL:
────────────────────────────────────────────────────────────────────────────────
24. LeetCode 1074 - Number of Submatrices That Sum to Target
    https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/

25. LeetCode 2025 - Maximum Number of Ways to Partition an Array
    https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/

26. CodeForces 1418C - Mortal Kombat Tower
    https://codeforces.com/problemset/problem/1418/C

27. CodeForces 1551D1 - Domino (easy version)
    https://codeforces.com/problemset/problem/1551/D1

28. AtCoder ABC159D - Banned K
    https://atcoder.jp/contests/abc159/tasks/abc159_d

29. CSES - Sum of Four Values
    https://cses.fi/problemset/task/1642

🔥 TOPIC-WISE SHEETS:
────────────────────────────────────────────────────────────────────────────────
• LeetCode Hashing Problems:
  https://leetcode.com/tag/hash-table/

• CodeForces EDU - Hashing:
  https://codeforces.com/edu/course/2/lesson/2

• CSES Sorting and Searching:
  https://cses.fi/problemset/list/

• A2OJ Hashing Ladder:
  https://a2oj.netlify.app/ladders
*/

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                           QUICK REFERENCE CARD                               ║
╚══════════════════════════════════════════════════════════════════════════════╝

┌─────────────────────────────────────────────────────────────────────────────┐
│ DATA TYPE        │ BEST STRUCTURE     │ CODE TEMPLATE                       │
├─────────────────────────────────────────────────────────────────────────────┤
│ int (0 to 10^6)  │ vector<int>        │ vector<int> freq(maxVal+1, 0);      │
│                  │                    │ freq[x]++;                          │
├─────────────────────────────────────────────────────────────────────────────┤
│ int (large/neg)  │ unordered_map      │ unordered_map<int,int> freq;        │
│                  │                    │ freq[x]++;                          │
├─────────────────────────────────────────────────────────────────────────────┤
│ char (a-z)       │ array<int, 26>     │ array<int, 26> freq = {0};          │
│                  │                    │ freq[c - 'a']++;                    │
├─────────────────────────────────────────────────────────────────────────────┤
│ char (A-Z)       │ array<int, 26>     │ freq[c - 'A']++;                    │
├─────────────────────────────────────────────────────────────────────────────┤
│ char (0-9)       │ array<int, 10>     │ freq[c - '0']++;                    │
├─────────────────────────────────────────────────────────────────────────────┤
│ char (all)       │ array<int, 256>    │ freq[(unsigned char)c]++;           │
├─────────────────────────────────────────────────────────────────────────────┤
│ string           │ unordered_map      │ unordered_map<string,int> freq;     │
│                  │                    │ freq[s]++;                          │
├─────────────────────────────────────────────────────────────────────────────┤
│ pair<int,int>    │ map                │ map<pair<int,int>, int> freq;       │
│                  │                    │ freq[{x,y}]++;                      │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║     FREQUENCY COUNT MASTERY - ALL DEMONSTRATIONS            ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";

    // Integer frequency methods
    frequencyWithVector();
    frequencyWithUnorderedMap();
    frequencyWithMap();

    // Character frequency methods
    lowercaseFrequencyArray();
    lowercaseFrequencyCArray();
    anagramDemo();
    uppercaseFrequency();
    mixedCaseFrequency();
    caseInsensitiveFrequency();
    allASCIIFrequency();
    digitFrequency();

    // String frequency
    stringFrequency();

    // Pair frequency
    pairFrequency();
    pairFrequencyUnordered();

    // 2D coordinate
    coordinate2DFrequency();

    // Advanced techniques
    findMaxFrequency();
    findFrequencyAtLeastK(3);
    firstUniqueElement();
    countDistinct();
    frequencyOfFrequencies();
    slidingWindowFrequency();

    // Safe hash demo
    safeHashMapDemo();

    cout << "\n✅ All demonstrations completed!\n";
    cout << "📚 Check the code comments for detailed explanations!\n";
    cout << "🎯 Practice the problems listed in section 11!\n";

    return 0;
}

