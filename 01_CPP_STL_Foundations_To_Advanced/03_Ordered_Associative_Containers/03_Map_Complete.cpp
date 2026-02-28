/*
╔══════════════════════════════════════════════════════════════════════════════╗
║           03 — MAP COMPLETE GUIDE                                          ║
║           From Zero to Grandmaster — Sorted Key-Value Store                ║
║           Author: Sarvan Yaduvanshi                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

TABLE OF CONTENTS:
─────────────────
 1. What is map? (Red-Black Tree of pairs)
 2. [] vs at() vs insert vs emplace
 3. find, count, erase
 4. Structured Binding Iteration (C++17)
 5. Frequency Counting Pattern
 6. map vs unordered_map — When to Use Which
 7. CP Problem: First Non-Repeating Character

MAP INTERNALS:
──────────────
  map<K,V> = balanced BST of (key, value) pairs, SORTED BY KEY.

  map<string, int> scores:
       ("charlie", 92)
        /              \
  ("alice", 95)    ("david", 88)
                   /
             ("bob", 87)

  All operations: O(log n)
  Keys are UNIQUE (use multimap for duplicate keys)

GM TIP: map is your go-to for:
  1. Frequency counting with sorted output
  2. Coordinate compression mapping
  3. Any key→value lookup needing sorted order
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// SECTION 1: INSERTION METHODS
// ═══════════════════════════════════════════════════════════════
/*
 FOUR WAYS TO INSERT:
 ────────────────────
 1. m[key] = value;          → Creates if not exist, overwrites if exist
 2. m.insert({key, value});  → Only inserts if key doesn't exist
 3. m.emplace(key, value);   → Same as insert but constructs in-place
 4. m.insert_or_assign(k,v); → Inserts or overwrites (C++17)

 CRITICAL DIFFERENCE:
   m[key] creates a DEFAULT entry if key doesn't exist!
   This can cause bugs — checking m[key] modifies the map!

 DRY RUN:
   map<string,int> m;
   m["alice"] = 95;          // Creates {"alice": 95}
   m["alice"] = 100;         // OVERWRITES to {"alice": 100}
   m.insert({"alice", 95});  // Does NOTHING (alice exists)
   m["bob"];                 // Creates {"bob": 0} ← DANGER!
*/

