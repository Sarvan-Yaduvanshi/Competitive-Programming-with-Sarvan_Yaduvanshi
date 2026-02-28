/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           🚀 HASHING MASTERY: ZERO TO GRANDMASTER LEVEL 🚀                   ║
║                    Complete Guide by Sarvan.DP.GrandMaster                   ║
║                           Created: 2026-02-17                                ║
╚══════════════════════════════════════════════════════════════════════════════╝

📚 TABLE OF CONTENTS:
═══════════════════════════════════════════════════════════════════════════════
 LEVEL 0: What is Hashing & Hash Table? (Foundation)
 LEVEL 1: C++ STL Data Structures Overview
 LEVEL 2: Frequency Counting (All Types)
 LEVEL 3: Map vs Unordered_Map (Deep Dive)
 LEVEL 4: Set vs Unordered_Set (Deep Dive)
 LEVEL 5: Multimap & Multiset
 LEVEL 6: Character Frequency (26 lowercase optimization)
 LEVEL 7: String Hashing
 LEVEL 8: Advanced Patterns for CP
 LEVEL 9: Practice Problems (Platform-wise)
═══════════════════════════════════════════════════════════════════════════════
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <climits>

using namespace std;
using i64 = long long;
#define nl '\n'
#define all(x) (x).begin(), (x).end()

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    LEVEL 0: WHAT IS HASHING & HASH TABLE?                    ║
╚══════════════════════════════════════════════════════════════════════════════╝

🔥 HASHING = Converting data into a fixed-size value (hash code)
🔥 HASH TABLE = Data structure that uses hashing for O(1) average lookup

┌─────────────────────────────────────────────────────────────────────────────┐
│                         HOW HASH TABLE WORKS                                │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│   Key ("apple")  ──→  Hash Function  ──→  Hash Code (e.g., 5)              │
│                                               │                             │
│                                               ▼                             │
│                          ┌─────────────────────────────────┐                │
│                          │  Index 0:  │                    │                │
│                          │  Index 1:  │                    │                │
│                          │  Index 2:  │                    │                │
│                          │  Index 3:  │                    │                │
│                          │  Index 4:  │                    │                │
│                          │  Index 5:  │ "apple" → value    │ ← Stored here │
│                          │  Index 6:  │                    │                │
│                          │  Index 7:  │                    │                │
│                          └─────────────────────────────────┘                │
│                                                                             │
│   COLLISION: When two keys hash to same index                              │
│   Solution: Chaining (linked list) or Open Addressing                      │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘

WHY USE HASHING?
├── Array: O(n) search
├── Sorted Array + Binary Search: O(log n) search
└── Hash Table: O(1) average search ⭐⭐⭐

*/

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                  LEVEL 1: C++ STL DATA STRUCTURES OVERVIEW                   ║
╚══════════════════════════════════════════════════════════════════════════════╝

┌───────────────────────────────────────────────────────────────────────────────┐
│   DATA STRUCTURE    │  ORDERED  │ DUPLICATES │ INSERT/FIND │    USE CASE     │
├───────────────────────────────────────────────────────────────────────────────┤
│   set               │    ✅     │     ❌     │  O(log n)   │ Unique, sorted  │
│   unordered_set     │    ❌     │     ❌     │  O(1) avg   │ Unique, fast    │
│   multiset          │    ✅     │     ✅     │  O(log n)   │ Sorted+dupes    │
├───────────────────────────────────────────────────────────────────────────────┤
│   map               │    ✅     │ Keys: ❌   │  O(log n)   │ Key-Val,sorted  │
│   unordered_map     │    ❌     │ Keys: ❌   │  O(1) avg   │ Key-Val,fast    │
│   multimap          │    ✅     │ Keys: ✅   │  O(log n)   │ Multi key-val   │
└───────────────────────────────────────────────────────────────────────────────┘

🎯 MOST USED IN CP: unordered_map > map > unordered_set > set
*/

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 1.1: SET - Unique Elements, Sorted
// ══════════════════════════════════════════════════════════════════════════════
void demo_set() {
    cout << "═══ SET DEMO ═══" << nl;
    set<int> s;

    // INSERT - O(log n)
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(2);  // Ignored! Already exists
    s.insert(1);

    // OUTPUT: {1, 2, 5, 8} - Always sorted!
    cout << "Set contents: ";
    for (int x : s) cout << x << " ";
    cout << nl;

    // FIND - O(log n)
    if (s.find(5) != s.end()) {
        cout << "5 exists in set" << nl;
    }

    // COUNT - Returns 0 or 1
    if (s.count(5)) {
        cout << "5 exists (using count)" << nl;
    }

    // CONTAINS (C++20)
    // if (s.contains(5)) { cout << "5 exists"; }

    // ERASE - O(log n)
    s.erase(5);

    // LOWER_BOUND - First element >= x
    auto it = s.lower_bound(3);
    if (it != s.end()) {
        cout << "First element >= 3: " << *it << nl; // Output: 8
    }

    // UPPER_BOUND - First element > x
    it = s.upper_bound(2);
    if (it != s.end()) {
        cout << "First element > 2: " << *it << nl; // Output: 8
    }

    // MIN & MAX - O(1)
    cout << "Min: " << *s.begin() << ", Max: " << *s.rbegin() << nl;

    cout << nl;
}

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 1.2: UNORDERED_SET - Unique Elements, Hash-based
// ══════════════════════════════════════════════════════════════════════════════
void demo_unordered_set() {
    cout << "═══ UNORDERED_SET DEMO ═══" << nl;
    unordered_set<int> us;

    // INSERT - O(1) average
    us.insert(5);
    us.insert(2);
    us.insert(8);
    us.insert(2);  // Ignored!

    // OUTPUT: Order not guaranteed! Could be {8, 2, 5} or any order
    cout << "Unordered_set contents: ";
    for (int x : us) cout << x << " ";
    cout << nl;

    // FIND - O(1) average
    if (us.find(5) != us.end()) {
        cout << "5 exists" << nl;
    }

    // COUNT - O(1) average
    cout << "Count of 5: " << us.count(5) << nl;

    // ERASE - O(1) average
    us.erase(5);

    // SIZE
    cout << "Size: " << us.size() << nl;

    // CLEAR
    // us.clear();

    cout << nl;
}

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 1.3: MAP - Key-Value Pairs, Sorted by Keys
// ══════════════════════════════════════════════════════════════════════════════
void demo_map() {
    cout << "═══ MAP DEMO ═══" << nl;
    map<string, int> mp;

    // INSERT - O(log n)
    mp["apple"] = 5;           // Method 1: Direct assignment
    mp.insert({"banana", 10}); // Method 2: insert()
    mp["cherry"] = 15;
    mp["apple"] = 7;           // Updates existing key!

    // OUTPUT: Sorted by keys alphabetically
    cout << "Map contents:" << nl;
    for (auto &[key, val] : mp) {
        cout << "  " << key << " → " << val << nl;
    }

    // ACCESS - O(log n)
    cout << "apple count: " << mp["apple"] << nl;

    // ⚠️ DANGER: Accessing non-existent key CREATES it with value 0!
    // cout << mp["mango"]; // Creates "mango" → 0

    // SAFE ACCESS
    if (mp.find("mango") != mp.end()) {
        cout << mp["mango"];
    } else {
        cout << "mango not found" << nl;
    }

    // COUNT - O(log n)
    if (mp.count("apple")) {
        cout << "apple exists" << nl;
    }

    // ERASE - O(log n)
    mp.erase("apple");

    // LOWER_BOUND & UPPER_BOUND work on keys
    mp["date"] = 20;
    auto it = mp.lower_bound("cherry");
    if (it != mp.end()) {
        cout << "Lower bound of 'cherry': " << it->first << nl;
    }

    cout << nl;
}

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 1.4: UNORDERED_MAP - Key-Value Pairs, Hash-based
// ══════════════════════════════════════════════════════════════════════════════
void demo_unordered_map() {
    cout << "═══ UNORDERED_MAP DEMO ═══" << nl;
    unordered_map<string, int> ump;

    // INSERT - O(1) average
    ump["apple"] = 5;
    ump["banana"] = 10;
    ump["cherry"] = 15;

    // OUTPUT: Order not guaranteed!
    cout << "Unordered_map contents:" << nl;
    for (auto &[key, val] : ump) {
        cout << "  " << key << " → " << val << nl;
    }

    // FIND - O(1) average
    auto it = ump.find("apple");
    if (it != ump.end()) {
        cout << "Found: " << it->first << " → " << it->second << nl;
    }

    // SAFE ACCESS with at() - throws exception if not found
    try {
        cout << "banana: " << ump.at("banana") << nl;
    } catch (out_of_range& e) {
        cout << "Key not found!" << nl;
    }

    cout << nl;
}

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 1.5: MULTISET - Allows Duplicates, Sorted
// ══════════════════════════════════════════════════════════════════════════════
void demo_multiset() {
    cout << "═══ MULTISET DEMO ═══" << nl;
    multiset<int> ms;

    // INSERT - O(log n)
    ms.insert(5);
    ms.insert(2);
    ms.insert(5);  // Allowed! Duplicate accepted
    ms.insert(5);  // Another duplicate
    ms.insert(8);

    // OUTPUT: {2, 5, 5, 5, 8}
    cout << "Multiset contents: ";
    for (int x : ms) cout << x << " ";
    cout << nl;

    // COUNT - Returns actual count of element
    cout << "Count of 5: " << ms.count(5) << nl; // Output: 3

    // ERASE - ⚠️ Be careful!
    // ms.erase(5);  // Removes ALL occurrences of 5!

    // To remove only ONE occurrence:
    auto it = ms.find(5);
    if (it != ms.end()) {
        ms.erase(it);  // Removes only ONE 5
    }

    cout << "After removing one 5: ";
    for (int x : ms) cout << x << " ";
    cout << nl;

    // EQUAL_RANGE - Get range of duplicates
    auto [first, last] = ms.equal_range(5);
    cout << "All 5s: ";
    for (auto iter = first; iter != last; iter++) {
        cout << *iter << " ";
    }
    cout << nl;

    cout << nl;
}

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 1.6: MULTIMAP - Multiple Values per Key, Sorted
// ══════════════════════════════════════════════════════════════════════════════
void demo_multimap() {
    cout << "═══ MULTIMAP DEMO ═══" << nl;
    multimap<string, int> mmp;

    // INSERT - O(log n)
    mmp.insert({"apple", 5});
    mmp.insert({"apple", 10});  // Same key, different value - Allowed!
    mmp.insert({"apple", 15});
    mmp.insert({"banana", 20});

    // OUTPUT: All entries
    cout << "Multimap contents:" << nl;
    for (auto &[key, val] : mmp) {
        cout << "  " << key << " → " << val << nl;
    }

    // COUNT - Number of entries with key
    cout << "Count of 'apple': " << mmp.count("apple") << nl; // Output: 3

    // FIND - Returns first occurrence
    auto it = mmp.find("apple");
    if (it != mmp.end()) {
        cout << "First apple: " << it->second << nl;
    }

    // EQUAL_RANGE - Get all values for a key
    auto [first, last] = mmp.equal_range("apple");
    cout << "All apple values: ";
    for (auto iter = first; iter != last; iter++) {
        cout << iter->second << " ";
    }
    cout << nl;

    cout << nl;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║              LEVEL 2: FREQUENCY COUNTING (ALL TYPES) 🔥🔥🔥                  ║
╚══════════════════════════════════════════════════════════════════════════════╝

This is the MOST IMPORTANT skill in CP/DSA!
*/

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 2.1: INTEGER FREQUENCY COUNTING
// ══════════════════════════════════════════════════════════════════════════════

// METHOD 1: Using unordered_map (MOST VERSATILE - Use this by default)
void freq_count_map() {
    cout << "═══ FREQUENCY COUNT (UNORDERED_MAP) ═══" << nl;
    vector<int> arr = {1, 2, 3, 2, 1, 3, 3, 4, 1};

    unordered_map<int, int> freq;

    // Count frequency
    for (int x : arr) {
        freq[x]++;  // If key doesn't exist, it's created with 0, then incremented
    }

    // Print frequencies
    cout << "Frequencies:" << nl;
    for (auto &[num, count] : freq) {
        cout << "  " << num << " appears " << count << " times" << nl;
    }

    // Find element with max frequency
    int maxFreq = 0, maxElement = 0;
    for (auto &[num, count] : freq) {
        if (count > maxFreq) {
            maxFreq = count;
            maxElement = num;
        }
    }
    cout << "Most frequent: " << maxElement << " (" << maxFreq << " times)" << nl;

    // Check if element exists
    if (freq.count(5) == 0) {
        cout << "5 is not in the array" << nl;
    }

    cout << nl;
}

// METHOD 2: Using vector (FASTEST - When range is known and small)
void freq_count_vector() {
    cout << "═══ FREQUENCY COUNT (VECTOR) ═══" << nl;
    vector<int> arr = {1, 2, 3, 2, 1, 3, 3, 4, 1};

    // ⚠️ Only works when:
    // 1. All elements are non-negative (or you shift them)
    // 2. Range is known and small (e.g., 0 to 10^6)

    int maxVal = *max_element(all(arr));
    vector<int> freq(maxVal + 1, 0);

    // Count frequency - O(n)
    for (int x : arr) {
        freq[x]++;
    }

    // Print frequencies
    cout << "Frequencies:" << nl;
    for (int i = 0; i <= maxVal; i++) {
        if (freq[i] > 0) {
            cout << "  " << i << " appears " << freq[i] << " times" << nl;
        }
    }

    cout << nl;
}

// METHOD 3: Using map (ORDERED - When you need sorted output)
void freq_count_ordered_map() {
    cout << "═══ FREQUENCY COUNT (ORDERED MAP) ═══" << nl;
    vector<int> arr = {5, 2, 8, 2, 1, 8, 8, 4, 1};

    map<int, int> freq;  // Will be sorted by keys

    for (int x : arr) {
        freq[x]++;
    }

    // Output is automatically sorted by value!
    cout << "Frequencies (sorted by value):" << nl;
    for (auto &[num, count] : freq) {
        cout << "  " << num << " appears " << count << " times" << nl;
    }

    cout << nl;
}

/*
┌───────────────────────────────────────────────────────────────────────────────┐
│ 🎯 VECTOR vs UNORDERED_MAP - WHEN TO USE WHAT?                               │
├───────────────────────────────────────────────────────────────────────────────┤
│                                                                               │
│   USE VECTOR when:                                                           │
│   ├── Values are non-negative integers (or can be shifted)                  │
│   ├── Range is SMALL (≤ 10^6 or 10^7)                                       │
│   ├── You need FASTEST possible access                                       │
│   └── Memory is not a concern                                                │
│                                                                               │
│   USE UNORDERED_MAP when:                                                    │
│   ├── Values can be negative                                                 │
│   ├── Range is LARGE or UNKNOWN (10^9, 10^18)                               │
│   ├── Values are sparse (only few unique values in large range)             │
│   ├── Keys are strings, pairs, or custom types                              │
│   └── You need flexibility                                                   │
│                                                                               │
│   USE MAP when:                                                              │
│   ├── You need output in SORTED order                                        │
│   ├── You need lower_bound/upper_bound operations                           │
│   └── O(log n) is acceptable                                                 │
│                                                                               │
│   COMPLEXITY:                                                                 │
│   ├── Vector: O(1) access, O(maxVal) space                                  │
│   ├── Unordered_map: O(1) average, O(n) worst case, O(unique) space         │
│   └── Map: O(log n) access, O(unique) space                                 │
│                                                                               │
└───────────────────────────────────────────────────────────────────────────────┘
*/

// ══════════════════════════════════════════════════════════════════════════════
// LEVEL 2.2: STRING FREQUENCY COUNTING
// ══════════════════════════════════════════════════════════════════════════════
void freq_count_strings() {
    cout << "═══ STRING FREQUENCY COUNT ═══" << nl;
    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};

    unordered_map<string, int> freq;

    for (const string& word : words) {
        freq[word]++;
    }

    cout << "Word frequencies:" << nl;
    for (auto &[word, count] : freq) {
        cout << "  \"" << word << "\" appears " << count << " times" << nl;
    }

    cout << nl;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║         LEVEL 3: CHARACTER FREQUENCY (26 LOWERCASE OPTIMIZATION) ⚡           ║
╚══════════════════════════════════════════════════════════════════════════════╝

When dealing with ONLY lowercase letters (a-z), we can use a vector of size 26
for MAXIMUM EFFICIENCY. This is VERY COMMON in CP!
*/

// METHOD 1: Vector of size 26 (MOST EFFICIENT for lowercase)
void char_freq_vector26() {
    cout << "═══ CHARACTER FREQUENCY (26 LOWERCASE) ═══" << nl;
    string s = "programming";

    // Vector of size 26 for 'a' to 'z'
    vector<int> freq(26, 0);

    // Count frequency
    // 'a' - 'a' = 0, 'b' - 'a' = 1, ..., 'z' - 'a' = 25
    for (char c : s) {
        freq[c - 'a']++;
    }

    // Print frequencies
    cout << "Character frequencies in \"" << s << "\":" << nl;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            char c = 'a' + i;  // Convert back to character
            cout << "  '" << c << "' appears " << freq[i] << " times" << nl;
        }
    }

    // Common operations
    cout << "Frequency of 'r': " << freq['r' - 'a'] << nl;
    cout << "Frequency of 'g': " << freq['g' - 'a'] << nl;

    cout << nl;
}