void demonstrateInsertion() {
    cout << "═══ MAP INSERTION METHODS ═══\n\n";

    map<string, int> m;

    // Method 1: [] operator
    m["alice"] = 95;
    m["bob"] = 87;
    m["charlie"] = 92;
    cout << "After [] inserts: ";
    for (auto& [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n";

    // [] overwrites!
    m["alice"] = 100;
    cout << "After m[\"alice\"]=100: alice=" << m["alice"] << "\n";

    // Method 2: insert (doesn't overwrite!)
    m.insert({"alice", 50});  // Does nothing — alice already exists
    cout << "After insert(alice,50): alice=" << m["alice"] << " (still 100!)\n";

    // Method 3: emplace
    m.emplace("david", 88);
    cout << "After emplace(david,88): ";
    for (auto& [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n";

    // DANGER: [] creates default entry!
    cout << "\nBefore checking 'eve': size=" << m.size() << "\n";
    int val = m["eve"];  // Creates {"eve": 0}!
    cout << "After m[\"eve\"]: size=" << m.size() << ", eve=" << val << "\n";
    cout << "WARNING: [] created a default entry!\n\n";

    // SAFE way to check existence:
    if (m.find("frank") != m.end()) {
        cout << "frank exists\n";
    } else {
        cout << "frank not found (safe check, no side effect)\n";
    }

    // Or use count:
    if (m.count("eve")) cout << "eve exists (count=1)\n";
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 2: find, count, erase
// ═══════════════════════════════════════════════════════════════

void demonstrateFindErase() {
    cout << "═══ FIND, COUNT, ERASE ═══\n\n";

    map<string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};

    // find returns iterator
    auto it = m.find("c");
    if (it != m.end()) {
        cout << "Found: " << it->first << " → " << it->second << "\n";
    }

    // count (0 or 1 for map)
    cout << "count(\"c\") = " << m.count("c") << "\n";
    cout << "count(\"z\") = " << m.count("z") << "\n";

    // erase by key
    m.erase("c");
    cout << "After erase(\"c\"): ";
    for (auto& [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n";

    // erase by iterator
    m.erase(m.begin());
    cout << "After erase(begin): ";
    for (auto& [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n";

    // erase range
    m = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
    m.erase(m.find("b"), m.find("d"));  // Erases [b, d)
    cout << "After erase [b,d): ";
    for (auto& [k, v] : m) cout << k << ":" << v << " ";
    cout << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 3: STRUCTURED BINDINGS (C++17)
// ═══════════════════════════════════════════════════════════════

void demonstrateStructuredBindings() {
    cout << "═══ STRUCTURED BINDINGS ═══\n\n";

    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};

    // Old way
    cout << "Old way (it->first, it->second):\n";
    for (auto it = scores.begin(); it != scores.end(); ++it) {
        cout << "  " << it->first << " → " << it->second << "\n";
    }

    // C++17 way
    cout << "C++17 way (auto& [key, val]):\n";
    for (auto& [name, score] : scores) {
        cout << "  " << name << " → " << score << "\n";
    }

    // Modify through structured binding
    for (auto& [name, score] : scores) {
        score += 5;  // Curve!
    }
    cout << "After +5 curve:\n";
    for (const auto& [name, score] : scores) {
        cout << "  " << name << " → " << score << "\n";
    }

    // Structured binding with insert result
    auto [it, inserted] = scores.insert({"David", 90});
    cout << "\ninsert David: " << (inserted ? "inserted" : "existed")
         << " → " << it->first << ":" << it->second << "\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 4: FREQUENCY COUNTING PATTERN
// ═══════════════════════════════════════════════════════════════
/*
 THE MOST COMMON MAP PATTERN IN CP:
 ───────────────────────────────────
 Count frequency of each element:
   for (int x : arr) freq[x]++;

 This works because [] creates default 0, then ++ increments.

 DRY RUN:
   arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
   freq[3]++ → freq = {3:1}
   freq[1]++ → freq = {1:1, 3:1}
   freq[4]++ → freq = {1:1, 3:1, 4:1}
   freq[1]++ → freq = {1:2, 3:1, 4:1}
   freq[5]++ → freq = {1:2, 3:1, 4:1, 5:1}
   ...
   Final: {1:2, 2:1, 3:2, 4:1, 5:3, 6:1, 9:1}
*/

void demonstrateFrequencyCounting() {
    cout << "═══ FREQUENCY COUNTING ═══\n\n";

    // Integer frequency
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    map<int, int> freq;
    for (int x : arr) freq[x]++;

    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nFrequencies (sorted by key):\n";
    for (auto& [val, cnt] : freq) {
        cout << "  " << val << " → " << cnt << " times\n";
    }

    // Find most frequent
    auto maxIt = max_element(freq.begin(), freq.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    cout << "Most frequent: " << maxIt->first << " (" << maxIt->second << " times)\n\n";

    // Character frequency
    string s = "competitive programming";
    map<char, int> charFreq;
    for (char c : s) if (c != ' ') charFreq[c]++;

    cout << "\"" << s << "\"\nChar frequencies:\n";
    for (auto& [c, cnt] : charFreq) {
        cout << "  '" << c << "' → " << cnt << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 5: MAP vs UNORDERED_MAP
// ═══════════════════════════════════════════════════════════════
/*
 ┌─────────────────────┬──────────────┬────────────────┐
 │ Feature             │ map          │ unordered_map  │
 ├─────────────────────┼──────────────┼────────────────┤
 │ Internal            │ Red-Black BST│ Hash Table     │
 │ Insert/Find         │ O(log n)     │ O(1) average   │
 │ Worst case          │ O(log n)     │ O(n) !!        │
 │ Order               │ Sorted ✓     │ Unordered      │
 │ lower_bound         │ O(log n) ✓   │ Not available  │
 │ Memory              │ More         │ Less           │
 │ Anti-hack safe      │ Yes ✓        │ No (hackable!) │
 └─────────────────────┴──────────────┴────────────────┘

 GM VERDICT:
 • Use unordered_map for pure lookup (O(1) average)
 • Use map when you need sorted order or lower_bound
 • Use map if you're worried about anti-hash attacks on CF
 • Custom hash makes unordered_map safe (see Chapter 04)
*/

// ═══════════════════════════════════════════════════════════════
// SECTION 6: CP PROBLEM — FIRST NON-REPEATING CHARACTER
// ═══════════════════════════════════════════════════════════════

void firstNonRepeating() {
    cout << "═══ CP PROBLEM: FIRST NON-REPEATING ═══\n\n";

    string s = "aabbccddeeffg";
    map<char, int> freq;
    for (char c : s) freq[c]++;

    cout << "String: \"" << s << "\"\n";
    for (char c : s) {
        if (freq[c] == 1) {
            cout << "First non-repeating: '" << c << "'\n\n";
            return;
        }
    }
    cout << "No non-repeating character found\n\n";
}

// ═══════════════════════════════════════════════════════════════
// SECTION 7: LOWER_BOUND & UPPER_BOUND ON MAP
// ═══════════════════════════════════════════════════════════════

void demonstrateMapBounds() {
    cout << "═══ MAP LOWER/UPPER BOUND ═══\n\n";

    map<int, string> m = {{10, "ten"}, {20, "twenty"}, {30, "thirty"},
                           {40, "forty"}, {50, "fifty"}};

    // lower_bound(25) → first key >= 25 → 30
    auto lb = m.lower_bound(25);
    cout << "lower_bound(25): " << lb->first << " → " << lb->second << "\n";

    // upper_bound(30) → first key > 30 → 40
    auto ub = m.upper_bound(30);
    cout << "upper_bound(30): " << ub->first << " → " << ub->second << "\n";

    // Find predecessor of key 35
    auto it = m.lower_bound(35);
    if (it != m.begin()) {
        --it;
        cout << "Predecessor of 35: " << it->first << "\n";
    }

    // Count keys in range [15, 45]
    auto from = m.lower_bound(15);
    auto to = m.upper_bound(45);
    cout << "Keys in [15,45]: ";
    for (auto it = from; it != to; ++it) {
        cout << it->first << " ";
    }
    cout << "\n\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    demonstrateInsertion();
    demonstrateFindErase();
    demonstrateStructuredBindings();
    demonstrateFrequencyCounting();
    demonstrateMapBounds();
    firstNonRepeating();

    cout << "═══ KEY TAKEAWAYS ═══\n";
    cout << "1. map = sorted BST of key-value pairs, O(log n) all ops\n";
    cout << "2. m[key] creates default if not exist — use find() to check!\n";
    cout << "3. insert doesn't overwrite, [] does\n";
    cout << "4. for (auto& [k,v] : m) — structured binding for clean iteration\n";
    cout << "5. Frequency counting: for (auto x : arr) freq[x]++\n";
    cout << "6. Use map when you need sorted keys or lower_bound\n";

    return 0;
}

/*
 PRACTICE PROBLEMS:
 ──────────────────
 1. [CSES Sum of Two Values] https://cses.fi/problemset/task/1640
 2. [LC Group Anagrams]      https://leetcode.com/problems/group-anagrams/
 3. [CF Frequency Sort]      Custom comparator on frequency map
*/