// METHOD 2: Array of size 26 (Slightly faster than vector)
void char_freq_array26() {
    cout << "═══ CHARACTER FREQUENCY (ARRAY[26]) ═══" << nl;
    string s = "competitive";

    int freq[26] = {0};  // Initialize all to 0

    for (char c : s) {
        freq[c - 'a']++;
    }

    cout << "Frequencies:" << nl;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << "  '" << (char)('a' + i) << "': " << freq[i] << nl;
        }
    }

    cout << nl;
}

// METHOD 3: For both uppercase and lowercase (52 characters)
void char_freq_52() {
    cout << "═══ CHARACTER FREQUENCY (MIXED CASE) ═══" << nl;
    string s = "HelloWorld";

    // Method A: Use 52-size vector
    // 0-25: lowercase, 26-51: uppercase
    vector<int> freq(52, 0);

    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
        } else if (c >= 'A' && c <= 'Z') {
            freq[c - 'A' + 26]++;
        }
    }

    // Method B: Use unordered_map (simpler)
    unordered_map<char, int> freqMap;
    for (char c : s) {
        freqMap[c]++;
    }

    cout << "Using map:" << nl;
    for (auto &[c, count] : freqMap) {
        cout << "  '" << c << "': " << count << nl;
    }

    cout << nl;
}

// METHOD 4: For all ASCII characters (256 or 128)
void char_freq_ascii() {
    cout << "═══ CHARACTER FREQUENCY (ALL ASCII) ═══" << nl;
    string s = "Hello, World! 123";

    vector<int> freq(256, 0);  // All ASCII characters

    for (char c : s) {
        freq[(unsigned char)c]++;
    }

    cout << "All character frequencies:" << nl;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            if (i >= 32 && i <= 126) {  // Printable characters
                cout << "  '" << (char)i << "' (ASCII " << i << "): " << freq[i] << nl;
            } else {
                cout << "  ASCII " << i << ": " << freq[i] << nl;
            }
        }
    }

    cout << nl;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    LEVEL 4: ANAGRAM CHECKING (CLASSIC PROBLEM)               ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// Check if two strings are anagrams
bool areAnagrams_vector(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;

    vector<int> freq(26, 0);

    // Increment for s1, decrement for s2
    for (int i = 0; i < s1.length(); i++) {
        freq[s1[i] - 'a']++;
        freq[s2[i] - 'a']--;
    }

    // All frequencies should be 0
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) return false;
    }
    return true;
}

bool areAnagrams_map(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;

    unordered_map<char, int> freq;

    for (char c : s1) freq[c]++;
    for (char c : s2) freq[c]--;

    for (auto &[c, count] : freq) {
        if (count != 0) return false;
    }
    return true;
}

void demo_anagram() {
    cout << "═══ ANAGRAM CHECK ═══" << nl;

    cout << "listen vs silent: " << (areAnagrams_vector("listen", "silent") ? "Yes" : "No") << nl;
    cout << "hello vs world: " << (areAnagrams_vector("hello", "world") ? "Yes" : "No") << nl;

    cout << nl;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                 LEVEL 5: FREQUENCY COUNT ON PAIRS & CUSTOM TYPES             ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// Frequency count on pairs
void freq_count_pairs() {
    cout << "═══ FREQUENCY COUNT (PAIRS) ═══" << nl;

    vector<pair<int, int>> points = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};

    map<pair<int, int>, int> freq;  // Use map, not unordered_map (pairs don't have default hash)

    for (auto& p : points) {
        freq[p]++;
    }

    cout << "Point frequencies:" << nl;
    for (auto &[point, count] : freq) {
        cout << "  (" << point.first << ", " << point.second << "): " << count << nl;
    }

    cout << nl;
}

// For unordered_map with pairs, we need custom hash
struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

void freq_count_pairs_unordered() {
    cout << "═══ FREQUENCY COUNT (PAIRS - UNORDERED) ═══" << nl;

    vector<pair<int, int>> points = {{1, 2}, {3, 4}, {1, 2}, {5, 6}};

    unordered_map<pair<int, int>, int, PairHash> freq;

    for (auto& p : points) {
        freq[p]++;
    }

    for (auto &[point, count] : freq) {
        cout << "  (" << point.first << ", " << point.second << "): " << count << nl;
    }

    cout << nl;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                     LEVEL 6: ADVANCED PATTERNS FOR CP 🏆                      ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// PATTERN 1: Two Sum Problem (Classic!)
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // value -> index

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};
        }

        seen[nums[i]] = i;
    }

    return {-1, -1};
}

// PATTERN 2: Subarray Sum Equals K
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;  // Empty prefix has sum 0

    int count = 0, prefixSum = 0;

    for (int num : nums) {
        prefixSum += num;

        // If (prefixSum - k) exists, we found subarrays with sum k
        if (prefixCount.count(prefixSum - k)) {
            count += prefixCount[prefixSum - k];
        }

        prefixCount[prefixSum]++;
    }

    return count;
}

// PATTERN 3: Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastSeen;  // char -> last index
    int maxLen = 0, start = 0;

    for (int end = 0; end < s.length(); end++) {
        char c = s[end];

        if (lastSeen.count(c) && lastSeen[c] >= start) {
            start = lastSeen[c] + 1;  // Move start past the duplicate
        }

        lastSeen[c] = end;
        maxLen = max(maxLen, end - start + 1);
    }

    return maxLen;
}

// PATTERN 4: Group Anagrams
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());  // Sorted string as key
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto &[key, group] : groups) {
        result.push_back(group);
    }

    return result;
}

// PATTERN 5: First Unique Character in String
int firstUniqChar(string s) {
    vector<int> freq(26, 0);

    for (char c : s) {
        freq[c - 'a']++;
    }

    for (int i = 0; i < s.length(); i++) {
        if (freq[s[i] - 'a'] == 1) {
            return i;
        }
    }

    return -1;
}

// PATTERN 6: Contains Duplicate Within K Distance
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> lastIndex;

    for (int i = 0; i < nums.size(); i++) {
        if (lastIndex.count(nums[i]) && i - lastIndex[nums[i]] <= k) {
            return true;
        }
        lastIndex[nums[i]] = i;
    }

    return false;
}

// PATTERN 7: Find All Duplicates
vector<int> findDuplicates(vector<int>& nums) {
    unordered_map<int, int> freq;
    vector<int> result;

    for (int x : nums) {
        freq[x]++;
    }

    for (auto &[num, count] : freq) {
        if (count > 1) {
            result.push_back(num);
        }
    }

    return result;
}

// PATTERN 8: Majority Element (appears > n/2 times)
int majorityElement(vector<int>& nums) {
    unordered_map<int, int> freq;
    int n = nums.size();

    for (int x : nums) {
        freq[x]++;
        if (freq[x] > n / 2) {
            return x;
        }
    }

    return -1;
}

// PATTERN 9: Top K Frequent Elements
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    // Use bucket sort approach
    int n = nums.size();
    vector<vector<int>> buckets(n + 1);

    for (auto &[num, count] : freq) {
        buckets[count].push_back(num);
    }

    vector<int> result;
    for (int i = n; i >= 0 && result.size() < k; i--) {
        for (int num : buckets[i]) {
            result.push_back(num);
            if (result.size() == k) break;
        }
    }

    return result;
}

// PATTERN 10: Count Distinct Elements in Window
vector<int> countDistinct(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        freq[nums[i]]++;

        // Remove element leaving the window
        if (i >= k) {
            int leaving = nums[i - k];
            freq[leaving]--;
            if (freq[leaving] == 0) {
                freq.erase(leaving);
            }
        }

        // Add count after window is complete
        if (i >= k - 1) {
            result.push_back(freq.size());
        }
    }

    return result;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                        LEVEL 7: CODEFORCES TRICKS 🎯                          ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// TRICK 1: Custom hash for unordered_map (prevent TLE from anti-hash attacks)
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

void demo_safe_hash() {
    // Use this in Codeforces to avoid TLE!
    unordered_map<long long, int, SafeHash> safe_mp;
    safe_mp[1000000007] = 42;
}

// TRICK 2: Coordinate Compression
vector<int> coordinateCompress(vector<int>& arr) {
    vector<int> sorted_unique = arr;
    sort(all(sorted_unique));
    sorted_unique.erase(unique(all(sorted_unique)), sorted_unique.end());

    unordered_map<int, int> compress;
    for (int i = 0; i < sorted_unique.size(); i++) {
        compress[sorted_unique[i]] = i;
    }

    vector<int> result;
    for (int x : arr) {
        result.push_back(compress[x]);
    }

    return result;
}

// TRICK 3: Count inversions using map
i64 countInversions(vector<int>& arr) {
    map<int, int> freq;  // Use ordered map for range queries
    i64 inversions = 0;

    for (int i = arr.size() - 1; i >= 0; i--) {
        // Count elements smaller than arr[i] to the right
        for (auto it = freq.begin(); it != freq.end() && it->first < arr[i]; it++) {
            inversions += it->second;
        }
        freq[arr[i]]++;
    }

    return inversions;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                    LEVEL 8: COMPLETE PROBLEMS DEMONSTRATION                   ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

// Problem: Count pairs with given sum
int countPairsWithSum(vector<int>& arr, int target) {
    unordered_map<int, int> freq;
    int count = 0;

    for (int x : arr) {
        int complement = target - x;
        if (freq.count(complement)) {
            count += freq[complement];
        }
        freq[x]++;
    }

    return count;
}

// Problem: Find if array has two elements with difference K
bool hasPairWithDiff(vector<int>& arr, int k) {
    unordered_set<int> seen;

    for (int x : arr) {
        if (seen.count(x - k) || seen.count(x + k)) {
            return true;
        }
        seen.insert(x);
    }

    return false;
}

// Problem: Longest Consecutive Sequence
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(all(nums));
    int maxLen = 0;

    for (int num : numSet) {
        // Only start counting if num is the start of a sequence
        if (!numSet.count(num - 1)) {
            int currentNum = num;
            int currentLen = 1;

            while (numSet.count(currentNum + 1)) {
                currentNum++;
                currentLen++;
            }

            maxLen = max(maxLen, currentLen);
        }
    }

    return maxLen;
}

// Problem: Check if two arrays are equal (same elements, same frequency)
bool areArraysEqual(vector<int>& a, vector<int>& b) {
    if (a.size() != b.size()) return false;

    unordered_map<int, int> freq;

    for (int x : a) freq[x]++;
    for (int x : b) freq[x]--;

    for (auto &[num, count] : freq) {
        if (count != 0) return false;
    }

    return true;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                         MAIN FUNCTION - RUN ALL DEMOS                         ║
╚══════════════════════════════════════════════════════════════════════════════╝
*/

void runAllDemos() {
    cout << "╔══════════════════════════════════════════════════════════════╗" << nl;
    cout << "║           HASHING MASTERY: ALL DEMOS                        ║" << nl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << nl;
    cout << nl;

    // Level 1: Data Structure Demos
    demo_set();
    demo_unordered_set();
    demo_map();
    demo_unordered_map();
    demo_multiset();
    demo_multimap();

    // Level 2: Frequency Counting
    freq_count_map();
    freq_count_vector();
    freq_count_ordered_map();
    freq_count_strings();

    // Level 3: Character Frequency
    char_freq_vector26();
    char_freq_array26();
    char_freq_52();
    char_freq_ascii();

    // Level 4: Anagram
    demo_anagram();

    // Level 5: Pairs
    freq_count_pairs();
    freq_count_pairs_unordered();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    runAllDemos();

    return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║               LEVEL 9: PRACTICE PROBLEMS BY PLATFORM 📚                       ║
╚══════════════════════════════════════════════════════════════════════════════╝

══════════════════════════════════════════════════════════════════════════════
🔥 LEETCODE PROBLEMS (Beginner to Advanced)
══════════════════════════════════════════════════════════════════════════════

📗 EASY:
├── 1. Two Sum                           [Hash Map]
├── 217. Contains Duplicate              [Hash Set]
├── 219. Contains Duplicate II           [Hash Map + Sliding Window]
├── 242. Valid Anagram                   [Character Frequency]
├── 349. Intersection of Two Arrays      [Hash Set]
├── 350. Intersection of Two Arrays II   [Hash Map Frequency]
├── 383. Ransom Note                     [Character Frequency]
├── 387. First Unique Character          [Frequency Array]
├── 389. Find the Difference             [Character Frequency]
├── 409. Longest Palindrome              [Character Frequency]
├── 448. Find All Numbers Disappeared    [Index Hashing]
├── 500. Keyboard Row                    [Hash Set]
├── 560. Subarray Sum Equals K           [Prefix Sum + Hash Map] ⭐
├── 575. Distribute Candies              [Hash Set]
├── 594. Longest Harmonious Subsequence  [Hash Map]
├── 645. Set Mismatch                    [Frequency]
├── 697. Degree of an Array              [Multiple Hash Maps]
├── 705. Design HashSet                  [Implementation]
├── 706. Design HashMap                  [Implementation]
├── 771. Jewels and Stones               [Hash Set]
├── 804. Unique Morse Code Words         [Hash Set]
├── 819. Most Common Word                [Hash Map + String Processing]
├── 859. Buddy Strings                   [Character Frequency]
├── 884. Uncommon Words from Two Sentences
├── 961. N-Repeated Element              [Hash Map]
├── 1002. Find Common Characters         [Frequency Array]
├── 1207. Unique Number of Occurrences   [Hash Map + Hash Set]
├── 1496. Path Crossing                  [Hash Set of Pairs]
└── 2032. Two Out of Three               [Multiple Hash Sets]

📘 MEDIUM:
├── 3. Longest Substring Without Repeating Characters ⭐⭐
├── 36. Valid Sudoku                     [Hash Set per row/col/box]
├── 49. Group Anagrams                   ⭐⭐
├── 73. Set Matrix Zeroes                [Hash Sets]
├── 128. Longest Consecutive Sequence    ⭐⭐⭐
├── 138. Copy List with Random Pointer   [Hash Map]
├── 146. LRU Cache                       [Hash Map + Doubly Linked List] ⭐⭐⭐
├── 187. Repeated DNA Sequences          [Rolling Hash / Hash Set]
├── 229. Majority Element II             [Hash Map]
├── 244. Shortest Word Distance II       [Hash Map]
├── 274. H-Index                         [Frequency/Bucket Sort]
├── 290. Word Pattern                    [Bijection with Hash Maps]
├── 299. Bulls and Cows                  [Frequency Array]
├── 347. Top K Frequent Elements         ⭐⭐⭐
├── 380. Insert Delete GetRandom O(1)    [Hash Map + Vector] ⭐⭐
├── 438. Find All Anagrams in a String   [Sliding Window + Freq Array] ⭐⭐
├── 451. Sort Characters By Frequency    [Hash Map + Bucket Sort]
├── 454. 4Sum II                         [Hash Map]
├── 523. Continuous Subarray Sum         [Prefix Sum + Hash Map]
├── 525. Contiguous Array                [Prefix Sum + Hash Map] ⭐⭐
├── 532. K-diff Pairs in an Array        [Hash Map]
├── 554. Brick Wall                      [Hash Map]
├── 567. Permutation in String           [Sliding Window + Frequency]
├── 609. Find Duplicate File in System   [Hash Map]
├── 621. Task Scheduler                  [Frequency + Greedy]
├── 652. Find Duplicate Subtrees         [Hash Map + Serialization]
├── 718. Maximum Length of Repeated Subarray [Rolling Hash / DP]
├── 763. Partition Labels               [Hash Map]
├── 767. Reorganize String              [Frequency + Heap]
├── 791. Custom Sort String             [Hash Map]
├── 811. Subdomain Visit Count          [Hash Map]
├── 838. Push Dominoes                  [Hash Map]
├── 930. Binary Subarrays With Sum      [Prefix Sum + Hash Map]
├── 974. Subarray Sums Divisible by K   [Prefix Sum + Hash Map] ⭐⭐
├── 1010. Pairs of Songs With Total Durations [Hash Map + Modulo]
├── 1041. Robot Bounded In Circle       [Math + Set]
├── 1048. Longest String Chain          [Hash Map + DP]
├── 1074. Number of Submatrices That Sum to Target ⭐⭐⭐
├── 1146. Snapshot Array                [Hash Map]
├── 1244. Design A Leaderboard          [Hash Map + Multiset]
├── 1481. Least Number of Unique Integers [Frequency + Sorting]
├── 1590. Make Sum Divisible by P       [Prefix Sum + Hash Map]
├── 2007. Find Original Array From Doubled [Hash Map + Sorting]
├── 2225. Find Players With Zero or One Losses [Hash Set]
└── 2364. Count Number of Bad Pairs     [Hash Map + Math]

📕 HARD:
├── 30. Substring with Concatenation of All Words [Hash Map + Sliding Window]
├── 37. Sudoku Solver                   [Backtracking + Hash Sets]
├── 76. Minimum Window Substring        [Hash Map + Sliding Window] ⭐⭐⭐
├── 127. Word Ladder                    [BFS + Hash Set]
├── 149. Max Points on a Line           [Hash Map + GCD]
├── 166. Fraction to Recurring Decimal  [Hash Map]
├── 202. Happy Number                   [Hash Set + Cycle Detection]
├── 336. Palindrome Pairs               [Hash Map + String Processing]
├── 381. Insert Delete GetRandom O(1) - Duplicates [Hash Map + Set]
├── 460. LFU Cache                      [Multiple Hash Maps] ⭐⭐⭐
├── 480. Sliding Window Median          [Multiset]
├── 532. K-diff Pairs in an Array       [Hash Map]
├── 710. Random Pick with Blacklist     [Hash Map]
├── 726. Number of Atoms                [Hash Map + Parsing]
├── 895. Maximum Frequency Stack        [Hash Map + Stack] ⭐⭐⭐
├── 992. Subarrays with K Different Integers [Sliding Window + Hash Map]
├── 1044. Longest Duplicate Substring   [Binary Search + Rolling Hash] ⭐⭐⭐
├── 1153. String Transforms Into Another String [Hash Map + Graph]
└── 2034. Stock Price Fluctuation       [Hash Map + Multiset]

══════════════════════════════════════════════════════════════════════════════
🔥 CODEFORCES PROBLEMS
══════════════════════════════════════════════════════════════════════════════

📗 BEGINNER (800-1200):
├── 4A. Watermelon                      [Basic Logic]
├── 112A. Petya and Strings             [Character Comparison]
├── 236A. Boy or Girl                   [Set - Distinct Count]
├── 263A. Beautiful Matrix              [Basic Implementation]
├── 282A. Bit++                         [String Matching]
├── 339A. Helpful Maths                 [Sorting/Frequency]
├── 469A. I Wanna Be the Guy            [Set Union]
├── 520A. Pangram                       [Set - 26 Characters]
├── 546A. Soldier and Bananas           [Basic Math]
├── 702A. Maximum Increase              [Implementation]
├── 732A. Buy a Shovel                  [Modulo/Basic]
├── 785A. Anton and Polyhedrons         [Map]
├── 791A. Bear and Big Brother          [Simulation]
├── 900A. Find Extra One                [XOR/Hashing]
├── 996A. Hit the Lottery               [Greedy]
├── 1154A. Restoring Three Numbers      [Basic Logic]
├── 1272A. Three Friends                [Implementation]
└── 1399A. Remove Smallest              [Frequency/Sorting]

📘 INTERMEDIATE (1200-1600):
├── 4C. Registration System             [Map - String Frequency] ⭐
├── 25A. IQ test                        [Frequency - Odd/Even]
├── 69A. Young Physicist                [Sum Check]
├── 158B. Taxi                          [Frequency Array]
├── 230B. T-primes                      [Set + Sieve]
├── 276A. Lunch Rush                    [Map]
├── 313B. Ilya and Queries              [Prefix Sum]
├── 381A. Sereja and Dima               [Two Pointers]
├── 405A. Gravity Flip                  [Sorting]
├── 427A. Police Recruits               [Implementation]
├── 478B. Random Teams                  [Math/Combinatorics]
├── 546B. Soldier and Badges            [Set + Modification] ⭐
├── 579A. Raising Bacteria              [Bit Manipulation]
├── 586B. Laurenty and Shop             [Implementation]
├── 617A. Elephant                      [Greedy]
├── 702B. Powers of Two                 [Map - Two Sum Variant] ⭐⭐
├── 723B. Text Document Analysis        [Stack/String]
├── 742A. Arpa's hard exam              [Pattern/Cycle]
├── 745A. Hongcow Learns the Cyclic Shift [Set of Strings]
├── 766A. Mahmoud and Longest Uncommon Subsequence [Logic]
├── 797A. K-Factorization               [Factor Finding]
├── 835A. Key races                     [Math]
├── 862B. Mahmoud and Ehab and the bipartiteness [Bipartite Graph]
├── 939A. Love Triangle                 [Map + Cycle Detection]
├── 1003B. Binary String Constructing   [Construction]
├── 1037A. Packets                      [Greedy]
├── 1077B. Disturbed People             [Greedy]
├── 1092B. Teams Forming                [Frequency + Sorting]
├── 1294C. Product of Three Numbers     [Factorization]
├── 1296C. Yet Another Walking Robot    [Map + Prefix] ⭐⭐
├── 1328C. Ternary XOR                  [Greedy]
├── 1360D. Buying Shovels               [GCD/Divisibility]
├── 1399C. Boats Competition            [Map + Two Pointers] ⭐⭐
├── 1443B. Saving the City              [DP + Frequency]
├── 1472D. Even-Odd Game                [Sorting + Game Theory]
├── 1512D. Corrupted Array              [Multiset + Sum] ⭐⭐
├── 1520D. Same Differences             [Map + Transform] ⭐⭐⭐
├── 1538C. Number of Pairs              [Binary Search + Map] ⭐⭐
├── 1539B. Love Song                    [Prefix Sum + Frequency]
├── 1551B1. Wonderful Coloring - 1      [Frequency]
├── 1551B2. Wonderful Coloring - 2      [Frequency + Greedy]
├── 1560C. Infinity Table               [Math/Pattern]
├── 1579C. Ticks                        [Implementation]
├── 1619D. New Year's Problem           [Binary Search + Implementation]
├── 1669E. 2-Letter Strings             [Map of Pairs] ⭐⭐
├── 1701C. Schedule Management          [Binary Search + Frequency]
├── 1722E. Counting Rectangles          [2D Prefix + Map] ⭐⭐
└── 1729D. Friends and the Restaurant   [Sorting + Two Pointers]

📕 ADVANCED (1600-2000+):
├── 1A. Theatre Square                  [Math]
├── 6A. Triangle                        [Sorting]
├── 32B. Borze                          [String Parsing]
├── 61A. Ultra-Fast Mathematician       [XOR]
├── 160A. Twins                         [Greedy + Sum]
├── 165B. Burning Midnight Oil          [Binary Search]
├── 268B. Buttons                       [Game Theory]
├── 285B. Find Marble                   [Permutation Cycle]
├── 313A. Ilya and Bank Account         [String]
├── 327A. Flipping Game                 [Prefix Sum]
├── 361A. Levko and Table               [Math]
├── 368B. Sereja and Suffixes           [Suffix Array/Set] ⭐
├── 476B. Dreamoon and WiFi             [Combinatorics]
├── 489C. Given Length and Sum of Digits [Greedy + Construction]
├── 501B. Misha and Changing Handles    [Map + DSU] ⭐⭐
├── 515B. Drazil and His Happy Friends  [GCD + Set]
├── 519B. A and B and Compilation Errors [Multiset/XOR] ⭐⭐
├── 577B. Modulo Sum                    [DP + Pigeonhole] ⭐⭐
├── 616C. The Labyrinth                 [BFS + Component Labeling]
├── 652B. z-sort                        [Sorting Pattern]
├── 659A. Round House                   [Modulo]
├── 706C. Hard problem                  [DP + Strings]
├── 714B. Filya and Homework            [Set + Math] ⭐
├── 734C. Anton and Making Potions      [Binary Search + Prefix]
├── 760B. Frodo and pillows             [Binary Search]
├── 782B. The Meeting Place Cannot Be Changed [Binary Search]
├── 797C. Minimal string                [Stack + Greedy]
├── 817C. Really Big Numbers            [Binary Search]
├── 837D. Round Subset                  [DP + Factorization]
├── 863B. Kayaking                      [Sorting + Greedy]
├── 877B. Nikita and string             [DP]
├── 895A. Pizza Separation              [Prefix Sum + Set]
├── 903C. Boxes Packing                 [Binary Search]
├── 913B. Christmas Spruce              [Tree + DFS]
├── 939B. Hamster Farm                  [Divisibility + Max]
├── 978F. Mentors                       [Binary Search + Sorting] ⭐⭐
├── 988C. Equal Sums                    [Map + Array] ⭐⭐⭐
├── 1003C. Intense Heat                 [Prefix Sum]
├── 1015C. Songs Compression            [Sorting + Prefix]
├── 1027C. Minimum Value Rectangle      [Frequency + Sorting] ⭐⭐
├── 1077D. Cutting Out                  [Binary Search + Frequency] ⭐⭐⭐
├── 1095D. Circular Dance               [Graph Construction]
├── 1118D1. Coffee and Coursework (Easy) [Binary Search]
├── 1132D. Stressful Training           [Binary Search + Simulation]
├── 1151C. Problem for Nazar            [Math + Prefix]
├── 1165D. Almost All Divisors          [Number Theory + Map] ⭐⭐
├── 1175B. Catch Overflow!              [Stack + Parsing]
├── 1196D2. RGB Substring (hard)        [Prefix Sum + Sliding Window]
├── 1209B. Koala and Lights             [Simulation + LCM]
├── 1234D. Distinct Characters Queries  [Segment Tree + Set]
├── 1253C. Sweets Eating                [Sorting + Prefix]
├── 1255C. League of Leesins            [Graph + Map] ⭐⭐
├── 1263C. Everyone is a Winner!        [Math + Set]
├── 1283D. Christmas Trees              [Sorting + Greedy]
├── 1294D. MEX maximizing               [Frequency + MEX] ⭐⭐⭐
├── 1326D2. Prefix-Suffix Palindrome (Hard) [String + Hashing]
├── 1352E. Special Elements             [Prefix Sum + Map] ⭐⭐
├── 1360F. Spy-string                   [Brute Force + Hamming Distance]
├── 1374D. Zero Remainder Array         [Map + Modulo] ⭐⭐⭐
├── 1385D. a]and b[                     [Implementation]
├── 1400D. Zigzags                      [Map + Combinatorics] ⭐⭐⭐
├── 1418C. Mortal Kombat Tower          [DP]
├── 1433E. Two Round Dances             [Combinatorics]
├── 1462E1. Close Tuples (easy)         [Binary Search + Combinatorics]
├── 1462E2. Close Tuples (hard)         [Binary Search + Combinatorics]
├── 1475D. Cleaning the Phone           [Prefix + Two Pointers]
├── 1485B. Replace and Keep Sorted      [Prefix + Math]
├── 1500A. Going Home                   [Map + Pairs] ⭐⭐⭐
├── 1525C. Robot Collisions             [Map + Stack] ⭐⭐⭐
├── 1535C. Unstable String              [DP/Sliding Window]
├── 1553D. Backspace                    [Binary Search + Greedy]
├── 1559D1. Mocha and Diana (Easy)      [DSU]
├── 1560E. Polycarp and String Transformation [String + Frequency] ⭐⭐⭐
├── 1593D1. All Are Same (Easy)         [GCD + Set]
├── 1620D. Exact Change                 [DP/Brute Force]
├── 1669F. Eating Candies               [Prefix + Two Pointers]
├── 1679B. Stone Age Problem            [Lazy Update + Map] ⭐⭐
├── 1700C. Helping the Nature           [Difference Array]
├── 1722D. Line                         [Sorting/Prefix]
├── 1732C1. Sheikh (Easy)               [Prefix + Sparse Table]
├── 1741D. Masha and a Beautiful Tree   [Tree + Merging]
├── 1760E. Binary Inversions            [Prefix + Suffix Count]
├── 1790D. Matryoshkas                  [Map + Greedy] ⭐⭐⭐
├── 1800E1. Unforgivable Curse (easy)   [Graph + BFS]
├── 1829E. The Lakes                    [BFS/DFS]
└── 1838C. No Prime Differences         [Number Theory]

══════════════════════════════════════════════════════════════════════════════
🔥 CODECHEF PROBLEMS
══════════════════════════════════════════════════════════════════════════════

📗 BEGINNER:
├── ATM                                 [Basic Implementation]
├── FLOW001 - Add Two Numbers           [Basic]
├── FLOW002 - First and Last Digit Sum  [Basic]
├── LAPIN - Lapindrome                  [Frequency Matching] ⭐
├── VOTERS - Election                   [Set Intersection]
├── FCTRL - Factorial                   [Math]
├── TURB - Turbo Sort                   [Sorting]
├── INTEST - Enormous Input Test        [Fast I/O]
├── SUMTRIAN - Sums in a Triangle       [DP]
├── MARCHA1 - Shopping                  [Subset Sum/DP]
├── CHOPRT - Chef and Operators         [String Processing]
└── SNTEMPLE - Temple                   [Stack]

📘 INTERMEDIATE:
├── ANAGRAM - Chef and Anagrams         [Frequency] ⭐⭐
├── CHEFSTR - Chef and Strings          [Frequency]
├── PERMPAL - Permutation Palindrome    [Frequency] ⭐
├── COUPON - Coupons                    [Set/Map]
├── MFREQ - Most Frequent Element       [Map Frequency] ⭐
├── SUBSEQ - Count Subsequences         [DP + Map]
├── PPSUM - Power Pair Sum              [Map] ⭐⭐
├── CHEFPRES - Chef and President       [Graph + Map]
├── SSTRING - String Operations         [Map]
├── LECANDY - Little Elephant and Candies [Math]
├── TIDRICE - Distribute the Rice       [Greedy]
├── CHFQUEUE - Chef and Queue           [Simulation + Map]
├── CHFPLN - Chef and Planes            [Set]
├── NUMCOMP - Number of Components      [DSU + Map]
└── PAIRCLST - Closest Pair             [Sorting + Two Pointers]

📕 ADVANCED:
├── SUBINC - Count Subarrays            [Two Pointers]
├── MAXDIFF - Maximum Weight Difference [Sorting]
├── SPREAD - Spreading Rumors           [BFS + Map]
├── CHEFZERO - Chef and Zero            [Frequency + Prefix Sum]
├── CARRAY - Circular Array             [Sliding Window + Map]
├── PSHTTR - Psychic Traps              [Hashing]
├── FLIPCOIN - Flip Coins               [Segment Tree]
├── PALIN - Next Palindrome             [String]
├── PRIME1 - Prime Generator            [Segmented Sieve]
├── DIVMAC - Divisor Machinery          [Number Theory + Map]
├── SNAKEEAT - Snake Eating             [Binary Search]
└── GERALD03 - Watch Repair             [Advanced DS]

══════════════════════════════════════════════════════════════════════════════
🔥 GEEKSFORGEEKS PROBLEMS
══════════════════════════════════════════════════════════════════════════════

📗 EASY:
├── Check if two arrays are equal       [Frequency Map] ⭐
├── Count pairs with given sum          [Hash Map] ⭐⭐
├── First element occurring k times     [Frequency Map]
├── Largest subarray with 0 sum         [Prefix Sum + Map] ⭐⭐
├── Non-Repeating Character             [Frequency]
├── Array Duplicates                    [Set/Map]
├── Subarray with given sum             [Sliding Window/Map]
├── Missing number in array             [XOR/Sum]
├── Union of two arrays                 [Set]
├── Intersection of two arrays          [Set/Map]
├── Anagram                             [Frequency] ⭐
├── Check if frequencies can be equal   [Frequency of Frequencies]
├── First non-repeating character       [Queue + Map]
├── Smallest subarray with sum greater than x [Sliding Window]
├── Zero Sum Subarrays                  [Prefix Sum + Map]
├── Count distinct elements in every window [Sliding Window + Map] ⭐⭐
├── Pair with given sum in sorted array [Two Pointers]
├── Relative Sorting                    [Map + Custom Sort]
├── Number of subarrays with maximum values [Monotonic Stack]
├── Elements with left side smaller and right side greater [Prefix/Suffix]
└── Longest Subarray with Sum K         [Prefix Sum + Map] ⭐⭐

📘 MEDIUM:
├── Count subarrays with equal 0s and 1s [Prefix Sum + Map] ⭐⭐
├── Longest consecutive subsequence     [Set] ⭐⭐⭐
├── Find all four sum numbers           [Two Pointers + Hash]
├── Count pairs with given difference   [Hash Set]
├── Longest subarray with sum divisible by K [Prefix Sum + Map] ⭐⭐
├── Subarrays with K different integers [Sliding Window + Map] ⭐⭐⭐
├── Smallest window containing all characters [Sliding Window + Map] ⭐⭐
├── Largest subarray of 0s and 1s       [Prefix + Map]
├── Number of distinct subsequences     [DP + Map]
├── Group Anagrams                      [Map of Sorted Strings] ⭐⭐
├── Minimum indexed character           [Map]
├── Print anagrams together             [Map + Sorting]
├── Longest substring without repeating characters [Sliding Window] ⭐⭐
├── Subarrays with equal 1s and 0s      [Prefix Sum + Map]
├── Count subarrays with given XOR      [Prefix XOR + Map] ⭐⭐
├── Maximum sum of 3 non-overlapping subarrays [DP + Prefix]
├── Find itinerary from tickets         [Map + DFS]
├── Clone a linked list with random pointer [Map]
└── LRU Cache                           [Map + DLL] ⭐⭐⭐

📕 HARD:
├── Minimum Window Substring            [Sliding Window + Map] ⭐⭐⭐
├── Count of Subarrays with given XOR   [Prefix XOR + Map]
├── Distinct subsequences               [DP]
├── Alien Dictionary                    [Topological Sort + Map]
├── Word Ladder                         [BFS + Set]
├── Palindrome Pairs                    [Trie/Map]
├── Count subarrays having sum less than K [Sliding Window]
└── Maximum points on a line            [GCD + Map]

══════════════════════════════════════════════════════════════════════════════
🎯 TOPIC-WISE PRACTICE ROADMAP (Recommended Order)
══════════════════════════════════════════════════════════════════════════════

WEEK 1: FREQUENCY BASICS
├── Day 1-2: LC 1, 217, 242, 383, 387
├── Day 3-4: CF 4C, 520A, 236A
├── Day 5-7: GFG Basic frequency problems

WEEK 2: INTERMEDIATE FREQUENCY + SET
├── Day 1-2: LC 349, 350, 219, 409
├── Day 3-4: CF 546B, 702B, 1520D
├── Day 5-7: LC 128 (Longest Consecutive), GFG Medium

WEEK 3: PREFIX SUM + HASH MAP
├── Day 1-2: LC 560, 525, 523
├── Day 3-4: CF 1374D, 1294D, 988C
├── Day 5-7: GFG Subarray sum problems

WEEK 4: SLIDING WINDOW + HASH MAP
├── Day 1-2: LC 3, 438, 567
├── Day 3-4: LC 76 (Minimum Window)
├── Day 5-7: CF 1077D, 1296C

WEEK 5: ADVANCED PATTERNS
├── Day 1-2: LC 146 (LRU Cache), 380
├── Day 3-4: LC 347, 895, 460
├── Day 5-7: CF 1400D, 1500A, 1525C

WEEK 6: STRING HASHING
├── Day 1-2: LC 49, 187, 30
├── Day 3-4: CF 1326D2, 1560E
├── Day 5-7: Rolling hash problems

══════════════════════════════════════════════════════════════════════════════
💡 PRO TIPS FOR COMPETITIVE PROGRAMMING
══════════════════════════════════════════════════════════════════════════════

1. ALWAYS use unordered_map with custom hash in Codeforces (anti-hash attacks!)
2. For character frequency, prefer int freq[26] over map (10x faster)
3. For pair keys, use map instead of unordered_map (easier, no custom hash)
4. Remember: mp[key] creates entry with value 0 if key doesn't exist!
5. Use freq[x]++ instead of if-else (cleaner code)
6. For sliding window, always handle both add and remove operations
7. Prefix sum + hash map = powerful combination for subarray problems
8. When stuck, think: "Can I transform this to a frequency problem?"

*/

